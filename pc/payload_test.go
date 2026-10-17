package main

import (
	"context"
	"encoding/json"
	"os"
	"os/exec"
	"testing"
	"time"
)

func TestEmbeddedPayloadIdentity(t *testing.T) {
	raw, err := payload.ReadFile("payload/manifest.json")
	if err != nil {
		t.Fatal(err)
	}
	var manifest map[string]struct {
		SHA256 string `json:"sha256"`
	}
	if err = json.Unmarshal(raw, &manifest); err != nil {
		t.Fatal(err)
	}
	for _, name := range []string{"original", "unbound"} {
		data, err := payload.ReadFile("payload/" + name + ".apk")
		if err != nil {
			t.Fatal(err)
		}
		if len(manifest[name].SHA256) != 64 || sha256sum(data) != manifest[name].SHA256 {
			t.Fatal("embedded APK does not match the supplied artifact:", name)
		}
	}
}

func TestInstalledPayloadLive(t *testing.T) {
	serial, adb := os.Getenv("PCR_TEST_ADB_SERIAL"), os.Getenv("PCR_TEST_ADB")
	if serial == "" || adb == "" {
		t.Skip("set PCR_TEST_ADB_SERIAL and PCR_TEST_ADB to validate an owned test emulator")
	}
	variant := os.Getenv("PCR_TEST_VARIANT")
	if variant == "" {
		variant = "unbound"
	}
	data, err := payload.ReadFile("payload/" + variant + ".apk")
	if err != nil {
		t.Fatal(err)
	}
	run := func(timeout time.Duration, args ...string) ([]byte, error) {
		ctx, cancel := context.WithTimeout(context.Background(), timeout)
		defer cancel()
		return exec.CommandContext(ctx, adb, append([]string{"-s", serial}, args...)...).CombinedOutput()
	}
	if !installedAPKMatches(run, sha256sum(data)) {
		t.Fatal("installed APK is not recognized as byte-identical to the supplied payload")
	}
}
