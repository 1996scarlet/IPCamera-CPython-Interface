# Export shared object to C++ in Linux

## 如何编译

```bash
mkdir build
cd build
cmake .. # gen the makefile
sudo make     # gen *.so
```

> 生成的`libHKCamera_v4.so`就在`/../sdk/lib`文件夹内

## API说明

> 针对C++程序的API

```C++
HKIPCamera(char *IP, int Port, char *UserName, char *Password); //构造函数
bool start(); //初始化变量 登录 注册回调 打开回调
bool stop(); //关闭回调 注销回调 登出 清除变量
cv::Mat current(); //获取当前帧
```

> 针对C和Python程序的扩展API

```C++
extern "C"
{
    HKIPCamera *HKIPCamera_init(char *ip, int port, char *name, char *pass); //扩展构造函数
    int HKIPCamera_start(HKIPCamera *hkcp); //初始化变量 登录 注册回调 打开回调
    int HKIPCamera_stop(HKIPCamera *hkcp); //关闭回调 注销回调 登出 清除变量
    void HKIPCamera_frame(HKIPCamera *hkcp, int rows, int cols, unsigned char *frompy); //获取当前帧
}
```
