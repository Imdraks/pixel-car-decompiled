package main

import (
	"context"
	"encoding/json"
	"fmt"
	"math"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
	"sync"
	"syscall"
	"time"
	"unsafe"
)

var user32 = syscall.NewLazyDLL("user32.dll")
var foreground = user32.NewProc("GetForegroundWindow")
var windowText = user32.NewProc("GetWindowTextW")
var asyncKey = user32.NewProc("GetAsyncKeyState")
var cursorPosition = user32.NewProc("GetCursorPos")
var screenToClient = user32.NewProc("ScreenToClient")
var clientRect = user32.NewProc("GetClientRect")

type screenPoint struct{ X, Y int32 }
type screenRect struct{ Left, Top, Right, Bottom int32 }
type keyBind struct {
	Name string
	VK   uintptr
}

var gameKeys = []keyBind{{"Z", 0x5A}, {"W", 0x57}, {"S", 0x53}, {"Q", 0x51}, {"D", 0x44}, {"A", 0x41}, {"E", 0x45}, {"ESPACE", 0x20}, {"HAUT", 0x26}, {"BAS", 0x28}}

func pressed(key uintptr) bool { r, _, _ := asyncKey.Call(key); return r&0x8000 != 0 }
func gameWindow(name string) uintptr {
	h, _, _ := foreground.Call()
	if h == 0 {
		return 0
	}
	var title [512]uint16
	windowText.Call(h, uintptr(unsafe.Pointer(&title[0])), uintptr(len(title)))
	if !strings.Contains(syscall.UTF16ToString(title[:]), name) {
		return 0
	}
	return h
}
func pointInGame(window uintptr) (touchPoint, bool) {
	var p screenPoint
	var r screenRect
	ok, _, _ := cursorPosition.Call(uintptr(unsafe.Pointer(&p)))
	if ok == 0 {
		return touchPoint{}, false
	}
	ok, _, _ = screenToClient.Call(window, uintptr(unsafe.Pointer(&p)))
	if ok == 0 {
		return touchPoint{}, false
	}
	ok, _, _ = clientRect.Call(window, uintptr(unsafe.Pointer(&r)))
	if ok == 0 {
		return touchPoint{}, false
	}
	width, height := float64(r.Right-r.Left), float64(r.Bottom-r.Top)
	scale := math.Min(width/1280, height/720)
	if scale <= 0 {
		return touchPoint{}, false
	}
	x := (float64(p.X) - (width-1280*scale)/2) / (1280 * scale)
	y := (float64(p.Y) - (height-720*scale)/2) / (720 * scale)
	if x < 0 || x > 1 || y < 0 || y > 1 {
		return touchPoint{}, false
	}
	return touchPoint{x, y}, true
}

func startKeyboard(adb, serial string, env []string, root, variant, avdName string) (func(), error) {
	ctx, cancel := context.WithCancel(context.Background())
	inventoryCmd := exec.CommandContext(ctx, adb, "-s", serial, "shell", "getevent", "-lp")
	inventoryCmd.Env = env
	inventory, err := inventoryCmd.Output()
	if err != nil {
		cancel()
		return nil, err
	}
	device, err := findTouchDevice(string(inventory))
	if err != nil {
		cancel()
		return nil, err
	}
	probeCtx, probeCancel := context.WithTimeout(ctx, 10*time.Second)
	probe := exec.CommandContext(probeCtx, adb, "-s", serial, "shell", "-T", "cat > "+device)
	probe.Env = env
	probeOutput, probeErr := probe.CombinedOutput()
	probeCancel()
	if probeErr != nil {
		cancel()
		return nil, fmt.Errorf("surface tactile non accessible : %s (%w)", probeOutput, probeErr)
	}
	configPath := filepath.Join(root, "keyboard-"+variant+".json")
	bindings := map[string]touchPoint{}
	if data, err := os.ReadFile(configPath); err == nil {
		if err = json.Unmarshal(data, &bindings); err != nil {
			cancel()
			return nil, fmt.Errorf("configuration clavier invalide : %w", err)
		}
	}
	for _, p := range bindings {
		if math.IsNaN(p.X) || math.IsNaN(p.Y) || p.X < 0 || p.X > 1 || p.Y < 0 || p.Y > 1 {
			cancel()
			return nil, fmt.Errorf("configuration clavier hors limites : %s", configPath)
		}
	}
	stream := exec.CommandContext(ctx, adb, "-s", serial, "shell", "-T", "cat > "+device)
	stream.Env = env
	writer, err := stream.StdinPipe()
	if err != nil {
		cancel()
		return nil, err
	}
	if err = stream.Start(); err != nil {
		cancel()
		writer.Close()
		return nil, err
	}
	fmt.Println("Clavier : F8 dans la fenetre du jeu active/desactive le reglage des touches.")
	fmt.Println("Pour regler une touche : survolez le bouton du jeu, puis appuyez sur Z/W/S/Q/D/A/E/Espace/Haut/Bas. F8 pour jouer.")
	var stopOnce sync.Once
	done := make(chan struct{})
	go func() {
		defer close(done)
		defer writer.Close()
		defer stream.Wait()
		ticker := time.NewTicker(16 * time.Millisecond)
		defer ticker.Stop()
		previous := make([]bool, len(gameKeys))
		active := make([]bool, len(gameKeys))
		calibrating := false
		f8Previous := false
		release := func() {
			for i, on := range active {
				if on {
					sendTouch(writer, i+1, touchPoint{}, false)
					active[i] = false
				}
			}
		}
		defer release()
		for {
			select {
			case <-ctx.Done():
				return
			case <-ticker.C:
			}
			window := gameWindow(avdName)
			if window == 0 {
				release()
				for i := range previous {
					previous[i] = false
				}
				f8Previous = false
				continue
			}
			f8 := pressed(0x77)
			if f8 && !f8Previous {
				release()
				calibrating = !calibrating
				if calibrating {
					fmt.Println("Reglage clavier actif : survolez un bouton et appuyez sur la touche a lui attribuer.")
				} else {
					fmt.Println("Reglage termine. Les touches maintiennent les boutons ; la souris reste active.")
				}
			}
			f8Previous = f8
			for i, key := range gameKeys {
				down := pressed(key.VK)
				if calibrating {
					if down && !previous[i] {
						if p, ok := pointInGame(window); ok {
							bindings[key.Name] = p
							data, _ := json.MarshalIndent(bindings, "", "  ")
							if err = os.WriteFile(configPath, data, 0600); err != nil {
								fmt.Println("Impossible d'enregistrer le reglage clavier :", err)
							} else {
								fmt.Printf("Touche %s enregistree.\n", key.Name)
							}
						}
					}
				} else if down != active[i] {
					if p, ok := bindings[key.Name]; ok {
						if err = sendTouch(writer, i+1, p, down); err != nil {
							fmt.Println("Clavier tactile deconnecte ; utilisez la souris.")
							return
						}
						active[i] = down
					}
				}
				previous[i] = down
			}
		}
	}()
	return func() { stopOnce.Do(func() { cancel(); writer.Close(); <-done }) }, nil
}
