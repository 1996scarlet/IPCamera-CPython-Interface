# ICT-XMNet-xmcamera
## 雄迈SDK下载地址（XM-SDK Download Url）
This is the [download page](https://download.xm030.cn/d/MDAwMDA3MzM= "Title") .
注意：这个SDK对linux的支持较差 提供的说明文档和demo不够详细

## SDK使用方法 （How to use the SDK）
> 0.   定义`video.cpp`文件所在的文件夹为根目录。
> 1.   将SDK压缩包中的lib文件夹下的所有内容拷贝到根目录中。
> 2.   将SDK压缩包中的incCn文件夹下的`HCNetSDK.h`头文件拷贝到根目录中。
> 3.   (可选)将`LinuxPlayM4.h`和`PlayM4.h`拷贝到根目录中。

## 目录结构（Files-Tree）
> 0.   Demo_HK_PY - 封装后的python调用demo 通过CV2对解析后的H264图像序列进行显示
> 1.   PyCExt - 接口封装源文件
> 2.   目录下其他文件 - 用于测试雄迈API

## 使用前的准备（Pre-Works）
> 0.   安装FFMPEG
> 1.   安装OPENCV
> 2.   安装Python（可选）

## 注意事项 （Cautious）
> 0.   使用FFMPEG对视频帧进行解码时需要进行适当偏移 具体参见回调函数中的处理
> 1.   不要在回调函数中执行耗时操作 否则会导致解码出现问题
> 2.   使用FFMPEG解码回调数据时尽量使用旧版接口进行处理