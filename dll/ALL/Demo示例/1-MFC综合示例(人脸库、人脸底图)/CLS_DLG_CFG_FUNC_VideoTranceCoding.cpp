// CLS_DLG_CFG_FUNC_VideoTranceCoding.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "CLS_DLG_CFG_FUNC_VideoTranceCoding.h"


// CLS_DLG_CFG_FUNC_VideoTranceCoding 对话框

IMPLEMENT_DYNAMIC(CLS_DLG_CFG_FUNC_VideoTranceCoding, CDialog)

CLS_DLG_CFG_FUNC_VideoTranceCoding::CLS_DLG_CFG_FUNC_VideoTranceCoding(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DLG_CFG_FUNC_VideoTranceCoding::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = -1;
}

CLS_DLG_CFG_FUNC_VideoTranceCoding::~CLS_DLG_CFG_FUNC_VideoTranceCoding()
{
}

void CLS_DLG_CFG_FUNC_VideoTranceCoding::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_DLG_CFG_FUNC_VideoTranceCoding, CLS_BasePage)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CLS_DLG_CFG_FUNC_VideoTranceCoding::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	GetDlgItem(IDC_CHK_FUNC_VTC_ENABLE)->EnableWindow(FALSE);

	return TRUE;
}

void CLS_DLG_CFG_FUNC_VideoTranceCoding::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		InitDialogItemText();
		GetFuncVideoTranscoding();
	}
}

void CLS_DLG_CFG_FUNC_VideoTranceCoding::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (m_iLogonID == _iLogonID && m_iChannelNo == _iChannelNo && m_iStreamNo == _iStreamNo)
	{
		return;
	}

	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;
	GetFuncVideoTranscoding();
}

void CLS_DLG_CFG_FUNC_VideoTranceCoding::OnLanguageChanged( int _iLanguage )
{
	InitDialogItemText();
}

void CLS_DLG_CFG_FUNC_VideoTranceCoding::InitDialogItemText()
{
	SetDlgItemTextEx(IDC_GPO_FUNC_VTC_ENABLE, IDS_CFG_FUNC_VIDEOTRANSCODING);
	SetDlgItemTextEx(IDC_CHK_FUNC_VTC_ENABLE, IDS_ENABLE);

}

void CLS_DLG_CFG_FUNC_VideoTranceCoding::GetFuncVideoTranscoding()
{
	((CButton*)GetDlgItem(IDC_CHK_FUNC_VTC_ENABLE))->SetCheck(FALSE);

	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DLG_CFG_FUNC_VideoTranceCoding::GetFuncVideoTranscoding] Error  LogonID!");
		return;
	}
	int iByteReturn = -1;
	FuncAbilityLevel stFunAbilityLevel = {0};
	stFunAbilityLevel.iSize = sizeof(stFunAbilityLevel);
	stFunAbilityLevel.iMainFuncType = MAIN_FUNC_TYPE_TRANSCODING;
	stFunAbilityLevel.iSubFuncType = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_GET_FUNC_ABILITY, m_iChannelNo, (void*)&stFunAbilityLevel, sizeof(stFunAbilityLevel), &iByteReturn);
	if (iRet < 0 || strlen(stFunAbilityLevel.cParam) < 1)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DLG_CFG_FUNC_VideoTranceCoding::GetFuncVideoTranscoding] GetDevConfig  Failed! m_iLogonId %d", m_iLogonID);
		return;
	}
	else
	{
		BOOL blChkEnable = ((stFunAbilityLevel.cParam[0]) == '1')?TRUE:FALSE;
		((CButton*)GetDlgItem(IDC_CHK_FUNC_VTC_ENABLE))->SetCheck(blChkEnable);
	}
}
