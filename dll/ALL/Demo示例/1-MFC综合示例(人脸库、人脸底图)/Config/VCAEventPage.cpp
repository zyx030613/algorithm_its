// VCAEventPage.cpp : implementation file
//

#include "stdafx.h"
#include "VCAEventPage.h"
#include "../Common/CommonFun.h"
#include "AdvLocalSet.h"
#include "../Common/Ini.h"

#define LEN_31				31		//长度为31
// CLS_VCAEventPage dialog

IMPLEMENT_DYNAMIC(CLS_VCAEventPage, CDialog)

CLS_VCAEventPage::CLS_VCAEventPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_VCAEventPage::IDD, pParent)
{
	for(int i=0; i<MAX_EVENT_NUM; i++)
	{
		m_plArrEventPage[i] = NULL;
	}

	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNO = 0;
	m_iSceneID = 0;
}

CLS_VCAEventPage::~CLS_VCAEventPage()
{
	if (NULL != m_pVcaParam)
	{
		free(m_pVcaParam);
		m_pVcaParam = NULL;
	}

	for (int i = 0; i < MAX_EVENT_NUM; ++i)
	{
		if (NULL == m_plArrEventPage[i])
		{
			continue;
		}

		if (IsWindow(m_plArrEventPage[i]->GetSafeHwnd()))
		{
			m_plArrEventPage[i]->DestroyWindow();
		}

		delete m_plArrEventPage[i];
		m_plArrEventPage[i] = NULL;
	}
}

void CLS_VCAEventPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_EVNETID, m_cboEventType);
	DDX_Control(pDX, IDC_STATIC_GROP_EVENTPARAM, m_staticEventGroup);
	DDX_Control(pDX, IDC_COMBO_RULEID, m_cboRuleID);
	DDX_Control(pDX, IDC_CHECK_VALID_RULE, m_chkRuleValid);
	DDX_Control(pDX, IDC_EDIT_RULENAME, m_edtRuleName);
	DDX_Control(pDX, IDC_COMBO_VCA_ENABLE, m_cboEnable);
	DDX_Control(pDX, IDC_COMBO_SCENEID, m_cboSceneID);
	DDX_Control(pDX, IDC_EDIT_SCENENAME, m_cdtSceneName);
	DDX_Control(pDX, IDC_VCA_CHECK1, m_checkVCA[0]);
	DDX_Control(pDX, IDC_VCA_CHECK2, m_checkVCA[1]);
	DDX_Control(pDX, IDC_VCA_CHECK3, m_checkVCA[2]);
	DDX_Control(pDX, IDC_VCA_CHECK4, m_checkVCA[3]);
	DDX_Control(pDX, IDC_VCA_CHECK5, m_checkVCA[4]);
	DDX_Control(pDX, IDC_VCA_CHECK6, m_checkVCA[5]);
	DDX_Control(pDX, IDC_VCA_CHECK7, m_checkVCA[6]);
	DDX_Control(pDX, IDC_VCA_CHECK8, m_checkVCA[7]);
	DDX_Control(pDX, IDC_VCA_CHECK9, m_checkVCA[8]);
}


BEGIN_MESSAGE_MAP(CLS_VCAEventPage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RULE_SET, &CLS_VCAEventPage::OnBnClickedButtonRuleSet)
//	ON_CBN_SELENDCANCEL(IDC_COMBO_EVNETID, &CLS_VCAEventPage::OnCbnSelendcancelComboEvnetid)
	ON_CBN_SELCHANGE(IDC_COMBO_EVNETID, &CLS_VCAEventPage::OnCbnSelchangeComboEvnetid)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_COMBO_RULEID, &CLS_VCAEventPage::OnCbnSelchangeComboRuleid)
	ON_CBN_SELCHANGE(IDC_COMBO_VCA_ENABLE, &CLS_VCAEventPage::OnCbnSelchangeComboVcaEnable)
	ON_BN_CLICKED(IDC_CHECK_VALID_RULE, &CLS_VCAEventPage::OnBnClickedCheckValidRule)
	ON_BN_CLICKED(IDC_BUTTON_SCENEIDSET, &CLS_VCAEventPage::OnBnClickedButtonSceneidset)
	ON_BN_CLICKED(IDC_BUTTON_CALL_SCENE, &CLS_VCAEventPage::OnBnClickedButtonCallScene)
	ON_CBN_SELCHANGE(IDC_COMBO_SCENEID, &CLS_VCAEventPage::OnCbnSelchangeComboSceneid)
	ON_BN_CLICKED(IDC_VCA_CHECK1, &CLS_VCAEventPage::OnBnClickedVcaCheck1)
	ON_BN_CLICKED(IDC_VCA_CHECK3, &CLS_VCAEventPage::OnBnClickedVcaCheck3)
	ON_BN_CLICKED(IDC_VCA_CHECK4, &CLS_VCAEventPage::OnBnClickedVcaCheck4)
	ON_BN_CLICKED(IDC_VCA_CHECK6, &CLS_VCAEventPage::OnBnClickedVcaCheck6)
	ON_BN_CLICKED(IDC_VCA_CHECK8, &CLS_VCAEventPage::OnBnClickedVcaCheck8)
	ON_BN_CLICKED(IDC_VCA_CHECK9, &CLS_VCAEventPage::OnBnClickedVcaCheck9)
END_MESSAGE_MAP()


// CLS_VCAEventPage message handlers

