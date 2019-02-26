// Config/DZPage.cpp : implementation file
//

#include "stdafx.h"
#include "DZPage.h"


// CLS_DZPage dialog

IMPLEMENT_DYNAMIC(CLS_DZPage, CDialog)

CLS_DZPage::CLS_DZPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DZPage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_DZPage::~CLS_DZPage()
{
}

void CLS_DZPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PARAM1, m_edtParam1);
	DDX_Control(pDX, IDC_EDIT_PARAM2, m_edtParam2);
	DDX_Control(pDX, IDC_EDIT_PARAM3, m_edtParam3);
	DDX_Control(pDX, IDC_EDIT_PARAM4, m_edtParam4);
	DDX_Control(pDX, IDC_EDIT_PARAM5, m_edtParam5);
	DDX_Control(pDX, IDC_EDIT_PARAM6, m_edtParam6);
	DDX_Control(pDX, IDC_EDIT_PARAM7, m_edtParam7);
	DDX_Control(pDX, IDC_EDIT_PARAM8, m_edtParam8);
	DDX_Control(pDX, IDC_EDIT_PARAM9, m_edtParam9);
	DDX_Control(pDX, IDC_EDIT_PARAM10, m_edtParam10);
	DDX_Control(pDX, IDC_EDIT_PARAM11, m_edtParam11);
	DDX_Control(pDX, IDC_EDIT_PARAM12, m_edtParam12);
	DDX_Control(pDX, IDC_EDIT_PARAM13, m_edtParam13);
	DDX_Control(pDX, IDC_EDIT_PARAM14, m_edtParam14);
	DDX_Control(pDX, IDC_EDIT_PARAM15, m_edtParam15);
	DDX_Control(pDX, IDC_EDIT_PARAM16, m_edtParam16);
	DDX_Control(pDX, IDC_EDIT_PARAM17, m_edtParam17);
	DDX_Control(pDX, IDC_EDIT_PARAM18, m_edtParam18);
	DDX_Control(pDX, IDC_EDIT_PARAM19, m_edtParam19);
	DDX_Control(pDX, IDC_EDIT_PARAM20, m_edtParam20);
}


BEGIN_MESSAGE_MAP(CLS_DZPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_DZSET, &CLS_DZPage::OnBnClickedButtonDzset)
END_MESSAGE_MAP()


// CLS_DZPage message handlers

BOOL CLS_DZPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	m_iLogonID = -1;

	m_edtParam1.SetLimitText(63);
	m_edtParam2.SetLimitText(63);
	m_edtParam3.SetLimitText(63);
	m_edtParam4.SetLimitText(63);
	m_edtParam5.SetLimitText(63);
	m_edtParam6.SetLimitText(63);
	m_edtParam7.SetLimitText(63);
	m_edtParam8.SetLimitText(63);
	m_edtParam9.SetLimitText(63);
	m_edtParam10.SetLimitText(63);
	m_edtParam11.SetLimitText(63);
	m_edtParam12.SetLimitText(63);
	m_edtParam13.SetLimitText(63);
	m_edtParam14.SetLimitText(63);
	m_edtParam15.SetLimitText(63);
	m_edtParam16.SetLimitText(63);
	m_edtParam17.SetLimitText(63);
	m_edtParam18.SetLimitText(63);
	m_edtParam19.SetLimitText(63);
	m_edtParam20.SetLimitText(63);

	UI_UpdateDialog();
	return TRUE;
}

