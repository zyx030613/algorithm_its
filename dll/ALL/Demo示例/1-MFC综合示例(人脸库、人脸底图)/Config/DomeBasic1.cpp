// DomeBasic.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "DomeBasic1.h"

#define CAMRATYPE_LASER_COVER			701 //320激光护罩
#define CAMRATYPE_COVER					702 //320普通护罩

//温度控制模式：0-关闭 1-风冷 2-自动 3-除雾 4-加热
#define HEAT_MODE_OFF		0
#define HEAT_MODE_COOL		1
#define HEAT_MODE_AUTO		2
#define HEAT_MODE_FOG		3
#define HEAT_MODE_HOT		4

// CLS_DomeBasic dialog

IMPLEMENT_DYNAMIC(CLS_DomeBasicInfo, CDialog)

CLS_DomeBasicInfo::CLS_DomeBasicInfo(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DomeBasicInfo::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNO = -1;
}

CLS_DomeBasicInfo::~CLS_DomeBasicInfo()
{
}

void CLS_DomeBasicInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_AUTO_FLIP, m_chkAutoFlip);
	DDX_Control(pDX, IDC_CHECK_PRESET_FREEZE, m_chkPresetFrozen);
	DDX_Control(pDX, IDC_CHECK_DIGIST_ZOOM, m_chkDigistZoom);
	DDX_Control(pDX, IDC_CHK_PRESET_SNAP, m_chkPresetSnap);
	DDX_Control(pDX, IDC_CHK_SCALE_ZOOM, m_chkScaleZoom);
	DDX_Control(pDX, IDC_CHK_SCAN_VIDEO, m_chkScanVideo);
	DDX_Control(pDX, IDC_CHK_MODELPATH_VIDEO, m_chkModelPathVideo);
	DDX_Control(pDX, IDC_CBO_ANGLE_SET, m_cboAngleSet);
	DDX_Control(pDX, IDC_COMBO_MANUAL_SPEED_RATING, m_cboManualSpeed);
	DDX_Control(pDX, IDC_COMBO_ZOOM_SPEED_RATING, m_cboZoomSpeed);
	DDX_Control(pDX, IDC_CBO_HEAT_MODE, m_cboHeatMode);
	DDX_Control(pDX, IDC_COMBO_TIME_AUTO_STOP, m_cboAutoStopTime);
	DDX_Control(pDX, IDC_COMBO_PRESET_SPEED_RATING, m_cboPresetSpeed);
	DDX_Control(pDX, IDC_CBO_DADO_PRIORITY, m_cboDadoPRI);
	DDX_Control(pDX, IDC_SLD_PRI_DELAY_TIME, m_sldPRIDelayTime);
	DDX_Control(pDX, IDC_CBO_485, m_cbo485);
	DDX_Control(pDX, IDC_CBO_NO_ELECTRICITY_MEMORY, m_cboNoElectricityMemory);
	DDX_Control(pDX, IDC_CBO_VIDEO_TURN, m_cboVideoTurn);
	DDX_Control(pDX, IDC_COMBO_AWATE_ACTION, m_cboAwateAction);
	DDX_Control(pDX, IDC_CHECK_AWATE_ACTION, m_chkAwateAction);
	DDX_Control(pDX, IDC_COMBO_AWATE_TIME, m_cboAwateTime);
	DDX_Control(pDX, IDC_BTN_PRI_DELAY_TIME, m_btnPriDelayTime);
}


