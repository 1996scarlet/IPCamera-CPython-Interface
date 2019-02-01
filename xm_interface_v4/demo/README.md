
# 雄迈IPC取帧接口测试demo

## C++的调用方式

```C++
XMIPCamera *xmcp = new XMIPCamera("ip", port, "name", "pass");
cout << *xmcp << endl;
xmcp->start();

sleep(2);
for (auto i = 0; i < 5; i++)
{
    imshow("display", xmcp->current());
    waitKey(1);
}

xmcp->stop();
delete (xmcp);
```

## C的调用方式

```C
XMIPCamera *c_xmcp = XMIPCamera_init("10.41.0.208", 34567, "admin", "");
XMIPCamera_start(c_xmcp);

sleep(2);
for (auto i = 0; i < 50; i++)
{
    imshow("c_display", c_xmcp->current());
    waitKey(1);
}

XMIPCamera_stop(c_xmcp);
free c_xmcp;
```

## Python的调用方式

> 首先引用so文件

```Python
lib = C.cdll.LoadLibrary('../sdk/interface/libXMCamera_v4.so')
```

> （可选）定义一个封装类

```Python
class XMIPCamera(object):

    def __init__(self, ip, port, name, password):
        self.obj = lib.XMIPCamera_init(ip, port, name, password)

    def start(self):
        lib.XMIPCamera_start(self.obj)

    def stop(self):
        lib.XMIPCamera_stop(self.obj)

    def frame(self, rows=1080, cols=1920):
        res = np.zeros(dtype=np.uint8, shape=(rows, cols, 3))

        lib.XMIPCamera_frame(self.obj, rows, cols,
                             res.ctypes.data_as(C.POINTER(C.c_ubyte)))

        return res
```

> 初始化并调用 注意：`b'IP'`中的`b`不可省略

```Python
xmcp = XMIPCamera(b'IP', PORT, b'NAME', b'PASS')
xmcp.start()

# start_time = time.time()

for i in range(1000):
    cv2.imshow("", xmcp.frame())
    cv2.waitKey(1)
    # cp.frame()

# print(time.time() - start_time)
xmcp.stop()
```