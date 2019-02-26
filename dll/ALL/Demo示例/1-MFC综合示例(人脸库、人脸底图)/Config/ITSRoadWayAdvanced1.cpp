// ITSRoadWayAdvanced1.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ITSRoadWayAdvanced1.h"


// CLS_ITSRoadWayAdvanced1 对话框

IMPLEMENT_DYNAMIC(CLS_ITSRoadWayAdvanced1, CDialog)

CLS_ITSRoadWayAdvanced1::CLS_ITSRoadWayAdvanced1(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ITSRoadWayAdvanced1::IDD, pParent)
{
	memset(m_usRangeTimeStartH, 0, sizeof(m_usRangeTimeStartH));
	memset(m_usRangeTimeStartM, 0, sizeof(m_usRangeTimeStartM));
	memset(m_usRangeTimeEndH, 0, sizeof(m_usRangeTimeEndH));
	memset(m_usRangeTimeEndM, 0, sizeof(m_usRangeTimeEndM));

	//memset(m_edtPointx, 0, sizeof(m_edtPointx));
	//memset(m_edtPointy, 0, sizeof(m_edtPointy));
}

CLS_ITSRoadWayAdvanced1::~CLS_ITSRoadWayAdvanced1()
{
}

void CLS_ITSRoadWayAdvanced1::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_PRESET, m_cboPreset);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_dtcFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_dtcTo);
	DDX_Control(pDX, IDC_COMBO_TIMERANGE, m_cboTimeRange);
	DDX_Control(pDX, IDC_COMBO_AREA, m_cboArea);
	DDX_Control(pDX, IDC_EDT_PARKTIME, m_edtParkTime);
	DDX_Control(pDX, IDC_EDIT_SENSITIVITY, m_edtSensitivity);
	DDX_Control(pDX, IDC_EDT_ILLEGALPARKTIME, m_edtTime);

	DDX_Control(pDX, IDC_EDT_POINT1_X, m_edtPointx[0]);
	DDX_Control(pDX, IDC_EDT_POINT1_Y, m_edtPointy[0]);
	DDX_Control(pDX, IDC_EDT_POINT2_X, m_edtPointx[1]);
	DDX_Control(pDX, IDC_EDT_POINT2_Y, m_edtPointy[1]);
	DDX_Control(pDX, IDC_EDT_POINT3_X, m_edtPointx[2]);
	DDX_Control(pDX, IDC_EDT_POINT3_Y, m_edtPointy[2]);
	DDX_Control(pDX, IDC_EDT_POINT4_X, m_edtPointx[3]);
	DDX_Control(pDX, IDC_EDT_POINT4_Y, m_edtPointy[3]);
	DDX_Control(pDX, IDC_CBO_RULE_ID, m_cboRuleId);
	DDX_Control(pDX, IDC_CBO_CAR_TYPE, m_cboCarType);
	DDX_Control(pDX, IDC_CBO_ROADWAYID, m_cboRoadwayID);
	DDX_Control(pDX, IDC_CHK_REGION_EN, m_chkRegionEn);
	DDX_Control(pDX, IDC_CHK_EVENT_ENABLE, m_chkEventCheckEn);
	DDX_Control(pDX, IDC_CHECK_ROADWAYNO, m_chkRoadwayNo);
}


BEGIN_MESSAGE_MAP(CLS_ITSRoadWayAdvanced1, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_SET_ILLEGALPARK, &CLS_ITSRoadWayAdvanced1::OnBnClickedBtnSetIllegalpark)
	ON_BN_CLICKED(IDC_BTN_SET_CAR_PERMI, &CLS_ITSRoadWayAdvanced1::OnBnClickedBtnSetCarPermi)
	ON_CBN_SELCHANGE(IDC_CBO_ROADWAYID, &CLS_ITSRoadWayAdvanced1::OnCbnSelchangeCboRoadwayid)
	ON_CBN_SELCHANGE(IDC_CBO_CAR_TYPE, &CLS_ITSRoadWayAdvanced1::OnCbnSelchangeCboCarType)
	ON_BN_CLICKED(IDC_CHECK_ROADWAYNO, &CLS_ITSRoadWayAdvanced1::OnBnClickedCheckRoadwayno)
END_MESSAGE_MAP()


// CLS_ITSRoadWayAdvanced1 消息处理程序

