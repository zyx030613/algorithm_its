// DomeHDParam3.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "DomeHDParam3.h"


// CLS_DomeHDParam3 dialog

#define HD_MODE_INDEX0                      0
#define HD_MODE_IMMEDIATELY                 255

IMPLEMENT_DYNAMIC(CLS_DomeHDParam3, CDialog)

CLS_DomeHDParam3::CLS_DomeHDParam3(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DomeHDParam3::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNO = -1;
}

CLS_DomeHDParam3::~CLS_DomeHDParam3()
{
}

void CLS_DomeHDParam3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CURRENT_TEMP, m_cboTempleID);
	DDX_Control(pDX, IDC_CBO_VIDEO_STYLE, m_cboImageStyle);
	DDX_Control(pDX, IDC_COMBO_InOutDoor_Mode, m_cboInOutDoorMode);
	DDX_Control(pDX, IDC_CBO_THROUGH_MIST, m_cboThroughMist);
	DDX_Control(pDX, IDC_SLIDER_MIST_STRENGTH, m_slidMistStrength);
	DDX_Control(pDX, IDC_CBO_STRONGLIGHT, m_cboStrongLight);
	DDX_Control(pDX, IDC_SLIDER_BIG_LIGHT, m_slidBigLight);
	DDX_Control(pDX, IDC_COMBO_DNR, m_cboDNR);
	DDX_Control(pDX, IDC_SLIDER_NOISE, m_slidTimeDomainNoise);
	DDX_Control(pDX, IDC_SLIDER_NOISE2, m_slidSpaceDomainNoise);
	DDX_Control(pDX, IDC_SLIDER_DNRSET, m_slidNoiseLevel);
	DDX_Control(pDX, IDC_CBO_AUTO_CONTRAST, m_cboAutoContrast);
	DDX_Control(pDX, IDC_COMBO_SENCITIVITY_AUTO_CONTRAST, m_cboSencitivityAutoContrast);
	DDX_Control(pDX, IDC_CBO_NIGHT_STRENTH, m_cboNightStrength);
	DDX_Control(pDX, IDC_CBO_LIGHTLESS, m_cboLightness);
	DDX_Control(pDX, IDC_CBO_VIDEO_FROST, m_cboVidoeFrost);
	DDX_Control(pDX, IDC_BTN_PARAM3_SET_LIGHT_INHIBITION, m_btnSetLightInhibition);
	DDX_Control(pDX, IDC_BTN_PARAM3_SET_THROUGH_MIST, m_btnSetThroughMist);
	DDX_Control(pDX, IDC_BTN_PARAM3_SET_DNR, m_btnParam3SetDnr);
}


BEGIN_MESSAGE_MAP(CLS_DomeHDParam3, CDialog)
	ON_CBN_SELCHANGE(IDC_CBO_VIDEO_STYLE, &CLS_DomeHDParam3::OnCbnSelchangeCboVideoStyle)
	ON_CBN_SELCHANGE(IDC_COMBO_InOutDoor_Mode, &CLS_DomeHDParam3::OnCbnSelchangeComboInoutdoorMode)
	ON_CBN_SELCHANGE(IDC_CBO_THROUGH_MIST, &CLS_DomeHDParam3::OnCbnSelchangeCboThroughMist)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MIST_STRENGTH, &CLS_DomeHDParam3::OnNMCustomdrawSliderMistStrength)
	ON_CBN_SELCHANGE(IDC_CBO_STRONGLIGHT, &CLS_DomeHDParam3::OnCbnSelchangeCboStronglight)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BIG_LIGHT, &CLS_DomeHDParam3::OnNMCustomdrawSliderBigLight)
	ON_CBN_SELCHANGE(IDC_COMBO_DNR, &CLS_DomeHDParam3::OnCbnSelchangeComboDnr)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_DNRSET, &CLS_DomeHDParam3::OnNMCustomdrawSliderNoiseLevel)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_NOISE, &CLS_DomeHDParam3::OnNMCustomdrawSliderTimeDomainNoise)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_NOISE2, &CLS_DomeHDParam3::OnNMCustomdrawSliderSpaceDomainNoise)
	ON_CBN_SELCHANGE(IDC_CBO_AUTO_CONTRAST, &CLS_DomeHDParam3::OnCbnSelchangeCboAutoContrast)
	ON_CBN_SELCHANGE(IDC_COMBO_SENCITIVITY_AUTO_CONTRAST, &CLS_DomeHDParam3::OnCbnSelchangeComboSencitivityAutoContrast)
	ON_CBN_SELCHANGE(IDC_CBO_LIGHTLESS, &CLS_DomeHDParam3::OnCbnSelchangeCboLightless)
	ON_CBN_SELCHANGE(IDC_CBO_NIGHT_STRENTH, &CLS_DomeHDParam3::OnCbnSelchangeCboNightStrenth)
	ON_CBN_SELCHANGE(IDC_CBO_VIDEO_FROST, &CLS_DomeHDParam3::OnCbnSelchangeCboVideoFrost)
	ON_BN_CLICKED(IDC_BTN_PARAM3_SET_LIGHT_INHIBITION, &CLS_DomeHDParam3::OnBnClickedBtnParam3SetLightInhibition)
	ON_BN_CLICKED(IDC_BTN_PARAM3_SET_THROUGH_MIST, &CLS_DomeHDParam3::OnBnClickedBtnParam3SetThroughMist)
	ON_BN_CLICKED(IDC_BTN_PARAM3_SET_DNR, &CLS_DomeHDParam3::OnBnClickedBtnParam3SetDnr)
	ON_CBN_SELCHANGE(IDC_COMBO_CURRENT_TEMP, &CLS_DomeHDParam3::OnCbnSelchangeComboCurrentTemp)
