// VCAframDomeCurise.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAframDomeCurise.h"
#include "Common/CommonFun.h"

#define	MAX_COUNT_NUM				16		//支持最大序号数为16
#define TIME_MIN					15		//
#define TIME_MAX					3000
#define DEFAULT_TIME				300

// VCAframDomeCurise dialog
HWND VCAframDomeCurise::s_hVCA_CRUISE = NULL;
IMPLEMENT_DYNAMIC(VCAframDomeCurise, CDialog)

VCAframDomeCurise::VCAframDomeCurise(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(VCAframDomeCurise::IDD, pParent)
{
	m_vecAnyScene.clear();
	m_vecSceneTimerCruise.clear();
	m_vecSceneTimeRangeCruise.clear();
	m_iCruiseType = SENCE_CRUISE_TYPE_TIMER ;
	m_bTimeSetControl = false ;
	m_bSetControl = false ;
	m_bTimingByTimeRangeSetControl = false;
	m_mapTimeInfo.clear();
	m_mapTimingCruiseTimeInfo.clear();
	m_bTimeCurise = false;
	m_bTimingCuriseByTimeRange = false;
}

VCAframDomeCurise::~VCAframDomeCurise()
{
	m_lst_CuriseInfo.ReleaseControls();
	m_lst_CuriseTimeInfo.ReleaseControls();
	m_lstTimingCruiseByTimeRange.ReleaseControls();
	ClearMapTimeInfo();
}

void VCAframDomeCurise::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CURISE, m_lst_CuriseInfo);
	DDX_Control(pDX, IDC_LIST_TIME_CURISE, m_lst_CuriseTimeInfo);
	DDX_Control(pDX, IDC_LIST_TIMING_CURISE_BY_TIMERANGE, m_lstTimingCruiseByTimeRange);
}

BEGIN_MESSAGE_MAP(VCAframDomeCurise, CDialog)
	ON_BN_CLICKED(IDC_RADIO_CURISE_TIMER, &VCAframDomeCurise::OnBnClickedRadioCuriseTimer)
	ON_BN_CLICKED(IDC_RADIO_CURISE_TIMERANGE, &VCAframDomeCurise::OnBnClickedRadioCuriseTimerange)
	ON_BN_CLICKED(IDC_BUTTON_CURISEADD, &VCAframDomeCurise::OnBnClickedButtonCuriseadd)
	ON_BN_CLICKED(IDC_BUTTON_CURISEDEL, &VCAframDomeCurise::OnBnClickedButtonCurisedel)
	ON_BN_CLICKED(IDC_BUTTON_CURISE_SAVE, &VCAframDomeCurise::OnBnClickedButtonCuriseSave)
	ON_BN_CLICKED(IDC_BUTTON1, &VCAframDomeCurise::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &VCAframDomeCurise::OnBnClickedButton5)
	ON_MESSAGE(MESSAGE_SELECT, &VCAframDomeCurise::OnRecSelectMessage)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CURISE, &VCAframDomeCurise::OnNMRClickListCurise)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_TIME_CURISE, &VCAframDomeCurise::OnNMRClickListTimeCurise)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO_TIMING_CURISE_BY_TIMERANGE, &VCAframDomeCurise::OnBnClickedRadioTimingCuriseByTimerange)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_TIMING_CURISE_BY_TIMERANGE, &VCAframDomeCurise::OnNMRClickListTimingCuriseByTimerange)
	ON_NOTIFY(HDN_BEGINTRACK, 0, &VCAframDomeCurise::OnHdnBegintrackListCurise)
END_MESSAGE_MAP()

//定时巡航
void VCAframDomeCurise::OnBnClickedRadioCuriseTimer()
{
 	m_iCruiseType = SENCE_CRUISE_TYPE_TIMER;
	m_lst_CuriseTimeInfo.ShowWindow(SW_HIDE);
	m_lstTimingCruiseByTimeRange.ShowWindow(SW_HIDE);
	m_lst_CuriseInfo.DeleteAllItems();
	m_lst_CuriseInfo.ResetContent();

	m_vecSceneTimerCruise.clear();
	SceneTimerCruise sTimeCruise = {0};
	int iReturnByteEX = 0;
	int iRet = -1;
	for(int j = 0; j < MAX_SCENE_NUM; j++)
	{
		sTimeCruise.iCruiseID = j;
		NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_SENCE_CRUISE_TIMER, m_iChannelNO, &sTimeCruise, sizeof(sTimeCruise), &iReturnByteEX);
		if (sTimeCruise.iEnable != 0)//使能
		{
			m_vecSceneTimerCruise.push_back(sTimeCruise);
		}
		else
		{
			continue;
		}
	}

	if (m_vecSceneTimerCruise.size() == 0)
	{
		m_lst_CuriseInfo.ShowControls(FALSE);
		m_lst_CuriseInfo.Invalidate();
	}
	m_lst_CuriseInfo.ShowWindow(SW_SHOW);
	m_lst_CuriseInfo.Invalidate(TRUE);

	if(m_vecSceneTimerCruise.size() != 0 && m_bSetControl == false)//有定时巡航模版，同时list ctrl里没有插入控件，先插入控件，在插入数据
	{

		m_lst_CuriseInfo.SetItemControl(EDITBOX,E_CRUISE_FOUTH);
		m_lst_CuriseInfo.SetItemControl(COMBOBOX, E_CRUISE_SECOND);//添加combox控件 ，此函数要在AddToControlsData（）函数之前调用
		m_lst_CuriseInfo.SetLimitTextLength(E_CRUISE_FOUTH,4);
		m_bSetControl = true ;
	}
	else if (m_vecSceneTimerCruise.size() == 0)//模版里没有内容，直接返回，不插入
	{
		m_iCruiseType = SENCE_CRUISE_TYPE_TIMER ;
		return ;
	}

	//获取定制巡航的信息
	AnyScene sScene = {0};
	int iReturnByte ;
	m_vecAnyScene.clear();
	for (int i = 0; i < MAX_SCENE_NUM; i++)//循环0-15个场景
	{
		sScene.iSceneID = i;
		NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_ANYSCENE, m_iChannelNO, &sScene, sizeof(AnyScene), &iReturnByte);
		m_vecAnyScene.push_back(sScene);
		//给使能的场景编号，插入到combox中去
		m_lst_CuriseInfo.AddToControlsData(E_CRUISE_SECOND, IntToStr(i+1).c_str());//1 代表第一列 
	}

	//将获取的到信息插入到list contrl中
	int iCount = (int)m_vecSceneTimerCruise.size();
	for(int i = 0; i < iCount; i++)
	{
		m_lst_CuriseInfo.InsertItem(i,_T(""));
		LVITEM item;
		memset(&item, 0, sizeof(LVITEM));
		item.mask = LVIF_TEXT;
		item.iItem = i;
		CString cstrTmp = "";

		//序号
		item.iSubItem = E_CRUISE_FIRST;
		cstrTmp = IntToStr(i+1).c_str() ;
		item.pszText = (LPSTR)(LPCTSTR)cstrTmp;
		m_lst_CuriseInfo.SetItem(&item);

		item.iSubItem = E_CRUISE_SECOND;
		CString strSceneid = IntToCString(m_vecSceneTimerCruise[i].iSceneID +1);
		int iSceneId = m_vecSceneTimerCruise[i].iSceneID;
		item.pszText = (LPSTR)(LPCTSTR)(strSceneid);
		m_lst_CuriseInfo.SetItem(&item);
		m_lst_CuriseInfo.SetItemData(i,m_vecSceneTimerCruise[i].iSceneID);

		//场景名称
		item.iSubItem = E_CRUISE_THIRD;
		if (iSceneId >= 0 && iSceneId < MAX_SCENE_NUM)
		{
			item.pszText = (LPSTR)(LPCTSTR)m_vecAnyScene[iSceneId].cSceneName;
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "[VCAframDomeCurise::OnBnClickedRadioCuriseTimer]invalid iScenceId = %d", iSceneId);
		}
		m_lst_CuriseInfo.SetItem(&item);

		//保留时间
		item.iSubItem = E_CRUISE_FOUTH;
		if(m_vecSceneTimerCruise[i].iTime > TIME_MAX || m_vecSceneTimerCruise[i].iTime < TIME_MIN)
		{
			m_vecSceneTimerCruise[i].iTime = DEFAULT_TIME ;
		}
		CString strTime = IntToCString(m_vecSceneTimerCruise[i].iTime);
		item.pszText = (LPSTR)(LPCTSTR)strTime ;
		m_lst_CuriseInfo.SetItem(&item);

	}
	m_iCruiseType = SENCE_CRUISE_TYPE_TIMER ;

	m_lst_CuriseInfo.SetItemState(m_iCount, 0, LVIS_SELECTED|LVIS_FOCUSED);
	m_lst_CuriseInfo.SetItemColor(m_iCount, COLOR_CANCEL);

	int iTotal = m_lst_CuriseInfo.GetItemCount();
	if (iTotal > 0)
	{
		m_lst_CuriseInfo.MoveControlToFocusItem(0);
	} 
}