BEGIN_MESSAGE_MAP(CLS_DomeBasicInfo, CDialog)
	ON_BN_CLICKED(IDC_CHECK_AUTO_FLIP, &CLS_DomeBasicInfo::OnBnClickedCheckAutoFlip)
	ON_BN_CLICKED(IDC_CHECK_PRESET_FREEZE, &CLS_DomeBasicInfo::OnBnClickedCheckPresetFreeze)
	ON_BN_CLICKED(IDC_CHECK_DIGIST_ZOOM, &CLS_DomeBasicInfo::OnBnClickedCheckDigistZoom)
	ON_BN_CLICKED(IDC_CHK_PRESET_SNAP, &CLS_DomeBasicInfo::OnBnClickedChkPresetSnap)
	ON_BN_CLICKED(IDC_CHK_SCALE_ZOOM, &CLS_DomeBasicInfo::OnBnClickedChkScaleZoom)
	ON_BN_CLICKED(IDC_CHK_SCAN_VIDEO, &CLS_DomeBasicInfo::OnBnClickedChkScanVideo)
	ON_BN_CLICKED(IDC_CHK_MODELPATH_VIDEO, &CLS_DomeBasicInfo::OnBnClickedChkModelpathVideo)
	ON_CBN_SELCHANGE(IDC_CBO_ANGLE_SET, &CLS_DomeBasicInfo::OnCbnSelchangeCboAngleSet)
	ON_CBN_SELCHANGE(IDC_COMBO_MANUAL_SPEED_RATING, &CLS_DomeBasicInfo::OnCbnSelchangeComboManualSpeedRating)
	ON_CBN_SELCHANGE(IDC_COMBO_ZOOM_SPEED_RATING, &CLS_DomeBasicInfo::OnCbnSelchangeComboZoomSpeedRating)
	ON_CBN_SELCHANGE(IDC_CBO_HEAT_MODE, &CLS_DomeBasicInfo::OnCbnSelchangeCboHeatMode)
	ON_CBN_SELCHANGE(IDC_COMBO_TIME_AUTO_STOP, &CLS_DomeBasicInfo::OnCbnSelchangeComboTimeAutoStop)
	ON_CBN_SELCHANGE(IDC_COMBO_PRESET_SPEED_RATING, &CLS_DomeBasicInfo::OnCbnSelchangeComboPresetSpeedRating)
	ON_CBN_SELCHANGE(IDC_CBO_DADO_PRIORITY, &CLS_DomeBasicInfo::OnCbnSelchangeCboDadoPriority)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_PRI_DELAY_TIME, &CLS_DomeBasicInfo::OnNMCustomdrawSldPriDelayTime)
	ON_CBN_SELCHANGE(IDC_CBO_485, &CLS_DomeBasicInfo::OnCbnSelchangeCbo485)
	ON_CBN_SELCHANGE(IDC_CBO_NO_ELECTRICITY_MEMORY, &CLS_DomeBasicInfo::OnCbnSelchangeCboNoElectricityMemory)
	ON_CBN_SELCHANGE(IDC_CBO_VIDEO_TURN, &CLS_DomeBasicInfo::OnCbnSelchangeCboVideoTurn)
	ON_BN_CLICKED(IDC_CHECK_AWATE_ACTION, &CLS_DomeBasicInfo::OnBnClickedCheckAwateAction)
	ON_BN_CLICKED(IDC_BUTTON_SET_WAITE_ACTION, &CLS_DomeBasicInfo::OnBnClickedButtonSetWaiteAction)
	ON_BN_CLICKED(IDC_BTN_PRI_DELAY_TIME, &CLS_DomeBasicInfo::OnBnClickedBtnPriDelayTime)
END_MESSAGE_MAP()


// CLS_DomeBasic message handlers

BOOL CLS_DomeBasicInfo::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UI_UpdateDialogText();
	UI_UpdateDomeMenuInfo();
	UI_UpdateDomePTZInfo();
	UI_UpdateVideoFlipType();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_DomeBasicInfo::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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
	UI_UpdateDomeMenuInfo();
	UI_UpdateDomePTZInfo();
	UI_UpdateVideoFlipType();
}

void CLS_DomeBasicInfo::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialogText();
	UI_UpdateDomeMenuInfo();
	UI_UpdateDomePTZInfo();
	UI_UpdateVideoFlipType();
}

