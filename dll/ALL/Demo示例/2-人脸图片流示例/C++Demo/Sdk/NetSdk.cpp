#include "NetSdk.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef  __WIN__
#include <sys/ioctl.h>
#include <sys/socket.h> 
#include <net/if.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/times.h>
#include <sys/time.h>
#include <stdint.h>
#include <dlfcn.h>
#endif

void* g_pvInstance = NULL;

pNetClient_Startup_V4 NetClient_Startup_V4 = NULL;
pNetClient_Cleanup  NetClient_Cleanup = NULL;
pNetClient_Logon NetClient_Logon = NULL;
pNetClient_Logon_V4 NetClient_Logon_V4 = NULL;
pNetClient_Logoff NetClient_Logoff = NULL;
pNetClient_GetChannelNum NetClient_GetChannelNum = NULL;
pNetClient_StartRecv  NetClient_StartRecv = NULL;
pNetClient_StartRecvEx NetClient_StartRecvEx = NULL;
pNetClient_SetFullStreamNotify_V4 NetClient_SetFullStreamNotify_V4 = NULL;
pNetClient_StartPlay  NetClient_StartPlay = NULL;
pNetClient_StopPlay NetClient_StopPlay = NULL;
pNetClient_StartCaptureData NetClient_StartCaptureData = NULL;
pNetClient_StopCaptureData NetClient_StopCaptureData = NULL;
pNetClient_StopRecv NetClient_StopRecv = NULL;
pNetClient_SetNotifyFunction_V4  NetClient_SetNotifyFunction_V4 = NULL;
pNetClient_StartRecvNetPicStream NetClient_StartRecvNetPicStream = NULL;
pNetClient_StopRecvNetPicStream NetClient_StopRecvNetPicStream = NULL;
pNetClient_GetDsmRegstierInfo NetClient_GetDsmRegstierInfo = NULL;
pNetClient_GetLogonStatus NetClient_GetLogonStatus = NULL;

void* DemoLoadLibrary(char* _pcLibrary)
{
#ifdef  __WIN__
	return LoadLibrary(_pcLibrary);
#else
	dlopen(_pcLibrary, RTLD_LAZY);
#endif
}

void* DemoExportInterface(void* _pvHandle, const char* _pcSymbol)
{
#ifdef  __WIN__
	return GetProcAddress((HMODULE)_pvHandle, _pcSymbol);
#else
	return dlsym(_pvHandle, _pcSymbol);
#endif
}

void DemoReleaseLibrary(void* _pvHandle)
{
#ifdef  __WIN__
	FreeLibrary((HMODULE)_pvHandle);
#else
	dlclose(_pvHandle);
#endif
}

int LoadLib()
{
	if (g_pvInstance)
	{
		return 0;
	}
	else
	{
		g_pvInstance = DemoLoadLibrary("NVSSDK.dll");
		if (NULL == g_pvInstance)
		{
			return -1;
		}
	}

	NetClient_Startup_V4 = (pNetClient_Startup_V4)DemoExportInterface(g_pvInstance, "NetClient_Startup_V4");
	NetClient_Cleanup = (pNetClient_Cleanup)DemoExportInterface(g_pvInstance, "NetClient_Cleanup");
	NetClient_Logon = (pNetClient_Logon)DemoExportInterface(g_pvInstance, "NetClient_Logon");
	NetClient_Logon_V4 = (pNetClient_Logon_V4)DemoExportInterface(g_pvInstance, "NetClient_Logon_V4");
	NetClient_GetLogonStatus = (pNetClient_GetLogonStatus)DemoExportInterface(g_pvInstance, "NetClient_GetLogonStatus");
	NetClient_Logoff = (pNetClient_Logoff)DemoExportInterface(g_pvInstance, "NetClient_Logoff");
	NetClient_GetChannelNum = (pNetClient_GetChannelNum)DemoExportInterface(g_pvInstance, "NetClient_GetChannelNum");
	NetClient_StartRecv = (pNetClient_StartRecv)DemoExportInterface(g_pvInstance, "NetClient_StartRecv");
	NetClient_StartRecvEx = (pNetClient_StartRecvEx)DemoExportInterface(g_pvInstance, "NetClient_StartRecvEx");
	NetClient_SetFullStreamNotify_V4 = (pNetClient_SetFullStreamNotify_V4)DemoExportInterface(g_pvInstance, "NetClient_SetFullStreamNotify_V4");
	NetClient_StartPlay = (pNetClient_StartPlay)DemoExportInterface(g_pvInstance, "NetClient_StartPlay");
	NetClient_StopPlay = (pNetClient_StopPlay)DemoExportInterface(g_pvInstance, "NetClient_StopPlay");
	NetClient_StartCaptureData = (pNetClient_StartCaptureData)DemoExportInterface(g_pvInstance, "NetClient_StartCaptureData");
	NetClient_StopCaptureData = (pNetClient_StopCaptureData)DemoExportInterface(g_pvInstance, "NetClient_StopCaptureData");
	NetClient_StopRecv = (pNetClient_StopRecv)DemoExportInterface(g_pvInstance, "NetClient_StopRecv");
	NetClient_SetNotifyFunction_V4 = (pNetClient_SetNotifyFunction_V4)DemoExportInterface(g_pvInstance, "NetClient_SetNotifyFunction_V4");
	NetClient_StartRecvNetPicStream = (pNetClient_StartRecvNetPicStream)DemoExportInterface(g_pvInstance, "NetClient_StartRecvNetPicStream");
	NetClient_StopRecvNetPicStream = (pNetClient_StopRecvNetPicStream)DemoExportInterface(g_pvInstance, "NetClient_StopRecvNetPicStream");
	NetClient_GetDsmRegstierInfo = (pNetClient_GetDsmRegstierInfo)DemoExportInterface(g_pvInstance, "NetClient_GetDsmRegstierInfo");

	return 0;
}

void FreeLib()
{
	if (g_pvInstance != NULL)
	{
		DemoReleaseLibrary(g_pvInstance);
		g_pvInstance = NULL;
	}
}

