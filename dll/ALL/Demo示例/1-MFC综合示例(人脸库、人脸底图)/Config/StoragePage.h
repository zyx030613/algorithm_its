#pragma once
#include "BasePage.h"
#include "afxwin.h"
#include "afxdtctl.h"


// CStoragePage dialog
#define MAX_RECORDMODE_CONTROL 4

class CStoragePage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CStoragePage)

public:
	CStoragePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStoragePage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_STORAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNo;
	CEdit m_edtByTime;
	CEdit m_edtByFileSize;
	CButton m_chkSubRecord;
	CButton m_chk_AlarmRecEnable;
	CButton m_chkByTime;
	CButton m_chkByFileSize;
	CButton m_chkAlarmPreRec;
	CButton m_chk_TaskRecEnable;
	CButton m_chkRedundantRec;
	CComboBox m_cboStorageTime;
	CComboBox m_cboSubStorageTime;
	CComboBox m_cbo_WeekDay;
	CComboBox m_cboRecordMode1;
	CComboBox m_cboRecordMode2;
	CComboBox m_cboRecordMode3;
	CComboBox m_cboRecordMode4;
	CComboBox m_cboRecRule;
	CComboBox m_cboStorageRuleType;
	CComboBox m_cboRecordStatus;
	CComboBox* m_pCboRecordMode[MAX_RECORDMODE_CONTROL];

	CDateTimeCtrl m_dtTMStart1;
	CDateTimeCtrl m_dtTMStart2;
	CDateTimeCtrl m_dtTMStart3;
	CDateTimeCtrl m_dtTMStart4;
	CDateTimeCtrl m_dtTMEnd1;
	CDateTimeCtrl m_dtTMEnd2;
	CDateTimeCtrl m_dtTMEnd3;
	CDateTimeCtrl m_dtTMEnd4;
	CDateTimeCtrl* m_pDtTMStart[MAX_RECORDMODE_CONTROL];
	CDateTimeCtrl* m_pDtTMEnd[MAX_RECORDMODE_CONTROL];

public:
	BOOL UI_UpdateSurface();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);

	int UpdateRecordStatusParam();
	void UI_UpdateStorageRule();
	void UI_UpdateRecordStatus(int _iCurSel);
	void UI_UpdateWeek(int _iCurSel);
	void UI_UpdateRecordMode(int* _iCurSel, int _iSize);
	void UI_UpdatePolicy(int _iCurSel);
	void UI_UpdateStorageType(int _iCurSel);
	void UI_UpdateAllStorageInfo();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckAlarmrecEnable();
	afx_msg void OnBnClickedCheckTaskrecEnable();
	afx_msg void OnCbnSelchangeComboWeekday();
	afx_msg void OnBnClickedButtonSetallchannel();
	afx_msg void OnBnClickedButtonSetrec();
	afx_msg void OnBnClickedButtonSetAllday();
	afx_msg void OnBnClickedCheckBytime();
	afx_msg void OnBnClickedCheckBysize();
	afx_msg void OnBnClickedButtonSetpolicy();
	afx_msg void OnBnClickedButtonPrerecSet();
	afx_msg void OnBnClickedButtonExtensionSet();
	afx_msg void OnBnClickedButtonRuleTypeSet();
	afx_msg void OnBnClickedButtonSnapshot();
	afx_msg void OnBnClickedButtonCtrlrec();
	afx_msg void OnBnClickedButtonManualRec();
	afx_msg void OnBnClickedButtonManualStatus();
	afx_msg void OnBnClickedButtonRebuilder();
	afx_msg void OnCbnSelchangeComboStorageRuleType();
	afx_msg void OnBnClickedCheckredundantrecEnable();
	afx_msg void OnBnClickedButtonStorageTime();
	afx_msg void OnBnClickedButtonSubStorageTime();
	afx_msg void OnBnClickedCheckSubRecord();
};
