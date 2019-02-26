// DomeHDParam1.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "DomeHDParam1.h"


// CLS_DomeHDParam1 dialog

#define MAX_HD_CURVE_NUM		6
#define HD_MODE_INDEX0          0
#define HD_MODE_IMMEDIATELY     255

//快门速度
//27--1、25--1/3、22--1/6、19--1/12、0--1/25、16--1/30、1--1/50、2--1/60、4--1/100、10--1/250、11--1/500、12--1/1000 15--1/10000
const int g_iShutSpdManual[] = {27,25,22,19,0,16,1,2,4,10,11,12,15};
CString g_szShutSpdManualS6[] = {"1","1/3","1/6","1/12","1/25","1/30","1/50","1/60",
"1/100","1/250","1/500","1/1000","1/10000"};

//const int g_iShutSpdAuto[] = {0,16,1,2,4,10,11,12,15};
//CString g_szShutSpdAutoS6[] = {"1/25","1/30","1/50","1/60",
//"1/100","1/250","1/500","1/1000","1/10000"};

const int g_iShutSpd3516[] = {27,  26,    25,    24,   23,    22,    21,    20,
				19,     18,     0,     16,    1,     2,      3,      4,       5,       6, 
				7,       8,        9,      10,     11,     12,      13,      14,       15,         17};
CString g_szShutSpd3516[] = {"1", "1/2", "1/3", "1/4", "1/5", "1/6", "1/8", "1/10", "1/12",
		"1/15", "1/25","1/30","1/50","1/60", "1/80", "1/100", "1/120", "1/125", "1/150", "1/180", 
		"1/200", "1/250","1/500","1/1000","1/2000", "1/4000", "1/10000", "1/100000"};

IMPLEMENT_DYNAMIC(CLS_DomeHDParam1, CDialog)

CLS_DomeHDParam1::CLS_DomeHDParam1(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DomeHDParam1::IDD, pParent)
	, m_iApertureTypePiris(0)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNO = -1;
}

CLS_DomeHDParam1::~CLS_DomeHDParam1()
{
}

void CLS_DomeHDParam1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CURRENT_TEMP, m_cboTempleID);
	DDX_Control(pDX, IDC_EDIT_TEMPNAME, m_edtTempleName);
	DDX_Control(pDX, IDC_SLIDER_Sharpness, m_slipSharpness);
	DDX_Control(pDX, IDC_SLIDER_COLOR_INCREASE, m_slidColorIncrease);
	DDX_Control(pDX, IDC_SLIDER_COLOR_PHASE, m_slidColorPhase);
	DDX_Control(pDX, IDC_COMBO_GAMMASET, m_cboGammaSet);
	DDX_Control(pDX, IDC_SLIDER_GAMMA_MODIFY, m_slidGammaModify);
	DDX_Radio(pDX, IDC_RADIO_APERTURE_TYPE_DC, m_iApertureTypePiris);
	DDX_Control(pDX, IDC_SLD_REGULATE, m_sldRegulateAE);
	DDX_Control(pDX, IDC_COMBO_EXPOMODE, m_cboExpoMode);
	DDX_Control(pDX, IDC_COMBO_SHUTTER, m_cboShutter);
	DDX_Control(pDX, IDC_COMBO_APERTURE, m_cboAperture);
	DDX_Control(pDX, IDC_COMBO_Auto_Aperture, m_cboAutoAperture);
	DDX_Control(pDX, IDC_COMBO_GAIN_AUTO, m_cboAutoGain);
	DDX_Control(pDX, IDC_SLIDER_GAIN_MAX, m_slidMaxGainLimit);
	DDX_Control(pDX, IDC_SLIDER_GAIN, m_slidGain);
	DDX_Control(pDX, IDC_SLIDER_TARGET_BRIGHT, m_slidBright);
	DDX_Control(pDX, IDC_SLIDER_AUTO_SLOW_EXPO, m_sliderSensUp);
	DDX_Control(pDX, IDC_COMBO_EXPO_OFFSET, m_cbo_Expo_OffSet);
	DDX_Control(pDX, IDC_COMBO_SENSITIVE, m_cboSensitive);
}


