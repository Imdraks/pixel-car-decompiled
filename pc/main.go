package main

import (
	"bufio"
	"context"
	"embed"
	"errors"
	"flag"
	"fmt"
	"net"
	"os"
	"os/exec"
	"os/signal"
	"path/filepath"
	"regexp"
	"runtime"
	"strconv"
	"strings"
	"time"
)

//go:embed payload/*.apk payload/manifest.json licenses/ANDROID-SDK-LICENSE.txt
var payload embed.FS

const packageID = "com.StudioFurukawa.PixelCarRacer"
const activity = packageID + "/" + packageID + ".RunnerActivity"

func main() {
	if err := run(); err != nil {
		fmt.Fprintln(os.Stderr, "\nEchec :", err)
		if runtime.GOOS == "windows" {
			fmt.Println("Appuyez sur Entree pour fermer.")
			bufio.NewReader(os.Stdin).ReadString('\n')
		}
		os.Exit(1)
	}
}

func run() error {
	original := flag.Bool("original", false, "Lancer le jeu original 1.2.5 au lieu du mod Unbound")
	software := flag.Bool("software", false, "Emulation CPU sans hyperviseur (lente)")
	headless := flag.Bool("headless", false, "Validation sans fenetre")
	accepted := flag.Bool("accept-sdk-license", false, "Accepter explicitement la licence Android SDK")
	dataArg := flag.String("data-dir", "", "Dossier des donnees et sauvegardes")
	sdkArg := flag.String("sdk-root", "", "SDK externe deja installe (developpement)")
	flag.Parse()
	if runtime.GOARCH != "amd64" {
		return errors.New("un PC x64 est requis")
	}
	variant := "unbound"
	avdName := "PCRUnboundPC_API25"
	label := "Unbound 1.1.80"
	if *original {
		variant = "original"
		avdName = "PCROriginalPC_API25"
		label = "Pixel Car Racer original 1.2.5"
	}
	fmt.Printf("Pixel Car Racer PC — %s\nExecution par compatibilite Android.\n\n", label)
	root := *dataArg
	if root == "" {
		cache, err := os.UserCacheDir()
		if err != nil {
			return err
		}
		root = filepath.Join(cache, "PixelCarRacerPC")
	}
	root, err := filepath.Abs(root)
	if err != nil {
		return err
	}
	if err = os.MkdirAll(root, 0700); err != nil {
		return err
	}
	unlock, err := acquireLock(filepath.Join(root, "launcher.lock"))
	if err != nil {
		return err
	}
	defer unlock()
	fmt.Println("Donnees et sauvegardes :", root)
	sdk := *sdkArg
	if sdk == "" {
		sdk = filepath.Join(root, "sdk")
		if err = os.MkdirAll(sdk, 0700); err != nil {
			return err
		}
		license := filepath.Join(root, "ANDROID-SDK-LICENSE.txt")
		text, _ := payload.ReadFile("licenses/ANDROID-SDK-LICENSE.txt")
		if err = os.WriteFile(license, text, 0600); err != nil {
			return err
		}
		if _, e := os.Stat(filepath.Join(root, "sdk-license-accepted")); e != nil {
			fmt.Println("Le premier lancement telecharge environ 780 Mo depuis dl.google.com.")
			fmt.Println("Conditions Google Android SDK :", license)
			if !*accepted {
				fmt.Println("Lisez ces conditions avant de continuer :")
				fmt.Println(string(text))
				fmt.Print("Acceptez-vous ces conditions ? Tapez OUI : ")
				answer, _ := bufio.NewReader(os.Stdin).ReadString('\n')
				if strings.TrimSpace(strings.ToUpper(answer)) != "OUI" {
					return errors.New("installation annulee ; conditions non acceptees")
				}
			}
			if err = os.WriteFile(filepath.Join(root, "sdk-license-accepted"), []byte(time.Now().UTC().Format(time.RFC3339)), 0600); err != nil {
				return err
			}
		}
		if err = prepareSDK(sdk, filepath.Join(root, "downloads"), runtime.GOOS); err != nil {
			return err
		}
	}
	sdk, err = filepath.Abs(sdk)
	if err != nil {
		return err
	}
	adb := filepath.Join(sdk, "platform-tools", "adb"+exeSuffix())
	emulator := filepath.Join(sdk, "emulator", "emulator"+exeSuffix())
	for _, path := range []string{adb, emulator, filepath.Join(sdk, systemArchive.Required)} {
		if _, err = os.Stat(path); err != nil {
			return err
		}
	}
	avdHome := filepath.Join(root, "avd")
	androidHome := filepath.Join(root, "android-user")
	for _, dir := range []string{avdHome, androidHome} {
		if err = os.MkdirAll(dir, 0700); err != nil {
			return err
		}
	}
	env := append(os.Environ(), "ANDROID_SDK_ROOT="+sdk, "ANDROID_HOME="+sdk, "ANDROID_AVD_HOME="+avdHome, "ANDROID_USER_HOME="+androidHome, "ANDROID_EMULATOR_HOME="+androidHome)
	avdDir := filepath.Join(avdHome, avdName+".avd")
	if err = os.MkdirAll(avdDir, 0700); err != nil {
		return err
	}
	ini := "avd.ini.encoding=UTF-8\npath=" + avdDir + "\ntarget=android-25\n"
	if err = os.WriteFile(filepath.Join(avdHome, avdName+".ini"), []byte(ini), 0600); err != nil {
		return err
	}
	config := "AvdId=" + avdName + "\navd.ini.encoding=UTF-8\nabi.type=x86\nhw.cpu.arch=x86\nimage.sysdir.1=system-images/android-25/default/x86/\ntag.id=default\ntag.display=Default\nhw.ramSize=1536\nhw.cpu.ncore=2\nhw.lcd.width=1280\nhw.lcd.height=720\nhw.lcd.density=160\nhw.keyboard=yes\nhw.mainKeys=no\nhw.gpu.enabled=yes\nhw.gpu.mode=swiftshader\nhw.audioInput=no\nhw.audioOutput=yes\nhw.sensors.orientation=no\ndisk.dataPartition.size=2048M\nshowDeviceFrame=no\nfastboot.forceColdBoot=yes\n"
	if err = os.WriteFile(filepath.Join(avdDir, "config.ini"), []byte(config), 0600); err != nil {
		return err
	}
	apkBytes, err := payload.ReadFile("payload/" + variant + ".apk")
	if err != nil {
		return err
	}
	apkPath := filepath.Join(root, variant+".apk")
	existing, _ := os.ReadFile(apkPath)
	if sha256sum(existing) != sha256sum(apkBytes) {
		if err = os.WriteFile(apkPath, apkBytes, 0600); err != nil {
			return err
		}
	}
	port, err := availablePort()
	if err != nil {
		return err
	}
	serial := "emulator-" + strconv.Itoa(port)
	gpuMode := "auto"
	if *headless || *software {
		gpuMode = "swiftshader"
	}
	args := []string{"-avd", avdName, "-port", strconv.Itoa(port), "-no-snapshot", "-no-boot-anim", "-no-metrics", "-gpu", gpuMode, "-feature", "-Vulkan", "-memory", "1536"}
	if *headless {
		args = append(args, "-no-window", "-no-audio", "-show-kernel", "-verbose")
	}
	check := exec.Command(emulator, "-accel-check")
	check.Env = env
	if *software || check.Run() != nil {
		args = append(args, "-accel", "off", "-cores", "1")
		fmt.Println("Mode CPU logiciel : le demarrage peut prendre plusieurs minutes.")
	} else {
		args = append(args, "-accel", "on", "-cores", "2")
	}
	logPath := filepath.Join(root, "emulator-"+variant+".log")
	log, err := os.OpenFile(logPath, os.O_CREATE|os.O_TRUNC|os.O_WRONLY, 0600)
	if err != nil {
		return err
	}
	defer log.Close()
	cmd := exec.Command(emulator, args...)
	cmd.Env = env
	cmd.Stdout = log
	cmd.Stderr = log
	if err = enableChildReaping(); err != nil {
		return err
	}
	if err = cmd.Start(); err != nil {
		return err
	}
	exited := make(chan error, 1)
	emulatorFinished := make(chan struct{})
	go func() { exited <- cmd.Wait(); close(emulatorFinished) }()
	adbRun := func(timeout time.Duration, args ...string) ([]byte, error) {
		ctx, cancel := context.WithTimeout(context.Background(), timeout)
		defer cancel()
		c := exec.CommandContext(ctx, adb, append([]string{"-s", serial}, args...)...)
		c.Env = env
		return c.CombinedOutput()
	}
	defer func() {
		enginePID := engineLockPID(filepath.Join(avdDir, "hardware-qemu.ini.lock"))
		adbRun(5*time.Second, "emu", "kill")
		// Let the emulator launcher reap QEMU and release the AVD lock.
		// Killing its parent immediately leaves an orphan and a stale lock.
		select {
		case <-emulatorFinished:
		case <-time.After(20 * time.Second):
			cmd.Process.Kill()
			<-emulatorFinished
		}
		reapOwnedEngine(enginePID, cmd.Process.Pid)
	}()
	interrupts := make(chan os.Signal, 1)
	signal.Notify(interrupts, os.Interrupt)
	defer signal.Stop(interrupts)
	fmt.Println("Demarrage du systeme de jeu...")
	deadline := time.Now().Add(15 * time.Minute)
	ready := false
	for time.Now().Before(deadline) {
		select {
		case e := <-exited:
			return fmt.Errorf("le moteur s'est ferme (%v). Journal : %s", e, logPath)
		case <-interrupts:
			return errors.New("demarrage annule")
		default:
		}
		out, e := adbRun(5*time.Second, "shell", "getprop", "sys.boot_completed")
		if e == nil && strings.TrimSpace(string(out)) == "1" {
			ready = true
			break
		}
		time.Sleep(2 * time.Second)
	}
	if !ready {
		return fmt.Errorf("delai de demarrage depasse. Journal : %s", logPath)
	}
	// The AOSP development image permits root ADB for multi-touch injection.
	// This affects only this owned virtual device, never a connected phone.
	rootOutput, rootErr := adbRun(30*time.Second, "root")
	if rootErr == nil && !strings.Contains(string(rootOutput), "cannot") {
		adbRun(30*time.Second, "wait-for-device")
	}
	for _, args := range [][]string{{"shell", "settings", "put", "system", "screen_off_timeout", "2147483647"}, {"shell", "input", "keyevent", "224"}, {"shell", "input", "keyevent", "82"}, {"shell", "settings", "put", "global", "window_animation_scale", "0"}, {"shell", "settings", "put", "global", "transition_animation_scale", "0"}} {
		adbRun(10*time.Second, args...)
	}
	var out []byte
	if installedAPKMatches(adbRun, sha256sum(apkBytes)) {
		fmt.Println("Jeu deja installe et verifie.")
	} else {
		fmt.Println("Installation du jeu (les sauvegardes existantes sont conservees)...")
		out, err = adbRun(10*time.Minute, "install", "--no-streaming", "-r", apkPath)
		if err != nil || !strings.Contains(string(out), "Success") {
			return fmt.Errorf("installation APK : %s (%v)", out, err)
		}
	}
	// Legacy GameMaker versions use the virtual SD card for saves. These
	// permissions apply only to this app in this isolated Android profile.
	if !*original {
		for _, permission := range []string{"android.permission.WRITE_EXTERNAL_STORAGE", "android.permission.READ_EXTERNAL_STORAGE"} {
			permissionOutput, permissionErr := adbRun(15*time.Second, "shell", "pm", "grant", packageID, permission)
			if permissionErr != nil || strings.Contains(string(permissionOutput), "Exception") {
				return fmt.Errorf("autorisation de sauvegarde Android : %s (%v)", permissionOutput, permissionErr)
			}
		}
	}
	out, err = adbRun(time.Minute, "shell", "am", "start", "-W", "-n", activity)
	if err != nil || strings.Contains(string(out), "Error:") {
		return fmt.Errorf("lancement : %s (%v)", out, err)
	}
	time.Sleep(10 * time.Second)
	out, err = adbRun(10*time.Second, "shell", "pidof", packageID)
	if err != nil || strings.TrimSpace(string(out)) == "" {
		crash, _ := adbRun(10*time.Second, "logcat", "-d", "-b", "crash")
		os.WriteFile(filepath.Join(root, "crash-"+variant+".log"), crash, 0600)
		return fmt.Errorf("le jeu s'est arrete ; voir les journaux dans %s", root)
	}
	fmt.Printf("Jeu demarre. Appareil : %s\nUtilisez la souris pour les commandes tactiles. Fermez la fenetre Android pour quitter.\n", serial)
	stopKeyboard, keyErr := startKeyboard(adb, serial, env, root, variant, avdName)
	if keyErr != nil {
		fmt.Println("Souris active ; clavier tactile indisponible :", keyErr)
	} else {
		defer stopKeyboard()
	}
	// Keep this process alive to own the emulator lifecycle and preserve save data.
	select {
	case err = <-exited:
		return err
	case <-interrupts:
		return nil
	}
}

