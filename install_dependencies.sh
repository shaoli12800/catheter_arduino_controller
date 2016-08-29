#!/bin/bash
# Russell Jackson
# dependency installation for the catheter arduino controller on linux
# meant for Ubuntu.
# v 0.1

echo "Beginning Dependency Installation"

sudo apt-get --yes --force-yes install build-essential

sudo apt-get --yes --force-yes install libboost-dev libwgtk2.8-dev

sudo apt-get --yes --force-yes install arduino ardunio-core 

sudo usermod -a -G dialout $USER
