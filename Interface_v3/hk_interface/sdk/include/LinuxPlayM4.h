#ifndef __LINUX_PLAYM4_H__
#define __LINUX_PLAYM4_H__

#ifdef __cplusplus
	extern "C" 
	{
#endif

typedef unsigned int PLAYM4_HWND;
typedef void * PLAYM4_HDC;

#define PLAYM4_API 

#define __stdcall

#ifndef CALLBACK
#define CALLBACK
#endif

//Max channel numbers
#define PLAYM4_MAX_SUPPORTS 500

//Wave coef range;
#define MIN_WAVE_COEF -100
#define MAX_WAVE_COEF 100

//Timer type
#define TIMER_1 1 //Only 16 timers for every process.Default TIMER;
#define TIMER_2 2 //Not limit;But the precision less than TIMER_1; 

//BUFFER AND DATA TYPE
#define BUF_VIDEO_SRC               (1) //mixed input,total src buffer size;splited input,video src buffer size 
#define BUF_AUDIO_SRC               (2) //mixed input,not defined;splited input,audio src buffer size
#define BUF_VIDEO_RENDER            (3) //video render node count or node cout for decoded data
#define BUF_AUDIO_RENDER            (4) //audio render node count 
#define BUF_VIDEO_DECODED           (5) //video decoded node count to render
#define BUF_AUDIO_DECODED           (6) //audio decoded node count to render

//Error code
#define  PLAYM4_NOERROR					0	//no error
#define	 PLAYM4_PARA_OVER				1	//input parameter is invalid;
#define  PLAYM4_ORDER_ERROR				2	//The order of the function to be called is error.
#define	 PLAYM4_TIMER_ERROR				3	//Create multimedia clock failed;
#define  PLAYM4_DEC_VIDEO_ERROR			4	//Decode video data failed.
#define  PLAYM4_DEC_AUDIO_ERROR			5	//Decode audio data failed.
#define	 PLAYM4_ALLOC_MEMORY_ERROR		6	//Allocate memory failed.
#define  PLAYM4_OPEN_FILE_ERROR			7	//Open the file failed.
#define  PLAYM4_CREATE_OBJ_ERROR		8	//Create thread or event failed
//#define  PLAYM4_CREATE_DDRAW_ERROR		9	//Create DirectDraw object failed.
//#define  PLAYM4_CREATE_OFFSCREEN_ERROR 10	//failed when creating off-screen surface.
#define  PLAYM4_BUF_OVER			   11	//buffer is overflow
#define  PLAYM4_CREATE_SOUND_ERROR	   12	//failed when creating audio device.	
#define	 PLAYM4_SET_VOLUME_ERROR	   13	//Set volume failed
#define  PLAYM4_SUPPORT_FILE_ONLY	   14	//The function only support play file.
#define  PLAYM4_SUPPORT_STREAM_ONLY	   15	//The function only support play stream.
#define  PLAYM4_SYS_NOT_SUPPORT		   16	//System not support.
#define  PLAYM4_FILEHEADER_UNKNOWN     17	//No file header.
#define  PLAYM4_VERSION_INCORRECT	   18	//The version of decoder and encoder is not adapted.  
#define  PLAYM4_INIT_DECODER_ERROR     19	//Initialize decoder failed.
#define  PLAYM4_CHECK_FILE_ERROR	   20	//The file data is unknown.
#define  PLAYM4_INIT_TIMER_ERROR	   21	//Initialize multimedia clock failed.
#define	 PLAYM4_BLT_ERROR		       22	//Display failed.
//#define  PLAYM4_UPDATE_ERROR		   23	//Update failed.
#define  PLAYM4_OPEN_FILE_ERROR_MULTI  24   //openfile error, streamtype is multi
#define  PLAYM4_OPEN_FILE_ERROR_VIDEO  25   //openfile error, streamtype is video
#define  PLAYM4_JPEG_COMPRESS_ERROR    26   //JPEG compress error
#define  PLAYM4_EXTRACT_NOT_SUPPORT    27	//Don't support the version of this file.
#define  PLAYM4_EXTRACT_DATA_ERROR     28	//extract video data failed.
#define  PLAYM4_SECRET_KEY_ERROR       29	//Secret key is error //add 20071218
#define  PLAYM4_DECODE_KEYFRAME_ERROR  30   //add by hy 20090318
#define  PLAYM4_NEED_MORE_DATA         31   //add by hy 20100617
#define  PLAYM4_INVALID_PORT		   32	//add by cj 20100913
#define  PLAYM4_NOT_FIND               33	//add by cj 20110428
#define  PLAYM4_NEED_LARGER_BUFFER     34  //add by pzj 20130528
#define  PLAYM4_FAIL_UNKNOWN		   99   //Fail, but the reason is unknown;	

//鱼眼功能错误码
#define PLAYM4_FEC_ERR_ENABLEFAIL				100 // 鱼眼模块加载失败
#define PLAYM4_FEC_ERR_NOTENABLE				101 // 鱼眼模块没有加载
#define PLAYM4_FEC_ERR_NOSUBPORT				102 // 子端口没有分配
#define PLAYM4_FEC_ERR_PARAMNOTINIT				103 // 没有初始化对应端口的参数
#define PLAYM4_FEC_ERR_SUBPORTOVER				104 // 子端口已经用完
#define PLAYM4_FEC_ERR_EFFECTNOTSUPPORT			105 // 该安装方式下这种效果不支持
#define PLAYM4_FEC_ERR_INVALIDWND				106 // 非法的窗口
#define PLAYM4_FEC_ERR_PTZOVERFLOW				107 // PTZ位置越界
#define PLAYM4_FEC_ERR_RADIUSINVALID			108 // 圆心参数非法
#define PLAYM4_FEC_ERR_UPDATENOTSUPPORT			109 // 指定的安装方式和矫正效果，该参数更新不支持
#define PLAYM4_FEC_ERR_NOPLAYPORT				110 // 播放库端口没有启用
#define PLAYM4_FEC_ERR_PARAMVALID				111 // 参数为空
#define PLAYM4_FEC_ERR_INVALIDPORT				112 // 非法子端口
#define PLAYM4_FEC_ERR_PTZZOOMOVER				113 // PTZ矫正范围越界
#define PLAYM4_FEC_ERR_OVERMAXPORT				114  // 矫正通道饱和，最大支持的矫正通道为四个
#define PLAYM4_FEC_ERR_ENABLED                  115  //该端口已经启用了鱼眼模块
#define PLAYM4_FEC_ERR_D3DACCENOTENABLE			116 // D3D加速没有开启

//Max display regions.
#define MAX_DISPLAY_WND 4

//Display type
#define DISPLAY_NORMAL            0x00000001
#define DISPLAY_QUARTER           0x00000002
#define DISPLAY_YC_SCALE          0x00000004	//add by gb 20091116
#define DISPLAY_NOTEARING         0x00000008
//Display buffers
#define MAX_DIS_FRAMES 50
#define MIN_DIS_FRAMES 1

//Locate by
#define BY_FRAMENUM  1
#define BY_FRAMETIME 2

//Source buffer
#define SOURCE_BUF_MAX	1024*100000
#define SOURCE_BUF_MIN	1024*50

//Stream type
#define STREAME_REALTIME 0
#define STREAME_FILE	 1

//frame type
#define T_AUDIO16	101
#define T_AUDIO8	100
#define T_UYVY		1
#define T_YV12		3
#define T_RGB32		7

//capability
#define SUPPORT_DDRAW		1 
#define SUPPORT_BLT         2 
#define SUPPORT_BLTFOURCC   4 
#define SUPPORT_BLTSHRINKX  8 
#define SUPPORT_BLTSHRINKY  16
#define SUPPORT_BLTSTRETCHX 32
#define SUPPORT_BLTSTRETCHY 64
#define SUPPORT_SSE         128
#define SUPPORT_MMX			256 

// 以下宏定义用于HIK_MEDIAINFO结构
#define FOURCC_HKMI			0x484B4D49	// "HKMI" HIK_MEDIAINFO结构标记
// 系统封装格式	
#define SYSTEM_NULL			0x0				// 没有系统层，纯音频流或视频流	
#define SYSTEM_HIK          0x1				// 海康文件层
#define SYSTEM_MPEG2_PS     0x2				// PS封装
#define SYSTEM_MPEG2_TS     0x3				// TS封装
#define SYSTEM_RTP          0x4				// rtp封装
#define SYSTEM_RTPHIK       0x401				// rtp封装

// 视频编码类型
#define VIDEO_NULL          0x0 // 没有视频
#define VIDEO_H264          0x1 // 标准H.264和海康H.264都可以用这个定义
#define VIDEO_MPEG2			0x2	// 标准MPEG2
#define VIDEO_MPEG4         0x3 // 标准MPEG4
#define VIDEO_MJPEG			0x4
#define VIDEO_AVC264        0x0100

// 音频编码类型
#define AUDIO_NULL          0x0000 // 没有音频
#define AUDIO_ADPCM         0x1000 // ADPCM 
#define AUDIO_MPEG          0x2000 // MPEG 系列音频，解码器能自适应各种MPEG音频
#define AUDIO_AAC           0x2001
// G系列音频
#define AUDIO_RAW_DATA8		0x7000      //采样率为8k的原始数据
#define AUDIO_RAW_UDATA16	0x7001      //采样率为16k的原始数据，即L16
#define AUDIO_G711_U		0x7110
#define AUDIO_G711_A		0x7111
#define AUDIO_G722_1		0x7221
#define AUDIO_G723_1        0x7231
#define AUDIO_G726_U        0x7260
#define AUDIO_G726_A        0x7261
#define AUDIO_G729          0x7290
#define AUDIO_AMR_NB		0x3000

#define SYNCDATA_VEH	    1 //同步数据:车载信息	
#define SYNCDATA_IVS	    2 //同步数据:智能信息

//motion flow type
#define	MOTION_FLOW_NONE			0
#define MOTION_FLOW_CPU				1
#define MOTION_FLOW_GPU				2

//音视频加密类型
#define ENCRYPT_AES_3R_VIDEO     1
#define ENCRYPT_AES_10R_VIDEO    2
#define ENCRYPT_AES_3R_AUDIO     1
#define ENCRYPT_AES_10R_AUDIO    2

typedef struct tagSystemTime
{
    short wYear;
    short wMonth;
    short wDayOfWeek;
    short wDay;
    short wHour;
    short wMinute;
    short wSecond;
    short wMilliseconds;
}SYSTEMTIME;

typedef struct tagHKRect
{
    unsigned long left;
    unsigned long top;
    unsigned long right;
    unsigned long bottom;
}HKRECT;

//Frame position
typedef struct
{
	long long nFilePos;
    int nFrameNum;
    int nFrameTime;
    int nErrorFrameNum;
    SYSTEMTIME *pErrorTime;
    int nErrorLostFrameNum;
    int nErrorFrameSize;
}FRAME_POS,*PFRAME_POS;

//Frame Info
typedef struct
{
    int nWidth;
    int nHeight;
    int nStamp;
    int nType;
    int nFrameRate;
    unsigned int dwFrameNum;
}FRAME_INFO;

//Frame 
typedef struct
{
    char *pDataBuf;
    int  nSize;
    int  nFrameNum;
    int  bIsAudio;
    int  nReserved;
}FRAME_TYPE;

//Watermark Info	//add by gb 080119
typedef struct
{
    char *pDataBuf;
    int  nSize;
    int  nFrameNum;
    int  bRsaRight;
    int  nReserved;
}WATERMARK_INFO;

typedef struct SYNCDATA_INFO 
{
    unsigned int dwDataType;        //和码流数据同步的附属信息类型，目前有：智能信息，车载信息
    unsigned int dwDataLen;         //附属信息数据长度
    unsigned char* pData;           //指向附属信息数据结构的指针,比如IVS_INFO结构
} SYNCDATA_INFO;

#ifndef _HIK_MEDIAINFO_FLAG_
#define _HIK_MEDIAINFO_FLAG_
typedef struct _HIK_MEDIAINFO_				// modified by gb 080425
{
    unsigned int    media_fourcc;			// "HKMI": 0x484B4D49 Hikvision Media Information
    unsigned short  media_version;			// 版本号：指本信息结构版本号，目前为0x0101,即1.01版本，01：主版本号；01：子版本号。
    unsigned short  device_id;				// 设备ID，便于跟踪/分析			

    unsigned short  system_format;          // 系统封装层
    unsigned short  video_format;           // 视频编码类型

    unsigned short  audio_format;           // 音频编码类型
    unsigned char   audio_channels;         // 通道数  
    unsigned char   audio_bits_per_sample;  // 样位率
    unsigned int    audio_samplesrate;      // 采样率 
    unsigned int    audio_bitrate;          // 压缩音频码率,单位：bit

    unsigned int    reserved[4];            // 保留
}HIK_MEDIAINFO;
#endif

typedef struct  
{
    int nPort;
    char* pBuf;
    int nBufLen;
    int nWidth;
    int nHeight;
    int nStamp;
    int nType;
    void* nUser;
}DISPLAY_INFO;

typedef struct
{
    int nPort;
    char *pVideoBuf;
    int nVideoBufLen;
    char *pPriBuf;
    int nPriBufLen;
    int nWidth;
    int nHeight;
    int nStamp;
    int nType;
    void* nUser;
}DISPLAY_INFOEX;

typedef struct PLAYM4_SYSTEM_TIME //绝对时间 
{
    unsigned int dwYear; //年
    unsigned int dwMon;  //月
    unsigned int dwDay;  //日
    unsigned int dwHour; //时
    unsigned int dwMin;  //分
    unsigned int dwSec;  //秒
    unsigned int dwMs;   //毫秒
} PLAYM4_SYSTEM_TIME;

#ifndef CROP_PIC_INFO_TAG
#define CROP_PIC_INFO_TAG
typedef struct
{
    unsigned char* pDataBuf;      //抓图数据buffer
    unsigned int   dwPicSize;	  //实际图片大小
    unsigned int   dwBufSize;      //数据buffer大小
    unsigned int   dwPicWidth;	  //截图宽
    unsigned int   dwPicHeight;    //截图高
    unsigned int   dwReserve;      //多加一个reserve字段
    HKRECT*        pCropRect;     //选择区域NULL, 同老的抓图接口
}CROP_PIC_INFO;
#endif

//////////////////////////////////////////////////////////////////////////////
//API
//////////////////////////////////////////////////////////////////////////////
int  PlayM4_GetPort(int* nPort);
int  PlayM4_FreePort(int nPort);

int  PlayM4_OpenFile(int nPort,char * sFileName);
int  PlayM4_CloseFile(int nPort);
int  PlayM4_SetStreamOpenMode(int nPort,unsigned int nMode);
int  PlayM4_GetStreamOpenMode(int nPort);
int  PlayM4_OpenStream(int nPort,unsigned char * pFileHeadBuf,unsigned int nSize,unsigned int nBufPoolSize);
int  PlayM4_CloseStream(int nPort);

int  PlayM4_Play(int nPort, PLAYM4_HWND hWnd);
int  PlayM4_Stop(int nPort);
int  PlayM4_Pause(int nPort,unsigned int nPause);
int  PlayM4_Fast(int nPort);
int  PlayM4_Slow(int nPort);
int  PlayM4_RefreshPlay(int nPort);
int  PlayM4_InputData(int nPort,unsigned char * pBuf,unsigned int nSize);

int  PlayM4_PlaySound(int nPort);
int  PlayM4_StopSound();
int  PlayM4_PlaySoundShare(int nPort);
int  PlayM4_StopSoundShare(int nPort);
int  PlayM4_SetVolume(int nPort,unsigned short nVolume);
unsigned short  PlayM4_GetVolume(int nPort);

int  PlayM4_OneByOne(int nPort);
int  PlayM4_OneByOneBack(int nPort);

int  PlayM4_SetPlayPos(int nPort,float fRelativePos);
float  PlayM4_GetPlayPos(int nPort);

unsigned int  PlayM4_GetFileTime(int nPort);
unsigned int  PlayM4_GetPlayedTime(int nPort);
unsigned int  PlayM4_GetPlayedFrames(int nPort);
unsigned int  PlayM4_GetFileTotalFrames(int nPort);
unsigned int  PlayM4_GetCurrentFrameRate(int nPort);
unsigned int  PlayM4_GetCurrentFrameNum(int nPort);
unsigned int  PlayM4_GetSpecialData(int nPort);
unsigned int  PlayM4_GetAbsFrameNum(int nPort); 
unsigned int  PlayM4_GetFileHeadLength();
unsigned int  PlayM4_GetSdkVersion();
unsigned int  PlayM4_GetLastError(int nPort);
unsigned int  PlayM4_GetPlayedTimeEx(int nPort);

int  PlayM4_GetSystemTime(int nPort, PLAYM4_SYSTEM_TIME *pstSystemTime);
int  PlayM4_GetFileTimeEx(int nPort, unsigned int* pStart, unsigned int* pStop, unsigned int* pRev);
int  PlayM4_GetCurrentFrameRateEx(int nPort, float* pfFrameRate);
int  PlayM4_GetPictureSize(int nPort,int *pWidth,int *pHeight);
int  PlayM4_GetKeyFramePos(int nPort,unsigned int nValue, unsigned int nType, PFRAME_POS pFramePos);
int  PlayM4_GetNextKeyFramePos(int nPort,unsigned int nValue, unsigned int nType, PFRAME_POS pFramePos);

int  PlayM4_ConvertToBmpFile(char * pBuf,int nSize,int nWidth,int nHeight,int nType,char *sFileName);
int  PlayM4_ConvertToJpegFile(char * pBuf,int nSize,int nWidth,int nHeight,int nType,char *sFileName);
int  PlayM4_SetJpegQuality(int nQuality);
int  PlayM4_GetBMP(int nPort,unsigned char * pBitmap,unsigned int nBufSize,unsigned int* pBmpSize);
int  PlayM4_GetJPEG(int nPort,unsigned char * pJpeg,unsigned int nBufSize,unsigned int* pJpegSize);

int  PlayM4_SetPlayedTimeEx(int nPort,unsigned int nTime);
int  PlayM4_SetCurrentFrameNum(int nPort,unsigned int nFrameNum);
int  PlayM4_SetDisplayRegion(int nPort,unsigned int nRegionNum, HKRECT *pSrcRect, PLAYM4_HWND hDestWnd, int bEnable);
int  PlayM4_SetDecodeFrameType(int nPort,unsigned int nFrameType);
int  PlayM4_SetSecretKey(int nPort, int lKeyType, char *pSecretKey, int lKeyLen);
int  PlayM4_SetVideoWindow(int nPort, unsigned int nRegionNum, PLAYM4_HWND hWnd);

int  PlayM4_SetDecCBStream(int nPort,unsigned int nStream);
int  PlayM4_SetDecCallBack(int nPort,void (CALLBACK* DecCBFun)(int nPort,char* pBuf,int nSize,FRAME_INFO * pFrameInfo, void* nReserved1,int nReserved2));
int  PlayM4_SetDecCallBackEx(int nPort,void (CALLBACK* DecCBFun)(int nPort,char * pBuf,int nSize,FRAME_INFO * pFrameInfo, void* nReserved1,int nReserved2), char* pDest, int nDestSize);
int  PlayM4_SetDecCallBackMend(int nPort,void (CALLBACK* DecCBFun)(int nPort,char * pBuf,int nSize,FRAME_INFO * pFrameInfo, void* nUser,int nReserved2), void* nUser);
int  PlayM4_SetDecCallBackExMend(int nPort, void (CALLBACK* DecCBFun)(int nPort, char* pBuf, int nSize, FRAME_INFO* pFrameInfo, void* nUser, int nReserved2), char* pDest, int nDestSize, void* nUser);

int  PlayM4_SetDisplayCallBack(int nPort,void (CALLBACK* DisplayCBFun)(int nPort,char * pBuf,int nSize,int nWidth,int nHeight,int nStamp,int nType,int nReserved));
int  PlayM4_SetDisplayCallBackEx(int nPort,void (CALLBACK* DisplayCBFun)(DISPLAY_INFO *pstDisplayInfo), void* nUser);
int  PlayM4_SetFileRefCallBack(int nPort, void (CALLBACK *pFileRefDone)(unsigned int nPort,void* nUser),void* nUser);
int  PlayM4_SetEncTypeChangeCallBack(int nPort, void(CALLBACK *funEncChange)(int nPort, void* nUser), void* nUser);
int  PlayM4_SetCheckWatermarkCallBack(int nPort, void(CALLBACK* funCheckWatermark)(int nPort, WATERMARK_INFO* pWatermarkInfo, void* nUser), void* nUser);
int  PlayM4_SetFileEndCallback(int nPort, void(CALLBACK*FileEndCallback)(int nPort, void *pUser), void *pUser);

int  PlayM4_ResetSourceBuffer(int nPort);
int  PlayM4_SetDisplayBuf(int nPort, unsigned int nNum);
int  PlayM4_ResetBuffer(int nPort,unsigned int nBufType);
unsigned int  PlayM4_GetSourceBufferRemain(int nPort);
unsigned int  PlayM4_GetDisplayBuf(int nPort);
unsigned int  PlayM4_GetBufferValue(int nPort,unsigned int nBufType);

int  PlayM4_GetRefValue(int nPort,unsigned char  *pBuffer, unsigned int *pSize);
int  PlayM4_SetRefValue(int nPort,unsigned char  *pBuffer, unsigned int nSize);

int  PlayM4_RegisterDrawFun(int nPort,void (CALLBACK* DrawFun)(int nPort,PLAYM4_HDC hDc,void* nUser),void* nUser);
int  PlayM4_RigisterDrawFun(int nPort,void (CALLBACK* DrawFun)(int nPort,PLAYM4_HDC hDc,void* nUser),void* nUser);

int  PlayM4_ThrowBFrameNum(int nPort,unsigned int nNum);
int  PlayM4_SkipErrorData(int nPort, int bSkip);

//////////NO TEST////////////////////////////////////////////////////////////////////////////

int  PlayM4_SetDisplayMode(int nPort, unsigned int dwType);
int  PlayM4_SetTimerType(int nPort,unsigned int nTimerType,unsigned int nReserved);
int  PlayM4_GetTimerType(int nPort,unsigned int *pTimerType,unsigned int *pReserved);
int  PlayM4_ReversePlay(int nPort);

#ifndef PLAYM4_SESSION_INFO_TAG
#define PLAYM4_SESSION_INFO_TAG
//nProtocolType
#define PLAYM4_PROTOCOL_RTSP    1
//nSessionInfoType
#define PLAYM4_SESSION_INFO_SDP 1

typedef struct _PLAYM4_SESSION_INFO_     //交互信息结构
{
    int            nSessionInfoType;   //交互信息类型，比如SDP，比如海康私有信息头
    int            nSessionInfoLen;    //交互信息长度
    unsigned char* pSessionInfoData;   //交互信息数据

} PLAYM4_SESSION_INFO;
#endif

PLAYM4_API int __stdcall PlayM4_OpenStreamAdvanced(int nPort, int nProtocolType, PLAYM4_SESSION_INFO* pstSessionInfo, unsigned int nBufPoolSize);

#define R_ANGLE_0   -1  //不旋转
#define R_ANGLE_L90  0  //向左旋转90度
#define R_ANGLE_R90  1  //向右旋转90度
#define R_ANGLE_180  2  //旋转180度

PLAYM4_API int __stdcall PlayM4_SetRotateAngle(int nPort, unsigned int nRegionNum, unsigned int dwType);

#ifndef PLAYM4_ADDITION_INFO_TAG
#define PLAYM4_ADDITION_INFO_TAG
typedef struct _PLAYM4_ADDITION_INFO_     //交互信息结构
{
    unsigned char*  pData;			//附件数据
    unsigned int    dwDatalen;		//附件数据长度
    unsigned int	dwDataType;		//数据类型
    unsigned int	dwTimeStamp;	//相对时间戳
} PLAYM4_ADDITION_INFO;
#endif

//dwGroupIndex 暂约定取值0~3，第一版本取消同步只能同个closestream处理
PLAYM4_API int __stdcall PlayM4_SetSycGroup(int nPort, unsigned int dwGroupIndex);
//暂不实现此函数，同个组设置的起始时间不一致，以最小的时间作为播放起点，同一组可只设一路
PLAYM4_API int __stdcall PlayM4_SetSycStartTime(int nPort, PLAYM4_SYSTEM_TIME *pstSystemTime);

// 以下实现鱼眼相关的接口
#ifndef FISH_EYE_TAG
#define FISH_EYE_TAG

// 矫正类型
typedef enum tagFECPlaceType
{
    FEC_PLACE_WALL = 0x1,			// 壁装方式		(法线水平)
    FEC_PLACE_FLOOR = 0x2,			// 地面安装		(法线向上)
    FEC_PLACE_CEILING = 0x3,		// 顶装方式		(法线向下)

}FECPLACETYPE;

typedef enum tagFECCorrectType
{
    FEC_CORRECT_PTZ = 0x100,		// PTZ
    FEC_CORRECT_180 = 0x200,		// 180度矫正  （对应2P）
    FEC_CORRECT_360 = 0x300,		// 360全景矫正 （对应1P）

}FECCORRECTTYPE;

typedef struct tagCycleParam
{
    float	fRadiusLeft;	// 圆的最左边X坐标
    float	fRadiusRight;	// 圆的最右边X坐标
    float   fRadiusTop;		// 圆的最上边Y坐标
    float   fRadiusBottom;	// 圆的最下边Y坐标

}CYCLEPARAM;

typedef struct tagPTZParam
{
    float fPTZPositionX;		// PTZ 显示的中心位置 X坐标
    float fPTZPositionY;		// PTZ 显示的中心位置 Y坐标	

}PTZPARAM;

// 更新标记变量定义

#define 		FEC_UPDATE_RADIUS			 0x1
#define 		FEC_UPDATE_PTZZOOM			 0x2
#define 		FEC_UPDATE_WIDESCANOFFSET	 0x4
#define 		FEC_UPDATE_PTZPARAM			 0x8

typedef struct tagFECParam
{


    unsigned int 	nUpDateType;			// 更新的类型

    unsigned int	nPlaceAndCorrect;		// 安装方式和矫正方式，只能用于获取，SetParam的时候无效,该值表示安装方式和矫正方式的和

    PTZPARAM		stPTZParam;				// PTZ 校正的参数

    CYCLEPARAM		stCycleParam;			// 鱼眼图像圆心参数

    float			fZoom;					// PTZ 显示的范围参数

    float			fWideScanOffset;		// 180或者360度校正的偏移角度

    int				nResver[16];			// 保留字段

}FISHEYEPARAM;

#endif

typedef void (__stdcall * FISHEYE_CallBack )(  void* pUser  , unsigned int  nPort , unsigned int nCBType , void * hDC ,   unsigned int nWidth , unsigned int nHeight); 

// 启用鱼眼
PLAYM4_API int __stdcall PlayM4_FEC_Enable(int nPort);

// 关闭鱼眼模块
PLAYM4_API int __stdcall PlayM4_FEC_Disable(int nPort);

// 获取鱼眼矫正处理子端口 [1~31] 
PLAYM4_API int  __stdcall PlayM4_FEC_GetPort(int nPort , unsigned int* nSubPort , FECPLACETYPE emPlaceType , FECCORRECTTYPE emCorrectType);

// 删除鱼眼矫正处理子端口
PLAYM4_API int __stdcall PlayM4_FEC_DelPort(int nPort , unsigned int nSubPort);

// 设置鱼眼矫正参数
PLAYM4_API int __stdcall PlayM4_FEC_SetParam(int nPort , unsigned int nSubPort , FISHEYEPARAM * pPara);

// 获取鱼眼矫正参数
PLAYM4_API int __stdcall PlayM4_FEC_GetParam(int nPort , unsigned int nSubPort , FISHEYEPARAM * pPara);

// 设置显示窗口，可以随时切换
PLAYM4_API int __stdcall PlayM4_FEC_SetWnd(int nPort , unsigned int nSubPort , void * hWnd);

// 设置鱼眼窗口的绘图回调
PLAYM4_API int __stdcall PlayM4_FEC_SetCallBack(int nPort , unsigned int nSubPort , FISHEYE_CallBack cbFunc , void * pUser);

//motionflow
PLAYM4_API int __stdcall PlayM4_MotionFlow(int nPort, unsigned int dwAdjustType);

//图像增强相关
#ifndef PLAYM4_HIKVIE_TAG
#define PLAYM4_HIKVIE_TAG

typedef struct _PLAYM4_VIE_DYNPARAM_
{
    int moduFlag;      //启用的算法处理模块，在PLAYM4_VIE_MODULES中定义
    //如 PLAYM4_VIE_MODU_ADJ | PLAYM4_VIE_MODU_EHAN
    //模块启用后，必须设置相应的参数；
    //PLAYM4_VIE_MODU_ADJ
    int brightVal;     //亮度调节值，[-255, 255]
    int contrastVal;   //对比度调节值，[-256, 255]
    int colorVal;      //饱和度调节值，[-256, 255]
    //PLAYM4_VIE_MODU_EHAN
    int toneScale;     //滤波范围，[0, 100]
    int toneGain;      //对比度调节，全局对比度增益值，[-256, 255]
    int toneOffset;    //亮度调节，亮度平均值偏移，[-255, 255]
    int toneColor;     //颜色调节，颜色保真值，[-256, 255]
    //PLAYM4_VIE_MODU_DEHAZE
    int dehazeLevel;   //去雾强度，[0, 255]
    int dehazeTrans;   //透射值，[0, 255]
    int dehazeBright;  //亮度补偿，[0, 255]
    //PLAYM4_VIE_MODU_DENOISE
    int denoiseLevel;  //去噪强度，[0, 255]
    //PLAYM4_VIE_MODU_SHARPEN
    int usmAmount;     //锐化强度，[0, 255]
    int usmRadius;     //锐化半径，[1, 15]
    int usmThreshold;  //锐化阈值，[0, 255]
    //PLAYM4_VIE_MODU_DEBLOCK
    int deblockLevel;  //去块强度，[0, 100]
    //PLAYM4_VIE_MODU_LENS
    int lensWarp;      //畸变量，[-256, 255]
    int lensZoom;      //缩放量，[-256, 255]
    //PLAYM4_VIE_MODU_CRB
    //无响应参数
} PLAYM4_VIE_PARACONFIG;

typedef enum _PLAYM4_VIE_MODULES
{
    PLAYM4_VIE_MODU_ADJ      = 0x00000001, //图像基本调节
    PLAYM4_VIE_MODU_EHAN     = 0x00000002, //局部增强模块
    PLAYM4_VIE_MODU_DEHAZE   = 0x00000004, //去雾模块
    PLAYM4_VIE_MODU_DENOISE  = 0x00000008, //去噪模块
    PLAYM4_VIE_MODU_SHARPEN  = 0x00000010, //锐化模块
    PLAYM4_VIE_MODU_DEBLOCK  = 0x00000020, //去块滤波模块
    PLAYM4_VIE_MODU_CRB      = 0x00000040, //色彩平衡模块
    PLAYM4_VIE_MODU_LENS     = 0x00000080, //镜头畸变矫正模块
}PLAYM4_VIE_MODULES;
#endif

//设置关闭/开启模块
//dwModuFlag对应PLAYM4_VIE_MODULES宏,可组合
//先设置模块开启，再设置模块参数；期间采用默认的参数;
//关闭模块后，上次设置的参数清空
//其他接口调用，必须在该接口开启模块后；否则，返回错误
PLAYM4_API int __stdcall PlayM4_VIE_SetModuConfig(int nPort, int nModuFlag, int bEnable);

//设置图像增强区域，NULL全图；超过全图，采用全图；最小区域16*16像素
//可支持设置区域，最多比较说4个，第一个版本可以只支持一个。多个区域要求不能重叠，有重叠就报错
PLAYM4_API int __stdcall PlayM4_VIE_SetRegion(int nPort, int nRegNum, HKRECT* pRect);

//获取开启模块
PLAYM4_API int __stdcall PlayM4_VIE_GetModuConfig(int nPort, int* pdwModuFlag);

//设置参数
//未开启模块的参数设置被忽略
PLAYM4_API int __stdcall PlayM4_VIE_SetParaConfig(int nPort, PLAYM4_VIE_PARACONFIG* pParaConfig);

//获取开启模块的参数
PLAYM4_API int __stdcall PlayM4_VIE_GetParaConfig(int nPort, PLAYM4_VIE_PARACONFIG* pParaConfig);

// 私有信息模块类型
typedef enum _PLAYM4_PRIDATA_RENDER
{	
    PLAYM4_RENDER_ANA_INTEL_DATA   = 0x00000001, //智能分析
    PLAYM4_RENDER_MD               = 0x00000002, //移动侦测
    PLAYM4_RENDER_ADD_POS          = 0x00000004, //POS信息后叠加
}PLAYM4_PRIDATA_RENDER;

// 智能信息开关
PLAYM4_API int __stdcall PlayM4_RenderPrivateData(int nPort, int nIntelType, int bTrue);

//ENCRYPT Info
typedef struct{
    long nVideoEncryptType;  //视频加密类型
    long nAudioEncryptType;  //音频加密类型
    long nSetSecretKey;      //是否设置，1表示设置密钥，0表示没有设置密钥
}ENCRYPT_INFO;

// 加密码流回调,nType=0表示码流加密标记位发生变化就回调，nType=1表示码流有加密位发生回调
PLAYM4_API int __stdcall PlayM4_SetEncryptTypeCallBack(int nPort, unsigned int nType, void (CALLBACK* EncryptTypeCBFun)(int nPort, ENCRYPT_INFO* pEncryptInfo, void* nUser, int nReserved2), void* nUser);

#define PLAYM4_MEDIA_HEAD     1   //系统头数据
#define PLAYM4_VIDEO_DATA     2   //视频流数据
#define PLAYM4_AUDIO_DATA     3   //音频流数据
#define PLAYM4_PRIVT_DATA     4   //私有流数据

//预录像数据信息
typedef struct  
{
    long nType;                     // 数据类型，如文件头，视频，音频，私有数据等
    long nStamp;                    // 时间戳
    long nFrameNum;                 // 帧号
    long nBufLen;                   // 数据长度
    char* pBuf;                     // 帧数据，以帧为单位回调
    PLAYM4_SYSTEM_TIME  stSysTime;  // 全局时间
}RECORD_DATA_INFO;

//设置预录像开关，bFlag=1开启，bFlag=0关闭
PLAYM4_API int __stdcall PlayM4_SetPreRecordFlag(int nPort, int bFlag);

//预录像数据数据回调
PLAYM4_API int __stdcall PlayM4_SetPreRecordCallBack(int nPort, void (CALLBACK* PreRecordCBfun)(int nPort, RECORD_DATA_INFO* pRecordDataInfo, void* pUser), void* pUser);

typedef struct
{
    long    lDataType;          //私有数据类型
    long    lDataStrVersion;    //数据返回的结构体版本，主要是为了兼容性
    long    lDataTimeStamp;
    long    lDataLength;
    char*   pData;
}AdditionDataInfo;

PLAYM4_API int __stdcall PlayM4_SetAdditionDataCallBack(int nPort, unsigned int nSyncType, void (CALLBACK* AdditionDataCBFun)(int nPort, AdditionDataInfo* pstAddDataInfo, void* pUser), void* pUser);

//lType: 1 表示获取当前显示帧PTZ信息。以特定结构体形式存储在pInfo内，plLen返回长度信息;起先传入pInfo = null，可以获取出需要分配的内存长度plLen
PLAYM4_API int __stdcall PlayM4_GetStreamAdditionalInfo(int nPort, int lType, unsigned char* pInfo, int* plLen);

typedef struct
{
    int            nRunTimeModule;     //当前运行模块，暂定2为解码模块，后续扩展
    int            nStrVersion;        //数据返回的结构体版本，主要是为了兼容性,第一个版本定义成0x0001
    int            nFrameTimeStamp;    //帧号
    int            nFrameNum;          //时间戳
    int            nErrorCode;         //错误码,0为硬解错误
    unsigned char  reserved[12];       //保留字节
}RunTimeInfo;

PLAYM4_API int __stdcall PlayM4_SetRunTimeInfoCallBack(int nPort, void (CALLBACK* RunTimeInfoCBFun)(int nPort, RunTimeInfo* pstRunTimeInfo, void* pUser), void* pUser);

PLAYM4_API int __stdcall PlayM4_WndResolutionChange(int nPort);

/////////////////////////////////////////////////////////////////////////////

////////////////NO SUPPORT///////////////////////////////////////////////////

int          PlayM4_InitDDraw(PLAYM4_HWND hWnd);
int          PlayM4_RealeseDDraw();
#if (WINVER >= 0x0400)
//Note: These funtion must be builded under win2000 or above with Microsoft Platform sdk.
//You can download the sdk from "http://www.microsoft.com/msdownload/platformsdk/sdkupdate/";
int          PlayM4_InitDDrawDevice();
void         PlayM4_ReleaseDDrawDevice();
int          PlayM4_SetDDrawDevice(int nPort, unsigned int nDeviceNum);
int          PlayM4_SetDDrawDeviceEx(int nPort,unsigned int nRegionNum,unsigned int nDeviceNum);
int          PlayM4_GetDDrawDeviceInfo(unsigned int nDeviceNum, char* lpDriverDescription, unsigned int nDespLen, char* lpDriverName, unsigned int nNameLen, HMONITOR* hhMonitor);
int          PlayM4_GetCapsEx(unsigned int nDDrawDeviceNum);
unsigned int PlayM4_GetDDrawDeviceTotalNums();
#endif
int          PlayM4_GetCaps();
int          PlayM4_OpenStreamEx(int nPort, unsigned char* pFileHeadBuf, unsigned int nSize, unsigned int nBufPoolSize);
int          PlayM4_CloseStreamEx(int nPort);
int          PlayM4_InputVideoData(int nPort, unsigned char* pBuf, unsigned int nSize);
int          PlayM4_InputAudioData(int nPort, unsigned char* pBuf, unsigned int nSize);
int          PlayM4_GetFileSpecialAttr(int nPort, unsigned int* pTimeStamp, unsigned int* pFileNum, unsigned int* pReserved);
//int          PlayM4_SetOverlayMode(int nPort, int bOverlay, COLORREF colorKey);
int          PlayM4_GetOverlayMode(int nPort);
int          PlayM4_SetOverlayFlipMode(int nPort, int bTrue);
//COLORREF     PlayM4_GetColorKey(int nPort);
int          PlayM4_SetPicQuality(int nPort, int bHighQuality);
int          PlayM4_GetPictureQuality(int nPort, int* bHighQuality);
int          PlayM4_ResetSourceBufFlag(int nPort);
int          PlayM4_SetDisplayType(int nPort, int nType);
int          PlayM4_GetDisplayType(int nPort);
int          PlayM4_SyncToAudio(int nPort, int bSyncToAudio);
int          PlayM4_RefreshPlayEx(int nPort, unsigned int nRegionNum);
int          PlayM4_AdjustWaveAudio(int nPort, int nCoefficient);
int          PlayM4_SetPlayMode(int nPort, int bNormal);
int          PlayM4_SetColor(int nPort, unsigned int nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);
int          PlayM4_GetColor(int nPort, unsigned int nRegionNum, int* pBrightness, int* pContrast, int* pSaturation, int* pHue);
int          PlayM4_SetImageSharpen(int nPort, unsigned int nLevel);
int          PlayM4_SetDeflash(int nPort, int bDefalsh);
int          PlayM4_CheckDiscontinuousFrameNum(int nPort, int bCheck);
int          PlayM4_SetFileEndMsg(int nPort, PLAYM4_HWND hWnd, unsigned int nMsg);
int          PlayM4_SetVerifyCallBack(int nPort, unsigned int nBeginTime, unsigned int nEndTime, void (__stdcall* funVerify)(int nPort, FRAME_POS* pFilePos, unsigned int bIsVideo, unsigned int nUser), unsigned int nUser);
int          PlayM4_SetEncChangeMsg(int nPort, PLAYM4_HWND hWnd, unsigned int nMsg);
int          PlayM4_SetGetUserDataCallBack(int nPort, void(CALLBACK* funGetUserData)(int nPort, unsigned char* pUserBuf, unsigned int nBufLen, unsigned int nUser), unsigned int nUser);
int          PlayM4_SetSourceBufCallBack(int nPort, unsigned int nThreShold, void (CALLBACK* SourceBufCallBack)(int nPort, unsigned int nBufSize, unsigned int dwUser, void* pResvered), unsigned int dwUser, void* pReserved);
int          PlayM4_GetOriginalFrameCallBack(int nPort, int bIsChange, int bNormalSpeed, int nStartFrameNum, int nStartStamp, int nFileHeader, void(CALLBACK *funGetOrignalFrame)(int nPort, FRAME_TYPE* frameType, int nUser), int nUser);
int          PlayM4_GetThrowBFrameCallBack(int nPort, void(CALLBACK* funThrowBFrame)(int nPort, unsigned int nBFrame, unsigned int nUser), unsigned int nUser);
int          PlayM4_SetAudioCallBack(int nPort, void (__stdcall* funAudio)(int nPort, char* pAudioBuf, int nSize, int nStamp, int nType, int nUser), int nUser);


////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
    }
#endif

#endif //_PLAYM4_H_
