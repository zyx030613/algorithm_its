#ifndef _FUNC_ALERT_ALARM_LINK_H
#define _FUNC_ALERT_ALARM_LINK_H

#include "BasePage.h"

//特色警戒-报警联动
class CLS_DlgUniqueAlertAlarmLink : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DlgUniqueAlertAlarmLink)

public:
	CLS_DlgUniqueAlertAlarmLink(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_DlgUniqueAlertAlarmLink();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_ALERT_ALARM_LINK };

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