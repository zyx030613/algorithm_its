
#include "stdafx.h"
#include "NetClientDemo.h"
#include "LinkSet.h"
#include <shlwapi.h>
#include "..\Common\CommonFun.h"
#define  MAX_LINK_NUM 32
// CLS_LinkSet 对话框

IMPLEMENT_DYNAMIC(CLS_LinkSet, CDialog)

CLS_LinkSet::CLS_LinkSet(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_LinkSet::IDD, pParent)
{
	m_iLogonID = -1;
	m_iDevType = -1;
	m_iDevNo = -1;
	m_iFreeLinkIndex = -1;
}

CLS_LinkSet::~CLS_LinkSet()
{
}

void CLS_LinkSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_LINKSET, m_lstLink);
	DDX_Control(pDX, IDC_CBO_NUM, m_cboLinkType);
}


BEGIN_MESSAGE_MAP(CLS_LinkSet, CDialog)
	ON_CBN_SELCHANGE(IDC_CBO_NUM, &CLS_LinkSet::OnCbnSelchangeCboNum)
	ON_NOTIFY(NM_CLICK, IDC_LST_LINKSET, &CLS_LinkSet::OnNMClickLstLinkset)
	ON_BN_CLICKED(IDC_BTN_LINK_ADD, &CLS_LinkSet::OnBnClickedBtnLinkAdd)
END_MESSAGE_MAP()


// CLS_LinkSet 消息处理程序

BOOL CLS_LinkSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitDlgItems();

	InitMapInfo();

	return TRUE;
}

void CLS_LinkSet::InitDlgItems()
{
	SetDlgItemTextEx(IDC_STC_LINKSET, IDS_CONFIG_LINK_SET);
	SetDlgItemTextEx(IDC_STC_NUM, IDS_CONFIG_LINK_NUMBER);
	SetDlgItemTextEx(IDC_BTN_LINK_ADD, IDS_CONFIG_LINK_ADD);
	int iColumn = 0;
	DWORD dwStyle = m_lstLink.GetExtendedStyle();
	dwStyle = dwStyle | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;  
	m_lstLink.SetExtendedStyle(dwStyle);
	InsertColumn(m_lstLink, iColumn++, GetTextEx(IDS_CONFIG_LINK_ACTION_NUM), LVCFMT_LEFT, 100);
	InsertColumn(m_lstLink, iColumn++, GetTextEx(IDS_CONFIG_LINK_ACTION_NAME), LVCFMT_LEFT, 100);
	InsertColumn(m_lstLink, iColumn++, GetTextEx(IDS_CONFIG_LINK_ALARM_TYPE), LVCFMT_LEFT, 100);
	InsertColumn(m_lstLink, iColumn++, GetTextEx(IDS_CONFIG_LINK_TYPE), LVCFMT_LEFT, 100);
	InsertColumn(m_lstLink, iColumn++, GetTextEx(IDS_CONFIG_OPETATE), LVCFMT_LEFT, 100);
	InsertColumn(m_lstLink, iColumn++, GetTextEx(IDS_CONFIG_OPETATE), LVCFMT_LEFT, 100);
}

