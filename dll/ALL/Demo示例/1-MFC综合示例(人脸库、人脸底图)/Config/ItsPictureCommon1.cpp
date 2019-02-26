// ITSTimeRangePage.cpp : implementation file
//

#include "stdafx.h"
#include "ItsPictureCommon1.h"


// CLS_ITSTimeRangePage dialog

IMPLEMENT_DYNAMIC(Cls_ItsPictureCommon1, CDialog)

Cls_ItsPictureCommon1::Cls_ItsPictureCommon1(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(Cls_ItsPictureCommon1::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
}

Cls_ItsPictureCommon1::~Cls_ItsPictureCommon1()
{
}

void Cls_ItsPictureCommon1::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TIMERANGEINDEX, m_cboTimeRangeIndex);
	DDX_Control(pDX, IDC_CHECK_TIMERANGEINDEX, m_chkTimeRangeIndex);
	DDX_Control(pDX, IDC_EDIT_TIMERANGE, m_edtTimeRange);
	DDX_Control(pDX, IDC_BUTTON_TIMERANGE, m_btnTimeRange);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cboType);
	DDX_Control(pDX, IDC_COMBO_AUTOENABLE, m_cboAutoEnable);
	DDX_Control(pDX, IDC_EDIT_TIMERANGE_PARAM1, m_edtParam[0]);
	DDX_Control(pDX, IDC_EDIT_TIMERANGE_PARAM2, m_edtParam[1]);
	DDX_Control(pDX, IDC_EDIT_TIMERANGE_PARAM3, m_edtParam[2]);
	DDX_Control(pDX, IDC_EDIT_TIMERANGE_PARAM4, m_edtParam[3]);
	DDX_Control(pDX, IDC_BUTTON_PARAM, m_btnParam);
	DDX_Control(pDX, IDC_CHECK_AGCBLOCK_BIT0, m_chkBit[0]);
	DDX_Control(pDX, IDC_CHECK_AGCBLOCK_BIT1, m_chkBit[1]);
	DDX_Control(pDX, IDC_CHECK_AGCBLOCK_BIT2, m_chkBit[2]);
	DDX_Control(pDX, IDC_CHECK_AGCBLOCK_BIT3, m_chkBit[3]);
	DDX_Control(pDX, IDC_CHECK_AGCBLOCK_BIT4, m_chkBit[4]);
	DDX_Control(pDX, IDC_COMBO_BLOCK, m_cboBlock);
	DDX_Control(pDX, IDC_EDIT_BLOCK_X, m_edtBlockX);
	DDX_Control(pDX, IDC_EDIT_BLOCK_Y, m_edtBlockY);
	DDX_Control(pDX, IDC_BUTTON_BLOCK, m_btnBlock);
	DDX_Control(pDX, IDC_COMBO_DEVICETYPE, m_cboDeviceType);
	DDX_Control(pDX, IDC_BUTTON_DEVICETYPE, m_chkDeviceType);
	DDX_Control(pDX, IDC_COMBO_CAMERAPARAM, m_cboCameraParam);
	DDX_Control(pDX, IDC_EDIT_VALUE, m_edtValue);
	DDX_Control(pDX, IDC_BUTTON_CAMERA, m_btnCamera);
	DDX_Control(pDX, IDC_BUTTON_AGCBLOCK, m_btnSetArea);
}


BEGIN_MESSAGE_MAP(Cls_ItsPictureCommon1, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_TIMERANGEINDEX, &Cls_ItsPictureCommon1::OnCbnSelchangeComboTimerangeindex)
	ON_BN_CLICKED(IDC_BUTTON_TIMERANGE, &Cls_ItsPictureCommon1::OnBnClickedButtonTimerange)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &Cls_ItsPictureCommon1::OnCbnSelchangeComboType)
	ON_BN_CLICKED(IDC_BUTTON_PARAM, &Cls_ItsPictureCommon1::OnBnClickedButtonParam)
	ON_BN_CLICKED(IDC_BUTTON_AGCBLOCK, &Cls_ItsPictureCommon1::OnBnClickedButtonAgcblock)
	ON_CBN_SELCHANGE(IDC_COMBO_BLOCK, &Cls_ItsPictureCommon1::OnCbnSelchangeComboBlock)
	ON_BN_CLICKED(IDC_BUTTON_BLOCK, &Cls_ItsPictureCommon1::OnBnClickedButtonBlock)
	ON_BN_CLICKED(IDC_BUTTON_DEVICETYPE, &Cls_ItsPictureCommon1::OnBnClickedButtonDevicetype)
	ON_CBN_SELCHANGE(IDC_COMBO_CAMERAPARAM, &Cls_ItsPictureCommon1::OnCbnSelchangeComboCameraparam)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA, &Cls_ItsPictureCommon1::OnBnClickedButtonCamera)
	ON_CBN_SELCHANGE(IDC_COMBO_AUTOENABLE, &Cls_ItsPictureCommon1::OnCbnSelchangeComboAutoenable)
	ON_EN_CHANGE(IDC_EDIT_TIMERANGE_PARAM1, &Cls_ItsPictureCommon1::OnEnChangeEditTimerangeParam1)
	ON_BN_CLICKED(IDC_CHECK_TIMERANGEINDEX, &Cls_ItsPictureCommon1::OnBnClickedCheckTimerangeindex)
