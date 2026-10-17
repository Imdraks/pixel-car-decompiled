package main

import (
	"archive/zip"
	"crypto/sha1"
	"crypto/sha256"
	"encoding/hex"
	"errors"
	"fmt"
	"io"
	"net/http"
	"os"
	"path/filepath"
	"strings"
	"time"
)

type artifact struct {
	Name, URL, SHA1, Destination, Required string
	Size                                   int64
}

var platformArchives = map[string][]artifact{
	"windows": {
		{"emulator", "https://dl.google.com/android/repository/emulator-windows_x64-16428233.zip", "488ed747e82de7e9bb5247becd1ac043c7e5e85d", ".", "emulator/emulator.exe", 455342868},
		{"platform-tools", "https://dl.google.com/android/repository/platform-tools_r37.0.1-win.zip", "e03e78b1d80b396f1c3358e31251cb31740e1110", ".", "platform-tools/adb.exe", 8044989},
	},
	"linux": {
		{"emulator", "https://dl.google.com/android/repository/emulator-linux_x64-16428233.zip", "cd7362ea55dfb86a418958138dc396e74165dd01", ".", "emulator/emulator", 349654171},
		{"platform-tools", "https://dl.google.com/android/repository/platform-tools_r37.0.1-linux.zip", "477254aa5f903c15cf51001717bdf347fb6b53e0", ".", "platform-tools/adb", 9054187},
	},
}

var systemArchive = artifact{"android-25", "https://dl.google.com/android/repository/sys-img/android/x86-25_r01.zip", "78ce7eb1387d598685633b9f7cbb300c3d3aeb5f", "system-images/android-25/default", "system-images/android-25/default/x86/system.img", 316695942}

func checkArchive(path string, a artifact) error {
	f, err := os.Open(path)
	if err != nil {
		return err
	}
	defer f.Close()
	h := sha1.New()
	n, err := io.Copy(h, f)
	if err != nil {
		return err
	}
	if n != a.Size || hex.EncodeToString(h.Sum(nil)) != a.SHA1 {
		return fmt.Errorf("integrite invalide : %s", a.Name)
	}
	return nil
}

func download(a artifact, cache string) (string, error) {
	path := filepath.Join(cache, a.Name+".zip")
	if checkArchive(path, a) == nil {
		return path, nil
	}
	if err := os.MkdirAll(cache, 0700); err != nil {
		return "", err
	}
	temp := path + ".partial"
	f, err := os.OpenFile(temp, os.O_CREATE|os.O_TRUNC|os.O_WRONLY, 0600)
	if err != nil {
		return "", err
	}
	defer os.Remove(temp)
	client := &http.Client{Timeout: 45 * time.Minute, CheckRedirect: func(r *http.Request, via []*http.Request) error {
		if r.URL.Scheme != "https" || len(via) > 10 {
			return errors.New("redirection HTTPS refusee")
		}
		return nil
	}}
	fmt.Printf("Telechargement %s (%.0f Mo)...\n", a.Name, float64(a.Size)/1e6)
	resp, err := client.Get(a.URL)
	if err != nil {
		f.Close()
		return "", err
	}
	defer resp.Body.Close()
	if resp.StatusCode != http.StatusOK {
		f.Close()
		return "", fmt.Errorf("telechargement %s : HTTP %d", a.Name, resp.StatusCode)
	}
	buf := make([]byte, 1024*1024)
	var total int64
	last := time.Now()
	for {
		n, readErr := resp.Body.Read(buf)
		if n > 0 {
			if _, err = f.Write(buf[:n]); err != nil {
				f.Close()
				return "", err
			}
			total += int64(n)
		}
		if total > a.Size {
			f.Close()
			return "", errors.New("telechargement plus grand que la taille attendue")
		}
		if time.Since(last) > 3*time.Second {
			fmt.Printf("  %s : %.0f %%\n", a.Name, 100*float64(total)/float64(a.Size))
			last = time.Now()
		}
		if readErr == io.EOF {
			break
		}
		if readErr != nil {
			f.Close()
			return "", readErr
		}
	}
	if err = f.Close(); err != nil {
		return "", err
	}
	if err = checkArchive(temp, a); err != nil {
		return "", err
	}
	if err = os.Rename(temp, path); err != nil {
		return "", err
	}
	return path, nil
}

