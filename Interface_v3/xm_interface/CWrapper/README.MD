# Export shared object to C++ in Linux

## 如何编译

```bash
mkdir build
cd build
cmake .. # gen the makefile
make     # gen *.so
```

> 生成的`libXMCamera.so`就在`/../sdk/lib`文件夹内

## API说明

> 构造函数

```C++
XMIPCamera(char *IP, int Port, char *UserName, char *Password);
```

> 登录

```C++
int login(); //返回0代表成功 返回-1并打印错误代码则代表失败
```

> 注册回调并开始解码

```C++
int open(); //返回0代表成功 返回-1并打印错误代码则代表失败
```

> 取帧

```C++
cv::Mat get_current_frame_mat(); //返回最新的已经处理完毕的帧数据
void start_real_play(int frames); //用于本地测试
```

> 注销回调、登出、销毁对象

```C++
int close(); //返回0代表成功 返回-1并打印错误代码则代表失败
```