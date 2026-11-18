#!/usr/bin/env bash
set -euo pipefail
BINARY="bin/shae-ada-flight-calculator"
mkdir -p ~/.local/bin
cp "$BINARY" ~/.local/bin/
echo "Installed shae-ada-flight-calculator to ~/.local/bin"