void CLS_DZPage::OnChannelChanged( int _iLogonID, int /*_iChannelNo*/, int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	DZ_INFO_PARAM tDZInfo;
	memset(&tDZInfo, 0, sizeof(DZ_INFO_PARAM));
	int iRet;
	iRet = NetClient_GetDZInfo(m_iLogonID, &tDZInfo);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetDZInfo(%d)", m_iLogonID);
		m_edtParam1.SetWindowText(tDZInfo.m_cParam1); 
		m_edtParam2.SetWindowText(tDZInfo.m_cParam2);  
		m_edtParam3.SetWindowText(tDZInfo.m_cParam3);  
		m_edtParam4.SetWindowText(tDZInfo.m_cParam4);  
		m_edtParam5.SetWindowText(tDZInfo.m_cParam5);  
		m_edtParam6.SetWindowText(tDZInfo.m_cParam6);  
		m_edtParam7.SetWindowText(tDZInfo.m_cParam7);  
		m_edtParam8.SetWindowText(tDZInfo.m_cParam8);  
		m_edtParam9.SetWindowText(tDZInfo.m_cParam9);  
		m_edtParam10.SetWindowText(tDZInfo.m_cParam10);  
		m_edtParam11.SetWindowText(tDZInfo.m_cParam11);  
		m_edtParam12.SetWindowText(tDZInfo.m_cParam12);  
		m_edtParam13.SetWindowText(tDZInfo.m_cParam13);  
		m_edtParam14.SetWindowText(tDZInfo.m_cParam14);  
		m_edtParam15.SetWindowText(tDZInfo.m_cParam15);  
		m_edtParam16.SetWindowText(tDZInfo.m_cParam16);  
		m_edtParam17.SetWindowText(tDZInfo.m_cParam17);  
		m_edtParam18.SetWindowText(tDZInfo.m_cParam18);  
		m_edtParam19.SetWindowText(tDZInfo.m_cParam19);
		m_edtParam20.SetWindowText(tDZInfo.m_cParam20);  
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDZInfo(%d)", m_iLogonID);
	}
}

void CLS_DZPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();		
}
void CLS_DZPage::OnBnClickedButtonDzset()
{
	DZ_INFO_PARAM tDZInfo;
	memset(&tDZInfo,0,sizeof(DZ_INFO_PARAM));

	CString strParam1;
	m_edtParam1.GetWindowText(strParam1);
	strcpy_s(tDZInfo.m_cParam1, sizeof(tDZInfo.m_cParam1), (LPSTR)(LPCTSTR)strParam1);
	CString strParam2;
	m_edtParam2.GetWindowText(strParam2);
	strcpy_s(tDZInfo.m_cParam2, sizeof(tDZInfo.m_cParam2), (LPSTR)(LPCTSTR)strParam2);
	CString strParam3;
	m_edtParam3.GetWindowText(strParam3);
	strcpy_s(tDZInfo.m_cParam3, sizeof(tDZInfo.m_cParam3), (LPSTR)(LPCTSTR)strParam3);
	CString strParam4;
	m_edtParam4.GetWindowText(strParam4);
	strcpy_s(tDZInfo.m_cParam4, sizeof(tDZInfo.m_cParam4), (LPSTR)(LPCTSTR)strParam4);
	CString strParam5 ;
	m_edtParam5.GetWindowText(strParam5);
	strcpy_s(tDZInfo.m_cParam5, sizeof(tDZInfo.m_cParam5), (LPSTR)(LPCTSTR)strParam5);
	CString strParam6;
	m_edtParam6.GetWindowText(strParam6);
	strcpy_s(tDZInfo.m_cParam6, sizeof(tDZInfo.m_cParam6), (LPSTR)(LPCTSTR)strParam6);
	CString strParam7;
	m_edtParam7.GetWindowText(strParam7);
	strcpy_s(tDZInfo.m_cParam7, sizeof(tDZInfo.m_cParam7), (LPSTR)(LPCTSTR)strParam7);
	CString strParam8;
	m_edtParam8.GetWindowText(strParam8);
	strcpy_s(tDZInfo.m_cParam8, sizeof(tDZInfo.m_cParam8), (LPSTR)(LPCTSTR)strParam8);
	CString strParam9;
	m_edtParam9.GetWindowText(strParam9);
	strcpy_s(tDZInfo.m_cParam9, sizeof(tDZInfo.m_cParam9), (LPSTR)(LPCTSTR)strParam9);
	CString strParam10;
	m_edtParam10.GetWindowText(strParam10);
	strcpy_s(tDZInfo.m_cParam10, sizeof(tDZInfo.m_cParam10), (LPSTR)(LPCTSTR)strParam10);
	CString strParam11;
	m_edtParam11.GetWindowText(strParam11);
	strcpy_s(tDZInfo.m_cParam11, sizeof(tDZInfo.m_cParam11), (LPSTR)(LPCTSTR)strParam11);
	CString strParam12;
	m_edtParam12.GetWindowText(strParam12);
	strcpy_s(tDZInfo.m_cParam12, sizeof(tDZInfo.m_cParam12), (LPSTR)(LPCTSTR)strParam12);
	CString strParam13;
	m_edtParam13.GetWindowText(strParam13);
	strcpy_s(tDZInfo.m_cParam13, sizeof(tDZInfo.m_cParam13), (LPSTR)(LPCTSTR)strParam13);
	CString strParam14;
	m_edtParam14.GetWindowText(strParam14);
	strcpy_s(tDZInfo.m_cParam14, sizeof(tDZInfo.m_cParam14), (LPSTR)(LPCTSTR)strParam14);
	CString strParam15;
	m_edtParam15.GetWindowText(strParam15);
	strcpy_s(tDZInfo.m_cParam15, sizeof(tDZInfo.m_cParam15), (LPSTR)(LPCTSTR)strParam15);
	CString strParam16;
	m_edtParam16.GetWindowText(strParam16);
	strcpy_s(tDZInfo.m_cParam16, sizeof(tDZInfo.m_cParam16), (LPSTR)(LPCTSTR)strParam16);
	CString strParam17;
	m_edtParam17.GetWindowText(strParam17);
	strcpy_s(tDZInfo.m_cParam17, sizeof(tDZInfo.m_cParam17), (LPSTR)(LPCTSTR)strParam17);
	CString strParam18;
	m_edtParam18.GetWindowText(strParam18);
	strcpy_s(tDZInfo.m_cParam18, sizeof(tDZInfo.m_cParam18), (LPSTR)(LPCTSTR)strParam18);
	CString strParam19;
	m_edtParam19.GetWindowText(strParam19);
	strcpy_s(tDZInfo.m_cParam19, sizeof(tDZInfo.m_cParam19), (LPSTR)(LPCTSTR)strParam19);
	CString strParam20;
	m_edtParam20.GetWindowText(strParam20);
	strcpy_s(tDZInfo.m_cParam20, sizeof(tDZInfo.m_cParam20), (LPSTR)(LPCTSTR)strParam20);

	int iRet;
	iRet = NetClient_SetDZInfo(m_iLogonID, &tDZInfo);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetDZInfo(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDZInfo(%d)", m_iLogonID);
	}

}

