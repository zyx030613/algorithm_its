// RemoteFileTab.cpp : implementation file
//

#include "stdafx.h"
#include "RemoteFilePage.h"
#include <shlwapi.h>
#include "mmsystem.h"
#pragma comment(lib, "Winmm.lib")

#define YEARCOUNT			0		//年份检测值
#define MONTHMIN			1		//月份最小值
#define MONTHMAX			12		//月份最大值
#define MOONCOLUMN			1		//月照信息列表列数
#define MONTHDAYNUM			31		//每月的最大天数


int _g_iTimeInterval = 0;

void _PsDataCallBackFunction(unsigned int _ulID, unsigned char* _cData, int _iLen, int _iType, void* _pvUserData)
{
	if (NULL == _cData)
	{
		return;
	}

#ifdef _DEBUG
	CString cstrLog;
	int iTime = timeGetTime();
	cstrLog.Format("[RecvPsDataNotify ConnectId(%d) Time(%d) DataLen(%d)]\n", _ulID, iTime - _g_iTimeInterval, _iLen);
	_g_iTimeInterval = iTime;
	OutputDebugString(cstrLog);
#endif
}

// CLS_RemoteFilePage dialog
IMPLEMENT_DYNAMIC(CLS_RemoteFilePage, CDialog)
CString g_szDownloadPath = "c:\\netclientdemo_download\\";
CLS_RemoteFilePage::CLS_RemoteFilePage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_RemoteFilePage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNo = 0;

	m_iTotalCount = 0;
	m_iCurrentCount = 0;
	m_iCurrentPage = 0;
	m_iTotalPage = 0;
}

CLS_RemoteFilePage::~CLS_RemoteFilePage()
{
}

void CLS_RemoteFilePage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FILE_TYPE, m_ComboFileType);
	DDX_Control(pDX, IDC_COMBO_REC_TYPE, m_ComboRecType);
	DDX_Control(pDX, IDC_COMBO_Channel, m_ComboChannelNo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_QUERY_BEGINTIME, m_DTQueryBeginTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_QUERY_ENDTIME, m_DTQueryEndTime);
	DDX_Control(pDX, IDC_EDIT_OSD, m_EditOSD);
	DDX_Control(pDX, IDC_LIST_QUERY_FILE, m_ListQueryFile);
	DDX_Control(pDX, IDC_COMBO_QUERY_PAGE, m_ComboQueryPage);
	DDX_Control(pDX, IDC_COMBO_ALARM_TYPE, m_cboAlarmType);
	DDX_Control(pDX, IDC_COMBO_ALARMPORT, m_cboAlarmPort);
	DDX_Control(pDX, IDC_COMBO_REQ_MODE, m_cboReqMode);
	DDX_Control(pDX, IDC_DATETIMEPICKER_PLAYBACK_RECORINGDAY, m_DTRecordingDate);
	DDX_Control(pDX, IDC_LST_PLAYBACK_MOON_LIST, m_lstMoonInfoList);
	DDX_Control(pDX, IDC_CBO_DOWNLOAD_FILETYPE, m_cboDownloadFileType);
	DDX_Control(pDX, IDC_CBO_STREAM, m_cboStreamNo);
	DDX_Control(pDX, IDC_CHECK_BREAK_CONTINUE, m_chkBreakNetContinue);
	DDX_Control(pDX, IDC_CHECK_BATCH_QUERY, m_chkBatchQuery);
}


BEGIN_MESSAGE_MAP(CLS_RemoteFilePage, CLS_BasePage)


	ON_BN_CLICKED(IDC_BUTTON_PLAYBACK, &CLS_RemoteFilePage::OnBnClickedButtonPlayback)
	ON_CBN_SELCHANGE(IDC_COMBO_Channel, &CLS_RemoteFilePage::OnCbnSelchangeComboChannel)
	ON_CBN_SELCHANGE(IDC_COMBO_FILE_TYPE, &CLS_RemoteFilePage::OnCbnSelchangeComboFileType)
	ON_CBN_SELCHANGE(IDC_COMBO_REC_TYPE, &CLS_RemoteFilePage::OnCbnSelchangeComboRecType)
	ON_CBN_SELCHANGE(IDC_COMBO_QUERY_PAGE, &CLS_RemoteFilePage::OnCbnSelchangeComboQueryPage)
	ON_BN_CLICKED(IDC_BUTTON_PREPAGE, &CLS_RemoteFilePage::OnBnClickedButtonPrepage)
	ON_BN_CLICKED(IDC_BUTTON_NEXT_PAGE, &CLS_RemoteFilePage::OnBnClickedButtonNextPage)
	ON_BN_CLICKED(IDC_BUTTON_FIRST_PAGE, &CLS_RemoteFilePage::OnBnClickedButtonFirstPage)
	ON_BN_CLICKED(IDC_BUTTON_LAST_PAGE, &CLS_RemoteFilePage::OnBnClickedButtonLastPage)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_QUERY_BEGINTIME, &CLS_RemoteFilePage::OnDtnDatetimechangeDatetimepickerQueryBegintime)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_QUERY_ENDTIME, &CLS_RemoteFilePage::OnDtnDatetimechangeDatetimepickerQueryEndtime)
	ON_NOTIFY(NM_CLICK, IDC_LIST_QUERY_FILE, &CLS_RemoteFilePage::OnNMClickListQueryFile)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, &CLS_RemoteFilePage::OnBnClickedButtonDownload)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_QUERY, &CLS_RemoteFilePage::OnBnClickedButtonQuery)
	ON_BN_CLICKED(IDC_BUTTON_STOP_DOWNLOAD, &CLS_RemoteFilePage::OnBnClickedButtonStopDownload)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE_DOWNLOAD, &CLS_RemoteFilePage::OnBnClickedButtonPauseDownload)
	ON_BN_CLICKED(IDC_BUTTON_CONTINUE_DOWNLOAD, &CLS_RemoteFilePage::OnBnClickedButtonContinueDownload)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_QUERY_FILE, &CLS_RemoteFilePage::OnLvnItemchangedListQueryFile)
	ON_BN_CLICKED(IDC_BTN_PLAYBACK_MOON_REFRESH, &CLS_RemoteFilePage::OnBnClickedBtnPlaybackMoonRefresh)
	ON_MESSAGE(WM_PLAY_PAGE_DESTORY, &CLS_RemoteFilePage::OnPlayPageDestory)
	ON_BN_CLICKED(IDC_BUTTON_BREAK_NET_CONTINUE, &CLS_RemoteFilePage::OnBnClickedButtonBreakNetContinue)
END_MESSAGE_MAP()


// CLS_RemoteFilePage message handlers

