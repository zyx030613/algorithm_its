// LANWorkModePage.cpp : implementation file
//

#include "stdafx.h"
#include "LANWorkModePage.h"


// CLS_LANWorkModePage dialog

IMPLEMENT_DYNAMIC(CLS_LANWorkModePage, CDialog)

CLS_LANWorkModePage::CLS_LANWorkModePage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_LANWorkModePage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_LANWorkModePage::~CLS_LANWorkModePage()
{
}

void CLS_LANWorkModePage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WORKMODE, m_cboWokeMode);
	DDX_Control(pDX, IDC_COMBO_WORKMODE_LANNO, m_cboLanNo);
	DDX_Control(pDX, IDC_BUTTON_WORKMODE, m_btnWokeMode);
	DDX_Control(pDX, IDC_EDIT_MTU, m_edtMtu);
	DDX_Control(pDX, IDC_COMBO_LANSETMODE, m_cboLansetMode);
}


BEGIN_MESSAGE_MAP(CLS_LANWorkModePage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_WORKMODE, &CLS_LANWorkModePage::OnBnClickedButtonWorkmode)
	ON_BN_CLICKED(IDC_BUTTON_MTU, &CLS_LANWorkModePage::OnBnClickedButtonMtu)
	ON_BN_CLICKED(IDC_BUTTON_LANSETMODE, &CLS_LANWorkModePage::OnBnClickedButtonLansetmode)
END_MESSAGE_MAP()


// CLS_LANWorkModePage message handlers

BOOL CLS_LANWorkModePage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	UI_UpdateDialog();

	return TRUE;
}

void CLS_LANWorkModePage::OnChannelChanged( int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;

	UI_UpdateLanNum();
	UI_UpdateWokeMode();
	UI_UpdateLansetMode();
	UI_UpdateMtu();
}

void CLS_LANWorkModePage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_LANWorkModePage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_WORKMODE,IDS_CONFIG_LAN_WOKEMODE);
	SetDlgItemTextEx(IDC_STATIC_WORKMODE_LANNO,IDS_CONFIG_LAN_WOKEMODE_LANNO);
	SetDlgItemTextEx(IDC_BUTTON_WORKMODE,IDS_SET);

	SetDlgItemTextEx(IDC_STATIC_MTU, IDS_CONFIG_LAN_WOKEMODE_MTU);
	SetDlgItemTextEx(IDC_STATIC_LANSETMODE, IDS_CONFIG_LAN_WORKEMODE_LANSETMODE);
	SetDlgItemTextEx(IDC_STATIC_LANSETSPEED, IDS_CONFIG_LAN_WORKEMODE_LANSETSPEED);
	SetDlgItemTextEx(IDC_BUTTON_LANSETMODE, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_MTU, IDS_SET);

	InsertString(m_cboWokeMode,0,IDS_CONFIG_LAN_WOKEMODE_LOADBALANCE);
	InsertString(m_cboWokeMode,1,IDS_CONFIG_LAN_WOKEMODE_TOLERANT);
	InsertString(m_cboWokeMode,2,IDS_CONFIG_LAN_WOKEMODE_MULTIPLEADDRESS);
	
    InsertString(m_cboLansetMode, 0, IDS_CONFIG_LAN_WOKEMODE_LANSET_RESERVED);
	InsertString(m_cboLansetMode, 1, IDS_CONFIG_LAN_WOKEMODE_LANSET_HALFDUP);
	InsertString(m_cboLansetMode, 2, IDS_CONFIG_LAN_WOKEMODE_LANSET_RESERVED);
	InsertString(m_cboLansetMode, 3, IDS_CONFIG_LAN_WOKEMODE_LANSET_DUPLEX);

}

BOOL CLS_LANWorkModePage::UI_UpdateLanNum()
{
	if (m_iLogonID < 0)
		return FALSE;

	m_cboLanNo.ResetContent();
	int iLanNum = 0;
	int iRet = NetClient_GetLanParam(m_iLogonID, LAN_CMD_GET_LANNUM, &iLanNum);
	if (0 == iRet)
	{
		CString strLanNo;
		for (int i=0; i<iLanNum; i++)
		{
			strLanNo.Format("Lan%d",i+1);
			m_cboLanNo.AddString(strLanNo);
		}
		m_cboLanNo.SetCurSel(0);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetLanParam(WorkMode %d,%d)",m_iLogonID,iLanNum);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetLanParam(WorkMode %d,%d)",m_iLogonID,iLanNum);
	}
	return TRUE;
}

