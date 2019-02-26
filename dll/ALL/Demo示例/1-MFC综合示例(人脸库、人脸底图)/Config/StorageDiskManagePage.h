
#ifndef _Storage_Bad_Block_Page_H_
#define _Storage_Bad_Block_Page_H_

#include "BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"


class CLS_StorageDiskManagePage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_StorageDiskManagePage)

public:
	CLS_StorageDiskManagePage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_StorageDiskManagePage();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_STORAGE_DISKMANAGE };
//
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser);
	void InitDlgData();
	void UI_UpdateSurface();
	void DiskBadBlockTestInfo();
	void QueryDiskBLockSize();
	void DiskBadBlockTest();
	void GetCheckInfo(int _iDiskId);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonStorageQuery();
	afx_msg void OnBnClickedBtnStorageBegin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	int m_iLogonID;
	int m_iChannelNo;
	CComboBox m_cboDiskNo;
	CComboBox m_cboCheckWay;	

public:
	afx_msg void OnBnClickedBtnStorageSuspend();
	afx_msg void OnBnClickedBtnStorageCancel();
};

#endif
