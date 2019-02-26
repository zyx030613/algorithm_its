// LogView.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "LogView.h"


// CLS_LogView dialog

IMPLEMENT_DYNAMIC(CLS_LogView, CDialog)

CLS_LogView::CLS_LogView(CWnd* pParent /*=NULL*/)
	: CDialog(CLS_LogView::IDD, pParent)
{

}

CLS_LogView::~CLS_LogView()
{

}

void CLS_LogView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_OUTPUT_STRING, m_chkOutputDebugString);
	DDX_Control(pDX, IDC_CHECK_WRITE_FILE, m_chkWriteToFile);
	DDX_Control(pDX, IDC_CHECK_OPERATION_SUCCESS, m_chkOperationSuccess);
	DDX_Control(pDX, IDC_CHECK_OPERATION_FAILED, m_chkOperationFail);
	DDX_Control(pDX, IDC_CHECK_OPERATION_MSG, m_chkOperationMsg);
	DDX_Control(pDX, IDC_CHECK_ADD_LIST, m_chkAddList);
}


BEGIN_MESSAGE_MAP(CLS_LogView, CDialog)
	ON_BN_CLICKED(IDC_BTN_OK, &CLS_LogView::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CLS_LogView::OnBnClickedBtnCancel)
END_MESSAGE_MAP()


// CLS_LogView message handlers

BOOL CLS_LogView::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(GetTextEx(IDS_LOG_CONFIG));
	SetDlgItemTextEx(IDC_CHECK_ADD_LIST,IDS_LOG_ADD_LIST);
	SetDlgItemTextEx(IDC_CHECK_WRITE_FILE,IDS_LOG_WRITE_FILE);
	SetDlgItemTextEx(IDC_CHECK_OUTPUT_STRING,IDS_LOG_OUT_STRING);
	SetDlgItemTextEx(IDC_CHECK_OPERATION_SUCCESS,IDS_LOG_OPERATION_SUCCESS);
	SetDlgItemTextEx(IDC_CHECK_OPERATION_FAILED,IDS_LOG_OPERATION_FAIL);
	SetDlgItemTextEx(IDC_CHECK_OPERATION_MSG,IDS_LOG_OPERATION_MSG);
	SetDlgItemTextEx(IDC_BTN_OK,IDS_OK);
	SetDlgItemTextEx(IDC_BTN_CANCEL,IDS_CANCEL);

	unsigned int uCaps = GetLogCaps();
	if (uCaps & LOG_CAP_SUCC)
	{
		m_chkOperationSuccess.SetCheck(TRUE);
	}
	if (uCaps & LOG_CAP_FAIL)
	{
		m_chkOperationFail.SetCheck(TRUE);
	}
	if (uCaps & LOG_CAP_MSG)
	{
		m_chkOperationMsg.SetCheck(TRUE);
	}	
	if (uCaps & LOG_CAP_ADD_LIST)
	{
		m_chkAddList.SetCheck(TRUE);
	}	
	if (uCaps & LOG_CAP_OUTPUT_STRING)
	{
		m_chkOutputDebugString.SetCheck(TRUE);
	}
	if (uCaps & LOG_CAP_WRITE_FILE)
	{
		m_chkWriteToFile.SetCheck(TRUE);
	}

	return TRUE;  
}

void CLS_LogView::OnBnClickedBtnOk()
{
	unsigned int uCaps = 0;
	uCaps |= m_chkOperationSuccess.GetCheck();
	uCaps |= (m_chkOperationFail.GetCheck() << 1);
	uCaps |= (m_chkOperationMsg.GetCheck() << 2);
	uCaps |= (m_chkAddList.GetCheck() << 3);
	uCaps |= (m_chkOutputDebugString.GetCheck() << 4);
	uCaps |= (m_chkWriteToFile.GetCheck() << 5);
	SetLogCaps(LOG_CAP_ALL,uCaps);
	OnOK();
}

void CLS_LogView::OnBnClickedBtnCancel()
{
	OnCancel();
}