void CLS_LANWorkModePage::OnBnClickedButtonWorkmode()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	LANPARAM_WORKMODE lWokeMode = {0};
	lWokeMode.iSize = sizeof(LANPARAM_WORKMODE);
	lWokeMode.iMainLanNo = m_cboLanNo.GetCurSel();
	lWokeMode.iWorkMode = m_cboWokeMode.GetCurSel();
	int iRet = NetClient_SetLanParam(m_iLogonID, LAN_CMD_SET_WORKMODE, &lWokeMode);
	if (0 == iRet)
	{
		iRet = MessageBox(GetTextEx(IDS_CONFIG_LAN_MESSAGETEXT), GetTextEx(IDS_CONFIG_PROMPT),MB_OKCANCEL);
		if (IDOK == iRet)
		{
			iRet = NetClient_Reboot(m_iLogonID);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetLanParam(WorkMode %d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetLanParam(WorkMode %d)",m_iLogonID);
	}
}

BOOL CLS_LANWorkModePage::UI_UpdateWokeMode()
{
	if (m_iLogonID < 0)
		return FALSE;

	LANPARAM_WORKMODE lWokeMode = {0};
	lWokeMode.iSize = sizeof(LANPARAM_WORKMODE);
	int iRet = NetClient_GetLanParam(m_iLogonID, LAN_CMD_GET_WORKMODE, &lWokeMode);
	if (0 == iRet)
	{
		m_cboWokeMode.SetCurSel(lWokeMode.iWorkMode);
		m_cboLanNo.SetCurSel(lWokeMode.iMainLanNo);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetLanParam(WorkMode %d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetLanParam(WorkMode %d)",m_iLogonID);
	}
	return TRUE;
}

BOOL CLS_LANWorkModePage::UI_UpdateLansetMode()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iBytesReturned = 0;
	TLanParam tLanParam = {0};
	tLanParam.m_iSize = sizeof(TLanParam);

	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLINET_LANPARAM, 0x7FFFFFFF, &tLanParam, sizeof(tLanParam), &iBytesReturned);
	if (0 == iRet)
	{
		m_cboLansetMode.SetCurSel(tLanParam.m_iMode);
		m_cboLanNo.SetCurSel(tLanParam.m_iNo);
		SetDlgItemInt(IDC_EDIT_LANSETSPEED, tLanParam.m_iSpeed);
		SetDlgItemInt(IDC_EDIT_LANSETSPEED, tLanParam.m_iSpeed);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig(WorkMode %d)",m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig(WorkMode %d)",m_iLogonID);
		return FALSE;
	}

	return TRUE;
}

BOOL CLS_LANWorkModePage::UI_UpdateMtu()
{
	if (m_iLogonID < 0)
	{
		return FALSE;
	}

	int iEnableValue = 0;
	int iRet = NetClient_GetCommonEnable(m_iLogonID, CI_NET_CONNECT_INFO, 0x7FFFFFFF, &iEnableValue);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_MTU, iEnableValue);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetCommonEnable(%d)", iEnableValue);
	}
	else if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetCommonEnable(%d)", iEnableValue);
		return FALSE;
	}
	return TRUE;
}

void CLS_LANWorkModePage::OnBnClickedButtonMtu()
{
	// TODO: Add your control notification handler code here
	int iEnableValue = GetDlgItemInt(IDC_EDIT_MTU);
	int iRet = NetClient_SetCommonEnable(m_iLogonID, CI_NET_CONNECT_INFO, 0x7FFFFFFF, iEnableValue);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetCommonEnable(%d)", iEnableValue);
	}
	else if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetCommonEnable(%d)", iEnableValue);
	}

}

void CLS_LANWorkModePage::OnBnClickedButtonLansetmode()
{
	// TODO: Add your control notification handler code here
	int iLanNo = m_cboLanNo.GetCurSel();
	int iLanSpeedMode = m_cboLansetMode.GetCurSel();
	int iLanSpeed = GetDlgItemInt(IDC_EDIT_LANSETSPEED);

	TLanParam tLanParam = {0};
	tLanParam.m_iSize = sizeof(TLanParam);
	tLanParam.m_iNo = iLanNo;
	tLanParam.m_iMode = iLanSpeedMode;
	tLanParam.m_iSpeed = iLanSpeed;
	

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLINET_LANPARAM, 0x7FFFFFFF, &tLanParam, sizeof(TLanParam));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_LANWorkModePage::OnBnClickedButtonLansetmode] Set fail,error = %d", GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "[CLS_LANWorkModePage::OnBnClickedButtonLansetmode] set success!");
	}
}
