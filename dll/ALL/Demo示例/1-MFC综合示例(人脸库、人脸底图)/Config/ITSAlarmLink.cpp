
#include "stdafx.h"
#include "ITSAlarmLink.h"


IMPLEMENT_DYNAMIC(CLS_ITSAlarmLinkPage, CDialog)

CLS_ITSAlarmLinkPage::CLS_ITSAlarmLinkPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ITSAlarmLinkPage::IDD, pParent)
{
	m_iLogonId = -1;
	m_iChannelNo = -1;
	m_pclsChanCheck = NULL;
}

CLS_ITSAlarmLinkPage::~CLS_ITSAlarmLinkPage()
{
	if (NULL != m_pclsChanCheck)
	{
		delete m_pclsChanCheck;
		m_pclsChanCheck = NULL; 
	}
}

void CLS_ITSAlarmLinkPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_ITS_ILLEGAL_DETECT_SUB_ALARM_TYPE, m_cboSubAlarmType);
	DDX_Control(pDX, IDC_CHK_LINK_SINGLE_PIC, m_chkLinkSinglePic);
	DDX_Control(pDX, IDC_CHK_LINK_REC, m_chkLinkRecord);
	DDX_Control(pDX, IDC_CHK_LINK_PORT, m_chkLinkPort);
}


BEGIN_MESSAGE_MAP(CLS_ITSAlarmLinkPage, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_CBO_ITS_ILLEGAL_DETECT_SUB_ALARM_TYPE, &CLS_ITSAlarmLinkPage::OnCbnSelchangeCboItsIllegalDetectSubAlarmType)
	ON_BN_CLICKED(IDC_BTN_ITS_ILLEGAL_DETECT_SET, &CLS_ITSAlarmLinkPage::OnBnClickedBtnItsIllegalDetectLinkSet)
END_MESSAGE_MAP()


BOOL CLS_ITSAlarmLinkPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	UI_InitChanCheck();
	UI_UpdateDialog();

	return TRUE;
}

void CLS_ITSAlarmLinkPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
{
	m_iLogonId = _iLogonID;
	m_iChannelNo = (_iChannelNo < 0) ? 0 : _iChannelNo;
	UI_UpdateDialog();
	OnCbnSelchangeCboItsIllegalDetectSubAlarmType();
}

void CLS_ITSAlarmLinkPage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
	if (NULL != m_pclsChanCheck)
	{
		m_pclsChanCheck->OnLanguageChanged(_iLanguage);
	}
}

void CLS_ITSAlarmLinkPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_GBO_ITS_ILLEGAL_DETECT, IDS_ILLEGAL_DETECT);
	SetDlgItemTextEx(IDC_STC_ITS_ILLEGAL_DETECT_SUB_ALARM_TYPE, IDS_VCAEVENT_DETECT_STYLE);
	SetDlgItemText(IDC_CHK_ITS_ILLEGAL_DETECT_LINK_PORT_1, GetTextEx(IDS_LOGON_PORT) + _T("1"));
	SetDlgItemText(IDC_CHK_ITS_ILLEGAL_DETECT_LINK_PORT_2, GetTextEx(IDS_LOGON_PORT) + _T("2"));
	SetDlgItemTextEx(IDC_BTN_ITS_ILLEGAL_DETECT_SET, IDS_SET);
	
	SetDlgItemTextEx(IDC_CHK_LINK_SINGLE_PIC, IDS_CONFIG_DNVR_LINKSINGLEPIC);
	SetDlgItemTextEx(IDC_CHK_LINK_REC, IDS_CONFIG_DNVR_LINKRECORD);
	SetDlgItemTextEx(IDC_CHK_LINK_PORT, IDS_CONFIG_DNVR_LINKOUTPORT);
	UI_InitCboSubAlarmType();
}	

void CLS_ITSAlarmLinkPage::UI_InitCboSubAlarmType()
{
	int iTempSel = m_cboSubAlarmType.GetCurSel();
	iTempSel = (iTempSel < 0) ? 0 : iTempSel;
	m_cboSubAlarmType.ResetContent();
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_BAYONET)), 1);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_REDLIGHT)), 2);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_RETROGRADE)), 3);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_SPEED)), 4);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_FORBID_LEFT)), 5);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_FORBID_RIGHT)), 6);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_PRESS_YELLOW)), 7);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_NON_MOTOR)), 8);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_NOT_GUIDE_DRIVE)), 9);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_FORBID_STRAIGHT)), 10);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_BUS_WAY)), 11);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_PRESS_LINE)), 12);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_WAIT_RED_LIGHT)), 13);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_ILLEGAL_PARK)), 14);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_CONFIG_ITS_ILLEGALPARK)), 15);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_BACK)), 16);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_TURN2)), 17);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_CROSS_RED_LIGHT_AT_TRANSFER_AREA)), 18);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_FASTENSB)), 19);
	m_cboSubAlarmType.SetItemData(m_cboSubAlarmType.AddString(GetTextEx(IDS_ITS_CALLING)), 20);
	iTempSel = (iTempSel < m_cboSubAlarmType.GetCount()) ? iTempSel : 0;
	m_cboSubAlarmType.SetCurSel(iTempSel);
}

