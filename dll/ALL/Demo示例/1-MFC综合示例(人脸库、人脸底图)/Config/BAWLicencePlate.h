#pragma once
#include "../BasePage.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"

// CLS_BAWLicencePlate dialog

class CLS_BAWLicencePlate : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_BAWLicencePlate)

public:
	CLS_BAWLicencePlate(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_BAWLicencePlate();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_DNVR_BANDW_LICENCEPLATE };

public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _iLogonID,int _iWParam, void* _iLParam, void* _iUser);
	virtual void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);
	void UI_UpdateDialogText();
	void UpdateListInfo();
	void UpdateListType();
	CString GetSystemOutputPath();
	static void LicencePlateInputProgress(int _iLogonID, int _iServerState, void* _iUserData);
	static void LicencePlateOutputProgress(int _iLogonID, int _iServerState, void* _iUserData);
	
public:
	afx_msg void OnBnClickedBtnDnvrBawlicenceplateQuery();
	afx_msg void OnBnClickedBtnNdvrBawlicencepalteSet();
	afx_msg void OnBnClickedBtnNdvrBawlicenceplateBrowser();
	afx_msg void OnBnClickedBtnNdvrBawlicenceplateInput();
	afx_msg void OnBnClickedBtnNdvrBawlicenceplateOutput();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_lstQueryList;
	int m_iLogonID;
	int m_iChannelNo;
	CButton m_chkBalckEnable;
	CString m_cstrFilePath;
	CEdit m_edtFilePath;
	CString m_cstrOutPutPath;
};
