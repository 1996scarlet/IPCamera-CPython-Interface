# -*- coding: utf-8 -*-
import os
import time
import cv2

from interface import HKIPCamera

hkcp = HKIPCamera(b"10.41.0.231", 8000, b"admin", b"humanmotion01")
hkcp.start()

while True:
    cv2.imshow("display", hkcp.frame(rows=540, cols=960))
    # cv2.imshow("display", hkcp.frame(rows=1080, cols=1920))
    k = cv2.waitKey(38) & 0xff
    if k == ord('q') or k == 27:
        break

'''
for i in range(1000):
    # cv2.imwrite("./ppl/%d.jpg" % i, hkcp.frame())
    # cv2.imshow("display", hkcp.frame(rows=540, cols=960))
    # cv2.waitKey(40)
    start_time = time.time()
    hkcp.frame()
    print(time.time() - start_time)

'''

hkcp.stop()
