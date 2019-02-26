#ifndef _BURN_H323_PAGE_H
#define _BURN_H323_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxdtctl.h"


// CLS_BurnH323Page dialog

class CLS_BurnH323Page : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_BurnH323Page)

public:
	CLS_BurnH323Page(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_BurnH323Page();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_BURN_H323 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUser);
	afx_msg void OnBnClickedButtonH323LocalParaSet();
	afx_msg void OnBnClickedButtonH323GkParaSet();
	afx_msg void OnBnClickedButtonMutilReboot();
	void UI_UpdateDialogText();
	void UI_UpdateH323LocalPara();
	void UI_UpdateH323GKPara();
private:
	int m_iLogonID;
	CEdit m_edtH323ListenPort;
	CEdit m_edtH323TerminalNum;
	CEdit m_edtH323VideoChannel;
	CEdit m_edtH323GKAddress;
	CEdit m_edtH323GKPort;
	CEdit m_edtH323RegisterName;
	CEdit m_edtH323EncrytionPassword;
	CComboBox m_cboH323GKMode;
	CComboBox m_cboH323IdCodeMode;
	CComboBox m_cboH323RespondsByCall;
	CComboBox m_cboH323EncrytionType;
	CComboBox m_cboH323MutilRebootType;
};

#endif
