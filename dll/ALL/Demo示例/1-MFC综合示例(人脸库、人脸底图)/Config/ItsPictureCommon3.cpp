// ECOPImgDisposalPage.cpp : implementation file
//

#include "stdafx.h"
#include "ItsPictureCommon3.h"


// CLS_ECOPImgDisposalPage dialog

IMPLEMENT_DYNAMIC(CLS_ItsPictureCommon3, CDialog)

CLS_ItsPictureCommon3::CLS_ItsPictureCommon3(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ItsPictureCommon3::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
}

CLS_ItsPictureCommon3::~CLS_ItsPictureCommon3()
{
}

void CLS_ItsPictureCommon3::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ROADWAYID, m_cboRoadwayID);
	DDX_Control(pDX, IDC_CHECK_IMGDISPOSAL_ENABLE, m_chkEnable);
	DDX_Control(pDX, IDC_EDIT_QUALITY, m_edtQuality);
	DDX_Control(pDX, IDC_EDIT_SATURATION, m_edtSaturation);
	DDX_Control(pDX, IDC_EDIT_BRIGHTEN, m_edtBrighten);
	DDX_Control(pDX, IDC_EDIT_CONTRAST, m_edtContrast);
	DDX_Control(pDX, IDC_EDIT_GAMMA, m_edtGamma);
	DDX_Control(pDX, IDC_EDIT_ACUTANCE, m_edtAcutance);
	DDX_Control(pDX, IDC_EDIT_IMGENHANCE, m_edtImgEnhance);
	DDX_Control(pDX, IDC_BUTTON_IMGDISPOSAL, m_btnImgDisposal);
	DDX_Control(pDX, IDC_CHECK_TIMERANGEINDEX3, m_chkTimeRangeIndex3);
	DDX_Control(pDX, IDC_COMBO_TIMERANGEINDEX3, m_cboTimeRangeIndex3);
	DDX_Control(pDX, IDC_BTN_BACKUPLIGHT, m_btnSetExtraLight);
}


BEGIN_MESSAGE_MAP(CLS_ItsPictureCommon3, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_ROADWAYID, &CLS_ItsPictureCommon3::OnCbnSelchangeComboRoadwayid)
	ON_BN_CLICKED(IDC_BUTTON_IMGDISPOSAL, &CLS_ItsPictureCommon3::OnBnClickedButtonImgdisposal)
	ON_BN_CLICKED(IDC_BTN_BACKUPLIGHT, &CLS_ItsPictureCommon3::OnBnClickedBtnBackuplight)
	ON_BN_CLICKED(IDC_BUTTON_TIMERANGE3, &CLS_ItsPictureCommon3::OnBnClickedButtonTimerange3)
	ON_CBN_SELCHANGE(IDC_COMBO_TIMERANGEINDEX3, &CLS_ItsPictureCommon3::OnCbnSelchangeComboTimerangeindex3)
	ON_BN_CLICKED(IDC_CHECK_TIMERANGEINDEX3, &CLS_ItsPictureCommon3::OnBnClickedCheckTimerangeindex3)
END_MESSAGE_MAP()


// CLS_ECOPImgDisposalPage message handlers
BOOL CLS_ItsPictureCommon3::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	for (int i=0; i<4; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboRoadwayID.AddString(strNo);
	}
	m_cboRoadwayID.SetCurSel(0);

	m_edtQuality.SetLimitText(3);
	m_edtSaturation.SetLimitText(3);
	m_edtBrighten.SetLimitText(3);
	m_edtContrast.SetLimitText(3);
	m_edtGamma.SetLimitText(2);
	m_edtAcutance.SetLimitText(3);
	m_edtImgEnhance.SetLimitText(3);

	UI_UpdateDialog();

	return TRUE;
}

void CLS_ItsPictureCommon3::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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

	UI_UpdateImgDisposal();
	UI_UpdateTimeAgcFlash();
	UI_UpdateBackuplight();
	UI_UpdatePageEnable();
}