//按时间段巡航
void VCAframDomeCurise::OnBnClickedRadioCuriseTimerange()
{
 	m_iCruiseType = SENCE_CRUISE_TYPE_TIMERANGE;
	m_lst_CuriseInfo.ShowWindow(SW_HIDE);
	m_lstTimingCruiseByTimeRange.ShowWindow(SW_HIDE);
	m_lst_CuriseTimeInfo.DeleteAllItems();
	m_lst_CuriseTimeInfo.ResetContent();

	m_vecSceneTimeRangeCruise.clear();
	SceneTimeRangeCruise sTimeRangeCruise = {0};
	int iReturnByteEX = 0;
	int iRet = -1;
	for(int j = 0; j < MAX_SCENE_NUM ;j++)
	{
		sTimeRangeCruise.iCruiseID = j;
		NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_SENCE_CRUISE_TIMERANGE, m_iChannelNO, &sTimeRangeCruise, sizeof(sTimeRangeCruise), &iReturnByteEX);
		if (sTimeRangeCruise.iEnable != 0)//使能
		{
			m_vecSceneTimeRangeCruise.push_back(sTimeRangeCruise);
		}
		else
		{
			continue;
		}
	}

	if (m_vecSceneTimeRangeCruise.size() == 0)
	{
		m_lst_CuriseTimeInfo.ShowControls(FALSE);
		m_lst_CuriseTimeInfo.Invalidate();
	}
	m_lst_CuriseTimeInfo.ShowWindow(SW_SHOW);
	m_lst_CuriseTimeInfo.Invalidate(TRUE);

	if(m_vecSceneTimeRangeCruise.size() != 0 && m_bTimeCurise == false)//如果当前没有模版，就不需要插入
	{
		//这三个函数位置不可变，因为要保持按时间段巡航的comboxid和定时巡航保持一致
		m_lst_CuriseTimeInfo.SetItemControl(DATECTRL, E_TIMECRUISE_FOUTH);
		m_lst_CuriseTimeInfo.SetItemControl(COMBOBOX, E_TIMECRUISE_SECOND);//添加combox控件 ，此函数要在AddToControlsData（）函数之前调用
		m_lst_CuriseTimeInfo.SetItemControl(DATECTRL, E_TIMECRUISE_FIFTH);
		m_bTimeCurise = true ;

	}
	else if (m_vecSceneTimeRangeCruise.size() == 0)
	{
		m_iCruiseType = SENCE_CRUISE_TYPE_TIMERANGE ;
		m_bTimeCurise = true ;
		return ;
	}

	//获取时间段巡航的信息
	AnyScene sScene = {0};
	int iReturnByte ;
	m_vecAnyScene.clear();
	for (int i = 0; i < MAX_SCENE_NUM; i++)//循环0-15个场景
	{
		sScene.iSceneID = i;
		NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_ANYSCENE, m_iChannelNO, &sScene, sizeof(AnyScene), &iReturnByte);
		m_vecAnyScene.push_back(sScene);
		//给使能的场景编号，插入到combox中去
		m_lst_CuriseTimeInfo.AddToControlsData(E_TIMECRUISE_SECOND,IntToStr(i+1).c_str());//1 代表第一列 
	}

	//将获取的到信息插入到list contrl中
	int iCount = (int)m_vecSceneTimeRangeCruise.size();
	for(int i = 0;i < iCount; i++)
	{
		m_lst_CuriseTimeInfo.InsertItem(i,_T(""));
		LVITEM item;
		memset(&item, 0, sizeof(LVITEM));
		item.mask = LVIF_TEXT;
		item.iItem = i;
		CString cstrTmp = "";

		//序号
		item.iSubItem = E_TIMECRUISE_FIRST;
		cstrTmp = IntToStr(i+1).c_str() ;
		item.pszText = (LPSTR)(LPCTSTR)cstrTmp;
		m_lst_CuriseTimeInfo.SetItem(&item);

		item.iSubItem = E_TIMECRUISE_SECOND;
		CString strSceneid = IntToCString(m_vecSceneTimeRangeCruise[i].iSceneID +1);
		int iSceneId = m_vecSceneTimeRangeCruise[i].iSceneID ;
		item.pszText = (LPSTR)(LPCTSTR)(strSceneid);
		m_lst_CuriseTimeInfo.SetItem(&item);
		m_lst_CuriseTimeInfo.SetItemData(i,m_vecSceneTimeRangeCruise[i].iSceneID);

		//场景名称
		item.iSubItem = E_TIMECRUISE_THIRD;
		if (iSceneId >= 0 && iSceneId < MAX_SCENE_NUM)
		{
			item.pszText = (LPSTR)(LPCTSTR)m_vecAnyScene[iSceneId].cSceneName;
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "[VCAframDomeCurise::OnBnClickedRadioCuriseTimerange]invalid iScenceId = %d", iSceneId);
		}
		m_lst_CuriseTimeInfo.SetItem(&item);

		CString strStartTime = "" ;
		strStartTime.Format(_T("%02d:%02d"), m_vecSceneTimeRangeCruise[i].iBeginHour, m_vecSceneTimeRangeCruise[i].iBeginMinute);
		//开始时间
		item.iSubItem = E_TIMECRUISE_FOUTH;
		item.pszText = (LPSTR)(LPCTSTR)strStartTime;
		m_lst_CuriseTimeInfo.SetItem(&item);

		CString strEndTime = "";
		strEndTime.Format(_T("%02d:%02d"), m_vecSceneTimeRangeCruise[i].iEndHour, m_vecSceneTimeRangeCruise[i].iEndMinute);
		//结束时间
		item.iSubItem = E_TIMECRUISE_FIFTH;
		item.pszText = (LPSTR)(LPCTSTR)strEndTime;
		m_lst_CuriseTimeInfo.SetItem(&item);
	}
	//当前行被取消
	m_lst_CuriseTimeInfo.SetItemState(m_iCount, 0, LVIS_SELECTED|LVIS_FOCUSED);
	m_lst_CuriseTimeInfo.SetItemColor(m_iCount, COLOR_CANCEL);

	int iTotal = m_lst_CuriseTimeInfo.GetItemCount();
	if (iTotal > 0)
	{
		m_lst_CuriseTimeInfo.MoveControlToFocusItem(0);
	} 

	m_iCruiseType = SENCE_CRUISE_TYPE_TIMERANGE ;
	m_bTimeCurise = true ;
}

int VCAframDomeCurise::ChooseTimeUpdateUI( int _iType )
{
	GetDlgItem(IDC_STATIC_CURISE_STOPTIME)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_CURISE_BEGTIME)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_CURISE_ENDTIME)->ShowWindow(FALSE);
	if(_iType == SENCE_CRUISE_TYPE_TIMER)
	{
		GetDlgItem(IDC_STATIC_CURISE_STOPTIME)->ShowWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_CURISE_BEGTIME)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_CURISE_ENDTIME)->ShowWindow(TRUE);
	}
	return 0;
}

