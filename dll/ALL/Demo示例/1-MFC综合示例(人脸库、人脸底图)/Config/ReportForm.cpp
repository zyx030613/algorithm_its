// ReportForm.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ReportForm.h"


// CLS_ReportForm dialog

IMPLEMENT_DYNAMIC(CLS_ReportForm, CDialog)

CLS_ReportForm::CLS_ReportForm(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ReportForm::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNo = 0;
}

CLS_ReportForm::~CLS_ReportForm()
{
}

void CLS_ReportForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MAIN_FUNC_TYPE, m_cboMainFuncType);
	DDX_Control(pDX, IDC_COMBO_SUB_FUNC_TYPE, m_cboSubFuncType);
	DDX_Control(pDX, IDC_COMBO_FORM_TYPE, m_cboFormType);
	DDX_Control(pDX, IDC_EDIT_FUNC_ABILITY_LEVEL, m_edtFuncAbility);
	DDX_Control(pDX, IDC_EDIT_TOTAL_NUM, m_edtTotalNum);
	DDX_Control(pDX, IDC_EDIT_CURRENT_NUM, m_edtCurrentNum);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BEGIN_DATE, m_dtpBeginDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BEGIN_TIME, m_dtpBeginTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END_DATE, m_dtpEndDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END_TIME, m_dtpEndTime);
	DDX_Control(pDX, IDC_LIST_REPORT_FORM, m_lstReportForm);
}


BEGIN_MESSAGE_MAP(CLS_ReportForm, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_MAIN_FUNC_TYPE, &CLS_ReportForm::OnCbnSelchangeComboMainFuncType)
	ON_CBN_SELCHANGE(IDC_COMBO_SUB_FUNC_TYPE, &CLS_ReportForm::OnCbnSelchangeComboSubFuncType)
	ON_CBN_SELCHANGE(IDC_COMBO_FORM_TYPE, &CLS_ReportForm::OnCbnSelchangeComboFormType)
END_MESSAGE_MAP()


// CLS_ReportForm message handlers

BOOL CLS_ReportForm::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_lstReportForm.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	UI_UpdateDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_ReportForm::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo < 0 ? 0 :_iChannelNo;
	m_iStreamNo = _iStreamNo <0 ? 0 :_iStreamNo;

	UI_UpdateReportForm();
	UI_UpdateFuncAbilityLevel();
}

void CLS_ReportForm::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
	UI_UpdateReportForm();
	UI_UpdateFuncAbilityLevel();
}

void CLS_ReportForm::UI_UpdateDialog()
{
	InsertColumn(m_lstReportForm, 0, "ID", LVCFMT_LEFT, 80);
	InsertColumn(m_lstReportForm, 1, "Channel Num", LVCFMT_LEFT, 80);
	InsertColumn(m_lstReportForm, 2, "Enter Person", LVCFMT_LEFT, 100);
	InsertColumn(m_lstReportForm, 3, "Leave Person", LVCFMT_LEFT, 100);
	InsertColumn(m_lstReportForm, 4, "Occur Time", LVCFMT_LEFT, 220);

	SYSTEMTIME BeginDate;
	SYSTEMTIME BeginTime;
	SYSTEMTIME EndDate;
	SYSTEMTIME EndTime;
	GetLocalTime(&BeginDate);
	BeginDate.wDay -= 2;
	GetLocalTime(&BeginTime);
	GetLocalTime(&EndDate);
	GetLocalTime(&EndTime);
	m_dtpBeginDate.SetTime(&BeginDate);
	m_dtpBeginTime.SetTime(&BeginTime);
	m_dtpEndDate.SetTime(&EndDate);
	m_dtpEndTime.SetTime(&EndTime);

	m_cboMainFuncType.AddString("Transcording");
	m_cboMainFuncType.SetItemData(0, MAIN_FUNC_TYPE_TRANSCODING);
	m_cboMainFuncType.AddString("DDNS Service");
	m_cboMainFuncType.SetItemData(1, MAIN_FUNC_TYPE_DDNSSERVICE);
	m_cboMainFuncType.AddString("Report Form");
	m_cboMainFuncType.SetItemData(2, MAIN_FUNC_TYPE_FORMREPORT);
	m_cboMainFuncType.SetCurSel(0);

	m_cboSubFuncType.AddString("default");
	m_cboSubFuncType.SetCurSel(0);
	
	m_cboFormType.AddString("default");
	m_cboFormType.AddString("hour");
	m_cboFormType.AddString("day");
	m_cboFormType.AddString("month");
	m_cboFormType.AddString("year");
	m_cboFormType.SetCurSel(0);

	m_edtFuncAbility.SetLimitText(1024);
	m_edtTotalNum.SetLimitText(32);
	m_edtCurrentNum.SetLimitText(32);
}

void CLS_ReportForm::OnMainNotify( int _iLogonID,int _wParam, int _lParam,int _iUserData )
{
	int iType = LOWORD(_wParam);
	if (WCM_QUERY_REPORT_FORM == iType)
	{
		UI_UpdateReportForm();
	}
}