END_MESSAGE_MAP()


// CLS_DomeHDParam3 message handlers

BOOL CLS_DomeHDParam3::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	//UI_UpdateDialogText();
	//UpdateDomeHDPara();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_DomeHDParam3::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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
}

void CLS_DomeHDParam3::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialogText();
	UpdateDomeHDPara();
}

void CLS_DomeHDParam3::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
{
	STR_Para *pST_Para = (STR_Para*)_pPara;
	if (_iChannelNo == m_iChannelNo)//只刷新参数改变的通道
	{
		switch(_iParaType)
		{
		case PARA_ITS_TEMPLATENAME:	
		case PARA_HD_TEMPLATE_INDEX:
			{
				UI_UpdateDialogText();
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
					int iTemplateID = m_cboTempleID.GetCurSel();
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

void CLS_DomeHDParam3::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_STATIC_CURRENT_Template, IDS_HD_CUR_TEMPLATE);
	SetDlgItemTextEx(IDC_STATIC_HD_PICINCREASE, IDS_DOME_HD_PICINCREASE);
	SetDlgItemTextEx(IDC_STC_VIDEO_STYLE, IDS_IMAGE_STYLE);
	SetDlgItemTextEx(IDC_STATIC_InOut_Mode, IDS_HD_IndoorOutdoor);
	SetDlgItemTextEx(IDC_STC_THROUGH_MIST, IDS_STATIC_THROUGH_MIST);
	SetDlgItemTextEx(IDC_STATIC_MIST_STRENGTH, IDS_STATIC_THROUGH_MIST_STRENGTH);
	SetDlgItemTextEx(IDC_STATIC_STRONG_LIGHT, IDS_STATIC_STRONG_LIGHT);
	SetDlgItemTextEx(IDC_STATIC_BIG_LIGHT_TEXT, IDS__BIG_LIGHT_TEXT);
	SetDlgItemTextEx(IDC_STATIC_DNR, IDS_HD_NoiseMode);
	SetDlgItemTextEx(IDC_STATIC_NOISE_1, IDS_HD_NOISE_2);
	SetDlgItemTextEx(IDC_STATIC_NOISE_2, IDS_HD_NOISE_3);
	SetDlgItemTextEx(IDC_STATIC_DNRSET, IDS_HD_NOISE_1);
	SetDlgItemTextEx(IDC_STATIC_AUTO_CONTRAST, IDS_DOME_HD_AUTO_CONTRAST);
	SetDlgItemTextEx(IDC_STATIC_SENCITIVITY_AUTO_CONTRAST, IDS_VCA_SENSITIVITY);
	SetDlgItemTextEx(IDC_STC_LIGHTLESS, IDS_DOME_HD_LIGHTLESS);
	SetDlgItemTextEx(IDC_STATIC_NIGHT_STRENTH, IDS_DOME_HD_NIGHT_STRENTH);
	SetDlgItemTextEx(IDC_STATIC_HD_OTHER, IDS_CFG_LOG_DVR_OTHER);
	SetDlgItemTextEx(IDC_STC_VIDEO_FROST, IDS_DOME_HD_VIDEO_FROST);
	SetDlgItemTextEx(IDC_BTN_PARAM3_SET_LIGHT_INHIBITION, IDS_ITS_SET_DENOISE);
	SetDlgItemTextEx(IDC_BTN_PARAM3_SET_THROUGH_MIST, IDS_ITS_SET_DENOISE);
	SetDlgItemTextEx(IDC_BTN_PARAM3_SET_DNR, IDS_ITS_SET_DENOISE);

	//图像风格
	InsertString(m_cboImageStyle, 0, IDS_STYLE_AUTO);
	InsertString(m_cboImageStyle, 1, IDS_STYLE_NATURE);
	InsertString(m_cboImageStyle, 2, IDS_STYLE_BRIGHT);
	InsertString(m_cboImageStyle, 3, IDS_STYLE_SMOOTH);
	InsertString(m_cboImageStyle, 4, IDS_STYLE_COLORFUL);
	m_cboImageStyle.SetCurSel(0);

	//室内外场景
	InsertString(m_cboInOutDoorMode, 0, IDS_HD_MODE_INDOOR);
	InsertString(m_cboInOutDoorMode, 1, IDS_HD_MODE_OUTDOOR);
	m_cboInOutDoorMode.SetCurSel(0);

	//透雾
	InsertString(m_cboThroughMist, 0, IDS_CONFIG_CLOSE);
	InsertString(m_cboThroughMist, 1, IDS_CFG_SO_RUN);
	m_cboThroughMist.SetCurSel(0);
	m_slidMistStrength.SetRange(CONST_MIN_SLIDER, CONST_MAX_SLIDER);
	m_slidMistStrength.SetPos(CONST_MIN_SLIDER);

	//强光抑制
	InsertString(m_cboStrongLight, 0, IDS_CONFIG_CLOSE);
	InsertString(m_cboStrongLight, 1, IDS_CFG_SO_RUN);
	m_cboStrongLight.SetCurSel(0);
	m_slidBigLight.SetRange(CONST_MIN_SLIDER, CONST_MAX_SLIDER);
	m_slidBigLight.SetPos(CONST_MIN_SLIDER);

	//自动降噪
	InsertString(m_cboDNR, 0, IDS_CONFIG_CLOSE);
	InsertString(m_cboDNR, 1, IDS_HD_NoiseNode1);
	InsertString(m_cboDNR, 2, IDS_HD_NoiseNode2);
	m_cboDNR.SetCurSel(0);
	m_slidTimeDomainNoise.SetRange(CONST_MIN_SLIDER + 1, CONST_MAX_SLIDER);
	m_slidTimeDomainNoise.SetPos(CONST_MIN_SLIDER);
	m_slidSpaceDomainNoise.SetRange(CONST_MIN_SLIDER + 1, CONST_MAX_SLIDER);
	m_slidSpaceDomainNoise.SetPos(CONST_MIN_SLIDER);
	m_slidNoiseLevel.SetRange(CONST_MIN_SLIDER + 1, CONST_MAX_SLIDER);
	m_slidNoiseLevel.SetPos(CONST_MIN_SLIDER);
	GetDlgItem(IDC_STATIC_NOISE_1)->EnableWindow(FALSE);
	GetDlgItem(IDC_SLIDER_NOISE)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_NOISE_TEXT0)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_NOISE_2)->EnableWindow(FALSE);
	GetDlgItem(IDC_SLIDER_NOISE2)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_NOISE_TEXT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_DNRSET)->EnableWindow(FALSE);
	GetDlgItem(IDC_SLIDER_DNRSET)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_DNRSET_TEXT)->EnableWindow(FALSE);

	InsertString(m_cboAutoContrast, 0, IDS_CONFIG_CLOSE);
	InsertString(m_cboAutoContrast, 1, IDS_CFG_SO_RUN);
	m_cboAutoContrast.SetCurSel(0);
	InsertString(m_cboSencitivityAutoContrast, 0, IDS_VCA_SENS_LOW);
	InsertString(m_cboSencitivityAutoContrast, 1, IDS_VCA_SENS_MIDDLE);
	InsertString(m_cboSencitivityAutoContrast, 2, IDS_VCA_SENS_HIGH);
	m_cboSencitivityAutoContrast.SetCurSel(0);

	InsertString(m_cboLightness, 0, IDS_CONFIG_CLOSE);
	InsertString(m_cboLightness, 1, IDS_DOME_GRADE1);
	InsertString(m_cboLightness, 2, IDS_DOME_GRADE2);
	InsertString(m_cboLightness, 3, IDS_DOME_GRADE3);
	m_cboLightness.SetCurSel(0);

	InsertString(m_cboNightStrength, 0, IDS_CONFIG_CLOSE);
	InsertString(m_cboNightStrength, 1, IDS_CFG_SO_RUN);
	m_cboNightStrength.SetCurSel(0);

	InsertString(m_cboVidoeFrost, 0, IDS_CONFIG_CLOSE);
	InsertString(m_cboVidoeFrost, 1, IDS_CFG_SO_RUN);
	m_cboVidoeFrost.SetCurSel(0);

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
}

