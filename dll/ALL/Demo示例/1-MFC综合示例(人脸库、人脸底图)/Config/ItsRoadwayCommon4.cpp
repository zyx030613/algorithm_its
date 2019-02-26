// ItsRoadwayCommon4.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ItsRoadwayCommon4.h"
#define ITS_NUM_MAX 20 // 数组cCoordinate的最大数

// CLS_ItsRoadwayCommon4 对话框

IMPLEMENT_DYNAMIC(CLS_ItsRoadwayCommon4, CDialog)

CLS_ItsRoadwayCommon4::CLS_ItsRoadwayCommon4(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ItsRoadwayCommon4::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannel = -1;
}

CLS_ItsRoadwayCommon4::~CLS_ItsRoadwayCommon4()
{
}

void CLS_ItsRoadwayCommon4::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ROADWAYID, m_cboRoadwayID4);
	DDX_Control(pDX, IDC_CMB_LINE_ID, m_cboLineId);
	DDX_Control(pDX, IDC_CHK_ENABLE, m_chkEnable);
	DDX_Control(pDX, IDC_CMB_LINE_TYPE, m_cboLineType);
	DDX_Control(pDX, IDC_CHECK0, m_chkBayonet);
	DDX_Control(pDX, IDC_CHECK1, m_chkRedLight);
	DDX_Control(pDX, IDC_CHECK2, m_chkRetroGrade);
	DDX_Control(pDX, IDC_CHECK3, m_chkSpeed);
	DDX_Control(pDX, IDC_CHECK4, m_chkForbidLeft);
	DDX_Control(pDX, IDC_CHECK5, m_chkForbidRight);
	DDX_Control(pDX, IDC_CHECK6, m_chkYellowLine);
	DDX_Control(pDX, IDC_CHECK7, m_chkNonMotor);
	DDX_Control(pDX, IDC_CHECK8, m_chkNotGuide);
	DDX_Control(pDX, IDC_CHECK9, m_chkForbidStraight);
	DDX_Control(pDX, IDC_CHECK10, m_chkBusWay);
	DDX_Control(pDX, IDC_CHECK11, m_chkPressWayLine);
	DDX_Control(pDX, IDC_CHECK12, m_chkWaitturnRed);
	DDX_Control(pDX, IDC_CHECK13, m_chkIllegalPark);
	DDX_Control(pDX, IDC_CHECK14, m_chkMixCapSpeed);
	DDX_Control(pDX, IDC_CMB_CAR_TYPE, m_cmbCarType);
	DDX_Control(pDX, IDC_CMB_IDENTIFY_STRATEGY, m_cmbStrategy);
	DDX_Control(pDX, IDC_CMB_REDLIGHT_CAP_TYPE, m_cmbRedlightCap);
	DDX_Control(pDX, IDC_CMB_TRAIL_CAP_PLACE, m_cmbTrailCapPlace);
	DDX_Control(pDX, IDC_CHK_BACK, m_chkBack);
	DDX_Control(pDX, IDC_CHK_TURN, m_chkTurn);
	DDX_Control(pDX, IDC_CHK_RUSH, m_chkRush);
	DDX_Control(pDX, IDC_CHK_RIDE_CAPTURE, m_chkRideCapture);
	DDX_Control(pDX, IDC_BTN_SET_CAR_LANE, m_btnSetCarLane);
	DDX_Control(pDX, IDC_CHECK_ROADWAYNO, m_chkRoadwayNo);
}


