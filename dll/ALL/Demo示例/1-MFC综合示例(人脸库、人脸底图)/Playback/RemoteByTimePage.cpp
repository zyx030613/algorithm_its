// RemoteByTimePage.cpp : implementation file
//

#include "stdafx.h"
#include <shlwapi.h>
#include "RemoteByTimePage.h"
#include "mmsystem.h"
#pragma comment(lib, "Winmm.lib")

CString g_Path = "C:\\netclientdemo_download\\";
// CLS_RemoteByTimePage dialog

int g_iTimeInterval = 0;

void PsDataCallBackFunction(unsigned int _ulID, unsigned char* _cData, int _iLen, int _iType, void* _pvUserData)
{
	if (NULL == _cData)
	{
		return;
	}

#ifdef _DEBUG
	CString cstrLog;
	int iTime = timeGetTime();
	cstrLog.Format("[RecvPsDataNotify ConnectId(%d) Time(%d) DataLen(%d)]\n", _ulID, iTime - g_iTimeInterval, _iLen);
	g_iTimeInterval = iTime;
	OutputDebugString(cstrLog);
#endif
}

IMPLEMENT_DYNAMIC(CLS_RemoteByTimePage, CDialog)

CLS_RemoteByTimePage::CLS_RemoteByTimePage(CWnd* pParent /*=NULL*/)
	:  CLS_BasePage(CLS_RemoteByTimePage::IDD, pParent)
{
	m_ulConnID = INVALID_ID;
	m_iLogonID = INVALID_ID;
}

CLS_RemoteByTimePage::~CLS_RemoteByTimePage()
{
}

void CLS_RemoteByTimePage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DTDownloadBeginTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_DTDownloadEndTime);
	DDX_Control(pDX, IDC_COMBO1, m_ComboChannelNo);
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressDownload);
	DDX_Control(pDX, IDC_COMBO_STREAMNO, m_cboStreamNo);
	DDX_Control(pDX, IDC_CBO_DOWNLOADTYPE, m_cboDownloadFileType);
	DDX_Control(pDX, IDC_CBO_DOWNLOAD_FILE_FLAG, m_cboDownloadFileFlag);
}


BEGIN_MESSAGE_MAP(CLS_RemoteByTimePage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_BY_TIME_DOWNLOAD, &CLS_RemoteByTimePage::OnBnClickedButtonPlayByTimeDownload)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PLAYBACK_BY_TIME_PLAY, &CLS_RemoteByTimePage::OnBnClickedButtonPlaybackByTimePlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CLS_RemoteByTimePage::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BTN_SUPER_VOD_BY_TIME, &CLS_RemoteByTimePage::OnBnClickedBtnSuperVodByTime)
	ON_MESSAGE(WM_PLAY_PAGE_DESTORY, &CLS_RemoteByTimePage::OnPlayPageDestory)
END_MESSAGE_MAP()

void __stdcall testRAWFRAME_NOTIFY(unsigned int _ulID,unsigned char* _cData,int _iLen, RAWFRAME_INFO *_pRawFrameInfo, void* _iUser)
{
	//
}
// CLS_RemoteByTimePage message handlers

