
#include "stdafx.h"
#include "NetClientDemo.h"
#include "AdvLocalSet.h"
#include "../Common/Ini.h"

// CLS_AdvLocalSet 对话框

IMPLEMENT_DYNAMIC(CLS_AdvLocalSet, CDialog)

CLS_AdvLocalSet::CLS_AdvLocalSet(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_AdvLocalSet::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
}

CLS_AdvLocalSet::~CLS_AdvLocalSet()
{
}

void CLS_AdvLocalSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_LOGON_MODE, m_cboLogonMode);
	DDX_Control(pDX, IDC_COMBO_USE_RULE, m_cboDemoUseRule);
	DDX_Control(pDX, IDC_CBO_VCAFPGA_QUERYINFO, m_cboVcaFpgaQueryInfo);
	DDX_Control(pDX, IDC_CBO_VCAFPGA, m_cboVcaFpga);
}


BEGIN_MESSAGE_MAP(CLS_AdvLocalSet, CDialog)
	ON_BN_CLICKED(IDC_BTN_LOGON_MODE, &CLS_AdvLocalSet::OnBnClickedBtnLogonMode)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_SET_DEMO_USE_RULE, &CLS_AdvLocalSet::OnBnClickedButtonSetDemoUseRule)
	ON_BN_CLICKED(IDC_BTN_VCAFPGA_SET, &CLS_AdvLocalSet::OnBnClickedBtnVcafpgaSet)
	ON_BN_CLICKED(IDC_BTN_VCAFPGA_QUERYINFO_SET, &CLS_AdvLocalSet::OnBnClickedBtnVcafpgaQueryinfoSet)
	ON_CBN_SELCHANGE(IDC_CBO_VCAFPGA_QUERYINFO, &CLS_AdvLocalSet::OnCbnSelchangeCboVcafpgaQueryinfo)
	ON_CBN_SELCHANGE(IDC_CBO_VCAFPGA, &CLS_AdvLocalSet::OnCbnSelchangeCboVcafpga)
END_MESSAGE_MAP()


BOOL CLS_AdvLocalSet::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	UI_UpdateDialog();

	LoadSdkWorkMode();

	LoadDemoUseRule();

	return TRUE;
}

void CLS_AdvLocalSet::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
}

void CLS_AdvLocalSet::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_AdvLocalSet::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
}

void CLS_AdvLocalSet::OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser)
{
	if (m_iLogonID < 0 || m_iLogonID != _ulLogonID)
	{
		return;
	}

	int iMsgType = LOWORD(_iWparam);
	switch(iMsgType)
	{
	case WCM_VCAFPGA_QUERYINFO:
		{
			UI_UpdateVcaFpgaQueryInfo();
		}
		break;
	default:
		break;
	}
}

void CLS_AdvLocalSet::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara, int _iUserData)
{
	if (m_iLogonID < 0 || m_iLogonID != _iLogonID)
	{
		return;
	}

	if (_iChannelNo == m_iChannelNo)//只刷新参数改变的通道
	{
		switch(_iParaType)
		{
		case PARA_VCAFPGA:
			{
				UI_UpdateVcaFpga();
			}
			break;
		default:
			break;
		}
	}
}

