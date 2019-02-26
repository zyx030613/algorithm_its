#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "NetSdk.h"

#define MAX_SAVE_PCTURE_COUNT	20000
const char g_cPlateColor[][64] = {"未知", "蓝底白字", "黄底黑字", "白底黑字", "黑底白字", "绿底白字"};
const char g_cCarColor[][64] = {"白色", "红色", "黄色", "黄色", "蓝色", "绿色", "绿色", "紫色", "粉色", "黑色"
								, "红色", "黄色", "黄色", "灰色", "黄色", "蓝色", "蓝色", "绿色", "绿色", "白色"
								, "绿色", "青色", "黄色", "红色", "蓝色", "蓝色", "灰色", "紫色", "紫色", "棕色"
								, "棕色", "棕色"};

#ifndef __WIN__
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h> 
	int gets_s(char *_pcStr, int _iCount);
	#define min(a,b)	(((a) < (b)) ? (a) : (b))
#else
	#include<direct.h>
	void usleep(int _iMicroSecond);
#endif

int g_iLogonID = -1;
unsigned int g_uiRecvID = -1;
int to_int_def(const char* _pstrFrom, int _iDef = 0);
void LogonDevice(int _iLogonType);
void StartRecvPicture(void);
void StopRecvPicture(void);
void Notify_Main(int _iLogonID, long  _lWparam, void*  _pvLParam, void* _pvUsr);
int __stdcall Notify_NetPicStream(unsigned int _uiRecvID, long _lCommand, void* _pvCallBackInfo, int _BufLen, void* _pvUser);

FILE* OpenFile(char* _pcPath)
{
	FILE* pFile  = NULL;
	fopen_s(&pFile, _pcPath, "wb");
	return pFile;
}

int main(int argc,char *argv[])
{
	LoadLib();//初始化接口库

	int iLogonType = SERVER_NORMAL;
	char cTemp[8] = {0};
	fprintf(stderr, "Please input LogonType: 0----Normal  1----Active\n");
	gets_s(cTemp, 8);
	iLogonType = to_int_def(cTemp, 0);
	if (SERVER_ACTIVE == iLogonType)
	{
		fprintf(stderr, "Please input listening port:");
		gets_s(cTemp, 8);
		int iLlisteningPort = to_int_def(cTemp, 0);
		NetClient_Startup_V4(iLlisteningPort, 0, 0);//初始化SDK
	}
	else
	{
		NetClient_Startup_V4(0, 0, 0);//初始化SDK
	}
	
	//注册主回调函数
	NetClient_SetNotifyFunction_V4(Notify_Main, NULL, NULL, NULL, NULL);

	//登录设备
	LogonDevice(iLogonType);

	//在主回调Notify_Main里收到登陆成功的消息后开始接收图片流
	//创建存储图片目录
#ifdef __WIN__
	_mkdir(".\\PicStream");
#else
	mkdir(".//PicStream", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); 
#endif

	getchar();//等待用户输入

	StopRecvPicture(); //停止接收图片流
	NetClient_Logoff(g_iLogonID);//注销用户
	NetClient_Cleanup();//释放SDK资源

	return 0;
}

int to_int_def(const char* _pstrFrom, int _iDef)
{
	if(NULL == _pstrFrom)
	{
		return _iDef;
	}

	for (size_t i=0; i<strlen(_pstrFrom); i++)
	{
		if (!isdigit(_pstrFrom[i]))
		{
			if(i == 0 && _pstrFrom[i] == '-' && strlen(_pstrFrom) > 1)
			{
				continue;
			}
			return _iDef;
		}
	}

	return atoi(_pstrFrom);
}

#ifndef __WIN__
int gets_s(char *_pcStr, int _iCount)
{
	if (_pcStr == NULL)
		return -1;

	char* pcRet = fgets(_pcStr, _iCount, stdin);
	size_t uiLen = strlen(_pcStr);
	if (pcRet == NULL || uiLen == 0)
		return -2;

	if (_iCount - 1 > (int)uiLen || _pcStr[uiLen-1] == '\n')
	{
		_pcStr[uiLen-1] = '\0';
	}

	stdin->_IO_read_ptr = stdin->_IO_read_end;
	return 0;
}
#else	
void usleep(int _iMicroSecond)
{
	if (_iMicroSecond < 1000 && _iMicroSecond != 0)
	{
		_iMicroSecond = 1000;
	}
	Sleep(_iMicroSecond/1000);
}
#endif