void CLS_DomeBasicInfo::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_CHECK_AUTO_FLIP, IDS_DOME_PTZ_AUTO_FLIP);
	SetDlgItemTextEx(IDC_CHECK_PRESET_FREEZE, IDS_DOME_PTZ_PRESET_FREEZE_UP);
	SetDlgItemTextEx(IDC_CHECK_DIGIST_ZOOM, IDS_DIGITAL_ZOOM);
	SetDlgItemTextEx(IDC_CHK_PRESET_SNAP, IDS_PRESET_CAPTURE);
	SetDlgItemTextEx(IDC_CHK_SCALE_ZOOM, IDS_SCALE_ZOOM);
	SetDlgItemTextEx(IDC_CHK_SCAN_VIDEO, IDS_SCAN_VIDEO);
	SetDlgItemTextEx(IDC_CHK_MODELPATH_VIDEO, IDS_MODEL_PATH_VIDEO);
	SetDlgItemTextEx(IDC_STATIC_ANGLE_SET, IDS_VERTICAL_ANGLE_ADJUSTMENT);
	SetDlgItemTextEx(IDC_STATIC_MANUAL_SPEED_RATING, IDS_MANIPULATION_SPEED_RATING);
	SetDlgItemTextEx(IDC_STATIC_ZOOM_SPEED_RATING, IDS_DOME_ZOOMSPEED);
	SetDlgItemTextEx(IDC_STATIC_HEAT_MODE, IDS_TEMPERATURE_CONTROL_MODE);
	SetDlgItemTextEx(IDC_STATIC_TIME_AUTO_STOP, IDS_TIME_AUTO_STOP);
	SetDlgItemTextEx(IDC_STATIC_PRESET_SPEED_RATING, IDS_PRESET_SPEED_RATING);
	SetDlgItemTextEx(IDC_STC_DADO_PRIORITY, IDS_PTZ_PRIOR);
	SetDlgItemTextEx(IDC_STC_PRI_DELAY_TIME, IDS_PRI_DELAY_TIME);
	SetDlgItemTextEx(IDC_STATIC_485, IDS_485_ADDRESS_SETTING);
	SetDlgItemTextEx(IDC_STC_NO_ELECTRICITY_MEMORY, IDS_OUTAGE_MEMORY);
	SetDlgItemTextEx(IDC_STC_VIDEO_TURN, IDS_VIDEO_PARAM_FLIP);
	SetDlgItemTextEx(IDC_STATIC_AWATE, IDS_DOME_PTZ_WAIT_ACT);
	SetDlgItemTextEx(IDC_STATIC_AWATE_ACTION, IDS_DOME_PTZ_WAIT_ACT);
	SetDlgItemTextEx(IDC_STATIC_AWATE_TIME, IDS_STANDBY_TIME2);
	SetDlgItemTextEx(IDC_CHECK_AWATE_ACTION, IDS_POWER_DEV_LST_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_AWATE, IDS_WAITE);
	SetDlgItemTextEx(IDC_BTN_PRI_DELAY_TIME, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_SET_WAITE_ACTION, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_CAMERA_TYPE, IDS_CAMERA_TYPE);

	int iDevType = 0;
	NetClient_GetITSExtraInfo(m_iLogonID, ITS_CAMRATYPE_CMD_GET, 0, &iDevType, sizeof(int));
	SetDlgItemInt(IDC_EDIT_CAMERA_TYPE, iDevType);
	//垂直角度调整：0：0度 1：-1度 2：-2度 3：-3度 4：-4度 5：-5度 6：-6度 7：-7度 
	//8：-8度 9：-9度 10：-10度 11：-11度 12：-12度 13：-13度 14：-14度 15：-15度 
	CString cstrAngle = "";
	int iCount = 0;
	int iAngleNum = 11;
	//判断是否重载云台
	m_cboAngleSet.ResetContent();
	if (iDevType == CAMRATYPE_LASER_COVER || iDevType == CAMRATYPE_COVER)
	{
		iAngleNum = 16;
		for (int i=0; i<iAngleNum; i++)
		{
			cstrAngle.Format("%d", -45-i);//重载云台此参数从-45~-60
			m_cboAngleSet.AddString(cstrAngle);
			m_cboAngleSet.SetItemData(iCount++, -45-i);
		}
	} 
	else
	{
		for (int i=0; i<iAngleNum; i++)
		{
			cstrAngle.Format("%d", 0-i);
			m_cboAngleSet.AddString(cstrAngle);
			m_cboAngleSet.SetItemData(iCount++, 0-i);
		}
	}
	m_cboAngleSet.SetCurSel(0);

	//操控速度等级：0-低速 1-中速 2-高速   
	InsertString(m_cboManualSpeed, 0, IDS_VCA_SENS_LOW);
	InsertString(m_cboManualSpeed, 1, IDS_VCA_SENS_MIDDLE);
	InsertString(m_cboManualSpeed, 2, IDS_VCA_SENS_HIGH);
	m_cboManualSpeed.SetCurSel(0);

	//变倍速度等级：0-低速 1-中速 2-高速   
	InsertString(m_cboZoomSpeed, 0, IDS_VCA_SENS_LOW);
	InsertString(m_cboZoomSpeed, 1, IDS_VCA_SENS_MIDDLE);
	InsertString(m_cboZoomSpeed, 2, IDS_VCA_SENS_HIGH);
	m_cboZoomSpeed.SetCurSel(0);

	//温度控制模式：0-关闭 1-风冷 2-自动 3-除雾 4-加热
	m_cboHeatMode.ResetContent();
	iCount = 0;
	m_cboHeatMode.AddString(GetTextEx(IDS_CONFIG_CLOSE));
	m_cboHeatMode.SetItemData(iCount++, HEAT_MODE_OFF);
	m_cboHeatMode.AddString(GetTextEx(IDS_HEAT_MODE_COOL));
	m_cboHeatMode.SetItemData(iCount++, HEAT_MODE_COOL);
	m_cboHeatMode.AddString(GetTextEx(IDS_DOME_AUTO));
	m_cboHeatMode.SetItemData(iCount++, HEAT_MODE_AUTO);
	m_cboHeatMode.AddString(GetTextEx(IDS_HEAT_MODE_FOG));
	m_cboHeatMode.SetItemData(iCount++, HEAT_MODE_FOG);
	m_cboHeatMode.AddString(GetTextEx(IDS_HEAT_MODE_HOT));
	m_cboHeatMode.SetItemData(iCount++, HEAT_MODE_HOT);
	m_cboHeatMode.SetCurSel(0);

	//自动停止时间：0-5秒 1-15秒 2-30秒 3-60秒 
	m_cboAutoStopTime.ResetContent();
	iCount = 0;
	m_cboAutoStopTime.AddString("5");
	m_cboAutoStopTime.SetItemData(iCount++, 5);
	m_cboAutoStopTime.AddString("15");
	m_cboAutoStopTime.SetItemData(iCount++, 15);
	m_cboAutoStopTime.AddString("30");
	m_cboAutoStopTime.SetItemData(iCount++, 30);
	m_cboAutoStopTime.AddString("60");
	m_cboAutoStopTime.SetItemData(iCount++, 60);
	m_cboAutoStopTime.SetCurSel(0);

	//预置位速度等级：0-低速 1-中速 2-高速    
	InsertString(m_cboPresetSpeed, 0, IDS_VCA_SENS_LOW);
	InsertString(m_cboPresetSpeed, 1, IDS_VCA_SENS_MIDDLE);
	InsertString(m_cboPresetSpeed, 2, IDS_VCA_SENS_HIGH);
	m_cboPresetSpeed.SetCurSel(0);

	m_cboDadoPRI.ResetContent();
	m_cboDadoPRI.AddString(GetTextEx(IDS_NETWORK));
	m_cboDadoPRI.SetItemData(0, 0);
	m_cboDadoPRI.AddString("RS485");
	m_cboDadoPRI.SetItemData(1, 1);
	m_cboDadoPRI.SetCurSel(0);

	m_sldPRIDelayTime.SetRange(0, 200);
	m_sldPRIDelayTime.SetPos(0);
	SetDlgItemInt(IDC_STC_PRI_DELAY_TIME_TEXT, m_sldPRIDelayTime.GetPos());

	//485地址设置：0～255
	m_cbo485.ResetContent();
	CString cstr485 = "";
	for(int i=0; i<256; i++)
	{
		cstr485.Format("%d", i);
		m_cbo485.AddString(cstr485);
	}
	m_cbo485.SetCurSel(0);

	m_cboNoElectricityMemory.ResetContent();
	m_cboNoElectricityMemory.AddString(GetTextEx(IDS_CONFIG_CLOSE));//关闭
	m_cboNoElectricityMemory.SetItemData(0, 0);
	m_cboNoElectricityMemory.AddString("30" + GetTextEx(IDS_SECOND));
	m_cboNoElectricityMemory.SetItemData(1, 30);
	m_cboNoElectricityMemory.AddString("1" + GetTextEx(IDS_MINUTE));
	m_cboNoElectricityMemory.SetItemData(2, 60);
	m_cboNoElectricityMemory.AddString("5" + GetTextEx(IDS_MINUTE));
	m_cboNoElectricityMemory.SetItemData(3, 300);
	m_cboNoElectricityMemory.AddString("10" + GetTextEx(IDS_MINUTE));
	m_cboNoElectricityMemory.SetItemData(4, 600);
	m_cboNoElectricityMemory.SetCurSel(0);

	m_cboVideoTurn.ResetContent();
	m_cboVideoTurn.AddString(GetTextEx(IDS_DOME_HANDLE));
	m_cboVideoTurn.AddString(GetTextEx(IDS_DOME_AUTO));
	m_cboVideoTurn.SetCurSel(0);

	m_cboAwateAction.ResetContent();
	m_cboAwateAction.AddString(GetTextEx(IDS_CONFIG_8D1_PRESET)+_T(" 1"));
	m_cboAwateAction.AddString(GetTextEx(IDS_DOME_ADV_SCAN)+_T(" 1"));
	m_cboAwateAction.AddString(GetTextEx(IDS_DOME_ADV_CURISE)+_T(" 1"));
	m_cboAwateAction.AddString(GetTextEx(IDS_DOME_PTZ_ACT_PATTERN)+_T(" 1"));
	m_cboAwateAction.SetCurSel(0);

	//待机信息
	m_cboAwateTime.ResetContent();
	m_cboAwateTime.AddString(_T("30"));
	m_cboAwateTime.AddString(_T("60"));
	m_cboAwateTime.AddString(_T("300"));
	m_cboAwateTime.AddString(_T("600"));
	m_cboAwateTime.AddString(_T("1800"));
	m_cboAwateTime.SetCurSel(0);
}

