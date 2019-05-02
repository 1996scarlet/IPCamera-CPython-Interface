# Export shared object to C++ in Linux

## 如何编译

```shell
mkdir build
cd build
cmake .. # gen the makefile
sudo make     # gen *.so
```

> 生成的`libXMCamera_v4.so`就在`/../sdk/interface/`文件夹内

## API说明

> 针对C++程序的API

```C++
XMIPCamera(char *IP, int Port, char *UserName, char *Password); //构造函数
bool start(); //初始化变量 登录 注册回调 打开回调
bool stop(); //关闭回调 注销回调 登出 清除变量
cv::Mat current(); //获取当前帧
```

> 针对C和Python程序的扩展API

```C++
extern "C"
{
  XMIPCamera *XMIPCamera_init(char *ip, int port, char *name, char *pass); //扩展构造函数
  int XMIPCamera_start(XMIPCamera *xmcp); //初始化变量 登录 注册回调 打开回调
  int XMIPCamera_stop(XMIPCamera *xmcp); //关闭回调 注销回调 登出 清除变量
  void XMIPCamera_frame(XMIPCamera *xmcp, int rows, int cols, unsigned char *frompy); //获取当前帧
}
```