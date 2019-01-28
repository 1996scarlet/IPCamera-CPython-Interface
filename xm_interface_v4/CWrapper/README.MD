# Export shared object to C++ in Linux

## 注意事项
编译需要ffmpeg、opencv
编译时需要libxmnetsdk.so & netsdk.h文件
建议编译时的目录结构如下所示
	.
	├── CMakeLists.txt
	├── CMakeModules
	│   └── FindFFmpeg.cmake
	├── CXMCamera.cpp
	├── CXMCamera.h
	├── libxmnetsdk.so
	├── netsdk.h
	└── README.MD

## 如何编译
        mkdir build
        cd build
        cmake .. # gen the makefile
        make     # gen *.so

生成的`libXMCamera.so`就在`/../demo_c_cpp`文件夹内

## 简单使用
	#include "CXMCamera.h"
	#include <iostream>
	#include <unistd.h>

	using namespace std;
	using namespace cv;
	int main()
	{
	    XMIPCamera cp = XMIPCamera("10.41.0.211", 34567, "admin", "");

	    cp.login();
	    cp.open();

	    sleep(2);

	    int i = 0;
	    while (i++ < 5000)
	    {
		imshow("display", cp.get_current_frame_mat());
		cvWaitKey(1);
	    }

	    cp.close();
	    return 0;
	}

## 输出位置
请修改`set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../demo_c_cpp)`为合适位置
