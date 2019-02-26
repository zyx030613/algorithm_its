// DVRLogPage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "DVRLogPage.h"
#include "../Common/LanguageManager.h"

#define LOG_PAGE_SIZE	10

// CLS_DVRLogPage dialog

IMPLEMENT_DYNAMIC(CLS_DVRLogPage, CDialog)

CLS_DVRLogPage::CLS_DVRLogPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DVRLogPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iCurrentPage = 0;
	m_iTotalFiles = 0;
	m_iTotalPages = 0;
}

CLS_DVRLogPage::~CLS_DVRLogPage()
{
}

void CLS_DVRLogPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CFG_LOG_DVR_LISTCONTROL, m_ctlListDVRLog);
	DDX_Control(pDX, IDC_COMBO_LOGDVR_LOGTYPE, m_cboLogType);
	DDX_Control(pDX, IDC_COMBO_LOGDVR_LANGUAGE, m_cboLanguage);
	DDX_Control(pDX, IDC_DATETIMEPICKER_CFG_LOG_DVR_BEGIN, m_dtpBeginTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_CFG_LOG_DVR_END, m_dtpEndTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_LOG_DVR_BEGINDATE, m_dtpBeginDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_LOG_DVR_ENDDATE, m_dtpEndDate);
}


BEGIN_MESSAGE_MAP(CLS_DVRLogPage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CFG_LOG_DVR_QUERY, &CLS_DVRLogPage::OnBnClickedButtonCfgLogDvrQuery)
	ON_BN_CLICKED(IDC_BUTTON_CFG_LOGDVR_FIRSTPAGE, &CLS_DVRLogPage::OnBnClickedButtonCfgLogdvrFirstpage)
	ON_BN_CLICKED(IDC_BUTTON_CFG_LOGDVR_PREPAGE, &CLS_DVRLogPage::OnBnClickedButtonCfgLogdvrPrepage)
	ON_BN_CLICKED(IDC_BUTTON_CFG_LOGDVR_NEXTPAGE, &CLS_DVRLogPage::OnBnClickedButtonCfgLogdvrNextpage)
	ON_BN_CLICKED(IDC_BUTTON_CFG_LOGDVR_LASTPAGE, &CLS_DVRLogPage::OnBnClickedButtonCfgLogdvrLastpage)
END_MESSAGE_MAP()

void CLS_DVRLogPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	if (m_iLogonID < 0)
	{
		return;
	}
	if (m_iChannelNo == -1)
	{
		m_iChannelNo = FLAG_QUERY_ALL_CHANNEL;
	}

	//UI_UpdateLogCount();
	UI_UpdateTimeRange();

	m_ctlListDVRLog.DeleteAllItems();
	m_iCurrentPage = 0;
	m_iTotalPages = 0;
	m_iTotalFiles = 0;
	SetDlgItemInt(IDC_STATIC_CFG_LOGDVR_TOTALLOGS, m_iTotalFiles);
	SetDlgItemInt(IDC_STATIC_CFG_LOGDVR_TOTALPAGES, m_iTotalPages);
	SetDlgItemInt(IDC_STATIC_CFG_LOGDVR_CURRENTPAGE, m_iCurrentPage);
}

void CLS_DVRLogPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
	UI_UpdateLogCount();
}

// CLS_DVRLogPage message handlers

