// ItsRoadwayCommon2.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ItsRoadwayCommon2.h"


// CLS_ItsRoadwayCommon2 对话框

IMPLEMENT_DYNAMIC(CLS_ItsRoadwayCommon2, CDialog)

CLS_ItsRoadwayCommon2::CLS_ItsRoadwayCommon2(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ItsRoadwayCommon2::IDD, pParent)
{

}

CLS_ItsRoadwayCommon2::~CLS_ItsRoadwayCommon2()
{
}

void CLS_ItsRoadwayCommon2::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_ROADWAYID, m_cboRoadwayId);
	DDX_Control(pDX, IDC_CMB_CAR_TYPE, m_cboCarType);
	DDX_Control(pDX, IDC_CHK_ROADWAY_ENABLE, m_chkRoadwayEnable);
	DDX_Control(pDX, IDC_CMB_CAR_UPDOWN, m_cboCarUpDown);
	DDX_Control(pDX, IDC_CMB_CAR_USE, m_cboCarUse);
	DDX_Control(pDX, IDC_CMB_CAR_BOUN, m_cboCarBoun);
	DDX_Control(pDX, IDC_CHECK_ROADWAYNO, m_chkRoadwayNo);
	DDX_Control(pDX, IDC_EDT_CAR_LIMIT_START, m_edtSpeedLow);
	DDX_Control(pDX, IDC_EDT_CAR_LIMIT_END, m_edtSpeedHigh);
	DDX_Control(pDX, IDC_EDT_ABNORMAL_LIMIT_START, m_edtErrorSpeedLow);
	DDX_Control(pDX, IDC_EDT_ABNORMAL_LIMIT_END, m_edtErrorSpeedHigh);
	DDX_Control(pDX, IDC_EDTIDC_STA_LAW_PERCENT_START, m_edtImNotGoodAtEnglish);
	DDX_Control(pDX, IDC_EDT_LAW_PERCENT_END, m_edtPercent);
	DDX_Control(pDX, IDC_BTN_SPEEDLIMIT, m_btnSetSpeed);
}


BEGIN_MESSAGE_MAP(CLS_ItsRoadwayCommon2, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_SPEEDLIMIT, &CLS_ItsRoadwayCommon2::OnBnClickedBtnSpeedlimit)
	ON_BN_CLICKED(IDC_BTN_CAR_PROPERTY, &CLS_ItsRoadwayCommon2::OnBnClickedBtnCarProperty)
	ON_CBN_SELCHANGE(IDC_CMB_ROADWAYID, &CLS_ItsRoadwayCommon2::OnCbnSelchangeCmbRoadwayid)
	ON_CBN_SELCHANGE(IDC_CMB_CAR_TYPE, &CLS_ItsRoadwayCommon2::OnCbnSelchangeCmbCarType)
	ON_BN_CLICKED(IDC_CHECK_ROADWAYNO, &CLS_ItsRoadwayCommon2::OnBnClickedCheckRoadwayno)
END_MESSAGE_MAP()


// CLS_ItsRoadwayCommon2 消息处理程序

BOOL CLS_ItsRoadwayCommon2::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	for (int i=0; i<4; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboRoadwayId.AddString(strNo);
	}

	for (int i=0; i<3; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboCarType.AddString(strNo);
	}

	m_cboCarUpDown.AddString(GetTextEx(IDS_ITS_UP));
	m_cboCarUpDown.AddString(GetTextEx(IDS_ITS_DOWN));

	m_cboCarUse.AddString(GetTextEx(IDS_ITS_NORMALROADWAY));
	m_cboCarUse.AddString(GetTextEx(IDS_ITS_NOT_CAR_ROADWAY));
	m_cboCarUse.AddString(GetTextEx(IDS_ITS_BUS_ROADWAY));
	m_cboCarUse.AddString(GetTextEx(IDS_ITS_SMALLCAR_ROADWAY));
	
	
	m_cboCarBoun.AddString(GetTextEx(IDS_CONFIG_VIDEOPARAM_DISABLE));
	m_cboCarBoun.AddString(GetTextEx(IDS_ITS_LEFT_BOUND));
	m_cboCarBoun.AddString(GetTextEx(IDS_ITS_RIGHT_BOUND));
	m_cboCarBoun.AddString(GetTextEx(IDS_ITS_LEFT_RIGHT));
	UI_UpdateDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CLS_ItsRoadwayCommon2::UI_UpdateRoadway()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iRoadwayID = m_cboRoadwayId.GetCurSel();
	TITSRoadwayInfo pa = {0};
	pa.iRoadwayID = iRoadwayID;
	int iRet = NetClient_GetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_GET_ENABLE, &pa, sizeof(pa));
	if (0 == iRet)
	{
		m_chkRoadwayNo.SetCheck(pa.iEnable?BST_CHECKED:BST_UNCHECKED);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	}
	return TRUE;
}

