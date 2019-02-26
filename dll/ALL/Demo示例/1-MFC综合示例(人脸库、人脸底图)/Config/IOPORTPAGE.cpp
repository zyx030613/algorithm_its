// LS_IOPORTPAGE.cpp : implementation file
//

#include "stdafx.h"
#include "IOPORTPAGE.h"


// CLS_IOPORTPAGE dialog
#define ENABLE 1

IMPLEMENT_DYNAMIC(CLS_IOPORTPAGE, CDialog)

CLS_IOPORTPAGE::CLS_IOPORTPAGE(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_IOPORTPAGE::IDD, pParent)
{
	m_iLogonID = -1;
	for(int i = 0; i < LEN_16; i++)
	{
		m_iEnable[i] = 0;
	}

}

CLS_IOPORTPAGE::~CLS_IOPORTPAGE()
{
}

void CLS_IOPORTPAGE::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ALARMINPORT, m_cmbAlarmInPortID);
	DDX_Control(pDX, IDC_COMBO_ALARMINMODE, m_cmbAlarmInModeID);
	DDX_Control(pDX, IDC_COMBOALARMOUTMODE, m_cmbAlarmOutModeID);
	//DDX_Control(pDX, IDC_CHECK_ALARMOUTPORT_ENABLE, m_chkAlarmOutPortEnable);

	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE0, m_chkOutPortEnable[0]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE1, m_chkOutPortEnable[1]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE2, m_chkOutPortEnable[2]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE3, m_chkOutPortEnable[3]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE4, m_chkOutPortEnable[4]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE5, m_chkOutPortEnable[5]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE6, m_chkOutPortEnable[6]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE7, m_chkOutPortEnable[7]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE8, m_chkOutPortEnable[8]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE9, m_chkOutPortEnable[9]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE10, m_chkOutPortEnable[10]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE11, m_chkOutPortEnable[11]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE12, m_chkOutPortEnable[12]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE13, m_chkOutPortEnable[13]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE14, m_chkOutPortEnable[14]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE15, m_chkOutPortEnable[15]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE16, m_chkOutPortEnable[16]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE17, m_chkOutPortEnable[17]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE18, m_chkOutPortEnable[18]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE19, m_chkOutPortEnable[19]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE20, m_chkOutPortEnable[20]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE21, m_chkOutPortEnable[21]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE22, m_chkOutPortEnable[22]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE23, m_chkOutPortEnable[23]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE24, m_chkOutPortEnable[24]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE25, m_chkOutPortEnable[25]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE26, m_chkOutPortEnable[26]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE27, m_chkOutPortEnable[27]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE28, m_chkOutPortEnable[28]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE29, m_chkOutPortEnable[29]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE30, m_chkOutPortEnable[30]);
	DDX_Control(pDX, IDC_CHECK_OUTPORTENABLE31, m_chkOutPortEnable[31]);

	DDX_Control(pDX, IDC_COMBO_ALARMOUTPORT, m_cmbAlarmOutPortID);
	DDX_Control(pDX, IDC_COMBO_STOPAMODE, m_cmbStopModeID);
	DDX_Control(pDX, IDC_COMBO_IOPORT_NUM, m_cmbInPortChnID);
	DDX_Control(pDX, IDC_COMBO_ALARMOUTPORT_NUM, m_cmbAlarmActiveModeOutPortID);
	DDX_Control(pDX, IDC_EDIT_DELAYTIME, m_edtAlarmDelayTimeID);
	DDX_Control(pDX, IDC_CHECK_ALARMPORT, m_chkAlarmPortEnableID);
	DDX_Control(pDX, IDC_COMBO_OUTPORTSTATUS, m_cmbAlarmOutPortStatusID);
}


