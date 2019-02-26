// ITSSetVCAPage.cpp : implementation file
//

#include "stdafx.h"
#include "ITSSetVCAPage.h"
#include "VideoView.h"
#include "Common/CommonFun.h"

unsigned int P_ulConnID[36]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
bool blExactFix = false;    //是否手动操作精确定位
int iFixPreset = -1;       // 精确定位的预置位
int iFixArea  = -1;        // 精确定位的区域
int iFixRect  = -1;        // 精确定位的区域中四边形

#define	INVALID_CONNECT_ID	(0xFFFFFFFF)

// CLS_ITSSetVCAPage dialog

IMPLEMENT_DYNAMIC(CLS_ITSSetVCAPage, CDialog)

CLS_ITSSetVCAPage::CLS_ITSSetVCAPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ITSSetVCAPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNo = 0;
	memset(m_cDeviceType,0,sizeof(m_cDeviceType));
	m_iPolyCount = 0;
	m_iPointCount = 0;
	m_iCurPolyIndex = 0;
	m_iCurDrawGrh = 0;
	m_hResetPlayerWnd = NULL;
	m_bMouseDown = false;
}

CLS_ITSSetVCAPage::~CLS_ITSSetVCAPage()
{
}

void CLS_ITSSetVCAPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PRESET, m_cboPreset);
	DDX_Control(pDX, IDC_COMBO_AREA, m_cboArea);
	DDX_Control(pDX, IDC_EDIT_ILLEGALPARKTIME, m_edtTime);
	DDX_Control(pDX, IDC_COMBO_TIMERANGE, m_cboTimeRange);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_dtcFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_dtcTo);
	DDX_Control(pDX, IDC_EDIT_POINT1_X, m_edtPointx[0]);
	DDX_Control(pDX, IDC_EDIT_POINT1_Y, m_edtPointy[0]);
	DDX_Control(pDX, IDC_EDIT_POINT2_X, m_edtPointx[1]);
	DDX_Control(pDX, IDC_EDIT_POINT2_Y, m_edtPointy[1]);
	DDX_Control(pDX, IDC_EDIT_POINT3_X, m_edtPointx[2]);
	DDX_Control(pDX, IDC_EDIT_POINT3_Y, m_edtPointy[2]);
	DDX_Control(pDX, IDC_EDIT_POINT4_X, m_edtPointx[3]);
	DDX_Control(pDX, IDC_EDIT_POINT4_Y, m_edtPointy[3]);
	DDX_Control(pDX, IDC_EDIT_PARKTIME, m_edtParkTime);
	DDX_Control(pDX, IDC_EDIT_SENSITIVITY, m_edtSensitivity);
	DDX_Control(pDX, IDC_BUTTON_RESET, m_btnReset);
	DDX_Control(pDX, IDC_BUTTON_SET, m_btnSet);
	DDX_Control(pDX, IDC_EDIT_RECT1_POINT1_X, m_edtRectPointx[0][0]);
	DDX_Control(pDX, IDC_EDIT_RECT1_POINT1_Y, m_edtRectPointy[0][0]);
	DDX_Control(pDX, IDC_EDIT_RECT1_POINT2_X, m_edtRectPointx[0][1]);
	DDX_Control(pDX, IDC_EDIT_RECT1_POINT2_Y, m_edtRectPointy[0][1]);
	DDX_Control(pDX, IDC_EDIT_RECT2_POINT1_X,  m_edtRectPointx[1][0]);
	DDX_Control(pDX, IDC_EDIT_RECT2_POINT1_Y,  m_edtRectPointy[1][0]);
	DDX_Control(pDX, IDC_EDIT_RECT2_POINT2_X,  m_edtRectPointx[1][1]);
	DDX_Control(pDX, IDC_EDIT_RECT2_POINT2_Y,  m_edtRectPointy[1][1]);
	DDX_Control(pDX, IDC_EDIT_RECT3_POINT1_X,  m_edtRectPointx[2][0]);
	DDX_Control(pDX, IDC_EDIT_RECT3_POINT1_Y,  m_edtRectPointy[2][0]);
	DDX_Control(pDX, IDC_EDIT_RECT3_POINT2_X,  m_edtRectPointx[2][1]);
	DDX_Control(pDX, IDC_EDIT_RECT3_POINT2_Y,  m_edtRectPointy[2][1]);
	DDX_Control(pDX, IDC_EDIT_RECT4_POINT1_X,  m_edtRectPointx[3][0]);
	DDX_Control(pDX, IDC_EDIT_RECT4_POINT1_Y,  m_edtRectPointy[3][0]);
	DDX_Control(pDX, IDC_EDIT_RECT4_POINT2_X,  m_edtRectPointx[3][1]);
	DDX_Control(pDX, IDC_EDIT_RECT4_POINT2_Y,  m_edtRectPointy[3][1]);
	DDX_Control(pDX, IDC_COMBO_PARAM_AREA, m_cboParamArea);
	DDX_Control(pDX, IDC_BUTTON_PARAM_RESET, m_btnParamReset);
	DDX_Control(pDX, IDC_BUTTON_PARAM_SET, m_btnParamSet);
	DDX_Control(pDX, IDC_BUTTON_PARAM_EXACTFIX, m_btnExactFix);
	DDX_Control(pDX, IDC_STATIC_PLAYWND, m_StxtPlayWnd);
}


BEGIN_MESSAGE_MAP(CLS_ITSSetVCAPage, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_PRESET, &CLS_ITSSetVCAPage::OnCbnSelchangeComboPreset)
	ON_CBN_SELCHANGE(IDC_COMBO_AREA, &CLS_ITSSetVCAPage::OnCbnSelchangeComboArea)
	ON_CBN_SELCHANGE(IDC_COMBO_TIMERANGE, &CLS_ITSSetVCAPage::OnCbnSelchangeComboTimerange)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CLS_ITSSetVCAPage::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CLS_ITSSetVCAPage::OnBnClickedButtonSet)
	ON_CBN_SELCHANGE(IDC_COMBO_PARAM_AREA, &CLS_ITSSetVCAPage::OnCbnSelchangeComboParamArea)
	ON_BN_CLICKED(IDC_BUTTON_PARAM_RESET, &CLS_ITSSetVCAPage::OnBnClickedButtonParamReset)
	ON_BN_CLICKED(IDC_BUTTON_PARAM_SET, &CLS_ITSSetVCAPage::OnBnClickedButtonParamSet)
	ON_BN_CLICKED(IDC_BUTTON_PARAM_EXACTFIX, &CLS_ITSSetVCAPage::OnBnClickedButtonParamExactfix)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()

	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLS_ITSSetVCAPage message handlers
BOOL CLS_ITSSetVCAPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

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
		m_cboParamArea.AddString(strNo);
	}
	m_cboArea.SetCurSel(0);
	m_cboTimeRange.SetCurSel(0);
	m_cboParamArea.SetCurSel(0);

	m_edtTime.SetLimitText(10);
	for (int i=0; i<4; i++)
	{
		m_edtPointx[i].SetLimitText(6);
		m_edtPointy[i].SetLimitText(6);
		for (int j=0; j<2; j++)
		{
			m_edtRectPointx[i][j].SetLimitText(6);
			m_edtRectPointy[i][j].SetLimitText(6);
		}
	}
	
	m_edtParkTime.SetLimitText(10);
	m_edtSensitivity.SetLimitText(10);

	StartPlay();

	UI_UpdateDeviceType();
	UI_UpdateGraph();

	UI_UpdateDialog();

	return TRUE;
}

