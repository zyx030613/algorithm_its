// CLS_DlgFuncDome.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "CLS_DlgFuncDome.h"


// CLS_DlgFuncDome 对话框

IMPLEMENT_DYNAMIC(CLS_DlgFuncDome, CDialog)

CLS_DlgFuncDome::CLS_DlgFuncDome(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DlgFuncDome::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = -1;
}

CLS_DlgFuncDome::~CLS_DlgFuncDome()
{
}

void CLS_DlgFuncDome::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_DlgFuncDome, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CLS_DlgFuncDome::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	GetDlgItem(IDC_CHK_FUNC_DOME_FOG)->EnableWindow(FALSE);


	return TRUE;
}

void CLS_DlgFuncDome::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		InitDialogItemText();
		GetFuncDome();
	}
}

void CLS_DlgFuncDome::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (m_iLogonID == _iLogonID && m_iChannelNo == _iChannelNo && m_iStreamNo == _iStreamNo)
	{
		return;
	}

	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;
	GetFuncDome();
}

void CLS_DlgFuncDome::OnLanguageChanged( int _iLanguage )
{
	InitDialogItemText();
}

void CLS_DlgFuncDome::GetFuncDome()
{
	((CButton*)(GetDlgItem(IDC_CHK_FUNC_DOME_FOG)))->SetCheck(FALSE);

	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgFuncDome::GetFuncDome] Error  LogonID!");
		return;
	}
	int iByteReturn = -1;
	FuncAbilityLevel stFunAbilityLevel = {0};
	stFunAbilityLevel.iSize = sizeof(stFunAbilityLevel);
	stFunAbilityLevel.iMainFuncType = MAIN_FUNC_TYPE_DOME_PARA;
	stFunAbilityLevel.iSubFuncType = 0;

	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_GET_FUNC_ABILITY, m_iChannelNo, (void*)&stFunAbilityLevel, sizeof(stFunAbilityLevel), &iByteReturn);
	if (iRet < 0 || strlen(stFunAbilityLevel.cParam) < 1)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgFuncDome::GetFuncDome] GetDevConfig MAIN_FUNC_TYPE_DOME_PARA Failed! m_iLogonID %d", m_iLogonID);
		return;
	}

	CString csCurrentParam;
	csCurrentParam = stFunAbilityLevel.cParam;
	csCurrentParam.ReleaseBuffer();
	int iCurrentParam[2] = {0};
	sscanf_s(csCurrentParam, "%d,%d", &iCurrentParam[0], &iCurrentParam[1]);

	if (1 == (iCurrentParam[0] & 0x01))
	{
		((CButton*)(GetDlgItem(IDC_CHK_FUNC_DOME_FOG)))->SetCheck(TRUE);
	}
	else
	{
		((CButton*)(GetDlgItem(IDC_CHK_FUNC_DOME_FOG)))->SetCheck(FALSE);
	}

}

void CLS_DlgFuncDome::InitDialogItemText()
{
	SetDlgItemTextEx(IDC_GPO_FUNC_DOME_DOME , IDS_CFG_FUNC_DOME);
	SetDlgItemTextEx(IDC_CHK_FUNC_DOME_FOG , IDS_HEAT_MODE_FOG);
}
