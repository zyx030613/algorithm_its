
#include "stdafx.h"
#include "NetClientDemo.h"
#include "StorageSmartPage.h"


// CLS_StorageSmartPage 对话框

IMPLEMENT_DYNAMIC(CLS_StorageSmartPage, CDialog)

CLS_StorageSmartPage::CLS_StorageSmartPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_StorageSmartPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = -1; 
	m_iSmartDiskSel = 0;
}

CLS_StorageSmartPage::~CLS_StorageSmartPage()
{
}

void CLS_StorageSmartPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_SMART_DISK, m_cboSmartDisk);
	DDX_Control(pDX, IDC_LST_SMART_DISK, m_lstSmartDisk);
	DDX_Control(pDX, IDC_CHK_SMART_DISK_ENABLE, m_chkSmartEnable);
	DDX_Control(pDX, IDC_CHK_SMART_DISK_ASSESS, m_chkSmartAssess);
}


BEGIN_MESSAGE_MAP(CLS_StorageSmartPage, CLS_BasePage)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_CBO_SMART_DISK, &CLS_StorageSmartPage::OnCbnSelchangeCboSmartDisk)
	ON_BN_CLICKED(IDC_CHK_SMART_DISK_ENABLE, &CLS_StorageSmartPage::OnBnClickedChkSmartDiskEnable)
	ON_BN_CLICKED(IDC_CHK_SMART_DISK_ASSESS, &CLS_StorageSmartPage::OnBnClickedChkSmartDiskAssess)
END_MESSAGE_MAP()

BOOL CLS_StorageSmartPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	InitDlgData();
	
	return TRUE;
}

void CLS_StorageSmartPage::InitDlgData()
{
	for(int i = 0; i < DISK_SATA_NUM+DISK_SATA_EX_NUM; i++)
	{
		int iDiskId = i;
		if (i >= DISK_SATA_NUM)
		{
			iDiskId = i + DISK_SATA_EX;
		}
		m_cboSmartDisk.InsertString(i, "SATA"+IntToCString(i+1));
		m_cboSmartDisk.SetItemData(i, iDiskId);
	}
	m_cboSmartDisk.SetCurSel(0);

	m_lstSmartDisk.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_lstSmartDisk.InsertColumn(0, _T("ID"), 0, 60);
	m_lstSmartDisk.InsertColumn(1, _T("ATTRIBUTE_NAME"), 0, 180);
	m_lstSmartDisk.InsertColumn(2, _T("FLAG"), 0, 70);
	m_lstSmartDisk.InsertColumn(3, _T("VALUE"), 0, 70);
	m_lstSmartDisk.InsertColumn(4, _T("WORST"), 0, 70);
	m_lstSmartDisk.InsertColumn(5, _T("THRESH"), 0, 70);
	m_lstSmartDisk.InsertColumn(6, _T("STATUS"), 0, 70);
	m_lstSmartDisk.InsertColumn(7, _T("RAW_VALUE"), 0, 120);
}

void CLS_StorageSmartPage::OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser)
{
	if (m_iLogonID != _ulLogonID)
	{
		return;
	}
	int iMsgType = LOWORD(_iWparam);
	CString strMsg;
	switch(iMsgType)
	{
	case WCM_DISK_SMART_INFO:
		{
			int iDiskId = ((_iWparam>>16)&0xFF);
			DiskSmartMsg *pstSmartMsg = (DiskSmartMsg*)_iLParam;
			UI_UpdateSmartInfo(pstSmartMsg);
		}
		break;
	default:
		break;
	}
}

void CLS_StorageSmartPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		UI_UpdateSurface();
		OnCbnSelchangeCboSmartDisk();//默认显示第一个磁盘的SMART信息
	}
}

void CLS_StorageSmartPage::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;

	UI_UpdateSurface();
}

void CLS_StorageSmartPage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateSurface();
}