END_MESSAGE_MAP()


// CLS_ITSTimeRangePage message handlers
BOOL Cls_ItsPictureCommon1::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	for (int i=0; i<8; i++)
	{
		CString strNo;
		strNo.Format("%d" ,i);
		m_cboTimeRangeIndex.AddString(strNo);
	}
	m_cboTimeRangeIndex.SetCurSel(0);

	m_edtTimeRange.SetLimitText(20);
	for (int i=0; i<4; i++)
	{
		m_edtParam[i].SetLimitText(20);
	}
	m_edtBlockX.SetLimitText(10);
	m_edtBlockY.SetLimitText(10);
	m_edtValue.SetLimitText(5);

	for (int i=0; i<5; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboBlock.AddString(strNo);
	}
	m_cboBlock.SetCurSel(0);

	m_cboDeviceType.AddString("0--CSR_IK16");
	m_cboDeviceType.AddString("1--CSR90NGA");
	m_cboDeviceType.AddString("2--T324V20");
	m_cboDeviceType.AddString("3--T324E");

	//m_cboCameraParam.AddString("JPEGQulity");
	m_cboCameraParam.AddString("LUT");

	UI_UpdateDialog();

	return TRUE;
}

void Cls_ItsPictureCommon1::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
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

	UI_UpdateAutoSetDialog();
	UI_UpdateTimeAgcFlash();
	UI_UpdateTimeRangeParam();
	UI_UpdateBlock();
	UI_UpdateGPEGQuality();
	UI_UpdateDevicetype();
	UI_UpdatePageEnable();
}

void Cls_ItsPictureCommon1::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void Cls_ItsPictureCommon1::UI_UpdateDialog()
{
	InsertString(m_cboType,0,IDS_CONFIG_ITS_TYPE0);
	InsertString(m_cboType,1,IDS_CONFIG_ITS_TYPE1);
	InsertString(m_cboType,2,IDS_CONFIG_ITS_TYPE2);
	InsertString(m_cboType,3,IDS_CONFIG_ITS_TYPE3);
	InsertString(m_cboType,4,IDS_CONFIG_ITS_TYPE4);
	InsertString(m_cboType,5,IDS_CONFIG_ITS_TYPE5);
	InsertString(m_cboType,6,IDS_CONFIG_ITS_TYPE6);
	InsertString(m_cboType,7,IDS_CONFIG_ITS_TYPE7);
	InsertString(m_cboType,8,IDS_CONFIG_ITS_TYPE8);
	InsertString(m_cboType,9,IDS_CONFIG_ITS_TYPE9);
	InsertString(m_cboType,10,IDS_CONFIG_ITS_TYPE10);
	InsertString(m_cboType,11,IDS_CONFIG_ITS_TYPE11);
	InsertString(m_cboType,12,IDS_CONFIG_ITS_TYPE12);
	InsertString(m_cboType,13,IDS_CONFIG_ITS_TYPE13);
	InsertString(m_cboType,14,IDS_CONFIG_ITS_TYPE14);
	InsertString(m_cboType,15,IDS_CONFIG_ITS_TYPE15);
	InsertString(m_cboType,16,IDS_CONFIG_ITS_TYPE16);
	InsertString(m_cboType,17,IDS_CONFIG_ITS_TYPE17);
	InsertString(m_cboType,18,IDS_CONFIG_ITS_TYPE18);
	InsertString(m_cboType,19,IDS_CONFIG_ITS_TYPE19);

	SetDlgItemTextEx(IDC_STATIC_TIMERANGEINDEX,IDS_CONFIG_ITS_TIMERANGE_INDEX);
	SetDlgItemTextEx(IDC_CHECK_TIMERANGEINDEX,IDS_CONFIG_ITS_TIMERANGE_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_TIMERANGE,IDS_CONFIG_ITS_TIMERANGE_RANGE);
	SetDlgItemTextEx(IDC_BUTTON_TIMERANGE,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_TIMERANGEPARAM,IDS_CONFIG_ITS_TIMERANGE_PARAM);
	SetDlgItemTextEx(IDC_STATIC_TYPE,IDS_CONFIG_ITS_TIMERANGE_TYPE);
	SetDlgItemTextEx(IDC_STATIC_AUTOENABLE,IDS_CONFIG_ITS_TIMERANGE_AUTOENABLE);
	SetDlgItemTextEx(IDC_STATIC_PARAM1,IDS_CONFIG_ITS_TIMERANGE_PARAM1);
	SetDlgItemTextEx(IDC_STATIC_PARAM2,IDS_CONFIG_ITS_TIMERANGE_PARAM2);
	SetDlgItemTextEx(IDC_STATIC_PARAM3,IDS_CONFIG_ITS_TIMERANGE_PARAM3);
	SetDlgItemTextEx(IDC_STATIC_PARAM4,IDS_CONFIG_ITS_TIMERANGE_PARAM4);
	SetDlgItemTextEx(IDC_BUTTON_PARAM,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_AGCBLOCK,IDS_CONFIG_ITS_TIMERANGE_AGCBLOCK);
	SetDlgItemTextEx(IDC_BUTTON_AGCBLOCK,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_BLOCK,IDS_CONFIG_ITS_TIMERANGE_BLOCK);
	SetDlgItemTextEx(IDC_BUTTON_FLASHLAMP,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_BLOCK,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_DEVICETYPE,IDS_CONFIG_ITS_TIMERANGE_DEVICETYPE);
	SetDlgItemTextEx(IDC_BUTTON_DEVICETYPE,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_CAMERAPARAM,IDS_CONFIG_ITS_TIMERANGE_CAMERAPARAM);
	SetDlgItemTextEx(IDC_STATIC_VALUE,IDS_CONFIG_ITS_TIMERANGE_VALUE);
	SetDlgItemTextEx(IDC_BUTTON_CAMERA,IDS_SET);
}

