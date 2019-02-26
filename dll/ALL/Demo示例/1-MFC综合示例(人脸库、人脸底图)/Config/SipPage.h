#ifndef _SIP_PAGE_H_
#define _SIP_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"

// CLS_SipPage dialog

class CLS_SipPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_SipPage)

public:
	CLS_SipPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_SipPage();
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

// Dialog Data
	enum { IDD = IDD_DLG_CFG_SIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	int m_iLogonID;
	int m_iChannelNum;
private:
	void GetChannelSipInfo();
	void UI_UpdateDialog();
private:
	CEdit m_edtSipChannelID1;
	CEdit m_edtSipLevel1;
	CEdit m_edtSipPtztime;
	CEdit m_edtSipChannelID2;
	CEdit m_edtSipLevel2;
public:
	afx_msg void OnBnClickedButtonSipVideochannelset();
	afx_msg void OnBnClickedButtonSipAlarmchannelset();
	afx_msg void OnCbnSelchangeComboAlarm();
	CComboBox m_cboAlarmNo;
	afx_msg void OnBnClickedBtnTest();
};

#endif
