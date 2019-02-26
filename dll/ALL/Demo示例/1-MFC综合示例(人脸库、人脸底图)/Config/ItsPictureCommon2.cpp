// Cls_ItsPictureCommon2.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ItsPictureCommon2.h"


// Cls_ItsPictureCommon2 对话框

IMPLEMENT_DYNAMIC(Cls_ItsPictureCommon2, CDialog)

Cls_ItsPictureCommon2::Cls_ItsPictureCommon2(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(Cls_ItsPictureCommon2::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
}

Cls_ItsPictureCommon2::~Cls_ItsPictureCommon2()
{
}

void Cls_ItsPictureCommon2::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_FLASHLAMP, m_chkFlashLamp);
	DDX_Control(pDX, IDC_CHECK_FLASHLAMP_AUTO, m_chkFlashLampAuto);
	DDX_Control(pDX, IDC_CHECK_STROBE, m_chkStrobe);
	DDX_Control(pDX, IDC_CHECK_STROBE_AUTO, m_chkStrobeAuto);
	DDX_Control(pDX, IDC_COMBO_TIMERANGEINDEX2, m_cboTimeRangeIndex2);
	DDX_Control(pDX, IDC_CHECK_TIMERANGEINDEX2, m_chkTimeRangeIndex2);
	DDX_Control(pDX, IDC_EDIT_TIMERANGE2, m_edtTimeRange2);
	DDX_Control(pDX, IDC_BUTTON_TIMERANGE2, m_btnTimeRange2);
	DDX_Control(pDX, IDC_CHK_CAP_ENABLE, m_chkCapEnable);
	DDX_Control(pDX, IDC_CBO_LEVEL, m_cboDenoise3D);
	DDX_Control(pDX, IDC_EDT_VALUE, m_edtDenoise2D);
	DDX_Control(pDX, IDC_COMBO1, m_cboSelectForm);
	DDX_Control(pDX, IDC_BTN_SET, m_btnSet);
	DDX_Control(pDX, IDC_SLD_LIGHT_EXPECT, m_sldLightExpect);
	DDX_Control(pDX, IDC_SLD_EXPO_UPPER_LIMIT, m_sldExpoUpperLimit);
	DDX_Control(pDX, IDC_SLD_GAIN_UPPER_LIMIT, m_sldGainUpperLimit);
	DDX_Control(pDX, IDC_BTN_BACKLIGHT_SET, m_btnSetLight);
	DDX_Control(pDX, IDC_EDT_3D, m_edtDenoise3D);
	DDX_Control(pDX, IDC_EDT_HAND, m_edtDenoiseValue);
}

BOOL Cls_ItsPictureCommon2::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	UI_UpdateDialog();
	InsertString(m_cboDenoise3D, 0, IDS_ITS_LOW);
	InsertString(m_cboDenoise3D, 1, IDS_ITS_MIDDLE);
	InsertString(m_cboDenoise3D, 2, IDS_ITS_HIGH);
	InsertString(m_cboDenoise3D, 3, IDS_ITS_CLOSEDENOISE);
	InsertString(m_cboSelectForm, 0, IDS_ITS_LMANUL);
	InsertString(m_cboSelectForm, 1, IDS_ITS_LSIMPLE);
	InsertString(m_cboSelectForm, 2, IDS_ITS_LDIFFCULT);
	InsertString(m_cboSelectForm, 3, IDS_ITS_LABLE_3D_DENOISE);
	m_sldLightExpect.SetRange(1,255);
	m_sldExpoUpperLimit.SetRange(32,40000);
	m_sldGainUpperLimit.SetRange(1,20);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BEGIN_MESSAGE_MAP(Cls_ItsPictureCommon2, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_BACKLIGHT_SET, &Cls_ItsPictureCommon2::OnBnClickedBtnBacklightSet)
	ON_BN_CLICKED(IDC_BUTTON_TIMERANGE2, &Cls_ItsPictureCommon2::OnBnClickedButtonTimerange2)
	ON_BN_CLICKED(IDC_CHK_CAP_ENABLE, &Cls_ItsPictureCommon2::OnBnClickedChkCapEnable)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_LIGHT_EXPECT, &Cls_ItsPictureCommon2::OnNMCustomdrawSldLightExpect)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_EXPO_UPPER_LIMIT, &Cls_ItsPictureCommon2::OnNMCustomdrawSldExpoUpperLimit)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_GAIN_UPPER_LIMIT, &Cls_ItsPictureCommon2::OnNMCustomdrawSldGainUpperLimit)
	ON_BN_CLICKED(IDC_BTN_PIC_SIZE_LIMIT_SET, &Cls_ItsPictureCommon2::OnBnClickedBtnPicSizeLimitSet)
	ON_BN_CLICKED(IDC_BTN_SET, &Cls_ItsPictureCommon2::OnBnClickedBtnSet)
	ON_CBN_SELCHANGE(IDC_COMBO_TIMERANGEINDEX2, &Cls_ItsPictureCommon2::OnCbnSelchangeComboTimerangeindex2)
	ON_BN_CLICKED(IDC_CHECK_TIMERANGEINDEX2, &Cls_ItsPictureCommon2::OnBnClickedCheckTimerangeindex2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Cls_ItsPictureCommon2::OnCbnSelchangeCombo1)
	ON_STN_CLICKED(IDC_STC_3D_LEVEL, &Cls_ItsPictureCommon2::OnStnClickedStc3dLevel)
	ON_CBN_SELCHANGE(IDC_CBO_LEVEL, &Cls_ItsPictureCommon2::OnCbnSelchangeCboLevel)
