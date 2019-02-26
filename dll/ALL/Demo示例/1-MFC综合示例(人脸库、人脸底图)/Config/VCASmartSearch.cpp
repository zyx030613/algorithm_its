// VCASmartSearch.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCASmartSearch.h"
#include "Common/CommonFun.h"

#define STATEMENT_TYPE_DAY			0			//日报表
#define STATEMENT_TYPE_WEEK			1			//周报表
#define STATEMENT_TYPE_MONTH		2			//月报表
#define STATEMENT_TYPE_YEAR			3			//年报表


// CLS_VCASmartSearch 对话框

IMPLEMENT_DYNAMIC(CLS_VCASmartSearch, CDialog)

CLS_VCASmartSearch::CLS_VCASmartSearch(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_VCASmartSearch::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNo = 0;
}

CLS_VCASmartSearch::~CLS_VCASmartSearch()
{
}

void CLS_VCASmartSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_VCA_SEARCH_STATEMENT, m_lstctrlStatement);
	DDX_Control(pDX, IDC_CBO_VCA_SEARCH_STATEMENT_TYPE, m_cboStatementType);
	DDX_Control(pDX, IDC_DTP_VCA_SEARCH_STATISTICS_TIME, m_dtpStatTime);
}


BEGIN_MESSAGE_MAP(CLS_VCASmartSearch, CDialog)
	ON_BN_CLICKED(IDC_BTN_VCA_SEARCH_EXPORT, &CLS_VCASmartSearch::OnBnClickedBtnVcaSearchExport)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CLS_VCASmartSearch 消息处理程序


BOOL CLS_VCASmartSearch::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	UpdateUIText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLS_VCASmartSearch::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
}

void CLS_VCASmartSearch::OnLanguageChanged( int _iLanguage )
{
	UpdateUIText();
}

void CLS_VCASmartSearch::OnChannelChanged(int _iLogonID, int _iChannelNo, int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = (_iChannelNo < 0) ? FLAG_QUERY_ALL_CHANNEL : _iChannelNo;
	m_iStreamNo = _iStreamNo;
}


void CLS_VCASmartSearch::UpdateUIText()
{
	SetDlgItemTextEx(IDC_STC_VCA_SEARCH_STATEMENT_TYPE, IDS_VCA_STATEMENT_TYPE);
	SetDlgItemTextEx(IDC_STC_VCA_SEARCH_STATISTICS_TIME, IDS_VCA_STATISTICS_TIME);
	SetDlgItemTextEx(IDC_BTN_VCA_SEARCH_EXPORT, IDS_VCA_EXPORT);

	m_cboStatementType.ResetContent();
	const CString cstType[] = {
		GetTextEx(IDS_VCA_STATEMENT_TYPE_DAY),
		GetTextEx(IDS_VCA_STATEMENT_TYPE_WEEK),
		GetTextEx(IDS_VCA_STATEMENT_TYPE_MONTH),
		GetTextEx(IDS_VCA_STATEMENT_TYPE_YEAR)
	};
	int iIndex = 0;
	iIndex = m_cboStatementType.AddString(cstType[0]);
	m_cboStatementType.SetItemData(iIndex, REPORT_FORM_TYPE_HOUR);
	iIndex = m_cboStatementType.AddString(cstType[1]);
	m_cboStatementType.SetItemData(iIndex, REPORT_FORM_TYPE_DAY);
	iIndex = m_cboStatementType.AddString(cstType[2]);
	m_cboStatementType.SetItemData(iIndex, REPORT_FORM_TYPE_DAY);
	iIndex = m_cboStatementType.AddString(cstType[3]);
	m_cboStatementType.SetItemData(iIndex, REPORT_FORM_TYPE_MONTH);
	m_cboStatementType.SetCurSel(0);

	m_lstctrlStatement.DeleteAllItems();
	for(int i = E_STATEMENT_SUM - 1; i >= 0; i--)
	{
		m_lstctrlStatement.DeleteColumn(i);
	}
	m_lstctrlStatement.InsertColumn(E_STATEMENT_FIRST, GetTextEx(IDS_CONFIG_DNVR_ALMSCH_CHANNELNO), LVCFMT_CENTER, 110);
	m_lstctrlStatement.InsertColumn(E_STATEMENT_SECOND, GetTextEx(IDS_VCA_PUSH_PERSON_NUM), LVCFMT_CENTER, 110);
	m_lstctrlStatement.InsertColumn(E_STATEMENT_THIRD, GetTextEx(IDS_VCA_POP_PERSON_NUM), LVCFMT_CENTER, 110);
	m_lstctrlStatement.InsertColumn(E_STATEMENT_FOUTH, GetTextEx(IDS_VCA_OCCUR_TIME), LVCFMT_CENTER, 130);

	m_lstctrlStatement.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);	
}