void CLS_DomeHDParam3::UpdateDomeHDPara(int _iTemplateID, int _iType)
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error(%d)", m_iLogonID, GetLastError());
		return;
	}

	int iTempID = m_cboTempleID.GetCurSel();
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
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetHDTimeRangeParam (%d, %d), error (%d)"
			, m_iLogonID, m_iChannelNo, GetLastError());
	}
	else
	{
		if(bGetTemplatePara || _iType == HD_PARA_GAMMA)
		{
			int iImageStyle = pb.iParam1[HD_PARA_GAMMA];
			if (iImageStyle < 0 || iImageStyle > 4)
			{
				m_cboImageStyle.SetCurSel(0);
			}
			else
			{
				m_cboImageStyle.SetCurSel(iImageStyle);
			}
		}

		//19-使用场景：0 室内；1室外
		if(bGetTemplatePara || _iType == HD_PARA_INOUT_DOOR_MODE)
		{
			m_cboInOutDoorMode.SetCurSel(pb.iParam1[HD_PARA_INOUT_DOOR_MODE]);
		}

		//24-透雾
		if(bGetTemplatePara || _iType == HD_PARA_THROUGH_MIST)
		{
			int iTemp = pb.iParam1[HD_PARA_THROUGH_MIST];
			m_cboThroughMist.SetCurSel(iTemp);	
			if (iTemp == 0)//关闭
			{
				GetDlgItem(IDC_STATIC_MIST_STRENGTH)->EnableWindow(FALSE);
				GetDlgItem(IDC_SLIDER_MIST_STRENGTH)->EnableWindow(FALSE);
				GetDlgItem(IDC_STATIC_MIST_STRENGTH_TEXT)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_PARAM3_SET_THROUGH_MIST)->EnableWindow(FALSE);
			}
			else
			{
				GetDlgItem(IDC_STATIC_MIST_STRENGTH)->EnableWindow(TRUE);
				GetDlgItem(IDC_SLIDER_MIST_STRENGTH)->EnableWindow(TRUE);
				GetDlgItem(IDC_STATIC_MIST_STRENGTH_TEXT)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_PARAM3_SET_THROUGH_MIST)->EnableWindow(TRUE);	
			}
			int iStrength = pb.iParam3[HD_PARA_THROUGH_MIST];
			m_slidMistStrength.SetPos(iStrength);
			SetDlgItemInt(IDC_STATIC_MIST_STRENGTH_TEXT, iStrength);

		}

		//17-强光抑制
		if(bGetTemplatePara || _iType == HD_PARA_STRONG_LIGHT)
		{
			m_cboStrongLight.SetCurSel(pb.iParam1[HD_PARA_STRONG_LIGHT]);
			if (pb.iParam1[HD_PARA_STRONG_LIGHT] == 1)
			{
				GetDlgItem(IDC_STATIC_BIG_LIGHT_TEXT)->EnableWindow(TRUE);
				GetDlgItem(IDC_SLIDER_BIG_LIGHT)->EnableWindow(TRUE);
				GetDlgItem(IDC_STATIC_BIG_LIGHT_RANGE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_PARAM3_SET_LIGHT_INHIBITION)->EnableWindow(TRUE);
			}
			else
			{	//关闭的情况下写入默认值
				GetDlgItem(IDC_STATIC_BIG_LIGHT_TEXT)->EnableWindow(FALSE);
				GetDlgItem(IDC_SLIDER_BIG_LIGHT)->EnableWindow(FALSE);
				GetDlgItem(IDC_STATIC_BIG_LIGHT_RANGE)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_PARAM3_SET_LIGHT_INHIBITION)->EnableWindow(FALSE);
			}
			int iStrongLightPos = pb.iParam2[HD_PARA_STRONG_LIGHT];
			m_slidBigLight.SetPos(iStrongLightPos);
			SetDlgItemInt(IDC_STATIC_BIG_LIGHT_RANGE, iStrongLightPos);	
		}

		//8-降噪调节
		if(bGetTemplatePara || _iType == HD_PARA_DNR)
		{
			int iEnable = pb.iAutoEnable[HD_PARA_DNR];
			int iValue = pb.iParam1[HD_PARA_DNR];
			int iValue2 = pb.iParam2[HD_PARA_DNR];
			int iMode = 0;
			if (iEnable == 1)											//普通模式
			{
				if(iValue == 0)											//表示关闭
				{
					m_slidTimeDomainNoise.SetPos(CONST_MIN_SLIDER + 1);
					m_slidSpaceDomainNoise.SetPos(CONST_MIN_SLIDER + 1);
					m_slidNoiseLevel.SetPos(CONST_MIN_SLIDER + 1);
					SetDlgItemInt(IDC_STATIC_DNRSET_TEXT, CONST_MIN_SLIDER + 1);
					SetDlgItemInt(IDC_STATIC_NOISE_TEXT0, CONST_MIN_SLIDER + 1);
					SetDlgItemInt(IDC_STATIC_NOISE_TEXT2, CONST_MIN_SLIDER + 1);
					GetDlgItem(IDC_STATIC_NOISE_1)->EnableWindow(FALSE);
					GetDlgItem(IDC_SLIDER_NOISE)->EnableWindow(FALSE);
					GetDlgItem(IDC_STATIC_NOISE_TEXT0)->EnableWindow(FALSE);
					GetDlgItem(IDC_STATIC_NOISE_2)->EnableWindow(FALSE);
					GetDlgItem(IDC_SLIDER_NOISE2)->EnableWindow(FALSE);
					GetDlgItem(IDC_STATIC_NOISE_TEXT2)->EnableWindow(FALSE);
					GetDlgItem(IDC_STATIC_DNRSET)->EnableWindow(FALSE);
					GetDlgItem(IDC_SLIDER_DNRSET)->EnableWindow(FALSE);
					GetDlgItem(IDC_STATIC_DNRSET_TEXT)->EnableWindow(FALSE);
					GetDlgItem(IDC_BTN_PARAM3_SET_DNR)->EnableWindow(FALSE);
				}
				else
				{
					iMode = 1;
					m_slidTimeDomainNoise.SetPos(CONST_MIN_SLIDER + 1);
					m_slidSpaceDomainNoise.SetPos(CONST_MIN_SLIDER + 1);
					GetDlgItem(IDC_STATIC_NOISE_1)->EnableWindow(FALSE);
					GetDlgItem(IDC_SLIDER_NOISE)->EnableWindow(FALSE);
					GetDlgItem(IDC_STATIC_NOISE_TEXT0)->EnableWindow(FALSE);
					GetDlgItem(IDC_STATIC_NOISE_2)->EnableWindow(FALSE);
					GetDlgItem(IDC_SLIDER_NOISE2)->EnableWindow(FALSE);
					GetDlgItem(IDC_STATIC_NOISE_TEXT2)->EnableWindow(FALSE);
					GetDlgItem(IDC_STATIC_DNRSET)->EnableWindow(TRUE);
					GetDlgItem(IDC_SLIDER_DNRSET)->EnableWindow(TRUE);
					GetDlgItem(IDC_STATIC_DNRSET_TEXT)->EnableWindow(TRUE);
					GetDlgItem(IDC_BTN_PARAM3_SET_DNR)->EnableWindow(TRUE);
					SetDlgItemInt(IDC_STATIC_DNRSET_TEXT, iValue);
					m_slidNoiseLevel.SetPos(iValue);
				}
			}
			else if (iEnable == 2)										//专家模式
			{
				iMode = 2;
				m_slidNoiseLevel.SetPos(CONST_MIN_SLIDER + 1);
				GetDlgItem(IDC_STATIC_NOISE_1)->EnableWindow(TRUE);
				GetDlgItem(IDC_SLIDER_NOISE)->EnableWindow(TRUE);
				GetDlgItem(IDC_STATIC_NOISE_TEXT0)->EnableWindow(TRUE);
				GetDlgItem(IDC_STATIC_NOISE_2)->EnableWindow(TRUE);
				GetDlgItem(IDC_SLIDER_NOISE2)->EnableWindow(TRUE);
				GetDlgItem(IDC_STATIC_NOISE_TEXT2)->EnableWindow(TRUE);
				GetDlgItem(IDC_STATIC_DNRSET)->EnableWindow(FALSE);
				GetDlgItem(IDC_SLIDER_DNRSET)->EnableWindow(FALSE);
				GetDlgItem(IDC_STATIC_DNRSET_TEXT)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_PARAM3_SET_DNR)->EnableWindow(TRUE);
				m_slidTimeDomainNoise.SetPos(iValue);
				m_slidSpaceDomainNoise.SetPos(iValue2);
				SetDlgItemInt(IDC_STATIC_NOISE_TEXT0, iValue);
				SetDlgItemInt(IDC_STATIC_NOISE_TEXT2, iValue2);
			}
			else
			{
				m_slidTimeDomainNoise.SetPos(CONST_MIN_SLIDER + 1);
				m_slidSpaceDomainNoise.SetPos(CONST_MIN_SLIDER + 1);
				m_slidNoiseLevel.SetPos(CONST_MIN_SLIDER + 1);
				SetDlgItemInt(IDC_STATIC_DNRSET_TEXT, CONST_MIN_SLIDER + 1);
				SetDlgItemInt(IDC_STATIC_NOISE_TEXT0, CONST_MIN_SLIDER + 1);
				SetDlgItemInt(IDC_STATIC_NOISE_TEXT2, CONST_MIN_SLIDER + 1);
				GetDlgItem(IDC_STATIC_NOISE_1)->EnableWindow(FALSE);
				GetDlgItem(IDC_SLIDER_NOISE)->EnableWindow(FALSE);
				GetDlgItem(IDC_STATIC_NOISE_TEXT0)->EnableWindow(FALSE);
				GetDlgItem(IDC_STATIC_NOISE_2)->EnableWindow(FALSE);
				GetDlgItem(IDC_SLIDER_NOISE2)->EnableWindow(FALSE);
				GetDlgItem(IDC_STATIC_NOISE_TEXT2)->EnableWindow(FALSE);
				GetDlgItem(IDC_STATIC_DNRSET)->EnableWindow(FALSE);
				GetDlgItem(IDC_SLIDER_DNRSET)->EnableWindow(FALSE);
				GetDlgItem(IDC_STATIC_DNRSET_TEXT)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_PARAM3_SET_DNR)->EnableWindow(FALSE);
			}
			m_cboDNR.SetCurSel(iMode);
		}
		
		//自动对比度	
		if(bGetTemplatePara || _iType == HD_PARA_AUTO_CONTRAST)
		{
			int iAutoContrast = pb.iParam1[HD_PARA_AUTO_CONTRAST];
			m_cboAutoContrast.SetCurSel(iAutoContrast);
			m_cboSencitivityAutoContrast.SetCurSel(pb.iParam2[HD_PARA_AUTO_CONTRAST]);
		}
		
		//低照色彩抑制
		if(bGetTemplatePara || _iType == HD_PARA_LIGHTLESS)
		{
			int iLightness = pb.iParam1[HD_PARA_LIGHTLESS];
			m_cboLightness.SetCurSel(iLightness);
		}

		//夜视强化
		if(bGetTemplatePara || _iType == HD_PARA_NIGHT_STRENTH)
		{
			int iNightStrength = pb.iParam1[HD_PARA_NIGHT_STRENTH];
			m_cboNightStrength.SetCurSel(iNightStrength);
		}

		//图像冻结
		if(bGetTemplatePara || _iType == HD_PARA_VIDEO_FROST)
		{
			int iVideoFrost = pb.iParam1[HD_PARA_VIDEO_FROST];
			m_cboVidoeFrost.SetCurSel(iVideoFrost);
		}

		AddLog(LOG_TYPE_SUCC,"","NetClient_GetHDTimeRangeParam");
	}
}

