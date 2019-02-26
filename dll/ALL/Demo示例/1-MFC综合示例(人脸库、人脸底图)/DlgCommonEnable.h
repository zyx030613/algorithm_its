#ifndef _DLG_COMMONENABLE_PAGE_H
#define _DLG_COMMONENABLE_PAGE_H

#include "BasePage.h"
#include "afxwin.h"

class CLS_DlgCommonEnable : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DlgCommonEnable)

public:
	CLS_DlgCommonEnable(CWnd* pParent = NULL);   
	virtual ~CLS_DlgCommonEnable();

	enum { IDD = IDD_DLG_CFG_COMMONENABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

	DECLARE_MESSAGE_MAP()

public:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNo;

public:
	CComboBox m_CboCommonEnableType;
	afx_msg void OnCbnSelchangeCboCfgComenableId();
	afx_msg void OnBnClickedBtnCfgComenableSet();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);

	virtual void OnLanguageChanged(int _iLanguage);
	void InitDialogItemText();
	void GetCommonEnable();
	void SetCommonEnable();
	void UpDateCommonEnableList();


};

#endif