#pragma once
#include "../BasePage.h"
#include "afxwin.h"
#include "afxdtctl.h"

// CLS_AdvChannelParamPage dialog

//彩转黑类型，按SDK定义
#define COLOR_AUTO_IN			0			//自动内同步
#define COLOR2GRAY_GRAY			1			//黑白
#define COLOR2GRAY_COLOR		2			//彩色
#define COLOR2GRAY_OUT_SYN		3			//自动外同步
#define COLOR_AUTO_ALARM		4			//报警同步
#define COLOR2GRAY_SETTIME		5			//定时
#define COLOR2GRAY_AUTO			6           //auto
#define COLOR2GRAY_FILL_LIGHT	7           //补光模式

enum CHANNEL_TYPE
{
	VIDEO_CHANNEL = 0,
	ALARM_INPUT_CHANNEL,
	ALARM_OUTPUT_CHANNEL
};

class CLS_AdvChannelParamPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_AdvChannelParamPage)

public:
	CLS_AdvChannelParamPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_AdvChannelParamPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ADVANCE_CHANNEL_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void    OnMainNotify(int _iLogonID,int _wParam, void* _iLParam, void* _iUser);
	void    OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	void    OnLanguageChanged(int _iLanguage);
	void    OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);
	DECLARE_MESSAGE_MAP()

private:
	int m_iLogonID;
	int m_iChannelNo;
	
	void UI_UpdateParam();
	void UI_UpdateCustomChannel();
	void UI_UpdateChannelName();
	void UI_UpateCustomRecName();
	void UI_UpdateComBoxLaguage();
	void UI_UpdateText();
	BOOL CheckChannel();
	void GetBrightValue();

public:
	CComboBox m_ComboBoxPreRecord;
	CComboBox m_ComboBoxColorToGray;
	CComboBox m_ComboBoxChannelType;
	CComboBox m_ComboBoxChannelNo;
	CComboBox m_ComboBoxTypeNo;
	
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedButtonChannelPrerecordEnable();
	afx_msg void OnBnClickedButtonChannelColor();
	afx_msg void OnBnClickedButtonChannelPwm();
	afx_msg void OnBnClickedButtonChannelCustom();
	afx_msg void OnBnClickedButtonChannelCustomRecordType();
	afx_msg void OnCbnSelchangeComboChannelType();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnCbnSelchangeComboChannelTypeNo();
	afx_msg void OnCbnSelchangeComboChannelColorToGray();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	CEdit m_edtBrightValue;
	CDateTimeCtrl m_dtpGray2ColorTime;
	CDateTimeCtrl m_dtpColor2GrayTime;
	CEdit m_edtDayLight;
	CEdit m_edtNightLight;
	CEdit m_edtColor2GrayDelay;
	CEdit m_edtGray2ColorDelay;
public:
	afx_msg void OnEnChangeEditChannelDayrange();
	afx_msg void OnEnChangeEditChannelNightrange();
	afx_msg void OnEnChangeEditColordelay();
	afx_msg void OnEnChangeEditGraydelay();
};
