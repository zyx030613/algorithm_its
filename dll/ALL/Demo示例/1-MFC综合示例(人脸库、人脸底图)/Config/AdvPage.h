#ifndef _ADV_PAGE_H_
#define _ADV_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"


// CLS_AdvPage dialog


class CLS_AdvPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_AdvPage)

public:
	CLS_AdvPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_AdvPage();
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara,int _iUser);
// Dialog Data
	enum { IDD = IDD_DLG_CFG_ADV };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNo;
	CEdit m_edtAdvCPU;
	CEdit m_edtAdvMEM;
	CEdit m_edtAdvFlash;
private:
	void UI_UpdateTRebootInfo();
	void UI_UpdateARBootInfo();
	void UI_UpdateSendStreamInfo();
	void UI_UpdateUserData();
	void UI_UpdateLanguage();
	void UI_UpdateSystemInfo();
	void UI_UpdateStreamInsertDataInfo();
public:
	afx_msg void OnBnClickedButtonAdvGetsysinfo();
	afx_msg void OnBnClickedButtonSetCpuenable();
private:
	CButton m_chkCPUcheck;
	CEdit m_edtInternaiTime;
	CEdit m_edtStartPos;
	CEdit m_edtLength;
	CEdit m_edtDataText;
	CEdit m_edtIntervalDays;
	CEdit m_edtIntervalHour;
	CButton m_chkTRebootEnable;
	CEdit m_edtClientPort;
	CEdit m_edtClientIP;
	CComboBox m_cmbStreamType;
public:
	afx_msg void OnBnClickedUserData();
	afx_msg void OnBnClickedButton();
	afx_msg void OnBnClickedButtonAdvStreamset();
private:
	CEdit m_edtUserDefData;
	CComboBox m_cboUserDefType;
public:
	afx_msg void OnBnClickedButtonInsetSet();
private:
	CButton m_chkMainStream;
	CButton m_chkSubStream;
	CButton m_chkMainSub;
public:
	afx_msg void OnBnClickedCheckMainStream();
	afx_msg void OnBnClickedCheckSubStream();
	afx_msg void OnBnClickedCheckMainSub();
	afx_msg void OnBnClickedButtonArbootset();
	CComboBox m_cboArbootWeek;
	afx_msg void OnCbnSelchangeComboArbootweek();
};

#endif

