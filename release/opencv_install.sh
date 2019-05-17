#!/bin/sh

read -p "Enter the version of opencv [4.1.0]: " CV_VERSION
CV_VERSION=${CV_VERSION:-4.1.0}
echo $"Opencv $CV_VERSION Building Scripts 2019.05.03 by 1996scarlet@gmail.com"

#1: Install OpenCV 4 dependencies on Ubuntu
sudo apt update
sudo apt dist-upgrade
sudo apt install build-essential cmake unzip pkg-config
sudo apt install libjpeg-dev libpng-dev libtiff-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libx265-dev libvpx-dev
sudo apt install python3.7 python3.7-dev python3-pip libgtk-3-dev libatlas-base-dev gfortran
pip3 install numpy --user

#2: Download OpenCV 4
cd ~
wget -O opencv.zip https://github.com/opencv/opencv/archive/$CV_VERSION.zip
wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/$CV_VERSION.zip
unzip opencv.zip
unzip opencv_contrib.zip
mv opencv-$CV_VERSION opencv
mv opencv_contrib-$CV_VERSION opencv_contrib

#4: CMake and compile OpenCV 4 for Ubuntu
cd ~/opencv
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE\
-D CMAKE_INSTALL_PREFIX=/usr/local\
-D OPENCV_ENABLE_NONFREE=ON\
-D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules\
-D PYTHON_EXECUTABLE=/usr/bin/python3\
-D BUILD_EXAMPLES=OFF ..
make -j8
sudo make install
sudo ldconfig
pip3 install -U opencv-python opencv-contrib-python --user