# -*- coding: utf-8 -*-
import os
import sys
import time
import cv2
import numpy as np
import threading

command = ['ffmpeg',
           '-y',
           '-f', 'rawvideo',
           '-vcodec', 'rawvideo',
           '-pix_fmt', 'bgr24',
           '-s', '1920x1080',
           '-i', '-',
           '-c:v', 'libx264',
           '-pix_fmt', 'yuv420p',
           '-preset', 'ultrafast',
           '-f', 'flv',
           'rtmp://127.0.0.1:1935/hls/livestream']

import subprocess as sp

proc = sp.Popen(command, stdin=sp.PIPE, shell=False)

image_dir = os.path.dirname(os.path.realpath(__file__)) + "/Temp"  # 路径不要修改

from pycext import IPCamera
cp = IPCamera("10.41.0.236", 8000, "admin", "humanmotion01", image_dir)
cp.PrintInfo()
cp.login()

cp.open()
time.sleep(2)

pre_frame = None

# isSavingFlag = False

nowSavingName = None

counter = 0

safe_counter = 0

while True:
    frame = np.asarray(cp.queryframe('array')).reshape(1080, 1920, 3)

    gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    gray_frame = cv2.resize(gray_frame, (500, 500))
    gray_frame = cv2.GaussianBlur(gray_frame, (21, 21), 0)

    if pre_frame is None:
        pre_frame = gray_frame
    else:
        img_delta = cv2.absdiff(pre_frame, gray_frame)
        thresh = cv2.threshold(img_delta, 25, 255, cv2.THRESH_BINARY)[1]
        thresh = cv2.dilate(thresh, None, iterations=2)
        image, contours, hierarchy = cv2.findContours(
            thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        for c in contours:
            if cv2.contourArea(c) > 1000:
                safe_counter = -1

                if nowSavingName is None:
                    nowSavingName = str(int(round(time.time() * 1000)))
                    os.system("mkdir ./Temp/{}".format(nowSavingName))

                cv2.imwrite(
                    './Temp/{}/{:0>5d}.jpg'.format(nowSavingName, counter), frame)
                counter += 1

                break

        if (safe_counter != -1) or (len(contours) == 0):
            safe_counter += 1

        if (safe_counter > 50):
            if counter > 25:
                os.system("ffmpeg -i ./Temp/{}/%05d.jpg ./Temp/{}.mp4".format(nowSavingName, nowSavingName))
                os.system("rm -rf ./Temp/{}".format(nowSavingName))
            elif counter < 5:
                os.system("rm -rf ./Temp/{}".format(nowSavingName))
                
            nowSavingName = None
            counter = 0
            safe_counter = 0

        pre_frame = gray_frame

    # cv2.imshow("OKOK", frame)
    # cv2.waitKey(1)
    proc.stdin.write(frame.tostring())

cp.close()