//添加定时巡航
void VCAframDomeCurise::AddTimerCruiseInfo()
{
	m_lst_CuriseInfo.GetAndDisplayControlsData();
	m_lst_CuriseInfo.ShowControls(false);

	int iCount = m_lst_CuriseInfo.GetItemCount();
	if(iCount >= MAX_COUNT_NUM)
	{
		return;
	}

	if (iCount == 0 && !m_bSetControl)
	{
		m_lst_CuriseInfo.SetItemControl(EDITBOX, E_CRUISE_FOUTH);
		m_lst_CuriseInfo.SetItemControl(COMBOBOX, E_CRUISE_SECOND);//添加combox控件 ，此函数要在AddToControlsData（）函数之前调用
		m_lst_CuriseInfo.SetLimitTextLength(E_CRUISE_FOUTH, LEN_8);
		m_bSetControl = true;
	} 

	AnyScene sScene = {0};
	int iReturnByte = 0;
	m_lst_CuriseInfo.ResetContent();
	m_vecAnyScene.clear();
	for (int i = 0; i < MAX_SCENE_NUM; ++i)//循环0-15个场景
	{
		sScene.iSceneID = i;
		int iRet = -1;
		iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_ANYSCENE, m_iChannelNO, &sScene, sizeof(AnyScene), &iReturnByte);
		m_vecAnyScene.push_back(sScene);
		//给使能的场景编号，插入到combox中去
		m_lst_CuriseInfo.AddToControlsData(E_CRUISE_SECOND, IntToStr(i+1).c_str());//i是index 
	}

	//将获取的到信息插入到list contrl中
	int iSize = (int)m_vecAnyScene.size();
	m_lst_CuriseInfo.InsertItem(iCount, _T(""));
	LVITEM item;
	memset(&item, 0, sizeof(LVITEM));
	item.mask = LVIF_TEXT;
	item.iItem = iCount;
	CString cstrTmp = "";

	int iNum = iCount + 1 ; 
	//序号
	item.iSubItem = E_CRUISE_FIRST;
	cstrTmp = IntToStr(iNum).c_str();
	item.pszText = (LPSTR)(LPCTSTR)cstrTmp;
	m_lst_CuriseInfo.SetItem(&item);

	item.iSubItem = E_CRUISE_SECOND;
	CString strScenID = IntToCString(m_vecAnyScene[0].iSceneID +1);
	item.pszText = (LPSTR)(LPCTSTR)strScenID;
	m_lst_CuriseInfo.SetItem(&item);
	m_lst_CuriseInfo.SetItemData(0,m_vecAnyScene[0].iSceneID);

	//场景名称
	item.iSubItem = E_CRUISE_THIRD;
	item.pszText =(LPSTR)(LPCTSTR) m_vecAnyScene[0].cSceneName;
	m_lst_CuriseInfo.SetItem(&item);

	//保留时间---默认写30
	CString strTempTime = _T("300");
	item.iSubItem = E_CRUISE_FOUTH;
	item.pszText = (LPSTR)(LPCTSTR)strTempTime;
	m_lst_CuriseInfo.SetItem(&item);

	if(iCount == 0)
	{
		//第一行被选中
		m_lst_CuriseInfo.SetItemState(E_CRUISE_FIRST, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		m_lst_CuriseInfo.SetItemColor(E_CRUISE_FIRST, COLOR_SET);
	}
	else
	{
		//当前行被取消
		m_lst_CuriseInfo.SetItemState(iCount-1, 0, LVIS_SELECTED|LVIS_FOCUSED);
		m_lst_CuriseInfo.SetItemColor(iCount-1, COLOR_CANCEL);
		//当前行被选中
		m_lst_CuriseInfo.SetItemState(iCount, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		m_lst_CuriseInfo.SetItemColor(iCount, COLOR_SET);
		m_iCount = iCount;

	}
	m_lst_CuriseInfo.MoveControlToFocusItem(iCount);
}

//添加按时间段巡航
void VCAframDomeCurise::AddTimeRangeCruiseInfo()
{
	m_lst_CuriseTimeInfo.ShowControls(false);
	m_lst_CuriseTimeInfo.GetAndDisplayControlsData();

	int iCount = m_lst_CuriseTimeInfo.GetItemCount();
	if(iCount >= MAX_COUNT_NUM)
	{
		return;
	}
	if (iCount == 0 && !m_bTimeSetControl)
	{
		m_lst_CuriseTimeInfo.SetItemControl(DATECTRL, E_TIMECRUISE_FOUTH);
		m_lst_CuriseTimeInfo.SetItemControl(COMBOBOX, E_TIMECRUISE_SECOND);//添加combox控件 ，此函数要在AddToControlsData（）函数之前调用
		m_lst_CuriseTimeInfo.SetItemControl(DATECTRL, E_TIMECRUISE_FIFTH);
		m_bTimeSetControl = true;
	}
	m_lst_CuriseTimeInfo.SetItemColor(iCount, COLOR_SET);//新添加的item颜色置为蓝色

	AnyScene sScene = {0};
	int iReturnByte = 0;
	m_lst_CuriseTimeInfo.ResetContent();
	m_vecAnyScene.clear();
	for (int i = 0; i < MAX_SCENE_NUM; ++i)//循环0-15个场景
	{
		sScene.iSceneID = i ;
		NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_ANYSCENE, m_iChannelNO, &sScene, sizeof(AnyScene), &iReturnByte);
		m_vecAnyScene.push_back(sScene);
		//给使能的场景编号，插入到combox中去
		m_lst_CuriseTimeInfo.AddToControlsData(E_TIMECRUISE_SECOND, IntToStr(i+1).c_str());//i是index 
	}

	//将获取的到信息插入到list contrl中
	int iSize = (int)m_vecAnyScene.size();
	m_lst_CuriseTimeInfo.InsertItem(iCount, _T(""));
	LVITEM item;
	memset(&item, 0, sizeof(LVITEM));
	item.mask = LVIF_TEXT;
	item.iItem = iCount;
	CString cstrTmp = "";

	int iNum = iCount + 1; 
	//序号
	item.iSubItem = E_TIMECRUISE_FIRST;
	cstrTmp = IntToStr(iNum).c_str() ;
	item.pszText = (LPSTR)(LPCTSTR)cstrTmp;
	m_lst_CuriseTimeInfo.SetItem(&item);

	item.iSubItem = E_TIMECRUISE_SECOND;
	CString strScenID = IntToCString(m_vecAnyScene[0].iSceneID + 1);
	item.pszText = (LPSTR)(LPCTSTR)strScenID;
	m_lst_CuriseTimeInfo.SetItem(&item);
	m_lst_CuriseTimeInfo.SetItemData(0,m_vecAnyScene[0].iSceneID);

	//场景名称
	item.iSubItem = E_TIMECRUISE_THIRD;
	item.pszText = (LPSTR)(LPCTSTR) m_vecAnyScene[0].cSceneName;
	m_lst_CuriseTimeInfo.SetItem(&item);

	//开始时间
	CString strTempStartTime = _T("00:00");
	item.iSubItem = E_TIMECRUISE_FOUTH;
	item.pszText = (LPSTR)(LPCTSTR)strTempStartTime;
	m_lst_CuriseTimeInfo.SetItem(&item);


	CString strTempEndTime = _T("23:59");
	//结束时间
	item.iSubItem = E_TIMECRUISE_FIFTH;
	item.pszText = (LPSTR)(LPCTSTR)strTempEndTime;
	m_lst_CuriseTimeInfo.SetItem(&item);

	if(iCount == 0)
	{
		//当前行被选中
		m_lst_CuriseTimeInfo.SetItemState(E_TIMECRUISE_FIRST, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		m_lst_CuriseTimeInfo.SetItemColor(E_TIMECRUISE_FIRST, COLOR_SET);
	}
	else
	{
		//当前行被取消
		m_lst_CuriseTimeInfo.SetItemState(iCount-1, 0, LVIS_SELECTED|LVIS_FOCUSED);
		m_lst_CuriseTimeInfo.SetItemColor(iCount-1, COLOR_CANCEL);
		//当前行被选中
		m_lst_CuriseTimeInfo.SetItemState(iCount, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		m_lst_CuriseTimeInfo.SetItemColor(iCount, COLOR_SET);
		m_iCount = iCount;

	}
	m_lst_CuriseTimeInfo.MoveControlToFocusItem(iCount);
}

//添加时间段内的定时巡航
void VCAframDomeCurise::AddTimingCruiseByTimeRangeInfo()
{
	m_lstTimingCruiseByTimeRange.ShowControls(false);
	m_lstTimingCruiseByTimeRange.GetAndDisplayControlsData();

	int iCount = m_lstTimingCruiseByTimeRange.GetItemCount();
	if(iCount >= MAX_COUNT_NUM)
	{
		return;
	}
	if (iCount == 0 && !m_bTimingByTimeRangeSetControl)
	{
		m_lstTimingCruiseByTimeRange.SetItemControl(DATECTRL, E_TIMINGCRUISEBYTIMERANGE_FOUTH);
		m_lstTimingCruiseByTimeRange.SetItemControl(COMBOBOX, E_TIMINGCRUISEBYTIMERANGE_SECOND);//添加combox控件 ，此函数要在AddToControlsData（）函数之前调用
		m_lstTimingCruiseByTimeRange.SetItemControl(DATECTRL, E_TIMINGCRUISEBYTIMERANGE_FIFTH);
		m_lstTimingCruiseByTimeRange.SetItemControl(EDITBOX, E_TIMINGCRUISEBYTIMERANGE_SIXTH);
		m_lstTimingCruiseByTimeRange.SetLimitTextLength(E_TIMINGCRUISEBYTIMERANGE_SIXTH, LEN_8);
		m_bTimingByTimeRangeSetControl = true;
	}
	m_lstTimingCruiseByTimeRange.SetItemColor(iCount, COLOR_SET);//新添加的item颜色置为蓝色

	AnyScene sScene = {0};
	int iReturnByte = 0;
	m_lstTimingCruiseByTimeRange.ResetContent();
	m_vecAnyScene.clear();
	for (int i = 0; i < MAX_SCENE_NUM; ++i)//循环0-15个场景
	{
		sScene.iSceneID = i;
		NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_ANYSCENE, m_iChannelNO, &sScene, sizeof(AnyScene), &iReturnByte);
		m_vecAnyScene.push_back(sScene);
		//给使能的场景编号，插入到combox中去
		m_lstTimingCruiseByTimeRange.AddToControlsData(E_TIMINGCRUISEBYTIMERANGE_SECOND, IntToStr(i+1).c_str());//i是index 
	}

	//将获取的到信息插入到list contrl中
	int iSize = (int)m_vecAnyScene.size();
	m_lstTimingCruiseByTimeRange.InsertItem(iCount, _T(""));
	LVITEM item;
	memset(&item, 0, sizeof(LVITEM));
	item.mask = LVIF_TEXT;
	item.iItem = iCount;
	CString cstrTmp = "";

	int iNum = iCount + 1; 
	//序号
	item.iSubItem = E_TIMINGCRUISEBYTIMERANGE_FIRST;
	cstrTmp = IntToStr(iNum).c_str();
	item.pszText = (LPSTR)(LPCTSTR)cstrTmp;
	m_lstTimingCruiseByTimeRange.SetItem(&item);

	item.iSubItem = E_TIMINGCRUISEBYTIMERANGE_SECOND;
	CString strScenID = IntToCString(m_vecAnyScene[0].iSceneID + 1);
	item.pszText = (LPSTR)(LPCTSTR)strScenID;
	m_lstTimingCruiseByTimeRange.SetItem(&item);
	m_lstTimingCruiseByTimeRange.SetItemData(0, m_vecAnyScene[0].iSceneID);

	//场景名称
	item.iSubItem = E_TIMINGCRUISEBYTIMERANGE_THIRD;
	item.pszText = (LPSTR)(LPCTSTR) m_vecAnyScene[0].cSceneName;
	m_lstTimingCruiseByTimeRange.SetItem(&item);

	//开始时间
	CString strTempStartTime = _T("00:00");
	item.iSubItem = E_TIMINGCRUISEBYTIMERANGE_FOUTH;
	item.pszText = (LPSTR)(LPCTSTR)strTempStartTime;
	m_lstTimingCruiseByTimeRange.SetItem(&item);


	CString strTempEndTime = _T("23:59");
	//结束时间
	item.iSubItem = E_TIMINGCRUISEBYTIMERANGE_FIFTH;
	item.pszText = (LPSTR)(LPCTSTR)strTempEndTime;
	m_lstTimingCruiseByTimeRange.SetItem(&item);

	//保留时间---默认写30
	CString strTempTime = _T("300");
	item.iSubItem = E_TIMINGCRUISEBYTIMERANGE_SIXTH;
	item.pszText = (LPSTR)(LPCTSTR)strTempTime;
	m_lstTimingCruiseByTimeRange.SetItem(&item);

	if(iCount == 0)
	{
		//当前行被选中
		m_lstTimingCruiseByTimeRange.SetItemState(E_TIMINGCRUISEBYTIMERANGE_FIRST, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		m_lstTimingCruiseByTimeRange.SetItemColor(E_TIMINGCRUISEBYTIMERANGE_FIRST, COLOR_SET);
	}
	else
	{
		//当前行被取消
		m_lstTimingCruiseByTimeRange.SetItemState(iCount-1, 0, LVIS_SELECTED|LVIS_FOCUSED);
		m_lstTimingCruiseByTimeRange.SetItemColor(iCount-1, COLOR_CANCEL);
		//当前行被选中
		m_lstTimingCruiseByTimeRange.SetItemState(iCount, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		m_lstTimingCruiseByTimeRange.SetItemColor(iCount, COLOR_SET);
		m_iCount = iCount;

	}
	m_lstTimingCruiseByTimeRange.MoveControlToFocusItem(iCount);
}

//添加按钮
void VCAframDomeCurise::OnBnClickedButtonCuriseadd()
{
	if(m_iCruiseType == SENCE_CRUISE_TYPE_TIMER)//定时
	{
		return AddTimerCruiseInfo();
	}
	else if(m_iCruiseType == SENCE_CRUISE_TYPE_TIMERANGE)
	{
		return AddTimeRangeCruiseInfo();
	}
	else
	{
		return AddTimingCruiseByTimeRangeInfo();	
	}
}

//删除按钮
void VCAframDomeCurise::DeleteTimerCruiseInfo()
{
	int iStartCount = m_lst_CuriseInfo.GetItemCount();
	if(iStartCount == 0)
	{
		return;
	}
	for(int i = iStartCount; i > 0; i--)
	{	
		if (BST_CHECKED == m_lst_CuriseInfo.GetCheck(i-1))
		{
			m_lst_CuriseInfo.DeleteItem(i-1);
		}
	}

	//删除后重新排序
	CString strRefresh;
	for(int i = 1; i <= m_lst_CuriseInfo.GetItemCount(); i++)
	{
		strRefresh.Format(_T("%d"), i);
		m_lst_CuriseInfo.SetItemText(i-1, 0, strRefresh);
	}

	int iEndCount = m_lst_CuriseInfo.GetItemCount();
	if (iEndCount == 0)
	{
		m_lst_CuriseInfo.ShowControls(FALSE);
		m_lst_CuriseInfo.ReleaseControls();
		m_bSetControl = false;
	} 
	else
	{
		m_lst_CuriseInfo.MoveControlToFocusItem(0);
	}

	m_lst_CuriseInfo.Invalidate();
}

void VCAframDomeCurise::DeleteTimeRangeCruiseInfo()
{
	int iStartCount = m_lst_CuriseTimeInfo.GetItemCount();
	if(iStartCount == 0)
	{
		return;
	}
	for(int i = iStartCount; i > 0; i--)
	{	
		if (BST_CHECKED == m_lst_CuriseTimeInfo.GetCheck(i-1))
		{
			m_lst_CuriseTimeInfo.DeleteItem(i-1);
		}
	}
	//删除后重新排序
	CString strRefresh;
	for(int i = 1;i <= m_lst_CuriseTimeInfo.GetItemCount();i++)
	{
		strRefresh.Format(_T("%d"), i);
		m_lst_CuriseTimeInfo.SetItemText(i-1, 0, strRefresh);
	}

	int iEndCount = m_lst_CuriseTimeInfo.GetItemCount();
	if (iEndCount == 0)
	{
		m_lst_CuriseTimeInfo.ShowControls(FALSE);
		m_lst_CuriseTimeInfo.ReleaseControls();
		m_bTimeSetControl = false;
	} 
	else
	{
		m_lst_CuriseTimeInfo.MoveControlToFocusItem(0);
	}

	m_lst_CuriseTimeInfo.Invalidate();
}

void VCAframDomeCurise::DeleteTimingCruiseByTimeRangeInfo()
{
	int iStartCount = m_lstTimingCruiseByTimeRange.GetItemCount();
	if(iStartCount == 0)
	{
		return;
	}
	for(int i = iStartCount; i > 0; i--)
	{	
		if (BST_CHECKED == m_lstTimingCruiseByTimeRange.GetCheck(i-1))
		{
			m_lstTimingCruiseByTimeRange.DeleteItem(i-1);
		}
	}
	//删除后重新排序
	CString strRefresh;
	for(int i = 1; i <= m_lstTimingCruiseByTimeRange.GetItemCount(); i++)
	{
		strRefresh.Format(_T("%d"), i);
		m_lstTimingCruiseByTimeRange.SetItemText(i-1, 0, strRefresh);
	}

	int iEndCount = m_lstTimingCruiseByTimeRange.GetItemCount();
	if (iEndCount == 0)
	{
		m_lstTimingCruiseByTimeRange.ShowControls(FALSE);
		m_lstTimingCruiseByTimeRange.ReleaseControls();
		m_bTimingByTimeRangeSetControl = false;
	} 
	else
	{
		m_lstTimingCruiseByTimeRange.MoveControlToFocusItem(0);
	}	

	m_lstTimingCruiseByTimeRange.Invalidate();
}

//删除
void VCAframDomeCurise::OnBnClickedButtonCurisedel()
{
	if(m_iCruiseType == SENCE_CRUISE_TYPE_TIMER)//定时巡航
	{
		return DeleteTimerCruiseInfo();
	}
	else if (m_iCruiseType == SENCE_CRUISE_TYPE_TIMERANGE)
	{
		return DeleteTimeRangeCruiseInfo();	
	}
	else
	{
		return DeleteTimingCruiseByTimeRangeInfo();
	}
}

void VCAframDomeCurise::SaveTimerCruiseInfo()
{
	int iTotal = 0;
	m_lst_CuriseInfo.GetAndDisplayControlsData();
	int iCount = m_lst_CuriseInfo.GetItemCount();

	//先判断时间是否都符合要求，不符合提示，同时不发送协议
	for(int i = 0; i < iCount; i++)
	{
		CString strTime = m_lst_CuriseInfo.GetItemText(i, E_CRUISE_FOUTH);
		int iTime = StrToInt(strTime);
		if (iTime > TIME_MAX || iTime < TIME_MIN)
		{
			iTotal++;
		}
	}
	if (iTotal > 0)//如果有不符合的时间段，就返回，不发送，都满足条件后在发送
	{
		return;
	}
	else
	{
		int iEnable = SENCE_CRUISE_TYPE_TIMER;//定时模版使能
		int iRet = -1;
		iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_SENCE_CRUISE_TYPE, m_iChannelNO, &iEnable, sizeof(int));
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TYPE] (%d, %d, %d)", m_iLogonID, m_iChannelNO, iEnable);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TYPE] (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNO, iEnable, GetLastError());
			return;
		}
		SceneTimerCruise sTimerCruise = {0};
		sTimerCruise.iBufSize = sizeof(SceneTimerCruise);
		for(int i = 0 ;i < iCount; i++)//发送使能的
		{
			sTimerCruise.iCruiseID = i;
			CString strTime = m_lst_CuriseInfo.GetItemText(i, E_CRUISE_FOUTH);
			sTimerCruise.iTime = StrToInt(strTime);
			if(sTimerCruise.iTime > TIME_MAX || sTimerCruise.iTime < TIME_MIN)
			{
				sTimerCruise.iTime = DEFAULT_TIME;
			}
			CString strSceneID = m_lst_CuriseInfo.GetItemText(i, E_CRUISE_SECOND);
			sTimerCruise.iSceneID = StrToInt(strSceneID) - 1;

			vector<AnyScene>::iterator iter ;
			for(iter = m_vecAnyScene.begin(); iter != m_vecAnyScene.end(); iter++)
			{
				if (iter->iSceneID == sTimerCruise.iSceneID)
				{
					if (iter->iArithmetic != 0)
					{
						sTimerCruise.iEnable = 1 ;
						iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_SENCE_CRUISE_TIMER, m_iChannelNO
							, &sTimerCruise, sizeof(SceneTimerCruise));
						if (0 == iRet)
						{
							AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TIMER] (%d, %d, %d)", m_iLogonID, m_iChannelNO, iEnable);
						}
						else
						{
							AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TIMER] (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNO, iEnable, GetLastError());
							return;
						}
					} 
					else//已经添加没使能的
					{
						sTimerCruise.iEnable = 0;
						sTimerCruise.iTime = 0;
						int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_SENCE_CRUISE_TIMER, m_iChannelNO
							, &sTimerCruise, sizeof(SceneTimerCruise));
						if (0 == iRet)
						{
							AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TIMER] (%d, %d, %d)", m_iLogonID, m_iChannelNO, iEnable);
						}
						else
						{
							AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TIMER] (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNO, iEnable, GetLastError());
							return;
						}
					}
				}	
			}
		}
		for (int j = iCount; j < MAX_SCENE_NUM; j++)//每天就不使能的
		{
			sTimerCruise.iEnable = 0;
			sTimerCruise.iTime = 0;
			sTimerCruise.iSceneID = j;
			sTimerCruise.iCruiseID  = j;
			iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_SENCE_CRUISE_TIMER, m_iChannelNO, &sTimerCruise, sizeof(SceneTimerCruise));
			if (0 == iRet)
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TIMER] (%d, %d, %d)", m_iLogonID, m_iChannelNO, iEnable);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TIMER] (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNO, iEnable, GetLastError());
				return;
			}
		}	
	}
}

