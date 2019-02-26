// VCAAlarmLinkPage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAAlarmLinkPage.h"


// CLS_VCAAlarmLinkPage dialog

IMPLEMENT_DYNAMIC(CLS_VCAAlarmLinkPage, CDialog)
static vca_TVCAParam g_VcaParam = {0};
CLS_VCAAlarmLinkPage::CLS_VCAAlarmLinkPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_VCAAlarmLinkPage::IDD, pParent)
{
	m_iChannelNo = 0;
	m_iLogonID = -1;
	m_pclsChanCheck = NULL;
}

CLS_VCAAlarmLinkPage::~CLS_VCAAlarmLinkPage()
{
	if (NULL != m_pclsChanCheck)
	{
		delete m_pclsChanCheck;
		m_pclsChanCheck = NULL; 
	}
}

void CLS_VCAAlarmLinkPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_VCA_ALARM_LINK, m_cboAlarmLinkType);
	DDX_Control(pDX, IDC_COMBO_VCA_ALARM_ENABLE, m_cboEnbale);
	DDX_Control(pDX, IDC_EDIT_VCA_ALARM_LINK_PTZ_TYPE, m_cboLinkPTZType);
	DDX_Control(pDX, IDC_COMBO_VCA_ALARM_LINK_NO, m_cboPtzNo);
	DDX_Control(pDX, IDC_COMBO_VCA_ALARM_RULE, m_cboAlarmLinkRule);
	DDX_Control(pDX, IDC_COMBO_VCA_ALARM_EVENT, m_cboEvent);
	DDX_Control(pDX, IDC_EDIT_VCA_ALARM_LINK_PTZ_CHANNEL, m_cboChannel);
	DDX_Control(pDX, IDC_CHECK_ALMLINK1, m_chkChannelEnable[0]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK2, m_chkChannelEnable[1]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK3, m_chkChannelEnable[2]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK4, m_chkChannelEnable[3]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK5, m_chkChannelEnable[4]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK6, m_chkChannelEnable[5]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK7, m_chkChannelEnable[6]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK8, m_chkChannelEnable[7]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK9, m_chkChannelEnable[8]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK10, m_chkChannelEnable[9]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK11, m_chkChannelEnable[10]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK12, m_chkChannelEnable[11]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK13, m_chkChannelEnable[12]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK14, m_chkChannelEnable[13]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK15, m_chkChannelEnable[14]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK16, m_chkChannelEnable[15]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK17, m_chkChannelEnable[16]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK18, m_chkChannelEnable[17]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK19, m_chkChannelEnable[18]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK20, m_chkChannelEnable[19]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK21, m_chkChannelEnable[20]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK22, m_chkChannelEnable[21]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK23, m_chkChannelEnable[22]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK24, m_chkChannelEnable[23]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK25, m_chkChannelEnable[24]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK26, m_chkChannelEnable[25]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK27, m_chkChannelEnable[26]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK28, m_chkChannelEnable[27]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK29, m_chkChannelEnable[28]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK30, m_chkChannelEnable[29]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK31, m_chkChannelEnable[30]);
	DDX_Control(pDX, IDC_CHECK_ALMLINK32, m_chkChannelEnable[31]);
	DDX_Control(pDX, IDC_COMBO_SINGLEPIC_CHANNEL, m_cboSinglePic);
	DDX_Control(pDX, IDC_COMBO_ALARM_LINK_SCENE, m_cboAlarmLinkScene);
	DDX_Control(pDX, IDC_COMBO_HD_TEMP, m_cboHDTemplate);
	DDX_Control(pDX, IDC_CBO_LASERVIOCE, m_cboLaserVioce);
}


BEGIN_MESSAGE_MAP(CLS_VCAAlarmLinkPage, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_VCA_ALARM_RULE, &CLS_VCAAlarmLinkPage::OnCbnSelchangeComboVcaAlarmRule)
	ON_CBN_SELCHANGE(IDC_COMBO_VCA_ALARM_LINK, &CLS_VCAAlarmLinkPage::OnCbnSelchangeComboVcaAlarmLink)
	ON_CBN_SELCHANGE(IDC_EDIT_VCA_ALARM_LINK_PTZ_TYPE, &CLS_VCAAlarmLinkPage::OnCbnSelchangeEditVcaAlarmLinkPtzType)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CLS_VCAAlarmLinkPage::OnBnClickedButtonSet)
	ON_CBN_SELCHANGE(IDC_EDIT_VCA_ALARM_LINK_PTZ_CHANNEL, &CLS_VCAAlarmLinkPage::OnCbnSelchangeEditVcaAlarmLinkPtzChannel)
	ON_BN_CLICKED(IDC_BUTTON_SCENE_TEMP_MAP_SET, &CLS_VCAAlarmLinkPage::OnBnClickedButtonSceneTempMapSet)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_LINK_SCENE, &CLS_VCAAlarmLinkPage::OnCbnSelchangeComboAlarmLinkScene)
	ON_BN_CLICKED(IDC_BTN_LASERVIOCE_PLAY, &CLS_VCAAlarmLinkPage::OnBnClickedBtnLaserviocePlay)
END_MESSAGE_MAP()


// CLS_VCAAlarmLinkPage message handlers

