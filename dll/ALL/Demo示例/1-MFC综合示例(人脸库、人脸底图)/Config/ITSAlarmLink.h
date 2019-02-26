#ifndef _ITS_ALARM_LINK_PAGE_H
#define _ITS_ALARM_LINK_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "ChanCheck.h"

#define MAX_ILLEGAL_DETECT_LINKPORT		2


class CLS_ITSAlarmLinkPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ITSAlarmLinkPage)

public:
	CLS_ITSAlarmLinkPage(CWnd* pParent = NULL);  
	virtual ~CLS_ITSAlarmLinkPage();

	enum { IDD = IDD_DLG_ITS_ALARM_LINK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	void UI_InitChanCheck();

public:
	int m_iLogonId;
	int m_iChannelNo;
	CComboBox m_cboSubAlarmType;
	CButton m_chkLinkSinglePic;
	CButton m_chkLinkRecord;
	CButton m_chkLinkPort;
	CLS_ChanCheck* m_pclsChanCheck;

public:
	afx_msg void OnCbnSelchangeCboItsIllegalDetectSubAlarmType();
	afx_msg void OnBnClickedBtnItsIllegalDetectLinkSet();
	void UI_InitCboSubAlarmType();
	int SetItsIllegalAlarmLink(int _iLinkType, int* _iCommonSet);
	void UI_UpdateAlarmLinkPortParam();
	void UI_UpdateAlarmLinkSinglePicParam();
	void UI_UpdateAlarmLinkRecordParam();
};

#endif
