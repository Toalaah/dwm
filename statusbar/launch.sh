#!/bin/bash

# various constants & helper functions
CONF_BASE="$HOME"/.config/dwm/statusbar
TEMP_FILE=/tmp/polybar.config

# environment variables injected into 'bar-base.ini'
# these default to a non-hidpi, non-laptop bar configuration.
export THEME_PATH="$CONF_BASE"/themes/colors-default.ini
export MODULE_PATH="$CONF_BASE"/module-layouts/default.ini
export FONT_PATH="$CONF_BASE"/font-config/fonts-default.ini

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
  sed -i "s/colors-default/$THEME/" "$TEMP_FILE"
}

configure_hidpi() {
  sed -i "s/fonts-default/fonts-hidpi/" "$TEMP_FILE"
  sed -i "s/height=.*/height=40/" "$TEMP_FILE"
}

main() {
  # ensure polybar insance is not already running
  killall -q polybar

  if is_hidpi; then
    export MODULE_PATH="$CONF_BASE"/module-layouts/laptop.ini
    export FONT_PATH="$CONF_BASE"/font-config/fonts-hidpi.ini
  fi

  envsubst < "$CONF_BASE"/bar-base.ini > "$TEMP_FILE"
  polybar -c "$TEMP_FILE" main 2>&1 | tee -a /tmp/polybar.log & disown
}

main
