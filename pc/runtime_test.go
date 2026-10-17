package main

import (
	"archive/zip"
	"crypto/sha1"
	"encoding/hex"
	"os"
	"path/filepath"
	"runtime"
	"testing"
)

func fixtureZIP(t *testing.T, name, contents string) string {
	t.Helper()
	path := filepath.Join(t.TempDir(), "fixture.zip")
	f, err := os.Create(path)
	if err != nil {
		t.Fatal(err)
	}
	z := zip.NewWriter(f)
	w, err := z.Create(name)
	if err != nil {
		t.Fatal(err)
	}
	if _, err = w.Write([]byte(contents)); err != nil {
		t.Fatal(err)
	}
	if err = z.Close(); err != nil {
		t.Fatal(err)
	}
	if err = f.Close(); err != nil {
		t.Fatal(err)
	}
	return path
}

func TestZIPRejectsEscapingPaths(t *testing.T) {
	for _, name := range []string{"../outside.txt", "safe/../../outside.txt", "..\\outside.txt", "/absolute.txt", "C:\\outside.txt"} {
		t.Run(name, func(t *testing.T) {
			parent := t.TempDir()
			dest := filepath.Join(parent, "sdk")
			if err := extractZIP(fixtureZIP(t, name, "bad"), dest); err == nil {
				t.Fatal("unsafe archive accepted")
			}
			if _, err := os.Stat(filepath.Join(parent, "outside.txt")); !os.IsNotExist(err) {
				t.Fatal("file escaped staging directory")
			}
		})
	}
}

func TestZIPPreservesExistingFiles(t *testing.T) {
	dest := t.TempDir()
	path := filepath.Join(dest, "keep.txt")
	if err := os.WriteFile(path, []byte("user data"), 0600); err != nil {
		t.Fatal(err)
	}
	if err := extractZIP(fixtureZIP(t, "keep.txt", "replacement"), dest); err == nil {
		t.Fatal("existing file overwritten")
	}
	b, _ := os.ReadFile(path)
	if string(b) != "user data" {
		t.Fatal("existing file changed")
	}
}

func TestZIPExtractsVerifiedContents(t *testing.T) {
	dest := t.TempDir()
	if err := extractZIP(fixtureZIP(t, "sdk/data.txt", "expected bytes"), dest); err != nil {
		t.Fatal(err)
	}
	b, err := os.ReadFile(filepath.Join(dest, "sdk/data.txt"))
	if err != nil || string(b) != "expected bytes" {
		t.Fatal("archive contents not recovered", err)
	}
}

func TestArtifactChecksumAndLength(t *testing.T) {
	path := filepath.Join(t.TempDir(), "download")
	contents := []byte("trusted artifact")
	sum := sha1.Sum(contents)
	a := artifact{Name: "test", SHA1: hex.EncodeToString(sum[:]), Size: int64(len(contents))}
	if err := os.WriteFile(path, contents, 0600); err != nil {
		t.Fatal(err)
	}
	if err := checkArchive(path, a); err != nil {
		t.Fatal(err)
	}
	contents[0] ^= 1
	os.WriteFile(path, contents, 0600)
	if err := checkArchive(path, a); err == nil {
		t.Fatal("corruption accepted")
	}
	os.WriteFile(path, contents[:len(contents)-1], 0600)
	if err := checkArchive(path, a); err == nil {
		t.Fatal("truncation accepted")
	}
}

func TestSingleLauncherLock(t *testing.T) {
	path := filepath.Join(t.TempDir(), "lock")
	release, err := acquireLock(path)
	if err != nil {
		t.Fatal(err)
	}
	second, err := acquireLock(path)
	if err == nil {
		second()
		release()
		t.Fatal("two launchers can hold the same state")
	}
	release()
	final, err := acquireLock(path)
	if err != nil {
		t.Fatal("lock was not released", err)
	}
	final()
}

func TestOfficialSDKInstallation(t *testing.T) {
	cache := os.Getenv("PCR_TEST_ARCHIVE_CACHE")
	if cache == "" {
		t.Skip("set PCR_TEST_ARCHIVE_CACHE to the verified official archive cache")
	}
	root := t.TempDir()
	if err := prepareSDK(root, cache, runtime.GOOS); err != nil {
		t.Fatal(err)
	}
	before, err := os.Stat(filepath.Join(root, systemArchive.Required))
	if err != nil {
		t.Fatal(err)
	}
	if err = prepareSDK(root, cache, runtime.GOOS); err != nil {
		t.Fatal("repeat setup failed", err)
	}
	after, err := os.Stat(filepath.Join(root, systemArchive.Required))
	if err != nil {
		t.Fatal(err)
	}
	if !before.ModTime().Equal(after.ModTime()) {
		t.Fatal("repeat setup replaced the verified system image")
	}
}

func TestOfficialWindowsSDKInstallation(t *testing.T) {
	cache := os.Getenv("PCR_TEST_WINDOWS_ARCHIVE_CACHE")
	if cache == "" {
		t.Skip("set PCR_TEST_WINDOWS_ARCHIVE_CACHE to validate the official Windows archive installation")
	}
	root := t.TempDir()
	if err := prepareSDK(root, cache, "windows"); err != nil {
		t.Fatal(err)
	}
	if err := prepareSDK(root, cache, "windows"); err != nil {
		t.Fatal("repeat Windows setup failed", err)
	}
}

func TestOfficialDownload(t *testing.T) {
	if os.Getenv("PCR_TEST_LIVE_DOWNLOAD") != "1" {
		t.Skip("set PCR_TEST_LIVE_DOWNLOAD=1 for the official HTTPS download check")
	}
	cache := t.TempDir()
	a := platformArchives["windows"][1]
	path, err := download(a, cache)
	if err != nil {
		t.Fatal(err)
	}
	if err = checkArchive(path, a); err != nil {
		t.Fatal(err)
	}
	before, err := os.Stat(path)
	if err != nil {
		t.Fatal(err)
	}
	if _, err = download(a, cache); err != nil {
		t.Fatal("cached download failed", err)
	}
	after, err := os.Stat(path)
	if err != nil {
		t.Fatal(err)
	}
	if !before.ModTime().Equal(after.ModTime()) {
		t.Fatal("verified cache was downloaded again")
	}
}