void CLS_VCAEventPage::OnBnClickedButtonRuleSet()
{
	// TODO: Add your control notification handler code here
	int iRuleID = m_cboRuleID.GetCurSel();
	int iIndex = m_cboEventType.GetCurSel();
	int iSelIndex = m_cboEventType.GetItemData(iIndex);
	int iEventID = GetEventIDBySelIndex(iSelIndex);

	vca_TVCAParam *vp = m_pVcaParam;
	if (NULL == vp)
	{
		AddLog(LOG_TYPE_FAIL, "Error!!", "VCA param is NULL.");
		return;
	}
	memset(vp, 0, sizeof(vca_TVCAParam));
	vp->iChannelID = m_iChannelNo;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_CHANNEL, m_iChannelNo, vp, sizeof(vca_TVCAParam));

	bool bVCAChanEnable = false;
	if (iRet >= 0)
		bVCAChanEnable = vp->chnParam[vp->iChannelID].iEnable==1;

	if (!bVCAChanEnable)
		return;

	memset(vp, 0, sizeof(vca_TVCAParam));
	vp->iChannelID = m_iChannelNo;
	vp->chnParam[m_iChannelNo].iRuleID = iRuleID;

	//设置规则使能属性
	iRet = -1;
	if (m_iLogonID < 0 && m_iChannelNo == -1)
	{
		return;
	}

	CString strRuleName;
	GetDlgItemText(IDC_EDIT_RULENAME, strRuleName);
	strncpy_s(vp->chnParam[m_iChannelNo].rule[iRuleID].cRuleName, (LPSTR)(LPCTSTR)strRuleName, min(VCA_MAX_RULE_NAME_LEN-1, strRuleName.GetLength()));


	VCARuleParam  pParam = {0};
	strncpy_s(pParam.cRuleName, (LPSTR)(LPCTSTR)strRuleName, min(VCA_MAX_RULE_NAME_LEN-1, strRuleName.GetLength()));
	pParam.stRule.iRuleID = m_cboRuleID.GetCurSel();
	pParam.stRule.iSceneID = m_cboSceneID.GetCurSel();
	pParam.stRule.iValid = m_chkRuleValid.GetCheck();
	pParam.iEventID = iEventID;
	iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_RULE_PARAM, m_iChannelNo, &pParam, sizeof(VCARuleParam));
	if(iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","VCASetConfig Error!LogonID(%d), Error(0x%08x)",m_iLogonID,::GetLastError());
	}
	// 跟踪在不使能时也可以发送下面的设置协议 [11/28/2012 hanyongqiang]
	if (m_chkRuleValid.GetCheck() == 0 && iEventID != TRACK_SEL)		//规则不使能，没有必要再发下面的协议
	{
		//重启智能库
		iRet = RestartVCALib(m_iLogonID, m_iChannelNo);
		if (iRet < 0)
		{
			//log(1, "[CVCAEventPage::OnBnClickedButtonRuleSet]RestartVCALib error = %d", GetLastError());
		}
		//log(1, "[CVCAEventPage::OnBnClickedButtonRuleSet] Rule set disable.");

		return;
	}
}

void CLS_VCAEventPage::EventPageInit()
{
	UpdatePageUI();
	OnCbnSelchangeComboEvnetid();
}

BOOL CLS_VCAEventPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_pVcaParam = (vca_TVCAParam*)malloc(sizeof(vca_TVCAParam));
	if (NULL != m_pVcaParam)
	{
		memset(m_pVcaParam, 0, sizeof(vca_TVCAParam));
	}
	else
	{
		MessageBox("malloc memory fail!", GetTextEx(IDS_CONFIG_PROMPT), MB_OK|MB_TOPMOST);
	}

	UpdateUIText();
	m_cboEventType.SetCurSel(0);
	m_cboRuleID.SetCurSel(0);
	m_cboEnable.SetCurSel(0);
	m_cboSceneID.SetCurSel(0);
	m_cdtSceneName.SetLimitText(LEN_31);
	m_edtRuleName.SetLimitText(VCA_MAX_RULE_NAME_LEN - 1);

	return TRUE; 
}

#define ADJUST_EVENT_RECT(rc) {rc.top += 15; rc.left += 5; rc.right -= 5; rc.bottom -= 5;}

