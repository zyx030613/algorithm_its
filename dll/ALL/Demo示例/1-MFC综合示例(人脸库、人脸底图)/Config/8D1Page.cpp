// 8D1Page.cpp : implementation file
//

#include "stdafx.h"
#include "8D1Page.h"
#include "Preview\ActionControl.h"


// CLS_8D1Page dialog

IMPLEMENT_DYNAMIC(CLS_8D1Page, CDialog)

CLS_8D1Page::CLS_8D1Page(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_8D1Page::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;

}

CLS_8D1Page::~CLS_8D1Page()
{
}

void CLS_8D1Page::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_8D1_CRUISENO, m_cboCruiseNo);
	DDX_Control(pDX, IDC_COMBO_8D1_CRUISENUM, m_cboCruiseNum);
	DDX_Control(pDX, IDC_COMBO_8D1_PRESET, m_cboPreset[0]);
	DDX_Control(pDX, IDC_COMBO_8D1_STAYTIME, m_cboStayTime[0]);
	DDX_Control(pDX, IDC_COMBO_8D1_SPEED, m_cboSpeed[0]);
	DDX_Control(pDX, IDC_COMBO_8D1_PRESET1, m_cboPreset[1]);
	DDX_Control(pDX, IDC_COMBO_8D1_PRESET2, m_cboPreset[2]);
	DDX_Control(pDX, IDC_COMBO_8D1_PRESET3, m_cboPreset[3]);
	DDX_Control(pDX, IDC_CHECK_8D1_CRUISEENABLE, m_chkCruiseEnable);
	DDX_Control(pDX, IDC_COMBO_8D1_STAYTIME1, m_cboStayTime[1]);
	DDX_Control(pDX, IDC_COMBO_8D1_STAYTIME2, m_cboStayTime[2]);
	DDX_Control(pDX, IDC_COMBO_8D1_STAYTIME3, m_cboStayTime[3]);
	DDX_Control(pDX, IDC_COMBO_8D1_SPEED1, m_cboSpeed[1]);
	DDX_Control(pDX, IDC_COMBO_8D1_SPEED2, m_cboSpeed[2]);
	DDX_Control(pDX, IDC_COMBO_8D1_SPEED3, m_cboSpeed[3]);
	DDX_Control(pDX, IDC_BUTTON_8D1_CRUISE, m_btnCruise);
}


BEGIN_MESSAGE_MAP(CLS_8D1Page, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_8D1_CRUISE, &CLS_8D1Page::OnBnClickedButton8d1Cruise)
	ON_CBN_SELCHANGE(IDC_COMBO_8D1_CRUISENO, &CLS_8D1Page::OnCbnSelchangeCombo8d1Cruiseno)
	ON_CBN_SELCHANGE(IDC_COMBO_8D1_CRUISENUM, &CLS_8D1Page::OnCbnSelchangeCombo8d1Cruisenum)
	ON_BN_CLICKED(IDC_BUTTON_CRUISE_START, &CLS_8D1Page::OnBnClickedButtonCruiseStart)
	ON_BN_CLICKED(IDC_BUTTON_CRUISE_STOP, &CLS_8D1Page::OnBnClickedButtonCruiseStop)
	ON_BN_CLICKED(IDC_BUTTON_TRACK_START, &CLS_8D1Page::OnBnClickedButtonTrackStart)
	ON_BN_CLICKED(IDC_BUTTONT_TRACK_STOP, &CLS_8D1Page::OnBnClickedButtontTrackStop)
	ON_BN_CLICKED(IDC_CHECK_8D1_CRUISEENABLE, &CLS_8D1Page::OnBnClickedCheck8d1Cruiseenable)
END_MESSAGE_MAP()


// CLS_8D1Page message handlers
BOOL CLS_8D1Page::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	for (int i=0; i<8; i++)
	{
		CString strCruiseNo;
		strCruiseNo.Format("%d",i);
		m_cboCruiseNo.AddString(strCruiseNo);
	}
	m_cboCruiseNo.SetCurSel(0);
	CString strNo;
	for (int i=0; i<=4; i++)
	{
		strNo.Format("%d", i);
		m_cboCruiseNum.AddString(strNo);
	}
	m_cboCruiseNum.SetCurSel(0);
// 	for (int i=0; i<4; i++)
// 	{
// 		for (int j=1; j<=4; j++)
// 		{
// 			strNo.Format("%d", j);
// 			m_cboPreset[i].AddString(strNo);
// 			m_cboStayTime[i].AddString(strNo);
// 			m_cboSpeed[i].AddString(strNo);
// 		}
// 	}
	for (int i=0; i<4; ++i)
	{
		for (int j = 1; j <= 255; ++j)
		{
			strNo.Format("%d", j);
			m_cboPreset[i].AddString(strNo);
		}
	}
	for (int i=0; i<4; ++i)
	{
		for (int j = 1; j <= 60; ++j)
		{
			strNo.Format("%d", j);
			m_cboStayTime[i].AddString(strNo);
		}
	}
	for (int i=0; i<4; ++i)
	{
		for (int j = 0; j <= 100; ++j)
		{
			strNo.Format("%d", j);
			m_cboSpeed[i].AddString(strNo);
		}
	}
	for (int i=0; i<4; i++)
	{
		m_cboPreset[i].SetCurSel(0);
		m_cboStayTime[i].SetCurSel(0);
		m_cboSpeed[i].SetCurSel(0);
	}

	UI_UpdateDialog();

	return TRUE;
}

