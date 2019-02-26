// ECOPLightPage.cpp : implementation file
//

#include "stdafx.h"
#include "ItsSignalCheck.h"
#include "math.h"
#define ITS_ROADTYPE_NUM 8 //车道类型数量
#define ITS_INTERVAL_MAX 1000 // 时间间隔最大值
// CLS_ECOPLightPage dialog

IMPLEMENT_DYNAMIC(CLS_ItsSignalCheck, CDialog)

CLS_ItsSignalCheck::CLS_ItsSignalCheck(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ItsSignalCheck::IDD, pParent)
{
	m_iLogonID = -1;
	m_iLightID = -1;
	m_iChannel = -1;
}

CLS_ItsSignalCheck::~CLS_ItsSignalCheck()
{
}

void CLS_ItsSignalCheck::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LIGHTINFOID, m_cboLightInfoID);
	DDX_Control(pDX, IDC_EDIT_INTERVAL, m_edtInterval);
	//ontrol(pDX, IDC_EDIT_ACCEPTDIFF, m_edtAcceptDiff);
	DDX_Control(pDX, IDC_CHECK_START, m_btnStartLight);
	DDX_Control(pDX, IDC_CBO_AREATYPE,  m_cboLightType);
	DDX_Control(pDX, IDC_CBO_ROADTYPE, m_cboRoadType);
	DDX_Control(pDX, IDC_BTN_SETTIME, m_cboSetTime);
	DDX_Control(pDX, IDC_EDIT_REDINTERVAL, m_editRedInterval);
	DDX_Control(pDX, IDC_EDIT_YELLOWTIME, m_editYellowTime);
	DDX_Control(pDX, IDC_EDIT_REDUPDATE, m_editRedupdate);
	DDX_Control(pDX, IDC_EDIT_REDPHASE, m_editRedPhase);
	DDX_Control(pDX, IDC_CBO_AREAID, m_cboAreaId);
	DDX_Control(pDX, IDC_CBO_RECTSUM, m_cboRectNum);
	DDX_Control(pDX, IDC_CBO_AREA, m_cboLightArea);
	DDX_Control(pDX, IDC_EDT_RECT1, m_edtRect);
}


BEGIN_MESSAGE_MAP(CLS_ItsSignalCheck, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_LIGHTINFO, &CLS_ItsSignalCheck::OnBnClickedButtonLightinfo)
	ON_CBN_SELCHANGE(IDC_COMBO_ROADWAYID, &CLS_ItsSignalCheck::OnCbnSelchangeComboRoadwayid)
	ON_CBN_SELCHANGE(IDC_COMBO_LIGHTINFOID, &CLS_ItsSignalCheck::OnCbnSelchangeComboLightinfoid)
	ON_BN_CLICKED(IDC_BTN_LIGHTSET, &CLS_ItsSignalCheck::OnBnClickedBtnLightset)
	//ON_BN_CLICKED(IDC_BTN_SETAREA, &CLS_ItsSignalCheck::OnBnClickedBtnSetarea)
	ON_BN_CLICKED(IDC_BTN_SETTIME, &CLS_ItsSignalCheck::OnBnClickedBtnSettime)
	ON_BN_CLICKED(IDC_BTN_SETAREA, &CLS_ItsSignalCheck::OnBnClickedBtnSetarea)
	ON_CBN_SELCHANGE(IDC_CBO_AREATYPE, &CLS_ItsSignalCheck::OnCbnSelchangeCboAreatype)
	ON_CBN_SELCHANGE(IDC_CBO_AREAID, &CLS_ItsSignalCheck::OnCbnSelchangeCboAreaid)
END_MESSAGE_MAP()


// CLS_ECOPLightPage message handlers

BOOL CLS_ItsSignalCheck::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	for (int i = 0; i < LIGHT_COUNT_EX; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboLightInfoID.AddString(strNo);
	}

// 	for(int i = 0; i < 8; i++)
// 	{
// 		CString strNo;
// 		strNo.Format("%d",i);
// 		m_cboLightArea.AddString(strNo);
// 	}
	m_cboLightType.AddString("0");
	m_cboLightType.AddString("1");

	m_cboLightInfoID.SetCurSel(0);

	m_edtInterval.SetLimitText(4);

	UI_UpdateDialog();

	return TRUE;
}

