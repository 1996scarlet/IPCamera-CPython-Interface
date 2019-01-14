#include "CHKCamera.h"

extern "C"{
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
}
#include <linux/videodev2.h>

#define HPR_ERROR -1
#define HPR_OK 0

using namespace cv;
using namespace std;

AVCodecContext *m_dCodecCtx;
AVFrame *pYUVFrame = av_frame_alloc();
AVFrame *pRGBFrame = av_frame_alloc();
Mat cvImg;

HKIPCamera::HKIPCamera(char *IP, int Port, char *UserName, char *Password)
{
    m_ip = IP;
    m_port = Port;
    m_username = UserName;
    m_password = Password;
}

void g_fPlayESCallBack(LONG lPreviewHandle, NET_DVR_PACKET_INFO_EX *pstruPackInfo, void *pUser)
{
    if (pstruPackInfo->dwPacketType == 11) return;

    AVPacket *avpacket = av_packet_alloc();

    avpacket->size = pstruPackInfo->dwPacketSize;
    avpacket->data = (uint8_t *)(pstruPackInfo->pPacketBuffer);

    int numBytes = avpicture_get_size(AV_PIX_FMT_BGR24, m_dCodecCtx->width, m_dCodecCtx->height);
    uint8_t *buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
    avpicture_fill((AVPicture *)pRGBFrame, buffer, AV_PIX_FMT_BGR24, m_dCodecCtx->width, m_dCodecCtx->height);
    int frameFinished;

    avcodec_decode_video2(m_dCodecCtx, pYUVFrame, &frameFinished, avpacket);

    if (frameFinished)
    {
        struct SwsContext *img_convert_ctx = sws_getCachedContext(NULL, m_dCodecCtx->width, m_dCodecCtx->height, AV_PIX_FMT_YUV420P, m_dCodecCtx->width, m_dCodecCtx->height, AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);
        sws_scale(img_convert_ctx, (uint8_t const *const *)pYUVFrame->data,
                  pYUVFrame->linesize, 0, m_dCodecCtx->height,
                  pRGBFrame->data, pRGBFrame->linesize);

        // current_data_point = pRGBFrame->data[0];
        cvImg = Mat(pYUVFrame->height, pYUVFrame->width, CV_8UC3, *(pRGBFrame->data)); //dst->data[0]);

        av_free(buffer);
        av_free_packet(avpacket);
        sws_freeContext(img_convert_ctx);
    }
}

int HKIPCamera::initFFMPEG()
{
    av_register_all();
    avformat_network_init();

    AVCodec *dCodec;

    dCodec = avcodec_find_decoder(AV_CODEC_ID_H264);

    if (dCodec)
    {
        m_dCodecCtx = avcodec_alloc_context3(dCodec);
        m_dCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
        m_dCodecCtx->width = 1920;
        m_dCodecCtx->height = 1080;

        if (avcodec_open2(m_dCodecCtx, dCodec, NULL) < 0)
        {
            printf("avcode open failed!\n");
            return HPR_ERROR;
        }
    }
    else
    {
        printf("Can't find dectector!");
        return HPR_ERROR;
    }

    return HPR_OK;
}

int HKIPCamera::login()
{
    NET_DVR_Init();
    initFFMPEG();
    cout << "已初始化" << endl;
    NET_DVR_DEVICEINFO struDeviceInfo;
    m_lUserID = NET_DVR_Login(m_ip, m_port, m_username, m_password, &struDeviceInfo);
    if (m_lUserID < 0)
    {
        cout << "错误" << NET_DVR_GetLastError() << endl;
        return HPR_ERROR;
    }
    cout <<"已登录" << endl;
    return HPR_OK;
}

int HKIPCamera::open()
{
    NET_DVR_PREVIEWINFO struPlayInfo = {0};
    struPlayInfo.hPlayWnd = 0; //需要 SDK 解码时句柄设为有效值,仅取流不解码时可设为空
    struPlayInfo.lChannel = 1; //预览通道号
    struPlayInfo.dwStreamType = 0;
    //0-主码流,1-子码流,2-码流 3,3-码流 4,以此类推
    struPlayInfo.dwLinkMode = 0; //0- TCP 方式,1- UDP 方式,2- 多播方式,3- RTP 方式,4-RTP/RTSP,5-RSTP/HTTP
    struPlayInfo.bBlocked = 1;   //0- 非阻塞取流,1- 阻塞取流
    m_lRealPlayHandle = NET_DVR_RealPlay_V40(m_lUserID, &struPlayInfo, NULL, NULL);

    if (m_lRealPlayHandle < 0)
    {
        cout << "预览开始错误" << NET_DVR_GetLastError() << endl;
        NET_DVR_Logout(m_lUserID);
        NET_DVR_Cleanup();
        return HPR_ERROR;
    }

    //Set callback function of getting stream.
    if (!NET_DVR_SetESRealPlayCallBack(m_lRealPlayHandle, g_fPlayESCallBack, 0))
    {
        NET_DVR_StopRealPlay(m_lRealPlayHandle);
        NET_DVR_Logout(m_lUserID);
        NET_DVR_Cleanup();
        cout << "回调设置错误" << NET_DVR_GetLastError() << endl;

        return HPR_ERROR;
    }
    cout << "已打开" << endl;
    return HPR_OK;
}

int HKIPCamera::close()
{
    NET_DVR_StopRealPlay(m_lRealPlayHandle);
    cout << "已停止预览" << endl;
    NET_DVR_Logout(m_lUserID);
    cout << "已登出" << endl;
    NET_DVR_Cleanup();
    cout << "已释放资源" << endl;
    return HPR_OK;
}

Mat HKIPCamera::get_current_frame_mat()
{
    return cvImg;
    //return Mat(pYUVFrame->height, pYUVFrame->width, CV_8UC3, *(pRGBFrame->data));
}


extern "C"
{

int cpp_hello()
{
    printf("hello");
}

HKIPCamera * cpp_hkipc_ptr;

int init_hk_ipc( char* IP,  int Port,  char* UserName,  char* Password)
{
    cpp_hkipc_ptr = new HKIPCamera(IP,Port, UserName, Password);
    cpp_hkipc_ptr->login();
    cpp_hkipc_ptr->open();
}

int get_image(const IplImage * img, const int row_numb, const int col_numb, const int pix_byte)
{
    if(pix_byte != 3)
    {
        printf("IplImage should be cv_8uc3");
        return -1;
    }
    cv::Mat tempdata = cpp_hkipc_ptr->get_current_frame_mat();
    memcpy((void *)img, tempdata.data, tempdata.size().area()* 3);

}

int dest_hk_ipc()
{
    cpp_hkipc_ptr->close();
    delete((void *)cpp_hkipc_ptr);
}

};
