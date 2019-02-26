#include "stdafx.h"
#include <shlwapi.h>
#include <process.h>
#include "RetValue.h"
#include "CLS_DownloadFileMp4.h"

CLS_DownloadFileMp4::CLS_DownloadFileMp4(HWND _pParent, int _iLogonId, DOWNLOAD_FILE _tDownLoadInfo, BOOL _blBreakContinue /*= FALSE*/ )
{
	m_iLogonId = _iLogonId;
	m_tDownLoadInfo = _tDownLoadInfo;
	m_blBreakContinue = _blBreakContinue;
	m_iConnectId  = -1;				
	m_iDownLoadStatus = n_DLStatus_wait;	
	m_blKeepSdvFile = TRUE;
	m_hParents = _pParent;
}

CLS_DownloadFileMp4::~CLS_DownloadFileMp4()
{
	StopDowmLoad(FALSE, FALSE, FALSE);
}

int CLS_DownloadFileMp4::StartDownLoad( BOOL blRestart /*= FALSE*/ )
{
	int iRet = NetClient_NetFileDownload((unsigned int*)&m_iConnectId, m_iLogonId, DOWNLOAD_CMD_FILE, &m_tDownLoadInfo, sizeof(DOWNLOAD_FILE));
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DownloadFileMp4::StartDownLoad] start failed! LogonId(%d), File(%s)", m_iLogonId, m_tDownLoadInfo.m_cLocalFilename);
	}

	//正在下载
	m_iDownLoadStatus = (iRet < RET_SUCCESS || m_iConnectId < 0) ? n_DLStatus_DL_Fail : n_DLStatus_Doing;
	return iRet;
}

int CLS_DownloadFileMp4::StopDowmLoad( BOOL _blDownLoadSuccess /*= TRUE*/, BOOL _blKeepSdvFile /*= FALSE*/, BOOL _blConvertToMp4 /*= TRUE*/ )
{
	m_blKeepSdvFile = _blKeepSdvFile;
	NetClient_NetFileStopDownloadFile(m_iConnectId);

	if (!_blDownLoadSuccess)
	{
		m_iDownLoadStatus = n_DLStatus_DL_Fail;
		//删除本地SDV文件
		DeleteFile(m_tDownLoadInfo.m_cLocalFilename);
		return RET_SUCCESS;
	}

	m_iDownLoadStatus = _blConvertToMp4 ? n_DLStatus_Converting : n_DLStatus_Finish;
	
	if (_blConvertToMp4)
	{
		HANDLE hConvertThread = (HANDLE)_beginthreadex(NULL, 0, FileConvertThread, (LPVOID)(this), 0, NULL);

		if (NULL == hConvertThread)
		{
			InnerDealConvertResult(CONVERT_STATUS_FAILED, TRUE);
		}

		if (NULL != hConvertThread)
		{
			CloseHandle(hConvertThread);
		}
	}

	return RET_SUCCESS;
}

BOOL CLS_DownloadFileMp4::CheckDownLoadInfo(int _iLogonId, char* _pcRemoteFileName )
{
	if (NULL == _pcRemoteFileName)
	{
		return FALSE;
	}

	BOOL blChk = FALSE;
	if (0 == strcmp(_pcRemoteFileName, m_tDownLoadInfo.m_cRemoteFilename) && m_iLogonId == _iLogonId)
	{
		blChk = TRUE;
	}
	return blChk;
}

BOOL CLS_DownloadFileMp4::CheckDownLoadInfo(int _iConnectId )
{
	if (-1 == _iConnectId)
	{
		return FALSE;
	}

	BOOL blChk = FALSE;
	if (m_iConnectId == _iConnectId)
	{
		blChk = TRUE;
	}
	return blChk;
}

int CLS_DownloadFileMp4::SetDownLoadSpeed( DOWNLOAD_CONTROL _tDownLoadControl )
{
	if (m_iConnectId < 0 || m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DownloadFileMp4::SetDownLoadSpeed] Illegal LogonId(%d), ConnectId(%d)", m_iLogonId, m_iConnectId);
		return RET_FAILED;
	}
	int iRet = NetClient_NetFileDownload((unsigned int*)&m_iConnectId, m_iLogonId, DOWNLOAD_CMD_CONTROL, &_tDownLoadControl, sizeof(DOWNLOAD_CONTROL));
	
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DownloadFileMp4::SetDownLoadSpeed] Download Control Failed! LogonId(%d), ConnectId(%d)", m_iLogonId, m_iConnectId);
		goto EXIT_FUNC;
	}

	m_iDownLoadStatus = (DOWN_LOAD_SPEED_PAUSE == _tDownLoadControl.m_iSpeed) ? n_DLStatus_Pause : n_DLStatus_Doing;

EXIT_FUNC:
	return iRet;
}

