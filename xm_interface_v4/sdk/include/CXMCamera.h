#include "netsdk.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
}

#define HPR_ERROR 0
#define HPR_OK 1

class XMIPCamera
{
public:
  bool start();
  bool stop();
  cv::Mat current();
  XMIPCamera(char *IP, int Port, char *UserName, char *Password);

protected:
  bool initFFMPEG();
  bool login();
  bool logout();
  bool open();
  bool close();

private:
  char *m_ip;       // ip address of the camera
  int m_port;       // port
  char *m_username; // username
  char *m_password; // password
  long m_lRealPlayHandle;
  long m_lUserID;
};
