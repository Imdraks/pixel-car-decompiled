package main

import (
	"encoding/binary"
	"math"
	"testing"
)

func TestTouchPressAndReleaseProtocol(t *testing.T) {
	p, err := touchPacket(2, touchPoint{.25, .75}, true)
	if err != nil {
		t.Fatal(err)
	}
	if len(p) != 7*16 {
		t.Fatalf("wrong event count: %d", len(p)/16)
	}
	expected := []struct {
		kind, code uint16
		value      int32
	}{{3, 47, 2}, {3, 57, 2}, {3, 53, 8191}, {3, 54, 24575}, {3, 48, 1}, {3, 58, 1024}, {0, 0, 0}}
	for i, want := range expected {
		event := p[i*16 : (i+1)*16]
		if binary.LittleEndian.Uint16(event[8:10]) != want.kind || binary.LittleEndian.Uint16(event[10:12]) != want.code || int32(binary.LittleEndian.Uint32(event[12:16])) != want.value {
			t.Fatalf("bad event %d", i)
		}
	}
	release, err := touchPacket(2, touchPoint{}, false)
	if err != nil || len(release) != 48 {
		t.Fatal("bad release", err)
	}
	if int32(binary.LittleEndian.Uint32(release[28:32])) != -1 {
		t.Fatal("tracking ID not released")
	}
}

func TestTouchRejectsInvalidCoordinatesAndSlots(t *testing.T) {
	for _, c := range []struct {
		slot int
		p    touchPoint
	}{{0, touchPoint{}}, {11, touchPoint{}}, {1, touchPoint{-1, 0}}, {1, touchPoint{0, 2}}, {1, touchPoint{math.NaN(), 0}}, {1, touchPoint{0, math.Inf(1)}}} {
		if _, err := touchPacket(c.slot, c.p, true); err == nil {
			t.Fatal("invalid touch accepted", c)
		}
	}
}

func TestTouchDeviceSelection(t *testing.T) {
	fixture := "add device 1: /dev/input/event0\n name: \"Power Button\"\nadd device 2: /dev/input/event2\n name: \"virtio_input_multi_touch_1\"\n"
	if path, err := findTouchDevice(fixture); err != nil || path != "/dev/input/event2" {
		t.Fatal("wrong touch device", path, err)
	}
	if _, err := findTouchDevice("add device 1: /dev/input/event0\n name: \"keyboard\""); err == nil {
		t.Fatal("keyboard selected as touchscreen")
	}
	legacy := "add device 2: /dev/input/event1\n  name:     \"qwerty2\"\n ABS_MT_SLOT ABS_MT_POSITION_X ABS_MT_POSITION_Y\n"
	if path, err := findTouchDevice(legacy); err != nil || path != "/dev/input/event1" {
		t.Fatal("legacy multitouch device not found", path, err)
	}
	if _, err := findTouchDevice("add device 2: /dev/input/event1\n name: \"qwerty2\"\n KEY_A KEY_B\n"); err == nil {
		t.Fatal("keyboard-only qwerty2 accepted")
	}
}
