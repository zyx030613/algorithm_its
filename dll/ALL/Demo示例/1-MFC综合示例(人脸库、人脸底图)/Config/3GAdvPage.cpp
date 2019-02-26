// 3GAdvPage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "3GAdvPage.h"


// CLS_3GAdvPage dialog

IMPLEMENT_DYNAMIC(CLS_3GAdvPage, CDialog)

CLS_3GAdvPage::CLS_3GAdvPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_3GAdvPage::IDD, pParent)
{

}

CLS_3GAdvPage::~CLS_3GAdvPage()
{
	m_iLogonID = -1;
}

void CLS_3GAdvPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_3GADV_BEGIN, m_dtp3GTaskScheduleStart);
	DDX_Control(pDX, IDC_DATETIMEPICKER_3GADV_END, m_dtp3GTaskScheduleStop);
	DDX_Control(pDX, IDC_CHECK_3GADV_TASKSCHEDULE, m_chk3GTaskScheduleEnable);
	DDX_Control(pDX, IDC_COMBO_3GADV_NOTIFYTYPE, m_cbo3GNotifyType);
	DDX_Control(pDX, IDC_EDIT_3GADV_NOTIFYMESSAGR, m_edt3GNotifyMessage);
	DDX_Control(pDX, IDC_EDIT_3GADV_DIALNUMBER, m_edtDialNumber);
	DDX_Control(pDX, IDC_EDIT_3GADV_ACCOUNTER, m_edtAccounter);
	DDX_Control(pDX, IDC_EDIT_3GADV_PASSWORD, m_edtPassword);
}


BEGIN_MESSAGE_MAP(CLS_3GAdvPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_3GADV_TIMESET, &CLS_3GAdvPage::OnBnClickedButton3GADVTimeSet)
	ON_BN_CLICKED(IDC_BUTTON_3GADV_NOTIFYSET, &CLS_3GAdvPage::OnBnClickedButton3GADVNotifySet)
	ON_BN_CLICKED(IDC_BUTTON_3GADV_VPDNSET, &CLS_3GAdvPage::OnBnClickedButton3GADVVpdnSet)
	ON_BN_CLICKED(IDC_CHECK_3GADV_TASKSCHEDULE, &CLS_3GAdvPage::OnBnClickedCheck3GADVTaskSchedule)
END_MESSAGE_MAP()

void CLS_3GAdvPage::OnChannelChanged( int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;
	if (m_iLogonID < 0)
	{
		return;
	}
	UI_Update3GADVInfo();
}

void CLS_3GAdvPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

// CLS_3GAdvPage message handlers

void CLS_3GAdvPage::OnBnClickedButton3GADVTimeSet()
{
	// TODO: Add your control notification handler code here
	int iEnable = (m_chk3GTaskScheduleEnable.GetCheck() == BST_CHECKED)?1:0;
	NVS_SCHEDTIME timeSeg1;
	memset(&timeSeg1,0,sizeof(NVS_SCHEDTIME));
	SYSTEMTIME StartTime = {0};
	SYSTEMTIME StopTime = {0};
	memset(&StartTime, 0, sizeof(StartTime));
	memset(&StopTime, 0, sizeof(StopTime));
	m_dtp3GTaskScheduleStart.GetTime(&StartTime);
	m_dtp3GTaskScheduleStop.GetTime(&StopTime);
	timeSeg1.iStartHour = StartTime.wHour;
	timeSeg1.iStartMin = StartTime.wMinute;
	timeSeg1.iStopHour = StopTime.wHour;
	timeSeg1.iStopMin = StopTime.wMinute;
	
	int iStart = timeSeg1.iStartHour*60+timeSeg1.iStartMin;
	int iStop = timeSeg1.iStopHour*60+timeSeg1.iStopMin;
	if (0 != (iStart+iStop) && iStart >= iStop)
	{
		AddLog(LOG_TYPE_MSG,"","start time(%2d:%2d) collide with stop time(%2d:%2d)"
			,timeSeg1.iStartHour,timeSeg1.iStartMin,timeSeg1.iStopHour,timeSeg1.iStopMin);
		return;
	}

	NVS_SCHEDTIME* schedule = &timeSeg1;
	if (NetClient_Set3GTaskSchedule)
	{
		int iRet = NetClient_Set3GTaskSchedule(m_iLogonID,iEnable,schedule);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","Set3GTaskSchedule Error!LogonID(%d), Error(0x%08x)",m_iLogonID,::GetLastError());
		} 
		else
		{
			AddLog(LOG_TYPE_SUCC,"","Set3GTaskSchedule Success!LogonID(%d)",m_iLogonID);
		}
	}
}

