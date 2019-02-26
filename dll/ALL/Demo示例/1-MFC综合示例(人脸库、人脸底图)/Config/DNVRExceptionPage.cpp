// DNVRExceptionPage.cpp : implementation file
//

#include "stdafx.h"
#include "DNVRExceptionPage.h"


// CLS_DNVRExceptionPage dialog

IMPLEMENT_DYNAMIC(CLS_DNVRExceptionPage, CDialog)

CLS_DNVRExceptionPage::CLS_DNVRExceptionPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DNVRExceptionPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
}

CLS_DNVRExceptionPage::~CLS_DNVRExceptionPage()
{
}

void CLS_DNVRExceptionPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_DISKFULL, m_chkException[EXCEPTION_TYPE_DISK_FULL]);
	DDX_Control(pDX, IDC_CHECK_NODISK, m_chkException[EXCEPTION_TYPE_NO_DISK]);
	DDX_Control(pDX, IDC_CHECK_IOERROR, m_chkException[EXCEPTION_TYPE_DISK_IO_ERROR]);
	DDX_Control(pDX, IDC_CHECK_NOALLOWACCESS, m_chkException[EXCEPTION_TYPE_NOALLOW_ACCESS]);
	DDX_Control(pDX, IDC_CHECK_IPCOLLSION, m_chkException[EXCEPTION_TYPE_IP_COLLISION]);
	DDX_Control(pDX, IDC_CHECK_NETINTERRUPT, m_chkException[EXCEPTION_TYPE_NETWORK_INTERRUPT]);
	DDX_Control(pDX, IDC_CHECK_SYSTEM_BUSY, m_chkException[EXCEPTION_TYPE_SYSTEM_BUSY]);
	DDX_Control(pDX, IDC_CHECK_NO_REDUNDANCY_DISK, m_chkException[EXCEPTION_TYPE_NO_REDUNDANCY_DISK]);
	DDX_Control(pDX, IDC_CHECK_ABNORMAL_VOLTAGE, m_chkException[EXCEPTION_TYPE_ABNORMAL_VOLTAGE]);
	DDX_Control(pDX, IDC_CHECK_MAC_COLLISION, m_chkException[EXCEPTION_TYPE_MAC_COLLISION]);
	DDX_Control(pDX, IDC_CHECK_RAID_ABNORMAL, m_chkException[EXCEPTION_TYPE_RAID]);
	DDX_Control(pDX, IDC_CHECK_HOTBACKUP, m_chkException[EXCEPTION_TYPE_HOTBACKUP]);
	DDX_Control(pDX, IDC_CHECK_OVERLOAD, m_chkException[EXCEPTION_TYPE_OVERLOAD]);
	DDX_Control(pDX, IDC_CHECK_DISK_OVERLOAD, m_chkException[EXCEPTION_TYPE_DISK_OVERLOAD]);
	DDX_Control(pDX, IDC_CHECK_EXCEPTION_RECODE, m_chkException[EXCEPTION_TYPE_RECODE]);
	DDX_Control(pDX, IDC_CHECK_EXCEPTION_PASSOWRD_ULTRALIMIT, m_chkException[EXCEPTION_TYPE_PASSOWRD_ULTRALIMIT]);
	DDX_Control(pDX, IDC_CHECK_EXCEPTION_SMART, m_chkException[EXCEPTION_TYPE_SMART]);
	DDX_Control(pDX, IDC_CHECK_EXCEPTION_FTP_SERVER, m_chkException[EXCEPTION_TYPE_FTP_SERVER]);
	DDX_Control(pDX, IDC_CHECK_EXCEPTION_IO_CHIP, m_chkException[EXCEPTION_TYPE_IO_CHIP]);
	DDX_Control(pDX, IDC_CHECK_EXCEPTION_DISK_TEMPERATURE, m_chkException[EXCEPTION_TYPE_DISK_TEMPERATURE]);
	DDX_Control(pDX, IDC_CHECK_EXCEPTION_WATERGAUGE_CALIBRATION, m_chkException[EXCEPTION_TYPE_WATERGAUGE_CALIBRATION]);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_chkEnable);
	DDX_Control(pDX, IDC_CHECK_BELL, m_chkBell);
	DDX_Control(pDX, IDC_CHECK_NETCLIENT, m_chkNetClient);
	DDX_Control(pDX, IDC_BUTTON_EXCEPTIONHANDLE, m_btnExceptionHandle);
	DDX_Control(pDX, IDC_CHECK_ALLCHANNEL, m_chkAllChannel);
	DDX_Control(pDX, IDC_COMBO_ALARMTYPE, m_cboAlarmType);
	DDX_Control(pDX, IDC_BUTTON_ALARMCLEAR, m_btnAlarmClear);
	DDX_Control(pDX, IDC_COMBO_EXCEPTIONHANDLE, m_cboExceptionHandle);
	DDX_Control(pDX, IDC_CHK_DIALOG, m_chkShowDialog);
}


