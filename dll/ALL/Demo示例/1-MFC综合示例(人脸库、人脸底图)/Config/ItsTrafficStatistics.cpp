// ItsTrafficStatistics.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ItsTrafficStatistics.h"


// Cls_ItsTrafficStatistics 对话框

IMPLEMENT_DYNAMIC(Cls_ItsTrafficStatistics, CDialog)

Cls_ItsTrafficStatistics::Cls_ItsTrafficStatistics(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(Cls_ItsTrafficStatistics::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
}

Cls_ItsTrafficStatistics::~Cls_ItsTrafficStatistics()
{
}

void Cls_ItsTrafficStatistics::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GP_TRAFFIC_STATIS, m_gpTrafficStatis);
	DDX_Control(pDX, IDC_CHK_USE_TRAFFIC_STATIC, m_chkUseTrafficStatis);
	DDX_Control(pDX, IDC_STC_LABLE_OF_PART_OF_STATIS, m_stcPartOfStatis);
	DDX_Control(pDX, IDC_EDT_INPUT_PART, m_edtInputPart);
	DDX_Control(pDX, IDC_BTN_SET_PART, m_btnSetPart);
	DDX_Control(pDX, IDC_EDT_SHOW_STATIS, m_edtShowPart);
	DDX_Control(pDX, IDC_BTN_CLEAN_UP, m_btnCleanUp);
	DDX_Control(pDX, IDC_CBO_ROADID, m_cboRoadID);
}


BEGIN_MESSAGE_MAP(Cls_ItsTrafficStatistics, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_SET_PART, &Cls_ItsTrafficStatistics::OnBnClickedBtnSetPart)
	ON_BN_CLICKED(IDC_BTN_CLEAN_UP, &Cls_ItsTrafficStatistics::OnBnClickedBtnCleanUp)
	ON_CBN_SELCHANGE(IDC_CBO_ROADID, &Cls_ItsTrafficStatistics::OnCbnSelchangeCboRoadid)
END_MESSAGE_MAP()


// Cls_ItsTrafficStatistics 消息处理程序

BOOL Cls_ItsTrafficStatistics::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	UI_UpdateDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void Cls_ItsTrafficStatistics::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	if(_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo;
	}
	
	UI_UpdateStatis();
}

