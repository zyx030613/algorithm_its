// DomeRun.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "DomeRun1.h"

#define SCAN_SPEED	30	//最大扫描速度
#define MAX_SCREW_STEP	15 //螺旋扫描，设置步进的最大值 0-15
#define SCAN_LIST_PRESET_NUM	32	//巡航列表中最大预置位数目

//预置位操作：0-设置、1-删除、2-调用
#define PRESET_FOCUS_MODE_SET	0
#define PRESET_FOCUS_MODE_DEL	1
#define PRESET_FOCUS_MODE_CALL	2

//扫描类型 0-左右扫描、1-自动扫描、2-帧扫描、3-随机扫描、4-垂直扫描、5-全景扫描
#define SCAN_TYPE_LEFTANDRIGHT	0
#define SCAN_TYPE_AUTO			1
#define SCAN_TYPE_FRAME			2
#define SCAN_TYPE_RANDOM		3
#define SCAN_TYPE_VERTIAL		4
#define SCAN_TYPE_PANORAMIC		5
#define SCAN_TYPE_SCREW_SPEED	6 //螺旋扫描-设置速度
#define SCAN_TYPE_SCREW_STEP	7//螺旋扫描-设置步进

//扫描操作：0-左边界(上边界)、1-右边界(下边界)、2-调用
#define SCAN_BRODER_LEFT	0
#define SCAN_BRODER_RIGHT	1
#define SCAN_BRODER_CALL    2

// CLS_DomeRun dialog

IMPLEMENT_DYNAMIC(CLS_DomeRun1, CDialog)

CLS_DomeRun1::CLS_DomeRun1(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DomeRun1::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNO = -1;
	memset(&m_ptzCruise, 0, sizeof(st_PTZCruise));
	m_iCruiseNum = 0;
	m_iCruiseSpeed = 50;
}

CLS_DomeRun1::~CLS_DomeRun1()
{
}

void CLS_DomeRun1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PRESET_NO, m_cboPresetNo);
	DDX_Control(pDX, IDC_COMBO_FOUCUS_MODE, m_cboFocusMode);
	DDX_Control(pDX, IDC_COMBO_CRUISE_NO, m_cboCruiseNo);
	DDX_Control(pDX, IDC_EDT_CRUISE_LIST, m_edtCruiseList);
	DDX_Control(pDX, IDC_COMBO_CRUISE_PRESET_ADD, m_cboPreset);
	DDX_Control(pDX, IDC_COMBO_SCAN_NO, m_cboScanNo);
	DDX_Control(pDX, IDC_COMBO_SCAN_TYPE, m_cboScanType);
	DDX_Control(pDX, IDC_COMBO_SCAN_SPEED, m_cboScanSpeed);
	DDX_Control(pDX, IDC_CBO_VER_STEP, m_cboVerStep);
	DDX_Control(pDX, IDC_COMBO_CRUISE_TIME, m_cboCruiseTime);
}


BEGIN_MESSAGE_MAP(CLS_DomeRun1, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_PRESET_NO, &CLS_DomeRun1::OnCbnSelchangeComboPresetNo)
	ON_BN_CLICKED(IDC_BUTTON_PRESET_CALL, &CLS_DomeRun1::OnBnClickedButtonPresetCall)
	ON_BN_CLICKED(IDC_BUTTON_PRESET_SET, &CLS_DomeRun1::OnBnClickedButtonPresetSet)
	ON_BN_CLICKED(IDC_BUTTON_DEL_PRESET, &CLS_DomeRun1::OnBnClickedButtonDelPreset)
	ON_CBN_SELCHANGE(IDC_COMBO_CRUISE_NO, &CLS_DomeRun1::OnCbnSelchangeComboCruiseNo)
	ON_BN_CLICKED(IDC_BUTTON_CRUISE_CALL, &CLS_DomeRun1::OnBnClickedButtonCruiseCall)
	ON_BN_CLICKED(IDC_BUTTON_ADDPRESET, &CLS_DomeRun1::OnBnClickedButtonAddpreset)
	ON_BN_CLICKED(IDC_BUTTON_DELPRESET, &CLS_DomeRun1::OnBnClickedButtonDelpreset)
	ON_CBN_SELCHANGE(IDC_COMBO_SCAN_NO, &CLS_DomeRun1::OnCbnSelchangeComboScanNo)
	ON_CBN_SELCHANGE(IDC_COMBO_SCAN_TYPE, &CLS_DomeRun1::OnCbnSelchangeComboScanType)
	ON_BN_CLICKED(IDC_BUTTON_SCAN_CALL, &CLS_DomeRun1::OnBnClickedButtonScanCall)
	ON_BN_CLICKED(IDC_BUTTON_SCAN_BRODR_LEFT, &CLS_DomeRun1::OnBnClickedButtonScanBrodrLeft)
	ON_BN_CLICKED(IDC_BUTTON_SCAN_BRODER_RIGHT, &CLS_DomeRun1::OnBnClickedButtonScanBroderRight)
	ON_CBN_SELCHANGE(IDC_COMBO_CRUISE_TIME, &CLS_DomeRun1::OnCbnSelchangeComboCruiseTime)
