
#include "stdafx.h"
#include "NetClientDemo.h"
#include "OSDManagePage.h"
#include <shlwapi.h>
//  CLS_OSDManagePage 对话框

IMPLEMENT_DYNAMIC( CLS_OSDManagePage, CDialog)

 CLS_OSDManagePage:: CLS_OSDManagePage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage( CLS_OSDManagePage::IDD, pParent)
{
	m_iLogonID = -1;
	m_pclsOSDEdit = NULL;
}

 CLS_OSDManagePage::~CLS_OSDManagePage()
{
	if (m_pclsOSDEdit != NULL)
	{
		delete m_pclsOSDEdit;
		m_pclsOSDEdit = NULL;
	}
}

void  CLS_OSDManagePage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_OSD, m_lstOSDInfo);
	DDX_Control(pDX, IDC_CBO_OSD_NUM, m_cboOverlayType);
}


BEGIN_MESSAGE_MAP( CLS_OSDManagePage, CDialog)
	ON_BN_CLICKED(IDC_BTN_OSD_ADD, & CLS_OSDManagePage::OnBnClickedBtnOsdAdd)
	ON_NOTIFY(NM_CLICK, IDC_LST_OSD, &CLS_OSDManagePage::OnNMClickLstOsd)
	ON_CBN_SELCHANGE(IDC_CBO_OSD_NUM, &CLS_OSDManagePage::OnCbnSelchangeCboOsdNum)
END_MESSAGE_MAP()


//  CLS_OSDManagePage 消息处理程序

BOOL  CLS_OSDManagePage::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemTextEx(IDC_STC_OSD_NUM, IDS_CONFIG_LINK_NUMBER);
	SetDlgItemTextEx(IDC_BTN_OSD_ADD, IDS_CONFIG_LINK_ADD);
	
	int iColumn = 0;
	DWORD dwStyle = m_lstOSDInfo.GetExtendedStyle();
	dwStyle = dwStyle | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;  
	m_lstOSDInfo.SetExtendedStyle(dwStyle);
	InsertColumn(m_lstOSDInfo, iColumn++, GetTextEx(IDS_CONFIG_LINK_IP), LVCFMT_LEFT, 100);
	InsertColumn(m_lstOSDInfo, iColumn++, GetTextEx(IDS_CONFIG_LINK_OSD_CH), LVCFMT_LEFT, 70);
	InsertColumn(m_lstOSDInfo, iColumn++, GetTextEx(IDS_CONFIG_LINK_OSD_AREA), LVCFMT_LEFT, 70);
	InsertColumn(m_lstOSDInfo, iColumn++, GetTextEx(IDS_CONFIG_LINK_OSD_COLOR), LVCFMT_LEFT, 100);
	InsertColumn(m_lstOSDInfo, iColumn++, GetTextEx(IDS_CONFIG_OPETATE), LVCFMT_LEFT, 50);
	InsertColumn(m_lstOSDInfo, iColumn++, GetTextEx(IDS_CONFIG_OPETATE), LVCFMT_LEFT, 50);

	if (NULL == m_pclsOSDEdit)
	{
		m_pclsOSDEdit = new CLS_OSDEdit();
	}

	return TRUE; 
}

void CLS_OSDManagePage::OnLanguageChanged(int _iLanguage)
{
	OnInitDialog();
	UpdateUI();
}

void CLS_OSDManagePage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	UpdateUI();
}

BOOL CLS_OSDManagePage::UpdateUI()
{
	UpdateInputList();
	OnCbnSelchangeCboOsdNum();
	return TRUE;
}	