void CLS_DomeBasicInfo::UI_UpdateDomeMenuInfo()
{
	TDomeParam tParam = {0};
	//数字变倍
	memset(&tParam, 0, sizeof(TDomeParam));
	tParam.iType = DOME_PARA_DIGITAL_ZOOM;
	if (GetDomeMenu(tParam) == 0)
	{
		m_chkDigistZoom.SetCheck(tParam.iParam1);
	}

	//垂直角度调整
	memset(&tParam, 0, sizeof(TDomeParam));
	tParam.iType = DOME_PARA_VERTICAL_ANGLE_ADJUSTMENT;
	if (GetDomeMenu(tParam) == 0)
	{
		int iIndex = m_cboAngleSet.FindString(-1, IntToStr(tParam.iParam1).c_str());
		if (iIndex < 0)
		{
			iIndex = 0;
		}
		m_cboAngleSet.SetCurSel(iIndex);
	}

	//变倍速度
	memset(&tParam, 0, sizeof(TDomeParam));
	tParam.iType = DOME_PARA_ZOOM_SPEED;
	if (GetDomeMenu(tParam) == 0)
	{
		m_cboZoomSpeed.SetCurSel(tParam.iParam1);
	}

	//温度控制模式
	memset(&tParam, 0, sizeof(TDomeParam));
	tParam.iType = DOME_PARA_TEMPERATURE_CONTROL_MODE;
	if (GetDomeMenu(tParam) == 0)
	{
		int iIndex = 0;
		for (int i=0; i<m_cboHeatMode.GetCount(); i++)
		{
			if (m_cboHeatMode.GetItemData(i) == tParam.iParam1)
			{
				iIndex = i;
				break;
			}
		}
		m_cboHeatMode.SetCurSel(iIndex);
	}

	//自动停止时间
	memset(&tParam, 0, sizeof(TDomeParam));
	tParam.iType = DOME_PARA_AUTOMATIC_STOP_TIME;
	if (GetDomeMenu(tParam) == 0)
	{
		int iIndex = m_cboAutoStopTime.FindString(-1, IntToStr(tParam.iParam1).c_str());
		if (iIndex < 0 )
		{
			iIndex = 0;
		}
		m_cboAutoStopTime.SetCurSel(iIndex);
	}

	//云台优先
	memset(&tParam, 0, sizeof(TDomeParam));
	tParam.iType = DOME_PARA_PTZ_PRIOR;
	if (GetDomeMenu(tParam) == 0)
	{
		if (tParam.iParam1 == 1)
		{
			m_cboDadoPRI.SetCurSel(1);
		}
		else
		{
			m_cboDadoPRI.SetCurSel(0);
		}

		m_sldPRIDelayTime.SetPos(tParam.iParam2);
		SetDlgItemInt(IDC_STC_PRI_DELAY_TIME_TEXT, m_sldPRIDelayTime.GetPos());
	}

	//485地址设置
	memset(&tParam, 0, sizeof(TDomeParam));
	tParam.iType = DOME_PARA_485_ADDRESS_SETTING;
	if (GetDomeMenu(tParam) == 0)
	{
		m_cbo485.SetCurSel(tParam.iParam1);
	}

	//掉电记忆模式
	memset(&tParam, 0, sizeof(TDomeParam));
	tParam.iType = DOME_PARA_OUTAGE_MEMORY;
	if (GetDomeMenu(tParam) == 0)
	{
		for (int i=0; i<m_cboNoElectricityMemory.GetCount(); i++)
		{
			if (tParam.iParam1 == m_cboNoElectricityMemory.GetItemData(i))
			{
				m_cboNoElectricityMemory.SetCurSel(i);
				break;
			}
		}
	}
}