void CLS_3GAdvPage::OnBnClickedButton3GADVNotifySet()
{
	// TODO: Add your control notification handler code here
	//int iIndex = GetLogonID(edtIP1->Text,edtProID->Text,edtServerPort->Text.ToIntDef(3000));
	CString strNotifyMessage;
	m_edt3GNotifyMessage.GetWindowText(strNotifyMessage);
	if (NetClient_Set3GNotify)
	{
		int iRet = NetClient_Set3GNotify(m_iLogonID,m_cbo3GNotifyType.GetCurSel(),(LPSTR)(LPCTSTR)strNotifyMessage);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","Set3GNotify Error!LogonID(%d), Error(0x%08x)",m_iLogonID,::GetLastError());
		} 
		else
		{
			AddLog(LOG_TYPE_SUCC,"","Set3GNotify Success!LogonID(%d)",m_iLogonID);
		}
	}
}

void CLS_3GAdvPage::OnBnClickedButton3GADVVpdnSet()
{
	// TODO: Add your control notification handler code here
	CString strDialNumber;
	CString strAccounnter;
	CString strPassword;
	m_edtDialNumber.GetWindowText(strDialNumber);
	m_edtAccounter.GetWindowText(strAccounnter);
	m_edtPassword.GetWindowText(strPassword);
	if (NetClient_Set3GVPND)
	{
		int iRet = NetClient_Set3GVPND(m_iLogonID,(LPSTR)(LPCTSTR)strDialNumber,(LPSTR)(LPCTSTR)strAccounnter,(LPSTR)(LPCTSTR)strPassword);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_Set3GVPND Error!LogonID(%d), Error(0x%08x)",m_iLogonID,::GetLastError());
		} 
		else
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_Set3GVPND Success!LogonID(%d)",m_iLogonID);
		}
	}
}

BOOL CLS_3GAdvPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_cbo3GNotifyType.AddString(_T("no notification"));
	m_cbo3GNotifyType.AddString(_T("notify after success"));
	m_cbo3GNotifyType.AddString(_T("notify after failure"));

	m_edt3GNotifyMessage.SetLimitText(63);
	m_edtDialNumber.SetLimitText(23);
	m_edtAccounter.SetLimitText(23);
	m_edtPassword.SetLimitText(23);

	m_dtp3GTaskScheduleStart.SetFormat("HH:mm");
	m_dtp3GTaskScheduleStop.SetFormat("HH:mm");

	m_cbo3GNotifyType.SetCurSel(0);

	SYSTEMTIME StartTime = {0};
	SYSTEMTIME StopTime = {0};
	m_dtp3GTaskScheduleStart.SetTime(&StartTime);
	m_dtp3GTaskScheduleStop.SetTime(&StopTime);

	UI_UpdateDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_3GAdvPage::OnBnClickedCheck3GADVTaskSchedule()
{
	// TODO: Add your control notification handler code here
	if (BST_CHECKED == m_chk3GTaskScheduleEnable.GetCheck())
	{
		m_dtp3GTaskScheduleStart.EnableWindow(TRUE);
		m_dtp3GTaskScheduleStop.EnableWindow(TRUE);
	}
	else
	{
// 		SYSTEMTIME StartTime = {0};
// 		SYSTEMTIME StopTime = {0};
// 		GetLocalTime(&StartTime);
// 		GetLocalTime(&StopTime);
// 		m_dtp3GTaskScheduleStart.SetTime(&StartTime);
// 		m_dtp3GTaskScheduleStop.SetTime(&StopTime);
		m_dtp3GTaskScheduleStart.EnableWindow(FALSE);
		m_dtp3GTaskScheduleStop.EnableWindow(FALSE);
	}
}

