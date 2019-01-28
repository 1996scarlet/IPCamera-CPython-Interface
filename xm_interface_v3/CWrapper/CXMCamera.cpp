#include "CXMCamera.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
#include <linux/videodev2.h>
}

#define HPR_ERROR -1
#define HPR_OK 0

using namespace cv;
using namespace std;

AVCodecContext *m_dCodecCtx;
AVFrame *pYUVFrame = av_frame_alloc();
AVFrame *pRGBFrame = av_frame_alloc();

Mat cvImg;

uint8_t *current_data_point;

XMIPCamera::XMIPCamera(char *IP, int Port, char *UserName, char *Password)
{
    m_ip = IP;
    m_port = Port;
    m_username = UserName;
    m_password = Password;
}

int RealDataCallBack_V2(long lRealHandle, const PACKET_INFO_EX *pFrame, long dwUser)
{
    // printf("time:%04d-%02d-%02d %02d:%02d:%02d\n", pFrame->dwPacketSize, pFrame->nMonth, pFrame->nDay, pFrame->nHour, pFrame->nMinute, pFrame->nSecond);

    AVPacket *avpacket = av_packet_alloc();

    if (pFrame->nPacketType == VIDEO_I_FRAME)
    {
        avpacket->size = pFrame->dwPacketSize - 16;
        avpacket->data = (uint8_t *)(pFrame->pPacketBuffer + 16);
    }
    else if (pFrame->nPacketType == VIDEO_P_FRAME)
    {
        avpacket->size = pFrame->dwPacketSize - 8;
        avpacket->data = (uint8_t *)pFrame->pPacketBuffer + 8;
    }
    else
    {
        printf("time:%04d-%02d-%02d %02d:%02d:%02d\n", pFrame->dwPacketSize, pFrame->nMonth, pFrame->nDay, pFrame->nHour, pFrame->nMinute, pFrame->nSecond);
        return TRUE;
    }

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
    return TRUE;
}

int XMIPCamera::initFFMPEG()
{
    av_register_all();
    // avformat_network_init();

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

int XMIPCamera::login()
{
    H264_DVR_Init(NULL, NULL);
    printf("H264_DVR_Init\n");

    initFFMPEG();

    H264_DVR_DEVICEINFO OutDev;
    memset(&OutDev, 0, sizeof(OutDev));
    int nError = 0;
    m_lUserID = H264_DVR_Login(m_ip, m_port, m_username, m_password, (LPH264_DVR_DEVICEINFO)(&OutDev), &nError, NULL);

    printf("g_LoginID=%d,nError:%d\n", m_lUserID, nError);

    if (m_lUserID > 0)
    {
        printf("**************login ok***************\n");
        return HPR_OK;
    }
    else
    {
        printf("**************login wrong************\n");
        return HPR_ERROR;
    }
}

int XMIPCamera::open()
{
    if (m_lUserID > 0)
    {
        H264_DVR_CLIENTINFO playstru;

        playstru.nChannel = 0;
        playstru.nStream = 0;
        playstru.nMode = 0;
        long nPlayHandle = H264_DVR_RealPlay(m_lUserID, &playstru);
        printf("nPlayHandle=%ld\n", nPlayHandle);

        nPlayHandle = H264_DVR_RealPlay(m_lUserID, &playstru);

        if (nPlayHandle == 0)
        {
            printf("start RealPlay wrong!\n");
            cout << "Handler <= 0 : " << nPlayHandle << endl
                 << "GET LAST ERROR:" << H264_DVR_GetLastError() << endl;
        }
        else
        {
            cout << nPlayHandle << endl;
            printf("starting RealPlay ......\n");
            if (H264_DVR_SetRealDataCallBack_V2(nPlayHandle, RealDataCallBack_V2, 0))
            {
                printf("start RealPlay ok!\n");

                m_lRealPlayHandle = nPlayHandle;
                return HPR_OK;
            }
            else
            {
                cout << "GET LAST ERROR:" << H264_DVR_GetLastError() << endl;
                // close();
            }
        }
    }
    return HPR_ERROR;
}

int XMIPCamera::close()
{
    if (H264_DVR_StopRealPlay(m_lRealPlayHandle))
    {
        printf("stop realPlay ok\n");
    }

    if (m_lUserID > 0)
    {
        H264_DVR_Logout(m_lUserID);
        printf("Logout success!!!\n");
    }
    H264_DVR_Cleanup();

    printf("**************OVER************\n");

    return HPR_OK;
}

Mat XMIPCamera::get_current_frame_mat()
{
    // return Mat(1080, 1920, CV_8UC3, *current_data_point); //dst->data[0]);

    return cvImg;
    //return Mat(pYUVFrame->height, pYUVFrame->width, CV_8UC3, *(pRGBFrame->data));
}

void XMIPCamera::start_real_play(int frames)
{
    int i = 0;
    while (i++ < frames)
    {
        imwrite("frames.jpg", Mat(1080, 1920, CV_8UC3, *current_data_point));
        // waitKey(0);
    }
}

// extern "C"
// {

//     int cpp_hello()
//     {
//         printf("hello");
//     }

//     XMIPCamera *cpp_hkipc_ptr;

//     int init_hk_ipc(char *IP, int Port, char *UserName, char *Password)
//     {
//         cpp_hkipc_ptr = new XMIPCamera(IP, Port, UserName, Password);
//         cpp_hkipc_ptr->login();
//         cpp_hkipc_ptr->open();
//     }

//     int get_image(const IplImage *img, const int row_numb, const int col_numb, const int pix_byte)
//     {
//         if (pix_byte != 3)
//         {
//             printf("IplImage should be cv_8uc3");
//             return -1;
//         }
//         cv::Mat tempdata = cpp_hkipc_ptr->get_current_frame_mat();
//         memcpy((void *)img, tempdata.data, tempdata.size().area() * 3);
//     }

//     int dest_hk_ipc()
//     {
//         cpp_hkipc_ptr->close();
//         delete ((void *)cpp_hkipc_ptr);
//     }
// };
