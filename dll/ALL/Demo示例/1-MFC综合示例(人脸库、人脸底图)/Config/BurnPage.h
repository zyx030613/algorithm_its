#ifndef _BURN_PAGE_H
#define _BURN_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxdtctl.h"

// CLS_BurnPage dialog

class CLS_BurnPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_BurnPage)

public:
	CLS_BurnPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_BurnPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_BURN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser);
private:
	void UI_UpdateDialog();
	BOOL UI_UpdateCount();
	BOOL UI_UpdateMode();
	BOOL UI_UpdateSet();
	BOOL UI_UpdateStatus();

private:
	CComboBox m_cboBurnMode;
	CEdit m_edtChannelBits;
	CEdit m_edtCDRomBits;
	CComboBox m_cboDiskType;
	CComboBox m_cboBurnSpeed;
	CEdit m_edtBurnHour;
	CEdit m_edtResSpace;
	CEdit m_edtDvdName;
	CButton m_btnSet;
	CComboBox m_cboCDRomID;
	CEdit m_edtFlagByBits;
	CComboBox m_cboBurnStatus;
	CEdit m_edtTotalSpace;
	CEdit m_edtFreeSpace;
	CEdit m_edtReserved;
	CButton m_btnStartBurn;
	CButton m_btnStopBurn;
	int m_iLogonID;

public:
	afx_msg void OnCbnSelchangeComboBurnmode();
	afx_msg void OnBnClickedButtonDvdname();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonStartburn();
	afx_msg void OnBnClickedButtonStopburn();
	afx_msg void OnCbnSelchangeComboCdromId();
private:
	CComboBox m_cboBurnFileMode;
};

#endif