void Cls_ItsPictureCommon1::UI_UpdateAutoSetDialog()
{
	int iType = m_cboType.GetCurSel();
	if(iType == CAMERA_PARA_WHITE_BALANCE_ADJUSTMENT)
	{
		m_cboAutoEnable.ResetContent();
		InsertString(m_cboAutoEnable,0,IDS_CONFIG_ITS_AUTOENABLE0);
		InsertString(m_cboAutoEnable,1,IDS_CONFIG_ITS_AUTOENABLE1);
		InsertString(m_cboAutoEnable,2,IDS_CONFIG_ITS_AUTOENABLE2);
	}
	else if(iType == CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT)
	{
		m_cboAutoEnable.ResetContent();
		InsertString(m_cboAutoEnable,0,IDS_ITS_LMANUL);
		InsertString(m_cboAutoEnable,1,IDS_ITS_LSIMPLE);
		InsertString(m_cboAutoEnable,2,IDS_ITS_LDIFFCULT);
		InsertString(m_cboAutoEnable,3,IDS_ITS_LABLE_3D_DENOISE);
	}
	else
	{
		m_cboAutoEnable.ResetContent();
		InsertString(m_cboAutoEnable,0,IDS_MANUAL);
		InsertString(m_cboAutoEnable,1,IDS_DOME_AUTO);
	}
}

void Cls_ItsPictureCommon1::UI_UpdatePageEnable()
{
	
	if(m_chkTimeRangeIndex.GetCheck())
	{
		m_cboType.EnableWindow(TRUE);
		m_cboAutoEnable.EnableWindow(TRUE);
		m_btnParam.EnableWindow(TRUE);
		m_btnSetArea.EnableWindow(TRUE);
		m_cboBlock.EnableWindow(TRUE);
		m_btnBlock.EnableWindow(TRUE);
		m_cboDeviceType.EnableWindow(TRUE);
		m_chkDeviceType.EnableWindow(TRUE);
		m_cboCameraParam.EnableWindow(TRUE);
		m_btnCamera.EnableWindow(TRUE);
	}
	else
	{
		m_cboType.EnableWindow(FALSE);
		m_cboAutoEnable.EnableWindow(FALSE);
		m_btnParam.EnableWindow(FALSE);
		m_btnSetArea.EnableWindow(FALSE);
		m_cboBlock.EnableWindow(FALSE);
		m_btnBlock.EnableWindow(FALSE);
		m_cboDeviceType.EnableWindow(FALSE);
		m_chkDeviceType.EnableWindow(FALSE);
		m_cboCameraParam.EnableWindow(FALSE);
		m_btnCamera.EnableWindow(FALSE);
	}
}

