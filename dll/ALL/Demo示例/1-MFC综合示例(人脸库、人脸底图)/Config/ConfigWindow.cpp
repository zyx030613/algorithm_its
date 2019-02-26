// ConfigWindow.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigWindow.h"
#include "VideoParamPage.h"
#include "AudioParamPage.h"
#include "VideoEncryptPage.h"
#include "AlarmPage.h"
#include "OSDPage.h"
#include "VideoPage.h"
#include "SOPage.h"
#include "DZPage.h"
#include "LanguagePage.h"
#include "IPPage.h"
#include "IPAdvPage.h"
#include "UserPage.h"
#include "SipPage.h"
#include "CmosPage.h"
#include "DDNSPage.h"
#include "UDPPage.h"
#include "NTPPage.h"
#include "PUPage.h"
#include "ITSRoadwayPage.h"

#include "ITSOSDPage.h"
#include "ITSOtherPage.h"
#include "LANIPV4Page.h"
#include "LANIPV6Page.h"
#include "LANWorkModePage.h"
#include "FTPPage.h"
#include "BurnPage.h"
#include "8D1Page.h"
#include "StoragePage.h"
#include "StorageStrategyPage.h"
#include "StorageSmartPage.h"

#include "DeviceDiskInfo.h"
#include "HDPage.h"
#include "DNVRAlmSchPage.h"
#include "DNVRAlmLinkPage.h"
#include "DNVRDigitPage.h"
#include "DNVRVideoCombinePage.h"
#include "DNVRExceptionPage.h"
#include "3GAdvPage.h"
#include "3GDVRPage.h"
#include "3GNormalPage.h"
#include "NVSLogPage.h"
#include "DVRLogPage.h"
#include "VideoParamSchedulePage.h"
#include "PTZPage.h"
#include "WifiPage.h"
#include "AdvPage.h"
#include "ATMPage.h"
#include "VCATargetPage.h"
#include "VCAAdvanceParam.h"
#include "VCASmartSearch.h"
#include "VCAEventPage.h"
#include "AdvParam\VcaQueryFile.h"
#include "Vca\FaceLibManage.h"
#include "Vca\FacePicManage.h"
#include "ComPage.h"
#include "IOPORTPAGE.h"
#include "AdvVersionPage.h"
#include "AdvSystemInfoPage.h"
#include "AdvUpgrade.h"
#include "AdvChannelParamPage.h"
#include "VCAAlarmInfoPage.h"
#include "VCAAlarmSchedulePage.h"
#include "VCAAlarmLinkPage.h"
#include "AuthorityChannelPage.h"
#include "AuthorityLocalPage.h"
#include "AuthorityRemotePage.h"
#include "HolidayPlanPage.h"
#include "DomeInfrared.h"
#include "VehiclePage.h"
#include "VideoInterested.h"
#include "AppendOSDPage.h"
#include "DomeState.h"
#include "DomeSchedule.h"
#include "DomeMenu.h"
#include "DonghuanSet.h"
#include "LinkSet.h"
#include "SerialManagePage.h"
#include "OSDManagePage.h"
#include "PowerEnvParamPage.h"
#include "DefenceTemplatePage.h"
#include "DNVRCreateFree.h"
#include "ReportSet.h"
#include "VCAEvnetsAdvParam.h"
#include "VCAEvnetsSmartTrack.h"
#include "Events/VCAframDomeCurise.h"
#include "BurnH323Page.h"
#include "AdvLocalSet.h"
#include "../Common/Ini.h"
#include "BurnH8Page.h"
#include "DomeBasic1.h"
#include "DomeBasic2.h"
#include "DomeRun1.h"
#include "DomeRun2.h"
#include "DomeHDParam1.h"
#include "DomeHDParam2.h"
#include "DomeHDParam3.h"
#include "HDSchedule.h"

#include "ItsPictureCommon1.h"
#include "ItsPictureCommon2.h"
#include "ItsPictureCommon3.h"
#include "ItsSignalCheck.h"
#include "ItsSignalOther.h"
#include "ITSRoadWayAdvanced2.h"
#include "ItsRoadwayCommon2.h"
#include "ItsRoadwayCommon3.h"
#include "ItsRoadwayCommon4.h"
#include "ItsRecognitionParam.h"
#include "ItsSystemParam1.h"
#include "ItsSystemParam2.h"
#include "ItsSystemParam3.h"
#include "ItsCompoPic.h"
#include "ItsTrafficStatistics.h"

#include "ItsIllegalType.h"
#include "ItsStateQuery.h"
#include "ItsFocusAid.h"
#include "ItsRecognitionParam2.h"
#include "ITSRoadWayAdvanced1.h"
#include "LinkHttp.h"
#include "PortMapping.h"
#include "ITSRoadWayAdvanced3.h"
#include "ExtendedParam.h"
#include "ItsAdvanceConf2.h"
#include "AutoTestPage.h"
#include "IOData.h"
#include "CLS_DLG_FUNC_COLORTOGRAY.h"
#include "CLS_DLG_CFG_FUNC_VideoTranceCoding.h"
#include "CLS_DlgFuncSmarta.h"
#include "CLS_DlgFuncDdns.h"
#include "CLS_DlgFuncNetwork.h"
#include "CLS_DlgFuncDecoder.h"
#include "CLS_DlgFuncStatisPeopleNum.h"
#include "CLS_DlgFuncRoi.h"
#include "CLS_DlgFuncLaw.h"
#include "CLS_DlgFuncDome.h"
#include "DlgCommonEnable.h"
#include "ITSOSDPageEx.h"
#include "OSDBackGroundPage.h"
#include "ITSAlarmLink.h"
#include "ITSRoadwayCaptureCfg.h"
#include "ITSPlatformConfig.h"
#include "ITSDevManage.h"
#include "ITSLaneManage.h"
#include "ITSBayonetData.h"
#include "DNVRTextPlan.h"
#include "QosPage.h"
#include "BAWLicencePlate.h"
#include "StorageDiskManagePage.h"
#include "DNVRChannelInfo.h"
#include "FECHeatMap.h"
#include "CLS_UPnpPage.h"
#include "VideoEncodeSlicePage.h"
#include "StoragePathSet.h"
#include "StorageANR.h"
#include "DlgAlarmHumTem.h"
#include "RtmpPage.h"

//#define ALERT_TODO
#ifdef ALERT_TODO
#include "CLS_DlgUniqueAlertEnable.h"
#include "CLS_DlgUniqueAlertCustom.h"
#include "CLS_DlgUniqueAlertPlan.h"
#include "CLS_DlgUniqueAlertAlarmLink.h"
#endif

// CLS_ConfigWindow dialog
#define WAIT_PAUSE_TIME 300
IMPLEMENT_DYNAMIC(CLS_ConfigWindow, CDialog)

CLS_ConfigWindow::CLS_ConfigWindow(CWnd* pParent /*=NULL*/)
	: CLS_BaseWindow(CLS_ConfigWindow::IDD, pParent)
{
	for (int i = 0; i < CONFIG_MAX; ++i)
	{
		m_pPage[i] = NULL;
	}
	m_pCurrent = NULL;
	m_pVideo = NULL;
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNo = 0;
	m_bLocked = FALSE;
	m_iCurrentPage = -1;
}

CLS_ConfigWindow::~CLS_ConfigWindow()
{
	for (int i = 0; i < CONFIG_MAX; ++i)
	{
		if (NULL == m_pPage[i])
		{
			continue;
		}

		if (IsWindow(m_pPage[i]->GetSafeHwnd()))
		{
			m_pPage[i]->DestroyWindow();
		}

		delete m_pPage[i];
		m_pPage[i] = NULL;
	}
}

void CLS_ConfigWindow::DoDataExchange(CDataExchange* pDX)
{
	CLS_BaseWindow::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_CONFIG, m_tvConfig);
}

BEGIN_MESSAGE_MAP(CLS_ConfigWindow, CLS_BaseWindow)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_CONFIG, &CLS_ConfigWindow::OnTvnSelchangedTreeConfig)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_CONFIG, &CLS_ConfigWindow::OnNMDblclkTreeConfig)
END_MESSAGE_MAP()


// CLS_ConfigWindow message handlers

BOOL CLS_ConfigWindow::OnInitDialog()
{
	CLS_BaseWindow::OnInitDialog();

	UI_UpdateDialog();

	return TRUE;  
}

