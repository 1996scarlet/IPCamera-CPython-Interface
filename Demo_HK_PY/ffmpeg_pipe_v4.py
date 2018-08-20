# -*- coding: utf-8 -*-
import os, sys
import time
import cv2
import numpy as np

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

import subprocess as sp

proc = sp.Popen(command, stdin=sp.PIPE,shell=False)

image_dir = os.path.dirname(os.path.realpath(__file__)) + "/Temp"  # 路径不要修改

from pycext import IPCamera
cp = IPCamera("10.41.0.51", 8000, "admin", "humanmotion01", image_dir)
cp.PrintInfo()
cp.login()

cp.open()
time.sleep(2)

while True:
    frame = np.asarray(cp.queryframe('array')).reshape(1080,1920,3)
    #cv2.imshow("OKOK", frame)
    #cv2.waitKey(1)
    proc.stdin.write(frame.tostring())

cp.close()