void CLS_DomeBasicInfo::UI_UpdateDomePTZInfo()
{
	DOMEPTZ tDomePtz = {0};

	//预置位冻结
	GetDomePTZ(DOME_PTZ_TYPE_PRESET_FREEZE_UP, 0, 0, &tDomePtz);
	CheckDlgButton(IDC_CHECK_PRESET_FREEZE,tDomePtz.iAutoEnable);

	//自动翻转
	GetDomePTZ(DOME_PTZ_TYPE_AUTO_FLIP, 0, 0, &tDomePtz);
	CheckDlgButton(IDC_CHECK_AUTO_FLIP,tDomePtz.iAutoEnable);

	//比例变倍
	GetDomePTZ(DOME_PTZ_TYPE_SCALE_ZOOM, 0, 0, &tDomePtz);
	CheckDlgButton(IDC_CHK_SCALE_ZOOM,tDomePtz.iAutoEnable);

	//预置位抓拍、扫描录像、模式路径录像
	GetDomePTZ(DOME_PTZ_TYPE_LINK_DISJUNCTOR, 0, 0, &tDomePtz);
	CheckDlgButton(IDC_CHK_PRESET_SNAP,tDomePtz.iParam1&0x01);
	CheckDlgButton(IDC_CHK_SCAN_VIDEO,tDomePtz.iParam1>>1&0x01);
	CheckDlgButton(IDC_CHK_MODELPATH_VIDEO,tDomePtz.iParam1>>2&0x01);

	//操控速度等级
	GetDomePTZ(DOME_PTZ_TYPE_MANUL_SEPPD_LEVEL, 0, 0, &tDomePtz);
	if (0 > m_cboManualSpeed.SetCurSel(tDomePtz.iParam1))
	{
		m_cboManualSpeed.SetCurSel(0);
	}

	//预置位速度等级
	GetDomePTZ(DOME_PTZ_TYPE_PRESET_SPEED_LEVE, 0, 0, &tDomePtz);
	if (0 > m_cboPresetSpeed.SetCurSel(tDomePtz.iParam1))
	{
		m_cboPresetSpeed.SetCurSel(0);
	}
	
	//待机
	GetDomePTZ(DOME_PTZ_TYPE_WAIT_ACT, 0, 0, &tDomePtz);
	m_chkAwateAction.SetCheck(tDomePtz.iAutoEnable);
	m_cboAwateAction.SetCurSel(tDomePtz.iParam2);
	int iIndex = m_cboAwateTime.FindString(-1, IntToStr(tDomePtz.iParam1).c_str());
	if (iIndex == -1)
	{
		iIndex = 0;
	}
	m_cboAwateTime.SetCurSel(iIndex);
}

