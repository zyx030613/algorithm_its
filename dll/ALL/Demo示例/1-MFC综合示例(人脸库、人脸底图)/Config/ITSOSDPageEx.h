#ifndef _ITS_OSD_PAGE_EX_H
#define _ITS_OSD_PAGE_EX_H


#include "../BasePage.h"
#include "afxwin.h"


class CLS_ITSOSDPageEx : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ITSOSDPageEx)

public:
	CLS_ITSOSDPageEx(CWnd* pParent = NULL);
	virtual ~CLS_ITSOSDPageEx();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ITS_OSD_EX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	void UI_UpdateDateTime();
	void UI_UpdateOsdInfo();

public:
	int m_iLogonID;
	int m_iChannel;

public:
	afx_msg void OnBnClickedBtnTimePreview();
	afx_msg void OnBnClickedBtnSetTimeType();
	afx_msg void OnFormatEditChange(UINT _uiID);
};

#endif