void LogonDevice(int _iLogonType)
{
	char cIP[16] = {0};
	char cUserName[16] = {0};
	char cPassword[16] = {0};
	char cProductID[32] = {0};

	fprintf(stderr, "Please input user name: ");
	gets_s(cUserName, 16);
	fprintf(stderr, "Please input password: ");
	gets_s(cPassword, 16);

	LogonPara tNormal = {0};
	LogonActiveServer tActive = {0};
	void* pvPara = NULL;
	int iBufLen = 0;
	if (SERVER_ACTIVE == _iLogonType)
	{
		fprintf(stderr, "Please input ProductID: ");
		gets_s(cProductID, 32);
		tActive.iSize = sizeof(LogonActiveServer);
		strcpy_s(tActive.cUserName, sizeof(tActive.cUserName), cUserName);
		strcpy_s(tActive.cUserPwd, sizeof(tActive.cUserPwd), cPassword);
		strcpy_s(tActive.cProductID, sizeof(tActive.cProductID), cProductID);
		pvPara = &tActive;
		iBufLen = sizeof(LogonActiveServer);

		DsmOnline tOnline = {0};
		tOnline.iSize = sizeof(DsmOnline);
		strncpy_s(tOnline.cProductID, cProductID, LEN_32);
		NetClient_GetDsmRegstierInfo(DSM_CMD_GET_ONLINE_STATE, &tOnline, sizeof(DsmOnline));
		int iOutTime = 0;
		while (DSM_STATE_ONLINE != tOnline.iOnline)
		{
			if (iOutTime >= 20)
			{
				fprintf(stderr, "Device not register!\n");
				break;
			}
			usleep(1000 * 1000);
			NetClient_GetDsmRegstierInfo(DSM_CMD_GET_ONLINE_STATE, &tOnline, sizeof(DsmOnline));
			iOutTime++;
		}
	}
	else
	{
		fprintf(stderr, "Please input server IP: ");
		gets_s(cIP, 16);
		tNormal.iSize = sizeof(LogonPara);
		tNormal.iNvsPort = 3000;
		strcpy_s(tNormal.cNvsIP, sizeof(tNormal.cNvsIP), cIP);
		strcpy_s(tNormal.cUserName, sizeof(tNormal.cUserName), cUserName);
		strcpy_s(tNormal.cUserPwd, sizeof(tNormal.cUserPwd), cPassword);
		strcpy_s(tNormal.cCharSet, sizeof(tNormal.cCharSet), "UTF-8");
		pvPara = &tNormal;
		iBufLen = sizeof(LogonPara);
	}

	g_iLogonID = NetClient_Logon_V4(_iLogonType, pvPara, iBufLen);
	if(g_iLogonID < 0)
	{
		fprintf(stderr,"[NetClient_Logon_V4] fail! %d\n", g_iLogonID);
	}
}

void StartRecvPicture(void)
{
	NetPicPara tPara = {0};
	tPara.iStructLen = sizeof(NetPicPara);
	tPara.iChannelNo = 0;
	tPara.cbkPicStreamNotify = Notify_NetPicStream;
	tPara.pvUser = NULL;
	int iRet = NetClient_StartRecvNetPicStream(g_iLogonID, &tPara, sizeof(NetPicPara), &g_uiRecvID);
	if (0 != iRet)
	{
		fprintf(stderr,"[NetClient_StartRecvNetPicStream] fail!");
	}
}

void StopRecvPicture(void)
{
	int iRet = NetClient_StopRecvNetPicStream(g_uiRecvID);
	if (0 != iRet)
	{
		fprintf(stderr,"[NetClient_StopRecvNetPicStream] fail!");
	}
}

void Notify_Main(int _iLogonID, long  _lWparam, void*  _pvLParam, void* _pvUsr)
{
	int iMsgType = LOWORD(_lWparam);
	int iMsgValue = (int)_pvLParam;
	switch (iMsgType)
	{
	case WCM_LOGON_NOTIFY:
		{
			printf("WCM_LOGON_NOTIFY!\n");
			if((LOGON_SUCCESS == iMsgValue) && (-1 == g_uiRecvID))
			{
				printf("Logon success!\n");
				StartRecvPicture(); //开始接收图片流
			}
			else
			{
				printf("Logon failed!\n");
			}
		}
		break;
	default:
		break;
	}
}

