#ifndef _LOG_VIEW_H_
#define _LOG_VIEW_H_

#include "Common/CommonFun.h"
#include "afxwin.h"
// CLS_LogView dialog

class CLS_LogView : public CDialog
{
	DECLARE_DYNAMIC(CLS_LogView)

public:
	CLS_LogView(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_LogView();

// Dialog Data
	enum { IDD = IDD_DLG_MAIN_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();

private:
	CButton m_chkAddList;
	CButton m_chkOutputDebugString;
	CButton m_chkWriteToFile;
	CButton m_chkOperationSuccess;
	CButton m_chkOperationFail;
	CButton m_chkOperationMsg;
	
};

#endif