void CLS_StorageSmartPage::UI_UpdateSurface()
{
	SetDlgItemTextEx(IDC_STC_SMART_DISK, IDS_SMART_DISK);
	SetDlgItemTextEx(IDC_CHK_SMART_DISK_ENABLE, IDS_SMART_ENABLE);
	SetDlgItemTextEx(IDC_STC_SMART_MODEL, IDS_SMART_MODEL);
	SetDlgItemTextEx(IDC_STC_SMART_INDEX, IDS_SMART_INDEX);
	SetDlgItemTextEx(IDC_STC_SMART_TEP, IDS_SMART_TEP);
	SetDlgItemTextEx(IDC_STC_SMART_USETIME, IDS_SMART_USETIME);
	SetDlgItemTextEx(IDC_STC_SMART_EVALUATE_SELF, IDS_SMART_SELF);
	SetDlgItemTextEx(IDC_STC_SMART_EVALUATE_WHOLE, IDS_SMART_WHOLE);
	SetDlgItemTextEx(IDC_CHK_SMART_DISK_ASSESS, IDS_SMART_ASSESS);
}

void CLS_StorageSmartPage::UI_UpdateSmartInfo(DiskSmartMsg* _pstSmartMsg)
{
 	if (NULL == _pstSmartMsg || NULL == _pstSmartMsg->pstSmartInfo)
 	{
 		return;
 	}

	CString cstrTemp;
	int iSel = m_cboSmartDisk.GetCurSel();
	int iDiskNo = (int)m_cboSmartDisk.GetItemData(iSel);
	if (iDiskNo != _pstSmartMsg->iDiskId)
	{
		return;
	}

	SetDlgItemText(IDC_EDT_SMART_MODEL, (CString)_pstSmartMsg->cHDDModel);
	SetDlgItemText(IDC_EDT_SMART_INDEX, (CString)_pstSmartMsg->cSericalNum);
	SetDlgItemInt(IDC_EDT_SMART_TEP, _pstSmartMsg->iTemprt);
	SetDlgItemInt(IDC_EDT_SMART_USETIME, _pstSmartMsg->iUsedTime);
	SetDlgItemTextEx(IDC_EDT_SMART_EVALUATE_SELF, _pstSmartMsg->iHealth?IDS_SMART_PASS:IDS_SMART_NOPASS);
	SetDlgItemTextEx(IDC_EDT_SMART_EVALUATE_WHOLE, _pstSmartMsg->iHealth?IDS_SMART_HEALTH:IDS_SMART_UNHEALTH);
	
	//表格中插入信息
	m_lstSmartDisk.DeleteAllItems();
	for (int i=0; i<_pstSmartMsg->iTotalSmartInfoNum; i++)
	{
		cstrTemp = (CString)(_pstSmartMsg->pstSmartInfo[i].cId);
		SmartInfo st = _pstSmartMsg->pstSmartInfo[i];
		m_lstSmartDisk.InsertItem(i, cstrTemp);
		m_lstSmartDisk.SetItemText(i, 1, (CString)st.cAttributeName);
		m_lstSmartDisk.SetItemText(i, 2, IntToCString(st.iFlag));
		m_lstSmartDisk.SetItemText(i, 3, IntToCString(st.iValue));
		m_lstSmartDisk.SetItemText(i, 4, IntToCString(st.iWorst));
		m_lstSmartDisk.SetItemText(i, 5, IntToCString(st.iThresh));
		m_lstSmartDisk.SetItemText(i, 6, (CString)st.cStatue);
		m_lstSmartDisk.SetItemText(i, 7, (CString)st.cRawValue);
	}
}

