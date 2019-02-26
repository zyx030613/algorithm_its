#ifndef _FUNC_TRANCECODING_PAGE_H
#define _FUNC_TRANCECODING_PAGE_H

#include "BasePage.h"

class CLS_DLG_CFG_FUNC_VideoTranceCoding : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DLG_CFG_FUNC_VideoTranceCoding)

public:
	CLS_DLG_CFG_FUNC_VideoTranceCoding(CWnd* pParent = NULL);   
	virtual ~CLS_DLG_CFG_FUNC_VideoTranceCoding();

	enum { IDD = IDD_DLG_CFG_FUNC_VIDEOTCODING };

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
	void GetFuncVideoTranscoding();
	void InitDialogItemText();
};

#endif