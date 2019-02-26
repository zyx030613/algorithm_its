#ifndef _FUNC_UNIQUE_ALERT_CUSTOM_H
#define _FUNC_UNIQUE_ALERT_CUSTOM_H

#include "BasePage.h"

//��ɫ����-�Զ��徯��
class CLS_DlgUniqueAlertCustom : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DlgUniqueAlertCustom)

public:
	CLS_DlgUniqueAlertCustom(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLS_DlgUniqueAlertCustom();

// �Ի�������
	enum { IDD = IDD_DLG_CFG_ALERT_CUSTOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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