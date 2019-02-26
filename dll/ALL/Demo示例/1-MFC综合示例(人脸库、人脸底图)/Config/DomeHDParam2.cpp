// DomeHDParam2.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "DomeHDParam2.h"

#define WIDE_DY_CLOSE						0
#define WIDE_DY_OPEN						1	
#define WIDE_DY_VISUAL_ENHANCE				2
#define WIDE_DY_HANDLE						0
#define WIDE_DY_AUTO						1
#define MAX_WHITEBALANCE_OPERATYPE		    20
#define HD_MODE_INDEX0                      0
#define HD_MODE_IMMEDIATELY                 255
const int CONST_iSemiautomaticWhiteBalanceIndex = 1;//半自动白平衡的COMBOX值索引
const int CONST_iManualWhiteBalanceIndex = 19;//手动白平衡的COMBOX值索引
// CLS_DomeHDParam2 dialog

IMPLEMENT_DYNAMIC(CLS_DomeHDParam2, CDialog)

CLS_DomeHDParam2::CLS_DomeHDParam2(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DomeHDParam2::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNO = -1;
	m_pDlgVideoView = NULL;
}

CLS_DomeHDParam2::~CLS_DomeHDParam2()
{
}

void CLS_DomeHDParam2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CURRENT_TEMP, m_cboTempleID);
	DDX_Control(pDX, IDC_COMBO_FOCUS_MODE, m_cmbFocusMode);
	DDX_Control(pDX, IDC_COMBO_FOCUSTYPE, m_cboFocusType);
	DDX_Control(pDX, IDC_COMBO_MIN_FOCUS_DIS, m_cboMinFocusDst);
	DDX_Control(pDX, IDC_COMBO_SMARTIR, m_cboSmartIR);
	DDX_Control(pDX, IDC_COMBO_DAYNIGHT, m_cboDayNight);
	DDX_Control(pDX, IDC_COMBO_SENCITIVITY, m_cboSencitivity);
	DDX_Control(pDX, IDC_COMBO_INFRARED, m_cboInfrared);
	DDX_Control(pDX, IDC_COMBO_BACKLIGHT, m_cboBackLight);
	DDX_Control(pDX, IDC_COMBO_RANGE, m_cboBackLightRange);
	DDX_Control(pDX, IDC_COMBO_WIDE_DYNAMIC, m_cboWideDynamic);
	DDX_Control(pDX, IDC_COMBO_SENCITIVITY_W, m_cboSencitivityW);
	DDX_Control(pDX, IDC_COMBO_WHITEBALANCE, m_cboWhiteBalance);
	DDX_Control(pDX, IDC_SLIDER_RED, m_slidRed);
	DDX_Control(pDX, IDC_SLIDER_BLUE, m_slidBlue);
	DDX_Control(pDX, IDC_BTN_PARAM2_SET_WHITE_BALANCE, m_btnSetWhiteBalance);
	DDX_Control(pDX, IDC_SLIDER_GREEN, m_slidGreen);
	DDX_Control(pDX, IDC_STC_WIDE_SENSITY_DEGREE, m_stcWideSensityDegree);
	DDX_Control(pDX, IDC_SLD_PARAM2_WIDE_SENSITY_DEGREE, m_sldWideSensityDegree);
	DDX_Control(pDX, IDC_EDIT_BACKLIGHT_AREA, m_edtBackLightArea);
}


BEGIN_MESSAGE_MAP(CLS_DomeHDParam2, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_CURRENT_TEMP, &CLS_DomeHDParam2::OnCbnSelchangeComboCurrentTemp)
	ON_CBN_SELCHANGE(IDC_COMBO_FOCUS_MODE, &CLS_DomeHDParam2::OnCbnSelchangeComboFocusMode)
	ON_CBN_SELCHANGE(IDC_COMBO_FOCUSTYPE, &CLS_DomeHDParam2::OnCbnSelchangeComboFocustype)
	ON_CBN_SELCHANGE(IDC_COMBO_MIN_FOCUS_DIS, &CLS_DomeHDParam2::OnCbnSelchangeComboMinFocusDis)
	ON_CBN_SELCHANGE(IDC_COMBO_SMARTIR, &CLS_DomeHDParam2::OnCbnSelchangeComboSmartir)
	ON_CBN_SELCHANGE(IDC_COMBO_DAYNIGHT, &CLS_DomeHDParam2::OnCbnSelchangeComboDaynight)
	ON_CBN_SELCHANGE(IDC_COMBO_SENCITIVITY, &CLS_DomeHDParam2::OnCbnSelchangeComboSencitivity)
	ON_CBN_SELCHANGE(IDC_COMBO_INFRARED, &CLS_DomeHDParam2::OnCbnSelchangeComboInfrared)
	ON_CBN_SELCHANGE(IDC_COMBO_BACKLIGHT, &CLS_DomeHDParam2::OnCbnSelchangeComboBacklight)
	ON_CBN_SELCHANGE(IDC_COMBO_RANGE, &CLS_DomeHDParam2::OnCbnSelchangeComboRange)
	ON_CBN_SELCHANGE(IDC_COMBO_WIDE_DYNAMIC, &CLS_DomeHDParam2::OnCbnSelchangeComboWideDynamic)
	ON_CBN_SELCHANGE(IDC_COMBO_SENCITIVITY_W, &CLS_DomeHDParam2::OnCbnSelchangeComboSencitivityW)
	ON_CBN_SELCHANGE(IDC_COMBO_WHITEBALANCE, &CLS_DomeHDParam2::OnCbnSelchangeComboWhitebalance)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_RED, &CLS_DomeHDParam2::OnNMCustomdrawSliderRed)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BLUE, &CLS_DomeHDParam2::OnNMCustomdrawSliderBlue)
	ON_BN_CLICKED(IDC_BTN_PARAM2_SET_WHITE_BALANCE, &CLS_DomeHDParam2::OnBnClickedBtnParam2SetWhiteBalance)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_GREEN, &CLS_DomeHDParam2::OnNMCustomdrawSliderGreen)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_PARAM2_WIDE_SENSITY_DEGREE, &CLS_DomeHDParam2::OnNMCustomdrawSldParam2WideSensityDegree)
	ON_BN_CLICKED(IDC_BTN_PARAM2_SET_WIDE_SENSITY_DEGREE, &CLS_DomeHDParam2::OnBnClickedBtnParam2SetWideSensityDegree)
	ON_BN_CLICKED(IDC_BUTTON_BACKLIGHT_DRAW, &CLS_DomeHDParam2::OnBnClickedButtonBacklightDraw)
