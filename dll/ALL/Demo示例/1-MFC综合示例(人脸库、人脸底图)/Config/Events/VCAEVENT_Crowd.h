#pragma once

#include "VCAEventBasePage.h"
#include "afxwin.h"

// CLS_VCAEVENT_CROWD dialog

class CLS_VCAEVENT_CROWD : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_CROWD)

public:
	CLS_VCAEVENT_CROWD(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAEVENT_CROWD();

// Dialog Data
	enum { IDD = IDD_DLG_VCAEVENT_CROWD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	void OnLanguageChanged();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

private:
	void UpdatePageUI();
	void UpdateUIText();
	void CleanText();
public:
	CButton m_chkDisplayRule;
	CButton m_chkDisplayState;
	CEdit m_edtPointNum;
	CEdit m_edtPoints;
	afx_msg void OnBnClickedButtonDraw();
	afx_msg void OnBnClickedButtonCrowdset();
	afx_msg void OnBnClickedButtonCrowdStop();
	afx_msg void OnBnClickedButtonCrowdStart();
};
