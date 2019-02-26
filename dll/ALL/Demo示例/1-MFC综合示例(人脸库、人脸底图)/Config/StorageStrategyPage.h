#ifndef _STORAGE_STRATEGY_PAGE_H
#define _STORAGE_STRATEGY_PAGE_H

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"

// CLS_StorageStrategyPage dialog
#define MAX_DISK_NUM_EX  32
class CLS_StorageStrategyPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_StorageStrategyPage)

public:
	CLS_StorageStrategyPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_StorageStrategyPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_STORAGE_STRATEGY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser);
	void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);

	void ChannelCheck();
	void UpdateDiskQuota(int _iWparam);
	afx_msg void OnBnClickedChkChannel(UINT _uiID);
private:
	void UI_UpdateDialog();
	void UI_UpdateStrategyType();
	BOOL UI_UpdateDiskGroup();
	BOOL UI_UpdateDiskQuota();

private:
	CComboBox m_cboStorageStrategy;
	CComboBox m_cboGroupNo;
	CButton m_chkDiskNo[MAX_DISK_NUM_EX];
	CButton m_chkChannelNo[LEN_64]; //按照最大数创建，客户使用需要建议动态创建@cb150429
	CComboBox m_cboChannelNo;
	CEdit m_edtRecQuota;
	CEdit m_edtPicQuota;
	int m_iLogonID;
	int m_iChannelNo;
	CEdit m_edtRecUsed;
	CEdit m_edtPicUsed;
	DISK_GROUP m_strDiskGroup[MAX_DISK_GROUP_NUM];
	int m_iCurStrategy;			//0:盘组策略， 1:配额策略
	DISK_QUOTA_USED m_strDiskQuota[MAX_CHANNEL_NUM];
	int m_iModeType;
	int m_iChannelEnable[LEN_16];	//联动通道
	int m_iPageNo;
	int m_iMaxLinkNum;
public:
	afx_msg void OnCbnSelchangeComboStorageStrategy();
	afx_msg void OnBnClickedButtonStrategySet();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnCbnSelchangeComboDiskgroupNo();
	afx_msg void OnCbnSelchangeComboChannelNo();
	CComboBox m_cboChnIndex;
	afx_msg void OnCbnSelchangeCboChnRange();
};

#endif