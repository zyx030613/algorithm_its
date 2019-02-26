
#include "stdafx.h"
#include "NetClientDemo.h"
#include "OSDEdit.h"
#include <shlwapi.h>
#include <afxwin.h>
#include "../Common/CommonFun.h"
#include "..\\Include\\NVSSDK_INTERFACE.h"
using namespace NVSSDK_INTERFACE;
// CLS_OSDEdit 对话框

#define MAX_OSD_CHANNELNUM 64
#define MAX_OSD_BLOCKNUM 16
#define MAX_COLOUR_NUM 5

IMPLEMENT_DYNAMIC(CLS_OSDEdit, CDialog)

CLS_OSDEdit::CLS_OSDEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CLS_OSDEdit::IDD, pParent)
{

}

CLS_OSDEdit::~CLS_OSDEdit()
{
}

void CLS_OSDEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_OSD_EDIT_NAME, m_edtDevName);
	DDX_Control(pDX, IDC_EDT_OSD_EDIT_IP, m_edtDevIP);
	DDX_Control(pDX, IDC_CBO_OSD_EDIT_CH, m_cboDevCH);
	DDX_Control(pDX, IDC_CBO_OSD_EDIT_AREA, m_cboOSDArea);
	DDX_Control(pDX, IDC_CBO_OSD_EDIT_COLOR, m_cboOSDColor);
}


BEGIN_MESSAGE_MAP(CLS_OSDEdit, CDialog)
	ON_BN_CLICKED(IDC_BTN_OSD_SET, &CLS_OSDEdit::OnBnClickedBtnOsdSet)
END_MESSAGE_MAP()


// CLS_OSDEdit 消息处理程序

BOOL CLS_OSDEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemTextEx(IDC_STC_OSD_EDIT_NAME, IDS_CONFIG_LINK_DEV_NAME);
	SetDlgItemTextEx(IDC_STC_OSD_EDIT_IP, IDS_CONFIG_LINK_IP);
	SetDlgItemTextEx(IDC_STC_OSD_EDIT_CH, IDS_CONFIG_LINK_OSD_CH);
	SetDlgItemTextEx(IDC_STC_OSD_EDIT_AREA, IDS_CONFIG_LINK_OSD_AREA);
	SetDlgItemTextEx(IDC_STC_OSD_EDIT_COLOR, IDS_CONFIG_LINK_OSD_COLOR);
	SetDlgItemTextEx(IDC_BTN_OSD_SET, IDS_CONFIG_LINK_SURE);

	InitOSDInfo();

	UpdateUI();

	return TRUE;
}

void CLS_OSDEdit::InitOSDInfo()
{
	//初始化叠加通道
	m_cboDevCH.EnableWindow(TRUE);

	for (int i = 1; i <= MAX_OSD_CHANNELNUM; i++)
	{
		CString cstrNo = "";
		cstrNo.Format("%d",i);
		m_cboDevCH.AddString(cstrNo);
	}
	m_cboDevCH.SetCurSel(0);

	//初始化叠加区域
	m_cboOSDArea.EnableWindow(TRUE);
	m_cboOSDArea.ResetContent();
	for (int i = 1; i <= MAX_OSD_BLOCKNUM; i++)
	{
		CString cstrNo = "";
		cstrNo.Format("%d",i);
		m_cboOSDArea.AddString(cstrNo);
	}
	m_cboOSDArea.SetCurSel(0);

	//初始化字体颜色
	m_cboOSDColor.ResetContent();
	for (int i = 0; i < MAX_COLOUR_NUM; i++)
	{
		m_cboOSDColor.AddString(GetColorStr(i));
	}
	m_cboOSDColor.SetCurSel(0);
}

