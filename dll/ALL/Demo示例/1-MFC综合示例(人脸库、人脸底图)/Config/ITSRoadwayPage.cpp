// ITSRoadwayPage.cpp : implementation file
//

#include "stdafx.h"
#include "ITSRoadwayPage.h"


// CLS_ITSRoadwayPage dialog

IMPLEMENT_DYNAMIC(CLS_ITSRoadwayPage, CDialog)

CLS_ITSRoadwayPage::CLS_ITSRoadwayPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ITSRoadwayPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
}

CLS_ITSRoadwayPage::~CLS_ITSRoadwayPage()
{

}

void CLS_ITSRoadwayPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ROADWAYNO, m_cboRoadwayNo);
	DDX_Control(pDX, IDC_CHECK_ROADWAYNO, m_chkRoadwayNo);
	DDX_Control(pDX, IDC_BUTTON_ROADWAY, m_btnRoadway);
	DDX_Control(pDX, IDC_EDIT_ROADWAYNAME, m_edtRoadwayName);
	DDX_Control(pDX, IDC_EDIT_ROADWAYDIRECTION, m_edtRoadwayDirection);
	DDX_Control(pDX, IDC_EDIT_COMPORTNO, m_edtComportNo);
	DDX_Control(pDX, IDC_EDIT_SPEEDLOOPNO, m_edtSpeedLoopNo);
	DDX_Control(pDX, IDC_EDIT_CAPTURELOOPNO, m_edtCaptureLoopNo);
	DDX_Control(pDX, IDC_BUTTON_LOOP, m_btnLoop);
	DDX_Control(pDX, IDC_EDIT_LOOPMAXTIME, m_edtLoopMaxTime);
	DDX_Control(pDX, IDC_EDIT_LOOPMINTIME, m_edtLoopMinTime);
	DDX_Control(pDX, IDC_EDIT_LOOPDELAYTIME, m_edtLoopDelayTime);
	DDX_Control(pDX, IDC_BUTTON_TIME, m_btnTime);
	DDX_Control(pDX, IDC_EDIT_LOOPDISTANCE, m_edtLoopDistance);
	DDX_Control(pDX, IDC_EDIT_SPEEDLIMIT, m_edtSpeedLimit);
	DDX_Control(pDX, IDC_EDIT_SPEEDMODIFY, m_edtSpeedModify);
	DDX_Control(pDX, IDC_BUTTON_SPEED, m_btnSpeed);
	DDX_Control(pDX, IDC_EDIT_RECRANGE, m_edtRecRange);
	DDX_Control(pDX, IDC_BUTTON_RECRANGE, m_btnRecRange);
	DDX_Control(pDX, IDC_COMBO_LOOPID, m_cboLoopID);
	DDX_Control(pDX, IDC_COMBO_DAYNIGHT, m_cboDayNight);
	DDX_Control(pDX, IDC_BUTTON_VIRTUALLOOP, m_btnVirtualLoop);
	DDX_Control(pDX, IDC_EDIT_SENCE, m_edtSence);
	DDX_Control(pDX, IDC_COMBO_LOOPMODE2, m_cboLoopMode);
	DDX_Control(pDX, IDC_BUTTON_LOOPMODE, m_btnLoopMode);
}


BEGIN_MESSAGE_MAP(CLS_ITSRoadwayPage, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_ROADWAYNO, &CLS_ITSRoadwayPage::OnCbnSelchangeComboRoadwayno)
	ON_BN_CLICKED(IDC_BUTTON_ROADWAY, &CLS_ITSRoadwayPage::OnBnClickedButtonRoadway)
	ON_BN_CLICKED(IDC_BUTTON_LOOP, &CLS_ITSRoadwayPage::OnBnClickedButtonLoop)
	ON_BN_CLICKED(IDC_BUTTON_TIME, &CLS_ITSRoadwayPage::OnBnClickedButtonTime)
	ON_BN_CLICKED(IDC_BUTTON_SPEED, &CLS_ITSRoadwayPage::OnBnClickedButtonSpeed)
	ON_BN_CLICKED(IDC_BUTTON_RECRANGE, &CLS_ITSRoadwayPage::OnBnClickedButtonRecrange)
	ON_CBN_SELCHANGE(IDC_COMBO_LOOPID, &CLS_ITSRoadwayPage::OnCbnSelchangeComboLoopid)
	ON_CBN_SELCHANGE(IDC_COMBO_DAYNIGHT, &CLS_ITSRoadwayPage::OnCbnSelchangeComboDaynight)
	ON_BN_CLICKED(IDC_BUTTON_VIRTUALLOOP, &CLS_ITSRoadwayPage::OnBnClickedButtonVirtualloop)
	ON_BN_CLICKED(IDC_BUTTON_LOOPMODE, &CLS_ITSRoadwayPage::OnBnClickedButtonLoopmode)