void CLS_ITSAlarmLinkPage::UI_UpdateAlarmLinkPortParam()
{
	if (m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonId);
		return;
	}

	int iRet = RET_FAILED;
	int iInportNum = 0;
	int iOutportNum = 0;
	int iChanEnable[LEN_16] = {0};
	TAlarmLinkParam_V3 tAlarmLinkPara = {0};
	tAlarmLinkPara.tAlarmParam.iSize = sizeof(TAlarmParam_V3);
	tAlarmLinkPara.tLinkParam.iSize = sizeof(TLinkParam_V3);

	int iAlarmType = ALARM_TYPE_ILLEGAL_DETECT;
	tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKOUTPORT;

	tAlarmLinkPara.tAlarmParam.iReserved = (int)m_cboSubAlarmType.GetItemData(m_cboSubAlarmType.GetCurSel());
	iRet = NetClient_GetAlarmConfig(m_iLogonId, m_iChannelNo, iAlarmType, CMD_GET_ALARMLINK_V3, &tAlarmLinkPara);
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetAlarmConfig(%d,%d,%d)",m_iLogonId,m_iChannelNo,iAlarmType);
		goto EXIT_FUNC;
	}
	AddLog(LOG_TYPE_SUCC,"","NetClient_GetAlarmConfig(%d,%d,%d)",m_iLogonId,m_iChannelNo,iAlarmType);

	for (int i = 0; i < LEN_16; i++)
	{
		iChanEnable[i] = tAlarmLinkPara.tLinkParam.uLinkParam.iCommonSet[i];
	}

	iRet = NetClient_GetAlarmPortNum(m_iLogonId, &iInportNum, &iOutportNum);
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetAlarmPortNum(%d)",m_iLogonId);
		goto EXIT_FUNC;
	}

	m_pclsChanCheck->InitData(iOutportNum, iChanEnable);

EXIT_FUNC:
	return;
}

void CLS_ITSAlarmLinkPage::OnCbnSelchangeCboItsIllegalDetectSubAlarmType()
{
	UI_UpdateAlarmLinkPortParam();
	UI_UpdateAlarmLinkSinglePicParam();
	UI_UpdateAlarmLinkRecordParam();
}

void CLS_ITSAlarmLinkPage::OnBnClickedBtnItsIllegalDetectLinkSet()
{
	//设置联动端口
	int iCommonSet[MAX_BITSET_COUNT] = {0};
	if (m_chkLinkPort.GetCheck())
	{	m_pclsChanCheck->GetChanValue(iCommonSet);
	}
	SetItsIllegalAlarmLink(ALARMLINKTYPE_LINKOUTPORT, iCommonSet);
 
	//设置联动录像 现在只支持联动当前通道
	memset(iCommonSet, 0, MAX_BITSET_COUNT);
	iCommonSet[m_iChannelNo / LEN_32] |= ((1 & m_chkLinkRecord.GetCheck()) << (m_iChannelNo % LEN_32));
	SetItsIllegalAlarmLink(ALARMLINKTYPE_LINKRECORD, iCommonSet);

	//设置联动单画面 现在只支持联动当前通道
	memset(iCommonSet, 0, MAX_BITSET_COUNT);
	iCommonSet[m_iChannelNo / LEN_32] |= ((1 & m_chkLinkSinglePic.GetCheck()) << (m_iChannelNo % LEN_32));
	SetItsIllegalAlarmLink(ALARMLINKTYPE_LINKRECORD, iCommonSet);
}

void CLS_ITSAlarmLinkPage::UI_InitChanCheck()
{
	RECT rcTemp = {0};
	if (NULL == m_pclsChanCheck)
	{
		m_pclsChanCheck = new CLS_ChanCheck();
	}

	if (NULL == m_pclsChanCheck)
	{
		goto EXIT_FUNC;
	}

	m_pclsChanCheck->Create(IDD_DLG_CFG_CHANNEL_CHECK, this);

	GetDlgItem(IDC_STC_ILLEGAL_LINKSET)->GetWindowRect(&rcTemp);
	ScreenToClient(&rcTemp);
	m_pclsChanCheck->MoveWindow(&rcTemp);
	m_pclsChanCheck->ShowWindow(SW_SHOW);
	
EXIT_FUNC:
	return;
}