BOOL CLS_OSDManagePage::UpdateInputList()
{
	int iAlarmInPortNum = 0;
	int iAlarmOutPortNum = 0;
	int iRet = -1;
	iRet = NetClient_GetAlarmPortNum(m_iLogonID,&iAlarmInPortNum,&iAlarmOutPortNum);
	if(0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_OSDManagePage::UpdateInputList] NetClient_GetAlarmPortNum failed! iAlarmInPortNum(%d),iAlarmOutPortNum(%d)"
			,m_iLogonID,iAlarmInPortNum,iAlarmOutPortNum);
		return FALSE;
	}

	m_cboOverlayType.ResetContent();

	for (int i = 0; i < iAlarmInPortNum; i++)
	{
		AlarmInConfig alarminConfig = {0};
		alarminConfig.iSize = sizeof(AlarmInConfig);
		alarminConfig.iInterfaceNo = i;
		iRet = NetClient_GetAlarmConfig(m_iLogonID, i, -1, CMD_ALARM_IN_CONFIG, &alarminConfig);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","[CLS_OSDManagePage::UpdateInputList] NetClient_GetAlarmConfig failed! logonID(%d),i(%d)"
				,m_iLogonID,i);
			return FALSE;
		}

		if (alarminConfig.iInterfaceType == 1)
		{
			CString cstrOverlayType;
			cstrOverlayType.Format("%d-%s", i+1, alarminConfig.cName);
			int iItemComb = m_cboOverlayType.AddString(cstrOverlayType);
			m_cboOverlayType.SetItemData(iItemComb, i);
		}
	}

	m_cboOverlayType.SetCurSel(0);

	return TRUE;
}

void CLS_OSDManagePage::OnCbnSelchangeCboOsdNum()
{
	int iOverlayIndex = m_cboOverlayType.GetCurSel();
	if (iOverlayIndex < 0)
	{
		return;
	}

	m_lstOSDInfo.DeleteAllItems();

	int iID = (int)m_cboOverlayType.GetItemData(iOverlayIndex);

	for (int i = 0; i < MAX_OSDTYPE_NUM; i++)
	{ 
		UpdateOSDInfo(iID, i);
	}
}

void CLS_OSDManagePage::UpdateOSDInfo(int _iID,int _iOsdNo)
{
	AlarmInOSD alarminOSD = {0};
	alarminOSD.iSize = sizeof(AlarmInOSD);
	alarminOSD.iChannelNo = _iID;
	alarminOSD.iOsdIndex = _iOsdNo;
	int iRetGet = NetClient_GetAlarmConfig(m_iLogonID, _iID, -1, CMD_ALARM_IN_OSD, &alarminOSD);
	if (iRetGet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_OSDManagePage::UpdateOSDInfo] NetClient_GetAlarmConfig failed! logonID(%d),_iID(%d),error(%d)"
			,m_iLogonID,_iID,GetLastError());
		return;
	}

	if (alarminOSD.iEnable == 1)
	{
		int iItemIndex = 0;
		iItemIndex = m_lstOSDInfo.GetItemCount();
		m_lstOSDInfo.InsertItem(iItemIndex, "");
		m_lstOSDInfo.SetItemText(iItemIndex, 0, alarminOSD.cIP);
		m_lstOSDInfo.SetItemText(iItemIndex, 1, (IntToString(alarminOSD.iChannelNo)));
		m_lstOSDInfo.SetItemText(iItemIndex, 2, (IntToString(alarminOSD.iBlockNo)));

		int iOsdColor = alarminOSD.iColor;

		CString csColor = "";
		switch(iOsdColor)
		{
		case RGB(255,255,255):
			//RGB(255,255,255);//16777215;白
			csColor = GetTextEx(IDS_VCA_COL_WHITE);
			break;
		case RGB(0,0,0):
			//RGB(0,0,0);//0黑
			csColor = GetTextEx(IDS_VCA_COL_BLACK);
			break;
		case RGB(255,0,0):
			//RGB(255,0,0);//255;红
			csColor = GetTextEx(IDS_VCA_COL_RED);
			break;
		case RGB(32,102,150):
			//RGB(32,102,150);//32768;3,39,104206696蓝
			csColor = GetTextEx(IDS_VCA_COL_BLUE);
			break;
		case RGB(22,113,22):
			//RGB(22,113,22);//16711680;绿
			csColor = GetTextEx(IDS_VCA_COL_GREEN);
			break;
		default:
			break;
		}

		m_lstOSDInfo.SetItemText(iItemIndex, 3, csColor);
		m_lstOSDInfo.SetItemText(iItemIndex, 4, (GetText(IDS_CONFIG_LINK_EDIT)));
		m_lstOSDInfo.SetItemText(iItemIndex, 5, (GetText(IDS_CONFIG_LINK_DELE)));
		m_lstOSDInfo.SetItemData(iItemIndex,alarminOSD.iOsdIndex);
	}
}