END_MESSAGE_MAP()


// CLS_DomeHDParam2 message handlers

BOOL CLS_DomeHDParam2::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	//UI_UpdateDialogText();
	//UpdateDomeHDPara();

	m_edtBackLightArea.SetLimitText(LEN_256);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_DomeHDParam2::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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

void CLS_DomeHDParam2::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialogText();
	UpdateDomeHDPara();
}

void CLS_DomeHDParam2::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
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

void CLS_DomeHDParam2::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_STATIC_CURRENT_Template, IDS_HD_CUR_TEMPLATE);
	SetDlgItemTextEx(IDC_STATIC_FOCUS, IDS_PREVIEW_FOCUS);
	SetDlgItemTextEx(IDC_STATIC_FOCUS_MODE, IDS_STATIC_FOCUS_MODE);
	SetDlgItemTextEx(IDC_STATIC_FOCUSTYPE, IDS_DOME_HD_FOCUSTYPE);
	SetDlgItemTextEx(IDC_STATIC_MIN_FOCUS_DIS, IDS_DOME_HD_MIN_FOCUS_DIS);
	SetDlgItemTextEx(IDC_STATIC_VIDEO_DAYNIGHT, IDS_DOME_HD_VIDEO_DAYNIGHT);
	SetDlgItemTextEx(IDC_STATIC_DAYNIGHT, IDS_STATIC_DAYNIGHT);
	SetDlgItemTextEx(IDC_STATIC_SENCITIVITY, IDS_CONFIG_ITS_ILLEGALPARK_SENSITIVITY);
	SetDlgItemTextEx(IDC_STATIC_INFRARED, IDS_DOME_HD_INFRARED);
	SetDlgItemTextEx(IDC_STATIC_HD_BKLIGHT, IDS_DOME_HD_BKLIGHT);
	SetDlgItemTextEx(IDC_STATIC_BACKLIGHT, IDS_CONFIG_HD_APHELIOTROPICENABLE);
	SetDlgItemTextEx(IDC_STATIC_RANGE, IDS_DOME_HD_RANGE);
	SetDlgItemTextEx(IDC_STATIC_WIDE_DYNAMIC, IDS_CONFIG_HD_WIDTHDYNAMICENABLE);
	SetDlgItemTextEx(IDC_STATIC_SENCITIVITY_W, IDS_STATIC_SENCITIVITY_W);
	SetDlgItemTextEx(IDC_STATIC_HD_BALANCE, IDS_STATIC_WHITE_BALANCE);
	SetDlgItemTextEx(IDC_STATIC_WHITE_BALANCE, IDS_HD_WHITE_BALANCE);
	SetDlgItemTextEx(IDC_BTN_PARAM2_SET_WHITE_BALANCE, IDS_ITS_SET_DENOISE);
	SetDlgItemTextEx(IDC_BTN_PARAM2_SET_WIDE_SENSITY_DEGREE, IDS_ITS_SET_DENOISE);
	SetDlgItemTextEx(IDC_STC_WIDE_SENSITY_DEGREE, IDS_WIDE_SENSITY_DEGREE);
	SetDlgItemTextEx(IDC_BUTTON_BACKLIGHT_DRAW, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_STATIC_BACKLIGHT_AREA, IDS_DOME_HD_BACKLIGHT);

	InsertString(m_cmbFocusMode, 0, IDS_DOME_AUTO);
	InsertString(m_cmbFocusMode, 1, IDS_DOME_HANDLE);
	InsertString(m_cmbFocusMode, 2, IDS_DOME_HD_STRIKE);
	m_cmbFocusMode.SetCurSel(0);

	InsertString(m_cboFocusType, 0, IDS_CONFIG_CLOSE);
	InsertString(m_cboFocusType, 1, IDS_DOME_LOWLIGHT);
	InsertString(m_cboFocusType, 2, IDS_DOME_COMPLEX);
	InsertString(m_cboFocusType, 3, IDS_DOME_POINGLIGHT);
	m_cboFocusType.SetCurSel(0);

	m_cboMinFocusDst.ResetContent();
	//最小焦距距离10cm、50cm、1.0m、1.5m、3.0m、6.0m、无穷远（100m）
	int iMinFocusDst[] = {10, 50, 100, 150, 300, 600, 10000};
	CString cstrMinFocusDst[] = {"10cm", "50cm", "1.0m", "1.5m", "3.0m", "6.0m", "100m"};
	int iCount = sizeof(cstrMinFocusDst)/sizeof(CString);
	for (int i=0; i<iCount; i++)
	{
		m_cboMinFocusDst.InsertString(i, cstrMinFocusDst[i]);
		m_cboMinFocusDst.SetItemData(i,iMinFocusDst[i]);
	}
	m_cboMinFocusDst.SetCurSel(0);

	InsertString(m_cboSmartIR, 0, IDS_CONFIG_CLOSE);
	InsertString(m_cboSmartIR, 1, IDS_CFG_SO_RUN);
	m_cboSmartIR.SetCurSel(0);

	InsertString(m_cboDayNight, 0, IDS_DOME_AUTO);
	InsertString(m_cboDayNight, 1, IDS_ADV_CHANNEL_NIGHT);
	InsertString(m_cboDayNight, 2, IDS_ADV_CHANNEL_DAYTIME);
	m_cboDayNight.SetCurSel(0);

	InsertString(m_cboSencitivity, 0, IDS_VCA_SENS_LOW);
	InsertString(m_cboSencitivity, 1, IDS_VCA_SENS_MIDDLE);
	InsertString(m_cboSencitivity, 2, IDS_VCA_SENS_HIGH);
	m_cboSencitivity.SetCurSel(0);

	InsertString(m_cboInfrared, 0, IDS_CONFIG_CLOSE);
	InsertString(m_cboInfrared, 1, IDS_CFG_SO_RUN);
	m_cboInfrared.SetCurSel(0);

	//背光补偿
	InsertString(m_cboBackLight, 0, IDS_CONFIG_CLOSE);
	InsertString(m_cboBackLight, 1, IDS_CFG_SO_RUN);
	m_cboBackLight.SetCurSel(0);

	InsertString(m_cboBackLightRange, 0, IDS_VCA_SENS_LOW);
	InsertString(m_cboBackLightRange, 1, IDS_VCA_SENS_MIDDLE);
	InsertString(m_cboBackLightRange, 2, IDS_VCA_SENS_HIGH);
	m_cboBackLightRange.SetCurSel(0);

	//超宽动态
	InsertString(m_cboWideDynamic, 0, IDS_CONFIG_CLOSE);
	InsertString(m_cboWideDynamic, 1, IDS_DOME_AUTO);
	InsertString(m_cboWideDynamic, 2, IDS_DOME_HANDLE);
	InsertString(m_cboWideDynamic, 3, IDS_VISUAL_ENHANCE);
	m_cboWideDynamic.SetCurSel(0);

	//宽动态等级
	InsertString(m_cboSencitivityW, 0, IDS_VCA_SENS_LOW);
	InsertString(m_cboSencitivityW, 1, IDS_VCA_SENS_MIDDLE);
	InsertString(m_cboSencitivityW, 2, IDS_VCA_SENS_HIGH);
	m_cboSencitivityW.SetCurSel(0);

	//白平衡
	//自动下代表不同的场景模式:
	//0-默认自动 1-晴天模式 2-日光灯模式 3-暖光灯模式 4-白炽灯模式 5-自然光模式 6-锁定白平衡
	//7-ATW 8-室内 9-室外 10-室外自动 11-钠灯自动 12-钠灯 13-钠灯室外自动 14-钠蒸汽等模式
	//15-汞蒸气灯模式 16-阴天 17-黄昏
	//手动下代表不同模式:0-半自动 1-纯手动
	CString strAutoTypes[MAX_WHITEBALANCE_OPERATYPE] = {GetTextEx(IDS_DOME_AUTO),
		GetTextEx(IDS_DOME_HD_STRIKE),
		GetTextEx(IDS_WHITEBALANCE_SUNNYDAY),
		GetTextEx(IDS_WHITEBALANCE_SUNLIGHT),
		GetTextEx(IDS_WHITEBALANCE_WARMLIGHT),
		GetTextEx(IDS_WHITEBALANCE_FILAMENT),
		GetTextEx(IDS_WHITEBALANCE_NATURELIGHT),
		GetTextEx(IDS_WHITEBALANCE_LOCKED),
		"ATW",
		GetTextEx(IDS_HD_MODE_INDOOR),
		GetTextEx(IDS_HD_MODE_OUTDOOR),
		GetTextEx(IDS_WHITEBALANCE_OUTDOOR_AUTO),
		GetTextEx(IDS_WHITEBALANCE_SODIUMLAMP_AUTO),
		GetTextEx(IDS_WHITEBALANCE_SODIUMLAMP),
		GetTextEx(IDS_WHITEBALANCE_SODIUMLAMP_OUTDOOR_AUTO),
		GetTextEx(IDS_WHITEBALANCE_SODIUMVAPORLAMP),
		GetTextEx(IDS_WHITEBALANCE_MERCURYVAPORLAMP),
		GetTextEx(IDS_WHITEBALANCE_CLOUDYDAY),
		GetTextEx(IDS_WHITEBALANCE_DUSK),
		GetTextEx(IDS_DOME_HANDLE)};
	m_cboWhiteBalance.ResetContent();
	for (int i=0; i<MAX_WHITEBALANCE_OPERATYPE; i++)
	{
		m_cboWhiteBalance.InsertString(i, strAutoTypes[i]);
	}
	m_cboWhiteBalance.SetItemData(0, 0);
	for (int j=1; j<MAX_WHITEBALANCE_OPERATYPE-2; j++)
	{
		m_cboWhiteBalance.SetItemData(j+1, j);
	}

	m_slidRed.SetRange(CONST_MIN_SLIDER, CONST_MAX_SLIDER);
	m_slidRed.SetPos(CONST_MIN_SLIDER);

	m_slidGreen.SetRange(CONST_MIN_SLIDER, CONST_MAX_SLIDER);
	m_slidGreen.SetPos(CONST_MIN_SLIDER);

	m_slidBlue.SetRange(CONST_MIN_SLIDER, CONST_MAX_SLIDER);
	m_slidBlue.SetPos(CONST_MIN_SLIDER);

	m_sldWideSensityDegree.SetRange(CONST_MIN_SLIDER, CONST_MAX_SLIDER);
	m_sldWideSensityDegree.SetPos(CONST_MIN_SLIDER);

	m_cboTempleID.ResetContent();
	CString cstrTamplateName;
	m_cboTempleID.SetItemData(m_cboTempleID.InsertString(HD_MODE_INDEX0,GetTextEx(IDS_HD_MODE_IMMEDIATELY)), HD_MODE_IMMEDIATELY);
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

