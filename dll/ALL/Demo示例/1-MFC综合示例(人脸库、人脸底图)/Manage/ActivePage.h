#ifndef _ACTIVE_WINDOW_H
#define _ACTIVE_WINDOW_H

#include "../BasePage.h"
#include "afxwin.h"
#include "../Common/Ini.h"
#include "../Common/CommonFun.h"
#include "afxcmn.h"
#include "NSLOOK_INTERFACE.h"

// CLS_ActivePage dialog

class CLS_ActivePage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ActivePage)

public:
	CLS_ActivePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ActivePage();

// Dialog Data
	enum { IDD = IDD_DLG_MNG_ACTIVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnLanguageChanged(int _iLanguage);
	void UI_UpdateDialogText();
	void ReadConfig();
	void WriteConfig();
	afx_msg void OnBnClickedCheckRegServer();
	afx_msg void OnBnClickedButtonListenPortSet();
	afx_msg void OnBnClickedButtonDirectorySet();
	afx_msg void OnBnClickedButtonRefreshRegisterList();
	afx_msg void OnNMDblclkListActiveRegisterList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	void UpdateDevLstByRegisterServer();
	afx_msg LRESULT OnNvsLstMsg(WPARAM wParam, LPARAM lParam);
	static int __stdcall NvsLstNotify(int _iCount, st_NvsSingle* _ptNvs);
	void AddOneNvsItem(st_NvsSingle* _ptNvs);
	void UpdateDevLstByLocalServer();
private:
	CButton m_chkRegServer;
	CEdit m_edtActivePort;
	CEdit m_edtLocalIp;
	CEdit m_edtLocalPort;
	CEdit m_edtDsmIp;
	CEdit m_edtDsmPort;
	CEdit m_edtRegAccountName;
	CEdit m_edtRegAccountPwd;
	CEdit m_edtUsrMsg;
	CIniFile  m_iniFile;
	CListCtrl m_lstNvsLst;
	int m_iRegID;
	static HWND s_hWnd;
};

#endif