void CLS_VCAEventPage::OnCbnSelchangeComboEvnetid()
{
	int iIndex = m_cboEventType.GetCurSel();
	int iSelIndex = m_cboEventType.GetItemData(iIndex);

	//	先隐藏非当前选择的事件页面
	
	for (int i=0; i<MAX_EVENT_NUM; i++)
	{
		if (m_plArrEventPage[i])
		{
			m_plArrEventPage[i]->ShowWindow(SW_HIDE);	
		}
	}

	if (TRIPWIRE_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_Tripwire();

			if (NULL == m_plArrEventPage[iSelIndex])
				return;

			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_TRIPWIRE, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
		
	}
	else if (PERIMETER_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_Perimeter();

			if (NULL == m_plArrEventPage[iSelIndex])
				return;

			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_PERIMETER, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}	
	}
	else if (FACEREC_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_FaceRec();
			if (NULL == m_plArrEventPage[iSelIndex])
				return;

			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_FACEREC, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
		
	}
	else if (VIDEODETECT_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_VideoDetect();

			if (NULL == m_plArrEventPage[iSelIndex])
				return;

			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_VIDEODETECT, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	if (ABANDUM_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_Abandum();
			if (NULL == m_plArrEventPage[iSelIndex])
				return;

			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_ABANDUM, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}	
	}
	else if (TRACK_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_Track();
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_TRACK, this);

			if (NULL == m_plArrEventPage[iSelIndex])
				return;

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (CROWD_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_CROWD();
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_CROWD, this);

			if (NULL == m_plArrEventPage[iSelIndex])
				return;

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (FLUX_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_EVENT_FULX();
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_FLUX, this);

			if (NULL == m_plArrEventPage[iSelIndex])
				return;

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (LEAVE_DETECT_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_LeaveDetect();
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_LEAVE_DETECT, this);

			if (NULL == m_plArrEventPage[iSelIndex])
				return;

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (TRIPWIRE_SEL_EX == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_TripwireEx();
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_TRIPWIRE_EX, this);

			if (NULL == m_plArrEventPage[iSelIndex])
				return;

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}	
	else if (AUDIO_DIAGNOSE_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_AudioDiagnose();
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_AUDIODIAGNOSE, this);
			if (NULL == m_plArrEventPage[iSelIndex])
				return;
				
			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (MULIT_TRIP_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_MulitTrip();
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_MULIT_TRIP, this);
			if (NULL == m_plArrEventPage[iSelIndex])
				return;

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (LISENCE_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_Lisence();
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_LIENCE, this);
			if (NULL == m_plArrEventPage[iSelIndex])
				return;

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (RIVER_CLEAN_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_RiverClean();
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_RIVER_CLEAN, this);
			if (NULL == m_plArrEventPage[iSelIndex])
				return;

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (DREDGE_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_Dredge();
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_DREDGE, this);
			if (NULL == m_plArrEventPage[iSelIndex])
				return;

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (WATER_LEVEL_DETECTION_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_WaterLevelDetection();
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_WATER_LEVEL_DETECTION, this);
			if (NULL == m_plArrEventPage[iSelIndex])
				return;

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (SLUICE_GATE_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_SluiceGate();
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_SLUICEGATE, this);
			if (NULL == m_plArrEventPage[iSelIndex])
				return;

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (FIGHT_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_Fight();
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_FIGHT, this);
			if (NULL == m_plArrEventPage[iSelIndex])
				return;

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (ONDUTY_DETECT_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_OnDutyDetect();
			if (NULL == m_plArrEventPage[iSelIndex])
			{
				return;
			}
 			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_ONDUTY_DETECT, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (ILLEGAL_PARK_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_IllegalPark();
			if (NULL == m_plArrEventPage[iSelIndex])
			{
				return;
			}
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_ILLEGAL_PARK, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (GOODS_LOSE_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_GoodsLose();
			if (NULL == m_plArrEventPage[iSelIndex])
			{
				return;
			}
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_GOODS_LOSE, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (RUNNING_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_Running();
			if (NULL == m_plArrEventPage[iSelIndex])
			{
				return;
			}
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_RUNNING, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (HOVER_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_Hover();
			if (NULL == m_plArrEventPage[iSelIndex])
			{
				return;
			}
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_HOVER, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (PARKING_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_Parking();
			if (NULL == m_plArrEventPage[iSelIndex])
			{
				return;
			}
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_PARKING, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if(GOODS_DERELICT_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_GoodsDerelict();
			if (NULL == m_plArrEventPage[iSelIndex])
			{
				return;
			}
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_GOODS_DERELICT, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if(PERSON_STAT_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_PersonStat();
			if (NULL == m_plArrEventPage[iSelIndex])
			{
				return;
			}
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_PERSON_STAT, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (VIDEODETECT_NEW_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_VideoDetectNew();
			if (NULL == m_plArrEventPage[iSelIndex])
			{
				return;
			}
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_VIDEO_DETECT_NEW, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (AUDIO_DIAGNOSE_NEW_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_AudioDiagnoseNew();
			if (NULL == m_plArrEventPage[iSelIndex])
			{
				return;
			}
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_AUDIO_DIAGNOSE_NEW, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (FACEREC_NEW_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_FaceRecNew();
			if (NULL == m_plArrEventPage[iSelIndex])
			{
				return;
			}
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_FACEREC_NEW, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (CROWD_NEW_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_CrowdNew();
			if (NULL == m_plArrEventPage[iSelIndex])
			{
				return;
			}
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_CROWD_NEW, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (PROTECT_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_Protect();
			if (NULL == m_plArrEventPage[iSelIndex])
			{
				return;
			}
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_PROTECT, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (HEATMAP_SEL == iSelIndex)
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_HeatMap();
			if (NULL == m_plArrEventPage[iSelIndex])
			{
				return;
			}
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_HEATMAP, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	else if (WINDOW_DETECTION_SEL == iSelIndex)			//翻窗检测
	{
		if (NULL == m_plArrEventPage[iSelIndex])
		{
			m_plArrEventPage[iSelIndex] = new CLS_VCAEVENT_WindowDetection();
			if (NULL == m_plArrEventPage[iSelIndex])
			{
				return;
			}
			m_plArrEventPage[iSelIndex]->Create(IDD_DLG_VCAEVENT_WINDOW_DETECTION, this);

			RECT rcShow = {0};
			m_staticEventGroup.GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			ADJUST_EVENT_RECT(rcShow);
			m_plArrEventPage[iSelIndex]->MoveWindow(&rcShow);
		}
	}
	
	if (m_plArrEventPage[iSelIndex])
	{
		m_plArrEventPage[iSelIndex]->SetRuleID(m_cboRuleID.GetCurSel());
		m_plArrEventPage[iSelIndex]->SetSceneID(m_cboSceneID.GetCurSel());
		m_plArrEventPage[iSelIndex]->SetVCAParam(m_pVcaParam);
		m_plArrEventPage[iSelIndex]->Init(m_iLogonID, m_iChannelNo, m_iStreamNO);
		m_plArrEventPage[iSelIndex]->ShowWindow(SW_SHOW);
	}
}

void CLS_VCAEventPage::OnDestroy()
{
	CLS_BasePage::OnDestroy();

	if (NULL != m_pVcaParam)
	{
		free(m_pVcaParam);
		m_pVcaParam = NULL;
	}

	for(int i=0; i<MAX_EVENT_NUM; i++)
	{
		if (m_plArrEventPage[i])
		{
			m_plArrEventPage[i]->DestroyWindow();
			delete m_plArrEventPage[i];
			m_plArrEventPage[i] = NULL;
		}
	}
}

void CLS_VCAEventPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	int iLogonId = m_iLogonID;
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
		m_iStreamNO = 0;
	}
	else
	{
		m_iStreamNO = _iStreamNo;
	}

	UpdatePageUI();
	UpdateUIText();
	OnCbnSelchangeComboRuleid();
	if (iLogonId != m_iLogonID)
	{
		int iStatus = 0;
		int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNo, &iStatus, sizeof(int));
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig[NET_CLIENT_VCA_SUSPEND] failed logonID(%d)", m_iLogonID);
		}
		else
		{
			AddLog(LOG_TYPE_SUCC, "", "NetClient_SetDevConfig [NET_CLIENT_VCA_SUSPEND]", m_iLogonID);
		}

		InitVcaList();
	}
}

void CLS_VCAEventPage::OnLanguageChanged( int _iLanguage )
{
	UpdateUIText();
	m_cboEventType.SetCurSel(0);
	m_cboRuleID.SetCurSel(0);
	for (int i=0; i<MAX_EVENT_NUM; i++)
	{
		if (m_plArrEventPage[i])
		{
			m_plArrEventPage[i]->OnLanguageChanged();
		}
	}
	EventPageInit();
}

#define VCA_SUSPEND		0
#define VCA_OPENVCA		1

#define VCA_SUSPEND_RESULT_SUCCESS		1 
#define VCA_SUSPEND_RESULT_CONFIGING	2

void CLS_VCAEventPage::OnMainNotify( int _iLogonID,int _wParam, void* _iLParam, void* _iUser)
{
	int iIndex = m_cboEventType.GetCurSel();
	int iSelIndex = m_cboEventType.GetItemData(iIndex);
	if (m_plArrEventPage[iSelIndex])
	{
		m_plArrEventPage[iSelIndex]->OnMainNotify(_iLogonID, _wParam, _iLParam, _iUser);
	}

	switch(LOWORD(_wParam))
	{
	case WCM_VCA_SUSPEND:
		{
			int iChannelNo = HIWORD(_wParam);
			if (iChannelNo == m_iChannelNo)
			{
				VCASuspendResult tParam = {0};
				tParam.iBufSize = sizeof(VCASuspendResult);
				int iRetBytes = 0;
				int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNo, &tParam, sizeof(tParam), &iRetBytes);
				if(VCA_SUSPEND == tParam.iStatus && VCA_SUSPEND_RESULT_CONFIGING == tParam.iResult)
				{
					MessageBox(GetTextEx(IDS_VCA__SUSPEND_READONLY), GetTextEx(IDS_CONFIG_PROMPT), MB_OK|MB_TOPMOST);
				}
				else if (VCA_SUSPEND == tParam.iStatus && VCA_SUSPEND_RESULT_SUCCESS == tParam.iResult)//暂停成功
				{
					AddLog(LOG_TYPE_SUCC, "", "[OnMainNotify]WCM_VCA_SUSPEND success!", m_iLogonID);
				}
			}
		}
		break;
	default:
		break;
	}
}

void CLS_VCAEventPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	SetVCAStatus(bShow);
	if (bShow)
	{
		EventPageInit();		
	}
}

int CLS_VCAEventPage::RestartVCALib( int _iLogonID, int _iChannel /*= -1*/ )
{
	int iRet = -1;
	if (_iChannel == -1)
	{
		iRet = NetClient_VCARestart(_iLogonID);
		if (iRet < 0)
			AddLog(LOG_TYPE_FAIL, "", "VCARestart failed, ret(%d), err(%d)", iRet, GetLastError());

		return iRet;
	}

	iRet = NetClient_VCARestartEx(_iLogonID, _iChannel);
	if (iRet < 0)
		AddLog(LOG_TYPE_FAIL, "", "VCARestartEx failed, ret(%d), err(%d)", iRet, GetLastError());

	return iRet;
}

void CLS_VCAEventPage::OnCbnSelchangeComboRuleid()
{
	if (m_iLogonID == -1 || m_iChannelNo == -1)
	{
		return;
	}

	vca_TVCAParam *vp = m_pVcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));

	vp->iChannelID = m_iChannelNo;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_CHANNEL, m_iChannelNo, vp, sizeof(vca_TVCAParam));
	bool bVCAChanEnable = false;
	if (iRet >= 0)
	{
		bVCAChanEnable = (vp->chnParam[vp->iChannelID].iEnable != 0);
	}

	if (bVCAChanEnable)
	{
		VCARuleParam  pParam = {0};
		pParam.stRule.iRuleID = m_cboRuleID.GetCurSel();
		pParam.stRule.iSceneID = m_cboSceneID.GetCurSel();
		iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_RULE_PARAM, m_iChannelNo, &pParam, sizeof(VCARuleParam));
		if (iRet >= 0)
		{
			CString strRuleName;
			strRuleName.Format(_T("%s"),pParam.cRuleName);
			SetDlgItemText(IDC_EDIT_RULENAME, strRuleName);
			m_chkRuleValid.SetCheck(pParam.stRule.iValid);

			int iSelIndex = GetSelIndexByEventID(pParam.iEventID);
			for (int i = 0; i < m_cboEventType.GetCount(); ++i)
			{
				if (iSelIndex == m_cboEventType.GetItemData(i))
				{
					m_cboEventType.SetCurSel(i);
					break;
				}
			}
		}
		else
		{
			SetDlgItemText(IDC_EDIT_RULENAME, "");
			m_chkRuleValid.SetCheck(0);
			m_cboEventType.SetCurSel(TRIPWIRE_SEL);
		}
	}
		
	OnCbnSelchangeComboEvnetid();
}

void CLS_VCAEventPage::UpdateUIText()
{
	SetDlgItemTextEx(IDC_STATIC_RULEID, IDS_VCA_RULE_ID);
	SetDlgItemTextEx(IDC_CHECK_VALID_RULE, IDS_VCA_VALID);
	SetDlgItemTextEx(IDC_STATIC_RULENAME, IDS_VCA_RULENAME);
	SetDlgItemTextEx(IDC_STATIC_EVENTID, IDS_VCA_EVENT_ID);
	SetDlgItemTextEx(IDC_BUTTON_RULE_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_SCENEID, IDS_VCA_SCENE_ID);	
	SetDlgItemTextEx(IDC_BUTTON_SCENEIDSET, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_CALL_SCENE, IDS_PREVIEW_CALL_PREVIEW);
    SetDlgItemTextEx(IDC_STATIC_SCENENAME, IDS_VCA_SCENE_NAME);
	SetDlgItemTextEx(IDC_VCA_SCREEN, IDS_VCA_SCREEN);
	SetDlgItemTextEx(IDC_STATIC_VCA_POINTNUM, IDS_VCA_ARITHMETIC);
	SetDlgItemTextEx(IDC_VCA_CHECK1, IDS_VCA_BEHAVIOR);
	SetDlgItemTextEx(IDC_VCA_CHECK2, IDS_VCA_LINKAGE);
	SetDlgItemTextEx(IDC_VCA_CHECK3, IDS_VCA_FACE);
	SetDlgItemTextEx(IDC_VCA_CHECK4, IDS_VCA_PEOPLENUM);
	SetDlgItemTextEx(IDC_VCA_CHECK5, IDS_VCA_VIDEO);
	SetDlgItemTextEx(IDC_VCA_CHECK6, IDS_VCA_CARNUM);
	SetDlgItemTextEx(IDC_VCA_CHECK7, IDS_VCA_AUDIO);
	SetDlgItemTextEx(IDC_VCA_CHECK8, IDS_VCA_DUTY);
	SetDlgItemTextEx(IDC_VCA_CHECK9, IDS_VCA_PEOPLECROWD);
	SetDlgItemTextEx(IDC_STATIC_GROP_EVENTPARAM, IDS_VCA_EVENT_PARAM);

	m_cboRuleID.ResetContent();
	for (int i=0; i<8; i++)
	{
		m_cboRuleID.InsertString(i, IntToCString(i + 1));
	}
	m_cboRuleID.SetCurSel(0);

	m_cboSceneID.ResetContent();
	for (int i = 0; i < MAX_SCENE_NUM; i++)
	{
		m_cboSceneID.InsertString(i, IntToCString(i + 1));
	}
	m_cboSceneID.SetCurSel(0);

	const CString strEntype[] = {
		GetTextEx(IDS_VCA_DISABLE),
		GetTextEx(IDS_VCA_ENABLE_LOCAL),
		GetTextEx(IDS_VCA_ENABLE_REMOTE),
	};
	m_cboEnable.ResetContent();
	for (int i=0; i<sizeof(strEntype)/sizeof(CString); i++)
	{
		m_cboEnable.InsertString(i, strEntype[i]);
	}
	m_cboEnable.SetCurSel(0);

	OnBnClickedVcaCheck1();

	UpdatePageUI();
}

void CLS_VCAEventPage::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNo == -1)
	{
		return;
	}

	vca_TVCAParam *vp = m_pVcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));
	
	int iTmp = m_cboEnable.GetCount();
	if(IsDigistChannel(m_iChannelNo))
	{
		if (iTmp == 2)
		{
			m_cboEnable.AddString(GetTextEx(IDS_VCA_ENABLE_REMOTE));
		}
	}
	else
	{
		if (iTmp == 3)
		{
			m_cboEnable.DeleteString(2);
		}
	}

	AnyScene tParam = {0};
	tParam.iBufSize = sizeof(AnyScene);
	tParam.iSceneID = m_iSceneID;
	int iBytesReturned = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID,NET_CLIENT_ANYSCENE,m_iChannelNo,&tParam,sizeof(tParam), &iBytesReturned);
	if (iRet >= 0)
	{
		SetDlgItemText(IDC_EDIT_SCENENAME,tParam.cSceneName);
		SetParamVCA(tParam.iArithmetic);	
	}
	else
	{
		SetDlgItemText(IDC_EDIT_SCENENAME,tParam.cSceneName);
		SetParamVCA(0);
	}
	vp->iChannelID = m_iChannelNo;
	int iRuleId = m_cboRuleID.GetCurSel();
	if (iRuleId < 0)
	{
		return;
	}

	vp->chnParam->iRuleID = iRuleId;
	iRet = -1;
	iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_CHANNEL_ENABLE, m_iChannelNo, vp, sizeof(vca_TVCAParam));
	if (iRet >= 0)
	{
		m_cboEnable.SetCurSel(vp->chnParam[m_iChannelNo].iEnable);
	}
	else
	{
		m_cboEnable.SetCurSel(0);
	}
	
	VCARuleParam  pParam = {0};
	pParam.stRule.iRuleID = iRuleId;
	pParam.stRule.iSceneID = m_iSceneID;
	iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_RULE_PARAM, m_iChannelNo, &pParam, sizeof(VCARuleParam));
	if (iRet >= 0)
	{
		CString strRuleName;
		strRuleName.Format(_T("%s"),pParam.cRuleName);
		SetDlgItemText(IDC_EDIT_RULENAME, strRuleName);
		m_chkRuleValid.SetCheck(pParam.stRule.iValid);
	}
}