END_MESSAGE_MAP()


// CLS_ITSRoadwayPage message handlers

BOOL CLS_ITSRoadwayPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	for (int i=0; i<4; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboRoadwayNo.AddString(strNo);
	}
	for (int i=0; i<2; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboLoopID.AddString(strNo);
	}
	m_cboRoadwayNo.SetCurSel(0);
	m_cboLoopID.SetCurSel(0);

	m_edtRoadwayName.SetLimitText(31);
	m_edtRoadwayDirection.SetLimitText(31);
	m_edtComportNo.SetLimitText(8);
	m_edtSpeedLoopNo.SetLimitText(8);
	m_edtCaptureLoopNo.SetLimitText(8);
	m_edtLoopMaxTime.SetLimitText(8);
	m_edtLoopMinTime.SetLimitText(8);
	m_edtLoopDelayTime.SetLimitText(8);
	m_edtLoopDistance.SetLimitText(8);
	m_edtSpeedLimit.SetLimitText(8);
	m_edtSpeedModify.SetLimitText(8);
	m_edtRecRange.SetLimitText(8);
	SetDlgItemInt(IDC_EDIT_SENCE, 50);

	m_cboDayNight.AddString("0--Night");
	m_cboDayNight.AddString("1--Day");
	m_cboDayNight.SetCurSel(1);

	m_tipCtrl.Create(this,TTF_ALWAYSTIP);
	m_tipCtrl.AddTool(&m_edtSpeedLoopNo,_T("[1,8]"));
	m_tipCtrl.AddTool(&m_edtCaptureLoopNo,_T("[1,8]"));
	m_tipCtrl.AddTool(&m_edtLoopMaxTime,_T("[2000,10000]ms"));
	m_tipCtrl.AddTool(&m_edtLoopDelayTime,_T("[0,2000]ms"));
	m_tipCtrl.AddTool(&m_edtLoopDistance,_T("[100,6000]m"));
	m_tipCtrl.AddTool(&m_edtSpeedLimit,_T("[0,200000]m/h"));
	m_tipCtrl.AddTool(&m_edtSpeedModify,_T("[-20000,20000]m/h"));
	m_tipCtrl.SetDelayTime(150);

	UI_UpdateDialog();

	return TRUE;
}

void CLS_ITSRoadwayPage::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
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

	UI_UpdateRoadway();
	UI_UpdateVirtualLoop();
	UI_UpdateLoopmode();
	UI_UpdateRoadway();
}

