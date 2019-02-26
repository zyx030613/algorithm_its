#pragma once
#include "../BasePage.h"
#include "afxcmn.h"
#include "afxwin.h"

// CLS_PowerEnvParamPage 对话框

typedef struct __tagSwitchData
{	
	int iTime;
	int iState; 
}SwitchData;


typedef struct __tagAnalogData
{	
	int iTime;
	int iDistanceUpperLimit; 
	int iDistanceLowerLimit;
	int iData;
	char cUnit[LEN_16];
}AnalogData;

typedef struct __tagComData
{	
	int iTime;
	int iType; 
	int iTemperature;
	int iTemAlarmStatus;
	char cTemUnit[LEN_16];
	int iHumidity;
	int iHumAlarmStatus;
	char cHumUnit[LEN_16];
}ComData;



class CLS_PowerEnvParamPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_PowerEnvParamPage)

public:
	CLS_PowerEnvParamPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_PowerEnvParamPage();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_DH_DATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_iLogonID;
	CListCtrl m_lstctrlSchedule;
	CListCtrl m_lstctrlKey;
	CButton m_chkAllSchedule;
	CButton m_chkAllKey;
	virtual BOOL OnInitDialog();
	void OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo);
	BOOL UpdateDialog();
	BOOL UpdateInportInfo(int _iInportNum);
	BOOL UpdateOutportInfo(int _iOutportNum);
	BOOL UpdateScheduleStateItem(int _iOutportNo,int _iType,int _iState);
	int FindScheduleItem( int _iOutportNo );
	BOOL UpdateOutportItem(int _iIndex,int _iState);
	void OnAlarmNotify(int _iLogonID, int _iChannelNo, int _iAlarmState,int _iAlarmType,int _iUserData);
	BOOL UpdateAlarmStateItem( int _iOutportNo,int _iInterfaceType,int _iIIDAlarmType, int _iState);
	void OnMainNotify( int _iLogonID,int _wParam, void* _iLParam, void* _iUser);
	void OnMainNotify( WPARAM wParam, LPARAM lParam );
	 
	BOOL UpdateLiveDataItem( int _iOutportNo, char* _pcData);
	afx_msg void OnNMClickLstDh(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedChkDhSelall();
	afx_msg void OnBnClickedChkSwitchSelall();
	afx_msg void OnBnClickedBtnManualBf();
	afx_msg void OnBnClickedBtnManualSf();
	afx_msg void OnBnClickedBtnManualRecover();
	BOOL ScheduleEnable(int _iValue );
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnClose();
	BOOL OutportEnable(int _iValue );
	BOOL GetAlarmStateID( int _iAlarmType);


	int FindInportItem(int _iInportNo);
	int FindOutportItem(int _iInportNo);

	BOOL UpdateAlarmInfo(AlarmInfoData* _pData);
	BOOL UpdateLiveDataInfo(int _iInportNo,int _iInterfaceType,char* _pcInfo,int _iLen);	
	BOOL UpdateLiveDataItem(int _iIndex,int _iType,char* _pcInfo,int _iLen);	

	BOOL StringToStruct(CString _strSrc,SwitchData* _pDest);
	BOOL StringToStruct(CString _strSrc,AnalogData* _pDest);
	BOOL StringToStruct(CString _strSrc,ComData* _pDest);
	virtual void OnLanguageChanged(int _iLanguage);
};