BEGIN_MESSAGE_MAP(CLS_DNVRExceptionPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_EXCEPTIONHANDLE, &CLS_DNVRExceptionPage::OnBnClickedButtonExceptionhandle)
	ON_BN_CLICKED(IDC_BUTTON_ALARMCLEAR, &CLS_DNVRExceptionPage::OnBnClickedButtonAlarmclear)
	ON_CBN_SELCHANGE(IDC_COMBO_EXCEPTIONHANDLE, &CLS_DNVRExceptionPage::OnCbnSelchangeComboExceptionhandle)
END_MESSAGE_MAP()


// CLS_DNVRExceptionPage message handlers
BOOL CLS_DNVRExceptionPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	for (int i = 0; i < 6; i++)
	{
		if (NULL == m_chkException[i])
		{
			continue;
		}
		m_chkException[i].SetCheck(BST_UNCHECKED);
	}
	m_chkEnable.SetCheck(BST_UNCHECKED);
	m_chkShowDialog.SetCheck(BST_CHECKED);
	m_chkBell.SetCheck(BST_UNCHECKED);
	m_chkNetClient.SetCheck(BST_UNCHECKED);
	m_chkAllChannel.SetCheck(BST_UNCHECKED);
	
	UI_UpdateDialog();

	m_cboExceptionHandle.SetCurSel(0);
	m_cboAlarmType.SetCurSel(0);
	return TRUE;
}

void CLS_DNVRExceptionPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
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

	UI_UpdateExceptionHandle();
	UI_UpdateExceptionMsg();
}

