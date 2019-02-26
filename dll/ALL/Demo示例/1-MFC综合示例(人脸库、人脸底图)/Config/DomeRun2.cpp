// DomeRun2.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "DomeRun2.h"


//模式路径操作：0-开始、1-结束、2-删除、3-调用
#define SCHEMA_PATH_START	0
#define SCHEMA_PATH_OVER	1
#define SCHEMA_PATH_DELETE	2
#define SCHEMA_PATH_CALL	3

//区域指示 操作：0-左边界、1-右边界、2-删除
#define AREA_BRODER_LEFT	0
#define AREA_BRODER_RIGHT	1
#define AREA_BRODER_DELETE	2

//键控限位设置 0 -不启用 1- 启用限位 2-设置限位 3 - 清除限位
#define  DOME_PARA_DISENABLE_LIMIT	0 
#define  DOME_PARA_ENABLE_LIMIT		1

#define  DOME_PARA_SET_LIMIT		0 
#define  DOME_PARA_DELECT_LIMIT		1

// CLS_DomeRun2 dialog

IMPLEMENT_DYNAMIC(CLS_DomeRun2, CDialog)

CLS_DomeRun2::CLS_DomeRun2(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DomeRun2::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNO = -1;
	m_blSchemaPath = false;
}

CLS_DomeRun2::~CLS_DomeRun2()
{
}

void CLS_DomeRun2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SCHEMAPATH_NO, m_cboSchemaPathNo);
	DDX_Control(pDX, IDC_COMBO_AREA_NO, m_cboAreaNo);
	DDX_Control(pDX, IDC_CHECK_LIMIT_ENABEL, m_chkLimitEnable);
	DDX_Control(pDX, IDC_COMBO_LIMIT_STATUS, m_cboLimitStatus);
}


BEGIN_MESSAGE_MAP(CLS_DomeRun2, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_SCHEMAPATH_NO, &CLS_DomeRun2::OnCbnSelchangeComboSchemapathNo)
	ON_BN_CLICKED(IDC_BUTTON_SCHEMAPATH_CALL, &CLS_DomeRun2::OnBnClickedButtonSchemapathCall)
	ON_BN_CLICKED(IDC_BUTTON_SCHEMAPATH_START_REC, &CLS_DomeRun2::OnBnClickedButtonSchemapathStartRec)
	ON_BN_CLICKED(IDC_BUTTON_SCHEMAPATH_STOP_REC, &CLS_DomeRun2::OnBnClickedButtonSchemapathStopRec)
	ON_BN_CLICKED(IDC_BUTTON_DELSCHEMAPATH, &CLS_DomeRun2::OnBnClickedButtonDelschemapath)
	ON_CBN_SELCHANGE(IDC_COMBO_AREA_NO, &CLS_DomeRun2::OnCbnSelchangeComboAreaNo)
	ON_BN_CLICKED(IDC_BUTTON_AREA_BRODR_LEFT, &CLS_DomeRun2::OnBnClickedButtonAreaBrodrLeft)
	ON_BN_CLICKED(IDC_BUTTON_AREA_BRODER_RIGHT, &CLS_DomeRun2::OnBnClickedButtonAreaBroderRight)
	ON_BN_CLICKED(IDC_BUTTON_DELAREA, &CLS_DomeRun2::OnBnClickedButtonDelarea)
	ON_BN_CLICKED(IDC_CHECK_LIMIT_ENABEL, &CLS_DomeRun2::OnBnClickedCheckLimitEnabel)
	ON_BN_CLICKED(IDC_BUTTON_LIMIT_SET, &CLS_DomeRun2::OnBnClickedButtonLimitSet)
	ON_BN_CLICKED(IDC_BUTTON_LIMIT_DELETE, &CLS_DomeRun2::OnBnClickedButtonLimitDelete)
	ON_BN_CLICKED(IDC_BUTTON_ZERO, &CLS_DomeRun2::OnBnClickedButtonZero)
	ON_BN_CLICKED(IDC_BUTTON_NORTH, &CLS_DomeRun2::OnBnClickedButtonNorth)
END_MESSAGE_MAP()