BEGIN_MESSAGE_MAP(CLS_DomeHDParam1, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_CURRENT_TEMP, &CLS_DomeHDParam1::OnCbnSelchangeComboCurrentTemp)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Sharpness, &CLS_DomeHDParam1::OnNMCustomdrawSliderSharpness)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_COLOR_INCREASE, &CLS_DomeHDParam1::OnNMCustomdrawSliderColorIncrease)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_COLOR_PHASE, &CLS_DomeHDParam1::OnNMCustomdrawSliderColorPhase)
	ON_CBN_SELCHANGE(IDC_COMBO_GAMMASET, &CLS_DomeHDParam1::OnCbnSelchangeComboGammaset)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_GAMMA_MODIFY, &CLS_DomeHDParam1::OnNMCustomdrawSliderGammaModify)
	ON_BN_CLICKED(IDC_RADIO_APERTURE_TYPE_DC, &CLS_DomeHDParam1::OnBnClickedRadioApertureType)
	ON_BN_CLICKED(IDC_RADIO_APERTURE_TYPE_PIRIS, &CLS_DomeHDParam1::OnBnClickedRadioApertureType)
	ON_BN_CLICKED(IDC_BUTTON_SET_TEMPLATE_NAME, &CLS_DomeHDParam1::OnBnClickedButtonSetTemplateName)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_REGULATE, &CLS_DomeHDParam1::OnNMCustomdrawSldRegulate)
	ON_CBN_SELCHANGE(IDC_COMBO_EXPOMODE, &CLS_DomeHDParam1::OnCbnSelchangeComboExpomode)
	ON_CBN_SELCHANGE(IDC_COMBO_SHUTTER, &CLS_DomeHDParam1::OnCbnSelchangeComboShutter)
	ON_CBN_SELCHANGE(IDC_COMBO_APERTURE, &CLS_DomeHDParam1::OnCbnSelchangeComboAperture)
	ON_CBN_SELCHANGE(IDC_COMBO_Auto_Aperture, &CLS_DomeHDParam1::OnCbnSelchangeComboAutoAperture)
	ON_CBN_SELCHANGE(IDC_COMBO_GAIN_AUTO, &CLS_DomeHDParam1::OnCbnSelchangeComboGainAuto)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_GAIN_MAX, &CLS_DomeHDParam1::OnNMCustomdrawSliderGainMax)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_GAIN, &CLS_DomeHDParam1::OnNMCustomdrawSliderGain)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_TARGET_BRIGHT, &CLS_DomeHDParam1::OnNMCustomdrawSliderTargetBright)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_AUTO_SLOW_EXPO, &CLS_DomeHDParam1::OnNMCustomdrawSliderAutoSlowExpo)
	ON_CBN_SELCHANGE(IDC_COMBO_EXPO_OFFSET, &CLS_DomeHDParam1::OnCbnSelchangeComboExpoOffset)
	ON_CBN_SELCHANGE(IDC_COMBO_SENSITIVE, &CLS_DomeHDParam1::OnCbnSelchangeComboSensitive)
	ON_BN_CLICKED(IDC_BUTTON_Sharpness_SET, &CLS_DomeHDParam1::OnBnClickedButtonSharpnessSet)
	ON_BN_CLICKED(IDC_BUTTON_ColorIncrease_SET, &CLS_DomeHDParam1::OnBnClickedButtonColorincreaseSet)
	ON_BN_CLICKED(IDC_BUTTON_ColorPhase_SET, &CLS_DomeHDParam1::OnBnClickedButtonColorphaseSet)
	ON_BN_CLICKED(IDC_BUTTON_GammaModify_SET, &CLS_DomeHDParam1::OnBnClickedButtonGammamodifySet)
	ON_BN_CLICKED(IDC_BUTTON_AE_SET, &CLS_DomeHDParam1::OnBnClickedButtonAeSet)
	ON_BN_CLICKED(IDC_BUTTON_MaxGainLimit_SET, &CLS_DomeHDParam1::OnBnClickedButtonMaxgainlimitSet)
	ON_BN_CLICKED(IDC_BUTTON_Gain_SET, &CLS_DomeHDParam1::OnBnClickedButtonGainSet)
	ON_BN_CLICKED(IDC_BUTTON_Bright_SET, &CLS_DomeHDParam1::OnBnClickedButtonBrightSet)
	ON_BN_CLICKED(IDC_BUTTON_SensUp_SET, &CLS_DomeHDParam1::OnBnClickedButtonSensupSet)
END_MESSAGE_MAP()


// CLS_DomeHDParam1 message handlers

BOOL CLS_DomeHDParam1::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	//UI_UpdateDialogText();
	//UpdateDomeHDPara();
	//UpdateApertureType();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_DomeHDParam1::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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

	if (_iStreamNo < 0)
	{
		m_iStreamNO = 0;
	}
	else
	{
		m_iStreamNO =  _iStreamNo;
	}

	UI_UpdateDialogText();
	UpdateDomeHDPara();
	UpdateApertureType();
}

void CLS_DomeHDParam1::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialogText();
	UpdateTempName(m_cboTempleID.GetItemData(m_cboTempleID.GetCurSel()));
	UpdateDomeHDPara();
	UpdateApertureType();
}

void CLS_DomeHDParam1::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara, int _iUserData)
{
	STR_Para *pST_Para = (STR_Para*)_pPara;
	if (_iChannelNo == m_iChannelNo)//只刷新参数改变的通道
	{
		switch(_iParaType)
		{
		case PARA_ITS_TEMPLATENAME:	
		case PARA_HD_TEMPLATE_INDEX:
			{
				UpdateTempName(-1);
			}
			break;
		case PARA_ITS_TIMERANGEPARAM:
			{
				if (_pPara == NULL)
				{
					return;
				}

				int iIndex = ((int)pST_Para->m_iPara[1]) >> 16 & 0x0000FFFF;
				int iType = ((int)pST_Para->m_iPara[1]) & 0x0000FFFF;
				if (iType < 0 || iType >= MAX_TIME_RANGE_PARAM || iIndex < 0 || iIndex > MAX_ITS_TEMPLATE)//当前支持MAX_TIME_RANGE_PARAM-1个类型，MAX_ITS_TEMPLATE个模板，index=8为临时值
				{
					return;
				}
				if (MAX_ITS_TEMPLATE == iIndex)
				{
					UpdateDomeHDPara(255, iType);//更新对应类型的临时效果值
				}
				else
				{
					int iTemplateID = (int)m_cboTempleID.GetItemData(m_cboTempleID.GetCurSel());
					if (iIndex == iTemplateID)
					{
						UpdateDomeHDPara(iIndex, iType);//更新模板对应类型的效果值
					}	
				}
			}
			break;
		default:
			break;
		}
	}
}

