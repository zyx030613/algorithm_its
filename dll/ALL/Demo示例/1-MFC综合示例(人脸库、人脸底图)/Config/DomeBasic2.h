#ifndef _DOME_BASIC2_PAGE_H_
#define _DOME_BASIC2_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
// CLS_DomeBasic2 dialog

class CLS_DomeTitle : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DomeTitle)

public:
	CLS_DomeTitle(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DomeTitle();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DOME_BASIC2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	void UI_UpdateDialogText();
	void UI_UpdateDomeTitleInfo();
	afx_msg void OnCbnSelchangeCboTitleType();
	afx_msg void OnCbnSelchangeComboTitleNo();
	afx_msg void OnCbnSelchangeComboTitleTime();
	afx_msg void OnBnClickedCheckTitleDric();
	afx_msg void OnBnClickedCheckTitleBackground();
	afx_msg void OnBnClickedButtonDomeTitleSet();
	int GetTitleCMDType( int _iTitleType );
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;
	CComboBox m_cboTitleType;
	CComboBox m_cboTitleNo;
	CEdit m_edtTitleNmae;
	CComboBox m_cboTitleTime;
	CButton m_chkTitleDirc;
	CButton m_chkTitleBackGround;
};

#endif
