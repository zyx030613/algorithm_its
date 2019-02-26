// Config\CmosPage.cpp : implementation file
//

#include "stdafx.h"
#include "CmosPage.h"


// CLS_CmosPage dialog

IMPLEMENT_DYNAMIC(CLS_CmosPage, CDialog)

CLS_CmosPage::CLS_CmosPage(CWnd* pParent /*=NULL*/)
: CLS_BasePage(CLS_CmosPage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_CmosPage::~CLS_CmosPage()
{
}

void CLS_CmosPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_CMOS_SMTPSVR, m_edtSmtpSvr);
	DDX_Control(pDX, IDC_EDIT_CMOS_PORT, m_edtPort);
	DDX_Control(pDX, IDC_EDIT_CMOS_ACCOUNT, m_edtAccount);
	DDX_Control(pDX, IDC_EDIT_CMOS_PASSWORD, m_edtPassword);
	DDX_Control(pDX, IDC_EDIT_CMOS_SUJECT, m_edtMailSubject);
	DDX_Control(pDX, IDC_COMBO_CMOS_AUTHTYPE, m_cmbAuthtype);
	DDX_Control(pDX, IDC_EDIT_CMOS_MAILBOX, m_edtMailBox1);
	DDX_Control(pDX, IDC_EDIT_CMOS_MAILBOX1, m_edtMailBox2);
	DDX_Control(pDX, IDC_EDIT_CMOS_MAILBOX2, m_edtMailBox3);
	DDX_Control(pDX, IDC_EDIT_CMOS_MAILBOX3, m_edtMailBox4);
	DDX_Control(pDX, IDC_CHECK_CMOS_MAILNOTIFY, m_chkMailNotify);
	DDX_Control(pDX, IDC_COMBO_CMOS_SCENE, m_cmbScene);
	DDX_Control(pDX, IDC_COMBO_CMOS_FLIP, m_cmbFlip);
	DDX_Control(pDX, IDC_COMBO_CMOS_MIRROR, m_cmbMirror);
	DDX_Control(pDX, IDC_EDIT_CMOS_FACTORYID, m_edtFactoryID);
	DDX_Control(pDX, IDC_EDIT_CMOS_FUCTIONLIST, m_edtFuctionlist);
	DDX_Control(pDX, IDC_CBO_SCRITY_TYPE, m_cboScrityType);
}


BEGIN_MESSAGE_MAP(CLS_CmosPage, CDialog)
	
ON_BN_CLICKED(IDC_BUTTON_CMOS_SMTPSET, &CLS_CmosPage::OnBnClickedButtonCmosSmtpset)
ON_BN_CLICKED(IDC_CHECK_CMOS_MAILNOTIFY, &CLS_CmosPage::OnBnClickedCheckCmosMailnotify)
ON_CBN_SELCHANGE(IDC_COMBO_CMOS_SCENE, &CLS_CmosPage::OnCbnSelchangeComboCmosScene)
ON_CBN_SELCHANGE(IDC_COMBO_CMOS_FLIP, &CLS_CmosPage::OnCbnSelchangeComboCmosFlip)
ON_CBN_SELCHANGE(IDC_COMBO_CMOS_MIRROR, &CLS_CmosPage::OnCbnSelchangeComboCmosMirror)
ON_BN_CLICKED(IDC_BUTTON_CMOS_FUCSET, &CLS_CmosPage::OnBnClickedButtonCmosFucset)
ON_BN_CLICKED(IDC_BTN_EMAIL_TEST, &CLS_CmosPage::OnBnClickedBtnEmailTest)
END_MESSAGE_MAP()


// CLS_CmosPage message handlers
BOOL CLS_CmosPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	m_edtSmtpSvr.SetLimitText(31);
	m_edtPort.SetLimitText(5);
	m_edtAccount.SetLimitText(31);
	m_edtPassword.SetLimitText(31);
	m_edtMailSubject.SetLimitText(31);
	m_edtMailBox1.SetLimitText(31);
	m_edtMailBox2.SetLimitText(31);
	m_edtMailBox3.SetLimitText(31);
	m_edtMailBox4.SetLimitText(31);
	m_edtFuctionlist.SetLimitText(10);

	m_cmbAuthtype.AddString("off");
	m_cmbAuthtype.AddString("plain");
	m_cmbAuthtype.AddString("cram-md5");
	m_cmbAuthtype.AddString("digest-md5");
	m_cmbAuthtype.AddString("gssapi");
	m_cmbAuthtype.AddString("external");
	m_cmbAuthtype.AddString("login");
	m_cmbAuthtype.AddString("ntlm");
	m_cmbAuthtype.SetCurSel(0);

	m_cmbScene.SetCurSel(0);


	UI_UpdateDialog();

	return TRUE;
}