void CLS_ItsRoadwayCommon2::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;

	UI_UpdateSpeedlimit();
	UI_UpdateCarProperty();
	UI_UpdateRoadway();
}

void CLS_ItsRoadwayCommon2::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ItsRoadwayCommon2::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STA_ROADWAYID,IDS_CONFIG_ECOP_ROADWAYID);
	SetDlgItemTextEx(IDC_CHECK_ROADWAYNO,IDS_CONFIG_ITS_ROADWAY_ENABLE);
	SetDlgItemTextEx(IDC_STA_SPEED_LIMIT,IDS_ITS_SPEED_LIMIT);
	SetDlgItemTextEx(IDC_STA_CAR_SPEEDLIMIT,IDS_ITS_CAR_SPEEDLIMIT);
	SetDlgItemTextEx(IDC_STA_LAW_PERCENT,IDS_ITS_CAR_PERCENT);
	SetDlgItemTextEx(IDC_STA_ABNORMAL_LIMIT,IDS_ITS_ABNORMAL_LIMIT);
	SetDlgItemTextEx(IDC_STA_CAR_TYPE,IDS_ITS_CAR_TYPE);
	SetDlgItemTextEx(IDC_BTN_SPEEDLIMIT,IDS_SET);
	SetDlgItemTextEx(IDC_STA_ROADWAY_PROPERTY,IDS_ITS_ROADWAY_PROPERTY);
	SetDlgItemTextEx(IDC_STA_NAME,IDS_ITS_NAME);
	SetDlgItemTextEx(IDC_STA_SELF_DEFINE,IDS_ITS__SELF_DEFINE);
	SetDlgItemTextEx(IDC_STA_TYPE,IDS_ITS_TYPE);
	SetDlgItemTextEx(IDC_STA_USE,IDS_ITS_USE);
	SetDlgItemTextEx(IDC_STA_UPDOWN,IDS_ITS_UPDOWN);
	SetDlgItemTextEx(IDC_STA_COM,IDS_ITS_COM);
	SetDlgItemTextEx(IDC_STA_RADAR,IDS_ITS_RADAR);
	SetDlgItemTextEx(IDC_STA_CAP_DIRECT,IDS_ITS_CAP_DIRECT);
	SetDlgItemTextEx(IDC_STA_LINK_ROADWAY,IDS_ITS_LINK_ROADWAY);
	SetDlgItemTextEx(IDC_STA_ROADWAY_BOUNDARY,IDS_ITS_ROADWAY_BOUNDARY);
	SetDlgItemTextEx(IDC_STA_SPE_USE,IDS_ITS_SPE_USE);
	SetDlgItemTextEx(IDC_BTN_CAR_PROPERTY,IDS_SET);
	SetDlgItemTextEx(IDC_CHK_ROADWAY_ENABLE,IDS_ITS_ROADWAY_ENABLE);
	SetDlgItemTextEx(IDC_STA_ROADWAY_DIRECT,IDS_ITS_ROADWAY_DIRECT);
	InsertString(m_cboCarUse, 4, IDS_ITS_ROADWAY_EMERGENCY2);
	InsertString(m_cboCarUse, 5, IDS_ITS_ROADWAY_SINGAL);
}

