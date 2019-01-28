# -*- coding: utf-8 -*-
import time
import cv2
import numpy as np

from pycext import IPCamera
cp = IPCamera("10.41.0.99", 8000, "admin", "humanmotion01", "")
cp.PrintInfo()  # 打印信息
cp.login()

cp.open()
time.sleep(2)

while True:
    cv2.imshow("OKOK", np.asarray(cp.queryframe('array')).reshape(1080,1920,3))
    cv2.waitKey(1)

cp.close()
