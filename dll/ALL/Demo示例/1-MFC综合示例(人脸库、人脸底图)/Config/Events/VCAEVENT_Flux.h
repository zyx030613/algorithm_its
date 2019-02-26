#pragma once

#include "VCAEventBasePage.h"
#include "afxwin.h"

// CLS_EVENT_FULX dialog

class CLS_EVENT_FULX : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_EVENT_FULX)

public:
	CLS_EVENT_FULX(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_EVENT_FULX();

// Dialog Data
	enum { IDD = IDD_DLG_VCAEVENT_FLUX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void OnLanguageChanged();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonFluxset();
	afx_msg void OnBnClickedButtonDraw();

private:
	void UpdatePageUI();
	void UpdateUIText();
	void CleanText();

public:
	CButton m_chkDisplayRule;
	CButton m_chkDisplayState;
	CEdit m_edtPointNum;
	CEdit m_edtPoints;
	afx_msg void OnBnClickedButtonFluxstop();
	afx_msg void OnBnClickedButtonFluxstart();
};