void CLS_DNVRExceptionPage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_DNVRExceptionPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_EXCEPTIONMESSAGE,IDS_CONFIG_DNVR_EXCEPTIONMESSAGE);
	SetDlgItemTextEx(IDC_CHECK_DISKFULL,IDS_CONFIG_DNVR_DISKFULL);
	SetDlgItemTextEx(IDC_CHECK_NODISK,IDS_CONFIG_DNVR_NODISK);
	SetDlgItemTextEx(IDC_CHECK_IOERROR,IDS_CONFIG_DNVR_IOERROR);
	SetDlgItemTextEx(IDC_CHECK_NOALLOWACCESS,IDS_CONFIG_DNVR_NOALLOWACCES);
	SetDlgItemTextEx(IDC_CHECK_IPCOLLSION,IDS_CONFIG_DNVR_IPCOLLSION);
	SetDlgItemTextEx(IDC_CHECK_NETINTERRUPT,IDS_CONFIG_DNVR_NETINTERRUPT);
	SetDlgItemTextEx(IDC_CHECK_SYSTEM_BUSY,IDS_CONFIG_DNVR_SYSTEM_BUSY);
	SetDlgItemTextEx(IDC_CHECK_NO_REDUNDANCY_DISK,IDS_CONFIG_DNVR_NO_REDUNDANCY_DISK);
	SetDlgItemTextEx(IDC_CHECK_ABNORMAL_VOLTAGE,IDS_CONFIG_DNVR_VOLTAGE_EXCEPTION);
	SetDlgItemTextEx(IDC_CHECK_MAC_COLLISION,IDS_CONFIG_DNVR_MAC_CONFLICT);
	SetDlgItemTextEx(IDC_CHECK_RAID_ABNORMAL,IDS_CONFIG_DNVR_ARRAY_EXCEPTION);
	SetDlgItemTextEx(IDC_CHECK_HOTBACKUP,IDS_CONFIG_DNVR_SPARING_EXCEPTION);
	SetDlgItemTextEx(IDC_CHECK_OVERLOAD,IDS_CONFIG_DNVR_PSE_POWER_OVERLOAD);
	SetDlgItemTextEx(IDC_CHECK_DISK_OVERLOAD,IDS_CONFIG_DNVR_DISK_OVERLOAD);
	SetDlgItemTextEx(IDC_CHECK_EXCEPTION_RECODE,IDS_EXCEPTION_RECORD);
	SetDlgItemTextEx(IDC_CHECK_EXCEPTION_PASSOWRD_ULTRALIMIT, IDS_EXCEPTION_PASSOWRD_ULTRALIMIT);
	SetDlgItemTextEx(IDC_CHECK_EXCEPTION_SMART, IDS_EXCEPTION_DISK_SMART);
	SetDlgItemTextEx(IDC_CHECK_EXCEPTION_FTP_SERVER, IDS_EXCEPTION_FTP_SERVER);
	SetDlgItemTextEx(IDC_CHECK_EXCEPTION_IO_CHIP, IDS_EXCEPTION_IO_CHIP);
	SetDlgItemTextEx(IDC_CHECK_EXCEPTION_DISK_TEMPERATURE, IDS_EXCEPTION_DISK_TEMPERATURE);
	SetDlgItemTextEx(IDC_CHECK_EXCEPTION_WATERGAUGE_CALIBRATION, IDS_EXCEPTION_WATERGAUGE_CALIBRATION);

	SetDlgItemTextEx(IDC_CHECK_ENABLE,IDS_CONFIG_FTP_SNAPSHOT_ENABLE);
	SetDlgItemTextEx(IDC_CHK_DIALOG, IDS_CONFIG_DNVR_DIALOG);
	SetDlgItemTextEx(IDC_CHECK_BELL,IDS_CONFIG_DNVR_BELL);
	SetDlgItemTextEx(IDC_CHECK_NETCLIENT,IDS_CONFIG_DNVR_NETCLIENT);
	SetDlgItemTextEx(IDC_STATIC_EXCEPTIONHANDLE1,IDS_CONFIG_DNVR_EXCEPTIONHANDLE);
	SetDlgItemTextEx(IDC_STATIC_EXCEPTIONHANDLE,IDS_CONFIG_DNVR_EXCEPTIONHANDLE);
	SetDlgItemTextEx(IDC_BUTTON_EXCEPTIONHANDLE,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_ALARMCLEAR,IDS_CONFIG_DNVR_ALARMCLEAR);
	SetDlgItemTextEx(IDC_CHECK_ALLCHANNEL,IDS_CONFIG_DNVR_ALLCHANNEL);
	SetDlgItemTextEx(IDC_BUTTON_ALARMCLEAR,IDS_CONFIG_DNVR_ALARMCLEAR);

	InsertString(m_cboExceptionHandle,0,IDS_CONFIG_DNVR_DISKFULL);
	InsertString(m_cboExceptionHandle,1,IDS_CONFIG_DNVR_NODISK);
	InsertString(m_cboExceptionHandle,2,IDS_CONFIG_DNVR_IOERROR);
	InsertString(m_cboExceptionHandle,3,IDS_CONFIG_DNVR_NOALLOWACCES);
	InsertString(m_cboExceptionHandle,4,IDS_CONFIG_DNVR_IPCOLLSION);
	InsertString(m_cboExceptionHandle,5,IDS_CONFIG_DNVR_NETINTERRUPT);
	InsertString(m_cboExceptionHandle,6,IDS_CONFIG_DNVR_SYSTEM_BUSY);
	InsertString(m_cboExceptionHandle,7,IDS_CONFIG_DNVR_NO_REDUNDANCY_DISK);
	InsertString(m_cboExceptionHandle,8,IDS_CONFIG_DNVR_VOLTAGE_EXCEPTION);
	InsertString(m_cboExceptionHandle,9,IDS_CONFIG_DNVR_MAC_CONFLICT);
	InsertString(m_cboExceptionHandle,10,IDS_CONFIG_DNVR_ARRAY_EXCEPTION );
	InsertString(m_cboExceptionHandle,11,IDS_CONFIG_DNVR_SPARING_EXCEPTION);
	InsertString(m_cboExceptionHandle,12,IDS_CONFIG_DNVR_PSE_POWER_OVERLOAD);
	InsertString(m_cboExceptionHandle,13,IDS_CONFIG_DNVR_DISK_OVERLOAD);
	InsertString(m_cboExceptionHandle,14,IDS_EXCEPTION_RECORD);
	InsertString(m_cboExceptionHandle,15,IDS_EXCEPTION_PASSOWRD_ULTRALIMIT);
	InsertString(m_cboExceptionHandle,16,IDS_EXCEPTION_DISK_SMART);
	InsertString(m_cboExceptionHandle,17,IDS_EXCEPTION_FTP_SERVER);
	InsertString(m_cboExceptionHandle,18,IDS_EXCEPTION_IO_CHIP);
	InsertString(m_cboExceptionHandle,19,IDS_EXCEPTION_DISK_TEMPERATURE);
	InsertString(m_cboExceptionHandle,20,IDS_EXCEPTION_WATERGAUGE_CALIBRATION);

	InsertString(m_cboAlarmType,0,IDS_CONFIG_DNVR_VIDEOLOST);
	InsertString(m_cboAlarmType,1,IDS_CONFIG_DNVR_PORTALARM);
	InsertString(m_cboAlarmType,2,IDS_CONFIG_DNVR_MOTIONDETECT);
	InsertString(m_cboAlarmType,3,IDS_CONFIG_DNVR_VIDEOCOVER);
	InsertString(m_cboAlarmType,4,IDS_CONFIG_DVR_VCA);
	InsertString(m_cboAlarmType,5,IDS_CONFIG_DVR_AUDIO_LOST);
	InsertString(m_cboAlarmType,6,IDS_CONFIG_DVR_TEMPERATURE);
	InsertString(m_cboAlarmType,7,IDS_CONFIG_DNVR_EXCEPTION);
	InsertString(m_cboAlarmType,8,IDS_CONFIG_DNVR_CREATEFREEV0);
	InsertString(m_cboAlarmType,9,IDS_CONFIG_DNVR_ALL);
}

