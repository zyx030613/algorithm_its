
#include "stdafx.h"
#include "NetClientDemo.h"
#include "ReportSet.h"


// CLS_ReportSet 对话框

IMPLEMENT_DYNAMIC(CLS_ReportSet, CDialog)

CLS_ReportSet::CLS_ReportSet(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ReportSet::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iSelItem = -1;
}

CLS_ReportSet::~CLS_ReportSet()
{
}

void CLS_ReportSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_FTP_ADDR, m_edtFtpAddr);
	DDX_Control(pDX, IDC_EDT_FTP_PORT, m_edtFtpPort);
	DDX_Control(pDX, IDC_EDT_FTP_PATH, m_edtFtpPath);
	DDX_Control(pDX, IDC_EDT_FTP_USER, m_edtFtpUser);
	DDX_Control(pDX, IDC_EDT_FTP_PASSWORD, m_edtFtpPswd);
	DDX_Control(pDX, IDC_EDT_FTP_USAGE, m_edtFtpUsage);
	DDX_Control(pDX, IDC_EDT_CAPTURE_PICSIZE, m_edtCapturePicSize);
	DDX_Control(pDX, IDC_EDT_CAPTURE_INTERVAL, m_edtCaptureInterval);
	DDX_Control(pDX, IDC_CBO_CAPTURE_SCENEID, m_cboSceneId);
	DDX_Control(pDX, IDC_LST_REPORT_TIME, m_lstReportTime);
	DDX_Control(pDX, IDC_DT_REPORT_BEGINTIME, m_dtReportTime);
	DDX_Control(pDX, IDC_DT_CAPTURE_BEG, m_dtCaptureBeg);
	DDX_Control(pDX, IDC_DT_CAPTURE_END, m_dtCaptureEnd);
}


BEGIN_MESSAGE_MAP(CLS_ReportSet, CDialog)
	ON_BN_CLICKED(IDC_BTN_FTP_SET, &CLS_ReportSet::OnBnClickedBtnFtpSet)
	ON_BN_CLICKED(IDC_BTN_CAPTURE_SET, &CLS_ReportSet::OnBnClickedBtnCaptureSet)
	ON_BN_CLICKED(IDC_BTN_REPORT_ADD, &CLS_ReportSet::OnBnClickedBtnReportAdd)
	ON_BN_CLICKED(IDC_BTN_REPORT_MODIFY, &CLS_ReportSet::OnBnClickedBtnReportModify)
	ON_BN_CLICKED(IDC_BTN_REPORT_DELETE, &CLS_ReportSet::OnBnClickedBtnReportDelete)
	ON_NOTIFY(NM_CLICK, IDC_LST_REPORT_TIME, &CLS_ReportSet::OnNMClickLstReportTime)
	ON_STN_CLICKED(IDC_STC_CAPTURE_SCENEID, &CLS_ReportSet::OnStnClickedStcCaptureSceneid)
	ON_CBN_SELCHANGE(IDC_CBO_CAPTURE_SCENEID, &CLS_ReportSet::OnCbnSelchangeCboCaptureSceneid)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_WLD_GAUGE, &CLS_ReportSet::OnBnClickedButtonWldGauge)
END_MESSAGE_MAP()


BOOL CLS_ReportSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_edtCapturePicSize.SetLimitText(6);
	m_edtCaptureInterval.SetLimitText(6);

	m_edtFtpAddr.SetLimitText(63);
	m_edtFtpPort.SetLimitText(5);
	m_edtFtpPath.SetLimitText(63);
	m_edtFtpUser.SetLimitText(63);
	m_edtFtpPswd.SetLimitText(63);
	m_edtFtpUsage.SetLimitText(5);

	//m_dtReportTime.SetFormat(_T("HH:mm:ss"));
	m_dtReportTime.SetFormat(_T("HH:mm"));
	m_dtCaptureBeg.SetFormat(_T("HH:mm"));
	m_dtCaptureEnd.SetFormat(_T("HH:mm"));
	GetDlgItem(IDC_STC_CAPTURE_PICNUM)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDT_CAPTURE_PICSIZE)->ShowWindow(SW_HIDE);
	UI_UpdateDialog();
	
	return TRUE;
}

void CLS_ReportSet::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;
	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo;
	}

	UI_UpdateCaptureInfo();
	UI_UpdateFtpInfo();
	UI_UpdataFtpReportTime();
}

