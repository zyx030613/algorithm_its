// FilePlayReviewPage.cpp : implementation file
//

#include "stdafx.h"
#include "FilePlayReviewPage.h"
#include "mmsystem.h"
#pragma comment(lib, "Winmm.lib")

int g_iTime = 0;

int GetPlayerIdByConnectId(int _iConnectId)
{
	PlayBackInfo tPlayBackInfo = {0};
	tPlayBackInfo.iSize = sizeof(PlayBackInfo);

	int iRet = NetClient_PlayBackControl(_iConnectId, PLAY_CONTROL_GET_PLAYER_INFO, &tPlayBackInfo, tPlayBackInfo.iSize, NULL, 0);

	int iPlayerId = (iRet >= RET_SUCCESS) ? tPlayBackInfo.iPlayerId : RET_FAILED;

	CString cstrLog;
	cstrLog.Format("[GetPlayerId iRet(%d) ConnectId(%d) PlayerId(%d)*******************************\n]", iRet, _iConnectId, tPlayBackInfo.iPlayerId);
	OutputDebugString(cstrLog);

	return iPlayerId;
}

void __stdcall RecvRawFramNotify(unsigned int _ulID, unsigned char* _cData,int _iLen, RAWFRAME_INFO *_pRawFrameInfo, void* _iUser)
{
	RAWFRAME_INFO tRawFrameInfo = {0};
	memcpy(&tRawFrameInfo, _pRawFrameInfo, sizeof(tRawFrameInfo));
	CString cstrLog;
	int iTime = timeGetTime();
	cstrLog.Format("[RecvRawFramNotify PlayerId(%d) FrameType(%d) DataLen(%d) Time(%d) \
				   ,nWidth(%d), nHeight(%d),nStamp(%d) nEnCoder(%d)\
				   nFrameRate(%d) nAbsStamp(%d) ucBitsPerSample(%d)\
				   uiSamplesPerSec(%d)\n]", _ulID, tRawFrameInfo.nType, _iLen, iTime - g_iTime, \
				   tRawFrameInfo.nWidth, tRawFrameInfo.nHeight, tRawFrameInfo.nStamp, tRawFrameInfo.nEnCoder,\
				   tRawFrameInfo.nFrameRate, tRawFrameInfo.nAbsStamp, tRawFrameInfo.ucBitsPerSample, tRawFrameInfo.uiSamplesPerSec);
#ifdef _DEBUG_LOG_
	OutputDebugString(cstrLog);
#endif

	if (0 == tRawFrameInfo.nType || 1 == tRawFrameInfo.nType)
	{	//视频数据
	}
	else if (5 == tRawFrameInfo.nType)
	{
		//音频数据
	}
}

void AbsSecondsToNvsFileTime( NVS_FILE_TIME* _fileTime,long _tTime )
{
	time_t ltime = (time_t)_tTime;
	struct tm pTime = {0};
	gmtime_s(&pTime, &ltime);
	_fileTime->iYear = pTime.tm_year + 1900;
	_fileTime->iMonth = pTime.tm_mon + 1;
	_fileTime->iDay = pTime.tm_mday;
	_fileTime->iHour = pTime.tm_hour;
	_fileTime->iMinute = pTime.tm_min;
	_fileTime->iSecond = pTime.tm_sec;
}

unsigned int NvsFileTimeToAbsSeconds( NVS_FILE_TIME * _pFileTime )
{
	tm tm_Begin = {0};
	tm_Begin.tm_year = _pFileTime->iYear - 1900;
	tm_Begin.tm_mon  = _pFileTime->iMonth - 1;
	tm_Begin.tm_mday = _pFileTime->iDay;
	tm_Begin.tm_hour = _pFileTime->iHour;
	tm_Begin.tm_min  = _pFileTime->iMinute;
	tm_Begin.tm_sec  = _pFileTime->iSecond;

	time_t timenow, timeSpace;
	tm  pTimeg= {0} ;
	time(&timenow);
	gmtime_s(&pTimeg, &timenow);
	timeSpace = timenow - mktime(&pTimeg);
	time_t begin = mktime(&tm_Begin) + timeSpace;
	unsigned int uiSeconds = (unsigned int)begin;
	return uiSeconds;
}

IMPLEMENT_DYNAMIC(CLS_FilePlayReviewPage, CDialog)

CLS_FilePlayReviewPage::CLS_FilePlayReviewPage(CWnd* pParent /*=NULL*/)
	:  CDialog(CLS_FilePlayReviewPage::IDD, pParent)
{
	m_ulConnID = INVALID_ID;
	m_iLogonID = INVALID_ID;
	m_iPlayerID = INVALID_ID;
	m_iVideoHigth = 0;
	m_iVideoWidth = 0;
	m_hWndVideo = NULL;
	m_iDownloadType = DownloadByFile;
	m_iChannelNo = 0;
	m_iDownloadPause = 0;
	m_iDownloadSpeed = 1;
	memset(m_cDataBuffer, 0, sizeof(m_cDataBuffer));
	m_iDataLen = 0;
	LoadPLAYSDK();	
	m_iPlayState = 0;

	m_phParentHwnd = pParent;
}

CLS_FilePlayReviewPage::~CLS_FilePlayReviewPage()
{
}

void CLS_FilePlayReviewPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_DOWNLOAD, m_ProgressDownload);
	DDX_Control(pDX, IDC_PROGRESS_PLAY, m_ProgressPlay);
	DDX_Control(pDX, IDC_DATETIMEPICKER_PBK_LOCATE_TIME, m_DTLocate);
}