void CLS_ItsRoadwayCommon2::OnBnClickedBtnSpeedlimit()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

 	TITS_ChnCarSpeedPara tItsChnCarSpeedPara = {0};
 	tItsChnCarSpeedPara.iCarWayNo = m_cboRoadwayId.GetCurSel();
	tItsChnCarSpeedPara.iCarType = m_cboCarType.GetCurSel();
	tItsChnCarSpeedPara.iSpeedLowLimit = GetDlgItemInt(IDC_EDT_CAR_LIMIT_START) * 1000;
	tItsChnCarSpeedPara.iSpeedHighLimit = GetDlgItemInt(IDC_EDT_CAR_LIMIT_END) * 1000;

	tItsChnCarSpeedPara.fAbnormalLowSpeed = (float)GetDlgItemInt(IDC_EDT_ABNORMAL_LIMIT_START);
	tItsChnCarSpeedPara.fAbnormalHighSpeed = (float)GetDlgItemInt(IDC_EDT_ABNORMAL_LIMIT_END);
	tItsChnCarSpeedPara.iLowExceedPercent = GetDlgItemInt(IDC_EDTIDC_STA_LAW_PERCENT_START);
	tItsChnCarSpeedPara.iHighExceedPercent = GetDlgItemInt(IDC_EDT_LAW_PERCENT_END);
	
	int iRet = NetClient_SetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_CHNLCARSPEED, &tItsChnCarSpeedPara, sizeof(tItsChnCarSpeedPara));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_CHNLCARSPEED] (%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_CHNLCARSPEED] (%d) error(%d)", m_iLogonID, GetLastError());
	}
}

void CLS_ItsRoadwayCommon2::UI_UpdateSpeedlimit()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TITS_ChnCarSpeedPara tItsChnCarSpeedPara = {0};
	tItsChnCarSpeedPara.iCarWayNo = m_cboRoadwayId.GetCurSel();
	tItsChnCarSpeedPara.iCarType = m_cboCarType.GetCurSel();
	int iRet = NetClient_GetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_CHNLCARSPEED, &tItsChnCarSpeedPara, sizeof(tItsChnCarSpeedPara));
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDT_CAR_LIMIT_START, tItsChnCarSpeedPara.iSpeedLowLimit / 1000);
		SetDlgItemInt(IDC_EDT_CAR_LIMIT_END, tItsChnCarSpeedPara.iSpeedHighLimit / 1000);
		SetDlgItemInt(IDC_EDT_ABNORMAL_LIMIT_START, (UINT)tItsChnCarSpeedPara.fAbnormalLowSpeed);
		SetDlgItemInt(IDC_EDT_ABNORMAL_LIMIT_END, (UINT)tItsChnCarSpeedPara.fAbnormalHighSpeed);
		SetDlgItemInt(IDC_EDTIDC_STA_LAW_PERCENT_START, tItsChnCarSpeedPara.iLowExceedPercent);
		SetDlgItemInt(IDC_EDT_LAW_PERCENT_END, tItsChnCarSpeedPara.iHighExceedPercent);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam[ITS_ROADWAY_CMD_CHNLCARSPEED] (%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam[ITS_ROADWAY_CMD_CHNLCARSPEED] (%d) error(%d)", m_iLogonID, GetLastError());
	}
}

