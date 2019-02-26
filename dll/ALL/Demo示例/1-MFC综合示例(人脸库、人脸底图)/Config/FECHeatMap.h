
#ifndef _FEC_HEAT_MAP_H_
#define _FEC_HEAT_MAP_H_

#include "../BasePage.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"

//列
enum n_List_Time_Heat_Map_Column{
	n_LTHMC_OccurTime,
	n_LTHMC_ChannelNo,
	n_LTHMC_LogContent,
};

//列宽
enum n_List_Time_Heat_Map_Column_Width{
	n_LTHMCW_OccurTime = 150,
	n_LTHMCW_ChannelNo = 100,
	n_LTHMCW_LogContent = 250
};
class CLS_FECHeatMap : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_FECHeatMap)

public:
	CLS_FECHeatMap(CWnd* pParent = NULL);   
	virtual ~CLS_FECHeatMap();
	
	enum { IDD = IDD_DLG_CFG_FEC_HEAT_MAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   

	DECLARE_MESSAGE_MAP()

public:
	BOOL OnInitDialog();
	void OnLanguageChanged(int _iLanguage);
	void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	void OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData);

public:
	int m_iLogonID;
	int m_iChannelNo;
	CListCtrl m_lstTimeHeatMap;
	CDateTimeCtrl m_dtimeTimeMapBeginTime;
	CDateTimeCtrl m_dtimeTimeMapEndTime;
	CDateTimeCtrl m_dtimeSpaceMapBeginTime;
	CDateTimeCtrl m_dtimeSpaceMapEndTime;
	CComboBox m_cboPrecisionType;
	CComboBox m_cboReportQueryType;		//报表查询类型
private:
	void UI_UpdateDialog();
	void UpdateReportQueryMap(ReportQueryResult* _ptInfo);
	void UpdateSpaceHeatMap();
	void InitDlgWidget();
	void InsertListItemText(int _iIndex, ReportQueryInfo _tQueryInfo);

public:
	void OnMainNotify(int _iLogonID,int _wParam, void* _iLParam, void* _iUser);
	afx_msg void OnBnClickedBtnQueryTimeMap();
	afx_msg void OnBnClickedBtnQuerySpaceMap();
	afx_msg void OnCbnSelchangeCboReportQuerryType();
};

#endif
