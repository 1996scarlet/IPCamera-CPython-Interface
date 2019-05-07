#!/bin/sh

read -p "Enter the version of opencv [4.1.3]: " FFMPEG_VERSION
FFMPEG_VERSION=${FFMPEG_VERSION:-4.1.3}
echo $"Opencv $FFMPEG_VERSION Building Scripts 2019.05.03 by 1996scarlet@gmail.com"

#1: Install FFMPEG 4 dependencies on Ubuntu
sudo apt update
sudo apt dist-upgrade
sudo apt install build-essential cmake unzip pkg-config
sudo apt install libjpeg-dev libpng-dev libtiff-dev
sudo apt install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt install libxvidcore-dev libx264-dev libx265-dev libvpx-dev
sudo apt install yasm

#2: Download FFMPEG 4
cd ~
wget -O ffmpeg.zip https://codeload.github.com/FFmpeg/FFmpeg/zip/n$FFMPEG_VERSION
unzip ffmpeg.zip
mv FFmpeg-n$FFMPEG_VERSION ffmpeg

#4: Build and compile FFMPEG 4 for Ubuntu
cd ~/ffmpeg
./configure --enable-gpl --enable-nonfree --enable-pthreads --enable-libx264 --enable-libx265 --enable-shared
make -j8
sudo make install
sudo ldconfig
ffmpeg