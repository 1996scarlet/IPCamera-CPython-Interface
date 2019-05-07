# 相机接口运行库（libipc）

## 结构配置
* `cd 你的文件夹/`
* `mkdir -p usr/src`（存放代码）
* `mkdir -p usr/lib`（存放动态库）
* `mkdir DEBIAN`（存放control文件）
* `gedit DEBIAN/control`（编辑control文件） 
```
Package: libipc
Version: 1.0.0
Section: utils
Priority: optional
Architecture: amd64
Depends:
Installed-Size: 512
Maintainer: 1996scarlet@gmail.com
Description: libipc package for hk and xm
```

## 打包
* `sudo chmod 755 ./dist/* -R`（注意权限是755）
* `dpkg -b ./dist .`（i386->32bit amd64->64bit）

## 安装
* `dpkg -i libipc_1.0.0_amd64.deb`（强制安装：`--force-depends`）

## 卸载
* `dpkg -r libipc`（或者：`sudo apt remove libipc`）

## 目录结构
```shell
.
├── dist
│   ├── DEBIAN
│   │   ├── control
│   │   ├── postinst
│   │   └── postrm
│   ├── HKCWrapper
│   │   ├── CHKCamera.cpp
│   │   ├── CMakeLists.txt
│   │   └── CMakeModules
│   │       └── FindFFmpeg.cmake
│   ├── usr
│   │   ├── include
│   │   │   ├── CHKCamera.h
│   │   │   ├── CXMCamera.h
│   │   │   ├── HCNetSDK.h
│   │   │   └── netsdk.h
│   │   └── lib
│   │       ├── libanalyzedata.so
│   │       ├── libHCCoreDevCfg.so
│   │       ├── libhcnetsdk.so
│   │       ├── libHCPreview.so
│   │       └── libxmnetsdk.so
│   └── XMCWrapper
│       ├── CMakeLists.txt
│       ├── CMakeModules
│       │   └── FindFFmpeg.cmake
│       └── CXMCamera.cpp
├── libipc_1.0.0_amd64.deb
└── Readme.md
```