void CLS_ReportForm::UI_UpdateReportForm()
{
	m_lstReportForm.DeleteAllItems();

	int iCmd = COMMAND_ID_QUERY_REPORT;
	ReportFormResult tResult = {0};
	tResult.iSize = sizeof(ReportFormResult);
	int iRet = NetClient_RecvCommand(m_iLogonID, iCmd, m_iChannelNo, &tResult, sizeof(ReportFormResult));
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_TOTAL_NUM, tResult.iTotalNum);
		SetDlgItemInt(IDC_EDIT_CURRENT_NUM, tResult.iCurrentNum);
		if (tResult.iCurrentNum > 0)
		{
			for (int i = 0; i < tResult.iCurrentNum; i++)
			{
				CString cstrID;
				CString cstrChannelNo;
				CString cstrEnterPerson;
				CString cstrLeavePerson;
				CString cstrOccurTime;

				int iColumn = 0;
				cstrID.Format("%d", i);
				cstrChannelNo.Format("%d", tResult.tReport[i].iChannelNo);
				cstrEnterPerson.Format("%d", tResult.tReport[i].iPushPersonNum);
				cstrLeavePerson.Format("%d", tResult.tReport[i].iPopPersonNum);
				cstrOccurTime.Format("%04d/%02d/%02d-%02d:%02d:%02d"
					, tResult.tReport[i].tOccurTime.iYear
					, tResult.tReport[i].tOccurTime.iMonth
					, tResult.tReport[i].tOccurTime.iDay
					, tResult.tReport[i].tOccurTime.iHour
					, tResult.tReport[i].tOccurTime.iMinute
					, tResult.tReport[i].tOccurTime.iSecond);

				m_lstReportForm.InsertItem(i, "", tResult.iCurrentNum);
				m_lstReportForm.SetItemText(i, iColumn++, cstrID);
				m_lstReportForm.SetItemText(i, iColumn++, cstrChannelNo);
				m_lstReportForm.SetItemText(i, iColumn++, cstrEnterPerson);
				m_lstReportForm.SetItemText(i, iColumn++, cstrLeavePerson);
				m_lstReportForm.SetItemText(i, iColumn++, cstrOccurTime);
			}
		}
		AddLog(LOG_TYPE_SUCC, "", "NetClient_RecvCommand (%d)",iCmd);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_RecvCommand (%d)",iCmd);
	}

}

void CLS_ReportForm::UI_UpdateFuncAbilityLevel()
{
	int iCmd = NET_CLIENT_GET_FUNC_ABILITY;
	FuncAbilityLevel tFunc = {0};
	tFunc.iSize = sizeof(FuncAbilityLevel);
	int iIndex = m_cboMainFuncType.GetCurSel();
	tFunc.iMainFuncType = m_cboMainFuncType.GetItemData(iIndex);
	tFunc.iSubFuncType = m_cboSubFuncType.GetCurSel();
	int iBytesReturn = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, iCmd, m_iChannelNo, &tFunc, sizeof(FuncAbilityLevel), &iBytesReturn);
	if (0 == iRet)
	{
		m_edtFuncAbility.SetWindowText(tFunc.cParam);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetDevConfig (%d)",iCmd);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig (%d)",iCmd);
	}
}

void CLS_ReportForm::OnCbnSelchangeComboMainFuncType()
{
	// TODO: Add your control notification handler code here
	UI_UpdateFuncAbilityLevel();

}

void CLS_ReportForm::OnCbnSelchangeComboSubFuncType()
{
	// TODO: Add your control notification handler code here
	UI_UpdateFuncAbilityLevel();
}

void CLS_ReportForm::OnCbnSelchangeComboFormType()
{
	// TODO: Add your control notification handler code here
	int iCmd = COMMAND_ID_QUERY_REPORT;
	QueryReportForm tQuery = {0};
	tQuery.iSize = sizeof(QueryReportForm);
	tQuery.iFormType = m_cboFormType.GetCurSel();
	SYSTEMTIME BeginDate;
	SYSTEMTIME BeginTime;
	SYSTEMTIME EndDate;
	SYSTEMTIME EndTime;
	m_dtpBeginDate.GetTime(&BeginDate);
	tQuery.tBeginTime.iYear = BeginDate.wYear;
	tQuery.tBeginTime.iMonth = BeginDate.wMonth;
	tQuery.tBeginTime.iDay = BeginDate.wDay;
	m_dtpBeginTime.GetTime(&BeginTime);
	tQuery.tBeginTime.iHour = BeginTime.wHour;
	tQuery.tBeginTime.iMinute = BeginTime.wMinute;
	tQuery.tBeginTime.iSecond = BeginTime.wSecond;
	m_dtpEndDate.GetTime(&EndDate);
	tQuery.tEndTime.iYear = EndDate.wYear;
	tQuery.tEndTime.iMonth = EndDate.wMonth;
	tQuery.tEndTime.iDay = EndDate.wDay;
	m_dtpEndTime.GetTime(&EndTime);
	tQuery.tEndTime.iHour = EndTime.wHour;
	tQuery.tEndTime.iMinute = EndTime.wMinute;
	tQuery.tEndTime.iSecond = EndTime.wSecond;

	int iRet = NetClient_SendCommand(m_iLogonID, iCmd, m_iChannelNo, &tQuery, sizeof(QueryReportForm));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SendCommand (%d)",iCmd);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SendCommand (%d)",iCmd);
	}
}