BEGIN_MESSAGE_MAP(CLS_FilePlayReviewPage, CDialog)

	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_LOCATE, &CLS_FilePlayReviewPage::OnBnClickedButtonLocate)
	ON_MESSAGE( PLAYSDKMSG, &CLS_FilePlayReviewPage::OnPlaySDKMsg)
	ON_BN_CLICKED(IDC_BUTTON_DECRYPT, &CLS_FilePlayReviewPage::OnBnClickedButtonDecrypt)
	ON_NOTIFY(NM_THEMECHANGED, IDC_DATETIMEPICKER_PBK_LOCATE_TIME, &CLS_FilePlayReviewPage::OnNMThemeChangedDatetimepickerPbkLocateTime)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_PBK_LOCATE_TIME, &CLS_FilePlayReviewPage::OnDtnDatetimechangeDatetimepickerPbkLocateTime)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_SPEED, &CLS_FilePlayReviewPage::OnBnClickedButtonPlaySpeed)
	ON_BN_CLICKED(IDC_BTN_OSD, &CLS_FilePlayReviewPage::OnBnClickedBtnOsd)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CLS_FilePlayReviewPage::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_PLAY, &CLS_FilePlayReviewPage::OnBnClickedBtnPlay)
	ON_BN_CLICKED(IDC_BTN_FAST_FORWARD, &CLS_FilePlayReviewPage::OnBnClickedBtnFastForward)
	ON_BN_CLICKED(IDC_BTN_FAST_BACKWARD, &CLS_FilePlayReviewPage::OnBnClickedBtnFastBackward)
	ON_BN_CLICKED(IDC_BTN_SEEK, &CLS_FilePlayReviewPage::OnBnClickedBtnSeek)
	ON_BN_CLICKED(IDC_BTN_SLOWFORWARD, &CLS_FilePlayReviewPage::OnBnClickedBtnSlowforward)
END_MESSAGE_MAP()


BOOL CLS_FilePlayReviewPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	TC_RegisterEventMsg(m_hWnd, PLAYSDKMSG);

	UI_UpdateText();
	m_ProgressPlay.SetRange(1, 100);
	m_ProgressDownload.SetRange(1, 100);
	m_ProgressDownload.SetPos(0);
	m_ProgressPlay.SetPos(0);
	if (m_iDownloadType == DownloadByFile)
	{
		InitDownloadByFile();
	}
	else if(m_iDownloadType == DownloadByTime)
	{
		InitDownloadByTime();
	}
	SetTimer(TIMER_PLAY_REVIEW_CHECK_PROGRESS, 1000, NULL);
	SetTimer(TIMER_CHEACK_CONTINUE_DOWNLOAD, 100, NULL);
	m_hWndVideo = GetDlgItem(IDC_STATIC_PLAYVIDEO)->m_hWnd;
	//StartDownload();
	StartPlay();

	return TRUE;  
}

void CLS_FilePlayReviewPage::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case TIMER_PLAY_REVIEW_CHECK_PROGRESS:
		return UI_UpdateProgress();
	case TIMER_CHEACK_CONTINUE_DOWNLOAD:
		return ContinueDownload();	
	}
	CDialog::OnTimer(nIDEvent);
}

void CLS_FilePlayReviewPage::UI_UpdateProgress()
{
	if (m_iDownloadType == DownloadByFile)
	{
		UI_UpdateProgressByFile();
	}
	else if (m_iDownloadType == DownloadByTime)
	{
		UI_UpdateProgressByTime();
	}
	else
		return;
}

void CLS_FilePlayReviewPage::SetDownloadParam( int _iLogonID, CString _szRemoteFileName )
{
	m_iLogonID = _iLogonID;
	m_szFileName = _szRemoteFileName;
	m_iDownloadType = DownloadByFile;
}

void CLS_FilePlayReviewPage::SetDownloadParamEx( int _iLogonID, CString _szRemoteFileName )
{
	m_iLogonID = _iLogonID;
	m_szFileName = _szRemoteFileName;
	m_iDownloadType = SuperPlayBackByFile;
}

void CLS_FilePlayReviewPage::SetDownloadParam( int _iLogonID, int _iChannelNo, NVS_FILE_TIME * _BeginTime, NVS_FILE_TIME *_EndTime )
{
	m_iLogonID = _iLogonID;
	memcpy(&m_begintime, _BeginTime, sizeof(NVS_FILE_TIME));
	memcpy(&m_endtime, _EndTime, sizeof(NVS_FILE_TIME));
	m_iChannelNo = _iChannelNo;
	m_iDownloadType = DownloadByTime;
}

void CLS_FilePlayReviewPage::SetDownloadParamEx( int _iLogonID, int _iChannelNo, NVS_FILE_TIME * _BeginTime, NVS_FILE_TIME *_EndTime )
{
	m_iLogonID = _iLogonID;
	memcpy(&m_begintime, _BeginTime, sizeof(NVS_FILE_TIME));
	memcpy(&m_endtime, _EndTime, sizeof(NVS_FILE_TIME));
	m_iChannelNo = _iChannelNo;
	m_iDownloadType = SuperPlayBackByTime;
}

BOOL CLS_FilePlayReviewPage::DestroyWindow()
{
	KillTimer(TIMER_PLAY_REVIEW_CHECK_PROGRESS);
	ResetDownloadPage();
	return CDialog::DestroyWindow();
}

