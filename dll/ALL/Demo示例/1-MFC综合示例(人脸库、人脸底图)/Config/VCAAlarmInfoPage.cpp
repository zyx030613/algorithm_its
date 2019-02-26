// VCAAlarmInfoPage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAAlarmInfoPage.h"

#define RULE_ALL			0xFF		//规则号支持所有功能
#define SCENE_SUM			16			//场景总数

// CLS_VCAAlarmInfoPage dialog

IMPLEMENT_DYNAMIC(CLS_VCAAlarmInfoPage, CDialog)

extern int g_iEventIDS[VCA_EVENT_MAX];

static vca_TVCAParam g_VcaParam = {0};

CLS_VCAAlarmInfoPage::CLS_VCAAlarmInfoPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_VCAAlarmInfoPage::IDD, pParent)
{
	 m_iLogonID = -1;
	 m_iChannelNo = -1;
	
}

CLS_VCAAlarmInfoPage::~CLS_VCAAlarmInfoPage()
{
}

void CLS_VCAAlarmInfoPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_lstctAlarmInfo);
	DDX_Control(pDX, IDC_COMBO_VCA_ALARM_RULE, m_cboRuleID);
	DDX_Control(pDX, IDC_COMBO_VCA_ALARM_EVENT, m_cboEventID);
	DDX_Control(pDX, IDC_CBO_VCA_ALARMINFO_SCENE_NUM, m_cboSceneID);
	DDX_Control(pDX, IDC_EDT_VCA_ALARM_STATISTIC, m_edtAlarmTimes);
	DDX_Control(pDX, IDC_CHK_VCA_ALARMINFO_VALID, m_chkValid);
}


BEGIN_MESSAGE_MAP(CLS_VCAAlarmInfoPage, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_VCA_ALARM_RULE, &CLS_VCAAlarmInfoPage::OnCbnSelchangeComboVcaAlarmRule)
	ON_BN_CLICKED(IDC_BUTTON_VCA_ALARM_STATISTIC_CLEAR, &CLS_VCAAlarmInfoPage::OnBnClickedButtonVcaAlarmStatisticClear)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_RECORD, &CLS_VCAAlarmInfoPage::OnBnClickedButtonClearRecord)
	ON_CBN_SELCHANGE(IDC_CBO_VCA_ALARMINFO_SCENE_NUM, &CLS_VCAAlarmInfoPage::OnCbnSelchangeCboVcaAlarminfoSceneNum)
	ON_CBN_SELCHANGE(IDC_COMBO_VCA_ALARM_EVENT, &CLS_VCAAlarmInfoPage::OnCbnSelchangeComboVcaAlarmEvent)
END_MESSAGE_MAP()

BOOL CLS_VCAAlarmInfoPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_lstctAlarmInfo.SetExtendedStyle(m_lstctAlarmInfo.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	UI_UpdateText();
	m_lstctAlarmInfo.DeleteAllItems();
	UI_Clear();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAAlarmInfoPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateText();
}

void CLS_VCAAlarmInfoPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	if (m_iLogonID < 0 || m_iChannelNo < 0)
	{
		return;
	}
	UI_Clear();
	UI_UpdateVcaAlarmStatistic();
}