void CLS_CmosPage::OnChannelChanged(int _iLogonID, int _iChannelNo, int /*_iStreamNo*/)
{
	m_iLogonID = _iLogonID;
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	if (_iChannelNo<0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo;
	}
	//UI_UpdateDialog();
	UI_UpdateEmailAlarmEnable();
	UI_UpdateSmtpInfo();
	UI_UpdateSceneViewInfo();
}

void CLS_CmosPage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_CmosPage::OnBnClickedButtonCmosSmtpset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	SMTP_INFOEX pSmtp = {0};
	int iSmtpPort = GetDlgItemInt(IDC_EDIT_CMOS_PORT);
	if(iSmtpPort < 0 || iSmtpPort > 65535)
	{
		return;
	}
	pSmtp.smtpInfo.wdSmtpPort = iSmtpPort;
	pSmtp.smtpInfo.iAuthtype = m_cmbAuthtype.GetCurSel();
	pSmtp.iScrityType = m_cboScrityType.GetCurSel() + 1;
	GetDlgItemText(IDC_EDIT_CMOS_SMTPSVR, pSmtp.smtpInfo.cSmtpServer, 32);
	GetDlgItemText(IDC_EDIT_CMOS_ACCOUNT, pSmtp.smtpInfo.cEmailAccount, 32);
	GetDlgItemText(IDC_EDIT_CMOS_PASSWORD, pSmtp.smtpInfo.cEmailPassword, 32);
	GetDlgItemText(IDC_EDIT_CMOS_SUJECT, pSmtp.smtpInfo.cMailSubject, 32);
	GetDlgItemText(IDC_EDIT_CMOS_MAILBOX, pSmtp.smtpInfo.cEmailAddress, 32);
	GetDlgItemText(IDC_EDIT_CMOS_MAILBOX1, pSmtp.cMailAddr[0], 32);
	GetDlgItemText(IDC_EDIT_CMOS_MAILBOX2, pSmtp.cMailAddr[1], 32);
	GetDlgItemText(IDC_EDIT_CMOS_MAILBOX3, pSmtp.cMailAddr[2], 32);

	int iRet = NetClient_SetEmailAlarmEx(m_iLogonID, (PSMTP_INFO)&pSmtp, sizeof(SMTP_INFOEX));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetEmailAlarmEx ID(%d)", m_iLogonID);
	}
	else if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetEmailAlarmEx ID(%d)", m_iLogonID);
	}
}

void CLS_CmosPage::UI_UpdateSmtpInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	SMTP_INFOEX pSmtp = {0};
	int iRet = NetClient_GetEmailAlarmEx(m_iLogonID, (PSMTP_INFO)&pSmtp, sizeof(pSmtp));
	if(0 == iRet)
	{
		SetDlgItemText(IDC_EDIT_CMOS_SMTPSVR, pSmtp.smtpInfo.cSmtpServer);
		SetDlgItemInt(IDC_EDIT_CMOS_PORT, pSmtp.smtpInfo.wdSmtpPort);
		SetDlgItemText(IDC_EDIT_CMOS_ACCOUNT, pSmtp.smtpInfo.cEmailAccount);
		SetDlgItemText(IDC_EDIT_CMOS_PASSWORD, pSmtp.smtpInfo.cEmailPassword);
		m_cmbAuthtype.SetCurSel(pSmtp.smtpInfo.iAuthtype);
		m_cboScrityType.SetCurSel(pSmtp.iScrityType-1);
		SetDlgItemText(IDC_EDIT_CMOS_SUJECT, pSmtp.smtpInfo.cMailSubject);
		SetDlgItemText(IDC_EDIT_CMOS_MAILBOX, pSmtp.smtpInfo.cEmailAddress);
		SetDlgItemText(IDC_EDIT_CMOS_MAILBOX1, pSmtp.cMailAddr[0]);
		SetDlgItemText(IDC_EDIT_CMOS_MAILBOX2, pSmtp.cMailAddr[1]);
		SetDlgItemText(IDC_EDIT_CMOS_MAILBOX3, pSmtp.cMailAddr[2]);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetEmailAlarmEx ID(%d)", m_iLogonID);
	}
	else if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetEmailAlarmEx ID(%d)", m_iLogonID);
	}
}