void CLS_DomeHDParam2::UpdateDomeHDPara(int _iTemplateID, int _iType)
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
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetHDTimeRangeParam (%d, %d, %d), error(%d)"
			, m_iLogonID, m_iChannelNo, iTempID, GetLastError());
	}
	else
	{
		//20-聚焦模式
		if(bGetTemplatePara || _iType == HD_PARA_FOCUS_MODE)	
		{
			m_cmbFocusMode.SetCurSel(pb.iParam1[HD_PARA_FOCUS_MODE]);
		}

		//聚焦类型
		if(bGetTemplatePara || _iType == HD_PARA_FOCUS_TYPE)	
		{
			int iFocusType = pb.iParam1[HD_PARA_FOCUS_TYPE];
			m_cboFocusType.SetCurSel(iFocusType);
		}

		//21-最小聚焦距离
		if(bGetTemplatePara || _iType == HD_PARA_MIN_FOCUS_DISTANCE)	
		{
			int iMinFocusDst = 	pb.iParam1[HD_PARA_MIN_FOCUS_DISTANCE];
			int iCount = m_cboMinFocusDst.GetCount();
			for (int i=0; i<iCount; i++)
			{
				if (iMinFocusDst == m_cboMinFocusDst.GetItemData(i))
				{
					m_cboMinFocusDst.SetCurSel(i);
				}
			}
		}

		//SmartIR
		if(bGetTemplatePara || _iType == HD_PARA_SMARTIR)	
		{
			int iSmartIR = pb.iParam1[HD_PARA_SMARTIR];
			m_cboSmartIR.SetCurSel(iSmartIR);
		}

		//22-日夜模式
		if(bGetTemplatePara || _iType == HD_PARA_DAY_NIGHT)	
		{
			int iDayNigetMode = pb.iParam1[HD_PARA_DAY_NIGHT];
			int iSencitivity = pb.iParam2[HD_PARA_DAY_NIGHT];
			m_cboDayNight.SetCurSel(iDayNigetMode);
			if (iDayNigetMode == 0)
			{
				m_cboSencitivity.SetCurSel(iSencitivity);
			}
		}	

		//红外校正
		if(bGetTemplatePara || _iType == HD_PARA_INFRARED)	
		{
			int iInfrared = pb.iParam1[HD_PARA_INFRARED];
			m_cboInfrared.SetCurSel(iInfrared);
		}

		//2-背光补偿
		if(bGetTemplatePara || _iType == HD_PARA_BACK_LIGHT)	
		{
			int iBackLight = pb.iParam1[HD_PARA_BACK_LIGHT];
			if (iBackLight == 1)
			{
				GetDlgItem(IDC_STATIC_RANGE)->EnableWindow(TRUE);
				GetDlgItem(IDC_COMBO_RANGE)->EnableWindow(TRUE);
				int iBackLightRange = pb.iParam2[HD_PARA_BACK_LIGHT];
				if (iBackLightRange > 0)
				{
					iBackLightRange--;//LNM3020：背光补偿开启时，1-低、2-中、3-高
				}
				m_cboBackLightRange.SetCurSel(iBackLightRange);// combox  low 0,mid 1,high 2 
			}
			else
			{
				GetDlgItem(IDC_STATIC_RANGE)->EnableWindow(FALSE);
				GetDlgItem(IDC_COMBO_RANGE)->EnableWindow(FALSE);
			}
			m_cboBackLight.SetCurSel(iBackLight);
		}

		//10-背光补偿区域
		if(bGetTemplatePara || HD_PARA_BACK_LIGHT_AREA == _iType)	
		{
			CString cstrRect;
			int iLeft = pb.iParam1[HD_PARA_BACK_LIGHT_AREA];
			int iTop = pb.iParam2[HD_PARA_BACK_LIGHT_AREA];
			int iRight = pb.iParam3[HD_PARA_BACK_LIGHT_AREA];
			int iBottom = pb.iParam4[HD_PARA_BACK_LIGHT_AREA];
			cstrRect.Format("(%d,%d,%d,%d)", iLeft, iTop, iRight, iBottom);
			m_edtBackLightArea.SetWindowText(cstrRect);				
		}
		
		//1-超宽动态
		if(bGetTemplatePara || _iType == HD_PARA_WIDE_DYNAMIC)	
		{
			int iWideDynamic = pb.iParam1[HD_PARA_WIDE_DYNAMIC];
			int iAutoEnable = pb.iAutoEnable[HD_PARA_WIDE_DYNAMIC];
			if ((iWideDynamic == WIDE_DY_OPEN) && (iAutoEnable == WIDE_DY_AUTO))					//自动
			{
				m_cboWideDynamic.SetCurSel(1);

				m_sldWideSensityDegree.SetPos(pb.iParam2[HD_PARA_WIDE_DYNAMIC]);
				SetDlgItemInt(IDC_STC_PARAM2_WIDE_SENSITY_RANGE, pb.iParam2[HD_PARA_WIDE_DYNAMIC]);

				GetDlgItem(IDC_STC_WIDE_SENSITY_DEGREE)->EnableWindow(TRUE);
				GetDlgItem(IDC_SLD_PARAM2_WIDE_SENSITY_DEGREE)->EnableWindow(TRUE);
				GetDlgItem(IDC_STC_PARAM2_WIDE_SENSITY_RANGE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_PARAM2_SET_WIDE_SENSITY_DEGREE)->EnableWindow(TRUE);
			}
			else if ((iWideDynamic == WIDE_DY_OPEN) && (iAutoEnable == WIDE_DY_HANDLE))				//手动
			{
				m_cboWideDynamic.SetCurSel(2);
				m_sldWideSensityDegree.SetPos(pb.iParam2[HD_PARA_WIDE_DYNAMIC]);
				SetDlgItemInt(IDC_STC_PARAM2_WIDE_SENSITY_RANGE, pb.iParam2[HD_PARA_WIDE_DYNAMIC]);

				GetDlgItem(IDC_STC_WIDE_SENSITY_DEGREE)->EnableWindow(TRUE);
				GetDlgItem(IDC_SLD_PARAM2_WIDE_SENSITY_DEGREE)->EnableWindow(TRUE);
				GetDlgItem(IDC_STC_PARAM2_WIDE_SENSITY_RANGE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_PARAM2_SET_WIDE_SENSITY_DEGREE)->EnableWindow(TRUE);
			}
			else if (iWideDynamic == WIDE_DY_VISUAL_ENHANCE)										//可视增强
			{
				m_cboWideDynamic.SetCurSel(3);

				GetDlgItem(IDC_STC_WIDE_SENSITY_DEGREE)->EnableWindow(FALSE);
				GetDlgItem(IDC_SLD_PARAM2_WIDE_SENSITY_DEGREE)->EnableWindow(FALSE);
				GetDlgItem(IDC_STC_PARAM2_WIDE_SENSITY_RANGE)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_PARAM2_SET_WIDE_SENSITY_DEGREE)->EnableWindow(FALSE);
			}
			else																					//关闭
			{
				m_cboWideDynamic.SetCurSel(0);;
				GetDlgItem(IDC_STC_WIDE_SENSITY_DEGREE)->EnableWindow(FALSE);
				GetDlgItem(IDC_SLD_PARAM2_WIDE_SENSITY_DEGREE)->EnableWindow(FALSE);
				GetDlgItem(IDC_STC_PARAM2_WIDE_SENSITY_RANGE)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_PARAM2_SET_WIDE_SENSITY_DEGREE)->EnableWindow(FALSE);
			}
		}	

		//13-白平衡调节
		if(bGetTemplatePara || _iType == HD_PARA_WHITE_BALANCE)	
		{
			int iValueR=pb.iParam1[HD_PARA_WHITE_BALANCE];
			int iValueG=pb.iParam2[HD_PARA_WHITE_BALANCE];
			int iValueB=pb.iParam3[HD_PARA_WHITE_BALANCE];
			m_slidRed.SetPos(iValueR);
			m_slidGreen.SetPos(iValueG);
			m_slidBlue.SetPos(iValueB);
			SetDlgItemInt(IDC_STATIC_REDRANGE, iValueR);
			SetDlgItemInt(IDC_STATIC_GREENRANGE, iValueG);
			SetDlgItemInt(IDC_STATIC_BLUERANGE, iValueB);
			if (pb.iAutoEnable[HD_PARA_WHITE_BALANCE] == 0)
			{
				if (pb.iParam4[HD_PARA_WHITE_BALANCE] == 0)
				{
					m_cboWhiteBalance.SetCurSel(CONST_iSemiautomaticWhiteBalanceIndex);
				}
				else if (pb.iParam4[HD_PARA_WHITE_BALANCE] == 1)
				{
					m_cboWhiteBalance.SetCurSel(CONST_iManualWhiteBalanceIndex);
				}

				GetDlgItem(IDC_SLIDER_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SLIDER_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_SLIDER_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_STATIC_REDRANGE)->EnableWindow(TRUE);
				GetDlgItem(IDC_STATIC_GREENRANGE)->EnableWindow(TRUE);
				GetDlgItem(IDC_STATIC_BLUERANGE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_PARAM2_SET_WHITE_BALANCE)->EnableWindow(TRUE);
			}
			else if (pb.iAutoEnable[HD_PARA_WHITE_BALANCE] == 1)
			{
				int iTmpItem = pb.iParam4[HD_PARA_WHITE_BALANCE];
				if (iTmpItem == 0)
				{
					m_cboWhiteBalance.SetCurSel(0);
				}
				else
				{
					int iRealItem = iTmpItem + 1;//除0外索引+1
					m_cboWhiteBalance.SetCurSel(iRealItem);
				}

				GetDlgItem(IDC_SLIDER_RED)->EnableWindow(FALSE);
				GetDlgItem(IDC_SLIDER_BLUE)->EnableWindow(FALSE);
				GetDlgItem(IDC_SLIDER_GREEN)->EnableWindow(FALSE);
				GetDlgItem(IDC_STATIC_REDRANGE)->EnableWindow(FALSE);
				GetDlgItem(IDC_STATIC_GREENRANGE)->EnableWindow(FALSE);
				GetDlgItem(IDC_STATIC_BLUERANGE)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_PARAM2_SET_WHITE_BALANCE)->EnableWindow(FALSE);
			}		
		}

		AddLog(LOG_TYPE_SUCC,"","NetClient_GetHDTimeRangeParam (%d, %d, %d)", m_iLogonID, m_iChannelNo, iTempID);
	}
}