BEGIN_MESSAGE_MAP(CLS_ItsRoadwayCommon4, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_LINE_SET, &CLS_ItsRoadwayCommon4::OnBnClickedBtnLineSet)
	ON_BN_CLICKED(IDC_BTN_CAP_TYPE, &CLS_ItsRoadwayCommon4::OnBnClickedBtnCapType)
	ON_CBN_SELCHANGE(IDC_COMBO_ROADWAYID, &CLS_ItsRoadwayCommon4::OnCbnSelchangeComboRoadwayid)
	ON_BN_CLICKED(IDC_BTN_LINE_SET2, &CLS_ItsRoadwayCommon4::OnBnClickedBtnLineSet2)
	ON_BN_CLICKED(IDC_BUTTON1, &CLS_ItsRoadwayCommon4::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_SET_CAR_LANE, &CLS_ItsRoadwayCommon4::OnBnClickedBtnSetCarLane)
	ON_BN_CLICKED(IDC_CHECK_ROADWAYNO, &CLS_ItsRoadwayCommon4::OnBnClickedCheckRoadwayno)
	ON_CBN_SELCHANGE(IDC_CMB_LINE_ID, &CLS_ItsRoadwayCommon4::OnCbnSelchangeCmbLineId)
END_MESSAGE_MAP()


// CLS_ItsRoadwayCommon4 消息处理程序

void CLS_ItsRoadwayCommon4::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	if(_iChannelNo < 0)
	{
		m_iChannel = 0;
	}
	else
	{
		m_iChannel = _iChannelNo;
	}
	UI_UpdateLineSet();
	UI_UpdateCapType();
	UI_UpdateRoadway();
}

