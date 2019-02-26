#pragma once
#include "BasePage.h"
#include "afxwin.h"

#define HOUR_LIMIT		23  //时间（时）的上限值
#define MINUTE_LIMIT	59	//时间（分）的上限值


// CLS_ExtendedParam 对话框

class CLS_ExtendedParam : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ExtendedParam)

public:
	CLS_ExtendedParam(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_ExtendedParam();

// 对话框数据
	enum { IDD = IDD_DLG_ITS_EXTENDED_PARAM1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	BOOL OnInitDialog();
	void UI_UpdateDialog();
	void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	void OnLanguageChanged(int _iLanguage);
	void UI_UpdateBasicParamData();
	void UI_UpdateFillLightControlData();
	void UI_UpdateTrafficDayNightTimeData();
private:
	int m_iLogonID;
	int m_iChannel;
public:
	CStatic m_gpBasicParam;
	CStatic m_stcNightBitValue;
	CEdit m_edtNightBitValue;
	CButton m_btnNightBitValue;
	afx_msg void OnBnClickedGpFillLightControl();
	CStatic m_gpFillLightControl;
	CStatic m_stcDayThresholdValue;
	CStatic m_stcNightThresholdValue;
	CEdit m_edtDayThresholdValue;
	CEdit m_edtNightThresholdValue;
	CButton m_btnSetFillLightControl;
	CStatic m_gpTrafficDayNIghtTime;
	CStatic m_stcDayTime;
	CStatic m_stcNightTime;
	CEdit m_edtDayTimeHour;
	CEdit m_edtDayTimeMinute;
	CEdit m_edtNightTimeHour;
	CEdit m_edtNightTimeMiunte;
	CButton m_btnTrafficDayNightTime;
	afx_msg void OnBnClickedBtnSetTrafficDayNightTime();
	afx_msg void OnBnClickedBtnSetFillLightControl();
	afx_msg void OnBnClickedBtnSetBasicParam();
};
