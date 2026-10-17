package main

import (
	"fmt"
	"syscall"
)

func acquireLock(path string) (func(), error) {
	p, err := syscall.UTF16PtrFromString(path)
	if err != nil {
		return nil, err
	}
	handle, err := syscall.CreateFile(p, syscall.GENERIC_READ|syscall.GENERIC_WRITE, 0, nil, syscall.OPEN_ALWAYS, syscall.FILE_ATTRIBUTE_NORMAL, 0)
	if err != nil {
		return nil, fmt.Errorf("le lanceur est deja ouvert ou son dossier est inaccessible : %w", err)
	}
	return func() { syscall.CloseHandle(handle) }, nil
}
