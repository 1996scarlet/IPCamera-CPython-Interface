#include "netsdk.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <dirent.h>

class XMIPCamera
{
  public:
    int login();
    int open();
    int close();
    cv::Mat get_current_frame_mat();
    void start_real_play(int frames);
    XMIPCamera(char *IP, int Port, char *UserName, char *Password);

  private:
    int initFFMPEG();
    char *m_ip;       // ip address of the camera
    int m_port;       // port
    char *m_username; // username
    char *m_password; // password
    int m_lRealPlayHandle;
    long m_lUserID;
    uint8_t *current_data_point;
};
