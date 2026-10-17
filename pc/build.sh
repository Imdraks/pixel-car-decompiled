#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
GO_BIN=${GO_BIN:-/workspace/tools/go/bin/go}
export GOCACHE=${GOCACHE:-/workspace/pc-runtime/go-cache}
export GOTOOLCHAIN=local
test -f payload/unbound.apk
test -f payload/original.apk
"$GO_BIN" test -v .
GOOS=windows GOARCH=amd64 "$GO_BIN" vet .
GOOS=windows GOARCH=amd64 "$GO_BIN" build -trimpath -ldflags '-s -w -buildid=' -o build/PixelCarRacerPC.exe .
"$GO_BIN" build -trimpath -o build/pixel-car-linux .
