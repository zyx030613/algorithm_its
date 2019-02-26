#ifndef _ECOP_LIGHT_PAGE_H
#define _ECOP_LIGHT_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"

// CLS_ECOPLightPage dialog

class CLS_ECOPLightPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ECOPLightPage)

public:
	CLS_ECOPLightPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ECOPLightPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ECOP_LIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	BOOL UI_UpdateChnLight();
	BOOL UI_UpdateLightInfo();

private:
	CComboBox m_cboRoadwayID;
	CComboBox m_cboComNo;
	CEdit m_edtLightID;
	CEdit m_edtFloodID;
	CButton m_btnChnLight;
	CComboBox m_cboLightInfoID;
	CEdit m_edtInterval;
	CEdit m_edtAcceptDiff;
	CButton m_btnLightInfo;
	int m_iLogonID;

public:
	afx_msg void OnBnClickedButtonChnlight();
	afx_msg void OnBnClickedButtonLightinfo();
	afx_msg void OnCbnSelchangeComboRoadwayid();
	afx_msg void OnCbnSelchangeComboLightinfoid();
};

#endif