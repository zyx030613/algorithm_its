#ifndef _LOGON_VIEW_H
#define _LOGON_VIEW_H

#include "Common/CommonFun.h"

// CLS_LogonView dialog

class CLS_LogonView : public CDialog
{
	DECLARE_DYNAMIC(CLS_LogonView)

public:
	CLS_LogonView(PDEVICE_INFO _pDevice = NULL,CWnd* _pParent = NULL);   
	virtual ~CLS_LogonView();

// Dialog Data
	enum { IDD = IDD_DLG_MAIN_LOGON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnLogon();
	afx_msg LRESULT OnGetDefID(WPARAM _wParam,LPARAM _lParam);
	PDEVICE_INFO GetDeviceInfo(){return &m_tDevice;};

private:
	DEVICE_INFO m_tDevice;
	int m_iMode;

};

#endif