int CLS_DomeHDParam3::SetDomeHDPara(int _iType, int _iAutoEnable, int _iParam1, int _iParam2, int _iParam3, int _iParam4)
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d),error(%d)", m_iLogonID, GetLastError());
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
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetHDTimeRangeParam (%d, %d),error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
		return -1;
	}

	AddLog(LOG_TYPE_SUCC,"","NetClient_SetHDTimeRangeParam (%d, %d)", m_iLogonID, m_iChannelNo);
	return 0;
}

void CLS_DomeHDParam3::OnCbnSelchangeCboVideoStyle()
{
	// TODO: Add your control notification handler code here
	int iImageStyle = m_cboImageStyle.GetCurSel();
	SetDomeHDPara(HD_PARA_GAMMA, 1, iImageStyle, 255, 0, 0);
}

void CLS_DomeHDParam3::OnCbnSelchangeComboInoutdoorMode()
{
	// TODO: Add your control notification handler code here
	int iValue = m_cboInOutDoorMode.GetCurSel();
	SetDomeHDPara(HD_PARA_INOUT_DOOR_MODE, 1, iValue, 0, 0, 0);
}

void CLS_DomeHDParam3::OnCbnSelchangeCboThroughMist()
{
	int iStrength = m_slidMistStrength.GetPos();
	// TODO:透雾
	if (m_cboThroughMist.GetCurSel() == 1)														//开启
	{
		GetDlgItem(IDC_STATIC_MIST_STRENGTH)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLIDER_MIST_STRENGTH)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_MIST_STRENGTH_TEXT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PARAM3_SET_THROUGH_MIST)->EnableWindow(TRUE);
	}
	else																						//关闭
	{
		GetDlgItem(IDC_STATIC_MIST_STRENGTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_MIST_STRENGTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_MIST_STRENGTH_TEXT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PARAM3_SET_THROUGH_MIST)->EnableWindow(FALSE);						
	}
	SetDomeHDPara(HD_PARA_THROUGH_MIST, 1, m_cboThroughMist.GetCurSel(), 0, iStrength, 0);
}

