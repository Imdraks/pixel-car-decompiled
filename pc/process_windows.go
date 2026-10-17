package main

func enableChildReaping() error                  { return nil }
func reapOwnedEngine(enginePID, launcherPID int) {}
func engineLockPID(path string) int              { return 0 }
