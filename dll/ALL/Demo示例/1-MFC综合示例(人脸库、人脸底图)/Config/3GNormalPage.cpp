// 3GNormalPage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "3GNormalPage.h"


// CLS_3GNormalPage dialog

IMPLEMENT_DYNAMIC(CLS_3GNormalPage, CDialog)

CLS_3GNormalPage::CLS_3GNormalPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_3GNormalPage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_3GNormalPage::~CLS_3GNormalPage()
{
}

void CLS_3GNormalPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_3GNORMAL_TYPE, m_cboDeviceType);
	DDX_Control(pDX, IDC_COMBO_3GNORMAL_STATUS, m_cboDeviceStatus);
	DDX_Control(pDX, IDC_EDIT_3GNORMAL_IP, m_edtDeviceIP);
	DDX_Control(pDX, IDC_EDIT_3GNORMAL_INTENSITY, m_edtIntensity);
	DDX_Control(pDX, IDC_COMBO_3GNORMAL_STARTTYPE, m_cboStartType);
	DDX_Control(pDX, IDC_COMBO_3GNORMAL_STOPTYPE, m_cboStopType);
	DDX_Control(pDX, IDC_EDIT_3GNORMAL_DURATION, m_edtDuration);
	DDX_Control(pDX, IDC_EDIT_3GNORMAL_NOTIFY, m_edtNotify);
	DDX_Control(pDX, IDC_EDIT_3GNORMAL_PNum1, m_edtPNum1);
	DDX_Control(pDX, IDC_EDIT_3GNORMAL_PNum2, m_edtPNum2);
	DDX_Control(pDX, IDC_EDIT_3GNORMAL_PNum3, m_edtPNum3);
	DDX_Control(pDX, IDC_EDIT_3GNORMAL_PNum4, m_edtPNum4);
	DDX_Control(pDX, IDC_EDIT_3GNORMAL_PNum5, m_edtPNum5);
	DDX_Control(pDX, IDC_EDIT_3GNORMAL_STARTTIME, m_edtStartTime);
}


BEGIN_MESSAGE_MAP(CLS_3GNormalPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_3GNORMAL_GETSTATUS, &CLS_3GNormalPage::OnBnClickedButton3GNormalGetStatus)
	ON_BN_CLICKED(IDC_BUTTON_3GNORMAL_DISCONNECT, &CLS_3GNormalPage::OnBnClickedButton3GNormalDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_3GNORMAL_DIALOGSET, &CLS_3GNormalPage::OnBnClickedButton3GNormalDialogSet)
	ON_BN_CLICKED(IDC_BUTTON_3GNORMAL_MESSAGESET, &CLS_3GNormalPage::OnBnClickedButton3GNormalMessageSet)
END_MESSAGE_MAP()

BOOL CLS_3GNormalPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_edtDeviceIP.SetLimitText(15);
	m_edtIntensity.SetLimitText(15);
	m_edtDuration.SetLimitText(4);
	m_edtNotify.SetLimitText(63);
	m_edtPNum1.SetLimitText(23);
	m_edtPNum2.SetLimitText(23);
	m_edtPNum3.SetLimitText(23);
	m_edtPNum4.SetLimitText(23);
	m_edtPNum5.SetLimitText(23);
	m_edtStartTime.SetLimitText(15);

	m_cboDeviceType.AddString("DTM");
	m_cboDeviceType.AddString("EVDO");
	m_cboDeviceType.AddString("WCDMA");

	m_cboDeviceStatus.AddString("0-Off line");
	m_cboDeviceStatus.AddString("1-On line");
	m_cboDeviceStatus.AddString("2-Dialing");

	m_cboStartType.AddString("AutoDialog");
	m_cboStartType.AddString("SMSDialog");
	m_cboStartType.AddString("PhoneDialog");
	m_cboStartType.AddString("AlarmDialog");

	m_cboStopType.AddString("Initiative");
	m_cboStopType.AddString("Passive");

	m_cboDeviceStatus.SetCurSel(0);
	m_cboStartType.SetCurSel(0);
	m_cboStopType.SetCurSel(0);
	m_cboDeviceType.SetCurSel(0);

	UI_UpdateDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_3GNormalPage::OnChannelChanged( int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;
	if (m_iLogonID < 0)
	{
		return;
	}
	UI_UpdateDeviceStatus();
	UI_Update3GDialogInfo();
	UI_Update3GMessageInfo();
}