void CLS_DomeHDParam1::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_STATIC_CURRENT_Template, IDS_HD_CUR_TEMPLATE);
	SetDlgItemTextEx(IDC_STATIC_TEMPNAME, IDS_CONFIG_HD_TEMPLATENAME);
	SetDlgItemTextEx(IDC_STATIC_DOME_Image_adjustment, IDS_DOME_HD_VIDEO_MODIFY);
	SetDlgItemTextEx(IDC_STATIC_Sharpness, IDS_HD_SHARPNESS);
	SetDlgItemTextEx(IDC_STATIC_COLOR_INCREASE, IDS_DOME_HD_COLOR_INCREASE);
	SetDlgItemTextEx(IDC_STATIC_COLOR_PHASE, IDS_DOME_HD_COLOR_PHASE);
	SetDlgItemTextEx(IDC_STATIC_GAMMASET, IDS_DOME_HD_GAMMASET);
	SetDlgItemTextEx(IDC_STATIC_GAMMA_MODIFY, IDS_DOME_HD_GAMMA_MODIFY);
	SetDlgItemTextEx(IDC_BUTTON_SET_TEMPLATE_NAME, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_EXPO, IDS_DOME_HD_VIDEO_EXPO);
	SetDlgItemTextEx(IDC_STC_REGULATE_AE, IDS_REGULATE_AE);
	SetDlgItemTextEx(IDC_STATIC_EXPOMODE, IDS_HD_ExposalMode);
	SetDlgItemTextEx(IDC_STATIC_SHUTTER, IDS_HD_SHUTTER);
	SetDlgItemTextEx(IDC_STATIC_APERTURE, IDS_STATIC_APERTURE);
	SetDlgItemTextEx(IDC_STATIC_Auto_Aperture, IDS_AUTO_APERTURE);
	SetDlgItemTextEx(IDC_STATIC_GAIN_AUTO, IDS_HD_AUTO_INCREASE);
	SetDlgItemTextEx(IDC_STATIC_GAIN_MAX, IDS_DOME_HD_MAX_INCREASE_LIMIT);
	SetDlgItemTextEx(IDC_STATIC_GAIN, IDS_STATIC_GAIN);
	SetDlgItemTextEx(IDC_STATIC_TARGET_BRIGHT, IDS_TARGET_BRIGHT);
	SetDlgItemTextEx(IDC_STATIC_AUTO_SLOW_EXPO, IDS_DOME_HD_SENSUP);
	SetDlgItemTextEx(IDC_STATIC_EXPO_OFFSET, IDS_EXPOSE_OFFSET);
	SetDlgItemTextEx(IDC_STATIC_SENSITIVE, IDS_DOME_HD_SENSITIVE);
	SetDlgItemTextEx(IDC_BUTTON_Sharpness_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_ColorIncrease_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_ColorPhase_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_GammaModify_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_AE_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_MaxGainLimit_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_Gain_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_Bright_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_SensUp_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_APERTURE_SELECT, IDS_APERTURE_TYPE);

	//Gamma设置
	m_cboGammaSet.ResetContent();
	m_cboGammaSet.InsertString(0, GetTextEx(IDS_MNG_ADMIN_AUTO));
	for (int iNum = 0; iNum < MAX_HD_CURVE_NUM; ++iNum)
	{
		m_cboGammaSet.InsertString(iNum + 1, GetTextEx(IDS_DOME_HD_CURVE) + IntToStr(iNum).c_str());
	}
	m_cboGammaSet.SetCurSel(0);

	m_slipSharpness.SetRange(CONST_MIN_SLIDER, CONST_MAX_SLIDER);
	m_slipSharpness.SetPos(CONST_MIN_SLIDER);

	m_slidColorIncrease.SetRange(CONST_MIN_SLIDER, CONST_MAX_SLIDER);
	m_slidColorIncrease.SetPos(CONST_MIN_SLIDER);

	m_slidColorPhase.SetRange(CONST_MIN_SLIDER, CONST_MAX_SLIDER);
	m_slidColorPhase.SetPos(CONST_MIN_SLIDER);

	m_slidGammaModify.SetRange(CONST_MIN_SLIDER, CONST_MAX_SLIDER);
	m_slidGammaModify.SetPos(CONST_MIN_SLIDER);

	//曝光模式
	CString szExpoMode[] = {GetTextEx(IDS_DOME_AUTO),
		GetTextEx(IDS_DOME_HANDLE),
		GetTextEx(IDS_DOME_EXPOMODE_SHUTTER),
		GetTextEx(IDS_DOME_EXPOMODE_APERTURE)};
	int iExpoMode = 4;
	m_cboExpoMode.ResetContent();
	for (int i=0; i<iExpoMode; i++)
	{
		m_cboExpoMode.InsertString(i, szExpoMode[i]);
	}
	m_cboExpoMode.SetCurSel(0);

	m_cboShutter.ResetContent();
	for (int i = 0; i < sizeof(g_iShutSpd3516)/sizeof(CString); i++)
	{
		m_cboShutter.InsertString(i, g_szShutSpd3516[i]);
		m_cboShutter.SetItemData(i,g_iShutSpd3516[i]);
	}
	m_cboShutter.SetCurSel(0);

	//光圈大小
	//0-关闭、1-F1.6、2-F2.0、3-F3.4、4-F4.4、5-F6.0、6-F8.0、7-F11.0、8-F2.2、9-F2.3、10-F2.4
	//、11-F2.8、12-F3.2、13-F4.0、14-F4.5、15-F4.8、16-F5.6、17-F6.4、18-F6.8、19-F9.0、20-F9.1
	//、21-F9.6、22-F12.8、23-F14.0、24-F18.1、25-F25.6、26-F36.2
	CString szAperture[] = {"F1.6", "F2.0", "F2.2", "F2.3", "F2.4", "F2.8", "F3.2", "F3.4", "F4.0"
							, "F4.4", "F4.5", "F4.8", "F5.6", "F6.0", "F6.4", "F6.8", "F8.0", "F9.0"
							, "F9.1", "F9.6", "F11.0", "F12.8", "F14.0", "F18.1", "F25.6", "F36.2"};
	int iAperData[] = {1,2,8,9,10,11,12,3,13,4,14,15,16,5,17,18,6,19,20,21,7,22,23,24,25,26};
	m_cboAperture.ResetContent();
	for (int i=0; i<sizeof(szAperture)/sizeof(CString); i++)
	{
		m_cboAperture.InsertString(i, szAperture[i]);
		m_cboAperture.SetItemData(i, iAperData[i]);
	}
	m_cboAperture.SetCurSel(0);

	InsertString(m_cboAutoAperture, 0, IDS_CONFIG_CLOSE);
	InsertString(m_cboAutoAperture, 1, IDS_CFG_SO_RUN);
	m_cboAutoAperture.SetCurSel(0);

	InsertString(m_cboAutoGain, 0, IDS_CONFIG_CLOSE);
	InsertString(m_cboAutoGain, 1, IDS_CFG_SO_RUN);
	m_cboAutoGain.SetCurSel(0);

	m_slidBright.SetRange(CONST_MIN_SLIDER, CONST_MAX_SLIDER);
	m_slidBright.SetPos(CONST_MAX_SLIDER);

	InsertString(m_cbo_Expo_OffSet, 0, IDS_CONFIG_CLOSE);
	InsertString(m_cbo_Expo_OffSet, 1, IDS_CFG_SO_RUN);
	m_cbo_Expo_OffSet.SetCurSel(0);

	InsertString(m_cboSensitive, 0, IDS_CONFIG_CLOSE);
	InsertString(m_cboSensitive, 1, IDS_CFG_SO_RUN);
	m_cboSensitive.SetCurSel(0);

	m_slidMaxGainLimit.SetRange(CONST_MIN_SLIDER, CONST_MAX_SLIDER);
	m_slidMaxGainLimit.SetPos(CONST_MAX_SLIDER);

	m_slidGain.SetRange(CONST_MIN_SLIDER, CONST_MAX_SLIDER);
	m_slidGain.SetPos(CONST_MAX_SLIDER);

	m_sliderSensUp.SetRange(CONST_MIN_SLIDER, CONST_MAX_SLIDER);
	m_sliderSensUp.SetPos(CONST_MAX_SLIDER);

	m_sldRegulateAE.SetRange(CONST_MIN_SLIDER + 1, CONST_MAX_SLIDER);


	m_cboTempleID.ResetContent();
	CString cstrTamplateName;
	m_cboTempleID.SetItemData(m_cboTempleID.InsertString(HD_MODE_INDEX0, GetTextEx(IDS_HD_MODE_IMMEDIATELY)), HD_MODE_IMMEDIATELY);
	for (int i = 0; i < MAX_ITS_TEMPLATE; ++i)
	{
		char cTemplateName[LEN_64] = {0};
		int iRet = NetClient_GetHDTemplateName(m_iLogonID, i, cTemplateName);
		if (iRet >= 0)
		{
			cstrTamplateName = GetHDTemplateName(cTemplateName);
			m_cboTempleID.SetItemData(m_cboTempleID.InsertString(i+1,cstrTamplateName), i);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_GetHDTemplateName (%d), error(%d)",m_iLogonID, GetLastError());
		}
	}
	m_cboTempleID.SetCurSel(0);
	CEdit *pcedtTempName=(CEdit *)GetDlgItem(IDC_EDIT_TEMPNAME);

	pcedtTempName->SetWindowText(GetTextEx(IDS_HD_MODE_IMMEDIATELY));
}