void CLS_ItsRoadwayCommon4::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ItsRoadwayCommon4::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_ROADWAYID,IDS_CONFIG_ECOP_ROADWAYID);
	SetDlgItemTextEx(IDC_STA_LINE,IDS_ITS_ROAWAY_LINE);
	SetDlgItemTextEx(IDC_STA_LINENUM,IDS_ITS_LINENUM);
	SetDlgItemTextEx(IDC_STA_LINE_ID,IDS_ITS_LINE_ID);
	SetDlgItemTextEx(IDC_STA_DISTANCE,IDS_ITS_DISTANCE);
	SetDlgItemTextEx(IDC_STA_LINE_TYPE,IDS_ITS_LINE_TYPE);
	SetDlgItemTextEx(IDC_STA_LINE_COORDINATE,IDS_ITS_LINE_COORDINATE);
	SetDlgItemTextEx(IDC_CHK_ENABLE,IDS_CONFIG_ITS_ENABLE);
	SetDlgItemTextEx(IDC_BTN_LINE_SET,IDS_SET);

	SetDlgItemTextEx(IDC_STA_CAPTYPE,IDS_CONFIG_ECOP_CAPTURE_TYPE);
	SetDlgItemTextEx(IDC_CHECK0,IDS_ITS_BAYONET);
	SetDlgItemTextEx(IDC_CHECK1,IDS_ITS_REDLIGHT);
	SetDlgItemTextEx(IDC_CHECK2,IDS_ITS_RETROGRADE);
	SetDlgItemTextEx(IDC_CHECK3,IDS_ITS_SPEED);
	SetDlgItemTextEx(IDC_CHECK4,IDS_ITS_FORBID_LEFT);
	SetDlgItemTextEx(IDC_CHECK5,IDS_ITS_FORBID_RIGHT);
	SetDlgItemTextEx(IDC_CHECK6,IDS_ITS_PRESS_YELLOW);
	SetDlgItemTextEx(IDC_CHECK7,IDS_ITS_NON_MOTOR);
	SetDlgItemTextEx(IDC_CHECK8,IDS_ITS_NOT_GUIDE_DRIVE);
	SetDlgItemTextEx(IDC_CHECK9,IDS_ITS_FORBID_STRAIGHT);
	SetDlgItemTextEx(IDC_CHECK10,IDS_ITS_BUS_WAY);
	SetDlgItemTextEx(IDC_CHECK11,IDS_ITS_PRESS_LINE);
	SetDlgItemTextEx(IDC_CHECK12,IDS_ITS_WAIT_RED_LIGHT);
	SetDlgItemTextEx(IDC_CHECK13,IDS_ITS_ILLEGAL_PARK);
	SetDlgItemTextEx(IDC_CHECK14,IDS_ITS_MIX_CAP_SPEED);

	SetDlgItemTextEx(IDC_STA_FIRST_CAP,IDS_ITS_FIRST_CAP_PLACE);
	SetDlgItemTextEx(IDC_STA_SECON_CAP,IDS_ITS_SECOND_CAP_PLACE);
	SetDlgItemTextEx(IDC_STA_THIRD_CAP,IDS_ITS_THIRD_CAP_PLACE);
	SetDlgItemTextEx(IDC_STA_CAR_TYPE,IDS_ITS_TYPE);
	SetDlgItemTextEx(IDC_STA_IDENTIFY_STRATEGY,IDS_ITS_DISTINGUISH_STRATEGY);
	SetDlgItemTextEx(IDC_STA_REDLIGHT_CAP_TYPE,IDS_ITS_RED_LIGHT_CAP);
	SetDlgItemTextEx(IDC_STA_TRAIL_CAP_PLACE,IDS_ITS_TRAIL_CAP_PLACE);
	SetDlgItemTextEx(IDC_BTN_CAP_TYPE,IDS_SET);
	SetDlgItemTextEx(IDC_CHECK_ROADWAYNO,IDS_CONFIG_ITS_ROADWAY_ENABLE);

	SetDlgItemTextEx(IDC_CHK_BACK, IDS_ITS_BACK);
	SetDlgItemTextEx(IDC_CHK_TURN, IDS_ITS_TURN2);
	SetDlgItemTextEx(IDC_CHK_RUSH,IDS_ITS_MIXED_ENABLE);
	SetDlgItemTextEx(IDC_CHK_MAX, IDS_ITS_MAX2);
	SetDlgItemTextEx(IDC_CHK_RIDE_CAPTURE, IDS_ITS_RIDE_CAPTURE);
	SetDlgItemTextEx(IDC_BTN_SET_CAR_LANE,IDS_SET);

	//抓拍位置填写说明
	//0——不抓拍
	//1——进入测速线圈时抓拍
	//2——离开测速线圈时抓拍
	//3——进入抓拍线圈时抓拍
	//4——离开抓拍线圈时抓拍
	//5——延时抓拍
	//按类型进行，例：1,2,3,4
	InsertString(m_cmbCarType,0,IDS_ITS_LEFT_ROADWAY);
	InsertString(m_cmbCarType,1,IDS_ITS_RIGHT_ROADWAY);
	InsertString(m_cmbCarType,2,IDS_ITS_STRAIGHT_ROADWAY);
	InsertString(m_cmbCarType,3,IDS_ITS_LEFT_STRAIGHT_ROADWAY);
	InsertString(m_cmbCarType,4,IDS_ITS_RIGHT_STRAIGHT_ROADWAY);
	InsertString(m_cmbCarType,5,IDS_ITS_NON_MOTOR_ROADWAY);
	InsertString(m_cmbCarType,6,IDS_ITS_LEFT_RIGHT_ROADWAY);
	InsertString(m_cmbCarType,7,IDS_ITS_LEFT_WAY_WAITTURN);
	InsertString(m_cmbCarType,8,IDS_ITS_LEFT_RIGHT_STRAIGHT_WAY);
	InsertString(m_cmbStrategy,0,IDS_ITS_DISTINGUISH_FIRST);
	InsertString(m_cmbStrategy,1,IDS_ITS_DISTINGUISH_SECOND);
	InsertString(m_cmbStrategy,2,IDS_ITS_DISTINGUISH_FIRST_SECOND_HIGH);
	InsertString(m_cmbStrategy,3,IDS_ITS_DISTINGUISH_SECOND_FIRST);
	InsertString(m_cmbStrategy,4,IDS_ITS_DISTINGUISH_FIRST_SECOND);
	InsertString(m_cmbStrategy,5,IDS_ITS_LINE_DISTINGUISH_THIRD);
	InsertString(m_cmbRedlightCap,0,IDS_ITS_DIRECT_CAP);
	InsertString(m_cmbRedlightCap,1,IDS_ITS_ROADWAY_CAP);
	InsertString(m_cmbRedlightCap,2,IDS_ITS_ROADWAY_DIRECT_CAP);
	InsertString(m_cmbTrailCapPlace,0,IDS_ITS_CAP_ONE);
	InsertString(m_cmbTrailCapPlace,1,IDS_ITS_CAP_TWO);
	//
	for(int i = 0;i < ITS_LINE_ID_MAX;i++)
	{
		CString strNo;
		strNo.Format("%d", i);
		InsertString(m_cboLineId,i,strNo);
	}
	for(int i = 0;i < ITS_LINE_TYPE_MAX;i++)
	{
		InsertString(m_cboLineType,i,IDS_ITS_LEFT_BORDER + i);
	}
}

