#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "../Common/CommonFun.h"
#include "..\\Include\\NVSSDK_INTERFACE.h"
using namespace NVSSDK_INTERFACE;

class CLS_DefenceTemplateAdd : public CDialog
{
	DECLARE_DYNAMIC(CLS_DefenceTemplateAdd)

public:
	CLS_DefenceTemplateAdd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_DefenceTemplateAdd();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_DONGHUAN_SCHEDULE_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	AlarmInSchedule m_tAlmInTmpSet;
	AlarmInSchedule m_tAlmInTmp;
	CButton m_chkTime[MAX_DH_TIMESEGMENT];
	CDateTimeCtrl m_dtStart[MAX_DH_TIMESEGMENT];
	CDateTimeCtrl m_dtStop[MAX_DH_TIMESEGMENT];
	CButton m_chkWeek[MAX_DAYS];
	CButton m_chkWeekSelAll;
	CComboBox m_cboWeekSelect;
	CString m_cstrTmpName;
	int m_iWeekNum;	//0-6,0星期天
	int m_iDlgType;
	int m_iLogonID;
	int m_iTempNo;
	
public:	
	virtual BOOL OnInitDialog();	
	inline void InitParam(int _iDlgType, int _iLogonID, int _iTempNo)
	{
		m_iDlgType = _iDlgType;
		m_iLogonID = _iLogonID;
		m_iTempNo = _iTempNo;
	}
	void InitDlgCtrl();
	void UpdateUI();
	afx_msg void OnCbnSelchangeCboWeekSelect();
	BOOL GetTimeSegInfo(int _iWeek, int _iTimeSeg);
	void SetTimeSegInfo(int _iWeek, int _iTimeSeg);
	void OnBnClickedChkTime(UINT uId);
	void SetTimeCheck(int _iIsChk, int _iNo);
	CTime GetTimeHHmm(int _iHour, int _iMin);
	afx_msg void OnBnClickedChkWeekAll();
	afx_msg void OnBnClickedBtnAddTemplateOk();	
	
};
