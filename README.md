
# IPCamera-CPython-Interface-v3

## 这是什么东西（What is this）

> * 兼容主流海康和雄迈网络摄像机（小型机、球机、追踪相机）的python接口
> * 通过python进行海康（雄迈）IP相机连接、登录、注册回调、解码（FFMPEG）、取帧
> * 支持python2和python3（编译时修改CMAKE的`TARGET_PYTHON_VERSION`）

## 取帧方法（The way to get frame）

```python
    from pycext import IPCamera # 引用`pycext.so`
    cp = IPCamera("ip", port, "username", "password", "") # port为整型数
    cp.PrintInfo() # 可选：打印信息
    cp.login() # 登录
    cp.open() # 注册回调

    time.sleep(2) # 等待第一个I帧处理完毕 推荐等待不小于1秒

    while True: # 如果CPU处理能力很强 建议设置循环等待间隔
        frame = np.asarray(cp.queryframe('array')).reshape(1080,1920,3)
        # 可选择安装：`opencv-python` 和 `opencv-contrib-python`
        cv2.imshow("OKOK", frame)
        cv2.waitKey(1)
```

## 配合内存管道推流（python + ffmpeg -> rtmp）

```python
    # 首先配置命令如下
    command = ['ffmpeg',
        '-y',
        '-f', 'rawvideo',
        '-vcodec','rawvideo',
        '-pix_fmt', 'bgr24',
        '-s', '1920x1080',
        '-i', '-',
        '-c:v', 'libx264',
        '-pix_fmt', 'yuv420p',
        '-preset', 'ultrafast',
        '-f', 'flv',
        'rtmp://10.41.0.147:1935/hls/livestream']

    # 初始化子进程
    import subprocess as sp
    proc = sp.Popen(command, stdin=sp.PIPE,shell=False)

    # 帧数据写入内存管道
    while True:
        frame = np.asarray(cp.queryframe('array')).reshape(1080,1920,3)
        proc.stdin.write(frame.tostring())
```

## 环境要求（the environment require）

> 尽管本repo提供基于以下环境的预编译so文件
* `Ubuntu 18.04.1 LTS`（国内镜像）
* `Python 3.6.X`（apt下载）
* `Opencv 3.4.X`（源码编译）
* `FFmpeg 3.4.X`（源码编译）

> 但还是建议额外安装以下依赖环境自行编译
* `numpy-dev`
* `python3-dev/python-dev`
* `Cmake`
* `gcc/g++`
* `libx264-dev`
* [海康SDK-版本号: V5.3.5.2 build20171124](http://www.hikvision.com/cn/download_more_403.html "Title")
* [雄迈SDK-版本号: V5.3.5.2 build20171124](http://www.hikvision.com/cn/download_more_403.html "Title")

## SDK文件夹使用方法 （How to use the SDK）

> 1. 定义`video.cpp`文件所在的文件夹为根目录。
> 2. 将SDK压缩包中的lib文件夹下的所有内容拷贝到根目录中。
> 3. 将SDK压缩包中的incCn文件夹下的`HCNetSDK.h`头文件拷贝到根目录中。
> 4. (可选)将`LinuxPlayM4.h`和`PlayM4.h`拷贝到根目录中。解压到对应目录的sdk文件夹下

## 目录结构（Files-Tree）

> 1. Demo_HK_PY - 封装后的python调用demo 通过CV2对解析后的H264图像序列进行显示
> 2. PyCExt - 接口封装源文件
> 3. 目录下其他文件 - 用于测试SDK

## 注意事项 （Cautious）

* 使用内存管道方法配合`nginx_rtmp_module`推流延迟较高，如果需要低延迟推流可以考虑使用[基于类MJPEG协议的推流框架](...)

* Solve this problem with flag --with-darwinssl
* Go to folder with [curl source code](https://curl.haxx.se/download.html)
    1. cd /root/Downloads/curl
    2. ./configure --with-ssl
    3. make
    4. sudo make install
* [Install openCV 4.0.0 in Ubuntu 18.04](https://www.pyimagesearch.com/2018/08/15/how-to-install-opencv-4-on-ubuntu/)
* ffmpeg 4.1 -> ./configure --enbale-shared
