# How to Use HKCamera with Python

## 简单使用(easy_start.py)

```python
from pycext import IPCamera
cp = IPCamera("10.41.0.99", 8000, "admin", "humanmotion01", image_dir)
cp.PrintInfo()  # 打印信息
cp.login()
cp.open()
cp.close()
```

## 通过硬盘作为中间载体(disk_frame.py)

```python
cp.StratParsingStream() # 先用ffmpeg替代

time.sleep(2) # 最好暂停一段时间让ffmpeg启动 否则会导致cv图像显示失败
for _ in range(1000):
    cv2.imshow('stream',cv2.imread(cp.GetDetentionFrame()))
    cv2.waitKey(1)

cv2.destroyAllWindows()
cp.StopParsingStream() # 通过kill加pidof销毁进程
```

## 通过内存缓冲区作为中间载体(memory.py)

```python
while True:
    cv2.imshow("OKOK", np.asarray(cp.queryframe('array')).reshape(1080,1920,3))
    k = cv2.waitKey(1) & 0xff
    if k == ord('q') or k == 27:
        break
```

## 配合内存管道推流(ffmpeg_pipe.py)

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

## FAQ

Q:运行时报错“ImportError: dynamic module does not define init function (initpycext)”
A:使用的Python的版本与编译的Python的版本不一致。如编译的为Python 3,使用Python 2调用会报如上错误。

Q:运行时提示107错误？
A:需要将pycext.so文件和海康sdk文件放在同一目录下。

```bash
.
├── HCNetSDKCom
│   ├── libanalyzedata.so
│   ├── libHCAlarm.so
│   ├── libHCCoreDevCfg.so
│   ├── libHCDisplay.so
│   ├── libHCGeneralCfgMgr.so
│   ├── libHCIndustry.so
│   ├── libHCPlayBack.so
│   ├── libHCPreview.so
│   ├── libiconv2.so
│   ├── libStreamTransClient.so
│   └── libSystemTransform.so
├── 要执行的PY文件
├── HCNetSDK.h
├── libHCCore.so
├── libhcnetsdk.so
├── libhpr.so
├── pycext.so
```