BOOL Cls_ItsPictureCommon1::UI_UpdateTimeAgcFlash()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX);
	ITS_TTimeRange pa = {0};
	int iRet = NetClient_GetITSTimeRangeEnable(m_iLogonID, m_iChannelNo, iTimeRangeIndex, &pa, sizeof(pa));
	if (0 == iRet)
	{
		m_chkTimeRangeIndex.SetCheck(pa.iEnable?BST_CHECKED:BST_UNCHECKED);
		int iBeginHour = (pa.iTimeRange)>>24&0xFF;
		int iBeginMinute = (pa.iTimeRange)>>16&0xFF;
		int iEndHour = (pa.iTimeRange)>>8&0xFF;
		int iEndMinute = (pa.iTimeRange)&0xFF;
		CString strTimeRange;
		strTimeRange.Format("%02d:%02d-%02d:%02d", iBeginHour, iBeginMinute, iEndHour, iEndMinute);
		SetDlgItemText(IDC_EDIT_TIMERANGE, strTimeRange);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSTimeRangeEnable (%d,%d)",m_iLogonID, m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSTimeRangeEnable (%d,%d), error(%d)",m_iLogonID, m_iChannelNo, GetLastError());
	}
	int iAgcBlock = -1;
	iRet = NetClient_GetITSTimeRange(m_iLogonID, iTimeRangeIndex, ITS_CMD_GET_TIMERANGE_AGCBLOCK, &iAgcBlock, sizeof(iAgcBlock));
	if (0 == iRet)
	{
		for (int i=0; i<5; i++)
		{
			m_chkBit[i].SetCheck(((iAgcBlock>>i)&0x01)?BST_CHECKED:BST_UNCHECKED);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSTimeRange[ITS_CMD_GET_TIMERANGE_AGCBLOCK] (%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSTimeRange[ITS_CMD_GET_TIMERANGE_AGCBLOCK] (%d), error(%d)",m_iLogonID, GetLastError());
	}
	return TRUE;
}
void Cls_ItsPictureCommon1::OnCbnSelchangeComboTimerangeindex()
{
	UI_UpdateTimeAgcFlash();
	UI_UpdateTimeRangeParam();
	UI_UpdatePageEnable();

}
void Cls_ItsPictureCommon1::OnBnClickedButtonTimerange()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX);
	ITS_TTimeRange pa = {0};
	pa.iEnable = (m_chkTimeRangeIndex.GetCheck() == BST_CHECKED)?1:0;
	char cTimeRange[20];
	GetDlgItemText(IDC_EDIT_TIMERANGE, cTimeRange, 20);
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
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSTimeRangeEnable (%d,%d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}
}

BOOL Cls_ItsPictureCommon1::UI_UpdateTimeRangeParam()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX);
	int iType = m_cboType.GetCurSel();
	ITS_TTimeRangeParam pb = {0};
	int iRet = NetClient_GetHDTimeRangeParam(m_iLogonID, m_iChannelNo, iTimeRangeIndex, &pb, sizeof(pb));
	if (0 == iRet)
	{
		m_cboAutoEnable.SetCurSel(pb.iAutoEnable[iTimeRangeIndex]);
		SetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1, pb.iParam1[iType]);
		SetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2, pb.iParam2[iType]);
		SetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM3, pb.iParam3[iType]);
		SetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM4, pb.iParam4[iType]);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetHDTimeRangeParam (%d,%d)",m_iLogonID,m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetHDTimeRangeParam (%d,%d), error(%d)",m_iLogonID, m_iChannelNo,GetLastError());
	}
	return TRUE;
}

