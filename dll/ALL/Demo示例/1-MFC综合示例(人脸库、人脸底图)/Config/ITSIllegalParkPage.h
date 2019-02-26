#ifndef _ITS_ILLEGALPARK_PAGE_H
#define _ITS_ILLEGALPARK_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "ITSSetVCAPage.h"

// CLS_ITSIllegalParkPage dialog

class CLS_ITSIllegalParkPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ITSIllegalParkPage)

public:
	CLS_ITSIllegalParkPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ITSIllegalParkPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ITS_ITSPARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	void OnMainNotify(int _iLogonID,int _wParam, int _lParam,int _iUserData);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara,int _iUser);
private:
	void UI_UpdateDialog();
	BOOL UI_ModifyChar();
	void UI_UpdateParam();

private:
	CComboBox m_cboType;
	CComboBox m_cboCount;
	CEdit m_edtMC[8];
	CEdit m_edtOCW[8];
	CButton m_btnLicenseSet;
	CButton m_btnIllegalPark;
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNo;
	CLS_ITSSetVCAPage m_SetVCAPage;
public:
	afx_msg void OnBnClickedButtonIllegalpark();
	afx_msg void OnBnClickedButtonLicenseSet();
	afx_msg void OnBnClickedButtonCmd();
	CComboBox m_cboSendCmd;
	CComboBox m_cboComInfo;
	afx_msg void OnBnClickedButtonCommoninfoSet();
	afx_msg void OnCbnSelchangeComboCommoninfoType();
	afx_msg void OnBnClickedButtonCompoundSet();
	CComboBox m_cboRoadId;
	afx_msg void OnCbnSelchangeComboRoadid();
	afx_msg void OnCbnSelchangeComboType();
};

#endif