#ifndef _VIDEO_APPENDOSD_PAGE_H_
#define _VIDEO_APPENDOSD_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "../Common/SplitterButton.h"


// CLS_AppendOSDPage dialog

class CLS_AppendOSDPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_AppendOSDPage)

public:
	CLS_AppendOSDPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_AppendOSDPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_APPEND_OSD };

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
	afx_msg void OnBnClickedButtonSelectColor();
	afx_msg void OnBnClickedButtonAppendOsdSet();
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;
	CComboBox m_cboOSDArea;
	CEdit m_edtDiaphaneity;
	CComboBox m_cboFontSize;
	CEdit m_edt_X_Value;
	CEdit m_edt_Y_Value;
	CEdit m_edtOSDContent;
	CLS_SplitterButton m_btnColor;
	int m_iColor;
	CButton m_chkBackColorShow;
	CButton m_chkBackColorAdd;
public:
	afx_msg void OnBnClickedCheckBackcolorShow();
	afx_msg void OnBnClickedCheckBackColorAdd();
	afx_msg void OnCbnSelchangeComboOsdArea();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

#endif