void Cls_ItsPictureCommon1::OnCbnSelchangeComboType()
{
	UI_UpdateAutoSetDialog();
	UI_UpdateTimeRangeParam();
	int iType = m_cboType.GetCurSel();
	int iAUTOEnable = m_cboAutoEnable.GetCurSel();
	if(iType == CAMERA_PARA_IRIS_ADJUSTMENT)
	{
		m_cboAutoEnable.EnableWindow(TRUE);
	}
	else if((iType == CAMERA_PARA_IRIS_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
	}
	else if((iType == CAMERA_PARA_WDR) || (iType == CAMERA_PARA_BLC))
	{
		m_cboAutoEnable.EnableWindow(FALSE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(TRUE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if(iType == CAMERA_PARA_EXPOSURE_TIME)
	{
		m_cboAutoEnable.EnableWindow(TRUE);
	}
	else if((iType == CAMERA_PARA_EXPOSURE_TIME) && (iAUTOEnable == AUTO_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
	}
	else if((iType == CAMERA_PARA_SHUTTER_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
	}
	else if((iType == CAMERA_PARA_SHUTTER_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
	}
	else if((iType == CAMERA_PARA_GAIN_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
	}
	else if((iType == CAMERA_PARA_GAIN_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
	}
	else if((iType == CAMERA_PARA_GAMMA_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
	}
	else if((iType == CAMERA_PARA_GAMMA_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
	}
	else if((iType == CAMERA_PARA_SHARPNESS_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
	}
	else if((iType == CAMERA_PARA_SHARPNESS_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
	}
	else if(iType == CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT)
	{
		m_cboAutoEnable.EnableWindow(TRUE);
	}
	else if((iType == CAMERA_PARA_EXPOSURE_REGION) || (iType == CAMERA_PARA_BLC_REGION) || (iType == CAMERA_PARA_AF_REGION_SET))
	{
		m_cboAutoEnable.EnableWindow(FALSE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(TRUE);
		m_edtParam[2].EnableWindow(TRUE);
		m_edtParam[3].EnableWindow(TRUE);
	}
	else if(iType == CAMERA_PARA_TARGET_BRIGHTNESS_ADJUSTMENT)
	{
		
		m_cboAutoEnable.EnableWindow(TRUE);
	}
	else if(iType == CAMERA_PARA_WHITE_BALANCE_ADJUSTMENT)
	{
		m_cboAutoEnable.EnableWindow(TRUE);
	}
	else if(iType == CAMERA_PARA_JPEG_IMAGE_QUALITY)
	{
		m_cboAutoEnable.EnableWindow(FALSE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(TRUE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_LUT_ENABLE) || (iType == CAMERA_PARA_AUTOMATIC_BRIGHTNESS_ADJUST))
	{
		m_cboAutoEnable.EnableWindow(FALSE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(FALSE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if(iType == CAMERA_PARA_HSBLC)
	{
		m_cboAutoEnable.EnableWindow(FALSE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(TRUE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_AUTO_EXPOSURE_MODE) || (iType == CAMERA_PARA_SCENE_MODE))
	{
		m_cboAutoEnable.EnableWindow(FALSE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(FALSE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}
}

void Cls_ItsPictureCommon1::OnBnClickedButtonParam()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iType = m_cboType.GetCurSel();
	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX);
	int iAUTOEnable = m_cboAutoEnable.GetCurSel();
	ITS_TTimeRangeParam pb = {0};
	pb.iAutoEnable[iTimeRangeIndex] = iAUTOEnable;
	pb.iType = iType;
	if((iType == CAMERA_PARA_IRIS_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		if((pb.iParam1[iType] > PARAM_LIMIT26) || (pb.iParam1[iType] < PARAM_LIMIT0))
		{
			MessageBox("param error!");
				return;
		}
	}
	else if((iType == CAMERA_PARA_IRIS_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		if((pb.iParam1[iType] > PARAM_LIMIT1) || (pb.iParam1[iType] < PARAM_LIMIT0))
		{
			MessageBox("param1 error!");
			return;
		}
		if(pb.iParam1[iType] == 1)
		{
			pb.iParam2[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
		}
	}
	else if(iType == CAMERA_PARA_WDR)
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		if((pb.iParam1[iType] > PARAM_LIMIT2) || (pb.iParam1[iType] < PARAM_LIMIT0))
		{
			MessageBox("param1 error!");
			return;
		}
		pb.iParam2[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
		if((pb.iParam2[iType] > PARAM_LIMIT255) || (pb.iParam2[iType] < PARAM_LIMIT0))
		{
			MessageBox("param2 error!");
			return;
		}
	}
	else if(iType == CAMERA_PARA_BLC)
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		if((pb.iParam1[iType] > PARAM_LIMIT1) || (pb.iParam1[iType] < PARAM_LIMIT0))
		{
			MessageBox("param1 error!");
			return;
		}
		if(pb.iParam1[iType] == 1)
		{
			pb.iParam2[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
			if((pb.iParam2[iType] < PARAM_LIMIT1) || (pb.iParam2[iType] > PARAM_LIMIT3))
			{
				MessageBox("param2 error!");
				return;
			}
		}
	}
	else if((iType == CAMERA_PARA_EXPOSURE_TIME) && (iAUTOEnable == HAND_DO))
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
	}
	else if((iType == CAMERA_PARA_EXPOSURE_TIME) && (iAUTOEnable == AUTO_DO))
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		pb.iParam2[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
		pb.iParam3[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM3);
	}
	else if((iType == CAMERA_PARA_SHUTTER_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		if((pb.iParam1[iType] < PARAM_LIMIT0) || ((pb.iParam1[iType] > PARAM_LIMIT47) && (pb.iParam1[iType] < PARAM_LIMIT100)) || (pb.iParam1[iType] > PARAM_LIMIT115))
		{
			MessageBox("param error!");
			return;
		}
	}
	else if((iType == CAMERA_PARA_SHUTTER_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		pb.iParam2[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
		pb.iParam3[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM3);
	}
	else if((iType == CAMERA_PARA_GAIN_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		if((pb.iParam1[iType] < PARAM_LIMIT0) || (pb.iParam1[iType] > PARAM_LIMIT255))
		{
			MessageBox("param error!");
			return;
		}
	}
	else if((iType == CAMERA_PARA_GAIN_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{	
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		pb.iParam2[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
		pb.iParam3[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM3);
	}
	else if((iType == CAMERA_PARA_GAMMA_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		pb.iParam3[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM3);
		if((pb.iParam3[iType] < PARAM_LIMIT0) || (pb.iParam3[iType] > PARAM_LIMIT255))
		{
			MessageBox("param3 error!");
			return;
		}
	}
	else if((iType == CAMERA_PARA_GAMMA_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		pb.iParam2[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
		if((pb.iParam2[iType] > PARAM_LIMIT0) || (pb.iParam2[iType] < PARAM_LIMIT0))
		{
			MessageBox("param2 error!");
			return;
		}
	}
	else if((iType == CAMERA_PARA_SHARPNESS_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		if((pb.iParam1[iType] < PARAM_LIMIT0) || (pb.iParam1[iType] > PARAM_LIMIT255))
		{
			MessageBox("param error!");
			return;
		}
	}
	else if((iType == CAMERA_PARA_SHARPNESS_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		pb.iParam2[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
		if((pb.iParam2[iType] > PARAM_LIMIT1) || (pb.iParam2[iType] < PARAM_LIMIT0))
		{
			MessageBox("param error!");
			return;
		}
	}
	else if((iType == CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
	}
	else if((iType == CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
	}
	else if((iType == CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT) && (iAUTOEnable == EXPERT_DO))
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		if((pb.iParam1[iType] < PARAM_LIMIT0) || (pb.iParam1[iType] > PARAM_LIMIT5))
		{
			MessageBox("param1 error!");
			return;
		}
		pb.iParam2[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
	}
	else if(iType == CAMERA_PARA_EXPOSURE_REGION)
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		pb.iParam2[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
		pb.iParam3[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM3);
		pb.iParam4[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM4);
	}
	else if(iType == CAMERA_PARA_BLC_REGION)
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		pb.iParam2[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
		pb.iParam3[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM3);
		pb.iParam4[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM4);
	}
	else if(iType == CAMERA_PARA_AF_REGION_SET)
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		pb.iParam2[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
		pb.iParam3[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM3);
		pb.iParam4[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM4);
	}
	else if(iType == CAMERA_PARA_TARGET_BRIGHTNESS_ADJUSTMENT)
	{

		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		pb.iParam2[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
		pb.iParam3[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM3);
	}
	else if((iType == CAMERA_PARA_WHITE_BALANCE_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		if((pb.iParam1[iType] < PARAM_LIMIT0) || (pb.iParam1[iType] > PARAM_LIMIT255))
		{
			MessageBox("param1 error!");
			return;
		}
		pb.iParam2[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
		if((pb.iParam2[iType] < PARAM_LIMIT0) || (pb.iParam2[iType] > PARAM_LIMIT255))
		{
			MessageBox("param2 error!");
			return;
		}
		pb.iParam3[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM3);
		if((pb.iParam3[iType] < PARAM_LIMIT0) || (pb.iParam3[iType] > PARAM_LIMIT255))
		{
			MessageBox("param3 error!");
			return;
		}
		pb.iParam4[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM4);
		if((pb.iParam4[iType] < PARAM_LIMIT0) || (pb.iParam4[iType] > PARAM_LIMIT1))
		{
			MessageBox("param4 error!");
			return;
		}
	}

	else if((iType == CAMERA_PARA_WHITE_BALANCE_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		if((pb.iParam1[iType] < PARAM_LIMIT100) || (pb.iParam1[iType] > PARAM_LIMIT200))
		{
			MessageBox("param1 error!");
			return;
		}
		pb.iParam1[iType] = pb.iParam1[iType] / 5 * 5;
		pb.iParam2[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
		if((pb.iParam2[iType] < PARAM_LIMIT100) || (pb.iParam2[iType] > PARAM_LIMIT200))
		{
			MessageBox("param2 error!");
			return;
		}
		pb.iParam2[iType] = pb.iParam2[iType] / 5 * 5;
		pb.iParam3[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM3);
		if((pb.iParam3[iType] < PARAM_LIMIT100) || (pb.iParam3[iType] > PARAM_LIMIT200))
		{
			MessageBox("param3 error!");
			return;
		}
		pb.iParam3[iType] = pb.iParam3[iType] / 5 * 5;
		pb.iParam4[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM4);
		if((pb.iParam4[iType] < PARAM_LIMIT0) || (pb.iParam4[iType] > PARAM_LIMIT17))
		{
			MessageBox("param4 error!");
			return;
		}
	}
	else if(iType == CAMERA_PARA_JPEG_IMAGE_QUALITY)
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		if((pb.iParam1[iType] < PARAM_LIMIT0) || (pb.iParam1[iType] > PARAM_LIMIT100))
		{
			MessageBox("param1 error!");
			return;
		}
		pb.iParam2[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
		if((pb.iParam2[iType] < PARAM_LIMIT64) || (pb.iParam2[iType] > PARAM_LIMIT8192))
		{
			MessageBox("param2 error!");
			return;
		}
	}
	else if(iType == CAMERA_PARA_LUT_ENABLE)
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		if((pb.iParam1[iType] > PARAM_LIMIT1) || (pb.iParam1[iType] < PARAM_LIMIT0))
		{
			MessageBox("param error!");
			return;
		}
	}
	else if(iType == CAMERA_PARA_AUTOMATIC_BRIGHTNESS_ADJUST)
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		if((pb.iParam1[iType] > PARAM_LIMIT1) || (pb.iParam1[iType] < PARAM_LIMIT0))
		{
			MessageBox("param error!");
			return;
		}
	}
	else if(iType == CAMERA_PARA_HSBLC)
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		if((pb.iParam1[iType] > PARAM_LIMIT1) || (pb.iParam1[iType] < PARAM_LIMIT0))
		{
			MessageBox("param1 error!");
			return;
		}
		pb.iParam2[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
		if((pb.iParam2[iType] > PARAM_LIMIT255) || (pb.iParam2[iType] < PARAM_LIMIT0))
		{
			MessageBox("param2 error!");
			return;
		}
	}
	else if(iType == CAMERA_PARA_AUTO_EXPOSURE_MODE)
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		if((pb.iParam1[iType] < PARAM_LIMIT0) || (pb.iParam1[iType] > PARAM_LIMIT6))
		{
			MessageBox("param error!");
			return;
		}
	}
	else if(iType == CAMERA_PARA_SCENE_MODE)
	{
		pb.iParam1[iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
		if((pb.iParam1[iType] < PARAM_LIMIT0) || (pb.iParam1[iType] > PARAM_LIMIT1))
		{
			MessageBox("param error!");
			return;
		}
	}
	int iRet = NetClient_SetHDTimeRangeParam(m_iLogonID, m_iChannelNo, iTimeRangeIndex, &pb, sizeof(pb));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetHDTimeRangeParam (%d,%d)",m_iLogonID, m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetHDTimeRangeParam (%d,%d), error(%d)",m_iLogonID,m_iChannelNo, GetLastError());
	}
}

void Cls_ItsPictureCommon1::OnBnClickedButtonAgcblock()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	
	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX);
	int iAgcBlock = 0;
	for (int i=0; i<5; i++)
	{
		iAgcBlock += (m_chkBit[i].GetCheck() == BST_CHECKED)?(1<<i):0;
	}
	int iRet = NetClient_SetITSTimeRange(m_iLogonID, iTimeRangeIndex, ITS_CMD_SET_TIMERANGE_AGCBLOCK, &iAgcBlock, sizeof(iAgcBlock));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSTimeRange[ITS_CMD_SET_TIMERANGE_AGCBLOCK] (%d)",m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSTimeRange[ITS_CMD_SET_TIMERANGE_AGCBLOCK](%d), error(%d)",m_iLogonID,GetLastError());
	}
}

BOOL Cls_ItsPictureCommon1::UI_UpdateBlock()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iBlockID = m_cboBlock.GetCurSel();
	int iX = -1;
	int iY = -1;
	int iRet = NetClient_GetITSBlock(m_iLogonID, iBlockID, &iX, &iY);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_BLOCK_X, iX,FALSE);
		SetDlgItemInt(IDC_EDIT_BLOCK_Y, iY,FALSE);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSBlock (%d,%d,%d,%d)",m_iLogonID,iBlockID,iX,iY);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSBlock (%d,%d,%d,%d), error(%d)",m_iLogonID,iBlockID,iX,iY, GetLastError());
	}
	return TRUE;	
}

void Cls_ItsPictureCommon1::OnCbnSelchangeComboBlock()
{
	UI_UpdateBlock();
}

void Cls_ItsPictureCommon1::OnBnClickedButtonBlock()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	
	int iBlockID = m_cboBlock.GetCurSel();
	int iX = GetDlgItemInt(IDC_EDIT_BLOCK_X,NULL,FALSE);
	int iY = GetDlgItemInt(IDC_EDIT_BLOCK_Y,NULL,FALSE);
	int iRet = NetClient_SetITSBlock(m_iLogonID, iBlockID, iX, iY);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSBlock (%d,%d,%d,%d)",m_iLogonID,iBlockID,iX,iY);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSBlock (%d,%d,%d,%d), error(%d)",m_iLogonID,iBlockID,iX,iY, GetLastError());
	}
}

void Cls_ItsPictureCommon1::OnBnClickedButtonDevicetype()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	COMFORMAT tSet = {0};
	char cSelect[32];
	tSet.iSize = sizeof(COMFORMAT);
	tSet.iComNo = 1;
	tSet.iComType = 0;
	tSet.iWorkMode = 2;

	strcpy(tSet.cComFormat,"9600,n,8,1");
	int iDeviceType = m_cboDeviceType.GetCurSel();
	_itoa(iDeviceType, cSelect, 10);
	strcpy(tSet.cDeviceName, cSelect);
	int iRet = NetClient_SetComFormat_V2(m_iLogonID, &tSet);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetComFormat_V2 (%d,%d)",m_iLogonID,iDeviceType);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetComFormat_V2 (%d,%d), error(%d)",m_iLogonID,iDeviceType, GetLastError());
	}
}

BOOL Cls_ItsPictureCommon1::UI_UpdateGPEGQuality()
{
	if (m_iLogonID < 0)
		return FALSE;
	ITS_TTimeRangeParam tGetCameraParam = {0};
	tGetCameraParam.iType = m_cboCameraParam.GetCurSel() + 15;
	int iRet = NetClient_GetHDTimeRangeParam(m_iLogonID, m_iChannelNo, m_cboTimeRangeIndex.GetCurSel(), &tGetCameraParam, sizeof(tGetCameraParam));
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_VALUE,tGetCameraParam.iParam1[15]);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetHDTimeRangeParam[] (%d, %d)",m_iLogonID, m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetHDTimeRangeParam[] (%d, %d),error(%d)",m_iLogonID, m_iChannelNo, GetLastError());
	}
	return TRUE;
}

void Cls_ItsPictureCommon1::OnCbnSelchangeComboCameraparam()
{
	UI_UpdateGPEGQuality();
}

void Cls_ItsPictureCommon1::OnBnClickedButtonCamera()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	ITS_TTimeRangeParam tCameraParam = {0};
	tCameraParam.iType = m_cboCameraParam.GetCurSel() + 15;
	tCameraParam.iParam1[15] = GetDlgItemInt(IDC_EDIT_VALUE);
	int iRet = NetClient_SetHDTimeRangeParam(m_iLogonID, m_iChannelNo, m_cboTimeRangeIndex.GetCurSel(), &tCameraParam, sizeof(tCameraParam));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetHDTimeRangeParam[] (%d, %d)",m_iLogonID, 4);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetHDTimeRangeParam[] (%d, %d),error(%d)",m_iLogonID, 4, GetLastError());
	}
}

void Cls_ItsPictureCommon1::UI_UpdateDevicetype()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	COMFORMAT tSet = {0};
	tSet.iSize = sizeof(COMFORMAT);
	tSet.iComNo = 1;
	int iSelect = 0;
	int iRet = NetClient_GetComFormat_V2(m_iLogonID, &tSet);
	if (0 == iRet)
	{
		iSelect = atoi(tSet.cDeviceName);
		m_cboDeviceType.SetCurSel(iSelect);
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSDeviceType (%d,%d)",m_iLogonID,iSelect);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSDeviceType (%d,%d), error(%d)",m_iLogonID,iSelect, GetLastError());
	}
}


void Cls_ItsPictureCommon1::OnCbnSelchangeComboAutoenable()
{
	int iType = m_cboType.GetCurSel();;
	int iAUTOEnable = m_cboAutoEnable.GetCurSel();
	if((iType == CAMERA_PARA_IRIS_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(FALSE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_IRIS_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(TRUE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_EXPOSURE_TIME) && (iAUTOEnable == HAND_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(FALSE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_EXPOSURE_TIME) && (iAUTOEnable == AUTO_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(TRUE);
		m_edtParam[2].EnableWindow(TRUE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_SHUTTER_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(FALSE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_SHUTTER_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(TRUE);
		m_edtParam[2].EnableWindow(TRUE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_GAIN_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(FALSE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_GAIN_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(TRUE);
		m_edtParam[2].EnableWindow(TRUE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_GAMMA_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(FALSE);
		m_edtParam[2].EnableWindow(TRUE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_GAMMA_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(TRUE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_SHARPNESS_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(FALSE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_SHARPNESS_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(TRUE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(FALSE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(FALSE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT) && (iAUTOEnable == EXPERT_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(TRUE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}

	else if((iType == CAMERA_PARA_NOISE_REDUCTION_ADJUSTMENT) && (iAUTOEnable == REDUCTION_3D))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(TRUE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}

	else if((iType == CAMERA_PARA_TARGET_BRIGHTNESS_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(TRUE);
		m_edtParam[2].EnableWindow(TRUE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_TARGET_BRIGHTNESS_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(TRUE);
		m_edtParam[2].EnableWindow(TRUE);
		m_edtParam[3].EnableWindow(FALSE);
	}
	else if((iType == CAMERA_PARA_WHITE_BALANCE_ADJUSTMENT) && (iAUTOEnable == HAND_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(TRUE);
		m_edtParam[2].EnableWindow(TRUE);
		m_edtParam[3].EnableWindow(TRUE);
	}
	else if((iType == CAMERA_PARA_WHITE_BALANCE_ADJUSTMENT) && (iAUTOEnable == AUTO_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(TRUE);
		m_edtParam[1].EnableWindow(TRUE);
		m_edtParam[2].EnableWindow(TRUE);
		m_edtParam[3].EnableWindow(TRUE);
	}
	else if((iType == CAMERA_PARA_WHITE_BALANCE_ADJUSTMENT) && (iAUTOEnable == EXPERT_DO))
	{
		m_cboAutoEnable.EnableWindow(TRUE);
		m_edtParam[0].EnableWindow(FALSE);
		m_edtParam[1].EnableWindow(FALSE);
		m_edtParam[2].EnableWindow(FALSE);
		m_edtParam[3].EnableWindow(FALSE);
	}
}

void Cls_ItsPictureCommon1::OnEnChangeEditTimerangeParam1()
{
	int iCheckParam = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
	int iCheckSelect = m_cboType.GetCurSel();
	if((2 == iCheckSelect) && (0 == iCheckParam))
	{
		m_edtParam[1].EnableWindow(FALSE);
	}
	else if((2 == iCheckSelect) && (1 == iCheckParam))
	{
		m_edtParam[1].EnableWindow(TRUE);
	}
}

void Cls_ItsPictureCommon1::OnBnClickedCheckTimerangeindex()
{
	UI_UpdatePageEnable();
}
