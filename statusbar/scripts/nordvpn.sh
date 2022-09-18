#!/bin/sh

STATUS=$(nordvpn status | grep Status | tr -d ' ' | cut -d ':' -f2)

if [ "$STATUS" = "Connected" ]; then
    echo "🔒 $(nordvpn status | grep 'Current server' | cut -d ' ' -f3 | cut -d '.' -f1)"
else
    echo "🔓"
fi
