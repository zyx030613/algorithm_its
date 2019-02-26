#ifndef _FUNC_CDDNS_PAGE_H
#define _FUNC_CDDNS_PAGE_H

#include "BasePage.h"

class CLS_DlgFuncDdns : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DlgFuncDdns)

public:
	CLS_DlgFuncDdns(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLS_DlgFuncDdns();

// �Ի�������
	enum { IDD = IDD_DLG_CFG_FUNC_DDNS };

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
	void GetFuncDdns();
};


#endif