BOOL CLS_ITSRoadWayAdvanced1::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	for (int i=0; i<4; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboRoadwayID.AddString(strNo);
	}
	m_cboRoadwayID.SetCurSel(0);

	for (int i=0; i<8; i++)
	{
		CString strNo;
		strNo.Format("%d", i);
		m_cboPreset.AddString(strNo);
	}
	m_cboPreset.SetCurSel(0);
	for (int i=0; i<4; i++)
	{
		CString strNo;
		strNo.Format("%d", i);
		m_cboArea.AddString(strNo);
		m_cboTimeRange.AddString(strNo);
	}
	m_cboArea.SetCurSel(0);
	m_cboTimeRange.SetCurSel(0);

	m_edtTime.SetLimitText(10);
	for (int i=0; i<4; i++)
	{
		m_edtPointx[i].SetLimitText(6);
		m_edtPointy[i].SetLimitText(6);
	}

	m_edtParkTime.SetLimitText(10);
	m_edtSensitivity.SetLimitText(10);

	for (int i = 0; i < 10; i++)
	{
		CString strRuleId;
		strRuleId.Format("%d", i);
		InsertString(m_cboRuleId, i, strRuleId);
	}
	
	//0-reserve 1-small car 2-big car
	for (int i=0; i<3; i++)
	{
		CString strCarType;
		strCarType.Format("%d",i);
		m_cboCarType.AddString(strCarType);
	}
	UI_UpdateDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CLS_ITSRoadWayAdvanced1::UI_UpdateRoadway()
{
	if (m_iLogonID < 0)
		return FALSE;
	int iRoadwayID = m_cboRoadwayID.GetCurSel();
	TITSRoadwayInfo pa = {0};
	pa.iRoadwayID = iRoadwayID;
	int iRet = NetClient_GetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_GET_ENABLE, &pa, sizeof(pa));
	if (0 == iRet)
	{
		m_chkRoadwayNo.SetCheck(pa.iEnable?BST_CHECKED:BST_UNCHECKED);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	}
	return TRUE;
}

void CLS_ITSRoadWayAdvanced1::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	UI_UpdateDialog();
	UI_UpdateRoadway();
}

void CLS_ITSRoadWayAdvanced1::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
	
}

void CLS_ITSRoadWayAdvanced1::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STC_ROADWAYID,IDS_CONFIG_ECOP_ROADWAYID);
	SetDlgItemTextEx(IDC_STC_ILLEGALPARK,IDS_CONFIG_ITS_ILLEGALPARK);
	SetDlgItemTextEx(IDC_STC_PRESET,IDS_CONFIG_ITS_ILLEGALPARK_PRESET);
	SetDlgItemTextEx(IDC_STC_AREA,IDS_CONFIG_ITS_ILLEGALPARK_AREA);
	SetDlgItemTextEx(IDC_STC_ILLEGALPARKTIME,IDS_CONFIG_ITS_ILLEGALPARK_TIME);
	SetDlgItemTextEx(IDC_STC_TIMERANGE,IDS_ITS_COMMON1);
	SetDlgItemTextEx(IDC_STC_TIMEFROM,IDS_CONFIG_ITS_ILLEGALPARK_FROM);
	SetDlgItemTextEx(IDC_STC_TIMETO,IDS_CONFIG_ITS_ILLEGALPARK_TO);
	SetDlgItemTextEx(IDC_STC_POINT1,IDS_CONFIG_ITS_ILLEGALPARK_POINT1);
	SetDlgItemTextEx(IDC_STC_POINT2,IDS_CONFIG_ITS_ILLEGALPARK_POINT2);
	SetDlgItemTextEx(IDC_STC_POINT3,IDS_CONFIG_ITS_ILLEGALPARK_POINT3);
	SetDlgItemTextEx(IDC_STC_POINT4,IDS_CONFIG_ITS_ILLEGALPARK_POINT4);
	SetDlgItemTextEx(IDC_STC_PARKTIME,IDS_CONFIG_ITS_ILLEGALPARK_PARKTIME);
	SetDlgItemTextEx(IDC_STC_SENSITIVITY,IDS_CONFIG_ITS_ILLEGALPARK_SENSITIVITY);
	SetDlgItemTextEx(IDC_CHECK_ROADWAYNO,IDS_CONFIG_ITS_ROADWAY_ENABLE);

	SetDlgItemTextEx(IDC_STC_REGION_NAME,IDS_ITS_REGION_NAME);
	SetDlgItemTextEx(IDC_STC_RULE_ID,IDS_ITS_RULE_ID);
	SetDlgItemTextEx(IDC_CHK_REGION_EN,IDS_ITS_REGION_EN);
	SetDlgItemTextEx(IDC_CHK_EVENT_ENABLE,IDS_ITS_EVENT_ENABLE);
	SetDlgItemTextEx(IDC_BTN_SET_ILLEGALPARK,IDS_SET);
	SetDlgItemTextEx(IDC_STC_CAR_PEIMI,IDS_ITS_CAR_PEIMI);
	SetDlgItemTextEx(IDC_STC_CAR_TYPE,IDS_ITS_TYPE);
	SetDlgItemTextEx(IDC_STC_CAR_PEIMI_DIGIT,IDS_ITS_CAR_PEIMI);
	SetDlgItemTextEx(IDC_BTN_SET_CAR_PERMI,IDS_SET);
	UI_UpdateIllegalpark();
	UI_UpdateCarPermi();
}