void CLS_RemoteByTimePage::OnBnClickedButtonPlayByTimeDownload()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID == INVALID_ID || m_ulConnID != INVALID_ID)
	{
		return;
	}
	CTime BeginTime;
	CTime EndTime;
	CTime tempTime;
	m_DTDownloadBeginTime.GetTime(tempTime);
	m_timeBegin.iYear = tempTime.GetYear();
	m_timeBegin.iMonth = tempTime.GetMonth();
	m_timeBegin.iDay = tempTime.GetDay();
	m_timeBegin.iHour = tempTime.GetHour();
	m_timeBegin.iMinute = tempTime.GetMinute();
	m_timeBegin.iSecond = tempTime.GetSecond();
	BeginTime = tempTime;

	m_DTDownloadEndTime.GetTime(tempTime);
	m_timeEnd.iYear = tempTime.GetYear();
	m_timeEnd.iMonth = tempTime.GetMonth();
	m_timeEnd.iDay = tempTime.GetDay();
	m_timeEnd.iHour = tempTime.GetHour();
	m_timeEnd.iMinute = tempTime.GetMinute();
	m_timeEnd.iSecond = tempTime.GetSecond();
	EndTime = tempTime;

	if (BeginTime >= EndTime)
	{
		return;
	}

	CString cstrLocalFileName;
	cstrLocalFileName.Format("Demo_Download%d%d%d%d%d%d-%d%d%d%d%d%d.sdv",
		m_timeBegin.iYear,
		m_timeBegin.iMonth,
		m_timeBegin.iDay,
		m_timeBegin.iHour,
		m_timeBegin.iMinute,
		m_timeBegin.iSecond,
		m_timeEnd.iYear,
		m_timeEnd.iMonth ,
		m_timeEnd.iDay ,
		m_timeEnd.iHour ,
		m_timeEnd.iMinute,
		m_timeEnd.iSecond);
	cstrLocalFileName = GetLocalSaveDirectory() + "\\" + cstrLocalFileName;

	int iChannelNo = m_ComboChannelNo.GetCurSel();
	int iStreamNo = m_cboStreamNo.GetCurSel();

	DOWNLOAD_TIMESPAN tDownloadTimeSpan = {0};
	tDownloadTimeSpan.m_iSize = sizeof(DOWNLOAD_TIMESPAN);

	tDownloadTimeSpan.m_iSaveFileType = m_cboDownloadFileType.GetItemData(m_cboDownloadFileType.GetCurSel());
	tDownloadTimeSpan.m_iFileFlag = m_cboDownloadFileFlag.GetItemData(m_cboDownloadFileFlag.GetCurSel());
	if (DOWNLOAD_FILE_TYPE_MP4 == tDownloadTimeSpan.m_iSaveFileType)
	{
		PathRenameExtension(cstrLocalFileName.GetBuffer(),  _T(".mp4"));
		cstrLocalFileName.ReleaseBuffer();
	}
	if (DOWNLOAD_FILE_TYPE_PS == tDownloadTimeSpan.m_iSaveFileType)
	{
		PathRenameExtension(cstrLocalFileName.GetBuffer(),  _T(".ps"));
		cstrLocalFileName.ReleaseBuffer();
	}

	int iCpyLen =  min(cstrLocalFileName.GetLength() + 1, 255);

	strcpy_s(tDownloadTimeSpan.m_cLocalFilename, iCpyLen, cstrLocalFileName.GetBuffer());
	cstrLocalFileName.ReleaseBuffer();
	tDownloadTimeSpan.m_iChannelNO = iChannelNo;
	tDownloadTimeSpan.m_iStreamNo = iStreamNo;

	tDownloadTimeSpan.m_tTimeBegin = m_timeBegin;
	tDownloadTimeSpan.m_tTimeEnd = m_timeEnd;
	tDownloadTimeSpan.m_iPosition = -1;
	tDownloadTimeSpan.m_iSpeed = 32;
	tDownloadTimeSpan.m_iReqMode = 1;	//1:down frame mode,0= Flow pattern; if (mode == 0) Device do not send download time !
	//start dowmload
	int iRet = NetClient_NetFileDownload((unsigned int*)&m_ulConnID, m_iLogonID, DOWNLOAD_CMD_TIMESPAN,&tDownloadTimeSpan,sizeof(DOWNLOAD_TIMESPAN));
 	if (iRet >= 0)
 	{
		//set dowmlload speed
		DOWNLOAD_TIMESPAN tTemp = {0};
		tTemp.m_iSize = sizeof(DOWNLOAD_TIMESPAN);
		int iSz = sizeof(DOWNLOAD_FILE);
		tTemp.m_iPosition = -1;
		tTemp.m_iSpeed = 16;
		tTemp.m_iReqMode = 1;
		NetClient_NetFileDownload((unsigned int*)&m_ulConnID, m_iLogonID, DOWNLOAD_CMD_CONTROL,&tTemp,sizeof(DOWNLOAD_TIMESPAN));
 	}
	m_ProgressDownload.SetPos(0);

	//标准数据（PS）回调
	if (DOWNLOAD_FILE_TYPE_PS == tDownloadTimeSpan.m_iSaveFileType && NULL != NetClient_SetDataPackCallBack)
	{
		//若果不需要写文件的，只需要回调，可以将本地文件名称传空
		NetClient_SetDataPackCallBack(m_ulConnID, DTYPE_PS, (void*)&PsDataCallBackFunction, NULL);
	}

	SetDlgItemTextEx(IDC_STATIC_PBK_DOWNLOAD_BY_TIME_STATUS, IDS_PLAYBACK_DOWNLOAD_STATUS);
}

