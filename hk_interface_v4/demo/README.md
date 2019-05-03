# 海康C++接口测试demo

## C++的调用方式

```C++
HKIPCamera *hkcp = new HKIPCamera("ip", port, "name", "pass");
cout << *hkcp << endl;
hkcp->start();

sleep(2);
for (auto i = 0; i < 5; i++)
{
    // #define MAX_FRAME_WIDTH 1920
    // #define MAX_FRAME_HEIGHT 1080
    // ROWS和COLS的值不能超过头文件中预设的最大值 默认540*960
    imshow("display", hkcp->current(ROWS, COLS));
    waitKey(1);
}

hkcp->stop();
delete (hkcp);
```

## C的调用方式

```C
HKIPCamera *c_hkcp = HKIPCamera_init("10.41.0.208", 34567, "admin", "");
HKIPCamera_start(c_hkcp);

sleep(2);
for (auto i = 0; i < 50; i++)
{
    // #define MAX_FRAME_WIDTH 1920
    // #define MAX_FRAME_HEIGHT 1080
    // ROWS和COLS的值不能超过头文件中预设的最大值 默认540*960
    imshow("c_display", c_hkcp->current(ROWS, COLS));
    waitKey(1);
}

HKIPCamera_stop(c_hkcp);
free c_hkcp;
```

## Python的调用方式

> 首先引用so文件

```Python
lib = C.cdll.LoadLibrary('../sdk/interface/libHKCamera_v4.so')
```

> （可选）定义一个封装类

```Python
class HKIPCamera(object):

    def __init__(self, ip, port, name, password):
        self.obj = lib.HKIPCamera_init(ip, port, name, password)

    def start(self):
        lib.HKIPCamera_start(self.obj)

    def stop(self):
        lib.HKIPCamera_stop(self.obj)

    def frame(self, rows=1080, cols=1920):
        res = np.zeros(dtype=np.uint8, shape=(rows, cols, 3))

        lib.HKIPCamera_frame(self.obj, rows, cols,
                             res.ctypes.data_as(C.POINTER(C.c_ubyte)))

        return res
```

> 初始化并调用 注意：`b'IP'`中的`b`不可省略

```Python
hkcp = HKIPCamera(b'IP', PORT, b'NAME', b'PASS')
hkcp.start()

# start_time = time.time()

for i in range(1000):
    cv2.imshow("", hkcp.frame())
    cv2.waitKey(1)
    # cp.frame()

# print(time.time() - start_time)
hkcp.stop()
```

## 海康错误代码FAQ

Q:运行时提示107错误？
A:需要将libHKCamera.so文件、执行文件和海康sdk文件(包括HCNetSDKCom文件夹)放在同一目录下。

```bash
.
|-- HCNetSDKCom
|   |-- libHCAlarm.so
|   |-- libHCCoreDevCfg.so
|   |-- libHCDisplay.so
|   |-- libHCGeneralCfgMgr.so
|   |-- libHCIndustry.so
|   |-- libHCPlayBack.so
|   |-- libHCPreview.so
|   |-- libHCVoiceTalk.so
|   |-- libStreamTransClient.so
|   |-- libSystemTransform.so
|   |-- libanalyzedata.so
|   `-- libiconv2.so
|-- 要执行的文件
|-- libAudioRender.so
|-- libHCCore.so
|-- libHKCamera.so
|-- libPlayCtrl.so
|-- libSuperRender.so
|-- libhcnetsdk.so
`-- libhpr.so
```

Q:运行时提示17错误？
A:一般情况下，这个错误会伴随`错误7`出现，需要检查构造函数的用户名、密码和端口是否有误。