#!/bin/bash

previous_brightness=$(xbacklight -get)

while true; do
    battery_level=$(acpi -b | grep -P -o '[0-9]+(?=%)')
    battery_status=$(acpi -b | grep -P -o 'Charging|Discharging')
    
    if [ "$battery_level" -le 30 ] && [ "$battery_status" == "Discharging" ]; then
        # Reduce brightness to 50%
        xbacklight -set 50
        
        # Send notification
        notify-send "Battery is low: $battery_level%"
    elif [ "$battery_status" == "Charging" ]; then
        # Restore previous brightness
        xbacklight -set "$previous_brightness"
    fi
    
    # Wait for one minute before checking again
    sleep 60
done

