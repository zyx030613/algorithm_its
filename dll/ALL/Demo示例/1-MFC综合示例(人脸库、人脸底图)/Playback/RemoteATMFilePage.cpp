// RemoteATMFilePage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "RemoteATMFilePage.h"


// CLS_RemoteATMFilePage dialog

IMPLEMENT_DYNAMIC(CLS_RemoteATMFilePage, CDialog)
extern CString g_szDownloadPath ;
CLS_RemoteATMFilePage::CLS_RemoteATMFilePage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_RemoteATMFilePage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNo = 0;

	m_iTotalCount = 0;
	m_iCurrentCount = 0;
	m_iCurrentPage = 0;
	m_iTotalPage = 0;
	m_iATMQuery = 0;
}

CLS_RemoteATMFilePage::~CLS_RemoteATMFilePage()
{
}

void CLS_RemoteATMFilePage::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_COMBO_QUERY_ATM_TYPE, m_CBQueryATMType);
	DDX_Control(pDX, IDC_COMBO2, m_CBBusinessType);
	DDX_Control(pDX, IDC_COMBO3, m_CBExceptions);
}


BEGIN_MESSAGE_MAP(CLS_RemoteATMFilePage, CLS_BasePage)


	ON_BN_CLICKED(IDC_BUTTON_PLAYBACK, &CLS_RemoteATMFilePage::OnBnClickedButtonPlayback)
	ON_CBN_SELCHANGE(IDC_COMBO_Channel, &CLS_RemoteATMFilePage::OnCbnSelchangeComboChannel)
	ON_CBN_SELCHANGE(IDC_COMBO_FILE_TYPE, &CLS_RemoteATMFilePage::OnCbnSelchangeComboFileType)
	ON_CBN_SELCHANGE(IDC_COMBO_REC_TYPE, &CLS_RemoteATMFilePage::OnCbnSelchangeComboRecType)
	ON_CBN_SELCHANGE(IDC_COMBO_QUERY_PAGE, &CLS_RemoteATMFilePage::OnCbnSelchangeComboQueryPage)
	ON_BN_CLICKED(IDC_BUTTON_PREPAGE, &CLS_RemoteATMFilePage::OnBnClickedButtonPrepage)
	ON_BN_CLICKED(IDC_BUTTON_NEXT_PAGE, &CLS_RemoteATMFilePage::OnBnClickedButtonNextPage)
	ON_BN_CLICKED(IDC_BUTTON_FIRST_PAGE, &CLS_RemoteATMFilePage::OnBnClickedButtonFirstPage)
	ON_BN_CLICKED(IDC_BUTTON_LAST_PAGE, &CLS_RemoteATMFilePage::OnBnClickedButtonLastPage)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_QUERY_BEGINTIME, &CLS_RemoteATMFilePage::OnDtnDatetimechangeDatetimepickerQueryBegintime)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_QUERY_ENDTIME, &CLS_RemoteATMFilePage::OnDtnDatetimechangeDatetimepickerQueryEndtime)
	ON_NOTIFY(NM_CLICK, IDC_LIST_QUERY_FILE, &CLS_RemoteATMFilePage::OnNMClickListQueryFile)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, &CLS_RemoteATMFilePage::OnBnClickedButtonDownload)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_QUERY_ATM_TYPE, &CLS_RemoteATMFilePage::OnCbnSelchangeComboQueryAtmType)
	ON_BN_CLICKED(IDC_BUTTON_ATM_QUERY, &CLS_RemoteATMFilePage::OnBnClickedButtonAtmQuery)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CLS_RemoteATMFilePage::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_CONTINUE, &CLS_RemoteATMFilePage::OnBnClickedButtonContinue)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CLS_RemoteATMFilePage::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CLS_RemoteFilePage message handlers

BOOL CLS_RemoteATMFilePage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_DTQueryBeginTime.SetFormat("yyyy-MM-dd HH:mm:ss");
	m_DTQueryEndTime.SetFormat("yyyy-MM-dd HH:mm:ss");

	CTime SystemTime; 
	m_DTQueryBeginTime.GetTime(SystemTime);
	CTime BeginTime(SystemTime.GetYear(), SystemTime.GetMonth(), SystemTime.GetDay(), 0, 0, 0);
	m_DTQueryBeginTime.SetTime(&BeginTime);
	m_ListQueryFile.SetExtendedStyle(m_ListQueryFile.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	
	Update_UI_Text();
	SetTimer(TIMER_QUERY_DOWNLOAD_PROGRESS, 1000, NULL);
	CreateDirectory(g_szDownloadPath, NULL);
	m_ListQueryFile.DeleteAllItems();
	m_CBExceptions.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CLS_RemoteATMFilePage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (_iLogonID < 0)
	{
		return;
	}
	m_iLogonID = _iLogonID;
	Update_UI_IPAndID();
	ResetQuery();
	QueryFile();
}

