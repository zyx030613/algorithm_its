// DNVRAlmLinkPage.cpp : implementation file
//

#include "stdafx.h"
#include "DNVRAlmLinkPage.h"

#define PORT_ALARM				6
#define VIDEO_LOST				0
#define VIDEO_MOTION			1
#define VIDEO_COVER				2
#define AUDIO_LOST				3
#define TEMPERATURE_ALARM		4
#define ILLEGAL_DETECT			5

#define LINK_RECORD				0
#define LINK_SNAP				1
#define LINK_OUTPORT			8
#define LINK_AUDIO_VIDEO		2
#define LINK_PTZ				3
#define LINK_SINGLEPIC			4
#define LINK_MAIL				5
#define LINK_HTTP				6
#define LINK_LASER				7

#define NO_LINK					0
#define PRESET					1
#define TRACK					2
#define CRUISEPATH				3

#define PTZ_TYPE_NONE			0
#define PTZ_TYPE_PRESET			1
#define PTZ_TYPE_TRACK			2
#define PTZ_TYPE_CRUISEPATH		3

// CLS_DNVRAlmLinkPage dialog

IMPLEMENT_DYNAMIC(CLS_DNVRAlmLinkPage, CDialog)

CLS_DNVRAlmLinkPage::CLS_DNVRAlmLinkPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DNVRAlmLinkPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_pclsChanCheck = NULL;
	m_iAlarmTypeCMD = 0;
}

CLS_DNVRAlmLinkPage::~CLS_DNVRAlmLinkPage()
{
	if (NULL != m_pclsChanCheck)
	{
		delete m_pclsChanCheck;
		m_pclsChanCheck = NULL; 
	}
}

void CLS_DNVRAlmLinkPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cboType);
	DDX_Control(pDX, IDC_COMBO_LINKTYPE, m_cboLinkType);
	DDX_Control(pDX, IDC_COMBO_INPORT, m_cboInPort);
	DDX_Control(pDX, IDC_BUTTON_CHANNELENABLE, m_btnChannelEnable);
	DDX_Control(pDX, IDC_CHECK_DISPLAYENABLE, m_chkDisplayEnable);
	DDX_Control(pDX, IDC_CHECK_SOUNDENABLE, m_chkSoundEnable);
	DDX_Control(pDX, IDC_BUTTON_AVIDEO, m_btnAVideo);
	DDX_Control(pDX, IDC_COMBO_LINKCHANNELNO, m_cboLinkChannelNo);
	DDX_Control(pDX, IDC_COMBO_LINKPTZTYPE, m_cboLinkPTZType);
	DDX_Control(pDX, IDC_EDIT_LINKACTNO, m_edtLinkACTNo);
	DDX_Control(pDX, IDC_BUTTON_LINK, m_btnLink);
	DDX_Control(pDX, IDC_COMBO_SINGLEPIC_CHANNEL, m_cboSinglePic);
	DDX_Control(pDX, IDC_CBO_ALARM_LINK_COMMON_ENABLE, m_cboCommonEnable);
}


BEGIN_MESSAGE_MAP(CLS_DNVRAlmLinkPage, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CLS_DNVRAlmLinkPage::OnCbnSelchangeComboType)
	ON_CBN_SELCHANGE(IDC_COMBO_LINKTYPE, &CLS_DNVRAlmLinkPage::OnCbnSelchangeComboLinktype)
	ON_CBN_SELCHANGE(IDC_COMBO_INPORT, &CLS_DNVRAlmLinkPage::OnCbnSelchangeComboInport)
	ON_BN_CLICKED(IDC_BUTTON_CHANNELENABLE, &CLS_DNVRAlmLinkPage::OnBnClickedButtonChannelenable)
	ON_BN_CLICKED(IDC_BUTTON_AVIDEO, &CLS_DNVRAlmLinkPage::OnBnClickedButtonAvideo)
	ON_CBN_SELCHANGE(IDC_COMBO_LINKCHANNELNO, &CLS_DNVRAlmLinkPage::OnCbnSelchangeComboLinkchannelno)
	ON_BN_CLICKED(IDC_BUTTON_LINK, &CLS_DNVRAlmLinkPage::OnBnClickedButtonLink)
	ON_BN_CLICKED(IDC_BUTTON_SINGLEPIC_CHANNEL, &CLS_DNVRAlmLinkPage::OnBnClickedButtonSinglepicChannel)
	ON_BN_CLICKED(IDC_BTN_ALARM_LINK_COMMON_ENABLE_SET, &CLS_DNVRAlmLinkPage::OnBnClickedBtnAlarmLinkCommonEnableSet)
END_MESSAGE_MAP()