void CLS_OSDEdit::UpdateUI()
{
	int iIndexChannel = -1;
	int iIndexBlock = -1;
	int iIndexColour = -1;

	//设备名称
	AlarmInConfig alarminConfig = {0};
	alarminConfig.iSize = sizeof(AlarmInConfig);
	alarminConfig.iInterfaceNo = m_iDevNo;
	int iRet = NetClient_GetAlarmConfig(m_iLogonID, m_iDevNo, -1, CMD_ALARM_IN_CONFIG, &alarminConfig);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_OSDEdit::UpdateUI] NetClient_GetAlarmConfig failed! logonID(%d),m_iChannelNo(%d),error(%d)"
			,m_iLogonID,m_iDevNo,GetLastError());
		return;
	}

	string strName = alarminConfig.cName;
	m_edtDevName.SetWindowText(strName.c_str());
	m_edtDevName.EnableWindow(FALSE);

	if (m_iDlgType == n_Dlg_Edit)
	{

		AlarmInOSD alarminOSD;
		alarminOSD.iSize = sizeof(AlarmInOSD);
		alarminOSD.iChannelNo = m_iDevNo;
		alarminOSD.iOsdIndex = m_iOSDNo;
		iRet = NetClient_GetAlarmConfig(m_iLogonID, m_iDevNo, -1, CMD_ALARM_IN_OSD, &alarminOSD);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","[CLS_OSDEdit::UpdateUI] NetClient_GetAlarmConfig failed! logonID(%d),m_iChannelNo(%d),error(%d)"
				,m_iLogonID,m_iDevNo,GetLastError());
			return;
		}

		//IP地址
		CString strIP = alarminOSD.cIP;
		m_edtDevIP.SetWindowText(strIP);

		//叠加通道
		CString cstrCH = IntToString(alarminOSD.iChannelNo);
		iIndexChannel = m_cboDevCH.FindString(-1,cstrCH);
		m_cboDevCH.SetCurSel(iIndexChannel);

		//叠加区域
		CString cstrBlock = IntToString(alarminOSD.iBlockNo);
		iIndexBlock = m_cboOSDArea.FindString(-1,cstrBlock);
		m_cboOSDArea.SetCurSel(iIndexBlock);

		//字体颜色
		CString csColor = GetColorStr(alarminOSD.iColor);
		iIndexChannel = m_cboOSDColor.FindString(-1,csColor);;
		m_cboOSDColor.SetCurSel(iIndexChannel);
	}
}

void CLS_OSDEdit::OnBnClickedBtnOsdSet()
{
	AlarmInOSD alarminOSD = {0};
	alarminOSD.iSize = sizeof(AlarmInOSD);
	alarminOSD.iOsdIndex = m_iOSDNo;
	alarminOSD.iEnable = 1;
	CString cstrDevIP;
	m_edtDevIP.GetWindowText(cstrDevIP);
	strcpy_s(alarminOSD.cIP, cstrDevIP);
	alarminOSD.iChannelNo = m_cboDevCH.GetCurSel()+1;
	alarminOSD.iBlockNo = m_cboOSDArea.GetCurSel()+1;
	int iColor = m_cboOSDColor.GetCurSel();

	switch(iColor)
	{
	case 0:
		//RGB(255,255,255);//16777215;白
		alarminOSD.iColor = RGB(255,255,255);
		break;
	case 1:
		//RGB(0,0,0);//0黑
		alarminOSD.iColor = RGB(0,0,0);
		break;
	case 2:
		//RGB(255,0,0);//255;红
		alarminOSD.iColor = RGB(255,0,0);
		break;
	case 3:
		//RGB(32,102,150);//32768;3,39,104206696蓝
		alarminOSD.iColor =  RGB(32,102,150);
		break;
	case 4:
		//RGB(22,113,22);//16711680;绿
		alarminOSD.iColor = RGB(22,113,22);
		break;
	default:
		break;
	}

	int iRet = NetClient_SetAlarmConfig(m_iLogonID, m_iDevNo, -1, CMD_ALARM_IN_OSD, &alarminOSD);
	if (0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_OSDEdit::OnBnClickedBtnOsdSet] NetClient_SetAlarmConfig failed! logonID(%d),m_iChannelNo(%d),error(%d)"
			,m_iLogonID,m_iDevNo,GetLastError());
		return;
	}
	EndDialog(IDOK);
}

CString CLS_OSDEdit::GetColorStr(int _iColor)
{
// 	int iColString[MAX_OSD_COLOUR_NUM] = {IDS_VCA_COL_WHITE,
// 		IDS_VCA_COL_BLACK,IDS_VCA_COL_RED,IDS_VCA_COL_BLUE,
// 		IDS_VCA_COL_GREEN};
	CString csColor = "";
	switch(_iColor)
	{
	case 0:
		//RGB(255,255,255);//16777215;白
		csColor = GetTextEx(IDS_VCA_COL_WHITE);
		break;
	case 1:
		//RGB(0,0,0);//0黑
		csColor = GetTextEx(IDS_VCA_COL_BLACK);
		break;
	case 2:
		//RGB(255,0,0);//255;红
		csColor = GetTextEx(IDS_VCA_COL_RED);
		break;
	case 3:
		//RGB(32,102,150);//32768;3,39,104206696蓝
		csColor = GetTextEx(IDS_VCA_COL_BLUE);
		break;
	case 4:
		//RGB(22,113,22);//16711680;绿
		csColor = GetTextEx(IDS_VCA_COL_GREEN);
		break;
	default:
		break;
	}
	return csColor;
}
