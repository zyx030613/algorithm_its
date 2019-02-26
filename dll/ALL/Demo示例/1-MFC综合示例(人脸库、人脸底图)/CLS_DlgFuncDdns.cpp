// CLS_DlgFuncDdns.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "CLS_DlgFuncDdns.h"


// CLS_DlgFuncDdns 对话框

IMPLEMENT_DYNAMIC(CLS_DlgFuncDdns, CDialog)

CLS_DlgFuncDdns::CLS_DlgFuncDdns(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DlgFuncDdns::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = -1;
}

CLS_DlgFuncDdns::~CLS_DlgFuncDdns()
{
}

void CLS_DlgFuncDdns::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_DlgFuncDdns, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CLS_DlgFuncDdns::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	for (int i = IDC_CHK_FUNC_DDNS_DYNCOM; i <= IDC_CHK_FUNC_DDNS_3322; i++)
	{
		GetDlgItem(i)->EnableWindow(FALSE);
	}
	return TRUE;
}

void CLS_DlgFuncDdns::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		GetFuncDdns();
	}
}

void CLS_DlgFuncDdns::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (m_iLogonID == _iLogonID && m_iChannelNo == _iChannelNo && m_iStreamNo == _iStreamNo)
	{
		return;
	}

	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;
	GetFuncDdns();
}

void CLS_DlgFuncDdns::OnLanguageChanged( int _iLanguage )
{
}

void CLS_DlgFuncDdns::GetFuncDdns()
{
	for (int i = IDC_CHK_FUNC_DDNS_DYNCOM; i <= IDC_CHK_FUNC_DDNS_3322; i++)
	{
		((CButton*)GetDlgItem(i))->SetCheck(FALSE);
	}

	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgFuncDdns::GetFuncDdns] Error  LogonID!");
		return;
	}
	int iByteReturn = -1;
	FuncAbilityLevel stFunAbilityLevel = {0};
	stFunAbilityLevel.iSize = sizeof(stFunAbilityLevel);
	stFunAbilityLevel.iMainFuncType = MAIN_FUNC_TYPE_DDNSSERVICE;
	stFunAbilityLevel.iSubFuncType = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_GET_FUNC_ABILITY, m_iChannelNo, /*(void*)*/&stFunAbilityLevel, sizeof(stFunAbilityLevel), &iByteReturn);
	if (iRet < 0 || strlen(stFunAbilityLevel.cParam) < 1)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgFuncDdns::GetFuncDdns] GetDevConfig NET_CLIENT_GET_FUNC_ABILITY Failed! m_iLogonID %d", m_iLogonID);
		return;
	}


	CString cstrTemp;
	CString cstrParam = stFunAbilityLevel.cParam;
	cstrParam += _T(",");
	int iPos = -1;
	int iIndex = 0;
	int iType = -1;
	while (-1 != (iPos = cstrParam.Find(',')))
	{
		cstrTemp = cstrParam.Left(iPos);
		cstrParam = cstrParam.Right(cstrParam.GetLength() - iPos - 1);
		iType = _ttoi(cstrTemp);
		if (iType > 3 || iType < 1)
		{
			continue;
		}
		
		((CButton*)GetDlgItem(iType - 1 + IDC_CHK_FUNC_DDNS_DYNCOM))->SetCheck(TRUE);
	}
}