void CLS_VCAAlarmLinkPage::OnCbnSelchangeComboVcaAlarmRule()
{
	// TODO: Add your control notification handler code here
	m_cboEvent.SetCurSel(-1);
	UI_Clear();
	UI_UpdateAlarmLinkType();
	//UI_UpdateAlarmLink();
	UI_UpdateAlarmLinkEx();
}

void CLS_VCAAlarmLinkPage::OnCbnSelchangeComboVcaAlarmLink()
{
	UI_Clear();
	UI_UpdateAlarmLinkType();
	//UI_UpdateAlarmLink();
	UI_UpdateAlarmLinkEx();
}

static int g_iAlarmLinkIDS[] = {IDS_CONFIG_VCA_AUDIO, IDS_CONFIG_VCA_SCREEN,
	IDS_CONFIG_VCA_OUTPORT, IDS_CONFIG_VCA_RECORD, IDS_CONFIG_VCA_PTZ, IDS_CONFIG_VCA_SNAP,
	IDS_CONFIG_DNVR_LINKSINGLEPIC, IDS_CONFIG_CMOS_MAILENABLE, IDS_HTTP, IDS_LASER, 
	IDS_LINK_FLASHING_WHITE, IDS_LINK_TRAFFIC_TRIG,IDS_LINK_GUARD_SOUND};
static int g_iEnableIDS[] = {IDS_CONFIG_VCA_DISABLE, IDS_CONFIG_VCA_ENABLE};
static int g_iLinkPTZTypeIDS[] = {IDS_CONFIG_VCA_NOLINK, IDS_CONFIG_VCA_PRESET, IDS_CONFIG_VCA_TRACK ,IDS_CONFIGVCA_CRUISE_PATH};
extern int g_iEventIDS[VCA_EVENT_MAX];
BOOL CLS_VCAAlarmLinkPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	for (int i  = 0; i < VCA_MAX_RULE_NUM; i++)
	{
		CString szRuleID;
		szRuleID.Format("%d", i + 1);
		m_cboAlarmLinkRule.AddString(szRuleID);
	}
	for(int j = 1; j <= MAX_SCENE_NUM; j++)
	{
		CString SceneID;
		SceneID.Format("%d", j);
		m_cboAlarmLinkScene.AddString(SceneID);
	}
	m_cboAlarmLinkRule.SetCurSel(0);
	m_cboAlarmLinkScene.SetCurSel(0);
	UI_UpdateText();
	m_cboAlarmLinkType.SetCurSel(0);
	UI_UpdateAlarmLinkType();
	UI_UpdateChanCheck();
	UI_UpdateAlarmLinkEx();
	UI_UpdateHDTemplateName();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAAlarmLinkPage::UI_UpdateAlarmLinkType()
{
	int iAlarmLinkType = m_cboAlarmLinkType.GetCurSel();
	switch (iAlarmLinkType)
	{
	case ALARMLINKTYPE_LINKSOUND:
	case ALARMLINKTYPE_LINKDISPLAY:
	case ALARMLINKTYPE_LASER:
	case ALARMLINKTYPE_LINKEMAIL:
		{
			GetDlgItem(IDC_STATIC_VCA_ALARM_ENABLE)->EnableWindow(TRUE);
			GetDlgItem(IDC_COMBO_VCA_ALARM_ENABLE)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_VCA_ALARM_LINK_PTZ_TYPE)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_VCA_ALARM_LINK_PTZ_TYPE)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_VCA_ALARM_LINK_PTZ_CHANNEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_VCA_ALARM_LINK_PTZ_CHANNEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_VCA_ALARM_LINK_NO)->EnableWindow(FALSE);
			GetDlgItem(IDC_COMBO_VCA_ALARM_LINK_NO)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_VCA_ALARM_LINK_PTZ_CHANNEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_COMBO_SINGLEPIC_CHANNEL)->EnableWindow(FALSE);

			for (int i = 0 ;i < 32; i++)
			{
				m_chkChannelEnable[i].EnableWindow(FALSE);
			}
		}
		break;
	case VCA_ALARMLINK_PTZ:
		{
			GetDlgItem(IDC_STATIC_VCA_ALARM_ENABLE)->EnableWindow(FALSE);
			GetDlgItem(IDC_COMBO_VCA_ALARM_ENABLE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_VCA_ALARM_LINK_PTZ_TYPE)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_VCA_ALARM_LINK_PTZ_TYPE)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_VCA_ALARM_LINK_PTZ_CHANNEL)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_VCA_ALARM_LINK_PTZ_CHANNEL)->EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_VCA_ALARM_LINK_NO)->EnableWindow(TRUE);
			GetDlgItem(IDC_COMBO_VCA_ALARM_LINK_NO)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_VCA_ALARM_LINK_PTZ_CHANNEL)->EnableWindow(TRUE);
			GetDlgItem(IDC_COMBO_SINGLEPIC_CHANNEL)->EnableWindow(FALSE);

			for (int i = 0 ;i < 32; i++)
			{
				m_chkChannelEnable[i].EnableWindow(FALSE);
			}
		}
		break;
	case ALARMLINKTYPE_LINKOUTPORT:
	case ALARMLINKTYPE_LINKRECORD:
	case ALARMLINKTYPE_LINKSNAP:
	case ALARMLINKTYPE_LINKHTTP:
		{
			GetDlgItem(IDC_STATIC_VCA_ALARM_ENABLE)->EnableWindow(FALSE);
			GetDlgItem(IDC_COMBO_VCA_ALARM_ENABLE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_VCA_ALARM_LINK_PTZ_TYPE)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_VCA_ALARM_LINK_PTZ_TYPE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_VCA_ALARM_LINK_NO)->EnableWindow(FALSE);
			GetDlgItem(IDC_COMBO_VCA_ALARM_LINK_NO)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_VCA_ALARM_LINK_PTZ_CHANNEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_VCA_ALARM_LINK_PTZ_CHANNEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_COMBO_SINGLEPIC_CHANNEL)->EnableWindow(FALSE);

			for (int i = 0 ;i < 32; i++)
			{
				m_chkChannelEnable[i].EnableWindow(FALSE);
			}

			int iChannelNum = 0;
			int iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
			for (int i = 0 ;i < iChannelNum && i < 32; i++)
			{
				m_chkChannelEnable[i].EnableWindow(TRUE);
			}
		}
		break;
	case VCA_ALARMLINK_SINGLEPIC:
		{
			GetDlgItem(IDC_STATIC_VCA_ALARM_ENABLE)->EnableWindow(FALSE);
			GetDlgItem(IDC_COMBO_VCA_ALARM_ENABLE)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_VCA_ALARM_LINK_PTZ_TYPE)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_VCA_ALARM_LINK_PTZ_TYPE)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_VCA_ALARM_LINK_PTZ_CHANNEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_VCA_ALARM_LINK_PTZ_CHANNEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_VCA_ALARM_LINK_NO)->EnableWindow(FALSE);
			GetDlgItem(IDC_COMBO_VCA_ALARM_LINK_NO)->EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_VCA_ALARM_LINK_PTZ_CHANNEL)->EnableWindow(FALSE);
			GetDlgItem(IDC_COMBO_SINGLEPIC_CHANNEL)->EnableWindow(TRUE);

			for (int i = 0 ;i < 32; i++)
			{
				m_chkChannelEnable[i].EnableWindow(FALSE);
			}

			int iChannelNum = 0;
			int iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
			m_cboSinglePic.ResetContent();
			m_cboSinglePic.AddString("--");
			for (int i=1; i<=iChannelNum; i++)
			{
				CString strNo;
				strNo.Format("Channel%d", i);
				m_cboSinglePic.AddString(strNo);
			}
			m_cboSinglePic.SetCurSel(0);

		}
		break;
	default:
		break;
	}
}