void Cls_ItsTrafficStatistics::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void Cls_ItsTrafficStatistics::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_GP_TRAFFIC_STATIS, IDS_ITS_TRAFFIC_FROW);
	SetDlgItemTextEx(IDC_CHK_USE_TRAFFIC_STATIC, IDS_ITS_USE_TRAFFIC_FROW);
	SetDlgItemTextEx(IDC_STC_LABLE_OF_PART_OF_STATIS, IDS_ITS_STASTIC_INTERVAL);
	SetDlgItemTextEx(IDC_BTN_CLEAN_UP, IDS_ITS_CLEAR_UP);
	SetDlgItemTextEx(IDC_BTN_SET_PART, IDS_ITS_SET_TRAFFIC_LIGHT_GAIN);
	SetDlgItemTextEx(IDC_STC_ROADID, IDS_CONFIG_ITS_ITSPARAM_ROADID);
	for(int i = 0; i < MAX_ROADWAY_COUNT; i++)
	{
		CString strNo;
		strNo.Format("%d", i);
		InsertString(m_cboRoadID, i, strNo);
	}
	m_cboRoadID.SetCurSel(0);
	m_edtInputPart.SetLimitText(4);
	UI_UpdateStatis();
}
//设置流量统计
void Cls_ItsTrafficStatistics::OnBnClickedBtnSetPart()
{
	int iRet = -1;
	for (int iRoad = 0; iRoad < MAX_ROADWAY_COUNT; iRoad++)//4条车道
	{
		ITSTrafficFlow tSetTrafficFlow;
		memset( &tSetTrafficFlow, 0, sizeof(ITSTrafficFlow));

		tSetTrafficFlow.iBufSize = sizeof(ITSTrafficFlow);
		tSetTrafficFlow.iLaneID = m_cboRoadID.GetCurSel();
		tSetTrafficFlow.iType = 1;
		tSetTrafficFlow.iEnable = m_chkUseTrafficStatis.GetCheck();
		tSetTrafficFlow.iTimeInterval = GetDlgItemInt(IDC_EDT_INPUT_PART);
		iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_TRAFFIC_FLOW, m_iChannelNo, &tSetTrafficFlow, sizeof(ITSTrafficFlow));
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_LIGHTINFO_CMD_GET][ITS_EXTRAINFO_CMD_TRAFFIC_FLOW] (%d, %d)",m_iLogonID, m_iChannelNo);
		} 
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_LIGHTINFO_CMD_GET] (%d, %d),error(%d)",m_iLogonID, m_iChannelNo, GetLastError());
		}
	}
}
void Cls_ItsTrafficStatistics::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser )
{
	////char cOutPut[LEN_256] = {0};
	CString cstrOutPut;
	int iMsgType = LOWORD(_iWparam);
	switch(iMsgType)
	{
	case WCM_ITS_TRAFFICFLOWREPORT:
		{
			ITSTrafficFlowReport strctTrafficFlow = {0};
			ITSTrafficFlowReport* ptITSTrafficFlowReport = (ITSTrafficFlowReport*)_iLParam;
			if (NULL != ptITSTrafficFlowReport)
			{
				//底层没有传长度还是有崩溃的可能，待返测
				int iCpySize = min(ptITSTrafficFlowReport->iSize, sizeof(ITSTrafficFlowReport));
				memcpy(&strctTrafficFlow, ptITSTrafficFlowReport, iCpySize);
			}
			strctTrafficFlow.iLaneID = m_cboRoadID.GetCurSel();
			cstrOutPut.Format("车道: %d\r\n流量: %d\r\n时间占有率: %d\r\n平均速度: %d\r\n车头距离: %d\r\n开始时间: %d年%d月%d日%d:%d:%d\r\n结束时间: %d年%d月%d日%d:%d:%d", 
				strctTrafficFlow.iLaneID, strctTrafficFlow.iFlow, strctTrafficFlow.iHoldRate, strctTrafficFlow.iSpeed, strctTrafficFlow.iDistance,
				strctTrafficFlow.stStartTime.iYear, strctTrafficFlow.stStartTime.iMonth, strctTrafficFlow.stStartTime.iDay,
				strctTrafficFlow.stStartTime.iHour, strctTrafficFlow.stStartTime.iMinute, strctTrafficFlow.stStartTime.iSecond,
				strctTrafficFlow.stStopTime.iYear, strctTrafficFlow.stStopTime.iMonth, strctTrafficFlow.stStopTime.iDay,
				strctTrafficFlow.stStopTime.iHour, strctTrafficFlow.stStopTime.iMinute, strctTrafficFlow.stStopTime.iSecond);

			m_edtShowPart.SetWindowText(cstrOutPut);
		}
		break;
	default:
		break;
	}
}
void Cls_ItsTrafficStatistics::OnBnClickedBtnCleanUp()
{
	m_edtShowPart.SetWindowText("");
}

BOOL Cls_ItsTrafficStatistics::UI_UpdateStatis()
{
	if(m_iLogonID < 0)
		return FALSE;
	
	ITSTrafficFlow tSetTrafficFlow = {0};
	tSetTrafficFlow.iLaneID = m_cboRoadID.GetCurSel();
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_TRAFFIC_FLOW, m_iChannelNo, &tSetTrafficFlow, sizeof(ITSTrafficFlow));
	if(iRet == 0)
	{
		m_chkUseTrafficStatis.SetCheck(tSetTrafficFlow.iEnable);
		SetDlgItemInt(IDC_EDT_INPUT_PART, tSetTrafficFlow.iTimeInterval);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_TRAFFIC_FLOW](%d, %d)",m_iLogonID, m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_TRAFFIC_FLOW](%d, %d),error(%d)",m_iLogonID, m_iChannelNo,GetLastError());
		return FALSE;
	}

	return TRUE;
}

void Cls_ItsTrafficStatistics::OnCbnSelchangeCboRoadid()
{
	UI_UpdateStatis();
}
