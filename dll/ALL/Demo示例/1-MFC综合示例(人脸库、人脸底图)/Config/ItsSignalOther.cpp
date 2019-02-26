// Cls_ItsSignalOther.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ItsSignalOther.h"

IMPLEMENT_DYNAMIC(Cls_ItsSignalOther, CDialog)

Cls_ItsSignalOther::Cls_ItsSignalOther(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(Cls_ItsSignalOther::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
}

Cls_ItsSignalOther::~Cls_ItsSignalOther()
{
}

void Cls_ItsSignalOther::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	if(_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo;
	}
	
	UpdatePageData1();
	UpdatePageData2();
	UpdatePageData3();
	UpdateCheck();
}

void Cls_ItsSignalOther::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CEK_START_USE, m_chkUseOrNot);
	DDX_Control(pDX, IDC_CBO_SIGNAL_FREQUENCY, m_cboValue);
	DDX_Control(pDX, IDC_CBO_ROADID, m_cboRoadID);
	DDX_Control(pDX, IDC_SLD_EXPOSURE_TIME_LEVEL, m_sldExposureLevel);
	DDX_Control(pDX, IDC_SLD_RED_SATUR_LEVEL, m_sldRedStatus);
	DDX_Control(pDX, IDC_SLD_SWAY_RANGE, m_sldSwayRange);
	DDX_Control(pDX, IDC_SLD_DECETE_LEVEL, m_sldDeceteLevel);
	DDX_Control(pDX, IDC_SLD_OVER_EXPOURSE_ADJUST_LEVEL, m_sldOverExpourseAdjust);
	DDX_Control(pDX, IDC_SLD_HALATION_LEVEL, m_sldHalation);
	DDX_Control(pDX, IDC_CBO_SMOOTH_ENABLE, m_cboSmoothEnable);
	DDX_Control(pDX, IDC_CHK_ENHANCE_TYPE_ENHANCE, m_chkEnhanceUseType[0]);
	DDX_Control(pDX, IDC_CHK_ENHANCE_TYPE_DETECTION, m_chkEnhanceUseType[1]);
	DDX_Control(pDX, IDC_CHK_ENHANCE_TYPE_RED, m_chkEnhanceType[0]);
	DDX_Control(pDX, IDC_CHK_ENHANCE_TYPE_GREEN, m_chkEnhanceType[1]);
}


BEGIN_MESSAGE_MAP(Cls_ItsSignalOther, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_SET_TRAFFIC_RED_LIGHT_GAIN, &Cls_ItsSignalOther::OnBnClickedBtnSetTrafficRedLightGain)
	ON_BN_CLICKED(IDC_CEK_START_USE, &Cls_ItsSignalOther::OnBnClickedCekStartUse)
	ON_BN_CLICKED(IDC_BTN_SET_SIGNAL_FREQUENCY, &Cls_ItsSignalOther::OnBnClickedBtnSetSignalFrequency)
	ON_CBN_SELCHANGE(IDC_CBO_ROADID, &Cls_ItsSignalOther::OnCbnSelchangeCboRoadid)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// Cls_ItsSignalOther 消息处理程序

BOOL Cls_ItsSignalOther::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	UI_UpdateDialog();
		return TRUE;  // return TRUE unless you set the focus to a control
}