typedef struct 
{
	unsigned short  FrameRate;
	unsigned short  Width;
	unsigned short  Height;
}S_header;
void __stdcall DownloadDateNotify(unsigned long _ulID, unsigned char* _ucData,int _iLen, int _iFlag, void* _lpUserData)
{
	return; //use NetClient_PlayBack
	CLS_FilePlayReviewPage *pThis = (CLS_FilePlayReviewPage *)_lpUserData;
	S_header *sheader = (S_header*)_ucData;
	if (_ulID == pThis->m_ulConnID)
	{
		if (_iFlag == 1)
		{
			if (pThis->m_iPlayerID == INVALID_ID)
			{
				sheader->Height = 2048;
				sheader->Width = 2448;
				pThis->m_iPlayerID = TC_CreatePlayerFromVoD(pThis->m_hWndVideo, _ucData, _iLen);
				if (pThis->m_iPlayerID >= 0)
				{
					TC_Play(pThis->m_iPlayerID);
					TC_PlayAudio(pThis->m_iPlayerID);
				}
			}
			else if (pThis->m_iPlayerID > 0)
			{
				if (pThis->m_iDataLen > 0)
				{
					TC_PutStreamToPlayer(pThis->m_iPlayerID, pThis->m_cDataBuffer, pThis->m_iDataLen);
					pThis->m_iDataLen = 0;
				}
			}
		}
		else
		{
			if (pThis->m_iPlayerID >= 0)
			{
				if(pThis->m_iDownloadPause)
				{
					if (_iLen < (sizeof(pThis->m_cDataBuffer) - pThis->m_iDataLen))
					{
						memcpy(pThis->m_cDataBuffer + pThis->m_iDataLen, _ucData, _iLen);
						pThis->m_iDataLen += _iLen;
					}
					else
					{
						AddLog(LOG_TYPE_FAIL, "", "[CLS_StreamPlayer::ProcessStreamData] Pause lost data len %d, m_iDataLen %d\n", _iLen, pThis->m_iDataLen);
					}
					//pThis->PauseDownload();
				}
				else
				{
					if (pThis->m_iDataLen > 0)
					{
						TC_PutStreamToPlayer(pThis->m_iPlayerID, pThis->m_cDataBuffer, pThis->m_iDataLen);
						pThis->m_iDataLen = 0;
					}
					int iPushStreamStatus = TC_PutStreamToPlayer(pThis->m_iPlayerID, _ucData, _iLen);
					if (iPushStreamStatus == RET_BUFFER_FULL)
					{
						if (_iLen < (sizeof(pThis->m_cDataBuffer) - pThis->m_iDataLen))
						{
							memcpy(pThis->m_cDataBuffer + pThis->m_iDataLen, _ucData, _iLen);
							pThis->m_iDataLen += _iLen;
						}
						else
						{
							AddLog(LOG_TYPE_FAIL, "", "[CLS_StreamPlayer::ProcessStreamData] Pause lost data len %d, m_iDataLen %d\n", _iLen, pThis->m_iDataLen);
						}
						pThis->PauseDownload();
					}
				}
			}
		}
	}
}

void CLS_FilePlayReviewPage::StartDownload()
{
	if (m_iDownloadType == DownloadByFile)
	{
		StartDownloadByFile();
	}
	else if (m_iDownloadType == DownloadByTime)
	{
		StartDownloadByTime();
	}
	else 
		return;
}

void CLS_FilePlayReviewPage::StartPlay()
{
	if (m_iDownloadType == DownloadByFile)
	{
		StartSuperPlayBackByFile();
	}
	else if (m_iDownloadType == DownloadByTime)
	{
		StartSuperPlayBackByTime();
	}
	else
		return;
}

void CLS_FilePlayReviewPage::StopPlay()
{
	if (INVALID_ID == m_ulConnID)
	{
		return;
	}

	int iRet = NetClient_StopPlayBack(m_ulConnID);
	if(0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_FilePlayReviewPage::StopPlay]");
	}
	m_ulConnID = INVALID_ID;
	return;
}

void CLS_FilePlayReviewPage::OnBnClickedButtonLocate()
{
	if (m_iLogonID == INVALID_ID || m_ulConnID == INVALID_ID)
	{
		return;
	}

	BOOL bPos = FALSE;
	int iPos = GetDlgItemInt(IDC_EDIT_PLAYBACK_LOCATE, &bPos);

	if (iPos >=0 && iPos < 100)
	{
		//NetClient_NetFileDownloadFile(&m_ulConnID, m_iLogonID, "", "", 1, iPos, -1);

		int iRet = -1;
		int iOutLen = 0;
		int iControlCode = PLAY_CONTROL_PLAY;
		if (m_iPlayState == PLAY_CONTROL_PAUSE)
		{
			iRet = NetClient_PlayBackControl(m_ulConnID, iControlCode, NULL, 0, NULL, &iOutLen);
			Sleep(100);
}

		iControlCode = PLAY_CONTROL_SEEK;
		iRet = NetClient_PlayBackControl(m_ulConnID, iControlCode, &iPos, 0, NULL, &iOutLen);
		if (iRet < 0)
	{
			AddLog(LOG_TYPE_FAIL, "", "[CLS_FilePlayReviewPage::OnBnClickedButtonLocate] iPos %d, iRet %d\n", iPos, iRet);
	}
	}
}

void CLS_FilePlayReviewPage::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser )
{
	if (m_iLogonID < 0)
	{
		return;
	}

	int iMsgType = LOWORD(_iWparam);
	switch(iMsgType)
	{
 
 	case WCM_DWONLOAD_FINISHED:
 		if (m_ulConnID == (unsigned long)_iLParam)
 		{
			ProccessDownloadMsg(IDS_PLAYBACK_DOWNLOAD_FINISH);
			m_ProgressDownload.SetPos(100);
 		}
 		break;
	case WCM_DWONLOAD_FAULT:
		if (m_ulConnID == (unsigned long)_iLParam)
		{
			ProccessDownloadMsg(IDS_PLAYBACK_DOWNLOAD_FAULT);
			//m_ProgressDownload.SetPos(100);
		}
		break;
	case WCM_ERR_ORDER: 
		{
			if (m_iLogonID == _ulLogonID)
			{
				ProccessDownloadMsg(IDS_PLAYBACK_BREAK_OFF);
			}
		}
		break;
	case WCM_DOWNLOAD_INTERRUPT:
		if (m_ulConnID == (unsigned long)_iLParam)
		{
			ProccessDownloadMsg(IDS_PLAYBACK_DOWNLOAD_INTERRUPT);
		}
		break;
	case WCM_VOD_STREAM_END:
		if (m_ulConnID == (unsigned long)_iLParam)
		{
			StopPlay();
			TC_SetVoDPlayerOver(m_iPlayerID);
		}
		break;
	case WCM_LOGON_NOTIFY:
		{
			if (m_iLogonID == _ulLogonID && LOGON_SUCCESS == (int)_iLParam)
			{
				ProccessDownloadMsg(IDS_PLAYBACK_DOWNLOAD_STATUS);
			}
		}
		break;
	default:
		return;
	}
}

