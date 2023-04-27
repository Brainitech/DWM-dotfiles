#!/bin/bash

( exec "~/.config/polybar/scripts/spotify_loop_update.sh" ) &

( exec "~/.config/polybar/scripts/vol_status.sh" ) &

# see man zscroll for documentation of the following parameters
zscroll -l 20 \
        --delay 0.1 \
        --scroll-padding "          " \
        --match-command "`dirname $0`/get_spotify_status.sh --status" \
        --match-text "Playing" "--scroll 1" \
        --match-text "Paused" "--scroll 0" \
        --update-check true "`dirname $0`/get_spotify_status.sh" &

wait