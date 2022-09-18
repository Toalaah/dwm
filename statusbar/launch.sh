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

# if running onn laptop perform additional modifications to config
if [[ -f /sys/devices/virtual/dmi/id/chassis_vendor ]]; then
  VENDOR=$(cat /sys/devices/virtual/dmi/id/chassis_vendor)
  if [[ "$VENDOR" == "LENOVO" ]]; then
    sed -i \
      -e "s/height=.*/height=40/" \
      -e "s/JetBrains Mono:pixelsize=13;3/JetBrains Mono:pixelsize=20;3/" \
      -e "s/Hack Nerd Font Mono:size=17;3/Hack Nerd Font Mono:size=28;6/" \
      "$TMPFILE"
  fi
fi

# launch polybar
polybar -c "$TMPFILE" "$BAR_NAME" 2>&1 | tee -a "$LOG_FILE" & disown
