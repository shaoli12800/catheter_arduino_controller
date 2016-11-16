#!/bin/bash
# Russell Jackson
# dependency installation for the catheter arduino controller on linux
# meant for Ubuntu.
# v 0.1

echo "Beginning Dependency Installation"

sudo apt-get --yes --force-yes install build-essential

sudo apt-get --yes --force-yes install libboost-dev libwxgtk2.8-dev
sudo apt-get --yes --force-yes install libwxgtk3.0-dev

sudo apt-get --yes --force-yes install arduino arduino-core 

sudo usermod -a -G dialout $USER
