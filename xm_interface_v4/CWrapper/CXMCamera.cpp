#include "../sdk/include/CXMCamera.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
}

#define HPR_ERROR -1
#define HPR_OK 0

using namespace cv;
using namespace std;

AVFrame *pYUVFrame;
AVFrame *pRGBFrame;

Mat cvImg;

const AVCodec *codec;
AVCodecContext *c = NULL;
int ret;
AVPacket *pkt;

auto debug_line = [](string content) { cout << "==========" << content << "==========" << endl; };

XMIPCamera::XMIPCamera(char *IP, int Port, char *UserName, char *Password)
{
    m_ip = IP;
    m_port = Port;
    m_username = UserName;
    m_password = Password;
}

int RealDataCallBack_V2(long lRealHandle, const PACKET_INFO_EX *pFrame, long dwUser)
{
    if (pFrame->nPacketType == VIDEO_I_FRAME)
    {
        pkt->size = pFrame->dwPacketSize - 16;
        pkt->data = (uint8_t *)(pFrame->pPacketBuffer + 16);
    }
    else if (pFrame->nPacketType == VIDEO_P_FRAME)
    {
        pkt->size = pFrame->dwPacketSize - 8;
        pkt->data = (uint8_t *)pFrame->pPacketBuffer + 8;
    }
    else
    {
        printf("time:%04d-%02d-%02d %02d:%02d:%02d\n", pFrame->dwPacketSize, pFrame->nMonth, pFrame->nDay, pFrame->nHour, pFrame->nMinute, pFrame->nSecond);
        return TRUE;
    }

    int numBytes = avpicture_get_size(AV_PIX_FMT_BGR24, c->width, c->height);
    uint8_t *buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
    avpicture_fill((AVPicture *)pRGBFrame, buffer, AV_PIX_FMT_BGR24, c->width, c->height);

    ret = avcodec_send_packet(c, pkt);

    while (ret >= 0)
    {
        ret = avcodec_receive_frame(c, pYUVFrame);
        struct SwsContext *img_convert_ctx = sws_getCachedContext(NULL, c->width, c->height, AV_PIX_FMT_YUV420P, c->width, c->height, AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);

        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return TRUE;

        sws_scale(img_convert_ctx, (uint8_t const *const *)pYUVFrame->data,
                  pYUVFrame->linesize, 0, c->height,
                  pRGBFrame->data, pRGBFrame->linesize);

        cvImg = Mat(pYUVFrame->height, pYUVFrame->width, CV_8UC3, *(pRGBFrame->data));
        sws_freeContext(img_convert_ctx);
    }

    av_free(buffer);
    return TRUE;
}

int XMIPCamera::initFFMPEG()
{
    pkt = av_packet_alloc();
    if (!pkt)
        exit(1);

    codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if (!codec)
    {
        fprintf(stderr, "Codec not found\n");
        exit(1);
    }

    c = avcodec_alloc_context3(codec);
    if (!c)
    {
        fprintf(stderr, "Could not allocate video codec context\n");
        exit(1);
    }

    if (avcodec_open2(c, codec, NULL) < 0)
    {
        fprintf(stderr, "Could not open codec\n");
        exit(1);
    }

    pYUVFrame = av_frame_alloc();
    if (!pYUVFrame)
    {
        fprintf(stderr, "Could not allocate video pYUVFrame\n");
        exit(1);
    }

    pRGBFrame = av_frame_alloc();
    if (!pRGBFrame)
    {
        fprintf(stderr, "Could not allocate video pRGBFrame\n");
        exit(1);
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

    cout << m_ip << m_port << m_username << m_password << endl;

    m_lUserID = H264_DVR_Login(m_ip, m_port, m_username, m_password, (LPH264_DVR_DEVICEINFO)(&OutDev), &nError, NULL);

    printf("g_LoginID=%d,nError:%d\n", m_lUserID, nError);

    if (m_lUserID > 0)
    {
        debug_line("login ok");
        return HPR_OK;
    }
    else
    {
        debug_line("login wrong");
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
            debug_line("tarting RealPlay");

            if (H264_DVR_SetRealDataCallBack_V2(nPlayHandle, RealDataCallBack_V2, 0))
            {
                debug_line("start RealPlay ok!");
                m_lRealPlayHandle = nPlayHandle;
                return HPR_OK;
            }
            else
            {
                cout << "GET LAST ERROR:" << H264_DVR_GetLastError() << endl;
            }
        }
    }
    return HPR_ERROR;
}

int XMIPCamera::close()
{
    avcodec_free_context(&c);
    av_frame_free(&pYUVFrame);
    av_frame_free(&pRGBFrame);
    av_packet_free(&pkt);

    if (H264_DVR_StopRealPlay(m_lRealPlayHandle))
        debug_line("stop realPlay ok!");

    if (m_lUserID > 0)
    {
        H264_DVR_Logout(m_lUserID);
        debug_line("Logout success!!!");
    }
    H264_DVR_Cleanup();
    debug_line("OVER");

    return HPR_OK;
}

Mat XMIPCamera::get_current_frame_mat()
{
    cvImg = imread("/home/scarlet/Downloads/wallpaper.png");
    return cvImg;
}

extern "C"
{
    XMIPCamera *XMIPCamera_init(char *pa1, int pa2, char *pa3, char *pa4)
    {
        return new XMIPCamera(pa1, pa2, pa3, pa4);
    }
    int XMIPCamera_start(XMIPCamera *xmcp) { return xmcp->login() + xmcp->open(); }
    int XMIPCamera_stop(XMIPCamera *xmcp) { return xmcp->close(); }
    void XMIPCamera_frame(XMIPCamera *xmcp, int rows, int cols, unsigned char *frompy)
    {
        memcpy(frompy, xmcp->get_current_frame_mat().data, rows * cols * 3);
    }
}