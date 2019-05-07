#include "CXMCamera.h"

using namespace cv;
using namespace std;

INIT_DEBUG
INIT_TIMER

// cv::Mat wall = imread("/home/scarlet/Pictures/wallpaper.png");

XMIPCamera::XMIPCamera(char *IP, int Port, char *UserName, char *Password)
{
    m_ip = IP;
    m_port = Port;
    m_username = UserName;
    m_password = Password;
    cvImg = Mat(Size(MAX_FRAME_HEIGHT, MAX_FRAME_WIDTH), CV_8UC3);
}

int RealDataCallBack_V2(long lRealHandle, const PACKET_INFO_EX *pFrame, void *dwUser)
{
    XMIPCamera *xmcp = (XMIPCamera *)dwUser;

    if (pFrame->nPacketType == VIDEO_I_FRAME)
    {
        xmcp->pkt->size = pFrame->dwPacketSize - 16;
        xmcp->pkt->data = (uint8_t *)(pFrame->pPacketBuffer + 16);
    }
    else if (pFrame->nPacketType == VIDEO_P_FRAME)
    {
        xmcp->pkt->size = pFrame->dwPacketSize - 8;
        xmcp->pkt->data = (uint8_t *)pFrame->pPacketBuffer + 8;
    }
    else
    {
        cout << pFrame->dwPacketSize << endl;
        return TRUE;
    }

    int ret = avcodec_send_packet(xmcp->c, xmcp->pkt);

    while (ret >= 0)
    {
        ret = avcodec_receive_frame(xmcp->c, xmcp->pYUVFrame);

        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return TRUE;

        auto frame_height = xmcp->pYUVFrame->height;
        auto frame_width = xmcp->pYUVFrame->width;

        if (av_image_fill_arrays(xmcp->pRGBFrame->data, xmcp->pRGBFrame->linesize, xmcp->buffer, AV_PIX_FMT_BGR24, frame_width, frame_height, 1))
        {
            auto img_convert_ctx = sws_getContext(frame_width, frame_height, AV_PIX_FMT_YUV420P, frame_width, frame_height, AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);
            sws_scale(img_convert_ctx, (uint8_t const *const *)xmcp->pYUVFrame->data, xmcp->pYUVFrame->linesize, 0, frame_height, xmcp->pRGBFrame->data, xmcp->pRGBFrame->linesize);
            sws_freeContext(img_convert_ctx);
            xmcp->cvImg = Mat(frame_height, frame_width, CV_8UC3, *(xmcp->pRGBFrame->data));
        }
    }
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
    c->thread_count = 2;

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

    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_BGR24, MAX_FRAME_WIDTH, MAX_FRAME_HEIGHT, 1);
    buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));

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
    H264_DVR_CLIENTINFO playstru;
    playstru.nChannel = 0;
    playstru.nStream = 0;
    playstru.nMode = 1;

    m_lRealPlayHandle = H264_DVR_RealPlay(m_lUserID, &playstru);
    if (H264_DVR_SetRealDataCallBack_V2(m_lRealPlayHandle, RealDataCallBack_V2, this))
    {
        debug_line("RealPlay started!");
        return HPR_OK;
    }

    cout << "GET LAST ERROR:" << H264_DVR_GetLastError() << endl;
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
    av_free(buffer);

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

Mat XMIPCamera::current(int rows, int cols)
{
    Mat frame;
    resize(cvImg, frame, cv::Size(cols, rows));
    return frame;
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
void XMIPCamera_frame(XMIPCamera *xmcp, int rows, int cols, unsigned char *frompy)
{
    // START_TIMER
    memcpy(frompy, (xmcp->current(rows, cols)).data, rows * cols * 3);
    // STOP_TIMER("HKIPCamera_frame")
}