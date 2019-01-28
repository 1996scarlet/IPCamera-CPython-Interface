#ifndef _PLAYM4_H_ 
#define _PLAYM4_H_
#if defined(__APPLE__)
	#include"ApplePlayM4.h"
#elif defined(__linux__)
	#include"LinuxPlayM4.h"
#elif defined(ANDROID)
	#include"LinuxPlayM4.h"
#elif defined(WIN32)
	#include"WindowsPlayM4.h"
#endif


#endif //_PLAYM4_H_