void CLS_DomeBasicInfo::UI_UpdateVideoFlipType()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error (%d)", m_iLogonID, GetLastError());
		return;
	}

	int iType = -1;
	int iRet = NetClient_GetCommonEnable(m_iLogonID, CI_COMMON_ID_VIDEO_REVERSE, m_iChannelNo, &iType);
	if (iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetCommonEnable[CI_COMMON_ID_VIDEO_REVERSE] (%d, %d)", m_iLogonID, m_iChannelNo);
		m_cboVideoTurn.SetCurSel(iType);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetCommonEnable[CI_COMMON_ID_VIDEO_REVERSE] (%d, %d), error (%d)"
			, m_iLogonID, m_iChannelNo, GetLastError());
	}
}

int CLS_DomeBasicInfo::SetDomeMenu(int _iType, int _iParam1, int _iParam2, int _iParam3, int _iParam4)
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error(%d)", m_iLogonID, GetLastError());
		return -1;
	}

	TDomeParam tParam = {0};
	tParam.iType = _iType;
	tParam.iParam1 = _iParam1;
	tParam.iParam2 = _iParam2;
	tParam.iParam3 = _iParam3;
	tParam.iParam4 = _iParam4;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU
									, m_iChannelNo, &tParam,sizeof(TDomeParam));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d, %d)", m_iLogonID, m_iChannelNo, _iType);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d, %d), error (%d)",  m_iLogonID, m_iChannelNo, _iType, GetLastError());
	}
	return iRet;
}

