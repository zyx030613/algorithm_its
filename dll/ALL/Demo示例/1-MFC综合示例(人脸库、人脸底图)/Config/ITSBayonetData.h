#ifndef _ITS_BAYONET_DATA_H_
#define _ITS_BAYONET_DATA_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"
#include <vector>
using namespace std;
// CLS_ITSBayonetData dialog

class CLS_ITSBayonetData : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_ITSBayonetData)

public:
	CLS_ITSBayonetData(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_ITSBayonetData();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_ITS_STAR_NVR_BAYONET_DATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID, int _iChannelNo, int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _iLogonID, int _iWparam, void* _iLParam, void* _iUser);
	void UI_UpdateStaticDialogText();
	void UI_UpdateQueryDialogText();
	void UI_UpdateModifyDialogText();
	void GetCrossInfo();
	void GetLaneInfo();
	void GetQueryCondition(ITSQueryData &_tCaptureQueryCondition);
	void ShowQueryCountToUser(int _iLanguage = 0);
	void ShowMsgToUser(int _iMsgType, int _iResult);
	void ProcessQueryRecordResult();
	void SDKQueryData();
	afx_msg void OnBnClickedButtonItsQueryBayonetData();
	afx_msg void OnBnClickedBtnDataqueryFirstpage();
	afx_msg void OnBnClickedBtnDataqueryPrepage();
	afx_msg void OnBnClickedBtnDataqueryNextpage();
	afx_msg void OnBnClickedBtnDataqueryEndpage();
	afx_msg void OnBnClickedButtonItsModifyBayonetData();
	afx_msg void OnBnClickedButtonItsQueryTotalCount();
	afx_msg void OnCbnSelchangeCboDataqueryPlate();
private:
	int m_iLogonID;
	int m_iChannelNo;
	CDateTimeCtrl m_dtpBeginDate;
	CDateTimeCtrl m_dtpBeginTime;
	CDateTimeCtrl m_dtpEndDate;
	CDateTimeCtrl m_dtpEndTime;
	CComboBox m_cboUploadState;
	CComboBox m_cboCross;
	CComboBox m_cboLane;
	CComboBox m_cboQueryCarType;
	CComboBox m_cboQueryCarBrand;
	CComboBox m_cboDirection;
	CComboBox m_cboQueryCarColor;
	CComboBox m_cboQueryPlate;
	CComboBox m_cboQueryIllegalType;
	CEdit m_edtQueryPlate;
	CEdit m_edtModifyPlate;
	CComboBox m_cboModifyCarType;
	CComboBox m_cboModifyCarBrand;
	CComboBox m_cboModifyCarColor;
	CComboBox m_cboModifyIllegalType;
	CEdit m_edtModifyPicName;
	CListCtrl m_lstQueryRecord;

	int m_iTotalRecordCount;   // 总查询条数
	int m_iTotalPageCount;    // 界面分成m_iTotalPageCount页显示
	int m_iCurrentPageNo;     // 界面显示的当前页码
	int m_iBeginIndex;
	int m_iEndIndex;

	ITSCrossInfo m_tItsCross[MAX_ITS_CROSS_COUNT];
	ITSLaneInfo m_tItsLane[MAX_ITS_CROSS_COUNT * MAX_ITS_LANE_COUNT];
	ITSQueryDataRecord m_tRecordArray[MAX_ITS_QUERYDATA_PAGE_SIZE];
	int m_iSelectIndex;

public:
	afx_msg void OnNMClickLstDataqueryRecord(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonItsDeleteBayonetData();
	void InitIllegalTypeCbo();
	void InitCarTypeCbo();
	void InitCarBrandCbo();
	void InitCarColorCbo();
	void InitCarDirectionCbo();
};

#endif
