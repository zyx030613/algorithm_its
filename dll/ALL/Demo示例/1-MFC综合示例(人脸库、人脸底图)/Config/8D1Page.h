#ifndef _8D1_PAGE_H
#define _8D1_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"

// CLS_8D1Page dialog

class CLS_8D1Page : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_8D1Page)

public:
	CLS_8D1Page(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_8D1Page();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_8D1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
private:
	void UI_UpdateDialog();
	BOOL UI_UpdateCruise();
	void UI_EnableCruise(int _iNum);

private:
	CComboBox m_cboCruiseNo;
	CComboBox m_cboCruiseNum;
	CComboBox m_cboPreset[4];
	CComboBox m_cboStayTime[4];
	CComboBox m_cboSpeed[4];
	CButton m_btnCruise;
	CButton m_chkCruiseEnable;
	int m_iLogonID;
	int m_iChannelNo;

public:
	afx_msg void OnBnClickedButton8d1Cruise();
	afx_msg void OnCbnSelchangeCombo8d1Cruiseno();
	afx_msg void OnCbnSelchangeCombo8d1Cruisenum();
	afx_msg void OnBnClickedButtonCruiseStart();
	afx_msg void OnBnClickedButtonCruiseStop();
	afx_msg void OnBnClickedButtonTrackStart();
	afx_msg void OnBnClickedButtontTrackStop();
	afx_msg void OnBnClickedCheck8d1Cruiseenable();
};

#endif