int CLS_DomeHDParam2::SetDomeHDPara(int _iType, int _iAutoEnable, int _iParam1, int _iParam2, int _iParam3, int _iParam4)
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
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetHDTimeRangeParam (%d, %d), error (%d)", m_iLogonID, m_iChannelNo, GetLastError());
		return -1;
	}

	AddLog(LOG_TYPE_SUCC,"","NetClient_SetHDTimeRangeParam (%d, %d)" , m_iLogonID, m_iChannelNo);
	return 0;
}

void CLS_DomeHDParam2::OnCbnSelchangeComboCurrentTemp()
{
	// TODO: Add your control notification handler code here
	UpdateDomeHDPara();
}

void CLS_DomeHDParam2::OnCbnSelchangeComboFocusMode()
{
	// TODO: 聚焦模式
	SetDomeHDPara(HD_PARA_FOCUS_MODE, 1, m_cmbFocusMode.GetCurSel(), 0, 0, 0);
}

void CLS_DomeHDParam2::OnCbnSelchangeComboFocustype()
{
	// TODO:聚焦类型
	SetDomeHDPara(HD_PARA_FOCUS_TYPE, 1, m_cboFocusType.GetCurSel(), 0, 0, 0);
}

void CLS_DomeHDParam2::OnCbnSelchangeComboMinFocusDis()
{
	// TODO:最小聚焦距离
	int iIndex = m_cboMinFocusDst.GetCurSel();
	SetDomeHDPara(HD_PARA_MIN_FOCUS_DISTANCE, 1, (int)m_cboMinFocusDst.GetItemData(iIndex), 0, 0, 0);
}

