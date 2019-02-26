// CLS_DLG_FUNC_COLORTOGRAY.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "CLS_DLG_FUNC_COLORTOGRAY.h"


// CLS_DLG_FUNC_COLORTOGRAY 对话框

IMPLEMENT_DYNAMIC(CLS_DLG_FUNC_COLORTOGRAY, CDialog)

CLS_DLG_FUNC_COLORTOGRAY::CLS_DLG_FUNC_COLORTOGRAY(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DLG_FUNC_COLORTOGRAY::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = -1;
}

CLS_DLG_FUNC_COLORTOGRAY::~CLS_DLG_FUNC_COLORTOGRAY()
{
}

void CLS_DLG_FUNC_COLORTOGRAY::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_DLG_FUNC_COLORTOGRAY, CLS_BaseWindow)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


BOOL CLS_DLG_FUNC_COLORTOGRAY::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	for (int i = IDC_CHK_FUNC_CTG_LIGHTING; i <= IDC_CHK_FUNC_DNM_AUTO; i++)
	{
		GetDlgItem(i)->EnableWindow(FALSE);
	}
	return TRUE;
}

void CLS_DLG_FUNC_COLORTOGRAY::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		InitDialogItemText();
	}
}

void CLS_DLG_FUNC_COLORTOGRAY::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	//if (m_iLogonID == _iLogonID && m_iChannelNo == _iChannelNo && m_iStreamNo == _iStreamNo)
	//{
	//	return;
	//}

	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;

	GetFuncColorToGray();
	GetFuncDayNightMode();

}

void CLS_DLG_FUNC_COLORTOGRAY::OnLanguageChanged( int _iLanguage )
{
	InitDialogItemText();
}

void CLS_DLG_FUNC_COLORTOGRAY::GetFuncDayNightMode()
{
	for (int i = 0; i <= 2; i++)
	{
		((CButton*)GetDlgItem(i + IDC_CHK_FUNC_DNM_BLACKWHITE))->SetCheck(FALSE);
	}

	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DLG_FUNC_COLORTOGRAY : GetFuncDayNightMode] Error  LogonID!");
		return;
	}
	int iByteReturn = -1;
	FuncAbilityLevel stFunAbilityLevel = {0};
	stFunAbilityLevel.iSize = sizeof(stFunAbilityLevel);
	stFunAbilityLevel.iMainFuncType = 0x1;
	stFunAbilityLevel.iSubFuncType = 1;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_GET_FUNC_ABILITY, m_iChannelNo, (void*)&stFunAbilityLevel, sizeof(stFunAbilityLevel), &iByteReturn);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DLG_FUNC_COLORTOGRAY : GetFuncDayNightMode] GetDevConfig Failed!", m_iLogonID);
		return;
	}
// 	BOOL blChkEnable = (0 == (int)stFunAbilityLevel.cParam[2])?FALSE:TRUE;
// 	((CButton*)GetDlgItem(IDC_CHK_FUNC_DNM_BLACKWHITE))->SetCheck(blChkEnable);
// 
// 	blChkEnable = (0 == (int)stFunAbilityLevel.cParam[3])?FALSE:TRUE;
// 	((CButton*)GetDlgItem(IDC_CHK_FUNC_DNM_COLORFUL))->SetCheck(blChkEnable);
// 
// 	blChkEnable = (0 == (int)stFunAbilityLevel.cParam[7])?FALSE:TRUE;
// 	((CButton*)GetDlgItem(IDC_CHK_FUNC_DNM_AUTO))->SetCheck(blChkEnable);
	CString csTemp;
	CString csCurrentParam = stFunAbilityLevel.cParam;
	int iIndex = 0;
	int iTempIndex = 0;
	int iType = -1;
	while(-1 != csCurrentParam.Find(','))
	{
		int iPos = csCurrentParam.Find(',');
		csTemp = csCurrentParam.Left(iPos);
		csCurrentParam = csCurrentParam.Right(csCurrentParam.GetLength() - 1 - iPos);
		iType = _ttoi(csTemp);

		if (2 == iTempIndex || 3 == iTempIndex || 7 == iTempIndex)
		{
			if (0 == iType)
			{
				((CButton*)GetDlgItem(iIndex + IDC_CHK_FUNC_DNM_BLACKWHITE))->SetCheck(FALSE);
			}
			else
			{
				((CButton*)GetDlgItem(iIndex + IDC_CHK_FUNC_DNM_BLACKWHITE))->SetCheck(TRUE);
			}

			iIndex++;
		}
		else
		{
			break;
		}
		iTempIndex++;
	}

}