void CLS_VCAAlarmInfoPage::UI_UpdateText()
{
	SetDlgItemTextEx(IDC_STATIC_ALARM_STATISTIC, IDS_VCA_ALARM_STATISTIC);
	SetDlgItemTextEx(IDC_STATIC_VCA_ALARM_RULE, IDS_VCA_RULE_ID);
	SetDlgItemTextEx(IDC_STATIC_VCA_ALARM_EVENT, IDS_VCA_EVENT_ID);
	SetDlgItemTextEx(IDC_STATIC_VCA_ALARM_STATISTIC, IDS_VCA_ALRAM_TIMES);
	SetDlgItemTextEx(IDC_BUTTON_VCA_ALARM_STATISTIC_CLEAR, IDS_VCA_CLEAR_ALARM_STATISTIC);
	SetDlgItemTextEx(IDC_STATIC_ALARM_INFO, IDS_VCA_ALARM_INFO);
	SetDlgItemTextEx(IDC_BUTTON_CLEAR_RECORD, IDS_VCA_CLEAR_RECORD);
	SetDlgItemTextEx(IDC_STC_VCA_ALARMINFO_SCENE_NUM, IDS_AREA_NUM);

	int iColumn = 0;
	InsertColumn(m_lstctAlarmInfo, iColumn++, "IP", LVCFMT_LEFT, 100);
	InsertColumn(m_lstctAlarmInfo, iColumn++, IDS_VCA_CHANNEL_NO, LVCFMT_LEFT, 100);
	InsertColumn(m_lstctAlarmInfo, iColumn++, IDS_VCA_ALARM_STATUS, LVCFMT_LEFT, 100);
	InsertColumn(m_lstctAlarmInfo, iColumn++, IDS_VCA_EVENT_TYPE, LVCFMT_LEFT, 100);
	InsertColumn(m_lstctAlarmInfo, iColumn++, IDS_VCA_RULE_ID, LVCFMT_LEFT, 100);
	InsertColumn(m_lstctAlarmInfo, iColumn++, IDS_VCA_RULENAME, LVCFMT_LEFT, 100);
	InsertColumn(m_lstctAlarmInfo, iColumn++, IDS_VCA_TARGET_ID, LVCFMT_LEFT, 100);
	InsertColumn(m_lstctAlarmInfo, iColumn++, IDS_VCA_TARGET_TYPE, LVCFMT_LEFT, 100);
	InsertColumn(m_lstctAlarmInfo, iColumn++, IDS_VCA_TARGET_POS, LVCFMT_LEFT, 100);
	InsertColumn(m_lstctAlarmInfo, iColumn++, IDS_VCA_TARGET_SPEED, LVCFMT_LEFT, 100);
	InsertColumn(m_lstctAlarmInfo, iColumn++, IDS_VCA_TARGET_DIRECTION, LVCFMT_LEFT, 100);

	m_cboRuleID.ResetContent();
	InsertString(m_cboRuleID, 0, GetTextEx(IDS_PLAYBACK_TYPE_ALL));
	m_cboRuleID.SetItemData(0, RULE_ALL);
	for (int i = 1; i < VCA_MAX_RULE_NUM + 1; i++)
	{
		m_cboRuleID.InsertString(i, IntToCString(i));
		m_cboRuleID.SetItemData(i, i-1);
	}
	m_cboRuleID.SetCurSel(0);

	m_cboSceneID.ResetContent();
	for (int i = 0; i < MAX_SCENE_NUM; i++)
	{
		CString cstSceneID;
		cstSceneID.Format("%d", i + 1);
		m_cboSceneID.InsertString(i, cstSceneID);
	}
	m_cboSceneID.SetCurSel(0);

	m_cboEventID.ResetContent();
	for (int i = 0; i < sizeof(g_iEventIDS)/sizeof(int); i++)
	{
		InsertString(m_cboEventID, i, g_iEventIDS[i]);
	}	
	m_cboEventID.SetCurSel(0);
}

void CLS_VCAAlarmInfoPage::UI_UpdateVcaAlarmStatistic()
{
	if (m_iChannelNo < 0)
	{
		return;
	}

	VCARuleParam  tParam = {0};
	int iSelIndex = m_cboRuleID.GetCurSel();
	tParam.stRule.iRuleID = m_cboRuleID.GetItemData(iSelIndex);
	tParam.stRule.iSceneID = m_cboSceneID.GetCurSel();
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_RULE_PARAM, m_iChannelNo, &tParam, sizeof(VCARuleParam));
	if (iRet < 0 || !tParam.stRule.iValid)
	{
		UI_Clear();
		m_cboEventID.SetCurSel(0);
		return;
	}
 	if (tParam.iEventID == VCA_EVENT_TRIPWIRE || tParam.iEventID == VCA_EVENT_PERIMETER)
 	{
		vca_TVCAParam * vp = &g_VcaParam;
		memset(vp, 0, sizeof(vca_TVCAParam));
		int iRuleID = m_cboRuleID.GetCurSel();
		vp->chnParam[m_iChannelNo].iRuleID =  iRuleID;
		iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_ALARM_STATISTIC, m_iChannelNo, vp, sizeof(vca_TVCAParam));
		vca_TRuleParam *pRule = &(vp->chnParam[m_iChannelNo].rule[iRuleID]);
 		int iAlarmCount = pRule->iAlarmCount;
 		SetDlgItemInt(IDC_EDT_VCA_ALARM_STATISTIC, iAlarmCount);
 	}

 	m_cboEventID.SetCurSel(tParam.iEventID);
}

