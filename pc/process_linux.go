package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
	"syscall"
	"time"
)

// Adopt orphaned SDK children in containers whose PID 1 does not reap them.
func enableChildReaping() error {
	_, _, err := syscall.Syscall6(syscall.SYS_PRCTL, 36, 1, 0, 0, 0, 0) // PR_SET_CHILD_SUBREAPER
	if err != 0 {
		return fmt.Errorf("supervision du moteur Android : %w", err)
	}
	return nil
}

func reapOwnedEngine(enginePID, launcherPID int) {
	if enginePID <= 1 || enginePID == launcherPID {
		return
	}
	deadline := time.Now().Add(3 * time.Second)
	for time.Now().Before(deadline) {
		var status syscall.WaitStatus
		pid, err := syscall.Wait4(enginePID, &status, syscall.WNOHANG, nil)
		if pid == enginePID || err == syscall.ECHILD {
			return
		}
		if err != nil && err != syscall.EINTR {
			return
		}
		time.Sleep(50 * time.Millisecond)
	}
}

func engineLockPID(path string) int {
	data, err := os.ReadFile(path)
	if err != nil {
		return 0
	}
	pid, err := strconv.Atoi(strings.Trim(string(data), "\x00\r\n "))
	if err != nil {
		return 0
	}
	return pid
}