void CLS_DomeHDParam3::OnNMCustomdrawSliderMistStrength(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	int iPos = m_slidMistStrength.GetPos();
	SetDlgItemInt(IDC_STATIC_MIST_STRENGTH_TEXT, iPos);

	*pResult = 0;
}

//设置透雾
void CLS_DomeHDParam3::OnBnClickedBtnParam3SetThroughMist()
{
	int iStrength = m_slidMistStrength.GetPos();
	SetDomeHDPara(HD_PARA_THROUGH_MIST, 1, m_cboThroughMist.GetCurSel(), 0, iStrength, 0);
}

void CLS_DomeHDParam3::OnCbnSelchangeCboStronglight()
{
	// TODO: 强光抑制
	int iType = m_cboStrongLight.GetCurSel();
	if (0 == iType)
	{
		GetDlgItem(IDC_STATIC_BIG_LIGHT_TEXT)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_BIG_LIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_BIG_LIGHT_RANGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PARAM3_SET_LIGHT_INHIBITION)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_BIG_LIGHT_TEXT)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLIDER_BIG_LIGHT)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_BIG_LIGHT_RANGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PARAM3_SET_LIGHT_INHIBITION)->EnableWindow(TRUE);
	}
	int iStrongth = m_slidBigLight.GetPos();
	SetDomeHDPara(HD_PARA_STRONG_LIGHT, 1, iType, iStrongth, 0, 0);
}