END_MESSAGE_MAP()

void Cls_ItsPictureCommon2::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
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
	UI_UpdateTimeAgcFlash();
	UI_UpdateBacklightSet();
	UI_UpdateCap();
	CheckEnable();
	UI_UpdatePageEnable();
	UI_UpdateDenoise();

	int iType = n_Device_Type_Illumination;
	int iRet =  NetClient_QueryDevStatus(m_iLogonID, iType);
	//in callback call
	STR_DevStatus tTmpDevStatus = {0};
	tTmpDevStatus.iType = n_Device_Type_Illumination;
	iRet = NetClient_GetDevStatus(m_iLogonID, &tTmpDevStatus, sizeof(tTmpDevStatus));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevStatus (%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevStatus (%d), error(%d)", m_iLogonID,GetLastError());
	}
}

void Cls_ItsPictureCommon2::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

//void Cls_ItsPictureCommon2::UI_UpdateDenoise()
//{
//	int iCheck = m_cboSelectForm.GetCurSel();
//	if(iCheck == 3)
//	{
//		m_cboDenoise3D.EnableWindow(TRUE);
//		m_edtDenoise2D.EnableWindow(FALSE);
//		m_edtDenoise3D.EnableWindow(FALSE);
//		m_edtDenoiseValue.EnableWindow(FALSE);
//	}
//	else if(iCheck == 2)
//	{
//		m_cboDenoise3D.EnableWindow(FALSE);
//		m_edtDenoise2D.EnableWindow(TRUE);
//		m_edtDenoise3D.EnableWindow(TRUE);
//		m_edtDenoiseValue.EnableWindow(FALSE);
//	}
//	else
//	{
//		m_cboDenoise3D.EnableWindow(FALSE);
//		m_edtDenoise2D.EnableWindow(FALSE);
//		m_edtDenoise3D.EnableWindow(FALSE);
//		m_edtDenoiseValue.EnableWindow(TRUE);
//	}
//}

void Cls_ItsPictureCommon2::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_CAPTURE,IDS_ITS_CAPTURE);
	SetDlgItemTextEx(IDC_CHK_CAP_ENABLE,IDS_ITS_CAPTURE_ENABLE);
	SetDlgItemTextEx(IDC_STA_LIGHT_EXPECT,IDS_ITS_LIGHTEXPECT);
	SetDlgItemTextEx(IDC_STA_EXPO_UPPER_LIMIT,IDS_ITS_EXPOUPLIMIT);
	SetDlgItemTextEx(IDC_STA_GAIN_UPPER_LIMIT,IDS_ITS_GAINUPLIMIT);
	SetDlgItemTextEx(IDC_STA_PIC_HIGH,IDS_ITS_PIC_HIGH);
	SetDlgItemTextEx(IDC_STA_JPEG,IDS_ITS_JPEG_QUA);
	SetDlgItemTextEx(IDC_STA_PIC_SIZE_LIMIT,IDS_ITS_JPEG_SIZE_LIMIT);
	SetDlgItemTextEx(IDC_STATIC_BLOCK,IDS_ITS_BAUPLIGHT);
	SetDlgItemTextEx(IDC_CHECK_FLASHLAMP,IDS_ITS_FLASHLAMP);
	SetDlgItemTextEx(IDC_CHECK_STROBE,IDS_ITS_STROBE);
	SetDlgItemTextEx(IDC_CHECK_FLASHLAMP_AUTO,IDS_ITS_FLASHLAMP_AUTO);
	SetDlgItemTextEx(IDC_CHECK_STROBE_AUTO,IDS_ITS_FLASHLAMP4);

	SetDlgItemTextEx(IDC_STATIC_TIMERANGEINDEX2,IDS_CONFIG_ITS_TIMERANGE_INDEX);
	SetDlgItemTextEx(IDC_STATIC_TIMERANGE2,IDS_CONFIG_ITS_TIMERANGE_RANGE);
	SetDlgItemTextEx(IDC_CHECK_TIMERANGEINDEX2,IDS_CONFIG_ITS_TIMERANGE_ENABLE);
	SetDlgItemTextEx(IDC_BUTTON_TIMERANGE2,IDS_SET);
	SetDlgItemTextEx(IDC_BTN_PIC_SIZE_LIMIT_SET,IDS_SET);
	SetDlgItemTextEx(IDC_BTN_BACKLIGHT_SET,IDS_SET);
	SetDlgItemTextEx(IDC_STA_CURRENT_LIGHT,IDS_ITS_CURRENT_LIGHT);

	SetDlgItemTextEx(IDC_STC_3D_LEVEL, IDS_ITS_LABLE_3D_DENOISE);
	SetDlgItemTextEx(IDC_STC_2D_LEVEL, IDS_ITS_LABLE_2D_DENOISE);
	SetDlgItemTextEx(IDC_STC_3D_VALUE,IDS_ITS_LABLE_3D_DENOISE2);
	SetDlgItemTextEx(IDC_STC_DENOISE_VALUE,IDS_ITS_DENOISE_VALUE);
	SetDlgItemTextEx(IDC_STC_DENOISE_TYPE, IDS_ITS_LABLE_DENOISE_MODE);
	SetDlgItemTextEx(IDC_EDT_VALUE, IDS_ITS_INPUT_2D_DENOISE);
	SetDlgItemTextEx(IDC_BTN_SET, IDS_ITS_SET_DENOISE);

	InsertString(m_cboDenoise3D, 0, IDS_ITS_LOW);
	InsertString(m_cboDenoise3D, 1, IDS_ITS_MIDDLE);
	InsertString(m_cboDenoise3D, 2, IDS_ITS_HIGH);
	InsertString(m_cboDenoise3D, 3, IDS_ITS_CLOSEDENOISE);
	InsertString(m_cboSelectForm, 0, IDS_ITS_LMANUL);
	InsertString(m_cboSelectForm, 1, IDS_ITS_LSIMPLE);
	InsertString(m_cboSelectForm, 2, IDS_ITS_LDIFFCULT);
	//
	for (int i=0; i<8; i++)
	{
		CString strNo;
		strNo.Format("%d" ,i);
		InsertString(m_cboTimeRangeIndex2,i,strNo);
	}
	//InsertString(m_cboTimeRangeIndex2,8,"255");
}