void CLS_VCAAlarmLinkPage::OnCbnSelchangeEditVcaAlarmLinkPtzType()
{
	// TODO: Add your control notification handler code here
	m_cboPtzNo.ResetContent();
	int iPtzType = m_cboLinkPTZType.GetCurSel();
	if (iPtzType < VCA_LINKPTZ_TYPE_PRESET)
	{
		return;
	}
	if (iPtzType == VCA_LINKPTZ_TYPE_PRESET)
	{
		for (int i = 1; i < 256; i++)
		{
			CString szPtzNo;
			szPtzNo.Format("%d", i);
			m_cboPtzNo.AddString(szPtzNo);
		}
	}
	else if (iPtzType == VCA_LINKPTZ_TYPE_PATH)
	{
		for (int i = 1; i < 9; i++)
		{
			CString szPtzNo;
			szPtzNo.Format("%d", i);
			m_cboPtzNo.AddString(szPtzNo);
		}
	}
	else
	{
		CString szPtzNo;
		szPtzNo.Format("%d", 1);
		m_cboPtzNo.AddString(szPtzNo);
	}	
	m_cboPtzNo.SetCurSel(0);
}

void CLS_VCAAlarmLinkPage::UI_UpdateAlarmLink()
{
	if (m_iLogonID < 0 || m_iChannelNo < 0)
	{
		return;
	}
	vca_TVCAParam * vp = &g_VcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));
	int iRuleID = m_cboAlarmLinkRule.GetCurSel();
	vp->chnParam[m_iChannelNo].iRuleID = iRuleID;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_RULE_COMMON, m_iChannelNo, vp, sizeof(vca_TVCAParam));
	if (iRet < 0 || !vp->chnParam[m_iChannelNo].rule[iRuleID].iValid)
	{
		return;
	}
	int iEvent = vp->chnParam[m_iChannelNo].rule[iRuleID].iEventID;
	vca_TAlarmLink alarmLink = vp->chnParam[m_iChannelNo].rule[iRuleID].alarmLink;
	m_cboEvent.SetCurSel(iEvent);
	int iAlarmLinkType = m_cboAlarmLinkType.GetCurSel();
	
	if (ALARMLINKTYPE_LINKSOUND == iAlarmLinkType || ALARMLINKTYPE_LINKDISPLAY == iAlarmLinkType || ALARMLINKTYPE_LASER == iAlarmLinkType || ALARMLINKTYPE_LINKEMAIL == iAlarmLinkType)
	{
		int iEnable = alarmLink.iLinkSet[iAlarmLinkType];
		m_cboEnbale.SetCurSel(iEnable);
	}
	else if (iAlarmLinkType == VCA_ALARMLINK_PTZ)
	{
		int iChannelNo = m_cboChannel.GetCurSel();
		int iPtzType = alarmLink.ptz[iChannelNo].usType;
		m_cboLinkPTZType.SetCurSel(iPtzType);
		OnCbnSelchangeEditVcaAlarmLinkPtzType();
		if (iPtzType == VCA_LINKPTZ_TYPE_PRESET)
		{
			int iPtzNo = alarmLink.ptz[iChannelNo].usPresetNO;
			m_cboPtzNo.SetCurSel(iPtzNo-1);
		}
		else if (iPtzType == VCA_LINKPTZ_TYPE_PATH)
		{
			int iPtzNo = alarmLink.ptz[iChannelNo].usPathNO;
			m_cboPtzNo.SetCurSel(iPtzNo-1);
		}
		else
		{
			m_cboPtzNo.SetCurSel(0);
		}
	}
	else if (ALARMLINKTYPE_LINKOUTPORT == iAlarmLinkType || ALARMLINKTYPE_LINKRECORD == iAlarmLinkType ||
		ALARMLINKTYPE_LINKSNAP == iAlarmLinkType ||  ALARMLINKTYPE_LINKHTTP == iAlarmLinkType)
	{
		//zyb add 20150505		
		if (m_pclsChanCheck == NULL || m_iLogonID < 0)
		{
			return;
		}
		int iChannelNum = 0;
		int iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);

		//ys motify 20160331
		TAlarmLinkParam_V3 tAlarmLinkPara = {0};
		tAlarmLinkPara.tAlarmParam.iSize = sizeof(TAlarmParam_V3);
		tAlarmLinkPara.tLinkParam.iSize = sizeof(TLinkParam_V3);

		tAlarmLinkPara.tAlarmParam.iSceneID = 0;//需拓展
		tAlarmLinkPara.tAlarmParam.iAlarmTypeParam = iRuleID;
		tAlarmLinkPara.tAlarmParam.iReserved = m_cboEvent.GetCurSel();
		tAlarmLinkPara.tLinkParam.iLinkType = iAlarmLinkType;
		
		iRet = NetClient_GetAlarmConfig(m_iLogonID, m_iChannelNo, ALARM_TYPE_VCA, CMD_GET_ALARMLINK_V3, &tAlarmLinkPara);
		
		int iEnable[MAX_BITSET_COUNT] = {0};
		for(int i = 0; i < MAX_BITSET_COUNT; i++) 
		{
			iEnable[i]= tAlarmLinkPara.tLinkParam.uLinkParam.iCommonSet[i];
		}

		m_pclsChanCheck->InitData(iChannelNum, iEnable);
	}
	else if (iAlarmLinkType == VCA_ALARMLINK_SINGLEPIC)
	{
		int iChannelNum = 0;
		iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);

		TAlarmLinkParam_V3 tAlarmLinkPara = {0};
		tAlarmLinkPara.tAlarmParam.iSize = sizeof(TAlarmParam_V3);
		tAlarmLinkPara.tLinkParam.iSize = sizeof(TLinkParam_V3);

		tAlarmLinkPara.tAlarmParam.iAlarmTypeParam = iRuleID;
		tAlarmLinkPara.tLinkParam.iLinkType = VCA_ALARMLINK_SINGLEPIC;
		int iRet = NetClient_GetAlarmConfig(m_iLogonID, m_iChannelNo, ALARM_TYPE_VCA, CMD_GET_ALARMLINK_V3, &tAlarmLinkPara);
		if (iRet == 0)
		{
			int iEnable[MAX_BITSET_COUNT] = {0};
			int iTempChannel = iChannelNum > MAX_BITSET_COUNT ? MAX_BITSET_COUNT : iChannelNum;
			for (int i = 0; i < iChannelNum; i++)
			{
				iEnable[i] = tAlarmLinkPara.tLinkParam.uLinkParam.tLinkSinglePicParam.iChannelSet[i];
				if (1 == iEnable[i])
				{
					m_cboSinglePic.SetCurSel(i+1);
					break;
				}
			}
		}
	}
}