void CLS_3GAdvPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_3GADV_TASKSCHEDULE, IDS_CFG_3G_ADV_TASKSCHEDULE);
	SetDlgItemTextEx(IDC_CHECK_3GADV_TASKSCHEDULE, IDS_CFG_3G_ADV_SCHEDULEENABLE);
	SetDlgItemTextEx(IDC_STATIC_3GADV_TIME, IDS_CFG_3G_ADV_TASKTIME);
	SetDlgItemTextEx(IDC_BUTTON_3GADV_TIMESET, IDS_CFG_3G_ADV_TIMESET);
	SetDlgItemTextEx(IDC_STATIC_3GADV_NOTIFY, IDS_CFG_3G_ADV_NOTIFT);
	SetDlgItemTextEx(IDC_STATIC_3GADV_NOTIFYTYPE, IDS_CFG_3G_ADV_NOTIFYTYPE);
	SetDlgItemTextEx(IDC_STATIC_3GADV_NOTIFYMESSAGE, IDS_CFG_3G_ADV_NOTIFYMESSAGE);
	SetDlgItemTextEx(IDC_BUTTON_3GADV_NOTIFYSET, IDS_CFG_3G_ADV_NOTIFYSET);
	SetDlgItemTextEx(IDC_STATIC_3GADV_VPDN, IDS_CFG_3G_ADV_VPDN);
	SetDlgItemTextEx(IDC_STATIC_3GADV_DIALNUMBER, IDS_CFG_3G_ADV_DIALNUMBER);
	SetDlgItemTextEx(IDC_STATIC_3GADV_ACCOUNTER, IDS_CFG_3G_ADV_ACCOUNTER);
	SetDlgItemTextEx(IDC_STATIC_3GADV_PASSWORD, IDS_CFG_3G_ADV_PASSWORD);
	SetDlgItemTextEx(IDC_BUTTON_3GADV_VPDNSET, IDS_CFG_3G_ADV_VPDNSET);
}

void CLS_3GAdvPage::UI_Update3GADVInfo()
{
	int iEnable = -1;
	NVS_SCHEDTIME schedule;

	if (NetClient_Get3GTaskSchedule && NetClient_Get3GTaskSchedule(m_iLogonID, &iEnable,&schedule) == 0)
	{
		m_chk3GTaskScheduleEnable.SetCheck(iEnable);
		if (BST_CHECKED == m_chk3GTaskScheduleEnable.GetCheck())
		{
			m_dtp3GTaskScheduleStart.EnableWindow(TRUE);
			m_dtp3GTaskScheduleStop.EnableWindow(TRUE);
		}
		else
		{
			m_dtp3GTaskScheduleStart.EnableWindow(FALSE);
			m_dtp3GTaskScheduleStop.EnableWindow(FALSE);
		}
		CTime clsStartTime(1971,1,1,schedule.iStartHour,schedule.iStartMin,0);
		CTime clsStopTime(1971,1,1,schedule.iStopHour,schedule.iStopMin,0);
		m_dtp3GTaskScheduleStart.SetTime(&clsStartTime);
		m_dtp3GTaskScheduleStop.SetTime(&clsStopTime);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","Get3GTaskSchedule Error!LogonID(%d), Error(0x%08x)",m_iLogonID,::GetLastError());
	}

	int iIndex = -1;
	char cNotifyMessage[64] = {0};
	if (NetClient_Get3GNotify && NetClient_Get3GNotify(m_iLogonID, &iIndex, cNotifyMessage) == 0)
	{
		m_cbo3GNotifyType.SetCurSel(iIndex);
		m_edt3GNotifyMessage.SetWindowText(cNotifyMessage);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","Get3GNotify Error!LogonID(%d), Error(0x%08x)",m_iLogonID,::GetLastError());
	}

	char cDialNumber[32] = {0};
	char cAccounter[32] = {0};
	char cPassWord[32] = {0};
	if(NetClient_Get3GVPND && NetClient_Get3GVPND(m_iLogonID,cDialNumber,cAccounter,cPassWord) == 0)
	{
		m_edtDialNumber.SetWindowText(cDialNumber);
		m_edtAccounter.SetWindowText(cAccounter);
		m_edtPassword.SetWindowText(cPassWord);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_Get3GVPN Error!LogonID(%d), Error(0x%08x)",m_iLogonID,::GetLastError());
	}
}