void CLS_ItsRoadwayCommon2::OnBnClickedBtnCarProperty()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TITSRoadwayInfo_V1 tItsRoadwayInfo_V1 = {0};
	tItsRoadwayInfo_V1.iBufSize = sizeof(TITSRoadwayInfo_V1);
	tItsRoadwayInfo_V1.iRoadwayID = m_cboRoadwayId.GetCurSel();
	tItsRoadwayInfo_V1.iEnable = m_chkRoadwayEnable.GetCheck();
	CString cstrName;
	GetDlgItemText(IDC_EDT_NAME, cstrName);
	int iSize = cstrName.GetLength() > MAX_ROADWAY_CHANNEL_NAME?MAX_ROADWAY_CHANNEL_NAME:cstrName.GetLength();
	memcpy(tItsRoadwayInfo_V1.cChannelName, cstrName.GetBuffer(), iSize); 
	char cTimeRange[20] = {0};
	GetDlgItemText(IDC_EDT_SPE_USE_START, cTimeRange, 20);
	CTime tTime = CTime::GetCurrentTime(); 
	int iBeginHour = 0;
	int iBeginMinute = 0;
	//int iBeginSec = 0;
	int iEndHour = 0;
	int iEndMinute = 0;
	//int iEndSec = 0;
	sscanf_s(cTimeRange, "%2d:%2d-%2d:%2d", &iBeginHour, &iBeginMinute, &iEndHour, &iEndMinute);
	tItsRoadwayInfo_V1.stStartTime.iYear =  tTime.GetYear();
	tItsRoadwayInfo_V1.stStartTime.iMonth = tTime.GetMonth();
	tItsRoadwayInfo_V1.stStartTime.iDay = tTime.GetDay();
	tItsRoadwayInfo_V1.stStartTime.iHour =  iBeginHour;
	tItsRoadwayInfo_V1.stStartTime.iMinute = iBeginMinute;
	//tItsRoadwayInfo_V1.stStartTime.iSecond = iBeginSec;

	tItsRoadwayInfo_V1.stStopTime.iYear =  tTime.GetYear();
	tItsRoadwayInfo_V1.stStopTime.iMonth = tTime.GetMonth();
	tItsRoadwayInfo_V1.stStopTime.iDay = tTime.GetDay();
	tItsRoadwayInfo_V1.stStopTime.iHour =  iEndHour;
	tItsRoadwayInfo_V1.stStopTime.iMinute = iEndMinute;
	//tItsRoadwayInfo_V1.stStopTime.iSecond = iEndSec;
	
	CString cstrSelfDefine;
	GetDlgItemText(IDC_EDT_SELFDEFINE, cstrSelfDefine);
	iSize = cstrSelfDefine.GetLength() > LEN_32?  LEN_32:cstrSelfDefine.GetLength();
	memcpy(tItsRoadwayInfo_V1.cNewChannelID, cstrSelfDefine.GetBuffer(), iSize);

	

	CString cstrSelfDirect;
	GetDlgItemText(IDC_EDT_DIRECT, cstrSelfDirect);
	iSize = cstrSelfDirect.GetLength() > LEN_32?  LEN_32:cstrSelfDirect.GetLength();
	memcpy(tItsRoadwayInfo_V1.cChannelDir, cstrSelfDirect.GetBuffer(), iSize);
	
	tItsRoadwayInfo_V1.iChannelDownUp = m_cboCarUpDown.GetCurSel();
	tItsRoadwayInfo_V1.iUses = m_cboCarUse.GetCurSel();
	if (LEFT_BOUND == m_cboCarBoun.GetCurSel())
	{
		tItsRoadwayInfo_V1.iBorderEnable = 0x01;
	}
	else if (RIGHT_BOUND == m_cboCarBoun.GetCurSel())
	{
		tItsRoadwayInfo_V1.iBorderEnable = 0x10;
	}
	else if (BOTH_BOUND == m_cboCarBoun.GetCurSel())
	{
		tItsRoadwayInfo_V1.iBorderEnable = 0x11;
	}
	else
	{
		tItsRoadwayInfo_V1.iBorderEnable = 0;
	}
	int iCmd = ITS_ROADWAY_CMD_SET_ENABLE;
	int iRet = NetClient_SetITSRoadwayParam(m_iLogonID, iCmd, &tItsRoadwayInfo_V1, sizeof(tItsRoadwayInfo_V1) );
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_SET_ENABLE] (%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_SET_ENABLE] (%d) error(%d)", m_iLogonID, GetLastError());
	}
}

