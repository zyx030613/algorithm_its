// CLS_DlgFuncRoi.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "CLS_DlgFuncRoi.h"


// CLS_DlgFuncRoi 对话框

IMPLEMENT_DYNAMIC(CLS_DlgFuncRoi, CDialog)

CLS_DlgFuncRoi::CLS_DlgFuncRoi(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DlgFuncRoi::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = -1;
}

CLS_DlgFuncRoi::~CLS_DlgFuncRoi()
{
}

void CLS_DlgFuncRoi::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_DlgFuncRoi, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CLS_DlgFuncRoi::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	GetDlgItem(IDC_CHK_FUNC_ROI_ROI)->EnableWindow(FALSE);

	return TRUE;
}

void CLS_DlgFuncRoi::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		GetFuncRoi();
	}
}

void CLS_DlgFuncRoi::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (m_iLogonID == _iLogonID && m_iChannelNo == _iChannelNo && m_iStreamNo == _iStreamNo)
	{
		return;
	}

	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;
	GetFuncRoi();
}

void CLS_DlgFuncRoi::OnLanguageChanged( int _iLanguage )
{
}

void CLS_DlgFuncRoi::GetFuncRoi()
{
	((CButton*)(GetDlgItem(IDC_CHK_FUNC_ROI_ROI)))->SetCheck(FALSE);

	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgFuncRoi::GetFuncRoi] Error  LogonID!");
		return;
	}
	int iByteReturn = -1;
	FuncAbilityLevel stFunAbilityLevel = {0};
	stFunAbilityLevel.iSize = sizeof(stFunAbilityLevel);
	stFunAbilityLevel.iMainFuncType = MAIN_FUNC_TYPE_DYNAMIC_ROI;
	stFunAbilityLevel.iSubFuncType = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_GET_FUNC_ABILITY, m_iChannelNo, (void*)&stFunAbilityLevel, sizeof(stFunAbilityLevel), &iByteReturn);
	if (iRet < 0 || strlen(stFunAbilityLevel.cParam) < 1)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgFuncRoi::GetFuncRoi] GetDevConfig MAIN_FUNC_TYPE_DYNAMIC_ROI Failed! m_iLogonID %d", m_iLogonID);
		return;
	}

	BOOL blTempChk = ((stFunAbilityLevel.cParam[0]) == '1')?TRUE:FALSE;

	((CButton*)(GetDlgItem(IDC_CHK_FUNC_ROI_ROI)))->SetCheck(blTempChk);

}