void CLS_8D1Page::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
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

	UI_UpdateCruise();
}

void CLS_8D1Page::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_8D1Page::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_8D1_CRUISENO,IDS_CONFIG_8D1_CRUISENO);
	SetDlgItemTextEx(IDC_STATIC_8D1_CRUISENUM,IDS_CONFIG_8D1_CRUISENUM);
	SetDlgItemTextEx(IDC_STATIC_8D1_PRESET,IDS_CONFIG_8D1_PRESET);
	SetDlgItemTextEx(IDC_STATIC_8D1_STAYTIME,IDS_CONFIG_8D1_STAYTIME);
	SetDlgItemTextEx(IDC_STATIC_8D1_SPEED,IDS_CONFIG_8D1_SPEED);
	SetDlgItemTextEx(IDC_STATIC_8D1_CRUISENOPLAY,IDS_CONFIG_8D1_CRUISENOPLAY);
	SetDlgItemTextEx(IDC_STATIC_8D1_ACTION,IDS_CONFIG_8D1_ACTION);
	SetDlgItemTextEx(IDC_CHECK_8D1_CRUISEENABLE,IDS_CONFIG_8D1_CRUISEENABLE);
	SetDlgItemTextEx(IDC_BUTTON_8D1_CRUISE,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_CRUISE_START,IDS_CFG_CRUISE_START);
	SetDlgItemTextEx(IDC_BUTTON_CRUISE_STOP,IDS_CFG_CRUISE_STOP);
	SetDlgItemTextEx(IDC_BUTTON_TRACK_START,IDS_CFG_TRACK_START);
	SetDlgItemTextEx(IDC_BUTTONT_TRACK_STOP,IDS_CFG_TRACK_STOP);
}

void CLS_8D1Page::OnBnClickedButton8d1Cruise()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	
	int iCruiseNo = GetDlgItemInt(IDC_COMBO_8D1_CRUISENO);
	int iEnable = (m_chkCruiseEnable.GetCheck() == BST_CHECKED)?1:0;
	int iCruiseNum = m_cboCruiseNum.GetCurSel();
	st_PTZCruise stPtzCruise = {0};
	for (int i=0; i<4; i++)
	{
		stPtzCruise.iPreset[i] = m_cboPreset[i].GetCurSel()+1;
		stPtzCruise.iStayTime[i] = m_cboStayTime[i].GetCurSel()+1;
		stPtzCruise.iSpeed[i] = m_cboSpeed[i].GetCurSel();
	}
	int iRet = NetClient_SetCHNPTZCRUISE(m_iLogonID, m_iChannelNo, iCruiseNo, iEnable, iCruiseNum, &stPtzCruise);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetCHNPTZCRUISE(%d,%d,%d,%d,%d)",m_iLogonID, m_iChannelNo, iCruiseNo, iEnable, iCruiseNum);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetCHNPTZCRUISE(%d,%d,%d,%d,%d)",m_iLogonID, m_iChannelNo, iCruiseNo, iEnable, iCruiseNum);
	}
}

BOOL CLS_8D1Page::UI_UpdateCruise()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iCruiseNo = GetDlgItemInt(IDC_COMBO_8D1_CRUISENO);
	int iEnable = 0;
	int iCruiseNum = 0;
	st_PTZCruise stPtzCruise = {0};
	int iRet = NetClient_GetCHNPTZCRUISE(m_iLogonID, m_iChannelNo, iCruiseNo, &iEnable, &iCruiseNum, &stPtzCruise);
	if (0 == iRet)
	{
		m_cboCruiseNum.SetCurSel(iCruiseNum);
		m_chkCruiseEnable.SetCheck(iEnable?BST_CHECKED:BST_UNCHECKED);
		for (int i=0; i<4; i++)
		{
			m_cboPreset[i].SetCurSel(stPtzCruise.iPreset[i]-1);
			m_cboStayTime[i].SetCurSel(stPtzCruise.iStayTime[i]-1);
			m_cboSpeed[i].SetCurSel(stPtzCruise.iSpeed[i]);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetCHNPTZCRUISE(%d,%d,%d,%d,%d)",m_iLogonID, m_iChannelNo, iCruiseNo, iEnable, iCruiseNum);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetCHNPTZCRUISE(%d,%d,%d,%d,%d)",m_iLogonID, m_iChannelNo, iCruiseNo, iEnable, iCruiseNum);
	}
	UI_EnableCruise(iCruiseNum);
	return TRUE;
}

void CLS_8D1Page::OnCbnSelchangeCombo8d1Cruiseno()
{
	UI_UpdateCruise();
}

