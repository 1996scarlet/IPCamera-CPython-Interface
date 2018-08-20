# -*- coding: utf-8 -*-  
import cv2
import os, time

image_dir = os.path.dirname(os.path.realpath(__file__))+ "/Temp" # 路径不要修改

# cp.login() # 该方法已经实现 暂时不用 我的流解析方法还不完善 正在改进
# cp.open()

from pycext import IPCamera
cp = IPCamera("10.41.0.99",8000,"admin","humanmotion01",image_dir)
# IP PORT USERNAME PWD DIR
cp.PrintInfo() # 打印信息

cp.StratParsingStream() # 先用ffmpeg替代

print("Starting Parsing Stream...")

time.sleep(2) # 最好暂停一段时间让ffmpeg启动 否则会导致cv图像显示失败

### cp.GetDetentionFrame()会返回当前最新文件的路径 通过cv2可以连续显示
i = 0
while i<1000:
    cv2.imshow('stream',cv2.imread(cp.GetDetentionFrame()))
    cv2.waitKey(1)
    i = i + 1
### 

cv2.destroyAllWindows()
cp.StopParsingStream() # 通过kill加pidof销毁进程
print("Stoping Parsing Stream...")
cp.close() # 注销 释放资源

# while(True):
#     cv2.imshow('stream',cv2.imread(find_new_file(curr_dir)))
#     cv2.waitKey(0)
#     time.sleep(0.02)
