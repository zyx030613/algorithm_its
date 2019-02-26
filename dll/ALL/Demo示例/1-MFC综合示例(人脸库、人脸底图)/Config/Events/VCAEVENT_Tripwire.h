#pragma once

#include "afxwin.h"
#include "VCAEventBasePage.h"

// CLS_VCAEVENT_Tripwire dialog

class CLS_VCAEVENT_Tripwire : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(CLS_VCAEVENT_Tripwire)

public:
	CLS_VCAEVENT_Tripwire(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAEVENT_Tripwire();

// Dialog Data
	enum { IDD = IDD_DLG_VCAEVENT_TRIPWIRE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
// 	int		m_iLogonID;
// 	int		m_iChannelNO;
// 	int		m_iStreamNO;

private:
	void UpdatePageUI();
	void UpdateUIText();
	void CleanText();

public:
	afx_msg void OnBnClickedButtonDraw();

// 	void Init(int _iLogonID,int _iChannelNo,int _iStreamNo);
// 	void OnMainNotify( int _iLogonID,int _wParam, int _lParam,int _iUserData );
	afx_msg void OnBnClickedButtonTripset();
	CButton m_chkDisplayRule;
	CButton m_chkDisplayState;
	CButton m_chkDoubleDir;
	CEdit m_edtMinDis;
	CEdit m_edtMinTime;
	CComboBox m_cboColor;
	CComboBox m_cboAlarmColor;
	CEdit m_edtDirection;
	CEdit m_edtPoints;
	CEdit m_edtPointNum;
	CComboBox m_cboTargetCheck;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	void OnLanguageChanged();
	afx_msg void OnBnClickedButtonTripstop();
	afx_msg void OnBnClickedButtonTripstart();
};
