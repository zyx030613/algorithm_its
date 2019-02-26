
#include "stdafx.h"
#include "NetClientDemo.h"
#include "SerialManagePage.h"
#include "..\Common\CommonFun.h"

// CLS_SerialManagePage 对话框
#define  MAX_SWITCH_NUM		0
#define  MAX_ANALOG_NUM		0

IMPLEMENT_DYNAMIC(CLS_SerialManagePage, CDialog)

CLS_SerialManagePage::CLS_SerialManagePage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_SerialManagePage::IDD, pParent)
{
	m_iLogonID = -1;
	m_pclsSerialInfo = NULL;
}

 CLS_SerialManagePage::~CLS_SerialManagePage()
{
	if (m_pclsSerialInfo !=NULL)
	{
		delete m_pclsSerialInfo;
		m_pclsSerialInfo = NULL;
	}
}

void  CLS_SerialManagePage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_COM_MNG, m_lstComMng);
}


BEGIN_MESSAGE_MAP(CLS_SerialManagePage, CDialog)
ON_NOTIFY(NM_CLICK, IDC_LST_COM_MNG, & CLS_SerialManagePage::OnNMClickLstComMng)
END_MESSAGE_MAP()


// CLS_SerialManagePage 消息处理程序

BOOL CLS_SerialManagePage::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemTextEx(IDC_STC_COM_MNG, IDS_CONFIG_DONGHUAN_COMFORT);
	int iColumn = 0;
	DWORD dwStyle = m_lstComMng.GetExtendedStyle();
	dwStyle = dwStyle | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;  
	m_lstComMng.SetExtendedStyle(dwStyle);
	InsertColumn(m_lstComMng, iColumn++, IDS_CONFIG_COM_NUM, LVCFMT_LEFT, 100);
	InsertColumn(m_lstComMng, iColumn++, IDS_CONFIG_COM_DEVICE_TYPE, LVCFMT_LEFT, 200);
	InsertColumn(m_lstComMng, iColumn++, IDS_CONFIG_COM_INFO, LVCFMT_LEFT, 100);
	InsertColumn(m_lstComMng, iColumn++, IDS_CONFIG_OPETATE, LVCFMT_LEFT, 100);

	if (NULL == m_pclsSerialInfo)
	{
		m_pclsSerialInfo = new CLS_SerialInfo();
	}
	
	return TRUE;  
}

void CLS_SerialManagePage::OnLanguageChanged( int _iLanguage )
{
	OnInitDialog();
	UI_Update();
}

void CLS_SerialManagePage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	UI_Update();
}

BOOL CLS_SerialManagePage::UI_Update()
{
	int iRet = -1;
	int iCount = 0;
	int iStatus = 0;
	iRet = NetClient_GetComPortCounts(m_iLogonID, &iCount, &iStatus);
	if (0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetAlarmPortNum(%d,%d,%d)"
			,m_iLogonID,iCount,iStatus);
		return FALSE;
	}
	int iRow = 0;
	m_lstComMng.DeleteAllItems();
	for (int i=0;i<iCount;i++)
	{	
		CString csTmp;
		m_lstComMng.InsertItem(i,"");	
		csTmp.Format("COM%d",i+1);
		m_lstComMng.SetItemText(i, 0, csTmp);
		m_lstComMng.SetItemText(i, 3, GetTextEx(IDS_CONFIG_LINK_EDIT));
		UpdateComInfo(i+1);
	}
	return TRUE;
}

void CLS_SerialManagePage::UpdateComInfo(int _iComNo)
{
	int iRow = _iComNo - 1;
	ComDevice srcComDevice = {0};
	srcComDevice.iSize = sizeof(ComDevice);
	srcComDevice.iComNo = _iComNo;
	int iBytesReturned = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_COM_DEVICE, -1, &srcComDevice, sizeof(srcComDevice), &iBytesReturned);
	if(iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig(%d)"
			,m_iLogonID);
		return;
	}

	//更新设备类型
	string strType;
	CString cstrTypeName;
	m_pclsSerialInfo->GetDevTypeName(srcComDevice.iDeviceType, strType);
	cstrTypeName = strType.c_str();
	m_lstComMng.SetItemText(iRow, 1, cstrTypeName);
	
	//更新串口信息
	m_lstComMng.SetItemText(iRow, 2, srcComDevice.cComFormat);
}

void  CLS_SerialManagePage::OnNMClickLstComMng(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	int nItem = pNMListView->iItem;		//行号
	int nSub = 	pNMListView->iSubItem;	//列号
	int iCount = m_lstComMng.GetItemCount();
	if(nItem == -1)	//该行没数据则返回
	{
		return;
	}
	
	if (nSub == 3)
	{
		m_pclsSerialInfo->InitParam(m_iLogonID,nItem+1);
		if(IDOK == m_pclsSerialInfo->DoModal())
		{
			UI_Update();
		}
	}
	*pResult = 0;
}
