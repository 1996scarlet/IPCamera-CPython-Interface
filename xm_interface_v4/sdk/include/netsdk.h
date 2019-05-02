#ifndef NETMODULE_H
#define NETMODULE_H

#ifdef WIN32

#ifdef NETMODULE_EXPORTS
#define H264_DVR_API  extern "C" __declspec(dllexport)
#else
#define H264_DVR_API  extern "C" __declspec(dllimport)   //VC ��
#endif

#ifndef CALL_METHOD
#define CALL_METHOD	__stdcall  //__cdecl
#endif
#define DEF_PARAM(x) = x
#define DEF_0_PARAM = 0
#else	//linux
#define Bool int
#define TYPE_USER_DATA  unsigned long
#define TYPE_USER_DATA2  long
#define LOGD printf
#ifdef OS_IOS
#define H264_DVR_API
#define DEF_PARAM(x)
#define DEF_0_PARAM
#else
#define H264_DVR_API	extern "C"
#define DEF_PARAM(x) = x
#define DEF_0_PARAM = 0
#endif
#define CALL_METHOD
#define CALLBACK
#define WORD	unsigned short
#define DWORD	unsigned long
#define LPDWORD	DWORD*
#define BOOL	int
#define TRUE	1
#define FALSE	0
#define BYTE	unsigned char
#define LONG	long
#define UINT	unsigned int
#define HDC		void*
#define HWND	void*
#define LPVOID	void*
#define LPCSTR  char*
#define LPCTSTR  const char*
#endif

#ifndef WIN32
typedef long long long64;
#else
typedef long long64;
#endif

#ifdef _NAMESPACE_
namespace JF_NETSDK{
#endif
enum SDK_RET_CODE
{
	H264_DVR_NOERROR				    = 0,				//û�д���
	H264_DVR_SUCCESS					= 1,				//���سɹ�
	H264_DVR_SDK_NOTVALID				= -10000,			//�Ƿ�����
	H264_DVR_NO_INIT					= -10001,			//SDKδ����ʼ��
	H264_DVR_ILLEGAL_PARAM				= -10002,			//�û��������Ϸ�
	H264_DVR_INVALID_HANDLE				= -10003,			//�����Ч
	H264_DVR_SDK_UNINIT_ERROR			= -10004,			//SDK�������
	H264_DVR_SDK_TIMEOUT				= -10005,			//�ȴ���ʱ
	H264_DVR_SDK_MEMORY_ERROR			= -10006,			//�ڴ���󣬴����ڴ�ʧ��
	H264_DVR_SDK_NET_ERROR				= -10007,			//�������
	H264_DVR_SDK_OPEN_FILE_ERROR		= -10008,			//���ļ�ʧ��
	H264_DVR_SDK_UNKNOWNERROR			= -10009,			//δ֪����
	H264_DVR_DEV_VER_NOMATCH			= -11000,			//�յ����ݲ���ȷ�����ܰ汾��ƥ��
	H264_DVR_SDK_NOTSUPPORT				= -11001,			//�汾��֧��

	H264_DVR_ANAS_EXIST					= -11130,			//NAS��ַ�Ѵ���
	H264_DVR_ANAS_ALIVE					= -11131,			//·����ʹ�ã��޷�����
	H264_DVR_ANAS_FULL					= -11132,			//NAS�Ѵﵽ֧�ֵ����ֵ


	H264_DVR_OPEN_CHANNEL_ERROR			= -11200,			//��ͨ��ʧ��,���ܼ�⵽�豸�Ѿ�������
	H264_DVR_CLOSE_CHANNEL_ERROR		= -11201,			//�ر�ͨ��ʧ��
	H264_DVR_SUB_CONNECT_ERROR			= -11202,			//����ý��������ʧ��,�����������豸���ܲ�����
	H264_DVR_SUB_CONNECT_SEND_ERROR		= -11203,			//ý��������ͨѶʧ��,���ܼ�⵽�豸�Ѿ�������
	H264_DVR_NATCONNET_REACHED_MAX		= -11204,           //Nat��Ƶ���Ӵﵽ��󣬲������µ�Nat��Ƶ���� 
	H264_DVR_NOTSUPPORT					= -11205,			//�汾��֧��
	H264_DVR_NOTVALID					= -11206,           //����Ƿ�,�����ӿ����ѶϿ�
	H264_DVR_TCPCONNET_REACHED_MAX		= -11207,			//Tcp��Ƶ���Ӵﵽ��󣬲������µ�Tcp��Ƶ����
	H264_DVR_OPENEDPREVIEW				= -11208,			//��ͨ���Ѿ���Ԥ��(ͨ���Ĵ򿪹ر���Ҫһһ��Ӧ,�򿪼�����Ҫ�رռ���;��һ�»����ʾ�ô���;Ԥ���ͻ��˿����߼��ϵĲ�����������Ӹô���ֵ)

	/// �û������ִ�����
	H264_DVR_NOPOWER					= -11300,			//��Ȩ��
	H264_DVR_PASSWORD_NOT_VALID			= -11301,			//�˺����벻��
	H264_DVR_LOGIN_USER_NOEXIST			= -11302,			//�û�������
	H264_DVR_USER_LOCKED				= -11303,			//���û�������
	H264_DVR_USER_IN_BLACKLIST			= -11304,			//���û����������(�ں�������)
	H264_DVR_USER_HAS_USED				= -11305,			//���û��ѵ�½
	H264_DVR_USER_NOT_LOGIN				= -11306,			//���û�û�е�½
	H264_DVR_CONNECT_DEVICE_ERROR		= -11307,			//�����豸������
	H264_DVR_ACCOUNT_INPUT_NOT_VALID	= -11308,			//�û��������벻�Ϸ�
	H264_DVR_ACCOUNT_OVERLAP			= -11309,			//�����ظ�
	H264_DVR_ACCOUNT_OBJECT_NONE		= -11310,			//�����ڶ���, ���ڲ�ѯʱ
	H264_DVR_ACCOUNT_OBJECT_NOT_VALID	= -11311,			//�����ڶ���
	H264_DVR_ACCOUNT_OBJECT_IN_USE		= -11312,			//��������ʹ��
	H264_DVR_ACCOUNT_SUBSET_OVERLAP		= -11313,			//�Ӽ�����Χ (�����Ȩ�޳���Ȩ�ޱ��û�Ȩ�޳������Ȩ�޷�Χ�ȵ�)
	H264_DVR_ACCOUNT_PWD_NOT_VALID		= -11314,			//���벻��ȷ
	H264_DVR_ACCOUNT_PWD_NOT_MATCH		= -11315,			//���벻ƥ��
	H264_DVR_ACCOUNT_RESERVED			= -11316,			//�����ʺ�
	H264_DVR_ACCOUNT_SYS_MAINTAIN		= -11317,			//ϵͳά���У����ɵ�½


	/// ���ù�����ش�����
	H264_DVR_OPT_RESTART				= -11400,			//�������ú���Ҫ����Ӧ�ó���
	H264_DVR_OPT_REBOOT					= -11401,			//��Ҫ����ϵͳ
	H264_DVR_OPT_FILE_ERROR				= -11402,			//д�ļ�����
	H264_DVR_OPT_CAPS_ERROR				= -11403,			//�������Բ�֧��
	H264_DVR_OPT_VALIDATE_ERROR			= -11404,			//����У��ʧ��
	H264_DVR_OPT_CONFIG_NOT_EXIST		= -11405,			//����������õ����ò�����
	
	//
	H264_DVR_CTRL_PAUSE_ERROR			= -11500,			//��ͣʧ��
	H264_DVR_SDK_NOTFOUND				= -11501,			//����ʧ�ܣ�û���ҵ���Ӧ�ļ�
	H264_DVR_CFG_NOT_ENABLE				= -11502,           //����δ����

	H264_DVR_DECORD_FAIL				= -11503,           //����ʧ��

	//DNSЭ��������ش�����
	H264_DVR_SOCKET_ERROR				= -11600,			//�����׽���ʧ��
	H264_DVR_SOCKET_CONNECT				= -11601,			//�����׽���ʧ��
	H264_DVR_SOCKET_DOMAIN				= -11602,			//��������ʧ��
	H264_DVR_SOCKET_SEND				= -11603,			//��������ʧ��
	H264_DVR_ARSP_NO_DEVICE				= -11604,			//û�л�ȡ���豸��Ϣ���豸Ӧ�ò�����
	H264_DVR_ARSP_BUSING				= -11605,			//ARSP����æ
	H264_DVR_ARSP_BUSING_SELECT			= -11606,			//ARSP����æ,selectʧ��
	H264_DVR_ARSP_BUSING_RECVICE		= -11607,			//ARSP����æ,recviceʧ��
	H264_DVR_CONNECTSERVER_ERROR		= -11608,			//���ӷ�����ʧ��
    H264_DVR_CONNECT_AGNET     			= -11609,			//����
    H264_DVR_CONNECT_NAT      			= -11610,			//��͸
    H264_DVR_CONNECT_FAILED				= -11611,			//����ʧ��
    H264_DVR_CONNECT_FULL				= -11612,			//����������������
	H264_DVR_CLOUD_LOGIN_ERR			= -11613,	        //�Ƶ�½����Ĵ�����,˵��:����½�ӿڵ�error=-11613ʱ��ͨ��H264_DVR_DEVICEINFO��ԱsCloudErrCode��ȡ������,�ײ����Ӵ�����ʱ�ϲ㲻�����Ӵ���
	H264_DVR_NO_CONNECT_FRONT			= -11614,			//ǰ���豸δ���ӻ������ӵ�ǰ���豸�ֱ���δ֪
	H264_DVR_LOGIN_FULL					= -11615,			//��¼����Ѵﵽ���ֵ���޷��ٵ�¼
	H264_DVR_ARSP_USER_NOEXIST			= -11619,			//�û������� 
	H264_DVR_ARSP_PASSWORD_ERROR		= -11620,			//�˺����벻��
	H264_DVR_ARSP_QUERY_ERROR			= -11621,			//��ѯʧ�� 
	//��Ȩ���
	H264_DVR_PIRATESOFTWARE				= -11700,			//�豸����
	H264_DVR_AUTH_TIMEOUT          		= -11800,			//��Ȩ��ʱ
	H264_DVR_AUTH_FILE_FAILED			= -11801,			//��Ȩ�ļ�ʧ��
	H264_DVR_GAIN_LIST_TIMEOUT			= -11802,			//��ȡ�������б�ʱ
	H264_DVR_AUTH_CODE_ERR				= -11803,			//��Ȩ�����
	//����������
	H264_DVR_NOENOUGH_MEMORY			= -11804,			//�ڴ治��
	H264_DVR_INVALID_FORMAT				= -11805,			//�����ļ���ʽ����
	H264_DVR_UPDATE_PART_FAIL			= -11806,			//ĳ����������ʧ��
	H264_DVR_INVALID_HARDWARE			= -11807,			//Ӳ���ͺŲ�ƥ��
	H264_DVR_INVALID_VENDOR				= -11808,			//�ͻ���Ϣ��ƥ��
	H264_DVR_INVALID_COMPALIBLE			= -11809,			//��������ļ��ݰ汾�ű��豸���е�С���������豸�������ϳ���
	H264_DVR_INVALID_VERSION			= -11810,			//�Ƿ��İ汾
	H264_DVR_INVALID_WIFI_DRIVE			= -11811,			//����������wifi�������豸��ǰ��ʹ�õ�wifi������ƥ��
};


//��̨��������
enum PTZ_ControlType
{
	TILT_UP = 0,					//��
	TILT_DOWN,						//��
	PAN_LEFT,						//��
	PAN_RIGHT,						//��
	PAN_LEFTTOP,					//����
	PAN_LEFTDOWN,					//����
	PAN_RIGTHTOP,					//����
	PAN_RIGTHDOWN,					//����
	ZOOM_OUT_1,						//�䱶С//ZOOM_OUT/ZOOM_IN��VS2010��ϵͳ����ĳ�ͻ��
	ZOOM_IN_1,						//�䱶��
	FOCUS_FAR,						//������
	FOCUS_NEAR,						//����ǰ��
	IRIS_OPEN,						//��Ȧ����
	IRIS_CLOSE,						//��Ȧ��С13

	EXTPTZ_OPERATION_ALARM,			//�������� 
	EXTPTZ_LAMP_ON,					//�ƹ⿪
	EXTPTZ_LAMP_OFF,				//�ƹ��
	EXTPTZ_POINT_SET_CONTROL,		//����Ԥ�õ� 
	EXTPTZ_POINT_DEL_CONTROL,		//���Ԥ�õ� 
	EXTPTZ_POINT_MOVE_CONTROL,		//תԤ�õ�
	EXTPTZ_STARTPANCRUISE,			//��ʼˮƽ��ת		20	
	EXTPTZ_STOPPANCRUISE,			//ֹͣˮƽ��ת	
	EXTPTZ_SETLEFTBORDER,			//������߽�		
	EXTPTZ_SETRIGHTBORDER,			//�����ұ߽�	
	EXTPTZ_STARTLINESCAN,			//�Զ�ɨ�迪ʼ 
	EXTPTZ_CLOSELINESCAN,			//�Զ�ɨ�迪ֹͣ 
	EXTPTZ_ADDTOLOOP,				//����Ԥ�õ㵽Ѳ��	p1Ѳ����·	p2Ԥ�õ�ֵ	
	EXTPTZ_DELFROMLOOP,				//ɾ��Ѳ����Ԥ�õ�	p1Ѳ����·	p2Ԥ�õ�ֵ	
	EXTPTZ_POINT_LOOP_CONTROL,		//��ʼѲ�� 28
	EXTPTZ_POINT_STOP_LOOP_CONTROL,	//ֹͣѲ��
	EXTPTZ_CLOSELOOP,				//���Ѳ��	p1Ѳ����·		
	EXTPTZ_FASTGOTO,				//���ٶ�λ	
	EXTPTZ_AUXIOPEN,				//�������أ��ر�����������//param1 �μ�SDK_PtzAuxStatus��param2���������ֵ
	EXTPTZ_OPERATION_MENU,			//����˵����������а��������أ�ȷ���ȵ�
	EXTPTZ_REVERSECOMM,				//��ͷ��ת
	EXTPTZ_OPERATION_RESET,			//��̨��λ

	EXTPTZ_TOTAL,
};
/// ��̨��������
enum SDK_PtzAuxStatus
{
	EXTPTZ_AUX_ON,	// ��
	EXTPTZ_AUX_OFF,	// ��
	EXTPTZ_AUX_NR,		
};

#define PAN_AUTO		29	/* ��̨��SS���ٶ������Զ�ɨ�� */
//#define EXTPTZ_FASTGOTO	30	//��ά��λ


#define NET_MAX_CHANNUM 			64			//���ͨ������
#define NET_DECORDR_CH              64          //������ͨ������
#define NET_MAX_USER_NUM			60			//����û���
#define NET_MAX_RIGTH_NUM			200			//���Ȩ����
#define NET_MAX_GROUP_NUM			50			//�������
#define NET_MAX_USER_LENGTH			32			//�û���������󳤶�
#define NET_MAX_COMBINE_NUM			2			//�����ϱ���ͨ����
#define NET_MAX_DECORDR_CH          64          //������ͨ������	

#define NET_MAX_DDNS_TYPE			5			//֧�ֵ�DDNS����
#define NET_MAX_ARSP_TYPE			5
#define NET_MAX_ALARMSERVER_TYPE    5           //֧�ֱ�����������
#define NET_MAX_SYSFUNC				20			//���ϵͳ���ܸ���
#define NET_MAX_PTZ_PROTOCOL_LENGTH 32			//��̨Э��������󳤶�
#define NET_N_WEEKS					7			//������
#define	NET_N_TSECT					6			//ʱ�����
#define NET_MD_REGION_ROW			32			//��̬�����������
#define NET_COVERNUM				8			 //����������
#define NET_MAX_FILTERIP_NUM		64			//IP��ַ��������
#define NET_NAME_PASSWORD_LEN		64			//�û���������󳤶�
#define NET_MAX_PATH_LENGTH	        260			//·������
#define NET_N_MIN_TSECT				2
#define NET_MAX_RETURNED_LOGLIST	128			//�����־����
#define NET_MAX_MAC_LEN             32          //MAC��ַ�ַ���󳤶�
#define NET_IW_ENCODING_TOKEN_MAX   128
#define NET_MAX_AP_NUMBER           32          //SID����������ݶ�10
#define NET_MAX_INFO_LEN		    128
#define NET_MAX_USERNAME_LENGTH		128
#define NET_MAX_SERIALNO_LENGTH		128         //������ͨ������
#define NET_CHANNEL_NAME_MAX_LEN    64			//ͨ��������󳤶�
#define NET_MAX_LINE_PER_OSD_AREA   12			//������һ��OSD������������ʾ���ַ�����

//DDNS����
#define DDNS_MAX_DDNS_NAMELEN       64  		//����������
#define DDNS_MAX_DDNS_PWDLEN        32   		//���볤��
#define DDNS_MAX_DDNS_IPSIZE        64   		//IP��ַ����
#define DDNS_MAX_DDNS_IDSIZE        32   		//�豸��ʶ����
#define DDNS_MAX_SERIALINFO_SIZE    16 			//���к��Լ��û�������

#define  NET_MAX_MSK_SIZE           128			//��������Ĵ�С


//���������
#define CAMERAPARA_MAXNUM           16    		//�ع�������Ŀǰ��󳤶�
//�����������
#define NET_MAX_RECIVE_MSG_PHONE_COUNT 3		///<�������������

//VGA�ֱ���
#define VGA_MAXNUM        32       				//�ֱ��� ����
#define VGA_NAME_LENGTH   10					//�ֱ��� ����	

//��ʾ���豸�б�(�豸������)
#define DEV_LIST_SHOW  256

//IP SIZE
#define IP_SIZE  16
//#define  MAX_HVR_CHNCAP 16
//DDNS�������豸����Ϣ

//ͨ��ģʽ
#define MAX_HVR_CHNCAP_CHN		32

#define  NET_NAME_TOKEN_LEN 128

#define  NET_NAME_URL_LEN 128
#define  NET_NAME_ID_LEN 64
#define  NET_MAX_POS_FUNC_KEYWORDS 4 //POS���������֧�ֵĹؼ��ָ���
#define  NET_MAX_TITLE_DOT_BUF_LEN	 64*24*24
//Ӳ����Ϣ
#define NET_FSLEN 8	//��IConstraint::FS_LEN������

//����ͼƬ��Ϣ��С
#define MAX_PLATE_NUM 7

typedef struct _DDNS_INFO
{
	char ID[64];    						//�豸��ʶ
	char Alias[DDNS_MAX_DDNS_NAMELEN];
	char IP[DDNS_MAX_DDNS_IPSIZE];   		//����IP
	char LanIP[DDNS_MAX_DDNS_IPSIZE];		//����IP
	int WebPort; 							//Web�˿�,Ĭ��Ϊ80
	int MediaPort; 							//ý��˿�,Ĭ��Ϊ34567
	int MobilePort;  						//�ֻ���ض˿ڣ�Ĭ��Ϊ34599
	int UPNPWebPort;  						//UPNP����Web�˿�,UPNP������Ϊ0
	int UPNPMediaPort; 						//UPNP����ý��˿�,UPNP������Ϊ0
	int UPNPMobilePort; 					//UPNP�����ֻ���ض˿�,UPNP������Ϊ0
	int ChannelNum; 						//ͨ����
	int Status; 							//״̬
	char Username[DDNS_MAX_DDNS_NAMELEN]; 	//�û���
	char Password[DDNS_MAX_DDNS_PWDLEN]; 	//����
}DDNS_INFO,*pDDNS_INFO;

//DDNS��Ϣ��ѯģʽ
typedef struct _SearchMode
{
	int  nType;        								//��ѯ���ͣ���SearchModeType
	char szSerIP[DDNS_MAX_DDNS_IPSIZE];				//��������ַ
	int nSerPort;           						//�������˿ں�
	char szSerialInfo[DDNS_MAX_SERIALINFO_SIZE];  	//����ǰ����кţ���Ϊ���кţ�������û�������Ϊ�û���
	char szPassWord[DDNS_MAX_DDNS_PWDLEN]; 			//���û�����½ʱ�������

}SearchMode;

//DDNS��Ϣ��ѯ����
enum SearchModeType
{
	DDNS_SERIAL = 0,//�����к�
	DDNS_USERNAME,  //���û���
};
//ʵʱԤ����չ�ӿ����ӵĲ�����Ԥ������
typedef enum _H264_DVR_RealPlayType
{
	NET_RType_Realplay = 0,		//ʵʱԤ��
	NET_RType_Main_Realplay2,	//ʵʱ����-����������ͬ��NET_RType_Realplay
	NET_RType_Main_Realplay3,
	NET_RType_Sub_Realplay_1,	//ʵʱ����-������1
	NET_RType_Sub_Realplay_2,	//ʵʱ����-������2
	NET_RType_Sub_Realplay_3,	//ʵʱ����-������3

	NET_RType_Multiplay_1,		//�໭��Ԥ����1����
	NET_RType_Multiplay_4,		//�໭��Ԥ����4����
	NET_RType_Multiplay_6,		//�໭��Ԥ����6����
	NET_RType_Multiplay_8,		//�໭��Ԥ����8����
	NET_RType_Multiplay_9,		//�໭��Ԥ����9����
	NET_RType_Multiplay_12,		//�໭��Ԥ����12����
	NET_RType_Multiplay_16,		//�໭��Ԥ����16����
} NET_RealPlayType;

/// ��ϱ���ģʽ
enum NetCombinType
{
	NET_COMBIN_NONE,
	NET_COMBIN_1,
	NET_COMBIN_2,
	NET_COMBIN_3,
	NET_COMBIN_4,
	NET_COMBIN_5,
	NET_COMBIN_6,
	NET_COMBIN_7,
	NET_COMBIN_8,
	NET_COMBIN_9,
	NET_COMBIN_10,
	NET_COMBIN_11,
	NET_COMBIN_12,
	NET_COMBIN_13,
	NET_COMBIN_14,
	NET_COMBIN_15,
	NET_COMBIN_16,
	NET_COMBIN_1_4,
	NET_COMBIN_5_8,
	NET_COMBIN_9_12,
	NET_COMBIN_13_16,
	NET_COMBIN_1_8,
	NET_COMBIN_9_16,
	NET_COMBIN_1_9,
	NET_COMBIN_8_16,
	NET_COMBIN_1_16
};

//��Щ�ṹ���ö�����ṩ���ⲿʹ�ã����п��ܻ���豸�Ǳ߶�����2��,���Զ���ǰ�����SDK_
enum SDK_CAPTURE_SIZE_t {
	SDK_CAPTURE_SIZE_D1,		///< 720*576(PAL)	720*480(NTSC)   800*480
	SDK_CAPTURE_SIZE_HD1,		///< 352*576(PAL)	352*480(NTSC)
	SDK_CAPTURE_SIZE_BCIF,		///< 720*288(PAL)	720*240(NTSC)
	SDK_CAPTURE_SIZE_CIF,		///< 352*288(PAL)	352*240(NTSC)
	SDK_CAPTURE_SIZE_QCIF,		///< 176*144(PAL)	176*120(NTSC)
	SDK_CAPTURE_SIZE_VGA,		///< 640*480(PAL)	640*480(NTSC)
	SDK_CAPTURE_SIZE_QVGA,		///< 320*240(PAL)	320*240(NTSC)
	SDK_CAPTURE_SIZE_SVCD,		///< 480*480(PAL)	480*480(NTSC)
	SDK_CAPTURE_SIZE_QQVGA,		///< 160*128(PAL)	160*128(NTSC)
	SDK_CAPTURE_SIZE_ND1 = 9,   ///< 240*192
	SDK_CAPTURE_SIZE_650TVL,    ///< 926*576
	SDK_CAPTURE_SIZE_720P,      ///< 1280*720
	SDK_CAPTURE_SIZE_1_3M,      ///< 1280*960
	SDK_CAPTURE_SIZE_UXGA ,     ///< 1600*1200
	SDK_CAPTURE_SIZE_1080P,     ///< 1920*1080
	SDK_CAPTURE_SIZE_WUXGA,     ///< 1920*1200
	SDK_CAPTURE_SIZE_2_5M,      ///< 1872*1408
	SDK_CAPTURE_SIZE_3M,        ///< 2048*1536
	SDK_CAPTURE_SIZE_5M,        ///< 3744*1408
	SDK_CAPTURE_SIZE_NR =19,
	SDK_CAPTURE_SIZE_1080N = 19,///< 960*1080
	SDK_CAPTURE_SIZE_4M,        ///< 2592*1520
	SDK_CAPTURE_SIZE_6M,		///< 3072��2048
	SDK_CAPTURE_SIZE_8M,		///< 3264��2448
	SDK_CAPTURE_SIZE_12M,		///< 4000*3000
	SDK_CAPTURE_SIZE_4K,		///< 4096 * 2160ͨ��/3840*2160��˼
	SDK_CAPTURE_SIZE_EXT_V2_NR =25,
	SDK_CAPTURE_SIZE_720N = 25,  	///< 640*720
	SDK_CAPTURE_SIZE_WSVGA,			///< 1024*576
	SDK_CAPTURE_SIZE_NHD,			///< Wifi IPC 640*360
	SDK_CAPTURE_SIZE_3M_N,			///< 1024*1536
	SDK_CAPTURE_SIZE_4M_N,			///< 1296*1520
	SDK_CAPTURE_SIZE_5M_N,			///< 1872*1408
	SDK_CAPTURE_SIZE_4K_N,			///< 2048 * 2160ͨ��/1920*2160��˼
	SDK_CAPTURE_SIZE_EXT_V3_NR,
};

/// ������������ģʽ����
enum SDK_capture_brc_t {
	SDK_CAPTURE_BRC_CBR,			///< �̶�������
	SDK_CAPTURE_BRC_VBR,			///< �ɱ�������
	SDK_CAPTURE_BRC_MBR,			///< ���������
	SDK_CAPTURE_BRC_NR				///< ö�ٵ���������ģʽ��Ŀ��
};

/// ����ѹ����ʽ����
enum SDK_CAPTURE_COMP_t {
	SDK_CAPTURE_COMP_DIVX_MPEG4,	///< DIVX MPEG4��
	SDK_CAPTURE_COMP_MS_MPEG4,		///< MS MPEG4��
	SDK_CAPTURE_COMP_MPEG2,			///< MPEG2��
	SDK_CAPTURE_COMP_MPEG1,			///< MPEG1��
	SDK_CAPTURE_COMP_H263,			///< H.263
	SDK_CAPTURE_COMP_MJPG,			///< MJPG
	SDK_CAPTURE_COMP_FCC_MPEG4,		///< FCC MPEG4
	SDK_CAPTURE_COMP_H264,			///< H.264
	SDK_CAPTURE_COMP_H265,			///< H.265
	SDK_CAPTURE_COMP_NR				///< ö�ٵ�ѹ����׼��Ŀ��
};

/// ����ͨ������
enum SDK_CAPTURE_CHANNEL_t {
	SDK_CHL_MAIN_T = 0,		///< ��ͨ��	��	������1 
	SDK_CHL_2END_T = 1,		///< ��ͨ��	��	��������2 
	SDK_CHL_3IRD_T = 2,		///< ��ͨ��	��	��������3 
	SDK_CHL_4RTH_T = 3,		///< ��ͨ��	��	��������4 
	SDK_CHL_JPEG_T = 4,		///< ��ͨ��	��	��JPEGץͼ 
	SDK_CHL_FUNCTION_NUM
};
/// ��Ƶ��������
enum SDK_AudioEncodeTypes
{
	SDK_AUDIO_ENCODE_NONE = 0,
	SDK_AUDIO_ENCODE_G729_8KBIT,
	SDK_AUDIO_ENCODE_G726_16KBIT,
	SDK_AUDIO_ENCODE_G726_24KBIT,
	SDK_AUDIO_ENCODE_G726_32KBIT,
	SDK_AUDIO_ENCODE_G726_40KBIT,
	SDK_AUDIO_ENCODE_PCM_8TO16BIT,
	SDK_AUDIO_ENCODE_PCM_ALAW,
	SDK_AUDIO_ENCODE_PCM_ULAW,
	SDK_AUDIO_ENCODE_ADPCM8K16BIT,
	SDK_AUDIO_ENCODE_ADPCM16K16BIT,
	SDK_AUDIO_ENCODE_G711_ALAW,
	SDK_AUDIO_ENCODE_MPEG2_LAYER1,
	SDK_AUDIO_ENCODE_AMR8K16BIT,
	SDK_AUDIO_ENCODE_G711_ULAW,
	SDK_AUDIO_ENCODE_IMA_ADPCM_8K16BIT,
	SDK_AUDIO_ENCODE_TYPES_NR,
};


typedef enum _SDK_CONFIG_TYPE
{
	E_SDK_CONFIG_NOTHING = 0,
	E_SDK_CONFIG_USER,					//�û���Ϣ��������Ȩ���б��û��б�����б�   ��Ӧ�ṹ��USER_MANAGE_INFO
	E_SDK_CONFIG_ADD_USER,				//�����û�---��Ӧ�ṹ��USER_INFO
	E_SDK_CONFIG_MODIFY_USER,			//�޸��û�---��Ӧ�ṹ��CONF_MODIFYUSER
	E_SDK_CONFIG_DELETE_USER,			//��Ӧ�ṹ��USER_INFO
	E_SDK_CONFIG_ADD_GROUP,				//������---��Ӧ�ṹ��USER_GROUP_INFO
	E_SDK_CONFIG_MODIFY_GROUP,			//�޸���---��Ӧ�ṹ��CONF_MODIFYGROUP
	E_SDK_COFIG_DELETE_GROUP,			//��Ӧ�ṹ��---USER_GROUP_INFO
	E_SDK_CONFIG_MODIFY_PSW,			//�޸�����---��Ӧ�ṹ��_CONF_MODIFY_PSW
	E_SDK_CONFIG_ABILITY_SYSFUNC = 9,	//֧�ֵ����繦��---��Ӧ�ṹ��SDK_SystemFunction
	E_SDK_CONFIG_ABILTY_ENCODE = 10,	//���Ȼ�ñ�������---��Ӧ�ṹ��CONFIG_EncodeAbility
	E_SDK_CONFIG_ABILITY_PTZPRO,		//��̨Э��---��Ӧ�ṹ��SDK_PTZPROTOCOLFUNC
	E_SDK_COMFIG_ABILITY_COMMPRO,		//����Э��---��Ӧ�ṹ��SDK_COMMFUNC
	E_SDK_CONFIG_ABILITY_MOTION_FUNC,	//��̬����---��Ӧ�ṹ��SDK_MotionDetectFunction
	E_SDK_CONFIG_ABILITY_BLIND_FUNC,	//��Ƶ�ڵ���---��Ӧ�ṹ��SDK_BlindDetectFunction
	E_SDK_CONFIG_ABILITY_DDNS_SERVER,	//DDNS����֧������---��Ӧ�ṹ��SDK_DDNSServiceFunction
	E_SDK_CONFIG_ABILITY_TALK,			//�Խ���������---��Ӧ�ṹ��SDK_DDNSServiceFunction
	E_SDK_CONFIG_SYSINFO = 17,			//ϵͳ��Ϣ---��Ӧ�ṹ��H264_DVR_DEVICEINFO
	E_SDK_CONFIG_SYSNORMAL,				//��ͨ����---��Ӧ�ṹ��SDK_CONFIG_NORMAL
	E_SDK_CONFIG_SYSENCODE,				//��������---��Ӧ�ṹ��SDK_EncodeConfigAll
	E_SDK_CONFIG_SYSNET = 20,			//��������---��Ӧ�ṹ��SDK_CONFIG_NET_COMMON
	E_SDK_CONFIG_PTZ,					//��̨ҳ��---��Ӧ�ṹ��SDK_STR_PTZCONFIG_ALL
	E_SDK_CONFIG_COMM,					//����ҳ��---��Ӧ�ṹ��SDK_CommConfigAll
	E_SDK_CONFIG_RECORD,				//¼�����ý���---��Ӧ�ṹ��SDK_RECORDCONFIG
	E_SDK_CONFIG_MOTION,				//��̬���ҳ��---��Ӧ�ṹ��SDK_MOTIONCONFIG
	E_SDK_CONFIG_SHELTER,				//��Ƶ�ڵ�---��Ӧ�ṹ��SDK_BLINDDETECTCONFIG
	E_SDK_CONFIG_VIDEO_LOSS,  			//��Ƶ��ʧ---��Ӧ�ṹ��SDK_VIDEOLOSSCONFIG
	E_SDK_CONFIG_ALARM_IN,				//��������---��Ӧ�ṹ��SDK_ALARM_INPUTCONFIG
	E_SDK_CONFIG_ALARM_OUT,				//�������---��Ӧ�ṹ��SDK_AlarmOutConfigAll
	E_SDK_CONFIG_DISK_MANAGER,			//Ӳ�̹������---��Ӧ�ṹ��SDK_StorageDeviceControl
	E_SDK_CONFIG_OUT_MODE = 30,			//���ģʽ����---��Ӧ�ṹ��SDK_VideoWidgetConfigAll
	E_SDK_CONFIG_CHANNEL_NAME,			//ͨ������---��Ӧ�ṹ��SDK_ChannelNameConfigAll
	E_SDK_CONFIG_AUTO,					//�Զ�ά����������---��Ӧ�ṹ��SDK_AutoMaintainConfig
	E_SDK_CONFIG_DEFAULT,     			//�ָ�Ĭ�Ͻ�������---��Ӧ�ṹ��SDK_SetDefaultConfigTypes
	E_SDK_CONFIG_DISK_INFO,				//Ӳ����Ϣ---��Ӧ�ṹ��SDK_StorageDeviceInformationAll
	E_SDK_CONFIG_LOG_INFO,				//��ѯ��־---��Ӧ�ṹ��SDK_LogList
	E_SDK_CONFIG_NET_IPFILTER,			//����������---��Ӧ�ṹ��SDK_NetIPFilterConfig
	E_SDK_CONFIG_NET_DHCP,				//DHCP����---��Ӧ�ṹ��SDK_NetDHCPConfigAll
	E_SDK_CONFIG_NET_DDNS,				//DDNS��Ϣ---��Ӧ�ṹ��SDK_NetDDNSConfigALL
	E_SDK_CONFIG_NET_EMAIL,				//EMAIL---��Ӧ�ṹ��SDK_NetEmailConfig
	E_SDK_CONFIG_NET_MULTICAST = 40,	//�鲥---��Ӧ�ṹ��SDK_NetMultiCastConfig
	E_SDK_CONFIG_NET_NTP,				//NTP---��Ӧ�ṹ��SDK_NetNTPConfig
	E_SDK_CONFIG_NET_PPPOE,				//PPPOE---��Ӧ�ṹ��SDK_NetPPPoEConfig
	E_SDK_CONFIG_NET_DNS,				//DNS---��Ӧ�ṹ��SDK_NetDNSConfig
	E_SDK_CONFIG_NET_FTPSERVER,			//FTP---��Ӧ�ṹ��SDK_FtpServerConfig
	E_SDK_CONFIG_SYS_TIME,				//ϵͳʱ��---��Ӧ�ṹ��SDK_SYSTEM_TIME(�ӿ�H264_DVR_SetSystemDateTimeҲ����ʵ��)
	E_SDK_CONFIG_CLEAR_LOG,				//�����־(�ӿ�H264_DVR_ControlDVR)											
	E_SDK_REBOOT_DEV,					//�������豸(�ӿ�H264_DVR_ControlDVR)												
	E_SDK_CONFIG_ABILITY_LANG,			//֧������---��Ӧ�ṹ��SDK_MultiLangFunction
	E_SDK_CONFIG_VIDEO_FORMAT,																	
	E_SDK_CONFIG_COMBINEENCODE = 50,	//��ϱ���---��Ӧ�ṹ��SDK_CombineEncodeConfigAll
	E_SDK_CONFIG_EXPORT,				//���õ���														
	E_SDK_CONFIG_IMPORT,				//���õ���
	E_SDK_LOG_EXPORT,					//��־����														
	E_SDK_CONFIG_COMBINEENCODEMODE, 	//��ϱ���ģʽ---��Ӧ�ṹ��SDK_CombEncodeModeAll
	E_SDK_WORK_STATE,					//����״̬---SDK_DVR_WORKSTATE(�ӿ�H264_DVR_GetDVRWorkStateҲ���Ի�ȡ)															
	E_SDK_ABILITY_LANGLIST, 			//ʵ��֧�ֵ����Լ�---��Ӧ�ṹ��SDK_MultiLangFunction									
	E_SDK_CONFIG_NET_ARSP,				//ARSP---��Ӧ�ṹ��SDK_NetARSPConfigAll
	E_SDK_CONFIG_SNAP_STORAGE,			//ץͼ����---��Ӧ�ṹ��SDK_SnapshotConfig
	E_SDK_CONFIG_NET_3G, 				//3G����---��Ӧ�ṹ��SDK_Net3GConfig
	E_SDK_CONFIG_NET_MOBILE = 60, 		//�ֻ����---��Ӧ�ṹ��SDK_NetMoblieConfig
	E_SDK_CONFIG_UPGRADEINFO, 			//��ȡ������Ϣ/����/�ļ���---��Ӧ�ṹ��SDK_UpgradeInfo
	E_SDK_CONFIG_NET_DECODER,			//��������ַ����V1(����)---��Ӧ�ṹ��SDK_NetDecoderConfigAll
	E_SDK_ABILITY_VSTD, 				//ʵ��֧�ֵ���Ƶ��ʽ---��Ӧ�ṹ��SDK_MultiVstd
	E_SDK_CONFIG_ABILITY_VSTD,			//֧����Ƶ��ʽ---��Ӧ�ṹ��SDK_MultiVstd
	E_SDK_CONFIG_NET_UPNP, 				//UPUN����---��Ӧ�ṹ��SDK_NetUPNPConfig
	E_SDK_CONFIG_NET_WIFI,				//WIFI---��Ӧ�ṹ��SDK_NetWifiConfig
	E_SDK_CONFIG_NET_WIFI_AP_LIST,		//��������wifi�б�---��Ӧ�ṹ��SDK_NetWifiDeviceAll
	E_SDK_CONFIG_SYSENCODE_SIMPLIIFY, 	//�򻯵ı�������---��Ӧ�ṹSDK_EncodeConfigAll_SIMPLIIFY
	E_SDK_CONFIG_ALARM_CENTER,  		//�澯����---��Ӧ�ṹ��SDK_NetAlarmServerConfigAll
	E_SDK_CONFIG_NET_ALARM = 70,		//����澯---��Ӧ�ṹ��SDK_NETALARMCONFIG_ALL																		
	E_SDK_CONFIG_NET_MEGA,     			//���Ż�ͨ---��Ӧ�ṹ��SDK_CONFIG_NET_MEGA
	E_SDK_CONFIG_NET_XINGWANG, 			//����---��Ӧ�ṹ��SDK_CONFIG_NET_XINGWANG
	E_SDK_CONFIG_NET_SHISOU,   			//����---��Ӧ�ṹ��SDK_CONFIG_NET_SHISOU
	E_SDK_CONFIG_NET_VVEYE,    			//VVEYE---��Ӧ�ṹ��SDK_CONFIG_NET_VVEYE
	E_SDK_CONFIG_NET_PHONEMSG,  		//����---��Ӧ�ṹ��SDK_NetShortMsgCfg
	E_SDK_CONFIG_NET_PHONEMEDIAMSG,  	//����---��Ӧ�ṹ��SDK_NetMultimediaMsgCfg
	E_SDK_VIDEO_PREVIEW,				//
	E_SDK_CONFIG_NET_DECODER_V2,		//��������ַ����V2(����)---��Ӧ�ṹ��SDK_NetDecorderConfigAll_V2
	E_SDK_CONFIG_NET_DECODER_V3,		//��������ַ����V3---��Ӧ�ṹ��SDK_NetDecorderConfigAll_V3
	E_SDK_CONFIG_ABILITY_SERIALNO = 80,	//���к�---��Ӧ�ṹ��SDK_AbilitySerialNo(�����Բ����豸���к�(������),���кſ��Դӵ�½�ӿڻ�ȡ��)
	E_SDK_CONFIG_NET_RTSP,    			//RTSP---��Ӧ�ṹ��SDK_NetRTSPConfig
	E_SDK_GUISET,              			//����GUI�������---��Ӧ�ṹ��SDK_GUISetConfig
	E_SDK_CATCHPIC,               		//ץͼ												
	E_SDK_VIDEOCOLOR,             		//��Ƶ��ɫ����---��Ӧ�ṹ��SDK_VideoColorConfigAll
	E_SDK_CONFIG_COMM485,				//����485Э������---��Ӧ�ṹ��SDK_STR_RS485CONFIG_ALL
	E_SDK_COMFIG_ABILITY_COMMPRO485, 	//����485Э��---��Ӧ�ṹ��SDK_COMMFUNC
	E_SDK_CONFIG_SYS_TIME_NORTC,		//����ϵͳʱ��noRtc---��Ӧ�ṹ��SDK_SYSTEM_TIME
	E_SDK_CONFIG_REMOTECHANNEL,   		//Զ��ͨ��---����
	E_SDK_CONFIG_OPENTRANSCOMCHANNEL , 	//��͸������---��Ӧ�ṹ��TransComChannel
	E_SDK_CONFIG_CLOSETRANSCOMCHANNEL = 90,//�ر�͸������
	E_SDK_CONFIG_SERIALWIRTE,  			//д��͸��������Ϣ
	E_SDK_CONFIG_SERIALREAD,   			//��ȡ͸��������Ϣ
	E_SDK_CONFIG_CHANNELTILE_DOT,		//������Ϣ-�޸�IPCͨ������Ҫ������Ϣ---��Ӧ�ṹ��SDK_TitleDot
	E_SDK_CONFIG_CAMERA,           		//���������---��Ӧ�ṹ��SDK_CameraParam
	E_SDK_CONFIG_ABILITY_CAMERA,    	//�ع�������---��Ӧ�ṹ��SDK_CameraAbility
	E_SDK_CONFIG_BUGINFO,    			//�������													
	E_SDK_CONFIG_STORAGENOTEXIST,		//Ӳ�̲�����---��Ӧ�ṹ��SDK_VIDEOLOSSCONFIG
	E_SDK_CONFIG_STORAGELOWSPACE, 		//Ӳ����������---��Ӧ�ṹ��SDK_StorageLowSpaceConfig								
	E_SDK_CONFIG_STORAGEFAILURE, 		//Ӳ�̳���---��Ӧ�ṹ��SDK_StorageFailConfig
	E_SDK_CFG_NETIPCONFLICT = 100,   	//IP��ͻ---��Ӧ�ṹ��SDK_VIDEOLOSSCONFIG
	E_SDK_CFG_NETABORT,  				//�����쳣---��Ӧ�ṹ��SDK_VIDEOLOSSCONFIG
	E_SDK_CONFIG_CHNSTATUS, 			//ͨ��״̬---��Ӧ�ṹ��SDK_NetDecorderChnStatusAll
	E_SDK_CONFIG_CHNMODE,  				//ͨ��ģʽ---��Ӧ�ṹ��SDK_NetDecorderChnModeConfig
	E_SDK_CONFIG_NET_DAS,    			//����ע��---��Ӧ�ṹ��SDK_DASSerInfo
	E_SDK_CONFIG_CAR_INPUT_EXCHANGE,    //�ⲿ��Ϣ�����복��״̬�Ķ�Ӧ��ϵ---��Ӧ�ṹ��SDK_CarStatusExchangeAll			
	E_SDK_CONFIG_DELAY_TIME,       		//����ϵͳ��ʱ����---��Ӧ�ṹ��SDK_CarDelayTimeConfig
	E_SDK_CONFIG_NET_ORDER,             //�������ȼ�---��Ӧ�ṹ��SDK_NetOrderConfig
	E_SDK_CONFIG_ABILITY_NETORDER , 	//�������ȼ���������---��Ӧ�ṹ��SDK_NetOrderFunction
	E_SDK_CONFIG_CARPLATE,				//���ƺ�����---��Ӧ�ṹ��SDK_CarPlates
	E_SDK_CONFIG_LOCALSDK_NET_PLATFORM = 110, //����ƽ̨��Ϣ����---��Ӧ�ṹ��SDK_LocalSdkNetPlatformConfig
	E_SDK_CONFIG_GPS_TIMING,            //GPSУʱ�������---��Ӧ�ṹ��SDK_GPSTimingConfig
	E_SDK_CONFIG_VIDEO_ANALYZE, 		//��Ƶ����(����DVR)---��Ӧ�ṹ��SDK_ANALYSECONFIG
	E_SDK_CONFIG_GODEYE_ALARM,			//���۽Ӿ�����ϵͳ---��Ӧ�ṹ��SDK_GodEyeConfig
	E_SDK_CONFIG_NAT_STATUS_INFO,   	//nat״̬��Ϣ---��Ӧ�ṹ��SDK_NatStatusInfo	
	E_SDK_CONFIG_BUGINFOSAVE,     		//�������(����)									 
	E_SDK_CONFIG_MEDIA_WATERMARK,		//ˮӡ����---��Ӧ�ṹ��SDK_WaterMarkConfigAll
	E_SDK_CONFIG_ENCODE_STATICPARAM,	//��������̬����---��Ӧ�ṹ��SDK_EncodeStaticParamAll
	E_SDK_CONFIG_LOSS_SHOW_STR,		    //��Ƶ��ʧ��ʾ�ַ���
	E_SDK_CONFIG_DIGMANAGER_SHOW,	    //ͨ��������ʾ����---��Ӧ�ṹ��SDK_DigManagerShowStatus
	E_SDK_CONFIG_ABILITY_ANALYZEABILITY = 120,//���ܷ�������---��Ӧ�ṹ��SDK_ANALYZEABILITY
	E_SDK_CONFIG_VIDEOOUT_PRIORITY,   //��ʾHDMI VGA���ȼ�������
	E_SDK_CONFIG_NAT,		  		  //NAT���ܣ�MTUֵ����---��Ӧ�ṹ��SDK_NatConfig
	E_SDK_CONFIG_CPCINFO,		      //����CPC����������Ϣ---��Ӧ�ṹ��SDK_CPCDataAll
	E_SDK_CONFIG_STORAGE_POSITION,    // ¼��洢�豸����---��Ӧ�ṹ��SDK_RecordStorageType
	E_SDK_CONFIG_ABILITY_CARSTATUSNUM,//����״̬��---��Ӧ�ṹ��SDK_CarStatusNum
	E_SDK_CFG_VPN,					//VPN---��Ӧ�ṹ��SDK_VPNConfig
	E_SDK_CFG_VIDEOOUT,				//VGA��Ƶ�ֱ���---��Ӧ�ṹ��SDK_VGAresolution
	E_SDK_CFG_ABILITY_VGARESOLUTION,//֧�ֵ�VGA�ֱ����б�---��Ӧ�ṹ��SDK_VGAResolutionAbility
	E_SDK_CFG_NET_LOCALSEARCH,      //�����豸���豸�˵ľ������豸---��Ӧ�ṹ��SDK_NetDevList
	E_SDK_CFG_NETPLAT_KAINENG = 130,//�ͻ�����---��Ӧ�ṹ��SDK_CONFIG_KAINENG_INFO
	E_SDK_CFG_ENCODE_STATICPARAM_V2,//DVR��������̬����---��Ӧ�ṹ��SDK_EncodeStaticParamV2
	E_SDK_ABILITY_ENC_STATICPARAM,	//��̬����������---��Ӧ�ṹ��SDK_EncStaticParamAbility (����)
	E_SDK_CFG_C7_PLATFORM,          //C7ƽ̨����---��Ӧ�ṹ��SDK_C7PlatformConfig
	E_SDK_CFG_MAIL_TEST,            //�ʼ�����---��Ӧ�ṹ��SDK_NetEmailConfig
	E_SDK_CFG_NET_KEYBOARD,         //������̷���---��Ӧ�ṹ��SDK_NetKeyboardConfig
	E_SDK_ABILITY_NET_KEYBOARD,		//�������Э��---��Ӧ�ṹ��SDK_NetKeyboardAbility  
	E_SDK_CFG_SPVMN_PLATFORM,       //28181Э������---��Ӧ�ṹ��SDK_ASB_NET_VSP_CONFIG	
	E_SDK_CFG_PMS,				    //�ֻ�����---��Ӧ�ṹ��SDK_PMSConfig
	E_SDK_CFG_OSD_INFO,             //��Ļ��ʾ��Ϣ---��Ӧ�ṹ��SDK_OSDInfoConfigAll
	E_SDK_CFG_KAICONG = 140,        //�ͻ�����---��Ӧ�ṹ��SDK_KaiCongAlarmConfig
	E_SDK_CFG_DIGITAL_REAL,			//����֧�ֵ�ͨ��ģʽ---��Ӧ�ṹ��SDK_VideoChannelManage
	E_SDK_ABILITY_PTZCONTROL,		//PTZ����������---��Ӧ�ṹ��SDK_PTZControlAbility
	E_SDK_CFG_XMHEARTBEAT,			//��Ӧ�ṹ��SDK_XMHeartbeatConfig
	E_SDK_CFG_MONITOR_PLATFORM,		//ƽ̨����---��Ӧ�ṹ��SDK_MonitorPlatformConfig
	E_SDK_CFG_PARAM_EX,				//����ͷ��չ����---��Ӧ�ṹ��SDK_CameraParamEx
	E_SDK_CFG_NETPLAT_ANJU_P2P,		//����P2P---��Ӧ�ṹ��SDK_NetPlatformCommonCfg  
	E_SDK_GPS_STATUS,				//GPS������Ϣ---��Ӧ�ṹ��SDK_GPSStatusInfo 
	E_SDK_WIFI_STATUS,				//Wifi������Ϣ---��Ӧ�ṹ��SDK_WifiStatusInfo
	E_SDK_3G_STATUS,  				//3G������Ϣ---��Ӧ�ṹ��SDK_WirelessStatusInfo
	E_SDK_DAS_STATUS = 150, 		//����ע��״̬---��Ӧ�ṹ��SDK_DASStatusInfo 
	E_SDK_ABILITY_DECODE_DELEY,		//�����������---��Ӧ�ṹ��SDK_DecodeDeleyTimePrame
	E_SDK_CFG_DECODE_PARAM,     	//���������ʱ---��Ӧ�ṹ��SDK_DecodeParam
	E_SDK_CFG_VIDEOCOLOR_CUSTOM,    //SDK_VIDEOCOLOR_PARAM_CUSTOM
	E_SDK_ABILITY_ONVIF_SUB_PROTOCOL,//onvif��Э��---��Ӧ�ṹ��SDK_AbilityMask   
	E_SDK_CONFIG_EXPORT_V2,      	//�����豸Ĭ�����ã�������������
	E_SDK_CFG_CAR_BOOT_TYPE,      	//���ؿ��ػ�ģʽ---��Ӧ�ṹ��SDK_CarBootTypeConfig
	E_SDK_CFG_IPC_ALARM,			//IPC���籨��---��Ӧ�ṹ��SDK_IPCAlarmConfigAll
	E_SDK_CFG_NETPLAT_TUTK_IOTC,	//TUTK IOTCƽ̨����---��Ӧ�ṹ��SDK_NetPlatformCommonCfg
	E_SDK_CFG_BAIDU_CLOUD,     		//�ٶ���---��Ӧ�ṹ��SDK_BaiduCloudCfg
	E_SDK_CFG_PMS_MSGNUM = 160,		//�ֻ�������---��Ӧ�ṹ��SDK_PhoneInfoNum
	E_SDK_CFG_IPC_IP,           	//����DVRȥ�޸��豸IP---��Ӧ�ṹ��SDK_IPSetCfg
	E_SDK_ABILITY_DIMEN_CODE,       //��ά�����---��Ӧ�ṹ��SDK_DimenCodeAll
	E_SDK_CFG_MOBILE_WATCH, 	 	//�й������ֻ�����ƽ̨����---��Ӧ�ṹ��SDK_MobileWatchCfg	
	E_SDK_CFG_BROWSER_LANGUAGE,   	//ʹ�������ʱʹ�õ�����---��Ӧ�ṹ��SDK_BrowserLanguageType
	E_SDK_CFG_TIME_ZONE,			//ʱ������---��Ӧ�ṹ��SDK_TimeZone
	E_SDK_CFG_NETBJTHY,       		//�ͻ�����---��Ӧ�ṹ��SDK_MonitorPlatformConfig
	E_SDK_ABILITY_MAX_PRE_RECORD,   //��������Ԥ¼ʱ��1~30---��Ӧ�ṹ��SDK_AbilityMask
	E_SDK_CFG_DIG_TIME_SYN,			//����ͨ��ʱ��ͬ������(����ǰ��ͬ����ʽ)---��Ӧ�ṹ��SDK_TimeSynParam
	E_SDK_CONFIG_OSDINFO_DOT,		//3��OSD
	E_SDK_CFG_NET_POS = 170,		//POS������---��Ӧ�ṹ��SDK_NetPosConfigAll
	E_SDK_CFG_CUSTOMIZE_OEMINFO,	//����OEM�ͻ��汾��Ϣ---��Ӧ�ṹ��SDK_CustomizeOEMInfo
	E_SDK_CFG_DIGITAL_ENCODE, 		//����ͨ��������������---��Ӧ�ṹ��SDK_EncodeConfigAll_SIMPLIIFY
	E_SDK_CFG_DIGITAL_ABILITY, 		//����ͨ���ı�������---��Ӧ�ṹ��SDK_DigitDevInfo
	E_SDK_CFG_ENCODECH_DISPLAY,		//IE�˱���������ʾ��ǰ��ͨ����---��Ӧ�ṹ��SDK_EncodeChDisplay
	E_SDK_CFG_RESUME_PTZ_STATE,		//������̨״̬---��Ӧ�ṹ��SDK_ResumePtzState
	E_SDK_CFG_LAST_SPLIT_STATE,   	//���һ�εĻ���ָ�ģʽ�����������ָ�֮ǰ�ķָ�ģʽ
	E_SDK_CFG_SYSTEM_TIMING_WORK,   //�豸��ʱ���ػ�ʱ�����á��������Զ�ά��ҳ���Ҫ�ó��������½���ܿ�������
	E_SDK_CFG_GBEYESENV,			//�����������ƽ̨����---��Ӧ�ṹ��SDK_NetPlatformCommonCfg
	E_SDK_ABILITY_AHD_ENCODE_L, 	//AHDL������---��Ӧ�ṹ��SDK_AHDEncodeLMask
	E_SDK_CFG_SPEEDALARM = 180,		//�ٶȱ���---��Ӧ�ṹ��SDK_SpeedAlarmConfigAll
	E_SDK_CFG_CORRESPONDENT_INFO,	//�û��Զ�������---��Ӧ�ṹ��SDK_CorrespondentOwnInfo
	E_SDK_SET_OSDINFO,				//OSD��Ϣ����---��Ӧ�ṹ��SDK_OSDInfo,(�����ֻ֧��ģ��ͨ��)
	E_SDK_SET_OSDINFO_V2,			//OSD��Ϣ���ӣ�����������---��Ӧ�ṹ��SDK_OSDInfoConfigAll��(�����ֻ֧��ģ��ͨ��)
	E_SDK_ABILITY_SUPPORT_EXTSTREAM,//֧�ָ�����¼��---��Ӧ�ṹ��SDK_AbilityMask
	E_SDK_CFG_EXT_RECORD,			//����������---��Ӧ�ṹ��SDK_RECORDCONFIG_ALL/SDK_RECORDCONFIG
	E_SDK_CFG_APP_DOWN_LINK,		//�����û�������������---��Ӧ�ṹ��SDK_AppDownloadLink
	E_SDK_CFG_EX_USER_MAP,			//���ڱ�����������---��Ӧ�ṹ��SDK_UserMap
	E_SDK_CFG_TRANS_COMM_DATA, 		//�������������ϴ���UDP��TCP������������TCP����������֧��˫��ͨ��---��Ӧ�ṹ��SDK_NetTransCommData
	E_SDK_EXPORT_LANGUAGE,			//���Ե���
	E_SDK_IMPORT_LANGUAGE = 190,	//���Ե���
	E_SDK_DELETE_LANGUAGE,			//����ɾ��
	E_SDK_CFG_UPGRADE_VERSION_LIST,	//�������ļ��б�---��Ӧ�ṹ��SDK_CloudUpgradeList
	E_SDK_CFG_GSENSORALARM,			//GSENSOR����
	E_SDK_CFG_USE_PROGRAM,			//��ͻ�С����---��Ӧ�ṹ��SDK_NetUseProgram
	E_SDK_CFG_FTP_TEST,             //FTP����---��Ӧ�ṹ��SDK_FtpServerConfig
	E_SDK_CFG_FbExtraStateCtrl,  	//�������Ʒ��¼��Ƶ�״̬---��Ӧ�ṹ��SDK_FbExtraStateCtrl
	E_SDK_CFG_PHONE,				//�ֻ���
	E_SDK_PicInBuffer,				//�ֻ�ץͼ,���� 
	E_SDK_GUARD,					//���� ����
	E_SDK_UNGUARD = 200,			//����������
	E_SDK_CFG_START_UPGRADE,		//��ʼ����������
	E_SDK_CFG_AUTO_SWITCH,			//������ʱ����---��ȡ���ö���H264_DVR_GetDevConfig_Json,����ʹ��H264_DVR_SetDevConfig_Json(����ʱ�ĸ�ʽ�����ܲ����õ�������.doc)(�����ӿڼ��Json�ӿ�,�����ü��) "Name":"PowerSocket.AutoSwitch"
	E_SDK_CFG_POWER_SOCKET_SET,		//���Ʋ�������---Json�ӿ� "Name":"OPPowerSocketGet"
	E_SDK_CFG_AUTO_ARM,				//�����Ķ�ʱ������---Json�ӿ� "Name":"PowerSocket.AutoArm"
	E_SDK_CFG_WIFI_MODE,			//Wifiģʽ���ã������г���¼���л�APģʽ---��Ӧ�ṹ��SDK_NetWifiMode
	E_SDK_CFG_CIENT_INFO,			//�����ֻ��ͻ�����Ϣ---Json�ӿ� "Name":"PowerSocket.ClientInfo"
	E_SDK_CFG_ATHORITY,				//SDK_Authority---Json�ӿ� "Name":"PowerSocket.Authority"
	E_SDK_CFG_ARM ,					//SDK_Arm---Json�ӿ� "Name":"PowerSocket.Arm"
	E_SDK_CFG_AUTOLIGHT,			//����ҹ�ƵĶ�ʱ���ع��� --Json�ӿ� "Name" : "PowerSocket.AutoLight",
	E_SDK_CFG_LIGHT = 210,			//ʹ�ܺͽ�ֹҹ�ƵĶ�����Ӧ����---Json�ӿ� "Name" : "PowerSocket.Light",
	E_SDK_CFG_WORKRECORD,			//���е���ͳ��---Json�ӿ� "Name" : "PowerSocket.WorkRecord",
	E_SDK_CFG_SYSTEMTIME,			//����ʱ������� ,�����������ӵ�ʱ��,���ӵ�ʱ��,���Ͷ�ʱ���� --Json�ӿ� "Name":"System.Time"
	E_SDK_CFG_USB,					//usb�ӿڿ��ƹ���---Json�ӿ� "Name":"PowerSocket.Usb"
	E_SDK_CFG_NETPLAT_BJHONGTAIHENG,//������̩��ƽ̨---��Ӧ�ṹ��SDK_CONFIG_NET_BJHONGTAIHENG
	E_SDK_CFG_CLOUD_STORAGE,		//�ƴ洢�������---��Ӧ�ṹ��SDK_CloudRecordConfigAll
	E_SDK_CFG_IDLE_PTZ_STATE,       //��̨���ж����������---��Ӧ�ṹ��SDK_PtzIdleStateAll
	E_SDK_CFG_CAMERA_CLEAR_FOG,	    //ȥ��������---��Ӧ�ṹ��SDK_CameraClearFogAll
	E_SDK_CFG_WECHATACCOUNT,		//---��Ӧjson "Name":"PowerSocket.WechatAccount"
	E_SDK_CFG_WECHATRENEW,			//---��Ӧjson "Name":"PowerSocket.WechatRenew" 
	E_SDK_CFG_POWERSOCKET_WIFI = 220,//---��Ӧjson "Name":"PowerSocket.WiFi"
	E_SDK_CFG_CAMERA_MOTOR_CONTROL, //������������---��Ӧ�ṹ��SDK_CameraMotorCtrl
	E_SDK_CFG_ENCODE_ADD_BEEP,		//���ñ������ÿ��30��beep��---��Ӧ�ṹ��SDK_EncodeAddBeep
	E_SDK_CFG_DATALINK,			    //datalink�ͻ�����������е�ִ�г���ʹ������---��Ӧ�ṹ�� SDK_DataLinkConfig
	E_SDK_CFG_FISH_EYE_PARAM,	    //���۹��ܲ�������---��Ӧ�ṹ��SDK_FishEyeParam
	E_SDK_OPERATION_SET_LOGO,	    //��Ƶ�ϵ��������ȳ��ҵ�LOGO---��Ӧ�ṹ��SDK_SetLogo
	E_SDK_CFG_SPARSH_HEARTBEAT,		//Sparsh�ͻ���������������---��Ӧ�ṹ�� SDK_SparshHeartbeat
	E_SDK_CFG_LOGIN_FAILED,			//��¼ʧ��ʱ�����ʼ���ʹ�ýṹ��:�����¼��ṹ---��Ӧ�ṹ�� SDK_VIDEOLOSSCONFIG
	E_SDK_CFG_NETPLAT_SPVMN_NAS,	//���ճ���ͻ���nas����������---��Ӧ�ṹ��SDK_SPVMN_NAS_SERVER
	E_SDK_CFG_DDNS_APPLY,			//ddns �������ܲ���---��Ӧ�ṹ��SDK_NetDDNSConfigALL
	E_SDK_OPERATION_NEW_UPGRADE_VERSION_REQ = 230,	//�°��������汾��ѯ����---��Ӧ�ṹ��SDK_CloudUpgradeVersionRep
	E_SDK_CFG_IPV6_ADDRESS,			//ipv6------��Ӧ�Ľṹ��SDK_IPAddressV6
	E_SDK_CFG_DDNS_IPMSG,         	//DDNS����IP��ַ
	E_SDK_CFG_ONLINE_UPGRADE,		//���������������-----��Ӧ�Ľṹ��SDK_OnlineUpgradeCfg
	E_SDK_CFG_CONS_SENSOR_ALARM,    //���ò�Ʒ433��������������-----��Ӧ��SDK_ConsSensorAlarmCfg
	E_SDK_OPEARTION_SPLIT_CONTROL,  //����ָ�ģʽ-----��Ӧ�Ľṹ��SDK_SplitControl
	E_SDK_CFG_Netinfo_TRANS_COMM,	//Netinfo_cctv�ͻ����Ӵ������ݵ�ָ������������-----��Ӧ�Ľṹ��SDK_NetinfoNetTransComm
	E_SDK_CFG_RECORD_ENABLE,       	//�Ƿ�׼���ÿ�ʼ¼���ץͼ�����������ձ��ͻ�ͨ�����ڿ��ƿ���͹ر�¼����
	E_SDK_CFG_NAS,					//nas����		//SDK_NAS_LIST
	E_SDK_CFG_NKB_DEVICE_LIST,		//��������豸����
	E_SDK_CFG_PARKING_PORT = 240,	//����ϵͳ�˿ں�����  SDK_PortService
	E_SDK_CFG_NET_GBEYES,			//�Ų�ȫ����ƽ̨ SDK_GbEyesCfg
	E_SDK_CFG_GLOBALEYE,			//ȫ�������� SDK_DefaultResponse
	E_SDK_OPERATION_FISHEYE_MODIFY_CENTER,	//����Բ��У�� SDK_Point
	E_SDK_OPERATION_UTC_TIME_SETTING = 244,	//����UTCʱ��---��Ӧ�ṹ��SDK_SYSTEM_TIME
	E_SDK_CFG_INTELBRAS_SPECIAL_INFO,		//interbras ����tcp�˿ں�-----SDK_IntelBrasSpecialInfo
	E_SDK_CFG_SPVMN_PLATFORM_SIP,			//28181Э������sip�忨ip-------SDK_SIP_NET_IP_CONFIG
	E_SDK_CFG_FISH_LENS_PARAM,				//�~���R�^����------SDK_FishLensParam
	E_SDK_CFG_PTZCTRLMODE,					//ģ��ͨ����̨���ƵĿ��Ʒ�ʽѡ��-----SDK_PTZControlModeAll
	E_SDK_CFG_ENCODE_SmartH264,				//SmartH264+����------SDK_SmartH264ParamAll
	E_SDK_CFG_WIFI_INFO,					//����WIFI��Ϣ--SDK_WifiInfo
	E_SDK_CFG_NET_RTMP,						//RTMPЭ��--SDK_NetRTMPConfig
	E_SDK_CFG_SNAP_SCHEDULE,				//��ʱץͼ����--SDK_SnapConfigAll
	E_SDK_OPERATION_SET_LANGUAGE,			//����һ������
	E_SDK_CFG_PTZPRESET,					//Ԥ�õ�����--SDK_PtzPreset
	E_SDK_CFG_PTZTOUR,						//Ѳ������--SDK_PtzTour
	E_SDK_CFG_PWD_SAFETY,					//��ȫ�����������(������������)--SDK_PasswordSafety
	E_SDK_ABILITY_QUESTION_DELIVERY,		//��ȡ�����һ�����--SDK_QuestionDelivery
	E_SDK_CFG_TUTK_VERSION,					//TUTK�ͻ����ư汾��Ϣ--SDK_TutkVersion
	E_SDK_CFG_BREVIARY,						//����ͼ����
	E_SDK_CFG_SERIALPORT_ALARM,				//���ڱ�������--SDK_SerialPortAlarm
	E_SDK_OPEARTION_SET_LEARN_CODE,			//֧�ִ��ڱ������ò�������ѧ��--SDK_AMIRLearnCode
	E_SDK_CFG_PIR_ALARM,					//�ͻ�����PIR��������--SDK_PIRConfigAll
	E_SDK_OPEARTION_CAMERA_VISCA,			//�ڼκ�ViscaЭ���޸ģ����úͻ�ȡ���ʽ����--SDK_CameraViscaControl
	E_SDK_OPERATION_TIME_SETTING_NEW_WAY,	//����ϵͳʱ�䣨��ص�ʱ��ͬ���ĳ��������������������֮ǰ��ʱ���������
	E_SDK_OPERATION_UTC_TIME_SETTING_NEW_WAY,//����UTCʱ�䣨��������Э������UTCʱ�䣩
	E_SDK_CFG_DDNSADDRINFO,					//DDNS״̬��Ϣ
	E_SDK_CFG_THXY_VERION_INFO,				//�����ӥ���ư汾��Ϣ--SDK_THXY_VersionInfo
	E_SDK_CFG_ALARM_BLUR_CHECK,				//ͼ��ģ�����--SDK_BlurCheckAlarmAll
	E_SDK_CFG_INTEL_ENCODE,					//���ܱ���--SDK_IntelEnCodeCfgAll
	E_SDK_CFG_PLATE_DETECT_WHITE_LIST,		//����ʶ�������--SDK_PlateDetectWhiteList
	E_SDK_OPERATION_PLATE_DETECT_LIFT,		//�������̧��--SDK_PlateDetectLiftBar
	E_SDK_CFG_ALARM_PLATE_DETECT,			//������ⱨ��--SDK_PlateDetectAll
	E_SDK_CFG_ALARM_FACE_DETECT,			//����ʶ�𱨾�--SDK_FaceDetectAll
	E_SDK_CFG_NET_IPADAPTIVE,				//ip����Ӧ���ع���ʹ������--SDK_IPAdaptiveCfg
	E_SDK_CFG_OEM_GETINFO,					//�ͻ����ƻ�ȡϵͳ��Ϣ--SDK_OemGetInfo
	E_SDK_CFG_433_ALARM_DEV,				//�ͻ�����433��������--SDK_ConsumerAlarm433DevList
	E_SDK_CFG_NET_ONVIF_PWD_CHECKOUT,		//onvif ����У��--SDK_IpcOnvifPwdCheckout
}SDK_CONFIG_TYPE;

/// �����¼���
enum SDK_EventCodeTypes
{
	SDK_EVENT_CODE_INIT = 0,
	SDK_EVENT_CODE_LOCAL_ALARM = 1,		//���ر���(�ⲿ����)
	SDK_EVENT_CODE_NET_ALARM,			//���籨��
	SDK_EVENT_CODE_MANUAL_ALARM,		//�ֶ�����
	SDK_EVENT_CODE_VIDEO_MOTION,		//��̬���
	SDK_EVENT_CODE_VIDEO_LOSS,			//��Ƶ��ʧ
	SDK_EVENT_CODE_VIDEO_BLIND,			//��Ƶ�ڵ�
	SDK_EVENT_CODE_VIDEO_TITLE,		
	SDK_EVENT_CODE_VIDEO_SPLIT,
	SDK_EVENT_CODE_VIDEO_TOUR,
	SDK_EVENT_CODE_STORAGE_NOT_EXIST,	//�洢�豸������
	SDK_EVENT_CODE_STORAGE_FAILURE,		//�洢�豸����ʧ��
	SDK_EVENT_CODE_LOW_SPACE,			//�洢�豸��������
	SDK_EVENT_CODE_NET_ABORT,
	SDK_EVENT_CODE_COMM,
	SDK_EVENT_CODE_STORAGE_READ_ERROR,	//�洢�豸������
	SDK_EVENT_CODE_STORAGE_WRITE_ERROR,	//�洢�豸д����
	SDK_EVENT_CODE_NET_IPCONFLICT,		//ip��ͻ
	SDK_EVENT_CODE_ALARM_EMERGENCY,
	SDK_EVENT_CODE_DEC_CONNECT,	
	SDK_EVENT_CODE_UPGRADE,
	SDK_EVENT_CODE_BACK_UP,
	SDK_EVENT_CODE_SHUT_DOWN,
	SDK_EVENT_CODE_REBOOT,
	SDK_EVENT_CODE_NEWFILE,
	SDK_EVENT_CODE_VideoAnalyze,
	SDK_EVENT_CODE_IPC_ALARM,
	SDK_EVENT_CODE_SPEED_ALARM,
	SDK_EVENT_CODE_GSENSOR_AlARM,
	SDK_EVENT_CODE_LOGIN_FAILED,		//��¼ʧ��
	SDK_EVENT_CODE_SERIAL_ALARM,
	SDK_EVENT_CODE_PIR_ALARM,			//�ͻ�����PIR����
	SDK_EVENT_CODE_CONSSENSOR_ALARM, 	//�������Ʒ�󶨵��ⲿ�豸����
	SDK_EVENT_CODE_WORDDETECT,			//���ò�Ʒ������ʶ����дʱ���
	SDK_EVENT_CODE_BLURCHECK_ALARM,		//ģ����ⱨ��
	SDK_EVENT_CODE_PLATEDETECT,			//���Ƽ�ⱨ��
	SDK_EVENT_CODE_FACEDETECT,			//������ⱨ��
	SDK_EVENT_CODE_433ALARM,			//�ͻ�����433����
	SDK_EVENT_CODE_433DEVADDRESULT,		//�ͻ�����433��Խ��
	SDK_EVENT_CODE_NR,
};
//! �������õ�����
enum SDK_ENCODE_TYPE_BY_RECORD
{
	SDK_ENCODE_TYPE_TIM = 0,
	SDK_ENCODE_TYPE_MTD = 1,
	SDK_ENCODE_TYPE_ALM = 2,
	SDK_ENCODE_TYPE_NUM = 3,
	SDK_ENCODE_TYPE_SNAP_TIMER = 0,
	SDK_ENCODE_TYPE_SNAP_TRIGGER = 1,
};
#define SDK_EXTRATYPES 3 //����������

//���紫�����
enum SDK_TransferPolicy
{
	SDK_TRANSFER_POLICY_AUTO,			///< ����Ӧ
	SDK_TRANSFER_POLICY_QUALITY,		///< ��������
	SDK_TRANSFER_POLICY_FLUENCY,		///< ��������
	SDK_TRANSFER_POLICY_TRANSMISSION,	///< ��������
	SDK_TRANSFER_POLICY_NR,
};

/// ���紫��Э������
enum SDK_NetTransProtocolType
{
	SDK_NET_TRANS_PRO_TCP = 0,
	SDK_NET_TRANS_PRO_UDP = 1,
};

typedef struct {
	int left;
	int top;
	int right;
	int bottom;
}sdkRect;

/// ��Ƶ�����ʽ������Խ���
typedef struct SDK_AudioInFormatConfig
{
	int iBitRate;	   ///< ������С��kbpsΪ��λ������192kbps��128kbps
	int iSampleRate;   ///< �����ʣ�HzΪ��λ������44100Hz
	int iSampleBit;    ///< ������λ��
	int iEncodeType;   ///< ���뷽ʽ������AudioEncodeTypes����
}SDK_AudioInFormatConfig;

//����Խ���ʽ
typedef enum __TALK_CODING_TYPE
{
	TALK_DEFAULT = 0,
	TALK_PCM = 1,		//PCM
	TALK_G711a,			//G711a
	TALK_AMR,			//AMR
	TALK_G711u,			//G711u
	TALK_G726,			//G726
}TALK_CODING_TYPE;
//����Խ�
typedef struct H264_DVR_TALKDECODE_INFO
{
	TALK_CODING_TYPE		encodeType;		//��������
	int						nAudioBit;		//��ʵ�ʵ�ֵ��ʾ����8λ ����ֵΪ8
	unsigned int			dwSampleRate;	//�����ʣ���16k ����ֵΪ16000
	char					reserved[64];
}H264_DVR_TALKDECODE_INFO;


/// ϵͳʱ��ṹ
typedef struct SDK_SYSTEM_TIME{
	int  year;		///< �ꡣ   
	int  month;		///< �£�January = 1, February = 2, and so on.   
	int  day;		///< �ա�   
	int  wday;		///< ���ڣ�Sunday = 0, Monday = 1, and so on   
	int  hour;		///< ʱ��   
	int  minute;	///< �֡�   
	int  second;	///< �롣   
	int  isdst;		///< ����ʱ��ʶ��   
}SDK_SYSTEM_TIME;

//¼��������ؽṹ��
typedef struct SDK_TIMESECTION
{
	//!ʹ��
	int enable;
	//!��ʼʱ��:Сʱ
	int startHour;
	//!��ʼʱ��:����
	int	startMinute;
	//!��ʼʱ��:����
	int	startSecond;
	//!����ʱ��:Сʱ
	int	endHour;
	//!����ʱ��:����
	int	endMinute;
	//!����ʱ��:����
	int	endSecond;
}SDK_TIMESECTION;

typedef struct{
	int dwYear;		//��
	int dwMonth;	//��
	int dwDay;		//��
	int dwHour;		//ʱ
	int dwMinute;	//��
    int dwSecond;	//��
}H264_DVR_TIME,*LPH264_DVR_TIME;

//ʱ��ṹ
typedef struct _NEW_NET_TIME
{
	unsigned int second		:6;		//	��	1-60		
	unsigned int minute		:6;		//	��	1-60		
	unsigned int hour		:5;		//	ʱ	1-24		
	unsigned int day		:5;		//	��	1-31		
	unsigned int month		:4;		//	��	1-12		
	unsigned int year		:6;		//	��	2000-2063	
}NEW_NET_TIME, *LPNET_TIME;
///< ����ʱ�ṹ
typedef struct DSTPoint
{
	int	iYear;
	int	iMonth;
	int	iWeek;		///<��1:first  to2 3 4 -1:last one   0:��ʾʹ�ð��ռ���ķ���[-1,4]
	int	iWeekDay;	///<weekday from sunday=0	[0, 6]
	int Hour;
	int Minute;
}DSTPoint;

typedef struct SDK_VIDEO_FORMAT
{
	int		iCompression;			//  ѹ��ģʽ(��Ƶ��ʽ) ����enum SDK_CAPTURE_COMP_t 	
	int		iResolution;			//  �ֱ��� ����ö��SDK_CAPTURE_SIZE_t
	int		iBitRateControl;		//  �������� ����ö��SDK_capture_brc_t
	int		iQuality;				//  �����Ļ��� ����1-6		
	int		nFPS;					//  ֡��ֵ��NTSC/PAL������,������ʾ����һ֡		
	int		nBitRate;				//  0-4096k,���б���Ҫ�ɿͻ��˱��棬�豸ֻ����ʵ�ʵ�����ֵ�������±ꡣ
	int		iGOP;					//  ��������I֮֡��ļ��ʱ�䣬2-12 
} SDK_VIDEO_FORMAT;

typedef struct  SDK_AUDIO_FORMAT
{
	int		nBitRate;				//  ����kbps	
	int		nFrequency;				//  ����Ƶ��	
	int		nMaxVolume;				//  ���������ֵ
}SDK_AUDIO_FORMAT;

// ý���ʽ
typedef struct SDK_MEDIA_FORMAT
{
	SDK_VIDEO_FORMAT vfFormat;		//  ��Ƶ��ʽ���� 			
	SDK_AUDIO_FORMAT afFormat;		//  ��Ƶ��ʽ���� 
	bool	bVideoEnable;			//  ������Ƶ���� 
	bool	bAudioEnable;			//  ������Ƶ���� 	
} SDK_MEDIA_FORMAT;

typedef union {	//IP addr
	unsigned char	c[4];
	unsigned short	s[2];
	unsigned int 	l;
}CONFIG_IPAddress;

///////////////////�û��ʺŹ�����ؽṹ��/////////////////////////////////
typedef struct _OPR_RIGHT
{
	char name[NET_MAX_USER_LENGTH];
}OPR_RIGHT;

typedef struct _USER_INFO
{
	int			rigthNum;
	char		rights[NET_MAX_RIGTH_NUM][NET_MAX_USER_LENGTH];
	char		Groupname[NET_MAX_USER_LENGTH];
	char		memo[NET_MAX_USER_LENGTH];
	char		name[NET_MAX_USER_LENGTH];
	char		passWord[NET_MAX_USER_LENGTH];
	bool		reserved;		//�Ƿ���
	bool		shareable;		//���û��Ƿ������� 1-���ã�0-������
}USER_INFO;

typedef struct _USER_GROUP_INFO
{
	int			rigthNum;
	char		memo[NET_MAX_USER_LENGTH]; 
	char		name[NET_MAX_USER_LENGTH];
	char		rights[NET_MAX_RIGTH_NUM][NET_MAX_USER_LENGTH];	//Ȩ���б�
}USER_GROUP_INFO;

//�û���Ϣ���ýṹ
typedef struct _USER_MANAGE_INFO
{
	int					rigthNum;
	OPR_RIGHT			rightList[NET_MAX_RIGTH_NUM];
	int					groupNum;
	USER_GROUP_INFO		groupList[NET_MAX_GROUP_NUM];
	int					userNum;
	USER_INFO			userList[NET_MAX_USER_NUM];
}USER_MANAGE_INFO;

//�޸��û�
typedef struct _CONF_MODIFYUSER
{
	char UserName[NET_MAX_USER_LENGTH];
	USER_INFO User;
}CONF_MODIFYUSER;

//�޸���
typedef struct _CONF_MODIFYGROUP
{
	char GroupName[NET_MAX_USER_LENGTH];
	USER_GROUP_INFO Group;
}CONF_MODIFYGROUP;


/// �޸��û���������
struct _CONF_MODIFY_PSW
{
	char sUserName[NET_MAX_USER_LENGTH];
	char Password[NET_MAX_USER_LENGTH];
    char NewPassword[NET_MAX_USER_LENGTH];
};

//��ͨ����ҳ�ṹ��
typedef struct _SDK_CONFIG_NORMAL
{
	SDK_SYSTEM_TIME sysTime;		//ϵͳʱ��

	int  iLocalNo;				///< �������:[0, 998] */
	int  iOverWrite;			///< Ӳ����ʱ���� "OverWrite��iOverWrite=1��", "StopRecord��iOverWrite=0��" */		
	char cIranCalendarEnable;	///< �Ƿ���������������1��ʾ���ã�0��ʾ������
	char cFontSize;				///< ʸ�������С
	char reserved[2];
	char sMachineName[64];		///< ������
	int  iVideoStartOutPut;		///< ���ģʽ */
	int  iAutoLogout;			///< ���ز˵��Զ�ע��(����)	[0, 120]

	int  iVideoFormat;			///< ��Ƶ��ʽ:��PAL��:0, ��NTSC��:1, ��SECAM�� */
	int  iLanguage;				///< ����ѡ��:��English��, ��SimpChinese��, ��TradChinese��, ��Italian��, ��Spanish��, ��Japanese��, ��Russian��, ��French��, ��German�� */	
	int  iDateFormat;			///< ���ڸ�ʽ:��YYMMDD��, ��MMDDYY��, ��DDMMYY�� */
	int  iDateSeparator;		///< ���ڷָ��:��.��, ��-��, ��/�� */
	int  iTimeFormat;			///< ʱ���ʽ:��12��, ��24�� */
	int  iDSTRule;				///< ����ʱ���� 
	int  iWorkDay;				///< ������
	DSTPoint dDSTStart;
	DSTPoint dDSTEnd;
}SDK_CONFIG_NORMAL;


//���±����������
// ��������
typedef struct SDK_CONFIG_ENCODE
{
	SDK_MEDIA_FORMAT dstMainFmt[SDK_ENCODE_TYPE_NUM];	//  ��������ʽ 	
	SDK_MEDIA_FORMAT dstExtraFmt[SDK_EXTRATYPES];		//  ��������ʽ 
	SDK_MEDIA_FORMAT dstSnapFmt[SDK_ENCODE_TYPE_NUM];	//  ץͼ��ʽ 
}SDK_CONFIG_ENCODE;

typedef struct  SDK_EncodeConfigAll
{
	SDK_CONFIG_ENCODE vEncodeConfigAll[NET_MAX_CHANNUM];
}SDK_EncodeConfigAll;


// �򻯰汾��������
/// ý���ʽ
typedef struct SDK_MEDIA_FORMAT_SIMPLIIFY
{
	SDK_VIDEO_FORMAT vfFormat;		//  ��Ƶ��ʽ���� 			
	bool	bVideoEnable;			//  ������Ƶ���� 
	bool	bAudioEnable;			//  ������Ƶ���� 	
}SDK_MEDIA_FORMAT_SIMPLIIFY;

/// ��������
typedef struct SDK_CONFIG_ENCODE_SIMPLIIFY
{
	SDK_MEDIA_FORMAT dstMainFmt;	//  ��������ʽ 	
	SDK_MEDIA_FORMAT dstExtraFmt;	//  ��������ʽ 
}SDK_CONFIG_ENCODE_SIMPLIIFY;

/// ȫͨ����������
typedef struct SDK_EncodeConfigAll_SIMPLIIFY
{
	SDK_CONFIG_ENCODE_SIMPLIIFY vEncodeConfigAll[NET_MAX_CHANNUM];
}SDK_EncodeConfigAll_SIMPLIIFY;


typedef struct  SDK_CombineEncodeConfigAll
{
	SDK_CONFIG_ENCODE vEncodeConfigAll[NET_MAX_COMBINE_NUM];
}SDK_CombineEncodeConfigAll;

/// ��ϱ���ģʽ
typedef struct SDK_CombEncodeParam
{
	int iEncodeMode;	 //��CombineEncodeMode
}SDK_CombEncodeParam;

typedef struct SDK_CombEncodeModeAll
{
	SDK_CombEncodeParam vEncodeParam[NET_MAX_COMBINE_NUM];
}SDK_CombEncodeModeAll;

//!��Ƶ����ṹ
typedef struct  SDK_VIDEO_WIDGET
{
	unsigned int rgbaFrontground;	///< �����ǰ��MakeRGB����͸����	
	unsigned int rgbaBackground;	///< ����ĺ�MakeRGB����͸����	
	sdkRect	rcRelativePos;			///< ����߾��������ı���*8191
	bool	bPreviewBlend;			///< Ԥ������,�Ƿ���ʾ��1����ʾ 0������
	bool	bEncodeBlend;			///< �������
}SDK_VIDEO_WIDGET;

//!��Ƶ�������
typedef struct SDK_CONFIG_VIDEOWIDGET
{
	SDK_VIDEO_WIDGET	dstCovers[NET_COVERNUM];
	SDK_VIDEO_WIDGET	ChannelTitle; //ͨ������
	SDK_VIDEO_WIDGET	TimeTitle;	  //�豸ʱ��
	struct 
	{
		char strName[NET_NAME_PASSWORD_LEN];
#ifdef WIN32
 		__int64 iSerialNo;	
#else
		long long iSerialNo;	
#endif
	}ChannelName;			///< ͨ������
	int		iCoverNum;		///< ��ǰ��ͨ���м������ӵ����� */
}SDK_CONFIG_VIDEOWIDGET;

/// ��Ƶ���(���ģʽ�Ի���)
typedef struct SDK_VideoWidgetConfigAll
{
	SDK_CONFIG_VIDEOWIDGET vVideoWidegetConfigAll[NET_MAX_CHANNUM];
}SDK_VideoWidgetConfigAll;

//��Ƶ��ɫ
typedef struct SDK_VIDEOCOLOR_PARAM
{
	int	nBrightness;		///< ����	0-100
	int	nContrast;			///< �Աȶ�	0-100
	int	nSaturation;		///< ���Ͷ�	0-100
	int	nHue;				///< ɫ��	0-100
	int	mGain;				///< ����	0-100 �ڣ�λ��1��ʾ�Զ�����		
	int	mWhitebalance;		///< �Զ��׵�ƽ���ƣ�bit7��λ��ʾ�����Զ�����.0x0,0x1,0x2�ֱ�����,��,�ߵȼ�
	int nAcutance;          ///< ���   0-15
}SDK_VIDEOCOLOR_PARAM;
///< ��Ƶ��ɫ����
typedef struct SDK_VIDEOCOLOR
{
	SDK_TIMESECTION			tsTimeSection;		/// ʱ���
	SDK_VIDEOCOLOR_PARAM	dstColor;			/// ��ɫ����
	int					iEnable;
}SDK_VIDEOCOLOR;

typedef struct SDK_CONFIG_VIDEOCOLOR
{
	SDK_VIDEOCOLOR dstVideoColor[NET_N_MIN_TSECT];
}SDK_CONFIG_VIDEOCOLOR;

typedef struct SDK_VideoColorConfigAll
{
	SDK_CONFIG_VIDEOCOLOR vVideoColorAll[NET_MAX_CHANNUM];
}SDK_VideoColorConfigAll;


/// ����ͨ�����Ʊ���
typedef struct SDK_ChannelNameConfigAll
{
	char channelTitle[NET_MAX_CHANNUM][NET_NAME_PASSWORD_LEN];
}SDK_ChannelNameConfigAll;

//���ģʽ
typedef struct SDK_GUISetConfig
{
	int iWindowAlpha;			///< ����͸����	[128, 255]
	bool bTimeTitleEn;			///< ʱ�������ʾʹ��
	bool bChannelTitleEn;		///< ͨ��������ʾʹ��	
	bool bAlarmStatus;			///< ����״̬
	bool bRecordStatus;			///< ¼��״̬��ʾʹ��
	bool bChanStateRecEn;		///< ¼���־��ʾʹ��
	bool bChanStateVlsEn;		///< ��Ƶ��ʧ��־��ʾʹ��
	bool bChanStateLckEn;		///< ͨ��������־��ʾʹ��	
	bool bChanStateMtdEn;		///< ��̬����־��ʾʹ��
	bool bBitRateEn;			///< ������ʾʹ��
	bool bRemoteEnable;			///< ң����ʹ��
	bool bDeflick;				///< ������
}SDK_GUISetConfig;


////!��ͨ��������
typedef struct SDK_CONFIG_NET_COMMON
{
	//!������
	char HostName[NET_NAME_PASSWORD_LEN];
	//!����IP
	CONFIG_IPAddress HostIP;
	//!��������
	CONFIG_IPAddress Submask;
	//!����IP
	CONFIG_IPAddress Gateway;
	//!HTTP����˿�
	int HttpPort;
	//!TCP�����˿�
	int TCPPort;	
	//!SSL�����˿�
	int SSLPort;
	//!UDP�����˿�
	int UDPPort;
	//!���������
	int MaxConn;
	//!����Э�� {"TCP","UDP","MCAST",��}
	int MonMode;
	//!�޶�����ֵ
	int MaxBps;
	//!�������
	//char TransferPlan[NET_NAME_PASSWORD_LEN];
	int TransferPlan;

	//!�Ƿ����ø���¼�����ز���
	bool bUseHSDownLoad;

	//!MAC��ַ
	char sMac[NET_MAX_MAC_LEN];
}SDK_CONFIG_NET_COMMON;

 typedef enum SDK_DevType
 {
 	SDK_DEV_TYPE_IPC,
 	SDK_DEV_TYPE_DVR,
	SDK_DEV_TYPE_HVR,
	SDK_DEV_TYPE_POEIPC,
	SDK_DEV_TYPE_NVR,
	SDK_DEV_TYPE_RTSPIPC,
 	SDK_DEV_TYPE_NR
 }SDK_DevType;


////!��ͨ�������� --
typedef struct SDK_CONFIG_NET_COMMON_V2
{
	//!������
	char HostName[NET_NAME_PASSWORD_LEN];
	//!����IP
	CONFIG_IPAddress HostIP;
	//!��������
	CONFIG_IPAddress Submask;
	//!����IP
	CONFIG_IPAddress Gateway;
	char pLocalLinkAddr[32];	//������·��ַ
	char pAddr[64];				//ipv6��ַ
	char pGateway[64];
	//!HTTP����˿�
	int HttpPort;
	//!TCP�����˿�
	int TCPPort;	
	//!SSL�����˿�
	int SSLPort;
	//!UDP�����˿�
	int UDPPort;
	//!���������
	int MaxConn;
	//!����Э�� {"TCP","UDP","MCAST",��}
	int MonMode;
	//!�޶�����ֵ
	int MaxBps;
	//!�������
	//char TransferPlan[NET_NAME_PASSWORD_LEN];
	int  TransferPlan;						///�������
	bool bUseHSDownLoad;					///�Ƿ����ø���¼�����ز���
	char sMac[NET_MAX_MAC_LEN];				///MAC��ַ
	char sSn[NET_MAX_MAC_LEN]; 				///���к�(�󻪺���ά�豸�������õ������������޸�IP��������)
#ifndef WIN32
	int  DeviceType;   						///�豸����,�ֻ������ǲ���������ͨ�豸
#endif

	int ChannelNum;			///ͨ����
	int	Device_Type;		///�豸���ͣ���enum SDK_DevType
#ifdef OME
	char Version[NET_MAX_INFO_LEN];         //�汾��Ϣ
	SDK_SYSTEM_TIME BuildDate;  			//�汾����
#endif
	char OtherFunction[49]; ///���������޸���������IP������Ϣ 
	char Resume[7];			///����

}SDK_CONFIG_NET_COMMON_V2;

////!����������IP�� --
typedef struct SDK_CONFIG_NET_COMMON_V3
{
    char HostName[NET_NAME_PASSWORD_LEN];	///������ 
    CONFIG_IPAddress HostIP;				///����IP
    CONFIG_IPAddress Submask;				///��������
    CONFIG_IPAddress Gateway;				///����IP  
    int  HttpPort;							///HTTP����˿�   
    int  TCPPort;							///TCP�����˿�   
    int  SSLPort;							///SSL�����˿�
    int  UDPPort;							///UDP�����˿�  
    int  MaxConn;							///���������
    int  MonMode;							///����Э�� {"TCP","UDP","MCAST",?}
    int  MaxBps;								///�޶�����ֵ
    //char TransferPlan[NET_NAME_PASSWORD_LEN];
    int  TransferPlan;						///�������
    bool bUseHSDownLoad; 					///�Ƿ����ø���¼�����ز���
    char sMac[NET_MAX_MAC_LEN];				///MAC��ַ
    char UserName[NET_NAME_PASSWORD_LEN];	///�豸�û���
    char Password[NET_NAME_PASSWORD_LEN];	///�豸����
    char LocalMac[NET_MAX_MAC_LEN];
    int  nPasswordType;
	char Resume[92];						///����
}SDK_CONFIG_NET_COMMON_V3;

//DHCP
#define SDK_MAX_ETH_NUM 4
typedef struct SDK_NetDHCPConfig
{
    bool bEnable;
    char ifName[32];
}SDK_NetDHCPConfig;
/// ����������DHCP����
typedef struct SDK_NetDHCPConfigAll
{
    SDK_NetDHCPConfig vNetDHCPConfig[SDK_MAX_ETH_NUM];
}SDK_NetDHCPConfigAll;

///< DNS����
typedef struct SDK_NetDNSConfig
{
    CONFIG_IPAddress		PrimaryDNS;
    CONFIG_IPAddress		SecondaryDNS;
}SDK_NetDNSConfig;
///< �������ṹ����
typedef struct SDK_RemoteServerConfig
{
    char ServerName[NET_NAME_PASSWORD_LEN];		///< ������
    CONFIG_IPAddress ip;						///< IP��ַ
    int Port;									///< �˿ں�
    char UserName[NET_NAME_PASSWORD_LEN];		///< �û���
    char Password[NET_NAME_PASSWORD_LEN];		///< ����
    bool Anonymity;								///< �Ƿ�������¼
}SDK_RemoteServerConfig;
///< IPȨ������
typedef struct SDK_NetIPFilterConfig
{
    bool Enable;											///< �Ƿ���
    CONFIG_IPAddress BannedList[NET_MAX_FILTERIP_NUM];		///< �������б�
    CONFIG_IPAddress TrustList[NET_MAX_FILTERIP_NUM];		///< �������б�
}SDK_NetIPFilterConfig;

///< �鲥����
typedef struct SDK_NetMultiCastConfig
{
    bool Enable;						///< �Ƿ���
    SDK_RemoteServerConfig Server;		///< �鲥������
}SDK_NetMultiCastConfig;

///< pppoe����
typedef struct SDK_NetPPPoEConfig
{
    bool Enable;						///< �Ƿ���
    SDK_RemoteServerConfig Server;		///< PPPOE������
    CONFIG_IPAddress addr;				///< ���ź��õ�IP��ַ
}SDK_NetPPPoEConfig;

///< DDNS����
typedef struct SDK_NetDDNSConfig
{
    bool Enable;							///< �Ƿ���
    bool Online;							///< �Ƿ�����
    char DDNSKey[NET_NAME_PASSWORD_LEN];	///< DDNS��������, Ŀǰ��: JUFENG
    char HostName[NET_NAME_PASSWORD_LEN];	///< ������
    SDK_RemoteServerConfig Server;			///< DDNS������
    
}SDK_NetDDNSConfig;

///< DDNS����
typedef struct SDK_NetDDNSConfigALL
{
    SDK_NetDDNSConfig ddnsConfig[NET_MAX_DDNS_TYPE];
}SDK_NetDDNSConfigALL;

///< FTP����
typedef struct SDK_FtpServerConfig{
    bool bEnable;        					///< ������ʹ��
    SDK_RemoteServerConfig Server;			///< FTP������
    char cRemoteDir[NET_MAX_PATH_LENGTH];	///< Զ��Ŀ¼
    int  iMaxFileLen;						///< �ļ���󳤶�
}SDK_FtpServerConfig;

///< NTP����
typedef struct SDK_NetNTPConfig
{
    ///< �Ƿ���
    bool Enable;
    ///< PPPOE������
    SDK_RemoteServerConfig Server;
    ///< ��������
    int  UpdatePeriod;
    ///< ʱ��
    int  TimeZone;
}SDK_NetNTPConfig;
#define  NET_MAX_EMAIL_TITLE_LEN 64
#define  NET_MAX_EMAIL_RECIEVERS  5
#define  NET_EMAIL_ADDR_LEN  64

///< EMAIL����
typedef struct SDK_NetEmailConfig
{
    ///< �Ƿ���
    bool Enable;
    ///< smtp ��������ַʹ���ַ�����ʽ���
    ///< ������ip,Ҳ����������
    SDK_RemoteServerConfig Server;
    bool bUseSSL;
    ///< ���͵�ַ
    char SendAddr[NET_EMAIL_ADDR_LEN];
    ///< �����˵�ַ
    char Recievers[NET_MAX_EMAIL_RECIEVERS][NET_EMAIL_ADDR_LEN];
    ///< �ʼ�����
    char Title[NET_MAX_EMAIL_TITLE_LEN];
    ///< email��Чʱ��
    SDK_TIMESECTION Schedule[NET_N_MIN_TSECT];
}SDK_NetEmailConfig;

///< ARSP(����ע�������)����
typedef struct SDK_NetARSPConfig
{
    bool bEnable;							///< �Ƿ���
    char sARSPKey[NET_NAME_PASSWORD_LEN];	///< DNS��������
    int  iInterval;							///< ������ʱ��
    char sURL[NET_NAME_PASSWORD_LEN];    	///< ��������
    SDK_RemoteServerConfig Server;			///< DDNS������
    int  nHttpPort;                  		///< ������HTTP�˿�
}SDK_NetARSPConfig;

typedef struct SDK_NetARSPConfigAll
{
    SDK_NetARSPConfig vNetARSPConfigAll[NET_MAX_ARSP_TYPE];
}SDK_NetARSPConfigAll;

///< ��������ַ����
typedef struct SDK_NetDecoderConfig
{
    bool Enable;							///< �Ƿ���
    char UserName[NET_NAME_PASSWORD_LEN];	///< DDNS��������, Ŀǰ��: JUFENG
    char PassWord[NET_NAME_PASSWORD_LEN];	///< ������
    char Address[NET_NAME_PASSWORD_LEN];
    int  Protocol;
    int  Port;								///< ���������Ӷ˿�
    int  Channel;							///< ����������ͨ����
    int  Interval;                       	///< ��Ѳ�ļ��ʱ��(s)
}SDK_NetDecoderConfig;

/// ����ͨ���Ľ�������ַ����
typedef struct SDK_NetDecoderConfigAll
{
    SDK_NetDecoderConfig vNetDecoderConfig[NET_MAX_DECORDR_CH];
}SDK_NetDecoderConfigAll;


/// ��������ַ����V2�汾
typedef struct SDK_NetDecoderConfig_V2
{
    int nTotalNum;            //��Ч��������������ΪNET_MAX_CHANNUM
    SDK_NetDecoderConfig vNetDecoderConfig[NET_MAX_CHANNUM];
}SDK_NetDecoderConfig_V2;

/// ����ͨ���Ľ�������ַ����V2�汾
typedef struct SDK_NetDecoderConfigAll_V2
{
    SDK_NetDecoderConfig_V2 vNetDecoderArray[NET_MAX_DECORDR_CH];
}SDK_NetDecoderConfigAll_V2;


/// ����ͨ������
enum SDK_CaptureChannelTypes 
{
	SDK_CAPTURE_CHN_MAIN = 0,		///< ��ͨ��	��	������1 
	SDK_CAPTURE_CHN_2END = 1,		///< ��ͨ��	��	��������2 
	SDK_CAPTURE_CHN_3IRD = 2,		///< ��ͨ��	��	��������3 
	SDK_CAPTURE_CHN_4RTH = 3,		///< ��ͨ��	��	��������4 
	SDK_CAPTURE_CHN_JPEG = 4,		///< ��ͨ��	��	��JPEGץͼ 
	SDK_CAPTURE_CHN_NR,
};

///< ��������ַ����
typedef struct SDK_NetDecorderConfigV3
{
    bool Enable;							///< �Ƿ���
    char UserName[NET_NAME_PASSWORD_LEN];	///< DDNS��������, Ŀǰ��: JUFENG
    char PassWord[NET_NAME_PASSWORD_LEN];	///< ������
    char Address[NET_NAME_URL_LEN];
    int  Protocol;							///��enum SDK_TransferProtocol_V2
    int  Port;								///< ���������Ӷ˿�
    int  Channel;							///< ����������ͨ����
    int  Interval;                       	///< ��Ѳ�ļ��ʱ��(s),0:��ʾ����
    char ConfName[NET_NAME_PASSWORD_LEN];	///<��������
    int  DevType;							///<�豸����
    int  StreamType;						///<���ӵ��������� ��enum SDK_CaptureChannelTypes
	char MainRtspUrl[NET_NAME_URL_LEN];		///<rtspЭ��ʱ��ʾǰ���豸����������ַ
	char SubRtspUrl[NET_NAME_URL_LEN];		///<rtspЭ��ʱ��ʾǰ���豸�ĸ�������ַ
}SDK_NetDecorderConfigV3;

/*��������������*/
enum SDK_DecorderConnType
{
    SDK_CONN_SINGLE = 0, 	/*������*/
    SDK_CONN_MULTI = 1,		/*��������Ѳ*/
    SDK_CONN_TYPE_NR,
};

/*����ͨ��������*/
typedef struct SDK_NetDigitChnConfig
{
    bool Enable;									/*����ͨ���Ƿ���*/
    int  ConnType;									/*�������ͣ�ȡDecoderConnectType��ֵ*/
    int  TourIntv;									/*������ʱ��Ѳ���*/
    unsigned int SingleConnId;						/*������ʱ����������ID, ��1��ʼ��0��ʾ��Ч*/
    bool EnCheckTime;								/*�����ʱ*/
    SDK_NetDecorderConfigV3 NetDecorderConf[32]; 	/*�����豸ͨ�����ñ�*/
    int  nNetDeorde; 								/* �ж��ٸ� */
	bool EnSynchResolution;							//ͬ���ֱ���ʹ�ܿ���,0��ʾ�򿪣�1��ʾ�ر�
}SDK_NetDigitChnConfig;

/*��������ͨ��������*/
typedef struct SDK_NetDecorderConfigAll_V3
{
    SDK_NetDigitChnConfig DigitChnConf[NET_MAX_DECORDR_CH];
}SDK_NetDecorderConfigAll_V3;

typedef struct SDK_HVR_CHNCAP
{
    int nD1Chn;					// ֧�ֵ�D1·��
    int n960HChn;				// ֧�ֵ�960H·��
    int n720PChn;				// ֧�ֵ�720P·��
    int n1080PChn;				// ֧�ֵ�1080P·��
    int nCIFChn;				//֧�ֵ�CIFͨ����
    int nHD1Chn;				//֧�ֵ�HD1ͨ����
    unsigned char nPlayChn; 	//֧�ֻط�·��
    unsigned char nDigiTalChn; 	//֧���������ͨ��·��
    unsigned char n960PChn; 	//֧�ֵ�960Pͨ����
    unsigned char n3MChn; 		//֧�ֵ�3Mͨ����
    unsigned char n5MChn; 		//֧�ֵ�5Mͨ����
    unsigned char nWUXGAChn; 	//֧�ֵ�WUXGAͨ����
    unsigned char n1080NChn;	//֧��1080Nͨ����
    unsigned char n4MChn;		//֧��4Mͨ����
    //unsigned char nResChar[2]; //����
}SDK_HVR_CHNCAP, *SDK_PHVR_CHNCAP;

typedef struct SDK_HVR_CHNCAPV2
{
    unsigned char nD1Chn;		// ֧�ֵ�D1·��
    unsigned char n960HChn;		// ֧�ֵ�960H·��
    unsigned char n720PChn;		// ֧�ֵ�720P·��
    unsigned char n1080PChn;	// ֧�ֵ�1080P·��
    unsigned char nCIFChn;		//֧�ֵ�CIFͨ����
    unsigned char nHD1Chn;		//֧�ֵ�HD1ͨ����
    unsigned char nPlayChn; 	//֧�ֻط�·��
    unsigned char nDigiTalChn; 	//֧���������ͨ��·��
    unsigned char n960PChn; 	//֧�ֵ�960Pͨ����
    unsigned char n3MChn; 		//֧�ֵ�3Mͨ����
    unsigned char n5MChn; 		//֧�ֵ�5Mͨ����
    unsigned char nWUXGAChn; 	//֧�ֵ�WUXGAͨ����
    unsigned char n1080NChn;	//֧��1080Nͨ����
    unsigned char n4MChn;		//֧��4Mͨ����
    unsigned char n720NChn;		//֧��720Nͨ����
	unsigned char nWSVGAChn;	//֧��WSVGA(1024*576)ͨ����
	unsigned char n4KChn;		//֧�ֵ�4Kͨ����
	unsigned char n3M_NChn;		//֧�ֵ�3M_Nͨ����
	unsigned char n4M_NChn;		//֧�ֵ�4M_Nͨ����
	unsigned char n5M_NChn;		//֧�ֵ�5M_Nͨ����
	unsigned char n4K_NChn;		//֧�ֵ�4K_Nͨ����
	unsigned char nRes[11];
}SDK_HVR_CHNCAPV2, *SDK_PHVR_CHNCAPV2;

typedef struct SDK_CAPTURE_HVRCAP  	//����CAPTURE_HVRCAPV2��Ϊ�˼����ϵı���
{
    SDK_HVR_CHNCAP DigitalCap;		// ֧�ֵ�����ͨ����Ϣ
    SDK_HVR_CHNCAP AnalogCap;		// ֧�ֵ�ģ��ͨ����Ϣ
}SDK_CAPTURE_HVRCAP, *SDK_PCAPTURE_HVRCAP;

typedef struct SDK_CAPTURE_HVRCAPV2
{
    SDK_HVR_CHNCAPV2 DigitalCap;	// ֧�ֵ�����ͨ����Ϣ
    SDK_HVR_CHNCAPV2 AnalogCap;		// ֧�ֵ�ģ��ͨ����Ϣ
}SDK_CAPTURE_HVRCAPV2, *SDK_PCAPTURE_HVRCAPV2;

typedef struct SDK_CAPTURE_TOTAL_HVRCAP //����CAPTURE_TOTAL_HVRCAPV2��Ϊ�˼����ϵı���
{
    int		nHVRCap;									// ʵ��֧�ֵ�ģʽ
    SDK_CAPTURE_HVRCAP	HVRCap[MAX_HVR_CHNCAP_CHN];		// ����ģʽ�Ļ���
}SDK_CAPTURE_TOTAL_HVRCAP, *SDK_PCAPTURE_TOTAL_HVRCAP;

typedef struct SDK_CAPTURE_TOTAL_HVRCAPV2
{
    int		nHVRCap;									// ʵ��֧�ֵ�ģʽ
    SDK_CAPTURE_HVRCAPV2	HVRCap[MAX_HVR_CHNCAP_CHN];	// ����ģʽ�Ļ���
}SDK_CAPTURE_TOTAL_HVRCAPV2, *SDK_PCAPTURE_TOTAL_HVRCAPV2;

//ͨ��ģʽ����
typedef struct SDK_NetDecorderChnModeConfig
{
    SDK_CAPTURE_TOTAL_HVRCAPV2 	HVRTotalCap;
    int HVRCurCapMode;
}SDK_NetDecorderChnModeConfig;


/*����ͨ��״̬*/
typedef struct SDK_NetDecorderChnStatus
{
    char ChnName[NET_NAME_PASSWORD_LEN];
    char pMaxResName[50];
    char pCurResName[50];
    char pStatus[50];
}SDK_NetDecorderChnStatus;

/*��������ͨ��״̬*/
typedef struct SDK_NetDecorderChnStatusAll
{
    SDK_NetDecorderChnStatus ChnStatusAll[NET_MAX_DECORDR_CH];
}SDK_NetDecorderChnStatusAll;

//Pos�豸����
enum SDK_PosDevType
{
    SDK_POS_TYPE_MANY_LINES, //�������ܽ���Ű���Ʒ��Ϣһ���͹���
    SDK_POS_TYPE_ONE_LINE,   //ÿͳ��һ����Ʒ�ͰѸ���Ʒ����Ϣ���͹���
    SDK_POS_NR
};

//���ֱ����ʽ
enum SDK_WordEncode
{
    SDK_WORD_ENCODE_GB2312,  //���ֱ���GB2312
    SDK_WORD_ENCODE_UNICODE, //����� Unicode
    SDK_WORD_ENCODE_UTF8,    //UTF-8
};

#define SDK_MAX_POS_FUNC_KEYWORDS 4
// pos�������
typedef struct SDK_NetPosConfig
{
    bool Enable;			/*pos��ͨ��ʹ��*/
    int  Devtype;			//pos������
    int  Protocol;			//ͨ��Э��
    int  Port;				//Э��˿ں�
    bool SnapEnable;		//ץ��ʹ��
    int  StartLine;			//���յ�����Ϣ�Ӷ����п�ʼ��ʾ
    int  WordEncodeType;	//���ֱ����ʽ����ö��ֵ WordEncodeType ��ʾ
    bool KeyWordEnable; 	//�ؼ���д��־����ʹ��
    char SearchWrod[SDK_MAX_POS_FUNC_KEYWORDS][16]; //��Ҫ��ӵ���־��ĵ���
    int  HideTime;         	//����ͨ����ʾ��pos��Ϣ��ʱ��,��λ���룬0��ʾ���Զ�����
    int  res;				//����
}SDK_NetPosConfig;
//����pos���������
typedef struct SDK_NetPosConfigAll
{
    SDK_NetPosConfig PosConfig[MAX_HVR_CHNCAP_CHN];
}SDK_NetPosConfigAll;


///< 3G��������
typedef struct SDK_Net3GConfig
{
    bool bEnable;			  				///< ����ģ��ʹ�ܱ�־
    int  iNetType;			  				///< ������������
    char sAPN[NET_NAME_PASSWORD_LEN];		///< ���������
    char sDialNum[NET_NAME_PASSWORD_LEN];   ///< ���ź���
    char sUserName[NET_NAME_PASSWORD_LEN];  ///< �����û���
    char sPassword[NET_NAME_PASSWORD_LEN];  ///< ��������
    CONFIG_IPAddress addr;			  		///< ���ź��õ�IP��ַ
	char sOperators[NET_NAME_PASSWORD_LEN]; ///< ��Ӫ��(�ϲ�ʹ��)
	char strSubNetMask[NET_NAME_PASSWORD_LEN];///< ������������
	char strGateWay[NET_NAME_PASSWORD_LEN];	  ///< ����Ĭ������
	bool bSIMState;							  ///< SIM����״̬
}SDK_Net3GConfig;

///< �ֻ�������ð���
typedef struct SDK_NetMoblieConfig
{
    bool bEnable;						///< �Ƿ���
    SDK_RemoteServerConfig Server;		///< ������
}SDK_NetMoblieConfig;

//RTSP
typedef struct SDK_NetRTSPConfig
{
    bool bServer;
    bool bClient;
    SDK_RemoteServerConfig Server;		///< ������ģʽ
    SDK_RemoteServerConfig Client;		///< �ͻ���ģʽ
}SDK_NetRTSPConfig;

///< UPNP����
typedef struct SDK_NetUPNPConfig
{
    bool bEnable;				///< ʹ�ܱ�־
    bool bState;				///< ״̬, 1: OK 0: NOK
    int  iHTTPPort;				///< HTTP����ӳ���Ķ˿�
    int  iMediaPort;			///< ý������ӳ���Ķ˿�
    int  iMobliePort;			///< �ֻ����ӳ���Ķ˿�
}SDK_NetUPNPConfig;

///< WIFI����
typedef struct SDK_NetWifiConfig
{
    bool bEnable;
    char sSSID[36];            	///< SSID Number
    int  nChannel;             	///< channel
    char sNetType[32];         	///< Infra, Adhoc
    char sEncrypType[32];      	///< NONE, WEP, TKIP, AES
    char sAuth[32];            	///< OPEN, SHARED, WEPAUTO, WPAPSK, WPA2PSK, WPANONE, WPA, WPA2
    int  nKeyType;             	///< 0:Hex 1:ASCII
    char sKeys[NET_IW_ENCODING_TOKEN_MAX];
    CONFIG_IPAddress HostIP;	///< host ip
    CONFIG_IPAddress Submask;	///< netmask
    CONFIG_IPAddress Gateway;	///< gateway
}SDK_NetWifiConfig;

enum SDK_RSSI_SINGNAL
{
    SDK_RSSI_NO_SIGNAL,    //<= -90db
    SDK_RSSI_VERY_LOW,     //<= -81db
    SDK_RSSI_LOW,          //<= -71db
    SDK_RSSI_GOOD,         //<= -67db
    SDK_RSSI_VERY_GOOD,    //<= -57db
    SDK_RSSI_EXCELLENT     //<= -57db
};

typedef struct SDK_NetWifiDevice
{
    char sSSID[36];            //SSID Number
    int  nRSSI;                //SEE SDK_RSSI_SINGNAL
    int  nChannel;
    char sNetType[32];         //Infra, Adhoc
    char sEncrypType[32];      //NONE, WEP, TKIP, AES
    char sAuth[32];            //OPEN, SHARED, WEPAUTO, WPAPSK, WPA2PSK, WPANONE, WPA, WPA2
}SDK_NetWifiDevice;

typedef struct SDK_NetWifiDeviceAll
{
    int nDevNumber;
    SDK_NetWifiDevice vNetWifiDeviceAll[NET_MAX_AP_NUMBER];
}SDK_NetWifiDeviceAll;

///< ������������
typedef struct SDK_NetAlarmCenterConfig
{
    bool bEnable;									///< �Ƿ���
    char sAlarmServerKey[NET_NAME_PASSWORD_LEN];	///< ��������Э����������,
    SDK_RemoteServerConfig Server;					///< �������ķ�����
    bool bAlarm;
    bool bLog;
}SDK_NetAlarmCenterConfig;

typedef struct SDK_NetAlarmServerConfigAll
{
    SDK_NetAlarmCenterConfig vAlarmServerConfigAll[NET_MAX_ALARMSERVER_TYPE];
}SDK_NetAlarmServerConfigAll;


//���Ż�ͨ
typedef struct SDK_CONFIG_NET_MEGA
{
    bool bEnable;
    bool bNetManEnable;
    CONFIG_IPAddress ServerIP;
    int  iServerPort;
    char sDeviceId[32];
    char sUserName[24];
    char sPasswd[32];
    int  iMaxCon;
    int  iVideoPort;
    int  iAudioPort;
    int  iMsgPort;
    int  iUpdatePort;
}SDK_CONFIG_NET_MEGA;

// ����ƽ̨
typedef struct SDK_CONFIG_NET_XINGWANG
{
    bool bEnable;
    bool bSyncTime;
    bool bSubStream;
    CONFIG_IPAddress ServerIP;
    int  iServerPort;
    int  iDownLoadPort;
    char sPasswd[32];
    char szSID[32];
}SDK_CONFIG_NET_XINGWANG;

// ����ƽ̨
typedef struct SDK_CONFIG_NET_SHISOU
{
    bool bEnable;
    SDK_RemoteServerConfig Server;
    char szSID[NET_MAX_USERNAME_LENGTH];
}SDK_CONFIG_NET_SHISOU;

// VVEYEƽ̨
typedef struct SDK_CONFIG_NET_VVEYE
{
    bool bEnable;
    bool bCorpEnable;            //ֻ����ʹ����ҵ������ʱ����Ҫ����Server
    SDK_RemoteServerConfig Server;
    char szDeviceName[NET_MAX_USERNAME_LENGTH];
}SDK_CONFIG_NET_VVEYE;

// ����������Ϣ����
enum SDK_AlarmCenterMsgType
{
    SDK_ALARMCENTER_ALARM,
    SDK_ALARMCENTER_LOG,
};

// ����������Ϣ����
enum SDK_AlarmCenterStatus
{
    SDK_AC_START,
    SDK_AC_STOP,
};

// �澯������Ϣ����
typedef struct SDK_NetAlarmCenterMsg
{
    CONFIG_IPAddress HostIP;			///< �豸IP
    int  nChannel;                  	///< ͨ��
    int  nType;                     	///< ���� ��AlarmCenterMsgType
    int  nStatus;                   	///< ״̬ ��AlarmCenterStatus
    SDK_SYSTEM_TIME Time;           	///< ����ʱ��
    char sEvent[NET_MAX_INFO_LEN];  	///< �¼�
    char sSerialID[NET_MAX_MAC_LEN]; 	///< �豸���к�
    char sDescrip[NET_MAX_INFO_LEN];  	///< ����
}SDK_NetAlarmCenterMsg;

/// ������Ϣ
typedef struct SDK_EncodeInfo
{
    bool bEnable;						///< ʹ����
    bool bHaveAudio;					///< �Ƿ�֧����Ƶ
    int  iStreamType;					///< �������ͣ�capture_channel_t
    unsigned int uiCompression;			///< capture_comp_t������
    unsigned int uiResolution;			///< SDK_CAPTURE_SIZE_t������
}SDK_EncodeInfo;

/// ��������
typedef struct CONFIG_EncodeAbility
{
    unsigned int iMaxEncodePower;							///< ֧�ֵ�����������
    int iChannelMaxSetSync;									///< ÿ��ͨ���ֱ����Ƿ���Ҫͬ�� 0-��ͬ��, 1 -ͬ��
    unsigned int nMaxPowerPerChannel[NET_MAX_CHANNUM];		///< ÿ��ͨ��֧�ֵ���߱�������
    unsigned int ImageSizePerChannel[NET_MAX_CHANNUM];		///< ÿ��ͨ��֧�ֵ�ͼ��ֱ���
    unsigned int ExImageSizePerChannel[NET_MAX_CHANNUM];	///< ÿ��ͨ��֧�ֵĸ�����ͼ��ֱ���
	unsigned int CompressionMask[NET_MAX_CHANNUM];			///< ����ģʽcapture_comp_t����
	unsigned int ThridImageSize[NET_MAX_CHANNUM];			///< CHL_3IRD_T����֧�ֵ�ͼ��ֱ���
	unsigned int FourthImageSize[NET_MAX_CHANNUM];			///< CHL_4RTH_T����֧�ֵ�ͼ��ֱ���
    SDK_EncodeInfo vEncodeInfo[SDK_CHL_FUNCTION_NUM];		///< ������Ϣ,��ʱ����4������
    SDK_EncodeInfo vCombEncInfo[SDK_CHL_FUNCTION_NUM];		///< ��ϱ�����Ϣ,��ʱ����4������
    int	iMaxBps;											///< �������Kbps
    unsigned int ExImageSizePerChannelEx[NET_MAX_CHANNUM][SDK_CAPTURE_SIZE_EXT_V3_NR];	///< ÿ��ͨ��֧�ֵĸ�����ͼ��ֱ���
}CONFIG_EncodeAbility;

// ����Э��
enum SDK_CommProtocol
{
    SDK_CONSOLE = 0,
    SDK_KEYBOARD,
    SDK_COM_TYPES,
};
/// ����Э��
typedef struct SDK_COMMFUNC
{
    //ÿ��Э�������64���ַ����
    int nProNum;
    char vCommProtocol[100][32];
}SDK_COMMFUNC;

/// ��̨Э��
typedef struct SDK_PTZPROTOCOLFUNC
{
    //ÿ��Э�������64���ַ����
    int nProNum;
    char vPTZProtocol[100][NET_MAX_PTZ_PROTOCOL_LENGTH];
}SDK_PTZPROTOCOLFUNC;

/// �����ڵ�������
typedef struct SDK_BlindDetectFunction
{
    int iBlindConverNum;	///< �����ڵ�����
}SDK_BlindDetectFunction;

/// ��������������
typedef struct SDK_MotionDetectFunction
{
    int iGridRow;
    int iGridColumn;
}SDK_MotionDetectFunction;

/// ֧�ֵ�DDNS����
typedef struct SDK_DDNSServiceFunction
{
    int  nTypeNum;
    char vDDNSType[NET_MAX_DDNS_TYPE][64];
}SDK_DDNSServiceFunction;

/// ֧������
typedef struct SDK_MultiLangFunction
{
    //ÿ��Э�������64���ַ����
    int nLangNum;
    char vLanguageName[128][64];
}SDK_MultiLangFunction;

/// ֧�ֵ���Ƶ��ʽ
typedef struct SDK_MultiVstd
{
    //ÿ��Э�������3���ַ����
    int nVstdNum;
    char vVstdName[3][64];
}SDK_MultiVstd;

/// ���빦��
enum SDK_EncodeFunctionTypes
{
    SDK_ENCODE_FUNCTION_TYPE_DOUBLE_STREAM,		///< ˫��������
    SDK_ENCODE_FUNCTION_TYPE_COMBINE_STREAM,	///< ��ϱ��빦��
    SDK_ENCODE_FUNCTION_TYPE_SNAP_STREAM,		///< ץͼ����
    SDK_ENCODE_FUNCTION_TYPE_WATER_MARK,		///< ˮӡ����
    SDK_ENCODE_FUNCTION_TYPE_IFRAME_RANGE,		///< I֡���
    SDK_ENCODE_FUNCTION_TYPE_LOW_BITRATE,   	///< ������
	SDK_ENCODE_FUNCTION_TYPE_SmartH264,			///< H264+
	SDK_ENCODE_FUNCTION_TYPE_INTELLIGENT_ENCODE,///< ���ܱ���
    SDK_ENCODE_FUNCTION_TYPE_NR,
};

/// ��������
enum SDK_AlarmFucntionTypes
{
    SDK_ALARM_FUNCTION_TYPE_MOTION_DETECT,		///< ��̬���
    SDK_ALARM_FUNCTION_TYPE_BLIND_DETECT,		///< �����ڵ�
    SDK_ALARM_FUNCTION_TYPE_LOSS_DETECT,		///< ������ʧ
    SDK_ALARM_FUNCTION_TYPE_LOCAL_ALARM,		///< ���ر���
    SDK_ALARM_FUNCTION_TYPE_NET_ALARM,			///< ���籨��
    SDK_ALARM_FUNCTION_TYPE_IP_CONFLICT,		///< IP��ַ��ͻ
    SDK_ALARM_FUNCTION_TYPE_NET_ABORT,			///< �����쳣
    SDK_ALARM_FUNCTION_TYPE_STORAGE_NOTEXIST,	///< �洢�豸������
    SDK_ALARM_FUNCTION_TYPE_STORAGE_LOWSPACE,	///< �洢�豸��������
    SDK_ALARM_FUNCTION_TYPE_STORAGE_FAILURE,	///< �洢�豸����ʧ��
    SDK_ALARM_FUNCTION_TYPE_VIDEOANALYSE,		///< ��Ƶ����
    SDK_ALARM_FUNCTION_TYPE_NET_ABORT_EXTEND,	///< �����쳣��չ
    SDK_ALARM_FUNCTION_TYPE_IPC_ALARM,			///< IPC����
	SDK_ALARM_FUNCTION_TYPE_CONSUMER_433ALARM,	///< ���ò�Ʒ433�豸����
	SDK_ALARM_FUNCTION_TYPE_CONSUMER_REMOTE, 	///< ���ò�Ʒ2.4G ң����
	SDK_ALARM_FUNCTION_TYPE_SERIAL_ALARM,		///< ���ڱ���
	SDK_ALARM_FUNCTION_TYPE_NEW_VIEDO_ANALYZE,	///< ��������
	SDK_ALARM_FUNCTION_TYPE_PIR_ALARM,			///< PIR����
	SDK_ALARM_FUNCTION_TYPE_BLUR_CHECK,			///< ģ����ⱨ��
	SDK_ALARM_FUNCTION_TYPE_433_ALARM,			///< �ͻ�����433����
    SDK_ALARM_FUNCTION_TYPE_NR
};

/// ���������
enum SDK_NetServerTypes
{
    SDK_NET_SERVER_TYPES_IPFILTER,			///< �׺�����
    SDK_NET_SERVER_TYPES_DHCP,				///< DHCP����
    SDK_NET_SERVER_TYPES_DDNS,				///< DDNS����
    SDK_NET_SERVER_TYPES_EMAIL,				///< Email����
    SDK_NET_SERVER_TYPES_MULTICAST,			///< �ಥ����
    SDK_NET_SERVER_TYPES_NTP,				///< NTP����
    SDK_NET_SERVER_TYPES_PPPOE,
    SDK_NET_SERVER_TYPES_DNS,
    SDK_NET_SERVER_TYPES_ARSP,				///< ����ע�����
    SDK_NET_SERVER_TYPES_3G,            	///< 3G����
    SDK_NET_SERVER_TYPES_MOBILE=10,     	///< �ֻ����
    SDK_NET_SERVER_TYPES_UPNP,				///< UPNP
    SDK_NET_SERVER_TYPES_FTP,				///< FTP
    SDK_NET_SERVER_TYPES_WIFI,          	///< WIFI
    SDK_NET_SERVER_TYPES_ALARM_CENTER,  	///< �澯����
    SDK_NET_SERVER_TYPES_NETPLAT_MEGA,  	///< ���Ż�ͨ
    SDK_NET_SERVER_TYPES_NETPLAT_XINWANG,  	///< ����
    SDK_NET_SERVER_TYPES_NETPLAT_SHISOU,  	///< ����
    SDK_NET_SERVER_TYPES_NETPLAT_VVEYE,  	///< ������
    SDK_NET_SERVER_TYPES_RTSP,     			///< RTSP
    SDK_NET_SERVER_TYPES_PHONEMSG=20,     	///< �ֻ���Ϣ��������
    SDK_NET_SERVER_TYPES_PHONEMULTIMEDIAMSG,///< �ֻ���Ϣ��������
    SDK_NET_SERVER_TYPES_DAS,          		///< ����ע��
    SDK_NET_SERVER_TYPES_LOCALSDK_PLATFORM, ///< ����ƽ̨��Ϣ����
    SDK_NET_SERVER_TYPES_GOD_EYE,			///< ���۽Ӿ�����ϵͳ
    SDK_NET_SERVER_TYPES_NAT,				///< NAT��͸��MTU����
    SDK_NET_SERVER_TYPES_VPN,     			///< VPN
    SDK_NET_SERVER_TYPES_NET_KEYBOARD,		///< �����������
    SDK_NET_SERVER_TYPES_SPVMN,				///< 28181Э������
    SDK_NET_SERVER_TYPES_PMS,      			///< �ֻ�����
    SDK_NET_SERVER_TYPE_KAICONG,			///< ��������
    SDK_NET_SERVER_TYPE_PROTOCOL_MAC,		///< ֧��MACЭ��
    SDK_NET_SERVER_TYPE_XMHEARTBEAT, 		///< ��������
    SDK_NET_SERVER_TYPES_MONITOR_PLATFORM, 	///< ����������ƽ̨
    SDK_NET_SERVER_TYPES_ANJUP2P,			///< 
    SDK_NET_SERVER_TYPES_TUTKIOTC,			///< TUTK IOTCƽ̨
    SDK_NET_SERVER_TYPES_BAIDUCLOUD, 		///< �ٶ���
    SDK_NET_SERVER_TYPES_MOBILWATCH,		///< �ֻ�����
	SDK_NET_SERVER_TYPES_BJLTHY,			///< �������ڷ��ʷ�����ƽ̨
    SDK_NET_SERVER_TYPES_OPENVPN,			///< openvpn����
    SDK_NET_SERVER_TYPES_PROTOCOL_NAT,		///< ֧��NATЭ��
    SDK_NET_SERVER_TYPES_PLATFORM_GBEYES,	///< ֧�ֻ������ݵ���
	SDK_NET_SERVER_TYPES_GBEYES,			///< �Ų�ȫ����ƽ̨
    SDK_NET_SERVER_TYPES_DATALINK,			///< DataLink�ͻ����������ִ�г���ʹ������
    SDK_NET_SERVER_TYPES_WIFI_MODE,			///< �Ƿ�֧��wifiģʽ�������
	SDK_NET_SERVER_TYPES_IPV6,				///< ֧��ipv6
	SDK_NET_SERVER_TYPES_PMS_V2,			///< �°�PMSҳ��
	SDK_NET_SERVER_TYPES_4G,				///< ���߲��ŵ�Э���������Ƿ���ʾ4G
	SDK_NET_SERVER_TYPES_SPVMN_SIP,			///< 28181������ʾSIP �忨��ַ
	SDK_NET_SERVER_TYPES_RTMP,				///< RTMPЭ��
	SDK_NET_SERVER_TYPES_IPADAPTIVE,		///< IP����Ӧ��������
	SDK_NET_SERVER_TYPES_ONVIF_PWD_CHECKOUT,///< ONVIF����У��
    SDK_NET_SERVER_TYPES_NR,
};

/// Ԥ������
enum SDK_PreviewTypes
{
    SDK_PREVIEW_TYPES_TOUR,		///< ��Ѳ
    SDK_PREVIEW_TYPES_TALK,		///< GUI��������
    SDK_PREVIEW_TYPES_NR
};

///��������
enum SDK_CommTypes
{
    SDK_COMM_TYPES_RS485,		///<485����
    SDK_COMM_TYPES_RS232,		///<232����
    SDK_COMM_TYPES_NR
};

//���뷨����
enum SDK_InPutMethod
{
    SDK_NO_SUPPORT_CHINESE,		//��֧����������
    SDK_NO_SUPPORT_NR
};

//�����б�ǩ��ʾ
enum SDK_TipShow
{
    SDK_NO_BEEP_TIP_SHOW,  		//������ʾ
    SDK_NO_FTP_TIP_SHOW,  		//FTP��ʾ
    SDK_NO_EMAIL_TIP_SHOW,  	//EMAIL��ʾ
	SDK_NO_DISK_MANAGER_SHOW, //����ʾӲ�̹���ҳ��ķ����������޸ĵȰ�ť
    SDK_NO_TIP_SHOW_NR
};
///���ع���
enum SDK_MobileCar
{
    SDK_MOBILEDVR_STATUS_EXCHANGE,			//����״̬
    SDK_MOBILEDVR_DELAY_SET,	  			//��ʱ����
    SDK_MOBILEDVR_CARPLATE_SET,
    SDK_MOBILEDVR_GPS_TIMING,	  			//GPSУʱ
    SDK_MOBILEDVR_DVR_BOOT_TYPE_SET,
    SDK_MOBILEDVR_NR
};

///��������
enum SDK_OtherFunction
{
    SDK_OTHER_DOWNLOADPAUSE,				//¼��������ͣ����
    SDK_OTHER_USB_SUPPORT_RECORD,			//USB֧��¼����
    SDK_OTHER_SD_SUPPORT_RECORD,			//SD֧��¼����
    SDK_OTHER_ONVIF_CLIENT_SUPPORT,			//�Ƿ�֧��ONVIF�ͻ���
    SDK_OTHER_NET_LOCALSEARCH_SUPPORT,		//�Ƿ�֧��Զ������
    SDK_OTHER_MAXPLAYBACK_SUPPORT, 			//�Ƿ�֧�����ط�ͨ������ʾ
    SDK_OTHER_NVR_SUPPORT, 					//�Ƿ���רҵNVR
    SDK_OTHER_C7_PLATFORM_SUPPORT,			//֧��C7ƽ̨
    SDK_OTHER_MAIL_TEST_SUPPORT,			//֧���ʼ�����
    SDK_OTHER_SHOW_OSD_INFO,            	//֧����ʾ3��OSD��Ϣ
    SDK_OTHER_HIDE_DIGITAL, 				//ͨ��ģʽ���ι���
    SDK_OTHER_ACUTANCE_HORIZONTAL,			//���
    SDK_OTHER_ACUTANCE_VERTIAL,
    SDK_OTHER_BROAD_TRENDS,					//��̬����
    SDK_OTHER_NO_TALK,						//�Խ�����
    SDK_OTHER_ALTER_DIGITAL_NAME,			//�޸�����ͨ������
    SDK_OTHER_SHOW_CONNECT_STATUS,      	//֧����ʾwifi 3G ����ע��ȵ�����״̬
    SDK_OTHER_SUPPORT_ECACT_SEEK,			//֧�ֻطž�׼��λ
    SDK_OTHER_UPLOAD_TITLEANDSTATE,			//ͨ�����������ͨ��״̬�ϴ�������
    SDK_OTHER_NO_HDD_RECORD,				//��Ӳ��¼��
    SDK_OTHER_MUSICFILE_PLAY,				//������Ƶ�ļ�
    SDK_OTHER_SUPPORT_SET_DIG_IP,			//����ǰ��ip����
    SDK_OTHER_VERSION_PRODUCT_TYPE,			//֧���ڰ汾��Ϣ����ʾ�豸�ͺ�
    SDK_OTHER_SUPPORT_CAMERA_IMG_STYLE,		//֧�������ͼ����
    SDK_OTHER_SUPPORT_TITLE_ABILITY,		//֧���޸�onvif����
    SDK_OTHER_SUPPORT_DIMEN_CODE,			//֧�ֶ�ά��
	SDK_OTHER_STORAGE_NAS_SUPPORT,			//�Ƿ�֧��NAS�洢����
    SDK_OTHER_SHOWFALSE_CHECKTIME,			//���ν�����ʱ��ͬ������
    SDK_OTHER_SUPPORT_TIME_ZONE, 			//ʱ������
    SDK_OTHER_SHOW_ALARM_LEVEL_REGION,		//��ʾ����ͨ���������ܵ�����Ⱥ���������
    SDK_OTHER_SUPPORT_POS,					//֧��POS
    SDK_OTHER_HDD_LOWSPACE_USE_MB,			//Ӳ�̿ռ䲻�㱨��������MB
    SDK_OTHER_SUPPORT_CUSTOMIZE_OEMINFO,	//����OEM�ͻ��汾��Ϣ
    SDK_OTHER_DIGITAL_ENCODE,				//����ͨ����������
    SDK_OTHER_RESUME_PTZ_STATE,				//�����ָ���̨״̬
    SDK_OTHER_SUPPORT_SNAP_CFG,				//֧��ץͼ����
    SDK_OTHER_ABNORMITY_SEND_EMAIL,			//�洢�豸���ڼ��洢�쳣���洢�ռ䲻�㷢�ʼ�
    SDK_OTHER_SUPPORT_DIGITAL_PRE,			//֧������ͨ��Ԥ¼
    SDK_OTHER_SUPPORT_WRITE_LOG, 			//����ҳ������Ƿ�д��־��ѡ��
    SDK_OTHER_SUPPORT_CHANGE_ONVIF_PORT,	//֧���޸�onvif�˿�
    SDK_OTHER_SUPPORT_COMM_DATA_UPLOAD,  	//֧�ִ��������ϴ���ָ��������
    SDK_OTHER_SUPPORT_TEXT_PASSWORD,		//��¼��������
    SDK_OTHER_SUPPORT_CLOUD_UPGRADE,		// ֧��������
    SDK_OTHER_SUPPORT_USER_PROGRAM,			//֧����ͻ�С����
    SDK_OTHER_SUPPORT_MODIFY_FRONT_CFG,		//֧���޸�ǰ������
    SDK_OTHER_SUPPORT_FTP_TEST,    			//�³���֧��FTP֧��FTP���ԣ��ϳ���֧�֡�
    SDK_OTHER_SUPPORT_PTZ_IDLE_STATE, 		//��̨����ʱִ�к��ֲ���������
	SDK_OTHER_SUPPORT_IMP_RCD,				//web���Ƿ��ṩ�ؼ�¼��������ѡ��	
	SDK_OTHER_SUPPORT_CAMERA_MOTOR_CTRL, 	//֧�ֻ�����������
	SDK_OTHER_SUPPORT_ENCODE_ADD_BEEP,		// ��Ƶ����ÿ��30�����beep��
	SDK_OTHER_SUPPORT_FISH_EYE,	        	//���۹���������
	SDK_OTHER_SUPPORT_SPVMN_NAS_SERVER,		//���ճ���ͻ���nas����������
	SDK_OTHER_SUPPORT_SMALL_CHN_TITLE_FONT, //IE�˴�12*18��ͨ���������
	SDK_OTHER_SUPPORT_CFG_CLOUD_UPGRADE, 	//֧���µ���������������
	SDK_OTHER_SUPPORT_STORAGE_FAIL_REBOOT,	//ȫ��Ӳ�̳�����Զ�����
	SDK_OTHER_SUPPORT_SPLIT_CONTROL,		//֧��CMS�ͻ��˻���ָ�
	SDK_OTHER_RTSP_CLIENT_SUPPORT,			//����ͨ���Ƿ�֧��ͨ��RTSP����ǰ���豸
	SDK_OTHER_LOW_LUX_MODE,					//΢��ģʽ
	SDK_OTHER_SUPPORT_Switch_Resolution,	//�޸�ǰ������ͨ���ֱ���
	SDK_OTHER_LOW_MOTION,					//�˶����������
	SDK_OTHER_SUPPORT_CORRIDOR_MODE,        //֧������ģʽ
	SDK_OTHER_WIFINVR_SUPPORT,				//�Ƿ���WIFINVR
	SDK_OTHER_SUPPORT_SNAP_SCHEDULE,		//�Ƿ�֧�ֶ�ʱץͼ
	SDK_OTHER_SUPPORT_PWD_SAFETY,			//�Ƿ�֧�������һ�
	SDK_OTHER_SUPPORT_PLATE_DETECT,			//�Ƿ�֧�ֳ������
	SDK_OTHER_SUPPORT_BREVIARY,				//�Ƿ�֧������ͼ
	SDK_OTHER_SUPPORT_INTELLIGENT_PLAYBACK, //�Ƿ�֧�����ܿ��
	SDK_OTHER_SUPPORT_FACE_DETECT,			//����ʶ����
	SDK_OTHER_SUPPORT_DEVICE_INFO,			//�Ƿ�֧�����豸��Ϣ
	SDK_OTHER_NR
};

///֧�ֵ�ϵͳ����
typedef struct SDK_SystemFunction
{
    bool vEncodeFunction[SDK_ENCODE_FUNCTION_TYPE_NR];	///< ���빦��SDK_EncodeFunctionTypes
    bool vAlarmFunction[SDK_ALARM_FUNCTION_TYPE_NR];	///< ��������AlarmFucntionTypes
    bool vNetServerFunction[SDK_NET_SERVER_TYPES_NR];	///< ���������NetServerTypes
    bool vPreviewFunction[SDK_PREVIEW_TYPES_NR];		///< Ԥ������PreviewTypes
    bool vCommFunction[SDK_COMM_TYPES_NR];				///< ��������SDK_CommTypes
    bool vInputMethodFunction[SDK_NO_SUPPORT_NR];  		///< ���뷨����SDK_InPutMethod>
    bool vTipShowFunction[SDK_NO_TIP_SHOW_NR];          ///< ������ǩ��ʾSDK_TipShow>
    bool vMobileCarFunction[SDK_MOBILEDVR_NR];			///< ���ع���
    bool vOtherFunction[SDK_OTHER_NR];					///< ��������OtherFunction
}SDK_SystemFunction;

typedef struct SDK_COMMATTRI
{
    int	iDataBits;	// ����λȡֵΪ5,6,7,8
    int	iStopBits;	// ֹͣλ
    int	iParity;	// У��λ
    int	iBaudRate;	// ʵ�ʲ�����
}SDK_COMMATTRI;

// ��������
typedef struct SDK_CONFIG_COMM_X
{
    char iProtocolName[32];		// ����Э��:��Console��
    int iPortNo;				// �˿ں�
    SDK_COMMATTRI aCommAttri;	// ��������
}SDK_CONFIG_COMM_X;

typedef struct SDK_CommConfigAll
{
    SDK_CONFIG_COMM_X vCommConfig[SDK_COM_TYPES];
}SDK_CommConfigAll;

// ��̨����
typedef struct SDK_STR_CONFIG_PTZ
{
    char sProtocolName[NET_MAX_PTZ_PROTOCOL_LENGTH];	// Э������
    int	ideviceNo;										// ��̨�豸��ַ���
    int	iNumberInMatrixs;								// �ھ����е�ͳһ���
    int iPortNo;										// ���ڶ˿ں�	[1, 4]
    SDK_COMMATTRI dstComm;								// ��������
}SDK_STR_CONFIG_PTZ;

//����ͨ����̨Э��
typedef struct SDK_STR_PTZCONFIG_ALL
{
    SDK_STR_CONFIG_PTZ ptzAll[NET_MAX_CHANNUM];
}SDK_STR_PTZCONFIG_ALL;

//RS485
typedef struct SDK_STR_RS485CONFIG_ALL
{
    SDK_STR_CONFIG_PTZ ptzAll[NET_MAX_CHANNUM];
}SDK_STR_RS485CONFIG_ALL;


typedef struct SDK_CONFIG_WORKSHEET
{
    SDK_TIMESECTION	tsSchedule[NET_N_WEEKS][NET_N_TSECT];	/*!< ʱ��� */
}SDK_CONFIG_WORKSHEET;

/// ¼��ģʽ����
enum SDK_RecordModeTypes
{
    SDK_RECORD_MODE_CLOSED,		///< �ر�¼��
    SDK_RECORD_MODE_MANUAL,		///< �ֶ�¼��
    SDK_RECORD_MODE_CONFIG,		///< ������¼��
    SDK_RECORD_MODE_NR,
};

///< ¼������
typedef struct SDK_RECORDCONFIG
{
    int iPreRecord;										///< Ԥ¼ʱ�䣬Ϊ��ʱ��ʾ�ر�
    bool bRedundancy;									///< ���࿪��
    //bool bSnapShot;									///< ���տ���
    int iPacketLength;									///< ¼�������ȣ����ӣ�[1, 255]
    int iRecordMode;									///< ¼��ģʽ��0 �رգ�1 ��ֹ 2 ����
    SDK_CONFIG_WORKSHEET wcWorkSheet;					///< ¼��ʱ���
    unsigned int typeMask[NET_N_WEEKS][NET_N_TSECT];	///< ¼����������
}SDK_RECORDCONFIG;

//¼�����ýṹ��
typedef struct SDK_RECORDCONFIG_ALL
{
    SDK_RECORDCONFIG vRecordConfigAll[NET_MAX_CHANNUM];
}SDK_RECORDCONFIG_ALL;

///< ͼƬ����
typedef struct SDK_SnapshotConfig
{
    int iPreSnap;										///< ԤץͼƬ��
    bool bRedundancy;									///< ���࿪��
    int iSnapMode;										///< ¼��ģʽ����RecordModeTypes
    SDK_CONFIG_WORKSHEET wcWorkSheet;					///< ¼��ʱ���
    unsigned int typeMask[NET_N_WEEKS][NET_N_TSECT];	///< ¼���������룬��enum RecordTypes
}SDK_SnapshotConfig;

typedef struct SDK_SnapshotConfigAll
{
    SDK_SnapshotConfig vSnapshotConfigAll[NET_MAX_CHANNUM];
}SDK_SnapshotConfigAll;


//������ؽṹ��
// ��̨��������
enum PtzLinkTypes
{
	PTZ_LINK_NONE,		// ����Ҫ���� 
	PTZ_LINK_PRESET,		// ת��Ԥ�õ� 
	PTZ_LINK_TOUR,		// Ѳ�� 
	PTZ_LINK_PATTERN		// �켣 
};

//  ��̨�����ṹ
typedef struct SDK_PtzLinkConfig
{
    int iType;		// ����������--��Ӧ�ṹ��PtzLinkTypes
    int iValue;		// ���������Ͷ�Ӧ��ֵ
}SDK_PtzLinkConfig;

#define CHANNELNAME_MAX_LEN 64  //ͨ��������󳤶�

//����Ҫ���ݶ�ͨ���豸��������Ҫ�޸Ľṹ������
typedef struct SDK_EventHandler
{
	char	dwRecord[NET_MAX_MSK_SIZE];				// ¼������ 
    int		iRecordLatch;							// ¼����ʱ��10?300 sec
	char	dwTour[NET_MAX_MSK_SIZE];				// ��Ѳ���� 	
	char	dwSnapShot[NET_MAX_MSK_SIZE];			// ץͼ���� 
	char	dwAlarmOut[NET_MAX_MSK_SIZE];			// �������ͨ������ 
	char	dwMatrix[NET_MAX_MSK_SIZE];				// �������� 
    int		iEventLatch;							// ������ʼ��ʱʱ�䣬sΪ��λ
    int		iAOLatch;								// ���������ʱ��10?300 sec
    SDK_PtzLinkConfig PtzLink[NET_MAX_CHANNUM];		// ��̨������
    SDK_CONFIG_WORKSHEET schedule;					// ¼��ʱ���
    
    bool	bRecordEn;				// ¼��ʹ��
    bool	bTourEn;				// ��Ѳʹ��
    bool	bSnapEn;				// ץͼʹ��
    bool	bAlarmOutEn;			// ����ʹ��
    bool	bPtzEn;
    
    // ��̨����ʹ��
    bool	bTip;					// ��Ļ��ʾʹ��
    bool	bMail;					// �����ʼ�
    bool	bMessage;				// ������Ϣ����������
    bool	bBeep;					// ����
    bool	bVoice;					// ������ʾ
    bool	bFTP;					// ��FTP����
    bool	bMatrixEn;				// ����ʹ��
    bool	bLog;					// ��־ʹ��
    bool	bMessagetoNet;			// ��Ϣ�ϴ�������ʹ��
    
    bool    bShowInfo;              // �Ƿ���GUI�Ϻͱ�������ʾ������Ϣ
    char    dwShowInfoMask[NET_MAX_MSK_SIZE];	// Ҫ������ʾ������Ϣ��ͨ������
    char    pAlarmInfo[CHANNELNAME_MAX_LEN];	//Ҫ��ʾ�ı�����Ϣ
    
    bool    bShortMsg;              //���Ͷ���
    bool    bMultimediaMsg;         //���Ͳ���
}SDK_EventHandler;

enum SDK_ANALYSE_MODE
{
    SDK_ANALYSE_TRIPWIRE = 0, //������
    SDK_ANALYSE_PERIMETER     //�ܽ���
};
/** �ܽ���ģʽ */
enum SDK_URP_PERIMETER_MODE_E
{
    SDK_URP_PMODE_INTRUSION = 0,	/**< ���� */
    SDK_URP_PMODE_ENTER,			/**< ���� */
    SDK_URP_PMODE_EXIT				/**< �뿪 */
};

/** ���߽���� */
#define SDK_MAX_BOUNDARY_POINT_NUM 8
#define SDK_MAX_POINT_NUM 4
#define SDK_NAME_BUF_SIZE 16

/** ����� */
typedef struct URP_SDK_POINT_S
{
    short X;					/**< x */
    short Y;					/**< y */
}URP_SDK_POINT_S;

/** �߽ṹ */
typedef struct SDK_URP_LINE_S
{
    URP_SDK_POINT_S stStartPt;			/**< �߶���� */
    URP_SDK_POINT_S stEndPt;			/**< �߶��յ� */
}SDK_URP_LINE_S;

typedef struct SDK_URP_POLYGON_REGION_S
{
    int iValid;
    int iPointNum;
    URP_SDK_POINT_S astPoint[SDK_MAX_BOUNDARY_POINT_NUM];
}SDK_URP_POLYGON_REGION_S;

/** URP�ܽ���߽�� */
typedef struct SDK_URP_PERIMETER_LIMIT_BOUNDARY_S
{
    int      iBoundaryPtNum;										/**< �߽����Ŀ */
    URP_SDK_POINT_S   astBoundaryPts[SDK_MAX_BOUNDARY_POINT_NUM];	/**< �߽�㼯�� */
}SDK_URP_PERIMETER_LIMIT_BOUNDARY_S;

/** URP�ܽ������Ʋ��� */
typedef struct SDK_URP_PERIMETER_LIMIT_PARA_S
{
    int iMinDist;						/**< ��С���ؾ��� */
    int iMinTime;						/**< ���ʱ�� */
    int	iDirectionLimit;				/**< �Ƿ����������� */
    int iForbiddenDirection;			/**< ��ֹ����Ƕ�(��λ: �Ƕ�) */
    SDK_URP_PERIMETER_LIMIT_BOUNDARY_S stBoundary;	/**< �ܽ�߽����� */
}SDK_URP_PERIMETER_LIMIT_PARA_S;

/** URP�ܽ��������� */
typedef struct SDK_URP_PERIMETER_RULE_PARA_S
{
    int iTypeLimit;					/**< Ŀ���������� */
    int iTypeHuman;					/**< Ŀ�������(�޶�����ʱʹ��) */
    int iTypeVehicle;				/**< Ŀ����𣺳� */
    int iMode;						/**< �ܽ�ģʽ */
    SDK_URP_PERIMETER_LIMIT_PARA_S stLimitPara;	/**< �ܽ����Ʋ��� */
}SDK_URP_PERIMETER_RULE_PARA_S;

// ----------------------------------------------------------------------
//  �������ݽṹ
/** URP������������� */
#define SDK_URP_MAX_TRIPWIRE_CNT 8

/** URP�����߽ṹ */
typedef struct SDK_URP_TRIPWIRE_S
{
    int     iValid;						/**< �Ƿ���Ч */
    int    iIsDoubleDirection;			/**< ��ʾ�ð����Ƿ�Ϊ˫�����(0: ��, 1: ��) */
    int     iForbiddenDirection;		/**< �����߽�ֹ����*/
    SDK_URP_LINE_S	stLine;				/**< ������λ�� */
}SDK_URP_TRIPWIRE_S;

/** URP���������Ʋ��� */
typedef struct SDK_URP_TRIPWIRE_LIMIT_PARA_S
{
    int iMinDist;						/**< ��С���ؾ��� */
    int iMinTime;						/**< ���ʱ�� */
}SDK_URP_TRIPWIRE_LIMIT_PARA_S;

/** URP�����߹������ */
typedef struct SDK_URP_TRIPWIRE_RULE_PARA_S
{
    int iTypeLimit;						/**< Ŀ���������� */
    int iTypeHuman;						/**< Ŀ�������(�޶�����ʱʹ��) */
    int iTypeVehicle;					/**< Ŀ����𣺳� */
    SDK_URP_TRIPWIRE_S astLines[SDK_URP_MAX_TRIPWIRE_CNT];	/**< ������ */
    SDK_URP_TRIPWIRE_LIMIT_PARA_S stLimitPara;				/**< ���������Ʋ��� */
}SDK_URP_TRIPWIRE_RULE_PARA_S;


/** URPĿ���������ȼ��� */
enum SDK_SENSITIVITY_LEVEL_E
{
    SDK_HIGH_LEVEL_SENSITIVITY,         /**< ������� */
    SDK_MIDDLE_LEVEL_SENSITIVITY,		/**< ������� */
    SDK_LOW_LEVEL_SENSITIVITY			/**< ������� */
};

/** �㷨ģ�� */

enum SDK_MODULE_TYPE
{
    SDK_MODULE_TYPE_PEA = 0,
    SDK_MODULE_TYPE_OSC,
    SDK_MODULE_TYPE_AVD,
    SDK_MODULE_TYPE_ALL
};

// ----------------------------------------------------------------------
// ���濪ʼ���Զ���ṹ

typedef struct SDK_PEA_RULE_S
{
    int iShowTrack;						/// �Ƿ���ʾ�켣
    int iShowRule;						/// �Ƿ���ʾ����
    int iLevel;							/// ���伶������ȣ�0���߼���Ĭ��ֵ����1���м���2���ͼ���
    int iPerimeterEnable;				/// �ܽ����ʹ��
    SDK_URP_PERIMETER_RULE_PARA_S	stPerimeterRulePara;/**< �ܽ��� */
    int iTripWireEnable;				/// �����߹���ʹ��
    SDK_URP_TRIPWIRE_RULE_PARA_S	stTripwireRulePara;	/**< �����߼�� */
}SDK_PEA_RULE_S;

/// �㷨�����ṹ
typedef struct SDK_CAPS					/// ��1��ʾ��ͨ��֧�ֶ�Ӧ�������㷨����0��ʾ��֧�֡�
{
    int dwPEA;
    int dwAVD;
    int dwVFD;
    int dwAAI;
    int dwOSC;
    int iResv[3];
}SDK_CAPS;

typedef struct SDK_PEA_STATUS_S
{
    int dwPerimeter;					/// ���ּ��״̬�������˰��ߺ��ܽ�,��uintֵ�Ǹ�����������ͨ������״̬�����롣
    /// ��ͨ���ڵ�λ����ͨ���ڸ�λ��������1���ޱ�����0�������ڵ�ͨ����0��
    int iResv[4];
    int avdStatue;
}SDK_PEA_STATUS_S;


//��Ʒ����-begin
#define NET_MAX_OSC_NUM 4
#define NET_MAX_POINT_NUM 4
#define NET_NAME_BUF_SIZE 16

typedef struct SDK_URP_OSC_SPECL_REGIONS_S
{
    int nValid; 						//�Ƿ���Ч
    char chName[NET_NAME_BUF_SIZE]; 	//��������
    SDK_URP_POLYGON_REGION_S stOscRg; 	//Ҫ���������
    SDK_URP_POLYGON_REGION_S astSubRgA; //��������е���Ч������
    SDK_URP_POLYGON_REGION_S astSubRgB; //��������е���Ч������
    SDK_URP_POLYGON_REGION_S astSubRgC; //��������е���Ч������
}SDK_URP_OSC_SPECL_REGIONS_S;

typedef struct SDK_URP_OSC_LMT_PARA_S
{
    int nTimeMin; //ʱ��Լ��
    int nSizeMin; //��С�ߴ�
    int nSizeMax; //���ߴ�
}SDK_URP_OSC_LMT_PARA_S;

typedef struct SDK_URP_OSC_RULE_PARA_S
{
    int nSceneType; 					//��������
    int nCameraType; 					//�������
    SDK_URP_OSC_SPECL_REGIONS_S astSpclRgs[NET_MAX_OSC_NUM]; //Ҫ������������
    SDK_URP_OSC_LMT_PARA_S stOscPara; 	//һЩԼ��
}SDK_URP_OSC_RULE_PARA_S;

typedef struct SDK_OSC_RULE_S
{
    int iShowTrack;									/// �Ƿ���ʾ�켣
    int iShowRule;									/// �Ƿ���ʾ����
    int iLevel;										/// ���伶��0���Ǿ�����Ĭ��ֵ����1���ͼ���2���м���3: �߼�
    int iAbandumEnable;		   						/// ��Ʒ����ʹ��
    SDK_URP_OSC_RULE_PARA_S stObjAbandumRulePara; 	/// ��Ʒ�������
    int iStolenEnable;								/// ��Ʒ����ʹ��
    SDK_URP_OSC_RULE_PARA_S stObjStolenRulePara;   	/// ��Ʒ��������
    int iNoParkingEnable;							/// �Ƿ�ͣ��ʹ��
    SDK_URP_OSC_RULE_PARA_S stNoParkingRulePara;   	/// �Ƿ�ͣ������
}SDK_OSC_RULE_S;


typedef struct SDK_AVD_RULE_S
{
    int iLevel;						    /// ����ȵ�λ��1-5������ֵԽ��Խ����Խ�ױ���
    int itBrightAbnmlEnable;			///< �����쳣ʹ��
    int iClarityEnable;					///< �����ȼ��ʹ��
    int iNoiseEnable;					///< �������ʹ��
    int iColorEnable;					///< ƫɫ���ʹ��
    int iFreezeEnable;					///< ���涳����ʹ��
    int iNosignalEnable;				///< �ź�ȱʧ���ʹ��
    int iChangeEnable;					///< �����任���ʹ��
    int iInterfereEnable;				///< ��Ϊ���ż��ʹ��
    int iPtzLoseCtlEnable;				///< PTZʧ�ؼ��ʹ��
}SDK_AVD_RULE_S;

/** ����� */
typedef struct SDK_URP_IMP_POINT_S
{
    short s16X;				/**< x */
    short s16Y;				/**< y */
}SDK_URP_IMP_POINT_S;

typedef struct SDK_CPC_RULE_S
{
    SDK_URP_IMP_POINT_S stRulePoint[4];	///��������Ҫ����4����
    int s32Sizemin;			///��С���(0,height/2)
    int s32Sizemax;			///������(sizemin, height/2)
    int s32Countmax;		///���Ŀ����[1~15],
    int s32Sensitivity;		/// ����ȵ�λ��1-5������ֵԽ��Խ����Խ�ױ���
    unsigned int u32Flag;	///��־λ�������жϽ�����Ĭ����0
    int s32EnterDirection;	///����ķ���
}SDK_CPC_RULE_S;

//�����㷨�Ĺ������ü���
typedef struct SDK_RULECONFIG
{
    SDK_PEA_RULE_S stRulePea;   //�ܽ������������
    SDK_OSC_RULE_S stRuleOSC; 	//��Ʒ���ơ�����Ƿ�ͣ������
    SDK_AVD_RULE_S stRuleAVD;	//�쳣��Ƶ�ź��������
    SDK_CPC_RULE_S stRuleCPC; 	//��ͷ�����㷨����
}SDK_RULECONFIG;


//һ��ͨ�������ܷ�������
typedef struct SDK_ANALYSECONFIG
{
    bool         bEnable;      		//�Ƿ�������Ƶ��������
    int          moduleType;   		//ʹ�õ������㷨ģ��
    SDK_EventHandler hEvent;  		//�����¼�
    SDK_RULECONFIG   stRuleConfig; 	//�����㷨�Ĺ�������
}SDK_ANALYSECONFIG;

//����ͨ�������ܷ�������
typedef struct SDK_ANALYSECONFIG_ALL
{
    SDK_ANALYSECONFIG vAnalyzeAll[NET_MAX_CHANNUM];
}SDK_ANALYSECONFIG_ALL;

//PEA֧�ֵ��㷨����
enum SDK_PEA_TYPE{
	PEA_TYPE_TRIPWIRE   = 0,	//����
	PEA_TYPE_PERIMETER,			//�ܽ籣��
	PEA_TYPE_ALL
};

//OSC֧�ֵ��㷨����
enum SDK_OSC_TYPE{
	OSC_TYPE_ABANDUM = 0,		//��������
	OSC_TYPE_OBJSTOLEN,			//��������
	OSC_TYPE_NOPARKING,			//�Ƿ�ͣ�����
	OSC_TYPE_ALL
};

//AVD֧�ֵ��㷨����
enum SDK_AVD_TYPE{
	AVD_TYPE_BRIGHTABNML = 0,	//�����쳣
	AVD_TYPE_CLARITY,			//�����ȼ��
	AVD_TYPE_NOISE,				//�������
	AVD_TYPE_COLOR,				//ƫɫ���
	AVD_TYPE_FREEZE,			//���涳����AVD_TYPE_NOSIGNAL,	//�ź�ȱʧ���
	AVD_TYPE_CHANGE,			//�����任���
	AVD_TYPE_INTERFERE,			//��Ϊ���ż��
	AVD_TYPE_PTZLOSECTL,		//PTZʧ�ؼ��
	AVD_TYPE_ALL
};

//�����ܷ������ӵ�����
typedef struct SDK_PEALimit
{
	int  rectangle;     //�����Ƿ�����Ǿ��Σ�1:������       0:���Բ���
	char areaMaxLineNum;//һ����������ж�������
	char lineNum;       //֧�ֵľ���������
	char areaNum;       //֧�ֵľ����������
	char rev;
}SDK_PEALimit;

typedef struct SDK_OSCLimit
{
	int  rectangle;     //�����Ƿ�����Ǿ��Σ�1:������       0:���Բ���
	char areaMaxLineNum;//һ����������ж�������
	char areaNum;       //֧�ּ���������
	char Resv[2];
}SDK_OSCLimit;

//���ܷ������� //������������ҪSDK_ALARM_FUNCTION_TYPE_NEW_VIEDO_ANALYZE������ΪTRUE
typedef struct SDK_ANALYZEABILITY
{
	char uIntelPEA[NET_MAX_MSK_SIZE];	//����PEA֧�֣�λ��Ӧͨ�� 1���ֽڴ���һ��ͨ��
    UINT uAlgorithmPEA;					//PEA֧�ֵ��㷨����--��SDK_PEA_TYPEö��
	char uIntelOSC[NET_MAX_MSK_SIZE]; 	//����OSC֧�֣�λ��Ӧͨ�� 1���ֽڴ���һ��ͨ��
    UINT uAlgorithmOSC;					//OSC֧�ֵ��㷨����--��SDK_OSC_TYPEö��
	char uIntelAVD[NET_MAX_MSK_SIZE]; 	//����AVD֧�֣�λ��Ӧͨ�� 1���ֽڴ���һ��ͨ��
    UINT uAlgorithmAVD;					//AVD֧�ֵ��㷨����--��SDK_AVD_TYPEö��
	char uIntelCPC[NET_MAX_MSK_SIZE]; 	//����������֧�֣�λ��Ӧͨ�� 1���ֽڴ���һ��ͨ��
    UINT uAlgorithmCPC;							//CPC֧�ֵ��㷨����
	SDK_PEALimit uPEALimit;				//�����ܿ��PEA��������
	SDK_OSCLimit uOSCLimit;				//�����ܿ���OSC��������
}SDK_ANALYZEABILITY;

///< ��̬�������
typedef struct SDK_MOTIONCONFIG
{
    bool bEnable;								// ��̬��⿪��
    int iLevel;									// �����
    unsigned int mRegion[NET_MD_REGION_ROW];	// ����ÿһ��ʹ��һ�������ƴ�
    SDK_EventHandler hEvent;					// ��̬�������
}SDK_MOTIONCONFIG;

/// ȫͨ����̬�������
typedef struct SDK_MOTIONCONFIG_ALL
{
    SDK_MOTIONCONFIG vMotionDetectAll[NET_MAX_CHANNUM];
}SDK_MOTIONCONFIG_ALL;

///< �ڵ��������
typedef struct SDK_BLINDDETECTCONFIG
{
    bool	bEnable;			///< �ڵ���⿪��
    int		iLevel;				///< ����ȣ�1?6
    SDK_EventHandler hEvent;	///< �ڵ��������
}SDK_BLINDDETECTCONFIG;

/// ȫͨ���ڵ��������
typedef struct SDK_BLINDDETECTCONFIG_ALL
{
    SDK_BLINDDETECTCONFIG vBlindDetectAll[NET_MAX_CHANNUM];
}SDK_BLINDDETECTCONFIG_ALL;

///< �����¼��ṹ
typedef struct SDK_VIDEOLOSSCONFIG
{
    bool bEnable;				///< ʹ��
    SDK_EventHandler hEvent;	///< �������
}SDK_VIDEOLOSSCONFIG;

/// ����ͨ���Ļ���ʱ��ṹ
typedef struct SDK_VIDEOLOSSCONFIG_ALL
{
    SDK_VIDEOLOSSCONFIG vGenericEventConfig[NET_MAX_CHANNUM];
}SDK_VIDEOLOSSCONFIG_ALL;

///< ������������
typedef struct SDK_ALARM_INPUTCONFIG
{
    bool	bEnable;			///< �������뿪��
    int		iSensorType;		///< ���������ͳ��� or ����
    SDK_EventHandler hEvent;	///< ��������
}SDK_ALARM_INPUTCONFIG;

///< ����ͨ���ı�����������
typedef struct SDK_ALARM_INPUTCONFIG_ALL
{
    SDK_ALARM_INPUTCONFIG vAlarmConfigAll[NET_MAX_CHANNUM];
}SDK_ALARM_INPUTCONFIG_ALL;

///< ��·����
typedef struct SDK_NETALARMCONFIG
{
    bool bEnable;				///< ʹ��
    SDK_EventHandler hEvent;	///< �������
}SDK_NETALARMCONFIG;

/// ����ͨ������·�����ṹ
typedef struct SDK_NETALARMCONFIG_ALL
{
    SDK_NETALARMCONFIG vNetAlarmConfig[NET_MAX_CHANNUM];
}SDK_NETALARMCONFIG_ALL;

///< ���ر����������
typedef struct SDK_AlarmOutConfig
{
    int nAlarmOutType;		///< �����������: ����,�ֶ�,�ر�
    int nAlarmOutStatus;    ///< ����״̬: 0:�� 1;�պ�
}SDK_AlarmOutConfig;

//< Ӳ�����������¼�ʣ����������
enum SDK_StorageLowSpaceType
{
    SDK_PERSENT = 0,
    SDK_MB,
    SDK_GB,
};

///< Ӳ�����������¼��ṹ
typedef struct SDK_StorageLowSpaceConfig
{
    bool bEnable;
    int iLowerLimit;			///< Ӳ��ʣ����������, �ٷ���
    SDK_EventHandler hEvent;	///< �������
    bool bRecordTimeEnable;
    int iRecordTime;			///<¼������
    int iLowerLimitSpace;		///< Ӳ��ʣ������MB����GBΪ��λ
    int EnableType;				///< 0Ϊ�ðٷֱȣ�1Ϊ��MB����ö��StorageLowSpaceType
}SDK_StorageLowSpaceConfig;

///< ����ͨ���ı����������
typedef struct SDK_AlarmOutConfigAll
{
    SDK_AlarmOutConfig vAlarmOutConfigAll[NET_MAX_CHANNUM];
}SDK_AlarmOutConfigAll;

/// ����ͨ���Ľ�������ַ����V2�汾
typedef struct SDK_AbilitySerialNo
{
    char serialNo[NET_MAX_SERIALNO_LENGTH];
    char productType[NET_MAX_SERIALNO_LENGTH];
}SDK_AbilitySerialNo;

///< ��������Ϣ�ṹ
typedef struct SDK_DriverInformation
{
    int		iDriverType;				///< ����������
    bool	bIsCurrent;					///< �Ƿ�Ϊ��ǰ������
    unsigned int	uiTotalSpace;		///< ��������MBΪ��λ
    unsigned int	uiRemainSpace;		///< ʣ��������MBΪ��λ
    int		iStatus;					///< �����־���ļ�ϵͳ��ʼ��ʱ������
    int		iLogicSerialNo;				///< �߼����
    SDK_SYSTEM_TIME  tmStartTimeNew;	///< ��¼��ʱ��εĿ�ʼʱ��
    SDK_SYSTEM_TIME	 tmEndTimeNew;		///< ��¼��ʱ��εĽ���ʱ��
    SDK_SYSTEM_TIME	 tmStartTimeOld;	///< ��¼��ʱ��εĿ�ʼʱ��
    SDK_SYSTEM_TIME	 tmEndTimeOld;		///< ��¼��ʱ��εĽ���ʱ��
	char		fsType[NET_FSLEN];		///<�ļ�����
}SDK_DriverInformation;
enum
{
    SDK_MAX_DRIVER_PER_DISK = 4,		///< ÿ���������ķ�����
    SDK_MAX_DISK_PER_MACHINE = 8,		///< ���֧��8��Ӳ��
};
//Ӳ�̹���
typedef struct SDK_STORAGEDISK
{
    int		iPhysicalNo;
    int		iPartNumber;		// ������
    SDK_DriverInformation diPartitions[SDK_MAX_DRIVER_PER_DISK];
}SDK_STORAGEDISK;

typedef struct SDK_StorageDeviceInformationAll
{
    int iDiskNumber;
    SDK_STORAGEDISK vStorageDeviceInfoAll[SDK_MAX_DISK_PER_MACHINE];
}SDK_StorageDeviceInformationAll;

/// �洢�豸��������
enum SDK_StorageDeviceControlTypes
{
    SDK_STORAGE_DEVICE_CONTROL_SETTYPE,		///< ��������
    SDK_STORAGE_DEVICE_CONTROL_RECOVER,		///< �ָ�����
    SDK_STORAGE_DEVICE_CONTROL_PARTITIONS,	///< ��������
    SDK_STORAGE_DEVICE_CONTROL_CLEAR,		///< �������
   
	SDK_STORAGE_DEVICE_CONTROL_ADDNAS,		///<���NAS
	SDK_STORAGE_DEVICE_CONTROL_CHANGENAS,	///�޸�NAS
	SDK_STORAGE_DEVICE_CONTROL_DELNAS,		///<ɾ��NAS
 	SDK_STORAGE_DEVICE_CONTROL_NR,
};

/// ���������������
enum SDK_StorageDeviceClearTypes
{
    SDK_STORAGE_DEVICE_CLEAR_DATA,			///< ���¼������
    SDK_STORAGE_DEVICE_CLEAR_PARTITIONS,	///< �������
    SDK_STORAGE_DEVICE_CLEAR_NR,
};

/// ����������
enum SDK_FileSystemDriverTypes
{
	SDK_DRIVER_READ_WRITE	= 0,	///< ��д������
	SDK_DRIVER_READ_ONLY	= 1,	///< ֻ��������
	SDK_DRIVER_EVENTS		= 2,	///< �¼�������
	SDK_DRIVER_REDUNDANT	= 3,	///< ����������
	SDK_DRIVER_SNAPSHOT		= 4,	///< ����������
	SDK_DRIVER_TYPE_NR		= 5,	///< ���������͸���
	SDK_DRIVER_UNUSED		= 0xff,	///< û��ʹ�õ��������ṹ
};

/// �洢�豸����
typedef struct SDK_StorageDeviceControl
{
    int iAction;	///< ��enum SDK_StorageDeviceControlTypes
    int iSerialNo;	///< �������к�
    int iPartNo;    ///< ������
    int iType;		///< enum SDK_StorageDeviceClearTypes����SDK_FileSystemDriverTypes
    int iPartSize[4/*MAX_DRIVER_PER_DISK*/];	///< ���������Ĵ�С
}SDK_StorageDeviceControl;

/// �豸����
typedef enum SDK_DeviceType
{
    SDK_DEVICE_TYPE_DVR,	///< ��ͨDVR�豸
    SDK_DEVICE_TYPE_NVS,	///< NVS�豸
    SDK_DEVICE_TYPE_IPC,	///< IPC�豸
    SDK_DEVICE_TYPE_HVR,	///<���dvr
    SDK_DEVICE_TYPE_IVR,	///<����dvr
    SDK_DEVICE_TYPE_MVR,	///<����dvr
    SDK_DEVICE_TYPE_NR
}SDK_DeviceType;

/// �豸��Ϣ
typedef struct _H264_DVR_DEVICEINFO
{
    char sSoftWareVersion[64];	///< ����汾��Ϣ
    char sHardWareVersion[64];	///< Ӳ���汾��Ϣ
    char sEncryptVersion[64];	///< ���ܰ汾��Ϣ
    SDK_SYSTEM_TIME tmBuildTime;///< �������ʱ��
    char sSerialNumber[64];		///< �豸���к�
    int byChanNum;				///< ��Ƶ����ͨ����
    int iVideoOutChannel;		///< ��Ƶ���ͨ����
    int byAlarmInPortNum;		///< ��������ͨ����
    int byAlarmOutPortNum;		///< �������ͨ����
    int iTalkInChannel;			///< �Խ�����ͨ����
    int iTalkOutChannel;		///< �Խ����ͨ����
    int iExtraChannel;			///< ��չͨ����
    int iAudioInChannel;		///< ��Ƶ����ͨ����
    int iCombineSwitch;			///< ��ϱ���ͨ���ָ�ģʽ�Ƿ�֧���л�
    int iDigChannel;			///<����ͨ����
    unsigned int uiDeviceRunTime;///<ϵͳ����ʱ��
    SDK_DeviceType deviceTye;	///�豸����
    char sHardWare[64];			///<�豸�ͺ�
    char uUpdataTime[20];		///<�������� ���� 2013-09-03 14:15:13
    unsigned int uUpdataType;	///<��������
	int nLanguage;//���ҵ�����ID,0Ӣ�� 1���� 2���ķ��� 3���� 4���� 5�������� 6����
    char sCloudErrCode[NET_MAX_PATH_LENGTH];//�Ƶ�½�����������
	int status[32];
	//�ж��¹����������ǲ���ͨ������ת���ģ��������ô���շ�����3
	//���ص��������������ơ�
	//status[0] ·������:0�������ƣ� n��������n·
	//status[1]�������ơ�0 :�����ơ�1���Ʋ��ܹۿ���������
	//status[2]����ʱ�䡣0:�����ơ�n:����n���ӡ�
	//status[3]�������ʣ�Ŀǰ��Ϊ�ĵ���0:�����ơ�1:����ΪCIF 6֡ 100K ����������
	//status[4]����λ���������䡣
	//����status[0]��status[1]�ڴ˴����֡�
	//status[2]��status[3]�ڴ��������Ĺ���������
}H264_DVR_DEVICEINFO,*LPH264_DVR_DEVICEINFO;

//��������ص�����
typedef struct H264_DVR_ACTIVEREG_INFO
{
    char deviceSarialID[64];		//�豸���кţ��������64λ��ֵ0
    H264_DVR_DEVICEINFO deviceInfo;	//�豸��Ϣ
    char IP[IP_SIZE];   			//����IP
}H264_DVR_ACTIVEREG_INFO;
///< �Զ�ά������
typedef struct SDK_AutoMaintainConfig
{
    int iAutoRebootDay;				///< �Զ�������������
    int iAutoRebootHour;			///< ��������ʱ��	[0, 23]
    int iAutoDeleteFilesDays;		///< �Զ�ɾ���ļ�ʱ��[0, 30]
}SDK_AutoMaintainConfig;

/// Ĭ����������
enum SDK_DefaultConfigKinds
{
    SDK_DEFAULT_CFG_GENERAL,		// ��ͨ����
    SDK_DEFAULT_CFG_ENCODE,			// ��������
    SDK_DEFAULT_CFG_RECORD,			// ¼������
    SDK_DEFAULT_CFG_NET_SERVICE,	// �������
    SDK_DEFAULT_CFG_NET_COMMON,		// ͨ������
    SDK_DEFAULT_CFG_ALARM,			// ����
    SDK_DEFAULT_CFG_PTZCOMM,		// ��̨������
    SDK_DEFAULT_CFG_USERMANAGER,	// �û�����
    SDK_DEFAULT_CFG_PREVIEW,		// Ԥ������
    SDK_DEFAULT_CFG_CAMERA_PARAM,   // ��������ͷ����
    SDK_DEFAULT_CFG_END,
};

/// �ָ���Ĭ����������
typedef struct SDK_SetDefaultConfigTypes
{
    bool vSetDefaultKinds[SDK_DEFAULT_CFG_END];
	bool vDefaultFactory;			//�ָ�������������
}SDK_SetDefaultConfigTypes;


typedef struct H264_DVR_CLIENTINFO{
    int nChannel;	//ͨ����
    int nStream;	//0��ʾ��������Ϊ1��ʾ������
    int nMode;		//0��TCP��ʽ,1��UDP��ʽ,2���ಥ��ʽ,3 - RTP��ʽ��4-����Ƶ�ֿ�(TCP)
    int nComType;	//ֻ����ϱ���ͨ����Ч, ��ϱ���ͨ����ƴͼģʽ
    void* hWnd;
    
#ifndef OS_IOS
    H264_DVR_CLIENTINFO()
    {
        hWnd=0;
    }
#endif
    
}*LPH264_DVR_CLIENTINFO;


enum SDK_File_Type
{
    SDK_RECORD_ALL = 0,
    SDK_RECORD_ALARM = 1, //�ⲿ����¼��
    SDK_RECORD_DETECT,	  //��Ƶ���¼��
    SDK_RECORD_REGULAR,	  //��ͨ¼��
    SDK_RECORD_MANUAL,	  //�ֶ�¼��
    SDK_RECORD_KEY,		  //�ؼ�¼��
    SDK_PIC_ALL = 10,
    SDK_PIC_ALARM,		  //�ⲿ����ͼƬ
    SDK_PIC_DETECT,		  //��Ƶ���ͼƬ
    SDK_PIC_REGULAR,      //��ͨͼƬ
    SDK_PIC_MANUAL,       //�ֶ�ͼƬ
    SDK_PIC_IDXIMG,		  //����ͼƬ
    SDK_TYPE_NUM
};

//��ѯ¼������
typedef struct H264_DVR_FINDINFO
{
    int nChannelN0;			//ͨ����
    int nFileType;			//�ļ�����, ��SDK_File_Type
    H264_DVR_TIME startTime;//��ʼʱ��
    H264_DVR_TIME endTime;	//����ʱ��
    char szFileName[32];	//�ļ�����Ϊ�յĻ���ϵͳ������ֵ��ϵͳ����
    void *hWnd;				
    int  StreamType;		//��ѯ����������,������:0,������:1
#ifndef OS_IOS
    H264_DVR_FINDINFO()
    {
        hWnd=0;
        StreamType =0;
    }
#endif
}H264_DVR_FINDINFO;

//¼���ļ����ؽṹ��
typedef struct H264_DVR_FILE_DATA
{
    int ch;						//ͨ����
    int size;					//�ļ���С
    char sFileName[108];		//�ļ���
    SDK_SYSTEM_TIME stBeginTime;//�ļ���ʼʱ��
    SDK_SYSTEM_TIME stEndTime;	//�ļ�����ʱ��
    void *hWnd;					//���ھ��
    int StreamType;				//���������ǻط���������0�����Ǹ���������1��
#ifndef OS_IOS
    H264_DVR_FILE_DATA()
    {
        hWnd=0;
        StreamType =0;
    };
#endif
}H264_DVR_FILE_DATA;

//�طŶ���
enum SDK_PlayBackAction
{
    SDK_PLAY_BACK_PAUSE,		/*<! ��ͣ�ط� */
    SDK_PLAY_BACK_CONTINUE,		/*<! �����ط� */
    SDK_PLAY_BACK_SEEK,			/*<! �طŶ�λ��ʱ��sΪ��λ */
    SDK_PLAY_BACK_FAST,	        /*<! ���ٻط� */
    SDK_PLAY_BACK_SLOW,	        /*<! ���ٻط� */
    SDK_PLAY_BACK_SEEK_PERCENT, /*<! �طŶ�λ�ٷֱ� */
	SDK_PLAY_SET_TYPE,			/*<! �ط����ܶ�λ*/
};

//��ʱ��β�ѯ
typedef struct SDK_SearchByTime
{
    int nHighChannel;			///< 33~64¼��ͨ��������
    int nLowChannel;			///< 1~32¼��ͨ��������
    int nFileType;              ///< �ļ�����, ��SDK_File_Type
    SDK_SYSTEM_TIME stBeginTime;///< ��ѯ��ʼʱ��
    SDK_SYSTEM_TIME stEndTime;	///< ��ѯ����ʱ��
    int    iSync;               ///< �Ƿ���Ҫͬ��
    unsigned int	nHighStreamType;///< 33~64¼�����������,������λΪ0������������1��������
    unsigned int nLowStreamType;///< 1~32¼�����������,������λΪ0������������1��������
}SDK_SearchByTime;

//ÿ��ͨ����¼����Ϣ
typedef struct SDK_SearchByTimeInfo
{
    int iChannel;			    ///< ¼��ͨ����
    ///< ¼���¼��720���ֽڵ�5760λ����ʾһ���е�1440����
    ///< 0000:��¼�� 0001:F_COMMON 0002:F_ALERT 0003:F_DYNAMIC 0004:F_CARD 0005:F_HAND
    unsigned char cRecordBitMap[720];
}SDK_SearchByTimeInfo;

typedef struct SDK_SearchByTimeResult
{
    int nInfoNum;										 ///< ͨ����¼���¼��Ϣ����
    SDK_SearchByTimeInfo ByTimeInfo[NET_MAX_CHANNUM];    ///< ͨ����¼���¼��Ϣ
}SDK_SearchByTimeResult;

//������Ϣ
typedef struct SDK_ALARM_INFO
{
    int nChannel;
    int iEvent; //�����¼���:��ö��SDK_EventCodeTypes
    int iStatus;//0:������ʼ��1:��������
    SDK_SYSTEM_TIME SysTime;
	char pExtInfo[128]; //������Ϣ�������ߺͽ����߶Ը��ֱ������ͽ��и�ʽԼ��
}SDK_AlarmInfo;

/// ��־��ѯ����
typedef struct SDK_LogSearchCondition
{
    int nType;						///< ��־����
    int iLogPosition;				///< ���ϴβ�ѯ�Ľ���ʱ����־ָ��
    SDK_SYSTEM_TIME stBeginTime;	///< ��ѯ��־��ʼʱ��
    SDK_SYSTEM_TIME stEndTime;		///< ��ѯ��־����ʱ��
}SDK_LogSearchCondition;


typedef struct SDK_LogItem
{
    char sType[24];				///< ��־����
    char sUser[32];				///< ��־�û�
    char sData[68];				///< ��־����
    SDK_SYSTEM_TIME stLogTime;	///< ��־ʱ��
    int  iLogPosition;			///< ���ϴβ�ѯ�Ľ���ʱ����־ָ��
}SDK_LogItem;

//��־������Ϣ
typedef struct SDK_LogList
{
    int iNumLog;
    SDK_LogItem Logs[NET_MAX_RETURNED_LOGLIST];
}SDK_LogList;

/// ����Խ���ʽ
typedef struct SDK_AudioInFormatConfigAll
{
    SDK_AudioInFormatConfig vAudioInFormatConfig[SDK_AUDIO_ENCODE_TYPES_NR];
}SDK_AudioInFormatConfigAll;

/// �澯״̬
typedef struct SDK_DVR_ALARMSTATE
{
	char iVideoMotion[NET_MAX_MSK_SIZE];	///< �ƶ����״̬,�������ʾͨ����,byte0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
	char iVideoBlind[NET_MAX_MSK_SIZE];		///< ��Ƶ�ڵ�״̬,�������ʾͨ����,byte0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
	char iVideoLoss[NET_MAX_MSK_SIZE];		///< ��Ƶ��ʧ״̬,�������ʾͨ����,byte0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
	char iAlarmIn[NET_MAX_MSK_SIZE];		///< �澯����״̬,�������ʾͨ����,byte0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
	char iAlarmOut[NET_MAX_MSK_SIZE];		///< �澯���״̬,�������ʾͨ����,byte0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
}SDK_DVR_ALARMSTATE;

// ͨ��״̬
typedef struct SDK_DVR_CHANNELSTATE
{
    bool bRecord; ///< �Ƿ�����¼��
    int iBitrate;	///< ��ǰ����
}SDK_DVR_CHANNELSTATE;

// DVR����״̬
typedef struct SDK_DVR_WORKSTATE
{
    SDK_DVR_CHANNELSTATE vChnState[NET_MAX_CHANNUM];
    SDK_DVR_ALARMSTATE vAlarmState;
}SDK_DVR_WORKSTATE;


/// ����ֵ, ����������
enum SDK_NetKeyBoardValue
{
    SDK_NET_KEY_0, SDK_NET_KEY_1, SDK_NET_KEY_2, SDK_NET_KEY_3, SDK_NET_KEY_4, SDK_NET_KEY_5, SDK_NET_KEY_6, SDK_NET_KEY_7, SDK_NET_KEY_8, SDK_NET_KEY_9,
    SDK_NET_KEY_10, SDK_NET_KEY_11, SDK_NET_KEY_12, SDK_NET_KEY_13, SDK_NET_KEY_14, SDK_NET_KEY_15, SDK_NET_KEY_16, SDK_NET_KEY_10PLUS,SDK_NET_KEY_DIGIT,
    SDK_NET_KEY_UP = 20,     // �ϻ�����̨����
    SDK_NET_KEY_DOWN,        // �»�����̨����
    SDK_NET_KEY_LEFT,        // �������̨����
    SDK_NET_KEY_RIGHT,       // �һ�����̨����
    SDK_NET_KEY_SHIFT,
    SDK_NET_KEY_PGUP,        // ��һҳ
    SDK_NET_KEY_PGDN,        // ��һҳ
    SDK_NET_KEY_RET,         // ȷ��
    SDK_NET_KEY_ESC,         // ȡ�����˳�
    SDK_NET_KEY_FUNC,        // �л����뷨
    SDK_NET_KEY_PLAY,        // ����/��ͣ
    SDK_NET_KEY_BACK,        // ����
    SDK_NET_KEY_STOP,        // ֹͣ
    SDK_NET_KEY_FAST,        // ���
    SDK_NET_KEY_SLOW,        // ����
    SDK_NET_KEY_NEXT,        // ��һ���ļ�
    SDK_NET_KEY_PREV,        // ��һ���ļ�
	SDK_NET_KEY_PAUSE,		 // ��ͣ
	SDK_NET_KEY_FUNC_A,		 // ���ܼ�A
	SDK_NET_KEY_FUNC_B,	     // ���ܼ�B(���������Ʒ�ϣ�A��B�Ĺ��ܻ�����豸�Ĳ�ͬ���в�ͬ�ı���)
    SDK_NET_KEY_REC = 40,    // ¼������
    SDK_NET_KEY_SEARCH,      // ¼���ѯ
    SDK_NET_KEY_INFO,        // ϵͳ��Ϣ
    SDK_NET_KEY_ALARM,       // �澯���
    SDK_NET_KEY_ADDR,        // ң������ַ����
    SDK_NET_KEY_BACKUP,      // ����
    SDK_NET_KEY_SPLIT,       // ����ָ�ģʽ�л���ÿ��һ���л�����һ�����ģʽ
    SDK_NET_KEY_SPLIT1,      // ������
    SDK_NET_KEY_SPLIT4,      // �Ļ���
    SDK_NET_KEY_SPLIT8,      // �˻���
    SDK_NET_KEY_SPLIT9,      // �Ż���
    SDK_NET_KEY_SPLIT16,     // 16����
    SDK_NET_KEY_SHUT,        // �ػ�
    SDK_NET_KEY_MENU,        // �˵�
    SDK_NET_KEY_SPLIT25,	 // 25����
    SDK_NET_KEY_SPLIT36,     // 36����
    SDK_NET_KEY_PTZ = 60,    // ������̨����ģʽ
    SDK_NET_KEY_TELE,        // �䱶��
    SDK_NET_KEY_WIDE,        // �䱶��
    SDK_NET_KEY_IRIS_SMALL,  // ��Ȧ��
    SDK_NET_KEY_IRIS_LARGE,  // ��Ȧ��
    SDK_NET_KEY_FOCUS_NEAR,  // �۽�Զ
    SDK_NET_KEY_FOCUS_FAR,   // �۽���
    SDK_NET_KEY_BRUSH,       // ��ˢ
    SDK_NET_KEY_LIGHT,       // �ƹ�
    SDK_NET_KEY_SPRESET,     // ����Ԥ�õ�
    SDK_NET_KEY_GPRESET,     // ת��Ԥ�õ�
    SDK_NET_KEY_DPRESET,     // ���Ԥ�õ�
    SDK_NET_KEY_PATTERN,     // ģʽ
    SDK_NET_KEY_AUTOSCAN,    // �Զ�ɨ�迪ʼ����
    SDK_NET_KEY_AUTOTOUR,    // �Զ�Ѳ��
    SDK_NET_KEY_AUTOPAN,     // ��ɨ��ʼ/����
};

/// ����״̬
enum SDK_NetKeyBoardState
{
    SDK_NET_KEYBOARD_KEYDOWN,	// ��������
    SDK_NET_KEYBOARD_KEYUP,		// �����ɿ�
};

typedef struct SDK_NetKeyBoardData
{
    int iValue; //ö��SDK_NetKeyBoardValue
    int iState; //ö��SDK_NetKeyBoardState
}SDK_NetKeyBoardData;

// ������Ϣ��ȡ
typedef struct SDK_UpgradeInfo
{
    char szSerial[64];
    char szHardware[64];
    char szVendor[64];
    unsigned int uiLogoArea[2];
	char szLogoPartType[64];
}SDK_UpgradeInfo;

/// ���籨��
typedef struct SDK_NetAlarmInfo
{
    int iEvent;   //Ŀǰδʹ��
    int iState;   //ÿbit��ʾһ��ͨ��,bit0:��һͨ��,0-�ޱ��� 1-�б���, ��������
}SDK_NetAlarmInfo;

typedef enum SERIAL_TYPE
{
    RS232 = 0,
    RS485 = 1,
}SERIAL_TYPE;


enum MEDIA_PACK_TYPE
{
    FILE_HEAD =	0,	    		// �ļ�ͷ
    VIDEO_I_FRAME = 1,			// ��ƵI֡
    VIDEO_B_FRAME =	2,			// ��ƵB֡
    VIDEO_P_FRAME = 3,			// ��ƵP֡
    VIDEO_BP_FRAME = 4,			// ��ƵBP֡
    VIDEO_BBP_FRAME	= 5,		// ��ƵB֡B֡P֡
    VIDEO_J_FRAME = 6,			// ͼƬ֡
    AUDIO_PACKET = 10,			// ��Ƶ��
};

typedef struct
{
    int		       nPacketType;			// ������,��MEDIA_PACK_TYPE
    char*	       pPacketBuffer;		// ��������ַ
    unsigned int   dwPacketSize;		// ���Ĵ�С
    
    // ����ʱ��
    int		       nYear;				// ʱ��:��
    int		       nMonth;				// ʱ��:��
    int		       nDay;				// ʱ��:��
    int		       nHour;				// ʱ��:ʱ
    int		       nMinute;				// ʱ��:��
    int		       nSecond;				// ʱ��:��
    unsigned int   dwTimeStamp;			// ���ʱ���λ����λΪ����
    unsigned int   dwTimeStampHigh;    	//���ʱ���λ����λΪ����
    unsigned int   dwFrameNum;          //֡���
    unsigned int   dwFrameRate;         //֡��
    unsigned short uWidth;              //ͼ����
    unsigned short uHeight;             //ͼ��߶�
    unsigned int   Reserved[6];     	//����
} PACKET_INFO_EX;


typedef struct SDK_OEMInfo
{
    int nOEMID;                     	//OEM ID
    char sCompanyName[NET_MAX_USERNAME_LENGTH]; //��˾��
    char sTel[NET_MAX_USERNAME_LENGTH];         //�绰
    char sAddr[NET_MAX_USERNAME_LENGTH];        //��ַ
}SDK_OEMInfo;
typedef struct __TransComChannel//͸������
{
    SERIAL_TYPE TransComType;	//SERIAL_TYPE
    unsigned int baudrate;
    unsigned int databits;
    unsigned int stopbits;
    unsigned int parity;
} TransComChannel;
typedef enum SDK_State_Type
{
    DEV_STATE_DDNS=0,
}SDK_State_Type;

//���������.....

//�ع�����
typedef struct SDK_ExposureCfg
{
    int  level;    			//�ع�ȼ�
    unsigned int leastTime;	//�Զ��ع�ʱ�����޻��ֶ��ع�ʱ�䣬��λ΢��
    unsigned int mostTime; 	//�Զ��ع�ʱ�����ޣ���λ΢��
}SDK_ExposureCfg;

//��������
typedef struct SDK_GainCfg
{
    int gain;    //�Զ���������(�Զ���������)��̶�����ֵ
    int autoGain;//�Զ������Ƿ����ã�0:������  1:����
}SDK_GainCfg;

//�������������
typedef struct SDK_CameraParam
{
    unsigned int whiteBalance;      //��ƽ��
    unsigned int dayNightColor;     //��ҹģʽ��ȡֵ�в�ɫ���Զ��л��ͺڰ�
    int elecLevel;             		//�ο���ƽֵ
    unsigned int apertureMode;      //�Զ���Ȧģʽ
    unsigned int BLCMode;           //���ⲹ��ģʽ
    SDK_ExposureCfg exposureConfig;	//�ع�����
    SDK_GainCfg     gainConfig;    	//��������
    
    unsigned int PictureFlip;		//ͼƬ���·�ת
    unsigned int PictureMirror;		//ͼƬ���ҷ�ת(����)
    unsigned int RejectFlicker;		//�չ�Ʒ�������
    unsigned int EsShutter;			//���������Ź���
    
    int ircut_mode;		//IR-CUT�л� 0 = �����ͬ���л� 1 = �Զ��л�
    
    int dnc_thr;		//��ҹת����ֵ
    int ae_sensitivity;	//ae���������
    
    int Day_nfLevel;	//noise filter �ȼ���0-5,0���˲���1-5 ֵԽ���˲�Ч��Խ����
    int Night_nfLevel;
    int Ircut_swap;		//ircut ������= 0        ����= 1
	int high_light;     //ǿ�����ƹ��� 0~255,Ĭ����16
}SDK_CameraParam;

//�������������
typedef struct SDK_AllCameraParam
{
    SDK_CameraParam vCameraParamAll[NET_MAX_CHANNUM];   //���е�ͨ��
}SDK_AllCameraParam;

//�ع�������
typedef struct SDK_CameraAbility
{
    int  count;      						//֧���ع��ٶ�����
    unsigned int speeds[CAMERAPARA_MAXNUM]; //�ع��ٶ�
    int  status;     						//����״̬  >= 0 ����    < 0 �쳣
    int  elecLevel;  						//�ο���ƽֵ
    int  luminance;  						//ƽ������
    char pVersion[64];						//xm 2a�汾
	char isFishLens; //�Ƿ������۾�ͷ������ǣ�����Ҫapp��PC����ͼ��У��
	char resv1[3];   //�����������char�͵ĳ�Ա���������
	char reserve[28];//�����������int�͵ĳ�Ա������
}SDK_CameraAbility;

//���ز��ſ���
enum SDK_LoalPlayAction
{
    SDK_Local_PLAY_PAUSE,		/*<! ��ͣ���� */
    SDK_Local_PLAY_CONTINUE,	/*<! ������������ */
    SDK_Local_PLAY_FAST,	    /*<! ���ٲ��� */
    SDK_Local_PLAY_SLOW,	    /*<! ���ٲ��� */
    
};

//��������
typedef struct SDK_NetShortMsgCfg
{
    bool bEnable;       //�����ֻ����ŵĹ����Ƿ�����
    char pDesPhoneNum[NET_MAX_RECIVE_MSG_PHONE_COUNT][16];
    int  sendTimes;     //��Ҫ��ÿ���ֻ����Ͷ��ٴζ���
}SDK_NetShortMsgCfg;
//�ֻ���������
typedef struct SDK_NetMultimediaMsgCfg
{
    bool bEnable;				// �����ֻ����ŵĹ����Ƿ�����
    char pDesPhoneNum[NET_MAX_RECIVE_MSG_PHONE_COUNT][16]; //���ղ��ŵ��ֻ��ţ���֧��3���ֻ���
    char pGateWayDomain[40];	// ���ص�ַ��������IP
    int  gateWayPort;			// ���ض˿�
    char pMmscDomain[40];		// ���ŷ�������ַ��IP������
    int  mmscPort;				// ���ŷ������˿ں�
}SDK_NetMultimediaMsgCfg;

typedef struct SDK_DASSerInfo
{
    bool enable;
    char serAddr[NET_NAME_PASSWORD_LEN];
    int  port;
    char userName[NET_NAME_PASSWORD_LEN];
    char passwd[NET_NAME_PASSWORD_LEN];
    char devID[NET_NAME_PASSWORD_LEN];
}SDK_DASSerInfo;
typedef enum UploadDataType  //�ϴ���������
{
    VEHICLE=0,//������Ϣ
    SDK_RECORD_STATE,//¼��״̬
    SDK_DIGITCHN_STATE,	//����ͨ������״̬
    SDK_TITLE_INFO,		//ͨ������
	SDK_FUNCTION_STATE, // ����״̬�����˶����¼����ʱ�ĵ�
	SDK_ELECT_STATE, //����
	SDK_MUSICBOX_STATE, //wifi���ֺ�
}UploadDataType;
//�������************************************************************************
//����״̬
enum SDK_CAR_STATUS_TYPE
{
    SDK_CAR_WORKING,             //�Ƿ�������
    SDK_CAR_LIGHT_LEFT_TURN,     //��ת���Ƿ����
    SDK_CAR_LIGHT_RIGHT_TURN,    //��ת���Ƿ����
    SDK_CAR_DOOR_LEFT_FRONT,     //��ǰ���Ƿ��
    SDK_CAR_DOOR_RIGHT_FRONT,    //��ǰ���Ƿ��
    SDK_CAR_DOOR_LEFT_BACK,      //������Ƿ��
    SDK_CAR_DOOR_RIGHT_BACK,     //�Һ����Ƿ��
    SDK_CAR_DOOR_BACK,           //�����Ƿ��
    SDK_CAR_BRAKE,               //�Ƿ��ɲ��
    SDK_CAR_URGENCY_ALARM,       //�����
    SDK_CAR_STATUS_NR, //״̬������Ŀ
};

//�ⲿ��������
enum SDK_IO_INPUT_TYPE
{
    SDK_LOCAL_ALARM_INPUT,//���ر�������
    SDK_RS232_INPUT,      //ͨ��232��������
    SDK_RS485_INPUT,      //ͨ��485��������
};

//�ⲿ��Ϣ�����복��״̬�Ķ�Ӧ��ϵ
typedef struct SDK_CarStatusExchange
{
    int  statusType; //��һ�ֳ���״̬��������ת��
    bool bExist;     //�Ƿ��и���״̬����Ϣ���룬���ݳ�����ʵ�������������
    bool bEnable;    //�Ƿ������״̬
    int  inputType;  //����״̬��Ӧ����Ϣ�������ͣ���IO_INPUT_TYPEö�ٵ�ֵ��ȡ
    int  addr;       //��ַ�������Ǳ��ر��������һ��Ӧ0������ڶ���Ӧ1
    int  sensorType; //����(NO)�򳣱�(NC)����inputType�Ǳ��ر�������ʱ��Ч
}SDK_CarStatusExchange;

typedef struct SDK_CarStatusExchangeAll
{
    SDK_CarStatusExchange exchangeAll[16];
}SDK_CarStatusExchangeAll;

typedef struct SDK_CarStatusNum
{
    int iCarStatusNum;
}SDK_CarStatusNum;

typedef struct SDK_CarDelayTimeConfig
{
    bool bStartDelay;
    bool bCloseDelay;
    
    int timeStartDelay;		//��λ:����
    int timeCloseDelay;		//��λ:����
}SDK_CarDelayTimeConfig;
enum SDK_network_media {
    SDK_NM_WIRED = 0,  	//��������
    SDK_NM_WLAN,       	//Wifi
    SDK_NM_3G,         	//3G����
    SDK_NM_NR,    		//������
};
//�����������ȼ�
typedef struct SDK_tagNetLinkOrder
{
    int netType;  //ȡֵ��network_media���͵�
    int netOrder; //����ԽС�����ȼ�Խ��,0��������ȼ�
}SDK_NetLinkOrder;
//�������ȼ�
typedef struct SDK_NetOrderConfig
{
    bool         bEnable;        			//�Ƿ������������ȼ�
    int          netCount;       			//����������Ŀ
    SDK_NetLinkOrder pNetOrder[SDK_NM_NR];	//�������ȼ�
    SDK_NetLinkOrder pReserve[7-SDK_NM_NR];	//���µ���������Ԥ��
}SDK_NetOrderConfig;
///�������ȼ�����
typedef struct SDK_NetOrderFunction
{
    bool bNetOrder;
}SDK_NetOrderFunction;
#define  MAX_CAR_INFOR 24
/// �����ƺ�
struct  SDK_CarPlates
{
    char sPlateName[MAX_CAR_INFOR];
};
enum NET_ISP
{
    ISP_AUTO, 		//�Զ�ѡ��
    ISP_TELCOM, 	//����
    ISP_UNIONCOM, 	//��ͨ
    ISP_CNC,		//��ͨ
    ISP_MOBILE,		//�ƶ�����ͨ
    ISP_USER,		//�Զ���
};
//����ƽ̨��Ϣ����
typedef struct SDK_LocalSdkNetPlatformConfig
{
    int Enable;
    int nISP;                          ///�μ�NET_ISP
    char sServerName[32];
    char ID[32];
    char sUserName[32];
    char sPassword[32];
    CONFIG_IPAddress HostIP;		///< host ip
    int port;
}SDK_LOCALSDK_NET_PLATFORM_CONFIG;

//GPSУʱ����
typedef struct SDK_GPSTimingConfig
{
    bool bEnable;      // �Ƿ�����
    int  timeChange;   // �����UTCʱ����Ҫ�ı���٣���λ:��
    int  updatePeriod; // ��������  ��λ:����
}SDK_GPSTimingConfig;
//���۽Ӿ�����ϵͳ
typedef struct	SDK_GodEyeConfig
{
    bool	bEnable;
    char MainSeverName[NET_NAME_PASSWORD_LEN];	//������
    int MainPort;								//���˿�
    char ExSeverName[NET_NAME_PASSWORD_LEN]; 	//��������
    int ExPort;									//���ö˿�
}SDK_GodEyeConfig;
enum  SDK_DigManagerShowStatus
{
    SDK_DM_SHOW_NONE,
    SDK_DM_SHOW_ALL,
};


//����ͨ����ʾ״̬
typedef struct SDK_DigitalManagerShow
{
    int  nDigitalManagerShowSta;
}SDK_DigitalManagerShow;

//NAT���䣬MTUֵ
typedef struct SDK_NatConfig
{
    bool bEnable;
#if 0
    bool CloudpushEnable;
#endif
    int nMTU;             		// ��Χ (100,1400)
    char serverAddr[64];  		//�Ʒ������������IP��ַ��
    int  serverPort;      		//�Ʒ���Ķ˿�;
    CONFIG_IPAddress dnsSvr1;	//�Ʒ����DNS��������ַ
    CONFIG_IPAddress dnsSvr2;
#if 0
    char pResv[16];      		//����
#endif
}SDK_NatConfig;

typedef enum SubConnType
{
    conn_realTimePlay=1,
    conn_talk,
    conn_playback,
	conn_push
}SubConnType;
//*** */���豸ע��
enum SocketStyle
{
	TCPSOCKET=0,
	UDPSOCKET,	
	PLUGLANSOCKET=4,		//������������½
	PLUGOUTERSOCKET,		//����������½
	P2P_TUTKSOCKET,			//TUTK P2P
    SOCKETNR
};


enum SDK_NatStatusType
{
    SDK_NAT_STATUS_DISENABLE,	//δ����
    SDK_NAT_STATUS_PROBING,  	//����̽��DNS
    SDK_NAT_STATUS_CONNECTING,	//�������ӷ�����
    SDK_NAT_STATUS_CONNECTED,	//���ӳɹ�
};
//nat״̬��Ϣ
typedef struct SDK_NatStatusInfo
{
	int	iNatStatus;
	char NatInfoCode[256];//�������ݣ��Ӵ�

}SDK_NatStatusInfo;

/// ����ˮӡ����
typedef struct SDK_WaterMarkConfig
{
    bool	bEnable;		//  ����ˮӡ
    char  sKey[8];
    char sUserData[16];
}SDK_WaterMarkConfig;

typedef struct SDK_WaterMarkConfigAll
{
    SDK_WaterMarkConfig vWaterMarkConfigAll[NET_MAX_CHANNUM];
}SDK_WaterMarkConfigAll;

///��������̬����
typedef struct SDK_EncodeStaticParam
{
    int profile;
    int level;
    int reserved1[4];
}SDK_EncodeStaticParam;


typedef struct SDK_EncodeStaticParamAll
{
    SDK_EncodeStaticParam	EncodeStaticParamAll[NET_MAX_CHANNUM];
}SDK_EncodeStaticParamAll;

enum
{
    sdk_maxCPCDataItem = 2048,
    sdk_maxCPCDataReturn = 512,
    sdk_itemtotalLength = 96,	//2λͨ���ţ�20λ��ʼʱ�䣬20λ����ʱ�䣬������13λ������,������
    sdk_maxpack=4,// sdk_maxCPCDataItem/sdk_maxCPCDataReturn
};

typedef struct SDK_CPCDataItem	//����ͳ����ṹ��
{
    int channel;				//��Ӧ��ͨ����
    SDK_SYSTEM_TIME startTime;	//��ʼʱ��
    SDK_SYSTEM_TIME endTime;	//����ʱ��
    int inNum;					//��������
    int outNum;					//�뿪����
}SDK_CPCDataItem;

typedef struct SDK_CPCData
{
    int nItemNum;
    SDK_CPCDataItem CPCData[sdk_maxCPCDataReturn];
}SDK_CPCData;

typedef struct SDK_CPCDataAll
{
    int nCount;
    SDK_CPCData nCpcData[sdk_maxpack] ;
}SDK_CPCDataAll;

/// ¼��洢�豸���ͣ��������͵�һ�ֻ��߶���
typedef struct SDK_RecordStorageType
{
    bool SATA_as;
    bool USB_as;
    bool SD_as;
    bool DVD_as;
}SDK_RecordStorageType;

//VPN�ṹ��
typedef struct SDK_VPNConfig
{
    bool Enable;								///< �Ƿ���
    CONFIG_IPAddress ServiceIp;					///< ������IP��ַ
    char UserName[NET_NAME_PASSWORD_LEN];		///< �û���
    char Password[NET_NAME_PASSWORD_LEN];		///< ����
    CONFIG_IPAddress addr;						///< ���ź��õ�IP��ַ
    char ServerName[NET_NAME_PASSWORD_LEN];		///< openvpn��������ַ
    int port;
}SDK_VPNConfig;
//��ǰVGA�ֱ���
typedef struct SDK_VGAresolution
{
    int nHeight;
    int nWidth;
}SDK_VGAresolution;
//֧��VGA�ֱ����б�
typedef struct SDK_VGAResolutionAbility
{
    int vVGANum;
    char vVGAList[VGA_MAXNUM][VGA_NAME_LENGTH];
}SDK_VGAResolutionAbility;

//�豸�б�(�豸������)
typedef struct SDK_NetDevList
{
    int vNetDevNum;
    SDK_CONFIG_NET_COMMON_V2 vNetDevList[DEV_LIST_SHOW];
}SDK_NetDevList;


//���ݿ���ƽ̨
/***�û���Ϣ***/

typedef struct SDK_CONFIG_KAINENG_USERINFO
{
    char szUserName[16];           //�û�������5�����ֻ�ʮ����ĸ;
    char szUserAddr[128];          //�û���ַ��30�����ֻ�60����ĸ;
    char szUserAttr[16];           //�û����ʣ�5�����ֻ�ʮ����ĸ��
    
    char szBelongUnit[64];         //��ܵ�λ��15�����ֻ�30����ĸ;
    char szBelongUnitPhone[16];    //��ܵ�λ�绰��14λ���֣��ֻ���"-" �����;
    
    char szPoliceUnit[64];         //������λ��15�����ֻ�30����ĸ;
    char szPoliceUnitAddr[128];    //������λ��ַ��30�����ֻ�60����ĸ;
    char szPoliceUnitPhone[16];    //������λ�绰��14λ���֣��ֻ���"-"�����;
    
    char szPolicePhone[4][16];
    char szPolOrCenPhone[2][16];   //����/���ĵ绰1��2��14λ���֣��ֻ���"-" �����;
    
    char szFTP[64];                //FTP��50���ַ���
    char szEMail[64];              //E-Mail: 50���ַ���
    CONFIG_IPAddress PoliceIP;     //�Ӿ�����IP��ַ
    int nHttpPort;                 //�Ӿ�����IP�˿�
}SDK_CONFIG_KAINENG_USERINFO;

/***�豸��Ϣ***/
//���ò�������ö��
typedef enum SDK_GuardType
{
    SDK_FORBID = 0,      //��ֹ
    SDK_TEN_MIN,         //ʮ����
    SDK_THIRTY_MIN,      //��ʮ����
    SDK_SIXTY_MIN,       //��ʮ����
    SDK_MAX,
}SDK_GUARDTYEP;


typedef struct SDK_CONFIG_KAINENG_DEVINFO
{
    char ProbeNum1;                //��������������������ÿ��������� 1�ŵ�10��̽����ѡ�� ��Ĭ������Ϊ <1��̽����>
    char ProbeNum2;                //��������������������ÿ��������� 1�ŵ�10��̽����ѡ�� ��Ĭ������Ϊ <1��̽����>
    char nProbeType;			   //������������ ��ѡ��3��Ϊ <��ֹ>  <AND>  <OR>  Ĭ��Ϊ <��ֹ>
    char nGuardType;               //���ò���, ����GUARDTYEP
    
    int AlarmTime;                 //���ѿ���ʱ�䣺��λ���ִ�000-999  Ĭ��Ϊ��180
    int nGuardArea;               //���߷������ͣ���λ���֣�ÿλ��С0���3����00000000 ��33333333;  Ĭ�ϣ�00000000��
    
    char szRemConAddr[4][4];       //ң����1-4�ŵ�ַ ����λ16�����ַ�����գ���0-9  A-F����Ĭ��Ϊ�գ�
    char szLinDevAddr[6][4];       //�����豸��1-6��ַ����λ16�����ַ�����գ���0-9  A-F����Ĭ��Ϊ�գ�
    char szProbeAddr[10][4];       //̽����1-10�ŵ�ַ����λ16�����ַ�����գ���0-9  A-F����Ĭ��Ϊ�գ�
    
    //��ʱ������
    char szGuardTime[3][9];        //��ʱ������,ÿ�鶼Ϊchar [8] ���� ��00 00 00 00������ɿ�ʼʱ�ֵ�����ʱ�֣�����Ҫ��������
}SDK_CONFIG_KAINENG_DEVINFO;

/***��������***/
//��������ö��
typedef enum SDK_KNAlarmLink
{
    SDK_LINK_EMPTY = 0,
    SDK_LINK_SWITH,
    SDK_LINK_10S,
    SDK_LINK_30S,
    SDK_LINK_60S,
    SDK_LINK_200S,
    SDK_LINK_600S,
    SDK_LINK_METHOD_1,
    SDK_LINK_METHOD_2,
    SDK_LINK_MAX_1,
}SDK_KNALARMLINK;

typedef struct SDK_CONFIG_KAINENG_LINKINFO
{
    char eLink[10][7];        //��������,ȡֵΪ��������ö��
}SDK_CONFIG_KAINENG_LINKINFO;

//���ܶ��ƣ�3��������Ϣȫ�����
typedef struct SDK_CONFIG_KAINENG_INFO
{
    SDK_CONFIG_KAINENG_USERINFO UserInfo;
    SDK_CONFIG_KAINENG_DEVINFO DevInfo;
    SDK_CONFIG_KAINENG_LINKINFO LinkInfo;
}SDK_CONFIG_KAINENG_INFO;

//�����豸Э��
typedef enum SDK_TransferProtocol_V2
{
    SDK_TRANSFER_PROTOCOL_NETIP,
    SDK_TRANSFER_PROTOCOL_ONVIF,
    SDK_TRANSFER_PROTOCOL_MAC,
	SDK_TRANSFER_PROTOCOL_NAT,
	SDK_TRANSFER_PROTOCOL_DAHUA,
	SDK_TRANSFER_PROTOCOL_RTSP,
	SDK_TRANSFER_PROTOCOL_NETIPV6,
    SDK_TRANSFER_PROTOCOL_NR_V2,
    SDK_TRANSFER_PROTOCOL_ONVIF_DEFAULT = 128,
    SDK_TRANSFER_PROTOCOL_ONVIF_NR_V2
}SDK_TransferProtocol_V2;

typedef struct SDK_EncodeStaticParamV2
{
    int profile; //��ǰ��̬����
    int reserved1[4]; //�����ֶ�
}SDK_EncodeStaticParamV2;

/*
 ==	DVR��̬����������������3��
 ==	0 ��֧�� 1 ֧��baseline 2 ֧��main profile 4 ֧��high profile
 ==  �������
 */
typedef struct SDK_EncStaticParamAbility
{
    unsigned int encStaticParam;
}SDK_EncStaticParamAbility;

//���մ���C7ƽ̨����
typedef struct SDK_C7PlatformConfig
{
    char pServerAddr[64];//ƽ̨��ַ��IP��ַ������
    int  servPort;       //ƽ̨�˿�
    char pPUID[32];      //PUID
    char pPassword[32];  //����
    char pStatus[64];    //����״̬����LocalSDK���ǿɶ���д�ģ������ط���ֻ��
    char pResv[60];      //����
}SDK_C7PlatformConfig;

///�������
typedef struct SDK_NetKeyboardConfig
{
    bool Enable;				//�Ƿ���
    char sTransProtocol[4];		//����Э��
    int ListenPort;				//�����˿�
    char sParserProtocol[32];
    int deviceaddr;				//�豸��ַ
}SDK_NetKeyboardConfig;
////// �������Э��
typedef struct SDK_NetKeyboardAbility
{
    //ÿ��Э�������64���ַ����
    int nTransPNum;
    char vTransProtocol[32][NET_MAX_PTZ_PROTOCOL_LENGTH];
    int nParserNum;
    char vParserProtocol[32][NET_MAX_PTZ_PROTOCOL_LENGTH];
}SDK_NetKeyboardAbility;

//28181Э������
typedef struct SDK_ASB_NET_VSP_CONFIG
{
    bool	bCsEnable;								//ʹ�ܱ��
    char	szCsIP[64];								//��������ַ
    short	sCsPort;								//�������˿�
    short	sUdpPort;								//���ذ�udp�˿�
    char	szServerNo[64];							//���������к�
    char 	szServerDn[64];							//���������ڵ�������
    char	szDeviceNO[64];							//�豸���к�
    char 	szConnPass[64];							//�豸��������
    int		iHsIntervalTime;						//�������ʱ��,��λ����
    int		iRsAgedTime;							//���·���ע��ʱ�����λΪ��
    char	Camreaid[NET_MAX_CHANNUM][64];			//�豸������ͷID
    int		CamreaLevel[NET_MAX_CHANNUM];			//�����ȼ�
    char	Alarmid[NET_MAX_CHANNUM][64];			//�豸������ͷID
    int		AlarmLevel[NET_MAX_CHANNUM];			//�����ȼ�
    unsigned int	uiAlarmStateGpinEnable;			//�ⲿ����ʹ��
    unsigned int	uiAlarmStateLoseEnable;			//��Ƶ��ʧ�澯ʹ��
    unsigned int	uiAlarmStateMotionEnable;		//��Ƶ��̬���澯ʹ��
    unsigned int	uiAlarmStateBlindEnable;		//��Ļ�ڵ��澯ʹ��
    unsigned int	uiAlarmStatePerformanceEnable;	//ϵͳ�쳣�澯ʹ��
    unsigned int	uiAlarmStateConnectEnable;		//�û����Ӹ澯ʹ��
}SDK_ASB_NET_VSP_CONFIG;

//�ֻ���������
typedef struct SDK_PMSConfig
{
    bool Enable;		///< �Ƿ���
    char servname[64];
    int port;
    char boxid[128];
    char resume[24]; //����
}SDK_PMSConfig;

//��Ļ��ʾ��Ϣ
typedef struct  SDK_OSDInfoConfig
{
    SDK_VIDEO_WIDGET OSDInfoWidget;
    char ppInfo[NET_MAX_LINE_PER_OSD_AREA][NET_CHANNEL_NAME_MAX_LEN];
}SDK_OSDInfoConfig ;

typedef enum SDK_wordEncType
{
    SDK_wordEnc_GB2312,			//���ֱ���GB2312
    SDK_wordEnc_Unicode,		//����� Unicode
    SDK_wordEnc_UTF8,			//UTF-8
    SDK_wordEnc_NR,	
}SDK_wordEncType;

//����ͨ������Ļ��ʾ��Ϣ
typedef struct  SDK_OSDInfoConfigAll
{
    SDK_OSDInfoConfig   vOSDInfoAll[NET_MAX_CHANNUM];
    int strEnc;//�����ʽ,Ĭ��ΪUTF-8,�����κδ�����Ҫ���ڿͻ���������ö�ٲμ�SDK_wordEncType
}SDK_OSDInfoConfigAll;
//
typedef struct SDK_KaiCongAlarmConfig
{
    bool Enable;								///< �Ƿ���
    char ServerName[NET_NAME_PASSWORD_LEN];		///< ������
    int Port;									///< �˿ں�
    char UserName[NET_NAME_PASSWORD_LEN];		///< �û���
    char Password[NET_NAME_PASSWORD_LEN];		///< ����
}SDK_KaiCongAlarmConfig;
//
typedef struct SDK_VideoChannelManage
{
    int		nHVRCap;
    int		curMode;
    bool bhide[MAX_HVR_CHNCAP_CHN];
    SDK_CAPTURE_HVRCAPV2	HVRCap[MAX_HVR_CHNCAP_CHN];
}SDK_VideoChannelManage ;

//PTZ����������
typedef struct SDK_PTZControlAbility
{
    unsigned int nPTZPosition;
}SDK_PTZControlAbility;

typedef struct SDK_PositionPoint
{
    int iPointStart_x;
    int iPointStart_y;
    int iPointEnd_x;
    int iPointEnd_y;
}SDK_PositionPoint;

typedef struct SDK_XMHeartbeatConfig
{
    bool bEnable;								///< �Ƿ���
    int iInterval;								///< ������ʱ��
    char ServerName[NET_NAME_PASSWORD_LEN];		///< ������
    int Port;									///< �˿ں�
    char UserName[NET_NAME_PASSWORD_LEN];		///< �û���
    char Password[NET_NAME_PASSWORD_LEN];		///< ����
    char resume[24];
}SDK_XMHeartbeatConfig;

typedef struct SDK_MonitorPlatformConfig
{
    int Enable;		///< �Ƿ���
    char servname[NET_NAME_PASSWORD_LEN];
    int port;
    char resume[24];
    char agentid[128];	//�ͻ���id�����ƽ̨ʹ��(��SSJC��ͷ)
    char type[128];		//
}SDK_MonitorPlatformConfig;

typedef enum SDK_IMG_TYPE
{
    SDK_IMG_TYPE_DEFAULT,
    SDK_IMG_TYPE_1,
    SDK_IMG_TYPE_2,
    SDK_IMG_TYPE_NR,
}SDK_IMG_TYPE;
//��������ͷ��չ����
typedef struct SDK_CameraParamEx
{
    SDK_GainCfg broadTrends;		//��̬
    int style;						//enum SDK_IMG_TYPE
    unsigned int exposureTime;		//ʵ����Ч���ع�ʱ��
	int  Dis ;						//���ӷ�������  0:�ر� 1:����**/
	int Ldc; 						//��ͷ����У��  0:�ر� 1:����**/
	int AeMeansure; 				//���ģʽУ��  0:ƽ����� 1:������**/
	int LowLuxMode; 				//΢��ģʽ mode��0 �ر� 1���� ==only imx291
	int corridor_mode;				//1:����ģʽ  0:��ͨģʽ
	int lightRestrainLevel;			// ǿ�����ƹ���0~255��Ĭ��16
	int res[56];	//���� 
}SDK_CameraParamEx;

// ����ͷ������չ����
typedef struct SDK_CameraParamExAll
{
    SDK_CameraParamEx vCameraParamExAll[NET_MAX_CHANNUM];
}SDK_CameraParamExAll;

//���������ƽ̨ͨ�����ã��Ժ��ƶ������
typedef struct SDK_NetPlatformCommonCfg
{
    int	Enable;
    int Port;									///< �˿ں�
    char ServerName[NET_NAME_PASSWORD_LEN];		///< ������
    char ID[NET_NAME_PASSWORD_LEN];
    char UserName[NET_NAME_PASSWORD_LEN];		///< �û���
    char Password[NET_NAME_PASSWORD_LEN];		///< ����
    char resume[128];							///Ԥ��
}SDK_NetPlatformCommonCfg;

typedef enum SDK_INFO_NET_LINK_STATUS
{
    SDK_INFO_NET_LINK_OK         = 0,
    SDK_INFO_NET_LINK_FAILED     = 1,
    SDK_INFO_NET_LINK_NO_DEVICE  = 2,
    SDK_INFO_NET_LINK_INVALID    = 9,
}SDK_INFO_NET_LINK_STATUS;

typedef enum SDK_POSITIONING_DIRECTION
{
    SDK_POS_DIRECTION_EAST  = 'E',
    SDK_POS_DIRECTION_WEST  = 'W',
    SDK_POS_DIRECTION_SOUTH = 'S',
    SDK_POS_DIRECTION_NORTH = 'N'
}SDK_POSITIONING_DIRECTION;

typedef struct SDK_POSITIONING_POS//��γ��
{
    int  degree;     //��(��/1000)Ϊ��λ
    char direction;  //��λ ȡֵ��ö��ֵPOSITIONING_DIRECTION��ʾ
    char res[3];
}SDK_POSITIONING_POS;
//GPS״̬
typedef struct SDK_GPSStatusInfo
{
    int             positioningStatus; //��λ״̬��ȡֵ��ö��SDK_INFO_NET_LINK_STATUS����
    SDK_POSITIONING_POS longitudePos;      //����
    SDK_POSITIONING_POS latitudePos;       //γ��
    char            rev[12];
}SDK_GPSStatusInfo;

//wifi״̬
typedef struct SDK_WifiStatusInfo
{
    int  connectStatus;  //wifi����״̬  ��ö��SDK_INFO_NET_LINK_STATUS����
    int  strength;       //�ź�ǿ��
    char rev[24];
}SDK_WifiStatusInfo;

//3G״̬
typedef struct SDK_WirelessStatusInfo
{
    int  connectStatus;  //3G����״̬  ��ö��SDK_INFO_NET_LINK_STATUS����
    int  strength;       //�ź�ǿ��
    char rev[24];
}SDK_WirelessStatusInfo;

//����ע��״̬
typedef struct SDK_DASStatusInfo
{
    int  connectStatus;  //DAS����״̬  ��ö��SDK_INFO_NET_LINK_STATUS����
    char rev[28];
}SDK_DASStatusInfo;

typedef struct SDK_RecordStorageInfo
{
    unsigned int bStart;			//�Ƿ�¼���־λ
    SDK_SYSTEM_TIME beginTime;		//¼��ʼʱ��
    SDK_SYSTEM_TIME endTime;		//¼�����ʱ��
    unsigned int  storageCapacity;	//Ӳ��������
    unsigned int  useCapacity;		//ʹ������
    int res[16];					//����
}SDK_RecordStorageInfo;
/// ������ʱ�ȼ�
typedef enum SDK_DecodeDeleyTypes
{
    SDK_DecodeDeley_0 = 0,
    SDK_DecodeDeley_1,
    SDK_DecodeDeley_2,
    SDK_DecodeDeley_3,
    SDK_DecodeDeley_4,
    SDK_DecodeDeley_5,
    SDK_DecodeDeley_6,
    SDK_DecodeDeley_TYPE_NR,
}SDK_DecodeDeleyTypes;

typedef struct SDK_DecodeDeleyTimePrame
{
    unsigned int  DecodeDeleyTime[SDK_DecodeDeley_TYPE_NR];
}SDK_DecodeDeleyTimePrame;

// ����ͨ��
typedef struct SDK_DecodeParam
{
    int iMaxDeleyTime[NET_MAX_CHANNUM];	// ���Ľ�����ʱ
}SDK_DecodeParam;

typedef struct SDK_RecordStateInfo
{
    int nchannel;
    int RecordState;
}SDK_RecordStateInfo;

//������Ƶ��ɫ�ṹ
typedef struct SDK_VIDEOCOLOR_PARAM_EX
{
    int		BrightnessRef;		///< ����ref1��ȡֵ0-100��
    int		ContrastRef;		///< �Աȶ�ref1��ȡֵ0-100��
    int  		ContrastThRef;	///< �Աȶȷ�ֵref1��ȡֵ0-100��
    int		ContrastSlopeRef;	///< �Աȶ�б��ref1��ȡֵ0-100��
    int 		DarkBlfRef;
    int		DarkNfRef;
    int		DarkEcPthRef;
    int		DarkEcMthRef;
    int		DarkDcRef;
    int		CbGain;				///high low middle
    int		CrGain;				///higg low middle
    int		reserved;			///����
}SDK_VIDEOCOLOR_PARAM_EX;

typedef struct SDK_VIDEOCOLOR_PARAM_CUSTOM
{
    SDK_VIDEOCOLOR_PARAM_EX	VideoColor[3];
    int		Saturation;		///< ���Ͷȣ�ȡֵ0-100��
    int		Gain;			///< ���棬ȡֵ0-100��bit7��λ��ʾ�Զ����棬����λ�����ԡ�
    int		Acutance;		///< ��ȣ�ȡֵ0-100
    int		AeWight;		//���ⲹ��
}SDK_VIDEOCOLOR_PARAM_CUSTOM;

typedef enum SDK_FileControlType
{
    SDK_FILE_DEL,			//ɾ���ļ�
    SDK_FILE_DIR_DEL,		//ɾ���ļ���
    SDK_FILE_DIR_CLEAR,		//����ļ���
	SDK_RUNTIME_CLEAR,		//�������ʱ��
    SDK_FILE_NR,
}SDK_FileControlType;

typedef struct SDK_NetFileControl
{
    int iAction;			//enum FileControlType
    char strfile[256];
}SDK_NetFileControl;

typedef enum SDK_DecChnStateType
{
    SDK_DEC_STA_NONE, 			//����
    SDK_DEC_STA_NOCONFIG,		//δ����
    SDK_DEC_STA_NOLOGIN,		//δ��½
    SDK_DEC_STA_NOCONNECT,		//δ����
    SDK_DEC_STA_CONNECTED,		//������
    SDK_DEC_STA_LOGIN_FAILED,	//��¼ʧ��
	SDK_DEC_STA_OFFLINE,		//ǰ���豸������
}SDK_DecChnStateType;

typedef struct SDK_DigitStateInfo
{
    int nchannel;
    int DigitState; //SDK_DecChnStateType
}SDK_DigitStateInfo;

typedef struct SDK_TitleNameInfo
{
    int nchannel;
    char titleName[256];
}SDK_TitleNameInfo;

typedef struct SDK_AbilityMask
{
    unsigned int AbilityPram;
}SDK_AbilityMask;

typedef enum SDK_Music_Play_Action
{
    SDK_MUSIC_ACTION_PLAY,
    SDK_MUSIC_ACTION_STOP,
    SDK_MUSIC_ACTION_PAUSE,
    SDK_MUSIC_ACTION_CONTINUE
}SDK_Music_Play_Action;

typedef struct SDK_LocalMusicControl
{
    int iAction;            //�ο�SDK_Music_Play_Action
    char sFileName[20];
}SDK_LocalMusicControl;

/// ��Ƶ�ļ��б���Ϣ
typedef struct SDK_MusicFileList
{
    int iNumFiles;		///< �ļ�����
    char sFileName[8][20];
}SDK_MusicFileList;

typedef enum SDK_CAR_BOOT_TYPE
{
    SDK_CAR_BOOT_TYPE_SPARK,  //���Ϩ�𿪹ػ�
    SDK_CAR_BOOT_TYPE_TIMING, //��ʱ���ػ�
    SDK_CAR_BOOT_TYPE_NR,
}SDK_CAR_BOOT_TYPE;


//��𿪹ػ���ʱ����
typedef struct SDK_CarSparkWork
{
    int bootDelayMinute;  //������ʱ������
    int shutDelayMinute;  //�ػ���ʱ������
    char resv[24];        //����
}SDK_CarSparkWork;

//���ض�ʱ���ػ�����
typedef struct SDK_CarTimingWork
{
    SDK_TIMESECTION workSection1; //����ʱ���1
    SDK_TIMESECTION workSection2; //����ʱ���2
    char resv[32]; //����
}SDK_CarTimingWork;

typedef struct SDK_CarBootTypeConfig
{
    int           bootType;         	//��ö�� SDK_CAR_BOOT_TYPE ����
    SDK_CarSparkWork  sparkWorkConfig;  //��𿪹ػ�����
    SDK_CarTimingWork timingWorkConfig; //��ʱ���ػ�ʱ���1
    char          resv[48];
}SDK_CarBootTypeConfig;

//����IPC
typedef struct SDK_ALARM_IPCCONFIG
{
    bool	bEnable;			///< �������뿪��
    int		iSensorType;		///< ���������ͳ��� or ����
    SDK_EventHandler hEvent;	///< ��������
}SDK_ALARM_IPCCONFIG;
///< ��������ͨ���ı�������
typedef struct SDK_IPCAlarmConfigAll
{
    SDK_ALARM_IPCCONFIG vAlarmConfigAll[NET_DECORDR_CH];
}SDK_IPCAlarmConfigAll;

//�ٶ���
typedef struct SDK_BaiduCloudCfg
{
    bool	enable;
    char APIKey[NET_NAME_TOKEN_LEN];				//Ӧ��API��Կ
    char SecretKey[NET_NAME_TOKEN_LEN];				//Ӧ����Կ
    char AuthorizationCode[NET_NAME_TOKEN_LEN];		//��Ȩ��
    char accessToken[NET_NAME_TOKEN_LEN];			//����Ȩ����
    char refreshToken[NET_NAME_TOKEN_LEN];			//ˢ��Ȩ����
    char deviceID[NET_NAME_TOKEN_LEN];				//�豸ID
    char userCode[NET_NAME_TOKEN_LEN];				//�û���Ȩ��
    char qrcodeUrl[NET_NAME_TOKEN_LEN];				//��ά��
    char streamID[NET_NAME_TOKEN_LEN];				//��ID
    char describe[NET_NAME_TOKEN_LEN];				//�豸����
    int state;										//״̬
    SDK_SYSTEM_TIME	refreshTime;					//�ϴ�ˢ��Tokenʱ��
    int channelMain[NET_MAX_CHANNUM];				//�Ƿ�����
    int channelExtra[NET_MAX_CHANNUM];				//�Ƿ�����
    int	recordFileMode;								//����¼��ģʽ
    int	recordFileSize;								//¼���ļ���С
    int	recordFileTime;								//¼���ʱ��
    char resume[128];								//Ԥ��
}SDK_BaiduCloudCfg;

//�ֻ�������
typedef struct SDK_PhoneInfoNum
{
    int nNum;
}SDK_PhoneInfoNum;

typedef struct SDK_LOGIN_CFG//�޸�ǰ��ip��¼��
{
    char sUserName[NET_MAX_USER_LENGTH];		///< ��½����
    char sPassword[NET_MAX_USER_LENGTH];		///< ��½����
    int iEncryptType;			///< ������ܷ�ʽ �̶�ֵ 1
}SDK_LOGIN_CFG;

typedef struct SDK_IPSetCfg
{
    int ch;
    int devtype;
    SDK_CONFIG_NET_COMMON netcfg;
    SDK_LOGIN_CFG loginPram;
}SDK_IPSetCfg;

#define SDK_LONG_PATH_LEN 256	// Զ��·��(����Դ)
#define SDK_SHORT_PATH_LEN 64	// ���ع��ص�
#define SDK_FS_TYPE_LEN 8	//�ļ�ϵͳ����(eg: ext3)���ֳ�������
#define SDK_USERNAME_LEN 32
#define SDK_PASSWD_LEN 32
#define SDK_MAX_NAS_NUM 8	//���֧��NAS����
#define SDK_MAX_DEV_NUM 16	// ֧�ֱ����豸����
#define SDK_MAX_PART_NUM 4	// ����Ӳ��֧�ֵķ�����������
struct SDK_NAS_INFO	// NAS��Ϣ
{
	char mountSrc[SDK_LONG_PATH_LEN];	// Զ��·��(����Դ)
	char fsType[SDK_FS_TYPE_LEN];
	char mountOn[SDK_SHORT_PATH_LEN];	// ���ع��ص�
	char username[SDK_USERNAME_LEN];
	char password[SDK_PASSWD_LEN];
	unsigned int DirType;	//��ö��IStorageDirectory::DIR_TYPE����
};

typedef struct SDK_NAS_LIST	// NAS(samba, nfs)�б�
{
	unsigned int  count;
	SDK_NAS_INFO nasInfo[SDK_MAX_NAS_NUM];
}SDK_NAS_LIST;

//��ά
typedef struct SDK_DimenCode
{
    int size;
    unsigned char code[3920];// 177*177/32*4=3920���ֲ�����
}SDK_DimenCode;

typedef struct SDK_DimenCodeAll
{
    SDK_DimenCode sn;
    SDK_DimenCode appIOS;
    SDK_DimenCode appAndroid;
    SDK_DimenCode otherInfo;  //�ͻ��Զ�����Ϣ
}SDK_DimenCodeAll;

//�й������ֻ�����ƽ̨
typedef struct SDK_MobileWatchCfg
{
    int	Enable;
    char DevID[NET_NAME_ID_LEN];			// �豸����
    char DevKey[NET_NAME_ID_LEN];			// �豸��֤��
    char ManufacturerNo[NET_NAME_ID_LEN];	// ���̱��
    char Mode[NET_NAME_ID_LEN];				// �豸�ͺ�
    char GroupAddr[NET_NAME_URL_LEN];		// ����ƽ̨��ַ
    char ProvinceAddr[NET_NAME_URL_LEN];	// ʡƽ̨��ַ
    char NatIP[NET_NAME_ID_LEN];			// �豸�������������ַ
    int	NatPort;							// �豸������������˿�
    char BackupNatIP[NET_NAME_ID_LEN];		// �豸���÷����������ַ
    int	BackupNatPort;						// �豸���÷���������˿�
    char TurnIP[NET_NAME_ID_LEN];			// TurnServer��������ַ
    int	TurnPort;							// TurnServer�������˿�
    char BackupTurnIP[NET_NAME_ID_LEN];		// TurnServer���ݷ�������ַ
    int	BackupTurnPort;						// TurnServer���ݷ������˿�
    char FtpIP[NET_NAME_ID_LEN];			// ͼƬ�ϴ�FTP��������ַ
    int	FtpPort;							// ͼƬ�ϴ�FTP�������˿�
    char FtpAccount[NET_NAME_ID_LEN];		// ͼƬ�ϴ�FTP�������ʺ�
    char FtpPassword[NET_NAME_ID_LEN];		// ͼƬ�ϴ�FTP����������
    char resume[NET_NAME_URL_LEN];			// Ԥ��
}SDK_MobileWatchCfg;

typedef struct SDK_BrowserLanguageType
{
    int type;
}SDK_BrowserLanguageType;

typedef struct SDK_TimeZone
{
    int minuteswest; 	//��UTCʱ��Ĳ�ֵ����λ���ӣ�����Ϊ��
    int FistFlag;		//���ڱ�֤��һ��ʹ�õ�ʱ��ʱ�䲻��
}SDK_TimeZone;


typedef enum SDK_TimeSynTypes
{
    SDK_TST_OFF = 0,
    SDK_TST_TIME_UTC,
    SDK_TST_TIME_LOCAL,
    SDK_TST_TIME_ALL,
    SDK_TST_NR,
}SDK_TimeSynTypes;

// ����ͨ��ʱ��ͬ��
typedef struct SDK_TimeSynParam
{
    int iTimeModel[NET_MAX_CHANNUM]; //�ο�SDK_TimeSynTypes
}SDK_TimeSynParam;

typedef struct SDK_CustomizeOEMInfo
{
    unsigned int typeMask;//����: BITMSK(BURN_OEM_ID),BITMSK(BURN_OEM_PRODUCT),BITMSK(BURN_OEM_SERIAL)
    unsigned int oemID;
    unsigned int oemProduct;
    unsigned int oemSerial;
}SDK_CustomizeOEMInfo;

typedef struct SDK_IFrameRange
{
	int main_min;
	int main_max;
	int sub_min;
	int sub_max;
}SDK_IFrameRange;

typedef struct SDK_DigitDevInfo
{
    bool enable; 					//�����Ƿ���ã������豸ʹ��
    int nCapture;					//ģ��ͨ����
    int nAudio;						//��Ƶͨ����
    int videoFormat;				//��Ƶ��ʽ
    CONFIG_EncodeAbility ability;	//��������
	SDK_IFrameRange iGOPRange;	//����������I֡���Χ
}SDK_DigitDevInfo;

typedef struct SDK_EncodeChDisplay
{
    char displayChanelMask[NET_MAX_MSK_SIZE];	//IE��ʾ�ı�������ͨ��������
}SDK_EncodeChDisplay;

//���Ѳ��
typedef struct SDK_TourState
{
    bool bRunning;
    int  lineID;   //���Ѳ����·���
}SDK_TourState;

//Ѳ��
typedef struct SDK_PatternState
{
    bool bRunning;
    int  lineID;  //Ѳ����·��� (δʹ��)
}SDK_PatternState;

//��ɨ
typedef struct SDK_ScanState
{
    bool bRunning;
    int  lineID;  //��ɨ��·��� (δʹ��)
}SDK_ScanState;

//ˮƽ��ת
typedef struct SDK_PanonState
{
    bool bRunning;
    int  lineID;  //ˮƽ��ת��·��� (δʹ��)
}SDK_PanonState;

//����ת��ָ��Ԥ�õ�
typedef struct SDK_PresetState
{
    bool bEnable;
    int  iPresetID;
}SDK_PresetState;

//�ϵ�ǰλ��
typedef struct SDK_PoweroffState
{
    bool bEnable;
    int  iPresetID;
}SDK_PoweroffState;

//һ��ͨ������̨����״̬
typedef struct SDK_PtzState
{
    SDK_TourState    tourState;
    SDK_PatternState patternState;
    SDK_ScanState    scanState;
    SDK_PanonState   panonState;
    SDK_PresetState  presetState;
    SDK_PoweroffState poweroffState;
}SDK_PtzState;

//�����ָ�֮ǰ����̨����״̬
typedef struct SDK_ResumePtzState
{
    bool     bEnable;                    //�Ƿ������豸�����ָ���̨״̬����
    SDK_PtzState ptzStateAll[NET_MAX_CHANNUM];
}SDK_ResumePtzState;

/// �ٶȱ�������
typedef enum SDK_SpeedAlarmTypes
{
    SDK_SPEED_ALARM_HIGH,		// ���ٱ���
    SDK_SPEED_ALARM_LOW,		// ���ٱ���
    SDK_SPEED_ALARM_NR
}SDK_SpeedAlarmTypes;

///< �ٶȱ�������
typedef struct SDK_SpeedAlarmConfig
{
    bool	bEnable;			///< �ٶȱ�������
    int		iSpeed;				///< �ٶ�
    SDK_EventHandler hEvent;	///< �ٶȱ�����������
}SDK_SpeedAlarmConfig;

/// ȫ�����͵��ٶȱ�������
typedef struct SDK_SpeedAlarmConfigAll
{
    SDK_SpeedAlarmConfig vSpeedAlarmAll[SDK_SPEED_ALARM_NR];
}SDK_SpeedAlarmConfigAll;

typedef struct SDK_CorrespondentOwnInfo
{
    char brand[64];
    char pModel[32];
    char pFirmwareVersion[32];
    char pHardwareId[32];
    int port;
	int scopeNum;
	char vScopeInfo[32][64];
}SDK_CorrespondentOwnInfo;

typedef struct SDK_OSDInfo
{
    int index;//����ͨ�������ʱ�����֮�������ȡֵ0��1
    int nX;//��Χ0-1000
    int nY;//��Χ0-1000
    int nChannel;//Ҫ���õ�ͨ��
    char pOSDStr[1024];//Ҫ���ӵ��ַ���
}SDK_OSDInfo;

typedef struct SDK_AppDownloadLink
{
    bool IOSEnable;    		//�Ƿ���ʾiphone�ͻ��˶�ά��
    bool AndroidEnable;		//�Ƿ���ʾ��׿�ͻ��˶�ά��
    bool SNEnable;    		//�Ƿ���ʾ���кŶ�Ӧ�Ķ�ά��
    bool OtherEnable;  		//�Ƿ���ʾ�ͻ��Զ����ά��
    char inkIOS[128];
    char linkAndroid[128];
    char nameOther[128];  	//�ͻ��Զ����ά������
    char linkOther[128];  	//�ͻ��Զ����ά��
}SDK_AppDownloadLink;

typedef struct SDK_UserMap
{
    int size;
    USER_INFO UserCfg[64];
}SDK_UserMap;

//�ϴ��������ݵ�ָ��������
typedef struct SDK_NetTransCommData
{
    bool bEnable;								///< �Ƿ���
    int SerialType;  							//�������ͣ�0��ʾRS232��1��ʾRS485
    int ServerType;								///Э����������,0��ʾTCP��1��ʾUDP
    char ServerAddr[NET_NAME_PASSWORD_LEN];  	//��������IP��ַ��
    int  ServerPort;							//�˿�;
	int ReportTime;								//״̬��Ϣ���ͼ��ʱ�䣬��λ����
}SDK_NetTransCommData;

//Netinfo_cctv�ͻ����Ӵ������ݵ�ָ������������
typedef struct SDK_NetinfoNetTransComm
{
	char LastReportTime[32];	//���һ�α���ʱ��
	char KeyPadNu[16];			//�豸���
	int ConnStatus;				//����״̬(1:���ӳɹ�0:δ����)
	int  ReportTime;			//״̬��Ϣ���ͼ��ʱ�䣬��λ����
} SDK_NetinfoNetTransComm;

typedef struct SDK_PhoneInfo
{
    char command[NET_NAME_PASSWORD_LEN];
    char type[12];
    char asid[128];
    char username[NET_NAME_PASSWORD_LEN];
    char password[NET_NAME_PASSWORD_LEN];
    char acme[NET_NAME_PASSWORD_LEN];
    char resume[24];
}SDK_PhoneInfo;

#define SDK_MAX_VERSION_NUM 20

typedef struct SDK_CloudUpgradeVersion
{
    char name[128];			// �汾��
    char date[12];			//�汾���ڣ���ʽ:"2014-08-26"
    unsigned int length;	// �����ļ�����
}SDK_CloudUpgradeVersion;

typedef struct SDK_CloudUpgradeList
{
    int num;
    SDK_CloudUpgradeVersion versions[SDK_MAX_VERSION_NUM];
}SDK_CloudUpgradeList;

//��ͻ�demo
typedef struct SDK_NetUseProgram
{
    bool bEnable;   							///�Ƿ���
    char UserName[NET_NAME_PASSWORD_LEN];		///< �û���
    char Password[NET_NAME_PASSWORD_LEN];		///< ����
    int Port;									///< �˿ں�
    char ServerAddr[NET_NAME_PASSWORD_LEN];  	///��������IP��ַ��
    char Describe[NET_MAX_RIGTH_NUM];			///�豸����
}SDK_NetUseProgram;

typedef struct I_VERSION_INFO_T
{
    char name[128];			// �汾��
    char date[12];			//�汾���ڣ���ʽ:"2014-08-26"
    unsigned int length;	// �����ļ�����
}I_VERSION_INFO_T;


//wifiģʽ������ã������г���¼���Զ��л�APģʽ
typedef struct SDK_NetWifiMode
{
    int autoSwitchAPMode; //ȡֵ  1:�Զ��л���APģʽ(����ģʽ)  0:���Զ��л�
    int reserve[7];
}SDK_NetWifiMode;

//�������Ʒ��¼��Ƶ�״̬
typedef struct SDK_FbExtraStateCtrl
{
    int ison;
}SDK_FbExtraStateCtrl;

typedef struct SDK_AutoSwitch
{
    int  nStartTime;
    int  nStopTime;
    int  nStartDay;
    int  nStopDay;
    bool bEnable;
}SDK_AutoSwitch;

typedef struct SDK_AutoSwitchAll
{
    SDK_AutoSwitch Aswitch[10];
}SDK_AutoSwitchAll;

typedef struct SDK_tagPoint
{
	int x;
	int y;
}SDK_Point;

typedef struct SDK_TitleDot
{
	int width;
	int height;
	char pDotBuf[NET_MAX_TITLE_DOT_BUF_LEN];
}SDK_TitleDot;

typedef struct SDK_PowerSocketSet
{
    int nSwitch;
    int nLight;
}SDK_PowerSocketSet;

typedef struct SDK_ClientInfo
{
    char Description[NET_NAME_PASSWORD_LEN];
    char Uuid[NET_NAME_PASSWORD_LEN];
    char Phone[NET_NAME_PASSWORD_LEN];
    char LoginTime[NET_NAME_PASSWORD_LEN];
    char Number[NET_NAME_PASSWORD_LEN];
    int  Permission;
    bool DeleThisClient;
    
}SDK_ClientInfo;

typedef struct SDK_ClientInfoAll
{
    SDK_ClientInfo info[10];
}SDK_ClientInfoAll;

typedef struct SDK_Authority
{
    int Level;
	int Ability;
}SDK_Authority;

typedef struct SDK_Arm
{
    int Guard;
}SDK_Arm;

typedef struct SDK_AlarmInfo_V2
{
    char Descrip[64];
    char SerialID[64];
    char Type[32];
    char iEvent[20];
    char iStatus[20];
    SDK_SYSTEM_TIME SysTime;
}SDK_AlarmInfo_V2;

/// �û���½��ʽ
typedef enum SDK_LoginType
{
    H264_DVR_LOGIN_TYPE_WEB,			///< WEB��½(Ĭ��)
    H264_DVR_LOGIN_TYPE_LOCALUPGRADE,	///< ��������(����������)��½
    H264_DVR_LOGIN_TYPE_CLOUDUPGRADE,	///< ��������½
    H264_DVR_LOGIN_TYPE_PCCLIENT,		///< PC�ͻ��˵�½
    H264_DVR_LOGIN_TYPE_MOBILE,			///< �ƶ��նˣ�IPhone����½
	H264_DVR_LOGIN_TYPE_FUTRUE_HOME,	///δ����ͥ�ͻ��˵�½
	H264_DVR_LOGIN_TYPE_XM030,			///xmeye�ͻ��˵�½
    H264_DVR_LOGIN_TYPE_NR,				///< ��½����
}SDK_LoginType;

typedef struct SDK_Xpms_Search_AlarmInfo_Req
{
    char Uuid[100];
    char authCode[100];
    SDK_SYSTEM_TIME StarTime;	//������Ϣ��ѯ��ʼʱ��
    SDK_SYSTEM_TIME EndTime;	//������Ϣ��ѯ����ʱ�䣬ȫ0��ʾ��ǰʱ��
    int Channel;				//Channel < 0 ��ʾȫ����ѯ��ͨ�����Ǵ�0��ʼ��
    int AlarmType;				//��������(��ʱ����)
    int Number;					//����Ҫ��ı������� ��Number <= 0 ��ʾ��ȫ��
    int Index;					//��Ҫ�Ӳ�ѯ�Ľ������һ����ʼȡ
    char Res[32];
}SDK_XPMS_SEARCH_ALARMINFO_REQ;


typedef struct SDK_Xpms_Search_AlarmPic_Req
{
    char Uuid[100];
    char authCode[100];
#ifdef WIN32
    __int64 ID;
#else
    long long ID;		//������ϢID��
#endif
    char Res[32];
}SDK_XPMS_SEARCH_ALARMPIC_REQ;

// ������̩��ƽ̨
typedef struct SDK_CONFIG_NET_BJHONGTAIHENG
{
    bool bEnable;
    char ServerUrl[64]; //��������ַ
    char DevID[16];     //�豸id
    char Password[16];  //�豸��֤��
    char DevModel[16];	//�豸�ͺ�
    char SerialNo[20]; 	//�豸���к�
}SDK_CONFIG_NET_BJHONGTAIHENG;

typedef enum
{
    SDK_LocalAlarm = (int)0x00001,
    SDK_MotionDetect = (int)0x00002,
}SDK_AlarmRecType;

//�ƴ洢������ؽṹ��
typedef struct SDK_CloudRecordConfig
{
    int EnableMsk;			//0ȫ���棬1�Ƕ�ʱ�棬2�����棬3��ʱ&& ����
    int StreamType;			//��������
    int AlarmRecTypeMsk;	//��Ҫ�ϴ�¼��ı������ͣ�AlarmRecType��������
    SDK_CONFIG_WORKSHEET wcWorkSheet;	//��ͨ¼����洢��ʱ���
}SDK_CloudRecordConfig;

typedef struct SDK_CloudRecordConfigAll
{
    SDK_CloudRecordConfig vRecordConfigAll[NET_MAX_CHANNUM];
}SDK_CloudRecordConfigAll;

// ���ж���
typedef struct SDK_PtzIdleState
{
    bool bEnable;		// ���ж���ʹ��λ
    int iTime;			// ����ʱ�� ��λ: ��
    int iIdleState;		// ���ж�������
    int iId;			// ��Ӧ���ж������͵Ķ������
}SDK_PtzIdleState;
typedef struct SDK_PtzIdleStateAll
{
    SDK_PtzIdleState pPtzIdleStateAll[NET_MAX_CHANNUM];
}SDK_PtzIdleStateAll;

typedef struct SDK_CameraClearFog
{
    bool enable; //0 �򿪣�1 ����
    int  level ; // ǿ�ȵȼ�[0,100]
    char rev[4];
}SDK_CameraClearFog;
typedef struct SDK_CameraClearFogAll
{
    SDK_CameraClearFog vCameraClearFogAll[NET_MAX_CHANNUM];
}SDK_CameraClearFogAll;
//������������
typedef struct SDK_CameraMotorCtrl
{
	bool UDDireOverturn;   //���·���ת
	bool LRDireOverturn;   //���ҷ���ת
	bool UDRestOverturn;   //������λ��ת
	bool LRRestOverturn;   //������λ��ת
	int  rev[8];
}SDK_CameraMotorCtrl;

typedef struct SDK_EncodeAddBeep
{
	int Enable;       //��1 ��Ƶ����ÿ��30��beep������0û�д˹��� 
	char res[4];
}SDK_EncodeAddBeep;

typedef struct SDK_DataLinkConfig
{
	int DoProgramEnable;
	int NIP2Enable;
}SDK_DataLinkConfig;
//��װλ��
typedef enum SDK_FISHEYE_APP_TYPE_E
{
	SDK_FISHEYE_APP_CEIL = 0, //�컨��
	SDK_FISHEYE_APP_TABL = 1, //����
	SDK_FISHEYE_APP_WALL = 2, //ǽ��
}SDK_FISHEYE_APP_TYPE_E;

//����ģʽ
typedef enum SDK_FISHEYE_SECENE_E
{
	SDK_FISHEYE_SECENE_ORIG	= 0,
	SDK_FISHEYE_SECENE_R = 1,
	SDK_FISHEYE_SECENE_P180_ALL = 2,
	SDK_FISHEYE_SECENE_P180_ONE = 3,
	SDK_FISHEYE_SECENE_P180_TWO = 4,
	SDK_FISHEYE_SECENE_P360_FULL = 5,
	SDK_FISHEYE_SECENE_P360_SEPE = 6,
	SDK_FISHEYE_SECENE_P360_HALF = 7,
	SDK_FISHEYE_SECENE_ROP_R = 8,
	SDK_FISHEYE_SECENE_RORR_R = 9,
	SDK_FISHEYE_SECENE_RRRR_R = 10,
	SDK_FISHEYE_SECENE_RRP_R = 11
}SDK_FISHEYE_SECENE_E;

//���۾�ͷ����ģʽ
typedef enum{
	FISHEYE_BULB_MODE_TIMING = 0,//��ʱģʽ
	FISHEYE_BULB_MODE_OPEN = 1,//�ֶ�ģʽ��
	FISHEYE_BULB_MODE_CLOSE = 2, //�ֶ�ģʽ��
	FISHEYE_BULB_MODE_NR,
}SDK_FISHEYE_BULB_MODE_E;

typedef struct SDK_FishEyeParam
{
	int appType;	//��ö��SDK_FISHEYE_APP_TYPE_E
	int secene;		//��ö��SDK_FISHEYE_SECENE_E
	int duty;		// �������� 0~100��
	char bulbWorkMode; //���ݹ���ģʽ����ö��SDK_FISHEYE_BULB_MODE_E
	char resv[3];
	SDK_TIMESECTION ligthOnSection; // �����Զ�����ʱ���
	unsigned int reserv[5];
}SDK_FishEyeParam;

//�Ƿ����OSD logo
typedef struct SDK_SetLogo
{
	int Enable;
	int	reserve[8];
}SDK_SetLogo;

typedef struct SDK_SparshHeartbeat
{
	bool bEnable;							///�Ƿ�����
	int  IntevalTime; 						///����ϱ�ʱ��
	char AlarmType[NET_NAME_PASSWORD_LEN];	///����
}SDK_SparshHeartbeat;
typedef struct SDK_SDevicesState
{
    int 	num;	  	//�豸����
    char uuid[32][32];	//���32�����к�
    int state[32];    	//0:�����ߣ�1:����
}SDK_SDevicesState;

typedef enum SDK_EncMode
{
	WIFI_ENC_OPEN = 0,
	WIFI_ENC_AES = 1,
	WIFI_ENC_TKIP = 2,
	WIFI_ENC_WEP =3
}SDK_EncMode;

typedef struct SDK_SWifiInfo
{
	char wifiSsid[64];
	char wifiPassword[64];
	char wifiMac[64];       // ��:�ָ��ʮ�������ַ���
	char wifiGateWay[64];   // ����
	char wifiSubmark[64];   // ��������
	char wifiDNS1[64];      // DNS1
	char wifiDNS2[64];      // DNS2
	int  wifiEncMode;       // ���ܷ�ʽ--EncMode
	char mobileIp[32];
	char mobileMac[32];
}SDK_SWifiInfo;

//�ͻ���nas��������
typedef struct SDK_SPVMN_NAS_SERVER
{
	char ServerIP[16];
	int Port;
	char RootDir[256];
	char DowloadIP[16];	
	char DowloadPath[256];
}SDK_SPVMN_NAS_SERVER;

//IE�������ȡ�����汾��Ϣ
typedef struct SDK_CloudUpgradeVersionReq
{
	char uuid[20];				//�豸���к�
	char  devID[32];			//�豸���͵�ID��
	char  curVersion[16];		//��ǰ�汾����
	char Language[32];			//��������
	char devType;				//����
	char expect;				//0��ʾ���°汾1��ʾ��ѯ��Ҫ�汾
	char		manual;			//1��ʾ�ֶ���ѯ��0��ʾ�Զ���ѯ
	char		rev;
}SDK_CloudUpgradeVersionReq;

//��˻ظ���IE�˻�ȡ�������汾��Ϣ
typedef struct SDK_CloudUpgradeVersionRep
{
	char FileName[128];			//�ļ�������������ʱ�������ֵ
	char DevID[32];				//�豸���͵�ID��
	char Date[16];				//�汾����
	int 		   FileSize;	//�����ļ��Ĵ�С
	int		  FileLevel;		//�汾��Ҫ�̶�
	char ChangeLog[512];		//change log,�ӵ�512�ֽ�,��־�����кܶ�
}SDK_CloudUpgradeVersionRep;

//web�˷��͸���˵�������������
typedef struct SDK_CloudUpgradeStartReq
{
	char uuid[20];				//�豸���к�
	char DevID[32];				//�豸����ID��
	char FileName[128];			//�����ļ���
	char Date[16];				//�汾����
	bool 	manual;				//1��ʾ�û��ֶ���������0��ʾ�Զ��������ֻ��˸�ֵһ�㴫1����
}SDK_CloudUpgradeStartReq;

//ipv6
typedef struct SDK_IPAddressV6
{
	bool bEnable;				//�Ƿ�����ipv6
	char pLocalLinkAddr[32];	//������·��ַ
	char pAddr[64];				//ipv6��ַ
	char pGateway[64];			//����
	int	iPrefix;  				//ipv6ǰ׺����
} SDK_IPAddressV6;

typedef struct SDK_OnlineUpgradeCfg
{
	char cEnable; 				//�Ƿ�����������������
	char pServerAddr[63];
	int  serverPort;
	char cAutoCheck;		//�Ƿ����Զ����
	char cAutoUpgradeImp;		//ֻ�Զ�������Ҫ����
	char cIgnoreAllVersion;		//�������а汾��ҳ����ʾ
	char cIgnoreCurVersion;		//���Ե�ǰ�汾��ҳ����ʾ�����ָ��µİ汾��Ҳֻ��ʾһ��
	unsigned int IgnoreCurTime;	//���Ե�ĵ�ǰ�汾��ʱ�䣬�� bIgnoreCurVersion����
	char cJustImpVersion;		//ֻ����Ҫ�汾��ʾ
	char rev[3];
} SDK_OnlineUpgradeCfg;

//���ò�Ʒ433��������������
typedef struct SDK_ConsSensorAlarmCfg
{
	bool bEnable;				// ��̬��⿪��  
	SDK_EventHandler hEvent;	// ��̬������� 
} SDK_ConsSensorAlarmCfg;

///<Ӳ�̳����¼��ṹ
typedef struct SDK_StorageFailConfig
{
	bool 	bEnable;
	SDK_EventHandler hEvent;	///< �������
	bool	bRebootEnable;		//ϵͳ����ȫ��:hutianhao
	int		bRebooted;			//�Ƿ���������;0:δ���������;��0:���������
	int		NoBitRateCnt;		//�������豸�Զ��������
}SDK_StorageFailConfig;

//CMS�ͻ��˶˷����Ļ���ָ�����
typedef struct SDK_SplitControl
{
	int iSplitChannel;//�ָ�ͨ��
	int iSplitWinType;//�ָ�����(��:��ͨ��)
	char rev[8];
}SDK_SplitControl;

typedef enum _SDK_EXCEPTION_TYPE
{
	SDK_EXCEPTION_DISCONNECTED,//�豸����
	SDK_EXCEPTION_RECCONNECTED,//�豸�ָ�����
}SDK_EXCEPTION_TYPE;

//�����豸�������Ϣ
typedef struct SDK_ReconInfo
{
	LPH264_DVR_DEVICEINFO deviceInfo; //���µ�¼����豸��Ϣ���л�ģʽ���豸ͨ������Ϣ���ܻ�䣨����ͨ��ģʽ�仯�ˣ�,���������ɹ���Ҫ���س�����
	void* pWnd;			//������Ƶʱͨ����Ӧ�Ĵ��ھ��
	int nType;			//��ö��SDK_EXCEPTION_TYPE
}SDK_ReconInfo;

//�����������豸�������Ϣ
typedef struct SDK_SubConnectInfo
{
	long lRealHandle;	//Ԥ����Ƶ�����ӶϿ���������Ƶ�ɹ��Ĳ��ž��
	bool bSubOnline;	//Ԥ����Ƶ�������Ƿ�������,true������������������
	void* pWnd;			//Ԥ����Ƶ�����ӶϿ���������Ƶʱͨ����Ӧ�Ĵ��ھ����bSubOnlineΪtrieʱ����H264_DVR_RealPlayʱ���봰�ھ��ʱpWnd����ֵ������ΪNULL
}SDK_SubConnectInfo;

typedef struct SDK_IntelBrasSpecialInfo
{
	int TCPPort;		///< TCP�����˿�
	char  bEnableCloud;	//interbras �ƹ���
	char rev2[3];
	int searchPort;		//�����˿ں�
	int vvMinPort;		//vv ����С�˿�
	int vvMaxPort;		//vv �����˿�
	int rev[14];
}SDK_IntelBrasSpecialInfo;

//sip �豸�忨��ַ
typedef struct SDK_SIP_NET_IP_CONFIG
{
	char	SIPDevIP[64]; 

}SDK_SIP_NET_IP_CONFIG;
typedef struct SDK_registersercfg
{
	bool enable;
	char serAddr[NET_NAME_PASSWORD_LEN];//PAG����
	int  port;
	int  factorycode;//���̴���
	char userName[NET_NAME_PASSWORD_LEN];
	char passwd[NET_NAME_PASSWORD_LEN];
	char puid[NET_NAME_PASSWORD_LEN];//�豸id
	char mainid[NET_NAME_PASSWORD_LEN];//��id
	int TaskID;//�洢���
	int TaskName;//�洢���
	char MainRecordPath[256];//���õ�ַ
	char BakRecordPath[256];//���õ�ַ
	int FileMode;//�ļ������ʽ   0����ʱ����1������С
	int FileLength;//�ļ�ֵ10��FileModeΪ0��ʾ10���ӣ�Ϊ1ʱ��ʾ10M
	int VideoTransMode;//ʵʱ������Ƶ��ģʽ��ʵʱ��Ƶ����ģʽ��(0-UDP ,1-TCP)
	char Reserved[NET_NAME_PASSWORD_LEN];
}SDK_GbEyesCfg;

//AHDLͨ�����룬��ͨ��ΪAHDL��1
typedef struct SDK_AHDEncodeLMask
{
	char AHDLMask[NET_MAX_MSK_SIZE];
}SDK_AHDEncodeLMask;

typedef struct SDK_PortService
{
	BOOL Enable;		///< �Ƿ���
	int port;
}SDK_PortService;

/// Ĭ����Ӧ����ʽ
typedef struct SDK_DefaultResponse
{
	unsigned int uiSessionId;		///< �ỰID
	int iRet;				///< ����ֵ
	char sName[64];		///< ��������
}SDK_DefaultResponse;

typedef enum SDK_CloudRecType
{
	SDK_TimeRec = (int)0x00001,
	SDK_AlarmRec = (int)0x00002,
}SDK_CloudRecType;

//���۾�ͷ����ö��
typedef enum SDK_E_FISH_LENS_TYPE
{
	SDK_FISH_LENS_NORMAL,  //��ͨ��ͷ������app����ͼ��У��
	SDK_FISH_LENS_360VR,
	SDK_FISH_LENS_360LVR,
	SDK_FISH_LENS_180VR,
	SDK_FISH_LENS_DUAL_360VR,
	SDK_FISH_LENS_DUAL_180VR,
	SDK_FISH_LENS_NR,
}SDK_E_FISH_LENS_TYPE;

//���۾�ͷ���ò���
typedef struct SDK_FishLensParam
{
	char  version;		 //�ṹ��İ汾��(����޸�����ĳ�Ա����app��Ҫ�����ϳ���ֿ�����ʱ������Ҫ����չ�����������ù����еİ汾�ż�1�����޸��豸�ϵ�Ĭ������)
	char  lensType;      //��ͷ���ͣ���ö��SDK_E_FISH_LENS_TYPE
	short centerOffsetX; //Բ��ƫ�������  ��λ:���ص�
	short centerOffsetY; //Բ��ƫ��������  ��λ:���ص�
	short radius;        //�뾶  ��λ:���ص�
	short imageWidth;    //Բ��У��ʱ��ͼ����  ��λ:���ص�
	short imageHeight;	 //Բ��У��ʱ��ͼ��߶�  ��λ:���ص�
	char  viewAngle;	 //�ӽ�  0:����   1:ƽ��
	char  viewMode;		 //��ʾģʽ   0:360VR
	short zoom;			 //���ű�����Ϊ�˴��䷽�㣬���ｫԭֵ�Ŵ���100��
	char  resv[8];	
} SDK_FishLensParam;

//����ͨ�������۾�ͷ��������
typedef struct SDK_FishLensParamAll
{
	SDK_FishLensParam vLensParamAll[NET_MAX_CHANNUM];
}SDK_FishLensParamAll;

//��̨���õĿ��Ʒ�ʽ����
typedef enum SDK_PTZ_CTRL_TYPE
{
	PTZ_CTRL_COAX = 0,//ͨ��ͬ����
	PTZ_CTRL_RS485,   //ͨ��485��
	PTZ_CTRL_BOTH,    //ͬ���ߺ�485�߶����Ϳ�������
}SDK_PTZ_CTRL_TYPE;

typedef struct SDK_PTZControlMode
{
	int ctrlMode;			//��̨���Ƶķ�ʽ��PTZ_CTRL_TYPE ����ö��ֵ��
} SDK_PTZControlMode;

typedef struct SDK_PTZControlModeAll
{
	SDK_PTZControlMode CtrlModeAll[NET_MAX_CHANNUM];
}SDK_PTZControlModeAll;

typedef struct SDK_SmartH264Param
{
	bool SmartH264;
}SDK_SmartH264Param;

typedef struct SDK_SmartH264ParamAll
{
	 SDK_SmartH264Param SmartH264All[NET_MAX_CHANNUM];
}SDK_SmartH264ParamAll;

typedef struct SDK_WifiInfo
{
	char ssid[32];			//����SSID��Ϣ
	char wifiVersion[32];	//����ģ��İ汾��Ϣ
	int advance;			//������ǿģʽ
}SDK_WifiInfo;

typedef struct SDK_NetRTMPConfig
{
	bool bEnable;			//�Ƿ���
	char Directory[NET_MAX_PATH_LENGTH];	//RTMP�ĵ�ַ
}SDK_NetRTMPConfig;

///< �����ץͼ
struct SDK_IntervalSnapMode
{
	int iFTPTime;
	int iEmailTime;
	int iStorageTime;
};
///< ����ʱץͼ
struct SDK_TriggerSnapMode
{
	SDK_SYSTEM_TIME TriggerTime;
	bool bFTP;
	bool bEmail;
	bool bStorage;
};
///< ץͼ�ƻ�
struct SDK_SnapSchedule
{
	int iSnapType;			// 0:���ץͼ��1:��ʱץͼ 2:�ر�
	int iTriggerNum;		//��ʱץͼ�ĸ���
	SDK_IntervalSnapMode intervalMode;
	SDK_TriggerSnapMode vTriggerMode[256];
};

//����ͨ���ļƻ�ץͼ����
struct SDK_SnapConfigAll
{
	SDK_SnapSchedule vSnapScheduleAll[NET_MAX_CHANNUM];
};
// ����ͼ
struct SDK_BreviaryConfig
{
	bool bBreviaryEn;		//����ͼʹ��
	int  iBreviaryInteSec;	//����ͼץͼ���ʱ��
};
//Ԥ�õ���������
struct SDK_PtzPreset
{
	int nPresetId[256];
};
//����ͨ����Ԥ�õ���������
struct SDK_PtzPresetAll
{
	SDK_PtzPreset nPresetAll[NET_MAX_CHANNUM];
};

//Ԥ�õ����������
struct SDK_PtzTour_Preset
{
	int nPresetId;		//Ԥ�õ�Id
	int nPresetTime;	//���ʱ��
};
//Ѳ��·�ߵ���������
struct SDK_PtzTour 
{
	int nTourId;		//��·Id
	SDK_PtzTour_Preset nTourNum[20];	//��Ӧ������Ԥ�õ��ʱ����
};
//����Ѳ������������
struct SDK_PtzTours
{
	SDK_PtzTour nPtzTours[20];
};
//����ͨ��Ѳ������������
struct SDK_PtzTourAll
{
	SDK_PtzTours vPtzTour[NET_MAX_CHANNUM];
};

//��ȫ��������
struct SDK_PwdPresetQsPair 
{
	int questionIndex;				//�������
	char strAnswer[256];			//��
};
struct SDK_PasswordSafety 
{
	bool bTipPageHide;					//�Ƿ���������Ϊ��ʱ����ʾҳ��
	SDK_PwdPresetQsPair PwdResetQs[4];	//��ȫ����ʹ�
	char resv[20];
};

//��ȡ�һ����������
struct SDK_QuestionDelivery
{
	int  nStrNum;		//�������
	char vQuestionStr[7][256];
};
struct SDK_TutkVersion
{
	char Product[32];	//�豸�ͺ�
	int  version;		//�豸�汾
};

///< ���ڱ���
typedef struct SDK_SerialPortAlarm
{
	bool bEnable;				///< ʹ��
	int		iSensorType;		///< ���������ͳ��� or ����
	SDK_EventHandler hEvent;	///< �������
}SDK_SerialPortAlarm;

/// ����ͨ���Ĵ��ڱ����ṹ
typedef struct SDK_SerialPortAlarm_ALL
{
	SDK_SerialPortAlarm vSerialAlarmConfig[NET_MAX_CHANNUM];
}SDK_SerialPortAlarm_ALL;

/// �ͻ�����ѧ�빦��
typedef struct SDK_AMIRLearnCode
{
	int iValue;
}SDK_AMIRLearnCode;

///�����ȡ����ͼ
typedef struct SDK_NetBreviaryPic
{
	int iChannel;  //ͨ����
	int iNumJpg; //�����ȡ��ͼƬ��
	SDK_SYSTEM_TIME startTime;
	SDK_SYSTEM_TIME endTime;
}SDK_NetBreviaryPic;

///�ڼκ�ViscaЭ���޸ģ����úͻ�ȡ���ʽ����
enum SDK_CameraViscaCommand
{
	SDK_SET_CAM_ZOOM,		//���ñ���
	SDK_SET_CAM_FOCUS,		//���ý���
	SDK_SET_CAM_ZOOM_FOCUS,	//���ñ��ʺͽ���
	SDK_GET_CAM_ZOOM,		//��ȡ����
	SDK_GET_CAM_FOCUS,		//��ȡ����
};

//�ڼκ�ViscaЭ���޸ģ����úͻ�ȡ���ʽ����
typedef struct SDK_CameraViscaControl
{
	int iChannel;		//ͨ����
	int iCommand;		//����,ö�� SDK_CameraViscaCommand
	int iCameraZoom;	//����
	int iCameraFocus;	//����
}SDK_CameraViscaControl;

typedef struct SDK_PIRConfig
{
	bool	bEnable;		///< PIRʹ�ܿ���
	int		iLevel;			///< ����ȣ�1��6
	SDK_EventHandler hEvent;///< PIR��������
}SDK_PIRConfig;

/// ȫͨ��PIR����,ģ��ͨ����֧��
typedef struct SDK_PIRConfigAll
{
	SDK_PIRConfig vPIRAll[NET_MAX_CHANNUM];
}SDK_PIRConfigAll;

//���ܻطŶ�λ������,��������:1010��>IPC��������=1,��������=0,���籨��=1,���ر���=0
enum SDK_PLAY_BACK_SETTYPE
{
	F_SUB_COMMON,
	F_SUB_LOCALALARM, 	///< ���ر���
	F_SUB_NETALARM, 	///< ���籨��
	F_SUB_NETABORT, 	///< ��������
	F_SUB_IPCALARM, 	///< IPC����
	F_SUB_SPEEDALARM, 	///< ���ٱ���
	F_SUB_GSENSORALARM, ///< SENSOR����
	F_SUB_SERIALALARM, 	///< ���ڱ���
	F_SUB_MOTIONDETECT, ///< �ƶ����
	F_SUB_LOSSDETECT, 	///< ��Ƶ��ʧ
	F_SUB_BLINDDETECT, 	///< ��Ƶ�ڵ�
	F_SUB_PIRALARM, 	///< ������
	F_SUB_CARDNUMBER, 	///< ����¼��
	F_SUB_PERIMETER, 	///< �ܽ���
	F_SUB_TRIPWIRE,		///< �����߼��
	F_SUB_ABANDUM, 		///< ��Ʒ����
	F_SUB_STOLEN, 		///< ��Ʒ����
	F_SUB_CHANGE, 		///< �����任
	F_SUB_NR,
};

//DDNSʵʱ״̬
typedef struct SDK_NetDDNSInConfig
{
	char IP[32];
	int state;      //state 0 ��ʾδ���� 1��ʾ���ӳɹ�
	char resv[8];
}SDK_NetDDNSInConfig;

//�����ӥ���ư汾��Ϣ
typedef struct SDK_THXY_VersionInfo
{
	char productType[64];	//��Ʒ�ͺ�
	char serialNo[64];		//�豸���к�
	char ManuDate[64];		//��������
	char VersionNum[64];	//�汾��
	char buildDate[64];		//�汾����
	char hardVersion[64];	//�̼��汾
	int chnNum;				//ͨ����
	int handDiskNum;		//Ӳ����
	int alarmIn;			//��������
	int alarmOut;			//�������
	int	reserve[32];
}SDK_THXY_VersionInfo;

//ģ����ⱨ��
typedef struct SDK_BlurCheckAlarm
{
	bool bEnable;			//true:����,false:�ر�
	int	 iLevel;			//����ȣ�1��6
	int  iCheckFrequency;	//���Ƶ�ʣ���λ:����
	SDK_EventHandler hEvent;//ģ�������������
}SDK_BlurCheckAlarm;

//ȫͨ��ģ����ⱨ��
typedef struct SDK_BlurCheckAlarmAll
{
	SDK_BlurCheckAlarm vBlurCheckAlarm[NET_MAX_CHANNUM];
}SDK_BlurCheckAlarmAll;

typedef struct SDK_IntelEnCodeCfg
{
	bool bEnable;			//�ӿ�ʹ�����ٱ�־
	int highQP;				//���屳����QPֵ
	int lowQP;				//ǰ����QPֵ
	int highFPS;			//����fps
	int lowFPS;				//ǰ��fps
	int Channel;			//�����������ͣ�0����1��
}SDK_IntelEnCodeCfg;

//���ܱ���
typedef struct SDK_IntelEnCodeCfgAll
{
	SDK_IntelEnCodeCfg vEncodeCfg[NET_MAX_CHANNUM];
}SDK_IntelEnCodeCfgAll;

typedef struct SDK_PlateDetectWhiteList
{
	int iAddrCount;					//���Ƹ���
	char vWhiteListAddr[256][256]; // ���ư�������ַ
}SDK_PlateDetectWhiteList;

//������������˿���
typedef struct SDK_PlateDetectLiftBar
{
	bool bLiftBarCmd;
	int	iChannel;
}SDK_PlateDetectLiftBar;

//�����ص�����
enum {
	ALARM_TYPE = 1,
	PUSH_TYPE,
};

enum SDK_INTEL_PUSH_TYPE
{
	SDK_INTEL_PUSH_TYPE_CAR_PLATE = 0,	//��ʾ��������
	SDK_INTEL_PUSH_TYPE_FACE      = 1,	//��ʾ��������
	SDK_INTEL_PUSH_TYPE_ALL       = 255,//��ʾȫ������
};
enum SDK_INTEL_PUSH_IMG_TYPE
{
	SDK_INTEL_PUSH_IMG_TYPE_FULL   = 1,	//��ʾֻҪ��ͼ
	SDK_INTEL_PUSH_IMG_TYPE_TARGET = 2,	//��ʾֻҪСͼ
	SDK_INTEL_PUSH_IMG_TYPE_NR			//��ʾ����ͼ��Ҫ
};

//��������
typedef struct SDK_RECT_S
{
	int leftX;
	int topY;
	int width;
	int height;
} SDK_RECT_S;

typedef struct SDK_PLATE_DETECT
{
	char acPlateCode[20];	//���ƺ��룬β�����ַ���������"\0" 
	char acPlateColor[4];	//������ɫ�������ڰ׻�"��"����δ֪���ַ���������"\0"���ַ������ʽΪ
}SDK_PLATE_DETECT;

typedef struct SDK_FACE_DETECT
{
	char sex;//�Ա�
	char age;//����
	char resv[20];
}SDK_FACE_DETECT;

typedef struct SDK_IA_LPR_TARGET_INFO
{
	SDK_RECT_S stRect;
	union
	{
		SDK_FACE_DETECT face;
		SDK_PLATE_DETECT plate;
	}DETECT;
	char resv[16];
}SDK_IA_LPR_TARGET_INFO;

typedef struct SDK_IA_LPR_REC_S
{
	unsigned short resultType; //ʶ����������  0:����  1:����ʶ��  
	unsigned short picSubType; //0:��ͼ  1:Сͼ
	unsigned short picFormat;  //0:jpg  1:bmp   2:yuv
	unsigned short tagNum;		//Ŀ�����
	SDK_IA_LPR_TARGET_INFO pTargetInfo[8]; //���֧��8��Ŀ��
	char resv[32];
}SDK_IA_LPR_REC_S;

typedef struct SDK_PushRetData
{
	SDK_IA_LPR_REC_S iaLprRecs;	//
	int nChannel;				//ͨ����
	int nLenSize;				//ͼƬ��С
	unsigned char* pBuffer;		//ͼƬ����
}SDK_PushRetData;

typedef struct SDK_PlateDetectCfg
{
	int iDefaultL;//Ĭ����ĸ������"A" 
	int iDefaultP;// Ĭ�Ϻ��֣�����"��" ,����gb2312����
	int resv;
	SDK_RECT_S astLpRect[7];
	int iMaxWidth;
	int iMinWidth;
}SDK_PlateDetectCfg;

//���Ƽ��
typedef struct SDK_PlateDetect
{
	bool	bEnable;				//true:����,false:�ر�
	SDK_PlateDetectCfg stPlateParam;//���Ƽ���������
	SDK_EventHandler hEvent;			//���Ƽ����������
}SDK_PlateDetect;

//ȫͨ�����Ƽ��
typedef struct SDK_PlateDetectAll
{
	SDK_PlateDetect vPlateDetect[NET_MAX_CHANNUM];
}SDK_PlateDetectAll;

//������ؽṹ�壺
typedef struct SDK_FaceRect
{
	int s32X;
	int s32Y;
	int u32Width;
	int u32Height;
}SDK_FaceRect;

//�������
typedef struct SDK_FaceDetect
{
	bool	bEnable;			//true:����,false:�ر�
	SDK_FaceRect stFaceParam;	//��������������
	SDK_EventHandler hEvent;	//���������������
}SDK_FaceDetect;

//ȫͨ���������
typedef struct SDK_FaceDetectAll
{
	SDK_FaceDetect vFaceDetect[NET_MAX_CHANNUM];
}SDK_FaceDetectAll;

//ipc onvif����ʱ�Զ��޸�ipΪ������ip
typedef struct SDK_IPAdaptiveCfg
{
	bool bIPAdaptive;	//IP����Ӧ����
}SDK_IPAdaptiveCfg;

//��ѯ��������
typedef struct SDK_SearchCalendar
{
	int year;
	int month;
	int nFileType;			//�ļ�����, ��SDK_File_Type
}SDK_SearchCalendar;

//һ��������Щ���з���Ҫ���¼���ͼƬ
typedef struct SDK_SearchCalendarMask
{
	int mask;		//ÿλ����һ��ӵ�λ��ʼ��1:��¼��, 0:��¼��
}SDK_SearchCalendarMask;

typedef struct SDK_HardDiskInfo{
	bool	bIsCurrent;					///< �Ƿ�Ϊ��ǰ������
	unsigned int	uiTotalSpace;		///< ��������MBΪ��λ
	unsigned int	uiRemainSpace;		///< ʣ��������MBΪ��λ
}SDK_HardDiskInfo;

typedef struct SDK_OemGetInfo
{
	int iConnectNum;					//������
	int iDisk;							//Ӳ�̸���
	SDK_HardDiskInfo cHardDisk[SDK_MAX_DISK_PER_MACHINE];//Ӳ��ʣ������
	char cRecordState[NET_MAX_CHANNUM];	//¼��״̬
	char cVersion[64];					//�汾��Ϣ
}SDK_OemGetInfo;

typedef enum {
	DEV_TYPE3_DOOR_CONTACT = 0,		//�Ŵ�
	DEV_TYPE3_INFRA = 1,			//����
	DEV_TYPE3_SHOCK = 2,			//��
	DEV_TYPE3_BROKEN_GLASS = 3,		//����
	DEV_TYPE3_SMOKE_SENSOR = 4,		//�̸�
	DEV_TYPE3_GAS_SENSOR = 5,		//����
	DEV_TYPE3_WATER_SENSOR = 6,		//©ˮ
	DEV_TYPE3_REMOTE_CONTROL = 7,	//ң����
	DEV_TYPE3_ENVIRO_SENSOR = 8,	//�¶�
	DEV_TYPE3_NR,					//����
}SDK_DEVICE_TYPE3;
//433�������Ʒ��ӵı����豸
typedef struct SDK_ConsumerAlarm433Dev
{
	int  nChannel;			//ͨ��
	char pDevID[16];		//�����豸ID������ң����ID
	char pDevName[32];		//�����豸�ǳ�
	int  pDevType;			//�����豸����--��ö��SDK_DEVICE_TYPE3
	bool bEnable;			//��̬��⿪��  
	SDK_EventHandler hEvent;//��̬������� 
}SDK_ConsumerAlarm433Dev;
typedef struct SDK_ConsumerAlarm433DevList
{
	SDK_ConsumerAlarm433Dev vAlarm433DevList[32];	//IPC���ӵĴ���������	
}SDK_ConsumerAlarm433DevList;

enum SDK_ConsumerProCmd 
{
	CONSUMER_PRO_ADD_DEV = 0,			///< ��ӱ����豸
	CONSUMER_PRO_STOP_ADD_DEV = 1,		///< ֹͣ��ӱ����豸
	CONSUMER_PRO_DEL_DEV = 2,			///< ɾ���Ѿ���ӵı����豸
	CONSUMER_PRO_CHANGE_DEV_NAME = 3,	///< �޸��Ѿ�����豸������
	CONSUMER_PRO_INQUIRY_STATUS = 4,	///< ��ȡ�������ĵ�����״̬
	//CONSUMER_PRO_INQUIRY_INFO = 5,	///< ��ѯ�豸��Ϣ
	CONSUMER_PRO_GET_DEV_LIST = 5,		///< ��ȡ�豸�б�
	CONSUMER_PRO_CHANGE_DEV_STATUS = 6,	///< �޸Ĵ�������״̬ open or close
	CONSUMER_PRO_GET_DEVLIST_STATUS = 7,///< ��ȡ�Ѿ����ߵ��豸�б�
	CONSUMER_PRO_CHANGE_MODE = 8,		///< �л�����ģʽ
	CONSUMER_PRO_GET_MODE_CFG = 9,		///< ��ȡ��Ӧģʽ��״̬
	CONSUMER_PRO_GET_MODE_LIST = 10,	///< ��ȡģʽ�б�
	CONSUMER_PRO_CHANGE_MODE_NAME = 11,	///< �޸�ģʽ����
	CONSUMER_PRO_GET_LINK_STATE = 12,	///< �ж��豸�Ƿ�����
	CONSUMER_PRO_NR						///< �������
};

typedef struct SDK_ConsumerProOpr
{
	int  cmd;		//��ö��SDK_ConsumerProCmd
	char pArg1[20]; //�豸������--SDK_DEVICE_TYPE3
	char pArg2[32]; //�豸����
	int  Channel;	//��Ӧ���豸ͨ��
	char res[8];
}SDK_ConsumerProOpr;

//����ipc���ܵ�����У��
typedef struct SDK_IpcOnvifPwdCheckout
{
	bool cEnable;
}SDK_IpcOnvifPwdCheckout;

// �����ϴ�ͨ���ص�����ԭ��
typedef void (CALL_METHOD *fUploadDataCallBack) (long lLoginID, long UploadType, char *pBuffer, unsigned long dwBufSize, unsigned long dwUser);

// ͸�����ڻص�����ԭ��
typedef void (CALL_METHOD *fTransComCallBack) (long lLoginID, long lTransComType, char *pBuffer, unsigned long dwBufSize, unsigned long dwUser);
//�������Ͽ��ص�ԭ��
typedef void (CALL_METHOD *fDisConnect)(long lLoginID, char *pchDVRIP, long nDVRPort, unsigned long dwUser);
//ԭʼ���ݻص�ԭ��
typedef int(CALL_METHOD *fRealDataCallBack) (long lRealHandle, long dwDataType, unsigned char *pBuffer,long lbufsize,long dwUser);
typedef int(CALL_METHOD *fRealDataCallBack_V2) (long lRealHandle, const PACKET_INFO_EX *pFrame, void* dwUser);

// �ط�¼����Ȼص�ԭ��
typedef void(CALL_METHOD *fDownLoadPosCallBack) (long lPlayHandle, long lTotalSize, long lDownLoadSize, long dwUser);

//��Ϣ������,����ע�ᣩ�ص�ԭ��
/*
	1.����,pBuf˵��--ntype = ALARM_TYPE
	SDK_AlarmInfo alarmInfo;
	memcpy ( &alarmInfo, pBuf, dwBufLen );
	2.����ע��,pBuf˵��,
	H264_DVR_ACTIVEREG_INFO activeInfo;
	memcpy ( &activeInfo, pBuf, dwBufLen );
	3.ͼƬ����,pBuf˵��--nType=PUSH_TYPE
	SDK_PushRetData PushDetect;
	memcpy(&PushDetect, pBuf, sizeof(SDK_PushRetData));
	
*/
typedef bool (CALL_METHOD *fMessCallBack)(long lLoginID, char *pBuf, unsigned long dwBufLen, long dwUser, int nType);

//�����豸����ص�ԭ��
/*
	nSendSize = -1 ˵���������  
	nSendSize = -2 ˵����������
	nTotalSize = -1ʱ, nSendSize:1-99������������ 
	nTotalSize =0ʱ,nSendSize = H264_DVR_NOENOUGH_MEMORY-H264_DVR_INVALID_WIFI_DRIVE �������������
	�������Ƿ��ͽ���
	��������������һ��:nTotalSize=-2ʱ��nSendSize:0 - 100=���ؽ���,û�з��ͽ���
*/
typedef void(CALL_METHOD *fUpgradeCallBack) (long lLoginID, long lUpgradechannel,
                                             int nTotalSize, int nSendSize, long dwUser);


// ����Խ�����Ƶ���ݻص�����ԭ��
typedef void (CALL_METHOD *pfAudioDataCallBack)(long lVoiceHandle, char *pDataBuf,
                                                long dwBufSize, char byAudioFlag, long dwUser);


//���ز��Ž����ص�ԭ��
typedef void (CALL_METHOD * fLocalPlayFileCallBack)(long lPlayHand, long nUser);

//��Ϣ֡�ص�����
typedef void (CALL_METHOD  *InfoFramCallBack)(long lPlayHand, long nType, LPCSTR pBuf,long nSize, long nUser);

//�����Ӷ��߻ص�
typedef void (CALL_METHOD *fSubDisConnectCallBack)(long lLoginID, SubConnType type, long nChannel, long dwUser);

#ifdef WIN32
//RigisterDraw�ص�ԭ��
typedef void (CALL_METHOD * fPlayDrawCallBack)(long lPlayHand,HDC hDc,long nUser);
#else//linuxû�õ�����ص�
typedef void (CALL_METHOD * fPlayDrawCallBack)(long lPlayHand,void* hDc,long nUser);
#endif // WIN32

/*
	����:SDK��ʼ��
	����:
		cbDisConnect[out]:���߻ص�����
		dwUser[in]:�ص���������
	����ֵ:
		=1: �ɹ�
		<=0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_Init(fDisConnect cbDisConnect, unsigned long dwUser);

/*
	����:SDK�˳�����
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_Cleanup();

/*
	����:��ȡ������Ϣ
	����ֵ:
		������	
*/
H264_DVR_API long CALL_METHOD H264_DVR_GetLastError();

/*
	����:���õ�¼�豸��ʱʱ��ͳ��Դ���
	����:	
		nWaitTime[in]:��λms������ʱĬ��5000ms,
		nTryTimes[in]:����,������ʱĬ��3��
*/

H264_DVR_API bool CALL_METHOD H264_DVR_SetConnectTime(long nWaitTime, long nTryTimes);

/*
	����:��½�豸
	����:
		sDVRIP[in]:		  ip
		wDVRPort[in]:	  �˿�
		sUserName[in]:    �û���
		sPassword[in]:    ����
		lpDeviceInfo[out]:�����豸��Ϣ
		error[out]:		  ���ص�½������
		socketType[in]:	  ��½��ʽ
	����ֵ:
		>0:	   �ɹ�,��1��ʼ��n,ÿ�ε�¼һ̨�豸����ֵ+1
		=0:	   ʧ��
*/
H264_DVR_API long64 CALL_METHOD H264_DVR_Login(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
                                             LPH264_DVR_DEVICEINFO lpDeviceInfo, int *error,int socketType DEF_PARAM(0));

/*
	����:��½�豸��չ�ӿ�
	����:
		sDVRIP[in]:		  ip
		wDVRPort[in]:	  �˿�
		sUserName[in]:    �û���
		sPassword[in]:    ����
		lpDeviceInfo[out]:�����豸��Ϣ
		nType[in]:		  ��½����,0==web 1 ==�������� 2 == ��������  102 == �ⲿ���ܣ��ڲ��Ͳ��ü�����
		error[out]:		  ���ص�½������
	����ֵ:
		>0:	   �ɹ�
		=0:	   ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_LoginEx(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
							   LPH264_DVR_DEVICEINFO lpDeviceInfo, int nType, int *error);

/*
	����:��½�ӿ�V2�汾,����ָ���ͻ������͵�½
	����:
		sDVRIP[in]:		  ip
		wDVRPort[in]:	  �˿�
		sUserName[in]:    �û���
		sPassword[in]:    ����
		lpDeviceInfo[out]:�����豸��Ϣ
		nType[in]:		  ��½���ͣ���enum SDK_LoginType
		error[out]:		  ���ص�½������
		socketType[in]:	  ��½��ʽ
	����ֵ:
		>0:	   �ɹ�
		=0:	   ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_LoginEx_V2(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
												  LPH264_DVR_DEVICEINFO lpDeviceInfo, int nType, int *error,int socketType);
/*
	����:�ͻ��Ƶ�½�ӿ�
	����:
		sDVRIP[in]:		  �豸���к�
		wDVRPort[in]:	  �˿�
		sUserName[in]:    �û���
		sPassword[in]:    ����
		lpDeviceInfo[out]:�����豸��Ϣ
		error[out]:		  ���ص�½������
		uuid[in]:		  uuid
	����ֵ:
		>0:    �ɹ�
		=0:	   ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_Login_Cloud(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
												   LPH264_DVR_DEVICEINFO lpDeviceInfo, int *error,char* uuid);
/*
	����:���豸ע�����ǳ��豸
	����:
		lLoginID[in]:��½���
	����ֵ:
		=1:�ɹ�
		=0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_Logout(long lLoginID);

/*
	����:���ý���DVR��Ϣ�ص�, ���籨����Ϣ,��ID������
	����:
		cbAlarmcallback[out]:�ص�����
		lUser[in]:			 �ص���������
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_SetDVRMessCallBack(fMessCallBack cbAlarmcallback, unsigned long lUser);

/*
	����:���������ϴ�ͨ��
	����:
		lLoginID[in]:��½���
	����ֵ:
		=1:�ɹ�
		=0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_SetupAlarmChan(long lLoginID);

/*
	����:�رձ����ϱ�
	����:
		lLoginID[in]:��½���
	����ֵ:
		=1:�ɹ�
		=0:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_CloseAlarmChan(long lLoginID);

/*
	����:Զ�̻�ȡ���ò���
	����:
		lLoginID[in]:	     ��½���
		dwCommand[in]:		 ��������,��enum SDK_CONFIG_TYPE
		nChannelNO[in]:		 -1����ȫͨ��,0-n������ͨ��
		lpOutBuffer[out]:	 ���ջ���
		dwOutBufferSize[in]: ���ջ����С
		lpBytesReturned[out]:���ص����ݴ�С
		waittime[in]:		 �ȴ�ʱ�� 
	����ֵ:
		=1:�ɹ�
		<0:ʧ��
*/
H264_DVR_API long  CALL_METHOD H264_DVR_GetDevConfig(long lLoginID, unsigned long dwCommand, int nChannelNO, char * lpOutBuffer, unsigned long dwOutBufferSize, unsigned long* lpBytesReturned,int waittime DEF_PARAM(1000));

/*
	����:Զ���������ò���
	����:
		lLoginID[in]:	     ��½���
		dwCommand[in]:		 ��������,��enum SDK_CONFIG_TYPE
		nChannelNO[in]:		 -1����ȫͨ��,0-n������ͨ��
		lpInBuffer[out]:	 ���뻺��
		dwInBufferSize[in]:  ���뻺���С
		waittime[in]:		 �ȴ�ʱ�� 
	����ֵ:
		=1:�ɹ�
		<0:ʧ��
*/
H264_DVR_API long  CALL_METHOD H264_DVR_SetDevConfig(long lLoginID, unsigned long dwCommand, int nChannelNO, char * lpInBuffer, unsigned long dwInBufferSize, int waittime DEF_PARAM(1000));

/*
	����:�����������豸���ã�Ŀǰֻ֧�ֶ��������ý������� 
	����:
		dwCommand[in]:	   E_SDK_CONFIG_SYSNET
		nChannelNO[in]:	   1��ʱ����,����Ϊ���ñ���
		lpInBuffer[in]:	   SDK_CONFIG_NET_COMMON_V3�ṹ���ַ
		dwInBufferSize[in]:sizeof(SDK_CONFIG_NET_COMMON_V3)
		waittime[in]:	   �ȴ�ʱ��
	����ֵ:
		=0:�ɹ�
		<0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_SetConfigOverNet(unsigned long dwCommand, int nChannelNO, char * lpInBuffer, unsigned long dwInBufferSize, int waittime DEF_PARAM(1000));

/*
	����:��־��ѯ
	����:
		lLoginID[in]:��½���
		pFindParam[in]:��ѯ����
		pRetBuffer[out]:��־������Ϣ
		lBufSize[in]:������־��Ϣ��С
		waittime:�ȴ�ʱ��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_FindDVRLog(long lLoginID, SDK_LogSearchCondition *pFindParam, SDK_LogList *pRetBuffer, long lBufSize, int waittime DEF_PARAM(2000));

/*
	����:��ʵʱԤ��
	����:
		lLoginID[in]:	 ��½���
		lpClientInfo[in]:������Ϣ
	����ֵ:
		>0��<0:�ɹ���Ԥ�����ž��
		=0:ʧ��,�������ֵĴ������������-11202���ĵ�
*/
H264_DVR_API long CALL_METHOD H264_DVR_RealPlay(long lLoginID, LPH264_DVR_CLIENTINFO lpClientInfo);

/*
	����:ֹͣʵʱԤ��
	����:
		lRealHandle[in]: Ԥ�����ž��
		lpClientInfo[in]:������Ϣ
	����ֵ:
		>0��<0:�ɹ�
		=0:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_StopRealPlay(long lRealHandle,void*hWnd DEF_PARAM(0));

/*
	����:����ʵʱԤ��
	����:
		lRealHandle[in]:Ԥ�����ž��
		bPause[in]:	    ��ͣ����� 1-��ͣ 0-����
	����ֵ:
		=1:�ɹ�
		=0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_PauseRealPlay(long lRealHandle, bool bPause);

/*
	����:�������ݻص�
	����:
		lRealHandle[in]:Ԥ�����ž��
		cbRealData[out]:ʵʱ���ݻص�
		dwUser[in]:		�ص���������
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_SetRealDataCallBack(long lRealHandle,fRealDataCallBack cbRealData, long dwUser);

/*
	����:���ݾ�������������������֡�ľ�����Ϣ,������H264_DVR_SetRealDataCallBack��ͬ
*/
H264_DVR_API bool CALL_METHOD H264_DVR_SetRealDataCallBack_V2(long lRealHandle,fRealDataCallBack_V2 cbRealData, void* dwUser);

/*
	����:����ص�����,�ú�����Ҫ��H264_DVR_StopRealPlayǰ����
	����:
		lRealHandle[in]:Ԥ�����ž��
		cbRealData[in]: ʵʱ�ص�����
		dwUser[in]:	    ʵʱ�ص���������
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_DelRealDataCallBack(long lRealHandle,fRealDataCallBack cbRealData, long dwUser);

/*
	����:����ص�����V2�汾
	����:
		lRealHandle[in]:Ԥ�����ž��
		cbRealData[in]: ʵʱ�ص�����V2�汾
		dwUser[in]:	    ʵʱ�ص���������
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_DelRealDataCallBack_V2(long lRealHandle,fRealDataCallBack_V2 cbRealData, long dwUser);

/*
	����:���ļ�����ѯ¼��
	����:
		lLoginID[in]:��½���
		lpFindInfo[in]:��ѯ����
		lpFileData[out]:��ѯ���
		lMaxCount[in]:��ѯ�����¼������
		findcount[out]:��ѯ����¼������
		waittime[in]:�ȴ�ʱ��
	����ֵ:
		=1:�ɹ�
		=0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_FindFile(long lLoginID, H264_DVR_FINDINFO* lpFindInfo, H264_DVR_FILE_DATA *lpFileData, int lMaxCount, int *findcount, int waittime DEF_PARAM(5000));

/*
	����:��ʱ���ѯ¼���ļ�
	����:
		lLoginID[in]:��½���
		lpFindInfo[in]:��ѯ����
		lpFileData[out]:��ѯ���
		waittime[in]:�ȴ�ʱ��
	����ֵ:
		=1:�ɹ�
		=0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_FindFileByTime(long lLoginID, SDK_SearchByTime* lpFindInfo, SDK_SearchByTimeResult *lpFileData, int waittime DEF_PARAM(10000));

/*
	����:���ļ����ط�¼��
	����:
		lLoginID[in]:	   ��½���
		sPlayBackFile[in]: �طŵ��ļ�����
		cbDownLoadPos[out]:���Ȼص����û�֪ͨ�û��豸�Ƿ��Ѿ������ݷ�����ϣ��ص��е�lDownLoadSize=-1�������ݷ������
						   �ͻ������ʵʱ��ʾ���ȣ�Ӧ�ô����������ȡʱ�����������粿�ֲ���������������Ե�ǰ�������ݴ�С/�ܴ�С��������ȵĻ����Ǻ�׼��Ӧ���Ե�ǰʱ�䣬���ݿ�ʼʱ��ͽ���ʱ�����������
		fDownLoadDataCallBack[out]:�ط����ݻص�
		dwDataUser[in]:			   ���ݻص�����
	����ֵ:
		>0��<0:�ɹ�
		=0:	   ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByName(long lLoginID, H264_DVR_FILE_DATA *sPlayBackFile, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack fDownLoadDataCallBack, long dwDataUser);

/*
	����:���ļ����ط�¼��
	����:
		lLoginID[in]:	   ��½���
		sPlayBackFile[in]: �طŵ��ļ�����
		cbDownLoadPos[out]:���Ȼص����û�֪ͨ�û��豸�Ƿ��Ѿ������ݷ�����ϣ��ص��е�lDownLoadSize=-1�������ݷ������
						   �ͻ������ʵʱ��ʾ���ȣ�Ӧ�ô����������ȡʱ�����������粿�ֲ���������������Ե�ǰ�������ݴ�С/�ܴ�С��������ȵĻ����Ǻ�׼��Ӧ���Ե�ǰʱ�䣬���ݿ�ʼʱ��ͽ���ʱ�����������
		fDownLoadDataCallBack[out]:�ط����ݻص�,���ݾ�����������
		dwDataUser[in]:			   ���ݻص�����
	����ֵ:
		>0��<0:�ɹ�
		=0:	   ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByName_V2(long lLoginID, H264_DVR_FILE_DATA *sPlayBackFile, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack_V2 fDownLoadDataCallBack, long dwDataUser);

/*
	����:��ʱ��ط�¼��
	����:
		lLoginID[in]:      ��½���
		lpFindInfo[in]:    ��ѯ¼������
		cbDownLoadPos[out]:���Ȼص����û�֪ͨ�û��豸�Ƿ��Ѿ������ݷ�����ϣ��ص��е�lDownLoadSize=-1�������ݷ������
		fDownLoadDataCallBack[out]:�ط����ݻص�
		dwDataUser[in]:			   ���ݻص�����
	����ֵ:
		>0��<0:�ɹ�
		=0:	   ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByTime(long lLoginID, H264_DVR_FINDINFO* lpFindInfo, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack fDownLoadDataCallBack, long dwDataUser);


/*
	����:��ʱ��ط�¼��Ex,���Ȼص������ݻص��ò�ͬ�Ļص�����,������H264_DVR_PlayBackByTime��ͬ
	
*/
H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByTimeEx(long lLoginID, H264_DVR_FINDINFO* lpFindInfo,fRealDataCallBack fDownLoadDataCallBack, long dwDataUser,
											fDownLoadPosCallBack cbDownLoadPos, long dwPosUser);
/*
	����:fDownLoadDataCallBack���ݻص����������ݵ�������������������H264_DVR_PlayBackByTimeEx��ͬ
*/
H264_DVR_API long CALL_METHOD H264_DVR_PlayBackByTime_V2(long lLoginID, H264_DVR_FINDINFO* lpFindInfo,fRealDataCallBack_V2 fDownLoadDataCallBack, long dwDataUser,
											fDownLoadPosCallBack cbDownLoadPos, long dwPosUser);

/*
	����:ֹͣ¼��ط�
	����:
		lPlayHandle[in]:�طž��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_StopPlayBack(long lPlayHandle);

/*
	����:�طſ���
	����:
		lPlayHandle[in]:�طž��
		lControlCode[in]:��������,��enum SDK_PlayBackAction
		lCtrlValue[in]:����ֵ
		itype[in]:����--�����ܻطŶ�λ����Ч,�����͵�����--��enum SDK_PLAY_BACK_SETTYPE
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_PlayBackControl(long lPlayHandle, long lControlCode,long lCtrlValue, int itype DEF_PARAM(0));

/*
	����:���ļ�������,�û����Բ�ʹ�ûص����Լ�ͨ��H264_DVR_GetDownloadPos��ȡ����
	����:
		lLoginID[in]:	    ��½���
		sPlayBackFile[in]:  ���ص�¼����Ϣ
		sSavedFileName[in]: ������ļ�·��
		cbDownLoadPos[out]:���ؽ��Ȼص�
		dwDataUser[in]:    �ص���������
		fDownLoadDataCallBack[out]:���ݻص�
	����ֵ:
		<0��>0:�ɹ�
		=0:	   ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_GetFileByName(long lLoginID,H264_DVR_FILE_DATA *sPlayBackFile,char *sSavedFileName,
                                                     fDownLoadPosCallBack cbDownLoadPos DEF_0_PARAM, long dwDataUser DEF_0_PARAM,fRealDataCallBack fDownLoadDataCallBack DEF_0_PARAM);

/*
	����:���ļ�������V2�汾,���ݻص��Ǿ�������������,������H264_DVR_GetFileByName��ͬ
*/
H264_DVR_API long CALL_METHOD H264_DVR_GetFileByName_V2(long lLoginID,H264_DVR_FILE_DATA *sPlayBackFile,char *sSavedFileName,
													 fDownLoadPosCallBack cbDownLoadPos DEF_0_PARAM, long dwDataUser DEF_0_PARAM,fRealDataCallBack_V2 fDownLoadDataCallBack_V2 DEF_0_PARAM);

/*
	����:��ʱ������V2�汾
	����:
		lLoginID[in]:			  ��½���
		lpFindInfo[in]:           ¼���ѯ����
		sSavedFileDIR[in]:		  ¼���ļ�����·��
		bMerge[in]:				  �ļ��Ƿ�ϲ�
		cbDownLoadPos[out]:		  ���Ȼص�,�û�֪ͨ�û��豸�Ƿ��Ѿ������ݷ�����ϣ��ص��е�lDownLoadSize=-1�������ݷ������
		dwDataUser[in]:			  �ص���������
		fDownLoadDataCallBack[in]:���ݻص�
	����ֵ:
		>0��<0:�ɹ�
		=0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_GetFileByTime(long lLoginID, H264_DVR_FINDINFO* lpFindInfo, char *sSavedFileDIR, bool bMerge DEF_PARAM(0),
                                                     fDownLoadPosCallBack cbDownLoadPos DEF_0_PARAM, long dwDataUser DEF_0_PARAM,fRealDataCallBack fDownLoadDataCallBack DEF_0_PARAM);

/*
	����:���ݻص����������ݵ�����������,������H264_DVR_GetFileByTime��ͬ
*/
H264_DVR_API long CALL_METHOD H264_DVR_GetFileByTime_V2(long lLoginID, H264_DVR_FINDINFO* lpFindInfo, char *sSavedFileDIR, bool bMerge
														,fDownLoadPosCallBack cbDownLoadPos DEF_0_PARAM,long dwDataUser DEF_0_PARAM,fRealDataCallBack_V2 fDownLoadDataCallBack_V2 DEF_0_PARAM);

/*
	����:ֹͣ�����ļ�
	����:
		lFileHandle[in]:�����ļ����
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_StopGetFile(long lFileHandle);


/*
	����:���ؿ���
	����:
		lPlayHandle[in]: ���ؾ��
		lControlCode[in]:��������,��enum SDK_PlayBackAction
		bDown[in]:		 �Ƿ�λ���أ�Ĭ��Ϊ1
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_GetFileControl(long lPlayHandle, long lControlCode, bool bDown DEF_PARAM(1));

/*
	����:��ȡ���ؽ���
	����:
		lFileHandle[in]:���ؾ��
	����ֵ:
		>=0:���ؽ���
		<0:	ʧ��
*/
H264_DVR_API int CALL_METHOD H264_DVR_GetDownloadPos(long lFileHandle);

/* 
	����:��������
	����:
		lLoginID[in]: ��½���
		sFileName[in]:�����ļ�·��
		nType[in]:	  ��������,1-��ʼ���� 0-��ֹ����
		cbUpgrade[in]:�������Ȼص�
		dwUser[in]:	  �ص���������
	����ֵ:
		>0��<0: �ɹ�
		=0:		ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_Upgrade(long lLoginID, char *sFileName, int nType DEF_0_PARAM, fUpgradeCallBack cbUpgrade DEF_0_PARAM, long dwUser DEF_0_PARAM);

/*
	����:�õ�����״̬
	����:
		lUpgradeHandle[in]:�������
	����ֵ:
		1:�ɹ�
		2:��������
		3:ʧ��
*/
H264_DVR_API int CALL_METHOD H264_DVR_GetUpgradeState(long lUpgradeHandle);

/*
	����:�ͷ��������
	����:
		lUpgradeHandle[in]:�������
	����ֵ:
		=1:�ɹ�
		=0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_CloseUpgradeHandle(long lUpgradeHandle);


/* 
	����:��̨����
	����:
		lLoginID[in]:	��½���
		nChannelNo[in]:	ͨ����
		lPTZCommand[in]:���������enum PTZ_ControlType
		bStop[in]:		�Ƿ���ֹͣ��0Ϊ�򿪣�1Ϊֹͣ
		lSpeed[in]:		�ٶ�
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_PTZControl(long lLoginID,int nChannelNo, long lPTZCommand, bool bStop  DEF_PARAM(0), long lSpeed DEF_PARAM(4));

/*
	����:1�����ã�ɾ����ת��Ԥ�õ�ʱ��lParam1ΪԤ�õ�ֵ
		 2������Ԥ�õ㵽Ѳ����ɾ��Ѳ����Ԥ�õ�ʱ��lParam1ΪѲ����·ֵ��lParam2ΪԤ�õ�ֵ,lParam3Ϊʱ����
		 3����ʼѲ����ֹͣѲ�������Ѳ����·ʱ��lParam1ΪѲ����·ֵ
		 4����̨��������ʱ��lParam1Ϊˮƽ������lParam2Ϊ��ֱ����
		 5����߽����ã��ұ߽����ã��Զ�ɨ�߹��ܣ�
	����:
		lLoginID[in]:	��½���
		nChannelNo[in]:	ͨ����
		lPTZCommand[in]:���������enum PTZ_ControlType
		lParam1[in]:	����1
		lParam2[in]:	����2
		lParam3[in]:	����3
		bStop[in]:		�Ƿ���ֹͣ��0Ϊ�򿪣�1Ϊֹͣ
	����ֵ:
		true: �ɹ�
		false:ʧ��
 */
H264_DVR_API bool CALL_METHOD H264_DVR_PTZControlEx(long lLoginID,int nChannelNo, long lPTZCommand,
                                                    long lParam1, long lParam2, long lParam3, bool bStop DEF_0_PARAM);

/*
	����:�豸���� 
	����:
		lLoginID[in]:��½���
		type[in]:	 ��������,0 �����豸��1 �����־ 2 �ػ� 3.�ָ���¼��־ 4.ֹͣ��¼��־
		waittime[in]:�ȴ�ʱ��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_ControlDVR(long lLoginID, int type, int waittime DEF_PARAM(2000));
	
/*
	����:�����������ڵ��豸 
	����:
		szBuf[out]:		���ջ���
		nBufLen[in]:	���ջ����С,sizeof(SDK_CONFIG_NET_COMMON_V2)*n
		pRetLen[in]:	���صĴ�С
		nSearchTime[in]:�ȴ�ʱ��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_SearchDevice(char* szBuf, int nBufLen, int* pRetLen, int nSearchTime);

H264_DVR_API bool CALL_METHOD H264_DVR_SearchDevice_IPV6(char* szBuf, int nBufLen, int* pRetLen, int nSearchTime, int ntype);

typedef  void ( CALL_METHOD *pfSearchDeviceCallBack)(SDK_CONFIG_NET_COMMON_V2  *pNetCom , unsigned long userData);
//
/*
	����:�����������ڵ��豸,�����������ڵ��豸V2�汾
	����:
		pfNetCom[out]:	�ص�����
		userData[in]:	�ص�����
		nSearchTime[in]:�ȴ�ʱ��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_SearchDevice_V2(pfSearchDeviceCallBack pfNetCom,unsigned long userData, int nSearchTime);

/*
	����:��ʼ�Խ�
	����:
		lLoginID[in]:  ��½���
		pVcb[out]:	   ���նԽ����ݻص�	
		dwDataUser[in]:�ص���������
	����ֵ:
		>0��<0: �ɹ�
		=0:		ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_StartVoiceCom_MR(long lLoginID, pfAudioDataCallBack pVcb, long dwDataUser);

/*
	����:���ͶԽ�����
	����:
		lVoiceHandle[in]:�Խ����
		pSendBuf[in]:	 �Խ�����
		lBufSize[in]:	 �Խ����ݴ�С
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_VoiceComSendData(long lVoiceHandle, char *pSendBuf, long lBufSize);

/*
	����:ֹͣ�Խ�
	����:
		lVoiceHandle[in]:�Խ����
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_StopVoiceCom(long lVoiceHandle);

/*	
	����:���öԽ���Ƶ���뷽ʽ���û����Բ����ã�Ĭ��ΪG711A����
	����:
		lLoginID[in]:  ��½���
		pTalkMode[in]: ͨ����,-1����ȫͨ����0-n������ͨ��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_SetTalkMode(long lLoginID, SDK_AudioInFormatConfig* pTalkMode);

/*	
	����:����¼��ģʽ
	����:
		lLoginID[in]:  ��½���
		nChannelNo[in]: ͨ����,-1����ȫͨ����0-n������ͨ��
		lRecordType[in]:¼��ģʽ,��enum SDK_RecordModeTypes
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/ 
H264_DVR_API bool CALL_METHOD H264_DVR_StartDVRRecord(long lLoginID, int nChannelNo ,long lRecordType);

/*	
	����:�ر�¼��
	����:
		lLoginID[in]:  ��½���
		nChannelNo[in]: ͨ����,-1����ȫͨ����0-n������ͨ��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/ 
H264_DVR_API bool CALL_METHOD H264_DVR_StopDVRRecord(long lLoginID, int nChannelNo);

/*	
	����:�����豸ϵͳʱ��
	����:
		lLoginID[in]:��½���
		pSysTime[in]:ʱ��
		nType[in]:ϵͳʱ������(true-�µ�ϵͳʱ��)
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_SetSystemDateTime(long lLoginID, SDK_SYSTEM_TIME *pSysTime, bool nType DEF_0_PARAM);

/*	
	����:�õ��豸�Ĺ���״̬
	����:
		lLoginID[in]:   ��½���
		pWorkState[out]:�豸�Ĺ���״̬
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_GetDVRWorkState(long lLoginID, SDK_DVR_WORKSTATE *pWorkState);

/*	
	����:������̣�����ʹ�÷�����ClientDemo
	����:
		lLoginID[in]:     ��½���
		pKeyBoardData[in]:������̲���
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_ClickKey(long lLoginID, SDK_NetKeyBoardData *pKeyBoardData);

/*	
	����:��Ӳ�̽��з���,��ʽ���ȵȲ���
	����:
		lLoginID[in]:   ��½���
		pStorageCtl[in]:��������
	����ֵ:
		=1: �ɹ�
		<=0:ʧ��
*/
H264_DVR_API int CALL_METHOD H264_DVR_StorageManage(long lLoginID, SDK_StorageDeviceControl *pStorageCtl);

/*
	����:�������籨����Ϣ
	����:
		lLoginID[in]:  ��½���
		pAlarmInfo[in]:���籨������
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_SendNetAlarmMsg(long lLoginID, SDK_NetAlarmInfo *pAlarmInfo);

/*
	����:�豸��ץͼ,��ץ�豸�˷������ļ�ʱ��һ��ͼƬ���ڴ�buf
		1.��Ҫ�豸����������ץͼ����ѡ��ýӿڲ���Ч
		2.�������1��Ĭ��ץ�����ķֱ�����D1�������ץ����Ƶ�ֱ���һ����ͼƬ������Ҫ�޸ı����������ץͼ�ֱ��ʣ�
		  �����������û��ץͼ�ֱ���ѡ�����Ҫ����֧�ָ���ĳ���
    ����:
		lLoginID[in]: ��½���
		nChannel[in]: ͨ����
		sFileName[in]:����·��
		nType[in]:ͼƬ����Ĭ��Ϊjpg, 0:jpg 1:YUV
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_CatchPic(long lLoginID, int nChannel, char *sFileName, int nType DEF_0_PARAM);

/*
	����:�豸��ץͼ,��ץ�豸�˷������ļ�ʱ��һ��ͼƬ���ڴ�buf���ⲿ�����ļ�
		1.��Ҫ�豸����������ץͼ����ѡ��ýӿڲ���Ч
		2.�������1��Ĭ��ץ�����ķֱ�����D1�������ץ����Ƶ�ֱ���һ����ͼƬ������Ҫ�޸ı����������ץͼ�ֱ��ʣ�
		  �����������û��ץͼ�ֱ���ѡ�����Ҫ����֧�ָ���ĳ���
    ����:
		lLoginID[in]:��½���
		nChannel[in]:ͨ����
		pBuffer[out]:���ջ���
		nBufLen[in]:���ջ���Ĵ�С
		pPicLen[in]:ʵ�ʷ��صĴ�С
		nType[in]:ͼƬ����Ĭ��Ϊjpg, 0:jpg 1:YUV
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_CatchPicInBuffer(long lLoginID, int nChannel, char *pBuffer, int nBufLen, int *pPicLen, int nType DEF_0_PARAM);

/*
	����:��������ļ���(�����÷���AlarmCenter demo)
	����:
		nPort[in]:		   �����˿ں�
		cbAlarmCenter[out]:���ݻص�
		dwDataUser[in]:    �ص���������
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_StartAlarmCenterListen(int nPort, fMessCallBack cbAlarmCenter, unsigned long dwDataUser);

/*
	����:�رձ������ļ���(�����÷���AlarmCenter demo)
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_StopAlarmCenterListen();

/*
	����:ͨ���������豸д����
	����:
		lLoginID[in]:��½���
		nType[in]:	 ��������
		pBuffer[in]: ����
		nBufLen[in]: ���ݳ���
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_SerialWrite(long lLoginID, SERIAL_TYPE nType, char *pBuffer, int nBufLen);

/*
	����:ͨ�����ڴ��豸������
	����:
		lLoginID[in]: ��½���
		nType[in]:	  ��������
		pBuffer[out]: ��������
		nBufLen[in]:  �������ݳ���
		pReadLen[out]:�յ������ݳ���
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_SerialRead(long lLoginID, SERIAL_TYPE nType, char *pBuffer, int nBufLen, int *pReadLen);

/*
	����:��ȡDDNS��Ϣ�������÷���ClientDemo
	����:
		searchmode[in]:������Ϣ
		pDevicInfo[out]:DDNS��Ϣ
		maxDeviceNum[in]:����豸��
		nretNum[out]:�õ����豸��
	����ֵ:
		=1:�ɹ�
		<0:ʧ��
*/
H264_DVR_API int CALL_METHOD H264_DVR_GetDDNSInfo(SearchMode &searchmode, DDNS_INFO *pDevicInfo, int maxDeviceNum, int &nretNum);

/*
	����:ǿ��I֡
	����:
		lLoginID[in]:��½���
		nChannel[in]:ͨ����
		nStream[in]: ��������,0��ʾ��������Ϊ1��ʾ������
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_MakeKeyFrame(long lLoginID, int nChannel, int nStream);

/*
	����:��ȡOEM��Ϣ
	����:
		lLoginID[in]:	 ��½���
		pOEMInfo[out]:	 OEM��Ϣ
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_GetOEMInfo(long lLoginID, SDK_OEMInfo *pOEMInfo);

/*
	����:����͸������ͨ��
	����:
		lLoginID[in]:	 ��½���
		TransInfo[in]:	 ͸�����ڲ���
		cbTransCom[out]: �豸���ݻص�
		lUser[in]:		 �ص���������
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_OpenTransComChannel(long lLoginID, TransComChannel *TransInfo, fTransComCallBack cbTransCom, unsigned long lUser);

/*
	����:�ر�͸������ͨ��
	����:
		lLoginID[in]:	 ��½���
		nType[in]:		 ͸����������
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_CloseTransComChannel(long lLoginID, SERIAL_TYPE nType);
//��ȡ״̬��Ϣ
H264_DVR_API bool CALL_METHOD H264_DVR_GetDeviceState(long lLoginID, SDK_State_Type type, char *pState);

/*
	����:��ȡ����uiͼƬ
	����:
		lLoginID[in]:	 ��½���
		saveFileName[in]:ͼƬ����·��
		type[in]:		 ����ͼƬ����,1:ΪȫͼƬ 2:�����ͼƬ
*/
H264_DVR_API bool CALL_METHOD H264_DVR_CatchPicUI(long lLoginID,char *saveFileName,int type DEF_PARAM(1));

#ifdef WIN32

/*
	����:��ͨ����Ƶ,Ԥ��/�ط�/���ز���һ������
	����:
		lHandle[in]:���ž��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_OpenSound(long lHandle);

/*
	����:�ر�ͨ����Ƶ,Ԥ��/�ط�/���ز���һ������
	����:
		lHandle[in]:���ž��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_CloseSound(long lHandle);

/*
	����:ץ����ͼƬ,Ԥ��/�ط�/���ز���һ������
	����:
		lHandle[in]:���ž��
		szSaveFileName[in]:����ͼƬ·��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_LocalCatchPic(long lHandle,char*szSaveFileName);

/*
	����:�򿪶Խ�
	����:
		lLoginID[in]:��½���
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_StartLocalVoiceCom(long lLoginID);

/*
	����:��ʼ����¼��
	����:
		lRealHandle[in]:���ž��
		szSaveFileName[in]:¼��·��
		type[in]:¼������
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_StartLocalRecord(long lRealHandle,char*szSaveFileName,long type=0);

/*
	����:�رձ���¼��
	����:
		lRealHandle[in]:���ž��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_StopLocalRecord(long lRealHandle);

/*
	����:���ű����ļ�
	����:
		pFileName[in]:	  ¼���ļ�·��
		hWnd[in]:		  ���Ŵ��ھ��
		drawCallBack[out]:�ص�����
		user[in]:		  �ص���������
	����ֵ:���ز��ž��
		>0��<0:�ɹ�
		=0:	   ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_StartLocalPlay(char*pFileName,void* hWnd,fPlayDrawCallBack drawCallBack=0,long user=0);

/*
	����:�رձ��ز���
	����:
		lPlayHandle[in]:���ز��ž��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_StopLocalPlay(long lPlayHandle);

/*
	����:��ȡ����λ�ã��ٷֱȣ������ڻطźͱ��ز���,�ط�ʱ�����ھ���ýӿڲ���Ч
	����:
		lPlayHandle[in]:�طž���򱾵ز��ž��
	����ֵ:���Ž���
*/
H264_DVR_API float CALL_METHOD H264_DVR_GetPlayPos(long lPlayHandle);

/*
	����:���ò���λ�ã��ٷֱȣ�,���ڻطţ����ز���(���ػط�ʱ�����ھ���ýӿڲ���Ч)
	����:
		lPlayHandle[in]:�طž���򱾵ز��ž��
		fRelativPos[in]:���Ž���
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_SetPlayPos(long lPlayHandle,float fRelativPos);

/*
	����:���ſ��ƣ����ţ�ֹͣ���ָ����췢�����ţ�
	����:
		lPlayHandle[in]:�طž���򱾵ز��ž��
		action[in]:		���ſ�������
		lCtrlValue[in]: �����ٶ�
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_LocalPlayCtrl(long lPlayHandle,SDK_LoalPlayAction action,long lCtrlValue);

/*
	����:���ñ��ز��Ž����ص�
	����:
		lPlayHandle[in]:�طž���򱾵ز��ž��
		callBack[out]:	���Ž����ص�
		user[in]:		�ص���������
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_SetFileEndCallBack(long lPlayHandle,fLocalPlayFileCallBack callBack,long user);

/*
	����:������Ϣ֡�ص�
	����:
		lPlayHandle[in]:ʵʱ���ž�����߻طž���򱾵ز��ž��
		callback[out]:	��Ϣ֡�ص�
		user[in]:		�ص���������
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_SetInfoFrameCallBack(long lPlayHandle,InfoFramCallBack callback,long user);

/*
	����:��ȡ������ɫ��Ԥ��/�ط�/���ز���һ������
	����:
		lHandle[in]:     ʵʱ���ž�����߻طž���򱾵ز��ž��
		nRegionNum[in]:  ��ʾ����,���ֻ��һ����ʾ����(ͨ�����)��Ϊ0
		pBrightness[out]:����	  
		pContrast[out]:	 �Աȶ�
		pSaturation[out]:���Ͷ�
		pHue[out]:		 ɫ��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_LocalGetColor(long lHandle, DWORD nRegionNum, LONG *pBrightness, LONG *pContrast, LONG *pSaturation, LONG *pHue);

/*
	����:������ɫ���ƣ�Ԥ��/�ط�/���ز���һ������
	����:
		lHandle[in]:     ʵʱ���ž�����߻طž���򱾵ز��ž��
		nRegionNum[in]:  ��ʾ����,���ֻ��һ����ʾ����(ͨ�����)��Ϊ0
		pBrightness[in]: ����	  
		pContrast[in]:	 �Աȶ�
		pSaturation[in]: ���Ͷ�
		pHue[in]:		 ɫ��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_LocalSetColor(long lHandle, DWORD nRegionNum, LONG nBrightness, LONG nContrast, LONG nSaturation, LONG nHue);
#endif
/*
	����:���ñ���ip,socketͨ���׽��ְ󶨵�ip
	����:
		szIP[in]:ip
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_SetLocalBindAddress(char*szIP);

/*
	����:�����ϱ�����,����������Ϣ��γ��/¼��״̬/����ͨ������״̬/ͨ������
	����:
		lLoginID[in]:��½���
		upLoadType[in]:�ϱ���������
		callBack[out]:�ϱ����ݻص�
		lUser[in]:�ص���������
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_StartUploadData(long lLoginID,UploadDataType upLoadType,fUploadDataCallBack callBack,long lUser);

/*
	����:ֹͣ�ϱ�����
	����:
		lLoginID[in]:��½���
		upLoadType[in]:�ϱ���������
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_StopUploadData(long lLoginID,UploadDataType upLoadType);

/*
	����:��ʼ����ע��
	����:
		nPort[in]:�����˿ں�,0<=nPort<=65535
		cbFunc[out]: ע�����߻ص�����
		dwDataUser[in]:�ص���������
	����ֵ:
		true:�ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_StartActiveRigister(int nPort, fMessCallBack cbFunc, unsigned long dwDataUser);


/*
	����:�ر�����ע��
	����ֵ:
		true:�ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_StopActiveRigister();

/*
	����:����������쳣�Ͽ�
	����:
		callBack[out]:�����ӶϿ��ص�
		userData[in]: �ص���������
	����ֵ:
		=1:�ɹ�
		=0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_SetSubDisconnectCallBack(fSubDisConnectCallBack callBack,DWORD userData);

/*
	����:���ñ���ʱ��,perKeeplifeTime(�������):Ĭ��10��,detectDisconTime(���߼��ʱ��):Ĭ��60��
	����:
		lLoginID[in]:	     ��½���
		perKeeplifeTime[in]: ����ʱ��
		detectDisconTime[in]:���߼��ʱ��
	����ֵ:
		=1:�ɹ�
		=0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_SetKeepLifeTime(long lLoginID,unsigned int perKeeplifeTime,unsigned int detectDisconTime);

/*
	����:MAC�Ƿ�õ�����
	����:
		pMac[in]:MAC��ַ
	����ֵ:
		true: ����
		false:û�м���
*/
H264_DVR_API bool CALL_METHOD H264_DVR_CheckEncrypt(char *pMac);

/*
	����:�豸���������豸�����豸��ͬһ�����������豸,�豸ȥ������Ȼ�󷵻ؽ��(H264_DVR_SearchDevice����ӿ���sdk����ȥ����,���߷��صĽ����һ�µ�)
	����:
		lLoginID[in]:		 ��½���
		pDevlist[out]:		 �豸�б�
		transferProtocol[in]:����Э��,��enum SDK_TransferProtocol_V2
		waittime[in]:		 �ȴ�ʱ��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_SearchDeviceEX(long lLoginID,SDK_NetDevList *pDevlist,SDK_TransferProtocol_V2 transferProtocol DEF_PARAM(SDK_TRANSFER_PROTOCOL_NETIP),int waittime DEF_PARAM(15000));

/*
	����:��̨���ٶ�λ,ʹ��ǰ�ж��Ƿ�֧��
	����:
		lLoginID[in]:		��½���
		nChannel[in]:		ͨ����
		pPositionPoint[in]:λ��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_PTZPostion(long lLoginID,int nChannel,SDK_PositionPoint *pPositionPoint);

/* 
	����:NVR�������ӵ�ǰ�˶Խ�,�ù�����Ҫ���ⶨ�Ƴ���
	����:
		lLoginID[in]:��½���
		nChannel[in]:ͨ����
		waittime[in]:�ȴ�ʱ��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_StartDevTalk(long lLoginID,int nChannel,int waittime DEF_PARAM(2000));

/* 
	����:ֹͣNVR�������ӵ�ǰ�˶Խ�
	����:
		lLoginID[in]:��½���
		nChannel[in]:ͨ����
		waittime[in]:�ȴ�ʱ��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_StopDevTalk(long lLoginID,int nChannel,int waittime DEF_PARAM(2000));

/*
	����:��ѯӲ��¼����Ϣ
	����:
		lLoginID[in]:   ��½���
		lpFindInfo[in]: ��ѯ����
		lpFileData[out]:���ҵ���¼�����ݣ��ⲿ���ڴ�
		waittime[in]:	��ѯ��ʱʱ��
	����ֵ:
		=1:�ɹ�
		=0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_RecordInfo(long lLoginID, SDK_SearchByTime* lpFindInfo, SDK_RecordStorageInfo *lpRecordData, int waittime DEF_PARAM(15000));

/*
	����:�����豸���ļ�
	����:
		lLoginID[in]:	   ��½���
		lpFileControl[in]:��Ҫ���Ƶ��ļ��Ϳ�������
		waittime[in]:      �ȴ�ʱ��
	����ֵ:
		true: �ɹ�
		false:ʧ��
 */
H264_DVR_API bool CALL_METHOD H264_DVR_ControlFile(long lLoginID,SDK_NetFileControl *lpFileControl,int waittime DEF_PARAM(15000));

/*
	����:��ѯ¼���豸������Ƶ�ļ������8��
	����:
		lLoginID[in]:	��½���
		lpFileList[out]:���ҵ�����Ƶ����
		waittime[in]:	�ȴ�ʱ��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_FindAudioFile(long lLoginID, SDK_MusicFileList* lpFileList, int waittime DEF_PARAM(5000));

/*
	����:���Ʋ����豸����Ƶ�ļ�
	����:
		lLoginID[in]:	   ��½���
		lpMusicControl[in]:��Ҫ���ŵ��ļ��Ϳ�������
		waittime[in]:      �ȴ�ʱ��
	����ֵ:
		true: �ɹ�
		false:ʧ��
 */
H264_DVR_API bool CALL_METHOD H264_DVR_ControlAudio(long lLoginID, SDK_LocalMusicControl *lpMusicControl, int waittime DEF_PARAM(2000));

/*
	����:�޸��ƴ�͸��������ַ
	����:
		ntype[in]:	  ���ò���
		pUserData[in]:��������ַ
		nlen[in]:     ���ò���
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_UserData(int ntype,char *pUserData, long nlen);
/*
	����:��ʼ������
	����:
		lLoginID[in]:��½���
		sUpgradeVer[in]:�������ļ���Ϣ
	����ֵ:
		=0:�ɹ�
		<0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_Upgrade_Cloud(long lLoginID, SDK_CloudUpgradeVersion *sUpgradeVer, int nType DEF_0_PARAM, fUpgradeCallBack cbUpgrade DEF_0_PARAM, long dwUser DEF_0_PARAM);
/*
	����:�µ�������
	����:
		lLoginID[in]:��½���
		sUpgradeVer[in]:�������ļ���Ϣ
	����ֵ:
		=0:�ɹ�
		<0:ʧ��
		��غ���:H264_DVR_GetUpgradeVersion
*/
H264_DVR_API long CALL_METHOD H264_DVR_Upgrade_Cloud_V2(long lLoginID, SDK_CloudUpgradeStartReq *sUpgradeVer, int nType DEF_0_PARAM, fUpgradeCallBack cbUpgrade DEF_0_PARAM, long dwUser DEF_0_PARAM);
/*
	����:ֹͣ������
	����:
		lHandle[in]:���������
	����ֵ:
		=0:�ɹ�
		<0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_StopUpgrade_Cloud(long lHandle);
/*
	����:��ѯĳ���豸������ip
	����:
		uuid[in]:�豸���к�
		ip[out]: ����ip
	����ֵ:
		=1: �ɹ�
		<=0:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_Get_OutNet_IP(const char *uuid, char* ip);

/*
	����:�ȿ��Ի�ȡҲ���������豸����
	����:
		lLoginID[in]:		 ��½���
		nCmdReq[in]:		 ��������
		szCmd[in]:			 json����
		lpOutBuffer[out]:	 ����json����
		dwOutBufferSize[in]: ���ջ����С(�ֽ�)
		lpBytesReturned[out]:���յ���json��С
		nTimeout[in]:		 �ȴ�ʱ��
		pInParam[in]:		 ����ʱʹ�õ�json�ַ���
		nInParamLen[in]:	 ����ʱjson��С(�ֽ�)
	����ֵ:
		=0:�ɹ�
		<0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_CmdGeneral(long lLoginID, int nCmdReq, const char *szCmd, void *lpOutBuffer, unsigned long dwOutBufferSize, unsigned long* lpBytesReturned, int nTimeout, char *pInParam DEF_PARAM(0), int nInParamLen DEF_PARAM(0), int nCmdRes DEF_PARAM(-1));


#ifndef WIN32
/*
	����:������������������ַ�Ͷ˿�
	����:
		ip[in]:  ��������ַ
		port[in]:�˿�
	����ֵ:
		=0: �ɹ�
		<0:ʧ��
*/

H264_DVR_API int  CALL_METHOD H264_DVR_SetServerAddr(const char *ip, int port);
/*
	����:�õ������ļ��б�
	����:
		id[in]:id��
		VersionList[out]:�������ݻ���,��Сsizeof(I_VERSION_INFO_T)*n
		num[out]:��ȡ���������ļ�����
	����ֵ:
		=0:�ɹ�
		<0:ʧ��
*/
H264_DVR_API int  CALL_METHOD H264_DVR_GetUpgradeFileList(const char *id, char *VersionList,int &num);

typedef void (*IDownProcess)(int nProcess,int userData);
typedef void (*IDownData)(unsigned char* data, unsigned int length, int nUserData);

/*
	����:���������ļ�������
	����:
		strSaveFilePath[in]:����������ļ�·��
		id[in]:				id��
		date:				�����ļ�����
		name:				�����ļ�����
		length:				�����ļ���С
		ProgressCallback[out]:�����ļ����ؽ��Ȼص�
		IDownData[out]:		�����ļ��������ݻص�
		userData[out]:		�ص���������
	����ֵ:
		=0:�ɹ�
		<0:ʧ��
		
*/
H264_DVR_API int CALL_METHOD H264_DVR_StartDownload(const char* strSaveFilePath, const char *id, const char *date,const char *name,unsigned int length,IDownProcess ProgressCallback,IDownData DataCallback,int userData);
/*
	����:ȡ�����������ļ�
	����ֵ:
		=0:�ɹ�
		<0:ʧ��
		
*/
H264_DVR_API int CALL_METHOD H264_DVR_CancelDownload();

/*
	����:��ȡ�ƴ�͸������ip
	����:
		_serverip[out]:�ƴ�͸������ip
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_GetServerIp(char* _serverip);

H264_DVR_API int CALL_METHOD H264_DVR_AuthDevice_Init(char *uuid,char *ip,int port);
H264_DVR_API int CALL_METHOD H264_DVR_AuthDevice_Register();
H264_DVR_API int CALL_METHOD H264_DVR_AuthDevice_UnRegister();
H264_DVR_API int CALL_METHOD H264_DVR_AuthDevice_GetUpdateServer(char *ip,int size);


H264_DVR_API int CALL_METHOD H264_DVR_AlarmInit(char* uuid,char*ip,char* serIP);

typedef int (*MpsDevAuth)(char *buffer,int size);	//��Ȩ
typedef int (*MpsDevDataRecv)(char *buffer,int size,int clientID);	//�����ɿͻ��˷����豸

H264_DVR_API int CALL_METHOD H264_DVR_AlarmPush(char* buffer,int size);
H264_DVR_API int CALL_METHOD H264_DVR_AlarmStart(char* uuid,char* serIP,MpsDevAuth  AuthCb, MpsDevDataRecv DataRecvCb);

/*
	����:��ȡ��͸��İ汾��Ϣ
	����:
		version[out]:��͸��汾��Ϣ
		size[i]:	 ��С
*/
H264_DVR_API void CALL_METHOD H264_VV_NAT_GetVersion(char *version, int size);
/*
	����:ǿ����ת��
	����:
		skipP2P[in];1-ǿ��ת��;0-����������������
*/
H264_DVR_API void CALL_METHOD H264_Direct_Proxy(int skipP2P);
/*
	����:�ж��豸�Ǿ�Ʒ���ǷǾ�Ʒ
	����ֵ:
		=1:��Ʒ�豸
		=0:��ͨ�豸	
*/
H264_DVR_API int CALL_METHOD H264_XM_Unique();
/*
	����:�õ��������Ͷ���ָ��,���ֻ�������
	����ֵ:
		mps�������Ϳ�IMpsAlarmClient����ָ��
*/
H264_DVR_API void* get_MpsAlarmClient_Instance();

/*
	����:�õ����õ�json��ʽ
	����:
		lLoginID[in]:	     ��½���
		dwCommand[in]:	     json��
		nChannelNO[in]:		 ͨ����,-1:�õ�ȫͨ������,0-n:�õ�����ͨ��������,��0��ʼ
		lpOutBuffer[out]:	 ����json����
		dwOutBufferSize[in]: ���ջ����С
		lpBytesReturned[out]:�õ��Ļ����С(�ֽ�)
		waittime[in]:		 �ȴ�ʱ��
	����ֵ:
		=1:�ɹ�
		<0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_GetDevConfig_Json(long lLoginID, const char* dwCommand, int nChannelNO,char * lpOutBuffer,unsigned long dwOutBufferSize,unsigned long* lpBytesReturned,int waittime DEF_PARAM(1000));
/*
	����:�������õ�json��ʽ
	����:
		lLoginID[in]:	     ��½���
		dwCommand[in]:	     json��
		nChannelNO[in]:		 ͨ����,-1:�õ�ȫͨ������,0-n:�õ�����ͨ��������,��0��ʼ
		lpOutBuffer[in]:	 ���õ�json�ַ���
		waittime[in]:		 �ȴ�ʱ��
	����ֵ:
		=1:�ɹ�
		<0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_SetDevConfig_Json(long lLoginID,const char* dwCommand, int nChannelNO, char * lpInBuffer,int waittime DEF_PARAM(1000));


typedef void (*PFunOnWifiConfigResult)(int nResult, SDK_CONFIG_NET_COMMON_V2 *pConfig);
/*
	����:��ʼwifiһ������
	����:
		pInfo[i]:	   ����wifi��һЩ������Ϣ
		pOnResult[out]:����wifi�ɹ��󷵻ص��豸�������
	����ֵ:
		=1:�ɹ�
		<0:ʧ��
*/
H264_DVR_API int CALL_METHOD H264_DVR_StartWifiConfig(SDK_SWifiInfo *pInfo, PFunOnWifiConfigResult pOnResult);
/*
	����:ֹͣwifiһ������
*/
H264_DVR_API void CALL_METHOD H264_DVR_StopWifiConfig();
/*
	����:������֤���û���������
	����:
		userName[in]:�û���
		password[in]:����
	����ֵ:
		=0:�ɹ�
		<0:ʧ��
*/
H264_DVR_API int CALL_METHOD H264_DVR_SetAuthUserInfo(const char *userName, const char *password);

#endif

/*
	����:��ȡ���������豸��Ϣ
	����: 
	lLoginID[int]:��¼���
	versionInfo	[int]	:������������Ϣ
	lpOutBuffer[out];�豸�汾����Ϣ
	dwOutBufferSize[out]:�豸�汾�Ĵ�С
	lpBytesReturned[out]:���յ��Ĵ�С
	waittime���ȴ�ʱ��
	����ֵ:
	=0:�ɹ�
	<0:ʧ��
	��غ�����H264_DVR_Upgrade_Cloud_V2
*/
H264_DVR_API long CALL_METHOD H264_DVR_GetUpgradeVersion(long lLoginID,SDK_CloudUpgradeVersionReq* versionInfo, 
	
														 char * lpOutBuffer,unsigned long dwOutBufferSize,unsigned long* lpBytesReturned,int waittime/*=500*/);


typedef int (*OnFoundDevCB)(char * uuid,int state,int userData);
/*
	����:��ѯ����豸�Ƿ�����V2�汾
	����:
		pStates[out]: Ҫ��ѯ�Ķ���豸��Ϣ,�᷵���豸״̬
		nTimeout[in]: �ȴ�ʱ��
		decCb[out]:   �豸�������Ļص�
		userData[out]:�ص�����
	����ֵ:
		=0:�ɹ�
		<0:ʧ��
*/
H264_DVR_API int CALL_METHOD H264_DVR_Check_Device_Exist_V2(SDK_SDevicesState *pStates, int nTimeout,OnFoundDevCB decCb,int userData);
/*
	���������ö��ο����Ʒ���uuid
	������
		uuid[in]: �ͻ�uuid
*/
H264_DVR_API bool CALL_METHOD H264_DVR_Set_UUid(char* uuid);
/*
	��������ȡ��ʱ����ϵ�ͼƬ
	������
		lLoginID[int]:��¼���
		pNetBreviaryPic:�����ȡ����Ϣ
		pBuffer:���ص�ͼƬ����
*/
H264_DVR_API bool CALL_METHOD H264_DVR_GetNetPic(long lLoginID, SDK_NetBreviaryPic* pNetBreviaryPic, char* pBuffer, int nBufLen, int *pPicLen);
/* 
	����:�ڼκ�ViscaЭ���޸ģ����úͻ�ȡ���ʽ����
	����:
		lLoginID[in]:	��½���
		pCameraControl[in&out]: ����
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_CameraViscaControl(long lLoginID, SDK_CameraViscaControl *pCameraControl);

/*
	����:����ͼƬ�ϴ�ͨ��
	����:
		lLoginID[in]:��½���
		nChannelNo[in]:ͨ����
		nPicType[in]:��Ҫ��ע��ͼƬ����--��ö��SDK_INTEL_PUSH_TYPE
		nType[in]:���͵õ���ͼƬ����--��ö��SDK_INTEL_PUSH_IMG_TYPE
	����ֵ:
		=1:�ɹ�
		=0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_SetupPushChan(long lLoginID, int nChannel, int nPicType, int nType);

/*
	����:�ر�ͼƬ�ϱ�
	����:
		lLoginID[in]:��½���
		nChannelNo[in]:ͨ����
	����ֵ:
		=1:�ɹ�
		=0:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_ClosePushChan(long lLoginID, int nChannelNo);

/*
	����:������ѯ
	����:
		lLoginID[in]:��½���
		pFindParam[in]:��ѯ����
		pRetBuffer[out]:����������Ϣ
		lBufSize[out]:�������ش�С
		waittime:�ȴ�ʱ��
	����ֵ:
		true: �ɹ�
		false:ʧ��
*/
H264_DVR_API bool CALL_METHOD H264_DVR_SearchCalendar(long lLoginID, SDK_SearchCalendar *pFindParam, SDK_SearchCalendarMask *pRetBuffer, int waittime DEF_PARAM(2000));

/*
	����:�����������--��ö��SDK_ConsumerProCmd
	����:
	lLoginID[in]:	     ��½���
	lpOutBuffer[out]:	 ��������--SDK_ConsumerProOpr
	lpBytesReturned[out]:���ص�����
	waittime[in]:		 �ȴ�ʱ�� 
	����ֵ:
	=1:�ɹ�
	<0:ʧ��
*/
H264_DVR_API long CALL_METHOD H264_DVR_ConsumerCmd(long lLoginID, SDK_ConsumerProOpr* lpOutBuffer, int* lpBytesReturned,int waittime DEF_PARAM(1000));

#ifdef _NAMESPACE_
}
#endif

#endif
