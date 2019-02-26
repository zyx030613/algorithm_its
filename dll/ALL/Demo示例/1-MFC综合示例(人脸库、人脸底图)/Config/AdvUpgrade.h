#pragma once
#include "../BasePage.h"
#include "afxcmn.h"
#include <list>
#include "afxwin.h"
using namespace std;
// CLS_AdvUpgrade dialog
#define TIMER_CHECK_UPGRADE_PROGRESS 0
#define WM_UPGRADE_MESSAGE (WM_USER + 555)
enum UpgradeType
{
	UPGRADE_KERNEL = 0,
	UPGRADE_WEBPAGE
};
struct stUpgradeParam
{
	int m_iLogonID;
	int m_iUpgradeType;
	stUpgradeParam()
	{
		m_iLogonID = 0;
		m_iUpgradeType = UPGRADE_KERNEL;
	}
};
class CLS_AdvUpgrade : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_AdvUpgrade)

public:
	CLS_AdvUpgrade(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_AdvUpgrade();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ADVANCE_UPGRADE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	int m_iLogonID;
	list<stUpgradeParam*> m_lstUpgrade;
	void UI_UpDate_Text();
	void UpdateUpgradeProgress();
	void UI_UpdateBackupStatus(int _iLogonID, int _iStatus);
	BOOL IsInUpGradeList();
	int  GetUpGradeType(int _iLogonID);
	void DeleteUpgrade(int _iLogonID);
	void StopTalk();
	
public:
	void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	void OnMainNotify(int _iLogonID,int _wParam, void* _iLParam, void* _iUser);
	void OnLanguageChanged(int _iLanguage);
	void static  WebUpGrageNotify(int _iLogonID, int _iServerState, int _iUser);
	void static  KernelGrageNotify(int _iLogonID, int _iServerState, int _iUser);
public:
	CString m_szWebBoxFile;
	CString m_szKernelFile;
	CProgressCtrl m_ProgressCtrlUpgradeBin;
	CProgressCtrl m_ProgressCtrlUpgradeBox;
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedButtonAdvBackupKernel();
	afx_msg void OnBnClickedButtonAdvUpgradeBin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonAdvUpgradeSelectBin();
	afx_msg void OnBnClickedButtonAdvUpgradeSelectBox();
	afx_msg void OnBnClickedButtonAdvUpgradeClearBin();
	afx_msg void OnBnClickedButtonAdvUpgradeClearBox();
	afx_msg void OnBnClickedButtonAdvUpgradeBox();
	afx_msg LRESULT OnMessgeProcess(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonConfigBrowse();
	afx_msg void OnBnClickedButtonConfigInput();
	afx_msg void OnBnClickedButtonConfigOutput();
	CString GetSystemOutputPath();
private:
	CEdit m_edtConfigPath;
	CString m_strConfigPath;
};