void CLS_CmosPage::OnBnClickedCheckCmosMailnotify()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iEnable = m_chkMailNotify.GetCheck();
	int iTmp = NetClient_SetEmailAlarmEnable(m_iLogonID, m_iChannelNo, iEnable);
	if (0 == iTmp)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetEmailAlarmEnable(%d,%d,%d)", m_iLogonID, m_iChannelNo,iEnable);
	}
	else 
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetEmailAlarmEnable(%d,%d,%d)", m_iLogonID, m_iChannelNo,iEnable);
	}
}

void CLS_CmosPage::OnCbnSelchangeComboCmosScene()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iScene = m_cmbScene.GetCurSel();
	int iRet = NetClient_SetScene(m_iLogonID, m_iChannelNo, iScene);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetScene id(%d)channel(%d)", m_iLogonID, m_iChannelNo);
	}
	else
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetScene id(%d)channel(%d)", m_iLogonID, m_iChannelNo);
}

void CLS_CmosPage::OnCbnSelchangeComboCmosFlip()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iRet = NetClient_SetSensorFlip(m_iLogonID, m_iChannelNo, m_cmbFlip.GetCurSel());
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetSensorFlip id(%d)channel(%d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		MessageBox("Fail!", "", MB_OK|MB_TOPMOST);
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetSensorFlip id(%d)channel(%d)", m_iLogonID, m_iChannelNo);
	}		
}

void CLS_CmosPage::OnCbnSelchangeComboCmosMirror()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iRet = NetClient_SetSensorMirror(m_iLogonID, m_iChannelNo, m_cmbMirror.GetCurSel());
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetSensorMirror id(%d)channel(%d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		MessageBox("Fail!", "", MB_OK|MB_TOPMOST);
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetSensorMirror id(%d)channel(%d)", m_iLogonID, m_iChannelNo);
	}	
}

void CLS_CmosPage::UI_UpdateSceneViewInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iScene = 0;
	if(0 == NetClient_GetScene(m_iLogonID, m_iChannelNo, &iScene))
	{
		m_cmbScene.SetCurSel(iScene);
	}

	int iFlip = 0;
	if(0 == NetClient_GetSensorFlip(m_iLogonID, m_iChannelNo, &iFlip))
	{
		m_cmbFlip.SetCurSel(iFlip);
	}

	int iMirror = 0;
	if(0 == NetClient_GetSensorMirror(m_iLogonID, m_iChannelNo, &iMirror))
	{
		m_cmbMirror.SetCurSel(iMirror);
	}

	char cFactoryID[32] = {0};
	if(0 == NetClient_GetFactoryID(m_iLogonID, cFactoryID))
	{
		m_edtFactoryID.SetWindowText(cFactoryID);
	}

	int iEnableArray = 0;
	if (0 == NetClient_GetFuncListArray(m_iLogonID, &iEnableArray))
	{
		SetDlgItemInt(IDC_EDIT_CMOS_FUCTIONLIST, iEnableArray);
	}
}
void CLS_CmosPage::OnBnClickedButtonCmosFucset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iEnableArray = GetDlgItemInt(IDC_EDIT_CMOS_FUCTIONLIST);
	int iRet = NetClient_SetFuncListArray(m_iLogonID, iEnableArray);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetFuncListArray(%d)",m_iLogonID);
	}
	else
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetFuncListArray(%d)", m_iLogonID);
}

