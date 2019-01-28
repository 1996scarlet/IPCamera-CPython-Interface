
# SDK文件夹目录结构（Struct of the SDK floder）

## 文件夹-include

> 用于存放雄迈相关头文件和C++接口定义头文件`CXMCamera.h`

```bash
.
|-- CXMCamera.h
`-- netsdk.h
```

## 文件夹-lib

> 用于存放python接口生成的`xmcext.so`文件和C++接口生成的`libXMCamera.so`文件

```bash
.
|-- libXMCamera.so
`-- xmcext.so
```

## 文件夹-x86、x64

> 用于存放雄迈SDK相关文件

```bash
.
|-- README.md
|-- include
|   |-- CXMCamera.h
|   `-- netsdk.h
|-- lib
|   |-- libXMCamera.so
|   `-- xmcext.so
|-- x64
|   `-- libxmnetsdk.so
`-- x86
    `-- libxmnetsdk.so
```