void Cls_ItsSignalOther::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}
void Cls_ItsSignalOther::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_CEK_START_USE,IDS_ITS_OPEN_TRAFFIC_LIGHT_GAIN);
	SetDlgItemTextEx(IDC_EDT_TRAFFIC_LIGHT_GAIN, IDS_ITS_VALUE_OF_TRAFFIC_LIGHT_GAIN);
	SetDlgItemTextEx(IDC_STC_LEVEL_OF_RED_LIGHT_GAIN, IDS_ITS_LABLE_OF_LEVEL);
	SetDlgItemTextEx(IDC_BTN_SET_TRAFFIC_RED_LIGHT_GAIN, IDS_ITS_SET_TRAFFIC_LIGHT_GAIN);
	SetDlgItemTextEx(IDC_GP_TRAFFIC_RED_LIGHT_GAIN, IDS_ITS_GROUP_OF_TRAFFIC_LIGHT_GAIN);
	SetDlgItemTextEx(IDC_GP_SIGNAL_TOGHTER, IDS_ITS_GROUP_OF_TRAFFIC_LIGHT_GAIN);
	SetDlgItemTextEx(IDC_STC_SIGNAL_FREQUENCY, IDS_ITS_LABEL_OF_SIGNAL_FREQUENCY);
	SetDlgItemTextEx(IDC_CBO_SIGNAL_FREQUENCY, IDS_ITS_SELECT_VALUE);
	SetDlgItemTextEx(IDC_BTN_SET_SIGNAL_FREQUENCY, IDS_ITS_SET_SIGNAL_FREQUENCY);
	SetDlgItemTextEx(IDC_STC_HANCE_USE_TYPE, IDS_ENHANCE_USE_TYPE);
	SetDlgItemTextEx(IDC_CHK_ENHANCE_TYPE_ENHANCE, IDS_ENHANCE);
	SetDlgItemTextEx(IDC_CHK_ENHANCE_TYPE_DETECTION, IDS_DETECTION);
	SetDlgItemTextEx(IDC_STC_HANCE_TYPE, IDS_ENHANCE_TYPE);
	SetDlgItemTextEx(IDC_CHK_ENHANCE_TYPE_GREEN, IDS_GREEN_LIGHT_ENHANCE);
	SetDlgItemTextEx(IDC_CHK_ENHANCE_TYPE_RED, IDS_CONFIG_ITS_REDLTPLUS);
	SetDlgItemTextEx(IDC_STC_EXPOSURE_TIME_LEVEL, IDS_ENPOURSE_TIME_LEAVE);
	SetDlgItemTextEx(IDC_STC_RED_SATUR_LEVEL, IDS_RED_STATUR);
	SetDlgItemTextEx(IDC_STC_SWAY_RANGE, IDS_SWAY_RANGE);
	SetDlgItemTextEx(IDC_STC_DECETE_LEVEL, IDS_DECETE);
	SetDlgItemTextEx(IDC_STC_OVER_EXPOURSE_ADJUST_LEVEL, IDS_OVER_EXPOURSE_ADJUST);
	SetDlgItemTextEx(IDC_STC_HALATION_LEVEL, IDS_HALATION);
	SetDlgItemTextEx(IDC_STC_SMOOTH_ENABLE, IDS_SMOOTH);
	SetDlgItemTextEx(IDC_STC_LIGHT_POSITION_RULE, IDS_LIGHT_CHANGE_RULE);

	for (int i = 0; i < LIGHT_COUNT_EX; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		InsertString(m_cboRoadID, i, strNo);
	}
	InsertString(m_cboValue,0,"0");
	InsertString(m_cboValue,1,"50");
	InsertString(m_cboValue,2,"100");

	m_sldExposureLevel.SetRange(MIN_SLIDER_VALUE, MAX_SLIDER_VALUE);
	m_sldRedStatus.SetRange(MIN_SLIDER_VALUE, MAX_SLIDER_VALUE);
	m_sldSwayRange.SetRange(MIN_SLIDER_VALUE, MAX_SLIDER_VALUE);
	m_sldDeceteLevel.SetRange(MIN_SLIDER_VALUE, MAX_SLIDER_VALUE);
	m_sldOverExpourseAdjust.SetRange(MIN_SLIDER_VALUE, MAX_SLIDER_VALUE);
	m_sldHalation.SetRange(MIN_SLIDER_VALUE, MAX_SLIDER_VALUE);

	m_cboSmoothEnable.ResetContent();
	m_cboSmoothEnable.SetItemData(m_cboSmoothEnable.AddString(GetTextEx(IDS_CONFIG_FTP_SNAPSHOT_DISABLE)), 0);
	m_cboSmoothEnable.SetItemData(m_cboSmoothEnable.AddString(GetTextEx(IDS_CONFIG_FTP_SNAPSHOT_ENABLE)), 1);
	m_cboSmoothEnable.SetCurSel(0);

}