void CLS_ITSSetVCAPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo;
	}
	if (_iStreamNo < 0)
	{
		m_iStreamNo = 0;
	}
	else
	{
		m_iStreamNo = _iStreamNo;
	}
}

void CLS_ITSSetVCAPage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ITSSetVCAPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_ILLEGALPARK,IDS_CONFIG_ITS_ILLEGALPARK);
	SetDlgItemTextEx(IDC_STATIC_PRESET,IDS_CONFIG_ITS_ILLEGALPARK_PRESET);
	SetDlgItemTextEx(IDC_STATIC_AREA,IDS_CONFIG_ITS_ILLEGALPARK_AREA);
	SetDlgItemTextEx(IDC_STATIC_ILLEGALPARKTIME,IDS_CONFIG_ITS_ILLEGALPARK_TIME);
	SetDlgItemTextEx(IDC_STATIC_TIMERANGE,IDS_ITS_COMMON1);
	SetDlgItemTextEx(IDC_STATIC_TIMEFROM,IDS_CONFIG_ITS_ILLEGALPARK_FROM);
	SetDlgItemTextEx(IDC_STATIC_TIMETO,IDS_CONFIG_ITS_ILLEGALPARK_TO);
	SetDlgItemTextEx(IDC_STATIC_POINT1,IDS_CONFIG_ITS_ILLEGALPARK_POINT1);
	SetDlgItemTextEx(IDC_STATIC_POINT2,IDS_CONFIG_ITS_ILLEGALPARK_POINT2);
	SetDlgItemTextEx(IDC_STATIC_POINT3,IDS_CONFIG_ITS_ILLEGALPARK_POINT3);
	SetDlgItemTextEx(IDC_STATIC_POINT4,IDS_CONFIG_ITS_ILLEGALPARK_POINT4);
	SetDlgItemTextEx(IDC_STATIC_PARKTIME,IDS_CONFIG_ITS_ILLEGALPARK_PARKTIME);
	SetDlgItemTextEx(IDC_STATIC_SENSITIVITY,IDS_CONFIG_ITS_ILLEGALPARK_SENSITIVITY);
	SetDlgItemTextEx(IDC_BUTTON_RESET,IDS_CONFIG_ITS_ILLEGALPARK_RESET);
	SetDlgItemTextEx(IDC_BUTTON_SET,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_ILLEGALPARKPARAM,IDS_CONFIG_ITS_ILLEGALPARK_PARAM);
	SetDlgItemTextEx(IDC_STATIC_RECT1,IDS_CONFIG_ITS_ILLEGALPARK_RECT1);
	SetDlgItemTextEx(IDC_STATIC_RECT2,IDS_CONFIG_ITS_ILLEGALPARK_RECT2);
	SetDlgItemTextEx(IDC_STATIC_RECT3,IDS_CONFIG_ITS_ILLEGALPARK_RECT3);
	SetDlgItemTextEx(IDC_STATIC_RECT4,IDS_CONFIG_ITS_ILLEGALPARK_RECT4);
	SetDlgItemTextEx(IDC_STATIC_PARAM_AREA,IDS_CONFIG_ITS_ILLEGALPARK_AREA);
	SetDlgItemTextEx(IDC_BUTTON_PARAM_RESET,IDS_CONFIG_ITS_ILLEGALPARK_RESET);
	SetDlgItemTextEx(IDC_BUTTON_PARAM_SET,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_PARAM_EXACTFIX,IDS_CONFIG_ITS_ILLEGALPARK_EXACTFIX);
}

void CLS_ITSSetVCAPage::StartPlay()
{
	m_pstxtPlayWnd = (CStatic *)GetDlgItem(IDC_STATIC_PLAYWND);
	m_hPlayWnd = GetDlgItem(IDC_STATIC_PLAYWND)->GetSafeHwnd();
	PCHANNEL_INFO pChannel = FindChannel(m_iLogonID, m_iChannelNo, m_iStreamNo, &m_uiConnID);
	if (pChannel)
	{
		CLS_VideoView* pVideo = (CLS_VideoView*)pChannel->pVideo;
		m_hResetPlayerWnd = pVideo->GetSafeHwnd();
		NetClient_ResetPlayerWnd(m_uiConnID, m_hPlayWnd);
	}
	else
	{
		m_hResetPlayerWnd = NULL;
		RECT rctDisplay = {0};
		CLIENTINFO cltInfo = {0};
		memcpy(cltInfo.m_cRemoteIP, FindDevice(m_iLogonID)->cIP, 16);
		cltInfo.m_iServerID = m_iLogonID;
		cltInfo.m_iChannelNo = m_iChannelNo;
		cltInfo.m_iStreamNO = m_iStreamNo;
		cltInfo.m_iNetMode = 1;
		int iRet = NetClient_StartRecvEx(&m_uiConnID,&cltInfo,NULL,NULL);
		pChannel = AddChannel(m_uiConnID);
		if (pChannel)
		{
			pChannel->iLogonID = m_iLogonID;
			pChannel->iChannelNo = m_iChannelNo;
			pChannel->iStreamNo = m_iStreamNo;
			pChannel->pVideo = NULL;
		}
	}
}

void CLS_ITSSetVCAPage::StopPlay()
{
	if (INVALID_CONNECT_ID != m_uiConnID)
	{
		if (m_hResetPlayerWnd)
		{
			NetClient_ResetPlayerWnd(m_uiConnID, m_hResetPlayerWnd);
		}
		else
		{
			RECT rcShow = {0};
			int iRet = NetClient_StopPlay(m_uiConnID);

			if (iRet < 0)
			{
				AddLog(LOG_TYPE_FAIL," CH%d-%d","NetClient_StopPlay(%u,,,)",m_iChannelNo, m_iStreamNo, m_uiConnID);
			}
			
			iRet = NetClient_StopRecv(m_uiConnID);
			if (iRet < 0)
			{
				AddLog(LOG_TYPE_FAIL," CH%d-%d","NetClient_StopRecv(%u,,,)",m_iChannelNo, m_iStreamNo, m_uiConnID);
			}
			RemoveChannel(m_uiConnID);
		}
		m_uiConnID = INVALID_CONNECT_ID;
	}
}
void CLS_ITSSetVCAPage::OnCbnSelchangeComboPreset()
{
	if (m_cboPreset.GetCurSel() == -1)
	{
		return;
	}
	GotoPreset(m_cboPreset.GetCurSel(), 0, 3);     
	UI_UpdateGraph();
}

int CLS_ITSSetVCAPage::GotoPreset( int _iPreset, int _iDevAddress, int _iComNo )
{
	if (m_iLogonID < 0)
	{
		return -1;
	}

	int iAction = CALL_VIEW;
	CONTROL_PARAM ctrlParam = {0};
	ctrlParam.m_iAddress = _iDevAddress;
	ctrlParam.m_iPreset = _iPreset;

	//Get the real action code
	int iRet = m_tDevCtrl.GetCtrlCode(m_cDeviceType,iAction,&ctrlParam);
	if(0 == iRet)
	{
		CString strOut = Bytes2HexString(ctrlParam.m_btBuf,ctrlParam.m_iCount);
		iRet = NetClient_ComSend(m_iLogonID,ctrlParam.m_btBuf, ctrlParam.m_iCount,_iComNo);
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_ComSend(%d,%s,%d,%d)",m_iLogonID
				,(LPSTR)(LPCTSTR)strOut, ctrlParam.m_iCount,_iComNo);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_ComSend(%d,%s,%d,%d)",m_iLogonID
				,(LPSTR)(LPCTSTR)strOut, ctrlParam.m_iCount,_iComNo);
		}
		return TRUE;
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","GetCtrlCode(%s,%d)",m_cDeviceType,iAction);
		return FALSE;
	}
}