BOOL CLS_DVRLogPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	
	m_ctlListDVRLog.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	UI_UpdateDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_DVRLogPage::OnBnClickedButtonCfgLogDvrQuery()
{
	// TODO: Add your control notification handler code here
	if (m_cboLogType.GetCurSel() == -1 || m_cboLanguage.GetCurSel() == -1)
		return;

	m_iCurrentPage = 0;
	int iLogType = m_cboLogType.GetCurSel();
	if (6 == iLogType)
	{
		iLogType = 0xFF;
	}

	int iLanguage = m_cboLanguage.GetCurSel();

	m_logQuery.iChannelNo = m_iChannelNo;
	m_logQuery.iLogType = iLogType;
	m_logQuery.iLanguage = iLanguage;
	m_logQuery.iPageSize = LOG_PAGE_SIZE;
	m_logQuery.iPageNo = 0;

	unsigned short usTmp = 0;
	SYSTEMTIME BeginDate;
	SYSTEMTIME BeginTime;
	SYSTEMTIME EndDate;
	SYSTEMTIME EndTime;
	m_dtpBeginDate.GetTime(&BeginDate);
	m_logQuery.struStartTime.iYear = BeginDate.wYear;
	m_logQuery.struStartTime.iMonth = BeginDate.wMonth;
	m_logQuery.struStartTime.iDay = BeginDate.wDay;
	m_dtpBeginTime.GetTime(&BeginTime);
	m_logQuery.struStartTime.iHour = BeginTime.wHour;
	m_logQuery.struStartTime.iMinute = BeginTime.wMinute;
	m_logQuery.struStartTime.iSecond = BeginTime.wSecond;
	m_dtpEndDate.GetTime(&EndDate);
	m_logQuery.struStopTime.iYear = EndDate.wYear;
	m_logQuery.struStopTime.iMonth = EndDate.wMonth;
	m_logQuery.struStopTime.iDay = EndDate.wDay;
	m_dtpEndTime.GetTime(&EndTime);
	m_logQuery.struStopTime.iHour = EndTime.wHour;
	m_logQuery.struStopTime.iMinute = EndTime.wMinute;
	m_logQuery.struStopTime.iSecond = EndTime.wSecond;

	int iTimeFlag = 0;		//标志，如果查询日志开始时间>结束时间，会将其值置1
	if (BeginDate.wYear > EndDate.wYear)
	{
		iTimeFlag = 1;
	}
	else
	{
		if (BeginDate.wYear == EndDate.wYear)
		{
			if (BeginDate.wMonth > EndDate.wMonth)
			{
				iTimeFlag = 1;
			}
			else
			{
				if (BeginDate.wMonth == EndDate.wMonth)
				{
					if (BeginDate.wDay > EndDate.wDay)
					{
						iTimeFlag = 1;
					}
					else
					{
						if (BeginDate.wDay == EndDate.wDay)
						{
							if (BeginTime.wHour > EndTime.wHour)
							{
								iTimeFlag = 1;
							}
							else
							{
								if (BeginTime.wHour == EndTime.wHour)
								{
									if (BeginTime.wMinute > EndTime.wMinute)
									{
										iTimeFlag = 1;
									}
									else
									{
										if (BeginTime.wMinute == EndTime.wMinute)
										{
											if (BeginTime.wSecond > EndTime.wSecond)
											{
												iTimeFlag = 1;
											}
											else
											{
												if (BeginTime.wSecond == EndTime.wSecond)
												{
													iTimeFlag = 2;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	if (iTimeFlag == 1)
	{
		MessageBox(GetTextEx(IDS_CONFIG_DVRLOG_TIMEMSG_LATER),GetTextEx(IDS_CONFIG_PROMPT),MB_OK);
		return;
	}
	else if (iTimeFlag == 2)
	{
		MessageBox(GetTextEx(IDS_CONFIG_DVRLOG_TIMEMSG_EQUAL),GetTextEx(IDS_CONFIG_PROMPT),MB_OK);
		return;
	}
	int iRet = NetClient_NetLogQuery(m_iLogonID, &m_logQuery);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetLogQuery Error!LogonID(%d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetLogQuery Success!LogonID(%d)",m_iLogonID);
	}
}

void CLS_DVRLogPage::OnBnClickedButtonCfgLogdvrFirstpage()
{
	// TODO: Add your control notification handler code here
	if(m_iCurrentPage > 0)
	{
		m_iCurrentPage = 0;
		m_logQuery.iPageNo = m_iCurrentPage;
		int iRet = NetClient_NetLogQuery(m_iLogonID, &m_logQuery);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","NetLogQuery Error!LogonID(%d)",m_iLogonID);
		}
		else
		{
			AddLog(LOG_TYPE_SUCC,"","NetLogQuery Success!LogonID(%d)",m_iLogonID);
		}
	}
}

void CLS_DVRLogPage::OnBnClickedButtonCfgLogdvrPrepage()
{
	// TODO: Add your control notification handler code here
	if(m_iCurrentPage > 0)
	{
		m_iCurrentPage--;
		m_logQuery.iPageNo = m_iCurrentPage;
		int iRet = NetClient_NetLogQuery(m_iLogonID, &m_logQuery);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","NetLogQuery Error!LogonID(%d)",m_iLogonID);
		}
		else
		{
			AddLog(LOG_TYPE_SUCC,"","NetLogQuery Success!LogonID(%d)",m_iLogonID);
		}
	}
}

void CLS_DVRLogPage::OnBnClickedButtonCfgLogdvrNextpage()
{
	// TODO: Add your control notification handler code here
	if(m_iCurrentPage+1 < m_iTotalPages)
	{
		m_iCurrentPage++;
		m_logQuery.iPageNo = m_iCurrentPage;
		int iRet = NetClient_NetLogQuery(m_iLogonID, &m_logQuery);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","NetLogQuery Error!LogonID(%d)",m_iLogonID);
		}
		else
		{
			AddLog(LOG_TYPE_SUCC,"","NetLogQuery Success!LogonID(%d)",m_iLogonID);
		}
		::Sleep(100);
	}
}

void CLS_DVRLogPage::OnBnClickedButtonCfgLogdvrLastpage()
{
	// TODO: Add your control notification handler code here
	if(m_iCurrentPage+1 < m_iTotalPages)
	{
		m_iCurrentPage = m_iTotalPages - 1;
		m_logQuery.iPageNo = m_iCurrentPage;
		int iRet = NetClient_NetLogQuery(m_iLogonID, &m_logQuery);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","NetLogQuery Error!LogonID(%d)",m_iLogonID);
		}
		else
		{
			AddLog(LOG_TYPE_SUCC,"","NetLogQuery Success!LogonID(%d)",m_iLogonID);
		}
	}
}

void CLS_DVRLogPage::UI_UpdateDialog()
{
	InsertColumn(m_ctlListDVRLog,0,IDS_CFG_LOG_DVR_ID,LVCFMT_LEFT,60);
	InsertColumn(m_ctlListDVRLog,1,IDS_CFG_LOG_DVR_CHANNEL,LVCFMT_LEFT,60);
	InsertColumn(m_ctlListDVRLog,2,IDS_CFG_LOG_DVR_LOGTYPE,LVCFMT_LEFT,80);
	InsertColumn(m_ctlListDVRLog,3,IDS_CFG_LOG_DVR_BEGINTIME,LVCFMT_LEFT,130);
	InsertColumn(m_ctlListDVRLog,4,IDS_CFG_LOG_DVR_ACCOUNT,LVCFMT_LEFT,60);
	InsertColumn(m_ctlListDVRLog,5,IDS_CFG_LOG_DVR_LOGCONTENT,LVCFMT_LEFT,300);

	SetDlgItemTextEx(IDC_STATIC_CFG_DVR_LOGTYPE, IDS_CFG_LOG_DVR_LOGTYPE);
	SetDlgItemTextEx(IDC_STATIC_CFG_LOG_DVR_LANGUAGE, IDS_CFG_LOG_DVR_LANGUAGE );
	SetDlgItemTextEx(IDC_STATIC_CFG_LOG_DVR_BEGIN, IDS_CFG_LOG_DVR_BEGIN );
	SetDlgItemTextEx(IDC_STATIC_CFG_LOG_DVR_END, IDS_CFG_LOG_DVR_END);
	SetDlgItemTextEx(IDC_BUTTON_CFG_LOG_DVR_QUERY, IDS_CFG_LOG_DVR_QUERY);
	SetDlgItemTextEx(IDC_STATIC_CFG_LOG_DVR_TOTALLOGS, IDS_CFG_LOG_DVR_LOGTOTALS);
	SetDlgItemTextEx(IDC_STATIC_CFG_LOG_DVR_TOTALPAGES, IDS_CFG_LOG_DVR_LOGPAGES);
	SetDlgItemTextEx(IDC_STATIC_CFG_LOG_DVR_CURRENT, IDS_CFG_LOG_DVR_CURRENTPAGE);
	SetDlgItemTextEx(IDC_BUTTON_CFG_LOGDVR_FIRSTPAGE, IDS_CFG_LOG_DVR_FIRSTPAGE);
	SetDlgItemTextEx(IDC_BUTTON_CFG_LOGDVR_PREPAGE, IDS_CFG_LOG_DVR_PREPAGE);
	SetDlgItemTextEx(IDC_BUTTON_CFG_LOGDVR_NEXTPAGE, IDS_CFG_LOG_DVR_NEXTPAGE);
	SetDlgItemTextEx(IDC_BUTTON_CFG_LOGDVR_LASTPAGE, IDS_CFG_LOG_DVR_LASTPAGE);

	InsertString(m_cboLanguage,0,IDS_CFG_LOG_DVR_ENGLISH);
	InsertString(m_cboLanguage,1,IDS_CFG_LOG_DVR_CHINESE);
	InsertString(m_cboLanguage,2,IDS_CFG_LOG_DVR_CHINESETAIWAN);
	InsertString(m_cboLanguage,3,IDS_CFG_LOG_DVR_KOREAN);
	InsertString(m_cboLanguage,4,IDS_CFG_LOG_DVR_SPANISHECUADOR);
	InsertString(m_cboLanguage,5,IDS_CFG_LOG_DVR_ITALIAN);
	m_cboLanguage.SetCurSel(0);			
	InsertString(m_cboLogType,0,IDS_CFG_LOG_DVR_SYSTEM);
	InsertString(m_cboLogType,1,IDS_CFG_LOG_DVR_WARNING);
	InsertString(m_cboLogType,2,IDS_CFG_LOG_DVR_ALARM);
	InsertString(m_cboLogType,3,IDS_CFG_LOG_DVR_OPERATION);
	InsertString(m_cboLogType,4,IDS_CFG_LOG_DVR_USER);
	InsertString(m_cboLogType,5,IDS_CFG_LOG_DVR_OTHER);
	InsertString(m_cboLogType,6,IDS_CFG_LOG_DVR_ALL);
	m_cboLogType.SetCurSel(6);
}

void CLS_DVRLogPage::UI_UpdateLogCount()
{
	int iTotalCount = 0;
	int iCurrentCount = 0;
	m_ctlListDVRLog.DeleteAllItems();
	int iRet = NetClient_NetLogGetLogCount(m_iLogonID, &iTotalCount, &iCurrentCount);
	if(iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetLogGetLogCount Error!LogonID(%d)",m_iLogonID);
	}
	else
	{
		UpdateLogFiles( iTotalCount, iCurrentCount);
	}
}

void CLS_DVRLogPage::UpdateLogFiles(int _iTotal, int _iCount)
{   
	m_iTotalFiles = _iTotal;
	SetDlgItemInt(IDC_STATIC_CFG_LOGDVR_TOTALLOGS, _iTotal);
	int iTotalPages = (_iTotal/LOG_PAGE_SIZE) + ((_iTotal%LOG_PAGE_SIZE==0)?0:1);
	SetDlgItemInt(IDC_STATIC_CFG_LOGDVR_TOTALPAGES, iTotalPages);
	m_iTotalPages = iTotalPages;
	SetDlgItemInt(IDC_STATIC_CFG_LOGDVR_CURRENTPAGE, m_iCurrentPage + 1);

	for (int i=1; i< m_ctlListDVRLog.GetItemCount(); i++)
	{
		m_ctlListDVRLog.DeleteItem(i);
	}

	NVS_LOG_DATA logInfo = {0};
	for (int i = 0; i < _iCount; i++)
	{
		memset(&logInfo, 0, sizeof(logInfo));

		if(0 == NetClient_NetLogGetLogfile(m_iLogonID, i, &logInfo))
		{
			int iCellID = m_iCurrentPage*LOG_PAGE_SIZE + i+1;
			if (iCellID <= _iTotal)
			{
				CString strCellID;
				CString strChannelNo;
				CString strLogType;
				CString strStartTime;

				int iColumn = 0;
				strCellID.Format("%d", iCellID);
				strChannelNo.Format("%d", logInfo.iChannel);
				m_ctlListDVRLog.InsertItem(i, "", _iCount);
				m_ctlListDVRLog.SetItemText(i, iColumn++, strCellID.GetBuffer());

				if (logInfo.iChannel == 240)//  如果查询得到的Channel为240，则表示为System log，就不显示具体的ChannelID了
				{
					m_ctlListDVRLog.SetItemText(i, iColumn++, "");
				}
				else
				{
					m_ctlListDVRLog.SetItemText(i, iColumn++, strChannelNo);
				}

				if (logInfo.iLogType==0)
				{
					strLogType=GetTextEx(IDS_CFG_LOG_DVR_SYSTEM);
				} 
				else if (logInfo.iLogType==1)
				{
					strLogType=GetTextEx(IDS_CFG_LOG_DVR_WARNING);
				}
				else if (logInfo.iLogType==2)
				{
					strLogType=GetTextEx(IDS_CFG_LOG_DVR_ALARM);
				}
				else if (logInfo.iLogType==3)
				{
					strLogType=GetTextEx(IDS_CFG_LOG_DVR_OPERATION);
				}
				else if (logInfo.iLogType==4)
				{
					strLogType=GetTextEx(IDS_CFG_LOG_DVR_USER);
				}
				else if (logInfo.iLogType==5)
				{
					strLogType=GetTextEx(IDS_CFG_LOG_DVR_ALL);
				}
				else
				{
					strLogType=GetTextEx(IDS_CFG_LOG_DVR_ALL);
				}
				m_ctlListDVRLog.SetItemText(i, iColumn++, strLogType);

				m_ctlListDVRLog.SetItemText(i, iColumn++, TimeToCString(logInfo.struStartTime));

				CString strAccount;
				CString strContent;
				char *pcContent = strstr(logInfo.szLogContent,"@");
				if (pcContent)
				{
					*pcContent = '\0';
					strAccount = logInfo.szLogContent;
					strContent = pcContent+1;
				}
				else
				{
					strContent = logInfo.szLogContent;
				}
				m_ctlListDVRLog.SetItemText(i, iColumn++, strAccount);
				m_ctlListDVRLog.SetItemText(i, iColumn++, strContent);
			}
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","etLogGetLogfile Error!LogonID(%d)",m_iLogonID);
		}
	}
}

CString  CLS_DVRLogPage::TimeToCString(NVS_FILE_TIME _nvsTime)
{
	CString strMsg;
	strMsg.Format("%04d/%02d/%02d-%02d:%02d:%02d", _nvsTime.iYear, _nvsTime.iMonth, _nvsTime.iDay, _nvsTime.iHour, _nvsTime.iMinute, _nvsTime.iSecond);
	return strMsg;
}

void CLS_DVRLogPage::OnMainNotify( int _iLogonID,int _wParam, void* _iLParam, void* _iUser)
{
	int iType = LOWORD(_wParam);
	if (WCM_QUERYLOG_FINISHED == iType)
	{
		UI_UpdateLogCount();
	}
}

void CLS_DVRLogPage::UI_UpdateTimeRange()
{
	SYSTEMTIME BeginDate;
	SYSTEMTIME BeginTime;
	SYSTEMTIME EndDate;
	SYSTEMTIME EndTime;

	GetLocalTime(&BeginDate);
	BeginDate.wDay -= 2;
	GetLocalTime(&BeginTime);
	GetLocalTime(&EndDate);
	GetLocalTime(&EndTime);

	BeginTime.wHour = 0;
	BeginTime.wMinute = 0;
	BeginTime.wSecond = 0;

	EndTime.wHour = 23;
	EndTime.wMinute = 59;
	EndTime.wSecond = 59;

	m_dtpBeginDate.SetTime(&BeginDate);
	m_dtpBeginTime.SetTime(&BeginTime);
	m_dtpEndDate.SetTime(&EndDate);
	m_dtpEndTime.SetTime(&EndTime);
}
