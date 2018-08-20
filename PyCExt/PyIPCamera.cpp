// PyIPCamera.cpp: the python extension using C/C++ API
//
// Exporting a c++ class (CIPCamera) to python 2.7 or 3.6
//

#include <stdio.h>
#include "HCNetSDK.h"

#include <Python.h>
#include <structmember.h>
#include <numpy/arrayobject.h>
#include <unistd.h>
#include <math.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <sstream>
#include <iostream>
#include <dirent.h>

using namespace std;
using namespace cv;

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
#include <linux/videodev2.h>
};

#define HPR_ERROR -1
#define HPR_OK 0

AVCodecContext *dCodecCtx;
bool flag = false;

string m_result;

////////////////////////////////////////////////////////////
//1. Definition of class / structure
typedef struct _CIPCamera
{
	PyObject_HEAD		// == PyObject ob_base;
		char *m_szIP;   // ip address of the camera
	int m_nPort;		// port
	char *m_szUserName; // username
	char *m_szPWD;		// password
	int m_lRealPlayHandle;
	long m_lUserID;
	char *m_absPath;
} CIPCamera;

//2. Definition of the class data members
static PyMemberDef CIPCamera_DataMembers[] =
	{
		{"ip", T_STRING, offsetof(CIPCamera, m_szIP), 0, "The camera's IP address."},
		{"port", T_INT, offsetof(CIPCamera, m_nPort), 0, "The camers's services port."},
		{"userName", T_STRING, offsetof(CIPCamera, m_szUserName), 0, "user name for login."},
		{"password", T_STRING, offsetof(CIPCamera, m_szPWD), 0, "camera's password."},
		{"realPlayHandle", T_STRING, offsetof(CIPCamera, m_lRealPlayHandle), 0, "camera's realPlayHandle."},
		{"userID", T_STRING, offsetof(CIPCamera, m_lUserID), 0, "camera's userID."},
		{"absPath", T_STRING, offsetof(CIPCamera, m_absPath), 0, "camera's absPath."},
		{NULL, NULL, NULL, 0, NULL}};

//////////////////////////////////////////////////////////////
//3. Definition of constructor,destructor and some interner functions.
// Refer to PyTypeObject page of python API reference.

// IPCamera("10.41.0.99",8000,"admin","humanmotion01")

// constructor
#if PY_MAJOR_VERSION >= 3
    static int CIPCamera_init(CIPCamera *Self, PyObject *pArgs)
#else
    static void CIPCamera_init(CIPCamera *Self, PyObject *pArgs)
#endif
{
	//* IMPORTANT: this must be called for numpy (avoid exception:Segment Fault)
	//* BUG FIX: since PyArray_API is statically declared in _multiarray.h (numpy)
	if (PyArray_API == NULL)
	{
		// printf("1debug:===>xx1 PyArray_API=0x%x\r\n", PyArray_API);
		import_array();
		// printf("2debug:===>xx1 PyArray_API=0x%x\r\n", PyArray_API);
		// printf("3debug:===>xx1 PyArray_API=0x%x PyArray_API[93]=0x%X\r\n", PyArray_API, PyArray_API[93]);
	}

	const char *szIP = NULL;
	const char *szUserName = NULL;
	const char *szPWD = NULL;
	const char *absPath = NULL;

	if (!PyArg_ParseTuple(pArgs, "sisss", &szIP, &Self->m_nPort, &szUserName, &szPWD, &absPath))
	{
		// raise exceiont....
		printf("Parse the argument FAILED! You should pass correct values!\r\n");
#if PY_MAJOR_VERSION >= 3
    return -1;
#else
    return;
#endif
		
	}

	Self->m_szIP = new char[strlen(szIP) + 1];
	Self->m_szUserName = new char[strlen(szUserName) + 1];
	Self->m_szPWD = new char[strlen(szPWD) + 1];
	Self->m_absPath = new char[strlen(absPath) + 1];

	strcpy(Self->m_szIP, szIP);
	strcpy(Self->m_szUserName, szUserName);
	strcpy(Self->m_szPWD, szPWD);
	strcpy(Self->m_absPath, absPath);

	system("mkdir Temp");
	#if PY_MAJOR_VERSION >= 3
    return 0;
#else
    return;
#endif
}