void Cls_ItsSignalOther::UpdatePageData1()
{
	ITS_EnalbeParam tTrafficLightGain;
	memset(&tTrafficLightGain, 0, sizeof(tTrafficLightGain));
	tTrafficLightGain.iType = ITS_TRAFFIC_LIGHT_GAIN;
	int iRet1 = NetClient_GetITSExtraInfo(m_iLogonID, ITS_ENABLE_CMD_GET, m_iChannelNo, (void*)&tTrafficLightGain, sizeof(tTrafficLightGain));
	if(iRet1 == 0)
	{
		CButton* pBtn = (CButton*)GetDlgItem(IDC_CEK_START_USE);
		if(NULL != pBtn)
		{
			pBtn->SetCheck(tTrafficLightGain.iEnable);
			if(tTrafficLightGain.iEnable == BST_UNCHECKED)
			{
				GetDlgItem(IDC_BTN_SET_TRAFFIC_RED_LIGHT_GAIN)->EnableWindow(FALSE);
			}
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_ENABLE_CMD_GET] %d,%d",m_iLogonID,m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_ENABLE_CMD_GET] %d,%d,error(%d)",m_iLogonID,m_iChannelNo,GetLastError());
	}
}
void Cls_ItsSignalOther::UpdatePageData3()
{
	TITSLightInfoEx tLightInfoEx = {0};
	tLightInfoEx.iBufSize = sizeof(tLightInfoEx);
	tLightInfoEx.m_stLightInfo.iLightID = m_cboRoadID.GetCurSel();
	int iRet = NetClient_GetITSExtraInfo( m_iLogonID, ITS_LIGHTINFO_CMD_GET, m_iChannelNo, &tLightInfoEx, sizeof(int)); 
	if(iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_LIGHTINFO_CMD_GET] %d,%d,error(%d)",m_iLogonID,m_iChannelNo,GetLastError());
		return;
	}

	SetDlgItemInt(IDC_EDT_TEXT_OF_TRAFFIC_RED_LIGHT_GAIN, tLightInfoEx.m_iLightEnhanceLevel);
// 	//增益用途
	for (int i = 0; i < MAX_ENHANCE_USE_TYPE; i++)
	{
		BOOL blEnhanceUseTypeEnable = FALSE;
		blEnhanceUseTypeEnable = (0 != ((tLightInfoEx.iEnhanceUseType) & (1 << i))) ? TRUE : FALSE; 
		m_chkEnhanceUseType[i].SetCheck(blEnhanceUseTypeEnable);
	}


// 	//增益类型
	for (int i = 0; i < MAX_ENHANCE_USE_TYPE; i++)
	{
		BOOL blEnhanceTypeEnable = FALSE;
		blEnhanceTypeEnable = (0 != ((tLightInfoEx.iEnhanceLightType) & (1 << i))) ? TRUE : FALSE; 
		m_chkEnhanceUseType[i].SetCheck(blEnhanceTypeEnable);
	}
	m_sldExposureLevel.SetPos(tLightInfoEx.iExposureTimeLevel);
	m_sldRedStatus.SetPos(tLightInfoEx.iRedSaturationLevel);
	m_sldSwayRange.SetPos(tLightInfoEx.iSwayRange);
	m_sldDeceteLevel.SetPos(tLightInfoEx.iLightDetectLevel);
	m_sldOverExpourseAdjust.SetPos(tLightInfoEx.iOverExposureAdjustLevel);
	m_sldHalation.SetPos(tLightInfoEx.iHalationControlLevel);

	SetDlgItemInt(IDC_STC_EXPOSURE_TIME_LEVEL_POS, tLightInfoEx.iExposureTimeLevel);
	SetDlgItemInt(IDC_STC_RED_SATUR_LEVEL_POS, tLightInfoEx.iRedSaturationLevel);
	SetDlgItemInt(IDC_STC_SWAY_RANGE_POS, tLightInfoEx.iSwayRange);
	SetDlgItemInt(IDC_STC_DECETE_LEVEL_POS, tLightInfoEx.iLightDetectLevel);
	SetDlgItemInt(IDC_STC_OVER_EXPOURSE_ADJUST_LEVEL_POS, tLightInfoEx.iOverExposureAdjustLevel);
	SetDlgItemInt(IDC_STC_HALATION_LEVEL_POS, tLightInfoEx.iHalationControlLevel);

	m_cboSmoothEnable.SetCurSel(GetCboSel(&m_cboSmoothEnable, tLightInfoEx.iSmoothEnable));
	SetDlgItemInt(IDC_EDT_LIGHT_POSITION_RULE, tLightInfoEx.iLightPositionRules);
	
	AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_LIGHTINFO_CMD_GET],%d,%d",m_iLogonID,m_iChannelNo);
}