void CLS_ITSRoadWayAdvanced1::GetCoorEditShow( POINT *_ptPoint, int _iN0, int flag )
{
	if(_iN0 < 0 || _iN0 > 6)
	{
		return;
	}
	if(0 == flag)
	{
		switch(_iN0)
		{
		case 1:
			{
				_ptPoint->x = GetDlgItemInt(IDC_EDT_POINT1_X);
				_ptPoint->y = GetDlgItemInt(IDC_EDT_POINT1_Y);
				break;
			}
		case 2:
			{
				_ptPoint->x = GetDlgItemInt(IDC_EDT_POINT2_X);
				_ptPoint->y = GetDlgItemInt(IDC_EDT_POINT2_Y);
				break;
			}
		case 3:
			{
				_ptPoint->x = GetDlgItemInt(IDC_EDT_POINT3_X);
				_ptPoint->y = GetDlgItemInt(IDC_EDT_POINT3_Y);
				break;
			}
		case 4:
			{
				_ptPoint->x = GetDlgItemInt(IDC_EDT_POINT4_X);
				_ptPoint->y = GetDlgItemInt(IDC_EDT_POINT4_Y);
				break;
			}
		case 5:   //设置所有
			{
				_ptPoint[0].x = GetDlgItemInt(IDC_EDT_POINT1_X);
				_ptPoint[0].y = GetDlgItemInt(IDC_EDT_POINT1_Y);
				_ptPoint[1].x = GetDlgItemInt(IDC_EDT_POINT2_X);
				_ptPoint[1].y = GetDlgItemInt(IDC_EDT_POINT2_Y);
				_ptPoint[2].x = GetDlgItemInt(IDC_EDT_POINT3_X);
				_ptPoint[2].y = GetDlgItemInt(IDC_EDT_POINT3_Y);
				_ptPoint[3].x = GetDlgItemInt(IDC_EDT_POINT4_X);
				_ptPoint[3].y = GetDlgItemInt(IDC_EDT_POINT4_Y);
				break;
			}
		default:
			break;
		}
	}
}