char* CLS_DownloadFileMp4::GetDownLoadProgress(char* _pcProgress, int _iLen)
{
	if (m_iConnectId < 0 || m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DownloadFileMp4::GetDownLoadProgress] Illegal LogonId(%d), ConnectId(%d)", m_iLogonId, m_iConnectId);
		return _pcProgress;
	}

	if (NULL == _pcProgress)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DownloadFileMp4::GetDownLoadProgress] Illegal null == _pcProgress! LogonId(%d), ConnectId(%d)", m_iLogonId, m_iConnectId);
		return _pcProgress;
	}

	if (_iLen <= 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DownloadFileMp4::GetDownLoadProgress] Illegal _iLen <= 0! LogonId(%d), ConnectId(%d)", m_iLogonId, m_iConnectId);
		return _pcProgress;
	}
	int iDownLoadSize = 0;
	int iRet = NetClient_NetFileGetDownloadPos(m_iConnectId, &m_iDownLoadPos, &iDownLoadSize);
	char cProgress[LEN_128] = {0};
	sprintf(cProgress, "%d%/%dMb", m_iDownLoadPos, iDownLoadSize/RATIO_BYTE_CONVERT/RATIO_BYTE_CONVERT);
	int iCpyLen = min((int)strlen(cProgress), min(_iLen, LEN_128));
	memcpy(_pcProgress, cProgress, iCpyLen);
	return _pcProgress;
}

BOOL CLS_DownloadFileMp4::CheckBreakContinue()
{
	return m_blBreakContinue;
}

int CLS_DownloadFileMp4::GetConnectId()
{
	return m_iConnectId;
}

int CLS_DownloadFileMp4::GetLogonId()
{
	return m_iLogonId;
}

int CLS_DownloadFileMp4::StartBreakContineDownLoad()
{
	m_tDownLoadInfo.m_iPosition = m_iDownLoadPos;
	m_tDownLoadInfo.m_iSpeed = DOWN_LOAD_SPEED_START;
	int iRet = NetClient_NetFileDownload((unsigned int*)&m_iConnectId, m_iLogonId, DOWNLOAD_CMD_FILE_CONTINUE, &m_tDownLoadInfo, sizeof(DOWNLOAD_FILE));
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DownloadFileMp4::StartBreakContineDownLoad] Download Failed! LogonId(%d), ConnectId(%d)", m_iLogonId, m_iConnectId);
	}

	return iRet;
}

CString CLS_DownloadFileMp4::GetFileName()
{
	CString cstrLocalFileFullName = m_tDownLoadInfo.m_cLocalFilename;
	return cstrLocalFileFullName;
}

int CLS_DownloadFileMp4::GetDownLoadStatus()
{
	return m_iDownLoadStatus;
}

unsigned int __stdcall CLS_DownloadFileMp4::FileConvertThread( LPVOID _Param )
{
	CLS_DownloadFileMp4* pThis = (CLS_DownloadFileMp4*)_Param;

	int iConvertResult = RET_FAILED;

	if (NULL == pThis)
	{
		return RET_FAILED;
	}
	
	CString cstrSrcSdvFileName = pThis->m_tDownLoadInfo.m_cLocalFilename;
	CString cstrDstMp4FileName = pThis->m_tDownLoadInfo.m_cLocalFilename;
	cstrDstMp4FileName = cstrDstMp4FileName.Left(cstrDstMp4FileName.GetLength() - (int)strlen(TEMP_SRC_FILE_EXTENSION));

	PathRenameExtension(cstrDstMp4FileName.GetBuffer(),  _T(".mp4"));
	cstrDstMp4FileName.ReleaseBuffer();
	BOOL blKeepSdv = pThis->m_blKeepSdvFile;

	if (cstrSrcSdvFileName.IsEmpty() || cstrDstMp4FileName.IsEmpty())
	{
		goto DEAL_CONVERT_RESULT;
	}

	char* pcSdvName = cstrSrcSdvFileName.GetBuffer();
	char* pcMp4Name = cstrDstMp4FileName.GetBuffer();
	
	if (TMP4_ConvertSdvToMp4)
	{
		iConvertResult = TMP4_ConvertSdvToMp4(pcSdvName, pcMp4Name);
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DownloadFileMp4::FileConvertThread] File(%s) convert result(%d)", PathFindFileName(cstrSrcSdvFileName), iConvertResult);
	}

	cstrSrcSdvFileName.ReleaseBuffer();
	cstrDstMp4FileName.ReleaseBuffer();

DEAL_CONVERT_RESULT:
	iConvertResult = (RET_SUCCESS == iConvertResult) ? CONVERT_STATUS_SUCCESS : CONVERT_STATUS_FAILED;

	pThis->m_iDownLoadStatus = (CONVERT_STATUS_SUCCESS == iConvertResult) ? n_DLStatus_Convert_Complete : n_DLStatus_Convert_Fail;
	if (!blKeepSdv && (CONVERT_STATUS_SUCCESS == iConvertResult))
	{
		DeleteFile(cstrSrcSdvFileName);
	}

	if (NULL != pThis->m_hParents)
	{
		::PostMessage(pThis->m_hParents, WM_DOWNLOAD_FINSH_MSG, pThis->m_iConnectId, pThis->m_iDownLoadStatus);
	}

//EXIT_FUNC:
	return iConvertResult;
}

int CLS_DownloadFileMp4::InnerDealConvertResult( int _iConvertSatus, BOOL _blKeepSdvFile )
{
	m_iDownLoadStatus = (CONVERT_STATUS_SUCCESS == _iConvertSatus) ? n_DLStatus_Convert_Complete : n_DLStatus_Convert_Fail;

	if (CONVERT_STATUS_SUCCESS != _iConvertSatus || !_blKeepSdvFile)
	{
		DeleteFile(m_tDownLoadInfo.m_cLocalFilename);
	}

	return RET_SUCCESS;
}
