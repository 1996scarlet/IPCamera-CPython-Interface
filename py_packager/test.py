import cv2
import IPCamera.interface as ipc


def show_frames(camera, count=1000):
    camera.start()
    for _ in range(count):
        cv2.imshow("display", camera.frame(rows=540, cols=960))
        k = cv2.waitKey(1) & 0xff
        if k == ord('q') or k == 27:
            break
    camera.stop()


show_frames(ipc.HKIPCamera(b"10.41.0.231", 8000, b"admin", b"humanmotion01"))
show_frames(ipc.XMIPCamera(b'10.41.0.198', 34567, b'admin', b''))
