#ifndef _CMOS_HD_H_
#define _CMOS_HD_H_

#include "../BasePage.h"
#include "afxwin.h"

// CLS_HDPage dialog

class CLS_HDPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_HDPage)

public:
	CLS_HDPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_HDPage();
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

// Dialog Data
	enum { IDD = IDD_DLG_CFG_HD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:	
	void UI_UpdateAperture();
	void UI_UpdateInfo();
	void UI_UpdateLanguage();
	void UI_UpdateTemplate();
private:
	int m_iLogonID;	
	int m_iChannelNo;
private:
	CEdit m_edtEAV;
	CButton m_chkAutoApertureEnable;
	CButton m_chkWidthDynamicEnable;
	CButton m_chkApheliotropicEnable;
	CComboBox m_cmbExposalTime;
	CComboBox m_cmbShutter;
public:
	afx_msg void OnBnClickedButtonHdAaeset();
	afx_msg void OnBnClickedButtonHdEavset();
	afx_msg void OnBnClickedButtonHdWdeset();
	afx_msg void OnBnClickedButtonHdApeset();
	afx_msg void OnBnClickedButtonHdEt();
	afx_msg void OnBnClickedButtonHdShutterset();
	
	afx_msg void OnBnClickedCheckHdMouseset1();
	afx_msg void OnBnClickedCheckHdMouseset2();
private:
	
public:
	afx_msg void OnBnClickedCheckHdExprectSet();
	afx_msg void OnBnClickedCheckHdAprectSet();
private:
	CButton m_chkExprectSet;
	CButton m_chkAprectSet;
public:
	afx_msg void OnBnClickedButtonHdSetexprect();
private:
	CEdit m_edtExprectLeft;
	CEdit m_edtExprectTop;
	CEdit m_edtExprectRight;
	CEdit m_edtExprectBottom;
public:
	afx_msg void OnBnClickedButtonHdSetaprect();
private:
	CComboBox m_cmbAutoPlus;
public:
	afx_msg void OnBnClickedButtonHdSetautoplus();
private:
	CComboBox m_cmbTemplateID;
	CEdit m_edtTemplateName;
public:
	afx_msg void OnCbnSelchangeComboHdTemplateid();
	afx_msg void OnBnClickedButtonHdSettemplatename();
	afx_msg void OnBnClickedButtonHdSettemplatemap();
private:
	CEdit m_edtAprectLeft;
	CEdit m_edtAprectTop;
	CEdit m_edtAprectRight;
	CEdit m_edtAprectBottom;
public:
	CComboBox m_cboApertureType;
	afx_msg void OnBnClickedBtnHdApretureSet();
};

#endif