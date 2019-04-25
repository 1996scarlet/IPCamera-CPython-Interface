
# IPCamera-CPython-Interface-v4

## 这是什么东西（What is this）

> * 兼容主流海康和雄迈IPC的适用于C、C++和python2/3的帧数据获取接口
> * 简化海康和雄迈IPC连接、登录、注册回调、解码（FFMPEG）、取帧的步骤
> * 通过Ctypes支持python2和python3（编译时修改CMAKE的`TARGET_PYTHON_VERSION`）

## 近期更新（Recent update）

> * 添加对不同分辨率的摄像头的支持 并且支持在运行过程中动态切换分辨率
> * 现在可以在客户端取不同分辨率的帧数据
> * 现在在申请对象时会对buffer初始化 来防止取帧过快导致客户端崩溃
> * 为进一步优化取帧效率 启用了多线程解码

## 性能对比（Performance comparison）

![一张图看懂取帧接口版本差异](./introduction/different.png)

## 原理简要说明（Brief description of the principle）

![一张图看懂取帧接口处理流程](./introduction/process.png)

* [数据驱动层IPC取帧接口说明.pptx](数据驱动层IPC取帧接口说明.pptx)

## 接口调用方式（C/C++/Python）

* [海康IPC调用方式](hk_interface_v4/demo/README.md)
* [雄迈IPC调用方式](xm_interface_v4/demo/README.md)

## 环境要求（the environment require）

> 尽管本repo提供基于以下环境的预编译so文件

* `Ubuntu 18.04.X LTS`（或其他发行版本 要求Linux内核版本>=4.14）
* `Python 3`（建议使用3.7版本）
* `pip 3`（sudo apt install python3-pip）
* `Opencv 4.0.X`（源码编译 详见注意事项）
    1. `mkdir build`
    2. `cd ./build`
    3. `cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D OPENCV_ENABLE_NONFREE=ON -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules -D PYTHON_EXECUTABLE=/usr/bin/python3 -D BUILD_EXAMPLES=ON ..`
    4. `sudo make && make install`
* `FFmpeg 4.1.X`（源码编译 详见注意事项）
    1. `yasm/cosmic 1.3.0-2build1 amd64` (sudo apt install yasm)
    2. Type `./configure --enable-gpl --enable-nonfree --enable-pthreads --enable-libx264 --enable-shared` to create the configuration. A list of configure options is printed by running `configure --help`.
    3. Then type `make` to build FFmpeg. GNU Make 3.81 or later is required.
    4. Type `sudo make install` to install all binaries and libraries you built.
    5. Type `ffmpeg` to see configuration.

> 但还是建议额外安装以下依赖环境自行编译(无特殊版本要求)

* `gcc/g++/Cmake...`（sudo apt install build-essential cmake libssl-dev zlib1g-dev libncurses5-dev libncursesw5-dev libreadline-dev libsqlite3-dev libgdbm-dev libdb5.3-dev libbz2-dev libexpat1-dev liblzma-dev tk-dev libffi-dev）
* `python3-dev/python-dev`（sudo apt-get install python3-dev python-dev）
* `libx264-dev libvpx-dev`（sudo apt-get install libx264-dev libvpx-dev）
* [海康SDK-版本号: V5.3.5.2 build20171124](http://www.hikvision.com/cn/download_more_403.html "Title")
* [雄迈SDK-更新日期: 2018-06-26](https://download.xm030.cn/d/MDAwMDA3MzM "Title")

## 目录结构说明（Files-Tree）

* hk_interface - 存放海康接口源码、测试demo、SDK
* xm_interface - 存放雄迈接口源码、测试demo、SDK
* 每个关键子目录下都附带README文件

## 注意事项（Cautious）

* 使用内存管道方法配合`nginx_rtmp_module`推流延迟较高，需要低延迟推流可以考虑使用[基于类MJPEG协议的推流框架](...)
* 在Ubuntu 18.04上安装openCV可以参考[这个链接](https://www.pyimagesearch.com/2018/08/15/how-to-install-opencv-4-on-ubuntu/)
* 编译安装`ffmpeg`前需要设置`./configure --enable-gpl --enable-nonfree --enable-pthreads --enable-libx264 --enable-shared`来防止`opencv`编译过程无法引用动态库导致的`video.so`相关错误
* 编译安装`opencv`时若出现`xfeatures2d`相关错误，需要[重新下载`curl`](https://curl.haxx.se/download.html)并按照如下步骤编译安装
    1. cd /root/Downloads/curl
    2. ./configure --with-ssl
    3. make
    4. sudo make install
* 建议自行编译安装`opencv-python`来保持版本同步
    1. `cd ./opencv/build/python_loader`
    2. `python3 setup.py install`
    3. 或者通过`python3 setup.py build`命令 然后在`dist`文件夹下手动安装`opencv-4.0.1-py3.7.egg`