void CLS_LinkSet::InitMapInfo()
{
	m_mapAlarmTypeName.insert(pair<int,CString>(7,GetText(IDS_CONFIG_ALARM)));
	m_mapAlarmTypeName.insert(pair<int,CString>(8,GetText(IDS_CONFIG_ALARM_UPPER)));
	m_mapAlarmTypeName.insert(pair<int,CString>(9,GetText(IDS_CONFIG_ALARM_LOWER)));
	m_mapAlarmTypeName.insert(pair<int,CString>(10,GetText(IDS_CONFIG_ALARM_UPPER_TMP)));
	m_mapAlarmTypeName.insert(pair<int,CString>(11,GetText(IDS_CONFIG_ALARM_LOWER_TMP)));
	m_mapAlarmTypeName.insert(pair<int,CString>(12,GetText(IDS_CONFIG_ALARM_UPPER_HMD)));
	m_mapAlarmTypeName.insert(pair<int,CString>(13,GetText(IDS_CONFIG_ALARM_LOWER_HMD)));
	m_mapAlarmTypeName.insert(pair<int,CString>(7 + 256,GetText(IDS_CONFIG_ALARM_CLEAR)));
	m_mapAlarmTypeName.insert(pair<int,CString>(8 + 256,GetText(IDS_CONFIG_ALARM_UPPER_CLEAR)));
	m_mapAlarmTypeName.insert(pair<int,CString>(9 + 256,GetText(IDS_CONFIG_ALARM_LOWER_CLEAR)));
	m_mapAlarmTypeName.insert(pair<int,CString>(10 + 256,GetText(IDS_CONFIG_ALARM_UPPER_TMP_CLEAR)));
	m_mapAlarmTypeName.insert(pair<int,CString>(11 + 256,GetText(IDS_CONFIG_ALARM_LOWER_TMP_CLEAR)));
	m_mapAlarmTypeName.insert(pair<int,CString>(12 + 256,GetText(IDS_CONFIG_ALARM_UPPER_HMD_CLEAR)));
	m_mapAlarmTypeName.insert(pair<int,CString>(13 + 256,GetText(IDS_CONFIG_ALARM_LOWER_HMD_CLEAR)));

	m_mapLinkTypeName.insert(pair<int,CString>(1,GetText(IDS_CONFIG_LINK_OUT)));
	m_mapLinkTypeName.insert(pair<int,CString>(2,GetText(IDS_CONFIG_LINK_OSD)));
	m_mapLinkTypeName.insert(pair<int,CString>(3,GetText(IDS_CONFIG_LINK_BF)));
	m_mapLinkTypeName.insert(pair<int,CString>(4,GetText(IDS_CONFIG_LINK_SF)));
	m_mapLinkTypeName.insert(pair<int,CString>(5,GetText(IDS_CONFIG_LINK_RECOVER)));
}

void CLS_LinkSet::OnLanguageChanged( int _iLanguage )
{
	InitDlgItems();
	InitMapInfo();
}


void CLS_LinkSet::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	UpdateUI();
}

BOOL CLS_LinkSet::UpdateUI()
{
	UpdateInputList();

	OnCbnSelchangeCboNum();

	return TRUE;
}

BOOL CLS_LinkSet::UpdateInputList()
{
	int iRet = -1;
	int iAlarmInPortNum = -1;
	int iAlarmOutPortNum = -1;
	iRet = NetClient_GetAlarmPortNum(m_iLogonID, &iAlarmInPortNum, &iAlarmOutPortNum);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_LinkSet::UpdateInputList] NetClient_GetAlarmPortNum failed! logonID(%d),error(%d)"
			,m_iLogonID,GetLastError());
		return FALSE;
	}

	m_cboLinkType.ResetContent();

	for (int i=0; i<iAlarmInPortNum;i++)
	{
		AlarmInConfig AlmInCfg = {0};
		AlmInCfg.iSize = sizeof(AlarmInConfig);
		iRet = -1;
		iRet = NetClient_GetAlarmConfig(m_iLogonID, i, -1,CMD_ALARM_IN_CONFIG,&AlmInCfg);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","[CLS_LinkSet::UpdateInputList] NetClient_GetAlarmConfig failed! logonID(%d),i(%d),error(%d)"
				,m_iLogonID,i,GetLastError());
			continue;
		}

		//使能
		int iEnable = -1;
		iRet = NetClient_GetAlarmConfig(m_iLogonID, i, -1, CMD_DH_DEVICE_ENABLE, &iEnable);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "", "OperateInfo-TDGetAlarmConfig(Get EnableInfo error. iEnable %d)",iEnable);
		}

		if (1 == iEnable)
		{
			CString cstrLinkType;
			cstrLinkType.Format("%d-%s", i+1, AlmInCfg.cName);
			int iItemComb = m_cboLinkType.AddString(cstrLinkType);
			m_cboLinkType.SetItemData(iItemComb, i);
		}
	}
	m_cboLinkType.SetCurSel(0);

	return TRUE;
}

void CLS_LinkSet::OnCbnSelchangeCboNum()
{
	int iLinkIndex = m_cboLinkType.GetCurSel();
	if (iLinkIndex < 0)
	{
		return;
	}

	int iChNo = (int)m_cboLinkType.GetItemData(iLinkIndex);
	m_iDevNo = iChNo;
	//获得设备类型
	AlarmInConfig tParam = {0};
	tParam.iSize = sizeof(AlarmInConfig);
	int iRet = NetClient_GetAlarmConfig(m_iLogonID,iChNo,-1,CMD_ALARM_IN_CONFIG,&tParam);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_LinKSetPage::OnNMClickLstLinkset] NetClient_GetAlarmConfig failed! logonID(%d),m_iChNo(%d),m_iActionNo(%d),error(%d)"
			,m_iLogonID,iChNo,GetLastError());
	}
	m_iDevType = tParam.iInterfaceType;

	m_lstLink.DeleteAllItems();
	blGetFreeLink = false;
	for (int i = 0; i < MAX_LINK_NUM; i++)
	{
		UpdateLinkInfo(iChNo, i);
	}
}