void CLS_ITSRoadwayPage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ITSRoadwayPage::UI_UpdateDialog()
{
	
	SetDlgItemTextEx(IDC_STATIC_ROADWAYNANO,IDS_CONFIG_ITS_ROADWAY_ROADWAYNO);
	SetDlgItemTextEx(IDC_CHECK_ROADWAYNO,IDS_CONFIG_ITS_ROADWAY_ENABLE);
	SetDlgItemTextEx(IDC_BUTTON_ROADWAY,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_ROADWAYNAME,IDS_CONFIG_ITS_ROADWAY_ROADWAYNAME);
	SetDlgItemTextEx(IDC_STATIC_ROADWAYDIRECTION,IDS_CONFIG_ITS_ROADWAY_ROADWAYDIRECTION);
	SetDlgItemTextEx(IDC_STATIC_LOOP,IDS_CONFIG_ITS_ROADWAY_LOOP);
	SetDlgItemTextEx(IDC_STATIC_COMPORTNO,IDS_CONFIG_ITS_ROADWAY_COMPORTNO);
	SetDlgItemTextEx(IDC_STATIC_SPEEDLOOPNO,IDS_CONFIG_ITS_ROADWAY_SPEEDLOOPNO);
	SetDlgItemTextEx(IDC_STATIC_CAPTURELOOPNO,IDS_CONFIG_ITS_ROADWAY_CAPTURELOOPNO);
	SetDlgItemTextEx(IDC_BUTTON_LOOP,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_TIME,IDS_CONFIG_ITS_ROADWAY_TIME);
	SetDlgItemTextEx(IDC_STATIC_LOOPMAXTIME,IDS_CONFIG_ITS_ROADWAY_LOOPMAXTIME);
	SetDlgItemTextEx(IDC_STATIC_LOOPMINTIME,IDS_CONFIG_ITS_ROADWAY_LOOPMINTIME);
	SetDlgItemTextEx(IDC_STATIC_LOOPDELAYTIME,IDS_CONFIG_ITS_ROADWAY_LOOPDELAYTIME);
	SetDlgItemTextEx(IDC_BUTTON_TIME,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_SPEED,IDS_CONFIG_ITS_ROADWAY_SPEED);
	SetDlgItemTextEx(IDC_STATIC_LOOPDISTANCE,IDS_CONFIG_ITS_ROADWAY_LOOPDISTANCE);
	SetDlgItemTextEx(IDC_STATIC_SPEEDLIMIT,IDS_CONFIG_ITS_ROADWAY_SPEEDLIMIT);
	SetDlgItemTextEx(IDC_STATIC_SPEEDMODIFY,IDS_CONFIG_ITS_ROADWAY_SPEEDMODIFY);
	SetDlgItemTextEx(IDC_BUTTON_SPEED,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_RECRANGE,IDS_CONFIG_ITS_ROADWAY_RECRANGE);
	SetDlgItemTextEx(IDC_BUTTON_RECRANGE,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_VIRTUALLOOP,IDS_CONFIG_ITS_ROADWAY_VIRTUALLOOP);
	SetDlgItemTextEx(IDC_STATIC_LOOPID,IDS_CONFIG_ITS_ROADWAY_LOOPID);
	SetDlgItemTextEx(IDC_BUTTON_VIRTUALLOOP,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_LEFT, IDS_ITS_LEFT_EDGE);
	SetDlgItemTextEx(IDC_STATIC_UP, IDS_ITS_UP_EDGE);
	SetDlgItemTextEx(IDC_STATIC_RIGHT, IDS_ITS_RIGHT_EDGE);
	SetDlgItemTextEx(IDC_STATIC_DOWN, IDS_ITS_DOWN_EDGE);
	SetDlgItemTextEx(IDC_STATIC_POINT_1, IDS_ITS_POINT1);
	SetDlgItemTextEx(IDC_STATIC_POINT_2, IDS_ITS_POINT2);
	SetDlgItemTextEx(IDC_STATIC_POINT_3, IDS_ITS_POINT3);
	SetDlgItemTextEx(IDC_STATIC_POINT_4, IDS_ITS_POINT4);
	SetDlgItemTextEx(IDC_STATIC_SENCE,  IDS_CONFIG_ITS_ILLEGALPARK_SENSITIVITY);
	SetDlgItemTextEx(IDC_STATIC_LOOPMODE,IDS_CONFIG_ITS_TIMERANGE_LOOPMODE);
	SetDlgItemTextEx(IDC_BUTTON_LOOPMODE,IDS_SET);
	InsertString(m_cboLoopMode,0,IDS_CONFIG_ITS_LOOPMODE0);
	InsertString(m_cboLoopMode,1,IDS_CONFIG_ITS_LOOPMODE1);
}

