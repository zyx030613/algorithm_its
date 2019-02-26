#ifndef _3GNORMAL_PAGE_H_
#define _3GNORMAL_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"

// CLS_3GNormalPage dialog

class CLS_3GNormalPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_3GNormalPage)

public:
	CLS_3GNormalPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_3GNormalPage();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

// Dialog Data
	enum { IDD = IDD_DLG_CFG_3G_NORMAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3GNormalGetStatus();
	afx_msg void OnBnClickedButton3GNormalDisconnect();
	afx_msg void OnBnClickedButton3GNormalDialogSet();
	afx_msg void OnBnClickedButton3GNormalMessageSet();
	void UI_UpdateDialog();
	void UI_UpdateDeviceStatus();
	void UI_Update3GDialogInfo();
	void UI_Update3GMessageInfo();
private:
	int m_iLogonID;
	CComboBox m_cboDeviceType;
	CComboBox m_cboDeviceStatus;
	CEdit m_edtDeviceIP;
	CEdit m_edtIntensity;
	CComboBox m_cboStartType;
	CComboBox m_cboStopType;
	CEdit m_edtDuration;
	CEdit m_edtNotify;
	CEdit m_edtPNum1;
	CEdit m_edtPNum2;
	CEdit m_edtPNum3;
	CEdit m_edtPNum4;
	CEdit m_edtPNum5;
	CEdit m_edtStartTime;
public:
	virtual BOOL OnInitDialog();
};

#endif
