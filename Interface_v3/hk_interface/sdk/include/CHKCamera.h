#include "HCNetSDK.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

extern "C"{
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
}
#include <linux/videodev2.h>
#include <iostream>
#include <dirent.h>

#define HPR_ERROR -1
#define HPR_OK 0

class HKIPCamera
{
public:
    int login();
	int open();	
	int close();
    cv::Mat get_current_frame_mat();
	// HKIPCamera(int x, int y);
 
	HKIPCamera(char* IP, int Port, char* UserName, char* Password);

private:
    int initFFMPEG();
    char* m_ip;   // ip address of the camera
	int m_port;		// port
	char* m_username; // username
	char* m_password;		// password
	int m_lRealPlayHandle;
	long m_lUserID;
    uint8_t *current_data_point;
};