// CLS_DNVRAlmLinkPage message handlers
BOOL CLS_DNVRAlmLinkPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	UI_UpdateDialog();
	UI_UpdateChanCheck();
	m_cboType.SetCurSel(0);
	m_cboLinkType.SetCurSel(0);
	m_cboLinkPTZType.SetCurSel(0);

	int iOffset = 0;
	RECT rcPC = {0};
	RECT rcTemp = {0};
	GetDlgItem(IDC_STATIC_LINKSET)->GetWindowRect(&rcPC);
	ScreenToClient(&rcPC);

	GetDlgItem(IDC_STATIC_LINKSETAVIDEO)->GetWindowRect(&rcTemp);
	ScreenToClient(&rcTemp);
	iOffset = rcPC.top - rcTemp.top;
	OffsetWindow(IDC_STATIC_LINKSETAVIDEO,0,iOffset);
	OffsetWindow(IDC_CHECK_DISPLAYENABLE,0,iOffset);
	OffsetWindow(IDC_CHECK_SOUNDENABLE,0,iOffset);
	OffsetWindow(IDC_BUTTON_AVIDEO,0,iOffset);
	
	GetDlgItem(IDC_STATIC_LINK_SET_PTZ)->GetWindowRect(&rcTemp);
	ScreenToClient(&rcTemp);
	iOffset = rcPC.top - rcTemp.top;
	OffsetWindow(IDC_STATIC_LINK_SET_PTZ,0,iOffset);
	OffsetWindow(IDC_STATIC_LINKCHANNELNO,0,iOffset);
	OffsetWindow(IDC_STATIC_LINKPTZTYPE,0,iOffset);
	OffsetWindow(IDC_STATIC_LINKACTNO,0,iOffset);
	OffsetWindow(IDC_COMBO_LINKCHANNELNO,0,iOffset);
	OffsetWindow(IDC_COMBO_LINKPTZTYPE,0,iOffset);
	OffsetWindow(IDC_EDIT_LINKACTNO,0,iOffset);
	OffsetWindow(IDC_BUTTON_LINK,0,iOffset);

	GetDlgItem(IDC_STATIC_LINK_SET_PTZ2)->GetWindowRect(&rcTemp);
	ScreenToClient(&rcTemp);
	iOffset = rcPC.top - rcTemp.top;
	OffsetWindow(IDC_STATIC_LINK_SET_PTZ2,0,iOffset);
	OffsetWindow(IDC_STATIC_SINGLEPIC_CHANNEL,0,iOffset);
	OffsetWindow(IDC_COMBO_SINGLEPIC_CHANNEL,0,iOffset);
	OffsetWindow(IDC_BUTTON_SINGLEPIC_CHANNEL,0,iOffset);

	GetDlgItem(IDC_GBO_ALARM_LINK_COMMON_ENABLE)->GetWindowRect(&rcTemp);
	ScreenToClient(&rcTemp);
	iOffset = rcPC.top - rcTemp.top;
	OffsetWindow(IDC_GBO_ALARM_LINK_COMMON_ENABLE,0,iOffset);
	OffsetWindow(IDC_CBO_ALARM_LINK_COMMON_ENABLE,0,iOffset);
	OffsetWindow(IDC_BTN_ALARM_LINK_COMMON_ENABLE_SET,0,iOffset);

	return TRUE;
}

void CLS_DNVRAlmLinkPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
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

	UI_ShowLinkType();
	UI_UpdateType();
	UI_UpdateLinkSetAVideo();
	UI_UpdateLinkSinPic();
	OnCbnSelchangeComboInport();
}