void CLS_RemoteATMFilePage::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser )
{
	if (m_iLogonID < 0)
	{
		return;
	}

	int iMsgType = LOWORD(_iWparam);
	switch(iMsgType)
	{
	case WCM_QUERY_ATMFILE_FINISHED:
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
				Update_UI_Query_ATM_Result();
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
		ProcessDownloadInterrupt((unsigned long)_iLParam);
		break;


	}
	m_PlayPage.OnMainNotify(_ulLogonID, _iWparam, _iLParam, _iUser);
}

void CLS_RemoteATMFilePage::OnBnClickedButtonPlayback()
{
	// TODO: Add your control notification handler code here
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

// 	unsigned long iConnID = -1;
// 	if (IsFileInList(m_iLogonID, m_szFileName,&iConnID))
// 	{
// 		return;
// 	}
	int iChannelNo = 0;
	sscanf_s(m_szChannelNo, "%d", &iChannelNo);
	NVS_FILE_TIME struOperateTime = {0};
	int iYear = 0, iMonth = 0, iDay = 0, iHour = 0, iMinute = 0,iSecond = 0;
	sscanf_s(m_szOperationTime, "%d-%d-%d %d:%d:%d", &iYear, &iMonth, &iDay, &iHour, &iMinute, &iSecond);
	struOperateTime.iYear   = iYear;
	struOperateTime.iMonth  = iMonth;
	struOperateTime.iDay    = iDay;
	struOperateTime.iHour   = iHour;
	struOperateTime.iMinute = iMinute;
	struOperateTime.iSecond = iSecond;
	NVS_FILE_TIME struStoptime = {0};
	sscanf_s(m_szEndTime, "%d-%d-%d %d:%d:%d", &iYear, &iMonth, &iDay, &iHour, &iMinute, &iSecond);
	struStoptime.iYear	 = iYear;
	struStoptime.iMonth	 = iMonth;
	struStoptime.iDay	 = iDay;
	struStoptime.iHour	 = iHour;
	struStoptime.iMinute = iMinute;
	struStoptime.iSecond = iSecond;
	m_PlayPage.SetDownloadParam(m_iLogonID, iChannelNo, &struOperateTime, &struStoptime);
	m_PlayPage.DoModal();
}

void CLS_RemoteATMFilePage::Update_UI_Text()
{
	SetDlgItemTextEx(IDC_STATIC_PLAYBACK_QUERY_CONDITION, IDS_PLAYBACK_QUERY_CONDITION);

	m_ComboFileType.ResetContent();
	m_ComboFileType.AddString(GetTextEx(IDS_PLAYBACK_TYPE_ALL));
	m_ComboFileType.AddString(GetTextEx(IDS_PLAYBACK_FILE_TYPE_VIDEO));
	m_ComboFileType.AddString(GetTextEx(IDS_PLAYBACK_FILE_TYPE_PICTURE));
	m_ComboFileType.SetCurSel(0);

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
	SetDlgItemTextEx(IDC_BUTTON_PREPAGE, IDS_PLAYBACK_PREPAGE);
	SetDlgItemTextEx(IDC_BUTTON_NEXT_PAGE, IDS_PLAYBACK_NEXT_PAGE);
	SetDlgItemTextEx(IDC_BUTTON_FIRST_PAGE, IDS_PLAYBACK_FIRST_PAGE);
	SetDlgItemTextEx(IDC_BUTTON_LAST_PAGE, IDS_PLAYBACK_LAST_PAGE);
	SetDlgItemTextEx(IDC_STATIC_QUERY_PAGE, IDS_PLAYBACK_QUERY_PAGE);	
	SetDlgItemTextEx(IDC_BUTTON_STOP, IDS_PLAYBACK_STOP);
	SetDlgItemTextEx(IDC_BUTTON_PAUSE, IDS_PLAYBACK_PAUSE);
	SetDlgItemTextEx(IDC_BUTTON_CONTINUE, IDS_PLAYBACK_CONTINUE);

	int iColumnIndex = 0;
	InsertColumn( m_ListQueryFile, iColumnIndex++, "ID", LVCFMT_LEFT, 50 );//插入列
	InsertColumn( m_ListQueryFile, iColumnIndex++, IDS_PLAYBACK_FILE_NAME, LVCFMT_LEFT, 180 );
	InsertColumn( m_ListQueryFile, iColumnIndex++, IDS_PLAYBACK_REC_TYPE, LVCFMT_LEFT, 80 );
	InsertColumn( m_ListQueryFile, iColumnIndex++, IDS_PLAYBACK_CHANNEL, LVCFMT_LEFT, 80 );
	InsertColumn( m_ListQueryFile, iColumnIndex++, IDS_PLAYBACK_FILE_SIZE, LVCFMT_LEFT, 80 );
// 	InsertColumn( m_ListQueryFile, iColumnIndex++, IDS_PLAYBACK_DOWNLOAD_BEGINTIME, LVCFMT_LEFT, 80 );
// 	InsertColumn( m_ListQueryFile, iColumnIndex++, IDS_PLAYBACK_DOWNLOAD_ENDTIME, LVCFMT_LEFT, 80 );
	InsertColumn( m_ListQueryFile, iColumnIndex++, IDS_PLAYBACK_ATM_OPERATION, LVCFMT_LEFT, 80 );
	InsertColumn( m_ListQueryFile, iColumnIndex++, IDS_PLAYBACK_ATM_OPERATE_TIME, LVCFMT_LEFT, 80 );
	InsertColumn( m_ListQueryFile, iColumnIndex++, IDS_PLAYBACK_DOWNLOAD_ENDTIME, LVCFMT_LEFT, 80 );
	InsertColumn( m_ListQueryFile, iColumnIndex++, IDS_PLAYBACK_DOWNLOAD_PROGRESS, LVCFMT_LEFT, 120 );
	UpDate_UI_ATM();
}