void CLS_DomeHDParam2::OnCbnSelchangeComboSmartir()
{
	// TODO:SmartIR
	SetDomeHDPara(HD_PARA_SMARTIR, 1, m_cboSmartIR.GetCurSel(), 0, 0, 0);
}

void CLS_DomeHDParam2::OnCbnSelchangeComboDaynight()
{
	// TODO:日夜模式
	int iIndex = m_cboDayNight.GetCurSel();
	int iSensitiveRange = 0;
	if (iIndex == 0)
	{
		//自动
		GetDlgItem(IDC_COMBO_SENCITIVITY)->EnableWindow(TRUE);
		iSensitiveRange = m_cboSencitivity.GetCurSel();		
	}
	else
	{
		GetDlgItem(IDC_COMBO_SENCITIVITY)->EnableWindow(FALSE);
	}
	SetDomeHDPara(HD_PARA_DAY_NIGHT, 1, iIndex, iSensitiveRange, 0, 0);
}

void CLS_DomeHDParam2::OnCbnSelchangeComboSencitivity()
{
	// TODO: 灵敏度---只有自动有
	if (m_cboDayNight.GetCurSel() == 0)
	{
		int iSencitivity = m_cboSencitivity.GetCurSel();
		SetDomeHDPara(HD_PARA_DAY_NIGHT, 1, 0, iSencitivity, 0, 0);
	}
}

