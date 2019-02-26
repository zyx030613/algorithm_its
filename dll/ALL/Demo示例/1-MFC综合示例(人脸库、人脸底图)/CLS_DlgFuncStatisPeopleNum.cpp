// CLS_DlgFuncStatisPeopleNum.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "CLS_DlgFuncStatisPeopleNum.h"


// CLS_DlgFuncStatisPeopleNum 对话框

IMPLEMENT_DYNAMIC(CLS_DlgFuncStatisPeopleNum, CDialog)

CLS_DlgFuncStatisPeopleNum::CLS_DlgFuncStatisPeopleNum(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DlgFuncStatisPeopleNum::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = -1;
}

CLS_DlgFuncStatisPeopleNum::~CLS_DlgFuncStatisPeopleNum()
{
}

void CLS_DlgFuncStatisPeopleNum::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_DlgFuncStatisPeopleNum, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CLS_DlgFuncStatisPeopleNum::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	GetDlgItem(IDC_CHK_FUNC_SPN_SPN)->EnableWindow(FALSE);

	return TRUE;
}

void CLS_DlgFuncStatisPeopleNum::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		InitDialogItemText();
		GetFuncStaticsPeopleNum();
	}
}

void CLS_DlgFuncStatisPeopleNum::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (m_iLogonID == _iLogonID && m_iChannelNo == _iChannelNo && m_iStreamNo == _iStreamNo)
	{
		return;
	}

	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;
	GetFuncStaticsPeopleNum();
}

void CLS_DlgFuncStatisPeopleNum::OnLanguageChanged( int _iLanguage )
{
	InitDialogItemText();
}

void CLS_DlgFuncStatisPeopleNum::GetFuncStaticsPeopleNum()
{
	((CButton*)(GetDlgItem(IDC_CHK_FUNC_SPN_SPN)))->SetCheck(FALSE);

	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgFuncStatisPeopleNum::GetFuncStaticsPeopleNum] Error  LogonID!");
		return;
	}
	int iByteReturn = -1;
	FuncAbilityLevel stFunAbilityLevel = {0};
	stFunAbilityLevel.iSize = sizeof(stFunAbilityLevel);
	stFunAbilityLevel.iMainFuncType = MAIN_FUNC_TYPE_FORMREPORT;
	stFunAbilityLevel.iSubFuncType = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_GET_FUNC_ABILITY, m_iChannelNo, (void*)&stFunAbilityLevel, sizeof(stFunAbilityLevel), &iByteReturn);
	if (iRet < 0 || strlen(stFunAbilityLevel.cParam) < 1)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgFuncStatisPeopleNum::GetFuncStaticsPeopleNum] GetDevConfig MAIN_FUNC_TYPE_NET Failed! m_iLogonID %d", m_iLogonID);
		return;
	}

	BOOL blTempChk = ((stFunAbilityLevel.cParam[0]) == '1')?TRUE:FALSE;

	((CButton*)(GetDlgItem(IDC_CHK_FUNC_SPN_SPN)))->SetCheck(blTempChk);

}

void CLS_DlgFuncStatisPeopleNum::InitDialogItemText()
{
	SetDlgItemTextEx(IDC_CHK_FUNC_SPN_SPN, IDS_FUNC_STATISPEOPLENUM);
}