// Cls_ItsPictureCommon2 消息处理程序

void Cls_ItsPictureCommon2::OnBnClickedBtnBacklightSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX2);
	TITS_FlashEnable tTmpFlashEnable = {0};
	int iFlashLampEnable = m_chkFlashLamp.GetCheck();
	int iFlashLampAutoEnable = m_chkFlashLampAuto.GetCheck();
	int iStrobeEnable = m_chkStrobe.GetCheck();
	int iStobeAutoEnable = m_chkStrobeAuto.GetCheck();
	tTmpFlashEnable.m_iSize = sizeof(tTmpFlashEnable);
	tTmpFlashEnable.m_iIndex = iTimeRangeIndex;
	tTmpFlashEnable.m_iFlashLampEnable = iStrobeEnable<<1 | iFlashLampEnable;
	tTmpFlashEnable.m_iVideoLinkEnbale = iFlashLampAutoEnable<<1 | iStobeAutoEnable<<2;

	int iRet = NetClient_SetITSTimeRange(m_iLogonID, iTimeRangeIndex, ITS_CMD_SET_TIMERANGE_FLASHLAMP, &tTmpFlashEnable, sizeof(tTmpFlashEnable));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSTimeRange[ITS_CMD_SET_TIMERANGE_FLASHLAMP] (%d,%d)",m_iLogonID,iTimeRangeIndex);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSTimeRange[ITS_CMD_SET_TIMERANGE_FLASHLAMP] (%d,%d), error(%d)",m_iLogonID, iTimeRangeIndex, GetLastError());
	}
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
}

void Cls_ItsPictureCommon2::OnBnClickedButtonTimerange2()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX2);
	ITS_TTimeRange pa = {0};
	pa.iEnable = (m_chkTimeRangeIndex2.GetCheck() == BST_CHECKED)?1:0;
	char cTimeRange[20];
	GetDlgItemText(IDC_EDIT_TIMERANGE2, cTimeRange, 20);
	int iBeginHour = 0;
	int iTempBeginHour = 0;
	int iBeginMinute = 0;
	int iTempBeginMinute = 0;
	int iEndHour = 0;
	int iTempEndHour = 0;
	int iEndMinute = 0;
	int iTempEndMinute = 0;
	sscanf_s(cTimeRange, "%d:%d-%d:%d", &iBeginHour, &iBeginMinute, &iEndHour, &iEndMinute);
	if(iBeginHour > ITS_MAX_HOUR)
	{
		iBeginHour = ITS_MAX_HOUR;
	}
	if(iBeginMinute > ITS_MAX_MINUTE)
	{
		iBeginMinute = ITS_MAX_MINUTE;
	}
	if(iEndHour > ITS_MAX_HOUR)
	{
		iEndHour = ITS_MAX_HOUR;
	}
	if(iEndMinute > ITS_MAX_MINUTE)
	{
		iEndMinute = ITS_MAX_MINUTE;
	}
	if(iBeginHour > iEndHour)
	{
		MessageBox("The begin time is later than end time!");
	}
	else if((iBeginHour == iEndHour)&&(iBeginMinute > iEndMinute))
	{
		MessageBox("The begin time is later than end time!");
	}
	int iI = 0;
	int iCheck = -1;
	if(pa.iEnable == 1)
	{
		for(iI = 0;iI < 8;iI++)
		{
			if(iI == iTimeRangeIndex)
				continue;
			ITS_TTimeRange tTemp = {0};
			iCheck = NetClient_GetITSTimeRangeEnable(m_iLogonID, m_iChannelNo, iI, &tTemp, sizeof(ITS_TTimeRange));
			if(iCheck == 0)
			{
				iTempBeginHour = (tTemp.iTimeRange >> 24) & 0xFF;
				iTempBeginMinute = (tTemp.iTimeRange >> 16) & 0xFF;
				iTempEndHour = (tTemp.iTimeRange >> 8) & 0xFF;
				iTempEndMinute = tTemp.iTimeRange & 0xFF;
			}
			else
				return;
			if(tTemp.iEnable == 0)
				continue;
			if(iEndHour < iTempBeginHour)
				continue;
			else if(iBeginHour > iTempEndHour)
				continue;
			else if((iBeginHour == iTempEndHour)&&(iBeginMinute > iTempEndMinute))
				continue;
			else if((iEndHour == iTempBeginHour)&&(iEndMinute < iTempBeginMinute))
				continue;
			else
			{
				MessageBox("time range is overlap,please input again!");
				return;
			}
		}
	}
	pa.iTimeRange =  (iBeginHour<<24)|(iBeginMinute<<16)|(iEndHour<<8)| iEndMinute;
	int iRet = NetClient_SetITSTimeRangeEnable(m_iLogonID, m_iChannelNo, iTimeRangeIndex, &pa, sizeof(pa));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSTimeRangeEnable (%d,%d)", m_iLogonID, m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSTimeRangeEnable (%d,%d), error(%d)",m_iLogonID,m_iChannelNo, GetLastError());
	}
}