void CLS_VCAAlarmInfoPage::UI_UpdateVcaAlarmInfo(int _iLogonID, int _iAlarmIndex)
{
	PDEVICE_INFO Device = FindDevice(_iLogonID);
	if (Device == NULL)
	{
		return;
	}
	CString szIP = Device->cIP;
	vca_TAlarmInfo ti = {0};
	int iRetAlarmInfo = NetClient_VCAGetAlarmInfo(_iLogonID, _iAlarmIndex, &ti, sizeof(ti));

	int iCurrentRuleId = (int)m_cboRuleID.GetItemData(m_cboRuleID.GetCurSel());

	if (RULE_ALL == iCurrentRuleId || ti.iRuleID == iCurrentRuleId)
	{
		VCARuleParam stRulePara = {0};
		stRulePara.iBufSize = sizeof(stRulePara);	
		stRulePara.stRule.iRuleID = ti.iRuleID;
		stRulePara.stRule.iSceneID = m_cboSceneID.GetCurSel();

		int iRetConfig = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_RULE_PARAM, m_iChannelNo, &stRulePara, sizeof(stRulePara));
		if ((iRetAlarmInfo >= 0) && (iRetConfig >= 0))
		{
			CString State[2] = {"OFF", "ON"};

			//0：单绊线 1：双绊线 2：周界检测 3：徘徊 4：停车 5：奔跑 6：区域内人员密度 7：被盗物 8：遗弃物 9：人脸识别 10:视频诊断 11:智能跟踪
			//12：流量统计 13：人群聚集  14：离岗检测 15：水位监测 16：音频诊断 17：人脸遮挡(马赛克) 18:河道漂浮物 19：盗采盗卸 20：违章停车 21：打架
			//22：警戒 23：车牌识别(仅NVR使用，交通前端使用的是交通协议)
			//24-热度图 25-积水监测 26-翻窗检测 27-ST人脸识别 28-车位看守 30-安全帽检测算法 31-鱼球联动跟踪 32 闸门检测
			CString EventType[VCA_EVENT_MAX] = {"TRIPWIRE", "DBTRIPWIRE", "PERIMETER", "LOITER", "PARKING", "RUN", "HIGH_DENSITY", "OBJSTOLEN"
				, "ABANDUM", "FACEREC", "VIDEODETECT", "TRACK", "FLUXSTATISTIC", "CROWD", "LEAVE_DETECT", "WATER_LEVEL_DETECT", "AUDIO_DIAGNOSE"
				, "FACE_MOSAIC", "RIVERCLEAN", "DREDGE", "ILLEAGEPARK", "FIGHT", "ALERT", "PLATE_RECOGNISE", "HEAT_MAP", "SEEPER", "WINDOW_DETECTION"
				, "STFACEADVANCE", "PARK_GUARD", "UNKNOWN", "HELMET", "LINK_DOME_TRACK", "SLUICEGATE"};
			CString TargetType[] = {"People", "Thing", "Car"};
			CString AdvType[] = {"NOISE", "CLARITY", "BRIGHT_ABMNL", "COLOR", "FREEZE", "NOSIGNAL", "CHANGE", "INTERFERE", "PTZ_LOST_CTL"};
			int iItemCount = m_lstctAlarmInfo.GetItemCount();
			int iColumn = 0;
			m_lstctAlarmInfo.InsertItem(iItemCount, "");
			CString szChannelNo;
			szChannelNo.Format("%d", ti.iChannel + 1);
			CString szState = State[ti.iState];
			CString szEventType = EventType[ti.iEventType];
			CString szRuleID;
			szRuleID.Format("%d", ti.iRuleID + 1);
			CString szTargetID;
			szTargetID.Format("%u", ti.uiTargetID);
			CString szTargetType;
			if (VCA_EVENT_VIDEODETECT == ti.iEventType)
			{
				if (ti.iTargetType & VCA_AVD_NOISE)
				{
					szTargetType += "[" + AdvType[0] + "]";
				}
				if (ti.iTargetType & VCA_AVD_CLARITY)
				{
					szTargetType += "[" + AdvType[1] + "]";
				}
				if (ti.iTargetType & VCA_AVD_BRIGHT_ABMNL)
				{
					szTargetType += "[" + AdvType[2] + "]";
				}
				if (ti.iTargetType & VCA_ADV_COLOR)
				{
					szTargetType += "[" + AdvType[3] + "]";
				}
				if (ti.iTargetType & VCA_ADV_FREEZE)
				{
					szTargetType += "[" + AdvType[4] + "]";
				}
				if (ti.iTargetType & VCA_ADV_NOSIGNAL)
				{
					szTargetType += "[" + AdvType[5] + "]";
				}
				if (ti.iTargetType & VCA_ADV_CHANGE)
				{
					szTargetType += "[" + AdvType[6] + "]";
				}
				if (ti.iTargetType & VCA_ADV_INTERFERE)
				{
					szTargetType += "[" + AdvType[7] + "]";
				}
				if (ti.iTargetType & VCA_ADV_PTZ_LOST_CTL)
				{
					szTargetType += "[" + AdvType[8] + "]";
				}		
			}
			else
			{
				szTargetType = TargetType[ti.iTargetType];
			}
			CString szRctTarget;
			szRctTarget.Format("(%d,%d,%d,%d)", ti.rctTarget.left, ti.rctTarget.top, ti.rctTarget.right, ti.rctTarget.bottom);
			CString szTargetSpeed;
			szTargetSpeed.Format("%d", ti.iTargetSpeed);
			szTargetSpeed += "pixel/s";
			CString szTargetDirection;
			szTargetDirection.Format("%d", ti.iTargetDirection);

			CString cstRuleName = stRulePara.cRuleName;

			m_lstctAlarmInfo.SetItemText(iItemCount, iColumn++, szIP);
			m_lstctAlarmInfo.SetItemText(iItemCount, iColumn++, szChannelNo);
			m_lstctAlarmInfo.SetItemText(iItemCount, iColumn++, szState);
			m_lstctAlarmInfo.SetItemText(iItemCount, iColumn++, szEventType);
			m_lstctAlarmInfo.SetItemText(iItemCount, iColumn++, szRuleID);
			m_lstctAlarmInfo.SetItemText(iItemCount, iColumn++, cstRuleName);
			m_lstctAlarmInfo.SetItemText(iItemCount, iColumn++, szTargetID);
			m_lstctAlarmInfo.SetItemText(iItemCount, iColumn++, szTargetType);
			m_lstctAlarmInfo.SetItemText(iItemCount, iColumn++, szRctTarget);
			m_lstctAlarmInfo.SetItemText(iItemCount, iColumn++, szTargetSpeed);
			m_lstctAlarmInfo.SetItemText(iItemCount, iColumn++, szTargetDirection);
		}
	}
	UI_UpdateVcaAlarmStatistic();
}

