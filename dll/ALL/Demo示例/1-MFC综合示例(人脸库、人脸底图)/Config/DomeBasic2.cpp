// DomeBasic2.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "DomeBasic2.h"

//标题显示时间：0-关闭 1-持续 2-2秒 3-5秒 4-10秒  
#define TITLE_TIME_CLOSE	0	
#define TITLE_TIME_ALWAYS	0x7FFFFFFF
#define TITLE_TIME_2		2
#define TITLE_TIME_5		5
#define TITLE_TIME_10		10
// CLS_DomeBasic2 dialog

IMPLEMENT_DYNAMIC(CLS_DomeTitle, CDialog)

CLS_DomeTitle::CLS_DomeTitle(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DomeTitle::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNO = -1;
}

CLS_DomeTitle::~CLS_DomeTitle()
{
}

void CLS_DomeTitle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_TITLE_TYPE, m_cboTitleType);
	DDX_Control(pDX, IDC_COMBO_TITLE_NO, m_cboTitleNo);
	DDX_Control(pDX, IDC_EDIT_TITLE_NAME, m_edtTitleNmae);
	DDX_Control(pDX, IDC_COMBO_TITLE_TIME, m_cboTitleTime);
	DDX_Control(pDX, IDC_CHECK_TITLE_DRIC, m_chkTitleDirc);
	DDX_Control(pDX, IDC_CHECK_TITLE_BACKGROUND, m_chkTitleBackGround);
}


BEGIN_MESSAGE_MAP(CLS_DomeTitle, CDialog)
	ON_CBN_SELCHANGE(IDC_CBO_TITLE_TYPE, &CLS_DomeTitle::OnCbnSelchangeCboTitleType)
	ON_CBN_SELCHANGE(IDC_COMBO_TITLE_NO, &CLS_DomeTitle::OnCbnSelchangeComboTitleNo)
	ON_CBN_SELCHANGE(IDC_COMBO_TITLE_TIME, &CLS_DomeTitle::OnCbnSelchangeComboTitleTime)
	ON_BN_CLICKED(IDC_CHECK_TITLE_DRIC, &CLS_DomeTitle::OnBnClickedCheckTitleDric)
	ON_BN_CLICKED(IDC_CHECK_TITLE_BACKGROUND, &CLS_DomeTitle::OnBnClickedCheckTitleBackground)
	ON_BN_CLICKED(IDC_BUTTON_DOME_TITLE_SET, &CLS_DomeTitle::OnBnClickedButtonDomeTitleSet)
END_MESSAGE_MAP()


// CLS_DomeBasic2 message handlers

BOOL CLS_DomeTitle::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UI_UpdateDialogText();
	OnCbnSelchangeCboTitleType();

	//限制编辑框的输入长度为30个字节
	m_edtTitleNmae.SetLimitText(30);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_DomeTitle::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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
	OnCbnSelchangeCboTitleType();
}

void CLS_DomeTitle::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialogText();
	OnCbnSelchangeCboTitleType();
}

void CLS_DomeTitle::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_STATIC_TITLE_TYPE, IDS_LOG_TYPE);
	SetDlgItemTextEx(IDC_STATIC_TITLE_NO, IDS_PE_INDEX);
	SetDlgItemTextEx(IDC_STATIC_TITLE_NAME, IDS_PE_NAME);
	SetDlgItemTextEx(IDC_STATIC_TITLE_TIME, IDS_STATIC_TITLE_TIME);
	SetDlgItemTextEx(IDC_CHECK_TITLE_DRIC, IDS_CHECK_TITLE_DRIC);
	SetDlgItemTextEx(IDC_CHECK_TITLE_BACKGROUND, IDS_CHECK_TITLE_BACKGROUND);
	SetDlgItemTextEx(IDC_BUTTON_DOME_TITLE_SET, IDS_SET);

	//标题类型
	m_cboTitleType.ResetContent();
	m_cboTitleType.AddString(GetTextEx(IDS_PREVIEW_PRESET));
	m_cboTitleType.AddString(GetTextEx(IDS_DOME_ADV_SCAN));
	m_cboTitleType.AddString(GetTextEx( IDS_DOME_ADV_CURISE));
	m_cboTitleType.AddString(GetTextEx(IDS_DOME_PTZ_ACT_PATTERN));
	m_cboTitleType.AddString(GetTextEx(IDS_REGIONAL_INDICATIVE));
	m_cboTitleType.SetCurSel(0);

	//标题显示时间：0-关闭 1-持续 2-2秒 3-5秒 4-10秒  
	int iCount = 0;
	m_cboTitleTime.ResetContent();
	m_cboTitleTime.AddString(GetTextEx(IDS_CONFIG_CLOSE));
	m_cboTitleTime.SetItemData(iCount++, TITLE_TIME_CLOSE);
	m_cboTitleTime.AddString(GetTextEx(IDS_TITLE_TIME_ALWAYS));
	m_cboTitleTime.SetItemData(iCount++, TITLE_TIME_ALWAYS);
	m_cboTitleTime.AddString("2 s");
	m_cboTitleTime.SetItemData(iCount++, TITLE_TIME_2);
	m_cboTitleTime.AddString("5 s");
	m_cboTitleTime.SetItemData(iCount++, TITLE_TIME_5);
	m_cboTitleTime.AddString("10 s");
	m_cboTitleTime.SetItemData(iCount++, TITLE_TIME_10);
	m_cboTitleTime.SetCurSel(0);

}