END_MESSAGE_MAP()


// CLS_DomeRun message handlers

BOOL CLS_DomeRun1::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UI_UpdateDialogText();
	UpdateFocusMode();
	UpdateCruiseInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_DomeRun1::OnChannelChanged(int _iLogonID, int _iChannelNo, int _iStreamNo)
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
	UpdateFocusMode();
	UpdateScanDate();
	UpdateCruiseInfo();
}

void CLS_DomeRun1::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialogText();
	UpdateFocusMode();
	UpdateScanDate();
	UpdateCruiseInfo();
}

void CLS_DomeRun1::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara, int _iUserData)
{
	if (_iChannelNo == m_iChannelNo)//只刷新参数改变的通道
	{
		switch(_iParaType)
		{
		case PARA_DOME_MENU:
			{
				UpdateFocusMode();
			}
			break;
		default:
			break;
		}
	}
}

void CLS_DomeRun1::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_STATIC_PRESET_FOUCUS, IDS_PRESET);
	SetDlgItemTextEx(IDC_STATIC_CRUISE, IDS_DOME_ADV_CURISE);
	SetDlgItemTextEx(IDC_STATIC_PRESET, IDS_PRESET);
	SetDlgItemTextEx(IDC_STATIC_AUTO_SLOW_EXPO, IDS_DOME_ADV_SCAN);
	SetDlgItemTextEx(IDC_STATIC_PRESET_NO, IDS_CONFIG_ITS_ILLEGALPARK_PRESET);
	SetDlgItemTextEx(IDC_STATIC_FOUCUS_MODE, IDS_STATIC_FOCUS_MODE);
	SetDlgItemTextEx(IDC_STATIC_CRUISE_NO, IDS_DOME_CRUISE_NO);
	SetDlgItemTextEx(IDC_STATIC_CRUISE_LIST, IDS_DOME_CRUISE_LIST);
	SetDlgItemTextEx(IDC_STC_PRESET, IDS_PRESET);
	SetDlgItemTextEx(IDC_STATIC_SCAN_NO, IDS_DOME_SCAN_NO);
	SetDlgItemTextEx(IDC_STATIC_SCAN_TYPE, IDS_DOME_SCAN_TYPE);
	SetDlgItemTextEx(IDC_STATIC_SCAN_SPEED, IDS_DOME_SCAN_SPEED);
	SetDlgItemTextEx(IDC_STC_VER_STEP, IDS_VER_STEP);
	SetDlgItemTextEx(IDC_BUTTON_PRESET_CALL, IDS_PREVIEW_CALL_PREVIEW);
	SetDlgItemTextEx(IDC_BUTTON_PRESET_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_DEL_PRESET, IDS_POWER_DEV_LST_DELETE);
	SetDlgItemTextEx(IDC_BUTTON_CRUISE_CALL, IDS_PREVIEW_CALL_PREVIEW);
	SetDlgItemTextEx(IDC_BUTTON_ADDPRESET, IDS_ADD);
	SetDlgItemTextEx(IDC_BUTTON_DELPRESET, IDS_POWER_DEV_LST_DELETE);
	SetDlgItemTextEx(IDC_BUTTON_SCAN_CALL, IDS_PREVIEW_CALL_PREVIEW);
	SetDlgItemTextEx(IDC_BUTTON_SCAN_BRODR_LEFT, IDS_DOME_BRODER_LEFT);
	SetDlgItemTextEx(IDC_BUTTON_SCAN_BRODER_RIGHT, IDS_DOME_BRODER_RIGHT);
	SetDlgItemTextEx(IDC_STATIC_CRUISE_TIME, IDS_PTZCRUISE_STAYTIME);

	//预置位
	m_cboPresetNo.ResetContent();
	for (int i=0; i<500; i++)
	{
		//特殊预置位65~99不添加
		if (i>=64 && i<=98)
		{
			continue;
		}
		m_cboPresetNo.AddString(IntToStr(i+1).c_str());
	}
	m_cboPresetNo.SetCurSel(0);

	//聚焦模式
	m_cboFocusMode.ResetContent();
	m_cboFocusMode.AddString(GetTextEx(IDS_DOME_AUTO));
	m_cboFocusMode.AddString(GetTextEx(IDS_STATIONARY));
	m_cboFocusMode.SetCurSel(0);
	UpdateFocusMode();

	//自动巡航
	m_cboCruiseNo.ResetContent();
	for (int i=0; i<16; i++)
	{
		m_cboCruiseNo.AddString(IntToCString(i+1));
	}
	m_cboCruiseNo.SetCurSel(0);

	//预置位
	m_cboPreset.ResetContent();
	for (int i=0; i<500; i++)
	{
		//特殊预置位65~99不添加
		if (i>=64 && i<=98)
		{
			continue;
		}
		m_cboPreset.AddString(IntToStr(i+1).c_str());
	}
	m_cboPreset.SetCurSel(0);

	//巡航停留时间
	m_cboCruiseTime.ResetContent();
	for (int i=0; i<60; i++)
	{
		m_cboCruiseTime.AddString(IntToCString(i+1));
	}
	m_cboCruiseTime.SetCurSel(4);

	//自动扫描
	m_cboScanNo.ResetContent();
	for (int i=0; i<8; i++)
	{
		m_cboScanNo.AddString(IntToCString(i+1));
	}
	m_cboScanNo.SetCurSel(0);

	//扫描类型
	m_cboScanType.ResetContent();
	m_cboScanType.AddString(GetTextEx(IDS_SCAN_TYPE_LEFTANDRIGHT));	
	m_cboScanType.AddString(GetTextEx(IDS_SCAN_TYPE_AUTO));
	m_cboScanType.AddString(GetTextEx(IDS_SCAN_TYPE_FRAME));	
	m_cboScanType.AddString(GetTextEx(IDS_SCAN_TYPE_RANDOM));	
	m_cboScanType.AddString(GetTextEx(IDS_SCAN_TYPE_VERTIAL));	
	m_cboScanType.AddString(GetTextEx(IDS_SCAN_TYPE_PANORAMIC));	
	m_cboScanType.AddString(GetTextEx(IDS_SCAN_TYPE_SCREW));
	m_cboScanType.SetCurSel(0);

	//扫描速度
	m_cboScanSpeed.ResetContent();
	for (int i=0; i<SCAN_SPEED; i++)
	{
		m_cboScanSpeed.AddString(IntToCString(i+1));
	}
	m_cboScanSpeed.SetCurSel(19);

	CString strTmp;
	m_cboVerStep.ResetContent();
	for (int i = 0; i < MAX_SCREW_STEP; i++)
	{
		strTmp.Format("%d", i+1);
		int iIndex = m_cboVerStep.AddString(strTmp);
		m_cboVerStep.SetItemData(iIndex, i+1);
	}
	m_cboVerStep.SetCurSel(9);
}