int CLS_ConfigWindow::ShowBasePage( int _iIndex )
{
	if (_iIndex < CONFIG_MIN || _iIndex >= CONFIG_MAX)
	{
		return -1;
	}
	if(_iIndex == CONFIG_VCA_EVENTS && NULL != m_pPage[_iIndex])
	{
		if (IsWindow(m_pPage[_iIndex]->GetSafeHwnd()))
		{
			m_pPage[_iIndex]->DestroyWindow();
		}

		delete m_pPage[_iIndex];
		m_pPage[_iIndex] = NULL;
	}
	m_iCurrentPage = _iIndex;
	if (NULL == m_pPage[_iIndex])
	{
		switch(_iIndex)
		{
		case CONFIG_VIDEO_PARAM:
			{
				m_pPage[_iIndex] = new CLS_VideoParamPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VIDEO_PARAM,this);
			}
			break;
		case CONFIG_VIDEO_PARAM_SCHEDULE:
			{
				m_pPage[_iIndex] = new CLS_VideoParamSchedulePage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VIDEO_PARAM_SCHEDULE,this);
			}
			break;
		case CONFIG_AUDIO_PARAM:
			{
				m_pPage[_iIndex] = new CLS_AudioParamPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_AUDIO_PARAM,this);
			}
			break;
		case CONFIG_VIDEO_ENCRYPT:
			{
				m_pPage[_iIndex] = new CLS_VideoEncryptPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VIDEO_ENCRYPT,this);
			}
			break;
		case CONFIG_VIDEO_ENCODE_SLICE:
			{
				m_pPage[_iIndex] = new CLS_VideoEncodeSlicePage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VIDEO_ENCODE_SLICE,this);
			}
			break;
		case CONFIG_ALARM:
			{
				m_pPage[_iIndex] = new CLS_AlarmPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ALARM,this);
			}
			break;
		case CONFIG_LANGUAGE:
			{
				m_pPage[_iIndex] = new CLS_LanguagePage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_LANGUAGE,this);
			}
			break;
		case CONFIG_OSD:
			{
				m_pPage[_iIndex] = new CLS_OSDPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_OSD,this);
			}
			break;
		case CONFIG_IP:
			{
				m_pPage[_iIndex] = new CLS_IPPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_IP,this);
			}
			break;
		case CONFIG_IPADV:
			{
				m_pPage[_iIndex] = new CLS_IPAdvPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_IPADV, this);
			}
			break;
		case CONFIG_USER:
			{
				m_pPage[_iIndex] = new CLS_UserPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_USER,this);
			}
			break;
		case CONFIG_AUTHORITY_LOCAL:
			{
				m_pPage[_iIndex] = new CLS_AuthorityLocalPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_AUTHORITY_LOCAL,this);
			}
			break;
		case CONFIG_AUTHORITY_REMOTE:
			{
				m_pPage[_iIndex] = new CLS_AuthorityRemotePage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_AUTHORITY_REMOTE,this);
			}
			break;
		case CONFIG_AUTHORITY_CHANNEL:
			{
				m_pPage[_iIndex] = new CLS_AuthorityChannelPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_AUTHORITY_CHANNEL,this);
			}
			break;
		case CONFIG_SO:
			{
				m_pPage[_iIndex] = new CLS_SOPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_SO,this);
			}
			break;
		case CONFIG_DZ:
			{
				m_pPage[_iIndex] = new CLS_DZPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DZ,this);
			}
			break;
		case CONFIG_SIP:
			{
				m_pPage[_iIndex] = new CLS_SipPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_SIP,this);
			}
			break;
		case CONFIG_CMOS:
			{
				m_pPage[_iIndex] = new CLS_CmosPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_CMOS,this);
			}
			break;
		case CONFIG_DDNS:
			{
				m_pPage[_iIndex] = new CLS_DDNSPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DDNS,this);
			}
			break;
		case CONFIG_UDP:
			{
				m_pPage[_iIndex] = new CLS_UDPPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_UDP,this);
			}
			break;
		case CONFIG_NTP:
			{
				m_pPage[_iIndex] = new CLS_NTPPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_NTP,this);
			}
			break;
		case CONFIG_OPTION_PU:
			{
				m_pPage[_iIndex] = new CLS_PUPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_OPTION_PU,this);
			}
			break;
		case CONFIG_ITS_ROADWAY_COMMON1:
			{
				m_pPage[_iIndex] = new CLS_ITSRoadwayPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_ROADWAY_COMMON1,this);
			}
			break;
		case CONFIG_ITS_PICTURE_COMMON1:
			{
				m_pPage[_iIndex] = new Cls_ItsPictureCommon1(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_PICTURE_COMMON1,this);
			}
			break;
		case CONFIG_ITS_OSD:
			{
				m_pPage[_iIndex] = new CLS_ITSOSDPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ITS_OSD,this);
			}
			break;
		case CONFIG_ITS_OSD_EX:
			{
				m_pPage[_iIndex] = new CLS_ITSOSDPageEx(this);
 				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ITS_OSD_EX,this);
			}
			break;
		case CONFIG_ITS_ALARM_LINK:
			{
				m_pPage[_iIndex] = new CLS_ITSAlarmLinkPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_ALARM_LINK,this);
			}
			break;
		case CONFIG_ITS_ROADWAY_ADVANCED2:
			{
				m_pPage[_iIndex] = new CLS_ITSRoadWayAdvanced2(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_ROADWAY_ADVANCED2,this);
			}
			break;
		case CONFIG_ITS_OTHER:
			{
				m_pPage[_iIndex] = new CLS_ITSOtherPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ITS_OTHER,this);
			}
			break;
		case CONFIG_LAN_IPV4:
			{
				m_pPage[_iIndex] = new CLS_LANIPV4Page(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_LAN_IPV4,this);
			}
			break;
		case CONFIG_LAN_IPV6:
			{
				m_pPage[_iIndex] = new CLS_LANIPV6Page(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_LAN_IPV6,this);
			}
			break;	
		case CONFIG_LAN_WOKEMODE:
			{
				m_pPage[_iIndex] = new CLS_LANWorkModePage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_LAN_WORKMODE,this);
			}
			break;	
		case CONFIG_FTP:
			{
				m_pPage[_iIndex] = new CLS_FTPPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_FTP,this);
			}
			break;	
		case CONFIG_BURN:
			{
				m_pPage[_iIndex] = new CLS_BurnPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_BURN,this);
			}
			break;
		case CONFIG_BURN_H323:
			{
				m_pPage[_iIndex] = new CLS_BurnH323Page(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_BURN_H323,this);
			}
			break;
		case CONFIG_BURN_H8:
			{
				m_pPage[_iIndex] = new CLS_BurnH8Page(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_BURN_H8,this);
			}
			break;
		case CONFIG_8D1:
			{
				m_pPage[_iIndex] = new CLS_8D1Page(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_8D1,this);
			}
			break;
		case CONFIG_STORAGE:
			{
				m_pPage[_iIndex] = new CStoragePage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_STORAGE,this);
			}
			break;
		case CONFIG_STORAGE_SET:
			{
				m_pPage[_iIndex] = new CLS_StoragePathSetPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_STORAGE_SET,this);
			}
			break;
		case CONFIG_STORAGE_DISKINFO:
			{
				m_pPage[_iIndex] = new CDeviceDiskInfo(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_STORAGE_DISKINFO,this);
			}
			break;
		case CONFIG_HOLIDAY_PLAN:
			{
				m_pPage[_iIndex] = new CLS_HolidayPlanPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_STORAGE_HOLIDAY_PLAN,this);
			}
			break;
		case CONFIG_STORAGE_STRATEGY:
			{
				m_pPage[_iIndex] = new CLS_StorageStrategyPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_STORAGE_STRATEGY,this);
			}
			break;
		case CONFIG_STORAGE_SMART:
			{
				m_pPage[_iIndex] = new CLS_StorageSmartPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_STORAGE_SMART,this);
			}
			break;
		case CONFIG_STORAGE_DISKMANAGE:
			{
				m_pPage[_iIndex] = new CLS_StorageDiskManagePage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_STORAGE_DISKMANAGE,this);
			}
			break;
		case CONFIG_STORAGE_ANR:
			{
				m_pPage[_iIndex] = new CLS_StorageANR(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_STORAGE_ANR,this);
			}
			break;
		case CONFIG_ITS_SIGNAL_CHECK:
			{
				m_pPage[_iIndex] = new CLS_ItsSignalCheck(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_SIGNAL_CHECK,this);
			}
			break;
		case CONFIG_ITS_ROADWAY_COMMON3:
			{
				m_pPage[_iIndex] = new CLS_ItsRoadwayCommon3(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_ROADWAY_COMMON3,this);
			}
			break;
		case CONFIG_ITS_PICTURE_COMMON3:
			{
				m_pPage[_iIndex] = new CLS_ItsPictureCommon3(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_PICTURE_COMMON3,this);
			}
			break;
		case CONFIG_ITS_RECOPARAM:
			{
				m_pPage[_iIndex] = new CLS_ItsRecognitionParam(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_RECOPARAM,this);
			}
			break;
		case CONFIG_ITS_RECOPARAM2:
			{
				m_pPage[_iIndex] = new CLS_ItsRecognitionParam2(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_RECOPARAM_2,this);
			}
			break;
		case CONFIG_ITS_SYSTEMPARAM1:
			{
				m_pPage[_iIndex] = new CLS_ItsSystemParam1(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_SYSTEMPARAM1,this);
			}
			break;
		case CONFIG_ITS_SYSTEMPARAM2:
			{
				m_pPage[_iIndex] = new CLS_ItsSystemParam2(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_SYSTEMPARAM2,this);
			}
			break;
		case CONFIG_ITS_SYSTEMPARAM3:
			{
				m_pPage[_iIndex] = new CLS_ItsSystemParam3(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_SYSTEMPARAM3,this);
			}
			break;
		case CONFIG_HD:
			{
				m_pPage[_iIndex] = new CLS_HDPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_HD,this);
			}
			break;
		case CONFIG_ADV:
			{
				m_pPage[_iIndex] = new CLS_AdvPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ADV,this);
			}
			break;
		case CONFIG_ATM:
			{
				m_pPage[_iIndex] = new CLS_ATMPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ATM,this);
			}
			break;
		case CONFIG_DNVR_ALMSCH:
			{
				m_pPage[_iIndex] = new CLS_DNVRAlmSchPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DNVR_ALMSCH,this);
			}
			break;
		case CONFIG_DNVR_ALMLINK:
			{
				m_pPage[_iIndex] = new CLS_DNVRAlmLinkPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DNVR_ALMLINK,this);
			}
			break;
		case CONFIG_ALARM_HUM_TEM:
			{
				m_pPage[_iIndex] = new CLS_DlgAlarmHumTem(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ALARM_HUM_TEM,this);
			}
			break;
		case CONFIG_DNVR_DIGIT:
			{
				m_pPage[_iIndex] = new CLS_DNVRDigitPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DNVR_DIGIT,this);
			}
			break;
		case CONFIG_DNVR_VIDEOCOMBINE:
			{
				m_pPage[_iIndex] = new CLS_DNVRVideoCombinePage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DNVR_VIDEOCOMBINE,this);
			}
			break;
		case CONFIG_DNVR_BAWSLICENCEPLATE:
			{
				m_pPage[_iIndex] = new CLS_BAWLicencePlate(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DNVR_BANDW_LICENCEPLATE,this);
			}
			break;
		case CONFIG_DNVR_EXCEPTION:
			{
				m_pPage[_iIndex] = new CLS_DNVRExceptionPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DNVR_EXCEPTION,this);
			}
			break;
		case CONFIG_DNVR_CREATEFREEV:
			{
				m_pPage[_iIndex] = new CLS_DNVRCreateFree(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DNVR_CREATEFREE,this);
			}
			break;
		case CONFIG_DNVR_CHANNEL_INFO:
			{
				m_pPage[_iIndex] = new CLS_DNVRChannelInfo(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DNVR_CHANNEL_INFO,this);
			}
			break;
		case CONFIG_DNVR_TEXTPLAN:
			{
				m_pPage[_iIndex] = new CLS_DNVRTextPlan(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DNVR_TEXTPLAN,this);
			}
			break;
		case CONFIG_3G_NORMAL:
			{
				m_pPage[_iIndex] = new CLS_3GNormalPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_3G_NORMAL,this);
			}
			break;
		case CONFIG_3G_DVR:
			{
				m_pPage[_iIndex] = new CLS_3GDVRPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_3G_DVR,this);
			}
			break;
		case CONFIG_3G_ADV:
			{
				m_pPage[_iIndex] = new CLS_3GAdvPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_3G_ADV,this);
			}
			break;
		case CONFIG_VEHICLE:
			{
				m_pPage[_iIndex] = new CLS_VehiclePage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VEHICLE,this);
			}
			break;
		case CONFIG_LOG_NVS:
			{
				m_pPage[_iIndex] = new CLS_NVSLogPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_LOG_NVS,this);
			}
			break;
		case CONFIG_LOG_DVR:
			{
				m_pPage[_iIndex] = new CLS_DVRLogPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_LOG_DVR,this);
			}
			break;
		case CONFIG_PTZ:
			{
				m_pPage[_iIndex] = new CLS_PTZPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_PTZ,this);
			}
			break;
		case CONFIG_WIFI:
			{
				m_pPage[_iIndex] = new CWifiPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_WIFI,this);
			}
			break;	
		case CONFIG_VCA_TARGET:
			{
				m_pPage[_iIndex] = new CLS_VCATargetPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VCA_TARGET,this);
			}

			break;
		case CONFIG_VCA_ADVANCE:
			{
				m_pPage[_iIndex] = new CLS_VCAAdvanceParam(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VCA_ADV_PARAM,this);
			}
			break;
		case CONFIG_VCA_EVENTS:
			{
				m_pPage[_iIndex] = new CLS_VCAEventPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VCA_EVENTS,this);
			}
			break;
		case CONFIG_VCA_ALARM:
			{

			}
			break;
		case CONFIG_VCA_QUERY_FILES:
			{
				m_pPage[_iIndex] = new CLS_DlgCfgVcaQueryFile(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VCA_QUERY_FILE,this);
			}
			break;
		case CONFIG_VCA_FACE_LIB_MNG:
			{
				m_pPage[_iIndex] = new CLS_DlgCfgFaceLibMng(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VCA_FACE_LIB_MNG,this);
			}
			break;
		case CONFIG_VCA_FACE_PIC_MNG:
			{
				m_pPage[_iIndex] = new CLS_DlgCfgFacePicMng(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VCA_FACE_PIC_MNG,this);
			}
			break;
		case CONFIG_COM:
			{
				m_pPage[_iIndex] = new CLS_ComPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_COM,this);
			}
			break;
		case CONFIG_IOPORT:
			{
				m_pPage[_iIndex] = new CLS_IOPORTPAGE(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_IOPORT,this);
			}
			break;
		case CONFIG_ADVANCE_VERSION:
			{
				m_pPage[_iIndex] = new CLS_AdvVersionPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ADVANCE_VERSION,this);
			}
			break;
		case CONFIG_ADVANCE_SYSTEM:
			{
				m_pPage[_iIndex] = new CLS_AdvSystemInfoPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ADVANCE_SYSTEM_INFO,this);
			}
			break;
		case CONFIG_ADVANCE_UPGRADE:
			{
				m_pPage[_iIndex] = new CLS_AdvUpgrade(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ADVANCE_UPGRADE,this);
			}
			break;
		case CONFIG_ADVANCE_CHANNEL:
			{
				m_pPage[_iIndex] = new CLS_AdvChannelParamPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ADVANCE_CHANNEL_SET,this);
			}
			break;
		case CONFIG_VCA_ALARM_INFO:
			{
				m_pPage[_iIndex] = new CLS_VCAAlarmInfoPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VCA_ALARM_INFORMATION,this);
			}
			break;
		case CONFIG_VCA_ALARM_SCHEDULE:
			{
				m_pPage[_iIndex] = new CLS_VCAAlarmSchedulePage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VCA_ALARM_SCHEDULE,this);
			}
			break;
		case CONFIG_VCA_ALARM_LINK:
			{
				m_pPage[_iIndex] = new CLS_VCAAlarmLinkPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VCA_ALARM_LINK,this);
			}
			break;
		case CONFIG_COOPER_DOME:
			{
				m_pPage[_iIndex] = new CLS_DomeInfrared(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_COOPER_DOME,this);
			}
			break;
		case CONFIG_VIDEO_INTERESTED:
			{
				m_pPage[_iIndex] = new CLS_VideoInterested(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VIDEO_INTERESTED,this);
			}
			break;
		case CONFIG_APPEND_OSD:
			{
				m_pPage[_iIndex] = new CLS_AppendOSDPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_APPEND_OSD,this);
			}
			break;
		case CONFIG_OSD_BACK_GROUND:
			{
				m_pPage[_iIndex] = new CLS_OSDBackgroundPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_OSD_BACK_GROUND,this);
			}
			break;	
		case CONFIG_DOME_STATE:
			{
				m_pPage[_iIndex] = new CLS_DomeState(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DOME_STATE,this);
			}
			break;
		case CONFIG_DOME_SCHEDULE:
			{
				m_pPage[_iIndex] = new CLS_DomeSchedule(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DOME_SCHEDULE,this);
			}
			break;
		case CONFIG_DOME_MENU:
			{
				m_pPage[_iIndex] = new CLS_DomeMenu(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DOME_MENU,this);
			}
			break;
		case CONFIG_DONGHUAN_SET:
			{
				m_pPage[_iIndex] = new CLS_DonghuanSet(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DONGHUAN_SET,this);
			}
			break;
		case CONFIG_DONGHUAN_LINKSET:
			{
				m_pPage[_iIndex] = new CLS_LinkSet(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_LINK_SET,this);
			}
			break;
		case CONFIG_DONGHUAN_COMFORT:
			{
				m_pPage[_iIndex] = new CLS_SerialManagePage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_COM_PAGE,this);
			}
			break;
		case CONFIG_DONGHUAN_SCHEDULE:
			{
				m_pPage[_iIndex] = new CLS_DefenceTemplatePage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DONGHUAN_SCHEDULE,this);
			}
			break;
		case CONFIG_DONGHUAN_OSDSET:
			{
				m_pPage[_iIndex] = new  CLS_OSDManagePage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_OSD_SET,this);
			}
			break;
		case CONFIG_DONGHUAN_DATA:
			{
				m_pPage[_iIndex] = new CLS_PowerEnvParamPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DH_DATA,this);
			}
			break;	
		case CONFIG_REPORT_SET:
			{
				m_pPage[_iIndex] = new CLS_ReportSet(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_REPORT_SET,this);
			}
			break;
		case CONFIG_VCA_EVENTS_ADV:
			{
				m_pPage[_iIndex] = new CLS_VCAEvnetsAdvParam(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VCA_EVENTS_ADV_PARAM,this);
			}
			break;
		case CONFIG_DEMO_CRUSIE:
			{
				m_pPage[_iIndex] = new VCAframDomeCurise(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VCA_CRUSIE,this);
			}
			break;
		case CONFIG_VCA_SMART_SEARCH:
			{
 				m_pPage[_iIndex] = new CLS_VCASmartSearch(this);
 				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VCA_SMART_SEARCH,this);
			}
			break;
		case CONFIG_VCA_SMART_TRACK:
			{
				m_pPage[_iIndex] = new CLS_VCAEvnetsSmartTrack(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_VCA_EVENTS_SMART_TRACK,this);
			}
			break;
		case CONFIG_ADVANCE_LOCAL:
			{
				m_pPage[_iIndex] = new CLS_AdvLocalSet(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ADVANCE_LOCAL,this);
			}
			break;
		case CONFIG_DOME_HD1:
			{
				m_pPage[_iIndex] = new CLS_DomeHDParam1(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DOME_HD_PARAM1, this);
			}
			break;
		case CONFIG_DOME_HD2:
			{
				m_pPage[_iIndex] = new CLS_DomeHDParam2(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DOME_HD_PARAM2, this);
			}
			break;
		case CONFIG_DOME_HD3:
			{
				m_pPage[_iIndex] = new CLS_DomeHDParam3(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DOME_HD_PARAM3, this);
			}
			break;
		case CONFIG_HD_SCHEDULE:
			{
				m_pPage[_iIndex] = new CLS_HDSchedule(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_HD_SCHEDULE, this);
			}
			break;
		case CONFIG_DOME_BASIC1:
			{
				m_pPage[_iIndex] = new CLS_DomeBasicInfo(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DOME_BASIC1, this);
			}
			break;
		case CONFIG_DOME_BASIC2:
			{
				m_pPage[_iIndex] = new CLS_DomeTitle(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DOME_BASIC2, this);
			}
			break;
		case CONFIG_DOME_RUN1:
			{
				m_pPage[_iIndex] = new CLS_DomeRun1(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DOME_RUN1, this);
			}
			break;
		case CONFIG_DOME_RUN2:
			{
				m_pPage[_iIndex] = new CLS_DomeRun2(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_DOME_RUN2, this);
			}
			break;
		case CONFIG_ITS_PICTURE_COMMON2:
			{
				m_pPage[_iIndex] = new Cls_ItsPictureCommon2(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_PICTURE_COMMON2, this);
			}
			break;
		case CONFIG_ITS_PICTURE_OTHER:
			{
				//Cls_ItsPictureOther
				//IDD_DLG_ITS_PICTURE_OTHER
			}
			break;
		case CONFIG_ITS_SIGNAL_OTHER:
			{
				m_pPage[_iIndex] = new Cls_ItsSignalOther(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_SIGNAL_OTHER, this);
			}
			break;
		case CONFIG_ITS_ROADWAY_COMMON2:
			{
				m_pPage[_iIndex] = new CLS_ItsRoadwayCommon2(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_ROADWAY_COMMON2,this);
			}
			break;
		case CONFIG_ITS_ROADWAY_COMMON4:
			{
				m_pPage[_iIndex] = new CLS_ItsRoadwayCommon4(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_ROADWAY_COMMON4,this);
			}
			break;
		case CONFIG_ITS_ROADWAY_ADVANCED1:
			{
				m_pPage[_iIndex] = new CLS_ITSRoadWayAdvanced1(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_ROADWAY_ADVANCED1,this);
			}
			break;
		case CONFIG_ITS_COMPO_PIC:
			{
				m_pPage[_iIndex] = new Cls_ItsCompoPic(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_COMPO_PIC,this);
			}
			break;
		case CONFIG_ITS_TRAFFIC_STATIS:
			{
				m_pPage[_iIndex] = new Cls_ItsTrafficStatistics(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_TRAFFIC_STATIS,this);
			}
			break;
		case CONFIG_ITS_ILLEGAl_TYPE:
			{
				m_pPage[_iIndex] = new Cls_ItsIllegalTppe(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_ILLEGAL_TYPE,this);
			}
			break;
		case CONFIG_ITS_STATE_QUERY:
			{
				m_pPage[_iIndex] = new Cls_ItsStateQuery(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_STATE_QUERY,this);
			}
			break;
		case CONFIG_ITS_FOCUS_AID:
			{
				m_pPage[_iIndex] = new Cls_ItsFocusAid(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_FOCUS_AID,this);
			}
			break;
		case CONFIG_LAN_HTTP:
			{
				m_pPage[_iIndex] = new CLS_LinkHttp(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_LAN_HTTP,this);
			}
			break;
		case CONFIG_LAN_PORT:
			{
				m_pPage[_iIndex] = new CLS_PortMapping(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_LAN_PORT,this);
			}
			break;
		case CONFIG_LAN_UPNP:
			{
				m_pPage[_iIndex] = new CLS_UPnpPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_LAN_UPNP,this);
			}
			break;
		case CONFIG_LAN_QOS:
			{
				m_pPage[_iIndex] = new CLS_QosPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_QOS,this);
			}
			break;
		case CONFIG_LAN_RTMP:
			{
				m_pPage[_iIndex] = new CLS_RtmpPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_RTMP,this);
			}
			break;
		case CONFIG_ITS_ROADWAY_ADVANCED3:
			{
				m_pPage[_iIndex] = new CLS_ITSRoadWayAdvanced3(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_ROADWAY_ADVANCED3,this);
			}
			break;
		case CONFIG_ITS_ROADWAY_CAPTURECFG:
			{
				m_pPage[_iIndex] = new CLS_DLG_ITSRoadwayCaptureCfg(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_ROADWAY_CAP,this);
			}
			break;
		case CONFIG_ITS_EXTENDED_CONFIG1:
			{
				m_pPage[_iIndex] = new CLS_ExtendedParam(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_EXTENDED_PARAM1,this);
			}
			break;
		case CONFIG_ITS_EXTENDED_CONFIG2:
			{
				m_pPage[_iIndex] = new CLS_ItsAdvanceConf2(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_ADVANCE_CONF2,this);
			}
			break;
		case CONFIG_AUTO_TEST:
			{
				m_pPage[_iIndex] = new CLS_AutoTestPage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_AUTO_TEST, this);
			}
			break;
		case CONFIG_ITS_IO:
			{
				m_pPage[_iIndex] = new CLS_IOData(this);
				m_pPage[_iIndex]->Create(IDD_DLG_ITS_IO_DATA, this);
			}
			break;
		case CONFIG_ADVANCE_FUNC_CTG:		//Add by TDY
			{
				m_pPage[_iIndex] = new CLS_DLG_FUNC_COLORTOGRAY(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_FUNC_COLORTOGRAY, this);
			}
			break;
		case CONFIG_ADVANCE_FUNC_VTC:
			{
				m_pPage[_iIndex] = new CLS_DLG_CFG_FUNC_VideoTranceCoding(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_FUNC_VIDEOTCODING, this);
			}
			break;
		case CONFIG_ADVANCE_FUNC_SMARTA:
			{
				m_pPage[_iIndex] = new CLS_DlgFuncSmarta(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_FUNC_SMARTA, this);
			}
			break;
		case CONFIG_ADVANCE_FUNC_DDNS:
			{
				m_pPage[_iIndex] = new CLS_DlgFuncDdns(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_FUNC_DDNS, this);
			}
			break;
		case CONFIG_ADVANCE_FUNC_NETWORK:
			{
				m_pPage[_iIndex] = new CLS_DlgFuncNetwork(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_FUNC_NETWORK, this);
			}
			break;
		case CONFIG_ADVANCE_FUNC_DECODER:
			{
				m_pPage[_iIndex] = new CLS_DlgFuncDecoder(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_FUNC_DECORDER, this);
			}
			break;
		case CONFIG_ADVANCE_FUNC_PEOPLENUM:
			{
				m_pPage[_iIndex] = new CLS_DlgFuncStatisPeopleNum(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_FUNC_PEOPLENUMEXCEL, this);
			}
			break;
		case CONFIG_ADVANCE_FUNC_ROI:
			{
				m_pPage[_iIndex] = new CLS_DlgFuncRoi(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_FUNC_ROI, this);
			}
			break;
		case CONFIG_ADVANCE_FUNC_POTICS_LAW:
			{
				m_pPage[_iIndex] = new CLS_DlgFuncLaw(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_FUNC_LAW, this);
			}
			break;
		case CONFIG_ADVANCE_FUNC_DOME:
			{
				m_pPage[_iIndex] = new CLS_DlgFuncDome(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_FUNC_DOME, this);
			}
			break;
		case CONFIG_ADVANCE_COMMONENABLE:
			{
				m_pPage[_iIndex] = new CLS_DlgCommonEnable(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_COMMONENABLE, this);
			}
			break;
		case CONFIG_ITS_PLATFORM_CFG:
			{
				m_pPage[_iIndex] = new CLS_ITSPlatformConfig(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ITS_STAR_NVR_PLAT_CFG, this);
			}
			break;
		case CONFIG_ITS_DEV_MANAGE:
			{
				m_pPage[_iIndex] = new CLS_ITSDevManage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ITS_STAR_NVR_DEV_MNG, this);
			}
			break;
		case CONFIG_ITS_LANE_MANAGE:
			{
				m_pPage[_iIndex] = new CLS_ITSLaneManage(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ITS_STAR_NVR_LANE_MNG, this);
			}
			break;
		case CONFIG_ITS_BAYONET_DATA:
			{
				m_pPage[_iIndex] = new CLS_ITSBayonetData(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ITS_STAR_NVR_BAYONET_DATA, this);
			}
			break;
		case CONFIG_FEC_HEAT_MAP:
			{
				m_pPage[_iIndex] = new CLS_FECHeatMap(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_FEC_HEAT_MAP, this);
			}
			break;