BOOL CLS_ITSSetVCAPage::UI_UpdateDeviceType()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iProductType = 0;
	int iRet = NetClient_GetProductType(m_iLogonID,&iProductType);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetProductType(%d,%d)"
			,m_iLogonID, iProductType);

		iProductType &= 0xFFFF;
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetProductType(%d,%d)"
			,m_iLogonID, iProductType);
	}

	int iChannelNo = 0;
	if (IsDVR(iProductType)||iProductType==0x64)
	{
		iChannelNo = m_iChannelNo;
	}

	int iComNo = 1;
	int iAddress = 0;
	iRet = NetClient_GetDeviceType(m_iLogonID,iChannelNo,&iComNo,&iAddress,m_cDeviceType);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDeviceType(%d,%d,%d,%d,%s)"
			,m_iLogonID,iChannelNo,iComNo,iAddress,m_cDeviceType);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDeviceType(%d,%d,%d,%d,%s)"
			,m_iLogonID,iChannelNo,iComNo,iAddress,m_cDeviceType);
	}
	return TRUE;
}

void CLS_ITSSetVCAPage::OnCancel()
{
	StopPlay();
	CDialog::OnCancel();
}

BOOL CLS_ITSSetVCAPage::UI_UpdateGraph()
{
	if (m_iLogonID < 0)
		return FALSE;

	//清除视频上的所有图形
	POINT pt[2] = {0};
	NetClient_DrawPolyOnLocalVideo(m_uiConnID, pt, 2, 0);
	
	int iPreset = m_cboPreset.GetCurSel();
	int iArea = m_cboArea.GetCurSel();
	int iAreaPram = m_cboParamArea.GetCurSel();
	int iCurSegment = m_cboTimeRange.GetCurSel();

	//重画所有符合的图形
	ITS_IllegalPark tITSIllegalPark = {0};
	for(int i = 0; i < MAX_AREA_COUNT; i++)
	{
		tITSIllegalPark.iAreaNo = i;
		tITSIllegalPark.iPresetNo = iPreset;
		NetClient_GetITSExtraInfo( m_iLogonID, ITS_ILLEGALPARK_CMD_GET,
			NULL, &tITSIllegalPark, sizeof(ITS_IllegalPark));
		if(iArea == i)
		{
			SetDlgItemInt(IDC_EDIT_ILLEGALPARKTIME, tITSIllegalPark.iIllegalParkTime);
			int iRangeTimeStartH = (tITSIllegalPark.iTimeRange[iCurSegment]>>24)&0x000000ff;
			int iRangeTimeStartM = (tITSIllegalPark.iTimeRange[iCurSegment]>>16)&0x000000ff;
			int iRangeTimeEndH = (tITSIllegalPark.iTimeRange[iCurSegment]>>8)&0x000000ff;
			int iRangeTimeEndM = tITSIllegalPark.iTimeRange[iCurSegment]&0x000000ff;
			CTime clsStartTime(1971,1,1,iRangeTimeStartH,iRangeTimeStartM,0);
			CTime clsEndTime(1971,1,1,iRangeTimeEndH,iRangeTimeEndM,0);
			m_dtcFrom.SetTime(&clsStartTime);
			m_dtcTo.SetTime(&clsEndTime);
			SetCoorEditShow(tITSIllegalPark.arrPTArea, 5, 0);
			SetDlgItemInt(IDC_EDIT_PARKTIME, tITSIllegalPark.iCheckParkTime);
			SetDlgItemInt(IDC_EDIT_SENSITIVITY, tITSIllegalPark.iSensitivity);
		}
		//粗略判断是否画了此四边形
		if(0 == tITSIllegalPark.arrPTArea[3].y && 0 == tITSIllegalPark.arrPTArea[1].y)
		{
			if(iAreaPram == i)
			{
				POINT pt[2] = {0};
				for(int m = 0; m < 4; m++)
				{
					SetCoorEditShow(pt, m+1, 1);
				}
			}
		}
		//有此四边形
		else
		{
			AddOrDelPolygon(true);       //增加一个图形
			DrawITSQuadRangle(tITSIllegalPark.arrPTArea, 4);

			ITS_IllegalParkParm tITSIllegalParkParm = {0};
			tITSIllegalParkParm.iAreaNo = i;
			tITSIllegalParkParm.iPresetNo = iPreset;
			NetClient_GetITSExtraInfo( m_iLogonID, ITS_ILLEGALPARKPARM_CMD_GET,
				NULL, &tITSIllegalParkParm, sizeof(ITS_IllegalParkParm));

			for(int j = 0; j < MAX_PARAM_COUNT; j++)
			{
				//粗略判断是否画了此矩形
				if(0 == tITSIllegalParkParm.arrPTParam[j][0].y && 0 == tITSIllegalParkParm.arrPTParam[j][1].y)
				{
					//未画此矩形，继续判断
					//trace("%d无矩形%d\n",i,j);
				}
				else
				{
					AddOrDelPolygon(true);       //增加一个图形
					DrawRect(tITSIllegalParkParm.arrPTParam[j]);
				}
				if(iAreaPram == i)
				{
					SetCoorEditShow(tITSIllegalParkParm.arrPTParam[j], j+1, 1);
				}
			}
		}
	}
	AddOrDelPolygon(true); //保护图形不被下一次改动
	return TRUE;
}

void CLS_ITSSetVCAPage::SetCoorEditShow( POINT *_ptPoint, int _iN0, int flag )
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
				SetDlgItemInt(IDC_EDIT_POINT1_X, _ptPoint->x);
				SetDlgItemInt(IDC_EDIT_POINT1_Y, _ptPoint->y);
				break;
			}
		case 2:
			{
				SetDlgItemInt(IDC_EDIT_POINT2_X, _ptPoint->x);
				SetDlgItemInt(IDC_EDIT_POINT2_Y, _ptPoint->y);
				break;
			}
		case 3:
			{
				SetDlgItemInt(IDC_EDIT_POINT3_X, _ptPoint->x);
				SetDlgItemInt(IDC_EDIT_POINT3_Y, _ptPoint->y);
				break;
			}
		case 4:
			{
				SetDlgItemInt(IDC_EDIT_POINT4_X, _ptPoint->x);
				SetDlgItemInt(IDC_EDIT_POINT4_Y, _ptPoint->y);
				break;
			}
		case 5:   //设置所有
			{
				SetDlgItemInt(IDC_EDIT_POINT1_X, _ptPoint[0].x);
				SetDlgItemInt(IDC_EDIT_POINT1_Y, _ptPoint[0].y);
				SetDlgItemInt(IDC_EDIT_POINT2_X, _ptPoint[1].x);
				SetDlgItemInt(IDC_EDIT_POINT2_Y, _ptPoint[1].y);
				SetDlgItemInt(IDC_EDIT_POINT3_X, _ptPoint[2].x);
				SetDlgItemInt(IDC_EDIT_POINT3_Y, _ptPoint[2].y);
				SetDlgItemInt(IDC_EDIT_POINT4_X, _ptPoint[3].x);
				SetDlgItemInt(IDC_EDIT_POINT4_Y, _ptPoint[3].y);
				break;
			}
		default:
			break;
		}
	}
	else if(1 == flag)
	{
		switch(_iN0)
		{
		case 1:
			{
				SetDlgItemInt(IDC_EDIT_RECT1_POINT1_X, _ptPoint[0].x);
				SetDlgItemInt(IDC_EDIT_RECT1_POINT1_Y, _ptPoint[0].y);
				SetDlgItemInt(IDC_EDIT_RECT1_POINT2_X, _ptPoint[1].x);
				SetDlgItemInt(IDC_EDIT_RECT1_POINT2_Y, _ptPoint[1].y);
				break;
			}
		case 2:
			{
				SetDlgItemInt(IDC_EDIT_RECT2_POINT1_X, _ptPoint[0].x);
				SetDlgItemInt(IDC_EDIT_RECT2_POINT1_Y, _ptPoint[0].y);
				SetDlgItemInt(IDC_EDIT_RECT2_POINT2_X, _ptPoint[1].x);
				SetDlgItemInt(IDC_EDIT_RECT2_POINT2_Y, _ptPoint[1].y);
				break;
			}
		case 3:
			{
				SetDlgItemInt(IDC_EDIT_RECT3_POINT1_X, _ptPoint[0].x);
				SetDlgItemInt(IDC_EDIT_RECT3_POINT1_Y, _ptPoint[0].y);
				SetDlgItemInt(IDC_EDIT_RECT3_POINT2_X, _ptPoint[1].x);
				SetDlgItemInt(IDC_EDIT_RECT3_POINT2_Y, _ptPoint[1].y);
				break;
			}
		case 4:
			{
				SetDlgItemInt(IDC_EDIT_RECT4_POINT1_X, _ptPoint[0].x);
				SetDlgItemInt(IDC_EDIT_RECT4_POINT1_Y, _ptPoint[0].y);
				SetDlgItemInt(IDC_EDIT_RECT4_POINT2_X, _ptPoint[1].x);
				SetDlgItemInt(IDC_EDIT_RECT4_POINT2_Y, _ptPoint[1].y);
				break;
			}
		default:
			break;
		}
	}
}