BOOL CLS_RemoteByTimePage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_DTDownloadBeginTime.SetFormat("yyyy-MM-dd HH:mm:ss");
	m_DTDownloadEndTime.SetFormat("yyyy-MM-dd HH:mm:ss");

	CTime SystemTime; 
	m_DTDownloadBeginTime.GetTime(SystemTime);
	CTime BeginTime(SystemTime.GetYear(), SystemTime.GetMonth(), SystemTime.GetDay(), 0, 0, 0);
	m_DTDownloadBeginTime.SetTime(&BeginTime);
	CTime EndTime(SystemTime.GetYear(), SystemTime.GetMonth(), SystemTime.GetDay(), 23, 59, 0);
	m_DTDownloadEndTime.SetTime(&EndTime);

	m_ProgressDownload.SetRange(1, 100);
	m_ProgressDownload.SetPos(1);
	memset(&m_timeBegin, 0, sizeof(m_timeBegin));
	memset(&m_timeEnd, 0, sizeof(m_timeEnd));
	UI_UpdateText();
	SetTimer(TIMER_DOWNLOAD_BY_TIME, 1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CLS_RemoteByTimePage::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	return CLS_BasePage::DestroyWindow();
}

void CLS_RemoteByTimePage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (_iLogonID < 0 || m_ulConnID != INVALID_ID)
	{
		return;
	}
	m_iLogonID = _iLogonID;	
	Update_UI_IPAndID();
}

void CLS_RemoteByTimePage::ProccessDownloadMsg( int _iResourceID )
{
	NetClient_NetFileStopDownloadFile(m_ulConnID);
	m_ulConnID = INVALID_ID;
	SetDlgItemTextEx(IDC_STATIC_PBK_DOWNLOAD_BY_TIME_STATUS, _iResourceID);
}
void CLS_RemoteByTimePage::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser )
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
			m_ProgressDownload.SetPos(100);
			ProccessDownloadMsg(IDS_PLAYBACK_DOWNLOAD_FINISH);	
		}
		break;
	case WCM_DWONLOAD_FAULT:
		if (m_ulConnID == (unsigned long)_iLParam)
		{
			ProccessDownloadMsg(IDS_PLAYBACK_DOWNLOAD_FAULT);
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
	case WCM_LOGON_NOTIFY:
		{
			if (m_iLogonID == _ulLogonID && LOGON_SUCCESS == (int)_iLParam)
			{
				ProccessDownloadMsg(IDS_PLAYBACK_DOWNLOAD_STATUS);
			}
		}
		break;
	default:
		break;
	}
	for (list <CLS_FilePlayReviewPage *>::iterator it = m_lstPlayPage.begin(); it != m_lstPlayPage.end(); it++)
	{
		CLS_FilePlayReviewPage * pclsPlayPage = *it;
		if (NULL == pclsPlayPage)
		{
			continue;
		}

		if (NULL == pclsPlayPage->GetSafeHwnd() || !IsWindow(pclsPlayPage->GetSafeHwnd()))
		{
			continue;
		}
		pclsPlayPage->OnMainNotify(_ulLogonID, _iWparam, _iLParam, _iUser);
	}	
}

void CLS_RemoteByTimePage::OnLanguageChanged( int )
{
	UI_UpdateText();
}

LRESULT CLS_RemoteByTimePage::OnPlayPageDestory( WPARAM wParam, LPARAM lParam )
{
	int iSize = m_lstPlayPage.size();
	for (list <CLS_FilePlayReviewPage *>::iterator it = m_lstPlayPage.begin(); it != m_lstPlayPage.end();)
	{
		CLS_FilePlayReviewPage * pclsPlayPage = *it;
		if (NULL == pclsPlayPage)
		{
			it = m_lstPlayPage.erase(it);
			continue;
		}

		if (NULL == pclsPlayPage->GetSafeHwnd() || !IsWindow(pclsPlayPage->GetSafeHwnd()))
		{
			it = m_lstPlayPage.erase(it);
			delete pclsPlayPage;
			pclsPlayPage = NULL;
			continue;
		}

		++it;
	}

	return RET_SUCCESS;
}