void CLS_ITSRoadWayAdvanced1::OnBnClickedBtnSetIllegalpark()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	if (m_cboPreset.GetCurSel() == -1)
	{
		return;
	}
	if (-1 == GetDlgItemInt(IDC_EDT_ILLEGALPARKTIME))
	{
		MessageBox("Illegal parktime must be digit","Info",MB_OK);
		return;
	}
	else if (GetDlgItemInt(IDC_EDT_ILLEGALPARKTIME) > 3600 && GetDlgItemInt(IDC_EDT_ILLEGALPARKTIME) < 0)
	{
		MessageBox("Illegal parktime should  between 0 and 3600","Info",MB_OK);
		return;		
	}
	//-------20120604
	//获得开始和结束时间，并判断是否合法（结束时间大于或等于开始时间）
	int iTimeRange = 0;
	int iRangeTimeStartH = 0;
	int iRangeTimeStartM = 0;
	int iRangeTimeEndH = 0;
	int iRangeTimeEndM = 0;
	CTime cTime;
	m_dtcFrom.GetTime(cTime);
	iRangeTimeStartH = cTime.GetHour();
	iRangeTimeStartM = cTime.GetMinute();
	m_dtcTo.GetTime(cTime);
	iRangeTimeEndH = cTime.GetHour();
	iRangeTimeEndM = cTime.GetMinute();
	if(iRangeTimeStartH > iRangeTimeEndH)
	{
		MessageBox("TimeRange StartTime should not greater than EndTime!","Info",MB_OK);
		return;
	}
	else if(iRangeTimeStartH == iRangeTimeEndH)
	{
		if(iRangeTimeStartM > iRangeTimeEndM)
		{
			MessageBox("TimeRange StartTime should not greater than EndTime!","Info",MB_OK);
			return;
		}
	}
	//保存所有时间数据
	ITS_IllegalPark tITSIllegalPark;
	memset(&tITSIllegalPark, 0, sizeof(ITS_IllegalPark));
	int iCurSegment = m_cboTimeRange.GetCurSel();
	int iCurPresetNo = m_cboPreset.GetCurSel();
	int iCurArea = m_cboArea.GetCurSel();
	for(int iPreset = 0; iPreset < 8; iPreset++ ) 
	{
		for(int iArea = 0; iArea < 4; iArea++)
		{
			tITSIllegalPark.iAreaNo = iArea;
			tITSIllegalPark.iPresetNo = iPreset;
			int iRet = NetClient_GetITSExtraInfo( m_iLogonID, ITS_ILLEGALPARK_CMD_GET,
				NULL, &tITSIllegalPark, sizeof(ITS_IllegalPark));
			for(int iSegment = 0; iSegment < 4; iSegment++)
			{
				m_usRangeTimeStartH[iPreset][iArea] = (((unsigned int)tITSIllegalPark.iTimeRange[iSegment]>>24) & 0x000000ff);
				m_usRangeTimeStartM[iPreset][iArea] = (((unsigned int)tITSIllegalPark.iTimeRange[iSegment]>>16) & 0x000000ff);
				m_usRangeTimeEndH[iPreset][iArea] =  (((unsigned int)tITSIllegalPark.iTimeRange[iSegment]>>8) & 0x000000ff);
				m_usRangeTimeEndM[iPreset][iArea] = (((unsigned int)tITSIllegalPark.iTimeRange[iSegment]) & 0x000000ff);
				if(0 == m_usRangeTimeStartH[iPreset][iArea] && 0 == m_usRangeTimeStartM[iPreset][iArea] &&
					0 == m_usRangeTimeEndH[iPreset][iArea] && 0 == m_usRangeTimeEndM[iPreset][iArea])
				{
					m_usRangeTimeStartH[iPreset][iArea] = 24;
					m_usRangeTimeStartM[iPreset][iArea] = 60;
					m_usRangeTimeEndH[iPreset][iArea] = 24;
					m_usRangeTimeEndM[iPreset][iArea] = 60;
				}
				if(!(m_usRangeTimeStartH[iPreset][iArea]*60+m_usRangeTimeStartM[iPreset][iArea] >= iRangeTimeEndH*60+iRangeTimeEndM
					|| iRangeTimeStartH*60+iRangeTimeStartM >= m_usRangeTimeEndH[iPreset][iArea]*60+m_usRangeTimeEndM[iPreset][iArea]))
				{
					if(iPreset != iCurPresetNo)
					{
						MessageBox("TimeRange  StartTime or EndTime should not repeat with other presets!","Info",MB_OK);
						return ;
					}

					if(iArea == iCurArea && iSegment != iCurSegment)
					{
						MessageBox("TimeRange  StartTime or EndTime should not repeat with other segments!","Info",MB_OK);
						return ;
					}
				}
			}
		}
	}
	//不清空内容，因为要保留同一区域内的其他时间段数据
	//memset(&tITSIllegalPark, 0, sizeof(ITS_IllegalPark));
	tITSIllegalPark.iAreaNo = m_cboArea.GetCurSel();
	tITSIllegalPark.iPresetNo = m_cboPreset.GetCurSel();
	//先获得原来的，再把当前选择的时间段做设置
	int iRet = NetClient_GetITSExtraInfo( m_iLogonID, ITS_ILLEGALPARK_CMD_GET,
		NULL, &tITSIllegalPark, sizeof(ITS_IllegalPark));

	tITSIllegalPark.iIllegalParkTime = GetDlgItemInt(IDC_EDT_ILLEGALPARKTIME);
	tITSIllegalPark.iTimeRange[iCurSegment] = ((iRangeTimeStartH<<24) & 0xff000000) |   //开始小时放在int类型24~31位
		((iRangeTimeStartM<<16) & 0x00ff0000) | //开始分钟放在int类型16~23位
		((iRangeTimeEndH<<8) & 0x0000ff00) |                  //结束小时放在int类型8~15位
		(iRangeTimeEndM&0x000000ff);                          //结束分钟放在int类型0~7位
	GetCoorEditShow(tITSIllegalPark.arrPTArea, 5, 0);           //把界面上坐标数据写入tITSIllegalPark.arrPTArea数组
	tITSIllegalPark.iCheckParkTime = GetDlgItemInt(IDC_EDT_ILLEGALPARKTIME);
	if(tITSIllegalPark.iCheckParkTime < 1)
	{
		MessageBox("you can only fill in CheckParkTime(integer) bigger than 0", "warning", MB_OK);
		return;
	}
	tITSIllegalPark.iSensitivity = GetDlgItemInt(IDC_EDIT_SENSITIVITY);
	if(tITSIllegalPark.iSensitivity < 0 || tITSIllegalPark.iSensitivity > 2)
	{
		MessageBox("you can only fill in Sensitivity with 0 1 2", "warning", MB_OK);
		return;
	}
	char cTmpRegion[LEN_32] = {0};
	GetDlgItemText(IDC_EDT_REGION_NAME, cTmpRegion, LEN_32);
	memcpy(tITSIllegalPark.cAreaName, cTmpRegion, LEN_32);
	tITSIllegalPark.iEnable = m_chkRegionEn.GetCheck();
	tITSIllegalPark.iRuleID = m_cboRuleId.GetCurSel();
	tITSIllegalPark.iValid = m_chkEventCheckEn.GetCheck();
	iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_ILLEGALPARK_CMD_SET,NULL, &tITSIllegalPark, sizeof(ITS_IllegalPark));
	if(iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_ILLEGALPARK_CMD_SET](%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_ILLEGALPARK_CMD_SET] (%d) error(%d)", m_iLogonID, GetLastError());
	}
}