void CLS_3GNormalPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}


// CLS_3GNormalPage message handlers

void CLS_3GNormalPage::OnBnClickedButton3GNormalGetStatus()
{
	// TODO: Add your control notification handler code here
	UI_UpdateDeviceStatus();
}

void CLS_3GNormalPage::OnBnClickedButton3GNormalDisconnect()
{
	// TODO: Add your control notification handler code here
	int   i3GStartType=-1;
	int   i3GStopType=-1;
	int   i3GDuration=-1;
	int   i3GStatus = -1;

	i3GStartType = GetDlgItemInt(IDC_COMBO_3GNORMAL_STARTTYPE);
	i3GStopType = GetDlgItemInt(IDC_COMBO_3GNORMAL_STOPTYPE);
	i3GDuration = GetDlgItemInt(IDC_EDIT_3GNORMAL_DURATION);
	i3GStatus = GetDlgItemInt(IDC_COMBO_3GNORMAL_STATUS);
	if (i3GStatus==1)
	{
		if (NetClient_Set3GDialog && NetClient_Set3GDialog(m_iLogonID,i3GStartType,2,2)==0)
		{
			AddLog(LOG_TYPE_SUCC,"","Set3GDialog Success!LogonID(%d)",m_iLogonID);
		} 
		else
		{
			AddLog(LOG_TYPE_FAIL,"","Set3GDialog Error!(%d)",m_iLogonID);
		}
	}

	UI_Update3GDialogInfo();
}

void CLS_3GNormalPage::OnBnClickedButton3GNormalDialogSet()
{
	// TODO: Add your control notification handler code here
	int   i3GStartType=-1;
	int   i3GStopType=-1;
	int   i3GDuration=-1;

	i3GStartType = m_cboStartType.GetCurSel();
	i3GStopType = m_cboStopType.GetCurSel();
	i3GDuration = GetDlgItemInt(IDC_EDIT_3GNORMAL_DURATION);
	if ((i3GStartType>=0)&&(i3GStartType<=3)&&(i3GStopType>=0)&&(i3GStopType<=1)&&(i3GDuration>=2)&&(i3GDuration<=1440))
	{
		if (NetClient_Set3GDialog(m_iLogonID,i3GStartType,i3GStopType,i3GDuration)!=0)
		{
			AddLog(LOG_TYPE_FAIL,"","Set3GDialog Error!(%d)",m_iLogonID);
		}
		else
		{
			int iRet =  NetClient_Reboot(m_iLogonID);
			CString strIP;
			m_edtDeviceIP.GetWindowText(strIP);
			if (iRet < 0)
			{
				AddLog(LOG_TYPE_FAIL,"","Set3GDialog Error!IP(%s),LogonID(%d), Error(0x%08x)",strIP,m_iLogonID,::GetLastError());
			}
			else
			{
				AddLog(LOG_TYPE_SUCC,"","Set3GDialog Success!IP(%s),LogonID(%d)",strIP,m_iLogonID);
			}
		}
	}
	else
		AddLog(LOG_TYPE_FAIL,"","Input Parma invalid!");
}