BOOL CLS_ITSRoadwayPage::UI_UpdateRoadway()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iRoadwayID = m_cboRoadwayNo.GetCurSel();
	TITSRoadwayInfo pa = {0};
	pa.iRoadwayID = iRoadwayID;
	int iRet = NetClient_GetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_GET_ENABLE, &pa, sizeof(pa));
	if (0 == iRet)
	{
		m_chkRoadwayNo.SetCheck(pa.iEnable?BST_CHECKED:BST_UNCHECKED);
		SetDlgItemText(IDC_EDIT_ROADWAYNAME, pa.cChannelName);
		SetDlgItemText(IDC_EDIT_ROADWAYDIRECTION, pa.cChannelDir);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	}
	TITSRoadWayLoop pb = {0};
	pb.iRoadwayID = iRoadwayID;
	iRet = NetClient_GetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_GET_LOOP, &pb, sizeof(pb));
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_COMPORTNO, pb.iComportNo);
		SetDlgItemInt(IDC_EDIT_SPEEDLOOPNO, pb.iSpeedLoopNo);
		SetDlgItemInt(IDC_EDIT_CAPTURELOOPNO, pb.iCaptureLoopNo);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pb));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pb));
	}
	TITSRoadwayTime pc = {0};
	pc.iRoadwayID = iRoadwayID;
	iRet =  NetClient_GetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_GET_TIME, &pc, sizeof(pc));
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_LOOPMAXTIME, pc.iLoopMaxTime);
		SetDlgItemInt(IDC_EDIT_LOOPMINTIME, pc.iLoopMinTime);
		SetDlgItemInt(IDC_EDIT_LOOPDELAYTIME, pc.iLoopDelayTime);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pc));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pc));
	}
	TITSRoadwaySpeed pd = {0};
	pd.iRoadwayID = iRoadwayID;
	iRet = NetClient_GetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_GET_SPEED, &pd, sizeof(pd));
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_LOOPDISTANCE, pd.iLoopDistance);
		SetDlgItemInt(IDC_EDIT_SPEEDLIMIT, pd.iSpeedLimit);
		SetDlgItemInt(IDC_EDIT_SPEEDMODIFY, pd.iSpeedModify);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pd));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pd));
	}
	TITSRoadwayReco pe = {0};
	pe.iRoadwayID = iRoadwayID;
	iRet = NetClient_GetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_GET_RECO, &pe, sizeof(pe));
	if (0 == iRet)
	{
		int iLeftEdge = (pe.iRoadwayRange >> 24) & 0xFF;
		int iUpEdge = (pe.iRoadwayRange >> 16) & 0xFF;
		int iRightEdge = (pe.iRoadwayRange >> 8) & 0xFF;
		int iDownEdge = (pe.iRoadwayRange) & 0xFF;
		SetDlgItemInt(IDC_EDIT_RECRANGE, iLeftEdge);
		SetDlgItemInt(IDC_EDIT_RECRANGE2, iUpEdge);
		SetDlgItemInt(IDC_EDIT_RECRANGE3, iRightEdge);
		SetDlgItemInt(IDC_EDIT_RECRANGE4, iDownEdge);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pe));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pe));
	}
	UI_UpdateVirtualLoop();
	return TRUE;
}

void CLS_ITSRoadwayPage::OnCbnSelchangeComboRoadwayno()
{
	UI_UpdateRoadway();
}

void CLS_ITSRoadwayPage::OnBnClickedButtonRoadway()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITSRoadwayInfo pa = {0};
	pa.iRoadwayID = m_cboRoadwayNo.GetCurSel();
	pa.iEnable = (m_chkRoadwayNo.GetCheck() == BST_CHECKED)?1:0;
	GetDlgItemText(IDC_EDIT_ROADWAYNAME, pa.cChannelName, 31);
	GetDlgItemText(IDC_EDIT_ROADWAYDIRECTION, pa.cChannelDir, 31);
	int iRet = NetClient_SetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_SET_ENABLE, &pa, sizeof(pa));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	}
}

void CLS_ITSRoadwayPage::OnBnClickedButtonLoop()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITSRoadWayLoop pa = {0};
	pa.iRoadwayID = m_cboRoadwayNo.GetCurSel();
	pa.iComportNo = GetDlgItemInt(IDC_EDIT_COMPORTNO);
	pa.iSpeedLoopNo = GetDlgItemInt(IDC_EDIT_SPEEDLOOPNO);
	pa.iCaptureLoopNo = GetDlgItemInt(IDC_EDIT_CAPTURELOOPNO);
	int iRet = NetClient_SetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_SET_LOOP, &pa, sizeof(pa));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	}
}