void CLS_CmosPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_CHECK_CMOS_MAILNOTIFY, IDS_CONFIG_CMOS_MAILENABLE);
	SetDlgItemTextEx(IDC_STATIC, IDS_CONFIG_CMOS_MILEALARMINFO);
	SetDlgItemTextEx(IDC_STATIC_CMOS_SMTPSVR, IDS_CONFIG_CMOS_SMTPSVR);
	SetDlgItemTextEx(IDC_STATIC_CMOS_PORT, IDS_CONFIG_CMOS_PORT);
	SetDlgItemTextEx(IDC_STATIC_CMOS_ACCOUNT, IDS_CONFIG_CMOS_ACCOUNT);
	SetDlgItemTextEx(IDC_STATIC_CMOS_PASSWORD, IDS_CONFIG_CMOS_PASSWORD);
	SetDlgItemTextEx(IDC_STATIC_CMOS_SUBJECT, IDS_CONFIG_CMOS_SUBJECT);
	SetDlgItemTextEx(IDC_STATIC_CMOS_AUTHTYPE, IDS_CONFIG_CMOS_AUTHTYPE);
	SetDlgItemTextEx(IDC_BUTTON_CMOS_SMTPSET, IDS_CONFIG_CMOS_SMTPSET);
	SetDlgItemTextEx(IDC_STATIC_CMOS_MAILBOX, IDS_CONFIG_CMOS_MAILBOX);
	SetDlgItemTextEx(IDC_STATIC_CMOS_FACTORYID, IDS_CONFIG_CMOS_FACTORYID);
	SetDlgItemTextEx(IDC_STATIC_CMOS_FUCTIONLIST, IDS_CONFIG_CMOS_FUCTIONLIST);
	SetDlgItemTextEx(IDC_BUTTON_CMOS_FUCSET, IDS_CONFIG_CMOS_IDSET);
	SetDlgItemTextEx(IDC_STATIC_SCENEVIEW, IDS_CONFIG_COMS_SCENEVIEW);
	SetDlgItemTextEx(IDC_STATIC_CMOS_SCENE, IDS_CONFIG_COMS_SCENE);
	SetDlgItemTextEx(IDC_STATIC_CMOS_FLIP, IDS_CONFIG_COMS_FLIP);
	SetDlgItemTextEx(IDC_STATIC_CMOS_MIRROR, IDS_CONFIG_COMS_MIRROR);
	SetDlgItemTextEx(IDC_BTN_EMAIL_TEST, IDS_COMS_EMAIL_TEST);
	SetDlgItemTextEx(IDC_STC_SCRITY_TYPE, IDS_COMS_SCRITY_TYPE);

	InsertString(m_cmbScene,0,IDS_CONFIG_COMS_SCENE0);
	InsertString(m_cmbScene,1,IDS_CONFIG_COMS_SCENE1);
	InsertString(m_cmbScene,2,IDS_CONFIG_COMS_SCENE2);
	InsertString(m_cmbScene,3,IDS_CONFIG_COMS_SCENE3);
	InsertString(m_cmbScene,4,IDS_CONFIG_COMS_SCENE4);
	InsertString(m_cmbScene,5,IDS_CONFIG_COMS_SCENE5);
	InsertString(m_cmbScene,6,IDS_CONFIG_COMS_SCENE6);
	InsertString(m_cmbScene,7,IDS_CONFIG_COMS_SCENE7);

	InsertString(m_cmbFlip,0,IDS_CONFIG_COMS_Flip0);
	InsertString(m_cmbFlip,1,IDS_CONFIG_COMS_Flip1);
	InsertString(m_cmbMirror,0,IDS_CONFIG_COMS_Mirror0);
	InsertString(m_cmbMirror,1,IDS_CONFIG_COMS_Mirror1);

	InsertString(m_cboScrityType,0,IDS_CFG_COM_PARITY_NONE);
	InsertString(m_cboScrityType,1,"SSL");
	InsertString(m_cboScrityType,2,"TLS");

}

void CLS_CmosPage::UI_UpdateEmailAlarmEnable()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iEnable = 0;
	int iRet = NetClient_GetEmailAlarmEnable(m_iLogonID, m_iChannelNo, &iEnable);
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetEmailAlarmEnable(%d,%d,%d)", m_iLogonID, m_iChannelNo,iEnable);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_GetEmailAlarmEnable(%d,%d,%d)", m_iLogonID, m_iChannelNo,iEnable);
	}
	CheckDlgButton(IDC_CHECK_CMOS_MAILNOTIFY,iEnable);
}
void CLS_CmosPage::OnBnClickedBtnEmailTest()
{	
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_EMAIL_TEST, m_iChannelNo, &m_iChannelNo, 0);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig(%d,%d,%d)",m_iLogonID, NET_CLIENT_EMAIL_TEST, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig(%d,%d,%d)",m_iLogonID, NET_CLIENT_EMAIL_TEST, m_iChannelNo);
	}
}
