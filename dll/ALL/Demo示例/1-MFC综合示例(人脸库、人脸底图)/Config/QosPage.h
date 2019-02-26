#ifndef _QOS_PAGE_H
#define _QOS_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

class CLS_QosPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_QosPage)

public:
	CLS_QosPage(CWnd* pParent = NULL);   
	virtual ~CLS_QosPage();

	enum { IDD = IDD_DLG_CFG_QOS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	void UI_UpdateQosInfo();
	void UI_UpdateDialog();

private:
	int m_iLogonID;
	int m_iChannelNo;
	CComboBox m_cboQosType;
	CEdit m_edtDSCPValue;

public:
	afx_msg void OnBnClickedBtnQosSet();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCbnSelchangeCboQosType();
};

#endif