// destructor
static void CIPCamera_Destruct(CIPCamera *Self)
{
	// release all the member
	if (Self->m_szIP)
		delete[] Self->m_szIP;
	if (Self->m_szUserName)
		delete[] Self->m_szUserName;
	if (Self->m_szPWD)
		delete[] Self->m_szPWD;

	// release other PyObject* members
	// such as: Py_XDECREF(Self->Member);
	Py_TYPE(Self)->tp_free((PyObject *)Self); // release this instance.
}

// this function will be called from python
// str(obj)
// print(obj)
static PyObject *CIPCamera_Str(CIPCamera *Self)
{
	char sz[256] = {0};
	snprintf(sz, 255,
			 "IP       : %s\r\n"
			 "Port     : %d\r\n"
			 "UserName : %s\r\n"
			 "Password : %s\r\n",
			 Self->m_szIP,
			 Self->m_nPort,
			 Self->m_szUserName,
			 Self->m_szPWD);

	return Py_BuildValue("s", sz);
}

// this function will be called from python
// repr(obj)
static PyObject *CIPCamera_Repr(CIPCamera *Self)
{
	return CIPCamera_Str(Self);
}

////////////////////////////////////////////////////////////
// Getter / Setter
//
static PyObject *CIPCamera_GetIP(CIPCamera *Self)
{
	return Py_BuildValue("s", Self->m_szIP);
}

static PyObject *CIPCamera_GetPort(CIPCamera *Self)
{
	return Py_BuildValue("i", Self->m_nPort);
}

static PyObject *CIPCamera_GetUserName(CIPCamera *Self)
{
	return Py_BuildValue("s", Self->m_szUserName);
}

static PyObject *CIPCamera_GetPassword(CIPCamera *Self)
{
	return Py_BuildValue("s", Self->m_szPWD);
}

static PyObject *CIPCamera_GetParameters(CIPCamera *Self)
{
	return Py_BuildValue("(siss)", Self->m_szIP, Self->m_nPort, Self->m_szUserName, Self->m_szPWD);
}

