#ifndef _DNVR_VIDEO_COMBINE_PAGE_H
#define _DNVR_VIDEO_COMBINE_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"

// CLS_DNVRVideoCombinePage dialog

class CLS_DNVRVideoCombinePage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DNVRVideoCombinePage)

public:
	CLS_DNVRVideoCombinePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_DNVRVideoCombinePage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DNVR_VIDEOCOMBINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
private:
	void UI_UpdateDialog();
	BOOL UI_UpdateVideoCombineEnable();
	BOOL UI_UpdateVideoCombine();

private:
	CButton m_btnChannelEnable;
	CButton m_chkChannelEnable[32];
	CEdit m_edtPictureNum;
	CEdit m_edtCombineRect;
	CEdit m_edtCombineChannel;
	CButton m_btnVideoCombine;
	CButton m_btnEnableAudioMix;
	CEdit m_edtMixChannel;
	CButton m_btnAudioMix;
	int m_iLogonID;
	int m_iChannelNo;

public:
	afx_msg void OnBnClickedButtonChannelenable();
	afx_msg void OnBnClickedButtonVideocombine();
	afx_msg void OnBnClickedButtonAudiomix();
};
#endif