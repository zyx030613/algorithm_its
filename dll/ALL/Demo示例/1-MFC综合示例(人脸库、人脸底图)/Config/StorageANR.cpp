#include "stdafx.h"
#include "NetClientDemo.h"
#include "StorageANR.h"

#define ANRENABLE 35

IMPLEMENT_DYNAMIC(CLS_StorageANR, CDialog)

CLS_StorageANR::CLS_StorageANR(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_StorageANR::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_StorageANR::~CLS_StorageANR()
{
}

void CLS_StorageANR::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_STROAGE_ANR, m_cboDisconnectRec);
}


BEGIN_MESSAGE_MAP(CLS_StorageANR, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_STORAGE_ANR_SET, &CLS_StorageANR::OnBnClickedBtnStorageAnrSet)
END_MESSAGE_MAP()

BOOL CLS_StorageANR::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UI_UpdateDialogTest();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_StorageANR::UI_UpdateDialogTest()
{
	int iREnable = -1;

	m_cboDisconnectRec.ResetContent();
	m_cboDisconnectRec.AddString(GetTextEx(IDS_STORAGE_ANR_WIRELESS_OPEN));
	m_cboDisconnectRec.AddString(GetTextEx(IDS_STORAGE_ANR_WIRELESS_CLOSE));

	SetDlgItemTextEx(IDC_STC_STORAGE_ANR, IDS_STC_STORAGE_ANR);
	SetDlgItemTextEx(IDC_BTN_STORAGE_ANR_SET, IDS_BTN_STORAGE_ANR_SET);

	int iRet = NetClient_GetFuncListArray(m_iLogonID, &iREnable);
	if(RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetFuncListArray(%d)", iRet);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetFuncListArray(%d)", iRet);
	}

	if(ANRENABLE == iREnable)
	{
		m_cboDisconnectRec.SetCurSel(0);
	}
	else
	{
		m_cboDisconnectRec.SetCurSel(1);
	}
}

void CLS_StorageANR::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialogTest();

	return;
}

void CLS_StorageANR::OnChannelChanged(int _iLogonID, int _iChannelNo, int _iStreamNo)
{
	m_iLogonID = _iLogonID;

	UI_UpdateDialogTest();

	return;
}
void CLS_StorageANR::OnBnClickedBtnStorageAnrSet()
{
	// TODO: Add your control notification handler code here

	int iRecEnable = m_cboDisconnectRec.GetCurSel();
	int iFunList = 0;
	if(NetClient_GetFuncListArray(m_iLogonID, &iFunList) != 0)
	{
		iFunList = 0;
	}

	if (iRecEnable ==0)
	{	
		iFunList |= 0x01;
	} 
	else
	{
		iFunList = iFunList & 0xFFFE;
	}
	
	int iRet = NetClient_SetFuncListArray(m_iLogonID, iFunList);
	if(RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetFuncListArray(%d)", iRet);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetFuncListArray(%d)", iRet);
	}
}