void CLS_VCAAlarmLinkPage::UI_Clear()
{
	m_cboEnbale.SetCurSel(-1);
	m_cboLinkPTZType.SetCurSel(-1);
	m_cboPtzNo.ResetContent();
	SetDlgItemText(IDC_EDIT_VCA_ALARM_ENABLE_SET, "");
	m_cboChannel.ResetContent();
	if (m_iLogonID >= 0)
	{
		int iChannelNum = 0;
		int iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
		if (iRet >= 0)
		{
			for (int i = 0; i < iChannelNum; i++)
			{
				CString szChannelNo = 0;
				szChannelNo.Format("%d", i);
				m_cboChannel.AddString(szChannelNo);
			}
			if(0 != iChannelNum)
			{
				m_cboChannel.SetCurSel(0);
			}
			else
			{
				m_cboChannel.SetCurSel(-1);
			}
		}
	}
	for (int i = 0; i < 32; i++)
	{
		m_chkChannelEnable[i].SetCheck(BST_UNCHECKED);
	}
}
void CLS_VCAAlarmLinkPage::OnBnClickedButtonSet()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0 || m_iChannelNo < 0)
	{
		return;
	}
	int iRuleID = m_cboAlarmLinkRule.GetCurSel();
	int iEventID = m_cboEvent.GetCurSel();
	int iLinkType = m_cboAlarmLinkType.GetCurSel();
	
	TAlarmLinkParam_V3 tAlarmLinkPara = {0};
	tAlarmLinkPara.tAlarmParam.iSize = sizeof(TAlarmParam_V3);
	tAlarmLinkPara.tLinkParam.iSize = sizeof(TLinkParam_V3);

	tAlarmLinkPara.tAlarmParam.iSceneID = m_cboAlarmLinkScene.GetCurSel();
	tAlarmLinkPara.tAlarmParam.iAlarmTypeParam = iRuleID;
	tAlarmLinkPara.tLinkParam.iLinkType = iLinkType;			//联动类型
	tAlarmLinkPara.tAlarmParam.iReserved = iEventID;	//报警类型参数

	switch(iLinkType)
	{
	case ALARMLINKTYPE_LINKOUTPORT:
	case ALARMLINKTYPE_LINKRECORD:
	case ALARMLINKTYPE_LINKSNAP:
	case ALARMLINKTYPE_LINKHTTP:
		{
			GetChkLinkChannel(tAlarmLinkPara);
		}
		break;
	case ALARMLINKTYPE_LINKSINGLEPIC:
		{
 			int iEnable[MAX_BITSET_COUNT] = {0};
 			if (m_cboSinglePic.GetCurSel() > 0)
 			{
 				int iChanNo = m_cboSinglePic.GetCurSel()-1;
 				iEnable[iChanNo/LEN_32] |= 1<<iChanNo%LEN_32;			
 			}
 			for(int i = 0; i < MAX_BITSET_COUNT; i++) 
 			{
 				tAlarmLinkPara.tLinkParam.uLinkParam.iCommonSet[i] = iEnable[i];
 			}
		}
		break;
	case ALARMLINKTYPE_LINKPTZ:
		{
			int iLinkChannel = m_cboChannel.GetCurSel();
			//判断联动通道PTZ个数是否超过64
			int iPtzCount = 0;			//已经联动的通道
			bool bSelfLink = false;		//是否已联动了当前设置的通道

			tAlarmLinkPara.tAlarmParam.iSize = sizeof(TAlarmParam_V3);
			tAlarmLinkPara.tLinkParam.iSize = sizeof(TLinkParam_V3);
			tAlarmLinkPara.tAlarmParam.iSceneID = m_cboAlarmLinkScene.GetCurSel();
			tAlarmLinkPara.tAlarmParam.iAlarmTypeParam = iRuleID;
			tAlarmLinkPara.tAlarmParam.iReserved = iEventID;		//报警类型参数
			tAlarmLinkPara.tLinkParam.iLinkType = iLinkType;			//联动类型
			int iChannelNum = 0;
			int iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
			for (int i = 0; i < iChannelNum; i++)
			{
				tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.iPtzNo = i;
				NetClient_GetAlarmConfig(m_iLogonID, m_iChannelNo, ALARM_TYPE_VCA, CMD_SET_ALARMLINK_V3, &tAlarmLinkPara);
				if (LINKPTZ_TYPE_NOLINK != tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usType)
				{
					if (iLinkChannel == i)
					{
						bSelfLink = true;
					}
					iPtzCount++;
				}
			}
//			int iPtzNo = GetDlgItemInt(IDC_COMBO_Link_NO);
			int iPtzNo = GetDlgItemInt(IDC_COMBO_VCA_ALARM_LINK_NO);
			if (iPtzNo < 1)
			{
				m_cboPtzNo.SetCurSel(0);
				iPtzNo = 1;
			}
			else if (iPtzNo >  256)
			{
				m_cboPtzNo.SetCurSel(m_cboPtzNo.GetCount()-1);
				iPtzNo =  256;
			}
			else if (iPtzNo >= 65 && iPtzNo <= 99)
			{

				return;
			}

			tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.iPtzNo = iLinkChannel;
			if(m_cboLinkPTZType.GetCurSel()==0)
			{
				tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usType = LINKPTZ_TYPE_NOLINK;
				tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usTypeNO = 0;
			}
			else if(m_cboLinkPTZType.GetCurSel()==1)
			{
				tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usType  = LINKPTZ_TYPE_PRESET;
				tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usTypeNO = iPtzNo;
			}
			else if(m_cboLinkPTZType.GetCurSel()==2)
			{
				tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usType = LINKPTZ_TYPE_TRACK;
				tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usTypeNO = iPtzNo;
			}
			else if(m_cboLinkPTZType.GetCurSel()==3)
			{
				tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usType = LINKPTZ_TYPE_PATH;
				tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usTypeNO = iPtzNo;
			}

			if (iPtzCount >= LEN_64 && !bSelfLink 
				&& LINKPTZ_TYPE_NOLINK != tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usType)
			{
				return;
			}
		}
		break;
	case ALARMLINKTYPE_LINKSOUND:
	case ALARMLINKTYPE_LINKDISPLAY:
	case ALARM_LINKTYPE_EMAIL:
	case ALARMLINKTYPE_LASER:
		{
			tAlarmLinkPara.tLinkParam.uLinkParam.iCommonSet[0] = m_cboEnbale.GetCurSel();
		}
		break;
	default:
		break;
	}
	int iRet = NetClient_SetAlarmConfig(m_iLogonID, m_iChannelNo, ALARM_TYPE_VCA, CMD_SET_ALARMLINK_V3, &tAlarmLinkPara);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetAlarmConfig (%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetAlarmConfig(%d)", m_iLogonID);
	}
}