func extractZIP(source, destination string) error {
	z, err := zip.OpenReader(source)
	if err != nil {
		return err
	}
	defer z.Close()
	root, err := filepath.Abs(destination)
	if err != nil {
		return err
	}
	var total uint64
	for _, entry := range z.File {
		name := strings.ReplaceAll(entry.Name, "\\", "/")
		if strings.Contains(name, ":") || strings.HasPrefix(name, "/") || entry.Mode()&os.ModeSymlink != 0 {
			return fmt.Errorf("chemin ZIP refuse : %s", name)
		}
		target := filepath.Join(root, filepath.FromSlash(name))
		rel, err := filepath.Rel(root, target)
		if err != nil || rel == ".." || strings.HasPrefix(rel, ".."+string(os.PathSeparator)) {
			return fmt.Errorf("chemin ZIP hors dossier : %s", name)
		}
		if entry.UncompressedSize64 > 8<<30 || total > 8<<30-entry.UncompressedSize64 {
			return errors.New("archive trop grande")
		}
		total += entry.UncompressedSize64
		if entry.FileInfo().IsDir() {
			if err = os.MkdirAll(target, 0700); err != nil {
				return err
			}
			continue
		}
		if err = os.MkdirAll(filepath.Dir(target), 0700); err != nil {
			return err
		}
		input, err := entry.Open()
		if err != nil {
			return err
		}
		mode := os.FileMode(0600)
		if entry.Mode()&0111 != 0 {
			mode = 0700
		}
		output, err := os.OpenFile(target, os.O_CREATE|os.O_EXCL|os.O_WRONLY, mode)
		if err != nil {
			input.Close()
			return err
		}
		_, copyErr := io.Copy(output, input)
		closeErr := output.Close()
		input.Close()
		if copyErr != nil {
			return copyErr
		}
		if closeErr != nil {
			return closeErr
		}
	}
	return nil
}

func prepareSDK(root, cache, host string) error {
	archives, ok := platformArchives[host]
	if !ok {
		return fmt.Errorf("plateforme non prise en charge : %s", host)
	}
	archives = append(append([]artifact{}, archives...), systemArchive)
	for _, a := range archives {
		marker := filepath.Join(root, ".verified-"+a.Name)
		contents, _ := os.ReadFile(marker)
		if string(contents) == a.SHA1 {
			if _, err := os.Stat(filepath.Join(root, a.Required)); err == nil {
				continue
			}
		}
		path, err := download(a, cache)
		if err != nil {
			return err
		}
		staging, err := os.MkdirTemp(root, ".install-")
		if err != nil {
			return err
		}
		if err = extractZIP(path, staging); err != nil {
			os.RemoveAll(staging)
			return err
		}
		entries, err := os.ReadDir(staging)
		if err != nil {
			os.RemoveAll(staging)
			return err
		}
		dest := filepath.Join(root, a.Destination)
		if err = os.MkdirAll(dest, 0700); err != nil {
			os.RemoveAll(staging)
			return err
		}
		for _, e := range entries {
			target := filepath.Join(dest, e.Name())
			if _, err = os.Stat(target); err == nil {
				os.RemoveAll(staging)
				return fmt.Errorf("installation existante incomplete dans %s ; dossier conserve", target)
			}
			if err = os.Rename(filepath.Join(staging, e.Name()), target); err != nil {
				os.RemoveAll(staging)
				return err
			}
		}
		os.RemoveAll(staging)
		if _, err = os.Stat(filepath.Join(root, a.Required)); err != nil {
			return err
		}
		if err = os.WriteFile(marker, []byte(a.SHA1), 0600); err != nil {
			return err
		}
	}
	return nil
}

func sha256sum(data []byte) string { h := sha256.Sum256(data); return hex.EncodeToString(h[:]) }