int g_iCount = 0;
int __stdcall Notify_NetPicStream(unsigned int _uiRecvID, long _lCommand, void* _pvCallBackInfo, int _BufLen, void* _pvUser)
{
	if (NULL == _pvCallBackInfo)
	{
		return -1;
	}

	if (_uiRecvID != g_uiRecvID)
	{
		return -1;
	}

	if(NET_PICSTREAM_CMD_ITS != _lCommand)
	{
		return 0;
	}

	if (g_iCount++ >= MAX_SAVE_PCTURE_COUNT)
	{
		printf("save picture over 20000!\n");
		return -1;
	}

	ItsPicStream tIts = {0};
	memcpy(&tIts, _pvCallBackInfo, min(_BufLen, (int)sizeof(ItsPicStream)));
	//车牌颜色
	int iPlateColor = tIts.iPlateColor;
	char cPlateColor[32] = {0};
	if (iPlateColor < 0 || iPlateColor > (int)(sizeof(g_cPlateColor) / 64))
	{
		iPlateColor = 0;		
	}
	sprintf_s(cPlateColor, "%s", g_cPlateColor[iPlateColor]);
	
	//车身颜色
	int iCarColor = tIts.iCarColor;
	char cCarColor[32] = "未知";
	if (iCarColor >= 0 && iCarColor < sizeof(g_cCarColor) / 64)
	{
		sprintf_s(cCarColor, "%s", g_cCarColor[iPlateColor]);
	}

	//输出信息
	char cMsg[1024] = {0};
	sprintf_s(cMsg, "picture info:iPicCount(%d),cCameraIP(%s),cPlate(%s),PlateColor(%s),CarColor(%s)\n", tIts.iPicCount, tIts.cCameraIP, tIts.cPlate, cPlateColor, cCarColor);
	printf(cMsg);

	//保存抓拍图片	
	for (int i = 0; i < tIts.iPicCount && i < MAX_ITS_CAP_PIC_COUNT; ++i)
	{
		if (NULL == tIts.ptPicData[i])
		{
			continue;
		}
		PicData tData = {0};
		memcpy(&tData, tIts.ptPicData[i], min(tIts.iSize, sizeof(PicData)));
		char cFileName[256] = {0};
		sprintf_s(cFileName, ".//PicStream//ItsPic_%s_No%d_Time(2%03d%02d%02d%02d%02d%02d%d)_%d.jpg", tIts.cCameraIP, g_iCount
		, tData.tPicTime.uiYear, tData.tPicTime.uiMonth,  tData.tPicTime.uiDay, tData.tPicTime.uiHour
		, tData.tPicTime.uiMinute, tData.tPicTime.uiSecondsr, tData.tPicTime.uiMilliseconds, i);
		FILE* pFile  = OpenFile(cFileName);
		if (NULL != pFile)
		{
			fwrite(tData.pcPicData, tData.iDataLen, 1, pFile);
			fclose(pFile);
			pFile = NULL;
		}
	}
	//保存车牌图片
	if (tIts.iPlatCount > 0 && NULL != tIts.ptPlatData)
	{
		PicData tData = {0};
		memcpy(&tData, tIts.ptPlatData, min(tIts.iSize, sizeof(PicData)));
		char cFileName[256] = {0};
		sprintf_s(cFileName, ".//PicStream//ItsPlat_%s_No%d-CP.jpg", tIts.cCameraIP, g_iCount);
		FILE* pFile  = OpenFile(cFileName);
		if (NULL != pFile)
		{
			fwrite(tData.pcPicData, tData.iDataLen, 1, pFile);
			fclose(pFile);
			pFile = NULL;
		}
	}
	//保存人脸图片
	for (int i = 0; i < tIts.iFaceCount && i < MAX_ITS_CAP_FACE_COUNT; ++i)
	{
		if (NULL == tIts.ptFaceData[i])
		{
			continue;
		}

		PicData tData = {0};
		memcpy(&tData, tIts.ptFaceData[i], min(tIts.iSize, sizeof(PicData)));

		char cFileName[256] = {0};
		sprintf_s(cFileName, ".//PicStream//ItsFace_%s_No%d-RL_%d.jpg", tIts.cCameraIP, g_iCount,i);
		FILE* pFile  = OpenFile(cFileName);
		if (NULL != pFile)
		{
			fwrite(tData.pcPicData, tData.iDataLen, 1, pFile);
			fclose(pFile);
			pFile = NULL;
		}
	}
	return 0;
}



