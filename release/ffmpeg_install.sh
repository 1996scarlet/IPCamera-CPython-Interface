#!/bin/sh

read -p "Enter the version of FFMPEG [4.2]: " FFMPEG_VERSION
FFMPEG_VERSION=${FFMPEG_VERSION:-4.2}
echo $"FFMPEG $FFMPEG_VERSION Building Scripts 2019.08.13 by 1996scarlet@gmail.com"

#1: Install FFMPEG 4 dependencies on Ubuntu
sudo apt update
sudo apt dist-upgrade
sudo apt install build-essential cmake unzip pkg-config git -y
sudo apt install libjpeg-dev libpng-dev libtiff-dev libavcodec-dev libavformat-dev -y
sudo apt install libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libx265-dev libvpx-dev yasm -y
sudo apt install libopenmpi-dev openmpi-bin libfdk-aac-dev libass-dev libopus-dev libtheora-dev libvorbis-dev libssl-dev -y
sudo apt install frei0r-plugins frei0r-plugins-dev ladspa-sdk libaom-dev liblilv-dev libopenjp2-7 libopenjp2-7-dev -y
sudo apt install libbluray-dev libbs2b-dev libcaca-dev libcodec2-dev libgme-dev libgsm1-dev libmysofa-dev libopenjp2-tools -y
sudo apt install libopenmpt-dev libpulse-dev librsvg2-dev librubberband-dev libshine-dev libsoxr-dev libssh-dev libspeex-dev -y
sudo apt install libtwolame-dev libvidstab-dev libwavpack-dev libwebp-dev libzmq3-dev libzvbi-dev libopenal-dev -y
sudo apt install libomxil-bellagio-dev libjack-dev libsdl2-dev libsnappy-dev -y

#2: Download FFMPEG 4
cd ~
wget -O ffmpeg.zip https://codeload.github.com/FFmpeg/FFmpeg/zip/n$FFMPEG_VERSION
unzip ffmpeg.zip
mv FFmpeg-n$FFMPEG_VERSION ffmpeg

#4: Build and compile FFMPEG 4 for Ubuntu
cd ~/ffmpeg
git clone https://git.videolan.org/git/ffmpeg/nv-codec-headers.git
cd nv-codec-headers
make -j12
sudo make install -j12
cd ..

./configure --toolchain=hardened --libdir=/usr/lib/x86_64-linux-gnu --incdir=/usr/include/x86_64-linux-gnu --arch=amd64 --enable-gpl --disable-stripping --disable-filter=resample --enable-avisynth --enable-ladspa --enable-libaom --enable-libass --enable-libbluray --enable-libbs2b --enable-libcaca --enable-libcodec2 --enable-libfontconfig --enable-libfreetype --enable-libfribidi --enable-libgme --enable-libgsm --enable-libjack --enable-libopenjpeg --enable-libopenmpt --enable-libopus --enable-libpulse --enable-librsvg --enable-librubberband --enable-libshine --enable-libsnappy --enable-libsoxr --enable-libspeex --enable-libssh --enable-libtheora --enable-libtwolame --enable-libvidstab --enable-libvorbis --enable-libvpx --enable-libwavpack --enable-libwebp --enable-libx265 --enable-libxml2 --enable-libxvid --enable-libzmq --enable-libzvbi --enable-lv2 --enable-omx --enable-openal --enable-opengl --enable-sdl2 --enable-libdrm --enable-frei0r --enable-libx264 --enable-shared --enable-nonfree --enable-pthreads --enable-libfdk-aac --enable-cuda --enable-cuvid --enable-nvenc --enable-nonfree --enable-libnpp --extra-cflags=-I/usr/local/cuda/include --extra-ldflags=-L/usr/local/cuda/lib64
make -j12
sudo make install -j12
sudo ldconfig
ffmpeg
