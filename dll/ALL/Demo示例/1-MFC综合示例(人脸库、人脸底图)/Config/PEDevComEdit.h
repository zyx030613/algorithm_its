#pragma once
#include "afxwin.h"
#include "DonghuanSet.h"


// CLS_PEDevComEdit dialog
#define COM_START_NUM	32

class CLS_PEDevComEdit : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_PEDevComEdit)

public:
	CLS_PEDevComEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_PEDevComEdit();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONFIG_PE_COM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSave();
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);
	void	UI_UpdateDialogText();
	void	InitComNoInfo();
	void	InitComInfo();
	void	InitParentInfo(void* _pInfo);
	void	InitParamInfo(int _iComNo, int _iLogonID);
	void	InitDlgItemInfo();
	void	InitDlgStyle(int _iDlgStyle);
private:
	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNO;
	int	m_iComNo;

	CComboBox m_cboDevNo;
	CComboBox m_cboDevType;
	CComboBox m_cboDevSchedule;
	CEdit m_edtDevName;
	CEdit m_edtDevAddr;
	CEdit m_edtDisAlarmIntervelTime;
	CEdit m_edtTemAlarmUpLevel;
	CEdit m_edtTemAlarmDownLevel;
	CEdit m_edtTemDisAlarmUpLevel;
	CEdit m_edtTemDisAlarmDownLevel;
	CEdit m_edtHulDisAlarmDownLevel;
	CEdit m_edtHulDisAlarmUpLevel;
	CEdit m_edtHulAlarmUpLevel;
	CEdit m_edtHulAlarmDownLevel;

	CLS_DonghuanSet* m_clsPowerEnPage;
	int		 m_iDlgStyle;
public:
	afx_msg void OnClose();
protected:
	virtual void OnCancel();
};