void Cls_ItsPictureCommon2::CheckEnable()
{
	BOOL blState = ((CButton*)GetDlgItem(IDC_CHK_CAP_ENABLE))->GetCheck();

	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX2);
	ITS_TTimeRange strctCapTimeRange;
	memset(&strctCapTimeRange, 0, sizeof(ITS_TTimeRange));
	if (blState)
	{
		strctCapTimeRange.iEnable = 1;
	}
	else
	{
		strctCapTimeRange.iEnable = 0;
	}

	//7.0版本相机（不包括星光相机）
	int iChannelNo = CHANNEL_PICTURE;
	int iRet = NetClient_SetITSTimeRangeEnable(m_iLogonID, iChannelNo, iTimeRangeIndex, &strctCapTimeRange, sizeof(strctCapTimeRange));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSTimeRangeEnable (%d,%d)",m_iLogonID, iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSTimeRangeEnable (%d,%d), error(%d)",m_iLogonID, m_iChannelNo, GetLastError());
	}
	
	GetDlgItem(IDC_STA_LIGHT_EXPECT)->EnableWindow(blState);      //抓拍参数--亮度期望
	GetDlgItem(IDC_SLD_LIGHT_EXPECT)->EnableWindow(blState);
	GetDlgItem(IDC_STA_LIGHT_EXPECT_VALUE)->EnableWindow(blState);
	GetDlgItem(IDC_STA_EXPO_UPPER_LIMIT)->EnableWindow(blState);  //抓拍参数--曝光上限
	GetDlgItem(IDC_SLD_EXPO_UPPER_LIMIT)->EnableWindow(blState);
	GetDlgItem(IDC_STA_EXPO_UPPER_LIMIT_VALUE)->EnableWindow(blState);
	GetDlgItem(IDC_STA_GAIN_UPPER_LIMIT)->EnableWindow(blState);      //抓拍参数--增益上限
	GetDlgItem(IDC_SLD_GAIN_UPPER_LIMIT)->EnableWindow(blState);
	GetDlgItem(IDC_STA_GAIN_UPPER_LIMIT_VALUE)->EnableWindow(blState);
}

void Cls_ItsPictureCommon2::OnBnClickedChkCapEnable()
{
	CheckEnable();
}

void Cls_ItsPictureCommon2::OnNMCustomdrawSldLightExpect(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX2);//获取当前被选中的时间段 

	ITS_TTimeRangeParam strctTimeRangeParam;
	memset(&strctTimeRangeParam, 0, sizeof(ITS_TTimeRangeParam));
	strctTimeRangeParam.iType = 12;
	//strctTimeRangeParam.iParam1[12] = ((CScrollBar*)GetDlgItem(IDC_SLD_LIGHT_EXPECT))->GetScrollPos();//抓拍参数--亮度期望
	strctTimeRangeParam.iParam1[12] = m_sldLightExpect.GetPos();
	/*double dTemp = 0;
	dTemp = strctTimeRangeParam.iParam1[12] / 100.0;
	dTemp = 1 + 254 * dTemp;*/
	SetDlgItemInt(IDC_STA_LIGHT_EXPECT_VALUE, m_sldLightExpect.GetPos());
	strctTimeRangeParam.iParam2[12] = 255;
	strctTimeRangeParam.iParam3[12] = 1;

	//7.0版本相机（不包括星光相机）
	int iChannel = CHANNEL_PICTURE;
	int iRet = NetClient_SetHDTimeRangeParam(m_iLogonID, iChannel, iTimeRangeIndex, &strctTimeRangeParam, sizeof(strctTimeRangeParam));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetHDTimeRangeParam (%d,%d)",m_iLogonID,iChannel);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetHDTimeRangeParam (%d,%d), error(%d)",m_iLogonID,iChannel, GetLastError());
	}
}