BOOL CLS_RemoteFilePage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_DTQueryBeginTime.SetFormat("yyyy-MM-dd HH:mm:ss");
	m_DTQueryEndTime.SetFormat("yyyy-MM-dd HH:mm:ss");
	m_DTRecordingDate.SetFormat("yyyy-MM");


	CTime SystemTime; 
	m_DTQueryBeginTime.GetTime(SystemTime);
	CTime BeginTime(SystemTime.GetYear(), SystemTime.GetMonth(), SystemTime.GetDay(), 0, 0, 0);
	m_DTQueryBeginTime.SetTime(&BeginTime);
	CTime EndTime(SystemTime.GetYear(), SystemTime.GetMonth(), SystemTime.GetDay(), 23, 59, 0);
	m_DTQueryEndTime.SetTime(&EndTime);

	m_ListQueryFile.SetExtendedStyle(m_ListQueryFile.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	m_ListQueryFile.DeleteAllItems();
	Update_UI_Text();
	m_cboAlarmType.SetCurSel(0);
	SetTimer(TIMER_QUERY_DOWNLOAD_PROGRESS, 1000, NULL);
	//CreateDirectory(g_szDownloadPath, NULL);
	g_szDownloadPath = GetLocalSaveDirectory() + "\\";

	imageList.Create(16,16,ILC_COLOR32,2,2);
	imageList.SetBkColor(RGB(255,255,255));
	HICON hICON=AfxGetApp()->LoadIcon(IDI_LOCK_OPEN);
	imageList.Add(hICON);
	hICON=AfxGetApp()->LoadIcon(IDI_LOCK);
	imageList.Add(hICON);
	m_ListQueryFile.SetImageList(&imageList,LVSIL_SMALL);

	m_cboReqMode.SetCurSel(1);

	m_lstMoonInfoList.DeleteAllItems();
	m_lstMoonInfoList.SetExtendedStyle(m_lstMoonInfoList.GetExtendedStyle()| LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	CString cstrDay = "";
	CString cstrMoon = "";
	cstrMoon = GetTextEx(IDS_PLAYBACK_FILE_MOON_NO);
	for(int i = 0; i < MONTHDAYNUM; i++)
	{
		cstrDay.Format("%d", i + 1);
		m_lstMoonInfoList.InsertItem(i, cstrDay);
		m_lstMoonInfoList.SetItemText(i,  MOONCOLUMN, cstrMoon);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CLS_RemoteFilePage::UpdateMoonInfo()
{
	if(m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[CLS_RemoteFilePage::UpdateMoonInfo]Invalid logon id(%d)", m_iLogonID);
		return;
	}

	CString cstrMoon = "";
	FileMap stFileMap = {0};
	stFileMap.iSize = sizeof(FileMap);
	int iRet = NetClient_RecvCommand(m_iLogonID, COMMAND_ID_FILE_MAP, m_iChannelNo, &stFileMap, sizeof(FileMap));
	if(RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[RemoteFilePage::UpdateMoonInfo][FILE_MAP] Set fail,error = %d", GetLastError());
		return;
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_RecvCommand(%d)", m_iLogonID);
	}

	int iArryLength = sizeof(stFileMap.iRecFile)/sizeof(stFileMap.iRecFile[0]);//求取数组的长度
	for(int i = 0; i < iArryLength; i++)
	{
		if(0 != stFileMap.iRecFile[i])
		{
			cstrMoon = GetTextEx(IDS_PLAYBACK_FILE_MOON_HAS);
		}
		else
		{
			cstrMoon = GetTextEx(IDS_PLAYBACK_FILE_MOON_NO);
		}
		m_lstMoonInfoList.SetItemText(i,  MOONCOLUMN, cstrMoon);
	}

}

void CLS_RemoteFilePage::RefreshMoonInfo()
{
	if(m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","[CLS_RemoteFilePage::RefreshMoonInfo]Invalid logon id(%d)", m_iLogonID);
		return;
	}

	CTime tempTime;
	m_DTRecordingDate.GetTime(tempTime);

	FileMap stFileMap = {0};
	stFileMap.iSize = sizeof(FileMap);
	stFileMap.iChanNo = m_iChannelNo;	
	stFileMap.iStreamNo = m_iStreamNo;
	stFileMap.iYear = tempTime.GetYear();
	stFileMap.iMonth = tempTime.GetMonth();

	int iRet = NetClient_SendCommand(m_iLogonID, COMMAND_ID_FILE_MAP, m_iChannelNo, &stFileMap, sizeof(FileMap));
	if(RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_RemoteFilePage][FILE_MAP] Set fail,error = %d", GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SendCommand(%d)", m_iLogonID);
	}
}

void CLS_RemoteFilePage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (_iLogonID < 0)
	{
		return;
	}
	m_iLogonID = _iLogonID;
	m_iChannelNo = (_iChannelNo < 0) ? FLAG_QUERY_ALL_CHANNEL : _iChannelNo;
	m_iStreamNo = (_iStreamNo < MAIN_STREAM) ? MAIN_STREAM : _iStreamNo;

	//默认查主码流
	m_iStreamNo = (m_iStreamNo > SUB_STREAM) ? MAIN_STREAM : m_iStreamNo;

	Update_UI_IPAndID();
	ResetQuery();
	QueryFile();
	//RefreshMoonInfo();
	UpdateMoonInfo();
}

void CLS_RemoteFilePage::OnLogonNotify( int _ulLogonID, int _iStatus ) 
{
	if (LOGON_SUCCESS == _iStatus)
	{
		DOWNLOAD_FILE tdf = {sizeof(DOWNLOAD_FILE)};
		unsigned int iConnID = -1;
			for (list <CLS_DownloadFile *>::iterator it = m_lstDownloadFile.begin(); it != m_lstDownloadFile.end(); it++)
			{
				CLS_DownloadFile * downloadFile = *it;
				if ( downloadFile->GetLogonID() == _ulLogonID)
				{
					if (1 == downloadFile->GetBreakContinue())
					{
						strcpy_s(tdf.m_cRemoteFilename,downloadFile->GetFilename().GetLength()+1,(char *)(LPCSTR)downloadFile->GetFilename());
						strcpy_s(tdf.m_cLocalFilename,(g_szDownloadPath + downloadFile->GetFilename()).GetLength()+1,(char*)(LPCSTR)(g_szDownloadPath + downloadFile->GetFilename()));
						tdf.m_iPosition = downloadFile->GetPosition();
						tdf.m_iSpeed = 16;
						tdf.m_iReqMode = downloadFile->GetReqMode();
						int iRet = NetClient_NetFileDownload((unsigned int*)&iConnID, m_iLogonID, DOWNLOAD_CMD_FILE_CONTINUE,&tdf,sizeof(DOWNLOAD_FILE));
						if (iRet >= 0)
						{
							downloadFile->SetConnID(iConnID);
						}
					}
					break;
				}
			}
		
	}
	else
	{
		DeleteDownload(_ulLogonID,0);
	}
}

