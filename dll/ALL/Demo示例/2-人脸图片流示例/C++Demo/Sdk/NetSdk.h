#ifndef NETSDK_H
#define NETSDK_H

#include "NetClientTypes.h"

typedef int (__stdcall *pNetClient_Startup_V4)(int _iServerPort, int _iClientPort, int _iWnd);
extern pNetClient_Startup_V4 NetClient_Startup_V4;

typedef int (__stdcall *pNetClient_Cleanup)();
extern pNetClient_Cleanup  NetClient_Cleanup;

typedef int (__stdcall *pNetClient_Logon)(char* _cProxy, char* _cIP, char* _cUserName, char* _cPassword, char* _pcProID, int _iPort);
extern pNetClient_Logon NetClient_Logon;

typedef int (__stdcall *pNetClient_Logon_V4)(int _iLogonType, void* _pvPara, int _iInBufferSize);
extern pNetClient_Logon_V4 NetClient_Logon_V4;

typedef int (__stdcall *pNetClient_Logoff)(int _iLogonID);
extern  pNetClient_Logoff NetClient_Logoff;

typedef int (__stdcall *pNetClient_GetChannelNum)(int _iLogonID, int* _iChannelNum);
extern pNetClient_GetChannelNum NetClient_GetChannelNum;

typedef int (__stdcall *pNetClient_StartRecv)(unsigned int *_ulConID, CLIENTINFO* _cltInfo, RECVDATA_NOTIFY _cbkDataArrive);
extern pNetClient_StartRecv  NetClient_StartRecv;

typedef int (__stdcall *pNetClient_StartRecvEx)(unsigned int *_ulConID,CLIENTINFO* _cltInfo,RECVDATA_NOTIFY_EX _cbkDataNotifyEx, void* _lpUserData);
extern pNetClient_StartRecvEx  NetClient_StartRecvEx;

typedef int (__stdcall *pNetClient_SetFullStreamNotify_V4)(unsigned int _uiRecvID, FULLFRAME_NOTIFY_V4 _cbkFullStream, int _iUserData);
extern pNetClient_SetFullStreamNotify_V4  NetClient_SetFullStreamNotify_V4;

typedef int (__stdcall *pNetClient_StopPlay)(unsigned int _ulID);
extern pNetClient_StopPlay NetClient_StopPlay;

typedef int (__stdcall *pNetClient_StartPlay)(unsigned int _ulID, int _hWnd, RECT _rcShow, unsigned int _iDecflag);
extern pNetClient_StartPlay  NetClient_StartPlay;

typedef int (__stdcall *pNetClient_StartCaptureData)(unsigned long _ulID);
extern pNetClient_StartCaptureData NetClient_StartCaptureData;

typedef int (__stdcall *pNetClient_StopCaptureData)(unsigned long _ulID);
extern pNetClient_StopCaptureData NetClient_StopCaptureData;

typedef int (__stdcall *pNetClient_StopRecv)(unsigned long _ulID);
extern pNetClient_StopRecv NetClient_StopRecv;

typedef int (__stdcall *pNetClient_SetNotifyFunction_V4)(MAIN_NOTIFY_V4 _MainNotify,
														 ALARM_NOTIFY_V4 _AlarmNotify, 
														 PARACHANGE_NOTIFY_V4  _ParaNotify,
														 COMRECV_NOTIFY_V4 _ComNotify,
														 PROXY_NOTIFY _ProxyNotify);
extern pNetClient_SetNotifyFunction_V4  NetClient_SetNotifyFunction_V4;

typedef int (__stdcall *pNetClient_StartRecvNetPicStream)(int _iLogonID, NetPicPara* _ptPara, int _iBufLen, unsigned int* _puiRecvID);
extern pNetClient_StartRecvNetPicStream NetClient_StartRecvNetPicStream;

typedef int (__stdcall *pNetClient_StopRecvNetPicStream)(unsigned int _uiRecvID);
extern pNetClient_StopRecvNetPicStream NetClient_StopRecvNetPicStream;

typedef int (__stdcall *pNetClient_GetDsmRegstierInfo)(int _iCommand, void* _pvBuf, int _iBufSize);
extern pNetClient_GetDsmRegstierInfo NetClient_GetDsmRegstierInfo;

typedef int (__stdcall *pNetClient_GetLogonStatus)(int _iLogonId);
extern pNetClient_GetLogonStatus NetClient_GetLogonStatus;

void* DemoLoadLibrary(char* _pcLibrary);
void* DemoExportInterface(void* _pvHandle, const char* _pcSymbol);
void DemoReleaseLibrary(void* _pvHandle);

int  LoadLib();
void FreeLib();

#endif
