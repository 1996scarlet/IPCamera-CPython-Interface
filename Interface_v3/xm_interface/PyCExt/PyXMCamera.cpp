// PyXMCamera.cpp: the python extension using C/C++ API
//
// Exporting a c++ class (CXMCamera) to python 2.7 or 3.6
//

#include <stdio.h>
#include "netsdk.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <Python.h>
#include <structmember.h>
#include <numpy/arrayobject.h>
#include <unistd.h>

#include <sstream>
#include <iostream>
#include <dirent.h>
using namespace std;

using namespace cv;

#define HPR_ERROR -1
#define HPR_OK 0

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
#include <linux/videodev2.h>
};

AVCodecContext *dCodecCtx;
uint8_t *current_data_point;

AVFrame *pYUVFrame = av_frame_alloc();
AVFrame *pRGBFrame = av_frame_alloc();

bool flag = false;

////////////////////////////////////////////////////////////
//1. Definition of class / structure
typedef struct _CXMCamera
{
	PyObject_HEAD		// == PyObject ob_base;
		char *m_szIP;   // ip address of the camera
	int m_nPort;		// port
	char *m_szUserName; // username
	char *m_szPWD;		// password
	long m_lUserID;
	long m_iPlayhandle;
	char *m_absPath;
} CXMCamera;

int RealDataCallBack_V2(long lRealHandle, const PACKET_INFO_EX *pFrame, long dwUser)
{
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

	int numBytes = avpicture_get_size(AV_PIX_FMT_BGR24, dCodecCtx->width, dCodecCtx->height);
	uint8_t *buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
	avpicture_fill((AVPicture *)pRGBFrame, buffer, AV_PIX_FMT_BGR24, dCodecCtx->width, dCodecCtx->height);
	int frameFinished;

	avcodec_decode_video2(dCodecCtx, pYUVFrame, &frameFinished, avpacket);
	cout << "DEBUG====>FLAG_V5" << endl;


	if (frameFinished)
	{
		struct SwsContext *img_convert_ctx = sws_getContext(1920, 1080, AV_PIX_FMT_YUV420P, 1920, 1080, AV_PIX_FMT_BGR24, SWS_SINC, NULL, NULL, NULL);

		sws_scale(img_convert_ctx, (uint8_t const *const *)pYUVFrame->data,
				  pYUVFrame->linesize, 0, dCodecCtx->height,
				  pRGBFrame->data, pRGBFrame->linesize);

		// // Save the frame to disk

		current_data_point = pRGBFrame->data[0];

		cv::Mat img(pYUVFrame->height, pYUVFrame->width, CV_8UC3, pRGBFrame->data[0]); //dst->data[0]);

		if (flag)
		{
			//imshow("display", img);
			//cvWaitKey(1);
		}
		// else
		// {
		// 	char szFilename[32];

		// 	sprintf(szFilename, "./Temp/%07d.jpg", pYUVFrame->coded_picture_number);

		// 	imwrite(szFilename, img);
		// }
		sws_freeContext(img_convert_ctx);
		//av_free(img_convert_ctx);
	}
	av_free(buffer);
	// av_frame_free(&pYUVFrame);
	// av_frame_free(&pRGBFrame);
	av_free_packet(avpacket);
	return TRUE;
}

int initFfmpeg()
{
	av_register_all();
	//avformat_network_init();
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

//2. Definition of the class data members
static PyMemberDef CXMCamera_DataMembers[] =
	{
		{"ip", T_STRING, offsetof(CXMCamera, m_szIP), 0, "The camera's IP address."},
		{"port", T_INT, offsetof(CXMCamera, m_nPort), 0, "The camers's services port."},
		{"userName", T_STRING, offsetof(CXMCamera, m_szUserName), 0, "user name for login."},
		{"password", T_STRING, offsetof(CXMCamera, m_szPWD), 0, "camera's password."},
		{"userID", T_STRING, offsetof(CXMCamera, m_lUserID), 0, "camera's userID."},
		{"playhandle", T_STRING, offsetof(CXMCamera, m_iPlayhandle), 0, "camera's playhandle."},
		{"absPath", T_STRING, offsetof(CXMCamera, m_absPath), 0, "camera's absPath."},

		{NULL, NULL, NULL, 0, NULL}};

//////////////////////////////////////////////////////////////
//3. Definition of constructor,destructor and some interner functions.
// Refer to PyTypeObject page of python API reference.

// constructor
#if PY_MAJOR_VERSION >= 3

static int CXMCamera_init(CXMCamera *Self, PyObject *pArgs)
#else
static void CXMCamera_init(CXMCamera *Self, PyObject *pArgs)
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

	// system("mkdir Temp");
#if PY_MAJOR_VERSION >= 3

	return 0;
#else
	return;
#endif
}