void CLS_AdvLocalSet::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STC_LOGON_MODE, IDS_CFG_ADV_LOGON_MODE);
	SetDlgItemTextEx(IDC_BTN_LOGON_MODE, IDS_SET);

	SetDlgItemTextEx(IDC_STC_MODE_RESART_TIP, IDS_ADVANCE_LOCAL_HINT);
	SetDlgItemTextEx(IDC_STATIC_USE_RULE, IDS_ADVANCE_LOCAL_USE_METHOD);
	SetDlgItemTextEx(IDC_BUTTON_SET_DEMO_USE_RULE, IDS_SET);

	InsertString(m_cboLogonMode, 0, IDS_CFG_ADV_LOGON_HEAVY);
	m_cboLogonMode.SetItemData(0, HEAVY_MODE);
	InsertString(m_cboLogonMode, 1, IDS_CFG_ADV_LOGON_LIGHT);
	m_cboLogonMode.SetItemData(1, LIGHT_MODE);
	InsertString(m_cboLogonMode, 2, IDS_CFG_ADV_LOGON_EASYX_LIGHT);
	m_cboLogonMode.SetItemData(2, EASYX_LIGHT_MODE);	
	InsertString(m_cboLogonMode, 3, IDS_CFG_ADV_LOGON_MOBILE_LIGHT);
	m_cboLogonMode.SetItemData(3, MOBILE_LIGHT_MODE);	

	InsertString(m_cboDemoUseRule, 0, IDS_DEMO_USE_NORMAL);
	m_cboDemoUseRule.SetItemData(0, NORMAL_USE);
	InsertString(m_cboDemoUseRule, 1, IDS_DEMO_USE_RIVER);
	m_cboDemoUseRule.SetItemData(1, RIVER_USE);	

	InsertString(m_cboVcaFpgaQueryInfo, 0, IDS_ADVANCE_VCAFPGA_QUERY_RESERVR);
	m_cboVcaFpgaQueryInfo.SetItemData(0, VCAFPGA_RESERVR);
	InsertString(m_cboVcaFpgaQueryInfo, 1, IDS_ADVANCE_VCAFPGA_QUERY_TEMPERATURE);
	m_cboVcaFpgaQueryInfo.SetItemData(1, VCAFPGA_TEMPERATURE);	
	InsertString(m_cboVcaFpgaQueryInfo, 2, IDS_ADVANCE_VCAFPGA_QUERY_TIME);
	m_cboVcaFpgaQueryInfo.SetItemData(2, VCAFPGA_TIME);

	InsertString(m_cboVcaFpga, 0, IDS_ADVANCE_VCAFPGA_RESERVR);
	m_cboVcaFpga.SetItemData(0, VCAFPGA_RESERVR);
	InsertString(m_cboVcaFpga, 1, IDS_ADVANCE_VCAFPGA_MERGECNT);
	m_cboVcaFpga.SetItemData(1, VCAFPGA_TEMPERATURE);	
	InsertString(m_cboVcaFpga, 2, IDS_ADVANCE_VCAFPGA_POSTFILETER);
	m_cboVcaFpga.SetItemData(2, VCAFPGA_TIME);

	m_cboVcaFpgaQueryInfo.SetCurSel(0);
	m_cboVcaFpga.SetCurSel(0);
}

void CLS_AdvLocalSet::LoadSdkWorkMode()
{
	CString szNewFile = GetLocalSaveDirectory() + "\\SDKWorkMode.ini";
	CIniFile cFile(szNewFile);

	CString szSection = "WorkMode";
	CString szKey = "Mode";
	int iSDKWorkMode = cFile.ReadInteger((char *)(LPCTSTR)szSection, (char *)(LPCTSTR)szKey, 0);

	m_cboLogonMode.SetCurSel(iSDKWorkMode);
}

void CLS_AdvLocalSet::OnBnClickedBtnLogonMode()
{
	DWORD_PTR iSdkWorkMode = m_cboLogonMode.GetItemData(m_cboLogonMode.GetCurSel());

	//保存到配置文件中，重启软件时读取生效
	CString szNewFile = GetLocalSaveDirectory() + "\\SDKWorkMode.ini";
	CIniFile cFile(szNewFile);
	cFile.ResetFile();	//重新创建配置文件

	CString szSection = "WorkMode";
	CString szKey = "Mode";
	
	cFile.WriteInteger((char *)(LPCTSTR)szSection, (char *)(LPCTSTR)szKey, (int)iSdkWorkMode);	
}

void CLS_AdvLocalSet::LoadDemoUseRule()
{
	CString szNewFile = GetLocalSaveDirectory() + "\\DemoUseRule.ini";
	CIniFile cFile(szNewFile);

	CString szSection = "UseRule";
	CString szKey = "Rule";
	int iUseRule = cFile.ReadInteger((char *)(LPCTSTR)szSection, (char *)(LPCTSTR)szKey, 0);

	m_cboDemoUseRule.SetCurSel(iUseRule);
}

void CLS_AdvLocalSet::UI_UpdateVcaFpga()
{
	int iReturnByte = 0;
	VcaFpga tVcaFpga = {0};
	tVcaFpga.iSize = sizeof(VcaFpga);
	tVcaFpga.iType = (int)m_cboVcaFpga.GetItemData(m_cboVcaFpga.GetCurSel());
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_VCAFPGA, m_iChannelNo, &tVcaFpga, sizeof(VcaFpga), &iReturnByte);
	if (iRet != 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_GetDevConfig][NET_CLIENT_VCAFPGA] Get fail,error = %d", GetLastError());
	}
	else
	{
		SetDlgItemInt(IDC_EDT_VCAFPGA_TEMPLATEINDEX, tVcaFpga.iTemplateIndex);
		SetDlgItemInt(IDC_EDT_VCAFPGA, tVcaFpga.iPARA1);
	}
}