void CLS_ITSRoadWayAdvanced1::UI_UpdateIllegalpark()
{
	if (m_iLogonID < 0)
		return;

	ITS_IllegalPark tITSIllegalPark;
	memset(&tITSIllegalPark, 0, sizeof(ITS_IllegalPark));

	tITSIllegalPark.iPresetNo = m_cboPreset.GetCurSel();
	int iAreaNo =  m_cboArea.GetCurSel();
	tITSIllegalPark.iAreaNo = iAreaNo;
	int iRet = NetClient_GetITSExtraInfo( m_iLogonID, ITS_ILLEGALPARK_CMD_GET, NULL, &tITSIllegalPark, sizeof(ITS_IllegalPark));
	if(iRet == 0)
	{
		
		SetDlgItemInt(IDC_EDT_ILLEGALPARKTIME, tITSIllegalPark.iIllegalParkTime);
		if (iAreaNo >=  MAX_TIMESEGMENT)
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_ILLEGALPARK_CMD_GET] iAreaNo >=  MAX_TIMESEGMENT");
			return;
		}
		int iStartHour = tITSIllegalPark.iTimeRange[iAreaNo]>>24 & 0xFF;
		int iStartMinute = tITSIllegalPark.iTimeRange[iAreaNo]>>16 & 0xFF;

		int iEndHour = tITSIllegalPark.iTimeRange[iAreaNo]>>8 & 0xFF;
		int iEndMinute = tITSIllegalPark.iTimeRange[iAreaNo] & 0xFF;

		SYSTEMTIME stStartTime;        //定义一个系统时间类型的变量
		stStartTime.wHour = iStartHour;
		stStartTime.wMinute = iStartMinute;
		//CTime ctStartTime = CTime(stStartTime);   //定义CTime对象并赋值给它
		m_dtcFrom.SetTime(&stStartTime);

		SYSTEMTIME stEndTime;        //定义一个系统时间类型的变量
		stEndTime.wHour = iEndHour;
		stEndTime.wMinute = iEndMinute;
		//CTime ctEndTime(stEndTime);        //定义CTime对象并赋值给它
		m_dtcFrom.SetTime(&stEndTime);

		//char cArea[LEN_256]; //baoliu
		//memset(cArea, 0, sizeof(cArea));
		//sprintf(cArea, "%d:%d,%d:%d,%d:%d,%d:%d", 
		//	tITSIllegalPark.arrPTArea[0].x, tITSIllegalPark.arrPTArea[0].y,
		//	tITSIllegalPark.arrPTArea[1].x, tITSIllegalPark.arrPTArea[1].y,
		//	tITSIllegalPark.arrPTArea[2].x, tITSIllegalPark.arrPTArea[2].y,
		//	tITSIllegalPark.arrPTArea[3].x, tITSIllegalPark.arrPTArea[3].y
		//	);
		SetDlgItemInt(IDC_EDT_POINT1_X, tITSIllegalPark.arrPTArea[0].x);
		SetDlgItemInt(IDC_EDT_POINT1_Y, tITSIllegalPark.arrPTArea[0].y);
		SetDlgItemInt(IDC_EDT_POINT2_X, tITSIllegalPark.arrPTArea[1].x);
		SetDlgItemInt(IDC_EDT_POINT2_Y, tITSIllegalPark.arrPTArea[1].y);
		SetDlgItemInt(IDC_EDT_POINT3_X, tITSIllegalPark.arrPTArea[2].x);
		SetDlgItemInt(IDC_EDT_POINT3_Y, tITSIllegalPark.arrPTArea[2].y);
		SetDlgItemInt(IDC_EDT_POINT4_X, tITSIllegalPark.arrPTArea[3].x);
		SetDlgItemInt(IDC_EDT_POINT4_Y, tITSIllegalPark.arrPTArea[3].y);

		SetDlgItemInt(IDC_EDT_PARKTIME, tITSIllegalPark.iCheckParkTime);
		SetDlgItemInt(IDC_EDIT_SENSITIVITY, tITSIllegalPark.iSensitivity);
		SetDlgItemText(IDC_EDT_REGION_NAME, tITSIllegalPark.cAreaName);
		m_chkRegionEn.SetCheck(tITSIllegalPark.iEnable);
		m_cboRuleId.SetCurSel(tITSIllegalPark.iRuleID);
		m_chkEventCheckEn.SetCheck(tITSIllegalPark.iValid);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_ILLEGALPARK_CMD_GET](%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_ILLEGALPARK_CMD_GET] (%d) error(%d)", m_iLogonID, GetLastError());
	}
}