void CLS_LinkSet::UpdateLinkInfo(int _iID,int _iLinkNo)
{
	AlarmInLink alarminLink = {0};
	alarminLink.iSize = sizeof(AlarmInLink);
	alarminLink.iLinkIndex = _iLinkNo;
	int iRetGet = NetClient_GetAlarmConfig(m_iLogonID, _iID, -1, CMD_ALARM_IN_LINK, &alarminLink);
	if (iRetGet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_LinkSet::UpdateLinkInfo] NetClient_GetAlarmConfig failed! logonID(%d),_iID(%d),_iLinkNo(%d),error(%d)"
			,m_iLogonID,_iID,_iLinkNo,GetLastError());
		return;
	}

	if (alarminLink.iLinkEnable == 1)
	{
		UpdateLinkItem(_iLinkNo, alarminLink);
	}
	else if(!blGetFreeLink)
	{
		m_iFreeLinkIndex = _iLinkNo;
		blGetFreeLink = true;
	}
}	

void CLS_LinkSet::UpdateLinkItem(int _iLinkNo, AlarmInLink _alarminLink)
{	
	int iItemIndex = m_lstLink.GetItemCount();
	iItemIndex = m_lstLink.InsertItem(iItemIndex, IntToString(_alarminLink.iLinkIndex));
	m_lstLink.SetItemText(iItemIndex, 1, _alarminLink.cName);
	m_lstLink.SetItemText(iItemIndex, 2, m_mapAlarmTypeName[_alarminLink.iAlarmType]);
	m_lstLink.SetItemText(iItemIndex, 3, m_mapLinkTypeName[_alarminLink.iLinkType]);
	m_lstLink.SetItemText(iItemIndex, 4, GetText(IDS_CONFIG_LINK_EDIT));
	m_lstLink.SetItemText(iItemIndex, 5, GetText(IDS_CONFIG_LINK_DELE));
	m_lstLink.SetItemData(iItemIndex, _alarminLink.iLinkIndex);
}

void CLS_LinkSet::OnBnClickedBtnLinkAdd()
{
	CLS_LinkDevSetEdit *pclsLinkEdit = new CLS_LinkDevSetEdit;
	if (NULL != pclsLinkEdit)
	{
		pclsLinkEdit->InitLinkDevParam(n_Dlg_ADD,m_iLogonID,m_iDevType,m_iDevNo,m_iFreeLinkIndex);
		pclsLinkEdit->DoModal();
// 		if(IDOK == pclsLinkEdit->DoModal())
// 		{
// 			OnCbnSelchangeCboNum();
// 		}
	}
}

void CLS_LinkSet::OnNMClickLstLinkset(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	int nItem = pNMListView->iItem;		//行号
	int nSub = 	pNMListView->iSubItem;	//列号
	int iCount = m_lstLink.GetItemCount();
	if(nItem == -1)	//该行没数据则返回
	{
		return;
	}
	int iRet = -1;
	if (nSub == 4)
	{
		CLS_LinkDevSetEdit *pclsLinkEdit = new CLS_LinkDevSetEdit();
		if (NULL != pclsLinkEdit)
		{
			int iActionNum = (int)m_lstLink.GetItemData(nItem);
			pclsLinkEdit->InitLinkDevParam(n_Dlg_Edit,m_iLogonID,m_iDevType,m_iDevNo,iActionNum);
			if(IDOK == pclsLinkEdit->DoModal())
			{
				OnCbnSelchangeCboNum();
			}
		}
	}

	if (nSub == 5)
	{
		AlarmInLink almInLink = {0};
		almInLink.iSize = sizeof(AlarmInLink);
		almInLink.iLinkEnable = 0;
		almInLink.iLinkIndex = (int)m_lstLink.GetItemData(nItem);
		iRet = NetClient_SetAlarmConfig(m_iLogonID,m_iDevNo,-1,CMD_ALARM_IN_LINK,&almInLink);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","[CLS_LinKSetPage::OnNMClickLstLinkset] NetClient_SetAlarmConfig failed! logonID(%d),m_iChNo(%d),m_iActionNo(%d),error(%d)"
				,m_iLogonID,m_iDevNo,GetLastError());
		}
		OnCbnSelchangeCboNum();
	}
	*pResult = 0;
}