void CLS_RemoteATMFilePage::Update_UI_IPAndID()
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
		m_ComboChannelNo.AddString(GetTextEx(IDS_PLAYBACK_TYPE_ALL));
		for (int i = 0; i < iChannelNum; i++)
		{
			CString str;
			str.Format("%d", i);
			m_ComboChannelNo.AddString(str);
		}
		m_ComboChannelNo.SetCurSel(0);
	}
}

void CLS_RemoteATMFilePage::QueryFile()
{
	m_ListQueryFile.DeleteAllItems();
	QueryATMFile();
}

void CLS_RemoteATMFilePage::ResetQuery()
{
	m_ComboQueryPage.ResetContent();
	m_iCurrentPage = 0;
	m_szFileName = "";
}
void CLS_RemoteATMFilePage::OnCbnSelchangeComboChannel()
{
	// TODO: Add your control notification handler code here
	m_iCurrentPage =0;
	QueryFile();
}

void CLS_RemoteATMFilePage::OnCbnSelchangeComboFileType()
{
	// TODO: Add your control notification handler code here
	m_iCurrentPage =0;
	QueryFile();
}

void CLS_RemoteATMFilePage::OnCbnSelchangeComboRecType()
{
	// TODO: Add your control notification handler code here
	m_iCurrentPage =0;
	QueryFile();
}

void CLS_RemoteATMFilePage::OnCbnSelchangeComboQueryPage()
{
	// TODO: Add your control notification handler code here
	m_iCurrentPage = m_ComboQueryPage.GetCurSel();
	QueryFile();
}

void CLS_RemoteATMFilePage::OnBnClickedButtonPrepage()
{
	// TODO: Add your control notification handler code here
	if (m_iCurrentPage > 0)
	{
		m_iCurrentPage--;
		QueryFile();
	}
}

void CLS_RemoteATMFilePage::OnBnClickedButtonNextPage()
{
	// TODO: Add your control notification handler code here
	if (m_iCurrentPage < m_iTotalPage -1)
	{
		m_iCurrentPage++;
		QueryFile();
	}
}

void CLS_RemoteATMFilePage::OnBnClickedButtonFirstPage()
{
	// TODO: Add your control notification handler code here
	m_iCurrentPage = 0;
	QueryFile();
}

void CLS_RemoteATMFilePage::OnBnClickedButtonLastPage()
{
	// TODO: Add your control notification handler code here
	if (m_iTotalPage > 0)
	{
		m_iCurrentPage = m_iTotalPage - 1;
		QueryFile();
	}
}

void CLS_RemoteATMFilePage::OnDtnDatetimechangeDatetimepickerQueryBegintime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	m_iCurrentPage = 0;
	QueryFile();
}

void CLS_RemoteATMFilePage::OnDtnDatetimechangeDatetimepickerQueryEndtime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	m_iCurrentPage = 0;
	QueryFile();
}

void CLS_RemoteATMFilePage::OnLanguageChanged( int )
{
	Update_UI_Text();
	if (m_iLogonID >= 0)
	{
		m_iCurrentPage = 0;
		QueryFile();
	}
}