void CLS_VCASmartSearch::OnBnClickedBtnVcaSearchExport()
{
	if (m_iLogonID < 0 || m_iChannelNo < 0)
	{
		AddLog(LOG_TYPE_MSG,"","CLS_VCASmartSearch::Invalid logon id(%d), channel no(%d)", m_iLogonID, m_iChannelNo);
	}

	//获取当前时间，根据报表类型，构造起始终止时间
	COleDateTime time;
	m_dtpStatTime.GetTime(time);
	CTimeSpan ts(0, 0, 0, 1); //n= 一定的天数

	QueryReportForm ReportPara;
	memset(&ReportPara, 0, sizeof(QueryReportForm));
	ReportPara.iSize = sizeof(ReportPara);
	ReportPara.iFormType = (int)m_cboStatementType.GetItemData(m_cboStatementType.GetCurSel());

	// 年报表
	if (STATEMENT_TYPE_YEAR == m_cboStatementType.GetCurSel())
	{
		ReportPara.tBeginTime.iYear = time.GetYear();
		ReportPara.tBeginTime.iMonth = 1;
		ReportPara.tBeginTime.iDay = 1;
		ReportPara.tBeginTime.iHour = 0;
		ReportPara.tBeginTime.iMinute = 0;
		ReportPara.tBeginTime.iSecond = 0;

		ReportPara.tEndTime.iYear = time.GetYear();
		ReportPara.tEndTime.iMonth = 12;
		ReportPara.tEndTime.iDay = 31;
		ReportPara.tEndTime.iHour = 23;
		ReportPara.tEndTime.iMinute = 59;
		ReportPara.tEndTime.iSecond = 59;
	}
	// 月报表
	else if (STATEMENT_TYPE_MONTH == m_cboStatementType.GetCurSel())
	{
		ReportPara.tBeginTime.iYear = time.GetYear();
		ReportPara.tBeginTime.iMonth = time.GetMonth();
		ReportPara.tBeginTime.iDay = 1;
		ReportPara.tBeginTime.iHour = 0;
		ReportPara.tBeginTime.iMinute = 0;
		ReportPara.tBeginTime.iSecond = 0;

		//特殊处理12月份
		int iYear = time.GetYear();
		int iMonth = time.GetMonth();
		if (time.GetMonth() < 12)
		{
			iMonth += 1; 
		}
		else
		{
			iYear += 1;
			iMonth = 1;
		}
		CTime temptime(iYear,iMonth,1,0,0,0);
		temptime = temptime - ts;

		ReportPara.tEndTime.iYear = temptime.GetYear();
		ReportPara.tEndTime.iMonth = temptime.GetMonth();
		ReportPara.tEndTime.iDay = temptime.GetDay();
		ReportPara.tEndTime.iHour = temptime.GetHour();
		ReportPara.tEndTime.iMinute = temptime.GetMinute();
		ReportPara.tEndTime.iSecond = temptime.GetSecond();
	}
	// 周报表
	else if (STATEMENT_TYPE_WEEK == m_cboStatementType.GetCurSel())
	{
		CTime MyStartTime(time.GetYear(),time.GetMonth(),time.GetDay(),0,0,0);
		int iIndexofweek = time.GetDayOfWeek();
		//用周一作为一周的开始计算
		iIndexofweek = (iIndexofweek == 1) ? 6 : (iIndexofweek - 2);
		CTimeSpan wkts(iIndexofweek, 0, 0, 0);
		MyStartTime = MyStartTime - wkts; 

		ReportPara.tBeginTime.iYear   = MyStartTime.GetYear();
		ReportPara.tBeginTime.iMonth  = MyStartTime.GetMonth();
		ReportPara.tBeginTime.iDay    = MyStartTime.GetDay();
		ReportPara.tBeginTime.iHour   = 0;
		ReportPara.tBeginTime.iMinute = 0;
		ReportPara.tBeginTime.iSecond = 0;

		CTimeSpan endts(-7,0,0,1);
		MyStartTime = MyStartTime - endts;
		ReportPara.tEndTime.iYear   = MyStartTime.GetYear();
		ReportPara.tEndTime.iMonth  = MyStartTime.GetMonth();
		ReportPara.tEndTime.iDay    = MyStartTime.GetDay();
		ReportPara.tEndTime.iHour   = MyStartTime.GetHour();
		ReportPara.tEndTime.iMinute = MyStartTime.GetMinute();
		ReportPara.tEndTime.iSecond = MyStartTime.GetSecond();
	}
	// 日报表
	else if (STATEMENT_TYPE_DAY == m_cboStatementType.GetCurSel())
	{
		ReportPara.tBeginTime.iYear   = time.GetYear();
		ReportPara.tBeginTime.iMonth  = time.GetMonth();
		ReportPara.tBeginTime.iDay    = time.GetDay();
		ReportPara.tBeginTime.iHour   = 0;
		ReportPara.tBeginTime.iMinute = 0;
		ReportPara.tBeginTime.iSecond = 0;

		ReportPara.tEndTime.iYear   = time.GetYear();
		ReportPara.tEndTime.iMonth  = time.GetMonth();
		ReportPara.tEndTime.iDay    = time.GetDay();
		ReportPara.tEndTime.iHour   = 23;
		ReportPara.tEndTime.iMinute = 59;
		ReportPara.tEndTime.iSecond = 59;
	}
	else
	{
		return;
	}

	// 发送命令，获取统计信息
	int iRet = NetClient_SendCommand(m_iLogonID, COMMAND_ID_QUERY_REPORT, m_iChannelNo, &ReportPara, sizeof(ReportPara));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCASmartSearch::NetClient_SendCommand[COMMAND_ID_QUERY_REPORT] (%d, %d), error (%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCASmartSearch::NetClient_SendCommand[COMMAND_ID_QUERY_REPORT] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
}

void CLS_VCASmartSearch::WriteResult(ReportFormResult _ReportResult)
{
	int iCurrentNum = _ReportResult.iCurrentNum;
	if (iCurrentNum < 0 || iCurrentNum > MAX_ONCE_FORM_REPORT_NUM)
	{
		return;
	}
	else
	{
		for (int i = 0; i < iCurrentNum; i++)
		{
			int iItemCount = m_lstctrlStatement.GetItemCount();
			int iColumn = 0;

			CString cstChannelNo = "";
			cstChannelNo.Format(_T("%d"), _ReportResult.tReport[i].iChannelNo + 1);

			CString cstPushPersonNum = "";
			cstPushPersonNum.Format(_T("%d"), _ReportResult.tReport[i].iPushPersonNum);

			CString cstPopPersonNum = "";
			cstPopPersonNum.Format(_T("%d"), _ReportResult.tReport[i].iPopPersonNum);

			CString cstTime = "";
			cstTime = FormatTime(_ReportResult.iFormType, _ReportResult.tReport[i].tOccurTime);

			m_lstctrlStatement.SetItemText(iItemCount, iColumn++, cstChannelNo);
			m_lstctrlStatement.SetItemText(iItemCount, iColumn++, cstPushPersonNum);
			m_lstctrlStatement.SetItemText(iItemCount, iColumn++, cstPopPersonNum);
			m_lstctrlStatement.SetItemText(iItemCount, iColumn++, cstTime);
		}
	}
}

CString CLS_VCASmartSearch::FormatTime(int _iType, NVS_FILE_TIME _Time)
{
	CString cstTime = "";
	if (_iType == REPORT_FORM_TYPE_MONTH)
	{
		cstTime.Format(_T("%04d%s%02d%s"),_Time.iYear,GetText(IDS_VCA_YEAR),_Time.iMonth,GetText(IDS_VCA_MONTH));
	}
	else if (_iType == REPORT_FORM_TYPE_DAY)
	{
		cstTime.Format(_T("%04d/%02d/%02d"),_Time.iYear,_Time.iMonth,_Time.iDay);
	}
	else if (_iType == REPORT_FORM_TYPE_HOUR)
	{
		cstTime.Format(_T("%04d/%02d/%02d %02d:%02d:%02d"),_Time.iYear,_Time.iMonth,
			_Time.iDay,_Time.iHour + 1,_Time.iMinute,_Time.iSecond);
	}
	else
	{
		cstTime.Format(_T("%04d/%02d/%02d %02d:%02d:%02d"),_Time.iYear,_Time.iMonth,
			_Time.iDay,_Time.iHour + 1,_Time.iMinute,_Time.iSecond);
	}
	return cstTime;
}

void CLS_VCASmartSearch::OnMainNotify(int _ulLogonID, int _iWparam, void* _iLParam, void* _iUser)
{
	if (_ulLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","CLS_VCASmartSearch::Invalid logon id(%d)",_ulLogonID);
		return;
	}

	int iMessage = _iWparam;
	switch (iMessage)
	{
	case WCM_QUERY_REPORT_FORM:
		{
			ReportFormResult tReportResult;
			memset(&tReportResult, 0, sizeof(ReportFormResult));
			int iRet = NetClient_RecvCommand(m_iLogonID, COMMAND_ID_QUERY_REPORT, m_iChannelNo, &tReportResult, sizeof(tReportResult));
			if (iRet < 0)
			{
				AddLog(LOG_TYPE_FAIL,"","CLS_VCASmartSearch::NetClient_RecvCommand[COMMAND_ID_QUERY_REPORT] (%d, %d), error (%d)", m_iLogonID, m_iChannelNo, GetLastError());
			}
			else
			{
				WriteResult(tReportResult);
				AddLog(LOG_TYPE_SUCC,"","CLS_VCASmartSearch::NetClient_RecvCommand[COMMAND_ID_QUERY_REPORT] (%d, %d)", m_iLogonID, m_iChannelNo);
			}
		}
		break;
	default:
		break;
	}
}

