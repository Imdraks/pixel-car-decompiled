package main

import (
	"encoding/binary"
	"errors"
	"io"
	"math"
	"regexp"
	"strings"
)

type touchPoint struct{ X, Y float64 }

func touchPacket(slot int, p touchPoint, down bool) ([]byte, error) {
	if slot < 1 || slot > 10 || math.IsNaN(p.X) || math.IsNaN(p.Y) || p.X < 0 || p.X > 1 || p.Y < 0 || p.Y > 1 {
		return nil, errors.New("position tactile hors limites")
	}
	var packet []byte
	event := func(kind, code uint16, value int32) {
		// The pinned x86 Android image uses 32-bit userspace input_event records.
		b := make([]byte, 16)
		binary.LittleEndian.PutUint16(b[8:10], kind)
		binary.LittleEndian.PutUint16(b[10:12], code)
		binary.LittleEndian.PutUint32(b[12:16], uint32(value))
		packet = append(packet, b...)
	}
	event(3, 47, int32(slot))
	if down {
		event(3, 57, int32(slot))
		event(3, 53, int32(p.X*32767))
		event(3, 54, int32(p.Y*32767))
		event(3, 48, 1)
		event(3, 58, 1024)
	} else {
		event(3, 57, -1)
	}
	event(0, 0, 0)
	return packet, nil
}

func sendTouch(w io.Writer, slot int, p touchPoint, down bool) error {
	packet, err := touchPacket(slot, p, down)
	if err != nil {
		return err
	}
	n, err := w.Write(packet)
	if err == nil && n != len(packet) {
		return io.ErrShortWrite
	}
	return err
}

var touchDevicePattern = regexp.MustCompile(`add device\s+\d+:\s+(/dev/input/event\d+)\s+name:\s+"virtio_input_multi_touch_1"`)
var legacyTouchName = regexp.MustCompile(`name:\s*"qwerty2"`)
var eventDevicePath = regexp.MustCompile(`^\d+:\s+(/dev/input/event\d+)`)

func findTouchDevice(inventory string) (string, error) {
	m := touchDevicePattern.FindStringSubmatch(inventory)
	if len(m) == 2 {
		return m[1], nil
	}
	for _, block := range strings.Split(inventory, "add device ") {
		if !legacyTouchName.MatchString(block) || !strings.Contains(block, "ABS_MT_POSITION_X") || !strings.Contains(block, "ABS_MT_POSITION_Y") || !strings.Contains(block, "ABS_MT_SLOT") {
			continue
		}
		path := eventDevicePath.FindStringSubmatch(block)
		if len(path) == 2 {
			return path[1], nil
		}
	}
	return "", errors.New("surface tactile compatible introuvable")
}
