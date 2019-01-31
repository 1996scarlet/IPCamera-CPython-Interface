#include "../sdk/include/CXMCamera.h"

using namespace cv;
using namespace std;

cv::Mat cvImg;
AVFrame *pYUVFrame;
AVFrame *pRGBFrame;
const AVCodec *codec;
AVCodecContext *c = nullptr;
AVPacket *pkt;

// cv::Mat wall = imread("/home/scarlet/Pictures/wallpaper.png");

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
        cout << pFrame->dwPacketSize << endl;
        return TRUE;
    }

    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_BGR24, c->width, c->height, 1);

    // int numBytes = avpicture_get_size(AV_PIX_FMT_BGR24, c->width, c->height);
    uint8_t *buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
    av_image_fill_arrays(pRGBFrame->data, pRGBFrame->linesize, buffer, AV_PIX_FMT_BGR24, c->width, c->height, 1);
    // avpicture_fill((AVPicture *)pRGBFrame, buffer, AV_PIX_FMT_BGR24, c->width, c->height);

    int ret = avcodec_send_packet(c, pkt);

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

bool XMIPCamera::initFFMPEG()
{
    pkt = av_packet_alloc();
    if (!pkt)
        return HPR_ERROR;

    codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if (!codec)
    {
        fprintf(stderr, "Codec not found\n");
        return HPR_ERROR;
    }

    c = avcodec_alloc_context3(codec);
    if (!c)
    {
        fprintf(stderr, "Could not allocate video codec context\n");
        return HPR_ERROR;
    }

    if (avcodec_open2(c, codec, NULL) < 0)
    {
        fprintf(stderr, "Could not open codec\n");
        return HPR_ERROR;
    }

    pYUVFrame = av_frame_alloc();
    if (!pYUVFrame)
    {
        fprintf(stderr, "Could not allocate video pYUVFrame\n");
        return HPR_ERROR;
    }

    pRGBFrame = av_frame_alloc();
    if (!pRGBFrame)
    {
        fprintf(stderr, "Could not allocate video pRGBFrame\n");
        return HPR_ERROR;
    }

    return HPR_OK;
}

bool XMIPCamera::login()
{
    H264_DVR_Init(nullptr, 0);
    initFFMPEG();

    H264_DVR_DEVICEINFO OutDev;
    memset(&OutDev, 0, sizeof(OutDev));
    int nError = 0;

    m_lUserID = H264_DVR_Login(m_ip, m_port, m_username, m_password, (LPH264_DVR_DEVICEINFO)(&OutDev), &nError, 0);

    if (m_lUserID > 0)
        return HPR_OK;
    else
    {
        debug_line("login wrong");
        cout << "Login ID = : " << m_lUserID << "; Error Code = :" << nError << endl;
        return HPR_ERROR;
    }
}

bool XMIPCamera::open()
{
    if (m_lUserID > 0)
    {
        H264_DVR_CLIENTINFO playstru;
        playstru.nChannel = 0;
        playstru.nStream = 0;
        playstru.nMode = 1;

        // DO not delete this, because you have private m_lRealPlayHandle
        long nPlayHandle = H264_DVR_RealPlay(m_lUserID, &playstru);

        if (nPlayHandle == 0)
        {
            cout << "Handler wrong!" << endl
                 << "Handler <= 0 : " << nPlayHandle << endl
                 << "GET LAST ERROR:" << H264_DVR_GetLastError() << endl;
        }
        else
        {
            debug_line("Starting RealPlay");

            if (H264_DVR_SetRealDataCallBack_V2(nPlayHandle, RealDataCallBack_V2, m_lUserID))
            {
                debug_line("RealPlay started!");
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

bool XMIPCamera::close()
{
    if (H264_DVR_StopRealPlay(m_lRealPlayHandle))
    {
        debug_line("RealPlay Stopped!");
        H264_DVR_DelRealDataCallBack_V2(m_lRealPlayHandle, RealDataCallBack_V2, m_lUserID);
    }

    return HPR_OK;
}

bool XMIPCamera::logout()
{
    if (m_lUserID > 0)
    {
        H264_DVR_Logout(m_lUserID);
        debug_line("Logout success!!!");
    }

    H264_DVR_Cleanup();

    avcodec_free_context(&c);
    av_frame_free(&pYUVFrame);
    av_frame_free(&pRGBFrame);
    av_packet_free(&pkt);

    debug_line("Finished");
    return HPR_OK;
}

// ======================C++ Interface defined========================

bool XMIPCamera::start()
{
    return login() && open();
}

bool XMIPCamera::stop()
{
    return close() && logout();
}

Mat XMIPCamera::current()
{
    // cvImg = imread("/home/scarlet/Pictures/wallpaper.png");
    // cvImg = wall;
    return cvImg;
}

ostream &operator<<(ostream &output, XMIPCamera &xmcp)
{
    output << xmcp.m_ip << "-"
           << xmcp.m_port << "-"
           << xmcp.m_username << "-"
           << xmcp.m_password;

    return output;
}

// ======================C/Python Interface defined========================
XMIPCamera *XMIPCamera_init(char *ip, int port, char *name, char *pass) { return new XMIPCamera(ip, port, name, pass); }
int XMIPCamera_start(XMIPCamera *xmcp) { return xmcp->start(); }
int XMIPCamera_stop(XMIPCamera *xmcp) { return xmcp->stop(); }
void XMIPCamera_frame(XMIPCamera *xmcp, int rows, int cols, unsigned char *frompy) { memcpy(frompy, xmcp->current().data, rows * cols * 3); }