void CLS_3GNormalPage::OnBnClickedButton3GNormalMessageSet()
{
	// TODO: Add your control notification handler code here
	CString strNotify;
	CString strPNum1;
	CString strPNum2;
	CString strPNum3;
	CString strPNum4;
	CString strPNum5;
	m_edtNotify.GetWindowText(strNotify);
	m_edtPNum1.GetWindowText(strPNum1);
	m_edtPNum2.GetWindowText(strPNum2);
	m_edtPNum3.GetWindowText(strPNum3);
	m_edtPNum4.GetWindowText(strPNum4);
	m_edtPNum5.GetWindowText(strPNum5);
	if (NetClient_Set3GMessage && NetClient_Set3GMessage(m_iLogonID,(LPSTR)(LPCTSTR)strNotify,
			(LPSTR)(LPCTSTR)strPNum1,(LPSTR)(LPCTSTR)strPNum2,(LPSTR)(LPCTSTR)strPNum3,
				(LPSTR)(LPCTSTR)strPNum4,(LPSTR)(LPCTSTR)strPNum5) == 0)
	{
		AddLog(LOG_TYPE_SUCC,"","Set3GMessage Success!LogonID(%d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","Set3GMessage Error!LogonID(%d), Error(0x%08x)",m_iLogonID,::GetLastError());
	}
}

void CLS_3GNormalPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_3G_DEVICESTATUS, IDS_CFG_3G_NORMAL_DEVICESTATUS);
	SetDlgItemTextEx(IDC_STATIC_3GNORMAL_TYPE, IDS_CFG_3G_NORMAL_TYPE);
	SetDlgItemTextEx(IDC_STATIC_3GNORMAL_STATUS, IDS_CFG_3G_NORMAL_STATUS);
	SetDlgItemTextEx(IDC_STATIC_3GNORMAL_IP, IDS_CFG_3G_NORMAL_IP);
	SetDlgItemTextEx(IDC_STATIC_3GNORMAL_INTENSITY, IDS_CFG_3G_NORMAL_INTENSITY);
	SetDlgItemTextEx(IDC_STATIC_3GNORMAL_STARTTIME, IDS_CFG_3G_NORMAL_STARTTIME);
	SetDlgItemTextEx(IDC_BUTTON_3GNORMAL_GETSTATUS, IDS_CFG_3G_NORMAL_GETSTATUS);

	SetDlgItemTextEx(IDC_STATIC_3G_DIALOG, IDS_CFG_3G_NORMAL_DIALOG);
	SetDlgItemTextEx(IDC_STATIC_3GNORMAL_STARTTYPE, IDS_CFG_3G_STARTTYPE);
	SetDlgItemTextEx(IDC_STATIC_3GNORMAL_STOPTYPE, IDS_CFG_3G_STOPTYPE);
	SetDlgItemTextEx(IDC_STATIC_3GNORMAL_DURATION, IDS_CFG_3G_DURATION);
	SetDlgItemTextEx(IDC_BUTTON_3GNORMAL_DISCONNECT, IDS_CFG_3G_NORMAL_DISCONNECT);
	SetDlgItemTextEx(IDC_BUTTON_3GNORMAL_MESSAGESET, IDS_CFG_3G_NORMAL_MESSAGESET);

	SetDlgItemTextEx(IDC_STATIC_3G_MESSAGE, IDS_CFG_3G_NORMAL_MESSAGE);
	SetDlgItemTextEx(IDC_STATIC_3GNORMAL_NOTIFY, IDS_CFG_3G_NORMAL_NOTIFY);
	SetDlgItemTextEx(IDC_STATIC_3GNORMAL_PNUM1, IDS_CFG_3G_NORMAL_PNUM1);
	SetDlgItemTextEx(IDC_STATIC_3GNORMAL_PNUM2, IDS_CFG_3G_NORMAL_PNUM2);
	SetDlgItemTextEx(IDC_STATIC_3GNORMAL_PNUM3, IDS_CFG_3G_NORMAL_PNUM3);
	SetDlgItemTextEx(IDC_STATIC_3GNORMAL_PNUM4, IDS_CFG_3G_NORMAL_PNUM4);
	SetDlgItemTextEx(IDC_STATIC_3GNORMAL_PNUM5, IDS_CFG_3G_NORMAL_PNUM5);
	SetDlgItemTextEx(IDC_BUTTON_3GNORMAL_MESSAGESET, IDS_CFG_3G_NORMAL_MESSAGESET);

}

