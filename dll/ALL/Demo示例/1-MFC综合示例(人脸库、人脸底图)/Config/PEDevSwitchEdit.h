#pragma once
#include "afxwin.h"
#include "DonghuanSet.h"

#define MAX_SWITCH_NUM 16

// CLS_PEDevSwitchEdit dialog

class CLS_PEDevSwitchEdit : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_PEDevSwitchEdit)

public:
	CLS_PEDevSwitchEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_PEDevSwitchEdit();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONFIG_PE_SWITCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);
	void UI_UpdateDialogText();
	void InitParentInfo(void* _pInfo);
	void InitParamInfo(int _iSwitchNo, int _iLogonID);
	void InitDlgItemInfo();
	afx_msg void OnBnClickedButtonSave();
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;

	CComboBox m_cboModeSet;
	CComboBox m_cboIndex;
	CComboBox m_cboAlarmSchedule;
	CEdit m_edtName;
	CEdit m_edtDisAlarmDelayTime;
	int		m_iSwitchNo;
	CLS_DonghuanSet* m_clsPowerEnPage;
protected:
	virtual void OnCancel();
};