void VCAframDomeCurise::SaveTimeRangeCruiseInfo()
{
	m_lst_CuriseTimeInfo.GetAndDisplayControlsData();
	int iCount = m_lst_CuriseTimeInfo.GetItemCount();
	int iTotal = 0;

	ClearMapTimeInfo();

	//将list ctrl上的时间获取出来，放到map中去（无法实时获取比较，因此要先将时间保存起来，然后在比较）
	for(int i = 0; i < iCount; i++)
	{
		STRTTime *strTime = new STRTTime();
		strTime->strsBengin = m_lst_CuriseTimeInfo.GetItemText(i, E_TIMECRUISE_FOUTH); 
		strTime->strEnd = m_lst_CuriseTimeInfo.GetItemText(i, E_TIMECRUISE_FIFTH); 
		m_mapTimeInfo.insert(map<int,STRTTime*>::value_type(i, strTime));//将一行对应的开始时间，结束时间存入map中
	}

	//从map中提取信息第一个和第二个进行时间比较，然后依次类推，
	for (int i = 0; i < iCount; i++)
	{
		//进行时间判断
		int iTemp = (int)m_mapTimeInfo.size();
		int J = i + 1;
		if(J < iCount )
		{
			if (m_mapTimeInfo[i]->strEnd == m_mapTimeInfo[i+1]->strEnd && m_mapTimeInfo[i]->strsBengin == m_mapTimeInfo[i+1]->strsBengin )
			{
				iTotal++;
				break;
			}
			if(m_mapTimeInfo[i]->strEnd > m_mapTimeInfo[i+1]->strsBengin && m_mapTimeInfo[i]->strsBengin < m_mapTimeInfo[i+1]->strEnd
				|| m_mapTimeInfo[i+1]->strEnd > m_mapTimeInfo[i]->strsBengin && m_mapTimeInfo[i+1]->strsBengin < m_mapTimeInfo[i]->strsBengin)
			{
				iTotal++;
				break;
			}
		}
		if (m_mapTimeInfo[i]->strsBengin > m_mapTimeInfo[i]->strEnd)
		{
			iTotal++;
			break;
		}
	}
	if(iTotal > 0)//如果有不符合的时间段，就返回，不发送，都满足条件后在发送
	{
		MessageBox(GetTextEx(IDS_VCA_ENTER_CORRECT_TIME), "", MB_OK|MB_TOPMOST);
		return;
	}
	else
	{
		SceneTimeRangeCruise sTimeRangeCruise = {0};
		int iEnable = SENCE_CRUISE_TYPE_TIMERANGE;//按时间段模版使能
		int iRet = -1;
		iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_SENCE_CRUISE_TYPE, m_iChannelNO, &iEnable, sizeof(int));
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TYPE] (%d, %d, %d)", m_iLogonID, m_iChannelNO, iEnable);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TYPE] (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNO, iEnable, GetLastError());
			return;
		}

		sTimeRangeCruise.iBufSize = sizeof(SceneTimeRangeCruise);
		for(int i = 0; i < iCount; i++)
		{
			sTimeRangeCruise.iCruiseID = i;
			CString strSceneID = m_lst_CuriseTimeInfo.GetItemText(i, E_TIMECRUISE_SECOND);
			sTimeRangeCruise.iSceneID = StrToInt(strSceneID)-1;
			sTimeRangeCruise.iWeekday = 0;//星期暂时不用，先传0

			//----需要将时间截取
			CString strStartTime = m_lst_CuriseTimeInfo.GetItemText(i, E_TIMECRUISE_FOUTH); 
			int iStart = strStartTime.Find(":");
			if (iStart < 0)
			{
				iStart = 0;
			}

			sTimeRangeCruise.iBeginHour = StrToInt(strStartTime.Left(iStart));
			sTimeRangeCruise.iBeginMinute = StrToInt(strStartTime.Right(iStart));

			CString strEndTime = m_lst_CuriseTimeInfo.GetItemText(i, E_TIMECRUISE_FIFTH); 
			int iEnd = strEndTime.Find(":");
			if (iEnd < 0)
			{
				iEnd = 0;
			}
			sTimeRangeCruise.iEndHour = StrToInt(strEndTime.Left(iEnd));
			sTimeRangeCruise.iEndMinute = StrToInt(strEndTime.Right(iEnd));

			vector<AnyScene>::iterator iter ;
			for(iter = m_vecAnyScene.begin(); iter != m_vecAnyScene.end(); iter ++)
			{
				if (iter->iSceneID == sTimeRangeCruise.iSceneID)
				{
					if (iter->iArithmetic != 0)
					{
						sTimeRangeCruise.iEnable = 1;
						iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_SENCE_CRUISE_TIMERANGE, m_iChannelNO
							, &sTimeRangeCruise, sizeof(sTimeRangeCruise));
						if (0 == iRet)
						{
							AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TIMERANGE] (%d, %d, %d)", m_iLogonID, m_iChannelNO, iEnable);
						}
						else
						{
							AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TIMERANGE] (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNO, iEnable, GetLastError());
							return;
						}
					} 
					else
					{
						sTimeRangeCruise.iEnable = 0;
						iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_SENCE_CRUISE_TIMERANGE, m_iChannelNO
							, &sTimeRangeCruise, sizeof(sTimeRangeCruise));
						if (0 == iRet)
						{
							AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TIMERANGE] (%d, %d, %d)", m_iLogonID, m_iChannelNO, iEnable);
						}
						else
						{
							AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TIMERANGE] (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNO, iEnable, GetLastError());
							return;
						}
					}
				}
			}
		}
		for (int j = iCount; j < MAX_SCENE_NUM; j++)//发送不使能的
		{
			sTimeRangeCruise.iEnable = 0;
			sTimeRangeCruise.iCruiseID = j;
			int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_SENCE_CRUISE_TIMERANGE, m_iChannelNO, &sTimeRangeCruise, sizeof(SceneTimerCruise));
			if (0 == iRet)
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TIMERANGE] (%d, %d, %d)", m_iLogonID, m_iChannelNO, iEnable);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TIMERANGE] (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNO, iEnable, GetLastError());
				return;
			}
		}
	}
}