void CLS_FilePlayReviewPage::ResetDownloadPage()
{
	if (m_ulConnID != INVALID_ID)
	{
		StopPlay();
	}

	m_iLogonID = INVALID_ID;
	m_szFileName = "";
	m_iVideoHigth = 0;
	m_iVideoWidth = 0;
	m_ProgressDownload.SetPos(0);
	m_ProgressPlay.SetPos(0);
}

LRESULT CLS_FilePlayReviewPage::OnPlaySDKMsg( WPARAM _wParam, LPARAM _lParam )
{
	if (_wParam != m_iPlayerID)
	{
		return 0;
	}
	switch(_lParam)
	{
	case LPARAM_STREAM_SEARCH_END:
		ProcessStreamSearchEnd();
		break;
	case LPARAM_VOD_STREAM_END:
		ProcessVodEnd();
		break;
	case LPARAM_NEED_DECRYPT_KEY:
	case LPARAM_DECRYPT_KEY_FAILED:
	case LPARAM_DECRYPT_SUCCESS:
		ProcessPlayDecrypt((int)_lParam);
		break;
	}
	return 0;
}

void CLS_FilePlayReviewPage::ProcessStreamSearchEnd()
{
	ContinueDownload();
}

void CLS_FilePlayReviewPage::ProccessDownloadMsg( int _iResourceID )
{
	SetDlgItemTextEx(IDC_STATIC_REVIEW_DOWNLOAD, _iResourceID);
	SetDlgItemTextEx(IDC_STC_STATUS_LOG, _iResourceID);
}

void CLS_FilePlayReviewPage::ProcessPlayDecrypt(int _iDecryptCode)
{
	
}

void CLS_FilePlayReviewPage::StartDownloadByFile()
{
	int iRet = NetClient_NetFileDownloadFile(&m_ulConnID, m_iLogonID, (char*)(LPCSTR)m_szFileName, "", 0, -1, 2 );
	//sdk
	if (iRet >= 0)
	{
		NetClient_SetNetFileDownloadFileCallBack(m_ulConnID, (RECVDATA_NOTIFY_EX)DownloadDateNotify, this);
	}
	else
	{
		if (m_ulConnID != INVALID_ID)
		{
			StopPlay();
		}	
	}
}

void CLS_FilePlayReviewPage::StartDownloadByTime()
{
	int iRet = NetClient_NetFileDownloadByTimeSpanEx((unsigned int*)&m_ulConnID, 
		m_iLogonID,
		NULL,
		m_iChannelNo,
		&m_begintime,
		&m_endtime , 0, -1, 2);
	if (iRet < 0)
	{
		if (m_ulConnID != INVALID_ID)
		{
			StopPlay();
		}
		return;
	}
	else
	{
		NetClient_SetNetFileDownloadFileCallBack(m_ulConnID, (RECVDATA_NOTIFY_EX)DownloadDateNotify, this);
	}
}

void CLS_FilePlayReviewPage::UI_UpdateProgressByFile()
{
	if (m_ulConnID != INVALID_ID)
	{
		int iProgress = 0, iSize = 0;
		int iRet = NetClient_NetFileGetDownloadPos(m_ulConnID, &iProgress, &iSize);
		if (iRet >= 0)
		{
			CString szDownloadPorgress, szDownloadSize;
			szDownloadPorgress.Format("***%d", iProgress);
			szDownloadSize.Format("%dB", iSize);
			szDownloadPorgress += "%/" + szDownloadSize + "***";
			SetDlgItemText(IDC_STATIC_REVIEW_DOWNLOAD, szDownloadPorgress);
			m_ProgressDownload.SetPos(iProgress);
		}
	}

	int iCmd = PLAY_CONTROL_GET_PROCESS;
	tPlaybackProcess tTmpProcess = {0};
	int iSize = sizeof(tPlaybackProcess);
	tTmpProcess.iSize = iSize;
	tTmpProcess.iPlayByFileOrTime = PLAYBACK_TYPE_FILE;
	NetClient_PlayBackControl(m_ulConnID, iCmd, &tTmpProcess, iSize, NULL, NULL);
		CString szPlayProgress;
	szPlayProgress.Format("***%d", tTmpProcess.iProcess);
		szPlayProgress += "%***";
	m_ProgressPlay.SetPos(tTmpProcess.iProcess);
		SetDlgItemText(IDC_STATIC_REVIEW_PLAY, szPlayProgress);
}

