#ifndef _FUNC_UNIQUE_ALERT_ENABLE_H
#define _FUNC_UNIQUE_ALERT_ENABLE_H

#include "BasePage.h"

//特色警戒-警戒使能状态
class CLS_DlgUniqueAlertEnable : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DlgUniqueAlertEnable)

public:
	CLS_DlgUniqueAlertEnable(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_DlgUniqueAlertEnable();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_ALERT_ENABLE_STATUS };

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