void CLS_VCAAlarmInfoPage::OnBnClickedButtonVcaAlarmStatisticClear()
{
 	if (m_iLogonID < 0 || m_iChannelNo < 0)
 	{
 		return;
 	}
 	int iRuleID = (int)m_cboRuleID.GetItemData(m_cboRuleID.GetCurSel());
 	vca_TVCAParam * vp = &g_VcaParam;
 	memset(vp, 0, sizeof(vca_TVCAParam));
 
 	vp->chnParam[m_iChannelNo].iRuleID = iRuleID;

	if (RULE_ALL == m_cboRuleID.GetItemData(m_cboRuleID.GetCurSel()))
	{
		for (int i = 0;i < m_cboRuleID.GetCount();i++)
		{
			vp->chnParam[m_iChannelNo].iRuleID = (int)m_cboRuleID.GetItemData(i);
			if (RULE_ALL == vp->chnParam[m_iChannelNo].iRuleID)
			{
				continue;
			}
			int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_SET_ALARM_STATISTIC, m_iChannelNo, vp, sizeof(g_VcaParam));
			if (iRet != 0)
			{
				AddLog(LOG_TYPE_FAIL, "", "CLS_VCAAlarmInfoPage::NetClient_VCASetConfig[VCA_CMD_SET_ALARM_STATISTIC] (%d, %d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
			}
			else
			{
				SetDlgItemInt(IDC_EDT_VCA_ALARM_STATISTIC, 0);
				AddLog(LOG_TYPE_SUCC,"","CLS_VCAAlarmInfoPage::NetClient_VCASetConfig[VCA_CMD_SET_ALARM_STATISTIC] (%d, %d)", m_iLogonID, m_iChannelNo);
			}
		}
	}
	else
	{
		int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_SET_ALARM_STATISTIC, m_iChannelNo, vp, sizeof(g_VcaParam));
		if (iRet != 0)
		{
			AddLog(LOG_TYPE_FAIL, "", "CLS_VCAAlarmInfoPage::NetClient_VCASetConfig[VCA_CMD_SET_ALARM_STATISTIC] (%d, %d), error(%d)", m_iLogonID, m_iChannelNo, GetLastError());
		}
		else
		{
			SetDlgItemInt(IDC_EDT_VCA_ALARM_STATISTIC, 0);
			AddLog(LOG_TYPE_SUCC,"","CLS_VCAAlarmInfoPage::NetClient_VCASetConfig[VCA_CMD_SET_ALARM_STATISTIC] (%d, %d)", m_iLogonID, m_iChannelNo);
		}
	}
}