BOOL CLS_ItsRoadwayCommon4::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	for (int i=0; i<4; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboRoadwayID4.AddString(strNo);
	}
	m_cboRoadwayID4.SetCurSel(0);

	UI_UpdateDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLS_ItsRoadwayCommon4::OnBnClickedBtnLineSet()
{
	
}

BOOL CLS_ItsRoadwayCommon4::UI_UpdateRoadway()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iRoadwayID = m_cboRoadwayID4.GetCurSel();
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

void CLS_ItsRoadwayCommon4::UI_UpdateLineSet()
{
	if (m_iLogonID < 0)
		return;

	TITS_RefLineAarry tItsReflineArray = {0};
	tItsReflineArray.m_iRoadwayID = m_cboRoadwayID4.GetCurSel();
	/*int iLineNum = GetDlgItemInt(IDC_EDT_LINENUM);
	tItsReflineArray.m_iLineNum = iLineNum;*/
	int iRet = NetClient_GetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_GET_REFERENCELINE, &tItsReflineArray, sizeof(tItsReflineArray));
	int iLineNum = tItsReflineArray.m_iLineNum;
	if (0 == iRet)
	{
		if(iLineNum > -1 && iLineNum < MAX_ITS_REFLINE_NUM)
		{
			m_cboLineId.SetCurSel(tItsReflineArray.m_stLines[iLineNum].m_iLineID);
			SetDlgItemInt(IDC_DISTANCE, tItsReflineArray.m_stLines[iLineNum].m_iDistance);
			m_chkEnable.SetCheck(tItsReflineArray.m_stLines[iLineNum].m_iEnable);
			m_cboLineType.SetCurSel(tItsReflineArray.m_stLines[iLineNum].m_iLineType);

			char cCoordinate[ITS_NUM_MAX] = {0};

			int iStartX = tItsReflineArray.m_stLines[iLineNum].m_stLine1.stStart.iX;
			int iStartY = tItsReflineArray.m_stLines[iLineNum].m_stLine1.stStart.iY;
			int iEndX = tItsReflineArray.m_stLines[iLineNum].m_stLine1.stEnd.iX;
			int iEndY = tItsReflineArray.m_stLines[iLineNum].m_stLine1.stEnd.iY;
			sprintf_s(cCoordinate, sizeof(cCoordinate), "%d:%d,%d:%d", iStartX, iStartY, iEndX, iEndY);
			SetDlgItemText(IDC_EDT_LINE_COORDINATE, cCoordinate);
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_GET_REFERENCELINE](%d)", m_iLogonID);
		}
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_GET_REFERENCELINE](%d),error(%d)", m_iLogonID, GetLastError());
	}
}