void Cls_ItsSignalOther::UpdatePageData2()
{
	int iCheck = -1;
	int iRet = NetClient_GetCommonEnable(m_iLogonID, CI_COMMON_ID_ITS_SIGNAL_LIGHT, m_iChannelNo, &iCheck);
	if(iRet == 0)
	{
		if(ITS_NO_USE_SIGNAL_TOGHTER == iCheck)
		{
			m_cboValue.SetCurSel(0);
		}
		else if(ITS_SIGNAL_FREQUENCY_VALUE1 == iCheck)
		{
			m_cboValue.SetCurSel(1);
		}
		else if(ITS_SIGNAL_FREQUENCY_VALUE2 == iCheck)
		{
			m_cboValue.SetCurSel(2);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetCommonEnable[CI_COMMON_ID_ITS_SIGNAL_LIGHT],%d,%d",m_iLogonID,m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetCommonEnable[CI_COMMON_ID_ITS_SIGNAL_LIGHT] %d,%d,error(%d)",m_iLogonID,m_iChannelNo,GetLastError());
	}
}

void Cls_ItsSignalOther::UpdateCheck()
{
	int iCheck = m_chkUseOrNot.GetCheck();
	if(iCheck == BST_UNCHECKED)
	{
		GetDlgItem(IDC_BTN_SET_TRAFFIC_RED_LIGHT_GAIN)->EnableWindow(FALSE);
	}
	if(iCheck == BST_CHECKED)
	{
		GetDlgItem(IDC_BTN_SET_TRAFFIC_RED_LIGHT_GAIN)->EnableWindow(TRUE);
	}
}

void Cls_ItsSignalOther::OnBnClickedBtnSetTrafficRedLightGain()
{
	TITSLightInfoEx tLightInfoEx = {0};
	tLightInfoEx.iBufSize = sizeof(tLightInfoEx);
	tLightInfoEx.m_stLightInfo.iLightID = m_cboRoadID.GetCurSel();
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_LIGHTINFO_CMD_GET, m_iChannelNo, &tLightInfoEx, sizeof(int)) ;
	if(iRet != 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_LIGHTINFO_CMD_GET] %d,%d,error(%d)",m_iLogonID,m_iChannelNo,GetLastError());
		return ;
	}

	//增益等级
	tLightInfoEx.m_iLightEnhanceLevel = GetDlgItemInt(IDC_EDT_TEXT_OF_TRAFFIC_RED_LIGHT_GAIN);
	if(tLightInfoEx.m_iLightEnhanceLevel < 1)
	{
		tLightInfoEx.m_iLightEnhanceLevel = 1;
	}
	else if(tLightInfoEx.m_iLightEnhanceLevel > 255)
	{
		tLightInfoEx.m_iLightEnhanceLevel = 255;
	}

	//增益用途
	int iEnhanceUseType = 0;
	for (int i = 0; i < MAX_ENHANCE_USE_TYPE; i++)
	{
		iEnhanceUseType +=  (((int)(m_chkEnhanceUseType[i].GetCheck())) << i);
	}
	tLightInfoEx.iEnhanceUseType = iEnhanceUseType;

	//增益类型
	int iEnhanceType = 0;
	for (int i = 0; i < MAX_ENHANCE_TYPE; i++)
	{
		iEnhanceType +=  (((int)(m_chkEnhanceType[i].GetCheck())) << i);
	}
	tLightInfoEx.iEnhanceLightType = iEnhanceType;

	//等级参数
	tLightInfoEx.iExposureTimeLevel = m_sldExposureLevel.GetPos();
	tLightInfoEx.iRedSaturationLevel = m_sldRedStatus.GetPos();
	tLightInfoEx.iSwayRange = m_sldSwayRange.GetPos();
	tLightInfoEx.iLightDetectLevel = m_sldDeceteLevel.GetPos();
	tLightInfoEx.iOverExposureAdjustLevel = m_sldOverExpourseAdjust.GetPos();
	tLightInfoEx.iHalationControlLevel = m_sldHalation.GetPos();
	
	tLightInfoEx.iSmoothEnable = (int)m_cboSmoothEnable.GetItemData(m_cboSmoothEnable.GetCurSel());
	tLightInfoEx.iLightPositionRules = GetDlgItemInt(IDC_EDT_LIGHT_POSITION_RULE);

	iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_LIGHTINFO_CMD_SET, m_iChannelNo, (void*)&tLightInfoEx, sizeof(tLightInfoEx));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_LIGHTINFO_CMD_SET][ITS_LIGHTINFO_CMD_GET] (%d, %d)",m_iLogonID, m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_LIGHTINFO_CMD_SET] (%d, %d),error(%d)",m_iLogonID, m_iChannelNo, GetLastError());
	}

}