void CLS_DomeTitle::UI_UpdateDomeTitleInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error(%d)", m_iLogonID, GetLastError());
		return;
	}

	int iIndex = m_cboTitleType.GetCurSel() + 1;
	TDomeParam tParam = {0};
	memset(&tParam, 0, sizeof(TDomeParam));
	tParam.iType = GetTitleCMDType(iIndex);
	int iReturnByte = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo
		, &tParam,sizeof(TDomeParam), &iReturnByte);
	if (iRet >= 0)
	{
		//更新标题显示时间
		int iIndex = 0;
		bool blFlag = false;
		for (int i=0; i<m_cboTitleTime.GetCount(); i++)
		{
			iIndex = i;
			if (m_cboTitleTime.GetItemData(i) == tParam.iParam1)
			{
				blFlag = true;
				break;
			}
		}
		if (blFlag == false)
		{
			iIndex = 0;
		}
		m_cboTitleTime.SetCurSel(iIndex);
		AddLog(LOG_TYPE_SUCC, "","NetClient_GetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d, %d)", m_iLogonID, m_iChannelNo, iIndex);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNo, iIndex, GetLastError());
	}

	//标题背景、方向显示
	memset(&tParam, 0, sizeof(TDomeParam));
	tParam.iType = DOME_PARA_COORDINATE_DIRECTION_DISPLAY_TIME;
	iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo
		, &tParam,sizeof(TDomeParam), &iReturnByte);
	if (iRet == 0)
	{
		if (tParam.iParam1 == TITLE_TIME_2)
		{
			m_chkTitleDirc.SetCheck(BST_CHECKED);
		}
		else
		{
			m_chkTitleDirc.SetCheck(BST_UNCHECKED);
		}
		AddLog(LOG_TYPE_SUCC, "","NetClient_GetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "","NetClient_GetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d), error (%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}

	memset(&tParam, 0, sizeof(TDomeParam));
	tParam.iType = DOME_PARA_TITLE_BACKGROUND;
	iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo
		, &tParam,sizeof(TDomeParam), &iReturnByte);
	if (iRet == 0)
	{
		m_chkTitleBackGround.SetCheck(tParam.iParam1);
		AddLog(LOG_TYPE_SUCC, "","NetClient_GetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d), error (%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}
}	

void CLS_DomeTitle::OnCbnSelchangeCboTitleType()
{
	int iIndex = m_cboTitleType.GetCurSel() + 1;
	switch(iIndex)
	{
	case TITLETYPE_PRESET:
		{
			//预置位
			m_cboTitleNo.ResetContent();
			for (int i=0; i<32; i++)
			{
				m_cboTitleNo.AddString(IntToCString(i+1));
			}
			m_cboTitleNo.SetCurSel(0);
		}
		break;
	case TITLETYPE_SCAN:
		{
			//扫描
			m_cboTitleNo.ResetContent();
			for (int i=0; i<8; i++)
			{
				m_cboTitleNo.AddString(IntToCString(i+1));
			}
			m_cboTitleNo.SetCurSel(0);
		}
		break;
	case TITLETYPE_CRUISE:
		{
			//巡航
			m_cboTitleNo.ResetContent();
			for (int i=0; i<8; i++)
			{
				m_cboTitleNo.AddString(IntToCString(i+1));
			}
			m_cboTitleNo.SetCurSel(0);
		}
		break;
	case TITLETYPE_PATTERN:
		{
			//模式路径
			m_cboTitleNo.ResetContent();
			for (int i=0; i<8; i++)
			{
				m_cboTitleNo.AddString(IntToCString(i+1));
			}
			m_cboTitleNo.SetCurSel(0);
		}
		break;
	case TITLETYPE_ZONES:
		{
			//区域指示
			m_cboTitleNo.ResetContent();
			for (int i=0; i<8; i++)
			{
				m_cboTitleNo.AddString(IntToCString(i+1));
			}
			m_cboTitleNo.SetCurSel(0);
		}
		break;
	default:
		break;
	}
	OnCbnSelchangeComboTitleNo();
	UI_UpdateDomeTitleInfo();
}

void CLS_DomeTitle::OnCbnSelchangeComboTitleNo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error (%d)", m_iLogonID, GetLastError());
		return;
	}

	int iTitleType = m_cboTitleType.GetCurSel() + 1;
	int iTitleNo = m_cboTitleNo.GetCurSel();
	CString cstrTitle = "";
	if (NetClient_GetDomeAdvParam)
	{
		DOME_TITLE title = {0};
		title.m_iStructSize = sizeof(DOME_TITLE);
		title.m_iType = iTitleType;
		title.m_iNum = iTitleNo;

		//CMD_DOME_ADV_SETTITLE
		int iRet = NetClient_GetDomeAdvParam(m_iLogonID, m_iChannelNo, CMD_DOME_ADV_SETTITLE, &title, sizeof(title));
		if (iRet >= 0)
		{
			cstrTitle = title.m_cTitle;
			AddLog(LOG_TYPE_SUCC,"","NetClient_GetDomeAdvParam[CMD_DOME_ADV_SETTITLE] (%d, %d)", m_iLogonID, m_iChannelNo);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetDomeAdvParam[CMD_DOME_ADV_SETTITLE] (%d, %d), error (%d)", m_iLogonID, m_iChannelNo, GetLastError());
		}
	}
	GetDlgItem(IDC_EDIT_TITLE_NAME)->SetWindowText(cstrTitle);
}