void CLS_DNVRAlmLinkPage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_DNVRAlmLinkPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_TYPE,IDS_CONFIG_DNVR_ALMLINK_TYPE);
	SetDlgItemTextEx(IDC_STATIC_LINKTYPE,IDS_CONFIG_DNVR_ALMLINK_LINKTYPE);
	SetDlgItemTextEx(IDC_STATIC_INPORT,IDS_CONFIG_DNVR_ALMLINK_INPORT);
	//SetDlgItemTextEx(IDC_STATIC_LINKSET,IDS_CONFIG_DNVR_ALMLINK_LINKSET);
	SetDlgItemTextEx(IDC_STATIC_CHANNELENABLE,IDS_CONFIG_DNVR_ALMLINK_CHANNELENABLE);
	SetDlgItemTextEx(IDC_BUTTON_CHANNELENABLE,IDS_SET);
	//SetDlgItemTextEx(IDC_STATIC_LINKSETAVIDEO,IDS_CONFIG_DNVR_ALMLINK_LINKSETAVIDEO);
	SetDlgItemTextEx(IDC_CHECK_DISPLAYENABLE,IDS_CONFIG_DNVR_ALMLINK_DISPLAYENABLE);
	SetDlgItemTextEx(IDC_CHECK_SOUNDENABLE,IDS_CONFIG_DNVR_ALMLINK_SOUNDENABLE);
	SetDlgItemTextEx(IDC_BUTTON_AVIDEO,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_LINKCHANNELNO,IDS_CONFIG_DNVR_ALMLINK_LINKCHANNELNO);
	SetDlgItemTextEx(IDC_STATIC_LINKPTZTYPE,IDS_CONFIG_DNVR_ALMLINK_LINKPTZTYPE);
	SetDlgItemTextEx(IDC_STATIC_LINKACTNO,IDS_CONFIG_DNVR_ALMLINK_LINKACTNO);
	SetDlgItemTextEx(IDC_BUTTON_LINK,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_SINGLEPIC_CHANNEL,IDS_ALARM_LINK_SINGLEPIC_CHANNEL);
	SetDlgItemTextEx(IDC_BUTTON_SINGLEPIC_CHANNEL,IDS_SET);

	SetDlgItemTextEx(IDC_CHECK_DOUBLE_LIGHT_DAYNIGHT,IDS_DAYNIGHT_MODEL);
	SetDlgItemTextEx(IDC_CHECK_DOUBLE_LIGHT_COLOR,IDS_COLOR_MODEL);
	SetDlgItemTextEx(IDC_BUTTON_DOUBLE_LIGHT,IDS_SET);

	if (1 == m_iChangeInPort)
	{
		SetDlgItemTextEx(IDC_STATIC_INPORT,IDS_CONFIG_DNVR_ALMSCH_INPORT);
	}
	else if (0 == m_iChangeInPort)
	{
		SetDlgItemTextEx(IDC_STATIC_INPORT,IDS_CONFIG_DNVR_ALMSCH_CHANNELNO);
	}
	if (1 == m_iChangeOutPort)
	{
		SetDlgItemTextEx(IDC_STATIC_CHANNELENABLE,IDS_CONFIG_DNVR_ALMLINK_OUTPORT);
	}
	else if (0 == m_iChangeOutPort)
	{
		SetDlgItemTextEx(IDC_STATIC_CHANNELENABLE,IDS_CONFIG_DNVR_ALMLINK_CHANNELENABLE);
	}

	//输入端口报警联动输出端口报警 与IO联动中的端口报警联动端口输出，功能重复。
	//InsertString(m_cboType,0,IDS_CONFIG_DNVR_PORTALARM);
	InsertString(m_cboType,0,IDS_CONFIG_DNVR_VIDEOLOST);
	InsertString(m_cboType,1,IDS_CONFIG_DNVR_VIDEOMOTION);
	InsertString(m_cboType,2,IDS_CONFIG_DNVR_VIDEOCOVER);
	InsertString(m_cboType,3,IDS_CONFIG_DNVR_AUDIOLOST);
	InsertString(m_cboType,4,IDS_CONFIG_DVR_TEMPERATURE);

	InsertString(m_cboLinkType,0,IDS_CONFIG_DNVR_LINKRECORD);
	InsertString(m_cboLinkType,1,IDS_CONFIG_DNVR_LINKSNAP);
	//InsertString(m_cboLinkType,2,IDS_CONFIG_DNVR_LINKOUTPORT);
	InsertString(m_cboLinkType,2,IDS_CONFIG_DNVR_LINKAUDIO);
	InsertString(m_cboLinkType,3,IDS_CONFIG_DNVR_LINKPTZ);
	InsertString(m_cboLinkType,4,IDS_CONFIG_DNVR_LINKSINGLEPIC);
	InsertString(m_cboLinkType,5,IDS_CONFIG_CMOS_MAILENABLE);
	InsertString(m_cboLinkType,6,IDS_HTTP);
	InsertString(m_cboLinkType,7,IDS_LASER);
	//InsertString(m_cboLinkType,5,IDS_CONFIG_DNVR_LINKSINGLEPIC);
	
	InsertString(m_cboLinkPTZType,0,IDS_CONFIG_DNVR_NOLINK);
	InsertString(m_cboLinkPTZType,1,IDS_CONFIG_DNVR_PRESET);
	InsertString(m_cboLinkPTZType,2,IDS_CONFIG_DNVR_TRACK);
	InsertString(m_cboLinkPTZType,3,IDS_CONFIG_DNVR_CRUISEPATH);
	
	int iTempIndex = 0;
	iTempIndex = m_cboCommonEnable.GetCurSel();
	iTempIndex = (iTempIndex < 0) ? 0 : iTempIndex; 
	m_cboCommonEnable.ResetContent();
	m_cboCommonEnable.SetItemData(m_cboCommonEnable.AddString(GetTextEx(IDS_CONFIG_FTP_SNAPSHOT_DISABLE)), 0);
	m_cboCommonEnable.SetItemData(m_cboCommonEnable.AddString(GetTextEx(IDS_CONFIG_FTP_SNAPSHOT_ENABLE)), 1);
	iTempIndex = (iTempIndex < m_cboCommonEnable.GetCount()) ? iTempIndex : 0;
	m_cboCommonEnable.SetCurSel(iTempIndex);
}

BOOL CLS_DNVRAlmLinkPage::UI_UpdateType()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iAlarmInPortNum = -1;
	int iAlarmOutPortNum = -1;
	int iChannelNum = -1;
	int iRet;

	if (PORT_ALARM == m_cboType.GetCurSel())
	{
		iRet = NetClient_GetAlarmPortNum(m_iLogonID, &iAlarmInPortNum, &iAlarmOutPortNum);
		if (0 == iRet)
		{
			m_iChangeInPort = 1;
			if (m_cboInPort.GetCount() != iAlarmInPortNum)
			{
				m_cboInPort.ResetContent();
				for (int i=0; i<iAlarmInPortNum; i++)
				{
					m_cboInPort.InsertString(i, IntToStr(i).c_str());
				}
			}
			InsertString(m_cboInPort,iAlarmInPortNum,IDS_CONFIG_DNVR_ALL);
			m_cboInPort.SetCurSel(0);
			AddLog(LOG_TYPE_SUCC,"","NetClient_GetAlarmPortNum (%d,%d,%d)",m_iLogonID,iAlarmInPortNum,iAlarmOutPortNum);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetAlarmPortNum (%d,%d,%d)",m_iLogonID,iAlarmInPortNum,iAlarmOutPortNum);
		}
	}
	else
	{
		iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
		if (0 == iRet)
		{
			m_iChangeInPort = 0;
			if (m_cboInPort.GetCount() != iChannelNum)
			{
				m_cboInPort.ResetContent();
				for (int i=0; i<iChannelNum && i < 32; i++)
				{
					m_cboInPort.InsertString(i, IntToStr(i).c_str());
				}
				InsertString(m_cboInPort,iChannelNum,IDS_CONFIG_DNVR_ALL);
				m_cboInPort.SetCurSel(0);
			}
			AddLog(LOG_TYPE_SUCC,"","NetClient_GetChannelNum (%d,%d)",m_iLogonID,iChannelNum);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetChannelNum (%d,%d)",m_iLogonID,iChannelNum);
		}
	}

	if (LINK_OUTPORT == m_cboLinkType.GetCurSel())
	{
		m_iChangeOutPort = 1;
	}
	else
	{
		m_iChangeOutPort = 0;
	}
	return TRUE;
}

