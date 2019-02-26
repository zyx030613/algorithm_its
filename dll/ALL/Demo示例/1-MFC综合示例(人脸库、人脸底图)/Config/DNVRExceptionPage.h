#ifndef _DNVR_EXCEPTION_PAGE_H
#define _DNVR_EXCEPTION_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"

// CLS_DNVRExceptionPage dialog

class CLS_DNVRExceptionPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DNVRExceptionPage)

public:
	CLS_DNVRExceptionPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DNVRExceptionPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DNVR_EXCEPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);
	
private:
	void UI_UpdateDialog();
	BOOL UI_UpdateExceptionHandle();
	void UI_UpdateExceptionMsg();

private:
	CButton m_chkException[EXCEPTION_TYPE_MAX];
	CButton m_chkEnable;
	CButton m_chkDialog;
	CButton m_chkBell;
	CButton m_chkNetClient;
	CComboBox m_cboExceptionHandle;
	CButton m_btnExceptionHandle;
	CButton m_chkAllChannel;
	CComboBox m_cboAlarmType;
	CButton m_btnAlarmClear;
	int m_iLogonID;
	int m_iChannelNo;

public:
	afx_msg void OnBnClickedButtonExceptionhandle();
	afx_msg void OnBnClickedButtonAlarmclear();
	afx_msg void OnCbnSelchangeComboExceptionhandle();
	CButton m_chkShowDialog;
};
#endif
