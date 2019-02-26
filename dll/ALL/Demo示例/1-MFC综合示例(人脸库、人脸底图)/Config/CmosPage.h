#ifndef _CMOS_PAGE_H_
#define _CMOS_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"

// CLS_CmosPage dialog

class CLS_CmosPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_CmosPage)

public:
	CLS_CmosPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_CmosPage();
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

	// Dialog Data
	enum { IDD = IDD_DLG_CFG_CMOS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	int m_iLogonID;
	int m_iChannelNo;
private:
	void UI_UpdateSmtpInfo();
	void UI_UpdateSceneViewInfo();
	void UI_UpdateDialog();
	void UI_UpdateEmailAlarmEnable();
private:
	CEdit m_edtSmtpSvr;
	CEdit m_edtPort;
	CEdit m_edtAccount;
	CEdit m_edtPassword;
	CEdit m_edtMailSubject;
	CComboBox m_cmbAuthtype;
	CEdit m_edtMailBox1;
	CEdit m_edtMailBox2;
	CEdit m_edtMailBox3;
	CEdit m_edtMailBox4;
public:
	afx_msg void OnBnClickedButtonCmosSmtpset();
private:
	CButton m_chkMailNotify;
public:
	afx_msg void OnBnClickedCheckCmosMailnotify();
private:
	CComboBox m_cmbScene;
	CComboBox m_cmbFlip;
	CComboBox m_cmbMirror;
public:
	afx_msg void OnCbnSelchangeComboCmosScene();
	afx_msg void OnCbnSelchangeComboCmosFlip();
	afx_msg void OnCbnSelchangeComboCmosMirror();
	afx_msg void OnBnClickedButtonCmosFucset();
private:
	CEdit m_edtFactoryID;
	CEdit m_edtFuctionlist;
public:
	CComboBox m_cboScrityType;
	afx_msg void OnBnClickedBtnEmailTest();
};

#endif