void CLS_DomeHDParam1::SwitchExpoAutoText( int _iType/*=1*/ )
{
	switch(_iType)
	{
	case 0:
		{
			SetDlgItemText(IDC_STATIC_SHUTTER,GetTextEx(IDS_STATIC_SHUTTER));
			SetDlgItemText(IDC_STATIC_APERTURE,GetTextEx(IDS_STATIC_APERTURE));
			SetDlgItemText(IDC_STATIC_GAIN,GetTextEx(IDS_STATIC_GAIN));
		}
		break;
	case 1:
		{
			GetDlgItem(IDC_STATIC_SHUTTER)->SetWindowText(GetTextEx(IDS_MAX_EXEPORE_TIME));
			GetDlgItem(IDC_STATIC_APERTURE)->SetWindowText(GetTextEx(IDS_MAX_APERTURE_SET));
			GetDlgItem(IDC_STATIC_GAIN)->SetWindowText(GetTextEx(IDS_MAX_GAIN_SET));
		}
		break;
	case 2:
		{
			GetDlgItem(IDC_STATIC_SHUTTER)->SetWindowText(GetTextEx(IDS_STATIC_SHUTTER));
			GetDlgItem(IDC_STATIC_APERTURE)->SetWindowText(GetTextEx(IDS_MAX_APERTURE_SET));
			GetDlgItem(IDC_STATIC_GAIN)->SetWindowText(GetTextEx(IDS_MAX_GAIN_SET));
		}
		break;
	case 3:
		{
			GetDlgItem(IDC_STATIC_SHUTTER)->SetWindowText(GetTextEx(IDS_MAX_EXEPORE_TIME));
			GetDlgItem(IDC_STATIC_APERTURE)->SetWindowText(GetTextEx(IDS_STATIC_APERTURE));
			GetDlgItem(IDC_STATIC_GAIN)->SetWindowText(GetTextEx(IDS_MAX_GAIN_SET));
		}
		break;
	default:
		break;
	}

}

