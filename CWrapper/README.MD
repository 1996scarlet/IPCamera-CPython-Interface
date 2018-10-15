# Export shared object to C++ in Linux

## 如何编译
        mkdir build
        cd build
        cmake .. # gen the makefile
        make     # gen *.so

生成的`pycext.so`就在`/../Demo_HK_PY`文件夹内

## 注意事项
编译需要ffmpeg、opencv
编译时需要连接海康相关so文件
建议编译时的目录结构如下所示

## 简单使用
        HKIPCamera hkpc("10.41.0.99", 8000, "admin", "humanmotion01");
        hkpc.login();
        hkpc.open();
        sleep(1);
        imshow("OKK", hkpc.get_current_frame_mat());
        cvWaitKey(0);
        hkpc.close();

## 输出位置
请修改`set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../sdk/lib)`为合适位置

## FAQ
Q:运行时提示107错误？
A:需要将libHKCamera.so文件、执行文件和海康sdk文件放在同一目录下。