BOOL CLS_DNVRExceptionPage::UI_UpdateExceptionHandle()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iExceptionType = m_cboExceptionHandle.GetCurSel();
	//新扩了一个字段，6时为系统忙异常，为了不改变结构
	//当遍历到第6个的时候，直接赋上7，获取的也就是冗余的内容，保持一致 
	if (iExceptionType >= 6)
	{
		iExceptionType++;
	}
	int iFlag = 0;
	int iRet = NetClient_GetExceptionHandleParam(m_iLogonID, iExceptionType, &iFlag);
	if (0 == iRet)
	{
		if (EXCEPTION_HANDLE_ENABLE == (iFlag & EXCEPTION_HANDLE_ENABLE))
		{
			m_chkEnable.SetCheck(BST_CHECKED);
		}
		else
		{
			m_chkEnable.SetCheck(BST_UNCHECKED);
		}
		if (EXCEPTION_HANDLE_DIALOG == (iFlag & EXCEPTION_HANDLE_DIALOG))
		{
			m_chkShowDialog.SetCheck(BST_CHECKED);
		}
		else
		{
			m_chkShowDialog.SetCheck(BST_UNCHECKED);
		}
		if (EXCEPTION_HANDLE_LINK_BELL == (iFlag & EXCEPTION_HANDLE_LINK_BELL))
		{
			m_chkBell.SetCheck(BST_CHECKED);
		}
		else
		{
			m_chkBell.SetCheck(BST_UNCHECKED);
		}
		if (EXCEPTION_HANDLE_LINK_NETCLIENT == (iFlag & EXCEPTION_HANDLE_LINK_NETCLIENT))
		{
			m_chkNetClient.SetCheck(BST_CHECKED);
		}
		else
		{
			m_chkNetClient.SetCheck(BST_UNCHECKED);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetExceptionHandleParam(%d,%d,%d)",m_iLogonID, iExceptionType, iFlag);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetExceptionHandleParam(%d,%d,%d)",m_iLogonID, iExceptionType, iFlag);
	}
	return TRUE;
}
void CLS_DNVRExceptionPage::OnBnClickedButtonExceptionhandle()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iExceptionType = m_cboExceptionHandle.GetCurSel();
	int iFlag = 0;
	if (BST_CHECKED == m_chkEnable.GetCheck())
	{
		iFlag = iFlag | EXCEPTION_HANDLE_ENABLE;
	}
	if (BST_CHECKED == m_chkShowDialog.GetCheck())
	{
		iFlag = iFlag | EXCEPTION_HANDLE_DIALOG;
	}
	if (BST_CHECKED == m_chkBell.GetCheck())
	{
		iFlag = iFlag | EXCEPTION_HANDLE_LINK_BELL;
	}
	if (BST_CHECKED == m_chkNetClient.GetCheck())
	{
		iFlag = iFlag | EXCEPTION_HANDLE_LINK_NETCLIENT;
	}
	// 新扩字段到12，PSE功耗超负荷	
	int iRet = NetClient_SetExceptionHandleParam(m_iLogonID, iExceptionType, iFlag);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetExceptionHandleParam(%d,%d,%d)",m_iLogonID, iExceptionType, iFlag);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetExceptionHandleParam(%d,%d,%d)",m_iLogonID, iExceptionType, iFlag);
	}
}