void VCAframDomeCurise::SaveTimingCruiseByTimeRangeInfo()
{
	m_lstTimingCruiseByTimeRange.GetAndDisplayControlsData();
	int iCount = m_lstTimingCruiseByTimeRange.GetItemCount();
	int iTotal = 0;

	ClearTimingCruiseMapTimeInfo();

	//将list ctrl上的时间获取出来，放到map中去（无法实时获取比较，因此要先将时间保存起来，然后在比较）
	for(int i = 0; i < iCount; i++)
	{
		STRTTime *strTime = new STRTTime();
		strTime->strsBengin = m_lstTimingCruiseByTimeRange.GetItemText(i, E_TIMINGCRUISEBYTIMERANGE_FOUTH); 
		strTime->strEnd = m_lstTimingCruiseByTimeRange.GetItemText(i, E_TIMINGCRUISEBYTIMERANGE_FIFTH); 
		m_mapTimingCruiseTimeInfo.insert(map<int,STRTTime*>::value_type(i, strTime));//将一行对应的开始时间，结束时间存入map中
	}

	//从map中提取信息第一个和第二个进行时间比较，然后依次类推，
	for (int i = 0; i < iCount; i++)
	{
		//进行时间判断
		int iTemp = (int)m_mapTimingCruiseTimeInfo.size();
		int J = i + 1;
		if(J < iCount)
		{
			if (m_mapTimingCruiseTimeInfo[i]->strEnd == m_mapTimingCruiseTimeInfo[i+1]->strEnd
				&& m_mapTimingCruiseTimeInfo[i]->strsBengin == m_mapTimingCruiseTimeInfo[i+1]->strsBengin )
			{
				iTotal++;
				break;
			}
			if(m_mapTimingCruiseTimeInfo[i]->strEnd > m_mapTimingCruiseTimeInfo[i+1]->strsBengin
				&& m_mapTimingCruiseTimeInfo[i]->strsBengin < m_mapTimingCruiseTimeInfo[i+1]->strEnd
				|| m_mapTimingCruiseTimeInfo[i+1]->strEnd > m_mapTimingCruiseTimeInfo[i]->strsBengin
				&& m_mapTimingCruiseTimeInfo[i+1]->strsBengin < m_mapTimingCruiseTimeInfo[i]->strsBengin)
			{
				iTotal++;
				break;
			}
		}
		if (m_mapTimingCruiseTimeInfo[i]->strsBengin > m_mapTimingCruiseTimeInfo[i]->strEnd)
		{
			iTotal++;
			break;
		}
	}
	if(iTotal > 0)//如果有不符合的时间段，就返回，不发送，都满足条件后在发送
	{
		MessageBox(GetTextEx(IDS_VCA_ENTER_CORRECT_TIME), "", MB_OK|MB_TOPMOST);
		return;
	}
	else
	{
		SceneTimeRangeCruise tTimingCruiseByTimeRange = {0};
		int iEnable = SENCE_CRUISE_TYPE_TIMING_BY_TIMERANGE ;//按时间段模版使能
		int iRet = -1;
		iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_SENCE_CRUISE_TYPE, m_iChannelNO, &iEnable, sizeof(int));
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TYPE] (%d, %d, %d)", m_iLogonID, m_iChannelNO, iEnable);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_SENCE_CRUISE_TYPE] (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNO, iEnable, GetLastError());
			return;
		}
		tTimingCruiseByTimeRange.iBufSize = sizeof(SceneTimeRangeCruise);
		for(int i = 0; i < iCount; i++)
		{
			tTimingCruiseByTimeRange.iCruiseID = i;
			CString strSceneID = m_lstTimingCruiseByTimeRange.GetItemText(i, E_TIMINGCRUISEBYTIMERANGE_SECOND);
			tTimingCruiseByTimeRange.iSceneID = StrToInt(strSceneID)-1;
			tTimingCruiseByTimeRange.iWeekday = 0;//星期暂时不用，先传0
			CString strTime = m_lstTimingCruiseByTimeRange.GetItemText(i, E_TIMINGCRUISEBYTIMERANGE_SIXTH) ;
			int iTime = StrToInt(strTime);
			if(iTime > TIME_MAX || iTime < TIME_MIN)
			{
				iTime = DEFAULT_TIME;
			}
			tTimingCruiseByTimeRange.tInfo[i].iSceneID = tTimingCruiseByTimeRange.iSceneID;
			tTimingCruiseByTimeRange.tInfo[i].iRemainTime = iTime;

			//----需要将时间截取
			CString strStartTime = m_lstTimingCruiseByTimeRange.GetItemText(i, E_TIMINGCRUISEBYTIMERANGE_FOUTH); 
			int iStart = strStartTime.Find(":");
			if (iStart < 0)
			{
				iStart = 0;
			}

			tTimingCruiseByTimeRange.iBeginHour = StrToInt(strStartTime.Left(iStart));
			tTimingCruiseByTimeRange.iBeginMinute = StrToInt(strStartTime.Right(iStart));

			CString strEndTime = m_lstTimingCruiseByTimeRange.GetItemText(i, E_TIMINGCRUISEBYTIMERANGE_FIFTH); 
			int iEnd = strEndTime.Find(":");
			if (iEnd < 0)
			{
				iEnd = 0;
			}
			tTimingCruiseByTimeRange.iEndHour = StrToInt(strEndTime.Left(iEnd));
			tTimingCruiseByTimeRange.iEndMinute = StrToInt(strEndTime.Right(iEnd));

			vector<AnyScene>::iterator iter;
			for(iter = m_vecAnyScene.begin(); iter != m_vecAnyScene.end(); iter ++)
			{
				if (iter->iSceneID == tTimingCruiseByTimeRange.iSceneID)
				{
					if (iter->iArithmetic != 0)
					{
						tTimingCruiseByTimeRange.iEnable = 1;
						iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_TIMINGCRUISE_BY_TIMERANGE, m_iChannelNO
							, &tTimingCruiseByTimeRange, sizeof(tTimingCruiseByTimeRange));
						if (0 == iRet)
						{
							AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_TIMINGCRUISE_BY_TIMERANGE] (%d, %d, %d)", m_iLogonID, m_iChannelNO, iEnable);
						}
						else
						{
							AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_TIMINGCRUISE_BY_TIMERANGE] (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNO, iEnable, GetLastError());
							return;
						}
					} 
					else
					{
						tTimingCruiseByTimeRange.iEnable = 0;
						iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_TIMINGCRUISE_BY_TIMERANGE, m_iChannelNO
							, &tTimingCruiseByTimeRange, sizeof(tTimingCruiseByTimeRange));
						if (0 == iRet)
						{
							AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_TIMINGCRUISE_BY_TIMERANGE] (%d, %d, %d)", m_iLogonID, m_iChannelNO, iEnable);
						}
						else
						{
							AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_TIMINGCRUISE_BY_TIMERANGE] (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNO, iEnable, GetLastError());
							return;
						}
					}
				}
			}
		}
		for (int j = iCount; j < MAX_SCENE_NUM; j++)//发送不使能的
		{
			tTimingCruiseByTimeRange.iEnable = 0;
			tTimingCruiseByTimeRange.iCruiseID = j;
			iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_TIMINGCRUISE_BY_TIMERANGE, m_iChannelNO, &tTimingCruiseByTimeRange, sizeof(SceneTimerCruise));
			if (0 == iRet)
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_TIMINGCRUISE_BY_TIMERANGE] (%d, %d, %d)", m_iLogonID, m_iChannelNO, iEnable);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_TIMINGCRUISE_BY_TIMERANGE] (%d, %d, %d), error (%d)", m_iLogonID, m_iChannelNO, iEnable, GetLastError());
				return;
			}
		}
	}
}

//保存
void VCAframDomeCurise::OnBnClickedButtonCuriseSave()
{
	if(m_iCruiseType == SENCE_CRUISE_TYPE_TIMER)//定时巡航
	{
		return SaveTimerCruiseInfo();
	}
	else if (m_iCruiseType == SENCE_CRUISE_TYPE_TIMERANGE)//按时间段巡航
	{
		return SaveTimeRangeCruiseInfo();
	}
	else
	{
		return SaveTimingCruiseByTimeRangeInfo();
	}
}

void VCAframDomeCurise::ClearMapTimeInfo()
{
	if (m_mapTimeInfo.size() > 0)
	{
		for (map<int, STRTTime*>::iterator it = m_mapTimeInfo.begin(); it != m_mapTimeInfo.end(); ++it)	
		{
			if (NULL == it->second)
			{
				continue;
			}
			delete it->second;
			it->second = NULL;
		}
		m_mapTimeInfo.clear();
	}
}

void VCAframDomeCurise::ClearTimingCruiseMapTimeInfo()
{
	if (m_mapTimingCruiseTimeInfo.size() > 0)
	{
		for (map<int, STRTTime*>::iterator it = m_mapTimingCruiseTimeInfo.begin(); it != m_mapTimingCruiseTimeInfo.end(); ++it)	
		{
			if (NULL == it->second)
			{
				continue;
			}
			delete it->second;
			it->second = NULL;
		}
		m_mapTimingCruiseTimeInfo.clear();
	}
}