void CLS_DNVRAlmLinkPage::OnCbnSelchangeComboType()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	int iAlarmType = m_cboType.GetCurSel();

	int iAlarmInPortNum = -1;
	int iAlarmOutPortNum = -1;
	int iChannelNum = -1;
	int iRet;

	if (PORT_ALARM == iAlarmType)
	{
		iRet = NetClient_GetAlarmPortNum(m_iLogonID, &iAlarmInPortNum, &iAlarmOutPortNum);
		if (0 == iRet)
		{
			m_iChangeInPort = 1;
			if (m_cboInPort.GetCount() != iAlarmInPortNum)
			{
				m_cboInPort.ResetContent();
				for (int i=0; i<iAlarmInPortNum; i++)
				{
					CString strInPort;
					strInPort.Format("%d",i);
					m_cboInPort.AddString(strInPort);
				}
			}
			InsertString(m_cboInPort,iAlarmInPortNum,IDS_CONFIG_DNVR_ALL);
			m_cboInPort.SetCurSel(0);
			AddLog(LOG_TYPE_SUCC,"","NetClient_GetAlarmPortNum (%d,%d,%d)",m_iLogonID,iAlarmInPortNum,iAlarmOutPortNum);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetAlarmPortNum (%d,%d,%d)",m_iLogonID,iAlarmInPortNum,iAlarmOutPortNum);
		}
	}
	else
	{
		iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
		if (0 == iRet)
		{
			m_iChangeInPort = 0;
			if (m_cboInPort.GetCount() != iChannelNum)
			{
				m_cboInPort.ResetContent();
				for (int i=0; i<iChannelNum && i < 32; i++)
				{
					CString strInPort;
					strInPort.Format("%d",i);
					m_cboInPort.AddString(strInPort);
				}
				InsertString(m_cboInPort,iAlarmInPortNum,IDS_CONFIG_DNVR_ALL);
				m_cboInPort.SetCurSel(0);
			}
			AddLog(LOG_TYPE_SUCC,"","NetClient_GetChannelNum (%d,%d)",m_iLogonID,iChannelNum);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetChannelNum (%d,%d)",m_iLogonID,iChannelNum);
		}
	}
	if (1 == m_iChangeInPort)
	{
		SetDlgItemTextEx(IDC_STATIC_INPORT,IDS_CONFIG_DNVR_ALMSCH_INPORT);
	}
	else if (0 == m_iChangeInPort)
	{
		SetDlgItemTextEx(IDC_STATIC_INPORT,IDS_CONFIG_DNVR_ALMSCH_CHANNELNO);
	}

	OnCbnSelchangeComboInport();
}

void CLS_DNVRAlmLinkPage::OnCbnSelchangeComboLinktype()
{
	UI_ShowLinkType();
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	if (LINK_OUTPORT == m_cboLinkType.GetCurSel())
	{
		m_iChangeOutPort = 1;
	}
	else
	{
		m_iChangeOutPort = 0;
	}
	if (1 == m_iChangeOutPort)
	{
		SetDlgItemTextEx(IDC_STATIC_CHANNELENABLE,IDS_CONFIG_DNVR_ALMLINK_OUTPORT);
	}
	else if (0 == m_iChangeOutPort)
	{
		SetDlgItemTextEx(IDC_STATIC_CHANNELENABLE,IDS_CONFIG_DNVR_ALMLINK_CHANNELENABLE);
	}
	OnCbnSelchangeComboInport();
}