#ifdef ALERT_TODO
		case CONFIG_UNIQUE_ALERT:
		case CONFIG_UNIQUE_ALERT_ENABLE_STATUS:
			{
				m_pPage[_iIndex] = new CLS_DlgUniqueAlertEnable(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ALERT_ENABLE_STATUS, this);
			}
			break;
		case CONFIG_UNIQUE_ALERT_PLAN:
			{
				m_pPage[_iIndex] = new CLS_DlgUniqueAlertPlan(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ALERT_PLAN, this);
			}
			break;
		case CONFIG_UNIQUE_ALERT_CUSTOM_EVENT:
			{
				m_pPage[_iIndex] = new CLS_DlgUniqueAlertCustom(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ALERT_CUSTOM, this);
			}
			break;
		case CONFIG_UNIQUE_ALERT_ALARM_LINK:
			{
				m_pPage[_iIndex] = new CLS_DlgUniqueAlertAlarmLink(this);
				m_pPage[_iIndex]->Create(IDD_DLG_CFG_ALERT_ALARM_LINK, this);
			}
			break;
#endif
		}
		
		if (m_pPage[_iIndex])
		{
			RECT rcShow = {0};
			GetDlgItem(IDC_STATIC_CENTER_BG)->GetWindowRect(&rcShow);
			ScreenToClient(&rcShow);
			m_pPage[_iIndex]->MoveWindow(&rcShow);
		}
		else
		{
			return -1;
		}
	}

	if(m_pCurrent)
	{
		m_pCurrent->ShowWindow(SW_HIDE);
		CloseVideo();
	}
	m_pCurrent = m_pPage[_iIndex];

	//先通知再显示
	if (m_iLogonID < 0)
	{
		LockPage(TRUE);
	}
	else
	{
		LockPage(FALSE);
		m_pCurrent->OnChannelChanged(m_iLogonID,m_iChannelNo,m_iStreamNo);
	}
	m_pCurrent->ShowWindow(SW_SHOW);

	return 0;
}

