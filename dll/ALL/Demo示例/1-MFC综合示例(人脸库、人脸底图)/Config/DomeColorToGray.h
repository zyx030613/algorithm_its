#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include "../BasePage.h"
#include "afxwin.h"


// CLS_DomeColorToGray 对话框

class CLS_DomeColorToGray : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_DomeColorToGray)

public:
	CLS_DomeColorToGray(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_DomeColorToGray();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_DOME_COLOR_TO_GRAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnColor2graySet();
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;
	CComboBox m_cboType;
	CSliderCtrl m_sldDayLight;
	CSliderCtrl m_sldNightLight;
	CEdit m_edtGray2ColorDelay;
	CEdit m_edtColor2GrayDelay;
	CDateTimeCtrl m_dtpGray2ColorTime;
	CDateTimeCtrl m_dtpColor2GrayTime;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo );
	void OnLanguageChanged( int _iLanguage );
	void UI_UpdateDialogText();
};