void CLS_ItsSignalCheck::OnChannelChanged( int _iLogonID,int _iChannelNo, int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	if (_iChannelNo < 0)
	{
		m_iChannel = 0;
	} 
	else
	{
		m_iChannel = _iChannelNo;
	}

	UI_UpdateLightInfo();
	UI_UpdateAreaSet();
	UI_UpdateTimeSet();
	UI_UpDateArea();
}

void CLS_ItsSignalCheck::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ItsSignalCheck::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_LIGHTINFO,IDS_CONFIG_ECOP_LIGHTINFO);
	SetDlgItemTextEx(IDC_STATIC_LIGHTINFOID,IDS_CONFIG_ECOP_LIGHTID);
	SetDlgItemTextEx(IDC_STATIC_INTERVAL,IDS_CONFIG_ECOP_INTERVAL);
	SetDlgItemTextEx(IDC_STATIC_ACCEPTDIFF,IDS_CONFIG_ECOP_ACCEPTDIFF);
	SetDlgItemTextEx(IDC_BUTTON_LIGHTINFO,IDS_SET);
	SetDlgItemTextEx(IDC_CHECK_START,IDS_ITS_STARTLIGHT);
	SetDlgItemTextEx(IDC_STATIC_AREA, IDS_ITS_LIGHTTYPE);
	SetDlgItemTextEx(IDC_STATIC_LIGHTTYPE, IDS_ITS_LIGHT_ROAD);
	SetDlgItemTextEx(IDC_BTN_LIGHTSET, IDS_CFG_USER_SET);
	SetDlgItemTextEx(IDC_STATIC_ROADTYPE, IDS_CONFIG_ECOP_AREATYPE);
	SetDlgItemTextEx(IDC_CHECK_AREASTART, IDS_ITS_STARTAREA);
	SetDlgItemTextEx(IDC_BTN_SETAREA, IDS_CFG_USER_SET);
	SetDlgItemTextEx(IDC_STATIC_REDINTERVAL, IDS_CONFIG_ECOP_INTERVAL);
	SetDlgItemTextEx(IDC_STATIC_YELLOWTIME, IDS_ITS_YELLOWTIME);
	SetDlgItemTextEx(IDC_STATIC_REDUPDATE, IDS_CONFIG_ECOP_ACCEPTDIFF);
	SetDlgItemTextEx(IDC_STATIC_REDPHASE, IDS_ITS_REDPHASE);
	SetDlgItemTextEx(IDC_BTN_SETTIME, IDS_SET);
	SetDlgItemTextEx(IDC_STC_AREAID, IDS_ITS_AREAID);
	SetDlgItemTextEx(IDC_STC_RECT_NUM, IDS_ITS_RECTNUM);
	SetDlgItemTextEx(IDC_STC_RECT, IDS_ITS_RECT);
	//
	InsertString(m_cboRoadType, 0, IDS_ITS_STRAIGHT);
	InsertString(m_cboRoadType, 1, IDS_ITS_TURN_LEFT);
	InsertString(m_cboRoadType, 2, IDS_ITS_TURN_RIGHT);
	InsertString(m_cboRoadType,3, IDS_ITS_STRAIGHT_LEFT);
	InsertString(m_cboRoadType, 4, IDS_ITS_STRAIGHT_RIGHT);
	InsertString(m_cboRoadType, 5, IDS_ITS_LEFT_AND_RIGHT);
	InsertString(m_cboRoadType, 6, IDS_ITS_WAIT_LEFT);
	InsertString(m_cboRoadType,7, IDS_ITS_WAIT_STRAIGHT);
	InsertString(m_cboRoadType, 8, IDS_ITS_TURN_BACK);
	//
	InsertString(m_cboLightType,0,"0");
	InsertString(m_cboLightType,1, "1");
	InsertString(m_cboLightArea,  0, IDS_ITS_SOLO_LIGHT);
	InsertString(m_cboLightArea, 1, IDS_ITS_THREE_LIGHT);
	InsertString(m_cboLightArea,2,IDS_ITS_FIVE_LINGHT_RED);
	InsertString(m_cboLightArea, 3, IDS_ITS_FIVE_LIGHT_GREEN);
	InsertString(m_cboLightArea, 4, IDS_STRIP_LIGHT);
	InsertString(m_cboLightArea, 5, IDS_ARROWS_LIGHT);
	InsertString(m_cboLightArea, 6, IDS_CIRCLE_LIGHT);
	InsertString(m_cboLightArea, 7, IDS_NUMERAL_LIGHT);

	for(int i = 0; i < 8; i++)
	{
		CString strNo;
		strNo.Format("%d", i);
		InsertString(m_cboAreaId, i, strNo);
	}
	for(int i = 0;i < 3; i++)
	{
		CString strNo;
		strNo.Format("%d", (i + 4));
		InsertString(m_cboRectNum, i, strNo);
	}
}