void CLS_ConfigWindow::OnTvnSelchangedTreeConfig(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	int iIndex = (int)m_tvConfig.GetItemData(hItem);
	ShowBasePage(iIndex);

	*pResult = 0;
}

void CLS_ConfigWindow::OnDestroy()
{
	CLS_BaseWindow::OnDestroy();

	if (m_pVideo)
	{
		m_pVideo->DestroyWindow();
		delete m_pVideo;
		m_pVideo = NULL;
	}
	for (int i = 0; i < CONFIG_MAX; ++i)
	{
		if (m_pPage[i])
		{
			m_pPage[i]->DestroyWindow();
			delete m_pPage[i];
			m_pPage[i] = NULL;
		}
	}
	m_pCurrent = NULL;
	
}

void CLS_ConfigWindow::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (m_iLogonID == _iLogonID && m_iChannelNo == _iChannelNo && m_iStreamNo == _iStreamNo)
	{
		return;
	}

	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;
	if (m_iLogonID < 0)
	{
		LockPage(TRUE);
	}
	else
	{
		LockPage(FALSE);
		if (m_pCurrent)
		{
			CloseVideo();
			m_pCurrent->OnChannelChanged(_iLogonID,_iChannelNo,_iStreamNo);
		}
	}
}

int CLS_ConfigWindow::LockPage(BOOL _bLocked)
{
	if (m_bLocked == _bLocked)
	{
		return 0;
	}

	m_bLocked = _bLocked;
	BOOL bEnable = TRUE;
	if (TRUE == _bLocked)
	{
		bEnable = FALSE;
	}
	m_tvConfig.EnableWindow(bEnable);
	if (m_pCurrent)
	{
		m_pCurrent->EnableWindow(bEnable);
	}
	return 0;
}