void CLS_AdvLocalSet::UI_UpdateVcaFpgaQueryInfo()
{
	VcaFpgaQueryInfo tFpgaQueryInfo = {0};
	tFpgaQueryInfo.iSize = sizeof(VcaFpgaQueryInfo);
	int iRet = NetClient_RecvCommand(m_iLogonID, COMMAND_ID_VCAFPGA_QUERYINFO, m_iChannelNo, &tFpgaQueryInfo, sizeof(VcaFpgaQueryInfo));
	if(RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_AdvLocalSet][COMMAND_ID_VCAFPGA_QUERYINFO] Get fail,error = %d", GetLastError());
	}
	else
	{
		SetDlgItemInt(IDC_EDT_VCAFPGA_QUERYINFO, tFpgaQueryInfo.iValue);
	}
}

void CLS_AdvLocalSet::OnBnClickedButtonSetDemoUseRule()
{
	int iUseRule = (int)m_cboDemoUseRule.GetItemData(m_cboDemoUseRule.GetCurSel());
	CString szNewFile = GetLocalSaveDirectory() + "\\DemoUseRule.ini";
	CIniFile cFile(szNewFile);
	cFile.ResetFile();	//重新创建配置文件

	CString szSection = "UseRule";
	CString szKey = "Rule";

	cFile.WriteInteger((char *)(LPCTSTR)szSection, (char *)(LPCTSTR)szKey, iUseRule);	
}

void CLS_AdvLocalSet::OnBnClickedBtnVcafpgaSet()
{
	if (m_iLogonID < 0)
	{
		return;
	}

	int iType = (int)m_cboVcaFpga.GetItemData(m_cboVcaFpga.GetCurSel());
	int iTemplateIndex = GetDlgItemInt(IDC_EDT_VCAFPGA_TEMPLATEINDEX);
	int iPARA1 = GetDlgItemInt(IDC_EDT_VCAFPGA);
	VcaFpga tVcaFpga = {0};
	tVcaFpga.iSize = sizeof(VcaFpga);
	tVcaFpga.iChannelNo = m_iChannelNo;
	tVcaFpga.iTemplateIndex = iTemplateIndex;
	tVcaFpga.iPARA1 = iPARA1;
	tVcaFpga.iType = iType;

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCAFPGA, m_iChannelNo, &tVcaFpga, sizeof(VcaFpga));
	if(RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_SetDevConfig][NET_CLIENT_VCAFPGA] Set fail,error = %d", GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "[NetClient_SetDevConfig][NET_CLIENT_VCAFPGA] Set Success", m_iLogonID);
	}
}

void CLS_AdvLocalSet::OnBnClickedBtnVcafpgaQueryinfoSet()
{
	if(m_iLogonID < 0)
	{	
		return;
	}

	int iType = (int)m_cboVcaFpgaQueryInfo.GetItemData(m_cboVcaFpgaQueryInfo.GetCurSel());
	VcaFpgaQueryInfo tFpgaQueryInfo = {0};
	tFpgaQueryInfo.iSize = sizeof(VcaFpgaQueryInfo);
	tFpgaQueryInfo.iChannelNo = m_iChannelNo;	
	tFpgaQueryInfo.iType = iType;

	int iRet = NetClient_SendCommand(m_iLogonID, COMMAND_ID_VCAFPGA_QUERYINFO, m_iChannelNo, &tFpgaQueryInfo, sizeof(VcaFpgaQueryInfo));
	if(RET_SUCCESS > iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_SendCommand][COMMAND_ID_VCAFPGA_QUERYINFO] Set fail,error = %d", GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "[NetClient_SendCommand][COMMAND_ID_VCAFPGA_QUERYINFO] Set Success", m_iLogonID);
	}
}

void CLS_AdvLocalSet::OnCbnSelchangeCboVcafpgaQueryinfo()
{
	UI_UpdateVcaFpgaQueryInfo();
}

void CLS_AdvLocalSet::OnCbnSelchangeCboVcafpga()
{
	UI_UpdateVcaFpga();
}
