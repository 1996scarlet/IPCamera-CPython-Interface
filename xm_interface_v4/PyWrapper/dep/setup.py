from setuptools import setup, Extension

xm_module = Extension('xm_module', sources=["xm_module.cpp"],
                      language="c++",
                      include_dirs=['../../sdk/include','/usr/local/include/opencv4'],
                      library_dirs=['../../sdk/x64','/usr/local/lib'],
                      libraries=['xmnetsdk', 'pthread',
                                 'opencv_core', 'opencv_imgproc',
                                 'opencv_highgui', 'opencv_ml',
                                 'avformat', 'avutil', 'swscale', 'avcodec'])
setup(ext_modules=[xm_module])