void CLS_DomeRun1::UpdateFocusMode()
{
	if (m_iChannelNo < 0 || m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return ;
	}

	if (NetClient_GetDevConfig)
	{
		int iBytesReturned = 0;
		PTZList strctPtzList = {0};
		strctPtzList.iBufSize = sizeof(PTZList);
		strctPtzList.iChanNo = m_iChannelNo;
		int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_PTZLIST, m_iChannelNo, &strctPtzList, sizeof(strctPtzList), &iBytesReturned);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig[NET_CLIENT_PTZLIST] (%d, %d), error (%d)", m_iLogonID, m_iChannelNo, GetLastError());
		}
		else
		{
			CString cstrTmp;
			m_cboPresetNo.GetWindowText(cstrTmp);
			int iPTZIndex = atoi(cstrTmp);
			int iValue = strctPtzList.iFocusMode[iPTZIndex];
			if (iValue < 0)
			{
				iValue = 0;
			}
			m_cboFocusMode.SetCurSel(iValue);
		}
	}
}

void CLS_DomeRun1::UpdateCruiseInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error (%d)", m_iLogonID, GetLastError());
		return;
	}

	memset(&m_ptzCruise, 0, sizeof(st_PTZCruise));
	int iCruiseEna = 0;
	m_iCruiseNum = 0;
	if (NetClient_GetCHNPTZCRUISE)
	{
		int iRet = NetClient_GetCHNPTZCRUISE(m_iLogonID, m_iChannelNo, m_cboCruiseNo.GetCurSel(), &iCruiseEna, &m_iCruiseNum, &m_ptzCruise);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetCHNPTZCRUISE (%d, %d), error (%d) ", m_iLogonID, m_iChannelNo,GetLastError());
		}
		else
		{
			//显示巡航列表
			CString cstrList = "";
			for (int i=0; i<m_iCruiseNum; i++)
			{
				cstrList += IntToCString(m_ptzCruise.iPreset[i]);
				cstrList += " ";
			}

			GetDlgItem(IDC_EDT_CRUISE_LIST)->SetWindowText(cstrList);

			//更新预置位停留时间
			if (m_ptzCruise.iStayTime[0] > 0)
			{
				m_ptzCruise.iStayTime[0]--;
			}
			else if (m_ptzCruise.iStayTime[0] == 0)
			{
				m_ptzCruise.iStayTime[0] = 4;
			}
			m_cboCruiseTime.SetCurSel(m_ptzCruise.iStayTime[0]);
			m_cboPreset.SetCurSel(0);
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetCHNPTZCRUISE (%d, %d), error (%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}	
}

