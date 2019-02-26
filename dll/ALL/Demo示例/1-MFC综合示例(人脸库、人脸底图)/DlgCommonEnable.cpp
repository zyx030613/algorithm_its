// DlgCommonEnable.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "DlgCommonEnable.h"


// CLS_DlgCommonEnable 对话框

IMPLEMENT_DYNAMIC(CLS_DlgCommonEnable, CDialog)

CLS_DlgCommonEnable::CLS_DlgCommonEnable(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DlgCommonEnable::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = -1;
}

CLS_DlgCommonEnable::~CLS_DlgCommonEnable()
{
}

void CLS_DlgCommonEnable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_CFG_COMENABLE_ID, m_CboCommonEnableType);
}


BEGIN_MESSAGE_MAP(CLS_DlgCommonEnable, CLS_BasePage)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_CBO_CFG_COMENABLE_ID, &CLS_DlgCommonEnable::OnCbnSelchangeCboCfgComenableId)
	ON_BN_CLICKED(IDC_BTN_CFG_COMENABLE_SET, &CLS_DlgCommonEnable::OnBnClickedBtnCfgComenableSet)
END_MESSAGE_MAP()

BOOL CLS_DlgCommonEnable::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	return TRUE;
}

void CLS_DlgCommonEnable::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		InitDialogItemText();
		GetCommonEnable();
	}
}

void CLS_DlgCommonEnable::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (m_iLogonID == _iLogonID && m_iChannelNo == _iChannelNo && m_iStreamNo == _iStreamNo)
	{
		return;
	}

	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;
	GetCommonEnable();
}

void CLS_DlgCommonEnable::OnLanguageChanged( int _iLanguage )
{
	InitDialogItemText();
}

void CLS_DlgCommonEnable::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
{
	if (_iLogonID != m_iLogonID)
	{
		return;
	}

	//TODO
}

void CLS_DlgCommonEnable::InitDialogItemText()
{
	UpDateCommonEnableList();
}

void CLS_DlgCommonEnable::GetCommonEnable()
{
	SetDlgItemText(IDC_EDT_CFG_COMENABLE_NUM, "");

	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgCommonEnable::GetCommonEnable] Error  LogonID!");
		return;
	}

	DWORD_PTR iCommonEnableType = m_CboCommonEnableType.GetItemData(m_CboCommonEnableType.GetCurSel());
	int iEnableValue = -1;
	int iRet = -1;
	switch (iCommonEnableType)
	{
		case CI_NET_SERVICE_SNMP:
		case CI_STORAGE_DISK_GROUP:
		case CI_STORAGE_DISK_QUOTA:
		case CI_VEHICLE_GPS_CALIBRATION:
		case CI_VEHICLE_ALARM_THRESHOLD:
		case CI_VEHICLE_SHUTDOWN_THRESHOLD:
		case CI_NET_CONNECT_INFO:
		case CI_COMMON_ID_WORKDEV_BACKUP:
		case CI_COMMON_ID_RAID:
		case CI_COMMON_ID_BURN_AUDIO_FILE:
		case CI_COMMON_ID_BACK_AUDIO_FILE:
		case CI_COMMON_ID_BURNFILE_FORMAT:
		case CI_COMMON_ID_VO_ENABLE:
		case CI_COMMON_ID_RTSP_CHECK:
		case CI_COMMON_ID_FAN_CONTROL:
		case CI_COMMON_ID_FAN_TEMP_CONTROL:
		case CI_COMMON_ID_FORBIDCHN:
		case CI_COMMON_ID_TELNET:
		case CI_COMMON_ID_DISK:
		case CI_COMMON_ID_VCACARCHECK:
		case CI_COMMON_ID_WHTITELIGHT_ENABLE:
		case CI_COMMON_ID_NVR_LOCAL_VCA:
		case CI_COMMON_ID_TRENDS_ROI:
		case CI_HASH_CHECK:
		case CI_COMMON_ID_ITS_BUSINESS:
		case CI_COMMON_ID_ITS_ILLEGAL_PARK:
		case CI_NET_PUBLIC_NETWORK:
		case CI_COMMON_ID_PERIPHERAL_MANAGE:
		case CI_COMMON_ID_ERECT_MODE:
		case CI_COMMON_ID_OBLIGATE_MODE:
			{
				iRet = NetClient_GetCommonEnable(m_iLogonID, iCommonEnableType, INVALID_FLAG, &iEnableValue);
			}
			break;
		case CI_NET_SERVICE_SMTP:
		case CI_ALARM_MOTION_DETECT:
		case CI_ALARM_VIDEO_COVER:
		case CI_COMMON_ID_EIS:
		case CI_COMMON_ID_ANR:
		case CI_COMMON_ID_SVC:
		case CI_COMMON_ID_DENOISE:
		case CI_COMMON_ID_MAKE_AUDIO_FILE:
		case CI_COMMON_ID_ITS_SIGNAL_LIGHT:
		case CI_COMMON_ID_OSD_DOT_MATRIX:
		case CI_COMMON_ID_OSD_VECTOR:
		case CI_COMMON_ID_EVENT:
		case CI_COMMON_ID_VIDEO_REVERSE:
			{
				iRet = NetClient_GetCommonEnable(m_iLogonID, iCommonEnableType, m_iChannelNo, &iEnableValue);
			}
			break;
		default:
			break;
	}

	if (iRet < 0 || iEnableValue < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgCommonEnable::GetCommonEnable] Get EnableValue Failed  LogonID %d EnableType %d!", m_iLogonID, iCommonEnableType);
		return;
	}

	SetDlgItemInt(IDC_EDT_CFG_COMENABLE_NUM, iEnableValue);
}


