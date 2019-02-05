
# SDK文件夹目录结构（Struct of the SDK floder）

## 文件夹-include

> 用于存放海康相关头文件和C++接口定义头文件`CHKCamera.h`

```bash
.
|-- CHKCamera.h
|-- DataType.h
|-- DecodeCardSdk.h
|-- HCNetSDK.h
|-- LinuxPlayM4.h
`-- PlayM4.h
```

## 文件夹-lib

> 用于存放海康相关SDK文件和C++接口生成的`libHKCamera.so`文件

```bash
.
|-- HCNetSDKCom
|   |-- libHCAlarm.so
|   |-- libHCCoreDevCfg.so
|   |-- libHCDisplay.so
|   |-- libHCGeneralCfgMgr.so
|   |-- libHCIndustry.so
|   |-- libHCPlayBack.so
|   |-- libHCPreview.so
|   |-- libHCVoiceTalk.so
|   |-- libStreamTransClient.so
|   |-- libSystemTransform.so
|   |-- libanalyzedata.so
|   `-- libiconv2.so
|-- libAudioRender.so
|-- libHCCore.so
|-- libPlayCtrl.so
|-- libSuperRender.so
|-- libhcnetsdk.so
`-- libhpr.so
```