void CLS_VCAEventPage::OnCbnSelchangeComboVcaEnable()
{
	if (m_iLogonID<0 || m_iChannelNo<0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d), channel no(%d)", m_iLogonID, m_iChannelNo);
		return;
	}
	int iEnable = m_cboEnable.GetCurSel();
	vca_TVCAParam *vp = m_pVcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));
	vp->iChannelID = m_iChannelNo;
	vp->iEnable = iEnable;
	vp->chnParam[m_iChannelNo].iEnable = iEnable;
	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_SET_CHANNEL_ENABLE, m_iChannelNo, vp, sizeof(vca_TVCAParam));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_VCASetConfig failed logonID(%d)", m_iLogonID);
	}
}
bool CLS_VCAEventPage::IsDigistChannel( int _iChannelNO)
{
	int iChannelType = 0;
	if(NetClient_GetChannelProperty(m_iLogonID, _iChannelNO, GENERAL_CMD_GET_CHANNEL_TYPE,
		&iChannelType,sizeof(iChannelType)) == 0 && iChannelType == CHANNEL_TYPE_DIGITAL)
	{
		return true;
	}
	return false;
}

void CLS_VCAEventPage::OnBnClickedCheckValidRule()
{
	
}

void CLS_VCAEventPage::OnBnClickedButtonSceneidset()
{
	//设置场景号
	if(m_iSceneID < 0 || m_iSceneID > 15)
	{
		return;
	}
	CString strSceneName;
	m_cdtSceneName.GetWindowText(strSceneName);
	int iVcaType = 0;
	AnyScene tParam = {0};
	tParam.iBufSize = sizeof(AnyScene);
	tParam.iSceneID = m_iSceneID;
	strncpy_s(tParam.cSceneName, (LPSTR)(LPCTSTR)strSceneName, min(VCA_MAX_RULE_NAME_LEN-1, strSceneName.GetLength()));
	tParam.iArithmetic = ReturnParamVCA();
	int iRet = NetClient_SetDevConfig(m_iLogonID,NET_CLIENT_ANYSCENE,m_iChannelNo,&tParam,sizeof(tParam));	
	if (iRet < 0)
	{
		//log(1, "[CVCAEventPage::OnBnClickedCheckRuleenable]TDVCASetConfig error = 0x%p", GetLastError());
	}

}

