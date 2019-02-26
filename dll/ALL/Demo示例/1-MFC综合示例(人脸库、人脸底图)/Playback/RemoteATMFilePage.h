#pragma once
#include "RemoteFilePage.h"
#include "CLS_DownloadFile.h"


// CLS_RemoteATMFilePage dialog

class CLS_RemoteATMFilePage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_RemoteATMFilePage)

public:
	CLS_RemoteATMFilePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_RemoteATMFilePage();

// Dialog Data
	enum { IDD = IDD_DLG_PBK_REMOTE_ATM_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnLogoffDevice(int _iLogonID);
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnMainNotify(int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser );
	virtual void OnLanguageChanged(int );
	DECLARE_MESSAGE_MAP()

private:
	void Update_UI_Text();
	void Update_UI_Query_ATM_Result();
	void Update_UI_IPAndID();
	void ResetQuery();
	void UpDate_UI_ATM();

	void QueryFile();
	void QueryATMFile();
	void QueryDownloadPorgress();
	BOOL IsFileInList(int _iLogonID, CString _szFileName,unsigned long * _iConnID, CString _szOperationTime = _T(""),CString _szOperate = _T(""));
	void DeleteDownload(unsigned long  _ulConnID);
	void DeleteDownload(const int _iLogonID, int _iFlag);
	void ProcessDownloadFinished(unsigned long _ulID);
	void ProcessErrorOrder(const int _iLogonID);
	void ProcessDownloadFault(unsigned long _ulID);
	void ProcessDownloadInterrupt(unsigned long _ulID);
	CString GetFileNameByConID(unsigned long  _ulConnID);
	void OpenFile(unsigned long  _ulConnID);

public:

	int m_iLogonID;
	int m_iChannelNo;
	int m_iStreamNo;

	int m_iATMQuery;
	int m_iTotalCount;
	int m_iCurrentCount;
	int m_iCurrentPage;
	int m_iTotalPage;

	CString m_szFileName;
	CString m_szOperationTime;
	CString m_szOperate;
	CString m_szChannelNo;
	CString m_szEndTime;

	list<CLS_DownloadFile *> m_lstDownloadFile;
	CLS_FilePlayReviewPage m_PlayPage;

	CComboBox m_ComboFileType;
	CComboBox m_ComboRecType;
	CComboBox m_ComboChannelNo;
	CDateTimeCtrl m_DTQueryBeginTime;
	CDateTimeCtrl m_DTQueryEndTime;
	CEdit m_EditOSD;
	CListCtrl m_ListQueryFile;
	CComboBox m_ComboQueryPage;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPlayback();
	afx_msg void OnCbnSelchangeComboChannel();
	afx_msg void OnCbnSelchangeComboFileType();
	afx_msg void OnCbnSelchangeComboRecType();
	afx_msg void OnCbnSelchangeComboQueryPage();
	afx_msg void OnBnClickedButtonPrepage();
	afx_msg void OnBnClickedButtonNextPage();
	afx_msg void OnBnClickedButtonFirstPage();
	afx_msg void OnBnClickedButtonLastPage();
	afx_msg void OnDtnDatetimechangeDatetimepickerQueryBegintime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerQueryEndtime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListQueryFile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDownload();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	CComboBox m_CBQueryATMType;
	CComboBox m_CBBusinessType;
	CComboBox m_CBExceptions;
	afx_msg void OnCbnSelchangeComboQueryAtmType();
	afx_msg void OnBnClickedButtonAtmQuery();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonContinue();
	afx_msg void OnBnClickedButtonStop();
};
