#ifndef _VIDEO_ENCODE_SLICE_PAGE_H_
#define _VIDEO_ENCODE_SLICE_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
// CLS_VideoEncodeSlicePage dialog

class CLS_VideoEncodeSlicePage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_VideoEncodeSlicePage)

public:
	CLS_VideoEncodeSlicePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VideoEncodeSlicePage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_VIDEO_ENCODE_SLICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonSetSlice();

private:
	BOOL IsValidKey( char* _pcPwd );
	BOOL UI_UpdateVideoEncodeSlice();
	void UI_UpdateDialog();

private:
	CComboBox m_cboSliceType;
	CEdit m_edtSliceSize;
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNo;
	
};

#endif