int CLS_ITSAlarmLinkPage::SetItsIllegalAlarmLink(int _iLinkType, int* _iCommonSet)
{
	if (NULL == _iCommonSet)
	{
		AddLog(LOG_TYPE_SUCC,"","[CLS_ITSAlarmLinkPage::SetItsIllegalAlarmLink] NULL == _iCommonSet");
		return RET_FAILED;
	}
	if (m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonId);
		return RET_FAILED; 
	}

	int iRet = RET_FAILED;

	TAlarmLinkParam_V3 tAlarmLinkPara = {0};
	tAlarmLinkPara.tAlarmParam.iSize = sizeof(TAlarmParam_V3);
	tAlarmLinkPara.tLinkParam.iSize = sizeof(TLinkParam_V3);

	tAlarmLinkPara.tLinkParam.iLinkType = _iLinkType;
	tAlarmLinkPara.tAlarmParam.iReserved = (int)m_cboSubAlarmType.GetItemData(m_cboSubAlarmType.GetCurSel());
	int iAlarmType = ALARM_TYPE_ILLEGAL_DETECT;
	int iTempEnable[MAX_ILLEGAL_DETECT_LINKPORT] = {0};

	for (int i = 0; i < sizeof(_iCommonSet) / sizeof(int); i++)
	{
		tAlarmLinkPara.tLinkParam.uLinkParam.iCommonSet[i] = _iCommonSet[i];
	}

	iRet = NetClient_SetAlarmConfig(m_iLogonId, m_iChannelNo, iAlarmType, CMD_SET_ALARMLINK_V3, &tAlarmLinkPara);
	if (RET_SUCCESS == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetAlarmConfig(%d,%d,%d)",m_iLogonId,m_iChannelNo,iAlarmType);
		iRet = RET_SUCCESS;
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetAlarmConfig(%d,%d,%d)",m_iLogonId,m_iChannelNo,iAlarmType);
		iRet = RET_FAILED;
		goto EXIT_FUNC;
	}

EXIT_FUNC:
	return iRet;
	
}

void CLS_ITSAlarmLinkPage::UI_UpdateAlarmLinkSinglePicParam()
{
	if (m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonId);
		return;
	}

	int iRet = RET_FAILED;
	TAlarmLinkParam_V3 tAlarmLinkPara = {0};
	tAlarmLinkPara.tAlarmParam.iSize = sizeof(TAlarmParam_V3);
	tAlarmLinkPara.tLinkParam.iSize = sizeof(TLinkParam_V3);

	int iAlarmType = ALARM_TYPE_ILLEGAL_DETECT;
	tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKSINGLEPIC;

	tAlarmLinkPara.tAlarmParam.iReserved = (int)m_cboSubAlarmType.GetItemData(m_cboSubAlarmType.GetCurSel());
	iRet = NetClient_GetAlarmConfig(m_iLogonId, m_iChannelNo, iAlarmType, CMD_GET_ALARMLINK_V3, &tAlarmLinkPara);
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetAlarmConfig(%d,%d,%d)",m_iLogonId,m_iChannelNo,iAlarmType);
		goto EXIT_FUNC;
	}
	AddLog(LOG_TYPE_SUCC,"","NetClient_GetAlarmConfig(%d,%d,%d)",m_iLogonId,m_iChannelNo,iAlarmType);

	BOOL blTempChk = FALSE;
	blTempChk = (tAlarmLinkPara.tLinkParam.uLinkParam.iCommonSet[m_iChannelNo / LEN_32] >> ( m_iChannelNo % LEN_32 ) & 1) ? TRUE : FALSE;
	m_chkLinkSinglePic.SetCheck(blTempChk);

EXIT_FUNC:
	return;
}

void CLS_ITSAlarmLinkPage::UI_UpdateAlarmLinkRecordParam()
{
	if (m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonId);
		return;
	}

	int iRet = RET_FAILED;
	TAlarmLinkParam_V3 tAlarmLinkPara = {0};
	tAlarmLinkPara.tAlarmParam.iSize = sizeof(TAlarmParam_V3);
	tAlarmLinkPara.tLinkParam.iSize = sizeof(TLinkParam_V3);

	int iAlarmType = ALARM_TYPE_ILLEGAL_DETECT;
	tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKRECORD;

	tAlarmLinkPara.tAlarmParam.iReserved = (int)m_cboSubAlarmType.GetItemData(m_cboSubAlarmType.GetCurSel());
	iRet = NetClient_GetAlarmConfig(m_iLogonId, m_iChannelNo, iAlarmType, CMD_GET_ALARMLINK_V3, &tAlarmLinkPara);
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetAlarmConfig(%d,%d,%d)",m_iLogonId,m_iChannelNo,iAlarmType);
		goto EXIT_FUNC;
	}
	AddLog(LOG_TYPE_SUCC,"","NetClient_GetAlarmConfig(%d,%d,%d)",m_iLogonId,m_iChannelNo,iAlarmType);


	BOOL blTempChk = FALSE;
	blTempChk = (tAlarmLinkPara.tLinkParam.uLinkParam.iCommonSet[m_iChannelNo / LEN_32] >> ( m_iChannelNo % LEN_32 ) & 1) ? TRUE : FALSE;
	m_chkLinkRecord.SetCheck(blTempChk);

EXIT_FUNC:
	return;
}
