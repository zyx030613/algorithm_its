#pragma once

#include "VCAEventBasePage.h"
#include "afxwin.h"
// CLS_VCAEVENT_Track dialog

class CLS_VCAEVENT_Track : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_Track)

public:
	CLS_VCAEVENT_Track(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAEVENT_Track();

// Dialog Data
	enum { IDD = IDD_DLG_VCAEVENT_TRACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	CComboBox m_cboTrackNo;
	CComboBox m_cboTrackSence;
	CEdit m_edtTrackRegion;
	afx_msg void OnBnClickedButtonDraw();
	afx_msg void OnBnClickedButtonTrackset();

private:
	void UpdatePageUI();
	void UpdateUIText();
	void CleanText();

public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonCall();
	void OnLanguageChanged();
	
	afx_msg void OnBnClickedButtonTrackstop();
	afx_msg void OnBnClickedButtonTrackstart();
};