void CLS_VCAEventPage::OnBnClickedButtonCallScene()
{
	//调用场景号
	CallParam tParam = {0};
	tParam.iBufSize = sizeof(CallParam);
	tParam.iType = 0;
	tParam.iValue = m_iSceneID;
	int iRet = NetClient_SetDevConfig(m_iLogonID,NET_CLIENT_CALL_ANYSCENE,m_iChannelNo,&tParam,sizeof(tParam));	
	if (iRet < 0)
	{
		//log(1, "OnBnClickedButtonCallScene() fail", GetLastError());
	}
}

void CLS_VCAEventPage::OnCbnSelchangeComboSceneid()
{
	m_iSceneID = m_cboSceneID.GetCurSel();
	CallCurScene();
	UpdatePageUI();
	OnCbnSelchangeComboRuleid();
}

int CLS_VCAEventPage::ReturnParamVCA()
{
	int _param = 0;
	for(int i = 8; i != -1; i--)
	{
		if(m_checkVCA[i].IsWindowEnabled())
		{
			_param |= m_checkVCA[i].GetCheck()<<i;
		}		
	}
	return _param;
}

void CLS_VCAEventPage::SetVCAStatus(bool _bStatus)
{
	if(_bStatus)
	{
		if (-1 == m_iLogonID)
		{
			AddLog(LOG_TYPE_FAIL, "", "CLS_VCAEventPage::failed logonID(%d)", m_iLogonID);
			return;
		}

		int iStatus = 0;
		int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNo, &iStatus, sizeof(int));
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
		}
	}
	else
	{
		int iStatus = 1;
		int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNo, &iStatus, sizeof(int));
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
		}
	}
}