void CLS_ItsSignalCheck::OnCbnSelchangeComboRoadwayid()
{
	
}

BOOL CLS_ItsSignalCheck::UI_UpdateChnLight()
{
	return TRUE;
}

void CLS_ItsSignalCheck::OnBnClickedButtonLightinfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TITSLightInfo tLightInfo = {0};
	tLightInfo.iLightID = m_cboLightInfoID.GetCurSel();
	tLightInfo.iTimeInterval = GetDlgItemInt(IDC_EDIT_INTERVAL);

	if (tLightInfo.iTimeInterval>ITS_INTERVAL_MAX)
	{
		tLightInfo.iTimeInterval = ITS_INTERVAL_MAX;
	}

	tLightInfo.iTimeAcceptDiff = GetDlgItemInt(IDC_EDIT_ACCEPTDIFF);
	int iRet = NetClient_SetITSLightInfo(m_iLogonID,&tLightInfo,sizeof(tLightInfo));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSLightInfo (%d,%d,%d)",m_iLogonID,sizeof(tLightInfo));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSLightInfo (%d,%d)",m_iLogonID,sizeof(tLightInfo));
	}
}

BOOL CLS_ItsSignalCheck::UI_UpdateLightInfo()
{
	if (m_iLogonID < 0)
		return FALSE;

	TITSLightInfo tLightInfo = {0};
	tLightInfo.iLightID = m_cboLightInfoID.GetCurSel();
	int iRet = NetClient_GetITSLightInfo(m_iLogonID,&tLightInfo,sizeof(tLightInfo));
	if (0 == iRet)
	{
		m_cboLightInfoID.SetCurSel(tLightInfo.iLightID);
		SetDlgItemInt(IDC_EDIT_INTERVAL, tLightInfo.iTimeInterval);
		SetDlgItemInt(IDC_EDIT_ACCEPTDIFF, tLightInfo.iTimeAcceptDiff);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSLightInfo (%d,%d)",m_iLogonID,sizeof(tLightInfo));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSLightInfo (%d,%d)",m_iLogonID,sizeof(tLightInfo));
	}
	return TRUE;
}

void CLS_ItsSignalCheck::OnCbnSelchangeComboLightinfoid()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TITSLightInfo tLightInfo = {0};
	tLightInfo.iLightID = m_cboLightInfoID.GetCurSel();
	int iRet = NetClient_GetITSLightInfo(m_iLogonID,&tLightInfo,sizeof(tLightInfo));
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_INTERVAL, tLightInfo.iTimeInterval);
		SetDlgItemInt(IDC_EDIT_ACCEPTDIFF, tLightInfo.iTimeAcceptDiff);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSLightInfo (%d,%d)",m_iLogonID,sizeof(tLightInfo));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSLightInfo (%d,%d)",m_iLogonID,sizeof(tLightInfo));
	}
	UI_UpdateTimeSet() ;
	//UI_UpdateStartlight();
	UI_UpdateLightInfo();
	UI_UpdateAreaSet();
}

