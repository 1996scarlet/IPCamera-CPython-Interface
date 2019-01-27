# 海康C++接口测试demo

## 通过cv2连续显示内存中解码后的H264-stream中图像

```C++
#include "../sdk/include/CHKCamera.h"
#include <unistd.h>
using namespace std;
int main()
{
    HKIPCamera hkpc("10.41.0.236", 8000, "admin", "humanmotion01");
    hkpc.login();
    hkpc.open();
    sleep(1);
    int i=0;
    while (i++<200)
    {
        cv::imshow("OKK", hkpc.get_current_frame_mat());
        cv::waitKey(1);
    }
    hkpc.close();
}
```

## 海康错误代码FAQ

Q:运行时提示107错误？
A:需要将libHKCamera.so文件、执行文件和海康sdk文件(包括HCNetSDKCom文件夹)放在同一目录下。

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
|-- 要执行的文件
|-- libAudioRender.so
|-- libHCCore.so
|-- libHKCamera.so
|-- libPlayCtrl.so
|-- libSuperRender.so
|-- libhcnetsdk.so
`-- libhpr.so
```

Q:运行时提示17错误？
A:一般情况下，这个错误会伴随`错误7`出现，需要检查构造函数的用户名、密码和端口是否有误。