void CLS_FilePlayReviewPage::UI_UpdateProgressByTime()
{
	if (m_ulConnID != INVALID_ID)
	{
		int iCurrentDonwnTime = 0, iSize = 0;
		int iRet = NetClient_NetFileGetDownloadPos(m_ulConnID, &iCurrentDonwnTime, &iSize);
		if (iRet >= 0)
		{
			CString szDownloadPorgress, szDownloadSize;
			NVS_FILE_TIME CurrentTime = {0};
			AbsSecondsToNvsFileTime(&CurrentTime, (long)iCurrentDonwnTime);
			szDownloadPorgress.Format(GetTextEx(IDS_PLAYBACK_DOWNLOADING)+"***%d-%d-%d|%d:%d:%d", CurrentTime.iYear, 
				CurrentTime.iMonth, CurrentTime.iDay, CurrentTime.iHour
				, CurrentTime.iMinute, CurrentTime.iSecond);
			szDownloadSize.Format("%dB", iSize);
			szDownloadPorgress += "/" + szDownloadSize + "***";
			SetDlgItemText(IDC_STATIC_REVIEW_DOWNLOAD, szDownloadPorgress);
			unsigned int uiFrom = NvsFileTimeToAbsSeconds(&m_begintime);
			unsigned int uiTo = NvsFileTimeToAbsSeconds(&m_endtime);
			if((unsigned int)iCurrentDonwnTime >= uiFrom && (unsigned int)iCurrentDonwnTime <= uiTo)
			{
				int iCurDownlodPos = (int)(iCurrentDonwnTime-uiFrom)*100/(int)(uiTo-uiFrom);
				m_ProgressDownload.SetPos(iCurDownlodPos);
			}
		}
	}
	//if (m_iPlayerID != INVALID_ID)
	//{
		int iCmd = PLAY_CONTROL_GETUSERINFO;
		int iFlag = GET_USERDATA_INFO_TIME;
		int iAbsoluteFrameTime = 0;
		int iSize = sizeof(int);
		NetClient_PlayBackControl(m_ulConnID, iCmd, &iFlag, iSize, &iAbsoluteFrameTime, &iSize);
		if(iAbsoluteFrameTime > 0)
		{
			NVS_FILE_TIME CurrentTime = {0};
			AbsSecondsToNvsFileTime(&CurrentTime, iAbsoluteFrameTime);
			unsigned int uiFrom = NvsFileTimeToAbsSeconds(&m_begintime);
			unsigned int uiTo = NvsFileTimeToAbsSeconds(&m_endtime);
			if(iAbsoluteFrameTime >= uiFrom && iAbsoluteFrameTime <= uiTo)
			{
				int iCurPlayPos = (int)(iAbsoluteFrameTime-uiFrom)*100/(int)(uiTo-uiFrom);
				m_ProgressPlay.SetPos(iCurPlayPos);
			}
			CString szPlayProgress = GetTextEx(IDS_PLAYBACK_PLAYING);
			szPlayProgress.Format(GetTextEx(IDS_PLAYBACK_PLAYING) + "***%d-%d-%d|%d:%d:%d", CurrentTime.iYear, 
				CurrentTime.iMonth, CurrentTime.iDay, CurrentTime.iHour
				, CurrentTime.iMinute, CurrentTime.iSecond);
			szPlayProgress += "***";
			SetDlgItemText(IDC_STATIC_REVIEW_PLAY, szPlayProgress);
		}
	//}
}

void CLS_FilePlayReviewPage::InitDownloadByFile()
{
	SetDlgItemText(IDC_STATIC_PBK_DOWNLOAD_LOCATE, GetTextEx(IDS_PLAYBACK_DOWNLOAD_LOCATE));
	GetDlgItem(IDC_EDIT_PLAYBACK_LOCATE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_LOCATE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DATETIMEPICKER_PBK_LOCATE_TIME)->ShowWindow(SW_HIDE);
	SetDlgItemText(IDC_STATIC_PBK_REVIEW_BEGINTIME, m_szFileName);
	GetDlgItem(IDC_STATIC_PBK_REVIEW_BEGINTIME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_PBK_REVIEW_ENDTIME)->ShowWindow(SW_HIDE);
}

void CLS_FilePlayReviewPage::InitDownloadByTime()
{
	SetDlgItemTextEx(IDC_STATIC_PBK_DOWNLOAD_LOCATE, IDS_PLAYBACK_DOWNLOAD_LOCATE);	
	RECT Rect = {0};
	GetDlgItem(IDC_STATIC_PBK_DOWNLOAD_LOCATE)->GetWindowRect(&Rect);
	RECT RectParent = {0};
	GetWindowRect(&RectParent);
	RECT DstRect = {0};
	GetDlgItem(IDC_STATIC_PBK_VIDEO_DECRYPT)->GetWindowRect(&DstRect);
	int iDstTop = Rect.top - RectParent.top - 20;
	int iDstleft = DstRect.left - RectParent.left - 5;
	GetDlgItem(IDC_STATIC_PBK_DOWNLOAD_LOCATE)->MoveWindow(iDstleft, iDstTop, Rect.right - Rect.left, Rect.bottom - Rect.top);

	iDstTop -= 5;
	GetDlgItem(IDC_DATETIMEPICKER_PBK_LOCATE_TIME)->GetWindowRect(&Rect);
	GetWindowRect(&RectParent);
	GetDlgItem(IDC_EDIT_PLAYBACK_DECRYPT)->GetWindowRect(&DstRect);
	iDstleft = DstRect.left - RectParent.left - 5;
	GetDlgItem(IDC_DATETIMEPICKER_PBK_LOCATE_TIME)->MoveWindow(iDstleft, iDstTop, Rect.right - Rect.left, Rect.bottom - Rect.top);

	GetDlgItem(IDC_EDIT_PLAYBACK_LOCATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_LOCATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATETIMEPICKER_PBK_LOCATE_TIME)->ShowWindow(SW_SHOW);

	CString szBeginTime;
	szBeginTime.Format("%d-%d-%d|%d:%d:%d", m_begintime.iYear, 
		m_begintime.iMonth, m_begintime.iDay, m_begintime.iHour
		, m_begintime.iMinute, m_begintime.iSecond);
	CString szEndTime;
	szEndTime.Format("%d-%d-%d|%d:%d:%d", m_endtime.iYear, 
		m_endtime.iMonth, m_endtime.iDay, m_endtime.iHour
		, m_endtime.iMinute, m_endtime.iSecond);
	SetDlgItemText(IDC_STATIC_PBK_REVIEW_BEGINTIME, szBeginTime);
	SetDlgItemText(IDC_STATIC_PBK_REVIEW_ENDTIME, szEndTime);
	GetDlgItem(IDC_STATIC_PBK_REVIEW_BEGINTIME)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_PBK_REVIEW_ENDTIME)->ShowWindow(SW_SHOW);
	m_DTLocate.SetFormat("yyyy-MM-dd HH:mm:ss");
}

void CLS_FilePlayReviewPage::OnBnClickedButtonDecrypt()
{
	if (m_iPlayerID >= 0)
	{
		CString szDecryptKey;
		GetDlgItemText(IDC_EDIT_PLAYBACK_DECRYPT, szDecryptKey);
		TC_SetVideoDecryptKey(m_iPlayerID, szDecryptKey.GetBuffer(), szDecryptKey.GetLength());
	}
}

void CLS_FilePlayReviewPage::PauseDownload()
{
	if (m_iLogonID ==  INVALID_ID || m_ulConnID == INVALID_ID)
	{
		return;
	}
	int iRet = NetClient_NetFileDownloadFile(&m_ulConnID, m_iLogonID, "", "", 1, -1, 0);
	if (iRet >= 0)
	{
		m_iDownloadPause = 1;
	}
}

