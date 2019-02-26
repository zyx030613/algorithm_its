#ifndef _DLG_ALARM_HUM_TEM_PAGE_H
#define _DLG_ALARM_HUM_TEM_PAGE_H

#include "BasePage.h"
#include "afxwin.h"

class CLS_DlgAlarmHumTem : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DlgAlarmHumTem)

public:
	CLS_DlgAlarmHumTem(CWnd* pParent = NULL);   
	virtual ~CLS_DlgAlarmHumTem();

	enum { IDD = IDD_DLG_CFG_ALARM_HUM_TEM};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

	DECLARE_MESSAGE_MAP()

public:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNo;

public:

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);

	virtual void OnLanguageChanged(int _iLanguage);
	void InitDialogItemText();

	void UI_UpdateHumTemThreshold();
	void UI_UpdateHumThreshold();
	void UI_UpdateTemThreshold();

	afx_msg void OnBnClickedBtnHumTemThresholdSet();
};

#endif