void CLS_RemoteFilePage::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser )
{
	if (m_iLogonID < 0)
	{
		return;
	}

	int iMsgType = LOWORD(_iWparam);
	switch(iMsgType)
	{
	case WCM_QUERYFILE_FINISHED:
		{
			NVS_IPAndID *pNvs = (NVS_IPAndID *)_iLParam;
			if (pNvs)
			{
				int iLogonID = *pNvs->m_piLogonID;
				if (iLogonID != m_iLogonID)
				{
					return;
				}
				NetClient_NetFileGetFileCount(m_iLogonID, &m_iTotalCount, &m_iCurrentCount);
				Update_UI_Query_Result();
			}
			//break;
		}
	case WCM_DWONLOAD_FINISHED:
		ProcessDownloadFinished((unsigned long)_iLParam);
		break;
	case WCM_DWONLOAD_FAULT:
		{
			ProcessDownloadInterrupt((unsigned long)_iLParam);
			break;
		}
	case WCM_ERR_ORDER: 
		{
			ProcessErrorOrder(_ulLogonID);
			break;
		}
	case WCM_DOWNLOAD_INTERRUPT:
		{
			ProcessDownloadInterrupt((unsigned long)_iLParam);
			break;
		}
	case WCM_LOCALSTORE_LOCK_FILE:
		{
			OnNetFileLockFiles(_iWparam, (LPARAM)_iLParam);
			break;
		}	
	case WCM_LOGON_NOTIFY:
		{
			OnLogonNotify(_ulLogonID,(int)_iLParam);			
		}
		break;
	case WCM_FILE_MAP:
		{
			UpdateMoonInfo();
		}
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

void CLS_RemoteFilePage::OnBnClickedButtonPlayback()
{
	if (m_iLogonID < 0 || m_szFileName == "")
	{
		return;
	}

	if (m_szFileName.GetLength()	>=	4)
	{
		CString strExt	=	m_szFileName.Right(4).MakeLower();
		if(strExt	==	".bmp"	||	strExt	==	".jpg")
		{
			return;
		}
	}

	unsigned long iConnID = -1;
	if (IsFileInDownLoadList(m_iLogonID, m_szFileName, &iConnID))
	{
		AddLog(LOG_TYPE_MSG, "", "File(%s) is already in download list!", m_szFileName);
		return;
	}

	int iCurDevPlayPage = 0;
	if (IsFileInPlayBackList(m_iLogonID, m_szFileName, &iCurDevPlayPage))
	{
		AddLog(LOG_TYPE_MSG, "", "File(%s) is already in playback list!", m_szFileName);
		return;
	}

	if (MAX_PLAY_PAGE_NUM <= iCurDevPlayPage)
	{
		AddLog(LOG_TYPE_MSG, "", "Added too much file with same device to playback list!");
		return;
	}

	CLS_FilePlayReviewPage* pclsPlayReviewPage = new CLS_FilePlayReviewPage(this);

	if (NULL != pclsPlayReviewPage/* && IsWindow(pclsPlayReviewPage->GetSafeHwnd())*/)
	{
		pclsPlayReviewPage->SetDownloadParam(m_iLogonID, m_szFileName);
		pclsPlayReviewPage->Create(IDD_DLG_PBK_REVIEW, this);
		pclsPlayReviewPage->ShowWindow(SW_SHOW);
	}

	m_lstPlayPage.push_back(pclsPlayReviewPage);
}

void CLS_RemoteFilePage::Update_UI_Text()
{
	SetDlgItemTextEx(IDC_STATIC_PLAYBACK_QUERY_CONDITION, IDS_PLAYBACK_QUERY_CONDITION);

	m_ComboFileType.ResetContent();
	m_ComboFileType.AddString(GetTextEx(IDS_PLAYBACK_TYPE_ALL));
	m_ComboFileType.AddString(GetTextEx(IDS_PLAYBACK_FILE_TYPE_VIDEO));
	m_ComboFileType.AddString(GetTextEx(IDS_PLAYBACK_FILE_TYPE_PICTURE));
	m_ComboFileType.SetCurSel(1);

	m_ComboRecType.ResetContent();
	m_ComboRecType.AddString(GetTextEx(IDS_PLAYBACK_TYPE_ALL));
	m_ComboRecType.AddString(GetTextEx(IDS_PLAYBACK_REC_TYPE_MANUEL));
	m_ComboRecType.AddString(GetTextEx(IDS_PLAYBACK_REC_TYPE_TIMER));
	m_ComboRecType.AddString(GetTextEx(IDS_PLAYBACK_REC_TYPE_ALARM));
	for (int i = 32; i < 64; i++)
	{
		CString str;
		str.Format("%d", i);
		m_ComboRecType.AddString(str);
	}
	m_ComboRecType.SetCurSel(0);

	SetDlgItemTextEx(IDC_STATIC_FILE_TYPE, IDS_PLAYBACK_FILE_TYPE);
	SetDlgItemTextEx(IDC_STATIC_REC_TYPE, IDS_PLAYBACK_REC_TYPE);
	SetDlgItemTextEx(IDC_STATIC_CHANNEL, IDS_PLAYBACK_CHANNEL);
	SetDlgItemTextEx(IDC_STATIC_TIME_RANGE, IDS_PLAYBACK_TIME_RANGE);
	SetDlgItemTextEx(IDC_STATIC_OSD, IDS_PLAYBACK_OSD);
	SetDlgItemTextEx(IDC_STATIC_DEVICE_IP, IDS_PLAYBACK_DEVICE_IP);
	SetDlgItemTextEx(IDC_STATIC_DEVICE_ID, IDS_PLAYBACK_DEVICE_ID);
	SetDlgItemTextEx(IDC_STATIC_FILE_COUNT, IDS_PLAYBACK_TOTAL_FILE_COUNT);
	SetDlgItemTextEx(IDC_BUTTON_PLAYBACK, IDS_PLAYBACK_PLAY);
	SetDlgItemTextEx(IDC_BUTTON_DOWNLOAD, IDS_PLAYBACK_DOWNLOAD);
	SetDlgItemTextEx(IDC_BUTTON_STOP_DOWNLOAD, IDS_PLAYBACK_STOP);
	SetDlgItemTextEx(IDC_BUTTON_PAUSE_DOWNLOAD, IDS_PLAYBACK_PAUSE);
	SetDlgItemTextEx(IDC_BUTTON_CONTINUE_DOWNLOAD, IDS_PLAYBACK_CONTINUE);
	SetDlgItemTextEx(IDC_BUTTON_PREPAGE, IDS_PLAYBACK_PREPAGE);
	SetDlgItemTextEx(IDC_BUTTON_NEXT_PAGE, IDS_PLAYBACK_NEXT_PAGE);
	SetDlgItemTextEx(IDC_BUTTON_FIRST_PAGE, IDS_PLAYBACK_FIRST_PAGE);
	SetDlgItemTextEx(IDC_BUTTON_LAST_PAGE, IDS_PLAYBACK_LAST_PAGE);
	SetDlgItemTextEx(IDC_STATIC_QUERY_PAGE, IDS_PLAYBACK_QUERY_PAGE);	
	SetDlgItemTextEx(IDC_BUTTON_QUERY, IDS_PBK_QUERY);
	SetDlgItemTextEx(IDC_STATIC_ALARM_TYPE, IDS_PLAYBACK_ALARM_TYPE);
	SetDlgItemTextEx(IDC_STATIC_ALARMPORT, IDS_IOPORT_INPORT);

	int iIndex = 0;
	InsertString(m_cboAlarmType, iIndex++, IDS_CONFIG_ITS_NO_ENABLE);
	InsertString(m_cboAlarmType, iIndex++, IDS_CONFIG_DNVR_PORTALARM);
	InsertString(m_cboAlarmType, iIndex++, IDS_CONFIG_DNVR_MOTIONDETECT);
	InsertString(m_cboAlarmType, iIndex++, IDS_CONFIG_DNVR_VIDEOLOST);

	int iColumnIndex = 0;
	InsertColumn( m_ListQueryFile, iColumnIndex++, "ID", LVCFMT_LEFT, 60 );//插入列
	InsertColumn( m_ListQueryFile, iColumnIndex++, IDS_PLAYBACK_FILE_NAME, LVCFMT_LEFT, 180 );
	InsertColumn( m_ListQueryFile, iColumnIndex++, IDS_PLAYBACK_REC_TYPE, LVCFMT_LEFT, 70 );
	InsertColumn( m_ListQueryFile, iColumnIndex++, IDS_PLAYBACK_CHANNEL, LVCFMT_LEFT, 70 );
	InsertColumn( m_ListQueryFile, iColumnIndex++, IDS_PLAYBACK_FILE_SIZE, LVCFMT_LEFT, 80 );
	InsertColumn( m_ListQueryFile, iColumnIndex++, IDS_PLAYBACK_DOWNLOAD_BEGINTIME, LVCFMT_LEFT, 150 );
	InsertColumn( m_ListQueryFile, iColumnIndex++, IDS_PLAYBACK_DOWNLOAD_ENDTIME, LVCFMT_LEFT, 150 );
	InsertColumn( m_ListQueryFile, iColumnIndex++, IDS_PLAYBACK_DOWNLOAD_PROGRESS, LVCFMT_LEFT, 120 );

	iIndex = 0;
	InsertString( m_cboReqMode, iIndex++, IDS_PBK_REQ_MODE_STREAM);
	InsertString( m_cboReqMode, iIndex++, IDS_PBK_REQ_MODE_FRAME);

	SetDlgItemTextEx(IDC_STATIC_REQ_MODE, IDS_PBK_REQ_MODE);
	SetDlgItemTextEx(IDC_CHECK_BREAK_CONTINUE, IDS_PBK_BREAK_CONTINUE);
	SetDlgItemTextEx(IDC_GBO_PLAYBACK_MOON_INFO, IDS_PLAYBACK_FILE_MOON_GBO_MOONINFO);
	SetDlgItemTextEx(IDC_STC_PLAYBACK_MOON_YEAR, IDS_PLAYBACK_FILE_MOON_STC_YEAR);	
	SetDlgItemTextEx(IDC_STC_PLAYBACK_MOON_MONTH, IDS_PLAYBACK_FILE_MOON_STCMONTH);
	SetDlgItemTextEx(IDC_BTN_PLAYBACK_MOON_REFRESH, IDS_PLAYBACK_FILE_MOON_REFRESH);
	SetDlgItemTextEx(IDC_CHECK_BATCH_QUERY, IDS_BATCH);

	int iCountMoonIndex = 0;
	InsertColumn(m_lstMoonInfoList, iCountMoonIndex++, GetTextEx(IDS_PLAYBACK_FILE_MOON_DATE), LVCFMT_LEFT, 200);
	InsertColumn(m_lstMoonInfoList, iCountMoonIndex++, GetTextEx(IDS_PLAYBACK_FILE_MOON_SATUS), LVCFMT_LEFT, 235);

	SetDlgItemTextEx(IDC_STC_DOWNLOAD_FILETYPE, IDS_PLAYBACK_FILE_TYPE);
	iIndex = m_cboDownloadFileType.GetCurSel();
	m_cboDownloadFileType.ResetContent();
	m_cboDownloadFileType.SetItemData(m_cboDownloadFileType.AddString(_T("SDV")), DOWNLOAD_FILE_TYPE_SDV);
	m_cboDownloadFileType.SetItemData(m_cboDownloadFileType.AddString(_T("MP4")), DOWNLOAD_FILE_TYPE_MP4);
	m_cboDownloadFileType.SetItemData(m_cboDownloadFileType.AddString(_T("PS")), DOWNLOAD_FILE_TYPE_PS);
	iIndex = (iIndex >= m_cboDownloadFileType.GetCount() || iIndex < 0) ? 0 : iIndex;
	m_cboDownloadFileType.SetCurSel(iIndex);

	SetDlgItemTextEx(IDC_STC_STREAM, IDS_CONFIG_DNVR_DIGIT_STREAMTYPE);
	iIndex = m_cboStreamNo.GetCurSel();
	m_cboStreamNo.ResetContent();
	m_cboStreamNo.SetItemData(m_cboStreamNo.AddString(GetTextEx(IDS_MAJOR)), MAIN_STREAM);
	m_cboStreamNo.SetItemData(m_cboStreamNo.AddString(GetTextEx(IDS_MINOR)), SUB_STREAM);
	iIndex = (iIndex >= m_cboStreamNo.GetCount() || iIndex < 0) ? 0 : iIndex;
	m_cboStreamNo.SetCurSel(iIndex);
	OnCbnSelchangeComboChannel();

	m_chkBreakNetContinue.SetCheck(BST_CHECKED);
}

void CLS_RemoteFilePage::Update_UI_Query_Result()
{
	CString strTotalFile = GetTextEx(IDS_PLAYBACK_TOTAL_FILE_COUNT) + ":";
	strTotalFile.AppendFormat("%d", m_iTotalCount);
	SetDlgItemText(IDC_STATIC_FILE_COUNT ,strTotalFile);
	m_iTotalPage = (m_iTotalCount+MAX_PAGESIZE-1)/MAX_PAGESIZE;

	m_ComboQueryPage.ResetContent();
	for (int i = 0; i < m_iTotalPage; i++)
	{
		CString strPage;
		strPage.Format("%d", i+1);
		m_ComboQueryPage.AddString(strPage);
	}
	m_ComboQueryPage.SetCurSel(m_iCurrentPage);

	m_ListQueryFile.DeleteAllItems();
	NVS_FILE_DATA_EX fileInfo = {0};
	fileInfo.iSize = sizeof(NVS_FILE_DATA_EX);
	for(int i=0; i<m_iCurrentCount; i++)
	{
		int iRet = NetClient_NetFileGetQueryfileEx(m_iLogonID, i, &fileInfo);
 		if(0 == iRet)
 		{
 			int iCellID = m_iCurrentPage*MAX_PAGESIZE + i+1;
 			if (iCellID <= m_iTotalCount)
 			{
				CString szID;
				szID.Format("%d", iCellID);
				m_ListQueryFile.InsertItem(i, "");

				if(m_ListQueryFile.GetCheck(i) != fileInfo.iLocked)
				{
					m_ListQueryFile.SetCheck(i,fileInfo.iLocked);
				}
				m_ListQueryFile.SetItem(i,0,LVIF_IMAGE,NULL,fileInfo.iLocked,0,0,0,0);
				
				int iColumn = 0;
				m_ListQueryFile.SetItemText(i, iColumn++, szID);
 				m_ListQueryFile.SetItemText(i, iColumn++, fileInfo.tFileData.cFileName);
				CString szType;
				szType.Format("%d", fileInfo.tFileData.iType);
				m_ListQueryFile.SetItemText(i, iColumn++, szType);
				CString szChannel;
				szChannel.Format("%d", fileInfo.tFileData.iChannel);
				m_ListQueryFile.SetItemText(i, iColumn++, szChannel);
				CString szFileSize;
				szFileSize.Format("%d", fileInfo.tFileData.iFileSize);
				m_ListQueryFile.SetItemText(i, iColumn++, szFileSize);
				CString szTime;
				szTime.Format("%d-%02d-%02d %02d:%02d:%02d", fileInfo.tFileData.struStartTime.iYear
					, fileInfo.tFileData.struStartTime.iMonth, fileInfo.tFileData.struStartTime.iDay
					, fileInfo.tFileData.struStartTime.iHour, fileInfo.tFileData.struStartTime.iMinute
					, fileInfo.tFileData.struStartTime.iSecond);
				m_ListQueryFile.SetItemText(i, iColumn++, szTime);
			
				szTime.Format("%d-%02d-%02d %02d:%02d:%02d", fileInfo.tFileData.struStoptime.iYear
					, fileInfo.tFileData.struStoptime.iMonth, fileInfo.tFileData.struStoptime.iDay
					, fileInfo.tFileData.struStoptime.iHour, fileInfo.tFileData.struStoptime.iMinute
					, fileInfo.tFileData.struStoptime.iSecond);
				m_ListQueryFile.SetItemText(i, iColumn++, szTime);
				unsigned long iConnID;
				if (IsFileInDownLoadList(m_iLogonID, fileInfo.tFileData.cFileName, &iConnID))
				{
					int iPos = 0, iSize = 0;
					NetClient_NetFileGetDownloadPos(iConnID, &iPos, &iSize);
					CString szProgress;
					szProgress.Format("%d", iPos);
					szProgress += "%/";
					CString szSize;
					szSize.Format("%dB", iSize);
					szProgress += szSize;
					m_ListQueryFile.SetItemText(i, iColumn++, szProgress);
				}
 			}
 		}
	}
}

void CLS_RemoteFilePage::Update_UI_IPAndID()
{
	PDEVICE_INFO DeviceInfo = FindDevice(m_iLogonID);
	if (DeviceInfo)
	{
		CString strDeviceIP = GetTextEx(IDS_PLAYBACK_DEVICE_IP) + ":" + DeviceInfo->cIP;
		CString strDeviceID = GetTextEx(IDS_PLAYBACK_DEVICE_ID) + ":" + DeviceInfo->cID;
		SetDlgItemText(IDC_STATIC_DEVICE_IP ,strDeviceIP);
		SetDlgItemText(IDC_STATIC_DEVICE_ID ,strDeviceID);
		int iChannelNum = 0;
		NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
		m_ComboChannelNo.ResetContent();
		for (int i = 0; i < iChannelNum; i++)
		{
			CString str;
			str.Format("%d", i);
			m_ComboChannelNo.SetItemData(m_ComboChannelNo.AddString(str), i);
		}
		m_ComboChannelNo.SetItemData(m_ComboChannelNo.AddString(GetTextEx(IDS_PLAYBACK_TYPE_ALL)), FLAG_QUERY_ALL_CHANNEL);
		m_ComboChannelNo.SetCurSel(0);

		int iAlarmChannelNo = 0,iAlarmOutPortNum = 0;
	int iRet = NetClient_GetAlarmPortNum(m_iLogonID, &iAlarmChannelNo, &iAlarmOutPortNum);
		m_cboAlarmPort.ResetContent();
		for (int i = 0; i < iAlarmChannelNo; i++)
		{
			CString szChannel;
			szChannel.Format("%d", i);
			m_cboAlarmPort.AddString(szChannel);
		}
		m_cboAlarmPort.SetCurSel(0);
	}
}

void CLS_RemoteFilePage::QueryFile()
{
	m_ListQueryFile.DeleteAllItems();
	NETFILE_QUERY_V5 tMultiChanQueryFile = {0};
	int iType = m_ComboRecType.GetCurSel();
	if (iType == 0)
	{
		tMultiChanQueryFile.iType = 0xFF;
	}
	else if (iType <= 3)
	{
		tMultiChanQueryFile.iType = iType;
	}
	else
	{
		tMultiChanQueryFile.iType = GetDlgItemInt(IDC_COMBO_REC_TYPE);
	}

	int iSelIndex = m_ComboChannelNo.GetCurSel();
	int iChannelNo = m_ComboChannelNo.GetItemData(iSelIndex); 
	tMultiChanQueryFile.iQueryChannelNo = iChannelNo;
	tMultiChanQueryFile.iStreamNo = m_cboStreamNo.GetItemData(m_cboStreamNo.GetCurSel());
	CTime tempTime;
	m_DTQueryBeginTime.GetTime(tempTime);
	tMultiChanQueryFile.tStartTime.iYear = tempTime.GetYear();
	tMultiChanQueryFile.tStartTime.iMonth = tempTime.GetMonth();
	tMultiChanQueryFile.tStartTime.iDay = tempTime.GetDay();
	tMultiChanQueryFile.tStartTime.iHour = tempTime.GetHour();
	tMultiChanQueryFile.tStartTime.iMinute = tempTime.GetMinute();
	tMultiChanQueryFile.tStartTime.iSecond = tempTime.GetSecond();

	m_DTQueryEndTime.GetTime(tempTime);
	tMultiChanQueryFile.tStopTime.iYear = tempTime.GetYear();
	tMultiChanQueryFile.tStopTime.iMonth = tempTime.GetMonth();
	tMultiChanQueryFile.tStopTime.iDay = tempTime.GetDay();
	tMultiChanQueryFile.tStopTime.iHour = tempTime.GetHour();
	tMultiChanQueryFile.tStopTime.iMinute = tempTime.GetMinute();
	tMultiChanQueryFile.tStopTime.iSecond = tempTime.GetSecond();

	tMultiChanQueryFile.iPageSize = MAX_PAGESIZE;
	tMultiChanQueryFile.iPageNo = m_iCurrentPage;
	tMultiChanQueryFile.iFiletype = m_ComboFileType.GetCurSel();
	GetDlgItemText(IDC_EDIT_OSD, tMultiChanQueryFile.cOtherQuery, sizeof(tMultiChanQueryFile.cOtherQuery));
	if (m_cboAlarmType.GetCurSel() == 0)
	{
		tMultiChanQueryFile.iTriggerType = 0x7FFFFFFF;
	}
	else
	{
		tMultiChanQueryFile.iTriggerType = m_cboAlarmType.GetCurSel() + 2;
	}
	tMultiChanQueryFile.iTrigger = m_cboAlarmPort.GetCurSel();

	if (BST_CHECKED == m_chkBatchQuery.GetCheck())
	{
		tMultiChanQueryFile.iQueryChannelCount = 2;
	}
	else
	{
		tMultiChanQueryFile.iQueryChannelCount = 1;
	}
	QueryFileChannel ch_list_tmp[2] = {0};
	ch_list_tmp[0].iChannelNo = iChannelNo;
	ch_list_tmp[0].iStreamNo = 0;
	ch_list_tmp[1].iChannelNo = iChannelNo;
	ch_list_tmp[1].iStreamNo = 1;
	tMultiChanQueryFile.ptChannelList = ch_list_tmp;
	tMultiChanQueryFile.iBufferSize = sizeof(QueryFileChannel);

	int iRet = NetClient_Query_V4(m_iLogonID, CMD_NETFILE_MULTI_CHANNEL_QUERY_FILE, 0, &tMultiChanQueryFile, sizeof(tMultiChanQueryFile));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileQueryEx(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileQueryEx(%d)", m_iLogonID);
	}
}

void CLS_RemoteFilePage::ResetQuery()
{
	m_ComboQueryPage.ResetContent();
    m_iCurrentPage = 0;
	m_szFileName = "";
}
void CLS_RemoteFilePage::OnCbnSelchangeComboChannel()
{
	int iShowStream = SW_SHOW;
	if (0 >= m_ComboChannelNo.GetCurSel())
	{
		iShowStream = SW_HIDE;
	}

	m_cboStreamNo.ShowWindow(iShowStream);
	GetDlgItem(IDC_STC_STREAM)->ShowWindow(iShowStream);
}

void CLS_RemoteFilePage::OnCbnSelchangeComboFileType()
{

}

void CLS_RemoteFilePage::OnCbnSelchangeComboRecType()
{

}

void CLS_RemoteFilePage::OnCbnSelchangeComboQueryPage()
{
	// TODO: Add your control notification handler code here
	m_iCurrentPage = m_ComboQueryPage.GetCurSel();
	QueryFile();
}

void CLS_RemoteFilePage::OnBnClickedButtonPrepage()
{
	// TODO: Add your control notification handler code here
	if (m_iCurrentPage > 0)
	{
		m_iCurrentPage--;
		QueryFile();
	}
}

void CLS_RemoteFilePage::OnBnClickedButtonNextPage()
{
	// TODO: Add your control notification handler code here
	if (m_iCurrentPage < m_iTotalPage -1)
	{
		m_iCurrentPage++;
		QueryFile();
	}
}

void CLS_RemoteFilePage::OnBnClickedButtonFirstPage()
{
	// TODO: Add your control notification handler code here
	m_iCurrentPage = 0;
	QueryFile();
}

void CLS_RemoteFilePage::OnBnClickedButtonLastPage()
{
	// TODO: Add your control notification handler code here
	if (m_iTotalPage > 0)
	{
		m_iCurrentPage = m_iTotalPage - 1;
		QueryFile();
	}
}

void CLS_RemoteFilePage::OnDtnDatetimechangeDatetimepickerQueryBegintime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	*pResult = 0;
}

void CLS_RemoteFilePage::OnDtnDatetimechangeDatetimepickerQueryEndtime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	*pResult = 0;
}

