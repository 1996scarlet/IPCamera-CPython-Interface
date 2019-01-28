# Export c++ class to python2 or 3

## 如何编译

```bash
mkdir build
cd build
cmake .. # gen the makefile
make     # gen *.so
```

> 生成的`xmcext.so`就在`/../sdk/lib`文件夹内

## API说明

```python
# API原型
{"GetIP", 无参数, "Get the IP address of instance."},
{"GetPort", 无参数, "Get the port number of instance."},
{"GetUserName", 无参数, "Get the user name of isntance."},
{"GetPassword", 无参数, "Get the password of instance."},
{"GetParameters", 无参数, "Get all the properties of isntance."},
{"SetParameters", 需要参数, "Set the properties of instance."},
{"PrintInfo", 无参数, "Print all information of instance."},
{"login", 无参数, "login the camera"},
{"open", 无参数, "open the camera"},
{"isopen", 无参数, "is the camera opened."},
{"close", 无参数, "close the camera."},
{"read", 无参数, "query frame from camera."},
{"queryframe", 需要参数, "query frame from camera."},
{"StratParsingStream", 无参数, "Strat Parsing Stream With FFmpeg."},
{"StopParsingStream", 无参数, "Stop Parsing Stream With FFmpeg."},
{"GetDetentionFrame", 无参数, "Get Detention Frame (1500ms From Current)."},
{"GetCurrentionFrame", 无参数, "Get Currention Frame (100ms From Current)."},
```

```C++
static PyObject *CIPCamera_QueryFrame(CIPCamera *Self, PyObject *args)
static PyObject *CIPCamera_SetParameters(CIPCamera *Self, PyObject *pArgs)
```

## API调用示例

```python
from xmcext import XMCamera
cp = XMCamera("10.41.0.208",34567,"admin","",image_dir)
cp.login()
cp.open()
time.sleep(2)

while True:
    cv2.imshow("OKOK", np.asarray(cp.queryframe('array')).reshape(1080,1920,3))
    k = cv2.waitKey(1) & 0xff
    if k == ord('q') or k == 27:
        break
```

## 注意事项

* 在`CmakeLists.txt`中修改`SET(TARGET_PYTHON_VERSION 3)`即可切换Python版本
* 注意修改后需要清除cmake缓存 否则修改无效
* 编译时需要连接雄迈相关so文件