void CLS_FilePlayReviewPage::ContinueDownload()
{
	if (m_iLogonID ==  INVALID_ID || m_ulConnID == INVALID_ID)
	{
		return;
	}
	
	if (m_iDownloadPause == 1)
	{
		int iState = 0;
		int iRet = TC_GetStreamPlayBufferState(m_iPlayerID, &iState);
		if(iRet == 0)
		{
			if (iState == RET_BUFFER_WILL_BE_EMPTY )
			{
				int iRet = NetClient_NetFileDownloadFile(&m_ulConnID, m_iLogonID, "", "",1 , -1, m_iDownloadSpeed);
				m_iDownloadPause = 0;
			}
		}
	}
}

void CLS_FilePlayReviewPage::UI_UpdateText()
{
	SetWindowTextEx(IDS_PLAYBACK_PREVIEW);
	SetDlgItemTextEx(IDC_STATIC_PBK_OPTION, IDS_PLAYBACK_OPTION);
	SetDlgItemTextEx(IDC_BUTTON_LOCATE, IDS_PLAYBACK_LOCATE);
	SetDlgItemTextEx(IDC_STATIC_PBK_DOWNLOAD_SPEED, IDS_PLAYBACK_DOWNLOAD_SPEED);
	SetDlgItemTextEx(IDC_BUTTON_DOWNLOAD_SPEED, IDS_PLAYBACK_CHANGE_SPEED);
	SetDlgItemTextEx(IDC_STATIC_PBK_VIDEO_DECRYPT, IDS_PLAYBACK_VIDEO_DECRYPT);
	SetDlgItemTextEx(IDC_BUTTON_DECRYPT, IDS_PLAYBACK_DECRYPT);
	SetDlgItemTextEx(IDC_STATIC_PBK_PLAY_SPEED, IDS_PLAYBACK_PLAY_SPEED);
	SetDlgItemTextEx(IDC_BUTTON_PLAY_SPEED, IDS_PLAYBACK_CHANGE_SPEED);
	SetDlgItemTextEx(IDC_BTN_OSD, IDS_CONFIG_OSD);
	SetDlgItemTextEx(IDC_BTN_PLAY, IDS_START_PLAY);
	SetDlgItemTextEx(IDC_BTN_PAUSE, IDS_PLAY_PAUSE);
	SetDlgItemTextEx(IDC_BTN_FAST_FORWARD, IDS_PLAY_FAST);
	SetDlgItemTextEx(IDC_BTN_SLOWFORWARD, IDS_PLAY_SLOW);
	SetDlgItemTextEx(IDC_STC_DOWNLOAD_FILETYPE, IDS_CONFIG_FTP_FILETYPE);

	SetDlgItemText(IDC_STATIC_REVIEW_DOWNLOAD, "***" + GetTextEx(IDS_PLAYBACK_DOWNLOADING) + "***");
	SetDlgItemText(IDC_STATIC_REVIEW_PLAY, "***" + GetTextEx(IDS_PLAYBACK_PLAYING) + "***");
}
void CLS_FilePlayReviewPage::OnNMThemeChangedDatetimepickerPbkLocateTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	// This feature requires Windows XP or greater.
	// The symbol _WIN32_WINNT must be >= 0x0501.
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CLS_FilePlayReviewPage::OnDtnDatetimechangeDatetimepickerPbkLocateTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	*pResult = 0;
// 	if (m_ulConnID == INVALID_ID || m_iLogonID == INVALID_ID || m_iPlayerID == INVALID_ID)
// 	{
// 		return;
// 	}
	
	CTime tempTime;
	NVS_FILE_TIME time = {0};
	m_DTLocate.GetTime(tempTime);
	time.iYear = tempTime.GetYear();
	time.iMonth = tempTime.GetMonth();
	time.iDay = tempTime.GetDay();
	time.iHour = tempTime.GetHour();
	time.iMinute = tempTime.GetMinute();
	time.iSecond = tempTime.GetSecond();
	int iJumpTime = NvsFileTimeToAbsSeconds(&time);
	int iBeginTime = NvsFileTimeToAbsSeconds(&m_begintime);
	int iEndTime = NvsFileTimeToAbsSeconds(&m_endtime);
	if(iJumpTime > iBeginTime && iJumpTime < iEndTime)
	{
		int iRet = -1;
		int iOutLen = 0;
		int iControlCode = PLAY_CONTROL_PLAY;
		if (m_iPlayState == PLAY_CONTROL_PAUSE)
		{
			iRet = NetClient_PlayBackControl(m_ulConnID, iControlCode, NULL, 0, NULL, &iOutLen);
			Sleep(100);
		}

		iControlCode = PLAY_CONTROL_SEEK;
		iRet = NetClient_PlayBackControl(m_ulConnID, iControlCode, &iJumpTime, 0, NULL, &iOutLen);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "", "[CLS_FilePlayReviewPage::OnBnClickedButtonLocate] iJumpTime %d, iRet %d\n", iJumpTime, iRet);
		}
	}
}

void CLS_FilePlayReviewPage::OnBnClickedButtonPlaySpeed()
{
	if (m_iLogonID ==  INVALID_ID || m_ulConnID == INVALID_ID)
	{
		return;
	}
	int iPlaySpeed = GetDlgItemInt(IDC_EDIT_PLAY_SPEED);
	int iOutLen = 0;
	if (m_iPlayerID != INVALID_ID)
	{
		if(iPlaySpeed != 0)
		{
			//TC_FastForward(m_iPlayerID, iPlaySpeed);
			int iControlCode = PLAY_CONTROL_FAST_FORWARD;
			int iRet = NetClient_PlayBackControl(m_ulConnID, iControlCode, &iPlaySpeed, 0, NULL, &iOutLen);
			if (iRet < 0)
			{
				AddLog(LOG_TYPE_FAIL, "", "[CLS_FilePlayReviewPage::OnBnClickedButtonPlaySpeed] iPlaySpeed %d, iRet %d\n", iPlaySpeed, iRet);
			}
		}
		else
		{
			//TC_Play(m_iPlayerID);
			int iControlCode = PLAY_CONTROL_PLAY;
			int iRet = NetClient_PlayBackControl(m_ulConnID, iControlCode, NULL, 0, NULL, &iOutLen);
			if (iRet < 0)
			{
				AddLog(LOG_TYPE_FAIL, "", "[CLS_FilePlayReviewPage::OnBnClickedButtonPlaySpeed] iPlaySpeed %d, iRet %d\n", iPlaySpeed, iRet);
			}
		}
	}
}