void Cls_ItsPictureCommon2::OnNMCustomdrawSldExpoUpperLimit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	
	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX2);//获取当前被选中的时间段 

	ITS_TTimeRangeParam strctTimeRangeParam;
	memset(&strctTimeRangeParam, 0, sizeof(ITS_TTimeRangeParam));
	strctTimeRangeParam.iType = 3;
	//strctTimeRangeParam.iParam2[3] = ((CScrollBar*)GetDlgItem(IDC_SLD_EXPO_UPPER_LIMIT))->GetScrollPos();//抓拍参数--曝光上限
	strctTimeRangeParam.iParam2[3] = m_sldExpoUpperLimit.GetPos();
	/*double dTemp = 0;
	dTemp = strctTimeRangeParam.iParam1[12] / 100.0;
	dTemp = 32 + 39968 * dTemp;*/
	SetDlgItemInt(IDC_STA_EXPO_UPPER_LIMIT_VALUE, m_sldExpoUpperLimit.GetPos());
	//7.0版本相机（不包括星光相机）
	int iChannel = CHANNEL_PICTURE;
	int iRet = NetClient_SetHDTimeRangeParam(m_iLogonID, iChannel, iTimeRangeIndex, &strctTimeRangeParam, sizeof(strctTimeRangeParam));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetHDTimeRangeParam (%d,%d)", m_iLogonID, iChannel);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetHDTimeRangeParam (%d,%d), error(%d)",m_iLogonID, iChannel, GetLastError);
	}
}

void Cls_ItsPictureCommon2::OnNMCustomdrawSldGainUpperLimit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX2);//获取当前被选中的时间段 

	ITS_TTimeRangeParam strctTimeRangeParam;
	memset(&strctTimeRangeParam, 0, sizeof(ITS_TTimeRangeParam));
	strctTimeRangeParam.iType = 5;
	//strctTimeRangeParam.iParam2[5] = ((CScrollBar*)GetDlgItem(IDC_SLD_GAIN_UPPER_LIMIT))->GetScrollPos();//抓拍参数--增益上限
	strctTimeRangeParam.iParam2[5] = m_sldGainUpperLimit.GetPos();
	/*double dTemp = 0;
	dTemp = strctTimeRangeParam.iParam1[12] / 100.0;
	dTemp = 1 + 19 * dTemp;*/
	SetDlgItemInt(IDC_STA_GAIN_UPPER_LIMIT_VALUE, m_sldGainUpperLimit.GetPos());
	//7.0版本相机（不包括星光相机）
	int iChannel = CHANNEL_PICTURE;
	int iRet = NetClient_SetHDTimeRangeParam(m_iLogonID, iChannel, iTimeRangeIndex, &strctTimeRangeParam, sizeof(strctTimeRangeParam));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetHDTimeRangeParam (%d,%d)",m_iLogonID, iChannel);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetHDTimeRangeParam (%d,%d), error(%d)",m_iLogonID, iChannel, GetLastError);
	}
}

void Cls_ItsPictureCommon2::OnBnClickedBtnPicSizeLimitSet()
{
	int iIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX2);
	ITS_TTimeRangeParam strctTimeRangeParam;
	memset(&strctTimeRangeParam, 0, sizeof(ITS_TTimeRangeParam));

	strctTimeRangeParam.iType = 14;
	//NetClient_GetHDTimeRangeParam(m_iLogonID, m_iChannelNo, iIndex, &strctTimeRangeParam, sizeof(strctTimeRangeParam));
	//strctTimeRangeParam.iAutoEnable[ITS_TYPE_NUM] = 0;

	int iJpegQ = GetDlgItemInt(IDC_EDT_JPEG_VALUE);
	if((iJpegQ < ITS_JPEG_MIN_VALUE ) || ( iJpegQ > ITS_JPEG_MAX_VALUE ))
	{
		//iJpegQ = ITS_JPEG_MIN_VALUE;
		MessageBox("param1 error!");
		return;
	}
	/*if( iJpegQ > ITS_JPEG_MAX_VALUE )
	{
		iJpegQ = ITS_JPEG_MAX_VALUE;
	}*/
	strctTimeRangeParam.iParam1[14] = iJpegQ;
	//if (m_nCameraType == T238_6MP || m_nCameraType == T237_6MP || T238_816_6MP == m_nCameraType)
	int iPicSizeLimit = GetDlgItemInt(IDC_EDT_PIC_SIZE_LIMIT);
	if (iPicSizeLimit < ITS_LIMIT_MIN || iPicSizeLimit > ITS_LIMIT_MAX)
	{
		AddLog(LOG_TYPE_FAIL,"","OnBnClickedBtnJpegSet (%d), error(%d)", m_iLogonID, GetLastError());
		MessageBox("param2 error!");
		return;
	}
	strctTimeRangeParam.iParam2[14] = iPicSizeLimit;

	int iRet = NetClient_SetHDTimeRangeParam(m_iLogonID, m_iChannelNo, iIndex, &strctTimeRangeParam, sizeof(strctTimeRangeParam));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetHDTimeRangeParam (%d,%d,%d)", m_iLogonID, m_iChannelNo, iIndex);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetHDTimeRangeParam (%d,%d,%d), error(%d)", m_iLogonID, m_iChannelNo, iIndex, GetLastError());
	}
}	

