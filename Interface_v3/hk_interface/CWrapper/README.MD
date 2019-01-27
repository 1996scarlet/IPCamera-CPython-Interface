# Export shared object to C++ in Linux

## 如何编译

```shell
mkdir build
cd build
cmake .. # gen the makefile
make     # gen *.so
```

> 生成的`libHKCamera.so`就在`/../sdk/lib`文件夹内

## API说明

        HKIPCamera hkpc("10.41.0.99", 8000, "admin", "humanmotion01");
        hkpc.login();
        hkpc.open();
        sleep(1);
        imshow("OKK", hkpc.get_current_frame_mat());
        cvWaitKey(0);
        hkpc.close();

## FAQ

Q:运行时提示107错误？
A:需要将libHKCamera.so文件、执行文件和海康sdk文件放在同一目录下。