void CLS_ITSRoadWayAdvanced1::OnBnClickedBtnSetCarPermi()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	ITS_LinePressPermillage tItsLinePressPermullage = {0};
	tItsLinePressPermullage.iBufSize = sizeof(ITS_LinePressPermillage);
	tItsLinePressPermullage.iRoadID = m_cboRoadwayID.GetCurSel();
	tItsLinePressPermullage.iCarType = m_cboCarType.GetCurSel();
	tItsLinePressPermullage.iSpeed = GetDlgItemInt(IDC_EDT_CAR_PERMI);
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_LINEPRESSPERMILLAGE_CMD_SET, NULL, &tItsLinePressPermullage, sizeof(tItsLinePressPermullage));
	if(iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_LINEPRESSPERMILLAGE_CMD_SET](%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_LINEPRESSPERMILLAGE_CMD_SET] (%d) error(%d)", m_iLogonID, GetLastError());
	}
}

void CLS_ITSRoadWayAdvanced1::UI_UpdateCarPermi()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	ITS_LinePressPermillage tItsLinePressPermullage = {0};
	tItsLinePressPermullage.iBufSize = sizeof(ITS_LinePressPermillage);
	tItsLinePressPermullage.iRoadID = m_cboRoadwayID.GetCurSel();
	tItsLinePressPermullage.iCarType = m_cboCarType.GetCurSel();
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_LINEPRESSPERMILLAGE_CMD_GET, NULL, &tItsLinePressPermullage, sizeof(tItsLinePressPermullage));
	if(iRet == 0)
	{
		SetDlgItemInt(IDC_EDT_CAR_PERMI, tItsLinePressPermullage.iSpeed);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_LINEPRESSPERMILLAGE_CMD_GET](%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_LINEPRESSPERMILLAGE_CMD_GET] (%d) error(%d)", m_iLogonID, GetLastError());
	}

}

void CLS_ITSRoadWayAdvanced1::OnCbnSelchangeCboRoadwayid()
{
	UI_UpdateIllegalpark();
	UI_UpdateCarPermi();
	UI_UpdateRoadway();
}

void CLS_ITSRoadWayAdvanced1::OnCbnSelchangeCboCarType()
{
	UI_UpdateCarPermi();
}

void CLS_ITSRoadWayAdvanced1::OnBnClickedCheckRoadwayno()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITSRoadwayInfo pa = {0};
	pa.iRoadwayID = m_cboRoadwayID.GetCurSel();
	int iRet = NetClient_GetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_GET_ENABLE, &pa, sizeof(pa));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	}
	pa.iEnable = (m_chkRoadwayNo.GetCheck() == BST_CHECKED)?1:0;
	iRet = NetClient_SetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_SET_ENABLE, &pa, sizeof(pa));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	}
}