void CLS_RemoteATMFilePage::OnNMClickListQueryFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	int nItem = pNMItemActivate->iItem;
	m_szFileName = m_ListQueryFile.GetItemText(nItem, 1);
	m_szOperationTime = m_ListQueryFile.GetItemText(nItem, 6);
	m_szOperate = m_ListQueryFile.GetItemText(nItem, 5);
	m_szChannelNo = m_ListQueryFile.GetItemText(nItem, 3);
	m_szEndTime = m_ListQueryFile.GetItemText(nItem, 7);
}

void CLS_RemoteATMFilePage::OnBnClickedButtonDownload()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0 || m_szFileName == "")
	{
		return;
	}

	unsigned long iConnID = INVALID_ID;
	if (IsFileInList(m_iLogonID, m_szFileName,&iConnID))
	{
		return;
	}
	int iRet = NetClient_NetFileDownloadFile(&iConnID, m_iLogonID, (char *)(LPCSTR)m_szFileName, (char *)(LPCSTR)(g_szDownloadPath + m_szFileName), 0, -1, 32);
	if (iRet >= 0)
	{
		int iRet = NetClient_NetFileDownloadFile(&iConnID, m_iLogonID, (char *)(LPCSTR)m_szFileName, (char *)(LPCSTR)(g_szDownloadPath + m_szFileName), 1, -1, 32);//设置下载速度为32倍速
		CLS_DownloadFile *downloadfile = new CLS_DownloadFile(m_iLogonID, iConnID, m_szFileName,m_szOperationTime,m_szOperate);
		m_lstDownloadFile.push_back(downloadfile);
	}
}

void CLS_RemoteATMFilePage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case TIMER_QUERY_DOWNLOAD_PROGRESS:
		return QueryDownloadPorgress();

	}
	//CLS_BasePage::OnTimer(nIDEvent);
}

void CLS_RemoteATMFilePage::QueryDownloadPorgress()
{
	if (m_iLogonID < 0)
	{
		return;
	}
	for (int i = 0; i < MAX_PAGESIZE; i++)
	{
		CString szFileName = m_ListQueryFile.GetItemText(i, 1);
		CString szOperationTime = m_ListQueryFile.GetItemText(i, 6);
		CString szOperation = m_ListQueryFile.GetItemText(i, 5);
		if (szFileName == "")
		{
			return;
		}
		unsigned long iConnID;
		if (IsFileInList(m_iLogonID, szFileName, &iConnID,szOperationTime,szOperation))
		{
			int iPos = 0, iSize = 0;
			NetClient_NetFileGetDownloadPos(iConnID, &iPos, &iSize);
			CString szProgress;
			szProgress.Format("%d", iPos);
			szProgress += "%/";
			CString szSize;
			szSize.Format("%dB", iSize);
			szProgress += szSize;
			m_ListQueryFile.SetItemText(i, 8, szProgress);
		}
		else
		{
			CString szProgress;
			m_ListQueryFile.SetItemText(i, 8, szProgress);
		}
	}

}

BOOL CLS_RemoteATMFilePage::IsFileInList( int _iLogonID, CString _szFileName, unsigned long * _iConnID , CString _szOperationTime,CString _szOperate)
{
	BOOL bIn = FALSE;

	for (list <CLS_DownloadFile *>::iterator it = m_lstDownloadFile.begin(); it != m_lstDownloadFile.end(); it++)
	{
		CLS_DownloadFile * downloadFile = *it;
		if (downloadFile->GetFilename() == _szFileName && downloadFile->GetLogonID() == _iLogonID)
		{
			if (_szOperationTime.GetLength() > 0 )
			{
				if (0 == _szOperationTime.Compare(downloadFile->GetOperationTime()) && 0 == _szOperate.Compare(downloadFile->GetOperate()))
				{
					bIn = TRUE;
					*_iConnID = downloadFile->GetConnID();
					break;
				}
			}
			else
			{
				bIn = TRUE;
				*_iConnID = downloadFile->GetConnID();
				break;
			}
		}
	}
	return bIn;
}

void CLS_RemoteATMFilePage::OnDestroy()
{
	CLS_BasePage::OnDestroy();
	KillTimer(TIMER_QUERY_DOWNLOAD_PROGRESS);
	while(!m_lstDownloadFile.empty())
	{
		CLS_DownloadFile * downloadfile = m_lstDownloadFile.front();
		m_lstDownloadFile.pop_front();
		delete downloadfile;
	}
	// TODO: Add your message handler code here
}

void CLS_RemoteATMFilePage::DeleteDownload( unsigned long  _ulConnID )
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