void CLS_ItsRoadwayCommon2::UI_UpdateCarProperty()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TITSRoadwayInfo_V1 tItsRoadwayInfo_V1 = {0};
	tItsRoadwayInfo_V1.iBufSize = sizeof(TITSRoadwayInfo_V1);
	tItsRoadwayInfo_V1.iRoadwayID = m_cboRoadwayId.GetCurSel();
	int iCmd = ITS_ROADWAY_CMD_GET_ENABLE;
	int iRet = NetClient_GetITSRoadwayParam(m_iLogonID, iCmd, &tItsRoadwayInfo_V1, sizeof(tItsRoadwayInfo_V1) );
	if (0 == iRet)
	{
		CButton* pBtn = (CButton*)GetDlgItem(IDC_CHK_ROADWAY_ENABLE);
		if(NULL != pBtn)
		{
			 pBtn->SetCheck(tItsRoadwayInfo_V1.iEnable);
		}
		SetDlgItemText(IDC_EDT_NAME, tItsRoadwayInfo_V1.cChannelName);

		SetDlgItemText(IDC_EDT_SELFDEFINE, tItsRoadwayInfo_V1.cNewChannelID);

		SetDlgItemText(IDC_EDT_DIRECT, tItsRoadwayInfo_V1.cChannelDir);

		int iBeginHour = tItsRoadwayInfo_V1.stStartTime.iHour;
		int iBeginMinute = tItsRoadwayInfo_V1.stStartTime.iMinute;
		//int iBeginSec =  tItsRoadwayInfo_V1.stStartTime.iSecond;
		int iEndHour = tItsRoadwayInfo_V1.stStopTime.iHour;
		int iEndMinute = tItsRoadwayInfo_V1.stStopTime.iMinute;
		//int iEndSec =  tItsRoadwayInfo_V1.stStopTime.iSecond;
		CString strTimeRange;
		strTimeRange.Format("%2d:%2d-%2d:%2d", iBeginHour, iBeginMinute,  iEndHour, iEndMinute);
		//SetDlgItemText(IDC_EDT_SPE_USE, strTimeRange);
		SetDlgItemText(IDC_EDT_SPE_USE_START, strTimeRange);


		CString cstrSelfDefine;
		GetDlgItemText(IDC_EDT_SELFDEFINE, cstrSelfDefine);
		int iSize = cstrSelfDefine.GetLength() > LEN_32?  LEN_32:cstrSelfDefine.GetLength();
		memcpy(tItsRoadwayInfo_V1.cNewChannelID, cstrSelfDefine.GetBuffer(), iSize);

		m_cboCarUpDown.SetCurSel(tItsRoadwayInfo_V1.iChannelDownUp);

		m_cboCarUse.SetCurSel(tItsRoadwayInfo_V1.iUses);

		if (0x01 == tItsRoadwayInfo_V1.iBorderEnable)
		{
			m_cboCarBoun.SetCurSel(1);
		}
		else if (0x10 == tItsRoadwayInfo_V1.iBorderEnable)
		{
			m_cboCarBoun.SetCurSel(2);
		}
		else if (0x11 == tItsRoadwayInfo_V1.iBorderEnable)
		{
			m_cboCarBoun.SetCurSel(3);
		}
		else
		{
			m_cboCarBoun.SetCurSel(0);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam[ITS_ROADWAY_CMD_GET_ENABLE] (%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam[ITS_ROADWAY_CMD_GET_ENABLE] (%d) error(%d)", m_iLogonID, GetLastError());
	}
}	

void CLS_ItsRoadwayCommon2::OnCbnSelchangeCmbRoadwayid()
{
	UI_UpdateSpeedlimit();
	UI_UpdateCarProperty();
	UI_UpdateRoadway();
}
void CLS_ItsRoadwayCommon2::OnCbnSelchangeCmbCarType()
{
	UI_UpdateSpeedlimit();
}

void CLS_ItsRoadwayCommon2::UI_UpdateSpeedUse()
{
	int iCheck = m_cboCarType.GetCurSel();
	if(iCheck == 0)
	{
		m_edtSpeedLow.EnableWindow(FALSE);
		m_edtSpeedHigh.EnableWindow(FALSE);
		m_edtErrorSpeedLow.EnableWindow(FALSE);
		m_edtErrorSpeedHigh.EnableWindow(FALSE);
		m_edtImNotGoodAtEnglish.EnableWindow(FALSE);
		m_edtPercent.EnableWindow(FALSE);
		m_btnSetSpeed.EnableWindow(FALSE);
	}
	else
	{
		m_edtSpeedLow.EnableWindow(TRUE);
		m_edtSpeedHigh.EnableWindow(TRUE);
		m_edtErrorSpeedLow.EnableWindow(TRUE);
		m_edtErrorSpeedHigh.EnableWindow(TRUE);
		m_edtImNotGoodAtEnglish.EnableWindow(TRUE);
		m_edtPercent.EnableWindow(TRUE);
		m_btnSetSpeed.EnableWindow(TRUE);
	}
}

void CLS_ItsRoadwayCommon2::OnBnClickedCheckRoadwayno()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITSRoadwayInfo pa = {0};
	pa.iRoadwayID = m_cboRoadwayId.GetCurSel();
	int iRet = NetClient_GetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_GET_ENABLE, &pa, sizeof(pa));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	}
	pa.iEnable = (m_chkRoadwayNo.GetCheck() == BST_CHECKED)?1:0;
	iRet = NetClient_SetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_SET_ENABLE, &pa, sizeof(pa));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	}
}