void CLS_DomeTitle::OnCbnSelchangeComboTitleTime()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error (%d)", m_iLogonID, GetLastError());
		return;
	}

	int iCmdType = GetTitleCMDType(m_cboTitleType.GetCurSel() + 1);
	if (iCmdType != -1)
	{
		TDomeParam tParam = {0};
		tParam.iType = iCmdType;
		tParam.iParam1 = (int)m_cboTitleTime.GetItemData(m_cboTitleTime.GetCurSel());
		int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo, &tParam,sizeof(TDomeParam));
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d, %d)", m_iLogonID, m_iChannelNo, iCmdType);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU] (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNo, iCmdType, GetLastError());
		}
	}
}

void CLS_DomeTitle::OnBnClickedCheckTitleDric()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error(%d)", m_iLogonID, GetLastError());
		return;
	}

	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_COORDINATE_DIRECTION_DISPLAY_TIME;
	tParam.iParam1 = m_chkTitleDirc.GetCheck()?TITLE_TIME_2:TITLE_TIME_CLOSE;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo, &tParam,sizeof(TDomeParam));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_COORDINATE_DIRECTION_DISPLAY_TIME] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_COORDINATE_DIRECTION_DISPLAY_TIME] (%d, %d), error (%d)", m_iLogonID, m_iLogonID, GetLastError());
	}
}

void CLS_DomeTitle::OnBnClickedCheckTitleBackground()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error (%d)", m_iLogonID, GetLastError());
		return;
	}

	TDomeParam tParam = {0};
	tParam.iType = DOME_PARA_TITLE_BACKGROUND;
	tParam.iParam1 = m_chkTitleBackGround.GetCheck();
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_DOME_MENU, m_iChannelNo, &tParam,sizeof(TDomeParam));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_TITLE_BACKGROUND] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_DOME_MENU][DOME_PARA_TITLE_BACKGROUND] (%d, %d), error (%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}
}

void CLS_DomeTitle::OnBnClickedButtonDomeTitleSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error (%d)", m_iLogonID, GetLastError());
		return;
	}

	CString cstrTitle = "";
	GetDlgItemText(IDC_EDIT_TITLE_NAME, cstrTitle);
	if (NetClient_SetDomeAdvParam)
	{
		DOME_TITLE title = {0};
		title.m_iStructSize = sizeof(DOME_TITLE);
		title.m_iType = m_cboTitleType.GetCurSel()+1;
		title.m_iNum = m_cboTitleNo.GetCurSel();
		strcpy_s(title.m_cTitle, cstrTitle);
		int iRet = NetClient_SetDomeAdvParam(m_iLogonID, m_iChannelNo, CMD_DOME_ADV_SETTITLE, &title, sizeof(title));
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetDomeAdvParam[CMD_DOME_ADV_SETTITLE] (%d, %d)" , m_iLogonID, m_iChannelNo);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetDomeAdvParam[CMD_DOME_ADV_SETTITLE] (%d, %d), error (%d)", m_iLogonID, m_iChannelNo, GetLastError());
		}
	}
}

int CLS_DomeTitle::GetTitleCMDType( int _iTitleType )
{
	int iCmdType = -1;
	switch(_iTitleType)
	{
	default:
	case TITLETYPE_PRESET:
		{
			//预置位
			iCmdType = DOME_PARA_PRESET_TITLE_DISPLAY_TIME;
		}
		break;
	case TITLETYPE_SCAN:	//扫描
	case TITLETYPE_CRUISE:	//巡航
	case TITLETYPE_PATTERN:	//模式路径
		{

			iCmdType = DOME_PARA_AUTOMATIC_FUNCTION_TITLE_DISPLAY_TIME;
		}
		break;
	case TITLETYPE_ZONES:
		{
			//区域指示
			iCmdType = DOME_PARA_REGION_TITLE_DISPLAY_TIME;
		}
		break;
	}

	return iCmdType;
}