void CLS_ConfigWindow::OnLanguageChanged( int _iLanguage )
{
	for (int i = 0; i < CONFIG_MAX; ++i)
	{
		if (m_pPage[i])
		{
			m_pPage[i]->OnLanguageChanged(_iLanguage);
		}
	}
	UI_UpdateDialog();
}

void CLS_ConfigWindow::UI_UpdateDialog()
{
	HTREEITEM hItem = NULL;
	HTREEITEM hSubItem = NULL;
	HTREEITEM hThirdItem = NULL;
	
	hItem = InsertItem(m_tvConfig,IDS_CONFIG_AUDIO_VIDEO,CONFIG_VIDEO_PARAM);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_VIDEO_PARAM,CONFIG_VIDEO_PARAM,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_VIDEO_PARAM_SCHEDULE,CONFIG_VIDEO_PARAM_SCHEDULE,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_AUDIO_PARAM,CONFIG_AUDIO_PARAM,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_VIDEO_ENCRYPT,CONFIG_VIDEO_ENCRYPT,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_VIDEO_ENCODE,CONFIG_VIDEO_ENCODE_SLICE,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CFG_VIDEO_INTERESTED,CONFIG_VIDEO_INTERESTED,hItem);

	hItem = InsertItem(m_tvConfig, IDS_CONFIG_OSD, CONFIG_OSD);
	hSubItem = InsertItem(m_tvConfig, IDS_CONFIG_OSD, CONFIG_OSD, hItem);
	hSubItem = InsertItem(m_tvConfig, IDS_CFG_APPEND_OSD, CONFIG_APPEND_OSD, hItem);
	hSubItem = InsertItem(m_tvConfig, IDS_OSD_BACK_GROUND, CONFIG_OSD_BACK_GROUND, hItem);
	
	hItem = InsertItem(m_tvConfig,IDS_CONFIG_PTZ,CONFIG_PTZ);

	hItem = InsertItem(m_tvConfig,IDS_CONFIG_COM,CONFIG_COM);	
	
	hItem = InsertItem(m_tvConfig,IDS_CONFIG_8D1,CONFIG_8D1);

	hItem = InsertItem(m_tvConfig,IDS_CONFIG_BURN,CONFIG_BURN);
	hSubItem = InsertItem(m_tvConfig, IDS_CONFIG_BURN, CONFIG_BURN, hItem);
	hSubItem = InsertItem(m_tvConfig, "H323", CONFIG_BURN_H323, hItem);
	hSubItem = InsertItem(m_tvConfig, "H8", CONFIG_BURN_H8, hItem);

	hItem = InsertItem(m_tvConfig, IDS_HD_CAMERA_SET, CONFIG_DOME_HD1);
	hSubItem = InsertItem(m_tvConfig, IDS_DOME_HD_PARAM, CONFIG_DOME_HD1, hItem);
	hThirdItem = InsertItem(m_tvConfig, IDS_DOME_HD_PARAM1, CONFIG_DOME_HD1, hSubItem);
	hThirdItem = InsertItem(m_tvConfig, IDS_DOME_HD_PARAM2, CONFIG_DOME_HD2, hSubItem);
	hThirdItem = InsertItem(m_tvConfig, IDS_DOME_HD_PARAM3, CONFIG_DOME_HD3, hSubItem);
	hThirdItem = InsertItem(m_tvConfig, IDS_HD_SCHEDULE, CONFIG_HD_SCHEDULE, hSubItem);
	hSubItem = InsertItem(m_tvConfig, IDS_CFG_DOME_STATE, CONFIG_DOME_STATE, hItem);
	hSubItem = InsertItem(m_tvConfig, IDS_DOME_BASIC_SET, CONFIG_DOME_BASIC1, hItem);
	hThirdItem = InsertItem(m_tvConfig, IDS_DOME_BASIC_INFO, CONFIG_DOME_BASIC1, hSubItem);
	hThirdItem = InsertItem(m_tvConfig, IDS_DOME_BASIC_TITLE, CONFIG_DOME_BASIC2, hSubItem);
	hSubItem = InsertItem(m_tvConfig, IDS_DOME_RUN_SET, CONFIG_DOME_RUN1, hItem);
	hThirdItem = InsertItem(m_tvConfig, IDS_DOME_RUN_SET1, CONFIG_DOME_RUN1, hSubItem);
	hThirdItem = InsertItem(m_tvConfig, IDS_DOME_RUN_SET2, CONFIG_DOME_RUN2, hSubItem);
	hSubItem = InsertItem(m_tvConfig, IDS_DOME_REDOUT_SET, CONFIG_COOPER_DOME, hItem);	//Cooper球界面改成红外设置界面
	hSubItem = InsertItem(m_tvConfig, IDS_CFG_DOME_SCHEDULE, CONFIG_DOME_SCHEDULE, hItem);
	hSubItem = InsertItem(m_tvConfig, IDS_CFG_DOME_MENU, CONFIG_DOME_MENU, hItem);
	hSubItem = InsertItem(m_tvConfig, IDS_CONFIG_HD, CONFIG_HD, hItem);

	hItem = InsertItem(m_tvConfig, IDS_CONFIG_REPORT_SET, CONFIG_REPORT_SET);
	hItem = InsertItem(m_tvConfig,IDS_CONFIG_CMOS,CONFIG_CMOS);

	hItem = InsertItem(m_tvConfig,IDS_CONFIG_LAN,CONFIG_IP);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_IP,CONFIG_IP,hItem);
	hSubItem = InsertItem(m_tvConfig, IDS_CONFIG_IPADV, CONFIG_IPADV, hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_WIFI,CONFIG_WIFI,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_LAN_IPV4,CONFIG_LAN_IPV4,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_LAN_IPV6,CONFIG_LAN_IPV6,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_LAN_WOKEMODE,CONFIG_LAN_WOKEMODE,hItem);	
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_FTP,CONFIG_FTP,hItem); 
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DDNS,CONFIG_DDNS,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_NTP,CONFIG_NTP,hItem);	
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_UDP,CONFIG_UDP,hItem);
	hSubItem = InsertItem(m_tvConfig, "HTTP", CONFIG_LAN_HTTP, hItem);
	hSubItem = InsertItem(m_tvConfig, "PORT", CONFIG_LAN_PORT, hItem);
	hSubItem = InsertItem(m_tvConfig, "QOS", CONFIG_LAN_QOS, hItem);
	hSubItem = InsertItem(m_tvConfig, "UPNP", CONFIG_LAN_UPNP, hItem);
	hSubItem = InsertItem(m_tvConfig, "RTMP", CONFIG_LAN_RTMP, hItem);

	hItem = InsertItem(m_tvConfig,IDS_CONFIG_3G,CONFIG_3G_NORMAL);
	hSubItem = InsertItem(m_tvConfig,IDS_CFG_3G_NORMAL,CONFIG_3G_NORMAL,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CFG_3G_DVR,CONFIG_3G_DVR,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CFG_3G_ADV,CONFIG_3G_ADV,hItem);

	//车载设置
	hItem = InsertItem(m_tvConfig,IDS_CONFIG_VEHICLE,CONFIG_VEHICLE);

	//D/NVR
	hItem = InsertItem(m_tvConfig,IDS_CONFIG_DNVR,CONFIG_ALARM);
	hSubItem = InsertItem(m_tvConfig,IDD_DLG_CFG_IOPORT,CONFIG_IOPORT,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DNVR_DIGIT,CONFIG_DNVR_DIGIT,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DNVR_VIDEOCOMBINE,CONFIG_DNVR_VIDEOCOMBINE,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DNVR_EXCEPTION,CONFIG_DNVR_EXCEPTION,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DNVR_CREATEFREEV0,CONFIG_DNVR_CREATEFREEV,hItem);//画面自定义分割
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DNVR_TEXTPLAN,CONFIG_DNVR_TEXTPLAN,hItem);//文字预案
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DNVR_BAWLICENCEPLATE,CONFIG_DNVR_BAWSLICENCEPLATE,hItem);//黑白车牌
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DNVR_CHANNELINFO,CONFIG_DNVR_CHANNEL_INFO,hItem);//DNVR通道信息

	//存储
	hItem = InsertItem(m_tvConfig,IDS_CONFIG_STORAGE,CONFIG_STORAGE);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_STORAGE,CONFIG_STORAGE,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_STORAGE_SET,CONFIG_STORAGE_SET,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_STORAGE_DISKINFO,CONFIG_STORAGE_DISKINFO,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_HOLIDAY_PLAN,CONFIG_HOLIDAY_PLAN,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_STORAGE_STRATEGY,CONFIG_STORAGE_STRATEGY,hItem);
	hSubItem = InsertItem(m_tvConfig,"S.M.A.R.T",CONFIG_STORAGE_SMART,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CE_DISKMANAGE,CONFIG_STORAGE_DISKMANAGE,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_STORAGE_CAPTION_ANR,CONFIG_STORAGE_ANR,hItem);

	//日志
	hItem = InsertItem(m_tvConfig,IDS_CONFIG_LOG,CONFIG_LOG_NVS);
	hSubItem = InsertItem(m_tvConfig,IDS_CFG_LOG_NVS,CONFIG_LOG_NVS,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CFG_LOG_DVR,CONFIG_LOG_DVR,hItem);

	//智能分析
	hItem = InsertItem(m_tvConfig,IDS_CONFIGPAGE_VCA , CONFIG_VCA_TARGET);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIGPAGE_VCA_TARGET, CONFIG_VCA_TARGET, hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIGPAGE_VCA_ADV, CONFIG_VCA_ADVANCE, hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIGPAGE_VCA_EVENTS_ADV, CONFIG_VCA_EVENTS_ADV, hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIGPAGE_VCA_EVENTS, CONFIG_VCA_EVENTS, hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_VCA_ALARM_INFO, CONFIG_VCA_ALARM_INFO, hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_VCA_ALARM_SCHEDULE, CONFIG_VCA_ALARM_SCHEDULE, hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_VCA_ALARM_LINK, CONFIG_VCA_ALARM_LINK, hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CFG_CRUSIE,CONFIG_DEMO_CRUSIE,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_VCA_SMART_SEARCH,CONFIG_VCA_SMART_SEARCH,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_VCA_SMART_TRACK,CONFIG_VCA_SMART_TRACK,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_VCA_QUERY_FILE, CONFIG_VCA_QUERY_FILES,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_VCA_FACE_LIB, CONFIG_VCA_FACE_LIB_MNG,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_VCA_FACE_PIC, CONFIG_VCA_FACE_PIC_MNG,hItem);