void CLS_ITSRoadwayPage::OnBnClickedButtonTime()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITSRoadwayTime pa = {0};
	pa.iRoadwayID = m_cboRoadwayNo.GetCurSel();
	pa.iLoopMaxTime = GetDlgItemInt(IDC_EDIT_LOOPMAXTIME);
	pa.iLoopMinTime = GetDlgItemInt(IDC_EDIT_LOOPMINTIME);
	pa.iLoopDelayTime = GetDlgItemInt(IDC_EDIT_LOOPDELAYTIME);
	int iRet = NetClient_SetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_SET_TIME, &pa, sizeof(pa));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	}
}

void CLS_ITSRoadwayPage::OnBnClickedButtonSpeed()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITSRoadwaySpeed pa = {0};
	pa.iRoadwayID = m_cboRoadwayNo.GetCurSel();
	pa.iLoopDistance = GetDlgItemInt(IDC_EDIT_LOOPDISTANCE);
	pa.iSpeedLimit = GetDlgItemInt(IDC_EDIT_SPEEDLIMIT);
	pa.iSpeedModify = GetDlgItemInt(IDC_EDIT_SPEEDMODIFY);	
	int iRet = NetClient_SetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_SET_SPEED, &pa, sizeof(pa));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	}		
}

void CLS_ITSRoadwayPage::OnBnClickedButtonRecrange()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITSRoadwayReco pa = {0};
	pa.iRoadwayID = m_cboRoadwayNo.GetCurSel();
	int iLeftEdge = GetDlgItemInt(IDC_EDIT_RECRANGE);
	int iUpEdge = GetDlgItemInt(IDC_EDIT_RECRANGE2);
	int iRightEdge = GetDlgItemInt(IDC_EDIT_RECRANGE3);
	int iDownEdge = GetDlgItemInt(IDC_EDIT_RECRANGE4);
	if (iLeftEdge < 0 || iLeftEdge > 100 || iUpEdge < 0 || iUpEdge > 100
		|| iRightEdge < 0 || iRightEdge > 100 || iDownEdge < 0 || iDownEdge > 100)
	{
		AddLog(LOG_TYPE_FAIL, "", "Invalid Param!");
		return;
	}
	pa.iRoadwayRange = (iLeftEdge << 24) | (iUpEdge << 16) | (iRightEdge << 8) | (iDownEdge);
	int iRet = NetClient_SetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_SET_RECO, &pa, sizeof(pa));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	}
}

void CLS_ITSRoadwayPage::OnCbnSelchangeComboLoopid()
{
	UI_UpdateVirtualLoop();
}

void CLS_ITSRoadwayPage::OnCbnSelchangeComboDaynight()
{
	UI_UpdateVirtualLoop();
}

void CLS_ITSRoadwayPage::OnBnClickedButtonVirtualloop()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITSRoadwayVLoop pa = {0};
	pa.iRoadwayID = m_cboRoadwayNo.GetCurSel();
	pa.iLoopID = m_cboLoopID.GetCurSel();
	pa.iDayNight = m_cboDayNight.GetCurSel();
	pa.iSensitivity = GetDlgItemInt(IDC_EDIT_SENCE);
	
	int iPoint1x = GetDlgItemInt(IDC_EDIT_POINT1X);
	int iPoint1y = GetDlgItemInt(IDC_EDIT_POINT1Y);
	int iPoint2x = GetDlgItemInt(IDC_EDIT_POINT2X);
	int iPoint2y = GetDlgItemInt(IDC_EDIT_POINT2Y);
	int iPoint3x = GetDlgItemInt(IDC_EDIT_POINT3X);
	int iPoint3y = GetDlgItemInt(IDC_EDIT_POINT3Y);
	int iPoint4x = GetDlgItemInt(IDC_EDIT_POINT4X);
	int iPoint4y = GetDlgItemInt(IDC_EDIT_POINT4Y);
	pa.iPoint1[pa.iDayNight][pa.iLoopID] = (iPoint1x & 0xFFFF) | ((iPoint1y  & 0xFFFF)<< 16);
	pa.iPoint2[pa.iDayNight][pa.iLoopID] = (iPoint2x & 0xFFFF) | ((iPoint2y  & 0xFFFF)<< 16);
	pa.iPoint3[pa.iDayNight][pa.iLoopID] = (iPoint3x & 0xFFFF) | ((iPoint3y  & 0xFFFF)<< 16);
	pa.iPoint4[pa.iDayNight][pa.iLoopID] = (iPoint4x & 0xFFFF) | ((iPoint4y  & 0xFFFF)<< 16);
	int iRet = NetClient_SetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_SET_VLOOP, &pa, sizeof(pa));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	}
}

