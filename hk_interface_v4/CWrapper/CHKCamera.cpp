#include "CHKCamera.h"

using namespace cv;
using namespace std;

// cv::Mat wall;
// = imread("/home/scarlet/Pictures/wallpaper.png");
INIT_DEBUG
INIT_TIMER

HKIPCamera::HKIPCamera(char *IP, int Port, char *UserName, char *Password)
{
    m_ip = IP;
    m_port = Port;
    m_username = UserName;
    m_password = Password;
    cvImg = Mat(Size(MAX_FRAME_HEIGHT, MAX_FRAME_WIDTH), CV_8UC3);
}

void g_fPlayESCallBack(LONG lPreviewHandle, NET_DVR_PACKET_INFO_EX *pstruPackInfo, void *pUser)
{
    HKIPCamera *hkcp = (HKIPCamera *)pUser;
    if (pstruPackInfo->dwPacketType == 11)
        return;

    hkcp->pkt->size = pstruPackInfo->dwPacketSize;
    hkcp->pkt->data = (uint8_t *)pstruPackInfo->pPacketBuffer;

    int ret = avcodec_send_packet(hkcp->c, hkcp->pkt);

    // START_TIMER
    while (ret >= 0)
    {
        ret = avcodec_receive_frame(hkcp->c, hkcp->pYUVFrame);

        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
        {
            // STOP_TIMER("HKIPCamera_frame")
            return;
        }

        auto frame_height = hkcp->pYUVFrame->height;
        auto frame_width = hkcp->pYUVFrame->width;

        if (av_image_fill_arrays(hkcp->pRGBFrame->data, hkcp->pRGBFrame->linesize, hkcp->buffer, AV_PIX_FMT_BGR24, frame_width, frame_height, 1))
        {
            auto img_convert_ctx = sws_getContext(frame_width, frame_height, AV_PIX_FMT_YUV420P, frame_width, frame_height, AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);
            sws_scale(img_convert_ctx, (uint8_t const *const *)hkcp->pYUVFrame->data, hkcp->pYUVFrame->linesize, 0, frame_height, hkcp->pRGBFrame->data, hkcp->pRGBFrame->linesize);
            sws_freeContext(img_convert_ctx);
            hkcp->cvImg = Mat(frame_height, frame_width, CV_8UC3, *(hkcp->pRGBFrame->data));
        }
    }
}

bool HKIPCamera::initFFMPEG()
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

bool HKIPCamera::login()
{
    NET_DVR_Init();
    initFFMPEG();

    NET_DVR_DEVICEINFO struDeviceInfo;

    m_lUserID = NET_DVR_Login(m_ip, m_port, m_username, m_password, &struDeviceInfo);

    if (m_lUserID >= 0)
        return HPR_OK;
    else
    {
        OUTPUT_DEBUG("login wrong");
        cout << "Login ID = " << m_lUserID << "; Error Code = " << NET_DVR_GetLastError() << endl;
        return HPR_ERROR;
    }
}

bool HKIPCamera::open()
{
    NET_DVR_PREVIEWINFO struPlayInfo = {0};
    struPlayInfo.hPlayWnd = 0;     //需要 SDK 解码时句柄设为有效值,仅取流不解码时可设为空
    struPlayInfo.lChannel = 1;     //预览通道号
    struPlayInfo.dwStreamType = 0; //0-主码流,1-子码流,2-码流 3,3-码流 4,以此类推
    struPlayInfo.dwLinkMode = 1;   //0- TCP 方式,1- UDP 方式,2- 多播方式,3- RTP 方式,4-RTP/RTSP,5-RSTP/HTTP
    struPlayInfo.bBlocked = 0;     //0- 非阻塞取流,1- 阻塞取流

    m_lRealPlayHandle = NET_DVR_RealPlay_V40(m_lUserID, &struPlayInfo, NULL, this);

    if (NET_DVR_SetESRealPlayCallBack(m_lRealPlayHandle, g_fPlayESCallBack, this))
    {
        OUTPUT_DEBUG("RealPlay started!");
        return HPR_OK;
    }

    cout << "预览开始或回调设置错误：" << NET_DVR_GetLastError() << endl;
    NET_DVR_Logout(m_lUserID);
    NET_DVR_Cleanup();
    return HPR_ERROR;
}

bool HKIPCamera::close()
{
    NET_DVR_StopRealPlay(m_lRealPlayHandle);

    return HPR_OK;
}

bool HKIPCamera::logout()
{
    NET_DVR_Logout(m_lUserID);
    NET_DVR_Cleanup();

    avcodec_free_context(&c);

    av_frame_free(&pYUVFrame);
    av_frame_free(&pRGBFrame);
    av_packet_free(&pkt);
    av_free(buffer);

    OUTPUT_DEBUG("Finished");
    return HPR_OK;
}

// ======================C++ Interface defined========================

bool HKIPCamera::start()
{
    return login() && open();
}

bool HKIPCamera::stop()
{
    return close() && logout();
}

Mat HKIPCamera::current(int rows, int cols)
{
    // cvImg = imread("/home/scarlet/Pictures/wallpaper.png");
    // cvImg = wall;
    Mat frame;
    resize(cvImg, frame, cv::Size(cols, rows));
    return frame;
}

ostream &operator<<(ostream &output, HKIPCamera &hkcp)
{
    output << hkcp.m_ip << "-"
           << hkcp.m_port << "-"
           << hkcp.m_username << "-"
           << hkcp.m_password;

    return output;
}

// ======================C/Python Interface defined========================
HKIPCamera *HKIPCamera_init(char *ip, int port, char *name, char *pass) { return new HKIPCamera(ip, port, name, pass); }
int HKIPCamera_start(HKIPCamera *hkcp) { return hkcp->start(); }
int HKIPCamera_stop(HKIPCamera *hkcp) { return hkcp->stop(); }
void HKIPCamera_frame(HKIPCamera *hkcp, int rows, int cols, unsigned char *frompy)
{
    // START_TIMER
    memcpy(frompy, (hkcp->current(rows, cols)).data, rows * cols * 3);
    // STOP_TIMER("HKIPCamera_frame")
}
