#ifndef _OSD_BACK_GROUND_PAGE_H
#define _OSD_BACK_GROUND_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "../Common/SplitterButton.h"

class CLS_OSDBackgroundPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_OSDBackgroundPage)

public:
	CLS_OSDBackgroundPage(CWnd* pParent = NULL);  
	virtual ~CLS_OSDBackgroundPage();

	enum { IDD = IDD_DLG_CFG_OSD_BACK_GROUND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   

	DECLARE_MESSAGE_MAP()

public:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iColor;

public:
	CComboBox m_cboOsdCharType;
	CComboBox m_cboSort;  
	CComboBox m_cboEnhance;
	CLS_SplitterButton m_btnOSDColor;

public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUser);

private:
	void UI_UpdateDialog();
	void UI_UpdateOsdBackGroundParam();
	
public:
	afx_msg void OnBnClickedBtnSelectColor();
	afx_msg void OnBnClickedBtnSetOsdBackGround();
	afx_msg void OnCbnSelchangeCboChType();
	
};

#endif
