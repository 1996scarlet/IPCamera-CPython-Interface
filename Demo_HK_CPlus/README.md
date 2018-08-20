# How to Use

## 注意事项
运行时必须关联海康so文件

## 通过cv2连续显示内存中的H264-stream中图像

        #include "CHKCamera.h"
        #include <unistd.h>
        using namespace std;
        int main()
        {
            HKIPCamera hkpc("10.41.0.99", 8000, "admin", "humanmotion01");
            hkpc.login();
            hkpc.open();
            sleep(1);
            int i=0;
            while (i++<200)
            {
                cv::imshow("OKK", hkpc.get_current_frame_mat());
                cvWaitKey(1);
            }
            hkpc.close();
        }