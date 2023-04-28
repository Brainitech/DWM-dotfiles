#!/bin/bash

while true; do
    PARENT_BAR=
    PARENT_BAR_PID=$(pgrep -a "polybar" | grep "$PARENT_BAR" | awk '{print $1}')
    
    #update hooks
    vupdate_hooks() {
        while IFS= read -r id
        do
            polybar-msg -p "$id" hook volume $2 $3 $4 1>/dev/null 2>&1
        done < <(echo "$1")
    }

    vol_status=$(pulseaudio-control output | awk '{print $1}')
    
    if [[ "$vol_status" == *'%{F#6'* ]]; then
        :
    else
        percentage=$(echo "$vol_status" | awk '{print $1}')  # Extract the percentage value using awk
        perc=${percentage%\%}  # Remove the percentage sign
        vstatus=$((perc))  # Convert to an integer using arithmetic expansion
        
        # Update hooks based on volume level
        if [[ "$vstatus" -ge 95 ]]; then
            vupdate_hooks "$PARENT_BAR_PID" 1
        elif [[ "$vstatus" -ge 50 && "$vstatus" -le 94 ]]; then
            vupdate_hooks "$PARENT_BAR_PID" 2
        elif [[ "$vstatus" -ge 0 && "$vstatus" -le 49 ]]; then
            vupdate_hooks "$PARENT_BAR_PID" 3
        fi
    fi

    sleep 1
    
done