void CLS_DomeRun1::UpdateScanDate()
{
	//获取设置的扫描类型相关选项，然后初始化控件
	TDomeParam tparam = {0};
	tparam.iType = DOME_PARA_SCANNING;
	if (0 != GetDomeMenu(tparam))
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DomeRun1::UpdateScanDate][DOME_PARA_SCANNING] fail, error(%d)", GetLastError());
	}
	else
	{
		if (-1 != tparam.iParam1)
		{
			m_cboScanNo.SetCurSel(tparam.iParam1);
		}
		
		//类型为螺旋扫描速度设置
		if (tparam.iParam2 == SCAN_TYPE_SCREW_SPEED || tparam.iParam2 == SCAN_TYPE_SCREW_STEP)
		{
			GetDlgItem(IDC_CBO_VER_STEP)->EnableWindow(TRUE);
			m_cboScanType.SetCurSel(SCAN_TYPE_SCREW_SPEED);
			//iparam3高16位扫描速度，低16位垂直步进速度
			int iScanSpeed = (tparam.iParam3>>16 & 0xFFFF);
			int iVerStep = (tparam.iParam3 & 0xFFFF);
			if (iScanSpeed - 1 < 0)
			{
				iScanSpeed = 20;
			}
			m_cboScanSpeed.SetCurSel(iScanSpeed-1);

			if (iVerStep - 1 < 0)
			{
				iVerStep = 10;
			}
			m_cboVerStep.SetCurSel(iVerStep-1);
		}
		else
		{
			GetDlgItem(IDC_CBO_VER_STEP)->EnableWindow(FALSE);
			if (-1 != tparam.iParam2)
			{
				m_cboScanType.SetCurSel(tparam.iParam2);
			}
			if (tparam.iParam3-1 < 0)
			{
				tparam.iParam3 = 20;
			}
			m_cboScanSpeed.SetCurSel(tparam.iParam3-1);
		}
	}
	ChangeComboScanState();
} 

