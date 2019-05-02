from distutils.core import setup, Extension

module1 = Extension('XMIPCamera', sources=["CXMCamera.cpp"],
                    language="c++",
                    include_dirs=['../../sdk/include',
                                  '/usr/local/include/opencv4'],
                    library_dirs=['../../sdk/x64', '/usr/local/lib'],
                    libraries=['xmnetsdk', 'pthread',
                               'opencv_core', 'opencv_imgproc',
                               'opencv_highgui', 'opencv_ml',
                               'avformat', 'avutil', 'swscale', 'avcodec'])

setup(name='XMIPCamera',
      version='1.0',
      description='This is a XMIPCamera package',
      ext_modules=[module1])
