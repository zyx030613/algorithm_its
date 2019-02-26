// BurnH8.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "BurnH8Page.h"


// CLS_BurnH8 dialog

IMPLEMENT_DYNAMIC(CLS_BurnH8Page, CDialog)

CLS_BurnH8Page::CLS_BurnH8Page(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_BurnH8Page::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_BurnH8Page::~CLS_BurnH8Page()
{
}

void CLS_BurnH8Page::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOH8_MONITOR_TYPE, m_cboMonitorType);
	DDX_Control(pDX, IDC_COMBO_H8_MONSTATUS, m_cboMonitorStatus);
	DDX_Control(pDX, IDC_EDIT_H8_REALVALUE1, m_edtRealValue1);
	DDX_Control(pDX, IDC_EDIT_H8_REALVALUE2, m_edtRealValue2);
	DDX_Control(pDX, IDC_EDIT_H8_REALVALUE3, m_edtRealValue3);
	DDX_Control(pDX, IDC_EDIT_H8_REALVALUE4, m_edtRealValue4);
	DDX_Control(pDX, IDC_COMBO_H8_GRAM_ID, m_cboGramID);
	DDX_Control(pDX, IDC_EDIT_H8_GRAM_RATE, m_edtGramRate);
	DDX_Control(pDX, IDC_EDIT_H8_TOTAL_POINTS_NUM, m_edtTotalPoints);
	DDX_Control(pDX, IDC_EDIT_H8_POINTS_VALUE, m_edtPointsValue);
	DDX_Control(pDX, IDC_COMBOH8_MONITOR_TYPE_CFG, m_cboCfgMonitorType);
	DDX_Control(pDX, IDC_COMBOH8_CMD_ID, m_cboCfgCmdID);
	DDX_Control(pDX, IDC_COMBO_H8_CMD_CONTENT, m_cboCfgCmdContent);
	DDX_Control(pDX, IDC_COMBO_H8_GRAM_SEQ, m_cboGramSeq);
}


BEGIN_MESSAGE_MAP(CLS_BurnH8Page, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_H8_SET_CONFIG, &CLS_BurnH8Page::OnBnClickedButtonH8SetConfig)
	ON_CBN_SELCHANGE(IDC_COMBOH8_CMD_ID, &CLS_BurnH8Page::OnCbnSelchangeComboh8CmdId)
	ON_CBN_SELCHANGE(IDC_COMBO_H8_GRAM_SEQ, &CLS_BurnH8Page::OnCbnSelchangeComboH8GramSeq)
	ON_CBN_SELCHANGE(IDC_COMBOH8_MONITOR_TYPE, &CLS_BurnH8Page::OnCbnSelchangeComboh8MonitorType)
	ON_CBN_SELCHANGE(IDC_COMBO_H8_GRAM_ID, &CLS_BurnH8Page::OnCbnSelchangeComboH8GramId)
	ON_CBN_SELCHANGE(IDC_COMBOH8_MONITOR_TYPE_CFG, &CLS_BurnH8Page::OnCbnSelchangeComboh8MonitorTypeCfg)
END_MESSAGE_MAP()


// CLS_BurnH8 message handlers

BOOL CLS_BurnH8Page::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here

	UI_UpdateDialogText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_BurnH8Page::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	UpdateLifeMonitorConfigInfo();
	UpdateLifeMonitorHBRealInfo();
	UpdateLifeMonitorGramRealInfo();
}

void CLS_BurnH8Page::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialogText();
}