static PyObject *CIPCamera_SetParameters(CIPCamera *Self, PyObject *pArgs)
{
	const char *szIP = NULL;
	const char *szUserName = NULL;
	const char *szPWD = NULL;
	if (!PyArg_ParseTuple(pArgs, "siss", &szIP, &Self->m_nPort, &szUserName, &szPWD))
	{
		printf("Parse the argument FAILED! You should pass correct values!\r\n");
		return NULL;
	}

	delete[] Self->m_szIP;
	delete[] Self->m_szUserName;
	delete[] Self->m_szPWD;

	Self->m_szIP = new char[strlen(szIP) + 1];
	Self->m_szUserName = new char[strlen(szUserName) + 1];
	Self->m_szPWD = new char[strlen(szPWD) + 1];
	strcpy(Self->m_szIP, szIP);
	strcpy(Self->m_szUserName, szUserName);
	strcpy(Self->m_szPWD, szPWD);

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *CIPCamera_PrintInfo(CIPCamera *Self)
{
	std::cout << "The IPCamera's properties as follows:" << endl
			  << "==============================" << endl
			  << "IP       : " << Self->m_szIP << endl
			  << "Port     : " << Self->m_nPort << endl
			  << "UserName : " << Self->m_szUserName << endl
			  << "Password : " << Self->m_szPWD << endl
			  << "AbsPath  : " << Self->m_absPath << endl
			  << "==============================" << endl;

	Py_XINCREF(Py_None);
	return Py_None;
}
uint8_t *current_data_point;
AVFrame *pYUVFrame = av_frame_alloc();
AVFrame *pRGBFrame = av_frame_alloc();
// Mat current_image;
// HK-SDK start ================== strat
// 原始H264码流（裸码流）回调 暂时无用
void CALLBACK g_fPlayESCallBack(LONG lPreviewHandle, NET_DVR_PACKET_INFO_EX *pstruPackInfo, void *pUser)
{
	AVPacket *avpacket = av_packet_alloc();

	avpacket->size = pstruPackInfo->dwPacketSize;
	avpacket->data = (uint8_t *)(pstruPackInfo->pPacketBuffer);

	int numBytes = avpicture_get_size(AV_PIX_FMT_BGR24, dCodecCtx->width, dCodecCtx->height);
	uint8_t *buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
	avpicture_fill((AVPicture *)pRGBFrame, buffer, AV_PIX_FMT_BGR24, dCodecCtx->width, dCodecCtx->height);
	int frameFinished;

	avcodec_decode_video2(dCodecCtx, pYUVFrame, &frameFinished, avpacket);

	if (frameFinished)
	{
		struct SwsContext *img_convert_ctx = sws_getCachedContext(NULL, dCodecCtx->width, dCodecCtx->height, dCodecCtx->pix_fmt, dCodecCtx->width, dCodecCtx->height, AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);
		sws_scale(img_convert_ctx, (uint8_t const *const *)pYUVFrame->data,
				  pYUVFrame->linesize, 0, dCodecCtx->height,
				  pRGBFrame->data, pRGBFrame->linesize);

		current_data_point = pRGBFrame->data[0];

		Mat img(pYUVFrame->height, pYUVFrame->width, CV_8UC3, *(pRGBFrame->data)); //dst->data[0]);

		// ostringstream oss;
		// oss << format(img, 3);
		// m_result = oss.str();
		// cout << m_result << endl;

		if (flag)
		{
			cv::imshow("display", img);
			cvWaitKey(2);
		}
		// else
		// {
		// 	char szFilename[32];

		// 	sprintf(szFilename, "./Temp/%07d.jpg", pYUVFrame->coded_picture_number);
		// 	// sprintf(szFilename, "./Temp/OJBK.jpg", pYUVFrame->coded_picture_number);

		// 	imwrite(szFilename, img);
		// }
		av_free(buffer);
		av_free_packet(avpacket);
		sws_freeContext(img_convert_ctx);
	}
	// printf("pyd---(ES)Get data,the size is %d,%d.\n", pstruPackInfo->dwPacketType, pstruPackInfo->dwPacketSize);
}

int initFfmpeg()
{
	av_register_all();
	avformat_network_init();
	AVCodec *dCodec;

	dCodec = avcodec_find_decoder(AV_CODEC_ID_H264);
	if (dCodec)
	{
		dCodecCtx = avcodec_alloc_context3(dCodec);
		dCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
		dCodecCtx->width = 1920;
		dCodecCtx->height = 1080;

		if (avcodec_open2(dCodecCtx, dCodec, NULL) < 0)
		{
			printf("avcode open failed!\n");
			return -2;
		}
	}
	else
	{
		printf("Can't find dectector!");
		exit(-1);
	}

	return 0;
}

static PyObject *CIPCamera_Login(CIPCamera *Self)
{
	NET_DVR_Init();
	initFfmpeg();
	NET_DVR_DEVICEINFO struDeviceInfo;
	Self->m_lUserID = NET_DVR_Login(Self->m_szIP, Self->m_nPort, Self->m_szUserName, Self->m_szPWD, &struDeviceInfo);
	if (Self->m_lUserID < 0)
	{
		printf("pyd1---Login error, %d\n", NET_DVR_GetLastError());
		return Py_BuildValue("i", HPR_ERROR);
	}
	return Py_BuildValue("i", HPR_OK);
}

static PyObject *CIPCamera_Open(CIPCamera *Self)
{

	NET_DVR_PREVIEWINFO struPlayInfo = {0};
	struPlayInfo.hPlayWnd = 0; //需要 SDK 解码时句柄设为有效值,仅取流不解码时可设为空
	struPlayInfo.lChannel = 1; //预览通道号
	struPlayInfo.dwStreamType = 0;
	//0-主码流,1-子码流,2-码流 3,3-码流 4,以此类推
	struPlayInfo.dwLinkMode = 0; //0- TCP 方式,1- UDP 方式,2- 多播方式,3- RTP 方式,4-RTP/RTSP,5-RSTP/HTTP
	struPlayInfo.bBlocked = 1;   //0- 非阻塞取流,1- 阻塞取流
	Self->m_lRealPlayHandle = NET_DVR_RealPlay_V40(Self->m_lUserID, &struPlayInfo, NULL, NULL);

	if (Self->m_lRealPlayHandle < 0)
	{
		printf("m_lRealPlayHandle error, %d\n", NET_DVR_GetLastError());
		NET_DVR_Logout(Self->m_lUserID);
		NET_DVR_Cleanup();
		return Py_BuildValue("i", HPR_ERROR);
	}

	//Set callback function of getting stream.
	if (!NET_DVR_SetESRealPlayCallBack(Self->m_lRealPlayHandle, g_fPlayESCallBack, 0))
	{
		printf("callback error\n");
		NET_DVR_StopRealPlay(Self->m_lRealPlayHandle);
		NET_DVR_Logout(Self->m_lUserID);
		NET_DVR_Cleanup();
		return Py_BuildValue("i", HPR_ERROR);
	}

	return Py_BuildValue("i", HPR_OK);
}

static PyObject *CIPCamera_IsOpen(CIPCamera *Self)
{
	int nErr = 0;
	return Py_BuildValue("i", nErr);
}

static PyObject *CIPCamera_Close(CIPCamera *Self)
{
	//stop
	NET_DVR_StopRealPlay(Self->m_lRealPlayHandle);
	std::cout << "已停止预览" << endl;
	NET_DVR_Logout(Self->m_lUserID);
	std::cout << "已登出" << endl;
	NET_DVR_Cleanup();
	std::cout << "已释放资源" << endl;
	return Py_BuildValue("i", HPR_OK);
}

static PyObject *CIPCamera_Read(CIPCamera *Self)
{
	int nErr = 0;
	return Py_BuildValue("i", nErr);
}

static PyObject *CIPCamera_StratParsingStreamWithFFmpeg(CIPCamera *Self)
{
	//"ffmpeg -i rtsp://admin:humanmotion01@10.41.0.99/h264/ch1/main/av_stream -vf fps=25 ./Temp/%3d.jpg"

	system("rm -f ./Temp/*.*");

	ostringstream oss;
	oss << "gnome-terminal -- ffmpeg -i rtsp://" << Self->m_szUserName << ":" << Self->m_szPWD << "@" << Self->m_szIP << "/h264/ch1/main/av_stream -vf fps=25 ./Temp/%5d.jpg";
	system(oss.str().c_str());

	Py_XINCREF(Py_None);
	return Py_None;
}

static PyObject *CIPCamera_StopParsingStreamWithFFmpeg(CIPCamera *Self)
{
	system("kill $(pidof ffmpeg)");

	Py_XINCREF(Py_None);
	return Py_None;
}

static PyObject *CIPCamera_GetDetentionFrame(CIPCamera *Self)
{
	DIR *dp;
	struct dirent *dirp;
	string res = "";
	if ((dp = opendir(Self->m_absPath)) == NULL)
	{
		cout << "Can't open " << Self->m_absPath << endl;
	}
	while ((dirp = readdir(dp)) != NULL)
	{
		res = res < dirp->d_name ? dirp->d_name : res;
	}
	closedir(dp);

	ostringstream oss;
	oss << Self->m_absPath << '/' << res;
	return Py_BuildValue("s", oss.str().c_str());
}

static PyObject *CIPCamera_GetCurrentionFrame(CIPCamera *Self)
{
	// string cr = m_result;
	cout << m_result << endl;
	return Py_BuildValue("U", m_result);
}

typedef unsigned char BYTE;

//* Example of wrapping the cos function from math.h using the Numpy-C-API.
//* wrapped cosine function
//*
//* python test code:
//
//* ArrList = [1, 2, 3, 4, 5, 6, 7, 8, 9]
//* Array_A  = np.asarray(ArrList, dtype='float' )
//* Array_B  = np.asarray(ArrList, dtype='double')
//* pycext.cos_func_np(Array_A)
//* pycext.cos_func_np(Array_B)
//*
static PyObject *
CIPCamera_QueryFrame(CIPCamera *Self, PyObject *args)
{
	const char *cmd;
	if (!PyArg_ParseTuple(args, "s", &cmd))
		return NULL;

	if (cmd == NULL)
		return (PyObject *)Py_BuildValue("s", "Null Parammfd!");
	else if (strcmp(cmd, "list") != 0 && strcmp(cmd, "array") != 0 && strcmp(cmd, "bytes") != 0)
		return (PyObject *)Py_BuildValue("s", cmd);

	PyObject *pretobj = nullptr;

	int Index_i = 0, Index_k = 0, Index_m = 0, Index_n = 0;
	if (strcmp(cmd, "list") == 0)
	{ /*Pass by List: Transform an C Array to Python List*/
		double CArray[] = {1.2, 4.5, 6.7, 8.9, 1.5, 0.5};

		PyObject *PyList = PyList_New(6);
		pretobj = PyTuple_New(1);
		for (Index_i = 0; Index_i < PyList_Size(PyList); Index_i++)
		{

			PyList_SetItem(PyList, Index_i, PyFloat_FromDouble(CArray[Index_i]));
		}

		// PyObject *pFuncFour = PyDict_GetItemString(pDict, "PassListFromCToPython");
		// cout << "C Array Pass Into The Python List:" << endl;
		PyTuple_SetItem(pretobj, 0, PyList);
		//PyObject_CallObject(pFuncFour, ArgList);
	}
	else if (strcmp(cmd, "array") == 0)
	{ /*Pass by Python Array: Transform an C Array to Python Array*/
		//double CArrays[3][3] = { { 1.3, 2.4, 5.6 }, { 4.5, 7.8, 8.9 }, { 1.7, 0.4, 0.8 } };
		npy_intp Dims[1] = {1920 * 3 * 1080};
		PyObject *PyArray = PyArray_SimpleNewFromData(1, Dims, NPY_UBYTE, current_data_point);
		pretobj = PyTuple_New(1);
		PyTuple_SetItem(pretobj, 0, PyArray);

		//PyObject *pFuncFive = PyDict_GetItemString(pDict, "PassArrayFromCToPython");
		//PyObject_CallObject(pFuncFive, ArgArray);
	}
	else
	{ /*Pass by Python Array: Transform an C Array to Python Array*/
		BYTE CArrays[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
		npy_intp Dims[2] = {3, 3};

		PyObject *PyArray = PyArray_SimpleNewFromData(2, Dims, NPY_UBYTE, CArrays);
		pretobj = PyTuple_New(1);
		PyTuple_SetItem(pretobj, 0, PyArray);

		//PyObject *pFuncFive = PyDict_GetItemString(pDict, "PassArrayFromCToPython");
		//PyObject_CallObject(pFuncFive, ArgArray);
	}

	return pretobj;
}

// The member function list of the class, exporting to python
static PyMethodDef CIPCamera_MethodMembers[] =
	{
		{"GetIP", (PyCFunction)CIPCamera_GetIP, METH_NOARGS, "Get the IP address of instance."},
		{"GetPort", (PyCFunction)CIPCamera_GetPort, METH_NOARGS, "Get the port number of instance."},
		{"GetUserName", (PyCFunction)CIPCamera_GetUserName, METH_NOARGS, "Get the user name of isntance."},
		{"GetPassword", (PyCFunction)CIPCamera_GetPassword, METH_NOARGS, "Get the password of instance."},
		{"GetParameters", (PyCFunction)CIPCamera_GetParameters, METH_NOARGS, "Get all the properties of isntance."},
		{"SetParameters", (PyCFunction)CIPCamera_SetParameters, METH_VARARGS, "Set the properties of instance."},
		{"PrintInfo", (PyCFunction)CIPCamera_PrintInfo, METH_NOARGS, "Print all information of instance."},

		{"login", (PyCFunction)CIPCamera_Login, METH_NOARGS, "login the camera"},
		{"open", (PyCFunction)CIPCamera_Open, METH_NOARGS, "open the camera"},
		{"isopen", (PyCFunction)CIPCamera_IsOpen, METH_NOARGS, "is the camera opened."},
		{"close", (PyCFunction)CIPCamera_Close, METH_NOARGS, "close the camera."},
		{"read", (PyCFunction)CIPCamera_Read, METH_NOARGS, "query frame from camera."},
		{"queryframe", (PyCFunction)CIPCamera_QueryFrame, METH_VARARGS, "query frame from camera."},

		{"StratParsingStream", (PyCFunction)CIPCamera_StratParsingStreamWithFFmpeg, METH_NOARGS, "Strat Parsing Stream With FFmpeg."},
		{"StopParsingStream", (PyCFunction)CIPCamera_StopParsingStreamWithFFmpeg, METH_NOARGS, "Stop Parsing Stream With FFmpeg."},
		{"GetDetentionFrame", (PyCFunction)CIPCamera_GetDetentionFrame, METH_NOARGS, "Get Detention Frame (1500ms From Current)."},
		{"GetCurrentionFrame", (PyCFunction)CIPCamera_GetCurrentionFrame, METH_NOARGS, "Get Currention Frame (100ms From Current)."},

		{NULL, NULL, NULL, NULL}};

////////////////////////////////////////////////////////////
// construct a PyTypeObject, which is the python object
//
// static PyTypeObject CIPCamera_ClassInfo =
PyTypeObject CIPCamera_ClassInfo =
	{
		PyVarObject_HEAD_INIT(NULL, 0) "HikSDK.IPCamera", // __class__
		sizeof(CIPCamera),								  // used by PyObject_New
		0,
		(destructor)CIPCamera_Destruct, // deconstructor
		0,
		0,
		0,
		0,
		(reprfunc)CIPCamera_Repr, // repr
		0,
		0,
		0,
		0,
		0,
		(reprfunc)CIPCamera_Str, // Str/print
		0,
		0,
		0,
		Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
		"CIPCamera Objects---Extensioned by C++!", // __doc__
		0,
		0,
		0,
		0,
		0,
		0,
		CIPCamera_MethodMembers, // all member functions
		CIPCamera_DataMembers,   // all data members
		0,
		0,
		0,
		0,
		0,
		0,
		(initproc)CIPCamera_init, // constructor
		0,
};

/*
////////////////////////////////////////////////////////////
// Module initialization. 
// It will be call when "import" in python
//
PyMODINIT_FUNC           // == __decslpec(dllexport) PyObject*
PyInit_HikSDK(void) 
{
	CIPCamera_ClassInfo.tp_new = PyType_GenericNew; // fuction "new" --- create new instance

	/////////////////////////////////////////////////////
	// PyType_Ready: initialize the object type object
	// return:
	// 0 -- success
	// failed --- -1 and throws ex
	if (PyType_Ready(&CIPCamera_ClassInfo) < 0)
		return NULL;

	PyObject* pReturn = PyModule_Create(&ModuleInfo);          // create module info block
	if (pReturn == 0)
		return NULL;

	Py_INCREF(&ModuleInfo);
	PyModule_AddObject(pReturn, "IPCamera", (PyObject*)&CIPCamera_ClassInfo); // export in module Dictionary
	return pReturn;
}
*/