void CLS_DomeHDParam2::OnCbnSelchangeComboInfrared()
{
	// TODO: 红外校正 Param1取值0 关闭 1开启
	SetDomeHDPara(HD_PARA_INFRARED, 1, m_cboInfrared.GetCurSel(),0, 0, 0);
}

void CLS_DomeHDParam2::OnCbnSelchangeComboBacklight()
{
	// TODO: Add your control notification handler code here
	int iType = m_cboBackLight.GetCurSel();
	if (1 == iType)
	{
		GetDlgItem(IDC_STATIC_RANGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_RANGE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_RANGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_RANGE)->EnableWindow(FALSE);
	}
	SetDomeHDPara(HD_PARA_BACK_LIGHT, 1, iType, 0, 0, 0);
}

void CLS_DomeHDParam2::OnCbnSelchangeComboRange()
{
	// TODO: 背光补偿等级 LNM3020：背光补偿开启时，1-低、2-中、3-高
	if (m_cboBackLight.GetCurSel() == 1)
	{
		SetDomeHDPara(HD_PARA_BACK_LIGHT, 1, m_cboBackLight.GetCurSel(), m_cboBackLightRange.GetCurSel() + 1, 0, 0);
	}	
}

void CLS_DomeHDParam2::OnCbnSelchangeComboWideDynamic()
{
	// TODO:宽动态
	int iWideDyItem = m_cboWideDynamic.GetCurSel();
	int iEnable = 0;
	int iWDRange = 0;
	int iAutoEnable = 0;// 自动/手动
	if(1 == iWideDyItem)
	{
		//自动;
		GetDlgItem(IDC_STC_WIDE_SENSITY_DEGREE)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLD_PARAM2_WIDE_SENSITY_DEGREE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STC_PARAM2_WIDE_SENSITY_RANGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PARAM2_SET_WIDE_SENSITY_DEGREE)->EnableWindow(TRUE);
		iEnable = 1;
		iAutoEnable = 1;
		iWDRange = m_sldWideSensityDegree.GetPos();
	}
	else if (2 == iWideDyItem)
	{
		//手动
		GetDlgItem(IDC_STC_WIDE_SENSITY_DEGREE)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLD_PARAM2_WIDE_SENSITY_DEGREE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STC_PARAM2_WIDE_SENSITY_RANGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PARAM2_SET_WIDE_SENSITY_DEGREE)->EnableWindow(TRUE);
		iEnable = 1;
		iAutoEnable = 0;
		iWDRange = m_sldWideSensityDegree.GetPos();
	}
	else if (3 == iWideDyItem)
	{
		//可视增强
		GetDlgItem(IDC_STC_WIDE_SENSITY_DEGREE)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLD_PARAM2_WIDE_SENSITY_DEGREE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STC_PARAM2_WIDE_SENSITY_RANGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PARAM2_SET_WIDE_SENSITY_DEGREE)->EnableWindow(FALSE);
		iEnable = 2;
		iAutoEnable = 1;
	}
	else
	{	
		//关闭
		GetDlgItem(IDC_STC_WIDE_SENSITY_DEGREE)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLD_PARAM2_WIDE_SENSITY_DEGREE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STC_PARAM2_WIDE_SENSITY_RANGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PARAM2_SET_WIDE_SENSITY_DEGREE)->EnableWindow(FALSE);
		iEnable = 0;
		iAutoEnable = 1;
	}
	SetDomeHDPara(HD_PARA_WIDE_DYNAMIC, iAutoEnable, iEnable, iWDRange, 0, 0);
}