void CLS_StorageSmartPage::OnCbnSelchangeCboSmartDisk()
{
	if (NULL == NetClient_GetDevDiskConfig || NULL == NetClient_SetDevDiskConfig)
	{
		return;
	}

	int iSel = m_cboSmartDisk.GetCurSel();
	if (m_iSmartDiskSel == iSel)
	{
		return;
	}
	m_iSmartDiskSel = iSel;
	int iDiskNo = (int)m_cboSmartDisk.GetItemData(iSel);
	int iReturn = -1;

	DiskSmartEnable stDiskSmartEnable = {0};
	stDiskSmartEnable.iSize = sizeof(DiskSmartEnable);
	stDiskSmartEnable.iDiskId = iDiskNo;
	int iRet = NetClient_GetDevDiskConfig(m_iLogonID, NET_CLIENT_DISK_SMART_ENABLE, m_iChannelNo, &stDiskSmartEnable, sizeof(DiskSmartEnable), &iReturn);
	if (0 == iRet)
	{
		m_chkSmartEnable.SetCheck(stDiskSmartEnable.iEnable);
	}

	DiskSmartMsg stDiskSmartMsg = {0};
	stDiskSmartMsg.iSize = sizeof(DiskSmartMsg);
	stDiskSmartMsg.iDiskId = iDiskNo;
	iRet = NetClient_SetDevDiskConfig(m_iLogonID, NET_CLIENT_SMART_INFO, m_iChannelNo, &stDiskSmartMsg, sizeof(DiskSmartMsg));
	if (0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevDiskConfig(%d,%d,%d)",m_iLogonID, NET_CLIENT_SMART_INFO, m_iChannelNo);
	}

	SmartCheck stDiskSmartAssess = {0};
	stDiskSmartAssess.iSize = sizeof(stDiskSmartAssess);
	stDiskSmartAssess.iDiskId = iDiskNo;
	int iRetAses = NetClient_GetDevDiskConfig(m_iLogonID, NET_CLIENT_SMART_CHECK, m_iChannelNo, &stDiskSmartAssess, sizeof(SmartCheck), &iReturn);
	if (RET_SUCCESS == iRetAses)
	{
		m_chkSmartAssess.SetCheck(stDiskSmartAssess.iEnable);
	}
	if (RET_FAILED == iRetAses)
	{
		m_chkSmartAssess.SetCheck(BST_UNCHECKED);
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevDiskConfig(%d,%d,%d)",m_iLogonID, NET_CLIENT_SMART_CHECK, m_iChannelNo);
	}

	DiskSmartMsg *pstSmartMsg = {0};
	UI_UpdateSmartInfo(pstSmartMsg);
}

void CLS_StorageSmartPage::OnBnClickedChkSmartDiskEnable()
{
	if (NULL == NetClient_SetDevDiskConfig)
	{
		return;
	}

	int iSel = m_cboSmartDisk.GetCurSel();
	DiskSmartEnable stDiskSmartEnable = {0};
	stDiskSmartEnable.iSize = sizeof(DiskSmartEnable);
	stDiskSmartEnable.iDiskId = (int)m_cboSmartDisk.GetItemData(iSel);
	stDiskSmartEnable.iEnable = m_chkSmartEnable.GetCheck()?1:0;
	
	int iRet = NetClient_SetDevDiskConfig(m_iLogonID, NET_CLIENT_DISK_SMART_ENABLE, m_iChannelNo, &stDiskSmartEnable, sizeof(DiskSmartEnable));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevDiskConfig(%d,%d,%d)",m_iLogonID, NET_CLIENT_DISK_SMART_ENABLE, m_iChannelNo);
	}
}

void CLS_StorageSmartPage::OnBnClickedChkSmartDiskAssess()
{
	if (NULL == NetClient_SetDevDiskConfig)
	{
		return;
	}
	int iSel = m_cboSmartDisk.GetCurSel();
	SmartCheck stDiskSmartAssess = {0};
	stDiskSmartAssess.iSize = sizeof(stDiskSmartAssess);
	stDiskSmartAssess.iDiskId = (int)m_cboSmartDisk.GetItemData(iSel);
	stDiskSmartAssess.iEnable = m_chkSmartAssess.GetCheck()?1:0;

	int iRet = NetClient_SetDevDiskConfig(m_iLogonID, NET_CLIENT_SMART_CHECK, m_iChannelNo, &stDiskSmartAssess, sizeof(SmartCheck));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevDiskConfig(%d,%d,%d)",m_iLogonID, NET_CLIENT_SMART_CHECK, m_iChannelNo);
	}
}