void CLS_RemoteFilePage::OnLanguageChanged( int )
{
	Update_UI_Text();
	if (m_iLogonID >= 0)
	{
		m_iCurrentPage = 0;
		QueryFile();
	}
	UpdateMoonInfo();
	Update_UI_IPAndID();
}

void CLS_RemoteFilePage::OnNMClickListQueryFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	int nItem = pNMItemActivate->iItem;
	m_szFileName = m_ListQueryFile.GetItemText(nItem, 1);
}

void CLS_RemoteFilePage::OnBnClickedButtonDownload()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0 || m_szFileName == "")
	{
		return;
	}

	unsigned long iConnID = INVALID_ID;
	if (IsFileInDownLoadList(m_iLogonID, m_szFileName, &iConnID))
	{
		return;
	}
	CString cstrLocalFileName = g_szDownloadPath + m_szFileName;
	DOWNLOAD_FILE tDownloadFileInfo = {sizeof(DOWNLOAD_FILE)};
	tDownloadFileInfo.m_iSaveFileType = m_cboDownloadFileType.GetItemData(m_cboDownloadFileType.GetCurSel());
	if (DOWNLOAD_FILE_TYPE_MP4 == tDownloadFileInfo.m_iSaveFileType)
	{
		PathRenameExtension(cstrLocalFileName.GetBuffer(),  _T(".mp4"));
		cstrLocalFileName.ReleaseBuffer();
	}
	if (DOWNLOAD_FILE_TYPE_PS == tDownloadFileInfo.m_iSaveFileType)
	{
		PathRenameExtension(cstrLocalFileName.GetBuffer(),  _T(".ps"));
		cstrLocalFileName.ReleaseBuffer();
	}

	strcpy_s(tDownloadFileInfo.m_cRemoteFilename,m_szFileName.GetLength()+1,(char *)(LPCSTR)m_szFileName);
	strcpy_s(tDownloadFileInfo.m_cLocalFilename, cstrLocalFileName.GetLength() + 1,cstrLocalFileName.GetBuffer());
	cstrLocalFileName.ReleaseBuffer();
	tDownloadFileInfo.m_iPosition = -1;
	tDownloadFileInfo.m_iSpeed = 32;
	tDownloadFileInfo.m_iReqMode = m_cboReqMode.GetCurSel();
	
	int iRet = NetClient_NetFileDownload((unsigned int*)&iConnID, m_iLogonID, DOWNLOAD_CMD_FILE,&tDownloadFileInfo,sizeof(DOWNLOAD_FILE));
	if (iRet >= 0)
	{
		//int iRet = NetClient_NetFileDownloadFile(&iConnID, m_iLogonID, (char *)(LPCSTR)m_szFileName, (char *)(LPCSTR)(g_szDownloadPath + m_szFileName), 1, -1, 16);//设置下载速度为32倍速
		DOWNLOAD_CONTROL tdc = {sizeof(DOWNLOAD_CONTROL)};
		tdc.m_iPosition = -1;
		tdc.m_iSpeed = 16;
		tdc.m_iReqMode = m_cboReqMode.GetCurSel();
		int iRet = NetClient_NetFileDownload((unsigned int*)&iConnID, m_iLogonID, DOWNLOAD_CMD_CONTROL,&tdc,sizeof(DOWNLOAD_CONTROL));
		CLS_DownloadFile *downloadfile = new CLS_DownloadFile(m_iLogonID, iConnID, m_szFileName);
		downloadfile->SetBreakContinue(IsDlgButtonChecked(IDC_CHECK_BREAK_CONTINUE));
		downloadfile->SetReqMode(m_cboReqMode.GetCurSel());
		m_lstDownloadFile.push_back(downloadfile);

		//标准数据（PS）回调
		if (DOWNLOAD_FILE_TYPE_PS == tDownloadFileInfo.m_iSaveFileType && NULL != NetClient_SetDataPackCallBack)
		{
			//若果不需要写文件的，只需要回调，可以将本地文件名称传空
			NetClient_SetDataPackCallBack(iConnID, DTYPE_PS, (void*)&_PsDataCallBackFunction, NULL);
		}
	}
}