void CLS_DNVRAlmLinkPage::OnCbnSelchangeComboInport()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iChannelNum = 0;	//通道总数
	NetClient_GetChannelNum(m_iLogonID, &iChannelNum);

	int iChanEnable[LEN_16] = {0};
	TAlarmLinkParam_V3 tAlarmLinkPara = {0};
	tAlarmLinkPara.tAlarmParam.iSize = sizeof(TAlarmParam_V3);
	tAlarmLinkPara.tLinkParam.iSize = sizeof(TLinkParam_V3);

	int iRet = -1;
	int iAlarmType = m_cboType.GetCurSel();		//报警类型
	int iLinkType = m_cboLinkType.GetCurSel();	//联动类型

	switch(iAlarmType)
	{
	case PORT_ALARM:
		m_iAlarmTypeCMD = ALARM_TYPE_PORT_ALARM;
		break;
	case VIDEO_LOST:
		m_iAlarmTypeCMD = ALARM_TYPE_VIDEO_LOST;
		break;
	case VIDEO_MOTION:
		m_iAlarmTypeCMD = ALARM_TYPE_MOTION_DETECTION;
		break;
	case VIDEO_COVER:
		m_iAlarmTypeCMD = ALARM_TYPE_VIDEO_COVER;
		break;
	case AUDIO_LOST:
		m_iAlarmTypeCMD = ALARM_TYPE_AUDIOLOST;
		break;
	case TEMPERATURE_ALARM:
		m_iAlarmTypeCMD = ALARM_TYPE_TEMPERATURE;	
		break;
	case ILLEGAL_DETECT:
		m_iAlarmTypeCMD = ALARM_TYPE_ILLEGAL_DETECT;			
		break;
	default:
		break;
	}

	int iInportNum=0, iOutportNum=0; 
	switch (iLinkType)
	{
	case LINK_RECORD:	//联动录像
		tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKRECORD;
		break;
	case LINK_SNAP:		//联动抓拍
		tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKSNAP;
		break;
	case LINK_OUTPORT:	//联动输出端口
		tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKOUTPORT;
		iRet = NetClient_GetAlarmPortNum(m_iLogonID, &iInportNum, &iOutportNum);
		iChannelNum = iOutportNum;
		break;
	case LINK_HTTP:
		tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKHTTP;
		iChannelNum = MAX_LINK_HTTP_INDEX;
		break;
	case LINK_AUDIO_VIDEO:	//联动音视频
		tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKSOUND;
		iRet = NetClient_GetAlarmConfig(m_iLogonID, m_iChannelNo, m_iAlarmTypeCMD, CMD_GET_ALARMLINK_V3, &tAlarmLinkPara);
		m_chkSoundEnable.SetCheck(tAlarmLinkPara.tLinkParam.uLinkParam.tLinkSoundParam.iEnable ? BST_CHECKED : BST_UNCHECKED);

		tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKDISPLAY;
		iRet = NetClient_GetAlarmConfig(m_iLogonID, m_iChannelNo, m_iAlarmTypeCMD, CMD_GET_ALARMLINK_V3, &tAlarmLinkPara);
		m_chkDisplayEnable.SetCheck(tAlarmLinkPara.tLinkParam.uLinkParam.tLinkDisplayParam.iEnable ? BST_CHECKED : BST_UNCHECKED);
		return;
	case LINK_PTZ:		//联动PTZ
		tAlarmLinkPara.tLinkParam.iLinkType = ALARM_LINKTYPE_PTZ;
		tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.iPtzNo = m_cboLinkChannelNo.GetCurSel();
		iRet = NetClient_GetAlarmConfig(m_iLogonID, m_iChannelNo, m_iAlarmTypeCMD, CMD_GET_ALARMLINK_V3, &tAlarmLinkPara);
		m_cboLinkPTZType.SetCurSel(tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usType);
		SetDlgItemInt(IDC_EDIT_LINKACTNO, tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usTypeNO);
		return;
	case LINK_SINGLEPIC://联动单画面
		tAlarmLinkPara.tLinkParam.iLinkType = ALARM_LINKTYPE_SINGLEPIC;
		iRet = NetClient_GetAlarmConfig(m_iLogonID, m_iChannelNo, m_iAlarmTypeCMD, CMD_GET_ALARMLINK_V3, &tAlarmLinkPara);
		for (int i=0; i<LEN_16; i++)
		{
			iChanEnable[i] = tAlarmLinkPara.tLinkParam.uLinkParam.iCommonSet[i];
		}
		for (int i=0; i<iChannelNum; i++)
		{
			if (iChanEnable[i/LEN_32]>>(i%32)&1)
			{
				m_cboSinglePic.SetCurSel(i+1);
				break;
			}
		}
		return;
	case LINK_MAIL:	
	case LINK_LASER:
		tAlarmLinkPara.tLinkParam.iLinkType = iLinkType + 1;
		NetClient_GetAlarmConfig(m_iLogonID, m_iChannelNo, m_iAlarmTypeCMD, CMD_GET_ALARMLINK_V3, &tAlarmLinkPara);
		m_cboCommonEnable.SetCurSel(GetCboSel(&m_cboCommonEnable, tAlarmLinkPara.tLinkParam.uLinkParam.iCommonSet[0]));
		return;
	default:
		break;
	}

	iRet = NetClient_GetAlarmConfig(m_iLogonID, m_iChannelNo, m_iAlarmTypeCMD, CMD_GET_ALARMLINK_V3, &tAlarmLinkPara);
	for (int i=0; i < (sizeof(iChanEnable)/sizeof(int)); i++)
	{
		iChanEnable[i] = tAlarmLinkPara.tLinkParam.uLinkParam.iCommonSet[i]; 
	}

	m_pclsChanCheck->InitData(iChannelNum, iChanEnable);
}

void CLS_DNVRAlmLinkPage::OnBnClickedButtonChannelenable()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TAlarmLinkParam_V3 tAlarmLinkPara = {0};
	tAlarmLinkPara.tAlarmParam.iSize = sizeof(TAlarmParam_V3);
	tAlarmLinkPara.tLinkParam.iSize = sizeof(TLinkParam_V3);

	switch (m_cboLinkType.GetCurSel())
	{
	case LINK_RECORD:	//联动录像
		tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKRECORD;
		break;
	case LINK_SNAP:		//联动抓拍
		tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKSNAP;
		break;
	case LINK_OUTPORT:	//联动输出端口
		tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKOUTPORT;
		break;
	case LINK_HTTP:	
		tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKHTTP;
		break;	
	default:
		break;
	}

	m_pclsChanCheck->GetChanValue(tAlarmLinkPara.tLinkParam.uLinkParam.iCommonSet);

	int iRet = NetClient_SetAlarmConfig(m_iLogonID, m_iChannelNo, m_iAlarmTypeCMD, CMD_SET_ALARMLINK_V3, &tAlarmLinkPara);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetAlarmConfig(%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iAlarmTypeCMD);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetAlarmConfig(%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iAlarmTypeCMD);
	}
}

BOOL CLS_DNVRAlmLinkPage::UI_UpdateLinkSetAVideo()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iChannelNum = 0;
	m_cboLinkChannelNo.ResetContent();
	int iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
	for (int i=0; i<iChannelNum; i++)
	{
		CString strChannelNum;
		strChannelNum.Format("%d",i);
		m_cboLinkChannelNo.AddString(strChannelNum);
	}
	m_cboLinkChannelNo.SetCurSel(0);
	return TRUE;
}