void CLS_ItsPictureCommon3::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ItsPictureCommon3::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_ROADWAYID,IDS_CONFIG_ECOP_ROADWAYID);
	SetDlgItemTextEx(IDC_STATIC_IMGDISPOSAL,IDS_ITS_IMAGEDISPOSAL);
	SetDlgItemTextEx(IDC_CHECK_IMGDISPOSAL_ENABLE,IDS_CONFIG_ECOP_IMGDISPOSAL_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_QUALITY,IDS_CONFIG_ECOP_QUALITY);
	SetDlgItemTextEx(IDC_STATIC_SATURATION,IDS_CONFIG_ECOP_SATURATION);
	SetDlgItemTextEx(IDC_STATIC_BRIGHTEN,IDS_CONFIG_ECOP_BRIGHTEN);
	SetDlgItemTextEx(IDC_STATIC_CONTRAST,IDS_CONFIG_ECOP_CONTRAST);
	SetDlgItemTextEx(IDC_STATIC_GAMMA,IDS_CONFIG_ECOP_GAMMA);
	SetDlgItemTextEx(IDC_STATIC_ACUTANCE,IDS_CONFIG_ECOP_ACUTANCE);
	SetDlgItemTextEx(IDC_STATIC_IMGENHANCE,IDS_CONFIG_ECOP_IMGENHANCE);
	SetDlgItemTextEx(IDC_BUTTON_IMGDISPOSAL,IDS_SET);

	SetDlgItemTextEx(IDC_STA_PLATE_FILL,IDS_ITS_PLATE_FILL);
	SetDlgItemTextEx(IDC_CHK_FILL_ENABLE,IDS_START);
	SetDlgItemTextEx(IDC_STA_FAIRING,IDS_ITS_FAIRING);
	SetDlgItemTextEx(IDC_STA_BACKLIGHT,IDS_ITS_BACKLIGHT);
	SetDlgItemTextEx(IDC_STA_SENSITY,IDS_ITS_SENSITY);
	SetDlgItemTextEx(IDC_BTN_BACKUPLIGHT,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_TIMERANGEINDEX3,IDS_CONFIG_ITS_TIMERANGE_INDEX);
	SetDlgItemTextEx(IDC_STATIC_TIMERANGE3,IDS_CONFIG_ITS_TIMERANGE_RANGE);
	SetDlgItemTextEx(IDC_CHECK_TIMERANGEINDEX3,IDS_CONFIG_ITS_TIMERANGE_ENABLE);
	SetDlgItemTextEx(IDC_BUTTON_TIMERANGE3,IDS_SET);
	for (int i=0; i<8; i++)
	{
		CString strNo;
		strNo.Format("%d" ,i);
		InsertString(m_cboTimeRangeIndex3,i,strNo);
	}

	m_cboTimeRangeIndex3.SetCurSel(0);

}

void CLS_ItsPictureCommon3::UI_UpdatePageEnable()
{
	if(m_chkTimeRangeIndex3.GetCheck())
	{
		m_cboRoadwayID.EnableWindow(TRUE);
		m_btnImgDisposal.EnableWindow(TRUE);
		m_btnSetExtraLight.EnableWindow(TRUE);
	}
	else
	{
		m_cboRoadwayID.EnableWindow(FALSE);
		m_btnImgDisposal.EnableWindow(FALSE);
		m_btnSetExtraLight.EnableWindow(FALSE);
	}
}

void CLS_ItsPictureCommon3::UI_UpdateImgDisposal()
{
	if (m_iLogonID < 0)
		return;

	TImgDisposal tDisposal = {0};
	tDisposal.iChannelID = m_cboRoadwayID.GetCurSel();
	int iRet = NetClient_GetImgDisposal(m_iLogonID,&tDisposal,sizeof(tDisposal));
	if (0 == iRet)
	{
		//m_cboRoadwayID.SetCurSel(tDisposal.iChannelID);
		m_chkEnable.SetCheck(tDisposal.iStartUp?BST_CHECKED:BST_UNCHECKED);
		SetDlgItemInt(IDC_EDIT_QUALITY, tDisposal.iQuality);
		SetDlgItemInt(IDC_EDIT_SATURATION, tDisposal.iSaturation);
		SetDlgItemInt(IDC_EDIT_BRIGHTEN, tDisposal.iBrighten);
		SetDlgItemInt(IDC_EDIT_CONTRAST, tDisposal.iContrast);
		SetDlgItemInt(IDC_EDIT_GAMMA, tDisposal.iGamma);
		SetDlgItemInt(IDC_EDIT_ACUTANCE, tDisposal.iAcutance);
		SetDlgItemInt(IDC_EDIT_IMGENHANCE, tDisposal.iImgEnhanceLevel);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetImgDisposal (%d,%d)",m_iLogonID,sizeof(tDisposal));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetImgDisposal (%d,%d)",m_iLogonID,sizeof(tDisposal));
	}
	return;
}
void CLS_ItsPictureCommon3::OnCbnSelchangeComboRoadwayid()
{
	UI_UpdateImgDisposal();
}

void CLS_ItsPictureCommon3::OnBnClickedButtonImgdisposal()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TImgDisposal tDisposal = {0};
	tDisposal.iChannelID = m_cboRoadwayID.GetCurSel();
	tDisposal.iStartUp = (m_chkEnable.GetCheck() == BST_CHECKED)?1:0;
	tDisposal.iQuality = GetDlgItemInt(IDC_EDIT_QUALITY);
	tDisposal.iSaturation = GetDlgItemInt(IDC_EDIT_SATURATION);
	tDisposal.iBrighten = GetDlgItemInt(IDC_EDIT_BRIGHTEN);
	tDisposal.iContrast = GetDlgItemInt(IDC_EDIT_CONTRAST);
	tDisposal.iGamma = GetDlgItemInt(IDC_EDIT_GAMMA);
	tDisposal.iAcutance = GetDlgItemInt(IDC_EDIT_ACUTANCE);
	tDisposal.iImgEnhanceLevel = GetDlgItemInt(IDC_EDIT_IMGENHANCE);
	int iRet = NetClient_SetImgDisposal(m_iLogonID,&tDisposal,sizeof(tDisposal));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetImgDisposal (%d)",m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetImgDisposal (%d), error(%d)",m_iLogonID, GetLastError());
	}
} 