void Cls_ItsPictureCommon2::UI_UpdateDenoise()
{
	ITS_TTimeRangeParam tGetDenoise;
	int iRet = -1;
	memset(&tGetDenoise, 0, sizeof(ITS_TTimeRangeParam));
	iRet = NetClient_GetHDTimeRangeParam(m_iLogonID, m_iChannelNo, m_cboTimeRangeIndex2.GetCurSel(), &tGetDenoise, sizeof(ITS_TTimeRangeParam));
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDT_VALUE,tGetDenoise.iParam3[8]);
		m_cboDenoise3D.SetCurSel(tGetDenoise.iParam2[8]);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetHDTimeRangeParam[] (%d, %d)",m_iLogonID, m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetHDTimeRangeParam[] (%d, %d),error(%d)",m_iLogonID, m_iChannelNo, GetLastError());
	}
}	

void Cls_ItsPictureCommon2::UI_UpdateTimeAgcFlash()
{
	if (m_iLogonID < 0)
		return;

	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX2);
	ITS_TTimeRange pa = {0};

	int iRet = NetClient_GetITSTimeRangeEnable(m_iLogonID, m_iChannelNo, iTimeRangeIndex, &pa, sizeof(pa));
	if (0 == iRet)
	{
		m_chkTimeRangeIndex2.SetCheck(pa.iEnable?BST_CHECKED:BST_UNCHECKED);
		int iBeginHour = (pa.iTimeRange)>>24&0xFF;
		int iBeginMinute = (pa.iTimeRange)>>16&0xFF;
		int iEndHour = (pa.iTimeRange)>>8&0xFF;
		int iEndMinute = (pa.iTimeRange)&0xFF;
		CString strTimeRange;
		strTimeRange.Format("%02d:%02d-%02d:%02d", iBeginHour, iBeginMinute, iEndHour, iEndMinute);
		SetDlgItemText(IDC_EDIT_TIMERANGE2, strTimeRange);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSTimeRangeEnable (%d,%d)",m_iLogonID, m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSTimeRangeEnable (%d,%d), error(%d)",m_iLogonID, m_iChannelNo,GetLastError);
	}
}

void Cls_ItsPictureCommon2::UI_UpdatePageEnable()
{
	if(m_chkTimeRangeIndex2.GetCheck())
	{
		m_chkCapEnable.EnableWindow(TRUE);
		m_sldLightExpect.EnableWindow(TRUE);
		m_sldExpoUpperLimit.EnableWindow(TRUE);
		m_sldGainUpperLimit.EnableWindow(TRUE);
		//m_cboDenoise3D.EnableWindow(TRUE);
		//m_cboSelectForm.EnableWindow(TRUE);
		m_edtDenoise2D.EnableWindow(TRUE);
		m_btnSet.EnableWindow(TRUE);
		m_chkFlashLamp.EnableWindow(TRUE);
		m_chkFlashLampAuto.EnableWindow(TRUE);
		m_chkStrobe.EnableWindow(TRUE);
		m_chkStrobeAuto.EnableWindow(TRUE);
		m_btnSetLight.EnableWindow(TRUE);
	}
	else
	{
		m_chkCapEnable.EnableWindow(FALSE);
		m_sldLightExpect.EnableWindow(FALSE);
		m_sldExpoUpperLimit.EnableWindow(FALSE);
		m_sldGainUpperLimit.EnableWindow(FALSE);
		//m_cboDenoise3D.EnableWindow(FALSE);
		//m_cboSelectForm.EnableWindow(FALSE);
		m_edtDenoise2D.EnableWindow(FALSE);
		m_btnSet.EnableWindow(FALSE);
		m_chkFlashLamp.EnableWindow(FALSE);
		m_chkFlashLampAuto.EnableWindow(FALSE);
		m_chkStrobe.EnableWindow(FALSE);
		m_chkStrobeAuto.EnableWindow(FALSE);
		m_btnSetLight.EnableWindow(FALSE);
	}
}