//超宽动态 设置
void CLS_DomeHDParam2::OnBnClickedBtnParam2SetWideSensityDegree()
{
	OnCbnSelchangeComboWideDynamic();
}


//宽动态强度
void CLS_DomeHDParam2::OnNMCustomdrawSldParam2WideSensityDegree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	int iPos = m_sldWideSensityDegree.GetPos();
	SetDlgItemInt(IDC_STC_PARAM2_WIDE_SENSITY_RANGE, iPos);

	*pResult = 0;
}

void CLS_DomeHDParam2::OnCbnSelchangeComboSencitivityW()
{
	// TODO: 宽动态等级 
	int iIndex = m_cboWideDynamic.GetCurSel();
	int iValue = m_cboSencitivityW.GetCurSel();
	if(iIndex == 1)
	{
		SetDomeHDPara(HD_PARA_WIDE_DYNAMIC, 1, iIndex, iValue, 0, 0);
		int i = 0;
		i++;
	}
}

void CLS_DomeHDParam2::OnCbnSelchangeComboWhitebalance()
{
	// TODO:白平衡
	int iIndex = m_cboWhiteBalance.GetCurSel();
	int iIsAuto = 0;
	int iAutoType = 0;

	int iRed = m_slidRed.GetPos();
	int iGreen = m_slidGreen.GetPos();
	int iBlue = m_slidBlue.GetPos();
	if (CONST_iSemiautomaticWhiteBalanceIndex == iIndex || CONST_iManualWhiteBalanceIndex == iIndex)
	{
		GetDlgItem(IDC_SLIDER_RED)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLIDER_BLUE)->EnableWindow(TRUE);
		GetDlgItem(IDC_SLIDER_GREEN)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_REDRANGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_GREENRANGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_BLUERANGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_PARAM2_SET_WHITE_BALANCE)->EnableWindow(TRUE);
		if (CONST_iSemiautomaticWhiteBalanceIndex == iIndex)
		{
			//0 半自动
			SetDomeHDPara(HD_PARA_WHITE_BALANCE, iIsAuto, iRed, iGreen, iBlue, 0);
		}
		else if (CONST_iManualWhiteBalanceIndex == iIndex)
		{
			//1手动
			SetDomeHDPara(HD_PARA_WHITE_BALANCE, iIsAuto, iRed, iGreen, iBlue, 1);
		}
	}
	else
	{
		GetDlgItem(IDC_SLIDER_RED)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_BLUE)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_GREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_REDRANGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_GREENRANGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_BLUERANGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PARAM2_SET_WHITE_BALANCE)->EnableWindow(FALSE);
		iIsAuto = 1;
		iAutoType = (int)m_cboWhiteBalance.GetItemData(iIndex);
		SetDomeHDPara(HD_PARA_WHITE_BALANCE, iIsAuto, iRed, iGreen, iBlue, iAutoType);
	}
}