void CLS_RemoteFilePage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case TIMER_QUERY_DOWNLOAD_PROGRESS:
		return QueryDownloadProgress();

	}
	//CLS_BasePage::OnTimer(nIDEvent);
}

void CLS_RemoteFilePage::QueryDownloadProgress()
{
	if (m_iLogonID < 0)
	{
		return;
	}
	for (int i = 0; i < MAX_PAGESIZE; i++)
	{
		CString szFileName = m_ListQueryFile.GetItemText(i, 1);
		if (szFileName == "")
		{
			return;
		}
 	 	unsigned long iConnID;
		CLS_DownloadFile* pFile;
 	 	if (IsFileInDownLoadList(m_iLogonID, szFileName, &iConnID,&pFile))
 	 	{
 	 		int iPos = 0, iSize = 0;
 	 		NetClient_NetFileGetDownloadPos(iConnID, &iPos, &iSize);
			CString szProgress;
			szProgress.Format("%d", iPos);
			szProgress += "%/";
			CString szSize;
			szSize.Format("%dB", iSize);
			szProgress += szSize;
 	 		m_ListQueryFile.SetItemText(i, 7, szProgress);
			if (NULL != pFile && iSize > 0)
			{
				pFile->SetPosition(iSize);
			}
 	 	}
		else
		{
			CString szProgress;
			m_ListQueryFile.SetItemText(i, 7, szProgress);
		}
	}
	
}