void Cls_ItsPictureCommon2::UI_UpdateBacklightSet()
{
	int iRet = -1;
	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX2);

	TITS_FlashEnable tFlashEnable = {0};
	iRet = NetClient_GetITSTimeRange(m_iLogonID, iTimeRangeIndex, ITS_CMD_GET_TIMERANGE_FLASHLAMP, &tFlashEnable, sizeof(tFlashEnable));
	if (0 == iRet)
	{
		int iFlashLampEnable = (tFlashEnable.m_iFlashLampEnable)&0x1;
		m_chkFlashLamp.SetCheck(iFlashLampEnable);
		int iFlashLampAutoEnable = (tFlashEnable.m_iVideoLinkEnbale>>1)&0x1;
		m_chkFlashLampAuto.SetCheck(iFlashLampAutoEnable);
		int iStrobeEnable = (tFlashEnable.m_iFlashLampEnable>>1)&0x1;
		m_chkStrobe.SetCheck(iStrobeEnable);
		int iStrobeAutoEnable = (tFlashEnable.m_iVideoLinkEnbale>>2)&0x1;
		m_chkStrobeAuto.SetCheck(iStrobeAutoEnable);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSTimeRange[ITS_CMD_GET_TIMERANGE_FLASHLAMP] (%d)",m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSTimeRange[ITS_CMD_GET_TIMERANGE_FLASHLAMP] (%d), error(%d)",m_iLogonID, GetLastError());
	}
}

void Cls_ItsPictureCommon2::UI_UpdateCap()
{
	int iRet = -1;
	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX2);

	ITS_TTimeRange strctCapTimeRange;
	memset(&strctCapTimeRange, 0, sizeof(ITS_TTimeRange));
	//7.0版本相机（不包括星光相机）
	int iChannelNo = CHANNEL_PICTURE;
	iRet = NetClient_GetITSTimeRangeEnable(m_iLogonID, iChannelNo, iTimeRangeIndex, &strctCapTimeRange, sizeof(strctCapTimeRange));
	if (0 == iRet)
	{
		m_chkCapEnable.SetCheck(strctCapTimeRange.iEnable);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSTimeRangeEnable-Capture (%d)",m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSTimeRangeEnable-Capture (%d), error(%d)",m_iLogonID, GetLastError());
	}
	//
	ITS_TTimeRangeParam strctTimeRangeParam;
	memset(&strctTimeRangeParam, 0, sizeof(ITS_TTimeRangeParam));
	//only IS_CAM_V70_TD
	iRet = NetClient_GetHDTimeRangeParam(m_iLogonID, iChannelNo, iTimeRangeIndex, &strctTimeRangeParam, sizeof(strctTimeRangeParam));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetHDTimeRangeParam (%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetHDTimeRangeParam (%d), error(%d)", m_iLogonID, GetLastError());
	}

	//((CScrollBar*)GetDlgItem(IDC_SLD_LIGHT_EXPECT))->SetScrollPos(strctTimeRangeParam.iParam1[12]);//抓拍参数--亮度期望
	m_sldLightExpect.SetPos(strctTimeRangeParam.iParam1[12]);
	CString cstrCaptureLightExpect;
	cstrCaptureLightExpect.Format("%d", strctTimeRangeParam.iParam1[12]);
	GetDlgItem(IDC_STA_LIGHT_EXPECT_VALUE)->SetWindowText(cstrCaptureLightExpect);//亮度期望


	//((CScrollBar*)GetDlgItem(IDC_SLD_EXPO_UPPER_LIMIT))->SetScrollPos(strctTimeRangeParam.iParam2[3]);//抓拍参数--曝光上限
	m_sldExpoUpperLimit.SetPos(strctTimeRangeParam.iParam2[3]);
	CString cstrCaptureExposalUpLimit;
	cstrCaptureExposalUpLimit.Format("%d", strctTimeRangeParam.iParam2[3]);
	GetDlgItem(IDC_STA_EXPO_UPPER_LIMIT_VALUE)->SetWindowText(cstrCaptureExposalUpLimit);//曝光上限

	//((CScrollBar*)GetDlgItem(IDC_SLD_GAIN_UPPER_LIMIT))->SetScrollPos(strctTimeRangeParam.iParam2[5]);//抓拍参数--增益上限
	m_sldGainUpperLimit.SetPos(strctTimeRangeParam.iParam2[5]);
	CString cstrCaptureGainUpLimit;
	cstrCaptureGainUpLimit.Format("%d", strctTimeRangeParam.iParam2[5]);
	GetDlgItem(IDC_STA_GAIN_UPPER_LIMIT_VALUE)->SetWindowText(cstrCaptureGainUpLimit);//增益上限
}

void Cls_ItsPictureCommon2::UI_UpdatePic()
{
	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX2);
	ITS_TTimeRangeParam strctTimeRangeParam;
	memset(&strctTimeRangeParam, 0, sizeof(ITS_TTimeRangeParam));
	strctTimeRangeParam.iType = 5;
	int iChannelNo = 0;
	int iRet = NetClient_GetHDTimeRangeParam(m_iLogonID, iChannelNo, iTimeRangeIndex, &strctTimeRangeParam, sizeof(strctTimeRangeParam));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetHDTimeRangeParam (%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetHDTimeRangeParam (%d), error(%d)", m_iLogonID, GetLastError());
	}

	//获取JPEG品质
	CString cstrJPEGQuality ="";
	int iQuality = 0;
	if(strctTimeRangeParam.iParam1[14] > 100 )
	{
		iQuality = 100;
	}
	else if( strctTimeRangeParam.iParam1[14] < 0 )
	{
		iQuality = 0;
	}
	else
	{
		iQuality = strctTimeRangeParam.iParam1[14];
	}
	SetDlgItemInt(IDC_EDT_JPEG_VALUE, iQuality);

	//if (m_nCameraType == T238_6MP || m_nCameraType == T237_6MP|| T238_816_6MP == m_nCameraType)
	//获取图片大小
	int iPicSizeLimit = strctTimeRangeParam.iParam2[14];
	SetDlgItemInt(IDC_EDT_PIC_SIZE_LIMIT, iPicSizeLimit);
}