void CLS_OSDManagePage::OnBnClickedBtnOsdAdd()
{
	if (NULL == m_pclsOSDEdit)
	{
		return;
	}
	int iSel = m_cboOverlayType.GetCurSel();
	int iDevNo = (int)m_cboOverlayType.GetItemData(iSel);
	int iOsdNo = GetFreeOsdNo(iDevNo);
	m_pclsOSDEdit->InitOSDParam(n_Dlg_ADD,m_iLogonID,iDevNo,iOsdNo);
	if(IDOK == m_pclsOSDEdit->DoModal())
	{
		OnCbnSelchangeCboOsdNum();
	}
}

void CLS_OSDManagePage::OnNMClickLstOsd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	int nItem = pNMListView->iItem;		//行号
	int nSub = 	pNMListView->iSubItem;	//列号
	AlarmInOSD alarminOSD = {0};
	alarminOSD.iSize = sizeof(AlarmInOSD);
	int iRet = -1;
	int iCount = m_lstOSDInfo.GetItemCount();
	if(nItem == -1)
	{
		return;
	}
	int iSel = m_cboOverlayType.GetCurSel();
	int iDevNo = (int)m_cboOverlayType.GetItemData(iSel);
	if (nSub == 4)//编辑
	{
		if (NULL == m_pclsOSDEdit)
		{
			return;
		}
		int iOsdIndex = (int)m_lstOSDInfo.GetItemData(nItem);
		m_pclsOSDEdit->InitOSDParam(n_Dlg_Edit,m_iLogonID,iDevNo,iOsdIndex);
		if(IDOK == m_pclsOSDEdit->DoModal())
		{
			OnCbnSelchangeCboOsdNum();
		}
	}
	if (nSub == 5)//删除
	{
		AlarmInOSD alarminOSD = {0};
		alarminOSD.iSize = sizeof(AlarmInOSD);
		alarminOSD.iEnable = 0;
		alarminOSD.iOsdIndex = (int)m_lstOSDInfo.GetItemData(nItem);
		int iRet = NetClient_SetAlarmConfig(m_iLogonID, iDevNo, -1, CMD_ALARM_IN_OSD, &alarminOSD);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","[CLS_OSDManagePage::OnNMClickLstOsd] NetClient_SetAlarmConfig failed! logonID(%d),_iID(%d),error(%d)"
				,m_iLogonID,iDevNo,GetLastError());
			return;
		}
		OnCbnSelchangeCboOsdNum();
	}

	*pResult = 0;
}


int CLS_OSDManagePage::GetFreeOsdNo(int _iDevNo)
{
	for (int i = 1; i <= MAX_OSDTYPE_NUM; i++)
	{
		AlarmInOSD alarminOSD = {0};
		alarminOSD.iSize = sizeof(AlarmInOSD);
		alarminOSD.iOsdIndex = i;
		int iRet = NetClient_GetAlarmConfig(m_iLogonID, _iDevNo, -1, CMD_ALARM_IN_OSD, &alarminOSD);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","[CLS_OSDManagePage::OnBnClickedBtnOsdAdd] NetClient_GetAlarmConfig failed! logonID(%d),_iID(%d),error(%d)"
				,m_iLogonID,_iDevNo,GetLastError());
			continue;
		}
		if (alarminOSD.iEnable == 0)
		{
			return i;
		}
	}
	return -1;
}