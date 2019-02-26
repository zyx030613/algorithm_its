// BurnH323Page.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "BurnH323Page.h"


// CLS_BurnH323Page dialog

IMPLEMENT_DYNAMIC(CLS_BurnH323Page, CDialog)

CLS_BurnH323Page::CLS_BurnH323Page(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_BurnH323Page::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_BurnH323Page::~CLS_BurnH323Page()
{
}

void CLS_BurnH323Page::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LISTEN_PORT, m_edtH323ListenPort);
	DDX_Control(pDX, IDC_EDIT_TERMINAL_NUMBER, m_edtH323TerminalNum);
	DDX_Control(pDX, IDC_EDIT_ENCRYTION_PASSWORD, m_edtH323EncrytionPassword);
	DDX_Control(pDX, IDC_COMBO_ID_CODE_MODE, m_cboH323IdCodeMode);
	DDX_Control(pDX, IDC_COMBO_RESPONDS_BY_CALL, m_cboH323RespondsByCall);
	DDX_Control(pDX, IDC_EDIT_VIDEO_CHANNEL, m_edtH323VideoChannel);
	DDX_Control(pDX, IDC_COMBO_GK_MODE, m_cboH323GKMode);
	DDX_Control(pDX, IDC_EDIT_GK_ADDRESS, m_edtH323GKAddress);
	DDX_Control(pDX, IDC_EDIT_GK_PORT, m_edtH323GKPort);
	DDX_Control(pDX, IDC_EDIT_REGISTER_NAME, m_edtH323RegisterName);
	DDX_Control(pDX, IDC_COMBO_ENCRYTION_TYPE, m_cboH323EncrytionType);
	DDX_Control(pDX, IDC_COMBO_MUTIL_REBOOT, m_cboH323MutilRebootType);
}


BEGIN_MESSAGE_MAP(CLS_BurnH323Page, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_H323_LOCAL_PARA_SET, &CLS_BurnH323Page::OnBnClickedButtonH323LocalParaSet)
	ON_BN_CLICKED(IDC_BUTTON_H323_GK_PARA_SET, &CLS_BurnH323Page::OnBnClickedButtonH323GkParaSet)
	ON_BN_CLICKED(IDC_BUTTON_MUTIL_REBOOT, &CLS_BurnH323Page::OnBnClickedButtonMutilReboot)
END_MESSAGE_MAP()


// CLS_BurnH323Page message handlers

BOOL CLS_BurnH323Page::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_edtH323ListenPort.SetLimitText(LEN_64);
	m_edtH323TerminalNum.SetLimitText(LEN_64);
	m_edtH323VideoChannel.SetLimitText(LEN_64);
	m_edtH323GKAddress.SetLimitText(LEN_64);
	m_edtH323GKPort.SetLimitText(LEN_64);
	m_edtH323RegisterName.SetLimitText(LEN_64);
	m_edtH323EncrytionPassword.SetLimitText(LEN_64);

	UI_UpdateDialogText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_BurnH323Page::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	UI_UpdateH323LocalPara();
	UI_UpdateH323GKPara();
}

void CLS_BurnH323Page::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialogText();
}

