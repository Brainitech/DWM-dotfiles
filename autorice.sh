#!/bin/bash

echo "Checking for updates"

sudo pacman -Syu

echo "Installing Dependencies"

sudo pacman -S alacritty xorg lightdm lightdm-gtk-greeter linux linux-headers linux-firmware base-devel base pulseaudio pavucontrol flameshot rofi polybar code firefox cmake make nitrogen network-manager-applet notification-daemon plymouth thunar libreoffice-still vlc yajl

echo "Installing AUR helper"

cd /opt
sudo git clone https://aur.archlinux.org/yay-git.git
sudo chown -R brainiac:brainiac ./yay-git
cd yay-git
makepkg -si

sudo yay -Syu
yay -S nerd-fonts-git zscroll-git cava cmatrix-git plymouth-theme-arch-logo-new

echo "Copying configs"

cd
mkdir .config
cp -R ~/DWM-autorice/config/. .config

echo "Building DWM"
cd ~/.config/dwm 
sudo pacman -S jsoncpp
git clone https://github.com/mihirlad55/dwmipcpp
cd dwmipcpp
chmod +x build.sh
bash build.sh
cd ..
sudo make install
sudo cp ~/.config/polybar/scripts/dmenu_running_apps /usr/bin/chwin
sudo chmod +x /usr/bin/chwin
sudo cp ~/.config/low_battery.sh /usr/bin/batterycheck
sudo chmod +x /usr/bin/batterycheck


echo "Making display Manager"

cp -R ~/DWM-autorice/DM/. /etc/lightdm

cp -R ~/DWM-autorice/plymouth/. /etc/plymouth

echo "setting wallpaper"
cp -R ~/DWM-autorice/wallpapers/. /usr/share/pixmaps

cd ~/.config/polybar
chmod +x launch.sh
cd scripts
chmod +x ./*

sudo systemctl enable lightdm

echo "Restarting system"
sleep 5
reboot