BEGIN_MESSAGE_MAP(CLS_IOPORTPAGE, CLS_BasePage)
	ON_BN_CLICKED(IDC_ALARMINMODE, &CLS_IOPORTPAGE::OnBnClickedAlarminmode)
	ON_BN_CLICKED(IDC_BUTTONAlARMOUTMODE, &CLS_IOPORTPAGE::OnBnClickedButtonalarmoutmode)
	//ON_BN_CLICKED(IDC_CHECK_ALARMOUTPORT_ENABLE, &CLS_IOPORTPAGE::OnBnClickedCheckAlarmoutportEnable)
	ON_BN_CLICKED(IDC_BUTTON_ALARMLINK_SET, &CLS_IOPORTPAGE::OnBnClickedButtonAlarmlinkSet)
	ON_BN_CLICKED(IDC_BUTTON_STOPAMODE_SET, &CLS_IOPORTPAGE::OnBnClickedButtonStopamodeSet)
	ON_BN_CLICKED(IDC_CHECK_ALARMPORT, &CLS_IOPORTPAGE::OnBnClickedCheckAlarmport)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARMINPORT, &CLS_IOPORTPAGE::OnCbnSelchangeComboAlarminport)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARMOUTPORT_NUM, &CLS_IOPORTPAGE::OnCbnSelchangeComboalarmoutport)
	ON_CBN_SELCHANGE(IDC_COMBO_IOPORT_NUM, &CLS_IOPORTPAGE::OnCbnSelchangeComboIoportNum)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARMOUTPORT, &CLS_IOPORTPAGE::OnCbnSelchangeComboAlarmoutport)
	ON_EN_CHANGE(IDC_EDIT_DELAYTIME, &CLS_IOPORTPAGE::OnEnChangeEditDelaytime)
	ON_BN_CLICKED(IDC_BUTTON_ALARMOUTPORT_ENABLE_SET, &CLS_IOPORTPAGE::OnBnClickedButtonAlarmoutportEnableSet)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_CHECK_OUTPORTENABLE0,IDC_CHECK_OUTPORTENABLE31,&CLS_IOPORTPAGE::OnBnClickedChkChannel)
END_MESSAGE_MAP()


// CLS_IOPORTPAGE message handlers
BOOL CLS_IOPORTPAGE::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_cmbAlarmInModeID.SetCurSel(0);
	m_cmbAlarmInPortID.SetCurSel(0);
	m_cmbAlarmOutModeID.SetCurSel(0);
	m_cmbAlarmOutPortID.SetCurSel(0);
	m_cmbStopModeID.SetCurSel(0);
	SetDlgItemText(IDC_EDIT_DELAYTIME, "0");
	m_edtAlarmDelayTimeID.SetLimitText(2); 
 	m_cmbAlarmOutPortStatusID.AddString(_T("0-OFF"));
 	m_cmbAlarmOutPortStatusID.AddString(_T("1-ON"));
	m_cmbAlarmOutPortStatusID.SetCurSel(-1);
	//m_cmbAlarmOutPortStatusID.EnableWindow(FALSE);
	UI_UpdateDialog();
	UI_UpdateIOPortParam();

	return TRUE;
}

//Paramchanged
void CLS_IOPORTPAGE::OnChannelChanged(int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;

	UI_UpdateIOPortParam();
}

