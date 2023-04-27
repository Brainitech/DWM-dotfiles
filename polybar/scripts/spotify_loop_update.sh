#!/bin/bash
while true; do

    PARENT_BAR=
    PARENT_BAR_PID=$(pgrep -a "polybar" | grep "$PARENT_BAR" | cut -d" " -f1)
    PLAYER="spotify"

    #update hooks
    lupdate_hooks() {
        while IFS= read -r id
        do
            polybar-msg -p "$id" hook spotify-loop $2 $3 $4 1>/dev/null 2>&1
        done < <(echo "$1")
    }

    # Get the current loop status of Spotify
    loop_status=$(playerctl --player=$PLAYER loop 2>/dev/null)
    lstatus=$loop_status

    if [[ "$lstatus" == "None" ]]; then
        lupdate_hooks "$PARENT_BAR_PID" 1
    elif [[ "$lstatus" == "Playlist" ]]; then
        lupdate_hooks "$PARENT_BAR_PID" 2
    elif [[ "$lstatus" == "Track" ]]; then
        lupdate_hooks "$PARENT_BAR_PID" 3
    elif [[ "$lstatus" == "" ]]; then
        lupdate_hooks "$PARENT_BAR_PID" 4
    fi
done