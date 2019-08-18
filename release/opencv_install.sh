#!/bin/sh

read -p "Enter the version of opencv [4.1.1]: " CV_VERSION
CV_VERSION=${CV_VERSION:-4.1.1}
echo $"Opencv $CV_VERSION Building Scripts 2019.07.03 by 1996scarlet@gmail.com"
cwd=$(pwd)

#1: Install OpenCV 4 dependencies on Ubuntu
sudo apt -y update
sudo apt -y upgrade
sudo apt -y remove x264 libx264-dev

sudo apt -y install build-essential checkinstall cmake pkg-config yasm
sudo apt -y install git gfortran
sudo apt -y install libjpeg8-dev libpng-dev
 
sudo apt -y install software-properties-common
sudo add-apt-repository "deb http://security.ubuntu.com/ubuntu xenial-security main"
sudo apt -y update
 
sudo apt -y install libjasper1
sudo apt -y install libtiff-dev
 
sudo apt -y install libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev
sudo apt -y install libxine2-dev libv4l-dev
cd /usr/include/linux
sudo ln -s -f ../libv4l1-videodev.h videodev.h
cd "$cwd"
 
sudo apt -y install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
sudo apt -y install libgtk2.0-dev libtbb-dev qt5-default
sudo apt -y install libatlas-base-dev
sudo apt -y install libfaac-dev libmp3lame-dev libtheora-dev
sudo apt -y install libvorbis-dev libxvidcore-dev
sudo apt -y install libopencore-amrnb-dev libopencore-amrwb-dev
sudo apt -y install libavresample-dev
sudo apt -y install x264 v4l-utils
 
# Optional dependencies
sudo apt -y install libprotobuf-dev protobuf-compiler
sudo apt -y install libgoogle-glog-dev libgflags-dev
sudo apt -y install libgphoto2-dev libeigen3-dev libhdf5-dev doxygen
sudo apt -y install python3.7-dev python3-pip
sudo apt -y install python3-testresources
sudo cp ./opencv.pc /usr/local/lib/pkgconfig/

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
cmake -D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D WITH_CUDA=ON \
-D BUILD_opencv_cudacodec=OFF \
-D ENABLE_FAST_MATH=1 \
-D CUDA_FAST_MATH=1 \
-D INSTALL_C_EXAMPLES=ON \
-D INSTALL_PYTHON_EXAMPLES=ON \
-D WITH_TBB=ON \
-D WITH_V4L=ON \
-D WITH_QT=ON \
-D WITH_OPENGL=ON \
-D WITH_CUBLAS=1 \
-D OPENCV_ENABLE_NONFREE=ON \
-D BUILD_opencv_python3=ON \
-D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
-D PYTHON_EXECUTABLE=/usr/bin/python3 \
-D BUILD_EXAMPLES=ON ..
make -j12
sudo make install
sudo ldconfig
# pip3 install -U opencv-python opencv-contrib-python --user