//chineseToEnglish 
void CLS_IOPORTPAGE::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_IOPORTPAGE::UI_UpdateDialog()
{
	//SetDlgItemTextEx(IDC_STATIC_ROADWAYID,IDS_CONFIG_ECOP_ROADWAYID);
	SetDlgItemTextEx(IDC_ALARMINMODE,IDS_IOPORT_SETID);
	SetDlgItemTextEx(IDC_BUTTONAlARMOUTMODE,IDS_IOPORT_SETID);
	SetDlgItemTextEx(IDC_BUTTON_ALARMLINK_SET,IDS_IOPORT_SETID);
	SetDlgItemTextEx(IDC_BUTTON_STOPAMODE_SET,IDS_IOPORT_SETID);
	SetDlgItemTextEx(IDC_BUTTON_ALARMOUTPORT_ENABLE_SET,IDS_IOPORT_SETID);

	SetDlgItemTextEx(IDC_STATIC_ACTIVEMODE_SET,IDS_IOPORT_ACTIVEMODE);
	SetDlgItemTextEx(IDC_STATIC_ALARMINMODE,IDS_IOPORT_ALARMINPORT);
	SetDlgItemTextEx(IDC_STATIC_ALARMOUTPORT,IDS_IOPORT_ALARMINMODE);
	SetDlgItemTextEx(IDC_STATIC_OUTPORTSTATUS,IDS_IOPORT_OUTPORTSTATUS);
	//SetDlgItemTextEx(IDC_CHECK_ALARMOUTPORT_ENABLE,IDS_IOPORT_OUTPORT_ENABLE);

	SetDlgItemTextEx(IDC_STATIC_LINKSET,IDS_IOPORT_LINK_SET);
	SetDlgItemTextEx(IDC_STATIC_LINKSET_INPORT,IDS_IOPORT_INPORT);
	SetDlgItemTextEx(IDC_STATIC_LINKSET_OUTPORT,IDS_IOPORT_OUTPORT);
	SetDlgItemTextEx(IDC_CHECK_ALARMPORT,IDS_IOPORT_ALARMPORT_ENABLE);

	SetDlgItemTextEx(IDC_STATIC_ALARMOUTPORTDVR,IDS_IOPORT_ALARMOUTPORTDVR);
	SetDlgItemTextEx(IDC_STATIC_ALARMOUTPORT_OUTPORT,IDS_IOPORT_OUTPORTDVR);
	SetDlgItemTextEx(IDC_STATIC__ALARMOUTPORT_STOPALARMMODE,IDS_IOPORT_STOPALARMPORT);
	SetDlgItemTextEx(IDC_STATIC_ALARMOUTPORT_DELAYTIMES,IDS_IOPORT_DELAYTIME);
}

void CLS_IOPORTPAGE::OnBnClickedAlarminmode()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	//int iAlarmInPort = m_cmbAlarmInPortID.GetCurSel();
	int iAlarmInPort = m_cmbAlarmInPortID.GetCurSel();
	int iAlarmInMode = m_cmbAlarmInModeID.GetCurSel();
    
	int iRet = NetClient_SetAlarmInMode(m_iLogonID, iAlarmInPort, iAlarmInMode);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetAlarmInMode (%d,%d,%d)",m_iLogonID,iAlarmInPort,iAlarmInMode);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetAlarmInMode (%d,%d,%d)",m_iLogonID,iAlarmInPort,iAlarmInMode);
	}
}

void CLS_IOPORTPAGE::OnBnClickedButtonalarmoutmode()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	
	int iAlarmOutPort = m_cmbAlarmActiveModeOutPortID.GetCurSel();
    int iAlarmOutMode = m_cmbAlarmOutModeID.GetCurSel();
    int iPulseWidth = 0;
	int iRet = NetClient_SetAlarmOutMode(m_iLogonID, iAlarmOutPort, iAlarmOutMode, iPulseWidth);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetAlarmOutMode (%d,%d,%d)",m_iLogonID,iAlarmOutPort,iAlarmOutMode);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetAlarmOutMode (%d,%d,%d)",m_iLogonID,iAlarmOutPort,iAlarmOutMode);
	}
}

//void CLS_IOPORTPAGE::OnBnClickedCheckAlarmoutportEnable()
//{
//	// TODO: Add your control notification handler code here
//
//	if (m_iLogonID < 0)
//	{
//		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
//		return;
//	}
//
//	int iAlarmOutPort = GetDlgItemInt(IDC_COMBO_ALARMOUTPORT_NUM);
//	int iRet = NetClient_SetOutPortState(m_iLogonID, iAlarmOutPort, m_chkAlarmOutPortEnable.GetCheck());
//	if (0 == iRet)
//	{
//		AddLog(LOG_TYPE_SUCC,"","NetClient_SetOutPortState (%d,%d,%d)",m_iLogonID,iAlarmOutPort,m_chkAlarmOutPortEnable.GetCheck());
//	} 
//	else
//	{
//		AddLog(LOG_TYPE_FAIL,"","NetClient_SetOutPortState (%d,%d,%d)",m_iLogonID,iAlarmOutPort,m_chkAlarmOutPortEnable.GetCheck());
//	}
//
//}