BOOL CLS_RemoteFilePage::IsFileInDownLoadList( int _iLogonID, CString _szFileName , unsigned long * _iConnID, CLS_DownloadFile** _pFile)
{
	BOOL bIn = FALSE; 
	for (list <CLS_DownloadFile *>::iterator it = m_lstDownloadFile.begin(); it != m_lstDownloadFile.end(); it++)
	{
		CLS_DownloadFile * downloadFile = *it;
		if (downloadFile->GetFilename() == _szFileName && downloadFile->GetLogonID() == _iLogonID)
		{
			bIn = TRUE;
			*_iConnID = downloadFile->GetConnID();
			if (_pFile)
			{
				*_pFile = downloadFile;
			}
			break;
		}
	}
	return bIn;
}

BOOL CLS_RemoteFilePage::IsFileInPlayBackList(int _iLogonID, CString _szFileName, int* _piCurrentDevPlayPageNum)
{
	BOOL blFind = FALSE; 
	int iCurDevPlayPageNum = 0;
	for (list <CLS_FilePlayReviewPage *>::iterator it = m_lstPlayPage.begin(); it != m_lstPlayPage.end(); it++)
	{
		CLS_FilePlayReviewPage * pclsPlayPage = *it;
		if (NULL == pclsPlayPage || NULL == pclsPlayPage->GetSafeHwnd() || !IsWindow(pclsPlayPage->GetSafeHwnd()))
		{
			continue;
		}

		if (pclsPlayPage->GetLogonID() != _iLogonID)
		{
			continue;
		}

		//同一个设备同时播放的路数不能超过5路
		iCurDevPlayPageNum++;

		if (pclsPlayPage->GetFilename() == _szFileName)
		{
			blFind = TRUE;
			break;
		}
	}

	if (NULL != _piCurrentDevPlayPageNum)
	{
		*_piCurrentDevPlayPageNum = iCurDevPlayPageNum;
	}
	return blFind;
}