void CLS_DNVRAlmLinkPage::OnBnClickedButtonAvideo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	//联动声音提示
	TAlarmLinkParam_V3 tAlarmLinkPara = {0};
	tAlarmLinkPara.tAlarmParam.iSize = sizeof(TAlarmParam_V3);
	tAlarmLinkPara.tLinkParam.iSize = sizeof(TLinkParam_V3);

	tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKSOUND;
	tAlarmLinkPara.tLinkParam.uLinkParam.tLinkSoundParam.iEnable = (BST_CHECKED == m_chkSoundEnable.GetCheck()) ? 1 : 0;
	int iRetSound = NetClient_SetAlarmConfig(m_iLogonID, m_iChannelNo, m_iAlarmTypeCMD, CMD_SET_ALARMLINK_V3, &tAlarmLinkPara);
	/////连续设置可能有问题，设备上一条协议还没回复的时候SDK还没改，立马再设置，可能就错了
	Sleep(1500);
	//联动视频显示
	tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKDISPLAY;
	tAlarmLinkPara.tLinkParam.uLinkParam.tLinkDisplayParam.iEnable = (BST_CHECKED == m_chkDisplayEnable.GetCheck()) ? 1 : 0;
	int iRetDisPlay = NetClient_SetAlarmConfig(m_iLogonID, m_iChannelNo, m_iAlarmTypeCMD, CMD_SET_ALARMLINK_V3, &tAlarmLinkPara);
	if (0 == iRetDisPlay && 0 == iRetSound)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetAlarmConfig(%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iAlarmTypeCMD);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetAlarmConfig(%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iAlarmTypeCMD);
	}
}

void CLS_DNVRAlmLinkPage::OnCbnSelchangeComboLinkchannelno()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	int iRet = 0;
	int iPortNo = 0;
	int iChannelNo = 0;
	if (m_cboInPort.GetCount() - 1 == m_cboInPort.GetCurSel())
	{
		return;
	}
	else
	{
		iPortNo = GetDlgItemInt(IDC_COMBO_INPORT);
		iChannelNo = GetDlgItemInt(IDC_COMBO_INPORT);
	}
	int iLinkChannelNo = m_cboLinkChannelNo.GetCurSel();
	int iPTZLinkType = -1;
	
	if (m_cboType.GetCurSel() == AUDIO_LOST)
	{
		TAlarmLinkParam_V3 tAlarmLinkPara = {0};
		tAlarmLinkPara.tAlarmParam.iSize = sizeof(TAlarmParam_V3);
		tAlarmLinkPara.tLinkParam.iSize = sizeof(TLinkParam_V3);


		tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKPTZ;
		tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.iPtzNo = iLinkChannelNo;
		iRet = NetClient_GetAlarmConfig(m_iLogonID, iChannelNo, ALARM_TYPE_AUDIOLOST, CMD_GET_ALARMLINK_V3, &tAlarmLinkPara);

		iPTZLinkType = tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usType;
		m_cboLinkPTZType.SetCurSel(iPTZLinkType);	
		switch (iPTZLinkType)
		{
		case PTZ_TYPE_PRESET:
		case PTZ_TYPE_TRACK:
		case PTZ_TYPE_CRUISEPATH:
			SetDlgItemInt(IDC_EDIT_LINKACTNO,tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usTypeNO);
			break;
		default:
			SetDlgItemInt(IDC_EDIT_LINKACTNO, 0);
			break;
		}
		return;
	}
	else
	{
		int iAlarmType = m_cboType.GetCurSel();
		TAlarmLinkParam_V3 tAlarmLinkPara = {0};
		tAlarmLinkPara.tAlarmParam.iSize = sizeof(TAlarmParam_V3);
		tAlarmLinkPara.tLinkParam.iSize = sizeof(TLinkParam_V3);

		tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKPTZ;
		tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.iPtzNo = iLinkChannelNo;
		iRet = NetClient_GetAlarmConfig(m_iLogonID, iPortNo, iAlarmType, CMD_GET_ALARMLINK_V3, &tAlarmLinkPara);

		if (0 == iRet)
		{
			m_cboLinkPTZType.SetCurSel(iPTZLinkType);
			int iActNum = tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usTypeNO;
			SetDlgItemInt(IDC_EDIT_LINKACTNO, iActNum);
		}
	}

}


void CLS_DNVRAlmLinkPage::OnBnClickedBtnAlarmLinkCommonEnableSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TAlarmLinkParam_V3 tAlarmLinkPara = {0};
	tAlarmLinkPara.tAlarmParam.iSize = sizeof(TAlarmParam_V3);
	tAlarmLinkPara.tLinkParam.iSize = sizeof(TLinkParam_V3);

	switch (m_cboLinkType.GetCurSel())
	{
	case LINK_MAIL:	
		tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKEMAIL;
		break;
	case LINK_LASER:	
		tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LASER;
		break;
	default:
		{
			AddLog(LOG_TYPE_MSG,"","Err LinkType(%d)",m_cboLinkType.GetCurSel());
			return;
		}
		break;
	}

	tAlarmLinkPara.tLinkParam.uLinkParam.tLinkDisplayParam.iEnable = (int)m_cboCommonEnable.GetItemData(m_cboCommonEnable.GetCurSel());
	
	int iRet = NetClient_SetAlarmConfig(m_iLogonID, m_iChannelNo, m_iAlarmTypeCMD, CMD_SET_ALARMLINK_V3, &tAlarmLinkPara);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetAlarmConfig(%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iAlarmTypeCMD);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetAlarmConfig(%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iAlarmTypeCMD);
	}
}