#ifdef ALERT_TODO
	//特色警戒
	hItem = InsertItem(m_tvConfig, "特色警戒@#", CONFIG_UNIQUE_ALERT);
	hSubItem = InsertItem(m_tvConfig, "使能状态@#", CONFIG_UNIQUE_ALERT_ENABLE_STATUS,hItem);
	hSubItem = InsertItem(m_tvConfig, "警戒预案@#", CONFIG_UNIQUE_ALERT_PLAN,hItem);
	hSubItem = InsertItem(m_tvConfig, "自定义事件参数@#", CONFIG_UNIQUE_ALERT_CUSTOM_EVENT,hItem);
	hSubItem = InsertItem(m_tvConfig, "自定义报警联动@#", CONFIG_UNIQUE_ALERT_ALARM_LINK,hItem);
#endif

	//报警管理
	hItem = InsertItem(m_tvConfig,IDS_ALARM_MANAGE , CONFIG_DNVR_ALMLINK);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_ALARM,CONFIG_ALARM,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DNVR_ALMSCH,CONFIG_DNVR_ALMSCH,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DNVR_ALMLINK,CONFIG_DNVR_ALMLINK,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_ALARM_HUM_TEM, CONFIG_ALARM_HUM_TEM, hItem);

	hItem = InsertItem(m_tvConfig,IDS_CONFIG_ATM,CONFIG_ATM);

	hItem = InsertItem(m_tvConfig,IDS_CONFIG_ITS, CONFIG_ITS_PICTURE_COMMON1);
	hSubItem = InsertItem(m_tvConfig, IDS_ITS_PICTURE, CONFIG_ITS_PICTURE_COMMON1, hItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ITS_PICTURE_COMM1,CONFIG_ITS_PICTURE_COMMON1,hSubItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ITS_PICTURE_COMM2,CONFIG_ITS_PICTURE_COMMON2,hSubItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ITS_PICTURE_COMM3,CONFIG_ITS_PICTURE_COMMON3,hSubItem);
	//
	hSubItem = InsertItem(m_tvConfig, IDS_ITS_SIGNALlIGHT, CONFIG_ITS_SIGNAL_CHECK, hItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ITS_SIGNALlIGHT_CHECK,CONFIG_ITS_SIGNAL_CHECK,hSubItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ITS_OTHER,CONFIG_ITS_SIGNAL_OTHER,hSubItem);
	//
	hSubItem = InsertItem(m_tvConfig, IDS_ITS_ROADWAY, CONFIG_ITS_ROADWAY_COMMON1, hItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ITS_ROAD_COMM1,CONFIG_ITS_ROADWAY_COMMON1,hSubItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ITS_ROAD_COMM2,CONFIG_ITS_ROADWAY_COMMON2,hSubItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ITS_ROAD_COMM3,CONFIG_ITS_ROADWAY_COMMON3,hSubItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ITS_ROAD_COMM4,CONFIG_ITS_ROADWAY_COMMON4,hSubItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ITS_ROAD_ADV1,CONFIG_ITS_ROADWAY_ADVANCED1,hSubItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ITS_ADVANCED2,CONFIG_ITS_ROADWAY_ADVANCED2,hSubItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ITS_ADVANCED3,CONFIG_ITS_ROADWAY_ADVANCED3,hSubItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ROADWAY_CAP_CFG,CONFIG_ITS_ROADWAY_CAPTURECFG,hSubItem);
	//
	hSubItem = InsertItem(m_tvConfig,IDS_ITS_SYSTEMPARAM1,CONFIG_ITS_SYSTEMPARAM1,hItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ITS_SYS_1,CONFIG_ITS_SYSTEMPARAM1,hSubItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ITS_SYS_2,CONFIG_ITS_SYSTEMPARAM2,hSubItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ITS_SYS_3,CONFIG_ITS_SYSTEMPARAM3,hSubItem);
	//
	hSubItem = InsertItem(m_tvConfig,IDS_ITS_RECOPARAM,CONFIG_ITS_RECOPARAM,hItem);
	hThirdItem = InsertItem(m_tvConfig, IDS_ITS_RECOPARAM_1, CONFIG_ITS_RECOPARAM, hSubItem);
	hThirdItem = InsertItem(m_tvConfig, IDS_ITS_RECOPARAM_2, CONFIG_ITS_RECOPARAM2, hSubItem);
	//
	hSubItem = InsertItem(m_tvConfig,IDS_ITS_EXTENDED_PARAM ,CONFIG_ITS_EXTENDED_CONFIG1,hItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ITS_EXTENDED_PARAM1 , CONFIG_ITS_EXTENDED_CONFIG1, hSubItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_ITS_ADVANCE_CONF2 , CONFIG_ITS_EXTENDED_CONFIG2, hSubItem);
	//
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_ITS_OSD,CONFIG_ITS_OSD,hItem);
	//
	hSubItem = InsertItem(m_tvConfig,IDS_ITS_OSD_EX,CONFIG_ITS_OSD_EX,hItem);
	//
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DNVR_ALMLINK,CONFIG_ITS_ALARM_LINK,hItem);
	//
	hSubItem = InsertItem(m_tvConfig, IDS_ITS_COMPO_PIC, CONFIG_ITS_COMPO_PIC, hItem);
	//
	hSubItem = InsertItem(m_tvConfig, IDS_ITS_TRAFFIC_STATIS, CONFIG_ITS_TRAFFIC_STATIS, hItem);
	//
	hSubItem = InsertItem(m_tvConfig, IDS_ITS_ILLEGAL_TYPE,CONFIG_ITS_ILLEGAl_TYPE,hItem);
	//
	hSubItem = InsertItem(m_tvConfig, IDS_ITS_STATE_QUERY, CONFIG_ITS_STATE_QUERY, hItem);
	//
	hSubItem = InsertItem(m_tvConfig, IDS_ITS_FOCUS_AID, CONFIG_ITS_FOCUS_AID, hItem);
	//
	hSubItem = InsertItem(m_tvConfig, IDS_ITS_IO, CONFIG_ITS_IO, hItem);
	//
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_ITS_OTHER,CONFIG_ITS_OTHER,hItem);

	hSubItem = InsertItem(m_tvConfig, IDS_ITS_BAYONET_NVR, CONFIG_ITS_PLATFORM_CFG, hItem);
	hThirdItem = InsertItem(m_tvConfig, IDS_ITS_PLATFORM_CFG, CONFIG_ITS_PLATFORM_CFG, hSubItem);
	hThirdItem = InsertItem(m_tvConfig, IDS_ITS_DEVICE_MANAGE, CONFIG_ITS_DEV_MANAGE, hSubItem);
	hThirdItem = InsertItem(m_tvConfig, IDS_ITS_LANE_MANAGE, CONFIG_ITS_LANE_MANAGE, hSubItem);
	hThirdItem = InsertItem(m_tvConfig, IDS_BAYONET_DATA, CONFIG_ITS_BAYONET_DATA, hSubItem);

	hItem = InsertItem(m_tvConfig,IDS_CONFIG_ADVANCE_PAGE,CONFIG_ADVANCE_VERSION);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_ADVANCE_VERSION,CONFIG_ADVANCE_VERSION,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_ADVANCE_SYSTEM,CONFIG_ADVANCE_SYSTEM,hItem);

	//通用使能
	hSubItem = InsertItem(m_tvConfig,IDS_CFG_COMMONENABLE,CONFIG_ADVANCE_COMMONENABLE,hItem);

	hSubItem = InsertItem(m_tvConfig,IDS_CFG_ADV_LOCAL_SET,CONFIG_ADVANCE_LOCAL,hItem);	
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_USER,CONFIG_USER,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_AUTHORITY_MANAGEMENT,CONFIG_AUTHORITY_LOCAL,hItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_CFG_LOCAL_RIGHT,CONFIG_AUTHORITY_LOCAL,hSubItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_CFG_REMOTE_RIGHT,CONFIG_AUTHORITY_REMOTE,hSubItem);
	hThirdItem = InsertItem(m_tvConfig,IDS_CFG_CHANNEL_RIGHT,CONFIG_AUTHORITY_CHANNEL,hSubItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_LANGUAGE_TIMEZONE,CONFIG_LANGUAGE,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_ADVANCE_UPGRADE_BACKUP,CONFIG_ADVANCE_UPGRADE,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_ADVANCE_CHANNEL_PARAM,CONFIG_ADVANCE_CHANNEL,hItem);	
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DZ,CONFIG_DZ,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_OPTION_PU,CONFIG_OPTION_PU,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_SO,CONFIG_SO,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_SIP,CONFIG_SIP,hItem);	
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_ADV,CONFIG_ADV,hItem);

	hItem = InsertItem(m_tvConfig,IDS_CONFIG_DONGHUAN_MAN,CONFIG_DONGHUAN_SET);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DONGHUAN_SET,CONFIG_DONGHUAN_SET,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DONGHUAN_LINKSET,CONFIG_DONGHUAN_LINKSET,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DONGHUAN_COMFORT,CONFIG_DONGHUAN_COMFORT,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DONGHUAN_SCHEDULE,CONFIG_DONGHUAN_SCHEDULE,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DONGHUAN_OSDSET,CONFIG_DONGHUAN_OSDSET,hItem);
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DONGHUAN_DATA,CONFIG_DONGHUAN_DATA,hItem);

	hItem = InsertItem(m_tvConfig, IDS_AUTOTEST, CONFIG_AUTO_TEST);

	//能力集 TDY
	hItem = InsertItem(m_tvConfig,IDS_CFG_FUNC,CONFIG_ADVANCE_FUNCASSEMBLE);
	//彩转黑
	hSubItem = InsertItem(m_tvConfig,IDS_CFG_FUNC_CTG,CONFIG_ADVANCE_FUNC_CTG,hItem);
	//录像转码
	hSubItem = InsertItem(m_tvConfig,IDS_CFG_FUNC_VIDEOTRANSCODING,CONFIG_ADVANCE_FUNC_VTC,hItem);	
	//DDNS
	hSubItem = InsertItem(m_tvConfig,"DDNS",CONFIG_ADVANCE_FUNC_DDNS,hItem);	
	//人数统计
	hSubItem = InsertItem(m_tvConfig,IDS_VCA_PEOPLENUM,CONFIG_ADVANCE_FUNC_PEOPLENUM,hItem);	
	//政法业务
	hSubItem = InsertItem(m_tvConfig,IDS_CFG_FUNC_POTICS_LAW,CONFIG_ADVANCE_FUNC_POTICS_LAW,hItem);
	//解码器业务
	hSubItem = InsertItem(m_tvConfig,IDS_CFG_FUNC_DECODER,CONFIG_ADVANCE_FUNC_DECODER,hItem);
	//ROI
	hSubItem = InsertItem(m_tvConfig,"ROI",CONFIG_ADVANCE_FUNC_ROI,hItem);
	//球机参数
	hSubItem = InsertItem(m_tvConfig,IDS_CFG_FUNC_DOME,CONFIG_ADVANCE_FUNC_DOME,hItem);	
	//智能分析
	hSubItem = InsertItem(m_tvConfig,IDS_CONFIG_DVR_VCA,CONFIG_ADVANCE_FUNC_SMARTA,hItem);	
	//网络参数  
	hSubItem = InsertItem(m_tvConfig,IDS_NETWORK,CONFIG_ADVANCE_FUNC_NETWORK,hItem);	
	//add end

	hItem = InsertItem(m_tvConfig,IDS_CFG_FEC,CONFIG_FEC);
	//热度图
	hSubItem = InsertItem(m_tvConfig,IDS_CFG_FEC_HEAT_MAP,CONFIG_FEC_HEAT_MAP,hItem);

}