// CLS_DomeRun2 message handlers

BOOL CLS_DomeRun2::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UI_UpdateDialogText();
	UpdateSchemaPathInfo();
	UpdateLimitInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_DomeRun2::OnChannelChanged(int _iLogonID, int _iChannelNo, int _iStreamNo)
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
	UpdateSchemaPathInfo();
	UpdateLimitInfo();
}

void CLS_DomeRun2::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialogText();
	UpdateSchemaPathInfo();
	UpdateLimitInfo();
}

void CLS_DomeRun2::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara, int _iUserData)
{
	int* iType = (int*)_pPara;
	if (_iChannelNo == m_iChannelNo)//只刷新参数改变的通道
	{
		switch(_iParaType)
		{
		case PARA_DOME_MENU:
			{
				if (*iType == DOME_PARA_SCHEMA_PATH_CURRENT_STATE)
				{
					UpdateSchemaPathInfo();
				}
				
				UpdateLimitInfo();
			}
			break;
		default:
			break;
		}
	}
}

void CLS_DomeRun2::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_STATIC_SCHEMAPATH, IDS_SCHEMA_PATH);
	SetDlgItemTextEx(IDC_STATIC_SCHEMAPATH_NO, IDS_DOME_MODEPATH_NO);
	SetDlgItemTextEx(IDC_STATIC_SCHEMAPATH_STORAGE, IDS_DOME_STORARY_USED);
	SetDlgItemTextEx(IDC_STATIC_SCHEMAPATH_LEFTTIME, IDS_DOME_SCHEMAPATH_LEFTTIME);
	SetDlgItemTextEx(IDC_STATIC_AREA, IDS_REGIONAL_INDICATIVE);
	SetDlgItemTextEx(IDC_STATIC_AREA_NO, IDS_DOME_AREA_NO);
	SetDlgItemTextEx(IDC_STATIC_LIMIT, IDS_DEMO_LIMIT);
	SetDlgItemTextEx(IDC_CHECK_LIMIT_ENABEL, IDS_DOME_RUN_LIMIT_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_LIMIT_STATUS, IDS_DOME_RUN_LIMIT_STATUS);
	SetDlgItemTextEx(IDC_BUTTON_SCHEMAPATH_CALL, IDS_PREVIEW_CALL_PREVIEW);
	SetDlgItemTextEx(IDC_BUTTON_SCHEMAPATH_START_REC, IDS_SCHEMAPATH_START_REC);
	SetDlgItemTextEx(IDC_BUTTON_SCHEMAPATH_STOP_REC, IDS_SCHEMAPATH_STOP_REC);
	SetDlgItemTextEx(IDC_BUTTON_DELSCHEMAPATH, IDS_POWER_DEV_LST_DELETE);
	SetDlgItemTextEx(IDC_BUTTON_AREA_BRODR_LEFT, IDS_DOME_BRODER_LEFT);
	SetDlgItemTextEx(IDC_BUTTON_AREA_BRODER_RIGHT, IDS_DOME_BRODER_RIGHT);
	SetDlgItemTextEx(IDC_BUTTON_DELAREA, IDS_POWER_DEV_LST_DELETE);
	SetDlgItemTextEx(IDC_BUTTON_LIMIT_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_LIMIT_DELETE, IDS_POWER_DEV_LST_DELETE);
	SetDlgItemTextEx(IDC_BUTTON_ZERO, IDS_ZERO_SET);
	SetDlgItemTextEx(IDC_BUTTON_NORTH, IDS_NORTH_SET);

	//模式路径
	m_cboSchemaPathNo.ResetContent();
	for (int i=0; i<8; i++)
	{
		m_cboSchemaPathNo.AddString(IntToCString(i+1));
	}
	m_cboSchemaPathNo.SetCurSel(0);

	//区域指示
	m_cboAreaNo.ResetContent();
	for (int i=0; i<8; i++)
	{
		m_cboAreaNo.AddString(IntToCString(i+1));
	}
	m_cboAreaNo.SetCurSel(0);

	m_cboLimitStatus.ResetContent();
	m_cboLimitStatus.AddString(GetTextEx(IDS_DOME_RUN_LIMIT_STATUS_OFF));
	m_cboLimitStatus.AddString(GetTextEx(IDS_DOME_RUN_LIMIT_STATUS_ON));
	m_cboLimitStatus.SetCurSel(0);
	m_cboLimitStatus.EnableWindow(FALSE);
}