void CLS_IOPORTPAGE::OnBnClickedChkChannel(UINT _uiID)
{
	int index = _uiID - IDC_CHECK_OUTPORTENABLE0;

	if (m_chkOutPortEnable[index].GetCheck() == BST_CHECKED)
	{
		m_iEnable[index/LEN_32] |= 1<<index%LEN_32;
	}
	else 
	{
		m_iEnable[index/LEN_32] &= ~(1<<index%LEN_32);
	}

	return;
}

void CLS_IOPORTPAGE::OnBnClickedButtonAlarmlinkSet()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	TAlarmLinkParam_V1 tAlarmLinkPara = {0};
	tAlarmLinkPara.iLinkParamSize = sizeof(TAlarmLinkParam_V1);
	tAlarmLinkPara.iLinkType = ALARMLINKTYPE_LINKOUTPORT;
	for(int i = 0; i < LEN_16; i++)
	{
		tAlarmLinkPara.iChannelSet[i] = m_iEnable[i];
	}

	int iChannelNo = m_cmbInPortChnID.GetCurSel();
	int iRet = NetClient_SetAlarmConfig(m_iLogonID, iChannelNo, ALARM_TYPE_PORT_ALARM, CMD_GET_ALARMLINK_V2, &tAlarmLinkPara);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetAlarmConfig (%d,%d)",m_iLogonID,iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetAlarmConfig (%d,%d)",m_iLogonID,iChannelNo);
	}

}

void CLS_IOPORTPAGE::OnBnClickedButtonStopamodeSet()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iPortNum = m_cmbAlarmOutPortID.GetCurSel();
	int iClearType = m_cmbStopModeID.GetCurSel();

	int iDelayTime = GetDlgItemInt(IDC_EDIT_DELAYTIME);
	if(iPortNum < 0)
	{
		iPortNum = 0;
	}
	int iRet = NetClient_SetOutportAlarmDelay(m_iLogonID,iPortNum,iClearType,iDelayTime);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetOutportAlarmDelay (%d,%d,%d)",m_iLogonID,iPortNum,iClearType,iDelayTime);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetOutportAlarmDelay (%d,%d,%d)",m_iLogonID,iPortNum,iClearType,iDelayTime);
	}
} 

void CLS_IOPORTPAGE::OnBnClickedCheckAlarmport()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iRet = -1;
	int iIfEnable = -1;
	int iInPortNum = m_cmbInPortChnID.GetCurSel();
	if(m_chkAlarmPortEnableID.GetCheck())
	{
		/*iRet = NetClient_SetAlarmPortEnable(m_iLogonID,iInPortNum,ENABLE);*/
		iRet = NetClient_SetInportEnable(m_iLogonID, iInPortNum, ENABLE);
		iIfEnable = ENABLE;
	}	
	else
	{
		/*iRet = NetClient_SetAlarmPortEnable(m_iLogonID,iInPortNum,DISABLE);*/
		iRet = NetClient_SetInportEnable(m_iLogonID, iInPortNum, DISABLE);
		iIfEnable = DISABLE;
	}	
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetAlarmPortEnable (%d,%d,%d)",m_iLogonID,iInPortNum,iIfEnable);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetAlarmPortEnable (%d,%d,%d)",m_iLogonID,iInPortNum,iIfEnable);
	}

}

void CLS_IOPORTPAGE::OnCbnSelchangeComboAlarminport()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iInLowOrHigh = -1;
	int iInPortNum = m_cmbAlarmInPortID.GetCurSel();
	if (0 == NetClient_GetAlarmInMode(m_iLogonID,iInPortNum,&iInLowOrHigh))
	{
		m_cmbAlarmInModeID.SetCurSel(iInLowOrHigh);
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetAlarmInMode(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_GetAlarmInMode(%d)", m_iLogonID);
	}

}