void CLS_DlgCommonEnable::SetCommonEnable()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgCommonEnable::SetCommonEnable] Error  LogonID!");
		return;
	}

	DWORD_PTR iCommonEnableType = m_CboCommonEnableType.GetItemData(m_CboCommonEnableType.GetCurSel());
	int iEnableValue = -1;
	DWORD_PTR iRet = -1;
	iEnableValue = GetDlgItemInt(IDC_EDT_CFG_COMENABLE_NUM);
	
	int iTempChannelNo = -1;
	switch (iCommonEnableType)
	{
	case CI_NET_SERVICE_SNMP:
	case CI_STORAGE_DISK_GROUP:
	case CI_STORAGE_DISK_QUOTA:
	case CI_VEHICLE_GPS_CALIBRATION:
	case CI_VEHICLE_ALARM_THRESHOLD:
	case CI_VEHICLE_SHUTDOWN_THRESHOLD:
	case CI_NET_CONNECT_INFO:
	case CI_COMMON_ID_WORKDEV_BACKUP:
	case CI_COMMON_ID_RAID:
	case CI_COMMON_ID_BURN_AUDIO_FILE:
	case CI_COMMON_ID_BACK_AUDIO_FILE:
	case CI_COMMON_ID_BURNFILE_FORMAT:
	case CI_COMMON_ID_VO_ENABLE:
	case CI_COMMON_ID_RTSP_CHECK:
	case CI_COMMON_ID_FAN_CONTROL:
	case CI_COMMON_ID_FAN_TEMP_CONTROL:
	case CI_COMMON_ID_FORBIDCHN:
	case CI_COMMON_ID_TELNET:
	case CI_COMMON_ID_DISK:
	case CI_COMMON_ID_VCACARCHECK:
	case CI_COMMON_ID_WHTITELIGHT_ENABLE:
	case CI_COMMON_ID_NVR_LOCAL_VCA:
	case CI_COMMON_ID_TRENDS_ROI:
	case CI_HASH_CHECK:
	case CI_COMMON_ID_ITS_BUSINESS:
	case CI_COMMON_ID_ITS_ILLEGAL_PARK:
	case CI_NET_PUBLIC_NETWORK:
	case CI_COMMON_ID_PERIPHERAL_MANAGE:
	case CI_COMMON_ID_ERECT_MODE:
	case CI_COMMON_ID_OBLIGATE_MODE:
		{
			iTempChannelNo = INVALID_FLAG;
		}
		break;
	case CI_NET_SERVICE_SMTP:
	case CI_ALARM_MOTION_DETECT:
	case CI_ALARM_VIDEO_COVER:
	case CI_COMMON_ID_EIS:
	case CI_COMMON_ID_ANR:
	case CI_COMMON_ID_SVC:
	case CI_COMMON_ID_DENOISE:
	case CI_COMMON_ID_MAKE_AUDIO_FILE:
	case CI_COMMON_ID_ITS_SIGNAL_LIGHT:
	case CI_COMMON_ID_OSD_DOT_MATRIX:
	case CI_COMMON_ID_OSD_VECTOR:
	case CI_COMMON_ID_EVENT:
	case CI_COMMON_ID_VIDEO_REVERSE:
		{
			iTempChannelNo = m_iChannelNo;
		}
		break;
	default:
		{
			iTempChannelNo = m_iChannelNo;
		}
		break;
	}

	iRet = NetClient_SetCommonEnable(m_iLogonID, iCommonEnableType, iTempChannelNo, iEnableValue);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgCommonEnable::SetCommonEnable] Set Failed ! LogonID %d EnableType %d EnableValue %d", m_iLogonID, iCommonEnableType, iEnableValue);
		return;
	}
}

