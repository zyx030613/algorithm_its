// CLS_DlgFuncLaw.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "CLS_DlgFuncLaw.h"


// CLS_DlgFuncLaw 对话框

IMPLEMENT_DYNAMIC(CLS_DlgFuncLaw, CDialog)

CLS_DlgFuncLaw::CLS_DlgFuncLaw(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DlgFuncLaw::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = -1;
}

CLS_DlgFuncLaw::~CLS_DlgFuncLaw()
{
}

void CLS_DlgFuncLaw::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_DlgFuncLaw, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CLS_DlgFuncLaw::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	for (int i = IDC_CHK_FUNC_LAW_CASESORT; i <= IDC_CHK_FUNC_LAW_COMBINEVIEW; i++)
	{
		GetDlgItem(i)->EnableWindow(FALSE);
	}

	return TRUE;
}

void CLS_DlgFuncLaw::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		InitDialogItemText();
		GetFuncLaw();
	}
}

void CLS_DlgFuncLaw::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (m_iLogonID == _iLogonID && m_iChannelNo == _iChannelNo && m_iStreamNo == _iStreamNo)
	{
		return;
	}

	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;
	GetFuncLaw();
}

void CLS_DlgFuncLaw::OnLanguageChanged( int _iLanguage )
{
	InitDialogItemText();
}

void CLS_DlgFuncLaw::GetFuncLaw()
{
	for (int i = 0; i <= 2; i++)
	{
		((CButton*)(GetDlgItem(i + IDC_CHK_FUNC_LAW_CASESORT)))->SetCheck(FALSE);
	}

	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgFuncLaw::GetFuncLaw] Error  LogonID!");
		return;
	}
	int iByteReturn = -1;
	FuncAbilityLevel stFunAbilityLevel = {0};
	stFunAbilityLevel.iSize = sizeof(stFunAbilityLevel);
	stFunAbilityLevel.iMainFuncType = 0x5;

	for (int i = 0; i <= 2; i++)
	{
		stFunAbilityLevel.iSubFuncType = i;
		int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_GET_FUNC_ABILITY, m_iChannelNo, (void*)&stFunAbilityLevel, sizeof(stFunAbilityLevel), &iByteReturn);
		if (iRet < 0 || strlen(stFunAbilityLevel.cParam) < 1)
		{
			AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgFuncLaw::GetFuncLaw] GetDevConfig 0x5 Failed! m_iLogonID %d iSubFuncType %d", m_iLogonID, i);
			continue;
		}

		BOOL blTempChk = ((stFunAbilityLevel.cParam[0]) == '1')?TRUE:FALSE;

		((CButton*)(GetDlgItem(i + IDC_CHK_FUNC_LAW_CASESORT)))->SetCheck(blTempChk);

	}
}

void CLS_DlgFuncLaw::InitDialogItemText()
{
	SetDlgItemTextEx(IDC_CHK_FUNC_LAW_CASESORT , IDS_FUNC_CASESORT);
	SetDlgItemTextEx(IDC_CHK_FUNC_LAW_EVIDENCEVIEW , IDS_FUNC_EVIDENCEVIEW);
	SetDlgItemTextEx(IDC_CHK_FUNC_LAW_COMBINEVIEW , IDS_FUNC_COMBINEVIEW);
	SetDlgItemTextEx(IDC_GPO_FUNC_LAW , IDS_FUNC_LAW);
}
