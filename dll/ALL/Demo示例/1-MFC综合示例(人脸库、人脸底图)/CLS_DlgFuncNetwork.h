#ifndef _FUNC_NETWORK_PAGE_H
#define _FUNC_NETWORK_PAGE_H

#include "BasePage.h"


class CLS_DlgFuncNetwork : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DlgFuncNetwork)

public:
	CLS_DlgFuncNetwork(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_DlgFuncNetwork();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_FUNC_NETWORK };

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
	void GetFuncNetwork();
	void InitDialogItemText();


};

#endif