void CLS_ItsRoadwayCommon4::UI_UpdateLineSet2()
{
	if (m_iLogonID < 0)
		return;

	TITS_RefLineAarry tItsReflineArray = {0};
	tItsReflineArray.m_iRoadwayID = m_cboRoadwayID4.GetCurSel();
	int iLineNum = GetDlgItemInt(IDC_EDT_LINENUM);
	tItsReflineArray.m_iLineNum = iLineNum;
	int iRet = NetClient_GetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_GET_REFERENCELINE, &tItsReflineArray, sizeof(tItsReflineArray));
	if (0 == iRet)
	{
		if(iLineNum > -1 && iLineNum < MAX_ITS_REFLINE_NUM)
		{
			//m_cboLineId.SetCurSel(tItsReflineArray.m_stLines[iLineNum].m_iLineID);
			SetDlgItemInt(IDC_DISTANCE, tItsReflineArray.m_stLines[iLineNum].m_iDistance);
			m_chkEnable.SetCheck(tItsReflineArray.m_stLines[iLineNum].m_iEnable);
			m_cboLineType.SetCurSel(tItsReflineArray.m_stLines[iLineNum].m_iLineType);

			char cCoordinate[ITS_NUM_MAX] = {0};

			int iStartX = tItsReflineArray.m_stLines[iLineNum].m_stLine1.stStart.iX;
			int iStartY = tItsReflineArray.m_stLines[iLineNum].m_stLine1.stStart.iY;
			int iEndX = tItsReflineArray.m_stLines[iLineNum].m_stLine1.stEnd.iX;
			int iEndY = tItsReflineArray.m_stLines[iLineNum].m_stLine1.stEnd.iY;
			sprintf_s(cCoordinate, sizeof(cCoordinate), "%d:%d,%d:%d", iStartX, iStartY, iEndX, iEndY);
			SetDlgItemText(IDC_EDT_LINE_COORDINATE, cCoordinate);
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_SET_REFERENCELINE](%d)", m_iLogonID);
		}
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_SET_REFERENCELINE](%d),error(%d)", m_iLogonID, GetLastError());
	}
}

