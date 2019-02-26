#ifndef _PEDEVSIMUEDIT_H_
#define _PEDEVSIMUEDIT_H_
#pragma once
#include "afxwin.h"
#include "DonghuanSet.h"

#define MAX_SIMU_NUM 16

// CLS_PEDevSimuEdit dialog

class CLS_PEDevSimuEdit : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_PEDevSimuEdit)

public:
	CLS_PEDevSimuEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_PEDevSimuEdit();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONFIG_PE_SIMU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);
	void UI_UpdateDialogText();
	void	InitParentInfo(void* _pInfo);
	void	InitParamInfo(int _iSimuNo, int _iLogonID);
	void	InitDlgItemInfo();
	void ChangeUnitofText(int _iUnitType=-1, CString _strUnit="");//根据单位改变界面字符串
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;

	CComboBox m_cboSimuNo;
	CComboBox m_cboSimuSchedule;
	CComboBox m_cboUnit;
	CEdit m_edtName;
	CEdit m_edtDisAlarmDelayTime;
	CEdit m_edtCollectIntervel;
	CEdit m_edtRangeUpLevel;
	CEdit m_edtRangeUpValue;
	CEdit m_edtRangeDownValue;
	CEdit m_edtRangeDownLevel;
	CEdit m_edtAlarmUpLevel;
	CEdit m_edtAlarmDownLevel;
	CEdit m_edtDisAlarmUpLevel;
	CEdit m_edtDisAlarmDownLevel;

	CLS_DonghuanSet* m_clsPowerEnPage;
	int		 m_iSimuNo;
	int		 m_iDlgStyle;
public:
	afx_msg void OnBnClickedButtonSave();
protected:
	virtual void OnCancel();
public:
	afx_msg void OnCbnSelchangeComboSchdule();
};
#endif