void CLS_RemoteATMFilePage::DeleteDownload( const int _iLogonID, int _iFlag )
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
				m_lstDownloadFile.erase(it);
				delete downloadFile;
				iDelete = 1;
				break;
			}
		}
	}while(iDelete);
}

void CLS_RemoteATMFilePage::ProcessDownloadFinished( unsigned long _ulID )
{
	OpenFile(_ulID);
	DeleteDownload(_ulID);
}

void CLS_RemoteATMFilePage::ProcessErrorOrder( const int _iLogonID )
{
	DeleteDownload(_iLogonID, 0);
}

void CLS_RemoteATMFilePage::ProcessDownloadFault( unsigned long _ulID )
{
	DeleteDownload(_ulID);
}

void CLS_RemoteATMFilePage::ProcessDownloadInterrupt( unsigned long _ulID )
{
	DeleteDownload(_ulID);
}

void CLS_RemoteATMFilePage::QueryATMFile()
{
	if (m_CBQueryATMType.GetCurSel() == ATM_QUERY_CMD_FIELD)
	{
		ATM_FIELD_QUERY query = {0};
		query.iSize = sizeof(ATM_FIELD_QUERY);
// 		int iType = m_ComboRecType.GetCurSel();
// 		if (iType == 0)
// 		{
// 			query.iType = 0xFF;
// 		}
// 		else if (iType < 3)
// 		{
// 			query.iType = iType;
// 		}
// 		else
// 		{
// 			query.iType = GetDlgItemInt(IDC_COMBO_REC_TYPE);
// 		}
		query.iType = 0xFF;
		query.iChannel = m_ComboChannelNo.GetCurSel() -1;
		if (query.iChannel == -1)
		{
			query.iChannel = 0xFF;
		}
		CTime tempTime;
		m_DTQueryBeginTime.GetTime(tempTime);
		query.struStartTime.iYear = tempTime.GetYear();
		query.struStartTime.iMonth = tempTime.GetMonth();
		query.struStartTime.iDay = tempTime.GetDay();
		query.struStartTime.iHour = tempTime.GetHour();
		query.struStartTime.iMinute = tempTime.GetMinute();
		query.struStartTime.iSecond = tempTime.GetSecond();

		m_DTQueryEndTime.GetTime(tempTime);
		query.struStopTime.iYear = tempTime.GetYear();
		query.struStopTime.iMonth = tempTime.GetMonth();
		query.struStopTime.iDay = tempTime.GetDay();
		query.struStopTime.iHour = tempTime.GetHour();
		query.struStopTime.iMinute = tempTime.GetMinute();
		query.struStopTime.iSecond = tempTime.GetSecond();

		query.iPageSize = MAX_PAGESIZE;
		query.iPageNo = m_iCurrentPage;
		query.iFiletype = m_ComboFileType.GetCurSel();
		GetDlgItemText(IDC_EDIT_OSD, query.cOtherQuery, sizeof(query.cOtherQuery));
		query.iTriggerType = 0x7FFFFFFF;
		GetDlgItemText(IDC_EDIT_QUERY_ATM_DOMAIN1, query.cField[0], sizeof(query.cField[0]));
		GetDlgItemText(IDC_EDIT_QUERY_ATM_DOMAIN2, query.cField[1], sizeof(query.cField[1]));
		GetDlgItemText(IDC_EDIT_QUERY_ATM_DOMAIN3, query.cField[2], sizeof(query.cField[2]));
		GetDlgItemText(IDC_EDIT_QUERY_ATM_DOMAIN4, query.cField[3], sizeof(query.cField[3]));
		GetDlgItemText(IDC_EDIT_QUERY_ATM_DOMAIN5, query.cField[4], sizeof(query.cField[4]));
		NetClient_ATMQueryFile(m_iLogonID, ATM_QUERY_CMD_FIELD, &query);
	}
	else if (m_CBQueryATMType.GetCurSel() == ATM_QUERY_CMD_CARD)
	{
		ATM_CARD_QUERY query = {0};
		query.iSize = sizeof(ATM_CARD_QUERY);
		query.iType = m_ComboRecType.GetCurSel();
		if (query.iType == 0)
		{
			query.iType = 0xFF;
		}
		query.iChannel = m_ComboChannelNo.GetCurSel() -1;
		if (query.iChannel == -1)
		{
			query.iChannel = 0xFF;
		}
		CTime tempTime;
		m_DTQueryBeginTime.GetTime(tempTime);
		query.struStartTime.iYear = tempTime.GetYear();
		query.struStartTime.iMonth = tempTime.GetMonth();
		query.struStartTime.iDay = tempTime.GetDay();
		query.struStartTime.iHour = tempTime.GetHour();
		query.struStartTime.iMinute = tempTime.GetMinute();
		query.struStartTime.iSecond = tempTime.GetSecond();

		m_DTQueryEndTime.GetTime(tempTime);
		query.struStopTime.iYear = tempTime.GetYear();
		query.struStopTime.iMonth = tempTime.GetMonth();
		query.struStopTime.iDay = tempTime.GetDay();
		query.struStopTime.iHour = tempTime.GetHour();
		query.struStopTime.iMinute = tempTime.GetMinute();
		query.struStopTime.iSecond = tempTime.GetSecond();

		query.iPageSize = MAX_PAGESIZE;
		query.iPageNo = m_iCurrentPage;
		query.iFiletype = m_ComboFileType.GetCurSel();
		GetDlgItemText(IDC_EDIT_OSD, query.cOtherQuery, sizeof(query.cOtherQuery));
		query.iTriggerType = 0x7FFFFFFF;
		GetDlgItemText(IDC_EDIT_QUERY_ATM_DOMAIN1, query.cID, sizeof(query.cID));
		query.iOperate = m_CBBusinessType.GetCurSel();
		if (query.iOperate > 10)
		{
			query.iOperate = 0xff;
		}
		CString strQuantity;
		GetDlgItemText(IDC_EDIT_QUERY_ATM_DOMAIN3,strQuantity);
		if (strQuantity.GetLength() > 0)
		{
			query.iQuantity = GetDlgItemInt(IDC_EDIT_QUERY_ATM_DOMAIN3);
		}
		else
		{
			query.iQuantity = 0x7FFFFFFF;
		}
		
		query.iAbnormity = m_CBExceptions.GetCurSel();
		if (query.iAbnormity > 2)
		{
			query.iAbnormity = 0xff;
		}
		NetClient_ATMQueryFile(m_iLogonID, ATM_QUERY_CMD_CARD, &query);
	}
	else
	{
		return;
	}
}