void CLS_DlgCommonEnable::UpDateCommonEnableList()
{
	SetDlgItemTextEx(IDC_GPO_CFG_COMENABLE, IDS_CFG_COMMONENABLE);
	SetDlgItemTextEx(IDC_BTN_CFG_COMENABLE_SET, IDS_SET);


	int iTempSel = m_CboCommonEnableType.GetCurSel();
	iTempSel = iTempSel < 0 ? 0 : iTempSel;
	m_CboCommonEnableType.ResetContent();
// 	通用使能-工作机热备
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CFG_COMMONENABLE) + "-" + GetTextEx(IDS_CE_WORKDEV_BACKUP))		,	CI_COMMON_ID_WORKDEV_BACKUP			);
// 	通用使能-禁用通道数
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CFG_COMMONENABLE) + "-" + GetTextEx(IDS_CE_FORBIDCHN))			,	CI_COMMON_ID_FORBIDCHN				);
// 	通用使能-telnet使能
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CFG_COMMONENABLE) + "-" + GetTextEx(IDS_CE_TELNET))				,	CI_COMMON_ID_TELNET					);
// 	通用使能-光盘弹盘和封盘状态
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CFG_COMMONENABLE) + "-" + GetTextEx(IDS_CE_DISK))				,	CI_COMMON_ID_DISK					);
// 	通用使能-GPS校时
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CFG_COMMONENABLE) + "-" + GetTextEx(IDS_CE_GPS))				,	CI_VEHICLE_GPS_CALIBRATION			);
// 	"通用使能-过车检测
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CFG_COMMONENABLE) + "-" + GetTextEx(IDS_CE_CAR))				,	CI_COMMON_ID_VCACARCHECK			);
// 	通用使能-ANR使能
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CFG_COMMONENABLE) + "-" + "ANR")								,	CI_COMMON_ID_ANR					);
// 	通用使能-事件模板
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CFG_COMMONENABLE) + "-" + GetTextEx(IDS_CE_EVENT))				,	CI_COMMON_ID_EVENT					);
// 	通用使能-设备低压报警阈值
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CFG_COMMONENABLE) + "-" + GetTextEx(IDS_CE_VEHICLE_ALARM_THRESHOLD))		,	CI_VEHICLE_ALARM_THRESHOLD			);
// 	通用使能-设备低压关机阈值
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CFG_COMMONENABLE) + "-" + GetTextEx(IDS_CE_VEHICLE_SHUTDOWM_THRESHOLD))		,	CI_VEHICLE_SHUTDOWN_THRESHOLD		);
//	通用使能-外设管理使能
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CFG_COMMONENABLE) + "-" + GetTextEx(IDS_PERIPHERAL_MANAGE))		,	CI_COMMON_ID_PERIPHERAL_MANAGE			);

// 	网络服务-SNMP
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CE_NET) + "-" + "SNMP")										,	CI_NET_SERVICE_SNMP					);
// 	网络服务-RTSP校验使能
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CE_NET) + "-" + "RTSP")										,	CI_COMMON_ID_RTSP_CHECK				);
// 	网络服务-SMTP
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CE_NET) + "-" + "STMP")										,	CI_NET_SERVICE_SMTP					);
// 	网络连接-公网连接状态
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CE_NET) + "-" + GetTextEx(IDS_CE_PUB_NET))					,	CI_NET_PUBLIC_NETWORK				);
// 	网络连接-MTU设置
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CE_NET) + "-" + "MTU")										,	CI_NET_CONNECT_INFO					);

// 	存储-音频文件刻录使能
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CONFIG_STORAGE) + "-" + GetTextEx(IDS_CE_BURN_AUDIO_FILE))	,	CI_COMMON_ID_BURN_AUDIO_FILE		);
// 	存储-音频文件备份使能
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CONFIG_STORAGE) + "-" + GetTextEx(IDS_CE_BACK_AUDIO_FILE))	,	CI_COMMON_ID_BACK_AUDIO_FILE		);
// 	存储-实时刻录录像文件格式
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CONFIG_STORAGE) + "-" + GetTextEx(IDS_CE_BURNFILE_FORMAT))	,	CI_COMMON_ID_BURNFILE_FORMAT		);
// 	存储-哈希校验
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CONFIG_STORAGE) + "-" + GetTextEx(IDS_CE_HASH_CHECK))		,	CI_HASH_CHECK						);
// 	存储-音频文件生成
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CONFIG_STORAGE) + "-" + GetTextEx(IDS_CE_MAKE_AUDIO_FILE))	,	CI_COMMON_ID_MAKE_AUDIO_FILE		);

// 	磁盘管理-盘组配合策略
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CE_DISKMANAGE) + "-" + GetTextEx(IDS_CE_STORAGE_DISK_GROUP)),	CI_STORAGE_DISK_GROUP				);
// 	磁盘管理-配额模式
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CE_DISKMANAGE) + "-" + GetTextEx(IDS_CE_STORAGE_DISK_QUOTA)),	CI_STORAGE_DISK_QUOTA				);
// 	磁盘管理-RAID
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CE_DISKMANAGE) + "-" + "RAID")								,	CI_COMMON_ID_RAID					);