void CLS_ReportSet::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ReportSet::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_BTN_REPORT_ADD,IDS_ADD);
	SetDlgItemTextEx(IDC_BTN_REPORT_MODIFY,IDS_MODIFY);
	SetDlgItemTextEx(IDC_BTN_REPORT_DELETE,IDS_DELETE);

	//SetDlgItemTextEx(IDC_STC_CAPTURE_ENABLE, IDS_CONFIG_FTP_SNAPSHOT_ENABLE);
	SetDlgItemTextEx(IDC_STC_CAPTURE_SCENEID, IDS_VCA_SCENE_ID);
	SetDlgItemTextEx(IDC_STC_CAPTURE_PICNUM,IDS_VCA_EVENT_CAPNUM);
	SetDlgItemTextEx(IDC_STC_CAPTURE_INTERVAL,IDS_REPORT_MINUTE);	
	SetDlgItemTextEx(IDC_BTN_CAPTURE_SET,IDS_SET);

	SetDlgItemTextEx(IDC_STC_FTP_ADDR,IDS_CONFIG_FTP_ADDR);
	SetDlgItemTextEx(IDC_STC_FTP_PORT,IDS_CONFIG_FTP_PORT);
	SetDlgItemTextEx(IDC_STC_FTP_PATH,IDS_CONFIG_FTP_PATH);
	SetDlgItemTextEx(IDC_STC_FTP_USER,IDS_CONFIG_FTP_USER);
	SetDlgItemTextEx(IDC_STC_FTP_PASSWORD,IDS_CONFIG_FTP_PASSWORD);
	SetDlgItemTextEx(IDC_STC_FTP_USAGE,IDS_CONFIG_FTP_USAGE);
	SetDlgItemTextEx(IDC_BTN_FTP_SET,IDS_SET);

	SetDlgItemTextEx(IDC_GBO_REPORT_TIMING,IDS_CONFIG_REPORT_TIMING);
	SetDlgItemTextEx(IDC_STC_REPORT_TIME,IDS_CONFIG_REPORT_TIME);
	SetDlgItemTextEx(IDC_GBO_FTP_SET,IDS_CONFIG_REPORT_FTP_SET);
	SetDlgItemTextEx(IDC_GBO_CAPTURE_SET,IDS_CONFIG_REPORT_CAPTURE_SET);
	SetDlgItemTextEx(IDC_STC_CAPTURE_TIME,IDS_CONFIG_REPORT_CAPTURE_TIME);
	SetDlgItemTextEx(IDC_BUTTON_WLD_GAUGE, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_WLD_GAUGE, IDS_VCA_WLD_GAUGE);

	InsertString(m_cboSceneId, 0, IDS_CONFIG_COMS_SCENE1);
	InsertString(m_cboSceneId, 1, IDS_CONFIG_COMS_SCENE2);
	InsertString(m_cboSceneId, 2, IDS_CONFIG_COMS_SCENE3);
	InsertString(m_cboSceneId, 3, IDS_CONFIG_COMS_SCENE4);
	m_cboSceneId.SetCurSel(0);

	m_cboSceneId.ResetContent();
	for (int i = 0; i < MAX_SCENE_NUM; i++)
	{
		m_cboSceneId.InsertString(i, IntToCString(i + 1));
	}
	m_cboSceneId.SetCurSel(0);
}

BOOL CLS_ReportSet::UI_UpdateCaptureInfo()
{
	if (m_iLogonID < 0)
	{
		return FALSE;
	}

	WaterSampleSnapInfo Snapshot = {0};
	int iRetSize = -1;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_WATER_SNAPINFO,m_iChannelNo, &Snapshot, sizeof(Snapshot), &iRetSize);
	if (0 == iRet)
	{	
		int iTime = Snapshot.iTime;		
		CTime tTime =  CTime::GetCurrentTime();

		NVS_FILE_TIME st = {0};
		st.iHour = iTime >> 24 & 0xFF;
		st.iMinute = iTime >> 16 & 0xFF;

		tTime = CTime(tTime.GetYear(), tTime.GetMonth(), tTime.GetDay(),st.iHour, st.iMinute, tTime.GetSecond()); 
		m_dtCaptureBeg.SetTime(&tTime);

		st.iHour = iTime >> 8 & 0xFF;
		st.iMinute = iTime  & 0xFF;
		tTime = CTime(tTime.GetYear(), tTime.GetMonth(), tTime.GetDay(),st.iHour, st.iMinute, tTime.GetSecond()); 
		m_dtCaptureEnd.SetTime(&tTime);

		SetDlgItemInt(IDC_EDT_CAPTURE_PICSIZE, Snapshot.iCount);
		SetDlgItemInt(IDC_EDT_CAPTURE_INTERVAL, Snapshot.iInterVal);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(Snapshot));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(Snapshot));
	}

	return TRUE;
}

