#pragma once

#include "VCAEventBasePage.h"
#include "afxwin.h"
// CLS_VCAEVENT_VIDEODETECT dialog

class CLS_VCAEVENT_VideoDetect : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_VideoDetect)

public:
	CLS_VCAEVENT_VideoDetect(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAEVENT_VideoDetect();

// Dialog Data
	enum { IDD = IDD_DLG_VCAEVENT_VIDEODETECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CButton m_chkDisplayState;
	CEdit m_edtCheckTime;
	CButton m_chkNoise;
	CButton m_chkClarity;
	CButton m_chkBright;
	CButton m_chkColor;
	CButton m_chkFreeze;
	CButton m_chkNosignal;
	CButton m_chkChange;
	CButton m_chkInterfere;
	CButton m_chkPTZ_Lost;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void CleanText();

private:
	void UpdatePageUI();
	void UpdateUIText();
public:
	afx_msg void OnBnClickedButtonVideodetectset();
	void OnLanguageChanged();
	CEdit m_edtEnable;
	CEdit m_edtLevel;
	afx_msg void OnBnClickedButtonVideodetectstop();
	afx_msg void OnBnClickedButtonVideodetectstart();
};