void CLS_DomeRun1::SetDomeMenu( TDomeParam& _tParam )
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error (%d)", m_iLogonID, GetLastError());
		return;
	}

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo, &_tParam, sizeof(TDomeParam));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d, %d)", m_iLogonID, m_iChannelNo, _tParam.iType);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d, %d), error (%d)",  m_iLogonID, m_iChannelNo, _tParam.iType, GetLastError());
	}
}

int CLS_DomeRun1::GetDomeMenu( TDomeParam& _tParam )
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
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNo, _tParam.iType, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d, %d)", m_iLogonID, m_iChannelNo,  _tParam.iType);
	}

	return iRet;
}

bool CLS_DomeRun1::IsDigistChannel(int _iChannelNO)
{
	int iChannelType = 0;
	if(NetClient_GetChannelProperty(m_iLogonID, _iChannelNO, GENERAL_CMD_GET_CHANNEL_TYPE,
		&iChannelType,sizeof(iChannelType)) == 0 && iChannelType == CHANNEL_TYPE_DIGITAL)
	{
		return true;
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetChannelProperty[GENERAL_CMD_GET_CHANNEL_TYPE] (%d, %d), error (%d)", m_iLogonID, m_iChannelNo, GetLastError());
		return false;
	}	
}

void CLS_DomeRun1::DevControl( int _iType, int _iPresetNo )
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error(%d)", m_iLogonID, GetLastError());
		return;
	}

	//先获取原来的协议类型
	int iComPort = 0;
	int iDevAddress = 0;
	char pcProtocol[256] = {0};
	if (NetClient_GetDeviceType(m_iLogonID, m_iChannelNo, &iComPort, &iDevAddress, pcProtocol) == 0)
	{
		if(strcmp(pcProtocol, "DOME_PLUS")==0 || strcmp(pcProtocol, "DOME_TIANDY")==0)
		{
			strcpy_s(pcProtocol, "DOME_PLUS");
		}
		//设置预置位
		int iComNo = 1;
		int iAddress = 0;
		char cDeviceType[64] = {0};
		int iRet = NetClient_GetDeviceType(m_iLogonID, m_iChannelNo, &iComNo, &iAddress, cDeviceType);
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_GetDeviceType (%d, %d, %d)", m_iLogonID, m_iChannelNo, cDeviceType);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetDeviceType (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNo, cDeviceType, GetLastError());
		}

		CONTROL_PARAM ctrlParam;
		memset(&ctrlParam,0,sizeof(CONTROL_PARAM));
		ctrlParam.m_iAddress = iDevAddress;
		ctrlParam.m_iPreset = _iPresetNo;
		iRet = m_tDevCtrl.GetCtrlCode(cDeviceType, _iType, &ctrlParam);
		int iRetCode=0; 
		if(iRet == 0)
		{
			//按通道控制
			if (IsDigistChannel(m_iChannelNo))
			{
				if (NetClient_DigitalChannelSend(m_iLogonID, m_iChannelNo, 
					(PUCHAR)(LPCTSTR)ctrlParam.m_btBuf, ctrlParam.m_iCount) == 0)
				{
				}
				else
				{
					AddLog(LOG_TYPE_FAIL,"","NetClient_DigitalChannelSend (%d, %d), error (%d)", m_iLogonID, m_iChannelNo, GetLastError());
				}
			}
			else
			{
				iRetCode = NetClient_ComSend(m_iLogonID, ctrlParam.m_btBuf, ctrlParam.m_iCount, 1);
				iRetCode = NetClient_ComSend(m_iLogonID, ctrlParam.m_btBuf, ctrlParam.m_iCount, 2);
			}
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetDeviceType (%d, %d), error (%d)", m_iLogonID, m_iChannelNo, GetLastError());
		}
	} 
}

void CLS_DomeRun1::OnCbnSelchangeComboPresetNo()
{
	UpdateFocusMode();
}

void CLS_DomeRun1::OnBnClickedButtonPresetCall()
{
	CString strPressNo ;
	m_cboPresetNo.GetWindowText(strPressNo);
	int iPresetNo = atoi(strPressNo);
	//设置预置位聚焦模式
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_PRESET;
	tParam.iParam1 = m_cboFocusMode.GetCurSel();
	tParam.iParam2 = iPresetNo;
	tParam.iParam3 = PRESET_FOCUS_MODE_CALL;
	SetDomeMenu(tParam);
}