void CLS_RemoteATMFilePage::UpDate_UI_ATM()
{
	m_CBQueryATMType.ResetContent();
	m_CBQueryATMType.AddString(GetTextEx(IDS_PLAYBACK_QUERY_ATM_DOMAIN_QUERY));
	m_CBQueryATMType.AddString(GetTextEx(IDS_PLAYBACK_QUERY_ATM_CARD_NUMBER_QUERY));
	m_CBQueryATMType.SetCurSel(0);
	SetDlgItemTextEx(IDC_STATIC_QUERY_ATM_TYPE, IDS_PLAYBACK_QUERY_ATM_TYPE);
	m_CBBusinessType.ShowWindow(SW_HIDE);
	m_CBExceptions.ShowWindow(SW_HIDE);
	SetDlgItemTextEx(IDC_BUTTON_ATM_QUERY, IDS_PLAYBACK_QUERY);
	GetDlgItem(IDC_EDIT_QUERY_ATM_DOMAIN2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_QUERY_ATM_DOMAIN4)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_QUERY_ATM_DOMAIN5)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_STATIC_QUERY_ATM_DOMAIN1, GetTextEx(IDS_PLAYBACK_QUERY_ATM_DOMAIN_QUERY) + "1");
	SetDlgItemText(IDC_STATIC_QUERY_ATM_DOMAIN2, GetTextEx(IDS_PLAYBACK_QUERY_ATM_DOMAIN_QUERY) + "2");
	SetDlgItemText(IDC_STATIC_QUERY_ATM_DOMAIN3, GetTextEx(IDS_PLAYBACK_QUERY_ATM_DOMAIN_QUERY) + "3");
	SetDlgItemText(IDC_STATIC_QUERY_ATM_DOMAIN4, GetTextEx(IDS_PLAYBACK_QUERY_ATM_DOMAIN_QUERY) + "4");
	SetDlgItemText(IDC_STATIC_QUERY_ATM_DOMAIN5, GetTextEx(IDS_PLAYBACK_QUERY_ATM_DOMAIN_QUERY) + "5");

	m_CBBusinessType.ResetContent();
	m_CBBusinessType.AddString(GetTextEx(IDS_PLAYBACK_ATM_OPERATE_ALL));
	m_CBBusinessType.AddString(GetTextEx(IDS_PLAYBACK_ATM_OPERATE_QUERY));
	m_CBBusinessType.AddString(GetTextEx(IDS_PLAYBACK_ATM_OPERATE_CASH));
	m_CBBusinessType.AddString(GetTextEx(IDS_PLAYBACK_ATM_OPERATE_CHANGE_PASSWORD));
	m_CBBusinessType.AddString(GetTextEx(IDS_PLAYBACK_ATM_OPERATE_VIREMENT));
	m_CBBusinessType.AddString(GetTextEx(IDS_PLAYBACK_ATM_OPERATE_DEPOSIT));
	m_CBBusinessType.AddString(GetTextEx(IDS_PLAYBACK_ATM_OPERATE_QUERY_WITHOUT_CARD));
	m_CBBusinessType.AddString(GetTextEx(IDS_PLAYBACK_ATM_OPERATE_DEPOSIT_WITHOUT_CARD));
	m_CBBusinessType.AddString(GetTextEx(IDS_PLAYBACK_ATM_OPERATE_OTHER));
	m_CBBusinessType.AddString(GetTextEx(IDS_PLAYBACK_ATM_OPERATE_INSERT_CARD));
	m_CBBusinessType.AddString(GetTextEx(IDS_PLAYBACK_ATM_OPERATE_DRAW_CARD));
	m_CBBusinessType.AddString(GetTextEx(IDS_PLAYBACK_ATM_OPERATE_NOTHING));
	m_CBBusinessType.SetCurSel(0);

	m_CBExceptions.ResetContent();
	m_CBExceptions.AddString(GetTextEx(IDS_PLAYBACK_ATM_ABNORMAL_ALL));
	m_CBExceptions.AddString(GetTextEx(IDS_PLAYBACK_ATM_ABNORMAL_EAT_CASH));	
	m_CBExceptions.AddString(GetTextEx(IDS_PLAYBACK_ATM_ABNORMAL_EAT_CARD));
	m_CBExceptions.AddString(GetTextEx(IDS_PLAYBACK_ATM_ABNORMAL_NONE));
}