void CLS_ItsPictureCommon3::OnBnClickedButtonTimerange3()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX3);
	ITS_TTimeRange pa = {0};
	pa.iEnable = (m_chkTimeRangeIndex3.GetCheck() == BST_CHECKED)?1:0;
	char cTimeRange[20] = {0};
	GetDlgItemText(IDC_EDIT_TIMERANGE3, cTimeRange, 20);
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

void CLS_ItsPictureCommon3::UI_UpdateTimeAgcFlash()
{
	if (m_iLogonID < 0)
		return;

	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX3);
	ITS_TTimeRange pa = {0};
	//int iChannelNo = CHANNEL_PICTURE;
	int iRet = NetClient_GetITSTimeRangeEnable(m_iLogonID, m_iChannelNo, iTimeRangeIndex, &pa, sizeof(pa));
	if (0 == iRet)
	{
		m_chkTimeRangeIndex3.SetCheck(pa.iEnable?BST_CHECKED:BST_UNCHECKED);
		int iBeginHour = (pa.iTimeRange)>>24&0xFF;
		int iBeginMinute = (pa.iTimeRange)>>16&0xFF;
		int iEndHour = (pa.iTimeRange)>>8&0xFF;
		int iEndMinute = (pa.iTimeRange)&0xFF;
		CString strTimeRange;
		strTimeRange.Format("%02d:%02d-%02d:%02d", iBeginHour, iBeginMinute, iEndHour, iEndMinute);
		SetDlgItemText(IDC_EDIT_TIMERANGE3, strTimeRange);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSTimeRangeEnable (%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSTimeRangeEnable (%d), error(%d)", m_iLogonID, GetLastError());
	}
}

void CLS_ItsPictureCommon3::OnBnClickedBtnBackuplight()
{
	ITS_LightSupply strctLightSupply;
	memset(&strctLightSupply, 0, sizeof(ITS_LightSupply));

	strctLightSupply.iBufSize = sizeof(ITS_LightSupply);
	strctLightSupply.iIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX3);

	strctLightSupply.iEnable = ((CButton*)GetDlgItem(IDC_CHK_FILL_ENABLE))->GetCheck();
	strctLightSupply.iFrontLight = GetDlgItemInt(IDC_EDT_FAIRING);
	strctLightSupply.iBackLight = GetDlgItemInt(IDC_EDT_BACKLIGHT);
	strctLightSupply.iSensitivity = GetDlgItemInt(IDC_EDT_SENSITY);
	
	int	iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_LIGHTSUPPLY_CMD_SET, m_iChannelNo, &strctLightSupply, sizeof(ITS_LightSupply));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_LIGHTSUPPLY_CMD_SET] (%d,%d)", m_iLogonID, m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_LIGHTSUPPLY_CMD_SET](%d,%d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}	
}

void CLS_ItsPictureCommon3::UI_UpdateBackuplight()
{
	ITS_LightSupply strctLightSupply;
	memset(&strctLightSupply, 0, sizeof(ITS_LightSupply));

	strctLightSupply.iBufSize = sizeof(ITS_LightSupply);
	strctLightSupply.iIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX3);

	int	iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_LIGHTSUPPLY_CMD_GET, m_iChannelNo, &strctLightSupply, sizeof(ITS_LightSupply));
	if (0 == iRet)
	{
		((CButton*)GetDlgItem(IDC_CHK_FILL_ENABLE))->SetCheck(strctLightSupply.iEnable);
		SetDlgItemInt(IDC_EDT_FAIRING, strctLightSupply.iFrontLight);
		SetDlgItemInt(IDC_EDT_BACKLIGHT, strctLightSupply.iBackLight);
		SetDlgItemInt(IDC_EDT_SENSITY, strctLightSupply.iSensitivity);
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_LIGHTSUPPLY_CMD_GET] (%d,%d)", m_iLogonID, m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo (%d,%d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError);
	}	
}
void CLS_ItsPictureCommon3::OnCbnSelchangeComboTimerangeindex3()
{
	UI_UpdateImgDisposal();
	UI_UpdateTimeAgcFlash();
	UI_UpdateBackuplight();
	UI_UpdatePageEnable();
}

void CLS_ItsPictureCommon3::OnBnClickedCheckTimerangeindex3()
{
	UI_UpdatePageEnable();
}