BOOL CLS_ReportSet::UI_UpdateFtpInfo()
{
	if (m_iLogonID < 0)
	{
		return FALSE;
	}

	FTP_UPDATE ftpUpdate = {0};
	int iRet = NetClient_GetFTPUploadConfig(m_iLogonID, FTP_CMD_GET_UPDATE, &ftpUpdate, sizeof(ftpUpdate));
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDT_FTP_ADDR, ftpUpdate.cFtpAddr);
		SetDlgItemInt(IDC_EDT_FTP_PORT, ftpUpdate.iPort);
		SetDlgItemText(IDC_EDT_FTP_PATH, ftpUpdate.cFileName);
		SetDlgItemText(IDC_EDT_FTP_USER, ftpUpdate.cUserName);
		SetDlgItemText(IDC_EDT_FTP_PASSWORD, ftpUpdate.cPassword);
		SetDlgItemInt(IDC_EDT_FTP_USAGE, ftpUpdate.iUsage);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpUpdate));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpUpdate));
	}
	return TRUE;
}

BOOL CLS_ReportSet::UI_UpdataFtpReportTime()
{
	if (m_iLogonID < 0)
	{
		return FALSE;
	}

	int iRet = -1;
	int iRetSize = -1;
	m_lstReportTime.DeleteAllItems();
	m_vecReptTime.clear();
	for (int i = 0; i < MAX_SCENETIME_COUNT; i++)
	{
		ScenetimePoint stTmp = {0};
		stTmp.iBufSize = sizeof(stTmp);
		stTmp.iIndex = i;
		stTmp.iType = 1;
		iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_SCENETIMEPOINT, m_iChannelNo, &stTmp, sizeof(stTmp), &iRetSize);
		
		if (0 != iRet)
		{
			continue;
		}

		if (stTmp.iEnable == 0)
		{
			continue;
		}
		if(stTmp.stStartTime.iHour > 24 || stTmp.stStartTime.iHour < 0)
		{
			continue;
		}
		if(stTmp.stStartTime.iMinute > 59 || stTmp.stStartTime.iMinute < 0)
		{
			continue;
		}
		m_vecReptTime.push_back(stTmp);
	}	
	
	UpdataTimeList();
	return TRUE;
}

void CLS_ReportSet::OnBnClickedBtnFtpSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	FTP_UPDATE ftpUpdate = {0};
	GetDlgItemText(IDC_EDT_FTP_ADDR, ftpUpdate.cFtpAddr, 64);
	ftpUpdate.iPort = GetDlgItemInt(IDC_EDT_FTP_PORT);
	GetDlgItemText(IDC_EDT_FTP_PATH, ftpUpdate.cFileName, 64);
	GetDlgItemText(IDC_EDT_FTP_USER, ftpUpdate.cUserName, 64);
	GetDlgItemText(IDC_EDT_FTP_PASSWORD, ftpUpdate.cPassword, 64);
	ftpUpdate.iUsage = GetDlgItemInt(IDC_EDT_FTP_USAGE);
	int iRet = NetClient_SetFTPUploadConfig(m_iLogonID, FTP_CMD_SET_UPDATE, &ftpUpdate, sizeof(ftpUpdate));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpUpdate));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetFTPUploadConfig(%d,%d)",m_iLogonID,sizeof(ftpUpdate));
	}
}

void CLS_ReportSet::OnBnClickedBtnCaptureSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	CTime ctBeg;
	CTime ctEnd;
	m_dtCaptureBeg.GetTime(ctBeg);
	m_dtCaptureEnd.GetTime(ctEnd);
	int iBeginHour = ctBeg.GetHour();
	int iBeginMinute = ctBeg.GetMinute();
	int iEndHour = ctEnd.GetHour();
	int iEndMinute = ctEnd.GetMinute();

	int iTime = 0;

	iTime = iBeginHour << 24;
	iTime |= iBeginMinute << 16;
	iTime |= iEndHour << 8;
	iTime |= iEndMinute;
