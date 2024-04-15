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