void CLS_VCAAlarmLinkPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateText();
	if (m_pclsChanCheck != NULL)
	{
		m_pclsChanCheck->OnLanguageChanged(_iLanguage);
	}
}

void CLS_VCAAlarmLinkPage::UI_UpdateText()
{
	SetDlgItemTextEx(IDC_STATIC_ALARM_LINK, IDS_VCA_ALARM_LINK);
	SetDlgItemTextEx(IDC_STATIC_VCA_ALARM_RULE, IDS_VCA_RULE_ID);
	SetDlgItemTextEx(IDC_STATIC_VCA_ALARM_EVENT, IDS_VCA_EVENT_ID);
	SetDlgItemTextEx(IDC_STATIC_VCA_ALARM_LINK, IDS_VCA_LINK_TYPE);
	SetDlgItemTextEx(IDC_STATIC_VCA_ALARM_ENABLE, IDS_VCA_ALARM_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_VCA_ALARM_ENABLE_SET, IDS_VCA_ALARM_ENABLE_SET);
	SetDlgItemTextEx(IDC_STATIC_VCA_ALARM_LINK_PTZ_CHANNEL, IDS_VCA_CHANNEL_NO);
	SetDlgItemTextEx(IDC_STATIC_VCA_ALARM_LINK_PTZ_TYPE, IDS_VCA_LINK_PTZ_TYPE);
	SetDlgItemTextEx(IDC_STATIC_VCA_ALARM_LINK_NO, IDS_VCA_LINK_NO);
	SetDlgItemTextEx(IDC_BUTTON_SET, IDS_VCA_LINK_SET);
	SetDlgItemTextEx(IDC_STATIC_LINK_ENABLE, IDS_CONFIG_VCA_ENABLE_AUDIO);
	SetDlgItemTextEx(IDC_STATIC_LINK_SET, IDS_CONFIG_VCA_ENABLE_LINK_SET);
	SetDlgItemTextEx(IDC_STATIC_LINK_PTZ, IDS_CONFIG_VCA_LINK_PTZ);
	SetDlgItemTextEx(IDC_STATIC_LINK_SET_PTZ2,IDS_CONFIG_DNVR_LINKSINGLEPIC);
	SetDlgItemTextEx(IDC_STATIC_SINGLEPIC_CHANNEL,IDS_ALARM_LINK_SINGLEPIC_CHANNEL);
	SetDlgItemTextEx(IDC_STATIC_ALARM_LINK_SCENE,IDS_VCA_SCENE_ID);

	SetDlgItemTextEx(IDC_STATIC_HD_Template, IDS_HD_CUR_TEMPLATE);
	SetDlgItemTextEx(IDC_BUTTON_SCENE_TEMP_MAP_SET, IDS_SET);
	//警戒音
	SetDlgItemTextEx(IDC_STC_LASERVIOCE, IDS_LINK_GUARD_SOUND);
	SetDlgItemTextEx(IDC_BTN_LASERVIOCE_PLAY, IDS_START_PLAY);

	for (int i = 0; i < VCA_EVENT_MAX; i++)
	{
		InsertString(m_cboEvent, i, g_iEventIDS[i]);
	}
	for (int i = 0; i < 2; i++)
	{
		InsertString(m_cboEnbale, i, g_iEnableIDS[i]);
	}

	for (int i = 0; i < ALARMLINKTYPE_MAX; i++)
	{
		InsertString(m_cboAlarmLinkType, i, g_iAlarmLinkIDS[i]);
	}
	for (int i = 0; i < VCA_LINKPTZ_TYPE_MAX; i++)
	{
		InsertString(m_cboLinkPTZType, i, g_iLinkPTZTypeIDS[i]);
	}

	UI_UpdateHDTemplateName();
}