void CLS_DomeRun2::UpdateSchemaPathInfo()
{
	if (!m_blSchemaPath)
	{
		return;
	}

	TDomeParam tParam;
	memset(&tParam, 0, sizeof(TDomeParam));
	tParam.iType = DOME_PARA_SCHEMA_PATH_CURRENT_STATE;
	tParam.iParam1 = m_cboSchemaPathNo.GetCurSel();
	GetDomeMenu(tParam);
	GetDlgItem(IDC_EDT_SCHEMAPATH_STORAGE)->SetWindowText(IntToCString(tParam.iParam2));
	GetDlgItem(IDC_EDT_SCHEMAPATH_LEFTTIME)->SetWindowText(IntToCString(tParam.iParam3));
	if (tParam.iType == DOME_PARA_SCHEMA_PATH_CURRENT_STATE)
	{
		if (tParam.iParam2 >= 100 || tParam.iParam3 <= 0)
		{
			GetDlgItem(IDC_BUTTON_SCHEMAPATH_START_REC)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_SCHEMAPATH_STOP_REC)->EnableWindow(FALSE);
			//数据清空
			SetDlgItemText(IDC_EDT_SCHEMAPATH_STORAGE, "-");
			SetDlgItemText(IDC_EDT_SCHEMAPATH_LEFTTIME, "-");
		}
		else
		{
			GetDlgItem(IDC_BUTTON_SCHEMAPATH_START_REC)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_SCHEMAPATH_STOP_REC)->EnableWindow(TRUE);
		}
	}
}	

void CLS_DomeRun2::UpdateLimitInfo()
{
	TDomeParam tParam = {0};
	//获取限位信息
	tParam.iType = DOME_PARA_KEYING_LIMIT;
	GetDomeMenu(tParam);
	int iLimitStatu = tParam.iParam3;
	if (iLimitStatu>-1 && iLimitStatu<m_cboLimitStatus.GetCount())
	{
		m_cboLimitStatus.SetCurSel(iLimitStatu);
	}

	ZeroMemory(&tParam, sizeof(TDomeParam));
	tParam.iType = DOME_PARA_KEYING_USING;
	GetDomeMenu(tParam);
	m_chkLimitEnable.SetCheck(tParam.iParam1);
}

void CLS_DomeRun2::SetDomeMenu( TDomeParam& _tParam )
{ 
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error (%d)", m_iLogonID, GetLastError());
		return;
	}

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo, &_tParam, sizeof(TDomeParam));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d, %d)", m_iLogonID, m_iChannelNo,  _tParam.iType);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNo, _tParam.iType, GetLastError());
	}
}

int CLS_DomeRun2::GetDomeMenu( TDomeParam& _tParam )
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
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d, %d)", m_iLogonID, m_iChannelNo, _tParam.iType);
	}

	return iRet;
}

void CLS_DomeRun2::OnCbnSelchangeComboSchemapathNo()
{
	// TODO: Add your control notification handler code here
}

void CLS_DomeRun2::OnBnClickedButtonSchemapathCall()
{
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_SCHEMA_PATH;
	tParam.iParam1 = m_cboSchemaPathNo.GetCurSel();
	tParam.iParam2 = SCHEMA_PATH_CALL;
	SetDomeMenu(tParam);
}

void CLS_DomeRun2::OnBnClickedButtonSchemapathStartRec()
{
	int iType = SCHEMA_PATH_START;
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_SCHEMA_PATH;
	tParam.iParam1 = m_cboSchemaPathNo.GetCurSel();
	tParam.iParam2 = iType;
	SetDomeMenu(tParam);

	GetDlgItem(IDC_COMBO_SCHEMAPATH_NO)->EnableWindow(FALSE);	
	GetDlgItem(IDC_BUTTON_SCHEMAPATH_START_REC)->EnableWindow(FALSE);	
	GetDlgItem(IDC_BUTTON_SCHEMAPATH_STOP_REC)->EnableWindow(TRUE);
	m_blSchemaPath = true;
}