void CLS_DZPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_PARAM1, IDS_CONFIG_DZ_PARAM1);
	SetDlgItemTextEx(IDC_STATIC_PARAM2, IDS_CONFIG_DZ_PARAM2);
	SetDlgItemTextEx(IDC_STATIC_PARAM3, IDS_CONFIG_DZ_PARAM3);
	SetDlgItemTextEx(IDC_STATIC_PARAM4, IDS_CONFIG_DZ_PARAM4);
	SetDlgItemTextEx(IDC_STATIC_PARAM5, IDS_CONFIG_DZ_PARAM5);
	SetDlgItemTextEx(IDC_STATIC_PARAM6, IDS_CONFIG_DZ_PARAM6);
	SetDlgItemTextEx(IDC_STATIC_PARAM7, IDS_CONFIG_DZ_PARAM7);
	SetDlgItemTextEx(IDC_STATIC_PARAM8, IDS_CONFIG_DZ_PARAM8);
	SetDlgItemTextEx(IDC_STATIC_PARAM9, IDS_CONFIG_DZ_PARAM9);
	SetDlgItemTextEx(IDC_STATIC_PARAM10, IDS_CONFIG_DZ_PARAM10);
	SetDlgItemTextEx(IDC_STATIC_PARAM11, IDS_CONFIG_DZ_PARAM11);
	SetDlgItemTextEx(IDC_STATIC_PARAM12, IDS_CONFIG_DZ_PARAM12);
	SetDlgItemTextEx(IDC_STATIC_PARAM13, IDS_CONFIG_DZ_PARAM13);
	SetDlgItemTextEx(IDC_STATIC_PARAM14, IDS_CONFIG_DZ_PARAM14);
	SetDlgItemTextEx(IDC_STATIC_PARAM15, IDS_CONFIG_DZ_PARAM15);
	SetDlgItemTextEx(IDC_STATIC_PARAM16, IDS_CONFIG_DZ_PARAM16);
	SetDlgItemTextEx(IDC_STATIC_PARAM17, IDS_CONFIG_DZ_PARAM17);
	SetDlgItemTextEx(IDC_STATIC_PARAM18, IDS_CONFIG_DZ_PARAM18);
	SetDlgItemTextEx(IDC_STATIC_PARAM19, IDS_CONFIG_DZ_PARAM19);
	SetDlgItemTextEx(IDC_STATIC_PARAM20, IDS_CONFIG_DZ_PARAM20);
	SetDlgItemTextEx(IDC_BUTTON_DZSET, IDS_CONFIG_DZ_SET);
}