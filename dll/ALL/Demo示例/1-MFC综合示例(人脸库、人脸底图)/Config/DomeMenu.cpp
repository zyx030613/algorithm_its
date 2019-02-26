// DomeMenu.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "DomeMenu.h"


// CLS_DomeMenu dialog

IMPLEMENT_DYNAMIC(CLS_DomeMenu, CDialog)

CLS_DomeMenu::CLS_DomeMenu(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DomeMenu::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNO = 0;
}

CLS_DomeMenu::~CLS_DomeMenu()
{
}

void CLS_DomeMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DOME_TYPE, m_cboDomeType);
	DDX_Control(pDX, IDC_EDIT_DOME_PARA1, m_edtDomePara[0]);
	DDX_Control(pDX, IDC_EDIT_DOME_PARA2, m_edtDomePara[1]);
	DDX_Control(pDX, IDC_EDIT_DOME_PARA3, m_edtDomePara[2]);
	DDX_Control(pDX, IDC_EDIT_DOME_PARA4, m_edtDomePara[3]);
}


BEGIN_MESSAGE_MAP(CLS_DomeMenu, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DOME_PARA_SET, &CLS_DomeMenu::OnBnClickedButtonDomeParaSet)
	ON_CBN_SELCHANGE(IDC_COMBO_DOME_TYPE, &CLS_DomeMenu::OnCbnSelchangeComboDomeType)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CLS_DomeMenu message handlers

BOOL CLS_DomeMenu::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UI_UpdateDialog();
	for (int i = 0; i < 4; i++)
	{
		m_edtDomePara[i].SetLimitText(64);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_DomeMenu::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;

	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo =  _iChannelNo;
	}

	if (_iStreamNo < 0)
	{
		m_iStreamNO = 0;
	}
	else
	{
		m_iStreamNO = _iStreamNo;
	}
}

void CLS_DomeMenu::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

void CLS_DomeMenu::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNo == -1)
	{
		return;
	}

	int iParaType = m_cboDomeType.GetCurSel() + 1;
	TDomeParam DomeParam = {0};
	int iBytesReturned = 0;
	DomeParam.iType = iParaType;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo, &DomeParam, sizeof(TDomeParam), &iBytesReturned);
	if (iRet < 0 )
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DomeMenu::UpdatePageU] Get fail,error = %d", GetLastError());
	}
	else
	{
		SetDlgItemInt(IDC_EDIT_DOME_PARA1, DomeParam.iParam1);
		SetDlgItemInt(IDC_EDIT_DOME_PARA2, DomeParam.iParam2);
		SetDlgItemInt(IDC_EDIT_DOME_PARA3, DomeParam.iParam3);
		SetDlgItemInt(IDC_EDIT_DOME_PARA4, DomeParam.iParam4);
	}	
}

void CLS_DomeMenu::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
{
	switch(_iParaType)
	{
	case PARA_DOME_MENU:
		UpdatePageUI();
		break;
	default:
		break;
	}
}