void CLS_DNVRExceptionPage::OnBnClickedButtonAlarmclear()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iChannel = m_iChannelNo;
	int iClearType = m_cboAlarmType.GetCurSel();
	if(7 == iClearType)
	{
		iClearType = ALARM_TYPE_EXCPETION;
	}
	else if (8 == iClearType)
	{
		iClearType = ALARM_TYPE_ALL;
	}

	if (iChannel < 0)
	{
		return;
	}

	if (m_chkAllChannel.GetCheck())
	{
		iChannel = 255;
	}
	int iRet = NetClient_SetAlarmClear(m_iLogonID, iChannel, iClearType);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetAlarmClear(%d,%d,%d)",m_iLogonID, iChannel, iClearType);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetAlarmClear(%d,%d,%d)",m_iLogonID, iChannel, iClearType);
	}
}

void CLS_DNVRExceptionPage::OnCbnSelchangeComboExceptionhandle()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iExceptionType = m_cboExceptionHandle.GetCurSel();
	////新扩了一个字段，6时为系统忙异常，为了不改变结构
	////当遍历到第6个的时候，直接赋上7，获取的也就是冗余的内容，保持一致 
	//if (iExceptionType >= 6)
	//{
	//	iExceptionType++;
	//}
	int iFlag = 0;
	int iRet = NetClient_GetExceptionHandleParam(m_iLogonID, iExceptionType, &iFlag);
	if (0 == iRet)
	{
		if (EXCEPTION_HANDLE_ENABLE == (iFlag & EXCEPTION_HANDLE_ENABLE))
		{
			m_chkEnable.SetCheck(BST_CHECKED);
		}
		else
		{
			m_chkEnable.SetCheck(BST_UNCHECKED);
		}
		if (EXCEPTION_HANDLE_DIALOG == (iFlag & EXCEPTION_HANDLE_DIALOG))
		{
			m_chkShowDialog.SetCheck(BST_CHECKED);
		}
		else
		{
			m_chkShowDialog.SetCheck(BST_UNCHECKED);
		}
		if (EXCEPTION_HANDLE_LINK_BELL == (iFlag & EXCEPTION_HANDLE_LINK_BELL))
		{
			m_chkBell.SetCheck(BST_CHECKED);
		}
		else
		{
			m_chkBell.SetCheck(BST_UNCHECKED);
		}
		if (EXCEPTION_HANDLE_LINK_NETCLIENT == (iFlag & EXCEPTION_HANDLE_LINK_NETCLIENT))
		{
			m_chkNetClient.SetCheck(BST_CHECKED);
		}
		else
		{
			m_chkNetClient.SetCheck(BST_UNCHECKED);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetExceptionHandleParam(%d,%d,%d)",m_iLogonID, iExceptionType, iFlag);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetExceptionHandleParam(%d,%d,%d)",m_iLogonID, iExceptionType, iFlag);
	}
}

void CLS_DNVRExceptionPage::UI_UpdateExceptionMsg()
{
	if (m_iLogonID < 0)
	{
		return;
	}
	int iState = 0;
	for (int i = EXCEPTION_TYPE_DISK_FULL; i <EXCEPTION_TYPE_MAX; i++)
	{
		iState = 0;
		int iRet = NetClient_GetExceptionMsg(m_iLogonID, i, &iState);
		if (iRet == 0)
		{
			if (NULL == m_chkException[i])
			{
				continue;
			}
			m_chkException[i].SetCheck(iState);
		}
	}	
}

void CLS_DNVRExceptionPage::OnParamChangeNotify( int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData )
{
	if (_iParaType == PARA_EXCEPTION)
	{
		UI_UpdateExceptionMsg();
	}
}