void CLS_VCAEventPage::SetParamVCA( int _param )
{
	int _iStatus;
	for(int i = 8; i != -1; i--)
	{
		_iStatus = (_param >> i) & 0x01;
		m_checkVCA[i].SetCheck(_iStatus);
	}
}


void CLS_VCAEventPage::InitVcaList()
{	
	for (int i=0; i<9; i++)
	{
		m_checkVCA[i].EnableWindow(TRUE);
	}

	int iRetSize = 0;
	PotocolEnable stParam = {0};
	stParam.iSize = sizeof(stParam);
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_GET_PROTOCOL_ENABLE, m_iChannelNo, &stParam, sizeof(stParam), &iRetSize);
	if (0 == iRet)
	{
		int iVcaListEnable = PROTOCOL_VCALIST&stParam.iEnable;
		if(!iVcaListEnable)	//设备未发送vcalist协议,区分新老设备
		{
			return;
		}
	}
	else
	{
		return;
	}

	VcaArithmeticList tParam = {0};
	tParam.iSize = sizeof(tParam);
	tParam.iChannelNo = m_iChannelNo;
	//行为分析
	tParam.iArithmeticType = VCA_ARITHMETIC_BEHAVIOR_ANALYSIS;	
	iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_VCALIST, m_iChannelNo, &tParam, sizeof(tParam));
	if (iRet == -2 && tParam.iEnableCount > 0)
	{
		tParam.piEnableValue = new int[tParam.iEnableCount];
		iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_VCALIST, m_iChannelNo, &tParam, sizeof(tParam));
	}
	if (0 == iRet)
	{
		m_checkVCA[0].EnableWindow(tParam.piEnableValue[0]>0?1:0);		
	}
	//智能跟踪
	tParam.iArithmeticType = VCA_ARITHMETIC_TRACK;	
	iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_VCALIST, m_iChannelNo, &tParam, sizeof(tParam));
	if (0 == iRet)
	{
		m_checkVCA[1].EnableWindow(tParam.piEnableValue[0]>0?1:0);		
	}
	//人脸检测
	tParam.iArithmeticType = VCA_ARITHMETIC_FACE_DETECT;	
	iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_VCALIST, m_iChannelNo, &tParam, sizeof(tParam));
	if (0 == iRet)
	{
		m_checkVCA[2].EnableWindow(tParam.piEnableValue[0]>0?1:0);		
	}
	//人数统计
	tParam.iArithmeticType = VCA_ARITHMETIC_FLUX_STATISTIC;	
	iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_VCALIST, m_iChannelNo, &tParam, sizeof(tParam));
	if (0 == iRet)
	{
		m_checkVCA[3].EnableWindow(tParam.piEnableValue[0]>0?1:0);		
	}
	//视频诊断
	tParam.iArithmeticType = VCA_ARITHMETIC_VIDEO_DETECT;	
	iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_VCALIST, m_iChannelNo, &tParam, sizeof(tParam));
	if (0 == iRet)
	{
		m_checkVCA[4].EnableWindow(tParam.piEnableValue[0]>0?1:0);		
	}
	//车牌识别
	tParam.iArithmeticType = VCA_ARITHMETIC_LICENSE_RECOGNITION;	
	iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_VCALIST, m_iChannelNo, &tParam, sizeof(tParam));
	if (0 == iRet)
	{
		m_checkVCA[5].EnableWindow(tParam.piEnableValue[0]>0?1:0);		
	}
	//音频异常
	tParam.iArithmeticType = VCA_ARITHMETIC_AUDIO_DIAGNOSE;	
	iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_VCALIST, m_iChannelNo, &tParam, sizeof(tParam));
	if (0 == iRet)
	{
		m_checkVCA[6].EnableWindow(tParam.piEnableValue[0]>0?1:0);		
	}
	//值岗检测
	tParam.iArithmeticType = VCA_ARITHMETIC_LEAVE_DETECT;	
	iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_VCALIST, m_iChannelNo, &tParam, sizeof(tParam));
	if (0 == iRet)
	{
		m_checkVCA[7].EnableWindow(tParam.piEnableValue[0]>0?1:0);		
	}
	//人群聚集
	tParam.iArithmeticType = VCA_ARITHMETIC_CROWDS;	
	iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_VCALIST, m_iChannelNo, &tParam, sizeof(tParam));
	if (0 == iRet)
	{
		m_checkVCA[8].EnableWindow(tParam.piEnableValue[0]>0?1:0);		
	}
}
void CLS_VCAEventPage::OnBnClickedVcaCheck1()
{
	int iEnable = 0;
	VcaArithmeticList tParam = {0};
	tParam.iSize = sizeof(tParam);
	tParam.iChannelNo = m_iChannelNo;
	tParam.iArithmeticType = VCA_ARITHMETIC_BEHAVIOR_ANALYSIS;	
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_VCALIST, m_iChannelNo, &tParam, sizeof(tParam));
	if (RET_MALLOC_FALIED == iRet)
	{
		tParam.piEnableValue = new int[tParam.iEnableCount];
		iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_VCALIST, m_iChannelNo, &tParam, sizeof(tParam));
	}

	//TODO:注释掉的事件 设置/获取参数 都用的是SDK新架构不支持的老接口，注释掉，不对外显示，等以后升级更新，现在开放出去没任何意义！！！

	//行为分析类型：0：单绊线 1：双绊线 2：周界检测 3：徘徊 4：停车 5：奔跑  7：被盗物 8：遗弃物  9：警戒，10：热度图
	//11：水位监测，12：漂浮物检测，13：盗采河沙，14，闸门检测
	m_cboEventType.ResetContent();

	int iUseRule = GetDemoUseRule();
	if (RIVER_USE != iUseRule)
	{
		m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_TRIPWIRE)), TRIPWIRE_SEL);
		m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_EVENT_MULIT_TRIP)), MULIT_TRIP_SEL);
		m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_PERIMETER)), PERIMETER_SEL);
		m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_ALARM_EVENT_LOITER)), HOVER_SEL);
		m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_ALARM_EVENT_PARKING)), PARKING_SEL);
		m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_ALARM_EVENT_RUN)), RUNNING_SEL);
		m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCAEVENT_GOODS_DERELICT)), GOODS_DERELICT_SEL);
		m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCAEVENT_GOODS_LOSE)), GOODS_LOSE_SEL);
		m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_PROTECT)), PROTECT_SEL);
		m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_CFG_FEC_HEAT_MAP)), HEATMAP_SEL);
	}

	if (NULL != tParam.piEnableValue && -1 != tParam.piEnableValue[0])
	{
		iEnable = tParam.piEnableValue[0];
	}
	
	if (0 != (iEnable & VCA_BEHAVIOR_TYPE_WLD))
	{
		m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_CFG_FUNC_WATER_LEVEL)), WATER_LEVEL_DETECTION_SEL);
	}
	if (0 != (iEnable & VCA_BEHAVIOR_TYPE_FLOAT))
	{
		m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_EVENT_RIVER)), RIVER_CLEAN_SEL);
	}
	if (0 != (iEnable & VCA_BEHAVIOR_TYPE_DREDGE))
	{
		m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_EVENT_DREDGE)), DREDGE_SEL);
	}
	if (0 != (iEnable & VCA_BEHAVIOR_TYPE_SGATE))
	{
		m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_SLUICEGATE)), SLUICE_GATE_SEL);
	}

	if (BST_CHECKED == m_checkVCA[0].GetCheck())
	{
		m_checkVCA[2].SetCheck(BST_UNCHECKED);
		m_checkVCA[3].SetCheck(BST_UNCHECKED);
		m_checkVCA[5].SetCheck(BST_UNCHECKED);
		m_checkVCA[7].SetCheck(BST_UNCHECKED);
		m_checkVCA[8].SetCheck(BST_UNCHECKED);
	}
	else
	{	
		if (RIVER_USE != iUseRule)
		{
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_EVENT_VIDEODETECT_NEW)), VIDEODETECT_NEW_SEL);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_EVENT_AUDIO_DIAGNOSE_NEW)), AUDIO_DIAGNOSE_NEW_SEL);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_EVENT_FACEREC_NEW)), FACEREC_NEW_SEL);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_ABANDUM)), ABANDUM_SEL);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_EVENT_TRACK)), TRACK_SEL);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_EVENT_CROWD_NEW)), CROWD_NEW_SEL);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_EVENT_FLUX)), FLUX_SEL);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_EVENT_LEAVE_DETECT)), LEAVE_DETECT_SEL);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_TRIPWIRE_EX)), TRIPWIRE_SEL_EX);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_IDS_LISENCE)), LISENCE_SEL);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_EVENT_FIGHT)), FIGHT_SEL);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_DUTY)), ONDUTY_DETECT_SEL);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_CONFIG_ITS_ILLEGALPARK)), ILLEGAL_PARK_SEL);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_PEOPLENUM)), PERSON_STAT_SEL);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_EVENT_FACEREC)), FACEREC_SEL);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_EVENT_VIDEODETECT)), VIDEODETECT_SEL);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_EVENT_CROWD)), CROWD_SEL);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_VCA_EVENT_AUDIO_DIAGNOSE)), AUDIO_DIAGNOSE_SEL);
			m_cboEventType.SetItemData(m_cboEventType.AddString(GetTextEx(IDS_WINDOW_DETECTION)), WINDOW_DETECTION_SEL);
		}
	}
	m_cboEventType.SetCurSel(0);
	OnCbnSelchangeComboEvnetid();

	if(NULL != tParam.piEnableValue)
	{
		delete []tParam.piEnableValue;
		tParam.piEnableValue = NULL;
	}
}