// 	交通相关-交通业务
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CONFIG_ITS) + "-" + GetTextEx(IDS_CE_ITS_BUSINESS))			,	CI_COMMON_ID_ITS_BUSINESS			);
// 	交通相关-信号灯同步
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CONFIG_ITS) + "-" + GetTextEx(IDS_CE_ITS_SIGNAL_LIGHT))		,	CI_COMMON_ID_ITS_SIGNAL_LIGHT		);
// 	交通相关-违章停车系统抓拍类型
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CONFIG_ITS) + "-" + GetTextEx(IDS_CE_ILLEGAL_PARK))			,	CI_COMMON_ID_ITS_ILLEGAL_PARK		);

// 	系统管理-风扇远程控制
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CFG_RIGHT_SYSTEM_SET) + "-" + GetTextEx(IDS_CE_FAN_CONTROL)),	CI_COMMON_ID_FAN_CONTROL			);
// 	系统管理-风扇温控
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CFG_RIGHT_SYSTEM_SET) + "-" + GetTextEx(IDS_CE_TEMP_CONTROL))		,	CI_COMMON_ID_FAN_TEMP_CONTROL		);
// 	系统管理-white light
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CFG_RIGHT_SYSTEM_SET) + "-" + GetTextEx(IDS_CE_WHTITELIGHT_ENABLE))	,	CI_COMMON_ID_WHTITELIGHT_ENABLE		);

// 	音视频-trends ROI
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CONFIG_AUDIO_VIDEO) + "-" + "ROI")							,	CI_COMMON_ID_TRENDS_ROI				);
// 	音视频-电子防抖
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CONFIG_AUDIO_VIDEO) + "-" + GetTextEx(IDS_CE_EIS))			,	CI_COMMON_ID_EIS					);
// 	音视频-Video Output Control
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CONFIG_AUDIO_VIDEO) + "-" + GetTextEx(IDS_CE_VO))			,	CI_COMMON_ID_VO_ENABLE				);
// 	音视频-svc
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CONFIG_AUDIO_VIDEO) + "-" + "SVC")							,	CI_COMMON_ID_SVC					);
// 	音视频-audio denoise
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CONFIG_AUDIO_VIDEO) + "-" + GetTextEx(IDS_CE_DENOISE))		,	CI_COMMON_ID_DENOISE				);
// 	音视频-视频翻转
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CONFIG_AUDIO_VIDEO) + "-" + GetTextEx(IDS_CE_VIDEO_REVERSE)),	CI_COMMON_ID_VIDEO_REVERSE			);

// 	报警-MD报警使能
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_ALARM_TYPE_ALARM) + "-MD" + GetTextEx(IDS_ALARM_TYPE_ALARM)),	CI_ALARM_MOTION_DETECT				);
// 	报警-OD报警使能
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_ALARM_TYPE_ALARM) + "-OD" + GetTextEx(IDS_ALARM_TYPE_ALARM)),	CI_ALARM_VIDEO_COVER				);

// 	字符叠加-点阵字库
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_BURN_H8_OSD) + "-" + GetTextEx(IDS_OSD_FONT_DB_TYPE_LATTICE)),	CI_COMMON_ID_OSD_DOT_MATRIX			);
//  字符叠加-矢量字库
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_BURN_H8_OSD) + "-" + GetTextEx(IDS_OSD_FONT_DB_TYPE_VECTOR)),	CI_COMMON_ID_OSD_VECTOR				);

// 	智能分析-NVR Local VCAsss
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CONFIGPAGE_VCA) + "-" + GetTextEx(IDS_CE_NVR_VCA))			,	CI_COMMON_ID_NVR_LOCAL_VCA			);
	
//	鱼眼摄像机-安装方式
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CFG_FEC) + "-" + GetTextEx(IDS_ERECT_MODE))					,	CI_COMMON_ID_ERECT_MODE				);
//	鱼眼摄像机-预留模式
	m_CboCommonEnableType.SetItemData(m_CboCommonEnableType.AddString(GetTextEx(IDS_CFG_FEC) + "-" + GetTextEx(IDS_OBLIGATE_MODE))				,	CI_COMMON_ID_OBLIGATE_MODE			);

	if (iTempSel < m_CboCommonEnableType.GetCount())
	{
		m_CboCommonEnableType.SetCurSel(iTempSel);
	}
	else
	{
		m_CboCommonEnableType.SetCurSel(0);
	}
}


void CLS_DlgCommonEnable::OnCbnSelchangeCboCfgComenableId()
{
	GetCommonEnable();
}


void CLS_DlgCommonEnable::OnBnClickedBtnCfgComenableSet()
{
	SetCommonEnable();
}