void CLS_DomeRun1::OnBnClickedButtonPresetSet()
{
	//设置预置位
	CString strPressNo ;
	m_cboPresetNo.GetWindowText(strPressNo);
	int iPresetNo = atoi(strPressNo);
	//设置预置位聚焦模式
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_PRESET;
	tParam.iParam1 = m_cboFocusMode.GetCurSel();
	tParam.iParam2 = iPresetNo;
	tParam.iParam3 = PRESET_FOCUS_MODE_SET;
	SetDomeMenu(tParam);
}

void CLS_DomeRun1::OnBnClickedButtonDelPreset()
{
	CString strPressNo ;
	m_cboPresetNo.GetWindowText(strPressNo);
	int iPresetNo = atoi(strPressNo);
	//设置预置位聚焦模式
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_PRESET;
	tParam.iParam1 = 0;
	tParam.iParam2 =iPresetNo;
	tParam.iParam3 = PRESET_FOCUS_MODE_DEL;
	SetDomeMenu(tParam);
	UpdateFocusMode();
}

void CLS_DomeRun1::OnCbnSelchangeComboCruiseNo()
{
	UpdateCruiseInfo();
}

void CLS_DomeRun1::OnBnClickedButtonCruiseCall()
{
	//启动第N组巡航 Call_80 + Call_N + Call_98
	//停止第N组巡航 Call_96
	DevControl(CALL_VIEW, 96);
	int iCruiseNo = m_cboCruiseNo.GetCurSel();
	DevControl(CALL_VIEW, 80);
	DevControl(CALL_VIEW, iCruiseNo+1);
	DevControl(CALL_VIEW, 98);
}

void CLS_DomeRun1::OnBnClickedButtonAddpreset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error (%d)", m_iLogonID, GetLastError());
		return;
	}

	if (m_iCruiseNum >= SCAN_LIST_PRESET_NUM)
	{
		return;
	}

	int iCruiseSel = m_cboCruiseNo.GetCurSel();
	CString cstrPresetNo = "";
	m_cboPreset.GetWindowText(cstrPresetNo);
	int iPresetNo = atoi(cstrPresetNo);
	int iCruiseEna = 1;
	for (int i=0; i<=m_iCruiseNum; i++)
	{
		m_ptzCruise.iStayTime[i] = m_cboCruiseTime.GetCurSel()+1;
	}
	m_ptzCruise.iSpeed[m_iCruiseNum] = m_iCruiseSpeed;
	m_ptzCruise.iPreset[m_iCruiseNum] = iPresetNo;
	m_iCruiseNum++;
	int iRet = NetClient_SetCHNPTZCRUISE(m_iLogonID, m_iChannelNo, iCruiseSel, iCruiseEna, m_iCruiseNum, &m_ptzCruise);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetCHNPTZCRUISE (%d, %d), error (%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}
	else
	{
		//显示巡航列表
		CString cstrList = "";
		for (int i=0; i<m_iCruiseNum; i++)
		{
			cstrList += IntToCString(m_ptzCruise.iPreset[i]);
			cstrList += " ";
		}
		GetDlgItem(IDC_EDT_CRUISE_LIST)->SetWindowText(cstrList);
	}
}

void CLS_DomeRun1::OnBnClickedButtonDelpreset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error (%d)", m_iLogonID, GetLastError());
		return;
	}

	if (m_iCruiseNum - 1 < 0)
	{
		return;
	}

	int iCruiseSel = m_cboCruiseNo.GetCurSel();
	int iCruiseEna = 1;
	m_iCruiseNum--;
	m_ptzCruise.iSpeed[m_iCruiseNum] = 0;
	m_ptzCruise.iStayTime[m_iCruiseNum] = 0;
	m_ptzCruise.iPreset[m_iCruiseNum] = 0;
	int iRet = NetClient_SetCHNPTZCRUISE(m_iLogonID, m_iChannelNo, iCruiseSel, iCruiseEna, m_iCruiseNum, &m_ptzCruise);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetCHNPTZCRUISE (%d, %d), error (%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}
	else
	{
		//显示巡航列表
		CString cstrList = "";
		for (int i=0; i<m_iCruiseNum; i++)
		{
			cstrList += IntToCString(m_ptzCruise.iPreset[i]);
			cstrList += " ";
		}
		GetDlgItem(IDC_EDT_CRUISE_LIST)->SetWindowText(cstrList);
	}
}