void CLS_DomeHDParam1::UpdateTempName(int _iIndex)
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error(%d)", m_iLogonID, GetLastError());
		return;
	}

	int iTempID = _iIndex;
	if (-1 == iTempID)
	{
		NetClient_GetHDTemplateIndex(m_iLogonID, m_iChannelNo, &iTempID);
		iTempID = m_cboTempleID.GetItemData(iTempID);
	}

	CString cstrTamplateName;

	if (HD_MODE_IMMEDIATELY == iTempID)
	{
		cstrTamplateName = GetTextEx(IDS_HD_MODE_IMMEDIATELY);
	}
	else
	{
		char cTemplateName[LEN_64] = {0};
		int iRet = NetClient_GetHDTemplateName(m_iLogonID, iTempID, cTemplateName);
		if (iRet >= 0)
		{
			cstrTamplateName = GetHDTemplateName(cTemplateName);
		}
	}
	
	CEdit *pcedtTempName=(CEdit *)GetDlgItem(IDC_EDIT_TEMPNAME);

	pcedtTempName->SetWindowText(cstrTamplateName);
		
}

void CLS_DomeHDParam1::UpdateDomeHDPara(int _iTemplateID, int _iType)
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error(%d)", m_iLogonID, GetLastError());
		return;
	}

	int iTempID = (int)m_cboTempleID.GetItemData(m_cboTempleID.GetCurSel());
	bool bGetTemplatePara = false;
	if (-1 == _iTemplateID)
	{
		bGetTemplatePara = true;
	}
	if (255 == _iTemplateID)
	{
		iTempID = _iTemplateID;
	}

	ITS_TTimeRangeParam pb = {0};
	int iRet = NetClient_GetHDTimeRangeParam(m_iLogonID, m_iChannelNo, iTempID, &pb, sizeof(pb));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetHDTimeRangeParam  (%d, %d, %d), error (%d)"
			, m_iLogonID, m_iChannelNo, iTempID, GetLastError());
	}
	else
	{
		//7-锐度调节											
		if(bGetTemplatePara || _iType == HD_PARA_SHARPNESS)	
		{	
			int iSharpPos = pb.iParam1[HD_PARA_SHARPNESS];
			m_slipSharpness.SetPos(iSharpPos);
			SetDlgItemInt(IDC_STATIC_Sharpness_TEXT, iSharpPos);
		}

		//色彩增益
		if(bGetTemplatePara || _iType == HD_PARA_COLOR_INCREASE)	
		{
			int iColorIncrease = pb.iParam1[HD_PARA_COLOR_INCREASE];
			m_slidColorIncrease.SetPos(iColorIncrease);
			SetDlgItemInt(IDC_STATIC_COLOR_INCREASE_TEXT, iColorIncrease);
		}

		//色彩相位
		if(bGetTemplatePara || _iType == HD_PARA_COLOR_PHASE)	
		{
			int iColorPhase = pb.iParam1[HD_PARA_COLOR_PHASE];
			m_slidColorPhase.SetPos(iColorPhase);
			SetDlgItemInt(IDC_STATIC_COLOR_PHASE_TEXT, iColorPhase);
		}

		//6-Gamma类型
		if (bGetTemplatePara || _iType == HD_PARA_GAMMA)
		{
			int iGammaPos = pb.iParam3[HD_PARA_GAMMA];
			m_slidGammaModify.SetPos(iGammaPos);
			SetDlgItemInt(IDC_STATIC_GAMMA_MODIFY_TEXT, iGammaPos);
			if (1 == pb.iAutoEnable[HD_PARA_GAMMA])
			{
				m_cboGammaSet.SetCurSel(0);
				GetDlgItem(IDC_SLIDER_GAMMA_MODIFY)->EnableWindow(FALSE);
			}
			else
			{
				m_cboGammaSet.SetCurSel(pb.iParam2[HD_PARA_GAMMA]+1);
				GetDlgItem(IDC_SLIDER_GAMMA_MODIFY)->EnableWindow(TRUE);
			}
		}

		//25-AE调节
		if (bGetTemplatePara || _iType == HD_PARA_AE_SPEED)
		{
			int iValue = pb.iParam1[HD_PARA_AE_SPEED];
			m_sldRegulateAE.SetPos(iValue);
			SetDlgItemInt(IDC_STC_REGULATE_AE_TEXT, iValue);
		}

		//18-曝光模式
		if (bGetTemplatePara || _iType == HD_PARA_EXPO_MODE)
		{
			int iExpoMode = pb.iParam1[HD_PARA_EXPO_MODE] - 3;
			if (iExpoMode  < 0)
			{
				iExpoMode = 0;
			}
			m_cboExpoMode.SetCurSel(iExpoMode);
			switch(iExpoMode)
			{
			case 0:
				{
					SwitchExpoAutoText(1);
				}
				break;
			case 1:
				{
					SwitchExpoAutoText(0);
				}
				break;
			case 2:
				{		
					SwitchExpoAutoText(2);
				}
				break;
			case 3:
				{
					SwitchExpoAutoText(3);
				}
				break;
			default:
				break;
			}		
		}
		
		//快门
		if (bGetTemplatePara || _iType == HD_PARA_SHUTTER)
		{
			int iType = -1;
			int iIndex = pb.iAutoEnable[HD_PARA_SHUTTER];
			if (iIndex == 1)
			{
				iType = pb.iParam2[HD_PARA_SHUTTER];
			}
			else
			{
				iType = pb.iParam1[HD_PARA_SHUTTER];
			}
			int iCount = m_cboShutter.GetCount();
			for (int x=0; x<iCount; x++)
			{
				if (m_cboShutter.GetItemData(x) == iType)
				{
					m_cboShutter.SetCurSel(x);
					break;
				}
			}
		}						

		//0-光圈调节
		if (bGetTemplatePara || _iType == HD_PARA_APERTURE)
		{
			int iIndex = pb.iAutoEnable[HD_PARA_APERTURE];
			int iAperture = 0;
			if (iIndex == 1)
			{
				iAperture = pb.iParam2[HD_PARA_APERTURE];
			}
			else
			{
				iAperture = pb.iParam1[HD_PARA_APERTURE];
			}
			int iCount = m_cboAperture.GetCount();
			for (int x=0; x<iCount; x++)
			{
				if (m_cboAperture.GetItemData(x) == iAperture)
				{
					m_cboAperture.SetCurSel(x);
					break;
				}
			}
			m_cboAutoAperture.SetCurSel(pb.iParam1[HD_PARA_APERTURE]);
		}

		//5-增益调节
		if (bGetTemplatePara || _iType == HD_PARA_GAIN)
		{
			int iGainPos = -1;
			int iIndex = pb.iAutoEnable[HD_PARA_GAIN];
			m_cboAutoGain.SetCurSel(iIndex);
			if (iIndex == 1)
			{
				iGainPos = pb.iParam2[HD_PARA_GAIN];
			} 
			else
			{
				iGainPos = pb.iParam1[HD_PARA_GAIN];
			}
			m_slidGain.SetPos(iGainPos);
			m_slidMaxGainLimit.SetPos(iGainPos);	
			SetDlgItemInt(IDC_STATIC_GAIN_RANGE, iGainPos);	
			SetDlgItemInt(IDC_STATIC_GAIN_MAX_RANGE, iGainPos);	
		}

		//12-亮度调节
		if (bGetTemplatePara || _iType == HD_PARA_BRIGHTNESS_HD)
		{
			if (pb.iAutoEnable[HD_PARA_BRIGHTNESS_HD] == 1)
			{
				int iBright = pb.iParam1[HD_PARA_BRIGHTNESS_HD];
				m_slidBright.SetPos(iBright);
				SetDlgItemInt(IDC_SLIDER_TARGET_BRIGHT, iBright);
			}
		}
		
		if (bGetTemplatePara || _iType == HD_PARA_AUTO_SLOW_EXPO)
		{
			int iAutoSlowExpo = pb.iParam1[HD_PARA_AUTO_SLOW_EXPO];
			m_sliderSensUp.SetPos(iAutoSlowExpo);
			SetDlgItemInt(IDC_STATIC_AUTO_SLOW_EXPO_TEXT, iAutoSlowExpo);
		}	

		//补偿增益
		if (bGetTemplatePara || _iType == HD_PARA_OFFSET_INCREASE)
		{
			int iOffsetType = pb.iParam1[HD_PARA_OFFSET_INCREASE];
			m_cbo_Expo_OffSet.SetCurSel(iOffsetType);
			int iOffSetIncrease = pb.iParam2[HD_PARA_OFFSET_INCREASE];
		}

		//高感度
		if (bGetTemplatePara || _iType == HD_PARA_OFFSET_INCREASE)
		{
			int iSensetive = pb.iParam1[HD_PARA_SENSETIVE];
			m_cboSensitive.SetCurSel(iSensetive);
		}

		AddLog(LOG_TYPE_SUCC,"","NetClient_GetHDTimeRangeParam (%d, %d, %d)",m_iLogonID, m_iChannelNo, iTempID);
	}
}

