// CLS_DlgFuncDecoder.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "CLS_DlgFuncDecoder.h"


// CLS_DlgFuncDecoder 对话框

IMPLEMENT_DYNAMIC(CLS_DlgFuncDecoder, CDialog)

CLS_DlgFuncDecoder::CLS_DlgFuncDecoder(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DlgFuncDecoder::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = -1;
}

CLS_DlgFuncDecoder::~CLS_DlgFuncDecoder()
{
}

void CLS_DlgFuncDecoder::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_DlgFuncDecoder, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CLS_DlgFuncDecoder::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	for (int i = IDC_CHK_FUNC_DEC_DEVIDEPIC; i <= IDC_CHK_FUNC_DEC_TALK; i++)
	{
		GetDlgItem(i)->EnableWindow(FALSE);
	}
	return TRUE;
}

void CLS_DlgFuncDecoder::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		InitDialogItemText();
		GetFuncDecoderConfig();
	}
}

void CLS_DlgFuncDecoder::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (m_iLogonID == _iLogonID && m_iChannelNo == _iChannelNo && m_iStreamNo == _iStreamNo)
	{
		return;
	}

	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;
	GetFuncDecoderConfig();
}

void CLS_DlgFuncDecoder::OnLanguageChanged( int _iLanguage )
{
	InitDialogItemText();
}


void CLS_DlgFuncDecoder::InitDialogItemText()
{
	for (int i = 0; i <= 7; i++)
	{
		SetDlgItemTextEx(i + IDC_CHK_FUNC_DEC_DEVIDEPIC, i + IDS_FUNC_VIEW_SEGMENT);
	}
}

void CLS_DlgFuncDecoder::GetFuncDecoderConfig()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgFuncDecoder::GetFuncDecoderConfig] Error  LogonID!");
		return;
	}

	int iByteReturn = -1;
	FuncAbilityLevel stFunAbilityLevel = {0};
	stFunAbilityLevel.iSize = sizeof(stFunAbilityLevel);
	stFunAbilityLevel.iMainFuncType = 0x6;


	for (int i = 0; i <= 7; i++)
	{
		((CButton*)GetDlgItem(i + IDC_CHK_FUNC_DEC_DEVIDEPIC))->SetCheck(FALSE);
		if (i <= 3 || i == 6)
		{
			GetDlgItem(i + IDC_EDT_FUNC_DEC_DEVIDEPIC)->ShowWindow(SW_HIDE);
		}
		stFunAbilityLevel.iSubFuncType = i;
		int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_GET_FUNC_ABILITY, m_iChannelNo, (void*)&stFunAbilityLevel, sizeof(stFunAbilityLevel), &iByteReturn);
		if (iRet < 0 || strlen(stFunAbilityLevel.cParam) < 1)
		{
			AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgFuncDecoder::GetFuncDecoderConfig] GetDevConfig Failed! SubFuncType %d  %d", i, stFunAbilityLevel.iSubFuncType);
			continue;
		}
		CString csTempParam = stFunAbilityLevel.cParam;
		if (i <= 3 || i == 6)
		{
			if (csTempParam == '0')
			{
				((CButton*)GetDlgItem(i + IDC_CHK_FUNC_DEC_DEVIDEPIC))->SetCheck(FALSE);
				GetDlgItem(i + IDC_EDT_FUNC_DEC_DEVIDEPIC)->ShowWindow(SW_HIDE);
			} 
			else
			{
				((CButton*)GetDlgItem(i + IDC_CHK_FUNC_DEC_DEVIDEPIC))->SetCheck(TRUE);
				GetDlgItem(i + IDC_EDT_FUNC_DEC_DEVIDEPIC)->ShowWindow(SW_SHOW);
				GetDlgItem(i + IDC_EDT_FUNC_DEC_DEVIDEPIC)->SetWindowText(csTempParam);
			}
		}
		else
		{
			BOOL blTempChk = (csTempParam == '1')?TRUE:FALSE;
			((CButton*)GetDlgItem(i + IDC_CHK_FUNC_DEC_DEVIDEPIC))->SetCheck(blTempChk);
		}
	}
}