void CLS_ITSSetVCAPage::GetCoorEditShow( POINT *_ptPoint, int _iN0, int flag )
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
				_ptPoint->x = GetDlgItemInt(IDC_EDIT_POINT1_X);
				_ptPoint->y = GetDlgItemInt(IDC_EDIT_POINT1_Y);
				break;
			}
		case 2:
			{
				_ptPoint->x = GetDlgItemInt(IDC_EDIT_POINT2_X);
				_ptPoint->y = GetDlgItemInt(IDC_EDIT_POINT2_Y);
				break;
			}
		case 3:
			{
				_ptPoint->x = GetDlgItemInt(IDC_EDIT_POINT3_X);
				_ptPoint->y = GetDlgItemInt(IDC_EDIT_POINT3_Y);
				break;
			}
		case 4:
			{
				_ptPoint->x = GetDlgItemInt(IDC_EDIT_POINT4_X);
				_ptPoint->y = GetDlgItemInt(IDC_EDIT_POINT4_Y);
				break;
			}
		case 5:   //设置所有
			{
				_ptPoint[0].x = GetDlgItemInt(IDC_EDIT_POINT1_X);
				_ptPoint[0].y = GetDlgItemInt(IDC_EDIT_POINT1_Y);
				_ptPoint[1].x = GetDlgItemInt(IDC_EDIT_POINT2_X);
				_ptPoint[1].y = GetDlgItemInt(IDC_EDIT_POINT2_Y);
				_ptPoint[2].x = GetDlgItemInt(IDC_EDIT_POINT3_X);
				_ptPoint[2].y = GetDlgItemInt(IDC_EDIT_POINT3_Y);
				_ptPoint[3].x = GetDlgItemInt(IDC_EDIT_POINT4_X);
				_ptPoint[3].y = GetDlgItemInt(IDC_EDIT_POINT4_Y);
				break;
			}
		default:
			break;
		}
	}
	else if(1 == flag)
	{
		switch(_iN0)
		{
		case 1:
			{    //从界面上获取矩形对称两点坐标，转化后，保存四点坐标
				_ptPoint[0].x = GetDlgItemInt(IDC_EDIT_RECT1_POINT1_X);
				_ptPoint[0].y = GetDlgItemInt(IDC_EDIT_RECT1_POINT1_Y);
				_ptPoint[1].x = GetDlgItemInt(IDC_EDIT_RECT1_POINT2_X);
				_ptPoint[1].y = GetDlgItemInt(IDC_EDIT_RECT1_POINT1_Y);
				_ptPoint[2].x = GetDlgItemInt(IDC_EDIT_RECT1_POINT2_X);
				_ptPoint[2].y = GetDlgItemInt(IDC_EDIT_RECT1_POINT2_Y);
				_ptPoint[3].x = GetDlgItemInt(IDC_EDIT_RECT1_POINT1_X);
				_ptPoint[3].y = GetDlgItemInt(IDC_EDIT_RECT1_POINT2_Y);
				break;
			}
		case 2:
			{
				_ptPoint[0].x = GetDlgItemInt(IDC_EDIT_RECT2_POINT1_X);
				_ptPoint[0].y = GetDlgItemInt(IDC_EDIT_RECT2_POINT1_Y);
				_ptPoint[1].x = GetDlgItemInt(IDC_EDIT_RECT2_POINT2_X);
				_ptPoint[1].y = GetDlgItemInt(IDC_EDIT_RECT2_POINT1_Y);
				_ptPoint[2].x = GetDlgItemInt(IDC_EDIT_RECT2_POINT2_X);
				_ptPoint[2].y = GetDlgItemInt(IDC_EDIT_RECT2_POINT2_Y);
				_ptPoint[3].x = GetDlgItemInt(IDC_EDIT_RECT2_POINT1_X);
				_ptPoint[3].y = GetDlgItemInt(IDC_EDIT_RECT2_POINT2_Y);
				break;
			}
		case 3:
			{
				_ptPoint[0].x = GetDlgItemInt(IDC_EDIT_RECT3_POINT1_X);
				_ptPoint[0].y = GetDlgItemInt(IDC_EDIT_RECT3_POINT1_Y);
				_ptPoint[1].x = GetDlgItemInt(IDC_EDIT_RECT3_POINT2_X);
				_ptPoint[1].y = GetDlgItemInt(IDC_EDIT_RECT3_POINT1_Y);
				_ptPoint[2].x = GetDlgItemInt(IDC_EDIT_RECT3_POINT2_X);
				_ptPoint[2].y = GetDlgItemInt(IDC_EDIT_RECT3_POINT2_Y);
				_ptPoint[3].x = GetDlgItemInt(IDC_EDIT_RECT3_POINT1_X);
				_ptPoint[3].y = GetDlgItemInt(IDC_EDIT_RECT3_POINT2_Y);
				break;
			}
		case 4:
			{
				_ptPoint[0].x = GetDlgItemInt(IDC_EDIT_RECT4_POINT1_X);
				_ptPoint[0].y = GetDlgItemInt(IDC_EDIT_RECT4_POINT1_Y);
				_ptPoint[1].x = GetDlgItemInt(IDC_EDIT_RECT4_POINT2_X);
				_ptPoint[1].y = GetDlgItemInt(IDC_EDIT_RECT4_POINT1_Y);
				_ptPoint[2].x = GetDlgItemInt(IDC_EDIT_RECT4_POINT2_X);
				_ptPoint[2].y = GetDlgItemInt(IDC_EDIT_RECT4_POINT2_Y);
				_ptPoint[3].x = GetDlgItemInt(IDC_EDIT_RECT4_POINT1_X);
				_ptPoint[3].y = GetDlgItemInt(IDC_EDIT_RECT4_POINT2_Y);
				break;
			}
		default:
			break;
		}
	}
}
int CLS_ITSSetVCAPage::AddOrDelPolygon( bool _bFlag /*= true*/ )
{
	POINT pt[2] = {0};
	if(_bFlag)
	{
		NetClient_DrawPolyOnLocalVideo(m_uiConnID, pt, 2, 3);
	}
	else
	{
		NetClient_DrawPolyOnLocalVideo(m_uiConnID, pt, 2, 4);
	}
	return 1;
}