void CLS_ItsRoadwayCommon4::OnBnClickedBtnCapType()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITSRoadwayCapture tItsRoadwayCapture = {0};
	tItsRoadwayCapture.iRoadwayID = m_cboRoadwayID4.GetCurSel();

	int iEnable = 0;
	iEnable |= (m_chkBayonet.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_BAYONET_CAPTURE0:iEnable;
	iEnable |= (m_chkRedLight.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_RED_LIGHT:iEnable;
	iEnable |= (m_chkRetroGrade.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_RETROGRADE:iEnable;
	iEnable |= (m_chkSpeed.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_OVER_SPEED:iEnable;
	iEnable |= (m_chkForbidLeft.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_FORBID_LEFT:iEnable;
	iEnable |= (m_chkForbidRight.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_FORBID_RIGHT:iEnable;
	iEnable |= (m_chkYellowLine.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_PRESS_YELLOW:iEnable;
	iEnable |= (m_chkNonMotor.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_NON_MOTOR:iEnable;
	iEnable |= (m_chkNotGuide.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_NOT_GUIDE:iEnable;
	iEnable |= (m_chkForbidStraight.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_FORBID_STRAIGHT:iEnable;
	iEnable |= (m_chkBusWay.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_BUS_ROAD:iEnable;
	iEnable |= (m_chkPressWayLine.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_PRESS_ROAD_LINE:iEnable;
	iEnable |= (m_chkWaitturnRed.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_WAIT_TURN_REDLIGHT:iEnable;
	iEnable |= (m_chkIllegalPark.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_ILLEGAL_PARK:iEnable;
	iEnable |= (m_chkMixCapSpeed.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_CAP_MIX_SPEED:iEnable;
	iEnable |= (m_chkBack.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_REVERS:iEnable;
	iEnable |= (m_chkTurn.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_TURN_AROUND:iEnable;
	iEnable |= (m_chkRideCapture.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_BREAK_RIDE_LINE:iEnable;
	iEnable |= (m_chkRush.GetCheck() == BST_CHECKED)?1<<ITS_ROAD_CAP_BREAK_FORBID_LINE:iEnable;

	tItsRoadwayCapture.iType = iEnable;

	char cCapPlace[LEN_64] = "0";
	GetDlgItemText(IDC_EDT_FIRST_CAP, cCapPlace, LEN_64);
	memcpy(tItsRoadwayCapture.cPlace[0], cCapPlace, LEN_64);

	memset(cCapPlace, 0, LEN_64);
	GetDlgItemText(IDC_EDT_SECON_CAP, cCapPlace, LEN_64);
	memcpy(tItsRoadwayCapture.cPlace[1], cCapPlace, LEN_64);

	memset(cCapPlace, 0, LEN_64);
	GetDlgItemText(IDC_EDT_THIRD_CAP, cCapPlace, LEN_64);
	memcpy(tItsRoadwayCapture.cPlace[2], cCapPlace, LEN_64);

	tItsRoadwayCapture.iChannelTpye = m_cmbCarType.GetCurSel();
	tItsRoadwayCapture.iRecognizePlace = m_cmbStrategy.GetCurSel();
	tItsRoadwayCapture.iRedLightCapType = m_cmbRedlightCap.GetCurSel();
	tItsRoadwayCapture.iTrailCapPlace = m_cmbTrailCapPlace.GetCurSel();

	int iRet = NetClient_SetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_SET_CAPTURE, &tItsRoadwayCapture, sizeof(tItsRoadwayCapture));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_SET_CAPTURE](%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_SET_CAPTURE](%d),error(%d)", m_iLogonID, GetLastError());
	}

}

void CLS_ItsRoadwayCommon4::UI_UpdateCapType()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITSRoadwayCapture tItsRoadwayCapture = {0};
	tItsRoadwayCapture.iRoadwayID = m_cboRoadwayID4.GetCurSel();

	int iRet = NetClient_GetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_GET_CAPTURE, &tItsRoadwayCapture, sizeof(tItsRoadwayCapture));
	if (0 == iRet)
	{
		int iEnable = tItsRoadwayCapture.iType;
		m_chkBayonet.SetCheck((iEnable>>ITS_ROAD_CAP_BAYONET_CAPTURE0) & 0x1);
		m_chkRedLight.SetCheck((iEnable>>ITS_ROAD_CAP_RED_LIGHT) & 0x1);
		m_chkRetroGrade.SetCheck((iEnable>>ITS_ROAD_CAP_RETROGRADE) & 0x1);
		m_chkSpeed.SetCheck((iEnable>>ITS_ROAD_CAP_OVER_SPEED) & 0x1);
		m_chkForbidLeft.SetCheck((iEnable>>ITS_ROAD_CAP_FORBID_LEFT) & 0x1);
		m_chkForbidRight.SetCheck((iEnable>>ITS_ROAD_CAP_FORBID_RIGHT) & 0x1);
		m_chkYellowLine.SetCheck((iEnable>>ITS_ROAD_CAP_PRESS_YELLOW) & 0x1);
		m_chkNonMotor.SetCheck((iEnable>>ITS_ROAD_CAP_NON_MOTOR) & 0x1);
		m_chkNotGuide.SetCheck((iEnable>>ITS_ROAD_CAP_NOT_GUIDE) & 0x1);
		m_chkForbidStraight.SetCheck((iEnable>>ITS_ROAD_CAP_FORBID_STRAIGHT) & 0x1);
		m_chkBusWay.SetCheck((iEnable>>ITS_ROAD_CAP_BUS_ROAD) & 0x1);
		m_chkPressWayLine.SetCheck((iEnable>>ITS_ROAD_CAP_PRESS_ROAD_LINE) & 0x1);
		m_chkWaitturnRed.SetCheck((iEnable>>ITS_ROAD_CAP_WAIT_TURN_REDLIGHT) & 0x1);
		m_chkIllegalPark.SetCheck((iEnable>>ITS_ROAD_CAP_ILLEGAL_PARK) & 0x1);
		m_chkMixCapSpeed.SetCheck((iEnable>>ITS_ROAD_CAP_CAP_MIX_SPEED) & 0x1);
		m_chkBack.SetCheck((iEnable>>ITS_ROAD_CAP_REVERS) & 0x1);
		m_chkTurn.SetCheck((iEnable>>ITS_ROAD_CAP_TURN_AROUND) & 0x1);
		m_chkRideCapture.SetCheck((iEnable>>ITS_ROAD_CAP_BREAK_RIDE_LINE) & 0x1);
		m_chkRush.SetCheck((iEnable>>ITS_ROAD_CAP_BREAK_FORBID_LINE) & 0x1);
		SetDlgItemText(IDC_EDT_FIRST_CAP, tItsRoadwayCapture.cPlace[0]);
		SetDlgItemText(IDC_EDT_SECON_CAP, tItsRoadwayCapture.cPlace[1]);
		SetDlgItemText(IDC_EDT_THIRD_CAP, tItsRoadwayCapture.cPlace[2]);

		m_cmbCarType.SetCurSel(tItsRoadwayCapture.iChannelTpye);
		m_cmbStrategy.SetCurSel(tItsRoadwayCapture.iRecognizePlace);
		m_cmbRedlightCap.SetCurSel(tItsRoadwayCapture.iRedLightCapType);
		m_cmbTrailCapPlace.SetCurSel(tItsRoadwayCapture.iTrailCapPlace);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam[ITS_ROADWAY_CMD_GET_CAPTURE](%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam[ITS_ROADWAY_CMD_GET_CAPTURE](%d),error(%d)", m_iLogonID, GetLastError());
	}
}
void CLS_ItsRoadwayCommon4::OnCbnSelchangeComboRoadwayid()
{
	UI_UpdateLineSet();
	UI_UpdateCapType();
	UI_UpdateRoadway();
}

void CLS_ItsRoadwayCommon4::OnBnClickedBtnLineSet2()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TITS_RefLineAarry tItsReflineArray = {0};
	tItsReflineArray.m_iRoadwayID = m_cboRoadwayID4.GetCurSel();
	int iLineNum = GetDlgItemInt(IDC_EDT_LINENUM);
	tItsReflineArray.m_iLineNum = 1 /*iLineNum*/;
	tItsReflineArray.m_stLines[iLineNum].m_iLineID = m_cboLineId.GetCurSel();
	tItsReflineArray.m_stLines[iLineNum].m_iDistance = GetDlgItemInt(IDC_DISTANCE);
	tItsReflineArray.m_stLines[iLineNum].m_iEnable = m_chkEnable.GetCheck();
	tItsReflineArray.m_stLines[iLineNum].m_iLineType = m_cboLineType.GetCurSel();

	char cCoordinate[ITS_NUM_MAX] = {0};
	GetDlgItemText(IDC_EDT_LINE_COORDINATE, cCoordinate, ITS_NUM_MAX);
	int iStartX = 0;
	int iStartY = 0;
	int iEndX = 0;
	int iEndY = 0;
	scanf(cCoordinate, "%d:%d,%d:%d", &iStartX, &iStartY, &iEndX, &iEndY);
	tItsReflineArray.m_stLines[iLineNum].m_stLine1.stStart.iX = iStartX;
	tItsReflineArray.m_stLines[iLineNum].m_stLine1.stStart.iY = iStartY;

	tItsReflineArray.m_stLines[iLineNum].m_stLine1.stEnd.iX = iEndX;
	tItsReflineArray.m_stLines[iLineNum].m_stLine1.stEnd.iY = iEndY;


	int iRet = NetClient_SetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_SET_REFERENCELINE, &tItsReflineArray, sizeof(tItsReflineArray));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_SET_REFERENCELINE](%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_SET_REFERENCELINE](%d),error(%d)", m_iLogonID, GetLastError());
	}
}

void CLS_ItsRoadwayCommon4::OnBnClickedButton1()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TITS_RefLineAarry tItsReflineArray = {0};
	tItsReflineArray.m_iRoadwayID = m_cboRoadwayID4.GetCurSel();
	int iLineNum = GetDlgItemInt(IDC_EDT_LINENUM);
	tItsReflineArray.m_iLineNum = 1 /*iLineNum*/;
	tItsReflineArray.m_stLines[iLineNum].m_iLineID = m_cboLineId.GetCurSel();
	tItsReflineArray.m_stLines[iLineNum].m_iDistance = GetDlgItemInt(IDC_DISTANCE);
	tItsReflineArray.m_stLines[iLineNum].m_iEnable = m_chkEnable.GetCheck();
	tItsReflineArray.m_stLines[iLineNum].m_iLineType = m_cboLineType.GetCurSel();

	char cCoordinate[ITS_NUM_MAX] = {0};
	GetDlgItemText(IDC_EDT_LINE_COORDINATE, cCoordinate, ITS_NUM_MAX);
	int iStartX = 0;
	int iStartY = 0;
	int iEndX = 0;
	int iEndY = 0;
	scanf(cCoordinate, "%d:%d,%d:%d", &iStartX, &iStartY, &iEndX, &iEndY);
	tItsReflineArray.m_stLines[iLineNum].m_stLine1.stStart.iX = iStartX;
	tItsReflineArray.m_stLines[iLineNum].m_stLine1.stStart.iY = iStartY;

	tItsReflineArray.m_stLines[iLineNum].m_stLine1.stEnd.iX = iEndX;
	tItsReflineArray.m_stLines[iLineNum].m_stLine1.stEnd.iY = iEndY;


	int iRet = NetClient_SetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_SET_REFERENCELINE, &tItsReflineArray, sizeof(tItsReflineArray));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_SET_REFERENCELINE](%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_SET_REFERENCELINE](%d),error(%d)", m_iLogonID, GetLastError());
	}
}

void CLS_ItsRoadwayCommon4::OnBnClickedBtnSetCarLane()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TITS_RefLineAarry tItsReflineArray = {0};
	tItsReflineArray.m_iRoadwayID = m_cboRoadwayID4.GetCurSel();
	int iLineNum = GetDlgItemInt(IDC_EDT_LINENUM);
	tItsReflineArray.m_iLineNum = 1 /*iLineNum*/;
	tItsReflineArray.m_stLines[iLineNum].m_iLineID = m_cboLineId.GetCurSel();
	tItsReflineArray.m_stLines[iLineNum].m_iDistance = GetDlgItemInt(IDC_DISTANCE);
	tItsReflineArray.m_stLines[iLineNum].m_iEnable = m_chkEnable.GetCheck();
	tItsReflineArray.m_stLines[iLineNum].m_iLineType = m_cboLineType.GetCurSel();

	char cCoordinate[ITS_NUM_MAX] = {0};
	GetDlgItemText(IDC_EDT_LINE_COORDINATE, cCoordinate, ITS_NUM_MAX);
	int iStartX = 0;
	int iStartY = 0;
	int iEndX = 0;
	int iEndY = 0;
	sscanf_s(cCoordinate, "%d:%d,%d:%d", &iStartX, &iStartY, &iEndX, &iEndY);
	tItsReflineArray.m_stLines[iLineNum].m_stLine1.stStart.iX = iStartX;
	tItsReflineArray.m_stLines[iLineNum].m_stLine1.stStart.iY = iStartY;

	tItsReflineArray.m_stLines[iLineNum].m_stLine1.stEnd.iX = iEndX;
	tItsReflineArray.m_stLines[iLineNum].m_stLine1.stEnd.iY = iEndY;


	int iRet = NetClient_SetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_SET_REFERENCELINE, &tItsReflineArray, sizeof(tItsReflineArray));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_SET_REFERENCELINE](%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_SET_REFERENCELINE](%d),error(%d)", m_iLogonID, GetLastError());
	}
}

void CLS_ItsRoadwayCommon4::OnBnClickedCheckRoadwayno()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITSRoadwayInfo pa = {0};
	pa.iRoadwayID = m_cboRoadwayID4.GetCurSel();
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

void CLS_ItsRoadwayCommon4::OnCbnSelchangeCmbLineId()
{
	UI_UpdateLineSet2();
}