void CLS_DNVRAlmLinkPage::OnBnClickedButtonLink()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	if (m_cboType.GetCurSel() == VIDEO_MOTION)
	{
		AddLog(LOG_TYPE_MSG,"","Video motion can not link");
		return;
	}

	TAlarmLinkParam_V3 tAlarmLinkPara = {0};
	tAlarmLinkPara.tAlarmParam.iSize = sizeof(TAlarmParam_V3);
	tAlarmLinkPara.tLinkParam.iSize = sizeof(TLinkParam_V3);

	tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKPTZ;

	int iLinkChannelNo = m_cboLinkChannelNo.GetCurSel();	//联动通道

	//此处之前赋值可能有问题 之后需要跟一下
	tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usType = m_cboLinkPTZType.GetCurSel();	//联动PTZ类型

	//判断联动通道PTZ个数是否超过64
	int iPtzCount = 0;			//已经联动的通道
	bool bSelfLink = false;		//是否已联动了当前设置的通道
	int iChannelNum = 0;
	NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
	for (int i=0; i<iChannelNum; i++)
	{
		tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.iPtzNo = i;
		NetClient_GetAlarmConfig(m_iLogonID, i, m_iAlarmTypeCMD, CMD_GET_ALARMLINK_V3, &tAlarmLinkPara);
		if (LINKPTZ_TYPE_NOLINK != tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam.usType)
		{
			if (iLinkChannelNo == i)
			{
				bSelfLink = true;
			}
			iPtzCount++;
		}
	}

	//添加手动输入数据有效范围判断
	int iActNum = GetDlgItemInt(IDC_EDIT_LINKACTNO);
	int iCount = ActionInit();
	int iIndexMin = iCount > 0 ? 0 : -1;
	int iIndexMax = iCount;
	iActNum = iActNum < iIndexMin ? iIndexMin : iActNum;
	iActNum = iActNum > iIndexMax ? iIndexMax : iActNum;

	TLinkPtzParam_V3 &tLinkPtzParam = tAlarmLinkPara.tLinkParam.uLinkParam.tLinkPtzParam;
	tLinkPtzParam.iPtzNo = iLinkChannelNo;
	if(m_cboLinkPTZType.GetCurSel()==0)
	{
		tLinkPtzParam.usType = LINKPTZ_TYPE_NOLINK;
		tLinkPtzParam.usTypeNO = 0;
	}
	else if(m_cboLinkPTZType.GetCurSel()==1)
	{
		tLinkPtzParam.usType = LINKPTZ_TYPE_PRESET;
		tLinkPtzParam.usTypeNO = iActNum;
	}
	else if(m_cboLinkPTZType.GetCurSel()==2)
	{
		tLinkPtzParam.usType = LINKPTZ_TYPE_TRACK;
		tLinkPtzParam.usTypeNO = iActNum;
	}
	else if(m_cboLinkPTZType.GetCurSel()==3)
	{
		tLinkPtzParam.usType = LINKPTZ_TYPE_PATH;
		tLinkPtzParam.usTypeNO = iActNum;
	}

	if (iPtzCount >= LEN_64 && !bSelfLink 
		&& LINKPTZ_TYPE_NOLINK != tLinkPtzParam.usType)
	{	
		//报警联动PTZ最多联动64个通道
		return;
	}

	int iRet = NetClient_SetAlarmConfig(m_iLogonID, m_iChannelNo, m_iAlarmTypeCMD, CMD_SET_ALARMLINK_V3, &tAlarmLinkPara);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetAlarmConfig(%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iAlarmTypeCMD);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetAlarmConfig(%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iAlarmTypeCMD);
	}
}

void CLS_DNVRAlmLinkPage::UI_ShowLinkCP(int _iCmdShow)
{
	GetDlgItem(IDC_STATIC_LINKSET)->ShowWindow(_iCmdShow);
	GetDlgItem(IDC_STATIC_CHANNELENABLE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CHANNELENABLE)->ShowWindow(_iCmdShow);
	m_pclsChanCheck->ShowWindow(_iCmdShow?SW_SHOW:SW_HIDE);
}

void CLS_DNVRAlmLinkPage::UI_ShowLinkAV(int _iCmdShow)
{
	GetDlgItem(IDC_STATIC_LINKSETAVIDEO)->ShowWindow(_iCmdShow);
	GetDlgItem(IDC_CHECK_DISPLAYENABLE)->ShowWindow(_iCmdShow);
	GetDlgItem(IDC_CHECK_SOUNDENABLE)->ShowWindow(_iCmdShow);
	GetDlgItem(IDC_BUTTON_AVIDEO)->ShowWindow(_iCmdShow);
}

int CLS_DNVRAlmLinkPage::ActionInit()
{
	int iMaxPtzNo = 0;
	switch(m_cboLinkPTZType.GetCurSel())
	{
	case PTZ_TYPE_PRESET:
		{
			//预置位IDS_CONFIG_DNVR_PRESET
			iMaxPtzNo = 255;
			break;
		}
	case PTZ_TYPE_TRACK:
		{
			//轨迹IDS_CONFIG_DNVR_TRACK
			iMaxPtzNo = 1;
			break;
		}
	case PTZ_TYPE_CRUISEPATH:
		{
			//路径IDS_CONFIG_DNVR_CRUISEPATH
			iMaxPtzNo = 8;
			break;
		}
	default :
		break;
	}
	return iMaxPtzNo; 
}

void CLS_DNVRAlmLinkPage::UI_ShowLinkPTZ(int _iCmdShow)
{
	GetDlgItem(IDC_STATIC_LINK_SET_PTZ)->ShowWindow(_iCmdShow);
	GetDlgItem(IDC_STATIC_LINKCHANNELNO)->ShowWindow(_iCmdShow);
	GetDlgItem(IDC_STATIC_LINKPTZTYPE)->ShowWindow(_iCmdShow);
	GetDlgItem(IDC_STATIC_LINKACTNO)->ShowWindow(_iCmdShow);
	GetDlgItem(IDC_COMBO_LINKCHANNELNO)->ShowWindow(_iCmdShow);
	GetDlgItem(IDC_COMBO_LINKPTZTYPE)->ShowWindow(_iCmdShow);
	GetDlgItem(IDC_EDIT_LINKACTNO)->ShowWindow(_iCmdShow);
	GetDlgItem(IDC_BUTTON_LINK)->ShowWindow(_iCmdShow);
}

