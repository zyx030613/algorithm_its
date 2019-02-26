
#ifndef __H_DOWNLOAD_MP4_H__
#define __H_DOWNLOAD_MP4_H__

#include "../Common/CommonFun.h"
#include "../Include/NVSSDK_INTERFACE.h"
#include "../Include/MP4_INTERFACE.h"

using namespace NVSSDK_INTERFACE;
using namespace MP4_INTERFACE;

#define TEMP_SRC_FILE_EXTENSION		".tmp"

#define WM_DOWNLOAD_FINSH_MSG          (WM_USER + 0x3021)

enum FILE_DOWNLOAD_STATUS
{
	n_DLStatus_Reserved = -1,	//未知状态
	n_DLStatus_wait     =  0,	//准备下载
	n_DLStatus_Doing,			//正在下载
	n_DLStatus_Pause,			//暂停下载
	n_DLStatus_DL_Complete,		//下载成功
	n_DLStatus_DL_Fail,			//下载失败
	n_DLStatus_Converting,		//正在转换
	n_DLStatus_Convert_Complete,//转换成功
	n_DLStatus_Convert_Fail,	//转换失败
	n_DLStatus_Finish			//全部完成
};

enum SDV_CONVERT_STATUS
{
	CONVERT_STATUS_READY = 0,	//准备转换
	CONVERT_STATUS_SUCCESS,		//转换成功
	CONVERT_STATUS_FAILED		//转换失败
};

#define DOWN_LOAD_SPEED_PAUSE			0
#define DOWN_LOAD_SPEED_START			16
#define DOWN_LOAD_SPEED_32				32
#define DOWN_LOAD_POS_RESERVE			-1

#define RATIO_BYTE_CONVERT				1024

class CLS_DownloadFileMp4
{
public:
	CLS_DownloadFileMp4(HWND _pParent, int _iLogonId, DOWNLOAD_FILE _tDownLoadInfo, BOOL _blBreakContinue = FALSE);
	~CLS_DownloadFileMp4();

private:
	int				m_iLogonId;					//登陆ID
	DOWNLOAD_FILE	m_tDownLoadInfo;			//下载信息
	int				m_iConnectId;				//连接ID
	int				m_iDownLoadStatus;			//下载状态
	BOOL			m_blBreakContinue;			//断点续传
	int				m_iDownLoadPos;				//下载进度
	BOOL			m_blKeepSdvFile;
	HWND			m_hParents;

public:
	static unsigned int __stdcall FileConvertThread(LPVOID _Param);

public:
	int	StartDownLoad(BOOL blRestart = FALSE);					//开始下载
	int StartBreakContineDownLoad();
	int StopDowmLoad(BOOL _blDownLoadSuccess = TRUE, BOOL _blKeepSdvFile = FALSE, BOOL _blConvertToMp4 = TRUE);	//停止下载
	BOOL CheckDownLoadInfo(int _iLogonId, char* _pcRemoteFileName);	//判断是否为当前下载
	BOOL CheckDownLoadInfo(int _iConnectId);						//判断是否为当前下载
	int SetDownLoadSpeed(DOWNLOAD_CONTROL _tDownLoadControl);		//控制下载速度0：暂停下载, 16:默认下载速度开始下载
	char* GetDownLoadProgress(char* _pcProgress, int _iLen);		//获取下载进度
	BOOL CheckBreakContinue();
	int GetConnectId();		
	int GetLogonId();
	CString GetFileName();										//获取本地文件，全名称
	int GetDownLoadStatus();									//获取下载状态
	int InnerDealConvertResult(int _iConvertSatus, BOOL _blKeepSdvFile);

};

#endif