void CLS_IOPORTPAGE::OnCbnSelchangeComboalarmoutport()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iOutLowOrHigh = -1;
	int iPulseWidth = -1;
	int iOutPortNum = m_cmbAlarmActiveModeOutPortID.GetCurSel();;
	if (0 == NetClient_GetAlarmOutMode(m_iLogonID,iOutPortNum,&iOutLowOrHigh,&iPulseWidth))
	{
		m_cmbAlarmOutModeID.SetCurSel(iOutLowOrHigh);
	}
	int iOutPortStatus = -1;
	if (0 == NetClient_GetOutportState(m_iLogonID, iOutPortNum, &iOutPortStatus))
	{
		m_cmbAlarmOutPortStatusID.SetCurSel(iOutPortStatus);
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetOutportState(%d,%d,%d)", m_iLogonID,iOutPortNum,iOutPortStatus);
	}
	else
	{
		m_cmbAlarmOutPortStatusID.SetCurSel(iOutPortStatus);
		AddLog(LOG_TYPE_FAIL,"", "NetClient_GetOutportState(%d,%d)", m_iLogonID,iOutPortStatus);
	}

}

void CLS_IOPORTPAGE::OnCbnSelchangeComboIoportNum()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	int iEnable[LEN_32] = {0};
	int iInPort = m_cmbInPortChnID.GetCurSel();

	TAlarmLinkParam_V1 tAlarmLinkPara = {0};
	tAlarmLinkPara.iLinkParamSize = sizeof(TAlarmLinkParam_V1);
	tAlarmLinkPara.iLinkType = ALARMLINKTYPE_LINKOUTPORT;
	int iChannelNo = m_cmbInPortChnID.GetCurSel();

	int iREnable = -1;

	int iRet = NetClient_GetAlarmConfig(m_iLogonID, iChannelNo, ALARM_TYPE_PORT_ALARM, CMD_GET_ALARMLINK_V2, &tAlarmLinkPara);
	if(RET_SUCCESS == iRet)
	{
		for (int i=0; i < LEN_32; i++)
		{
			iEnable[i] = tAlarmLinkPara.iChannelSet[i]; 
			if((1<< i%LEN_32)&iEnable[ i/LEN_32]?TRUE:FALSE)
			{
				m_chkOutPortEnable[i].SetCheck(TRUE);
			}
			else
			{
				m_chkOutPortEnable[i].SetCheck(FALSE);
			}
		}	
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetAlarmConfig(%d, %d)", m_iLogonID, iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_GetAlarmConfig(%d, %d)", m_iLogonID, iChannelNo);
	}

	int iREnableRet = NetClient_GetInportEnable(m_iLogonID, iChannelNo, &iREnable);
	if(RET_SUCCESS == iREnableRet)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetInportEnable(%d, %d)", m_iLogonID, iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_GetInportEnable(%d, %d)", m_iLogonID, iChannelNo);
	}

	if(ENABLE == iREnable)
	{
		m_chkAlarmPortEnableID.SetCheck(TRUE);
	}
	else
	{
		m_chkAlarmPortEnableID.SetCheck(FALSE);
	}
}

void CLS_IOPORTPAGE::OnCbnSelchangeComboAlarmoutport()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	
	int iPortNo = m_cmbAlarmOutPortID.GetCurSel();
	int iClearType = -1;
	int iDelayTime = -1;

	if (0 == NetClient_GetOutportAlarmDelay(m_iLogonID,iPortNo,&iClearType,&iDelayTime))
	{
		m_cmbStopModeID.SetCurSel(iClearType);
		SetDlgItemInt(IDC_EDIT_DELAYTIME, iDelayTime);
	}
}

void CLS_IOPORTPAGE::OnEnChangeEditDelaytime()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CLS_BasePage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	// 	if (m_iLogonID < 0)
	// 	{
	// 		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
	// 		return;
	// 	}

	int iDelayTime = GetDlgItemInt(IDC_EDIT_DELAYTIME, &iDelayTime);
	if(iDelayTime < 0 || iDelayTime > 30)
	{
		SetDlgItemInt(IDC_EDIT_DELAYTIME, 30);
	}
}