void CLS_DomeHDParam1::UpdateApertureType()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	ApertureType strctApertureType = {0};
	strctApertureType.iBufSize = sizeof(ApertureType);
	int iReturn = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_IRIS_TYPE, m_iChannelNo
		, &strctApertureType, sizeof(ApertureType), &iReturn);
	if (iRet != 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig[NET_CLIENT_IRIS_TYPE] (%d, %d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}
	else
	{
		if (strctApertureType.iType > 0)
		{
			m_iApertureTypePiris = strctApertureType.iType - 1;
			UpdateData(FALSE);
		}
	}
}

int CLS_DomeHDParam1::SetDomeHDPara(int _iType, int _iAutoEnable, int _iParam1, int _iParam2, int _iParam3, int _iParam4)
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error(%d)", m_iLogonID, GetLastError());
		return -1;
	}

	int iSelIndex = m_cboTempleID.GetCurSel();
	int iTempID = (int)m_cboTempleID.GetItemData(iSelIndex);
	ITS_TTimeRangeParam pb = {0};
	pb.iType = _iType;
	pb.iAutoEnable[_iType] = _iAutoEnable;
	pb.iParam1[_iType] = _iParam1;
	pb.iParam2[_iType] = _iParam2;
	pb.iParam3[_iType] = _iParam3;
	pb.iParam4[_iType] = _iParam4;

	int iRet = NetClient_SetHDTimeRangeParam(m_iLogonID, m_iChannelNo, iTempID, &pb, sizeof(pb));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetHDTimeRangeParam, (%d, %d, %d), error(%d)",m_iLogonID, m_iChannelNo, _iType, GetLastError());
		return -1;
	}

	AddLog(LOG_TYPE_SUCC,"","NetClient_SetHDTimeRangeParam, (%d, %d, %d)",m_iLogonID, m_iChannelNo, _iType);
	return 0;
}

void CLS_DomeHDParam1::OnCbnSelchangeComboCurrentTemp()
{
	// TODO: Add your control notification handler code here
	UpdateTempName(m_cboTempleID.GetItemData(m_cboTempleID.GetCurSel()));
	UpdateDomeHDPara();
}

void CLS_DomeHDParam1::OnNMCustomdrawSliderSharpness(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 锐度调节
	int iPos = m_slipSharpness.GetPos();
	SetDlgItemInt(IDC_STATIC_Sharpness_TEXT, iPos);

	*pResult = 0;
}

void CLS_DomeHDParam1::OnNMCustomdrawSliderColorIncrease(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:色彩增益
	int iPos = m_slidColorIncrease.GetPos();
	SetDlgItemInt(IDC_STATIC_COLOR_INCREASE_TEXT, iPos);

	*pResult = 0;
}

void CLS_DomeHDParam1::OnNMCustomdrawSliderColorPhase(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 色彩相位
	int iPos = m_slidColorPhase.GetPos();
	SetDlgItemInt(IDC_STATIC_COLOR_PHASE_TEXT, iPos);

	*pResult = 0;
}

