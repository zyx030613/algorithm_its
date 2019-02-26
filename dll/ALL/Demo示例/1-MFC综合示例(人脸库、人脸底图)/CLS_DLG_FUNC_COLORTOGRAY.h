#ifndef _FUNC_COLORTOGRAY_PAGE_H
#define _FUNC_COLORTOGRAY_PAGE_H


#include "BasePage.h"


class CLS_DLG_FUNC_COLORTOGRAY : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DLG_FUNC_COLORTOGRAY)

public:
	CLS_DLG_FUNC_COLORTOGRAY(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_DLG_FUNC_COLORTOGRAY();

	enum { IDD = IDD_DLG_CFG_FUNC_COLORTOGRAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	void GetFuncColorToGray();
	void GetFuncDayNightMode();
	void InitDialogItemText();

};

#endif