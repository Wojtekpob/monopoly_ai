#!/bin/bash

# Aktualizacja listy pakietów
sudo apt update

# Instalacja wymienionych pakietów
sudo apt install -y \
    libx11-dev \
    libgl1-mesa-dev \
    libudev-dev \
    libopenal-dev \
    libvorbis-dev \
    libflac-dev \
    libxrandr-dev \
    libxcursor-dev \
    libfreetype6-dev

sudo apt-get install pybind11-dev

sudo apt install python3-pip
sudo pip3 insatll python-neat

