#pragma once
#include "NetClientTypes.h"

static HINSTANCE s_hInstance = NULL;		//	NetVideoConfig.dll¾ä±ú

enum PARAM_TYPE
{
	PARAM_TYPE_MIN = 0,
	PARAM_TYPE_LANGUAGE = PARAM_TYPE_MIN,
	PARAM_TYPE_LOG_OUTPUT_LEVEL,
	PARAM_TYPE_REC_FILE_TYPE,
	PARAM_TYPE_SAVE_PATH,
	PARAM_TYPE_HIDE_ENCRYPT_NODE,
	PARAM_TYPE_SET_VIDEO_DECRYPT,
	PARAM_TYPE_SET_SIP_INFO,
	PARAM_TYPE_LOCAL_SAVE_PATH,
	PARAM_TYPE_PREVIEW_PIC_PATH,
	PARAM_TYPE_PLAYBACK_PIC_PATH,
	PARAM_TYPE_RECEDIT_PATH,
	PARAM_TYPE_DOWNLOAD_PATH,
	PARAM_TYPE_PROTOCAL_TYPE,
	PARAM_TYPE_WINDOW_RECT,
	PARAM_TYPE_SHOW_HAND,
	PARAM_TYPE_SHOW_WINDOW,
	PARAM_TYPE_MAX
};

#define CFG_ERR_INVALID_PARAM		(-1)
#define	LEN_IP	(16)
typedef struct tagSipInfo
{
	char cSipIp[LEN_IP+1];
	int	iPort;
	char cSipServerID[LEN_64];
	char cSipDeviceID[LEN_64];
	char cUserName[LEN_64];
	char cPassWord[LEN_64];
	int iSIP_RegVality;
	int iSIP_Keepalive;
	int iSIP_HeartInterval;
	int iSIP_HeartTimes;
	int iEnable;
}SipInfo, *pSipInfo;

int LoadNetVideoConfig();
int FreeNetVideoConfig();

//NetVideoConfig.dll Interface

typedef int (__stdcall	*pfNetVideo_ShowConfigWindow)(CLIENTINFO *_pClientInfo, MAIN_NOTIFY _cbkMainNotify, ALARM_NOTIFY_EX _cbkAlarmNotify, PARACHANGE_NOTIFY_EX _cbkParaChangeNotify, void* _pNotifyUserData);
extern pfNetVideo_ShowConfigWindow NetVideo_ShowConfigWindow;

typedef int (__stdcall	*pfNetVideo_GetParam)(int _iType,void *_pValue,int _iLen);
extern pfNetVideo_GetParam NetVideo_GetParam;

typedef int (__stdcall	*pfNetVideo_SetParam)(int _iType,void *_pValue,int _iLen);
extern pfNetVideo_SetParam NetVideo_SetParam;