BOOL CLS_ConfigWindow::ShowVideo()
{
	if (NULL == m_pVideo)
	{
		m_pVideo = new CLS_VideoPage(this);
		m_pVideo->Create(IDD_DLG_CFG_VIDEO);
	}
	if (m_pVideo)
	{
		int iChannelNo = 0;
		int iStreamNo = 0;
		if (m_iChannelNo > 0)
		{
			iChannelNo = m_iChannelNo;
		}
		if (m_iStreamNo > 0)
		{
			iStreamNo = m_iStreamNo;
		}
		return m_pVideo->ShowVideo(m_iLogonID,iChannelNo,iStreamNo);
	}
	
	return FALSE;
}

BOOL CLS_ConfigWindow::CloseVideo()
{
	if (m_pVideo)
	{
		return m_pVideo->CloseVideo();
	}
	return FALSE;
}

void CLS_ConfigWindow::OnNMDblclkTreeConfig(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM hItem = m_tvConfig.GetSelectedItem();
	if (hItem)
	{
		if (m_tvConfig.ItemHasChildren(hItem))
		{
			return;
		}
		ShowVideo();
	}

	*pResult = 0;
}

void CLS_ConfigWindow::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BaseWindow::OnShowWindow(bShow, nStatus);

	if (FALSE == bShow && 0 == nStatus)
	{
		CloseVideo();
	}
}

