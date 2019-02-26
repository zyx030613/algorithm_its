#ifndef _ITS_OSD_PAGE_H
#define _ITS_OSD_PAGE_H

#define OSD_TYPE_NUM	5
#define ITS_CHK_MAX1	31
#define ITS_CHK_MAX2	3

#include "../BasePage.h"
#include "afxwin.h"

// CLS_ITSOSDPage dialog

class CLS_ITSOSDPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ITSOSDPage)

public:
	CLS_ITSOSDPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ITSOSDPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ITS_OSD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);

private:
	void UI_UpdateDialog();
	void UI_UpdateCheck();
	BOOL UI_UpdateOSD();
	BOOL UI_UpdateLocationset();
	BOOL UI_UpdateType();
	BOOL UI_UpdateFont();
	BOOL UI_UpdateMargin();
	BOOL UI_UpdateRename();
	BOOL UI_UpdateCheckKeeptype();
	BOOL UI_UpdateFontSize();
public:
	
	int m_iLogonID;
	int m_iChannel;
	afx_msg void OnBnClickedButtonOsd();
	afx_msg void OnStnClickedStaticOverlaylocation();
	afx_msg void OnBnClickedStaticImageoverlay();
	afx_msg void OnBnClickedStaticItsOsd();
	afx_msg void OnEnChangeEditLeftmargin();
	afx_msg void OnBnClickedBtnLocationset();
	afx_msg void OnBnClickedBtnTypeset();
	afx_msg void OnBnClickedBtnFontset();
	afx_msg void OnBnClickedCheckTime3();
	afx_msg void OnBnClickedBtnRenameset();
	afx_msg void OnBnClickedCheckOroadname();
	afx_msg void OnBnClickedCheckOlanname();
	afx_msg void OnBnClickedBtnMarginset();
	afx_msg void OnBnClickedCheckKeeptype();
private:
	CComboBox m_cboLocation;
	CComboBox m_cboFontColor;
	CComboBox m_cboFontSize;
	CButton m_chkAfterRed;
	CButton m_chkIllegalCode;
	CButton m_chkVehicleType;
	CButton m_chkRedEndtm;
	CButton m_chkSeatBelts;
	CButton m_chkMainFace;
	CButton m_chkCopilotFace;
	CButton m_chkTTime;	
	CEdit m_editTime;
	CEdit m_editORoadname;
	CButton m_chkORoadName;
	CButton m_chkOLanName;
	CEdit m_editLeftMargin;
	CEdit m_editRightMargin;
	CComboBox m_cboPicOverlay;
	CButton m_chkColor;
	CButton m_chkCarColor;
	CButton m_chkRoadNo;
	CButton m_chkIllegalType;
	CButton m_chkRoadUpDown;
	CButton m_chkSecurityCode;
	CButton m_chkCarFlag;
	CButton m_chkTime;
	CButton m_chkRoadName;
	CButton m_chkLanName;
	CButton m_chkLanDir;
	CButton m_chkSpeed;
	CButton m_chkLimitSpeed;
	CButton m_chkOverspeed;
	CButton m_chkLicense;
	CButton m_chkDeviceNum;
	CButton m_chkRedLTtm;
	CButton m_chkCheckTime;
	CButton m_chkCheckNo;
	CButton m_chkAreaShow;
	CButton m_chkOSDDbgInfo;
	CButton m_chkAreaInfoShow;
	CEdit m_edtOSDX;
	CEdit m_edtOSDY;
	CButton m_chkPareset;
	CButton m_chkDevStat;
	CButton m_btnOSD;
	CButton m_chkOneOverLay;
	CButton m_chkEnable[ITS_CHK_MAX1];
	CButton m_chkEnable2[ITS_CHK_MAX2];
public:
	afx_msg void OnCbnSelchangeCombo4();
};

#endif