void CLS_8D1Page::UI_EnableCruise( int _iNum )
{
	if (_iNum < 0)
	{
		_iNum = 0;
	}
	if (_iNum > 4)
	{
		_iNum = 4;
	}
	for (int i = 0; i < _iNum; ++i)
	{
		m_cboPreset[i].EnableWindow(TRUE);
		m_cboStayTime[i].EnableWindow(TRUE);
		m_cboSpeed[i].EnableWindow(TRUE);
	}
	for (int i = _iNum; i < 4; ++i)
	{
		m_cboPreset[i].EnableWindow(FALSE);
		m_cboStayTime[i].EnableWindow(FALSE);
		m_cboSpeed[i].EnableWindow(FALSE);
	}
}

void CLS_8D1Page::OnCbnSelchangeCombo8d1Cruisenum()
{
	UI_EnableCruise(m_cboCruiseNum.GetCurSel());
}

void CLS_8D1Page::OnBnClickedButtonCruiseStart()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iCruiseNo = GetDlgItemInt(IDC_COMBO_8D1_CRUISENO);
	int iRet = NetClient_DeviceCtrlEx(m_iLogonID, m_iChannelNo, PROTOCOL_START_TRACK_CRUISE, iCruiseNo, 0, 0);	
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_DeviceCtrlEx(%d,%d,%d,%d)",m_iLogonID, m_iChannelNo, PROTOCOL_START_TRACK_CRUISE,iCruiseNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_DeviceCtrlEx(%d,%d,%d,%d)",m_iLogonID, m_iChannelNo, PROTOCOL_START_TRACK_CRUISE,iCruiseNo);
	}
}

void CLS_8D1Page::OnBnClickedButtonCruiseStop()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iCruiseNo = GetDlgItemInt(IDC_COMBO_8D1_CRUISENO);
	int iRet = NetClient_DeviceCtrlEx(m_iLogonID, m_iChannelNo, PROTOCOL_STOP_TRACK_CRUISE, iCruiseNo, 0, 0);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_DeviceCtrlEx(%d,%d,%d,%d)",m_iLogonID, m_iChannelNo, PROTOCOL_STOP_TRACK_CRUISE,iCruiseNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_DeviceCtrlEx(%d,%d,%d,%d)",m_iLogonID, m_iChannelNo,PROTOCOL_STOP_TRACK_CRUISE, iCruiseNo);
	}
}

void CLS_8D1Page::OnBnClickedButtonTrackStart()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iCruiseNo = GetDlgItemInt(IDC_COMBO_8D1_CRUISENO);
	//轨迹只能设置1条
	int iRet = NetClient_DeviceCtrlEx(m_iLogonID, m_iChannelNo, PTZ_START_ROUTINE, 0, 0, 0);	
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_DeviceCtrlEx(%d,%d,%d)",m_iLogonID, m_iChannelNo, PTZ_START_ROUTINE);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_DeviceCtrlEx(%d,%d,%d)",m_iLogonID, m_iChannelNo, PTZ_START_ROUTINE);
	}	
}

void CLS_8D1Page::OnBnClickedButtontTrackStop()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iCruiseNo = GetDlgItemInt(IDC_COMBO_8D1_CRUISENO);
	int iRet = NetClient_DeviceCtrlEx(m_iLogonID, m_iChannelNo, PTZ_STOP_ROUTINE, 0, 0, 0);	
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_DeviceCtrlEx(%d,%d,%d)",m_iLogonID, m_iChannelNo, PTZ_STOP_ROUTINE);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_DeviceCtrlEx(%d,%d,%d)",m_iLogonID, m_iChannelNo, PTZ_STOP_ROUTINE);
	}
}

void CLS_8D1Page::OnBnClickedCheck8d1Cruiseenable()
{
	int iEnable = 0;
	int iCruiseNum = 0;
	int iCruiseNo = m_cboCruiseNo.GetCurSel();
	st_PTZCruise tPTZCruise = {0};

	int iRet = NetClient_GetCHNPTZCRUISE(m_iLogonID, m_iChannelNo, iCruiseNo, &iEnable, &iCruiseNum, &tPTZCruise);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetCHNPTZCRUISE(%d,%d,%d,%d)",m_iLogonID, m_iChannelNo, iCruiseNo, iEnable);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetCHNPTZCRUISE(%d,%d,%d,%d)",m_iLogonID, m_iChannelNo, iCruiseNo, iEnable);
	}

	
	iEnable = m_chkCruiseEnable.GetCheck();
	iRet = NetClient_SetCHNPTZCRUISE(m_iLogonID, m_iChannelNo, iCruiseNo, iEnable, iCruiseNum, &tPTZCruise);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetCHNPTZCRUISE(%d,%d,%d,%d)",m_iLogonID, m_iChannelNo, iCruiseNo, iEnable);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetCHNPTZCRUISE(%d,%d,%d,%d)",m_iLogonID, m_iChannelNo, iCruiseNo, iEnable);
	}
}