void Cls_ItsSignalOther::OnBnClickedCekStartUse()
{
	int iCheck = -1;
	ITS_EnalbeParam tTrafficLightGain;
	memset(&tTrafficLightGain, 0, sizeof(tTrafficLightGain));
	tTrafficLightGain.iType = ITS_TRAFFIC_LIGHT_GAIN;
	iCheck = m_chkUseOrNot.GetCheck();
	if(iCheck == BST_UNCHECKED)
	{
		tTrafficLightGain.iEnable = 0;
		GetDlgItem(IDC_BTN_SET_TRAFFIC_RED_LIGHT_GAIN)->EnableWindow(FALSE);
	}
	if(iCheck == BST_CHECKED)
	{
		tTrafficLightGain.iEnable = 1;
		GetDlgItem(IDC_BTN_SET_TRAFFIC_RED_LIGHT_GAIN)->EnableWindow(TRUE);
	}
	int iRet = -1;
	iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_ENABLE_CMD_SET, m_iChannelNo, (void*)&tTrafficLightGain, sizeof(tTrafficLightGain));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_LIGHTINFO_CMD_GET][ITS_ENABLE_CMD_SET] (%d, %d)",m_iLogonID, m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_LIGHTINFO_CMD_GET] (%d, %d),error(%d)",m_iLogonID, m_iChannelNo, GetLastError());
	}
}

void Cls_ItsSignalOther::OnBnClickedBtnSetSignalFrequency()
{
	int iRet = -1;
	int iSignalFrequencyValue = -1;
	int iCheck = m_cboValue.GetCurSel();
	if(iCheck == 0)
		iSignalFrequencyValue = 0;
	else if(iCheck == 1)
		iSignalFrequencyValue = 50;
	else
		iSignalFrequencyValue = 100;
	iRet = NetClient_SetCommonEnable( m_iLogonID, CI_COMMON_ID_ITS_SIGNAL_LIGHT, m_iChannelNo, iSignalFrequencyValue);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[CI_COMMON_ID_ITS_SIGNAL_LIGHT] (%d, %d)",m_iLogonID, m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[CI_COMMON_ID_ITS_SIGNAL_LIGHT] (%d, %d),error(%d)",m_iLogonID, m_iChannelNo, GetLastError());
	}
}

void Cls_ItsSignalOther::OnCbnSelchangeCboRoadid()
{
	UpdatePageData1();
	UpdatePageData2();
	UpdatePageData3();
}

void Cls_ItsSignalOther::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl* pSliderCtrl = (CSliderCtrl*)pScrollBar;
	switch (pSliderCtrl->GetDlgCtrlID())
	{
	case IDC_SLD_RED_SATUR_LEVEL:
		{
			SetDlgItemInt(IDC_STC_RED_SATUR_LEVEL_POS, ((CSliderCtrl*)GetDlgItem(IDC_SLD_RED_SATUR_LEVEL))->GetPos());
		}
		break;
	case IDC_SLD_SWAY_RANGE:
		{
			SetDlgItemInt(IDC_STC_SWAY_RANGE_POS, ((CSliderCtrl*)GetDlgItem(IDC_SLD_SWAY_RANGE))->GetPos());
		}
		break;
	case IDC_SLD_DECETE_LEVEL:
		{
			SetDlgItemInt(IDC_STC_DECETE_LEVEL_POS, ((CSliderCtrl*)GetDlgItem(IDC_SLD_DECETE_LEVEL))->GetPos());
		}
		break;
	case IDC_SLD_OVER_EXPOURSE_ADJUST_LEVEL:
		{
			SetDlgItemInt(IDC_STC_OVER_EXPOURSE_ADJUST_LEVEL_POS, ((CSliderCtrl*)GetDlgItem(IDC_SLD_OVER_EXPOURSE_ADJUST_LEVEL))->GetPos());
		}
		break;
	case IDC_SLD_HALATION_LEVEL:
		{
			SetDlgItemInt(IDC_STC_HALATION_LEVEL_POS, ((CSliderCtrl*)GetDlgItem(IDC_SLD_HALATION_LEVEL))->GetPos());
		}
		break;
	case IDC_SLD_EXPOSURE_TIME_LEVEL:
		{
			SetDlgItemInt(IDC_STC_EXPOSURE_TIME_LEVEL_POS, ((CSliderCtrl*)GetDlgItem(IDC_SLD_EXPOSURE_TIME_LEVEL))->GetPos());
		}
		break;
	default:
		break;
	}
	CLS_BasePage::OnHScroll(nSBCode, nPos, pScrollBar);
}