// 	int iTime = ctBeg.GetHour() << 24;
// 	iTime |= ctBeg.GetMinute() << 16;
// 	iTime |= ctBeg.GetMinute() << 8;
// 	iTime |= ctBeg.GetMinute();

	WaterSampleSnapInfo Snapshot = {0};
	Snapshot.iIndex = 0;
	Snapshot.iTime = iTime;
	Snapshot.iCount = 1;
	Snapshot.iInterVal = GetDlgItemInt(IDC_EDT_CAPTURE_INTERVAL);
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_WATER_SNAPINFO, m_iChannelNo, &Snapshot, sizeof(Snapshot));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig(%d,%d)",m_iLogonID,sizeof(Snapshot));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig(%d,%d)",m_iLogonID,sizeof(Snapshot));
	}
}

void CLS_ReportSet::SaveReportTimeInfo(int _iEnable)
{
}

void CLS_ReportSet::UpdataTimeList()
{
	m_lstReportTime.DeleteAllItems();
	size_t iCount = m_vecReptTime.size();
	for (int i=0; i<iCount; i++)
	{
		ScenetimePoint stTmp = m_vecReptTime[i];
		CString cstrTime = "";
		cstrTime.Format("%02d:%02d", stTmp.stStartTime.iHour, stTmp.stStartTime.iMinute);
		m_lstReportTime.InsertItem(i, "");
		m_lstReportTime.SetItemText(i, 0, cstrTime);
	}
}

void CLS_ReportSet::OnBnClickedBtnReportAdd()
{
	CTime ctTime;
	CTime ctEndTime;
	m_dtReportTime.GetTime(ctTime);
	ScenetimePoint st = {0};
	st.iBufSize = sizeof(st);
	st.iEnable = 1;
	st.iType = 1;
	st.stStartTime.iHour = ctTime.GetHour();
	st.stStartTime.iMinute = ctTime.GetMinute();
	st.stEndTime.iHour = ctTime.GetHour();
	st.stEndTime.iMinute = ctTime.GetMinute();
	for (int i=0; i<m_vecReptTime.size(); i++)
	{
		ScenetimePoint stTmp = m_vecReptTime[i];
		if (st.stStartTime.iHour == m_vecReptTime[i].stStartTime.iHour && st.stStartTime.iMinute == m_vecReptTime[i].stStartTime.iMinute)
		{
			return;
		}
	}
	int iIndex = -1;
	bool blFind = false;
	for (int i=0; i<MAX_SCENETIME_COUNT;i++)
	{
		blFind = false;
		for (int j=0; j<m_vecReptTime.size(); j++)
		{
			if (i == m_vecReptTime[j].iIndex)
			{
				blFind = true;
				break;
			}
		}

		if (blFind == false)
		{
			iIndex = i;
			break;
		}
	}

	if (iIndex == -1)
	{
		return;
	}
	st.iIndex = iIndex;
	//SaveReportTimeInfo(VCA_SEGMENTTIME_ENABLE);
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_SCENETIMEPOINT, m_iChannelNo, &st, sizeof(st));
	if (0 == iRet)
	{
		m_vecReptTime.push_back(st);
		UpdataTimeList();
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig(%d,%d)",m_iLogonID,sizeof(st));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig(%d,%d)",m_iLogonID,sizeof(st));
	}
}

void CLS_ReportSet::OnBnClickedBtnReportModify()
{
	if (m_iSelItem < 0 || m_iSelItem > m_vecReptTime.size())
	{
		return;
	}

	ScenetimePoint& st = m_vecReptTime[m_iSelItem];
	m_lstReportTime.SetItemState(m_iSelItem,LVNI_FOCUSED | LVIS_SELECTED, LVNI_FOCUSED | LVIS_SELECTED);
	CTime ctTime;
	m_dtReportTime.GetTime(ctTime);
	for (int i=0; i<m_vecReptTime.size(); i++)
	{
		if (ctTime.GetHour() == m_vecReptTime[i].stStartTime.iHour && ctTime.GetMinute() == m_vecReptTime[i].stStartTime.iMinute)
		{
			return;
		}
	}
	st.stStartTime.iHour = ctTime.GetHour();
	st.stStartTime.iMinute = ctTime.GetMinute();
	st.stEndTime.iHour = ctTime.GetHour();
	st.stEndTime.iMinute = ctTime.GetMinute();

	m_iSelItem = -1;
	UpdataTimeList();
	//SaveReportTimeInfo(VCA_SEGMENTTIME_ENABLE);
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_SCENETIMEPOINT, m_iChannelNo, &st, sizeof(st));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig(%d,%d)",m_iLogonID,sizeof(st));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig(%d,%d)",m_iLogonID,sizeof(st));
	}
}

