package main

import (
	"os"
	"os/exec"
	"strconv"
	"strings"
	"testing"
)

func TestOrphanedSDKChildIsReaped(t *testing.T) {
	if err := enableChildReaping(); err != nil {
		t.Fatal(err)
	}
	parent := exec.Command("sh", "-c", "sleep 0.1 & echo $!")
	output, err := parent.Output()
	if err != nil {
		t.Fatal(err)
	}
	child, err := strconv.Atoi(strings.TrimSpace(string(output)))
	if err != nil {
		t.Fatal(err)
	}
	reapOwnedEngine(child, parent.Process.Pid)
	if _, err = os.Stat("/proc/" + strconv.Itoa(child)); !os.IsNotExist(err) {
		t.Fatal("orphaned engine PID was not reaped", err)
	}
}