int CLS_DomeBasicInfo::GetDomeMenu(TDomeParam& _tParam)
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error (%d)", m_iLogonID, GetLastError());
		return -1;
	}

	int iReturnByte = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo, &_tParam, sizeof(TDomeParam), &iReturnByte);
	if (iRet != 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d), error(%d)"
			, m_iLogonID, m_iChannelNo, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d)", m_iLogonID, m_iChannelNo);
	}

	return iRet;
}

int CLS_DomeBasicInfo::SetDomePTZ(int _iType, int _iEnable, int _iParam1, int _iParam2)
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error (%d)", m_iLogonID, GetLastError());
		return -1;
	}

	DOMEPTZ tDomePtz = {0};
	tDomePtz.iSize = sizeof(DOMEPTZ);
	tDomePtz.iType = _iType;
	tDomePtz.iAutoEnable = _iEnable;
	tDomePtz.iParam1 = _iParam1;
	tDomePtz.iParam2 = _iParam2;
	int iRet = NetClient_SetDomePTZ(m_iLogonID, m_iChannelNo, &tDomePtz, sizeof(DOMEPTZ));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDomePTZ (%d, %d, %d)", m_iLogonID, m_iChannelNo, _iType);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDomePTZ (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNo, _iType, GetLastError());
	}

	return iRet;
}

int CLS_DomeBasicInfo::GetDomePTZ(int _iType, int _iParam1, int _iParam2, DOMEPTZ *_pDomePtz)
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error(%d)", m_iLogonID, GetLastError());
		return -1;
	}

	_pDomePtz->iSize = sizeof(DOMEPTZ);
	_pDomePtz->iType = _iType;
	_pDomePtz->iAutoEnable = 0;
	_pDomePtz->iParam1 = _iParam1;
	_pDomePtz->iParam2 = _iParam2;
	int iRet = NetClient_GetDomePTZ(m_iLogonID, m_iChannelNo, _pDomePtz, sizeof(DOMEPTZ));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDomePTZ (%d, %d, %d)", m_iLogonID, m_iChannelNo, _iType);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDomePTZ (%d, %d, %d), error(%d)", m_iLogonID, m_iChannelNo, _iType, GetLastError());
	}

	return iRet;
}

void CLS_DomeBasicInfo::OnBnClickedCheckAutoFlip()
{
	SetDomePTZ(DOME_PTZ_TYPE_AUTO_FLIP, IsDlgButtonChecked(IDC_CHECK_AUTO_FLIP));
}

void CLS_DomeBasicInfo::OnBnClickedCheckPresetFreeze()
{
	SetDomePTZ(DOME_PTZ_TYPE_PRESET_FREEZE_UP, IsDlgButtonChecked(IDC_CHECK_PRESET_FREEZE));
}

void CLS_DomeBasicInfo::OnBnClickedCheckDigistZoom()
{
	SetDomeMenu(DOME_PARA_DIGITAL_ZOOM, m_chkDigistZoom.GetCheck());
}

void CLS_DomeBasicInfo::OnBnClickedChkPresetSnap()
{
	int iPresetSnapEnable = BST_CHECKED == IsDlgButtonChecked(IDC_CHK_PRESET_SNAP)?1:0;
	int iScanVideoEnable = BST_CHECKED == IsDlgButtonChecked(IDC_CHK_SCAN_VIDEO)?1:0;
	int iModelPathEnable = BST_CHECKED == IsDlgButtonChecked(IDC_CHK_MODELPATH_VIDEO)?1:0;
	SetDomePTZ(DOME_PTZ_TYPE_LINK_DISJUNCTOR, 0, iPresetSnapEnable|iScanVideoEnable<<1|iModelPathEnable<<2);
}

void CLS_DomeBasicInfo::OnBnClickedChkScaleZoom()
{
	SetDomePTZ(DOME_PTZ_TYPE_SCALE_ZOOM, IsDlgButtonChecked(IDC_CHK_SCALE_ZOOM));
}

void CLS_DomeBasicInfo::OnBnClickedChkScanVideo()
{
	//启用扫描录像 同 启用预置位抓拍
	OnBnClickedChkPresetSnap();
}

void CLS_DomeBasicInfo::OnBnClickedChkModelpathVideo()
{
	//启用模式路径录像 同 启用预置位抓拍
	OnBnClickedChkPresetSnap();
}

