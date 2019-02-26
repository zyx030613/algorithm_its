// ECOPOtherPage.cpp : implementation file
//

#include "stdafx.h"
#include "ECOPOtherPage.h"


// CLS_ECOPOtherPage dialog

IMPLEMENT_DYNAMIC(CLS_ECOPOtherPage, CDialog)

CLS_ECOPOtherPage::CLS_ECOPOtherPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ECOPOtherPage::IDD, pParent)
{
	m_iLogonID = -1;

}

CLS_ECOPOtherPage::~CLS_ECOPOtherPage()
{
}

void CLS_ECOPOtherPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ROADWAYID, m_cboRoadwayID);
	DDX_Control(pDX, IDC_CHECK_WATERMARK_ENABLE, m_chkEnable);
	DDX_Control(pDX, IDC_COMBO_SN_TYPE, m_cboSnType);
	DDX_Control(pDX, IDC_EDIT_SN_SN, m_edtSn);
	DDX_Control(pDX, IDC_EDIT_LOCKRET, m_edtLocalRet);
	DDX_Control(pDX, IDC_BUTTON_SN, m_btnSn);
	DDX_Control(pDX, IDC_EDIT_SYSTEM_TYPE, m_edtSystemType);
	DDX_Control(pDX, IDC_BUTTON_SYSTEM, m_btnSystem);
}


BEGIN_MESSAGE_MAP(CLS_ECOPOtherPage, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_ROADWAYID, &CLS_ECOPOtherPage::OnCbnSelchangeComboRoadwayid)
	ON_BN_CLICKED(IDC_CHECK_WATERMARK_ENABLE, &CLS_ECOPOtherPage::OnBnClickedCheckWatermarkEnable)
	ON_BN_CLICKED(IDC_BUTTON_SN, &CLS_ECOPOtherPage::OnBnClickedButtonSn)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM, &CLS_ECOPOtherPage::OnBnClickedButtonSystem)
END_MESSAGE_MAP()


// CLS_ECOPOtherPage message handlers
BOOL CLS_ECOPOtherPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	for (int i=0; i<4; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboRoadwayID.AddString(strNo);
	}
	m_cboRoadwayID.SetCurSel(0);

	m_cboSnType.AddString("0--RECOGNIZE_ARITHMETIC");
	m_cboSnType.AddString("1--PROGRAM");

	m_edtSn.SetLimitText(63);

	UI_UpdateDialog();

	return TRUE;
}

void CLS_ECOPOtherPage::OnChannelChanged( int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;

	UI_UpdateOther();
}

void CLS_ECOPOtherPage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ECOPOtherPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_ROADWAYID,IDS_CONFIG_ECOP_ROADWAYID);
	SetDlgItemTextEx(IDC_STATIC_WATERMARK,IDS_CONFIG_ECOP_WATERMARK);
	SetDlgItemTextEx(IDC_CHECK_WATERMARK_ENABLE,IDS_CONFIG_ECOP_WATERMARK_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_SN,IDS_CONFIG_ECOP_SN);
	SetDlgItemTextEx(IDC_STATIC_SN_TYPE,IDS_CONFIG_ECOP_SN_TYPE);
	SetDlgItemTextEx(IDC_STATIC_SN_SN,IDS_CONFIG_ECOP_SN);
	SetDlgItemTextEx(IDC_STATIC_LOCKRET,IDS_CONFIG_ECOP_LOCALRET);
	SetDlgItemTextEx(IDC_BUTTON_SN,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_SYSTEM,IDS_CONFIG_ECOP_SYSTEM);
	SetDlgItemTextEx(IDC_STATIC_SYSTEM_TYPE,IDS_CONFIG_ECOP_SYSTEM_TYPE);
	SetDlgItemTextEx(IDC_BUTTON_SYSTEM,IDS_SET);

}

BOOL CLS_ECOPOtherPage::UI_UpdateOther()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iChannelID = m_cboRoadwayID.GetCurSel();
	int iWaterMarkEnable = 0;
	int iRet = NetClient_GetWaterMarkEnable(m_iLogonID,iChannelID,&iWaterMarkEnable);
	if (0 == iRet)
	{
		m_chkEnable.SetCheck(iWaterMarkEnable?BST_CHECKED:BST_UNCHECKED);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetWaterMarkEnable (%d,%d)",m_iLogonID,iWaterMarkEnable);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetWaterMarkEnable (%d,%d)",m_iLogonID,iWaterMarkEnable);
	}
	int iLockRet = 0;
	iRet = NetClient_GetSNReg(m_iLogonID,&iLockRet);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_LOCKRET, iLockRet);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetSNReg (%d,%d)",m_iLogonID,iLockRet);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetSNReg (%d,%d)",m_iLogonID,iLockRet);
	}
	int iSystemType = 0;
	iRet = NetClient_GetSystemType(m_iLogonID,&iSystemType);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_SYSTEM_TYPE, iSystemType);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetSystemType (%d,%d)",m_iLogonID,iSystemType);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetSystemType (%d,%d)",m_iLogonID,iSystemType);
	}
	return TRUE;
}

void CLS_ECOPOtherPage::OnCbnSelchangeComboRoadwayid()
{
	UI_UpdateOther();
}

void CLS_ECOPOtherPage::OnBnClickedCheckWatermarkEnable()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iChannelID = m_cboRoadwayID.GetCurSel();
	int iEnable = (m_chkEnable.GetCheck() == BST_CHECKED)?1:0;
	int iRet = NetClient_SetWaterMarkEnable(m_iLogonID,iChannelID,iEnable);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetWaterMarkEnable (%d,%d)",m_iLogonID,iEnable);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetWaterMarkEnable (%d,%d)",m_iLogonID,iEnable);
	}
}

void CLS_ECOPOtherPage::OnBnClickedButtonSn()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	
	int iType = m_cboSnType.GetCurSel();
	char cSN[64] = {0};
	GetDlgItemText(IDC_EDIT_SN_SN, cSN, 63);
	int iRet = NetClient_SetEncryptSN(m_iLogonID,iType,cSN);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetEncryptSN (%d,%s)",m_iLogonID,cSN);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetEncryptSN (%d,%s)",m_iLogonID,cSN);
	}
}

void CLS_ECOPOtherPage::OnBnClickedButtonSystem()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	
	int iType = GetDlgItemInt(IDC_EDIT_SYSTEM_TYPE);
	if(iType == SYSTEM_TYPE_DEBUG || iType == SYSTEM_TYPE_GATE || iType == SYSTEM_TYPE_ECOP)
	{
		int iRet = NetClient_SetSystemType(m_iLogonID,iType);
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetSystemType (%d,%d)",m_iLogonID,iType);
		} 
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetSystemType (%d,%d)",m_iLogonID,iType);
		}
	}
}
