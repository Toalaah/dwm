#!/bin/bash

LOG_FILE="/tmp/polybar.log"
CONFIG="$HOME"/.config/dwm/statusbar/bar.ini
BAR_NAME=main
THEME=${THEME:-colors-default}
echo "$THEME"

# kill polybar if already running
killall -q polybar

# make temporary polybar config with inserted theme
TMPFILE=$(mktemp /tmp/polybar.config.XXXXXX)
sed "s/colors-default/$THEME/" "$CONFIG" > "$TMPFILE"

# launch polybar
polybar -c "$TMPFILE" "$BAR_NAME" 2>&1 | tee -a "$LOG_FILE" & disown
