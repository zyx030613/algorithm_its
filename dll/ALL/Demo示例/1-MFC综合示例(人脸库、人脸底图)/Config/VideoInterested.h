#ifndef _VIDEO_INTERESTED_PAGE_H_
#define _VIDEO_INTERESTED_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "Events/VideoViewForDraw.h"

// CCLS_VideoInterested dialog

class CLS_VideoInterested : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_VideoInterested)

public:
	CLS_VideoInterested(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VideoInterested();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_VIDEO_INTERESTED };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnMainNotify( int _iLogonID,int _wParam, void* _lParam, void*_iUserData );
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	afx_msg void OnBnClickedButtonDraw();
	afx_msg void OnBnClickedButtonVideoInterestedSet();
	void UpdatePageUI();
	void UI_UpdateDialog();
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;
	CLS_VideoViewForDraw* m_pDlgVideoView;
	CComboBox m_cboAreaIndex;
	CComboBox m_cboAreaEnable;
	CComboBox m_cboQpType;
	CEdit m_edtQpValue;
	CEdit m_edtDarwPoint;
	int		m_iLeft;	//×ó±ß¾à-×óÉÏ½ÇX×ø±ê
	int		m_iTop;	//ÉÏ±ß¾à-×óÉÏ½ÇY×ø±ê
	int		m_iRight;	//ÓÒ±ß¾à-ÓÒÏÂ½ÇX×ø±ê
	int		m_iBottom;	//ÏÂ±ß¾à-ÓÒÏÂ½ÇY×ø±ê

	TInterestedArea m_tCurrentInterestRect;
public:
	afx_msg void OnCbnSelchangeComboAreaIndex();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

#endif