void CLS_VCAEventPage::OnBnClickedVcaCheck3()
{
	if (BST_CHECKED == m_checkVCA[2].GetCheck())
	{
		m_checkVCA[0].SetCheck(BST_UNCHECKED);
		m_checkVCA[3].SetCheck(BST_UNCHECKED);
		m_checkVCA[5].SetCheck(BST_UNCHECKED);
		m_checkVCA[7].SetCheck(BST_UNCHECKED);
		m_checkVCA[8].SetCheck(BST_UNCHECKED);
	}
}

void CLS_VCAEventPage::OnBnClickedVcaCheck4()
{
	if (BST_CHECKED == m_checkVCA[3].GetCheck())
	{
		m_checkVCA[0].SetCheck(BST_UNCHECKED);
		m_checkVCA[2].SetCheck(BST_UNCHECKED);
		m_checkVCA[5].SetCheck(BST_UNCHECKED);
		m_checkVCA[7].SetCheck(BST_UNCHECKED);
		m_checkVCA[8].SetCheck(BST_UNCHECKED);
	}
}

void CLS_VCAEventPage::OnBnClickedVcaCheck6()
{
	if (BST_CHECKED == m_checkVCA[5].GetCheck())
	{
		m_checkVCA[0].SetCheck(BST_UNCHECKED);
		m_checkVCA[2].SetCheck(BST_UNCHECKED);
		m_checkVCA[3].SetCheck(BST_UNCHECKED);
		m_checkVCA[7].SetCheck(BST_UNCHECKED);
		m_checkVCA[8].SetCheck(BST_UNCHECKED);
	}
}

void CLS_VCAEventPage::OnBnClickedVcaCheck8()
{
	if (BST_CHECKED == m_checkVCA[7].GetCheck())
	{
		m_checkVCA[0].SetCheck(BST_UNCHECKED);
		m_checkVCA[2].SetCheck(BST_UNCHECKED);
		m_checkVCA[3].SetCheck(BST_UNCHECKED);
		m_checkVCA[5].SetCheck(BST_UNCHECKED);
		m_checkVCA[8].SetCheck(BST_UNCHECKED);
	}
}

