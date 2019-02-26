#ifndef _NVS_DSM_PAGE_H
#define _NVS_DSM_PAGE_H

#include "../BasePage.h"
#include "../Include/NSLOOK_INTERFACE.h"
#include "afxwin.h"
#include "../Common/SortListCtrl.h"

// CLS_NvsDSMPage dialog

class CLS_NvsDSMPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_NvsDSMPage)

public:
	CLS_NvsDSMPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_NvsDSMPage();

// Dialog Data
	enum { IDD = IDD_DLG_MNG_DSM_NVS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iRegID,int _iRegUser,int _iRegPwd);
	virtual void OnLanguageChanged(int _iLanguage);
	static int __stdcall NvsNotify(int _iCount,st_NvsSingle *_regNVS);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnDsmNvsRefresh();
	afx_msg LRESULT OnNvsMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedBtnDsmNvsQuery();
	afx_msg void OnNMDblclkListDsmNvs(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListDsmNvs(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnGetCount();
	virtual void SetRegisterInfo(RegisterInfo* _ptInfo);

private:
	void Refresh();
	void AddNvs(st_NvsSingle* _pNvs);
	void UI_UpdateDialog();
	CString GetNvsType(int _iNvsType);
	int GetNvsType(CString _strNvsType);

public:
	static HWND s_hWnd;
	
private:
	CSortListCtrl m_lvNVS;
	int m_iRegID;
	char m_cRegUser[32];
	char m_cRegPwd[32];	
	char m_cRegIP[32];
	int m_iRegPort;
	
	CComboBox m_cboQueryType;
	CComboBox m_cboPage;
};

#endif