int CLS_ITSSetVCAPage::DrawITSQuadRangle( POINT *_ptPolygon, int _ptSum )
{
	POINT pt[10] = {0};
	pt[_ptSum] = *_ptPolygon;
	memcpy(pt, _ptPolygon, _ptSum * sizeof(POINT));
	NetClient_DrawPolyOnLocalVideo(m_uiConnID, pt, _ptSum+1, 4);
	return 1;
}

int CLS_ITSSetVCAPage::DrawRect( POINT *_ptRect )
{
	POINT pt[4] = {0};
	pt[0] = _ptRect[0];
	pt[1].x = _ptRect[1].x;
	pt[1].y = _ptRect[0].y;
	pt[2] = _ptRect[1];
	pt[3].x = _ptRect[0].x;
	pt[3].y = _ptRect[1].y;
	DrawITSQuadRangle(pt, 4);
	return 1;
}
void CLS_ITSSetVCAPage::OnCbnSelchangeComboArea()
{
	if (m_cboPreset.GetCurSel() == -1)
	{
		return;
	}
	UI_UpdateGraph();    //更新视频图形显示，未设置成功的图形去掉
}

void CLS_ITSSetVCAPage::OnCbnSelchangeComboTimerange()
{
	if (m_cboTimeRange.GetCurSel() == -1)
	{
		return;
	}
	UI_UpdateGraph();
}

void CLS_ITSSetVCAPage::OnBnClickedButtonReset()
{
	if (m_cboPreset.GetCurSel() == -1)
	{
		return;
	}
	m_iPointCount = 0;
	ITS_IllegalPark tITSIllegalPark = {0};
	int iArea = m_cboArea.GetCurSel();
	int iPreset = m_cboPreset.GetCurSel();
	tITSIllegalPark.iAreaNo = iArea;
	tITSIllegalPark.iPresetNo = iPreset;
	NetClient_SetITSExtraInfo(m_iLogonID, ITS_ILLEGALPARK_CMD_SET,
		NULL, &tITSIllegalPark, sizeof(ITS_IllegalPark));

	ITS_IllegalParkParm tITSIllegalParkParm = {0};
	tITSIllegalParkParm.iAreaNo = iArea;
	tITSIllegalParkParm.iPresetNo = iPreset;
	NetClient_SetITSExtraInfo(m_iLogonID, ITS_ILLEGALPARKPARM_CMD_SET, NULL,
		&tITSIllegalParkParm, sizeof(ITS_IllegalParkParm));
	UI_UpdateGraph();    //更新视频图形显示，未设置成功的图形去掉
}

void CLS_ITSSetVCAPage::OnBnClickedButtonSet()
{
	if (m_cboPreset.GetCurSel() == -1)
	{
		return;
	}
	if (-1 == GetDlgItemInt(IDC_EDIT_ILLEGALPARKTIME))
	{
		MessageBox("lbllIIParkTime must be digit","Info",MB_OK);
		return;
	}
	else if (GetDlgItemInt(IDC_EDIT_ILLEGALPARKTIME) > 3600 && GetDlgItemInt(IDC_EDIT_ILLEGALPARKTIME) < 0)
	{
		MessageBox("lbllIIParkTime should  between 0 and 3600","Info",MB_OK);
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

	tITSIllegalPark.iIllegalParkTime = GetDlgItemInt(IDC_EDIT_ILLEGALPARKTIME);
	tITSIllegalPark.iTimeRange[iCurSegment] = ((iRangeTimeStartH<<24) & 0xff000000) |   //开始小时放在int类型24~31位
		((iRangeTimeStartM<<16) & 0x00ff0000) | //开始分钟放在int类型16~23位
		((iRangeTimeEndH<<8) & 0x0000ff00) |                  //结束小时放在int类型8~15位
		(iRangeTimeEndM&0x000000ff);                          //结束分钟放在int类型0~7位
	GetCoorEditShow(tITSIllegalPark.arrPTArea, 5, 0);           //把界面上坐标数据写入tITSIllegalPark.arrPTArea数组
	tITSIllegalPark.iCheckParkTime = GetDlgItemInt(IDC_EDIT_ILLEGALPARKTIME);
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
	iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_ILLEGALPARK_CMD_SET,
		NULL, &tITSIllegalPark, sizeof(ITS_IllegalPark));
	if(iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo(ITS_ILLEGALPARK_CMD_SET)");
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo(ITS_ILLEGALPARK_CMD_SET)");
	}
}

void CLS_ITSSetVCAPage::OnCbnSelchangeComboParamArea()
{
	if (-1 == m_cboPreset.GetCurSel())
	{
		return;
	}
	UI_UpdateGraph();
}

void CLS_ITSSetVCAPage::OnBnClickedButtonParamReset()
{
	if (-1 == m_cboPreset.GetCurSel())
	{
		return;
	}
	ITS_IllegalParkParm tITSIllegalParkParm = {0};
	tITSIllegalParkParm.iPresetNo = m_cboPreset.GetCurSel();
	tITSIllegalParkParm.iAreaNo = m_cboParamArea.GetCurSel();
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_ILLEGALPARKPARM_CMD_SET, NULL,
		&tITSIllegalParkParm, sizeof(ITS_IllegalParkParm));
	UI_UpdateGraph();
}

void CLS_ITSSetVCAPage::OnBnClickedButtonParamSet()
{
	if (-1 == m_cboPreset.GetCurSel())
	{
		return;
	}
	ITS_IllegalParkParm tITSIllegalParkParm;
	tITSIllegalParkParm.iPresetNo = m_cboPreset.GetCurSel();
	tITSIllegalParkParm.iAreaNo = m_cboParamArea.GetCurSel();
	tITSIllegalParkParm.arrPTParam[0][0].x = GetDlgItemInt(IDC_EDIT_RECT1_POINT1_X);
	tITSIllegalParkParm.arrPTParam[0][0].y = GetDlgItemInt(IDC_EDIT_RECT1_POINT1_Y);
	tITSIllegalParkParm.arrPTParam[0][1].x = GetDlgItemInt(IDC_EDIT_RECT1_POINT2_X);
	tITSIllegalParkParm.arrPTParam[0][1].y = GetDlgItemInt(IDC_EDIT_RECT1_POINT2_Y);
	
	tITSIllegalParkParm.arrPTParam[1][0].x = GetDlgItemInt(IDC_EDIT_RECT2_POINT1_X);
	tITSIllegalParkParm.arrPTParam[1][0].y = GetDlgItemInt(IDC_EDIT_RECT2_POINT1_Y);
	tITSIllegalParkParm.arrPTParam[1][1].x = GetDlgItemInt(IDC_EDIT_RECT2_POINT2_X);
	tITSIllegalParkParm.arrPTParam[1][1].y = GetDlgItemInt(IDC_EDIT_RECT2_POINT2_Y);

	tITSIllegalParkParm.arrPTParam[2][0].x = GetDlgItemInt(IDC_EDIT_RECT3_POINT1_X);
	tITSIllegalParkParm.arrPTParam[2][0].y = GetDlgItemInt(IDC_EDIT_RECT3_POINT1_Y);
	tITSIllegalParkParm.arrPTParam[2][1].x = GetDlgItemInt(IDC_EDIT_RECT3_POINT2_X);
	tITSIllegalParkParm.arrPTParam[2][1].y = GetDlgItemInt(IDC_EDIT_RECT3_POINT2_Y);

	tITSIllegalParkParm.arrPTParam[3][0].x = GetDlgItemInt(IDC_EDIT_RECT4_POINT1_X);
	tITSIllegalParkParm.arrPTParam[3][0].y = GetDlgItemInt(IDC_EDIT_RECT4_POINT1_Y);
	tITSIllegalParkParm.arrPTParam[3][1].x = GetDlgItemInt(IDC_EDIT_RECT4_POINT2_X);
	tITSIllegalParkParm.arrPTParam[3][1].y = GetDlgItemInt(IDC_EDIT_RECT4_POINT2_Y);
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_ILLEGALPARKPARM_CMD_SET, NULL,
		&tITSIllegalParkParm, sizeof(ITS_IllegalParkParm));
	if(iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo(ITS_ILLEGALPARKPARM_CMD_SET)");

	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo(ITS_ILLEGALPARKPARM_CMD_SET)");
	}
}


