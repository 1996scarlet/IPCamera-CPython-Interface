# -*- coding: utf-8 -*-
import os
import time
import cv2
import numpy as np

# print (cv2.imshow.__doc__)

# cvimage = cv2.imread("./a1.png")

# print (len(cvimage))

image_dir = os.path.dirname(os.path.realpath(__file__)) + "/Temp"  # 路径不要修改
from pycext import IPCamera
cp = IPCamera("10.41.0.99", 8000, "admin", "humanmotion01", image_dir)
cp.PrintInfo()  # 打印信息

cp.login()

cp.open()

time.sleep(200)
'''
i = 0
while(i < 200):
    cv2.imshow("OKOK", cv2.imread(cp.GetDetentionFrame()))
    cv2.waitKey(1)
    i = i+1
cv2.destroyAllWindows()
'''

# cp.GetCurrentionFrame()

# i = 0
# while i < 1:
#     print(cp.GetCurrentionFrame())
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
