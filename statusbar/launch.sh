#!/bin/bash

# various constants & helper functions
LOG_FILE="/tmp/polybar.log"
CONFIG="$HOME"/.config/dwm/statusbar/bar.ini
BAR_NAME=main
THEME=${THEME:-colors-default}
echo "$THEME"
TMPFILE=$(mktemp /tmp/polybar.config.XXXXXX)

is_hidpi() {
  # default to no hidpi if can't determine product name
  [[ ! -f /sys/devices/virtual/dmi/id/product_name ]] && return 1
  case $(cat /sys/devices/virtual/dmi/id/product_name) in
    # add more product types here
    "21CBCTO1WW")
      return 0
      ;;
    *)
      return 1
      ;;
  esac
}

set_theme() {
  sed -i "s/colors-default/$THEME/" "$TMPFILE"
}

configure_hidpi() {
  sed -i "s/fonts-default/fonts-hidpi/" "$TMPFILE"
  sed -i "s/height=.*/height=40/" "$TMPFILE"
}

main() {
  killall -q polybar
  cat "$CONFIG" > "$TMPFILE"
  set_theme
  is_hidpi && configure_hidpi
  polybar -c "$TMPFILE" "$BAR_NAME" 2>&1 | tee -a "$LOG_FILE" & disown
}

main