void CLS_VCAAlarmInfoPage::UI_Clear()
{
	SetDlgItemTextEx(IDC_STATIC_VCA_ALARM_STATISTIC, IDS_VCA_ALRAM_TIMES);
}


void CLS_VCAAlarmInfoPage::OnBnClickedButtonClearRecord()
{
	m_lstctAlarmInfo.DeleteAllItems();
}

void CLS_VCAAlarmInfoPage::OnAlarmNotify( int _iLogonID, int _iChannelNo, int _iAlarmState,int _iAlarmType,int _iUserData )
{
	if (_iAlarmType == ALARM_VCA_INFO)
	{
		UI_UpdateVcaAlarmInfo(_iLogonID, _iAlarmState);
	}
}

void CLS_VCAAlarmInfoPage::OnCbnSelchangeCboVcaAlarminfoSceneNum()
{
	if (m_iLogonID < 0 || m_iChannelNo < 0)
	{
		return;
	}
	OnBnClickedButtonVcaAlarmStatisticClear();
	OnBnClickedButtonClearRecord();
	UI_UpdateVcaAlarmStatistic();
}

void CLS_VCAAlarmInfoPage::OnCbnSelchangeComboVcaAlarmEvent()
{
	if (m_iLogonID < 0 || m_iChannelNo < 0)
	{
		return;
	}
	OnBnClickedButtonVcaAlarmStatisticClear();
	OnBnClickedButtonClearRecord();
	UI_UpdateVcaAlarmStatistic();
}

void CLS_VCAAlarmInfoPage::OnCbnSelchangeComboVcaAlarmRule()
{
	if (m_iLogonID < 0 || m_iChannelNo < 0)
	{
		return;
	}
	OnBnClickedButtonVcaAlarmStatisticClear();
	OnBnClickedButtonClearRecord();
	UI_UpdateVcaAlarmStatistic();
}