void CLS_RemoteByTimePage::Update_UI_IPAndID()
{
	PDEVICE_INFO DeviceInfo = FindDevice(m_iLogonID);
	if (DeviceInfo)
	{
		CString strDeviceIP = GetTextEx(IDS_PLAYBACK_DEVICE_IP) + ":" + DeviceInfo->cIP;
		CString strDeviceID = GetTextEx(IDS_PLAYBACK_DEVICE_ID) + ":" + DeviceInfo->cID;
		SetDlgItemText(IDC_STATIC_PLAYBACK_BY_TIME_DEVICE_IP ,strDeviceIP);
		SetDlgItemText(IDC_STATIC_PLAYBACK_BY_TIME_DEVICE_ID ,strDeviceID);
		int iChannelNum = 0;
		NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
		m_ComboChannelNo.ResetContent();
		for (int i = 0; i < iChannelNum; i++)
		{
			CString str;
			str.Format("%d", i);
			m_ComboChannelNo.AddString(str);
		}
		m_ComboChannelNo.SetCurSel(0);
		m_cboStreamNo.SetCurSel(0);
	}
}
void CLS_RemoteByTimePage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case TIMER_DOWNLOAD_BY_TIME:
		QueryDownloadProgress();
		break;
	default:
		return;

	}
	CLS_BasePage::OnTimer(nIDEvent);
}

void CLS_RemoteByTimePage::QueryDownloadProgress()
{
	if (m_ulConnID != INVALID_ID)
	{
		int uiCurrentTime = 0;
		int iSize = 0;
		if (NetClient_NetFileGetDownloadPos(m_ulConnID, &uiCurrentTime, &iSize) >= 0)
		{
			unsigned int uiBeginTime = NvsFileTimeToAbsSeconds(&m_timeBegin);
			unsigned int uiEndTime = NvsFileTimeToAbsSeconds(&m_timeEnd);
			int iTimeInterval = uiEndTime - uiBeginTime;
			if (iTimeInterval > 0)
			{
				int iCurrentInterval = uiCurrentTime - uiBeginTime;
				if (iCurrentInterval < iTimeInterval)
				{

					int iProcess = iCurrentInterval*100/iTimeInterval;
					if (iProcess > 100)
					{
						return;
					}
					m_ProgressDownload.SetPos(iProcess);
				}

			}
			NVS_FILE_TIME CurrentTime = {0};
			AbsSecondsToNvsFileTime(&CurrentTime, uiCurrentTime);
			CString szTime;
			szTime.Format("%d-%d-%d %d:%d:%d", CurrentTime.iYear, CurrentTime.iMonth, CurrentTime.iDay,
				CurrentTime.iHour, CurrentTime.iMinute, CurrentTime.iSecond);
			SetDlgItemText(IDC_STATIC_PBK_DOWNLOAD_BY_TIME_STATUS, szTime);
		}
	}
}

