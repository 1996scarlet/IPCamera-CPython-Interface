import numpy as np
import ctypes as C

libxm = C.cdll.LoadLibrary('libXMCamera_v4.so')


class XMIPCamera(object):
    def __init__(self, ip, port, name, password):
        self.obj = libxm.XMIPCamera_init(ip, port, name, password)

    def start(self):
        libxm.XMIPCamera_start(self.obj)

    def stop(self):
        libxm.XMIPCamera_stop(self.obj)

    def frame(self, rows=1080, cols=1920):
        res = np.zeros(dtype=np.uint8, shape=(rows, cols, 3))

        libxm.XMIPCamera_frame(self.obj, rows, cols,
                               res.ctypes.data_as(C.POINTER(C.c_ubyte)))

        return res


libhk = C.cdll.LoadLibrary('libHKCamera_v4.so')


class HKIPCamera(object):
    def __init__(self, ip, port, name, password):
        self.obj = libhk.HKIPCamera_init(ip, port, name, password)

    def start(self):
        libhk.HKIPCamera_start(self.obj)

    def stop(self):
        libhk.HKIPCamera_stop(self.obj)

    def frame(self, rows=1080, cols=1920):
        res = np.zeros(dtype=np.uint8, shape=(rows, cols, 3))

        libhk.HKIPCamera_frame(self.obj, rows, cols,
                               res.ctypes.data_as(C.POINTER(C.c_ubyte)))

        return res