void CLS_VCAEventPage::OnBnClickedVcaCheck9()
{
	if (BST_CHECKED == m_checkVCA[8].GetCheck())
	{
		m_checkVCA[0].SetCheck(BST_UNCHECKED);
		m_checkVCA[2].SetCheck(BST_UNCHECKED);
		m_checkVCA[3].SetCheck(BST_UNCHECKED);
		m_checkVCA[5].SetCheck(BST_UNCHECKED);
		m_checkVCA[7].SetCheck(BST_UNCHECKED);
	}
}

int CLS_VCAEventPage::GetSelIndexByEventID(int _iEventID)
{
	int iSelIndex = 0;
	switch (_iEventID)
	{
	case VCA_EVENT_TRIPWIRE:
		iSelIndex = TRIPWIRE_SEL;
		break;
	case VCA_EVENT_PERIMETER:
		iSelIndex = PERIMETER_SEL;
		break;
	case VCA_EVENT_FACEREC:
		iSelIndex = FACEREC_SEL;
		break;
	case VCA_EVENT_VIDEODETECT:
		iSelIndex = VIDEODETECT_SEL;
		break;
	case VCA_EVENT_ABANDUM:
		iSelIndex = ABANDUM_SEL;
		break;
	case VCA_EVENT_TRACK:
		iSelIndex = TRACK_SEL;
		break;
	case VCA_EVENT_CROWD:
		iSelIndex = CROWD_SEL;
		break;
	case VCA_EVENT_FLUXSTATISTIC:
		iSelIndex = FLUX_SEL;
		break;
	case VCA_EVENT_LEAVE_DETECT:
		iSelIndex = LEAVE_DETECT_SEL;
		break;
	case VCA_EVENT_AUDIO_DIAGNOSE:
		iSelIndex = AUDIO_DIAGNOSE_SEL;
		break;
	case VCA_EVENT_RIVERCLEAN:
		iSelIndex = RIVER_CLEAN_SEL;
		break;
	case VCA_EVENT_DREDGE:
		iSelIndex = DREDGE_SEL;
		break;
	case VCA_EVENT_WATER_LEVEL_DETECT:
		iSelIndex = WATER_LEVEL_DETECTION_SEL;
		break;
	case VCA_EVENT_FIGHT:
		iSelIndex = FIGHT_SEL;
		break;
	case VCA_CMD_RULE14_LEAVE_DETECT:
		iSelIndex = ONDUTY_DETECT_SEL;
		break;
	case VCA_EVENT_RUN:
		iSelIndex = RUNNING_SEL;
		break;
	case VCA_EVENT_PARKING:
		iSelIndex = PARKING_SEL;
		break;
	case VCA_EVENT_LOITER:
		iSelIndex = HOVER_SEL;
		break;
	case VCA_EVENT_WINDOW_DETECTION:
		iSelIndex = WINDOW_DETECTION_SEL; //翻窗检测
		break;
	case VCA_EVENT_SLUICEGATE:
		iSelIndex = SLUICE_GATE_SEL; //闸门
		break;
	default:
		break;
	}	

	return iSelIndex;
}

int CLS_VCAEventPage::GetEventIDBySelIndex(int _iSelIndex)
{
	int iEventID = -1;
	switch (_iSelIndex)
	{
	case TRIPWIRE_SEL:
		iEventID = VCA_EVENT_TRIPWIRE;
		break;
	case PERIMETER_SEL:
		iEventID = VCA_EVENT_PERIMETER;
		break;
	case FACEREC_SEL:
		iEventID = VCA_EVENT_FACEREC;
		break;
	case VIDEODETECT_SEL:
		iEventID = VCA_EVENT_VIDEODETECT;
		break;
	case ABANDUM_SEL:
		iEventID = VCA_EVENT_ABANDUM;
		break;
	case TRACK_SEL:
		iEventID = VCA_EVENT_TRACK;
		break;
	case CROWD_SEL:
		iEventID = VCA_EVENT_CROWD;
		break;
	case FLUX_SEL:
		iEventID = VCA_EVENT_FLUXSTATISTIC;
		break;
	case LEAVE_DETECT_SEL:
		iEventID = VCA_EVENT_LEAVE_DETECT;
		break;
	case AUDIO_DIAGNOSE_SEL:
		iEventID = VCA_EVENT_AUDIO_DIAGNOSE;
		break;
	case RIVER_CLEAN_SEL:
		iEventID = VCA_EVENT_RIVERCLEAN;
		break;
	case DREDGE_SEL:
		iEventID = VCA_EVENT_DREDGE;
		break;
	case WATER_LEVEL_DETECTION_SEL:
		iEventID = VCA_EVENT_WATER_LEVEL_DETECT;
		break;
	case FIGHT_SEL:
		iEventID = VCA_EVENT_FIGHT;
		break;
	case ONDUTY_DETECT_SEL:
		iEventID = VCA_CMD_RULE14_LEAVE_DETECT;
		break;
	case RUNNING_SEL:
		iEventID = VCA_EVENT_RUN;
		break;
	case PARKING_SEL:
		iEventID = VCA_EVENT_PARKING;
		break;
	case HOVER_SEL:
		iEventID = VCA_EVENT_LOITER;
		break;
	case WINDOW_DETECTION_SEL:
		iEventID = VCA_EVENT_WINDOW_DETECTION; //翻窗检测
		break;
	case SLUICE_GATE_SEL:
		iEventID = VCA_EVENT_SLUICEGATE; //闸门
		break;
	default:
		break;
	}	

	return iEventID;
}

void CLS_VCAEventPage::CallCurScene()
{
	//调用场景位置
	CallParam tCallParam = {0};
	tCallParam.iBufSize = sizeof(tCallParam);
	tCallParam.iType = 0;
	tCallParam.iValue = m_iSceneID;
	tCallParam.iSceneType = 0;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_CALL_ANYSCENE, m_iChannelNo, &tCallParam, sizeof(tCallParam));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig::NET_CLIENT_CALL_ANYSCENE failed!");
	}
}

int CLS_VCAEventPage::GetDemoUseRule()
{
	CString szNewFile = GetLocalSaveDirectory() + "\\DemoUseRule.ini";
	CIniFile DemoFile(szNewFile);

	CString szSection = "UseRule";
	CString szKey = "Rule";

	return DemoFile.ReadInteger((char *)(LPCTSTR)szSection, (char *)(LPCTSTR)szKey, 0);
}