void CLS_FilePlayReviewPage::ProcessVodEnd()
{
	ResetDownloadPage();
	SetDlgItemTextEx(IDC_STATIC_REVIEW_PLAY, IDS_PLAYBACK_PLAY_OVER);
}

void CLS_FilePlayReviewPage::OnBnClickedBtnOsd()
{
	int iRet = -1;

	int iControlCode = PLAY_CONTROL_OSD;
	int iOutLen = 0;

	tPlayBackOsd tTmpPlayBackOsg = {0};
	tTmpPlayBackOsg.iSize = sizeof(tPlayBackOsd);
	tTmpPlayBackOsg.iX = -1;
	tTmpPlayBackOsg.iY = -1;
	tTmpPlayBackOsg.iColor = -1;
	memcpy(tTmpPlayBackOsg.cOsdText, "非宁静无以致远", sizeof("非宁静无以致远")); 
	iRet = NetClient_PlayBackControl(m_ulConnID, iControlCode, &tTmpPlayBackOsg, 0, NULL, &iOutLen);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_FilePlayReviewPage::OnBnClickedBtnOsd] iRet %d\n", iRet);
	}
}

//void CLS_FilePlayReviewPage::OnBnClickedBtnStart()
//{
//	// TODO: Add your control notification handler code here
//	// TODO: Add your control notification handler code here
//
//	unsigned int uiConId = 0; 
//	int iRet = -1;
//
//	//按文件播放
//	//PlayerParam tTmpPlayerParam = {0};
//
//	//tTmpPlayerParam.iChannNo = 0;
//	//tTmpPlayerParam.iLogonID = m_iLogonID;
//	//memcpy(tTmpPlayerParam.strFileName, "H20000000041E70F0000C00.sdv", sizeof("H20000000041E70F0000C00.sdv"));
//
//	//iRet =  NetClient_PlayBackByFlag(&uiConId, PLAYER_TYPE_FILE_STREAM, &tTmpPlayerParam, (void*)m_hWndVideo);
//	/*m_ulConnID = uiConId;*/
//	//按时间段播放
//	PlayerParam tmpPlayerParam = {0};
//	tmpPlayerParam.iSize = sizeof(PlayerParam);
//	tmpPlayerParam.iLogonID = m_iLogonID;
//	tmpPlayerParam.iChannNo = 0;
//	tmpPlayerParam.tBeginTime.iYear = 2015;
//	tmpPlayerParam.tBeginTime.iMonth = 9;
//	tmpPlayerParam.tBeginTime.iDay = 17;
//	tmpPlayerParam.tBeginTime.iHour = 12;
//	tmpPlayerParam.tBeginTime.iMinute = 10;
//	tmpPlayerParam.tBeginTime.iSecond = 10;
//
//	tmpPlayerParam.tEndTime.iYear = 2015;
//	tmpPlayerParam.tEndTime.iMonth = 9;
//	tmpPlayerParam.tEndTime.iDay = 17;
//	tmpPlayerParam.tEndTime.iHour = 12;
//	tmpPlayerParam.tEndTime.iMinute = 20;
//	tmpPlayerParam.tEndTime.iSecond = 20;
//	iRet =  NetClient_PlayBackByFlag(&uiConId, PLAYER_TYPE_TIME_STREAM, &tmpPlayerParam, (void*)m_hWndVideo);
//	m_ulConnID = uiConId;
//}

void CLS_FilePlayReviewPage::OnBnClickedBtnPause()
{
	int iRet = -1;

	int iControlCode = PLAY_CONTROL_PAUSE;
	int iOutLen = 0;
	iRet = NetClient_PlayBackControl(m_ulConnID, iControlCode, NULL, 0, NULL, &iOutLen);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_FilePlayReviewPage::OnBnClickedBtnPause] iRet %d\n", iRet);
	}
}

void CLS_FilePlayReviewPage::OnBnClickedBtnPlay()
{
	int iRet = -1;

	int iControlCode = PLAY_CONTROL_PLAY;
	int iOutLen = 0;
	iRet = NetClient_PlayBackControl(m_ulConnID, iControlCode, NULL, 0, NULL, &iOutLen);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_FilePlayReviewPage::OnBnClickedBtnPlay] iRet %d\n", iRet);
	}
}

void CLS_FilePlayReviewPage::OnBnClickedBtnFastForward()
{
	int iRet = -1;
	if (m_iPlayState == PLAY_CONTROL_PAUSE)
	{
		//return;
	}
	
	int iControlCode = PLAY_CONTROL_PLAY;
	if (m_iPlayState == PLAY_CONTROL_SLOW_FORWARD)
	{
		iRet = NetClient_PlayBackControl(m_ulConnID, iControlCode, NULL, 0, NULL, 0);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "", "[CLS_FilePlayReviewPage::OnBnClickedBtnFastForward-Play]iRet %d\n",iRet);
		}
		Sleep(500);
	}

	iControlCode = PLAY_CONTROL_FAST_FORWARD;
	m_iPlayState = PLAY_CONTROL_FAST_FORWARD;
	int iOutLen = 0;
	int iSpeed = 4;
	iRet = NetClient_PlayBackControl(m_ulConnID, iControlCode, &iSpeed, 0, NULL, &iOutLen);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_FilePlayReviewPage::OnBnClickedBtnFastForward-Forward] iSpeed %d, iRet %d\n", iSpeed, iRet);
	}
}