//自动扫描编号
void CLS_DomeRun1::OnCbnSelchangeComboScanNo()
{
	TDomeParam tParam = {0};
	memset(&tParam, 0, sizeof(TDomeParam));
	tParam.iType = DOME_PARA_SCANNING;
	tParam.iParam1 = m_cboScanNo.GetCurSel();

	if(GetDomeMenu(tParam) == 0 && tParam.iType == DOME_PARA_SCANNING)
	{
		if (tParam.iParam2 == SCAN_TYPE_SCREW_SPEED || tParam.iParam2 == SCAN_TYPE_SCREW_STEP)
		{
			m_cboScanType.SetCurSel(SCAN_TYPE_SCREW_SPEED);
			//iparam3高16位扫描速度，低16位垂直步进速度
			int iScanSpeed = (tParam.iParam3>>16 & 0xFFFF);
			int iVerStep = (tParam.iParam3 & 0xFFFF);

			if (iScanSpeed - 1 < 0)
			{
				iScanSpeed = 20;
			}
			m_cboScanSpeed.SetCurSel(iScanSpeed-1);

			if (iVerStep - 1 < 0)
			{
				iVerStep = 10;
			}
			m_cboVerStep.SetCurSel(iVerStep-1);
		}
		else
		{
			m_cboScanType.SetCurSel(tParam.iParam2);
			if (tParam.iParam3-1 < 0)
			{
				tParam.iParam3 = 20;
			}
			m_cboScanSpeed.SetCurSel(tParam.iParam3-1);
		}
	}
}

void CLS_DomeRun1::OnCbnSelchangeComboScanType()
{
	TDomeParam tParam = {0};
	memset(&tParam, 0, sizeof(TDomeParam));
	tParam.iType = DOME_PARA_SCANNING;
	tParam.iParam1 = m_cboScanNo.GetCurSel();
	tParam.iParam2 = m_cboScanType.GetCurSel();

	if (m_cboScanType.GetCurSel() == SCAN_TYPE_SCREW_SPEED)
	{
		GetDlgItem(IDC_CBO_VER_STEP)->EnableWindow(TRUE);
		if(GetDomeMenu(tParam) == 0 && tParam.iType == DOME_PARA_SCANNING)
		{			
			if (tParam.iParam3-1 < 0)
			{
				tParam.iParam3 = 20;
			}
			m_cboScanSpeed.SetCurSel(tParam.iParam3-1);
		}

		tParam.iParam2 = SCAN_TYPE_SCREW_STEP;
		if(GetDomeMenu(tParam) == 0 && tParam.iType == DOME_PARA_SCANNING)
		{
			if (tParam.iParam3-1 < 0)
			{
				tParam.iParam3 = 10;
			}
			m_cboVerStep.SetCurSel(tParam.iParam3-1);
		}
	}
	else
	{
		GetDlgItem(IDC_CBO_VER_STEP)->EnableWindow(FALSE);
		if(GetDomeMenu(tParam) == 0 && tParam.iType == DOME_PARA_SCANNING)
		{
			if (tParam.iParam3-1 < 0)
			{
				tParam.iParam3 = 20;
			}
			m_cboScanSpeed.SetCurSel(tParam.iParam3-1);
		}
	}
	ChangeComboScanState();
}