void CLS_BurnH8Page::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_STATIC__H8_HB_REAL, IDS_BURN_H8_HB_REAL);
	SetDlgItemTextEx(IDC_STATIC_H8_GRAM_REAL, IDS_BURN_H8_GRAM_REAL);
	SetDlgItemTextEx(IDC_STATIC_H8_CONFIG, IDS_CONFIG);
	SetDlgItemTextEx(IDC_STATIC_H8_MONITOR_TYPE, IDS_BURN_H8_MONITOR_TYPE);
	SetDlgItemTextEx(IDC_STATIC_MONITOR_STATUS, IDS_BURN_H8_MONITOR_STATUS);
	SetDlgItemTextEx(IDC_STATIC_H8_REALVALUE1, IDS_BURN_H8_REAL_VALUE);
	SetDlgItemTextEx(IDC_STATIC_H8_REALVALUE2, IDS_BURN_H8_REAL_VALUE2);
	SetDlgItemTextEx(IDC_STATIC_H8_REALVALUE3, IDS_BURN_H8_REAL_VALUE3);
	SetDlgItemTextEx(IDC_STATIC_H8_REALVALUE4, IDS_BURN_H8_REAL_VALUE4);
	SetDlgItemTextEx(IDC_STATIC_H8_GRAM_ID, IDS_BURN_H8_GRAM_ID);
	SetDlgItemTextEx(IDC_STATIC_H8_GRAM_SEQ, IDS_BURN_H8_GRAM_SEQ);
	SetDlgItemTextEx(IDC_STATIC_H8_GRAM_RATE, IDS_BURN_H8_GRAM_RATE);
	SetDlgItemTextEx(IDC_STATIC_H8TOTAL_POINTS, IDS_BURN_H8_TOTAL_POINTS);
	SetDlgItemTextEx(IDC_STATIC_H8_MONITOR_TYPE_CFG, IDS_BURN_H8_MONITOR_TYPE);
	SetDlgItemTextEx(IDC_STATIC_H8_CMD_ID, IDS_BURN_H8_COM_ID);
	SetDlgItemTextEx(IDC_STATIC_H8_CMD_CONTENT, IDS_BURN_H8_CMD_CONTENT);
	SetDlgItemTextEx(IDC_BUTTON_H8_SET_CONFIG, IDS_SET);

	InsertString(m_cboMonitorType, 0, IDS_BURN_H8_HEARTRATE);
	InsertString(m_cboMonitorType, 1, IDS_BURN_H8_OXYGEN);
	InsertString(m_cboMonitorType, 2, IDS_BURN_H8_BLOOD_PRESSURE);
	m_cboMonitorType.SetCurSel(0);
	InsertString(m_cboMonitorStatus, 0, IDS_NORMAL);
	InsertString(m_cboMonitorStatus, 1, IDS_BURN_H8_OVER_UP);
	InsertString(m_cboMonitorStatus, 2, IDS_BURN_H8_OVER_DOWN);
	InsertString(m_cboMonitorStatus, 3, IDS_BURN_H8_LOST);
	InsertString(m_cboMonitorStatus, 4, IDS_BURN_H8_DEVICE_OFFLINE);
	m_cboMonitorStatus.SetCurSel(0);
	InsertString(m_cboGramID, 0, IDS_BURN_H8_Electrocardiographic);
	InsertString(m_cboGramID, 1, IDS_BURN_H8_Oxygen_wave);
	m_cboGramID.SetCurSel(0);
	InsertString(m_cboCfgMonitorType, 0, IDS_BURN_H8_HEARTRATE);
	InsertString(m_cboCfgMonitorType, 1, IDS_BURN_H8_OXYGEN);
	InsertString(m_cboCfgMonitorType, 2, IDS_BURN_H8_BLOOD_PRESSURE);
	InsertString(m_cboCfgMonitorType, 3, IDS_PLAYBACK_TYPE_ALL);
	m_cboCfgMonitorType.SetCurSel(0);
	InsertString(m_cboCfgCmdID, 0, IDS_BURN_H8_REPORT_IE);
	InsertString(m_cboCfgCmdID, 1, IDS_BURN_H8_OSD);
	m_cboCfgCmdID.SetCurSel(0);
	if(0 == m_cboCfgCmdID.GetCurSel())
	{
		InsertString(m_cboCfgCmdContent, 0, IDS_BURN_H8_REPORT_IE_NO);
		InsertString(m_cboCfgCmdContent, 1, IDS_BURN_H8_REPORT_IE_YES);
	}
	else
	{
		InsertString(m_cboCfgCmdContent, 0, IDS_BURN_H8_NOT_OSD);
		InsertString(m_cboCfgCmdContent, 1, IDS_BURN_H8_YES_OSD);
	}
	m_cboCfgCmdContent.SetCurSel(0);

	if (0 == m_cboGramID.GetCurSel())
	{
		m_cboGramSeq.ResetContent();
		m_cboGramSeq.AddString("1");
		m_cboGramSeq.AddString("2");
		m_cboGramSeq.AddString("3");
	}
	else
	{
		m_cboGramSeq.ResetContent();
		m_cboGramSeq.AddString("1");
	}

	m_cboGramSeq.SetCurSel(0);
}

