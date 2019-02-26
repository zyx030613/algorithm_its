#ifndef _DNVR_TEXT_PLAN_H
#define _DNVR_TEXT_PLAN_H

#include "../BasePage.h"
#include "afxwin.h"
/*#include "afxdtctl.h"*/

// CLS_DNVRAlmSchPage dialog

class CLS_DNVRTextPlan : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DNVRTextPlan)

public:
	CLS_DNVRTextPlan(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DNVRTextPlan();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DNVR_TEXTPLAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
private:
	void UI_UpdateDialog();

private:


public:

	afx_msg void OnCbnSelchangeCboTextplaniid();
	afx_msg void OnBnClickedBtnTextplanSet();
private:
	CEdit m_edtTextPlancAlias;
	CComboBox m_cboTextPlaniId;
	CEdit m_edtTextPlancText;
	int m_iLogonID;
	int m_iChannel;
	int m_iChannelNo;
};

#endif
