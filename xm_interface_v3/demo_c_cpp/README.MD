# 雄迈C++接口测试demo

## API调用方式-C++

```C++
XMIPCamera cp = XMIPCamera("10.41.0.211", 34567, "admin", "");

cp.login();
cp.open();
sleep(2);

int i = 0;
while (i++ < 5000)
{
    imshow("display", cp.get_current_frame_mat());
    cv::waitKey(1);
}

cp.close();
```

## 用于手动连接opencv和ffmpeg的Makefile模板

```makefile
CC       = gcc
CXX      = g++
CFLAGS   = -g
CXXFLAGS = $(CFLAGS)

LIBPATH = ./
LIBS = -lxmnetsdk -lpthread -lavformat -lavutil -lswscale -lavcodec -lswresample -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lXMCamera
SRC = ./xm.cpp
TARGET = ./test

all:
    $(CXX) $(OPTI) $(CXXFLAGS) $(SRC) -o $(TARGET) -L$(LIBPATH) $(LIBS) $(INCLUDE)

.PHONY: clean
clean:
    rm -f $(TARGET)

```