void CLS_DomeBasicInfo::OnCbnSelchangeCboAngleSet()
{
	SetDomeMenu(DOME_PARA_VERTICAL_ANGLE_ADJUSTMENT, (int)m_cboAngleSet.GetItemData(m_cboAngleSet.GetCurSel()));
}

void CLS_DomeBasicInfo::OnCbnSelchangeComboManualSpeedRating()
{
	SetDomePTZ(DOME_PTZ_TYPE_MANUL_SEPPD_LEVEL, 1, m_cboManualSpeed.GetCurSel());
}

void CLS_DomeBasicInfo::OnCbnSelchangeComboZoomSpeedRating()
{
	SetDomeMenu(DOME_PARA_ZOOM_SPEED, m_cboZoomSpeed.GetCurSel());
}

void CLS_DomeBasicInfo::OnCbnSelchangeCboHeatMode()
{
	SetDomeMenu(DOME_PARA_TEMPERATURE_CONTROL_MODE, (int)m_cboHeatMode.GetItemData(m_cboHeatMode.GetCurSel()));
}

void CLS_DomeBasicInfo::OnCbnSelchangeComboTimeAutoStop()
{
	SetDomeMenu(DOME_PARA_AUTOMATIC_STOP_TIME, (int)m_cboAutoStopTime.GetItemData(m_cboAutoStopTime.GetCurSel()));
}

void CLS_DomeBasicInfo::OnCbnSelchangeComboPresetSpeedRating()
{
	SetDomePTZ(DOME_PTZ_TYPE_PRESET_SPEED_LEVE, 1, m_cboPresetSpeed.GetCurSel());
}

//云台优先 下拉框
void CLS_DomeBasicInfo::OnCbnSelchangeCboDadoPriority()
{
	SetDomeMenu(DOME_PARA_PTZ_PRIOR, (int)m_cboDadoPRI.GetItemData(m_cboDadoPRI.GetCurSel()), m_sldPRIDelayTime.GetPos());
}

//延时时间
void CLS_DomeBasicInfo::OnNMCustomdrawSldPriDelayTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	int iPos = m_sldPRIDelayTime.GetPos();
	SetDlgItemInt(IDC_STC_PRI_DELAY_TIME_TEXT, iPos);
	*pResult = 0;
}

//设置云台优先 延时时间
void CLS_DomeBasicInfo::OnBnClickedBtnPriDelayTime()
{
	OnCbnSelchangeCboDadoPriority();
}


void CLS_DomeBasicInfo::OnCbnSelchangeCbo485()
{
	SetDomeMenu(DOME_PARA_485_ADDRESS_SETTING, m_cbo485.GetCurSel());
}

void CLS_DomeBasicInfo::OnCbnSelchangeCboNoElectricityMemory()
{
	SetDomeMenu(DOME_PARA_OUTAGE_MEMORY, (int)m_cboNoElectricityMemory.GetItemData(m_cboNoElectricityMemory.GetCurSel()));
}

void CLS_DomeBasicInfo::OnCbnSelchangeCboVideoTurn()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error (%d)", m_iLogonID, GetLastError());
		return;
	}

	int iOldType = -1;
	NetClient_GetCommonEnable(m_iLogonID, CI_COMMON_ID_VIDEO_REVERSE, m_iChannelNo, &iOldType);
	int iNewType = m_cboVideoTurn.GetCurSel();
	if (iNewType != iOldType)
	{
		int iRet = NetClient_SetCommonEnable(m_iLogonID, CI_COMMON_ID_VIDEO_REVERSE, m_iChannelNo, iNewType);
		if (iRet != 0)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_SetCommonEnable[CI_COMMON_ID_VIDEO_REVERSE] (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNo, iNewType, GetLastError());
		}
	}
}

void CLS_DomeBasicInfo::OnBnClickedCheckAwateAction()
{
	SetDomePTZ(DOME_PTZ_TYPE_WAIT_ACT, m_chkAwateAction.GetCheck(), GetDlgItemInt(IDC_COMBO_AWATE_TIME), m_cboAwateAction.GetCurSel());
}

void CLS_DomeBasicInfo::OnBnClickedButtonSetWaiteAction()
{
	SetDomePTZ(DOME_PTZ_TYPE_WAIT_ACT, m_chkAwateAction.GetCheck(), GetDlgItemInt(IDC_COMBO_AWATE_TIME), m_cboAwateAction.GetCurSel());
}