void CLS_3GNormalPage::UI_UpdateDeviceStatus()
{
	int   i3GStartType=-1;
	int   i3GStopType=-1;
	int   i3GDuration=-1;
	if (NetClient_Get3GDialog && NetClient_Get3GDialog(m_iLogonID,&i3GStartType,&i3GStopType,&i3GDuration)==0)
	{
		if (i3GStartType == 0 || i3GStartType == 1 || i3GStartType == 2 || i3GStartType == 3)
			m_cboStartType.SetCurSel(i3GStartType);
		else
			m_cboStartType.SetCurSel(-1);


		if (i3GStopType == 0 || i3GStopType == 1 )
			m_cboStopType.SetCurSel(i3GStopType);
		else
			m_cboStopType.SetCurSel(-1);

		SetDlgItemInt(IDC_EDIT_3GNORMAL_DURATION,i3GDuration);
	}
	else
		AddLog(LOG_TYPE_FAIL,"","Get3GDialog Fail!LogonID(%d)",m_iLogonID);
}

void CLS_3GNormalPage::UI_Update3GDialogInfo()
{
	int i3GDeviceType;
	int i3GIntensity;
	int   i3GStatus = -1;
	char c3GIP[16] = {0};
	char c3Starttime[64] = {0};
	if (NetClient_Get3GDeviceStatus(m_iLogonID,&i3GDeviceType,&i3GStatus,&i3GIntensity,c3GIP,c3Starttime)==0)
	{
		if (i3GDeviceType == 0 || i3GDeviceType == 1 || i3GDeviceType == 2)
			m_cboDeviceType.SetCurSel(i3GDeviceType);
		else
			m_cboDeviceType.SetCurSel(-1);

		if (i3GStatus == 0 || i3GStatus == 1 || i3GStatus == 2)
			m_cboDeviceStatus.SetCurSel(i3GStatus);
		else
			m_cboDeviceStatus.SetCurSel(-1);
		SetDlgItemInt(IDC_EDIT_3GNORMAL_INTENSITY, i3GIntensity);
		m_edtDeviceIP.SetWindowText(c3GIP);
		m_edtStartTime.SetWindowText(c3Starttime);
	}
	else
		AddLog(LOG_TYPE_FAIL,"","Get3GDeviceStatus Fail!LogonID(%d)",m_iLogonID);
}

void CLS_3GNormalPage::UI_Update3GMessageInfo()
{
	char cNotify[64] = {0};
	char cNum1[24] = {0};
	char cNum2[24] = {0};
	char cNum3[24] = {0};
	char cNum4[24] = {0};
	char cNum5[24] = {0};
	if (NetClient_Get3GMessage && NetClient_Get3GMessage(m_iLogonID,cNotify,cNum1,cNum2,cNum3,cNum4,cNum5) == 0)
	{
		SetDlgItemText(IDC_EDIT_3GNORMAL_NOTIFY, cNotify);
		SetDlgItemText(IDC_EDIT_3GNORMAL_PNum1, cNum1);
		SetDlgItemText(IDC_EDIT_3GNORMAL_PNum2, cNum2);
		SetDlgItemText(IDC_EDIT_3GNORMAL_PNum3, cNum3);
		SetDlgItemText(IDC_EDIT_3GNORMAL_PNum4, cNum4);
		SetDlgItemText(IDC_EDIT_3GNORMAL_PNum5, cNum5);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","Get3GMessage Error!LogonID(%d), Error(0x%08x)",m_iLogonID,::GetLastError());
	}
}