void CLS_RemoteFilePage::OnDestroy()
{
	CLS_BasePage::OnDestroy();
	KillTimer(TIMER_QUERY_DOWNLOAD_PROGRESS);
	while(!m_lstDownloadFile.empty())
	{
		CLS_DownloadFile * downloadfile = m_lstDownloadFile.front();
		m_lstDownloadFile.pop_front();
		delete downloadfile;
	}

	while(!m_lstPlayPage.empty())
	{
		CLS_FilePlayReviewPage * pclsPlayer = m_lstPlayPage.front();
		m_lstPlayPage.pop_front();

		if (IsWindow(pclsPlayer->GetSafeHwnd()))
		{
			pclsPlayer->DestroyWindow();
		}
		delete pclsPlayer;
		pclsPlayer = NULL;
	}
	// TODO: Add your message handler code here
}

LRESULT CLS_RemoteFilePage::OnPlayPageDestory( WPARAM wParam, LPARAM lParam )
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

void CLS_RemoteFilePage::DeleteDownload( unsigned long  _ulConnID )
{
	for (list <CLS_DownloadFile *>::iterator it = m_lstDownloadFile.begin(); it != m_lstDownloadFile.end(); it++)
	{
		CLS_DownloadFile * downloadFile = *it;
		if ( downloadFile->GetConnID() == _ulConnID)
		{
			m_lstDownloadFile.erase(it);
			delete downloadFile;
			break;
		}
	}
}

void CLS_RemoteFilePage::DeleteDownload( const int _iLogonID , int _iFlag)
{
	int iDelete = 0;
	do
	{
		iDelete = 0;
		for (list <CLS_DownloadFile *>::iterator it = m_lstDownloadFile.begin(); it != m_lstDownloadFile.end(); it++)
		{
			CLS_DownloadFile * downloadFile = *it;
			if ( downloadFile->GetLogonID() == _iLogonID)
			{
				if (1 == _iFlag && 1 == downloadFile->GetBreakContinue())
				{
					continue;
				}
				m_lstDownloadFile.erase(it);
				delete downloadFile;
				iDelete = 1;
				break;
			}
		}
	}while(iDelete);
}

void CLS_RemoteFilePage::ProcessDownloadFinished( unsigned long _ulID )
{
	OpenFile(_ulID);
	DeleteDownload(_ulID);
}

void CLS_RemoteFilePage::ProcessErrorOrder( const int _iLogonID )
{
	DeleteDownload(_iLogonID, 1/*0*/);
}

void CLS_RemoteFilePage::ProcessDownloadFault( unsigned long _ulID )
{
	DeleteDownload(_ulID);
}

void CLS_RemoteFilePage::ProcessDownloadInterrupt( unsigned long _ulID )
{
	DeleteDownload(_ulID,1);
}


void CLS_RemoteFilePage::OnBnClickedButtonQuery()
{
	m_ListQueryFile.DeleteAllItems();
	m_iCurrentPage =0;
	QueryFile();
}

void CLS_RemoteFilePage::OnBnClickedButtonStopDownload()
{
	// TODO: Add your control notification handler code here
	unsigned long iConnID = INVALID_ID;
	if (IsFileInDownLoadList(m_iLogonID, m_szFileName, &iConnID))
	{
		DeleteDownload(iConnID);
	}
}

void CLS_RemoteFilePage::OnBnClickedButtonPauseDownload()
{
	// TODO: Add your control notification handler code here
	unsigned long iConnID = INVALID_ID;
	if (IsFileInDownLoadList(m_iLogonID, m_szFileName, &iConnID))
	{
		//NetClient_NetFileDownloadFile(&iConnID, m_iLogonID, "", "", 1, -1, 0);
		DOWNLOAD_CONTROL tdc = {sizeof(DOWNLOAD_CONTROL)};
		tdc.m_iPosition = -1;
		tdc.m_iSpeed = 0;
		tdc.m_iReqMode = m_cboReqMode.GetCurSel();
		int iRet = NetClient_NetFileDownload((unsigned int*)&iConnID, m_iLogonID, DOWNLOAD_CMD_CONTROL,&tdc,sizeof(DOWNLOAD_CONTROL));
	}
}

void CLS_RemoteFilePage::OnBnClickedButtonContinueDownload()
{
	// TODO: Add your control notification handler code here
	unsigned long iConnID = INVALID_ID;
	if (IsFileInDownLoadList(m_iLogonID, m_szFileName, &iConnID))
	{
		//NetClient_NetFileDownloadFile(&iConnID, m_iLogonID, "", "", 1, -1, 16);
		DOWNLOAD_CONTROL tdc = {sizeof(DOWNLOAD_CONTROL)};
		tdc.m_iPosition = -1;
		tdc.m_iSpeed = 16;
		tdc.m_iReqMode = m_cboReqMode.GetCurSel();
		NetClient_NetFileDownload((unsigned int*)&iConnID, m_iLogonID, DOWNLOAD_CMD_CONTROL,&tdc,sizeof(DOWNLOAD_CONTROL));
	}
}

CString CLS_RemoteFilePage::GetFileNameByConID( unsigned long _ulConnID )
{
	for (list <CLS_DownloadFile *>::iterator it = m_lstDownloadFile.begin(); it != m_lstDownloadFile.end(); it++)
	{
		CLS_DownloadFile * downloadFile = *it;
		if ( downloadFile->GetConnID() == _ulConnID)
		{
			return g_szDownloadPath + ((CLS_DownloadFile *)*it)->GetFilename();
		}
	}
	return "";
}