void CLS_BurnH8Page::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser )
{
	if (_ulLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",_ulLogonID);
		return;
	}

	int iMessage = _iWparam & 0xFFFF;
	switch (iMessage)
	{
	case WCM_LIFEMONITOR_HBREAL:
		UpdateLifeMonitorHBRealInfo();
		break;
	case WCM_LIFEMONITOR_GRAMREAl:
		UpdateLifeMonitorGramRealInfo();
		break;
	default:
		break;
	}
}

void CLS_BurnH8Page::OnParamChangeNotify( int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUser )
{
	switch(_iParaType)
	{
	case PARA_LIFEMONITOR_SET_CONFIG:
		UpdateLifeMonitorConfigInfo();
		break;
	default:
		break;
	}
}

void CLS_BurnH8Page::OnBnClickedButtonH8SetConfig()
{
	LifeMonitorConfig tPara = {0};
	tPara.iSize = sizeof(LifeMonitorConfig);
	tPara.iMonType = m_cboCfgMonitorType.GetCurSel() + 1;
	tPara.iCmdID = m_cboCfgCmdID.GetCurSel() + 1;
	tPara.iCmdContent = m_cboCfgCmdContent.GetCurSel();
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_LIFEMONITOR_SET_CONFIG
		, 0, &tPara, sizeof(LifeMonitorConfig));
	if (iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_LIFEMONITOR_SET_CONFIG] (%d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_LIFEMONITOR_SET_CONFIG] (%d)",m_iLogonID);
	}
}

void CLS_BurnH8Page::UpdateLifeMonitorConfigInfo()
{
	LifeMonitorConfig tPara = {0};
	tPara.iSize = sizeof(LifeMonitorConfig);
	tPara.iMonType = m_cboCfgMonitorType.GetCurSel() + 1;
	tPara.iCmdID = m_cboCfgCmdID.GetCurSel() + 1;
	int iBytesReturned = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_LIFEMONITOR_SET_CONFIG
		, 0, &tPara, sizeof(LifeMonitorConfig), &iBytesReturned);
	if (iRet == 0)
	{
		m_cboCfgCmdContent.SetCurSel(tPara.iCmdContent);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_LIFEMONITOR_SET_CONFIG] (%d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_LIFEMONITOR_SET_CONFIG] (%d)",m_iLogonID);
	}
}

void CLS_BurnH8Page::UpdateLifeMonitorHBRealInfo()
{
	LifeMonitorHBReal tPara = {0};
	tPara.iSize = sizeof(LifeMonitorHBReal);
	tPara.iMonType = m_cboMonitorType.GetCurSel() + 1;
	int iBytesReturned = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_GET_LIFEMONITOR_HBREAL
		, 0, &tPara, sizeof(LifeMonitorHBReal), &iBytesReturned);
	if (iRet == 0)
	{
		if (tPara.iMonStatus > 0)
		{
			m_cboMonitorStatus.SetCurSel(tPara.iMonStatus - 1);
		}
		SetDlgItemInt(IDC_EDIT_H8_REALVALUE1, tPara.iMonRealVal1);
		SetDlgItemInt(IDC_EDIT_H8_REALVALUE2, tPara.iMonRealVal2);
		SetDlgItemInt(IDC_EDIT_H8_REALVALUE3, tPara.iMonRealVal3);
		SetDlgItemInt(IDC_EDIT_H8_REALVALUE4, tPara.iMonRealVal4);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_GET_LIFEMONITOR_HBREAL] (%d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_GET_LIFEMONITOR_HBREAL] (%d)",m_iLogonID);
	}
}