void CLS_RemoteATMFilePage::OnCbnSelchangeComboQueryAtmType()
{
	// TODO: Add your control notification handler code here
	int a = m_CBQueryATMType.GetCurSel();
	if (m_CBQueryATMType.GetCurSel())
	{
		GetDlgItem(IDC_STATIC_QUERY_ATM_DOMAIN5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_QUERY_ATM_DOMAIN2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_QUERY_ATM_DOMAIN4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_QUERY_ATM_DOMAIN5)->ShowWindow(SW_HIDE);
		m_CBBusinessType.ShowWindow(SW_SHOW);
		m_CBExceptions.ShowWindow(SW_SHOW);
		SetDlgItemTextEx(IDC_STATIC_QUERY_ATM_DOMAIN1, IDS_PLAYBACK_QUERY_ATM_CARD_NUMBER);
		SetDlgItemTextEx(IDC_STATIC_QUERY_ATM_DOMAIN2, IDS_PLAYBACK_QUERY_ATM_BUSINESS_TYPE);
		SetDlgItemTextEx(IDC_STATIC_QUERY_ATM_DOMAIN3, IDS_PLAYBACK_QUERY_ATM_AMOUNT);
		SetDlgItemTextEx(IDC_STATIC_QUERY_ATM_DOMAIN4, IDS_PLAYBACK_QUERY_ATM_EXCEPTION);
	}
	else
	{
		GetDlgItem(IDC_STATIC_QUERY_ATM_DOMAIN5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_QUERY_ATM_DOMAIN2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_QUERY_ATM_DOMAIN4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_QUERY_ATM_DOMAIN5)->ShowWindow(SW_SHOW);
		m_CBBusinessType.ShowWindow(SW_HIDE);
		m_CBExceptions.ShowWindow(SW_HIDE);
		SetDlgItemText(IDC_STATIC_QUERY_ATM_DOMAIN1, GetTextEx(IDS_PLAYBACK_QUERY_ATM_DOMAIN_QUERY) + "1");
		SetDlgItemText(IDC_STATIC_QUERY_ATM_DOMAIN2, GetTextEx(IDS_PLAYBACK_QUERY_ATM_DOMAIN_QUERY) + "2");
		SetDlgItemText(IDC_STATIC_QUERY_ATM_DOMAIN3, GetTextEx(IDS_PLAYBACK_QUERY_ATM_DOMAIN_QUERY) + "3");
		SetDlgItemText(IDC_STATIC_QUERY_ATM_DOMAIN4, GetTextEx(IDS_PLAYBACK_QUERY_ATM_DOMAIN_QUERY) + "4");
		SetDlgItemText(IDC_STATIC_QUERY_ATM_DOMAIN5, GetTextEx(IDS_PLAYBACK_QUERY_ATM_DOMAIN_QUERY) + "5");
	}
}