void CLS_RemoteFilePage::OpenFile( unsigned long _ulConnID )
{
	CString szFile = GetFileNameByConID(_ulConnID);
	CString strResult;
	if (szFile.GetLength()	>=	4)
	{
		CString strExt	=	szFile.Right(4).MakeLower();
		if(strExt	==	".bmp"	||	strExt	==	".jpg")
		{
			CString	strKey	=	"jpegfile\\shell\\open\\command";
			HKEY  	hTempKey   = (HKEY)0;
			RegOpenKeyEx(HKEY_CLASSES_ROOT, strKey,	0,	KEY_READ,	&hTempKey);
			DWORD	dwType	=	0;
			CString	strFullPath;
			DWORD	dwBufferLength	=	256;
			TCHAR	taTmp[MAX_PATH*2];
			memset(taTmp,	0,	MAX_PATH*2*sizeof(TCHAR));
			LONG	ret	=	RegQueryValueEx(hTempKey,	_T(""),	NULL,	&dwType,	(LPBYTE)taTmp,	&dwBufferLength);
			RegCloseKey(hTempKey);

			CString	strCmd	=	taTmp;
			INT	iPos	=	strCmd.ReverseFind(_T(' '));
			strCmd.Delete(iPos+1,	strCmd.GetLength()-iPos-1);

			GetWindowsDirectory(taTmp,	MAX_PATH*2);
			strCmd.Replace(_T("%SystemRoot%"),	taTmp);
			CString	strDir(taTmp);
			iPos	=	strDir.ReverseFind(_T('\\'));
			strDir.Delete(iPos+1,	strDir.GetLength()-iPos-1);
			strDir.Append(_T("Program Files"));
			strCmd.Replace(_T("%ProgramFiles%"),	strDir);
			strCmd	+=	szFile;

			memcpy(taTmp,	strCmd.GetBuffer(),	strCmd.GetLength()+2);
			//////////////////////////////////////////////////////////////////////////
			STARTUPINFO si;
			PROCESS_INFORMATION pi;

			ZeroMemory( &si, sizeof(si) );
			si.cb = sizeof(si);
			ZeroMemory( &pi, sizeof(pi) );

			// Start the child process. 
			if( !CreateProcess( NULL,   // No module name (use command line)
				taTmp,        // Command line
				NULL,           // Process handle not inheritable
				NULL,           // Thread handle not inheritable
				FALSE,          // Set handle inheritance to FALSE
				0,              // No creation flags
				NULL,           // Use parent's environment block
				NULL,           // Use parent's starting directory 
				&si,            // Pointer to STARTUPINFO structure
				&pi )           // Pointer to PROCESS_INFORMATION structure
				) 
			{
				strResult.Format("%d",	GetLastError());
			}
			else
			{
				CloseHandle( pi.hProcess );
				CloseHandle( pi.hThread );						
			}
		}
	}	
}

void CLS_RemoteFilePage::OnLogoffDevice( int _iLogonID )
{
	DeleteDownload(_iLogonID, 0);
}


void CLS_RemoteFilePage::OnLvnItemchangedListQueryFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int iOldState = ((pNMLV->uOldState >> 12) & 3);
	int iNewState = ((pNMLV->uNewState >> 12) & 3);
	if (iOldState && iNewState)
	{
		int iLButtonDown = (GetKeyState(VK_LBUTTON) >> 15) & 0x0001;
		if (iLButtonDown)
		{
			CString strFileName = m_ListQueryFile.GetItemText(pNMLV->iItem,1);
			if (0 == strFileName.Right(4).Compare(_T(".sdv")))
			{
				int iRet = NetClient_NetFileLockFile(m_iLogonID,(LPSTR)(LPCTSTR)strFileName,iNewState-1);
				if (0 != iRet)
				{
					AddLog(LOG_TYPE_FAIL,"","NetFileLockFile failed! LogonID(%d),FileName(%s),Locked(%d)"
						,m_iLogonID,(LPSTR)(LPCTSTR)strFileName,iNewState-1);
				}
			}
			else
			{
				AddLog(LOG_TYPE_MSG,"","Not record file! LogonID(%d),FileName(%s)"
					,m_iLogonID,(LPSTR)(LPCTSTR)strFileName);
			}
		}
	}
	*pResult = 0;
}

void CLS_RemoteFilePage::OnNetFileLockFiles( WPARAM wParam, LPARAM lParam )
{
	NVS_IPAndID* pIPID = (NVS_IPAndID*)lParam;
	if (pIPID && pIPID->m_piLogonID)
	{
		int iLogonID = *pIPID->m_piLogonID;
		if (iLogonID != m_iLogonID)
		{
			return;
		}

		int iIndex = (int)wParam >> 16;
		NVS_FILE_DATA_EX tFileDataEx = {0};
		tFileDataEx.iSize = sizeof(NVS_FILE_DATA_EX);
		if(NetClient_NetFileGetQueryfileEx(iLogonID, iIndex, &tFileDataEx) == 0)
		{
			for(int i = 0; i < m_ListQueryFile.GetItemCount(); ++i)
			{
				if (0 == m_ListQueryFile.GetItemText(i,1).Compare(tFileDataEx.tFileData.cFileName))
				{
					if(m_ListQueryFile.GetCheck(iIndex) != tFileDataEx.iLocked)
					{
						m_ListQueryFile.SetCheck(i,tFileDataEx.iLocked);
					}
					m_ListQueryFile.SetItem(i,0,LVIF_IMAGE,NULL,tFileDataEx.iLocked,0,0,0,0);
					break;
				}
			}
		}
	}
}

void CLS_RemoteFilePage::OnBnClickedBtnPlaybackMoonRefresh()
{
	// TODO: Add your control notification handler code here
	//m_lstMoonInfoList.DeleteAllItems();
	RefreshMoonInfo();
}

void CLS_RemoteFilePage::OnBnClickedButtonBreakNetContinue()
{
	if (m_iLogonID < 0 || m_szFileName == "")
	{
		return;
	}

	unsigned long iConnID = INVALID_ID;
	if (IsFileInDownLoadList(m_iLogonID, m_szFileName, &iConnID))
	{
		return;
	}
	CString cstrLocalFileName = g_szDownloadPath + m_szFileName;

	__int64 iOffset = 0;
	FILE* pFile = fopen(cstrLocalFileName, "r+b");
	if (NULL == pFile)
	{
		return;
	}
	_fseeki64(pFile, 0, SEEK_END);
	iOffset = _ftelli64(pFile);
	fclose(pFile);

	DOWNLOAD_FILE tFileInfo = {sizeof(DOWNLOAD_FILE)};
	tFileInfo.m_iSaveFileType = m_cboDownloadFileType.GetItemData(m_cboDownloadFileType.GetCurSel());
	strcpy_s(tFileInfo.m_cRemoteFilename, m_szFileName.GetLength() + 1, (char *)(LPCSTR)m_szFileName);
	strcpy_s(tFileInfo.m_cLocalFilename, cstrLocalFileName.GetLength() + 1, cstrLocalFileName.GetBuffer());
	cstrLocalFileName.ReleaseBuffer();
	tFileInfo.m_iPosition = (int)iOffset;
	tFileInfo.m_iSpeed = 16;
	tFileInfo.m_iReqMode = m_cboReqMode.GetCurSel();
	int iRet = NetClient_NetFileDownload((unsigned int*)&iConnID, m_iLogonID, DOWNLOAD_CMD_FILE_CONTINUE, &tFileInfo, sizeof(DOWNLOAD_FILE));
	if (iRet >= 0)
	{
		CLS_DownloadFile *downloadfile = new CLS_DownloadFile(m_iLogonID, iConnID, m_szFileName);
		downloadfile->SetBreakContinue(IsDlgButtonChecked(IDC_CHECK_BREAK_CONTINUE));
		downloadfile->SetReqMode(m_cboReqMode.GetCurSel());
		m_lstDownloadFile.push_back(downloadfile);
	}
}