void CLS_ConfigWindow::OnMainNotify( int _iLogonID,int _wParam, void* _iLParam, void* _iUser )
{
	if (m_pCurrent)
	{
		m_pCurrent->OnMainNotify(_iLogonID,_wParam,_iLParam,_iUser);
	}
}

void CLS_ConfigWindow::OnParamChangeNotify( int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUser )
{
	if (m_pCurrent)
	{
		m_pCurrent->OnParamChangeNotify(_iLogonID,_iChannelNo,_iParaType,_pPara,_iUser);
	}
}

void CLS_ConfigWindow::OnAlarmNotify( int _iLogonID, int _iChannelNo, int _iAlarmState,int _iAlarmType,int _iUser )
{
	if (m_pCurrent)
	{
		m_pCurrent->OnAlarmNotify(_iLogonID,_iChannelNo,_iAlarmState,_iAlarmType,_iUser);
	}
}

void CLS_ConfigWindow::ChangeCurrentPage()
{
	if(m_iCurrentPage == CONFIG_VCA_EVENTS)
	{		
		HTREEITEM hItem = m_tvConfig.GetSelectedItem();
		for(int i = 0; i < 3; i++)
		{
			hItem = m_tvConfig.GetNextItem(hItem,TVGN_PREVIOUS); 
		}
		m_tvConfig.Select(hItem,TVGN_CARET);
		m_tvConfig.SetFocus();
		ShowBasePage(CONFIG_VCA_TARGET);
	}
}
