#!/usr/bin/env python2

import cv2
import os
import numpy as np
import pickle
from sklearn.mixture import GMM
import openface
import dlib
import threading
import time
import requests

np.set_printoptions(precision=2)

from websocket_server import WebsocketServer
server = WebsocketServer(9998, "127.0.0.1")

from multiprocessing import Process, Manager, Lock
lock = Lock()
queue = Manager().Queue()

mydict = Manager().dict()
mydict["now_push_ip"] = "255.255.255.255"


invasion_subsys_name_pipe = "/tmp/invasion_subsys_name_pipe"


def new_client(client, server):
    print("New client connected and was given id %d" % client['id'])
    server.send_message_to_all("Hey all, a new client has joined us")


def client_left(client, server):
    print("Client(%d) disconnected" % client['id'])


def message_received(client, server, message):
    if len(message) > 200:
        message = message[:200]+'..'
    print("Client(%d) said: %s" % (client['id'], message))
    mydict["now_push_ip"] = message


def start_wensocket_server():
    server.set_fn_new_client(new_client)
    server.set_fn_client_left(client_left)
    server.set_fn_message_received(message_received)
    server.run_forever()


threading.Thread(target=start_wensocket_server, name='LoopThread').start()
print ('websocket server start listening at 9998 port')


def getRep(bgrImg, detector, net, alignment):
    rgbImg = cv2.resize(cv2.cvtColor(bgrImg, cv2.COLOR_BGR2RGB),
                        (480, 270), interpolation=cv2.INTER_CUBIC)

    bb = detector(cv2.resize(cv2.cvtColor(bgrImg, cv2.COLOR_BGR2GRAY),
                             (480, 270), interpolation=cv2.INTER_CUBIC), 0)

    # bb = []

    # threading.Thread(target=lambda: (

    # )).join()

    # threading.Thread(target=lambda: (
    #     bb=
    # )).join()

    # bb = alignment.getAllFaceBoundingBoxes(
    #     cv2.resize(cv2.cvtCo/lor(bgrImg, cv2.COLOR_BGR2GRAY), (480, 270), interpolation=cv2.INTER_CUBIC))

    if bb is None:
        return None

    alignedFaces = []
    for box in bb:
        alignedFaces.append(
            alignment.align(
                96,
                rgbImg,
                box,
                landmarkIndices=openface.AlignDlib.OUTER_EYES_AND_NOSE))

    if alignedFaces is None:
        raise Exception("Unable to align the frame")

    reps = []
    for alignedFace in alignedFaces:
        reps.append(net.forward(alignedFace))

    return (reps, bb)


def infer(img, clf_name, detector, net, alignment):
    with open(clf_name, 'r') as f:
        (le, clf) = pickle.load(f)

    repsAndBBs = getRep(img, detector, net, alignment)
    reps = repsAndBBs[0]
    bbs = repsAndBBs[1]
    persons = []
    confidences = []
    for rep in reps:
        try:
            rep = rep.reshape(1, -1)
        except:
            print ("No Face detected")
            return (None, None)
        predictions = clf.predict_proba(rep).ravel()
        maxI = np.argmax(predictions)
        persons.append(le.inverse_transform(maxI))

        confidences.append(predictions[maxI])

        if isinstance(clf, GMM):
            dist = np.linalg.norm(rep - clf.means_[maxI])
            # print("  + Distance from the mean: {}".format(dist))
            pass

    return (persons, confidences, bbs)