BOOL VCAframDomeCurise::OnInitDialog()
{
	// TODO:  Add extra initialization here
	CLS_VCAEventBasePage::OnInitDialog();
	UpdateUIText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void VCAframDomeCurise::OnLanguageChanged( int _iLanguage )
{
	UpdateUIText();
}

void VCAframDomeCurise::UpdateUIText()
{
	CheckRadioButton(IDC_RADIO_CURISE_TIMER, IDC_RADIO_TIMING_CURISE_BY_TIMERANGE, IDC_RADIO_CURISE_TIMER);
	SetDlgItemTextEx(IDC_RADIO_CURISE_TIMER, IDS_CRUISE);
	SetDlgItemTextEx(IDC_RADIO_CURISE_TIMERANGE, IDS_TIME_CRUISE);
	SetDlgItemTextEx(IDC_RADIO_TIMING_CURISE_BY_TIMERANGE, IDS_VCA_TIMING_CURISE_BY_TIMERANGE);

	SetDlgItemTextEx(IDC_BUTTON_CURISE_SAVE, IDS_LOG_SAVE);
	SetDlgItemTextEx(IDC_BUTTON_CURISEADD, IDS_ADD);
	SetDlgItemTextEx(IDC_BUTTON_CURISEDEL, IDS_DELETE);

	//初始化定时巡航
	m_lst_CuriseInfo.DeleteAllColumns();
	m_lst_CuriseInfo.InsertColumn(E_CRUISE_FIRST,GetTextEx(IDS_NUM), LVCFMT_CENTER, 50);//序号
	m_lst_CuriseInfo.InsertColumn(E_CRUISE_SECOND,GetTextEx(IDS_AREA_NUM), LVCFMT_CENTER, 70);//场景编号
	m_lst_CuriseInfo.InsertColumn(E_CRUISE_THIRD,GetTextEx(IDS_AREA_NAME), LVCFMT_CENTER, 291);//场景名称
	m_lst_CuriseInfo.InsertColumn(E_CRUISE_FOUTH,GetTextEx(IDS_RESERVE_TIME), LVCFMT_CENTER, 170);//保留时间

	m_lst_CuriseInfo.SetRowHeigt(NeuRowHeigt);
	m_lst_CuriseInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	m_lst_CuriseInfo.SetHeaderHeight((float)1.1);
	m_lst_CuriseInfo.SetHeaderFontHW(HeaderFontHEX,NULL);
	m_lst_CuriseInfo.SetParentHwnd(m_hWnd);
	//初始化按时间段巡航
	m_lst_CuriseTimeInfo.DeleteAllColumns();
	m_lst_CuriseTimeInfo.InsertColumn(E_TIMECRUISE_FIRST,GetTextEx(IDS_NUM), LVCFMT_CENTER, 50);//序号
	m_lst_CuriseTimeInfo.InsertColumn(E_TIMECRUISE_SECOND,GetTextEx(IDS_AREA_NUM), LVCFMT_CENTER, 70);//场景编号
	m_lst_CuriseTimeInfo.InsertColumn(E_TIMECRUISE_THIRD,GetTextEx(IDS_AREA_NAME), LVCFMT_CENTER, 301);//场景名称
	m_lst_CuriseTimeInfo.InsertColumn(E_TIMECRUISE_FOUTH,GetTextEx(IDS_CONFIG_HOLIDAY_START_TIME), LVCFMT_CENTER, 80);//开始时间
	m_lst_CuriseTimeInfo.InsertColumn(E_TIMECRUISE_FIFTH,GetTextEx(IDS_CONFIG_HOLIDAY_END_TIME), LVCFMT_CENTER, 80);//结束时间

	m_lst_CuriseTimeInfo.SetRowHeigt(NeuRowHeigt);
	m_lst_CuriseTimeInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	m_lst_CuriseTimeInfo.SetHeaderHeight((float)1.1);
	m_lst_CuriseTimeInfo.SetHeaderFontHW(HeaderFontHEX,NULL);
	m_lst_CuriseTimeInfo.SetParentHwnd(m_hWnd);

	//初始化时间段内的定时巡航
	m_lstTimingCruiseByTimeRange.DeleteAllColumns();
	m_lstTimingCruiseByTimeRange.InsertColumn(E_TIMINGCRUISEBYTIMERANGE_FIRST,GetTextEx(IDS_NUM), LVCFMT_CENTER, 50);//序号
	m_lstTimingCruiseByTimeRange.InsertColumn(E_TIMINGCRUISEBYTIMERANGE_SECOND,GetTextEx(IDS_AREA_NUM), LVCFMT_CENTER, 70);//场景编号
	m_lstTimingCruiseByTimeRange.InsertColumn(E_TIMINGCRUISEBYTIMERANGE_THIRD,GetTextEx(IDS_AREA_NAME), LVCFMT_CENTER, 220);//场景名称
	m_lstTimingCruiseByTimeRange.InsertColumn(E_TIMINGCRUISEBYTIMERANGE_FOUTH,GetTextEx(IDS_CONFIG_HOLIDAY_START_TIME), LVCFMT_CENTER, 80);//开始时间
	m_lstTimingCruiseByTimeRange.InsertColumn(E_TIMINGCRUISEBYTIMERANGE_FIFTH,GetTextEx(IDS_CONFIG_HOLIDAY_END_TIME), LVCFMT_CENTER, 80);//结束时间
	m_lstTimingCruiseByTimeRange.InsertColumn(E_TIMINGCRUISEBYTIMERANGE_SIXTH,GetTextEx(IDS_RESERVE_TIME), LVCFMT_CENTER, 80);//保留时间
	m_lstTimingCruiseByTimeRange.SetRowHeigt(NeuRowHeigt);
	m_lstTimingCruiseByTimeRange.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	m_lstTimingCruiseByTimeRange.SetHeaderHeight((float)1.1);
	m_lstTimingCruiseByTimeRange.SetHeaderFontHW(HeaderFontHEX,NULL);
	m_lstTimingCruiseByTimeRange.SetParentHwnd(m_hWnd);

	m_lst_CuriseInfo.ShowWindow(SW_SHOW);
	m_lst_CuriseTimeInfo.ShowWindow(SW_HIDE);
	m_lstTimingCruiseByTimeRange.ShowWindow(SW_HIDE);

	OnBnClickedRadioCuriseTimer();
}

//向上移动
void VCAframDomeCurise::OnBnClickedButton1()
{
	if (m_iCruiseType == SENCE_CRUISE_TYPE_TIMER)//当前选择的是定时巡航
	{
		int iCount = m_lst_CuriseInfo.GetItemCount();
		if (iCount <= 1)
		{
			return;
		}

		int iCheck = 0 ;
		for (int i = 0; i < iCount; ++i)
		{		
			if (BST_CHECKED == m_lst_CuriseInfo.GetCheck(i))
			{
				iCheck ++ ;
			}
		}

		if (iCheck > 1)
		{
			//上下操作只支持选中一条
			return;
			
		}

		for (int i = 0; i < iCount; ++i)
		{		
			if (m_lst_CuriseInfo.GetItemState(i, LVIS_SELECTED))
			{
				MoveToNewPos(i, i - 1);	
			}
		}
	}
	else if (m_iCruiseType == SENCE_CRUISE_TYPE_TIMERANGE)
	{
		int iCount = m_lst_CuriseTimeInfo.GetItemCount();
		if (iCount <= 1)
		{
			return;
		}

		int iCheck = 0 ;
		for (int i = 0; i < iCount; ++i)
		{		
			if (BST_CHECKED == m_lst_CuriseTimeInfo.GetCheck(i))
			{
				iCheck ++ ;
			}
		}
		if (iCheck > 1)
		{
			//上下操作只支持选中一条
			return ;
		}

		for (int i = 0; i < iCount; ++i)
		{		
			if (m_lst_CuriseTimeInfo.GetItemState(i, LVIS_SELECTED))
			{
				MoveToNewPos(i, i - 1);	
			}
		}
	}
	else
	{
		int iCount = m_lstTimingCruiseByTimeRange.GetItemCount();
		if (iCount <= 1)
		{
			return;
		}

		int iCheck = 0 ;
		for (int i = 0; i < iCount; ++i)
		{		
			if (BST_CHECKED == m_lstTimingCruiseByTimeRange.GetCheck(i))
			{
				iCheck ++ ;
			}
		}
		if (iCheck > 1)
		{
			//上下操作只支持选中一条
			return ;
		}

		for (int i = 0; i < iCount; ++i)
		{		
			if (m_lstTimingCruiseByTimeRange.GetItemState(i, LVIS_SELECTED))
			{
				MoveToNewPos(i, i - 1);	
			}
		}
	}
}

//向下移动
void VCAframDomeCurise::OnBnClickedButton5()
{
	if (m_iCruiseType == SENCE_CRUISE_TYPE_TIMER)
	{
		int iCount = m_lst_CuriseInfo.GetItemCount();
		if (iCount <= 1)
		{
			return;
		}

		int iCheck = 0 ;
		for (int i = 0; i < iCount; ++i)
		{		
			if (BST_CHECKED == m_lst_CuriseInfo.GetCheck(i))
			{
				iCheck ++ ;
			}
		}
		if (iCheck > 1)
		{
			//上下操作只支持选中一条
			return ;
		}

		for (int i = iCount - 1; i >= 0; --i)
		{		
			if (m_lst_CuriseInfo.GetItemState(i, LVIS_SELECTED))
			{
				MoveToNewPos(i, i + 1);	
			}
		}
	}
	else if (m_iCruiseType == SENCE_CRUISE_TYPE_TIMERANGE)
	{
		int iCount = m_lst_CuriseTimeInfo.GetItemCount();
		if (iCount <= 1)
		{
			return;
		}

		int iCheck = 0 ;
		for (int i = 0; i < iCount; ++i)
		{		
			if (BST_CHECKED == m_lst_CuriseTimeInfo.GetCheck(i))
			{
				iCheck ++ ;
			}
		}
		if (iCheck > 1)
		{
			//上下操作只支持选中一条
			return ;
		}

		for (int i = iCount - 1; i >= 0; --i)
		{		
			if (m_lst_CuriseTimeInfo.GetItemState(i, LVIS_SELECTED))
			{
				MoveToNewPos(i, i + 1);	
			}
		}
	}
	else
	{
		int iCount = m_lstTimingCruiseByTimeRange.GetItemCount();
		if (iCount <= 1)
		{
			return;
		}

		int iCheck = 0 ;
		for (int i = 0; i < iCount; ++i)
		{		
			if (BST_CHECKED == m_lstTimingCruiseByTimeRange.GetCheck(i))
			{
				iCheck ++ ;
			}
		}
		if (iCheck > 1)
		{
			//上下操作只支持选中一条
			return ;
		}

		for (int i = iCount - 1; i >= 0; --i)
		{		
			if (m_lstTimingCruiseByTimeRange.GetItemState(i, LVIS_SELECTED))
			{
				MoveToNewPos(i, i + 1);	
			}
		}
	}
}

void VCAframDomeCurise::MoveToNewPos( int iOldItemIndex, int iNewItemIndex )
{
	if (m_iCruiseType == SENCE_CRUISE_TYPE_TIMER)
	{
		m_lst_CuriseInfo.GetAndDisplayControlsData();
		if (iOldItemIndex < 0 || iOldItemIndex >= m_lst_CuriseInfo.GetItemCount()
			|| iNewItemIndex < 0 || iNewItemIndex >= m_lst_CuriseInfo.GetItemCount())
		{
			m_lst_CuriseInfo.SetFocus();
			return;
		}

		const int iColCount = m_lst_CuriseInfo.GetHeaderCtrl()->GetItemCount();
		const DWORD_PTR dwData = m_lst_CuriseInfo.GetItemData(iOldItemIndex);

		//选中要移动的行
		CStringArray cstrArrayTexts;
		cstrArrayTexts.SetSize(iColCount);

		for (int i = 0; i < iColCount; i++)
		{
			cstrArrayTexts[i] = m_lst_CuriseInfo.GetItemText(iOldItemIndex, i);
		}	

		BOOL blCheck  =  m_lst_CuriseInfo.GetCheck(iOldItemIndex) ;

		m_lst_CuriseInfo.DeleteItem(iOldItemIndex);
		const int iItem = m_lst_CuriseInfo.InsertItem(iNewItemIndex, cstrArrayTexts[0]);

		if (blCheck)
		{
			m_lst_CuriseInfo.SetCheck(iItem);
		}

		for (int j = 1; j < iColCount; j++)
		{
			m_lst_CuriseInfo.SetItemText(iItem, j, cstrArrayTexts[j]);
		}
		m_lst_CuriseInfo.SetItemData(iItem,dwData);
		m_lst_CuriseInfo.SetItemState(iItem, LVIS_SELECTED, LVIS_SELECTED);

		if (m_iCount == iOldItemIndex)//用户向上操作，从最后一个往上移动
		{
			m_lst_CuriseInfo.SetItemState(m_iCount, 0, LVIS_SELECTED|LVIS_FOCUSED|LVIS_ACTIVATING);
			m_lst_CuriseInfo.SetItemColor(m_iCount,COLOR_CANCEL);
		} 
		else
		{
			if (m_iCount == iItem)//用户向下操作，从倒数第二个移动到最后一个
			{
				m_lst_CuriseInfo.SetItemState(m_iCount,LVIS_SELECTED, LVIS_SELECTED);
				m_lst_CuriseInfo.SetItemColor(m_iCount, COLOR_SET);
			} 
			else
			{
				m_lst_CuriseInfo.SetItemState(m_iCount, 0, LVIS_SELECTED|LVIS_FOCUSED|LVIS_ACTIVATING);
				m_lst_CuriseInfo.SetItemColor(m_iCount, COLOR_CANCEL);
			}
		}

		m_lst_CuriseInfo.SetFocus();
		m_lst_CuriseInfo.MapControlsForSubItems();
		m_lst_CuriseInfo.ShowControls(false);
		m_lst_CuriseInfo.EnsureVisible(iItem,FALSE);
	}
	else if (m_iCruiseType == SENCE_CRUISE_TYPE_TIMERANGE)
	{
		m_lst_CuriseTimeInfo.GetAndDisplayControlsData();
		if (iOldItemIndex < 0 || iOldItemIndex >= m_lst_CuriseTimeInfo.GetItemCount()
			|| iNewItemIndex < 0 || iNewItemIndex >= m_lst_CuriseTimeInfo.GetItemCount())
		{
			m_lst_CuriseTimeInfo.SetFocus();
			return;
		}

		const int iColCount = m_lst_CuriseTimeInfo.GetHeaderCtrl()->GetItemCount();
		const DWORD_PTR dwData = m_lst_CuriseTimeInfo.GetItemData(iOldItemIndex);

		//选中要移动的行
		CStringArray cstrArrayTexts;
		cstrArrayTexts.SetSize(iColCount);

		for (int i = 0; i < iColCount; i++)
		{
			cstrArrayTexts[i] = m_lst_CuriseTimeInfo.GetItemText(iOldItemIndex, i);
		}	

		BOOL blCheck  =  m_lst_CuriseTimeInfo.GetCheck(iOldItemIndex) ;
		m_lst_CuriseTimeInfo.DeleteItem(iOldItemIndex);
		const int iItem = m_lst_CuriseTimeInfo.InsertItem(iNewItemIndex, cstrArrayTexts[0]);

		if (blCheck)
		{
			m_lst_CuriseTimeInfo.SetCheck(iItem);
		}

		for (int j = 1; j < iColCount; j++)
		{
			m_lst_CuriseTimeInfo.SetItemText(iItem, j, cstrArrayTexts[j]);
		}

		m_lst_CuriseTimeInfo.SetItemData(iItem,dwData);
		m_lst_CuriseTimeInfo.SetItemState(iItem, LVIS_SELECTED, LVIS_SELECTED);

		if (m_iCount == iOldItemIndex)
		{
			m_lst_CuriseTimeInfo.SetItemState(m_iCount, 0, LVIS_SELECTED|LVIS_FOCUSED);
			m_lst_CuriseTimeInfo.SetItemColor(m_iCount,COLOR_CANCEL);
		} 
		else
		{
			if (m_iCount == iItem)
			{
				m_lst_CuriseTimeInfo.SetItemState(m_iCount,LVIS_SELECTED,LVIS_FOCUSED);
				m_lst_CuriseTimeInfo.SetItemColor(m_iCount,COLOR_SET);
			} 
			else
			{
				m_lst_CuriseTimeInfo.SetItemState(m_iCount, 0, LVIS_SELECTED|LVIS_FOCUSED);
				m_lst_CuriseTimeInfo.SetItemColor(m_iCount,COLOR_CANCEL);
			}
		}

		m_lst_CuriseTimeInfo.SetFocus();
		m_lst_CuriseTimeInfo.MapControlsForSubItems();
		m_lst_CuriseTimeInfo.ShowControls(FALSE);
		m_lst_CuriseTimeInfo.EnsureVisible(iItem,FALSE);
	}
	else
	{
		m_lstTimingCruiseByTimeRange.GetAndDisplayControlsData();
		if (iOldItemIndex < 0 || iOldItemIndex >= m_lstTimingCruiseByTimeRange.GetItemCount()
			|| iNewItemIndex < 0 || iNewItemIndex >= m_lstTimingCruiseByTimeRange.GetItemCount())
		{
			m_lstTimingCruiseByTimeRange.SetFocus();
			return;
		}

		const int iColCount = m_lstTimingCruiseByTimeRange.GetHeaderCtrl()->GetItemCount();
		const DWORD_PTR dwData = m_lstTimingCruiseByTimeRange.GetItemData(iOldItemIndex);

		//选中要移动的行
		CStringArray cstrArrayTexts;
		cstrArrayTexts.SetSize(iColCount);

		for (int i = 0; i < iColCount; i++)
		{
			cstrArrayTexts[i] = m_lstTimingCruiseByTimeRange.GetItemText(iOldItemIndex, i);
		}	

		BOOL blCheck  =  m_lstTimingCruiseByTimeRange.GetCheck(iOldItemIndex) ;
		m_lstTimingCruiseByTimeRange.DeleteItem(iOldItemIndex);
		const int iItem = m_lstTimingCruiseByTimeRange.InsertItem(iNewItemIndex, cstrArrayTexts[0]);

		if (blCheck)
		{
			m_lstTimingCruiseByTimeRange.SetCheck(iItem);
		}

		for (int j = 1; j < iColCount; j++)
		{
			m_lstTimingCruiseByTimeRange.SetItemText(iItem, j, cstrArrayTexts[j]);
		}

		m_lstTimingCruiseByTimeRange.SetItemData(iItem,dwData);
		m_lstTimingCruiseByTimeRange.SetItemState(iItem, LVIS_SELECTED, LVIS_SELECTED);

		if (m_iCount == iOldItemIndex)
		{
			m_lstTimingCruiseByTimeRange.SetItemState(m_iCount, 0, LVIS_SELECTED|LVIS_FOCUSED);
			m_lstTimingCruiseByTimeRange.SetItemColor(m_iCount,COLOR_CANCEL);
		} 
		else
		{
			if (m_iCount == iItem)
			{
				m_lstTimingCruiseByTimeRange.SetItemState(m_iCount,LVIS_SELECTED,LVIS_FOCUSED);
				m_lstTimingCruiseByTimeRange.SetItemColor(m_iCount,COLOR_SET);
			} 
			else
			{
				m_lstTimingCruiseByTimeRange.SetItemState(m_iCount, 0, LVIS_SELECTED|LVIS_FOCUSED);
				m_lstTimingCruiseByTimeRange.SetItemColor(m_iCount,COLOR_CANCEL);
			}
		}

		m_lstTimingCruiseByTimeRange.SetFocus();
		m_lstTimingCruiseByTimeRange.MapControlsForSubItems();
		m_lstTimingCruiseByTimeRange.ShowControls(FALSE);
		m_lstTimingCruiseByTimeRange.EnsureVisible(iItem,FALSE);
	}
}

void VCAframDomeCurise::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	if (_iChannelNo < 0)
	{
		m_iChannelNO = 0;
	}
	else
	{
		m_iChannelNO = _iChannelNo;
	}
	if (_iStreamNo < 0)
	{
		m_iStreamNO = 0;
	}
	else
	{
		m_iStreamNO = _iStreamNo;
	}

}