void CLS_DLG_FUNC_COLORTOGRAY::GetFuncColorToGray()
{
	for (int i = 0; i <= 7; i++)
	{
		((CButton*)GetDlgItem(i + IDC_CHK_FUNC_CTG_LIGHTING))->SetCheck(FALSE);
	}

	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DLG_FUNC_COLORTOGRAY : GetFuncColorToGray] Error  LogonID!");
		return;
	}
 	int iByteReturn = -1;
 	FuncAbilityLevel stFunAbilityLevel = {0};
 	stFunAbilityLevel.iSize = sizeof(stFunAbilityLevel);
 	stFunAbilityLevel.iMainFuncType = 0x1;
 	stFunAbilityLevel.iSubFuncType = 0;
 	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_GET_FUNC_ABILITY, m_iChannelNo, (void*)&stFunAbilityLevel, sizeof(stFunAbilityLevel), &iByteReturn);
 	if (iRet < 0 || strlen(stFunAbilityLevel.cParam) < 1)
 	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DLG_FUNC_COLORTOGRAY : GetFuncColorToGray] GetDevConfig NET_CLIENT_GET_FUNC_ABILITY Failed! m_iLogonID %d", m_iLogonID);
		return;
 	}

	CString csTemp;
	CString csCurrentParam = stFunAbilityLevel.cParam;
	int iIndex = 0;
	int iType = -1;
	while(-1 != csCurrentParam.Find(','))
	{
		if (iIndex >= 0 && iIndex <= 7)
		{
			int iPos = csCurrentParam.Find(',');
			csTemp = csCurrentParam.Left(iPos);
			csCurrentParam = csCurrentParam.Right(csCurrentParam.GetLength() - 1 - iPos);
			iType = _ttoi(csTemp);
;
			if (0 == iType)
			{
				((CButton*)GetDlgItem(iIndex + IDC_CHK_FUNC_CTG_LIGHTING))->SetCheck(FALSE);
			}
			else
			{
				((CButton*)GetDlgItem(iIndex + IDC_CHK_FUNC_CTG_LIGHTING))->SetCheck(TRUE);
			}
			
			iIndex++;
		}
		else
		{
			break;
		}
	}
//	int iFuncColorToGray[8] = {0};
// 	sscanf_s(stFunAbilityLevel.cParam, "%d,%d,%d,%d,%d,%d,%d,%d", &iFuncColorToGray[0], &iFuncColorToGray[1], &iFuncColorToGray[2], &iFuncColorToGray[3],
// 			&iFuncColorToGray[4], &iFuncColorToGray[5], &iFuncColorToGray[6], &iFuncColorToGray[7]);
// 	for (int i = 0; i < 8; i++)
// 	{
// 		if (0 == iFuncColorToGray[i])
// 		{
// 			((CButton*)GetDlgItem(i + IDC_CHK_FUNC_CTG_LIGHTING))->SetCheck(FALSE);
// 		}
// 		else
// 		{
// 			((CButton*)GetDlgItem(i + IDC_CHK_FUNC_CTG_LIGHTING))->SetCheck(TRUE);
// 		}
// 	}


}

void CLS_DLG_FUNC_COLORTOGRAY::InitDialogItemText()
{
	SetDlgItemTextEx(IDC_GPO_FUNC_COLORTOGRAY, IDS_ADV_COLOR_TO_GRAY);
	SetDlgItemTextEx(IDC_GPO_FUNC_DAYNIGHTMODE, IDS_STATIC_DAYNIGHT);
	SetDlgItemTextEx(IDC_CHK_FUNC_CTG_LIGHTING, IDS_ADV_CHANNEL_SET_BRIGHT);
	SetDlgItemTextEx(IDC_CHK_FUNC_CTG_INTERNAL_SYNC, IDS_CONFIG_INNER_SYN);
	SetDlgItemTextEx(IDC_CHK_FUNC_CTG_BLACK_WHITE, IDS_CONFIG_BLACK_WHITE);
	SetDlgItemTextEx(IDC_CHK_FUNC_CTG_COLORFUL, IDS_CONFIG_COLOR);
	SetDlgItemTextEx(IDC_CHK_FUNC_CTG_EXTERN_SYNC, IDS_CONFIG_OUT_SYN);
	SetDlgItemTextEx(IDC_CHK_FUNC_CTG_ALARM_SYNC, IDS_CONFIG_ALARM_SYN);
	SetDlgItemTextEx(IDC_CHK_FUNC_CTG_ONTIME, IDS_CONFIG_SETTIME);
	SetDlgItemTextEx(IDC_CHK_FUNC_CTG_AUTO, IDS_ITS_AUTO);
	SetDlgItemTextEx(IDC_CHK_FUNC_DNM_BLACKWHITE, IDS_CONFIG_BLACK_WHITE);
	SetDlgItemTextEx(IDC_CHK_FUNC_DNM_COLORFUL, IDS_CONFIG_COLOR);
	SetDlgItemTextEx(IDC_CHK_FUNC_DNM_AUTO, IDS_ITS_AUTO);
}


