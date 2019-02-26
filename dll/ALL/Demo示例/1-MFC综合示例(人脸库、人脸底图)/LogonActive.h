#ifndef _LOGON_ACTIVE_H
#define _LOGON_ACTIVE_H

#include "Common/CommonFun.h"

// CLS_LogonActive dialog

class CLS_LogonActive : public CDialog
{
	DECLARE_DYNAMIC(CLS_LogonActive)

public:
	CLS_LogonActive(PDEVICE_INFO _pDevice = NULL,CWnd* _pParent = NULL);   // standard constructor
	virtual ~CLS_LogonActive();

// Dialog Data
	enum { IDD = IDD_DLG_MAIN_LOGON_ACTIVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnLogon();
	PDEVICE_INFO GetDeviceInfo(){return &m_tDevice;};

private:
	DEVICE_INFO m_tDevice;
	int m_iMode;
};

#endif