func installedAPKMatches(run func(time.Duration, ...string) ([]byte, error), expected string) bool {
	out, err := run(30*time.Second, "shell", "pm", "path", packageID)
	if err != nil {
		return false
	}
	path := strings.TrimSpace(strings.TrimPrefix(strings.TrimSpace(string(out)), "package:"))
	if !regexp.MustCompile(`^/data/app/[A-Za-z0-9_./=+~\-]+/base\.apk$`).MatchString(path) {
		return false
	}
	// API 25 does not ship sha256sum. Hash the installed bytes on the host.
	out, err = run(90*time.Second, "exec-out", "cat", path)
	if err != nil {
		return false
	}
	return sha256sum(out) == expected
}

func exeSuffix() string {
	if runtime.GOOS == "windows" {
		return ".exe"
	}
	return ""
}
func availablePort() (int, error) {
	for p := 5560; p < 5680; p += 2 {
		a, e := net.Listen("tcp", fmt.Sprintf("127.0.0.1:%d", p))
		if e != nil {
			continue
		}
		b, e := net.Listen("tcp", fmt.Sprintf("127.0.0.1:%d", p+1))
		a.Close()
		if e == nil {
			b.Close()
			return p, nil
		}
	}
	return 0, errors.New("aucun port local libre pour le moteur")
}