//强光抑制设置按钮
void CLS_DomeHDParam3::OnBnClickedBtnParam3SetLightInhibition()
{
	// TODO: 在此添加控件通知处理程序代码
 	int iType = m_cboStrongLight.GetCurSel();
	int iStrongth = m_slidBigLight.GetPos();
	SetDomeHDPara(HD_PARA_STRONG_LIGHT, 1, iType, iStrongth, 0, 0);
}

void CLS_DomeHDParam3::OnNMCustomdrawSliderBigLight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	int iPos = m_slidBigLight.GetPos();
	SetDlgItemInt(IDC_STATIC_BIG_LIGHT_RANGE,iPos);

	*pResult = 0;
}

void CLS_DomeHDParam3::OnCbnSelchangeComboDnr()
{
	// TODO: Add your control notification handler code here
	int iMode=m_cboDNR.GetCurSel();
	int iValue1 = 0;
	int iValue2 = 0;

	if (iMode == 0)//关闭
	{
 		m_slidTimeDomainNoise.SetPos(CONST_MIN_SLIDER +1);
 		m_slidSpaceDomainNoise.SetPos(CONST_MIN_SLIDER +1);
 		m_slidNoiseLevel.SetPos(CONST_MIN_SLIDER +1);
 		SetDlgItemInt(IDC_STATIC_DNRSET_TEXT, CONST_MIN_SLIDER + 1);
 		SetDlgItemInt(IDC_STATIC_NOISE_TEXT0, CONST_MIN_SLIDER + 1);
 		SetDlgItemInt(IDC_STATIC_NOISE_TEXT2, CONST_MIN_SLIDER + 1);
		GetDlgItem(IDC_STATIC_NOISE_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_NOISE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_NOISE_TEXT0)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_NOISE_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_NOISE2)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_NOISE_TEXT2)->EnableWindow(FALSE);

		GetDlgItem(IDC_STATIC_DNRSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_DNRSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DNRSET_TEXT)->EnableWindow(FALSE);

		GetDlgItem(IDC_BTN_PARAM3_SET_DNR)->EnableWindow(FALSE);

		SetDomeHDPara(HD_PARA_DNR, 1, 0, 0, 0, 0);
	}
	else if (iMode == 1)//普通模式
	{
 		m_slidTimeDomainNoise.SetPos(CONST_MIN_SLIDER +1);
 		m_slidSpaceDomainNoise.SetPos(CONST_MIN_SLIDER +1);
 		SetDlgItemInt(IDC_STATIC_NOISE_TEXT0, CONST_MIN_SLIDER +1);
 		SetDlgItemInt(IDC_STATIC_NOISE_TEXT2, CONST_MIN_SLIDER +1);
		GetDlgItem(IDC_STATIC_NOISE_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_NOISE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_NOISE_TEXT0)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_NOISE_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_NOISE2)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_NOISE_TEXT2)->EnableWindow(FALSE);

		GetDlgItem(IDC_STATIC_DNRSET)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLIDER_DNRSET)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_DNRSET_TEXT)->EnableWindow(TRUE);

		GetDlgItem(IDC_BTN_PARAM3_SET_DNR)->EnableWindow(TRUE);

		iValue1 = m_slidNoiseLevel.GetPos();
		SetDomeHDPara(HD_PARA_DNR, 1, iValue1, 0, 0, 0);
	}
	else if (iMode == 2)//专家模式
	{
		m_slidNoiseLevel.SetPos(CONST_MIN_SLIDER +1);
		SetDlgItemInt(IDC_STATIC_DNRSET_TEXT, CONST_MIN_SLIDER +1);
		GetDlgItem(IDC_STATIC_NOISE_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLIDER_NOISE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_NOISE_TEXT0)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_NOISE_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLIDER_NOISE2)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_NOISE_TEXT2)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_DNRSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_DNRSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DNRSET_TEXT)->EnableWindow(FALSE);

		GetDlgItem(IDC_BTN_PARAM3_SET_DNR)->EnableWindow(TRUE);

 		iValue1 = m_slidTimeDomainNoise.GetPos();
 		iValue2 = m_slidSpaceDomainNoise.GetPos();
		SetDomeHDPara(HD_PARA_DNR, 2, iValue1, iValue2, 0, 0);
	}
}

