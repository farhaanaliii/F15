#!/usr/bin/env bash
set -e

# --- Config ---
VERSION="0.0.1"
EXEC_PATH="build/f15"
if [ "$OS" = "windows" ]; then
    EXEC_PATH="${EXEC_PATH}.exe"
else
    EXEC_PATH="$EXEC_PATH"
fi
DIST_DIR="dist"

# Detect OS
OS="$(uname -s | tr '[:upper:]' '[:lower:]')"
case "$OS" in
    linux*)   OS="linux" ;;
    darwin*)  OS="darwin" ;;
    msys*|mingw*|cygwin*) OS="windows" ;;
    *)        OS="unknown" ;;
esac

# Detect ARCH
ARCH="$(uname -m)"
case "$ARCH" in
    x86_64) ARCH="x86_64" ;;
    arm64|aarch64) ARCH="arm64" ;;
    *) ARCH="unknown" ;;
esac

# Final zip name
ZIP_NAME="F15-v${VERSION}-${OS}-${ARCH}.zip"

# --- Build Release ---
echo "[*] Building release..."
make clean
make release

# --- Prepare dist folder ---
echo "[*] Preparing dist folder..."
rm -rf "$DIST_DIR"
mkdir -p "$DIST_DIR"

# Copy executable (add .exe for windows)
if [ "$OS" = "windows" ]; then
    cp "${EXEC_PATH}.exe" "$DIST_DIR/f15.exe"
else
    cp "$EXEC_PATH" "$DIST_DIR/f15"
fi

# Optionally copy readme or examples
cp README.md "$DIST_DIR/" 2>/dev/null || true
cp hello.f15 "$DIST_DIR/" 2>/dev/null || true

# --- Create ZIP ---
echo "[*] Creating ZIP archive: $ZIP_NAME"
cd "$DIST_DIR"
zip -r "../$ZIP_NAME" ./*
cd ..

echo "[+] Release package created: $ZIP_NAME"