void CLS_DomeHDParam1::OnCbnSelchangeComboGammaset()
{
	// TODO: Gamma设置
	int iIndex = m_cboGammaSet.GetCurSel();
	int iGammaPos = m_slidGammaModify.GetPos();
	if (iIndex == 0)
	{
		GetDlgItem(IDC_SLIDER_GAMMA_MODIFY)->EnableWindow(FALSE);
		//选择自动，设置AutoEnable为1
		SetDomeHDPara(HD_PARA_GAMMA, 1, 0, 0, 0, 0);
	}
	else
	{
		GetDlgItem(IDC_SLIDER_GAMMA_MODIFY)->EnableWindow(TRUE);
		//选择手动，Param2给选择的曲线类型，Param3给相应的数值
		SetDomeHDPara(HD_PARA_GAMMA, 0, 0, (iIndex - 1), iGammaPos, 0);
	}
}

void CLS_DomeHDParam1::OnNMCustomdrawSliderGammaModify(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Gamma调节
	int iPos = m_slidGammaModify.GetPos();
	SetDlgItemInt(IDC_STATIC_GAMMA_MODIFY_TEXT, iPos);

	*pResult = 0;
}

void CLS_DomeHDParam1::OnBnClickedRadioApertureType()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error(%d)", m_iLogonID, GetLastError());
		return;
	}

	UpdateData();
	ApertureType strctApertureType = {0};
	strctApertureType.iBufSize = sizeof(ApertureType);
	strctApertureType.iType = m_iApertureTypePiris + 1;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_IRIS_TYPE
		, m_iChannelNo, &strctApertureType, sizeof(ApertureType));
	if (iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig[NET_CLIENT_IRIS_TYPE] (%d, %d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}	
}

void CLS_DomeHDParam1::OnBnClickedButtonSetTemplateName()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error(%d)", m_iLogonID, GetLastError());
		return;
	}

	int iTemplateID = (int)m_cboTempleID.GetItemData(m_cboTempleID.GetCurSel());
	if (iTemplateID<0 || iTemplateID == HD_MODE_IMMEDIATELY)
	{
		return;
	}

	CString strTempName;
	m_edtTempleName.GetWindowText(strTempName);	
	char cGetTemplateName[64] = {0};
	int iRet = NetClient_GetHDTemplateName(m_iLogonID, iTemplateID, cGetTemplateName);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_GetHDTemplateName(%d), error(%d)", m_iLogonID, GetLastError());;
		return;
	}
	CString strGetTemplateName = GetHDTemplateName(cGetTemplateName);
	if (strTempName != strGetTemplateName)
	{
		char cTemplateName[LEN_64] = {0};	
		memcpy_s(cTemplateName, sizeof(cTemplateName), strTempName, strTempName.GetLength());
		iRet = NetClient_SetHDTemplateName(m_iLogonID, iTemplateID, cTemplateName);

		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"", "NetClient_SetHDTemplateName(%d), error(%d)", m_iLogonID, GetLastError());
		}
		else
		{
			AddLog(LOG_TYPE_SUCC,"", "NetClient_SetHDTemplateName(%d)", m_iLogonID);
		}
	}
}

void CLS_DomeHDParam1::OnNMCustomdrawSldRegulate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	int iPos = m_sldRegulateAE.GetPos();
	SetDlgItemInt(IDC_STC_REGULATE_AE_TEXT, iPos);

	*pResult = 0;
}

void CLS_DomeHDParam1::OnCbnSelchangeComboExpomode()
{
	// TODO: Add your control notification handler code here
	int iIndex = m_cboExpoMode.GetCurSel();
	if (iIndex == 0)
	{
		SwitchExpoAutoText(1);
	}
	else if (iIndex == 1)
	{
		SwitchExpoAutoText(0);
	}
	else if (iIndex == 2)
	{
		SwitchExpoAutoText(2);
	}
	else if (iIndex == 3)
	{
		SwitchExpoAutoText(3);
	}
	SetDomeHDPara(HD_PARA_EXPO_MODE, 1, iIndex + 3, 0, 0, 0);
}

void CLS_DomeHDParam1::OnCbnSelchangeComboShutter()
{
	// TODO: 快门速度
	int iIndex = m_cboExpoMode.GetCurSel();
	int iShutter = (int)m_cboShutter.GetItemData(m_cboShutter.GetCurSel());
	if (iIndex == 1 || iIndex == 2)
	{
		SetDomeHDPara(HD_PARA_SHUTTER, 0, iShutter, 0, 0, 0); //手动
	} 
	else
	{
		SetDomeHDPara(HD_PARA_SHUTTER, 1, 0, iShutter, 0, 0); //非手动
	}
}

void CLS_DomeHDParam1::OnCbnSelchangeComboAperture()
{
	// TODO: 光圈大小
	int iIndex = m_cboExpoMode.GetCurSel();
	int iAperture = (int)m_cboAperture.GetItemData(m_cboAperture.GetCurSel());
	if (iIndex == 1 || iIndex == 3)
	{
		SetDomeHDPara(HD_PARA_APERTURE, 0, iAperture, 0, 0, 0); //手动
	} 
	else
	{
		SetDomeHDPara(HD_PARA_APERTURE, 1, 0, iAperture, 0, 0); //非手动	
	}
}

void CLS_DomeHDParam1::OnCbnSelchangeComboAutoAperture()
{
	// TODO: Add your control notification handler code here
	int iHDValue = m_cboAutoAperture.GetCurSel();
	SetDomeHDPara(HD_PARA_APERTURE, 1, iHDValue, 0, 0, 0);
}