void CLS_RemoteByTimePage::OnBnClickedButtonPlaybackByTimePlay()
{
	if (m_iLogonID == INVALID_ID)
	{
		return;
	}
	
	NVS_FILE_TIME begintime = {0};
	NVS_FILE_TIME endtime = {0};

	CTime tempTime,timeBegin, timeEnd;
	m_DTDownloadBeginTime.GetTime(tempTime);
	timeBegin= tempTime;
	begintime.iYear = tempTime.GetYear();
	begintime.iMonth = tempTime.GetMonth();
	begintime.iDay = tempTime.GetDay();
	begintime.iHour = tempTime.GetHour();
	begintime.iMinute = tempTime.GetMinute();
	begintime.iSecond = tempTime.GetSecond();

	m_DTDownloadEndTime.GetTime(tempTime);
	timeEnd = tempTime;
	endtime.iYear = tempTime.GetYear();
	endtime.iMonth = tempTime.GetMonth();
	endtime.iDay = tempTime.GetDay();
	endtime.iHour = tempTime.GetHour();
	endtime.iMinute = tempTime.GetMinute();
	endtime.iSecond = tempTime.GetSecond();

	if (timeBegin >= timeEnd)
	{
		return;
	}

	int iChannelNo = m_ComboChannelNo.GetCurSel();
	int iStreamNo = m_cboStreamNo.GetCurSel();
	int iChannelNum = 0;
	NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
	int iRealChannel = iStreamNo*iChannelNum+iChannelNo;

	int iCurDevPlayPageNum = 0;
	for (list <CLS_FilePlayReviewPage *>::iterator it = m_lstPlayPage.begin(); it != m_lstPlayPage.end(); it++)
	{
		CLS_FilePlayReviewPage * pclsPlayPage = *it;
		if (NULL == pclsPlayPage || NULL == pclsPlayPage->GetSafeHwnd() || !IsWindow(pclsPlayPage->GetSafeHwnd()))
		{
			continue;
		}

		if (pclsPlayPage->GetLogonID() == m_iLogonID)
		{
			iCurDevPlayPageNum++;
			continue;
		}
	}

	if (MAX_PLAY_PAGE_NUM <= iCurDevPlayPageNum)
	{
		AddLog(LOG_TYPE_MSG, "", "Added too much file with same device to playback list!");
		return;
	}

	CLS_FilePlayReviewPage* pclsPlayReviewPage = new CLS_FilePlayReviewPage(this);
	if (NULL != pclsPlayReviewPage)
	{
		pclsPlayReviewPage->SetDownloadParam(m_iLogonID, iRealChannel/*iChannelNo*/, &begintime, &endtime);
		pclsPlayReviewPage->Create(IDD_DLG_PBK_REVIEW, this);
		pclsPlayReviewPage->ShowWindow(SW_SHOW);
	}

	m_lstPlayPage.push_back(pclsPlayReviewPage);
}

void CLS_RemoteByTimePage::UI_UpdateText()
{
	SetDlgItemTextEx(IDC_STATIC_PLAYBACK_BY_TIME_DEVICE_IP, IDS_PLAYBACK_DEVICE_IP);
	SetDlgItemTextEx(IDC_STATIC_PLAYBACK_BY_TIME_DEVICE_ID, IDS_PLAYBACK_DEVICE_ID);
	SetDlgItemTextEx(IDC_STATIC_DOWNLOAD_AND_PLAY, IDS_PLAYBACK_DOWNLOAD_AND_PLAY);
	SetDlgItemTextEx(IDC_BUTTON_PLAY_BY_TIME_DOWNLOAD, IDS_PLAYBACK_DOWNLOAD);
	SetDlgItemTextEx(IDC_BUTTON_PLAYBACK_BY_TIME_PLAY, IDS_PLAYBACK_PLAY);
	SetDlgItemTextEx(IDC_STATIC_DOWNLOAD_BY_TIME_BEGINTIME, IDS_PLAYBACK_DOWNLOAD_BEGINTIME);
	SetDlgItemTextEx(IDC_STATIC_DOWNLOAD_BY_TIME_ENDTIME, IDS_PLAYBACK_DOWNLOAD_ENDTIME);
	SetDlgItemTextEx(IDC_STATIC_DOWNLOAD_BY_TIME_CHANNELNO, IDS_PLAYBACK_DOWNLOAD_CHANNELNO);
	SetDlgItemTextEx(IDC_STATIC_PBK_DOWNLOAD_BY_TIME_STATUS, IDS_PLAYBACK_DOWNLOAD_STATUS);
	SetDlgItemTextEx(IDC_BUTTON_STOP, IDS_CONFIG_DONWLOAD_STOP);
	SetDlgItemTextEx(IDC_STATIC_DOWNLOAD_BY_TIME_STREAMNO, IDS_CONFIG_ADV_STREAMTYPE);
	InsertString(m_cboStreamNo,0,GetTextEx(IDS_MAJOR));
	InsertString(m_cboStreamNo,1,GetTextEx(IDS_MINOR));

	int iIndex = m_cboDownloadFileType.GetCurSel();
	m_cboDownloadFileType.ResetContent();
	m_cboDownloadFileType.SetItemData(m_cboDownloadFileType.AddString(_T("SDV")), DOWNLOAD_FILE_TYPE_SDV);
	m_cboDownloadFileType.SetItemData(m_cboDownloadFileType.AddString(_T("MP4")), DOWNLOAD_FILE_TYPE_MP4);
	m_cboDownloadFileType.SetItemData(m_cboDownloadFileType.AddString(_T("PS")), DOWNLOAD_FILE_TYPE_PS);
	iIndex = (iIndex >= m_cboDownloadFileType.GetCount() || iIndex < 0) ? 0 : iIndex;
	m_cboDownloadFileType.SetCurSel(iIndex);

	iIndex = m_cboDownloadFileFlag.GetCurSel();
	m_cboDownloadFileFlag.ResetContent();
	m_cboDownloadFileFlag.SetItemData(m_cboDownloadFileFlag.AddString(GetTextEx(IDS_MULTI_FILE)), DOWNLOAD_FILE_FLAG_MULTI);
	m_cboDownloadFileFlag.SetItemData(m_cboDownloadFileFlag.AddString(GetTextEx(IDS_SINGLE_FILE)), DOWNLOAD_FILE_FLAG_SINGLE);
	iIndex = (iIndex >= m_cboDownloadFileFlag.GetCount() || iIndex < 0) ? 0 : iIndex;
	m_cboDownloadFileFlag.SetCurSel(iIndex);

}
void CLS_RemoteByTimePage::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID != INVALID_ID && m_ulConnID != INVALID_ID)
	{
		NetClient_NetFileStopDownloadFile(m_ulConnID);
		m_ProgressDownload.SetPos(0);
		m_ulConnID = INVALID_ID;
		SetDlgItemTextEx(IDC_STATIC_PBK_DOWNLOAD_BY_TIME_STATUS, IDS_PLAYBACK_DOWNLOAD_STATUS);
	}
}

