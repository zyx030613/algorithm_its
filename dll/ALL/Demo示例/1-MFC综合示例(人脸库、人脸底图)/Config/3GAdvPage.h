#ifndef _3GADV_PAGE_H_
#define _3GADV_PAGE_H_

#include "../BasePage.h"
#include "afxdtctl.h"
#include "afxwin.h"

// CLS_3GAdvPage dialog

class CLS_3GAdvPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_3GAdvPage)

public:
	CLS_3GAdvPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_3GAdvPage();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

// Dialog Data
	enum { IDD = IDD_DLG_CFG_3G_ADV };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3GADVTimeSet();
	afx_msg void OnBnClickedButton3GADVNotifySet();
	afx_msg void OnBnClickedButton3GADVVpdnSet();
private:
	int m_iLogonID;
	CDateTimeCtrl m_dtp3GTaskScheduleStart;
	CDateTimeCtrl m_dtp3GTaskScheduleStop;
	CButton m_chk3GTaskScheduleEnable;
	CComboBox m_cbo3GNotifyType;
	CEdit m_edt3GNotifyMessage;
	CEdit m_edtDialNumber;
	CEdit m_edtAccounter;
	CEdit m_edtPassword;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheck3GADVTaskSchedule();
	void UI_UpdateDialog();
	void UI_Update3GADVInfo();
};

#endif
