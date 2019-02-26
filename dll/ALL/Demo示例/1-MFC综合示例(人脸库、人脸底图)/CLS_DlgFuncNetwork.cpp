// CLS_DlgFuncNetwork.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "CLS_DlgFuncNetwork.h"


// CLS_DlgFuncNetwork 对话框

IMPLEMENT_DYNAMIC(CLS_DlgFuncNetwork, CDialog)

CLS_DlgFuncNetwork::CLS_DlgFuncNetwork(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DlgFuncNetwork::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = -1;
}

CLS_DlgFuncNetwork::~CLS_DlgFuncNetwork()
{
}

void CLS_DlgFuncNetwork::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_DlgFuncNetwork, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CLS_DlgFuncNetwork::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	GetDlgItem(IDC_CHK_FUNC_NET_CHANGGEIP)->EnableWindow(FALSE);
	
	return TRUE;
}

void CLS_DlgFuncNetwork::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		InitDialogItemText();
		GetFuncNetwork();
	}
}

void CLS_DlgFuncNetwork::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (m_iLogonID == _iLogonID && m_iChannelNo == _iChannelNo && m_iStreamNo == _iStreamNo)
	{
		return;
	}

	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;
	GetFuncNetwork();
}

void CLS_DlgFuncNetwork::OnLanguageChanged( int _iLanguage )
{
	InitDialogItemText();
}

void CLS_DlgFuncNetwork::GetFuncNetwork()
{
	((CButton*)(GetDlgItem(IDC_CHK_FUNC_NET_CHANGGEIP)))->SetCheck(FALSE);

	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgFuncNetwork::GetFuncNetwork] Error  LogonID!");
		return;
	}
	int iByteReturn = -1;
	FuncAbilityLevel stFunAbilityLevel = {0};
	stFunAbilityLevel.iSize = sizeof(stFunAbilityLevel);
	stFunAbilityLevel.iMainFuncType = MAIN_FUNC_TYPE_NET;
	stFunAbilityLevel.iSubFuncType = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_GET_FUNC_ABILITY, m_iChannelNo, (void*)&stFunAbilityLevel, sizeof(stFunAbilityLevel), &iByteReturn);
	if (iRet < 0 || strlen(stFunAbilityLevel.cParam) < 1)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgFuncNetwork::GetFuncNetwork] GetDevConfig MAIN_FUNC_TYPE_NET Failed! m_iLogonID %d", m_iLogonID);
		return;
	}
	
	BOOL blTempChk = ((stFunAbilityLevel.cParam[0]) == '1')?TRUE:FALSE;

	((CButton*)(GetDlgItem(IDC_CHK_FUNC_NET_CHANGGEIP)))->SetCheck(blTempChk);

}

void CLS_DlgFuncNetwork::InitDialogItemText()
{
	SetDlgItemTextEx(IDC_GPO_FUNC_NET, IDS_NETWORK);
	SetDlgItemTextEx(IDC_CHK_FUNC_NET_CHANGGEIP, IDS_FUNC_CHANGEIPREBOOT);
}
