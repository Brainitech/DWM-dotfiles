#!/usr/bin/env bash

## Author : Aditya Shakya (adi1090x)
## Mail : adi1090x@gmail.com
## Github : @adi1090x
## Reddit : @adi1090x

rofi_command="rofi -theme $HOME/.config/polybar/scripts/color.rasi"

# Options
shutdown="󰐥"
reboot="󰜉"
lock=""
suspend="󰤄"
logout="󰿅"

# Variable passed to rofi
options="$shutdown\n$reboot\n$lock\n$suspend\n$logout"

# Remapping movement
xmodmap -e "keycode 32 = Return"
xmodmap -e "keycode 44 = Down"
xmodmap -e "keycode 45 = Up"

chosen="$(echo -e "$options" | $rofi_command -dmenu -selected-row 0)"

# Reset Remapping
xmodmap -e "keycode 32 = o"
xmodmap -e "keycode 44 = j"
xmodmap -e "keycode 45 = k"

case $chosen in
    $shutdown)
	shutdown now
        ;;
    $reboot)
	reboot
        ;;
    $lock)
        dm-tool switch-to-greeter
        ;;
    $suspend)
	dm-tool switch-to-greeter && systemctl suspend &
        ;;
    $logout)
        killall dwm
        ;;
esac