void CLS_VCAAlarmLinkPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo;
	}
	m_iLogonID = _iLogonID;
	m_cboEvent.SetCurSel(-1);
	UI_Clear();
	UI_UpdateAlarmLinkType();
	//UI_UpdateAlarmLink();
	UI_UpdateAlarmLinkEx();
	UI_UpdateHDTemplateName();
	UI_UpdateLaserVoice();
}
void CLS_VCAAlarmLinkPage::OnCbnSelchangeEditVcaAlarmLinkPtzChannel()
{
	// TODO: Add your control notification handler code here
	if (m_cboAlarmLinkType.GetCurSel() == VCA_ALARMLINK_PTZ)
	{
		//UI_UpdateAlarmLink();
		UI_UpdateAlarmLinkEx();
	}
}

void CLS_VCAAlarmLinkPage::UI_UpdateChanCheck()
{
	for (int i=0; i<32; i++)
	{
		m_chkChannelEnable[i].ShowWindow(SW_HIDE);
	}
	 
	if (m_pclsChanCheck == NULL)
	{
		m_pclsChanCheck = new CLS_ChanCheck();
		m_pclsChanCheck->Create(IDD_DLG_CFG_CHANNEL_CHECK, this);
	}

	if (m_pclsChanCheck == NULL)
	{
		return;
	}

	RECT rc = {0};
	GetDlgItem(IDC_STATIC_LINK_SET)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	rc.top += 15;
	rc.bottom -= 10;
	rc.left += 35;
	rc.right -= 15;
	m_pclsChanCheck->MoveWindow(&rc);
	m_pclsChanCheck->ShowWindow(SW_SHOW);
}

