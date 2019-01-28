from setuptools import setup, Extension

xm_module = Extension('xm_module', sources=["xm_module.cpp"],
                      language="c++",
                      include_dirs=['../sdk/include'],
                      library_dirs=['../sdk/x64'],
                      libraries=['opencv','xmnetsdk','pthread','avformat','avutil','swscale','avcodec'])
setup(ext_modules=[xm_module])