LRESULT VCAframDomeCurise::OnRecSelectMessage( WPARAM wParam,LPARAM lParam )
{
	int iType = (int)wParam;
	int iRow  = (int)lParam;
	CString strType = IntToCString(iType);
	vector<AnyScene>::iterator iter ;
	for(iter = m_vecAnyScene.begin() ;iter != m_vecAnyScene.end() ;iter++)
	{
		if(iter->iSceneID == iType)
		{
			LVITEM item;
			memset(&item, 0, sizeof(LVITEM));
			item.mask = LVIF_TEXT;
			item.iItem = iRow;
			//场景名称
			item.iSubItem = 2;
			item.pszText = iter->cSceneName;
			if(m_iCruiseType == SENCE_CRUISE_TYPE_TIMER)
			{
				m_lst_CuriseInfo.SetItem(&item);
				m_lst_CuriseInfo.SetItemText(iRow, 1, strType);
			}
			else if(m_iCruiseType == SENCE_CRUISE_TYPE_TIMERANGE)
			{
				m_lst_CuriseTimeInfo.SetItem(&item);
				m_lst_CuriseTimeInfo.SetItemText(iRow, 1, strType);
			}
			else
			{
				m_lstTimingCruiseByTimeRange.SetItem(&item);
				m_lstTimingCruiseByTimeRange.SetItemText(iRow, 1, strType);
			}
		}
	}
	return TRUE ;

}

void VCAframDomeCurise::OnNMRClickListCurise( NMHDR *pNMHDR, LRESULT *pResult )
{

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	m_lst_CuriseInfo.SetItemState(m_iCount, 0, LVIS_SELECTED|LVIS_FOCUSED);
	m_lst_CuriseInfo.SetItemColor(m_iCount, COLOR_CANCEL);
}

