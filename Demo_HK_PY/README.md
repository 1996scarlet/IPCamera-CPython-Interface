# How to Use HKCamera with Python

# 编译生成pycext.so
具体方法请见Pycext文件夹
也可以使用本目录下的pycext.so文件（python3 编译）

# 部署方式

文件结构如下所示 如果缺少so文件可能会发生107错误

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
        ├── libHCCore.so
        ├── libhcnetsdk.so
        ├── libhpr.so
        ├── pycext.so
        ├── readme.md
        └── Temp

# 简单使用
        python3
        from pycext import IPCamera
        cp = IPCamera("IP",PORT,"USERNAME","PWD","DIR")
        cp.PrintInfo()

# 直接从内存读取帧画面并通过cv2连续显示
        while True:
        cv2.imshow("OKOK", np.asarray(cp.queryframe('array')).reshape(1080,1920,3))
        cv2.waitKey(1)

# 通过cv2连续显示H264-stream中图像

        import os, time
        image_dir = os.path.dirname(os.path.realpath(__file__))+ "/Temp"

        from pycext import IPCamera
        cp = IPCamera("10.41.0.99",8000,"admin","humanmotion01",image_dir)
        cp.PrintInfo()
        cp.StratParsingStream()

        print("Starting Parsing Stream...")

        time.sleep(2)

        import cv2

        i = 0
        while i<2000:
        cv2.imshow('stream',cv2.imread(cp.GetDetentionFrame()))
        cv2.waitKey(1)
        i = i + 1

        cv2.destroyAllWindows()
        cp.StopParsingStream()
        print("Stoping Parsing Stream...")
        cp.close()