void CLS_DomeHDParam1::OnCbnSelchangeComboGainAuto()
{
	// TODO: Add your control notification handler code here
	int iSel = m_cboAutoGain.GetCurSel();//0 关闭,1开启
	if (iSel == 1)//自动增益开启
	{
		SetDomeHDPara(HD_PARA_GAIN, 1, 0, m_slidMaxGainLimit.GetPos(), 0, 0);
	}
	else//自动增益关闭
	{
		SetDomeHDPara(HD_PARA_GAIN, 0, m_slidGain.GetPos(), 0, 0, 0);
	}
}

void CLS_DomeHDParam1::OnNMCustomdrawSliderGainMax(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:最大增益调节
	int iPos = m_slidMaxGainLimit.GetPos();
	SetDlgItemInt(IDC_STATIC_GAIN_MAX_RANGE, iPos);

	*pResult = 0;
}

void CLS_DomeHDParam1::OnNMCustomdrawSliderGain(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:增益调节
	int iPos = m_slidGain.GetPos();
	SetDlgItemInt(IDC_STATIC_GAIN_RANGE, iPos);

	*pResult = 0;
}

void CLS_DomeHDParam1::OnNMCustomdrawSliderTargetBright(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	int iPos = m_slidBright.GetPos();
	SetDlgItemInt(IDC_STATIC__TARGET_BRIGHT, iPos);

	*pResult = 0;
}

void CLS_DomeHDParam1::OnNMCustomdrawSliderAutoSlowExpo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Sens_Up
	int iPos = m_sliderSensUp.GetPos();
	SetDlgItemInt(IDC_STATIC_AUTO_SLOW_EXPO_TEXT, iPos);

	*pResult = 0;
}

void CLS_DomeHDParam1::OnCbnSelchangeComboExpoOffset()
{
	// TODO: 曝光补偿---用于控制补偿增益
	int iIndex = m_cbo_Expo_OffSet.GetCurSel();
	int iOffSet_Expo = 50;
	if (iIndex == 0)
	{
		//隐藏 补偿增益 调节选项
		SetDomeHDPara(HD_PARA_OFFSET_INCREASE, 1, iIndex, 0, 0, 0);
	}
	else
	{
		SetDomeHDPara(HD_PARA_OFFSET_INCREASE, 1, iIndex, iOffSet_Expo, 0, 0);
	}
}

void CLS_DomeHDParam1::OnCbnSelchangeComboSensitive()
{
	// TODO: 高感度 Param1代表高感度，1开启 0关闭和选项序号保持一致
	SetDomeHDPara(HD_PARA_SENSETIVE, 0, m_cboSensitive.GetCurSel(), 0, 0, 0);
}

void CLS_DomeHDParam1::OnBnClickedButtonSharpnessSet()
{
	// TODO: 锐度调节
	int iPos = m_slipSharpness.GetPos();
	SetDomeHDPara(HD_PARA_SHARPNESS, 0, iPos, 255, 0, 0);
}

void CLS_DomeHDParam1::OnBnClickedButtonColorincreaseSet()
{
	int iPos = m_slidColorIncrease.GetPos();
	SetDomeHDPara(HD_PARA_COLOR_INCREASE, 0, iPos, 0, 0, 0);
}

void CLS_DomeHDParam1::OnBnClickedButtonColorphaseSet()
{
	// TODO: 色彩相位
	int iPos = m_slidColorPhase.GetPos();
	SetDomeHDPara(HD_PARA_COLOR_PHASE, 0, iPos, 0, 0, 0);
}

void CLS_DomeHDParam1::OnBnClickedButtonGammamodifySet()
{
	int iPos = m_slidGammaModify.GetPos();
	int iType = m_cboGammaSet.GetCurSel();
	if (iType == 0)
	{	//自动
		SetDomeHDPara(HD_PARA_GAMMA, 1, 0, 0, 0, 0);
	}
	else
	{
		SetDomeHDPara(HD_PARA_GAMMA, 0, 0, iType - 1, iPos, 0);
	}
}

void CLS_DomeHDParam1::OnBnClickedButtonAeSet()
{
	int iPos = m_sldRegulateAE.GetPos();
	SetDomeHDPara(HD_PARA_AE_SPEED, 1, iPos, 0, 0, 0);
}

void CLS_DomeHDParam1::OnBnClickedButtonMaxgainlimitSet()
{
	// TODO:最大增益调节
	int iExpoMode = m_cboExpoMode.GetCurSel();
	int iPos = m_slidMaxGainLimit.GetPos();
	int iSel = m_cboAutoGain.GetCurSel();
	if (1 == iExpoMode)
	{
		SetDomeHDPara(HD_PARA_GAIN, 0, iPos, 0, 0, 0); //手动
	}
	else
	{
		SetDomeHDPara(HD_PARA_GAIN, 1, 0, iPos, 0, 0);
	}
}

void CLS_DomeHDParam1::OnBnClickedButtonGainSet()
{
	// TODO:增益调节
	int iPos = m_slidGain.GetPos();
	int iSel = m_cboAutoGain.GetCurSel();
	if (iSel != 1)//自动增益关闭
	{
		SetDomeHDPara(HD_PARA_GAIN, 0, iPos, 0, 0, 0);
	}
}

void CLS_DomeHDParam1::OnBnClickedButtonBrightSet()
{
	int iPos = m_slidBright.GetPos();
	SetDomeHDPara(HD_PARA_BRIGHTNESS_HD, 1, iPos, 255, 0, 0);
}

void CLS_DomeHDParam1::OnBnClickedButtonSensupSet()
{
	int iPos = m_sliderSensUp.GetPos();
	SetDomeHDPara(HD_PARA_AUTO_SLOW_EXPO, 1, m_sliderSensUp.GetPos(), 0, 0, 0);
}

