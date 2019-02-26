#ifndef _ECOP_OTHER_PAGE_H
#define _ECOP_OTHER_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"

// CLS_ECOPOtherPage dialog

class CLS_ECOPOtherPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ECOPOtherPage)

public:
	CLS_ECOPOtherPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ECOPOtherPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ECOP_OTHER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateOther();

private:
	CComboBox m_cboRoadwayID;
	CButton m_chkEnable;
	CComboBox m_cboSnType;
	CEdit m_edtSn;
	CEdit m_edtLocalRet;
	CButton m_btnSn;
	CEdit m_edtSystemType;
	CButton m_btnSystem;
	int m_iLogonID;

public:
	afx_msg void OnCbnSelchangeComboRoadwayid();
	afx_msg void OnBnClickedCheckWatermarkEnable();
	afx_msg void OnBnClickedButtonSn();
	afx_msg void OnBnClickedButtonSystem();
};

#endif