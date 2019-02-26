#pragma once
#include "../Common/CommonFun.h"
#include "PublicDef.h"


namespace PLAYSDK_INTERFACE
{
	int 	LoadPLAYSDK(const char* _pszPath = "playsdkm4.dll");
	bool    ReleasePLAYSDK();

	TYPEDEF_FUNCTION2(TC_CreateSystem)(HWND  hwnd);
	DECLARE_FUNCTION(TC_CreateSystem);
	TYPEDEF_FUNCTION2(TC_DeleteSystem)();
	DECLARE_FUNCTION(TC_DeleteSystem);
	TYPEDEF_FUNCTION2(TC_RegisterNotifyPlayToEnd)(void (*PlayEndFun)(int));
	DECLARE_FUNCTION(TC_RegisterNotifyPlayToEnd);
	TYPEDEF_FUNCTION2(TC_CreatePlayerFromStream)(HWND _hWnd, unsigned char* _pucVideoHeadBuf, int _iHeadSize);
	DECLARE_FUNCTION(TC_CreatePlayerFromStream);
	TYPEDEF_FUNCTION2(TC_CreatePlayerFromFile)(HWND _hWnd,char* _cFileName,int _iDownloadBuffSz,int _iFileTrueSz, int *_iNowSz,int _iLastFrmNo,int* _iCompleteFlag);
	DECLARE_FUNCTION(TC_CreatePlayerFromFile);
	TYPEDEF_FUNCTION2(TC_DeletePlayer)(int ID);
	DECLARE_FUNCTION(TC_DeletePlayer);
	TYPEDEF_FUNCTION2(TC_SetPlayRect)(int ID,RECT *rcDraw);
	DECLARE_FUNCTION(TC_SetPlayRect);
	TYPEDEF_FUNCTION2(TC_SetPlayRectEx)(int ID,RECT *rcDraw,DWORD dwMask);
	DECLARE_FUNCTION(TC_SetPlayRectEx);
	TYPEDEF_FUNCTION2(TC_PlayAudio)(int ID);
	DECLARE_FUNCTION(TC_PlayAudio);
	TYPEDEF_FUNCTION2(TC_StopAudio)(int ID);
	DECLARE_FUNCTION(TC_StopAudio);
	TYPEDEF_FUNCTION2(TC_Play)(int ID);
	DECLARE_FUNCTION(TC_Play);
	TYPEDEF_FUNCTION2(TC_Stop)(int ID);
	DECLARE_FUNCTION(TC_Stop);
	TYPEDEF_FUNCTION2(TC_GetPlayingFrameNum)(int ID);
	DECLARE_FUNCTION(TC_GetPlayingFrameNum);
	TYPEDEF_FUNCTION2(TC_FastForward)(int _iID, int _iSpeed);
	DECLARE_FUNCTION(TC_FastForward);
	TYPEDEF_FUNCTION2(TC_GetFrameCount)(int ID);
	DECLARE_FUNCTION(TC_GetFrameCount);
	TYPEDEF_FUNCTION2(TC_GetVersion)(SDK_VERSION *_ver);
	DECLARE_FUNCTION(TC_GetVersion);
	TYPEDEF_FUNCTION2(TC_SeekEx)(int ID, int _iFrameNo);
	DECLARE_FUNCTION(TC_SeekEx);
	TYPEDEF_FUNCTION2(TC_RegisterEventMsg)(HWND _hEventWnd, UINT _uiEventMsg);
	DECLARE_FUNCTION(TC_RegisterEventMsg);
	TYPEDEF_FUNCTION2(TC_RegisterCommonEventCallBackEx)(pfCBCommonEventNotifyEx _pf, void* _lpUserData);
	DECLARE_FUNCTION(TC_RegisterCommonEventCallBackEx);
	TYPEDEF_FUNCTION2(TC_SetVideoDecryptKey)(int _iID, void* _lpBuf, int _iBufSize);
	DECLARE_FUNCTION(TC_SetVideoDecryptKey);
	TYPEDEF_FUNCTION2(TC_PutStreamToPlayer)(int _iID, unsigned char* _pucStreamData, int _iSize);
	DECLARE_FUNCTION(TC_PutStreamToPlayer);
	TYPEDEF_FUNCTION2(TC_GetStreamPlayBufferState)(int _iPlayerID, int * _piStreamBufferState);
	DECLARE_FUNCTION(TC_GetStreamPlayBufferState);
	TYPEDEF_FUNCTION2(TC_CreatePlayerFromVoD)(HWND _hWnd, unsigned char* _pucVideoHeadBuf, int _iHeadSize);
	DECLARE_FUNCTION(TC_CreatePlayerFromVoD);
	TYPEDEF_FUNCTION2(TC_CleanStreamBuffer)(int _iID);
	DECLARE_FUNCTION(TC_CleanStreamBuffer);
	TYPEDEF_FUNCTION2(TC_GetUserDataInfo)(int _iID, int _iFrameNO, int _iFlag, void*  _Buffer, int _iSize);
	DECLARE_FUNCTION(TC_GetUserDataInfo);
	TYPEDEF_FUNCTION2(TC_SetVoDPlayerOver)(int _iID);
	DECLARE_FUNCTION(TC_SetVoDPlayerOver);
	TYPEDEF_FUNCTION2(TC_SetModeRule)(int _iID, int _iModeRule);
	DECLARE_FUNCTION(TC_SetModeRule);
}