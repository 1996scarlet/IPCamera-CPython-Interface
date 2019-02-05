#include "HCNetSDK.h"

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

#define FRAME_WIDTH 1920
#define FRAME_HEIGHT 1080

class HKIPCamera
{
public:
	bool start();
	bool stop();
	cv::Mat current();
	HKIPCamera(char *IP, int Port, char *UserName, char *Password);
	friend std::ostream &operator<<(std::ostream &output, HKIPCamera &hkcp);
	friend void g_fPlayESCallBack(LONG lPreviewHandle, NET_DVR_PACKET_INFO_EX *pstruPackInfo, void *pUser);

protected:
	bool initFFMPEG();
	bool login();
	bool logout();
	bool open();
	bool close();

private:
	char *m_ip;				// ip address of the camera
	int m_port;				// port
	char *m_username; // username
	char *m_password; // password
	long m_lRealPlayHandle;
	long m_lUserID;

	uint8_t *buffer; //for sws fill picture
	AVCodecContext *c;
	AVPacket *pkt;
	struct SwsContext *img_convert_ctx;
	const AVCodec *codec;
	cv::Mat cvImg;
	AVFrame *pYUVFrame;
	AVFrame *pRGBFrame;
};

extern "C"
{
	HKIPCamera *HKIPCamera_init(char *ip, int port, char *name, char *pass);
	int HKIPCamera_start(HKIPCamera *hkcp);
	int HKIPCamera_stop(HKIPCamera *hkcp);
	void HKIPCamera_frame(HKIPCamera *hkcp, int rows, int cols, unsigned char *frompy);
}