void CLS_DomeRun2::OnBnClickedButtonSchemapathStopRec()
{
	// TODO: Add your control notification handler code here
	int iType = SCHEMA_PATH_OVER;	
	//数据清空
	SetDlgItemText(IDC_EDT_SCHEMAPATH_STORAGE, "-");
	SetDlgItemText(IDC_EDT_SCHEMAPATH_LEFTTIME, "-");

	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_SCHEMA_PATH;
	tParam.iParam1 = m_cboSchemaPathNo.GetCurSel();
	tParam.iParam2 = iType;
	SetDomeMenu(tParam);

		GetDlgItem(IDC_COMBO_SCHEMAPATH_NO)->EnableWindow(TRUE);	
	GetDlgItem(IDC_BUTTON_SCHEMAPATH_START_REC)->EnableWindow(TRUE);	
	GetDlgItem(IDC_BUTTON_SCHEMAPATH_STOP_REC)->EnableWindow(FALSE);
	m_blSchemaPath = false;
}

void CLS_DomeRun2::OnBnClickedButtonDelschemapath()
{
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_SCHEMA_PATH;
	tParam.iParam1 = m_cboSchemaPathNo.GetCurSel();
	tParam.iParam2 = SCHEMA_PATH_DELETE;
	SetDomeMenu(tParam);
}

void CLS_DomeRun2::OnCbnSelchangeComboAreaNo()
{
	// TODO: Add your control notification handler code here
}

void CLS_DomeRun2::OnBnClickedButtonAreaBrodrLeft()
{
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_REGIONAL_INDICATIVE;
	tParam.iParam1 = m_cboAreaNo.GetCurSel();
	tParam.iParam2 = AREA_BRODER_LEFT;
	SetDomeMenu(tParam);
}

void CLS_DomeRun2::OnBnClickedButtonAreaBroderRight()
{
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_REGIONAL_INDICATIVE;
	tParam.iParam1 = m_cboAreaNo.GetCurSel();
	tParam.iParam2 = AREA_BRODER_RIGHT;
	SetDomeMenu(tParam);
}

void CLS_DomeRun2::OnBnClickedButtonDelarea()
{
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_REGIONAL_INDICATIVE;
	tParam.iParam1 = m_cboAreaNo.GetCurSel();
	tParam.iParam2 = AREA_BRODER_DELETE;
	SetDomeMenu(tParam);
}

void CLS_DomeRun2::OnBnClickedCheckLimitEnabel()
{
	TDomeParam tParam;
	memset(&tParam, 0, sizeof(TDomeParam));
	tParam.iType = DOME_PARA_KEYING_USING;
	tParam.iParam1 = m_chkLimitEnable.GetCheck()==0 ? DOME_PARA_DISENABLE_LIMIT : DOME_PARA_ENABLE_LIMIT;
	SetDomeMenu(tParam);
}

void CLS_DomeRun2::OnBnClickedButtonLimitSet()
{
	TDomeParam tParam = {0};
	memset(&tParam, 0, sizeof(TDomeParam));
	tParam.iType = DOME_PARA_KEYING_LIMIT;
	tParam.iParam1 = DOME_PARA_SET_LIMIT;
	SetDomeMenu(tParam);
}

void CLS_DomeRun2::OnBnClickedButtonLimitDelete()
{
	TDomeParam tParam;
	memset(&tParam, 0, sizeof(TDomeParam));
	tParam.iType = DOME_PARA_KEYING_LIMIT;
	tParam.iParam1 = DOME_PARA_DELECT_LIMIT;
	SetDomeMenu(tParam);
}

void CLS_DomeRun2::OnBnClickedButtonZero()
{
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_ZERO_SETTING;
	SetDomeMenu(tParam);
}

void CLS_DomeRun2::OnBnClickedButtonNorth()
{
	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_NORTH_SETTING;
	SetDomeMenu(tParam);
}
