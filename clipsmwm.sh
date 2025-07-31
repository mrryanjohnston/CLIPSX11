#!/usr/bin/env sh

DATA_DIR="${XDG_DATA_HOME:-$HOME/.local/share}/CLIPSX11"
[ -d "$DATA_DIR" ] || DATA_DIR="/usr/local/share/CLIPSX11"

CLIPSX11 -f2 "$DATA_DIR/clipsmwm.bat"