void CLS_DomeHDParam2::OnNMCustomdrawSliderRed(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 白平衡 R调节
	int iPos = m_slidRed.GetPos();
	SetDlgItemInt(IDC_STATIC_REDRANGE, iPos);

	*pResult = 0;
}

void CLS_DomeHDParam2::OnNMCustomdrawSliderBlue(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 白平衡 B调节
	int iPos = m_slidBlue.GetPos();
	SetDlgItemInt(IDC_STATIC_BLUERANGE, iPos);

	*pResult = 0;
}

//设置白平衡按钮
void CLS_DomeHDParam2::OnBnClickedBtnParam2SetWhiteBalance()
{
	// TODO: 在此添加控件通知处理程序代码
	int iIndex = m_cboWhiteBalance.GetCurSel();
	int iIsAuto = 0;
	int iAutoType = 0;

	int iRed = m_slidRed.GetPos();
	int iGreen = m_slidGreen.GetPos();
	int iBlue = m_slidBlue.GetPos();
	if (CONST_iSemiautomaticWhiteBalanceIndex == iIndex || CONST_iManualWhiteBalanceIndex == iIndex)
	{
		if (CONST_iSemiautomaticWhiteBalanceIndex == iIndex)
		{
			//0 半自动
			SetDomeHDPara(HD_PARA_WHITE_BALANCE, iIsAuto, iRed, iGreen, iBlue, 0);
		}
		else if (CONST_iManualWhiteBalanceIndex == iIndex)
		{
			//1手动
			SetDomeHDPara(HD_PARA_WHITE_BALANCE, iIsAuto, iRed, iGreen, iBlue, 1);
		}
	}
	else
	{
		iIsAuto = 1;
		iAutoType = (int)m_cboWhiteBalance.GetItemData(iIndex);
		SetDomeHDPara(HD_PARA_WHITE_BALANCE, iIsAuto, iRed, iGreen, iBlue, iAutoType);
	}
}

void CLS_DomeHDParam2::OnNMCustomdrawSliderGreen(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 白平衡 G调节
	int iPos = m_slidGreen.GetPos();
	SetDlgItemInt(IDC_STATIC_GREENRANGE, iPos);

	*pResult = 0;
}


void CLS_DomeHDParam2::OnBnClickedButtonBacklightDraw()
{
	if (NULL == m_pDlgVideoView)
	{
		m_pDlgVideoView = new CLS_VideoViewForDraw();
		if (NULL == m_pDlgVideoView)
		{
			return;
		}
	}

	m_pDlgVideoView->Init(m_iLogonID, m_iChannelNo, m_iStreamNO);
	m_pDlgVideoView->SetDrawType(DrawType_Crowd);
	int iPointNum = 0;
	int iDirection = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	m_pDlgVideoView->SetPointRegionParam(cPointBuf, &iPointNum, &iDirection);
	if (IDOK == m_pDlgVideoView->DoModal())
	{
		int iLeft = 0;
		int iTop = 0;
		int iRight = 0;
		int iBottom = 0;
		m_pDlgVideoView->GetPointCoordirate(&iLeft, &iTop, &iRight, &iBottom);
		CString cstrRect;
		cstrRect.Format("(%d,%d,%d,%d)", iLeft, iTop, iRight, iBottom);
		m_edtBackLightArea.SetWindowText(cstrRect);
		SetDomeHDPara(HD_PARA_BACK_LIGHT_AREA, 1, iLeft, iTop, iRight, iBottom);
	}

	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_DomeHDParam2::OnMainNotify(int _ulLogonID, int _iWparam, void* _pvLParam, void* _pvUser)
{
	if (NULL != m_pDlgVideoView)
	{
		m_pDlgVideoView->OnMainNotify(_ulLogonID, _iWparam, _pvLParam, _pvUser);
	}
}
