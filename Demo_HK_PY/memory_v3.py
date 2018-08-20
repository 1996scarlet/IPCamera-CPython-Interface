# -*- coding: utf-8 -*-
import os
import time
import cv2
import numpy as np

image_dir = os.path.dirname(os.path.realpath(__file__)) + "/Temp"  # 路径不要修改
from pycext import IPCamera
cp = IPCamera("10.41.0.51", 8000, "admin", "humanmotion01", image_dir)
cp.PrintInfo()  # 打印信息

cp.login()

cp.open()
time.sleep(2)


# x = np.zeros((1920*3*1080), dtype=np.uint8)
# print(x)

while True:
    cv2.imshow("OKOK", np.asarray(cp.queryframe('array')).reshape(1080,1920,3))
    cv2.waitKey(1)
# print (img)
# print(cp.GetCurrentionFrame())
# cp.GetCurrentionFrame()

#
# i = 0
# while i < 1:
#
#     # v = np.asarray(cp.GetCurrentionFrame())
#     # # print(v)
#     # cv2.imshow("OKOK", v)
#     # cv2.waitKey(2)
#     i = i+1
# i = 0
# while(i < 2):

#     # print (np.asarray(cp.queryframe('array'),dtype='uint8'))
#     # print ()
#     # print ()
#     # cp.queryframe('array')
#     # cv2.imshow("OKOK", cv2.imdecode(np.asarray(cp.queryframe('array'),
#     #                                            dtype="uint8").reshape(1080, 1920*3), cv2.IMREAD_COLOR))
#     # cv2.waitKey(2)

#     co = cp.queryframe('bytes')
#     print (type(co))

#     # cv2.imshow("OKOK", cv2.imdecode(np.asarray(cp.queryframe('array'), dtype="uint8"),0))
#     # cv2.waitKey(2)
#     i = i+1

# time.sleep(1)

cp.close()