void CLS_BurnH323Page::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_STATIC_LISTEN_PORT,IDS_MNG_LOCAL_POTR);
	SetDlgItemTextEx(IDC_STATIC_TERMINAL_NUMBER,IDS_H323_TERMINAL_NUMBER);
	SetDlgItemTextEx(IDC_STATIC_ENCRYTION_PASSWORD,IDS_CFG_VIDEO_ENCRYPT_ENCRYPT_KEY);
	SetDlgItemTextEx(IDC_STATIC_ID_CODE_MODE,IDS_H323_ID_CODE_MODE);
	SetDlgItemTextEx(IDC_STATIC_RESPONDS_BY_CALL,IDS_H323_RESPONDS_BY_CALL);
	SetDlgItemTextEx(IDC_STATICVIDEO_CHANNEL,IDS_H323_VIDEO_CHANNEL);
	SetDlgItemTextEx(IDC_STATIC_GK_MODE,IDS_H323_GK_MODE);
	SetDlgItemTextEx(IDC_STATIC_GK_ADDRESS,IDS_H323_GK_ADDRESS);
	SetDlgItemTextEx(IDC_STATIC_GK_PORT,IDS_H323_GK_PORT);
	SetDlgItemTextEx(IDC_STATIC_REGISTER_NAME,IDS_H323_GK_REGISTER_NAME);
	SetDlgItemTextEx(IDC_STATIC_GK_ENCRYTION_TYPE,IDSH323_GK_ENCRYTION_TYPE);
	SetDlgItemTextEx(IDC_STATIC_MUTIL_REBOOT,IDS_H323_REBOOT_TYPE);
	SetDlgItemTextEx(IDC_BUTTON_H323_LOCAL_PARA_SET,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_H323_GK_PARA_SET,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_MUTIL_REBOOT,IDS_ADV_SYSTEM_REBOOT);

	//0-禁用，1-指定，2-自动搜索
	InsertString(m_cboH323GKMode,0,IDS_POWER_DEV_LST_FORBID);
	InsertString(m_cboH323GKMode,1,IDS_H323_Designation);
	InsertString(m_cboH323GKMode,2,IDS_H323_AUTO_SEARCH);

	InsertString(m_cboH323IdCodeMode,0,"UTF-8");
	InsertString(m_cboH323IdCodeMode,1,"Unicode");

	//0-自动，1-手动，2-免打扰
	InsertString(m_cboH323RespondsByCall,0,IDS_MNG_ADMIN_AUTO);
	InsertString(m_cboH323RespondsByCall,1,IDS_DOME_PTZ_MODE_TYPE);
	InsertString(m_cboH323RespondsByCall,2,IDS_H323_DOT_DISTURB);

	//0-关闭，1-自动，2-中兴，3-新视通，4-思科
	InsertString(m_cboH323EncrytionType,0,IDS_CONFIG_CLOSE);
	InsertString(m_cboH323EncrytionType,1,IDS_MNG_ADMIN_AUTO);
	InsertString(m_cboH323EncrytionType,2,IDS_H323_ENY_ZHONGXING);
	InsertString(m_cboH323EncrytionType,3,IDS_H323_ENT_XINSHITONG);
	InsertString(m_cboH323EncrytionType,4,IDS_H323_ENY_SIKE);

	///0-设备，1-GUI，2-APP
	InsertString(m_cboH323MutilRebootType,0,IDS_H323_REBOOT_DEVICE);
	InsertString(m_cboH323MutilRebootType,1,"GUI");
	InsertString(m_cboH323MutilRebootType,2,"APP");
	m_cboH323MutilRebootType.SetCurSel(0);
}

void CLS_BurnH323Page::UI_UpdateH323LocalPara()
{
	H323LocalParam tParam = {0};
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_H323_LOCALPARAS
		, 0, &tParam, sizeof(H323LocalParam), NULL);
	if (iRet == 0)
	{
		SetDlgItemInt(IDC_EDIT_LISTEN_PORT, tParam.iListenPort);
		m_edtH323TerminalNum.SetWindowText(tParam.cLocalNo);
		m_edtH323EncrytionPassword.SetWindowText(tParam.cPassWord);
		m_cboH323IdCodeMode.SetCurSel(tParam.iIdCodeType);
		m_cboH323RespondsByCall.SetCurSel(tParam.iAnwTypeForCall);
		SetDlgItemInt(IDC_EDIT_VIDEO_CHANNEL, tParam.iMainSrcChnNo);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_H323_LOCALPARAS] (%d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_H323_LOCALPARAS] (%d)",m_iLogonID);
	}
}