void CLS_ItsSignalCheck::OnBnClickedBtnLightset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	ITS_RedLightDetectAreaV1 tLightInfo = {0};
	tLightInfo.iRegionID = m_cboLightInfoID.GetCurSel();

	NetClient_GetITSExtraInfo(m_iLogonID, ITS_REDLIGHTDETECTAREA_CMD_GET, m_iChannel, &tLightInfo, sizeof(tLightInfo)) ;
	tLightInfo.iLightType =  m_cboLightArea.GetCurSel();
	//tLightInfo.iChannelType = (int)pow(2.0,m_cboRoadType.GetCurSel());
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_START);
	if(NULL != pBtn)
	{
		tLightInfo.iEnabled = pBtn->GetCheck();
	}
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_REDLIGHTDETECTAREA_CMD_SET, m_iChannel, &tLightInfo, sizeof(tLightInfo)) ;
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_REDLIGHTDETECTAREA_CMD_SET](%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_REDLIGHTDETECTAREA_CMD_SET](%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}
}

BOOL CLS_ItsSignalCheck::UI_UpdateAreaSet() //信号灯区域
{
	if (m_iLogonID < 0)
		return FALSE;

	ITS_RedLightDetectAreaV1 tLightInfo = {0};
	tLightInfo.iBufSize = sizeof(tLightInfo);
	tLightInfo.iRegionID = m_cboLightInfoID.GetCurSel();
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_REDLIGHTDETECTAREA_CMD_GET, m_iChannel, &tLightInfo, sizeof(tLightInfo)) ;
	if(0 == iRet)
	{
		m_cboLightArea.SetCurSel(tLightInfo.iLightType);
		m_cboRoadType.SetCurSel(tLightInfo.iChannelType);
		CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_START);
		if(NULL != pBtn)
		{
			pBtn->SetCheck(tLightInfo.iEnabled);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo (%d, %d, %d)", __LINE__, m_iLogonID, sizeof(tLightInfo));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo (%d, %d, %d)", __LINE__ , m_iLogonID, sizeof(tLightInfo));
		return FALSE;
	}
	return TRUE;
}

void CLS_ItsSignalCheck::OnBnClickedBtnSettime() //设置时间参数
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITSLightInfoEx tLightInfoEx = {0};
	tLightInfoEx.iBufSize = sizeof(tLightInfoEx);
	tLightInfoEx.m_stLightInfo.iLightID = m_cboLightInfoID.GetCurSel();
	NetClient_GetITSExtraInfo(m_iLogonID, ITS_LIGHTINFO_CMD_GET, 0, &tLightInfoEx, sizeof(tLightInfoEx)) ;
	tLightInfoEx.m_stLightInfo.iTimeInterval = GetDlgItemInt(IDC_EDIT_REDINTERVAL);
	if(tLightInfoEx.m_stLightInfo.iTimeInterval > ITS_INTERVAL_MAX)
	{
		tLightInfoEx.m_stLightInfo.iTimeInterval = ITS_INTERVAL_MAX;
	}
	tLightInfoEx.m_iYellowLightTime = GetDlgItemInt(IDC_EDIT_YELLOWTIME);
	tLightInfoEx.m_stLightInfo.iTimeAcceptDiff  = GetDlgItemInt(IDC_EDIT_REDUPDATE);
	tLightInfoEx.iPhase = GetDlgItemInt(IDC_EDIT_REDPHASE);
	int iRet = NetClient_SetITSExtraInfo( m_iLogonID, ITS_LIGHTINFO_CMD_SET, m_iChannel, &tLightInfoEx, sizeof(tLightInfoEx) );
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo (%d, %d, %d)", __LINE__, m_iLogonID, sizeof(tLightInfoEx));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo (%d, %d, %d)", __LINE__ , m_iLogonID, sizeof(tLightInfoEx));
	}
}
BOOL CLS_ItsSignalCheck::UI_UpdateTimeSet() //刷新时间参数
{
	if (m_iLogonID < 0)
		return FALSE;
	TITSLightInfoEx tLightInfoEx = {0};
	tLightInfoEx.iBufSize = sizeof(tLightInfoEx);
	tLightInfoEx.m_stLightInfo.iLightID = m_cboLightInfoID.GetCurSel();
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_LIGHTINFO_CMD_GET, m_iChannel, &tLightInfoEx, sizeof(int)) ;
	if(0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_REDINTERVAL, tLightInfoEx.m_stLightInfo.iTimeInterval);
		SetDlgItemInt(IDC_EDIT_YELLOWTIME, tLightInfoEx.m_iYellowLightTime);
		SetDlgItemInt(IDC_EDIT_REDUPDATE, tLightInfoEx.m_stLightInfo.iTimeAcceptDiff);
		SetDlgItemInt(IDC_EDIT_REDPHASE, tLightInfoEx.iPhase);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo (%d, %d, %d)", __LINE__, m_iLogonID, sizeof(int));
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo (%d, %d, %d)", __LINE__ , m_iLogonID, sizeof(int));
	}
	return TRUE;
}
void CLS_ItsSignalCheck::OnBnClickedBtnSetarea()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	ITS_AreaInfo tAreaInfo = {0};
	tAreaInfo.iBufSize = sizeof(tAreaInfo);
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_AREASTART);
	if(NULL != pBtn)
	{
		tAreaInfo.iEnabled = pBtn->GetCheck();
	}
	tAreaInfo.iRegionID = m_cboAreaId.GetCurSel();
	tAreaInfo.iCount = m_cboRectNum.GetCurSel() + 4;
	tAreaInfo.iType = m_cboLightType.GetCurSel();
	CString str;
	GetDlgItemText(IDC_EDT_RECT1,str);
	int ilen=str.GetLength();
	int j=0;
	int iNum = 0; 
	int iSum = 0;
	int iArray[12] = {0};
	for(j=0;j<ilen;j++)
	{   
		char ctemp=(char)str.GetAt(j);
		if(ctemp != ':' && ctemp != ',')
		{
			iSum = iSum*10 + (int)(ctemp - '0');
		}
		else
		{
			if(iNum < 12)
			{
				iArray[iNum] = iSum;
				iNum++;
				iSum = 0;
			}

		}
	}
	if((j == ilen)&&(iNum < 12))
	{
		iArray[iNum] = iSum;
		iNum++;
	}
	for(int i = 0; i < iNum; i++)
	{
		tAreaInfo.stTPoint[i/2].iX = iArray[i];
		i++;
	}
	for(int i = 0; i <= iNum; i++)
	{
		if(i == 0)
		{
			i++;
		}
		else
		{
			tAreaInfo.stTPoint[i/2 - 1].iY = iArray[i-1];
			i++;
		}
	}
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_AREAINFO_CMD_SET, m_iChannel, &tAreaInfo,sizeof(tAreaInfo));
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo(%d,%d)",m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo(%d,%d), error(%d)",m_iLogonID, m_iChannel ,GetLastError());
	}
}