void CLS_RemoteByTimePage::OnLogoffDevice( int _iLogonID )
{
	if (_iLogonID == m_iLogonID)
	{
		ProccessDownloadMsg(IDS_PLAYBACK_DOWNLOAD_STATUS);
	}
}

void CLS_RemoteByTimePage::OnBnClickedBtnSuperVodByTime()
{
	if (m_iLogonID == INVALID_ID)
	{
		return;
	}

	NVS_FILE_TIME begintime = {0};
	NVS_FILE_TIME endtime = {0};

	CTime tempTime,timeBegin, timeEnd;
	m_DTDownloadBeginTime.GetTime(tempTime);
	timeBegin= tempTime;
	begintime.iYear = tempTime.GetYear();
	begintime.iMonth = tempTime.GetMonth();
	begintime.iDay = tempTime.GetDay();
	begintime.iHour = tempTime.GetHour();
	begintime.iMinute = tempTime.GetMinute();
	begintime.iSecond = tempTime.GetSecond();

	m_DTDownloadEndTime.GetTime(tempTime);
	timeEnd = tempTime;
	endtime.iYear = tempTime.GetYear();
	endtime.iMonth = tempTime.GetMonth();
	endtime.iDay = tempTime.GetDay();
	endtime.iHour = tempTime.GetHour();
	endtime.iMinute = tempTime.GetMinute();
	endtime.iSecond = tempTime.GetSecond();

	if (timeBegin >= timeEnd)
	{
		return;
	}

	int iChannelNo = m_ComboChannelNo.GetCurSel();
	int iStreamNo = m_cboStreamNo.GetCurSel();
	int iChannelNum = 0;
	NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
	int iRealChannel = iStreamNo*iChannelNum+iChannelNo;

	if (MAX_PLAY_PAGE_NUM <= m_lstPlayPage.size())
	{
		AddLog(LOG_TYPE_MSG, "", "Added too much file to playback list!");
		return;
	}

	CLS_FilePlayReviewPage* pclsPlayReviewPage = new CLS_FilePlayReviewPage(this);
	if (NULL != pclsPlayReviewPage)
	{
		pclsPlayReviewPage->SetDownloadParamEx(m_iLogonID, iRealChannel, &begintime, &endtime);
		pclsPlayReviewPage->Create(IDD_DLG_PBK_REVIEW, this);
		pclsPlayReviewPage->ShowWindow(SW_SHOW);
	}

	m_lstPlayPage.push_back(pclsPlayReviewPage);
}