void CLS_BurnH323Page::UI_UpdateH323GKPara()
{
	H323GKParam tParam = {0};
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_H323_GKPARAS
		, 0, &tParam, sizeof(H323GKParam), NULL);
	if (iRet == 0)
	{
		m_cboH323GKMode.SetCurSel(tParam.iGKMode);
		m_edtH323GKAddress.SetWindowText(tParam.cGKAddress);
		SetDlgItemInt(IDC_EDIT_GK_PORT, tParam.iGKPort);
		m_edtH323RegisterName.SetWindowText(tParam.cRegisterName);
		m_cboH323EncrytionType.SetCurSel(tParam.iGKEncrytionType);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_H323_GKPARAS] (%d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_H323_GKPARAS] (%d)",m_iLogonID);
	}
}

void CLS_BurnH323Page::OnBnClickedButtonH323LocalParaSet()
{
	// TODO: Add your control notification handler code here
	H323LocalParam tParam;
	tParam.iSize = sizeof(H323LocalParam);
	tParam.iListenPort = GetDlgItemInt(IDC_EDIT_LISTEN_PORT);
	CString cstrTerminalNum;
	m_edtH323TerminalNum.GetWindowText(cstrTerminalNum);
	strcpy_s(tParam.cLocalNo, LEN_64, cstrTerminalNum.GetBuffer());
	CString cstrEncrytionPassword;
	m_edtH323EncrytionPassword.GetWindowText(cstrEncrytionPassword);
	strcpy_s(tParam.cPassWord, LEN_64, cstrEncrytionPassword.GetBuffer());
	tParam.iIdCodeType = m_cboH323IdCodeMode.GetCurSel();
	tParam.iAnwTypeForCall = m_cboH323RespondsByCall.GetCurSel();
	tParam.iMainSrcChnNo = GetDlgItemInt(IDC_EDIT_VIDEO_CHANNEL);

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_H323_LOCALPARAS
		, 0, &tParam, sizeof(H323LocalParam));
	if (iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_H323_LOCALPARAS] (%d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_H323_LOCALPARAS] (%d)",m_iLogonID);
	}
}

void CLS_BurnH323Page::OnBnClickedButtonH323GkParaSet()
{
	// TODO: Add your control notification handler code here
	H323GKParam tParam;
	tParam.iSize = sizeof(H323GKParam);
	tParam.iGKMode = m_cboH323GKMode.GetCurSel();
	CString cstrGKAddress;
	m_edtH323GKAddress.GetWindowText(cstrGKAddress);
	strcpy_s(tParam.cGKAddress, LEN_64, cstrGKAddress.GetBuffer());
	tParam.iGKPort= GetDlgItemInt(IDC_EDIT_GK_PORT);
	CString cstrRegisterName;
	m_edtH323RegisterName.GetWindowText(cstrRegisterName);
	strcpy_s(tParam.cRegisterName, LEN_64, cstrRegisterName.GetBuffer());
	tParam.iGKEncrytionType = m_cboH323EncrytionType.GetCurSel();

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_H323_GKPARAS
		, 0, &tParam, sizeof(H323GKParam));
	if (iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_H323_GKPARAS] (%d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_H323_GKPARAS] (%d)",m_iLogonID);
	}
}

void CLS_BurnH323Page::OnBnClickedButtonMutilReboot()
{
	// TODO: Add your control notification handler code here
	int iType = m_cboH323MutilRebootType.GetCurSel();
	int iRet = NetClient_RebootDeviceByType(m_iLogonID, iType, NULL, 0);
	if (iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_RebootDeviceByType(%d),(%d)",m_iLogonID, iType);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_RebootDeviceByType(%d),(%d)",m_iLogonID, iType);
	}
}

void CLS_BurnH323Page::OnParamChangeNotify( int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUser )
{
	switch(_iParaType)
	{
	case PARA_H323_LOCAL_Param:
		UI_UpdateH323LocalPara();
		break;
	case PARA_H323_GK_Param:
		UI_UpdateH323GKPara();
		break;
	default:
		break;
	}
}