#ifndef _VIDEO_DOMEMENU_PAGE_H_
#define _VIDEO_DOMEMENU_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"


// CLS_DomeMenu dialog

class CLS_DomeMenu : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DomeMenu)

public:
	CLS_DomeMenu(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DomeMenu();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DOME_MENU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);
	void UpdatePageUI();
	void UI_UpdateDialog();
	afx_msg void OnBnClickedButtonDomeParaSet();
	afx_msg void OnCbnSelchangeComboDomeType();
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;
	CComboBox m_cboDomeType;
	CEdit m_edtDomePara[4];
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

#endif