void CLS_DomeMenu::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_DOME_PARA_TYPE, IDS_CONFIG_ITS_TIMERANGE_TYPE);
	SetDlgItemTextEx(IDC_STATIC_DOME_PARA1, IDS_CONFIG_ITS_TIMERANGE_PARAM1);
	SetDlgItemTextEx(IDC_STATIC_DOME_PARA2, IDS_CONFIG_ITS_TIMERANGE_PARAM2);
	SetDlgItemTextEx(IDC_STATIC_DOME_PARA3, IDS_CONFIG_ITS_TIMERANGE_PARAM3);
	SetDlgItemTextEx(IDC_STATIC_DOME_PARA4, IDS_CONFIG_ITS_TIMERANGE_PARAM4);
	SetDlgItemTextEx(IDC_BUTTON_DOME_PARA_SET, IDS_SET);

	m_cboDomeType.ResetContent();
	//1--预置位标题显示时间;2--自动功能标题显示时间;3--区域标题显示时间;4--坐标方向显示时间;
	//5--跟踪点标题显示时间;6--标题背景;7--自动停止时间;8--菜单关闭时间;9--垂直角度调整;10--操控速度等级;
	m_cboDomeType.InsertString(0, "1--"+GetTextEx(IDS_PRESET_TITLE_DISPLAY_TIME));
	m_cboDomeType.InsertString(1, "2--"+GetTextEx(IDS_AUTOMATIC_FUNCTION_TITLE_DISPLAY_TIME));
	m_cboDomeType.InsertString(2, "3--"+GetTextEx(IDS_REGION_TITLE_DISPLAY_TIME));
	m_cboDomeType.InsertString(3, "4--"+GetTextEx(IDS_COORDINATE_DIRECTION_DISPLAY_TIME));
	m_cboDomeType.InsertString(4, "5--"+GetTextEx(IDS_TRACEPOINTS_DISPLAY_TIME));
	m_cboDomeType.InsertString(5, "6--"+GetTextEx(IDS_TITLE_BACKGROUND));
	m_cboDomeType.InsertString(6, "7--"+GetTextEx(IDS_AUTOMATIC_STOP_TIME));
	m_cboDomeType.InsertString(7, "8--"+GetTextEx(IDS_MENU_OFF_TIME));
	m_cboDomeType.InsertString(8, "9--"+GetTextEx(IDS_VERTICAL_ANGLE_ADJUSTMENT));
	m_cboDomeType.InsertString(9, "10--"+GetTextEx(IDS_MANIPULATION_SPEED_RATING));
	//11--预置位速度等级;12--温度控制模式;13--485地址设置;14--零点设置;15--指北设置;
	//16--控制方式;17--感光阈值;18--延时时间;19--变倍匹配;20--预置位;
	m_cboDomeType.InsertString(10, "11--"+GetTextEx(IDS_PRESET_SPEED_RATING));
	m_cboDomeType.InsertString(11, "12--"+GetTextEx(IDS_TEMPERATURE_CONTROL_MODE));
	m_cboDomeType.InsertString(12, "13--"+GetTextEx(IDS_485_ADDRESS_SETTING));
	m_cboDomeType.InsertString(13, "14--"+GetTextEx(IDS_ZERO_SETTING));
	m_cboDomeType.InsertString(14, "15--"+GetTextEx(IDS_NORTH_SETTING));
	m_cboDomeType.InsertString(15, "16--"+GetTextEx(IDS_CONTROL_MODE));
	m_cboDomeType.InsertString(16, "17--"+GetTextEx(IDS_SENSITIVE_THRESHOLD));
	m_cboDomeType.InsertString(17, "18--"+GetTextEx(IDS_DELAY_TIME));
	m_cboDomeType.InsertString(18, "19--"+GetTextEx(IDS_ZOOM_MATCH));
	m_cboDomeType.InsertString(19, "20--"+GetTextEx(IDS_PRESET));
	//21--扫描;22--模式路径;23--模式路径当前状态;24--区域指示;25--变倍速度;26--数字变倍;
	//27--预置位冻结28--激光器亮度阈值;29--激光器同轴设置;30--设置可见光束打开时间;
	m_cboDomeType.InsertString(20, "21--"+GetTextEx(IDS_SCANNING));
	m_cboDomeType.InsertString(21, "22--"+GetTextEx(IDS_SCHEMA_PATH));
	m_cboDomeType.InsertString(22, "23--"+GetTextEx(IDS_SCHEMA_PATH_CURRENT_STATE));
	m_cboDomeType.InsertString(23, "24--"+GetTextEx(IDS_REGIONAL_INDICATIVE));
	m_cboDomeType.InsertString(24, "25--"+GetTextEx(IDS_ZOOM_SPEED));
	m_cboDomeType.InsertString(25, "26--"+GetTextEx(IDS_DIGITAL_ZOOM));
	m_cboDomeType.InsertString(26, "27--"+GetTextEx(IDS_PRESET_FROZEN));
	m_cboDomeType.InsertString(27, "28--"+GetTextEx(IDS_LASER_LIGHT));
	m_cboDomeType.InsertString(28, "29--"+GetTextEx(IDS_LASER_COAXIAL));
	m_cboDomeType.InsertString(29, "30--"+GetTextEx(IDS_VISIBLE_LIGHT_OPENTIME));
	//31--键控限位设置;32--掉电记忆模式;33--云台优先;34--键控限位启用
	m_cboDomeType.InsertString(30, "31--"+GetTextEx(IDS_KEYING_LIMIT));
	m_cboDomeType.InsertString(31, "32--"+GetTextEx(IDS_OUTAGE_MEMORY));
	m_cboDomeType.InsertString(32, "33--"+GetTextEx(IDS_PTZ_PRIOR));
	m_cboDomeType.InsertString(33, "34--"+GetTextEx(IDS_KEYING_USING));
	m_cboDomeType.SetCurSel(0);
}

void CLS_DomeMenu::OnBnClickedButtonDomeParaSet()
{
	// TODO: Add your control notification handler code here
	int iParaTye = m_cboDomeType.GetCurSel() + 1;
	TDomeParam TDomeParam = {0};
	TDomeParam.iType = iParaTye;
	TDomeParam.iParam1 = GetDlgItemInt(IDC_EDIT_DOME_PARA1);
	TDomeParam.iParam2 = GetDlgItemInt(IDC_EDIT_DOME_PARA2);
	TDomeParam.iParam3 = GetDlgItemInt(IDC_EDIT_DOME_PARA3);
	TDomeParam.iParam4 = GetDlgItemInt(IDC_EDIT_DOME_PARA4);

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo, &TDomeParam, sizeof(TDomeParam));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DomeMenu::OnBnClickedButtonDomeParaSet()] Set fail,error = %d", GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "[CLS_DomeMenu::OnBnClickedButtonDomeParaSet()] set success!");
	}
}

void CLS_DomeMenu::OnCbnSelchangeComboDomeType()
{
	// TODO: Add your control notification handler code here
	UpdatePageUI();
}

void CLS_DomeMenu::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	UpdatePageUI();
}
