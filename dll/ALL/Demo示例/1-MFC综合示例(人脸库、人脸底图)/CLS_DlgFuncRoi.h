#ifndef _FUNC_ROI_PAGE_H
#define _FUNC_ROI_PAGE_H

#include "BasePage.h"

class CLS_DlgFuncRoi : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DlgFuncRoi)

public:
	CLS_DlgFuncRoi(CWnd* pParent = NULL);   
	virtual ~CLS_DlgFuncRoi();

	enum { IDD = IDD_DLG_CFG_FUNC_ROI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	DECLARE_MESSAGE_MAP()


public:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNo;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	void GetFuncRoi();
};

#endif