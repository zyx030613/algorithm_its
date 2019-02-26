#ifndef _FUNC_UNIQUE_ALERT_CUSTOM_H
#define _FUNC_UNIQUE_ALERT_CUSTOM_H

#include "BasePage.h"

//特色警戒-自定义警戒
class CLS_DlgUniqueAlertCustom : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DlgUniqueAlertCustom)

public:
	CLS_DlgUniqueAlertCustom(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_DlgUniqueAlertCustom();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_ALERT_CUSTOM };

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
};


#endif