#ifndef _RTMP_PAGE_H_
#define _RTMP_PAGE_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

class CLS_RtmpPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_RtmpPage)

public:
	CLS_RtmpPage(CWnd* pParent = NULL);   
	virtual ~CLS_RtmpPage();

	enum { IDD = IDD_DLG_CFG_RTMP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	void UI_UpdateRtmpInfo();
	void UI_UpdateDialog();

private:
	int m_iLogonID;
	int m_iChannelNo;
	CComboBox m_cboPushStreamType;

public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnBnClickedBtnRtmpSet();
	CButton m_chkLiveEnable;
	CEdit m_edtLiveAddr;
	CEdit m_edtAuthKey;
};

#endif