void CLS_ITSRoadwayPage::UI_UpdateVirtualLoop()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITSRoadwayVLoop pf = {0};
	pf.iRoadwayID = m_cboRoadwayNo.GetCurSel();
	int iRet = NetClient_GetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_SET_VLOOP, &pf, sizeof(pf));
	if (0 == iRet)
	{
		int iVLoopID = m_cboLoopID.GetCurSel();
		int iDayorNight = m_cboDayNight.GetCurSel();
		int iPoint1 = pf.iPoint1[iDayorNight][iVLoopID];
		int iPoint2 = pf.iPoint2[iDayorNight][iVLoopID];
		int iPoint3 = pf.iPoint3[iDayorNight][iVLoopID] ;
		int iPoint4 = pf.iPoint4[iDayorNight][iVLoopID]; 

		int iPoint1x = iPoint1 & 0xFFFF;
		int iPoint1y = (iPoint1 >> 16) & 0xFFFF;
		int iPoint2x = iPoint2 & 0xFFFF;
		int iPoint2y = (iPoint2 >> 16) & 0xFFFF;
		int iPoint3x = iPoint3 & 0xFFFF;
		int iPoint3y = (iPoint3 >> 16) & 0xFFFF;
		int iPoint4x = iPoint4 & 0xFFFF;
		int iPoint4y = (iPoint4 >> 16) & 0xFFFF;

		SetDlgItemInt(IDC_EDIT_SENCE, pf.iSensitivity);
		SetDlgItemInt(IDC_EDIT_POINT1X, iPoint1x);
		SetDlgItemInt(IDC_EDIT_POINT1Y, iPoint1y);
		SetDlgItemInt(IDC_EDIT_POINT2X, iPoint2x);
		SetDlgItemInt(IDC_EDIT_POINT2Y, iPoint2y);
		SetDlgItemInt(IDC_EDIT_POINT3X, iPoint3x);
		SetDlgItemInt(IDC_EDIT_POINT3Y, iPoint3y);
		SetDlgItemInt(IDC_EDIT_POINT4X, iPoint4x);
		SetDlgItemInt(IDC_EDIT_POINT4Y, iPoint4y);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pf));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pf));
	}	
}
BOOL CLS_ITSRoadwayPage::PreTranslateMessage(MSG* pMsg)
{
	if(WM_MOUSEMOVE == pMsg->message)
	{
		m_tipCtrl.RelayEvent(pMsg);
	}

	return CLS_BasePage::PreTranslateMessage(pMsg);
}
void CLS_ITSRoadwayPage::OnBnClickedButtonLoopmode()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iRoadwayID = m_cboRoadwayNo.GetCurSel();
	int iLoopMode = m_cboLoopMode.GetCurSel();
	ITS_LoopMode tItsLoopMode = {0};
	tItsLoopMode.iBufSize = sizeof(ITS_LoopMode);
	tItsLoopMode.iLaneID = iRoadwayID;
	tItsLoopMode.iLoopMode = iLoopMode; 
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_LOOP_MODE, m_iChannelNo, &tItsLoopMode, sizeof(tItsLoopMode));
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_LOOP_MODE] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_LOOP_MODE] (%d, %d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}
}

void CLS_ITSRoadwayPage::UI_UpdateLoopmode()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}		

	int iRoadwayID = m_cboRoadwayNo.GetCurSel();
	ITS_LoopMode tItsLoopMode = {0};
	tItsLoopMode.iBufSize = sizeof(ITS_LoopMode);
	tItsLoopMode.iLaneID = iRoadwayID;

	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_LOOP_MODE, m_iChannelNo, &tItsLoopMode, sizeof(tItsLoopMode));
	if(0 == iRet)
	{
		m_cboLoopMode.SetCurSel(tItsLoopMode.iLoopMode);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_LOOP_MODE] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_LOOP_MODE] (%d, %d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}
}