void VCAframDomeCurise::OnNMRClickListTimeCurise( NMHDR *pNMHDR, LRESULT *pResult )
{

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	m_lst_CuriseTimeInfo.SetItemState(m_iCount , 0, LVIS_SELECTED|LVIS_FOCUSED);
	m_lst_CuriseTimeInfo.SetItemColor(m_iCount ,COLOR_CANCEL);
	*pResult = 0;
}

void VCAframDomeCurise::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);
	if(bShow)
	{
		int iType = -1;
		int iReturn = -1;
		int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_SENCE_CRUISE_TYPE, m_iChannelNO, &iType, sizeof(int), &iReturn);
		if (0 != iRet)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig[NET_CLIENT_SENCE_CRUISE_TYPE]");
			return;
		}
		if(iType == SENCE_CRUISE_TYPE_TIMERANGE)
		{
			m_iCruiseType = SENCE_CRUISE_TYPE_TIMERANGE;
			CheckRadioButton(IDC_RADIO_CURISE_TIMER, IDC_RADIO_TIMING_CURISE_BY_TIMERANGE, IDC_RADIO_CURISE_TIMERANGE);
			m_lst_CuriseTimeInfo.ShowWindow(SW_SHOW);
			OnBnClickedRadioCuriseTimerange();
		}
		else if (iType == SENCE_CRUISE_TYPE_TIMING_BY_TIMERANGE)
		{
			m_iCruiseType = SENCE_CRUISE_TYPE_TIMING_BY_TIMERANGE;
			CheckRadioButton(IDC_RADIO_CURISE_TIMER, IDC_RADIO_TIMING_CURISE_BY_TIMERANGE, IDC_RADIO_TIMING_CURISE_BY_TIMERANGE);
			m_lstTimingCruiseByTimeRange.ShowWindow(SW_SHOW);
			OnBnClickedRadioTimingCuriseByTimerange();
		}
		else
		{
			m_iCruiseType = SENCE_CRUISE_TYPE_TIMER;
			CheckRadioButton(IDC_RADIO_CURISE_TIMER, IDC_RADIO_TIMING_CURISE_BY_TIMERANGE, IDC_RADIO_CURISE_TIMER);
			m_lst_CuriseInfo.ShowWindow(SW_SHOW);
			OnBnClickedRadioCuriseTimer();	
		}
	}
	// TODO: Add your message handler code here
}

//时间段内的定时巡航
void VCAframDomeCurise::OnBnClickedRadioTimingCuriseByTimerange()
{
	m_iCruiseType = SENCE_CRUISE_TYPE_TIMING_BY_TIMERANGE;
	m_lst_CuriseInfo.ShowWindow(SW_HIDE);
	m_lst_CuriseTimeInfo.ShowWindow(SW_HIDE);
	m_lstTimingCruiseByTimeRange.DeleteAllItems();
	m_lstTimingCruiseByTimeRange.ResetContent();

	m_vecTimingCruiseByTimeRange.clear();
	SceneTimeRangeCruise sTimeRangeCruise = {0};
	int iReturnByteEX = 0;
	int iRet = -1;
	for(int j = 0; j < MAX_SCENE_NUM ;j++)
	{
		sTimeRangeCruise.iCruiseID = j;
		iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_TIMINGCRUISE_BY_TIMERANGE, m_iChannelNO
									, &sTimeRangeCruise, sizeof(sTimeRangeCruise), &iReturnByteEX);
		if (sTimeRangeCruise.iEnable != 0)//使能
		{
			m_vecTimingCruiseByTimeRange.push_back(sTimeRangeCruise);
		}
		else
		{
			continue;
		}
	}

	if (m_vecTimingCruiseByTimeRange.size() == 0)
	{
		m_lstTimingCruiseByTimeRange.ShowControls(FALSE);
		m_lstTimingCruiseByTimeRange.Invalidate();
	}
	m_lstTimingCruiseByTimeRange.ShowWindow(SW_SHOW);
	m_lstTimingCruiseByTimeRange.Invalidate(TRUE);

	if(m_vecTimingCruiseByTimeRange.size() != 0 && m_bTimingCuriseByTimeRange == false)//如果当前没有模版，就不需要插入
	{
		//这三个函数位置不可变，因为要保持按时间段巡航的comboxid和定时巡航保持一致
		m_lstTimingCruiseByTimeRange.SetItemControl(DATECTRL, E_TIMECRUISE_FOUTH);
		m_lstTimingCruiseByTimeRange.SetItemControl(COMBOBOX, E_TIMECRUISE_SECOND);//添加combox控件 ，此函数要在AddToControlsData（）函数之前调用
		m_lstTimingCruiseByTimeRange.SetItemControl(DATECTRL, E_TIMECRUISE_FIFTH);
		m_lstTimingCruiseByTimeRange.SetItemControl(EDITBOX, E_TIMINGCRUISEBYTIMERANGE_SIXTH);
		m_lst_CuriseInfo.SetLimitTextLength(E_TIMINGCRUISEBYTIMERANGE_SIXTH, LEN_16);
		m_bTimingCuriseByTimeRange = true ;
	}
	else if (m_vecTimingCruiseByTimeRange.size() == 0)
	{
		m_iCruiseType = SENCE_CRUISE_TYPE_TIMING_BY_TIMERANGE ;
		m_bTimingCuriseByTimeRange = true ;
		return ;
	}

	//获取时间段巡航的信息
	AnyScene sScene = {0};
	int iReturnByte ;
	m_vecAnyScene.clear();
	for (int i = 0; i < MAX_SCENE_NUM; i++)//循环0-15个场景
	{
		sScene.iSceneID = i;
		NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_ANYSCENE, m_iChannelNO, &sScene, sizeof(AnyScene), &iReturnByte);
		m_vecAnyScene.push_back(sScene);
		//给使能的场景编号，插入到combox中去
		m_lstTimingCruiseByTimeRange.AddToControlsData(E_TIMECRUISE_SECOND,IntToStr(i+1).c_str());//1 代表第一列 
	}

	//将获取的到信息插入到list contrl中
	int iCount = (int)m_vecTimingCruiseByTimeRange.size();
	for(int i = 0;i < iCount; i++)
	{
		m_lstTimingCruiseByTimeRange.InsertItem(i,_T(""));
		LVITEM item;
		memset(&item, 0, sizeof(LVITEM));
		item.mask = LVIF_TEXT;
		item.iItem = i;
		CString cstrTmp = "";

		//序号
		item.iSubItem = E_TIMECRUISE_FIRST;
		cstrTmp = IntToStr(i+1).c_str() ;
		item.pszText = (LPSTR)(LPCTSTR)cstrTmp;
		m_lstTimingCruiseByTimeRange.SetItem(&item);

		item.iSubItem = E_TIMECRUISE_SECOND;
		CString strSceneid = IntToCString(m_vecTimingCruiseByTimeRange[i].iSceneID +1);
		int iSceneId = m_vecSceneTimeRangeCruise[i].iSceneID ;
		item.pszText = (LPSTR)(LPCTSTR)(strSceneid);
		m_lstTimingCruiseByTimeRange.SetItem(&item);
		m_lstTimingCruiseByTimeRange.SetItemData(i,m_vecTimingCruiseByTimeRange[i].iSceneID);

		//场景名称
		item.iSubItem = E_TIMECRUISE_THIRD;
		if (iSceneId >= 0 && iSceneId < MAX_SCENE_NUM)
		{
			item.pszText = (LPSTR)(LPCTSTR)m_vecAnyScene[iSceneId].cSceneName;
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "[VCAframDomeCurise::OnBnClickedRadioTimingCuriseByTimerange]invalid iScenceId = %d", iSceneId);
		}
		m_lstTimingCruiseByTimeRange.SetItem(&item);

		CString strStartTime = "" ;
		strStartTime.Format(_T("%02d:%02d"), m_vecTimingCruiseByTimeRange[i].iBeginHour, m_vecTimingCruiseByTimeRange[i].iBeginMinute);
		//开始时间
		item.iSubItem = E_TIMECRUISE_FOUTH;
		item.pszText = (LPSTR)(LPCTSTR)strStartTime;
		m_lstTimingCruiseByTimeRange.SetItem(&item);

		CString strEndTime = "";
		strEndTime.Format(_T("%02d:%02d"), m_vecTimingCruiseByTimeRange[i].iEndHour, m_vecTimingCruiseByTimeRange[i].iEndMinute);
		//结束时间
		item.iSubItem = E_TIMECRUISE_FIFTH;
		item.pszText = (LPSTR)(LPCTSTR)strEndTime;
		m_lstTimingCruiseByTimeRange.SetItem(&item);
	}
	//当前行被取消
	m_lstTimingCruiseByTimeRange.SetItemState(m_iCount, 0, LVIS_SELECTED|LVIS_FOCUSED);
	m_lstTimingCruiseByTimeRange.SetItemColor(m_iCount, COLOR_CANCEL);

	int iTotal = m_lstTimingCruiseByTimeRange.GetItemCount();
	if (iTotal > 0)
	{
		m_lstTimingCruiseByTimeRange.MoveControlToFocusItem(0);
	} 

	m_iCruiseType = SENCE_CRUISE_TYPE_TIMING_BY_TIMERANGE ;
	m_bTimingCuriseByTimeRange = true ;
}

void VCAframDomeCurise::OnNMRClickListTimingCuriseByTimerange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	m_lstTimingCruiseByTimeRange.SetItemState(m_iCount , 0, LVIS_SELECTED|LVIS_FOCUSED);
	m_lstTimingCruiseByTimeRange.SetItemColor(m_iCount ,COLOR_CANCEL);
	*pResult = 0;
}

void VCAframDomeCurise::OnHdnBegintrackListCurise(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (m_iCruiseType == SENCE_CRUISE_TYPE_TIMER)
	{
		int iCount = m_lst_CuriseInfo.GetItemCount();
		if (iCount > 0)
		{
			m_lst_CuriseInfo.GetAndDisplayControlsData();
		}
		m_lst_CuriseInfo.MoveControlToFocusItem(-1);
	}
	else if (m_iCruiseType == SENCE_CRUISE_TYPE_TIMERANGE)
	{
		int iCount = m_lst_CuriseTimeInfo.GetItemCount();
		if (iCount > 0)
		{
			m_lst_CuriseTimeInfo.GetAndDisplayControlsData();
		}
		m_lst_CuriseTimeInfo.MoveControlToFocusItem(-1);
	}
	else if (m_iCruiseType == SENCE_CRUISE_TYPE_TIMING_BY_TIMERANGE)
	{
		int iCount = m_lstTimingCruiseByTimeRange.GetItemCount();
		if (iCount > 0)
		{
			m_lstTimingCruiseByTimeRange.GetAndDisplayControlsData();
		}
		m_lstTimingCruiseByTimeRange.MoveControlToFocusItem(-1);
	}

	*pResult = 0;
}