int CLS_VCAAlarmLinkPage::GetChkLinkChannel( TAlarmLinkParam_V3& _tLink )
{
	int iEnalbe[MAX_BITSET_COUNT];
	m_pclsChanCheck->GetChanValue(iEnalbe);
	for(int i = 0; i < MAX_BITSET_COUNT; i++) 
	{
		_tLink.tLinkParam.uLinkParam.iCommonSet[i]= iEnalbe[i];
	}
	return 0;
}

void CLS_VCAAlarmLinkPage::UI_UpdateAlarmLinkEx()
{
	TAlarmLinkParam_V3 tAlarmLinkPara = {0};
	tAlarmLinkPara.tAlarmParam.iSize = sizeof(TAlarmParam_V3);
	tAlarmLinkPara.tLinkParam.iSize = sizeof(TLinkParam_V3);

	int iLinkType = m_cboAlarmLinkType.GetCurSel();
	tAlarmLinkPara.tAlarmParam.iSceneID = m_cboAlarmLinkScene.GetCurSel();
	tAlarmLinkPara.tAlarmParam.iAlarmTypeParam = m_cboAlarmLinkRule.GetCurSel();
	tAlarmLinkPara.tAlarmParam.iReserved = m_cboEvent.GetCurSel();
	tAlarmLinkPara.tLinkParam.iLinkType = iLinkType;
	tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.iPtzNo = m_cboChannel.GetCurSel();//联动ptz使用
	tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usType = -1;;//联动ptz使用
	int iRet = NetClient_GetAlarmConfig(m_iLogonID, m_iChannelNo, ALARM_TYPE_VCA, CMD_GET_ALARMLINK_V3, &tAlarmLinkPara);
	if (iRet < 0)
	{
	}
	int iEnable[LEN_16] = {0};
	int iChannelNum = 0;
	int iRet1 = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);

	switch(iLinkType)
	{
	case ALARM_LINKTYPE_SINGLEPIC:
		{
			m_cboSinglePic.SetCurSel(0);
			for(int i = 0; i < MAX_BITSET_COUNT; i++)
			{
				iEnable[i] = tAlarmLinkPara.tLinkParam.uLinkParam.tLinkSinglePicParam.iChannelSet[i];
			}

			for (int i = 0; i < iChannelNum; i++)
			{
				if (iEnable[i/LEN_32]>>(i%32)&1)
				{
					m_cboSinglePic.SetCurSel(i+1);
					break;
				}
			}
		}
		break;
	case ALARM_LINKTYPE_OUTPORT:
		{
			iEnable[0]= tAlarmLinkPara.tLinkParam.uLinkParam.tLinkOutPortParam.iChannelSet[0];
			iEnable[1]= tAlarmLinkPara.tLinkParam.uLinkParam.tLinkOutPortParam.iChannelSet[1];
			int iInportNum=0,iOutportNum=0;
			NetClient_GetAlarmPortNum(m_iLogonID,&iInportNum,&iOutportNum);
			m_iMaxLinkNum = iOutportNum;
		}
		break;
	case ALARM_LINKTYPE_RECORD:
	case ALARM_LINKTYPE_SNAPSHOT:
	case ALARM_LINKTYPE_HTTP:
		{
			for(int i = 0; i < MAX_BITSET_COUNT; i++)
			{
				iEnable[i] = tAlarmLinkPara.tLinkParam.uLinkParam.tLinkSinglePicParam.iChannelSet[i];
			}
		}
		break;
	case ALARM_LINKTYPE_PTZ:
		{
			int iPtzType = tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usType;
			int iValue = tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usTypeNO;
			m_cboLinkPTZType.SetCurSel(iPtzType);
			OnCbnSelchangeEditVcaAlarmLinkPtzType();
			if (iPtzType == VCA_LINKPTZ_TYPE_PRESET)
			{
				m_cboPtzNo.SetCurSel(iValue-1);
			}
			else if (iPtzType == VCA_LINKPTZ_TYPE_PATH)
			{
				m_cboPtzNo.SetCurSel(iValue-1);
			}
			else
			{
				m_cboPtzNo.SetCurSel(0);
			}
		}
		break;
	case ALARM_LINKTYPE_AUDIO:
	case ALARM_LINKTYPE_VIDEO:
	case ALARM_LINKTYPE_EMAIL:
	case ALARMLINKTYPE_LASER:
		{
			m_cboAlarmLinkType.ShowWindow(SW_SHOW);
			m_cboEnbale.SetCurSel(tAlarmLinkPara.tLinkParam.uLinkParam.iCommonSet[0]);
		}
		break;
	}
	switch(iLinkType)
	{
	case ALARM_LINKTYPE_OUTPORT:
	case ALARM_LINKTYPE_RECORD:
	case ALARM_LINKTYPE_SNAPSHOT:
	case ALARM_LINKTYPE_HTTP:
		{
			if (m_pclsChanCheck == NULL || m_iLogonID < 0)
			{
				return;
			}
			int iChannelNum = 0;
			int iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
			int iEnable[MAX_BITSET_COUNT] = {0};
			for(int i = 0; i < MAX_BITSET_COUNT; i++)
			{
				iEnable[i] = tAlarmLinkPara.tLinkParam.uLinkParam.tLinkSinglePicParam.iChannelSet[i];
			}

			m_pclsChanCheck->InitData(iChannelNum, iEnable);
		}
		break;
	}

	for(int i=0; i<LEN_16; i++)
	{
		m_chkChannelEnable[i].SetCheck(iEnable[i]);
	}

}