void CLS_BurnH8Page::UpdateLifeMonitorGramRealInfo()
{
	LifeMonitorGramReal tPara = {0};
	tPara.iSize = sizeof(LifeMonitorGramReal);
	tPara.iOscilloGramID = m_cboGramID.GetCurSel() + 1;
	tPara.iGramSeq = m_cboGramSeq.GetCurSel() + 1;
	int iBytesReturned = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_GET_LIFEMONITOR_GRAMREAl
		, 0, &tPara, sizeof(LifeMonitorGramReal), &iBytesReturned);
	if (iRet == 1)
	{
		int	iPointCount = tPara.iPointCount;
		if (iPointCount > 0)
		{
			tPara.piPoints = (int*)malloc(iPointCount * sizeof(int));
			if (tPara.piPoints == NULL)
			{
				return;
			}
			int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_GET_LIFEMONITOR_GRAMREAl
				, 0, &tPara, sizeof(LifeMonitorGramReal), &iBytesReturned);
			if (iRet == 0)
			{
				SetDlgItemInt(IDC_EDIT_H8_GRAM_RATE, tPara.iGramRate);
				SetDlgItemInt(IDC_EDIT_H8_TOTAL_POINTS_NUM, tPara.iPointCount);
				string strPoints;
				int iSeq = 0;
				for (int i=0; i<iPointCount; ++i)
				{
					iSeq++;
					char cTmp[32] = {0};
					if (0 == iSeq%LEN_16)
					{
						sprintf_s(cTmp, "%d\r\n", tPara.piPoints[i]);
					}
					else
					{
						sprintf_s(cTmp, "%d,", tPara.piPoints[i]);
					}
					
					strPoints += string(cTmp);
				}
				m_edtPointsValue.SetWindowText(strPoints.c_str());
				AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_GET_LIFEMONITOR_GRAMREAl] (%d)",m_iLogonID);
			}
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_GET_LIFEMONITOR_GRAMREAl] (%d)",m_iLogonID);
	}	
}

void CLS_BurnH8Page::OnCbnSelchangeComboh8CmdId()
{
	// TODO: Add your control notification handler code here
	if (0 == m_cboCfgCmdID.GetCurSel())
	{
		m_cboCfgCmdContent.ResetContent();
		InsertString(m_cboCfgCmdContent, 0, IDS_BURN_H8_REPORT_IE_NO);
		InsertString(m_cboCfgCmdContent, 1, IDS_BURN_H8_REPORT_IE_YES);
	}
	else
	{
		m_cboCfgCmdContent.ResetContent();
		InsertString(m_cboCfgCmdContent, 0, IDS_BURN_H8_NOT_OSD);
		InsertString(m_cboCfgCmdContent, 1, IDS_BURN_H8_YES_OSD);
	}

	UpdateLifeMonitorConfigInfo();
}

void CLS_BurnH8Page::OnCbnSelchangeComboH8GramSeq()
{
	// TODO: Add your control notification handler code here
	UpdateLifeMonitorGramRealInfo();
}

void CLS_BurnH8Page::OnCbnSelchangeComboh8MonitorType()
{
	// TODO: Add your control notification handler code here
	UpdateLifeMonitorHBRealInfo();
}

void CLS_BurnH8Page::OnCbnSelchangeComboH8GramId()
{
	// TODO: Add your control notification handler code here
	if (0 == m_cboGramID.GetCurSel())
	{
		m_cboGramSeq.ResetContent();
		m_cboGramSeq.AddString("1");
		m_cboGramSeq.AddString("2");
		m_cboGramSeq.AddString("3");
	}
	else
	{
		m_cboGramSeq.ResetContent();
		m_cboGramSeq.AddString("1");
	}

	m_cboGramSeq.SetCurSel(0);

	UpdateLifeMonitorGramRealInfo();
}

void CLS_BurnH8Page::OnCbnSelchangeComboh8MonitorTypeCfg()
{
	// TODO: Add your control notification handler code here
	UpdateLifeMonitorConfigInfo();
}