void CLS_RemoteATMFilePage::OnBnClickedButtonAtmQuery()
{
	m_ListQueryFile.DeleteAllItems();
	m_iCurrentPage = 0;
	// TODO: Add your control notification handler code here
	if (m_iLogonID == -1)
	{
		return;
	}
	QueryATMFile();
}

void CLS_RemoteATMFilePage::Update_UI_Query_ATM_Result()
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
	ATM_FILE_DATA fileInfo = {0};
	for(int i=0; i<m_iCurrentCount; i++)
	{
		if(0 == NetClient_ATMGetQueryFile(m_iLogonID, i, &fileInfo))
		{
			int iCellID = m_iCurrentPage*MAX_PAGESIZE + i+1;
			if (iCellID <= m_iTotalCount)
			{
				CString szID;
				szID.Format("%d", iCellID);
				m_ListQueryFile.InsertItem(i, "");
				int iColumn = 0;
				m_ListQueryFile.SetItemText(i, iColumn++, szID);
				m_ListQueryFile.SetItemText(i, iColumn++, fileInfo.cFileName);
				CString szType;
				szType.Format("%d", fileInfo.iType);
				m_ListQueryFile.SetItemText(i, iColumn++, szType);
				CString szChannel;
				szChannel.Format("%d", fileInfo.iChannel);
				m_ListQueryFile.SetItemText(i, iColumn++, szChannel);
				CString szFileSize;
				szFileSize.Format("%d", fileInfo.iFileSize);
				m_ListQueryFile.SetItemText(i, iColumn++, szFileSize);
				CString szOperation;
				szOperation.Format("%d", fileInfo.iOperate);
				m_ListQueryFile.SetItemText(i, iColumn++, szOperation);
				CString szOpTime;
				
				szOpTime.Format("%d-%d-%d %d:%d:%d", fileInfo.struOperateTime.iYear
					, fileInfo.struOperateTime.iMonth
					, fileInfo.struOperateTime.iDay
					, fileInfo.struOperateTime.iHour
					, fileInfo.struOperateTime.iMinute
					, fileInfo.struOperateTime.iSecond);
				m_ListQueryFile.SetItemText(i, iColumn++, szOpTime);
 				CString szTime;
// 				szTime.Format("%d-%d-%d %d:%d:%d", fileInfo.struStartTime.iYear
// 					, fileInfo.struStartTime.iMonth
// 					, fileInfo.struStartTime.iDay
// 					, fileInfo.struStartTime.iHour
// 					, fileInfo.struStartTime.iMinute
// 					, fileInfo.struStartTime.iSecond);
//				m_ListQueryFile.SetItemText(i, iColumn++, szTime);
				szTime.Format("%d-%d-%d %d:%d:%d", fileInfo.struStoptime.iYear
					, fileInfo.struStoptime.iMonth
					, fileInfo.struStoptime.iDay
					, fileInfo.struStoptime.iHour
					, fileInfo.struStoptime.iMinute
					, fileInfo.struStoptime.iSecond);
				m_ListQueryFile.SetItemText(i, iColumn++, szTime);

				unsigned long iConnID;
				if (IsFileInList(m_iLogonID, fileInfo.cFileName, &iConnID,szOpTime,szOperation))
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



// CLS_RemoteATMFilePage message handlers

void CLS_RemoteATMFilePage::OnBnClickedButtonPause()
{
	// TODO: Add your control notification handler code here
	unsigned long iConnID = INVALID_ID;
	if (IsFileInList(m_iLogonID, m_szFileName, &iConnID,m_szOperationTime,m_szOperate))
	{
		NetClient_NetFileDownloadFile(&iConnID, m_iLogonID, "", "", 1, -1, 0);
	}
}

void CLS_RemoteATMFilePage::OnBnClickedButtonContinue()
{
	// TODO: Add your control notification handler code here
	unsigned long iConnID = INVALID_ID;
	if (IsFileInList(m_iLogonID, m_szFileName, &iConnID,m_szOperationTime,m_szOperate))
	{
		NetClient_NetFileDownloadFile(&iConnID, m_iLogonID, "", "", 1, -1, 16);
	}
}

void CLS_RemoteATMFilePage::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	unsigned long iConnID = INVALID_ID;
	if (IsFileInList(m_iLogonID, m_szFileName, &iConnID,m_szOperationTime,m_szOperate))
	{
		DeleteDownload(iConnID);
	}
}

void CLS_RemoteATMFilePage::OnLogoffDevice( int _iLogonID )
{
	DeleteDownload(_iLogonID, 0);
}

void CLS_RemoteATMFilePage::OpenFile( unsigned long _ulConnID )
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

CString CLS_RemoteATMFilePage::GetFileNameByConID( unsigned long _ulConnID )
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