void CLS_FilePlayReviewPage::OnBnClickedBtnFastBackward()
{
	int iRet = -1;
	if (m_iPlayState == PLAY_CONTROL_PAUSE)
	{
		//return;
	}

	int iControlCode = PLAY_CONTROL_PLAY;
	int iOutLen = 0;
	int iSpeed = 2;

	if (m_iPlayState == PLAY_CONTROL_SLOW_FORWARD)
	{
		iRet = NetClient_PlayBackControl(m_ulConnID, iControlCode, NULL, 0, NULL, &iOutLen);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "", "[CLS_FilePlayReviewPage::OnBnClickedBtnFastBackward-Play] iSpeed %d, iRet %d\n", iSpeed, iRet);
		}
		Sleep(500);
	}

	iControlCode = PLAY_CONTROL_FAST_FORWARD;
	iRet = NetClient_PlayBackControl(m_ulConnID, iControlCode, &iSpeed, 0, NULL, &iOutLen);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_FilePlayReviewPage::OnBnClickedBtnFastBackward-BackWard] iSpeed %d, iRet %d\n", iSpeed, iRet);
	}
}

void CLS_FilePlayReviewPage::OnBnClickedBtnSeek()
{
	int iRet = -1;
	if (m_iPlayState == PLAY_CONTROL_PAUSE)
	{
		return;
	}

	int iOutLen = 0;
	int iControlCode = PLAY_CONTROL_PLAY;
	if (m_iPlayState == PLAY_CONTROL_FAST_FORWARD)
	{
		iRet = NetClient_PlayBackControl(m_ulConnID, iControlCode, NULL, 0, NULL, &iOutLen);
		Sleep(500);
	}

	iControlCode = PLAY_CONTROL_SEEK;
	int iFrameNo = 400;
	iRet = NetClient_PlayBackControl(m_ulConnID, iControlCode, &iFrameNo, 0, NULL, &iOutLen);
	if (iRet < 0)
	{

	}
}

void CLS_FilePlayReviewPage::OnBnClickedBtnSlowforward()
{
	int iRet = -1;
	if (m_iPlayState == PLAY_CONTROL_PAUSE)
	{
		//return;
	}

	int iControlCode = PLAY_CONTROL_PLAY;
	int iOutLen = 0;

	if (m_iPlayState == PLAY_CONTROL_FAST_FORWARD)
	{
		iRet = NetClient_PlayBackControl(m_ulConnID, iControlCode, NULL, 0, NULL, &iOutLen);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "", "[CLS_FilePlayReviewPage::OnBnClickedBtnSlowforward-Play]iRet %d\n", iRet);
		}
		Sleep(500);
	}

	int iSpeed = 2;
	iControlCode = PLAY_CONTROL_SLOW_FORWARD;
	iRet = NetClient_PlayBackControl(m_ulConnID, iControlCode, &iSpeed, 0, NULL, &iOutLen);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_FilePlayReviewPage::OnBnClickedBtnSlowforward-Slowforward] iSpeed %d, iRet %d\n", iSpeed, iRet);
	}
}

void CLS_FilePlayReviewPage::StartSuperPlayBackByFile()
{
	PlayerParam stParam = {0};
	stParam.iSize = sizeof(PlayerParam);
	stParam.iLogonID = m_iLogonID;
	stParam.tRawNotifyInfo.pcbkRawFrameNotify = &RecvRawFramNotify;
	stParam.tRawNotifyInfo.pUserData = this;
	stParam.tRawNotifyInfo.iForbidDecodeEnable = /*RAW_NOTIFY_FORBID_DECODE*/RAW_NOTIFY_ALLOW_DECODE;

	strcpy_s(stParam.strFileName, LEN_128, m_szFileName);

	unsigned int uiConId = -1;
	int iRet =  NetClient_PlayBack(&uiConId, PLAYBACK_TYPE_FILE, &stParam, /*NULL*/(void*)m_hWndVideo);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_FilePlayReviewPage::StartSuperPlayBackByTime] logonId=%d, conId=%d, file=%s\n", m_iLogonID, uiConId, m_szFileName);
		return;
	}
	m_ulConnID = uiConId;
}

void CLS_FilePlayReviewPage::StartSuperPlayBackByTime()
{
	PlayerParam stParam = {0};
	stParam.iSize = sizeof(PlayerParam);
	stParam.iLogonID = m_iLogonID;
	stParam.iChannNo = m_iChannelNo;
	stParam.tBeginTime = m_begintime;
	stParam.tEndTime = m_endtime;
	stParam.tRawNotifyInfo.pcbkRawFrameNotify = &RecvRawFramNotify;
	stParam.tRawNotifyInfo.pUserData = this;
	stParam.tRawNotifyInfo.iForbidDecodeEnable = /*RAW_NOTIFY_FORBID_DECODE*/RAW_NOTIFY_ALLOW_DECODE;

	unsigned int uiConId = -1;
	int iRet =  NetClient_PlayBack(&uiConId, PLAYBACK_TYPE_TIME, &stParam, /*NULL*/(void*)m_hWndVideo);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_FilePlayReviewPage::StartSuperPlayBackByTime] logonId=%d, chanNo=%d, conId=%d\n", m_iLogonID, m_iChannelNo, uiConId);
		return;
	}
	m_ulConnID = uiConId;
}

void CLS_FilePlayReviewPage::OnCancel()
{
	StopPlay();
	DestroyWindow();

	if (NULL != m_phParentHwnd)
	{
		::PostMessage(m_phParentHwnd->GetSafeHwnd(), WM_PLAY_PAGE_DESTORY, NULL, NULL);
	}
}

CString CLS_FilePlayReviewPage::GetFilename()
{
	CString cstrCurFile;
	if (DownloadByFile != m_iDownloadType && SuperPlayBackByFile != m_iDownloadType)
	{
		goto EXIT_FUNC;
	}

	cstrCurFile = m_szFileName;

EXIT_FUNC:
	return cstrCurFile;
}

int CLS_FilePlayReviewPage::GetLogonID()
{
	return m_iLogonID;
}


