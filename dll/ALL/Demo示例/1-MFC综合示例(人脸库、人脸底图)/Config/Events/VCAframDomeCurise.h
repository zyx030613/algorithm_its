#pragma once
#include "NetClientTypes.h"
#include "VCAEventBasePage.h"
#include "Common/NeuListCtrl.h"
#include "afxwin.h"
#include "shlwapi.h"
#include "afxcmn.h"
#include "WinDef.h"
#include <map>
#include <vector>
// VCAframDomeCurise dialog
#define COLOR_SET RGB (51,153,255)
#define HeaderFontHEX	13		//表头的字高
#define NeuRowHeigt	30		//表头的字宽

typedef struct _STRTTime//保存list control中的时间数据
{
	CString   strsBengin ;
	CString   strEnd ;
}STRTTime;

enum ECruiseIndex	//定时巡航的列
{
	E_CRUISE_FIRST = 0,	//第一列
	E_CRUISE_SECOND,
	E_CRUISE_THIRD,		
	E_CRUISE_FOUTH		
};

enum ETimeCruiseIndex	//按时间段巡航的列
{
	E_TIMECRUISE_FIRST = 0,	//第一列
	E_TIMECRUISE_SECOND,
	E_TIMECRUISE_THIRD,		
	E_TIMECRUISE_FOUTH,	
	E_TIMECRUISE_FIFTH
};

enum ETimingCruiseByTimeRangeIndex	//时间段内的定时巡航
{
	E_TIMINGCRUISEBYTIMERANGE_FIRST = 0,	//第一列
	E_TIMINGCRUISEBYTIMERANGE_SECOND,
	E_TIMINGCRUISEBYTIMERANGE_THIRD,		
	E_TIMINGCRUISEBYTIMERANGE_FOUTH,	
	E_TIMINGCRUISEBYTIMERANGE_FIFTH,
	E_TIMINGCRUISEBYTIMERANGE_SIXTH,
};

class VCAframDomeCurise : public CLS_VCAEventBasePage
{
	DECLARE_DYNAMIC(VCAframDomeCurise)

public:
	VCAframDomeCurise(CWnd* pParent = NULL);   // standard constructor
	virtual ~VCAframDomeCurise();
	virtual BOOL OnInitDialog();
public:
	CComboBox m_cboChnNo;
	CButton m_btn_Ontime;													//定时巡航
	CButton m_btn_TimeSlot;													//按时间段巡航
	CNeuListCtrl m_lst_CuriseInfo;											//定时巡航信息列表
	CNeuListCtrl m_lst_CuriseTimeInfo;
	CNeuListCtrl m_lstTimingCruiseByTimeRange;
	vector<AnyScene> m_vecAnyScene ;
	vector<SceneTimerCruise> m_vecSceneTimerCruise ;
	vector<SceneTimeRangeCruise> m_vecSceneTimeRangeCruise ;
	vector<SceneTimeRangeCruise> m_vecTimingCruiseByTimeRange;
	CButton m_chkEveryDay;
	void OnBnClickedChkWeek(UINT _uiID);
	int m_iCruiseType ;//判断选择的是定时巡航还是按时段巡航
	bool m_bTimeCurise ;//第一次点击按时间段巡航界面为false,以后为true,防止多次添加list control的列标题
	bool m_bTimingCuriseByTimeRange ;//第一次点击时间段内的定时巡航界面为false,以后为true,防止多次添加list control的列标题
	int m_iCount ;//用于保存当前被选中的是第几行
	bool m_bSetControl ;//定时巡航是否已经执行setitmecontrol
	bool m_bTimeSetControl ;//按时间段巡航是否已经执行setitmecontrol
	bool m_bTimingByTimeRangeSetControl ;//时间段内的定时巡航是否已经执行setitmecontrol
	map<int, STRTTime*> m_mapTimeInfo;
	map<int, STRTTime*> m_mapTimingCruiseTimeInfo;

	int m_iChannelNO;
	void MoveToNewPos(int iOldItemIndex, int iNewItemIndex) ;
	static HWND s_hVCA_CRUISE;
	enum { IDD = IDD_DLG_CFG_VCA_CRUSIE };
private:
	CDateTimeCtrl m_timeSchedStart[MAX_TIMESEGMENT];
	CDateTimeCtrl m_timeSchedStop[MAX_TIMESEGMENT];
	CButton m_chkWeekdays[MAX_DAYS];
	CButton m_chkSchedtime[MAX_TIMESEGMENT];
	void UpdateDlgItem();
	void ClearMapTimeInfo();//清除申请的MAP内存
	void ClearTimingCruiseMapTimeInfo();//清除申请的MAP内存
public:
	//virtual BOOL OnInitDialog();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	afx_msg LRESULT OnRecSelectMessage(WPARAM wParam,LPARAM lParam);

	afx_msg void OnNMRClickListCurise(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListTimeCurise(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
public:
	int m_iCuriseType;
	int m_iNum;
	int m_iSceneCuriseID;
	CString m_strSceneName;
	int m_iStopTime;
	int m_iBeginTime;
	int m_iEndTime;
private:
	int	ChooseTimeUpdateUI(int _iType);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedRadioCuriseTimer();
public:
	afx_msg void OnBnClickedRadioCuriseTimerange();
	afx_msg void OnBnClickedButtonCuriseadd();
	afx_msg void OnBnClickedButtonCurisedel();
	afx_msg void OnBnClickedButtonCuriseSave();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedRadioTimingCuriseByTimerange();
	afx_msg void OnNMRClickListTimingCuriseByTimerange(NMHDR *pNMHDR, LRESULT *pResult);
	void AddTimerCruiseInfo();
	void AddTimeRangeCruiseInfo();
	void AddTimingCruiseByTimeRangeInfo();
	void DeleteTimerCruiseInfo();
	void DeleteTimeRangeCruiseInfo();
	void DeleteTimingCruiseByTimeRangeInfo();
	void SaveTimerCruiseInfo();
	void SaveTimeRangeCruiseInfo();
	void SaveTimingCruiseByTimeRangeInfo();
	afx_msg void OnHdnBegintrackListCurise(NMHDR *pNMHDR, LRESULT *pResult);
	void OnLanguageChanged( int _iLanguage );
	void UpdateUIText();
};