void CLS_VCAAlarmLinkPage::UI_UpdateHDTemplateName()
{
	m_cboHDTemplate.ResetContent();
	CString cstrTamplateName;
	for (int i = 0; i < MAX_ITS_TEMPLATE; ++i)
	{
		char cTemplateName[LEN_64] = {0};
		int iRet = NetClient_GetHDTemplateName(m_iLogonID, i, cTemplateName);
		if (iRet >= 0)
		{
			cstrTamplateName = GetHDTemplateName(cTemplateName);
			m_cboHDTemplate.AddString(cstrTamplateName);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_GetHDTemplateName (%d), error(%d)",m_iLogonID, GetLastError());
		}
	}
	m_cboHDTemplate.SetCurSel(0);

	UI_UpdateSceneAndTemplateMap();
};

void CLS_VCAAlarmLinkPage::UI_UpdateSceneAndTemplateMap()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error (%d)", m_iLogonID, GetLastError());
		return;
	}

	SceneTemplateMap tParam = {0};
	tParam.iBufSize = sizeof(SceneTemplateMap);
	tParam.iSceneId = m_cboAlarmLinkScene.GetCurSel();
	int iReturnByte = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_SCENETEMPLATE_MAP, m_iChannelNo, &tParam, sizeof(SceneTemplateMap), &iReturnByte);
	if (iRet != 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig[NET_CLIENT_SCENETEMPLATE_MAP] (%d, %d), error(%d)"
			, m_iLogonID, m_iChannelNo, GetLastError());
	}
	else
	{
		if (INVALID_FLAG == tParam.iTemplateIndex)
		{
			m_cboHDTemplate.SetCurSel(-1);
		}
		else
		{
			m_cboHDTemplate.SetCurSel(tParam.iTemplateIndex);
		}
		
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_SCENETEMPLATE_MAP] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
}

void CLS_VCAAlarmLinkPage::OnBnClickedButtonSceneTempMapSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d), error (%d)", m_iLogonID, GetLastError());
		return;
	}

	SceneTemplateMap tParam = {0};
	tParam.iBufSize = sizeof(SceneTemplateMap);
	tParam.iSceneId = m_cboAlarmLinkScene.GetCurSel();
	int iTempID = m_cboHDTemplate.GetCurSel();
	if (iTempID == 8)
	{
		iTempID = (int)m_cboHDTemplate.GetItemData(iTempID);
	}
	tParam.iTemplateIndex = iTempID;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_SCENETEMPLATE_MAP, m_iChannelNo, &tParam, sizeof(SceneTemplateMap));
	if (iRet != 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig[NET_CLIENT_SCENETEMPLATE_MAP] (%d, %d), error(%d)"
			, m_iLogonID, m_iChannelNo, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_SCENETEMPLATE_MAP] (%d, %d)", m_iLogonID, m_iChannelNo);
	}
}

void CLS_VCAAlarmLinkPage::OnCbnSelchangeComboAlarmLinkScene()
{
	UI_UpdateSceneAndTemplateMap();
	UI_UpdateAlarmLinkType();
	UI_UpdateAlarmLinkEx();
}

void CLS_VCAAlarmLinkPage::UI_UpdateLaserVoice()
{
	m_cboLaserVioce.ResetContent();
	AudioSampleFileCount tInfo = {0};
	tInfo.iSize = sizeof(tInfo);
	int iReturn = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_AUDIO_SAMPLE_FILE_COUNT, m_iChannelNo, &tInfo, sizeof(tInfo), &iReturn);
	if(RET_SUCCESS == iRet)
	{
		if(tInfo.iTotalCount > 100 || tInfo.iTotalCount <= 0)
		{
			tInfo.iTotalCount = 3;
		}

		CString cstrTemp;
		int iItem = 0;
		for(int i = 0; i < tInfo.iSampleCount; i++)
		{
			cstrTemp.Format("%d", i+1);
			m_cboLaserVioce.InsertString(iItem++,GetText(IDS_LINK_GUARD_SOUND) + cstrTemp);
		}

		for(int j = 0; j < tInfo.iCustomCount; j++)
		{
			cstrTemp.Format("%d", j+1);
			m_cboLaserVioce.InsertString(iItem++,GetText(IDS_HD_MODE_CUSTOMIZED) + cstrTemp);
		}
		m_cboLaserVioce.SetCurSel(0);
	}
}

void CLS_VCAAlarmLinkPage::OnBnClickedBtnLaserviocePlay()
{
	//发送远程播放音频命令
	PlayAudioSample stAudio = {0};
	stAudio.iSize = sizeof(stAudio);
	stAudio.iType = 0;
	stAudio.iSampleNo = m_cboLaserVioce.GetCurSel();	
	int iRet =	NetClient_SendCommand(m_iLogonID, COMMAND_ID_PLAY_AUDIO_SAMPLE, m_iChannelNo, &stAudio, sizeof(stAudio));
}