//设置数字降噪按钮
void CLS_DomeHDParam3::OnBnClickedBtnParam3SetDnr()
{
	int iMode=m_cboDNR.GetCurSel();
	int iValue1 = 0;
	int iValue2 = 0;

	if (iMode == 0)//关闭
	{
		m_slidTimeDomainNoise.SetPos(CONST_MIN_SLIDER +1);
		m_slidSpaceDomainNoise.SetPos(CONST_MIN_SLIDER +1);
		m_slidNoiseLevel.SetPos(CONST_MIN_SLIDER +1);
		SetDlgItemInt(IDC_STATIC_DNRSET_TEXT, CONST_MIN_SLIDER + 1);
		SetDlgItemInt(IDC_STATIC_NOISE_TEXT0, CONST_MIN_SLIDER + 1);
		SetDlgItemInt(IDC_STATIC_NOISE_TEXT2, CONST_MIN_SLIDER + 1);

		SetDomeHDPara(HD_PARA_DNR, 1, 0, 0, 0, 0);
	}
	else if (iMode == 1)//普通模式
	{
		m_slidTimeDomainNoise.SetPos(CONST_MIN_SLIDER +1);
		m_slidSpaceDomainNoise.SetPos(CONST_MIN_SLIDER +1);
		SetDlgItemInt(IDC_STATIC_NOISE_TEXT0, CONST_MIN_SLIDER +1);
		SetDlgItemInt(IDC_STATIC_NOISE_TEXT2, CONST_MIN_SLIDER +1);

		iValue1 = m_slidNoiseLevel.GetPos();
		SetDomeHDPara(HD_PARA_DNR, 1, iValue1, 0, 0, 0);
	}
	else if (iMode == 2)//专家模式
	{
		m_slidNoiseLevel.SetPos(CONST_MIN_SLIDER +1);
		SetDlgItemInt(IDC_STATIC_DNRSET_TEXT, CONST_MIN_SLIDER +1);

		iValue1 = m_slidTimeDomainNoise.GetPos();
		iValue2 = m_slidSpaceDomainNoise.GetPos();
		SetDomeHDPara(HD_PARA_DNR, 2, iValue1, iValue2, 0, 0);
	}
}

