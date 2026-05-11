#!/bin/sh
SCRIPT_PATH="$(readlink -f "$0")"
ROOT_DIR="$(dirname "$SCRIPT_PATH")"
SHARE="$HOME/.local/share"
mkdir -p "$HOME/.local/share"
DATA_DIR="$ROOT_DIR/data"
WTF_DATA_DIR="$SHARE/wtf-is"
ln -s "$DATA_DIR" "$WTF_DATA_DIR"
echo "Created a symbolic link to $DATA_DIR at $WTF_DATA_DIR"
