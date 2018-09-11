# ICT-HCNet-hkcamera
## 这是什么东西（What is this）
* 兼容主流海康网络摄像机（小型机、球机、追踪相机）的python接口
* 通过python进行海康相机连接、登录、取流、解码（FFMPEG）、取帧
* 支持python2和python3（编译时修改CMAKE即可）

## 海康SDK下载地址（HK-SDK Download Url）
This is the [download page](http://www.hikvision.com/cn/download_more_403.html "Title") .
版本号: V5.3.5.2 build20171124。将海康的SDK解压到/sdk文件夹下。

## SDK使用方法 （How to use the SDK）
> 0.   定义`video.cpp`文件所在的文件夹为根目录。
> 1.   将SDK压缩包中的lib文件夹下的所有内容拷贝到根目录中。
> 2.   将SDK压缩包中的incCn文件夹下的`HCNetSDK.h`头文件拷贝到根目录中。
> 3.   (可选)将`LinuxPlayM4.h`和`PlayM4.h`拷贝到根目录中。

## 目录结构（Files-Tree）
> 0.   Demo_HK_PY - 封装后的python调用demo 通过CV2对解析后的H264图像序列进行显示
> 1.   PyCExt - 接口封装源文件
> 2.   目录下其他文件 - 用于测试海康API

## 内存管道用法（python + ffmpeg -> rtmp）
> 0.   首先配置命令如下

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
    
> 1.   初始化子进程

```python
import subprocess as sp
proc = sp.Popen(command, stdin=sp.PIPE,shell=False)
```

> 2.   帧数据写入内存管道

```python
while True:
    frame = np.asarray(cp.queryframe('array')).reshape(1080,1920,3)
    #cv2.imshow("OKOK", frame)
    #cv2.waitKey(1)
    proc.stdin.write(frame.tostring())
```

## 注意事项 （Cautious）