// destructor
static void CXMCamera_Destruct(CXMCamera *Self)
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
static PyObject *CXMCamera_Str(CXMCamera *Self)
{
	char sz[256] = {0};
	snprintf(sz, 255,
			 "IP       : %s\r\n"
			 "Port     : %ld\r\n"
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
static PyObject *CXMCamera_Repr(CXMCamera *Self)
{
	return CXMCamera_Str(Self);
}

////////////////////////////////////////////////////////////
// Getter / Setter
//
static PyObject *CXMCamera_GetIP(CXMCamera *Self)
{
	return Py_BuildValue("s", Self->m_szIP);
}

static PyObject *CXMCamera_GetPort(CXMCamera *Self)
{
	return Py_BuildValue("i", Self->m_nPort);
}

static PyObject *CXMCamera_GetUserName(CXMCamera *Self)
{
	return Py_BuildValue("s", Self->m_szUserName);
}

static PyObject *CXMCamera_GetPassword(CXMCamera *Self)
{
	return Py_BuildValue("s", Self->m_szPWD);
}

static PyObject *CXMCamera_GetParameters(CXMCamera *Self)
{
	return Py_BuildValue("(siss)", Self->m_szIP, Self->m_nPort, Self->m_szUserName, Self->m_szPWD);
}

static PyObject *CXMCamera_SetParameters(CXMCamera *Self, PyObject *pArgs)
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

static PyObject *CXMCamera_PrintInfo(CXMCamera *Self)
{
	std::cout << "The XMCamera's properties as follows:" << endl
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

static PyObject *CXMCamera_Login(CXMCamera *Self)
{
	// system("rm -f ./Temp/*.*");

	H264_DVR_Init(NULL, NULL);
	printf("H264_DVR_Init\n");

	initFfmpeg();

	H264_DVR_DEVICEINFO OutDev;
	memset(&OutDev, 0, sizeof(OutDev));
	int nError = 0;
	Self->m_lUserID = H264_DVR_Login(Self->m_szIP, Self->m_nPort, Self->m_szUserName, Self->m_szPWD, (LPH264_DVR_DEVICEINFO)(&OutDev), &nError, NULL);

	printf("g_LoginID=%d,nError:%d\n", Self->m_lUserID, nError);

	if (Self->m_lUserID > 0)
	{
		printf("**************login ok***************\n");
		return Py_BuildValue("i", HPR_OK);
	}
	else
	{
		printf("**************login wrong************\n");
		return Py_BuildValue("i", HPR_ERROR);
	}
}

static PyObject *CXMCamera_Open(CXMCamera *Self)
{
	if (Self->m_lUserID > 0)
	{
		H264_DVR_CLIENTINFO playstru;

		playstru.nChannel = 0;
		playstru.nStream = 0;
		playstru.nMode = 0;

		Self->m_iPlayhandle = H264_DVR_RealPlay(Self->m_lUserID, &playstru);

		if (Self->m_iPlayhandle == 0)
		{
			printf("start RealPlay wrong!\n");
		}
		else
		{
			printf("start RealPlay ......\n");

			H264_DVR_SetRealDataCallBack_V2(Self->m_iPlayhandle, RealDataCallBack_V2, 0);
			printf("start RealPlay ok!\n");

			return Py_BuildValue("i", HPR_OK);
		}
	}
	return Py_BuildValue("i", HPR_ERROR);
}

static PyObject *CXMCamera_IsOpen(CXMCamera *Self)
{
	int nErr = 0;
	return Py_BuildValue("i", nErr);
}

static PyObject *CXMCamera_Close(CXMCamera *Self)
{
	if (H264_DVR_StopRealPlay(Self->m_iPlayhandle))
	{
		printf("stop realPlay ok\n");
	}

	if (Self->m_lUserID > 0)
	{
		H264_DVR_Logout(Self->m_lUserID);
		printf("Logout success!!!\n");
	}
	H264_DVR_Cleanup();

	printf("**************OVER************\n");

	return Py_BuildValue("i", HPR_OK);
}

// query camera frame, return an image in an numpy array
static PyObject *CXMCamera_Read(CXMCamera *Self)
{
	int nErr = 0;
	return Py_BuildValue("i", nErr);
}

// query camera frame, return an image in an numpy array
static PyObject *CXMCamera_StratParsingStreamWithFFmpeg(CXMCamera *Self)
{
	flag = true;
	Py_XINCREF(Py_None);
	return Py_None;
}

// query camera frame, return an image in an numpy array
static PyObject *CXMCamera_StopParsingStreamWithFFmpeg(CXMCamera *Self)
{
	flag = false;
	Py_XINCREF(Py_None);
	return Py_None;
}

// query camera frame, return an image in an numpy array
static PyObject *CXMCamera_GetDetentionFrame(CXMCamera *Self)
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

static PyObject *CXMCamera_GetCurrentionFrame(CXMCamera *Self)
{
	printf("start\n");

	// int i = 0;

	// while (++i < 50)
	// {

	// 	cout << "OK----" <<H264_DVR_GetLastError() << endl;
	// 	// printf("KEY!\n");
	// }

	// while (true)
	// {
	// 	if (rif != 0 && avcodec_receive_frame(dCodecCtx, pYUVFrame) == 0)
	// 	{
	// 		Mat cvImg;

	// 		AVFrame2Img(pYUVFrame, cvImg);
	// 	}

	// 	// Mat mat(dCodecCtx->height, dCodecCtx->width, CV_8UC3, pYUVFrame->data[0], pYUVFrame->linesize[0]);
	// 	// imshow("frame", img);
	// 	// waitKey(10);
	// }
	printf("end\n");

	int nErr = 0;
	return Py_BuildValue("i", nErr);
}

// typedef unsigned char BYTE;

// query camera frame, return an image in an numpy array
static PyObject *
CXMCamera_QueryFrame(CXMCamera *Self, PyObject *args)
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
static PyMethodDef CXMCamera_MethodMembers[] =
	{
		{"GetIP", (PyCFunction)CXMCamera_GetIP, METH_NOARGS, "Get the IP address of instance."},
		{"GetPort", (PyCFunction)CXMCamera_GetPort, METH_NOARGS, "Get the port number of instance."},
		{"GetUserName", (PyCFunction)CXMCamera_GetUserName, METH_NOARGS, "Get the user name of isntance."},
		{"GetPassword", (PyCFunction)CXMCamera_GetPassword, METH_NOARGS, "Get the password of instance."},
		{"GetParameters", (PyCFunction)CXMCamera_GetParameters, METH_NOARGS, "Get all the properties of isntance."},
		{"SetParameters", (PyCFunction)CXMCamera_SetParameters, METH_VARARGS, "Set the properties of instance."},
		{"PrintInfo", (PyCFunction)CXMCamera_PrintInfo, METH_NOARGS, "Print all information of instance."},

		{"login", (PyCFunction)CXMCamera_Login, METH_NOARGS, "login the camera"},
		{"open", (PyCFunction)CXMCamera_Open, METH_NOARGS, "open the camera"},
		{"isopen", (PyCFunction)CXMCamera_IsOpen, METH_NOARGS, "is the camera opened."},
		{"close", (PyCFunction)CXMCamera_Close, METH_NOARGS, "close the camera."},
		{"read", (PyCFunction)CXMCamera_Read, METH_NOARGS, "query frame from camera."},
		{"queryframe", (PyCFunction)CXMCamera_QueryFrame, METH_VARARGS, "query frame from camera."},

		{"StratParsingStream", (PyCFunction)CXMCamera_StratParsingStreamWithFFmpeg, METH_NOARGS, "Strat Parsing Stream With FFmpeg."},
		{"StopParsingStream", (PyCFunction)CXMCamera_StopParsingStreamWithFFmpeg, METH_NOARGS, "Stop Parsing Stream With FFmpeg."},
		{"GetDetentionFrame", (PyCFunction)CXMCamera_GetDetentionFrame, METH_NOARGS, "Get Detention Frame (1500ms From Current)."},
		{"GetCurrentionFrame", (PyCFunction)CXMCamera_GetCurrentionFrame, METH_NOARGS, "Get Currention Frame (100ms From Current)."},

		{NULL, NULL, NULL, NULL}};

////////////////////////////////////////////////////////////
// construct a PyTypeObject, which is the pythoEn object
//
// static PyTypeObject CXMCamera_ClassInfo =
PyTypeObject CXMCamera_ClassInfo =
	{
		PyVarObject_HEAD_INIT(NULL, 0) "HikSDK.XMCamera", // __class__
		sizeof(CXMCamera),								  // used by PyObject_New
		0,
		(destructor)CXMCamera_Destruct, // deconstructor
		0,
		0,
		0,
		0,
		(reprfunc)CXMCamera_Repr, // repr
		0,
		0,
		0,
		0,
		0,
		(reprfunc)CXMCamera_Str, // Str/print
		0,
		0,
		0,
		Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
		"CXMCamera Objects---Extensioned by C++!", // __doc__
		0,
		0,
		0,
		0,
		0,
		0,
		CXMCamera_MethodMembers, // all member functions
		CXMCamera_DataMembers,   // all data members
		0,
		0,
		0,
		0,
		0,
		0,
		(initproc)CXMCamera_init, // constructor
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
	CXMCamera_ClassInfo.tp_new = PyType_GenericNew; // fuction "new" --- create new instance

	/////////////////////////////////////////////////////
	// PyType_Ready: initialize the object type object
	// return:
	// 0 -- success
	// failed --- -1 and throws ex
	if (PyType_Ready(&CXMCamera_ClassInfo) < 0)
		return NULL;

	PyObject* pReturn = PyModule_Create(&ModuleInfo);          // create module info block
	if (pReturn == 0)
		return NULL;

	Py_INCREF(&ModuleInfo);
	PyModule_AddObject(pReturn, "XMCamera", (PyObject*)&CXMCamera_ClassInfo); // export in module Dictionary
	return pReturn;
}
*/
