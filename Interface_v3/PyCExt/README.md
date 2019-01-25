# Export c++ class to python2 or 3

# 如何编译
        mkdir build
        cd build
        cmake .. # gen the makefile
        make     # gen *.so

生成的`pycext.so`就在`/../Demo_HK_PY`文件夹内

# 切换Python版本
在`CmakeLists.txt`中修改`SET(TARGET_PYTHON_VERSION 3)`即可
修改后需要清除cmake缓存 否则修改无效

# 注意事项
编译时需要连接海康相关so文件
建议编译时的目录结构如下所示

.
├── build
├── CMakeLists.txt
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
├── HCNetSDK.h
├── libHCCore.so
├── libhcnetsdk.so
├── libhpr.so
├── PyIPCamera.cpp
├── pywrapper.cpp
└── readme.md

# 简单使用
        python3
        from pycext import IPCamera
        cp = IPCamera("IP",PORT,"USERNAME","PWD","DIR")
        cp.PrintInfo()

# 安装


# FAQ
Q:使用是报错“ImportError: dynamic module does not define init function (initpycext)”
A:使用的Python的版本与编译的Python的版本不一致。如编译的为Python 3,使用Python 2调用会报如上错误。

Q:运行时提示107错误？
A:需要将pycext.so文件和海康sdk文件放在同一目录下。

.
├── demo_v1.py
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
├── HCNetSDK.h
├── hk_demo_v2.py
├── libHCCore.so
├── libhcnetsdk.so
├── libhpr.so
├── pycext.so
├── py_disk_interface.py
├── README.md
└── Temp