void CLS_ReportSet::OnBnClickedBtnReportDelete()
{
	if (m_iSelItem < 0 || m_iSelItem > m_vecReptTime.size())
	{
		return;
	}

	ScenetimePoint st = m_vecReptTime[m_iSelItem];

	int i=0;
	for(vector<ScenetimePoint>::iterator it  = m_vecReptTime.begin(); it != m_vecReptTime.end();)
	{
		if (i == m_iSelItem)
		{
			m_vecReptTime.erase(it);
			m_iSelItem = -1;
			break;
		}
		it++;
		i++;
	}

	UpdataTimeList();
	//SaveReportTimeInfo(VCA_SEGMENTTIME_NOT_ENABLE);
	st.iEnable = 0;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_SCENETIMEPOINT, m_iChannelNo, &st, sizeof(st));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig(%d,%d)",m_iLogonID,sizeof(st));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig(%d,%d)",m_iLogonID,sizeof(st));
	}
}

void CLS_ReportSet::OnNMClickLstReportTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nItem = pNMListView->iItem;		//行号
	int nSub = 	pNMListView->iSubItem;	//列号

	if (nItem < 0 || nItem > m_vecReptTime.size())
	{
		return;
	}
	m_iSelItem = nItem;
	m_lstReportTime.SetItemState(nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

	ScenetimePoint st = m_vecReptTime[nItem];
	CTime tTime =  CTime::GetCurrentTime();
	tTime = CTime(tTime.GetYear(), tTime.GetMonth(), tTime.GetDay(),st.stStartTime.iHour, st.stStartTime.iMinute,0); 
	m_dtReportTime.SetTime(&tTime);
	*pResult = 0;
}

void CLS_ReportSet::OnStnClickedStcCaptureSceneid()
{
	// TODO: Add your control notification handler code here
}

void CLS_ReportSet::OnCbnSelchangeCboCaptureSceneid()
{
	// TODO: Add your control notification handler code here
	UI_UpdateCaptureInfo();
}

void CLS_ReportSet::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		CTime tTime =  CTime::GetCurrentTime();
		m_dtReportTime.SetTime(&tTime);
	}
}

void CLS_ReportSet::OnBnClickedButtonWldGauge()
{
	PlatformGauge tPlatformGauge = {0};
	tPlatformGauge.iSize = sizeof(PlatformGauge);
	tPlatformGauge.iSceneID = m_cboSceneId.GetCurSel();
	int iRet = NetClient_SendCommand(m_iLogonID, COMMAND_ID_PLATFORM_GAUGE,  m_iChannelNo, &tPlatformGauge, sizeof(PlatformGauge));
	if (RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SendCommand(COMMAND_ID_PLATFORM_GAUGE)");
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SendCommand(COMMAND_ID_PLATFORM_GAUGE)");
	}
}

void CLS_ReportSet::OnMainNotify(int _ulLogonID, int _iWparam, void* _pvLParam, void* _pvUser)
{
	int iMsgType = LOWORD(_iWparam);
	if (WCM_LASTERROR_INFO != iMsgType)
	{
		return;
	}

	int iLParam = (int)_pvLParam;
	if (EC_VCA_PLATFORM_GAUGE != iLParam)
	{
		return;
	}

	DevLastError tDecLastError = {0};
	NetClient_RecvCommand(m_iLogonID, COMMAND_ID_DEV_LASTERROR, m_iChannelNo, &tDecLastError, sizeof(tDecLastError));
	if (EC_VCA_PLATFORM_GAUGE != tDecLastError.iErrorID)
	{
		return;
	}

	int iResult = _ttoi(tDecLastError.cErrorInfo);
	switch(iResult)
	{
	case 1:
		{
			MessageBox("Water level detect success!", "Info", MB_OK);
			break;
		}
	case 2:
		{
			MessageBox("Water level detect fail!", "Info", MB_OK);
			break;
		}
	default:
		break;
	}
}