void CLS_ITSSetVCAPage::OnBnClickedButtonParamExactfix()
{
	//判断数据是否全部选择 发送定位数据
	if(iFixRect == -1)
	{
		MessageBox("please select Rect first","Info",MB_OK);
		return;
	}
	ITS_ExactConfirm tExactConfirm = {0};
	tExactConfirm.iPresetNo = iFixPreset;
	tExactConfirm.iAreaNo = iFixArea;
	tExactConfirm.iLocalPos1 = iFixRect;
	NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXACTCONFIRM_CMD_SET,
		NULL, &tExactConfirm, sizeof(ITS_ExactConfirm));
	iFixPreset = -1;       // 精确定位的预置位
	iFixArea  = -1;        // 精确定位的区域
	iFixRect  = -1;        // 精确定位的区域中四边形
	AddOrDelPolygon(false);
}

void CLS_ITSSetVCAPage::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser )
{
	switch (_iWparam)
	{
	case WCM_VIDEO_HEAD_EX:
		{
			CRect rect(0,0,0,0);
			NetClient_StartPlay(m_uiConnID, m_hPlayWnd, rect, H264DEC_DECTWO);
		}
		break;
	}
}

void CLS_ITSSetVCAPage::OnLButtonUp( UINT nFlags, CPoint point )
{
	if (IsInsideVideoStatic(point))
	{
		m_ptCur = (POINT)point;
		PolygonOnViedo(&m_ptCur, 1);
		if(2 == m_iCurDrawGrh) //画四边形内矩形
		{
			m_iCurDrawGrh = 0;
			m_ptSet[1] = m_ptCur;
			m_bMouseDown = false;
			if(false == IfRectValidAndDraw(m_ptSet))
			{
				AddOrDelPolygon(false);       //删除当前图形
			}
			AddOrDelPolygon(true);       //增加一个图形，提供给下一次画图形用，保护当前图形不被修改
		}
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CLS_ITSSetVCAPage::OnLButtonDown( UINT nFlags, CPoint point )
{
	if (-1 == m_cboPreset.GetCurSel())
	{
		return;
	}
	if (IsInsideVideoStatic(point))
	{
		m_ptCur = (POINT)point;
		PolygonOnViedo(&m_ptCur, 1);
		m_bMouseDown = true;
		int iPos = 0;
		iPos =  WhichAreaOfCurPt();   //获取当前点在视频中哪个位置
		int iii = GetDlgItemInt(IDC_EDIT_POINT4_Y);
		if(0 == iPos && 0 == GetDlgItemInt(IDC_EDIT_POINT4_Y))
		{
			m_iCurDrawGrh = 1;
			m_ptSet[m_iPointCount] = m_ptCur;

			SetCoorEditShow(m_ptSet+m_iPointCount, m_iPointCount + 1, 0);
			m_iPointCount++;
			if(4 == m_iPointCount)
			{
				ChangePoint();                     //交换四点坐标，使四点连线成为一个四边形，没有相交线
				if(false == IfPolygonValidAndDraw(m_ptSet,4))//假如四边形与其他四边形相交，没有画四边形成功
				{
					POINT pt[4] = {0};
					SetCoorEditShow(pt, 5, 0);
					AddOrDelPolygon(false);       //删除当前图形
				}
				//假如此四边形符合要求
				AddOrDelPolygon(true);            //增加一个图形，提供给下一次画图形用，保护当前图形不被修改
				m_iPointCount = 0;
				m_iCurDrawGrh = 0;
			}
		}
		else if (0 == iPos%10 && 0 == GetDlgItemInt(IDC_EDIT_RECT4_POINT2_Y))
		{
			if(0 == m_iCurDrawGrh)
			{
				//画矩形
				m_iCurDrawGrh = 2;
				m_ptSet[0] = m_ptCur;
				m_bMouseDown = true;
			}
		}
		else if (0 != iPos%10)
		{
			iFixPreset = m_cboPreset.GetCurSel();	 // 精确定位的预置位
			iFixArea  = iPos/10 -1;        // 精确定位的区域
			iFixRect  = iPos%10 -1;        // 精确定位的区域中四边形

			ITS_IllegalParkParm tITSIllegalParkParm;
			memset(&tITSIllegalParkParm, 0, sizeof(ITS_IllegalParkParm));
			tITSIllegalParkParm.iAreaNo = iFixArea;
			tITSIllegalParkParm.iPresetNo = iFixPreset;
			NetClient_GetITSExtraInfo( m_iLogonID, ITS_ILLEGALPARKPARM_CMD_GET,
				NULL, &tITSIllegalParkParm, sizeof(ITS_IllegalParkParm));
			tITSIllegalParkParm.arrPTParam[iFixRect][0].x -= 2;
			tITSIllegalParkParm.arrPTParam[iFixRect][0].y -= 1;
			tITSIllegalParkParm.arrPTParam[iFixRect][1].x += 2;
			tITSIllegalParkParm.arrPTParam[iFixRect][1].y += 1;

			DrawRect(tITSIllegalParkParm.arrPTParam[iFixRect]);
		}
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CLS_ITSSetVCAPage::OnMouseMove( UINT nFlags, CPoint point )
{
	if (m_bMouseDown)
	{
		if (IsInsideVideoStatic(point))
		{
			m_ptCur = (POINT)point;
			PolygonOnViedo(&m_ptCur, 1);
			if(1 == m_iCurDrawGrh)     //画四边形中
			{
				m_ptSet[m_iPointCount] = m_ptCur;
				int iRet = NetClient_DrawPolyOnLocalVideo(m_uiConnID, m_ptSet, m_iPointCount + 1, 4);
			}
			else if(2 == m_iCurDrawGrh)  //画矩形中
			{
				m_ptSet[1] = m_ptCur;
				DrawRect(m_ptSet);
			}
		}
	}
	CDialog::OnMouseMove(nFlags, point);
}

BOOL CLS_ITSSetVCAPage::IsInsideVideoStatic( POINT _pt )
{
	RECT rcVideo = {0};
	m_pstxtPlayWnd->GetWindowRect(&rcVideo);
	ScreenToClient(&rcVideo);

	if (_pt.x <= rcVideo.right && _pt.x >= rcVideo.left)
	{
		if (_pt.y <= rcVideo.bottom && _pt.y >= rcVideo.top)
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CLS_ITSSetVCAPage::PolygonOnViedo( POINT *_ptArr, int _iPointCnt )
{
	BOOL  bRet = FALSE;
	if (_ptArr == NULL && _iPointCnt <= 0)
	{
		return bRet;
	}

	int iVHeight = 0;
	int iVWidth = 0;
	if (NetClient_GetVideoSize)
	{
		NetClient_GetVideoSize(m_iLogonID, m_iChannelNo, &iVWidth, &iVHeight, m_iStreamNo);

		CRect localRect;
		GetDlgItem(IDC_STATIC_PLAYWND)->GetClientRect(&localRect);

		const double dRateWidth = (double)iVWidth/localRect.Width();
		const double dRateHeight = (double)iVHeight/localRect.Height();

		for (int i=0; i<_iPointCnt; i++)
		{
			_ptArr[i].x = (LONG)(_ptArr[i].x * dRateWidth);
			if (_ptArr[i].x > iVWidth)
			{
				_ptArr[i].x = iVWidth;
				bRet = TRUE;
			}
			if (_ptArr[i].x < 0)
			{
				_ptArr[i].x = 0;
				bRet = TRUE;
			}
			_ptArr[i].y = (LONG)(_ptArr[i].y * dRateHeight);
			if (_ptArr[i].y > iVHeight)
			{
				_ptArr[i].y = iVHeight;
				bRet = TRUE;
			}
			if (_ptArr[i].y < 0)
			{
				_ptArr[i].y = 0;
				bRet = TRUE;
			}
		}
	}
	return bRet;
}

//判断当前矩形是否与其他矩形相交，并且是否在当前四边形内 ，如果如何要求则画出此矩形
bool CLS_ITSSetVCAPage::IfRectValidAndDraw( POINT *_ptRect )
{
	//判断是否在当前四边形内  不是则返回false，就不用画矩形
	ITS_IllegalPark tITSIllegalPark;
	memset(&tITSIllegalPark, 0, sizeof(ITS_IllegalPark));
	tITSIllegalPark.iAreaNo = m_cboParamArea.GetCurSel();
	tITSIllegalPark.iPresetNo = m_cboPreset.GetCurSel();
	NetClient_GetITSExtraInfo( m_iLogonID, ITS_ILLEGALPARK_CMD_GET,
		NULL, &tITSIllegalPark, sizeof(ITS_IllegalPark));
	//1、粗略判断是否有此四边形
	if(0 == tITSIllegalPark.arrPTArea[3].y && 0 == tITSIllegalPark.arrPTArea[1].y)
	{
		//trace("%d无此四边形\n",i);
		return false;
	}
	//2、有此四边形，判断点是否在四边形内
	else if(!IfPointInPolygon(_ptRect[0], tITSIllegalPark.arrPTArea, 4))
	{
		return false;
	}

	//判断此矩形与四边形以及四边形内的其他矩形是否相交
	POINT ptCur[4] = {0};
	ptCur[0] = _ptRect[0];
	ptCur[1].x = _ptRect[1].x;
	ptCur[1].y = _ptRect[0].y;
	ptCur[2] = _ptRect[1];
	ptCur[3].x = _ptRect[0].x;
	ptCur[3].y = _ptRect[1].y;
	//1、判断是否与四边形相交
	if(IfPolygonIntersect(ptCur, 4, tITSIllegalPark.arrPTArea, 4))
	{
		return false;
	}
	//2、判断是否与其他矩形相交
	POINT ptCmp[4] = {0};
	for (int i = 0; i < 4; i++)
	{
		GetCoorEditShow(ptCmp, i+1, 1);
		if(0 == ptCmp[0].x && 0 == ptCmp[0].y && 0 == ptCmp[2].x && 0 == ptCmp[2].y)
		{
			DrawRect(_ptRect);
			SetCoorEditShow(_ptRect, i+1, 1);
			return true;
		}
		else if(IfPolygonIntersect(ptCur, 4, ptCmp, 4))
		{
			return false;
		}
		else if(IfPolygonInPolygon(ptCur, 4, ptCmp, 4))
		{
			return false;
		}
	}
	return true;
}

int CLS_ITSSetVCAPage::WhichAreaOfCurPt( void )
{
	ITS_IllegalPark tITSIllegalPark;
	memset(&tITSIllegalPark, 0, sizeof(ITS_IllegalPark));
	int iPreset = m_cboPreset.GetCurSel();
	for(int i = 0; i < MAX_AREA_COUNT; i++)
	{
		tITSIllegalPark.iAreaNo = i;
		tITSIllegalPark.iPresetNo = iPreset;
		NetClient_GetITSExtraInfo( m_iLogonID, ITS_ILLEGALPARK_CMD_GET,
			NULL, &tITSIllegalPark, sizeof(ITS_IllegalPark));
		//粗略判断是否画了此四边形
		if(0 == tITSIllegalPark.arrPTArea[3].y && 0 == tITSIllegalPark.arrPTArea[1].y)
		{
			//无四边形
		}
		//有此四边形，判断点是否在此四边形内
		else if(IfPointInPolygon(m_ptCur, tITSIllegalPark.arrPTArea))
		{
			//在此四边形内部 判断是否在哪个矩形内
			ITS_IllegalParkParm tITSIllegalParkParm;
			memset(&tITSIllegalParkParm, 0, sizeof(ITS_IllegalParkParm));
			tITSIllegalParkParm.iAreaNo = i;
			tITSIllegalParkParm.iPresetNo = iPreset;
			NetClient_GetITSExtraInfo( m_iLogonID, ITS_ILLEGALPARKPARM_CMD_GET,
				NULL, &tITSIllegalParkParm, sizeof(ITS_IllegalParkParm));
			for(int j = 0; j < MAX_PARAM_COUNT; j++)
			{
				//粗略判断是否画了此矩形
				if(0 == tITSIllegalParkParm.arrPTParam[j][0].y && 0 == tITSIllegalParkParm.arrPTParam[j][1].y)
				{
					//未画此矩形，继续判断
					//无四边形
				}
				else
				{
					POINT pt[4] = {0};
					pt[0] = tITSIllegalParkParm.arrPTParam[j][0];
					pt[1].x = tITSIllegalParkParm.arrPTParam[j][1].x;
					pt[1].y = tITSIllegalParkParm.arrPTParam[j][0].y;
					pt[2] = tITSIllegalParkParm.arrPTParam[j][1];
					pt[3].x = tITSIllegalParkParm.arrPTParam[j][0].x;
					pt[3].y = tITSIllegalParkParm.arrPTParam[j][1].y;
					if(IfPointInPolygon(m_ptCur, pt))
					{
						return  (i+1)*10+(j+1);
					}
				}
			}
			return  (i+1)*10;
		}
	}
	return 0;
}
//判断当前四边形 与 存在的其他形状是否相交，都不想交，且符合要求则画出此四边形
bool CLS_ITSSetVCAPage::IfPolygonValidAndDraw( POINT *_ptPolygon, int _iPoly )
{
	ITS_IllegalPark tITSIllegalPark;
	memset(&tITSIllegalPark, 0, sizeof(ITS_IllegalPark));

	for(int i = 0; i < MAX_AREA_COUNT; i++)
	{
		if(i == m_cboArea.GetCurSel())
		{
			continue;
		}
		tITSIllegalPark.iAreaNo = i;
		tITSIllegalPark.iPresetNo = m_cboPreset.GetCurSel();
		NetClient_GetITSExtraInfo( m_iLogonID, ITS_ILLEGALPARK_CMD_GET,
			NULL, &tITSIllegalPark, sizeof(ITS_IllegalPark));
		//粗略判断是否画了此四边形
		if(0 == tITSIllegalPark.arrPTArea[3].y && 0 == tITSIllegalPark.arrPTArea[1].y)
		{
			//trace("%d无此四边形\n",i);
		}
		//有此四边形，判断当前四边形与此四边形是否相交
		else if(IfPolygonIntersect(_ptPolygon, _iPoly, tITSIllegalPark.arrPTArea, 4))
		{
			return false;
		}
		//判断是否相包含
		else if(IfPolygonInPolygon(_ptPolygon, _iPoly, tITSIllegalPark.arrPTArea, 4))
		{
			return false;
		}
	}

	DrawITSQuadRangle(_ptPolygon, _iPoly);
	return true;
}

void CLS_ITSSetVCAPage::ChangePoint( void )
{
	if(IfHaveInterSection(m_ptSet[0],m_ptSet[1],m_ptSet[2],m_ptSet[3]))
	{
		POINT pt = {0};
		pt = m_ptSet[1];
		m_ptSet[1] = m_ptSet[2];
		m_ptSet[2] = pt;
		SetDlgItemInt(IDC_EDIT_POINT2_X, m_ptSet[1].x);
		SetDlgItemInt(IDC_EDIT_POINT2_Y, m_ptSet[1].y);
		SetDlgItemInt(IDC_EDIT_POINT3_X, m_ptSet[2].x);
		SetDlgItemInt(IDC_EDIT_POINT3_Y, m_ptSet[2].y);
	}
	else if(IfHaveInterSection(m_ptSet[1],m_ptSet[2],m_ptSet[0],m_ptSet[3]))
	{
		POINT pt = {0};
		pt = m_ptSet[2];
		m_ptSet[2] = m_ptSet[3];
		m_ptSet[3] = pt;
		SetDlgItemInt(IDC_EDIT_POINT4_X, m_ptSet[3].x);
		SetDlgItemInt(IDC_EDIT_POINT4_Y, m_ptSet[3].y);
		SetDlgItemInt(IDC_EDIT_POINT3_X, m_ptSet[2].x);
		SetDlgItemInt(IDC_EDIT_POINT3_Y, m_ptSet[2].y);
	}
}

void CLS_ITSSetVCAPage::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	//	清空视频上的画线

	POINT pt[2] = {0};
	if(NetClient_DrawPolyOnLocalVideo)
	{
		NetClient_DrawPolyOnLocalVideo(m_uiConnID, pt, 2, 0);
	}

	CLS_BasePage::OnClose();
}


////算法1 判断两条线是否有交点函数
//bool IfHaveInterSection(POINT _ptLine1Start, POINT _ptLine1End, POINT _ptLine2Start, POINT _ptLine2End)     //wxl 2011-11-22
//{
//	double iL1SX = _ptLine1Start.x;
//	double iL1SY = _ptLine1Start.y;
//
//	double iL2SX = _ptLine2Start.x;
//	double iL2SY = _ptLine2Start.y;
//
//	double iL1EX = _ptLine1End.x;
//	double iL1EY = _ptLine1End.y;
//
//	double iL2EX = _ptLine2End.x;
//	double iL2EY = _ptLine2End.y;
//	double fDiv = 0.0;
//	double fInterSX = 0.0;           //假如有焦点 焦点x坐标
//	double fInterSY = 0.0;           //假如有焦点 焦点y坐标
//
//	fDiv = (iL1SX -iL1EX)*(iL2SY -iL2EY) -(iL2SX -iL2EX)*(iL1SY - iL1EY);
//	if(fDiv == 0)
//	{
//		return false;
//	}
//	else
//	{
//		fInterSX = ((iL2SX-iL2EX)*(iL1SX*iL1EY -iL1EX*iL1SY)-(iL1SX-iL1EX)*(iL2SX*iL2EY - iL2EX*iL2SY))/fDiv;
//		fInterSY = ((iL2EX*iL2SY -iL2SX*iL2EY)*(iL1SY-iL1EY)-(iL2SY-iL2EY)*(iL1EX*iL1SY-iL1SX*iL1EY))/fDiv;
//
//		if (fInterSX < max(min(iL1SX,iL1EX),min(iL2SX,iL2EX)) || fInterSX > min(max(iL1SX,iL1EX),max(iL2SX,iL2EX)))
//		{
//			return false;
//		}
//		else if (fInterSY < max(min(iL1SY,iL1EY),min(iL2SY,iL2EY)) || fInterSY > min(max(iL1SY,iL1EY),max(iL2SY,iL2EY)))
//		{
//			return false;
//		}
//		else
//		{
//			return true;      //有交点
//		}
//	}
//}
//
////算法2 点是否在多边形内部  这里默认是四边形 _iPtSum默认为4
////_ptCur 当前点，_ptPolygon 多边形点坐标， 多边形点数
//// 判断方法 从当前点与（0，0）点做一条连线，然后与多边形每条边判断是否有交点，统计一共多少个交点，偶数在外部，奇数在内部
//bool IfPointInPolygon(POINT _ptCur, POINT *_ptPolygon, int _iPtSum)
//{
//	if(_iPtSum < 1)
//		return false;
//	POINT pt = {0};
//	int iPtSum = 0;
//	for(int i = 0; i< _iPtSum - 1; i++)   //判断当前点与（0，0）这点的连线与四边形的四条边共有多少条连线
//	{
//		if(IfHaveInterSection(_ptCur, pt, _ptPolygon[i], _ptPolygon[i+1]))
//			iPtSum++;
//	}
//	//判断当前点与（0，0）这点的连线与四边形的最后一条边是否有交点
//	if(IfHaveInterSection(_ptCur, pt, *_ptPolygon, *(_ptPolygon+ _iPtSum - 1)))
//		iPtSum++;
//
//	if(iPtSum%2)
//	{
//		//trace("在内部\n");
//		return true;
//	}
//	else
//	{
//		//trace("在外部\n");
//		return false;
//	}
//}
//
////算法 判断两个多边形是否相交，这个算法主要是判断两个四边形
//bool IfPolygonIntersect(POINT *_ptPolygon1, int _iPoly1, POINT *_ptPolygon2, int _iPoly2)
//{
//	POINT ptPolygon1[5] = {0};
//	memcpy(ptPolygon1, _ptPolygon1, _iPoly1 * sizeof(POINT));
//	ptPolygon1[_iPoly1] =  _ptPolygon1[0];
//
//	POINT ptPolygon2[5] = {0};
//	memcpy(ptPolygon2, _ptPolygon2, _iPoly2 * sizeof(POINT));
//	ptPolygon2[_iPoly2] =  _ptPolygon2[0];
//
//	for(int i = 0; i < _iPoly1; i++)
//	{
//		for(int j = 0; j < _iPoly2; j++)
//		{
//			if(IfHaveInterSection(*(ptPolygon1+i), *(ptPolygon1+i+1), *(ptPolygon2+j), *(ptPolygon2+j+1)))
//				return true;
//		}
//	}
//	return false;
//}
//
////算法 两个不相交的多边形，判断是否包含
//bool IfPolygonInPolygon(POINT *_ptPolygon1, int _iPoly1, POINT *_ptPolygon2, int _iPoly2)
//{
//	if(IfPointInPolygon(_ptPolygon1[0], _ptPolygon2, _iPoly2))
//	{
//		return true;
//	}
//	if(IfPointInPolygon(_ptPolygon2[0], _ptPolygon1, _iPoly2))
//	{
//		return true;
//	}
//	return false;
//}
