#!/usr/bin/env python2

import cv2
import os
import sys
import numpy as np
import threading
import time

np.set_printoptions(precision=2)

from multiprocessing import Process, Manager, Lock
lock = Lock()
queue = Manager().Queue()

mydict = Manager().dict()
mydict["now_push_ip"] = "255.255.255.255"


def camera_detect(q, l, address):
    image_dir = os.path.dirname(os.path.realpath(__file__)) + "/" + address  # 路径不要修改

    from xmcext import IPCamera
    cp = IPCamera(address, 8000, "admin", "humanmotion01", image_dir)
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
                        os.system("mkdir ./{}/{}".format(address, nowSavingName))

                    cv2.imwrite(
                        './{}/{}/{:0>5d}.jpg'.format(address, nowSavingName, counter), frame)
                    counter += 1

                    break

            if (safe_counter != -1) or (len(contours) == 0):
                safe_counter += 1

            if (safe_counter > 50):
                if counter > 25:
                    os.system("ffmpeg -i ./{}/{}/%05d.jpg ./{}/{}.mp4".format(address, nowSavingName, address, nowSavingName))
                    os.system("rm -rf ./{}/{}".format(address, nowSavingName))
                elif counter < 5:
                    os.system("rm -rf ./{}/{}".format(address, nowSavingName))

                nowSavingName = None
                counter = 0
                safe_counter = 0

            pre_frame = gray_frame

        # cv2.imshow("OKOK", frame)
        # cv2.waitKey(1)
        proc.stdin.write(frame.tostring())

    cp.close()


if __name__ == '__main__':

    for address in ["192.168.0.201", "192.168.0.202"]:
        Process(target=camera_detect, args=(queue, lock, address, )).start()

    while True:
        pass