void CLS_DNVRAlmLinkPage::UI_ShowLinkType()
{
	UI_ShowLinkCP(SW_HIDE);
	UI_ShowLinkAV(SW_HIDE);
	UI_ShowLinkPTZ(SW_HIDE);
	UI_ShowLinkSinPic(SW_HIDE);
	UI_ShowLinkCommonEnable(SW_HIDE);
	switch(m_cboLinkType.GetCurSel())
	{
	case LINK_RECORD:
	case LINK_SNAP:
	case LINK_OUTPORT:
	case LINK_HTTP:	
		UI_ShowLinkCP(SW_SHOW);
		break;
	case LINK_AUDIO_VIDEO:
		UI_ShowLinkAV(SW_SHOW);
		break;
	case LINK_PTZ:
		UI_ShowLinkPTZ(SW_SHOW);
		break;
	case LINK_SINGLEPIC:
		UI_ShowLinkSinPic(SW_SHOW);
		break;
	case LINK_MAIL:	
	case LINK_LASER:	
		UI_ShowLinkCommonEnable(SW_SHOW);
		break;
	default: 
		break;

	}
}

void CLS_DNVRAlmLinkPage::OffsetWindow(int iID,int dx,int dy)
{
	RECT rcTemp = {0};
	GetDlgItem(iID)->GetWindowRect(&rcTemp);
	ScreenToClient(&rcTemp);
	OffsetRect(&rcTemp,dx,dy);
	GetDlgItem(iID)->MoveWindow(&rcTemp);
}

void CLS_DNVRAlmLinkPage::UI_ShowLinkSinPic( int _iCmdShow )
{
	GetDlgItem(IDC_STATIC_LINK_SET_PTZ2)->ShowWindow(_iCmdShow);
	GetDlgItem(IDC_STATIC_SINGLEPIC_CHANNEL)->ShowWindow(_iCmdShow);
	GetDlgItem(IDC_COMBO_SINGLEPIC_CHANNEL)->ShowWindow(_iCmdShow);
	GetDlgItem(IDC_BUTTON_SINGLEPIC_CHANNEL)->ShowWindow(_iCmdShow);
}

void CLS_DNVRAlmLinkPage::UI_ShowLinkCommonEnable(int _iCmdShow)
{
	GetDlgItem(IDC_GBO_ALARM_LINK_COMMON_ENABLE)->ShowWindow(_iCmdShow);
	GetDlgItem(IDC_CBO_ALARM_LINK_COMMON_ENABLE)->ShowWindow(_iCmdShow);
	GetDlgItem(IDC_BTN_ALARM_LINK_COMMON_ENABLE_SET)->ShowWindow(_iCmdShow);
	int iTempIndex = 0;
	iTempIndex = m_cboCommonEnable.GetCurSel();
	iTempIndex = (iTempIndex < 0) ? 0 : iTempIndex; 
	m_cboCommonEnable.ResetContent();
	m_cboCommonEnable.SetItemData(m_cboCommonEnable.AddString(GetTextEx(IDS_CONFIG_FTP_SNAPSHOT_DISABLE)), 0);
	m_cboCommonEnable.SetItemData(m_cboCommonEnable.AddString(GetTextEx(IDS_CONFIG_FTP_SNAPSHOT_ENABLE)), 1);
	iTempIndex = (iTempIndex < m_cboCommonEnable.GetCount()) ? iTempIndex : 0;
	m_cboCommonEnable.SetCurSel(iTempIndex);
}
//add by zhy 2013.04.03
BOOL CLS_DNVRAlmLinkPage::UI_UpdateLinkSinPic()
{
	if (m_iLogonID < 0)
		return FALSE;

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

	return TRUE;
}

void CLS_DNVRAlmLinkPage::OnBnClickedButtonSinglepicChannel()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TAlarmLinkParam_V3 tAlarmLinkPara = {0};
	tAlarmLinkPara.tAlarmParam.iSize = sizeof(TAlarmParam_V3);
	tAlarmLinkPara.tLinkParam.iSize = sizeof(TLinkParam_V3);

	tAlarmLinkPara.tLinkParam.iLinkType = ALARMLINKTYPE_LINKSINGLEPIC;
	
	int iChanNo = m_cboSinglePic.GetCurSel()-1;
	tAlarmLinkPara.tLinkParam.uLinkParam.iCommonSet[iChanNo/LEN_32] |= 1<<iChanNo%LEN_32;

	int iRet = NetClient_SetAlarmConfig(m_iLogonID, m_iChannelNo, m_iAlarmTypeCMD, CMD_SET_ALARMLINK_V3, &tAlarmLinkPara);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetAlarmConfig(%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iAlarmTypeCMD);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetAlarmConfig(%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iAlarmTypeCMD);
	}
}
//add by zhy end

void CLS_DNVRAlmLinkPage::UI_UpdateChanCheck()
{
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
	GetDlgItem(IDC_STATIC_LINKSET)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	rc.top += 15;
	rc.bottom -= 10;
	rc.left += 5;
	rc.right -= 5;
	m_pclsChanCheck->MoveWindow(&rc);
	m_pclsChanCheck->ShowWindow(SW_HIDE);
}

