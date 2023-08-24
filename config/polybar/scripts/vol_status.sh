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

    vol_status=$(pamixer --get-volume-human)
    
    if [[ "$vol_status" == *muted* ]]; then
        vupdate_hooks "$PARENT_BAR_PID" 4
    else
        percentage=$(echo "$vol_status" | sed 's/%.*//')  # Remove the percentage sign using sed
        vstatus=$((percentage))  # Convert to an integer using arithmetic expansion
        
        # Update hooks based on volume level
        if [[ "$vstatus" -ge 68 ]]; then
            vupdate_hooks "$PARENT_BAR_PID" 1
        elif [[ "$vstatus" -ge 34 && "$vstatus" -le 67 ]]; then
            vupdate_hooks "$PARENT_BAR_PID" 2
        elif [[ "$vstatus" -ge 0 && "$vstatus" -le 33 ]]; then
            vupdate_hooks "$PARENT_BAR_PID" 3
        fi
    fi

    sleep 1
    
done