BOOL CLS_IOPORTPAGE::UI_UpdateIOPortParam()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return FALSE;
	}

	//获得通道号和端口号个数
	int  iAlarmInPortNum = 0;
	int  iAlarmOutPortNum = 0;
	int  iChannelNum = 0;
	if (0 == NetClient_GetAlarmPortNum(m_iLogonID,&iAlarmInPortNum,&iAlarmOutPortNum))
	{
		if(0 == NetClient_GetChannelNum(m_iLogonID, &iChannelNum))
		{
			if (m_cmbAlarmInPortID.GetCount() != iAlarmInPortNum)
			{
				m_cmbAlarmInPortID.ResetContent();
				for (int i = 0; i < iAlarmInPortNum; i++)
				{
					CString strInPort;
					strInPort.Format("%d", i);
					m_cmbAlarmInPortID.AddString(strInPort);
				}
				m_cmbAlarmInPortID.SetCurSel(0);
			}
			//update channel 0 state
			int iInLowOrHigh = -1;
			int iInPortNum = m_cmbAlarmInPortID.GetCurSel();
			if (0 == NetClient_GetAlarmInMode(m_iLogonID,iInPortNum,&iInLowOrHigh))
			{
				m_cmbAlarmInModeID.SetCurSel(iInLowOrHigh);
				AddLog(LOG_TYPE_SUCC,"", "NetClient_GetAlarmInMode(%d)", m_iLogonID);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"", "NetClient_GetAlarmInMode(%d)", m_iLogonID);
			}

			int i = m_cmbAlarmActiveModeOutPortID.GetCount();
			if (m_cmbAlarmActiveModeOutPortID.GetCount() != iAlarmOutPortNum)
			{
				m_cmbAlarmActiveModeOutPortID.ResetContent();
				m_cmbAlarmOutPortID.ResetContent();
				for (int i = 0; i < iAlarmOutPortNum; i++)
				{
					CString strOutPort;
					strOutPort.Format("%d",i);
					m_cmbAlarmActiveModeOutPortID.AddString(strOutPort);
					m_cmbAlarmOutPortID.AddString(strOutPort); 
				}
				m_cmbAlarmActiveModeOutPortID.SetCurSel(0);
				m_cmbAlarmOutPortID.SetCurSel(0);
			}
			//update channel 0 state
			int iOutLowOrHigh = -1;
			int iPulseWidth = -1;
			int iOutPortNum = m_cmbAlarmActiveModeOutPortID.GetCurSel();
			if(iOutPortNum < 0)
			{
				m_cmbAlarmActiveModeOutPortID.SetCurSel(0);
				iOutPortNum = 0;
			}
			if (0 == NetClient_GetAlarmOutMode(m_iLogonID,iOutPortNum,&iOutLowOrHigh,&iPulseWidth))
			{
				m_cmbAlarmOutModeID.SetCurSel(iOutLowOrHigh);
				AddLog(LOG_TYPE_SUCC,"", "NetClient_GetAlarmInMode(%d)", m_iLogonID);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"", "NetClient_GetAlarmInMode(%d)", m_iLogonID);
			}
			int iOutPortStatus = -1;
			if (0 == NetClient_GetOutportState(m_iLogonID, iOutPortNum, &iOutPortStatus))
			{
				m_cmbAlarmOutPortStatusID.SetCurSel(iOutPortStatus);
				AddLog(LOG_TYPE_SUCC,"", "NetClient_GetOutportState(%d,%d,%d)", m_iLogonID,iOutPortNum,iOutPortStatus);
			}
			else
			{
				m_cmbAlarmOutPortStatusID.SetCurSel(iOutPortStatus);
				AddLog(LOG_TYPE_FAIL,"", "NetClient_GetOutportState(%d,%d)", m_iLogonID,iOutPortNum);
			}
			int iPortNo = m_cmbAlarmOutPortID.GetCurSel();
			if(iPortNo < 0)
			{
				iPortNo = 0;
			}
			int iClearType = -1;
			int iDelayTime = -1;

			if (0 == NetClient_GetOutportAlarmDelay(m_iLogonID,iPortNo,&iClearType,&iDelayTime))
			{
				m_cmbStopModeID.SetCurSel(iClearType);
				SetDlgItemInt(IDC_EDIT_DELAYTIME, iDelayTime);
			}

			if (m_cmbInPortChnID.GetCount() != iAlarmInPortNum)
			{
				m_cmbInPortChnID.ResetContent();
				for (int i=0;i<iAlarmInPortNum;i++)
				{
					CString strInPort;
					strInPort.Format("%d", i);
					m_cmbInPortChnID.AddString(strInPort);
				}
				m_cmbInPortChnID.SetCurSel(0);
			}

			AddLog(LOG_TYPE_SUCC,"","NetClient_GetAlarmPortNum (%d)",m_iLogonID);
			AddLog(LOG_TYPE_SUCC,"","NetClient_GetChannelNum (%d)",m_iLogonID);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetChannelNum (%d)",m_iLogonID);
		}

	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetAlarmPortNum (%d)",m_iLogonID);
	}

	int iState = 0;
	int iInPort = m_cmbInPortChnID.GetCurSel();
	if (0 == NetClient_GetInportEnable(m_iLogonID, iInPort, &iState))
	{
		m_chkAlarmPortEnableID.SetCheck(iState);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetInportEnable (%d)",m_iLogonID);
	}
	else
	{
		m_chkAlarmPortEnableID.SetCheck(iState);
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetInportEnable (%d)",m_iLogonID);
	}

	int iEnable[LEN_32] = {0};
	TAlarmLinkParam_V1 tAlarmLinkPara = {0};
	tAlarmLinkPara.iLinkParamSize = sizeof(TAlarmLinkParam_V1);
	tAlarmLinkPara.iLinkType = ALARMLINKTYPE_LINKOUTPORT;
	int iChannelNo = m_cmbInPortChnID.GetCurSel();
	int iRet = NetClient_GetAlarmConfig(m_iLogonID, iChannelNo, ALARM_TYPE_PORT_ALARM, CMD_GET_ALARMLINK_V2, &tAlarmLinkPara);
	if(RET_SUCCESS == iRet)
	{
		for (int i=0; i < LEN_32; i++)
		{
			iEnable[i] = tAlarmLinkPara.iChannelSet[i]; 
			if((1<< i%LEN_32)&iEnable[ i/LEN_32]?TRUE:FALSE)
			{
				m_chkOutPortEnable[i].SetCheck(TRUE);
			}
			else
			{
				m_chkOutPortEnable[i].SetCheck(FALSE);
			}
		}	
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetAlarmConfig(%d, %d)", m_iLogonID, iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_GetAlarmConfig(%d, %d)", m_iLogonID, iChannelNo);
	}

	return TRUE;
}


void CLS_IOPORTPAGE::OnBnClickedButtonAlarmoutportEnableSet()
{
	// TODO: Add your control notification handler code here

	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	//int iAlarmOutPort = GetDlgItemInt(IDC_COMBO_ALARMOUTPORT_NUM);
	int iAlarmOutPort = m_cmbAlarmActiveModeOutPortID.GetCurSel();
	//是否Enable从控件中获取；
// 	int iAlarmOutPortEnable = DISABLE;
//     if (0 == GetDlgItemInt(IDC_COMBO_OUTPORTSTATUS))
//     {
//     } 
//     else if (1 == GetDlgItemInt(IDC_COMBO_OUTPORTSTATUS))
//     {
// 		iAlarmOutPortEnable = ENABLE;	
//     }
	int iAlarmOutPortEnable = m_cmbAlarmOutPortStatusID.GetCurSel();
	int iRet = NetClient_SetOutPortState(m_iLogonID, iAlarmOutPort, iAlarmOutPortEnable);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetOutPortState (%d,%d,%d)",m_iLogonID,iAlarmOutPort,iAlarmOutPortEnable);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetOutPortState (%d,%d,%d)",m_iLogonID,iAlarmOutPort,iAlarmOutPortEnable);
	}

}
