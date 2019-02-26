#ifndef _COM_PAGE_H
#define _COM_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"

// CLS_ComPage dialog

class CLS_ComPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ComPage)

public:
	CLS_ComPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ComPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_COM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	afx_msg void OnBnClickedButtonComFormat();
	afx_msg void OnCbnSelchangeComboComNo();
	afx_msg void OnBnClickedButtonComSend();

private:
	void UI_UpdateDialog();
	void UI_UpdateComFormat();

private:
	int m_iLogonID;
	CComboBox m_cboComNo;
	CComboBox m_cboBaudRate;
	CComboBox m_cboParityBit;
	CComboBox m_cboDataBit;
	CComboBox m_cboStopBit;
	CComboBox m_cboWorkMode;
	CComboBox m_cboComType;
	CComboBox m_cboDeviceName;
public:
	afx_msg void OnBnClickedBtnDlsend();
	CComboBox m_cboDlMem;
	afx_msg void OnCbnSelchangeCmbMem();
};

#endif