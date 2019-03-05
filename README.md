
# IPCamera-CPython-Interface-v4

## 这是什么东西（What is this）

> * 兼容主流海康和雄迈IPC的适用于C、C++和python2/3的帧数据获取接口
> * 简化海康和雄迈IPC连接、登录、注册回调、解码（FFMPEG）、取帧的步骤
> * 通过Ctypes支持python2和python3（编译时修改CMAKE的`TARGET_PYTHON_VERSION`）

## 性能对比（Performance comparison）

![一张图看懂取帧接口版本差异](./introduction/different.png)

## 原理简要说明（Brief description of the principle）

![一张图看懂取帧接口处理流程](./introduction/process.png)

* [数据驱动层IPC取帧接口说明.pptx](./introduction/intro.pdf)

## 接口调用方式（C/C++/Python）

* [海康IPC调用方式](hk_interface_v4/demo/README.md)
* [雄迈IPC调用方式](xm_interface_v4/demo/README.md)

## 环境要求（the environment require）

> 尽管本repo提供基于以下环境的预编译so文件
* `Ubuntu 18.04.1 LTS`（国内镜像）
* `Python 3.6.X`（apt下载）
* `Opencv 4.0.X`（源码编译）
* `FFmpeg 4.1.X`（源码编译）

> 但还是建议额外安装以下依赖环境自行编译
* `numpy-dev`
* `python3-dev/python-dev`
* `Cmake`
* `gcc/g++`
* `libx264-dev`
* [海康SDK-版本号: V5.3.5.2 build20171124](http://www.hikvision.com/cn/download_more_403.html "Title")
* [雄迈SDK-更新日期: 2018-06-26](https://download.xm030.cn/d/MDAwMDA3MzM "Title")

## 目录结构说明（Files-Tree）

* hk_interface - 存放海康接口源码、测试demo、SDK
* xm_interface - 存放雄迈接口源码、测试demo、SDK
* 每个关键子目录下都附带README文件

## 注意事项（Cautious）

* 使用内存管道方法配合`nginx_rtmp_module`推流延迟较高，需要低延迟推流可以考虑使用[基于类MJPEG协议的推流框架](https://github.com/1996scarlet/MJPEG_Framework)
* 编译安装`ffmpeg`前需要设置`./configure --enbale-shared`来防止`opencv`编译过程无法引用动态库导致的`video.so`相关错误
* 编译安装`opencv`时若出现`xfeatures2d`相关错误，需要[重新下载`curl`](https://curl.haxx.se/download.html)并按照如下步骤编译安装
    1. cd /root/Downloads/curl
    2. ./configure --with-ssl
    3. make
    4. sudo make install
* 在Ubuntu 18.04上安装openCV可以参考[这个链接](https://www.pyimagesearch.com/2018/08/15/how-to-install-opencv-4-on-ubuntu/)