void CLS_DomeRun1::ChangeComboScanState()
{
	if ((SCAN_TYPE_LEFTANDRIGHT == m_cboScanType.GetCurSel()) || (SCAN_TYPE_VERTIAL == m_cboScanType.GetCurSel()))
	{
		GetDlgItem(IDC_STATIC_SCAN_SPEED)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_SCAN_SPEED)->EnableWindow(TRUE);
		GetDlgItem(IDC_STC_VER_STEP)->EnableWindow(FALSE);
		GetDlgItem(IDC_CBO_VER_STEP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SCAN_BRODR_LEFT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SCAN_BRODER_RIGHT)->EnableWindow(TRUE);
	}
	else if ((SCAN_TYPE_AUTO == m_cboScanType.GetCurSel()) || (SCAN_TYPE_PANORAMIC == m_cboScanType.GetCurSel()))
	{
		GetDlgItem(IDC_STATIC_SCAN_SPEED)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_SCAN_SPEED)->EnableWindow(TRUE);
		GetDlgItem(IDC_STC_VER_STEP)->EnableWindow(FALSE);
		GetDlgItem(IDC_CBO_VER_STEP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SCAN_BRODR_LEFT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SCAN_BRODER_RIGHT)->EnableWindow(FALSE);
	}
	else if ((SCAN_TYPE_FRAME == m_cboScanType.GetCurSel()) || (SCAN_TYPE_RANDOM == m_cboScanType.GetCurSel()))
	{
		GetDlgItem(IDC_STATIC_SCAN_SPEED)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_SCAN_SPEED)->EnableWindow(FALSE);
		GetDlgItem(IDC_STC_VER_STEP)->EnableWindow(FALSE);
		GetDlgItem(IDC_CBO_VER_STEP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SCAN_BRODR_LEFT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SCAN_BRODER_RIGHT)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_SCAN_SPEED)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_SCAN_SPEED)->EnableWindow(TRUE);
		GetDlgItem(IDC_STC_VER_STEP)->EnableWindow(TRUE);
		GetDlgItem(IDC_CBO_VER_STEP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SCAN_BRODR_LEFT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SCAN_BRODER_RIGHT)->EnableWindow(TRUE);
	}
}

void CLS_DomeRun1::OnBnClickedButtonScanCall()
{
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_SCANNING;
	tParam.iParam1 = m_cboScanNo.GetCurSel();
	tParam.iParam2 = m_cboScanType.GetCurSel();
	tParam.iParam3 = m_cboScanSpeed.GetCurSel()+1;
	tParam.iParam4 = SCAN_BRODER_CALL;
	SetDomeMenu(tParam);
	if (m_cboScanType.GetCurSel() == SCAN_TYPE_SCREW_SPEED)
	{
		tParam.iParam2 = SCAN_TYPE_SCREW_STEP;
		tParam.iParam3 = (int)m_cboVerStep.GetItemData(m_cboVerStep.GetCurSel());

		SetDomeMenu(tParam);
	}
}

void CLS_DomeRun1::OnBnClickedButtonScanBrodrLeft()
{
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_SCANNING;
	tParam.iParam1 = m_cboScanNo.GetCurSel();
	tParam.iParam2 = m_cboScanType.GetCurSel();
	tParam.iParam3 = m_cboScanSpeed.GetCurSel()+1;
	tParam.iParam4 = SCAN_BRODER_LEFT;
	SetDomeMenu(tParam);
}

void CLS_DomeRun1::OnBnClickedButtonScanBroderRight()
{
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_SCANNING;
	tParam.iParam1 = m_cboScanNo.GetCurSel();
	tParam.iParam2 = m_cboScanType.GetCurSel();
	tParam.iParam3 = m_cboScanSpeed.GetCurSel()+1;
	tParam.iParam4 = SCAN_BRODER_RIGHT;
	SetDomeMenu(tParam);
}

void CLS_DomeRun1::OnCbnSelchangeComboCruiseTime()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error (%d)", m_iLogonID, GetLastError());
		return;
	}

	int iCruiseSel = m_cboCruiseNo.GetCurSel();
	int iCruiseEna = 1;
	for (int i=0; i<=m_iCruiseNum; i++)
	{
		m_ptzCruise.iStayTime[i] = m_cboCruiseTime.GetCurSel()+1;
	}
	int iRet = NetClient_SetCHNPTZCRUISE(m_iLogonID, m_iChannelNo, iCruiseSel, iCruiseEna, m_iCruiseNum, &m_ptzCruise);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetCHNPTZCRUISE (%d, %d), error (%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}
}