void Cls_ItsPictureCommon2::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
{
	switch(_iParaType)
	{
	case PARA_DEVSTATUS:
		{
			//STR_Para* pPara = (STR_Para*)_pPara;
			//int iDevType = pPara->m_iPara[0];
			//int iParam[MAX_DEVSTATUS_NUM]={0};
			//for (int i = 0; i < MAX_DEVSTATUS_NUM; ++i)
			//{
			//	iParam[i] = pPara->m_iPara[i+1];
			//}
			STR_DevStatus tTmpDevStatus = {0};
			tTmpDevStatus.iType = n_Device_Type_Illumination;
			int iRet = NetClient_GetDevStatus(m_iLogonID, &tTmpDevStatus, sizeof(tTmpDevStatus));
			if (0 == iRet)
			{
				SetDlgItemInt(IDC_EDT_CURRENT_LIGHT, tTmpDevStatus.iStatus[0]);
				AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevStatus (%d)", m_iLogonID);
			} 
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevStatus (%d), error(%d)", m_iLogonID,GetLastError());
			}
		}
		break;
	default:
		break;
	}
}

void Cls_ItsPictureCommon2::OnBnClickedBtnSet()
{
	// TODO: 在此添加控件通知处理程序代码
	ITS_TTimeRangeParam tDenoise;
	int iRet = -1;
	memset(&tDenoise, 0, sizeof(ITS_TTimeRangeParam));
	tDenoise.iType = CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT;
	tDenoise.iAutoEnable[CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT] = 2;
	tDenoise.iParam3[CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT] = GetDlgItemInt(IDC_EDT_VALUE);
	/*int iCheck = m_cboSelectForm.GetCurSel();
	if(iCheck == 3)
	{
		tDenoise.iAutoEnable[4] = iCheck;
		tDenoise.iParam1[8] = 3 - m_cboDenoise3D.GetCurSel();
	}
	else if(iCheck == 2)
	{
		tDenoise.iAutoEnable[4] = iCheck;
		tDenoise.iParam1[CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT] = GetDlgItemInt(IDC_EDT_VALUE);
		tDenoise.iParam2[CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT] = GetDlgItemInt(IDC_EDT_3D);
	}
	else
	{
		tDenoise.iAutoEnable[4] = iCheck;
		tDenoise.iParam1[CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT] = GetDlgItemInt(IDC_EDT_HAND);
	}*/
	iRet = NetClient_SetHDTimeRangeParam(m_iLogonID, m_iChannelNo, m_cboTimeRangeIndex2.GetCurSel(), &tDenoise, sizeof(tDenoise));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetHDTimeRangeParam[] (%d, %d)",m_iLogonID, 4);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetHDTimeRangeParam[] (%d, %d),error(%d)",m_iLogonID, 4, GetLastError());
	}
}


void Cls_ItsPictureCommon2::OnCbnSelchangeComboTimerangeindex2()
{
	UI_UpdateTimeAgcFlash();
	UI_UpdateBacklightSet();
	UI_UpdateCap();
	UI_UpdatePic();
	CheckEnable();
	UI_UpdatePageEnable();
	UI_UpdateDenoise();
}


void Cls_ItsPictureCommon2::OnBnClickedCheckTimerangeindex2()
{
	UI_UpdatePageEnable();
}

void Cls_ItsPictureCommon2::OnCbnSelchangeCombo1()
{
	//UI_UpdateDenoise();
}

void Cls_ItsPictureCommon2::OnStnClickedStc3dLevel()
{
	// TODO: 在此添加控件通知处理程序代码
}

void Cls_ItsPictureCommon2::OnCbnSelchangeCboLevel()
{
	ITS_TTimeRangeParam tDenoise;
	int iRet = -1;
	memset(&tDenoise, 0, sizeof(ITS_TTimeRangeParam));
	tDenoise.iType = CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT;
	tDenoise.iAutoEnable[CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT] = 3;
	tDenoise.iParam2[CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT] = m_cboDenoise3D.GetCurSel() + 1;
	iRet = NetClient_SetHDTimeRangeParam(m_iLogonID, m_iChannelNo, m_cboTimeRangeIndex2.GetCurSel(), &tDenoise, sizeof(tDenoise));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetHDTimeRangeParam[] (%d, %d)",m_iLogonID, 4);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetHDTimeRangeParam[] (%d, %d),error(%d)",m_iLogonID, 4, GetLastError());
	}
}