def camera_detect(q, l, address, detector, net, alignment):

    from xmcext import XMCamera
    cp = XMCamera(address, 34567, "admin", "", "")
    cp.login()
    cp.open()

    warning_counter = 0
    safe_counter = 0
    previous_exist_unknown_person = True
    clf_name = "simple" + address.split('.')[3] + ".pkl"
    # confidenceList = []

    danger_lock = False

    # video_name = ""
    counter = 0

    color = (0, 0, 0)

    while True:

        frame = np.asarray(cp.queryframe('array')).reshape(1080, 1920, 3)

        persons, confidences, bbs = infer(
            frame, clf_name, detector, net, alignment)

        # try:
        #     confidenceList.append('%.2f' % confidences[0])
        # except:
        #     pass

        if (persons)

        for i, c in enumerate(confidences):
            if c <= 0.5:
                persons[i] = "UNKNOW"

        exist_unknown_person = False

        send_safe = ""
        send_unsafe = ""

        for idx, person in enumerate(persons):

            if persons[idx] == "UNKNOW":
                exist_unknown_person = True
                send_unsafe += "{} @{:.2f}".format(person,
                                                   confidences[idx]) + "\n"
                color = (0, 0, 255)
            else:
                send_safe += "{} @{:.2f}".format(person,
                                                 confidences[idx]) + "\n"
                color = (0, 255, 0)

            cv2.rectangle(frame, (bbs[idx].left()*4, bbs[idx].top()*4),
                          (bbs[idx].right()*4, bbs[idx].bottom()*4), color, 2)

            cv2.putText(frame, "{}@{:.2f}".format(person, confidences[idx]),
                        (bbs[idx].left()*4, bbs[idx].top()*4+60), cv2.FONT_HERSHEY_SIMPLEX, 4.0, color, 4)

        if(str(persons) != '[]'):
            l.acquire()
            q.put(address+'&' + send_safe+'&'+send_unsafe)
            l.release()
            print (address+'&' + send_safe+'&'+send_unsafe)

            threading.Thread(target=lambda: (
                cv2.imwrite('./Temp/a{}.png'.format(counter % 32), frame)
                and
                cv2.imwrite('./Temp/Face/f{}.png'.format(counter % 32),
                            frame[bbs[0].top()*4:bbs[0].bottom()*4 + 1, bbs[0].left()*4:bbs[0].right()*4+1])
            )).start()

        if warning_counter > 15:

            l.acquire()
            q.put(address)
            if (not danger_lock):
                q.put("danger")
                danger_lock = True
                print ("danger at {}".format(address))

                # video_name = str(int(round(time.time() * 1000)))
                # os.mkdir('./' + video_name)
            l.release()
            # if (exist_unknown_person):
            #     threading.Thread(target=lambda: (cv2.imwrite('./Temp/a{}.png'.format(counter % 32), frame) and cv2.imwrite(
            #         './Temp/Face/f{}.png'.format(counter % 32), frame[bbs[idx].top()*4:bbs[idx].bottom()*4 + 1, bbs[idx].left()*4:bbs[idx].right()*4+1]))).start()
            # cv2.imwrite('./{}/{:0>5d}.jpg'.format(video_name, counter), frame)
            # cv2.imwrite('./Temp/{}.png'.format(counter), frame)
            # cv2.imwrite('./Temp/Face/{}.png'.format(counter), frame[bbs[idx].top()*4:bbs[idx].bottom()*4, bbs[idx].left()*4:bbs[idx].right()*4])
            counter += 1
            # video_writer.write(frame)
            # server.send_message_to_all(address)

        if exist_unknown_person and previous_exist_unknown_person:
            warning_counter = warning_counter + 1

        elif ((not exist_unknown_person) and (not previous_exist_unknown_person)):
            safe_counter = safe_counter + 1

        elif ((not exist_unknown_person) and previous_exist_unknown_person):
            safe_counter = 0

        if(danger_lock and safe_counter > 15):
            warning_counter = 0
            danger_lock = False
            l.acquire()
            q.put("safe")
            l.release()
            print ("safe at {}".format(address))
            threading.Thread(target=lambda: (
                os.system("rm -rf ./Temp/*.png")
            )).start()

            '''
            if (video_name != ""):
                threading.Thread(target=lambda: (os.system("ffmpeg -i {}/%05d.jpg /usr/local/nginx/html/videos/{}.mp4".format(
                    video_name, video_name, video_name)) or os.system("rm -rf {}/".format(video_name)))).start()
                tempstr = video_name

                threading.Thread(target=lambda: (requests.post("http://10.41.0.147:5432", data={
                    'VName': tempstr, 'VIP': '10.41.0.147', 'VDescription': 'XM DANGER DETECTED'}))).start()

                video_name = ""
                counter = 0
            '''
        previous_exist_unknown_person = exist_unknown_person

        if mydict["now_push_ip"] == address:
            os.write(invasion_subsys_fh, frame.tobytes())
            # threading.Thread(target=lambda: (
            #     os.write(invasion_subsys_fh, frame.tobytes())
            # )).start()

    cp.close()


if __name__ == '__main__':

    try:
        os.mkfifo(invasion_subsys_name_pipe)
    except OSError:
        pass

    invasion_subsys_fh = os.open(invasion_subsys_name_pipe, os.O_WRONLY)

    for address in ["192.168.0.201", "192.168.0.202"]:
        Process(target=camera_detect, args=(queue, lock, address, dlib.get_frontal_face_detector(), openface.TorchNeuralNet(
            "nn4.small2.v1.t7", imgDim=96, cuda=False), openface.AlignDlib("shape_predictor_68_face_landmarks.dat"), )).start()

    while True:
        server.send_message_to_all(queue.get())
