#ifndef _ECOP_CAPTURE_PAGE_H
#define _ECOP_CAPTURE_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"


// CLS_ECOPCapturePage dialog

class CLS_ECOPCapturePage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ECOPCapturePage)

public:
	CLS_ECOPCapturePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ECOPCapturePage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ECOP_CAPTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateCapture();

private:
	CComboBox m_cboRoadwayID;
	CEdit m_edtCaptureType;
	CEdit m_edtFirstPlace;
	CEdit m_edtSecondPlace;
	CEdit m_edtThirdPlace;
	CButton m_btnCapture;
	int m_iLogonID;
public:
	afx_msg void OnCbnSelchangeComboRoadwayid();
	afx_msg void OnBnClickedButtonCapture();
};

#endif