void CLS_DomeHDParam3::OnNMCustomdrawSliderNoiseLevel(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 降噪等级
	int iPos = m_slidNoiseLevel.GetPos();
	SetDlgItemInt(IDC_STATIC_DNRSET_TEXT, iPos);

	*pResult = 0;
}

void CLS_DomeHDParam3::OnNMCustomdrawSliderTimeDomainNoise(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 时域降噪等级
	int iPos = m_slidTimeDomainNoise.GetPos();
	SetDlgItemInt(IDC_STATIC_NOISE_TEXT0, iPos);

	*pResult = 0;
}

void CLS_DomeHDParam3::OnNMCustomdrawSliderSpaceDomainNoise(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 空域降噪等级
	int iPos = m_slidSpaceDomainNoise.GetPos();
	SetDlgItemInt(IDC_STATIC_NOISE_TEXT2, iPos);

	*pResult = 0;
}

void CLS_DomeHDParam3::OnCbnSelchangeCboAutoContrast()
{
	// TODO:自动对比度 Param1 1开启，0关闭
	int iIndex = m_cboAutoContrast.GetCurSel();
	if(iIndex == 0)
	{
		SetDomeHDPara(HD_PARA_AUTO_CONTRAST, 1, 0, 0, 0, 0);
	}
	else
	{
		SetDomeHDPara(HD_PARA_AUTO_CONTRAST, 1, 1, m_cboSencitivityAutoContrast.GetCurSel(), 0, 0);

		m_cboThroughMist.SetCurSel(0);//20140410 自动对比度与透雾互斥
	}
}

void CLS_DomeHDParam3::OnCbnSelchangeComboSencitivityAutoContrast()
{
	// TODO: Add your control notification handler code here
	//开启自动对比后有低中高三种等级
	SetDomeHDPara(HD_PARA_AUTO_CONTRAST, 1, 1, m_cboSencitivityAutoContrast.GetCurSel(), 0, 0);
}

void CLS_DomeHDParam3::OnCbnSelchangeCboLightless()
{
	// TODO:低照色彩抑制  0-关闭、1-1级、2-2级、3-3级
	SetDomeHDPara(HD_PARA_LIGHTLESS, 1, m_cboLightness.GetCurSel(), 0, 0, 0);
}

void CLS_DomeHDParam3::OnCbnSelchangeCboNightStrenth()
{
	// TODO:夜视强化   1代表开启，0代表关闭
	SetDomeHDPara(HD_PARA_NIGHT_STRENTH, 1, m_cboNightStrength.GetCurSel(), 0, 0, 0);
}

void CLS_DomeHDParam3::OnCbnSelchangeCboVideoFrost()
{
	// TODO: 图像冻结
	SetDomeHDPara(HD_PARA_VIDEO_FROST, 1, m_cboVidoeFrost.GetCurSel(), 0, 0, 0);
}


void CLS_DomeHDParam3::OnCbnSelchangeComboCurrentTemp()
{
	// TODO: 选中当前模板并获取相应参数
	UpdateDomeHDPara();
}
