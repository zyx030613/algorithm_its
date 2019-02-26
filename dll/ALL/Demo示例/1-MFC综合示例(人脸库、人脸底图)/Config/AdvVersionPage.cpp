// AdvVersionPage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "AdvVersionPage.h"


// CLS_AdvVersionPage dialog

IMPLEMENT_DYNAMIC(CLS_AdvVersionPage, CDialog)

CLS_AdvVersionPage::CLS_AdvVersionPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_AdvVersionPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
}

CLS_AdvVersionPage::~CLS_AdvVersionPage()
{
}

void CLS_AdvVersionPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_AdvVersionPage, CDialog)
	ON_BN_CLICKED(IDC_EDIT_ADVANCE_SET, &CLS_AdvVersionPage::OnBnClickedEditAdvanceSet)
END_MESSAGE_MAP()

void CLS_AdvVersionPage::UI_UpdateText()
{
	SetDlgItemTextEx(IDC_STATIC_ADV_VERSION_KERNEL, IDS_ADV_VERSION_KERNEL);
	SetDlgItemTextEx(IDC_STATIC_ADV_VERSION_UI, IDS_ADV_VERSION_UI);
	SetDlgItemTextEx(IDC_STATIC_ADV_VERSION_PRODUCT_ID, IDS_ADV_VERSION_ID);
	SetDlgItemTextEx(IDC_STATIC_ADV_VERSION_PLUGIN, IDS_ADV_VERSION_PLUGIN);
	SetDlgItemTextEx(IDC_STATIC_ADV_VERSION_SLAVE, IDS_ADV_VERSION_SLAVE);
	SetDlgItemTextEx(IDC_STATIC_ADVI_SER_OTHID, IDS_CFG_ADVI_VER_OTHRTID);
	SetDlgItemTextEx(IDC_STATIC_SINGLECHIP_VERSION, IDS_CFG_ADVI_VER_SINGLECHIP);
}

void CLS_AdvVersionPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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

	UI_UpdateParam();
}

void CLS_AdvVersionPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateText();
	UI_UpdateParam();
}

void CLS_AdvVersionPage::UI_UpdateParam()
{
	if (m_iLogonID < 0)
	{
		return;
	}
	PDEVICE_INFO Device = FindDevice(m_iLogonID);
	SERVER_VERSION version = {0};
	version.m_iStructSize = sizeof(SERVER_VERSION);
	int iRet = NetClient_GetServerVersion_V1(m_iLogonID, &version);
	if (Device && iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "","NetClient_GetServerVersion_V1(%s,%d)", Device->cIP, m_iLogonID);
	}
	SetDlgItemText(IDC_EDIT_ADV_VERSION_KERNEL, version.m_cVersion);
	SetDlgItemText(IDC_EDIT_ADV_VERSION_UI, version.m_cUIVersion);
	SetDlgItemText(IDC_EDIT_ADV_VERSION_SLAVE, version.m_cSlaveVersion);
	SetDlgItemText(IDC_EDIT_ADV_VERSION_PLUGIN, version.m_cPlugInVersion);
	SetDlgItemText(IDC_EDIT_ADV_VERSION_SINGLECHIP, version.m_cSCMVersion);
	SetDlgItemText(IDC_EDIT_ADV_VERSION_ID, Device->cID);

	char cOtherID[LEN_32] = {0};
	iRet = NetClient_GetOtherID(m_iLogonID, cOtherID, LEN_32);
	if (iRet != 0)
	{
		AddLog(LOG_TYPE_FAIL, "","NetClient_GetOtherID(%s,%d)", Device->cIP, m_iLogonID);
	}
	else
	{
		SetDlgItemText(IDC_EDIT_ADVISER_OTHERID,cOtherID);
	}
//add 设置设备型号
	int iBytesReturned = 0;
	DevModel tPCModel = {0};
	tPCModel.iSize = sizeof(tPCModel);
	int iRetPCModel = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_DEV_MODEL, m_iChannelNo, &tPCModel, sizeof(tPCModel), &iBytesReturned);
	
	SetDlgItemText(IDC_EDIT_ADVANCE_PCMODEL, tPCModel.cModel);
 	SetDlgItemTextEx(IDC_EDIT_ADVANCE_SET,IDS_SET);
 	SetDlgItemTextEx(IDC_STATIC_ADVANCE_PCMODEL,IDS_CONFIG_ADVANCE_PCMODEL);
	if( RET_SUCCESS == iRetPCModel)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[DEV_MODEL] (%d,%d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[DEV_MODEL] (%d,%d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}
}
// CLS_AdvVersionPage message handlers

BOOL CLS_AdvVersionPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UI_UpdateText();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_AdvVersionPage::OnBnClickedEditAdvanceSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	DevModel tPCModel = {0};
	CString strPCModel;
	GetDlgItemText(IDC_EDIT_ADVANCE_PCMODEL, strPCModel);
	strncpy(tPCModel.cModel, strPCModel.GetBuffer(),LEN_64);
	tPCModel.iSize = sizeof(tPCModel);

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_DEV_MODEL, m_iChannelNo, &tPCModel, sizeof(tPCModel));
	if( RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[DEV_MODEL] (%d,%d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[DEV_MODEL] (%d,%d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}
}