BOOL CLS_ItsSignalCheck::UI_UpDateArea()
{
	if(m_iLogonID < 0)
		return FALSE;

	ITS_AreaInfo tAreaInfo = {0};
	//tAreaInfo.iRegionID = m_cboLightInfoID.GetCurSel();
	tAreaInfo.iRegionID = m_cboAreaId.GetCurSel();
	tAreaInfo.iType = m_cboLightType.GetCurSel();
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_AREAINFO_CMD_GET, m_iChannel, &tAreaInfo,sizeof(tAreaInfo));
	if(0 == iRet)
	{
		CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_AREASTART);
		if(NULL != pBtn)
		{
			 pBtn->SetCheck(tAreaInfo.iEnabled);
		}
		/*m_cboAreaId.SetCurSel(tAreaInfo.iRegionID);
		m_cboLightType.SetCurSel(tAreaInfo.iType);
		SetDlgItemInt(IDC_CBO_RECTSUM, tAreaInfo.iCount);*/
		m_cboRectNum.SetCurSel(tAreaInfo.iCount - 4);
		CString str;
		CString getstr;
		for(int i = 0;i < tAreaInfo.iCount;i++)
		{
			getstr.Format("%d:%d,",tAreaInfo.stTPoint[i].iX,tAreaInfo.stTPoint[i].iY);
			str = str + getstr;
		}
		m_edtRect.SetWindowText(str);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo(%d,%d)",m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo(%d,%d), error(%d)",m_iLogonID, m_iChannel ,GetLastError());
		return FALSE;
	}

	return TRUE;
}


void CLS_ItsSignalCheck::OnCbnSelchangeCboAreatype()
{
	UI_UpDateArea();
}

void CLS_ItsSignalCheck::OnCbnSelchangeCboAreaid()
{
	UI_UpDateArea();
}
