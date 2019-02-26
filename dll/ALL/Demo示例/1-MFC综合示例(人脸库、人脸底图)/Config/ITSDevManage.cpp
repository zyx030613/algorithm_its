// ITSDevManage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ITSDevManage.h"


IMPLEMENT_DYNAMIC(CLS_ITSDevManage, CDialog)

CLS_ITSDevManage::CLS_ITSDevManage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ITSDevManage::IDD, pParent)
{
	m_iLogonId = -1;
	m_iChannelNo = -1;
	memset(m_iOrderId, 0, sizeof(m_iOrderId));
}

CLS_ITSDevManage::~CLS_ITSDevManage()
{
}

void CLS_ITSDevManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_BAYONET_DATA, m_chkPicDataEnable);
	DDX_Control(pDX, IDC_IPADDR_DEV_EDIT_IP, m_ipaddrDigitalChnIp);
	DDX_Control(pDX, IDC_CHECK_NVR_ANR, m_chkNvrAnrEnable);
	DDX_Control(pDX, IDC_EDIT_FTP_FILE_NAME, m_edtFtpFileName);
	DDX_Control(pDX, IDC_EDIT_FTP_PATH, m_edtFtpPath);
	DDX_Control(pDX, IDC_EDIT_FTP_USERNAME, m_edtFtpUserName);
	DDX_Control(pDX, IDC_EDIT_FTP_PASSWORD, m_edtFtpPassword);
}


BEGIN_MESSAGE_MAP(CLS_ITSDevManage, CDialog)
	ON_BN_CLICKED(IDC_BTN_HOST_NUM_SET, &CLS_ITSDevManage::OnBnClickedBtnHostNumSet)
	ON_BN_CLICKED(IDC_BTN_DEV_EDIT_SET, &CLS_ITSDevManage::OnBnClickedBtnDevEditSet)
	ON_BN_CLICKED(IDC_CHK_BAYONET_DATA, &CLS_ITSDevManage::OnBnClickedChkBayonetData)
	ON_BN_CLICKED(IDC_CHECK_NVR_ANR, &CLS_ITSDevManage::OnBnClickedCheckNvrAnr)
	ON_BN_CLICKED(IDC_BUTTON_FTP_SET, &CLS_ITSDevManage::OnBnClickedButtonFtpSet)
END_MESSAGE_MAP()

BOOL CLS_ITSDevManage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	((CEdit*)GetDlgItem(IDC_EDT_HOST_NUM))->SetLimitText(LEN_32);
	((CEdit*)GetDlgItem(IDC_EDT_DEV_EDIT_NUM))->SetLimitText(LEN_32);
	((CEdit*)GetDlgItem(IDC_EDT_DEV_EDIT_ID))->SetLimitText(LEN_64);
	((CEdit*)GetDlgItem(IDC_EDT_DEV_EDIT_NAME))->SetLimitText(LEN_32);

	m_edtFtpFileName.SetLimitText(LEN_64 - 1);
	m_edtFtpPath.SetLimitText(LEN_64 - 1);
	m_edtFtpUserName.SetLimitText(LEN_32 - 1);
	m_edtFtpPassword.SetLimitText(LEN_32- 1);

	UI_UpdateDialog();

	return TRUE;
}

void CLS_ITSDevManage::OnChannelChanged(int _iLogonID, int _iChannelNo, int /*_iStreamNo*/)
{
	m_iLogonId = _iLogonID;
	m_iChannelNo = (_iChannelNo < 0) ? 0 : _iChannelNo;
	
	UI_UpdateDialog();
	UI_UpdateHostId();
	UI_UpdateBayonetDataEnable();
	UI_UpdateDigitalChnIp();
	UI_UpdateDeviceNum();
	UI_UpdateNvrAnrEnable();
}

void CLS_ITSDevManage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ITSDevManage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STC_HOST_NUM, IDS_HOST_ID);
	SetDlgItemTextEx(IDC_GBO_SYS_CFG, IDS_SYSTEM_CONFIG);
	SetDlgItemTextEx(IDC_GBO_DEV_EDIT, IDS_DEV_CONFIG);
	SetDlgItemTextEx(IDC_CHK_BAYONET_DATA, IDS_BAYONET_DATA);
	SetDlgItemTextEx(IDC_STC_DEV_EDIT_IP, IDS_CONFIG_LAN_IP);
	SetDlgItemTextEx(IDC_STC_DEV_EDIT_NUM, IDS_CONFIG_ITS_DEVICENUM);
	SetDlgItemTextEx(IDC_STC_DEV_EDIT_ID, IDS_PLAYBACK_DEVICE_ID);
	SetDlgItemTextEx(IDC_STC_DEV_EDIT_NAME, IDS_CONFIG_LINK_DEV_NAME);
	SetDlgItemTextEx(IDC_BTN_HOST_NUM_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BTN_DEV_EDIT_SET, IDS_SET);
	SetDlgItemTextEx(IDC_CHECK_NVR_ANR, IDS_CONFIG_ITS_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_FTP_FILE_NAME, IDS_PLAYBACK_FILE_NAME);
	SetDlgItemTextEx(IDC_STATIC_FTP_PATH, IDS_ITS_FTP_PATH);
	SetDlgItemTextEx(IDC_STATIC_FTP_USERNAME, IDS_ITS_FTP_USERNAME);
	SetDlgItemTextEx(IDC_STATIC_FTP_PASSWORD, IDS_ITS_FTP_PASSWORD);
	SetDlgItemTextEx(IDC_BUTTON_FTP_SET, IDS_SET);
}

void CLS_ITSDevManage::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara, int _iUserData)
{
	switch(_iParaType)
	{
	case PARA_ITS_HOSTNUMBER:
		{
			UI_UpdateHostId();
		}
		break;
	case PARA_ITS_DEVICENUMBER:
		{
			UI_UpdateDeviceNum();
		}
		break;
	case PARA_CE_NVR_ANR:
		{
			UI_UpdateNvrAnrEnable();
		}
		break;
	default:
		break;
	}
}

void CLS_ITSDevManage::OnBnClickedBtnHostNumSet()
{
	if (m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonId);
		return;
	}

	int iRet = RET_FAILED;
	ITSHostNumber tITSHostNumber = {0};
	tITSHostNumber.iSize = sizeof(ITSHostNumber);
	GetDlgItem(IDC_EDT_HOST_NUM)->GetWindowText(tITSHostNumber.cHostNumber, sizeof(tITSHostNumber.cHostNumber) - 1);

	iRet = NetClient_SetITSExtraInfo(m_iLogonId, ITS_EXTRAINFO_CMD_HOSTNUMBER, m_iChannelNo, &tITSHostNumber, sizeof(ITSHostNumber));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo ITS_EXTRAINFO_CMD_HOSTNUMBER(%d£¬%d)",m_iLogonId, m_iChannelNo);
		goto EXIT_FUNC;
	}

	AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo ITS_EXTRAINFO_CMD_HOSTNUMBER(%d£¬%d)",m_iLogonId, m_iChannelNo);

EXIT_FUNC:
	return;
}

void CLS_ITSDevManage::OnBnClickedBtnDevEditSet()
{
	SetDeviceNum();		
}

void CLS_ITSDevManage::SetBayonetDataEnable()
{
	if (m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonId);
		return;
	}
	
	int iRet = RET_FAILED;
 	int iEnableValue = m_chkPicDataEnable.GetCheck();
	iRet = NetClient_SetCommonEnable(m_iLogonId, CI_COMMON_ID_ITS_PICSTREAM, m_iChannelNo, iEnableValue);
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetCommonEnable CI_COMMON_ID_ITS_PICSTREAM(%d£¬%d)",m_iLogonId, m_iChannelNo);
		goto EXIT_FUNC;
	}

	AddLog(LOG_TYPE_SUCC,"","NetClient_SetCommonEnable CI_COMMON_ID_ITS_PICSTREAM(%d£¬%d)",m_iLogonId, m_iChannelNo);

EXIT_FUNC:
	return;
}

void CLS_ITSDevManage::SetDeviceNum()
{
	if (m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonId);
		return;
	}

	int iRet = RET_FAILED;
	ITSDeviceNumber tITSDeviceNumber = {0};
	tITSDeviceNumber.iSize = sizeof(ITSDeviceNumber);	
	GetDlgItem(IDC_EDT_DEV_EDIT_NUM)->GetWindowText(tITSDeviceNumber.cDevNumber, LEN_32 - 1);
	GetDlgItem(IDC_EDT_DEV_EDIT_ID)->GetWindowText(tITSDeviceNumber.cDevID, LEN_64 - 1);
	GetDlgItem(IDC_EDT_DEV_EDIT_NAME)->GetWindowText(tITSDeviceNumber.cDevName, LEN_32 - 1);
	tITSDeviceNumber.iOrderId = m_iOrderId[m_iChannelNo];
	iRet = NetClient_SetITSExtraInfo(m_iLogonId, ITS_EXTRAINFO_CMD_DEVICENUMBER, m_iChannelNo, &tITSDeviceNumber, sizeof(ITSDeviceNumber));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo ITS_EXTRAINFO_CMD_DEVICENUMBER(%d£¬%d)",m_iLogonId, m_iChannelNo);
		goto EXIT_FUNC;
	}

	AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo ITS_EXTRAINFO_CMD_DEVICENUMBER(%d£¬%d)",m_iLogonId, m_iChannelNo);

EXIT_FUNC:
	return;
}

void CLS_ITSDevManage::UI_UpdateHostId()
{
	if (m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonId);
		return;
	}

	int iRet = RET_FAILED;
	ITSHostNumber tITSHostNumber = {0};
	tITSHostNumber.iSize = sizeof(ITSHostNumber);

	iRet = NetClient_GetITSExtraInfo(m_iLogonId, ITS_EXTRAINFO_CMD_HOSTNUMBER, m_iChannelNo, &tITSHostNumber, sizeof(ITSHostNumber));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo ITS_EXTRAINFO_CMD_HOSTNUMBER(%d£¬%d)",m_iLogonId, m_iChannelNo);
		goto EXIT_FUNC;
	}

	AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo ITS_EXTRAINFO_CMD_HOSTNUMBER(%d£¬%d)",m_iLogonId, m_iChannelNo);
	
	GetDlgItem(IDC_EDT_HOST_NUM)->SetWindowText(tITSHostNumber.cHostNumber);

EXIT_FUNC:
	return;

}

void CLS_ITSDevManage::UI_UpdateBayonetDataEnable()
{
	if (m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonId);
		return;
	}

	int iRet = RET_FAILED;
	int iEnableValue = 0;
	iRet = NetClient_GetCommonEnable(m_iLogonId, CI_COMMON_ID_ITS_PICSTREAM, m_iChannelNo, &iEnableValue);
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetCommonEnable CI_COMMON_ID_ITS_PICSTREAM(%d£¬%d)",m_iLogonId, m_iChannelNo);
		goto EXIT_FUNC;
	}

	AddLog(LOG_TYPE_SUCC,"","NetClient_SetCommonEnable CI_COMMON_ID_ITS_PICSTREAM(%d£¬%d)",m_iLogonId, m_iChannelNo);

	m_chkPicDataEnable.SetCheck(iEnableValue);

EXIT_FUNC:
	return;
}

void CLS_ITSDevManage::UI_UpdateDigitalChnIp()
{
	if (m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonId);
		return;
	}

	int iRet = RET_FAILED;
	TDigitalChannelParam tTDigitalChannelParam = {0};
	tTDigitalChannelParam.iChannel = m_iChannelNo;
	iRet = NetClient_GetDigitalChannelConfig(m_iLogonId, m_iChannelNo, DC_CMD_GET_ALL, &tTDigitalChannelParam, sizeof(TDigitalChannelParam));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDigitalChannelConfig DC_CMD_GET_ALL(%d£¬%d)",m_iLogonId, m_iChannelNo);
		goto EXIT_FUNC;
	}

	AddLog(LOG_TYPE_SUCC,"","NetClient_GetDigitalChannelConfig DC_CMD_GET_ALL(%d£¬%d)",m_iLogonId, m_iChannelNo);
	
	GetDlgItem(IDC_IPADDR_DEV_EDIT_IP)->SetWindowText(tTDigitalChannelParam.cIP);

EXIT_FUNC:
	return;
}

void CLS_ITSDevManage::UI_UpdateDeviceNum()
{
	if (m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonId);
		return;
	}

	int iRet = RET_FAILED;
	ITSDeviceNumber tITSDeviceNumber = {0};
	tITSDeviceNumber.iSize = sizeof(ITSDeviceNumber);

	iRet = NetClient_GetITSExtraInfo(m_iLogonId, ITS_EXTRAINFO_CMD_DEVICENUMBER, m_iChannelNo, &tITSDeviceNumber, sizeof(ITSDeviceNumber));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo ITS_EXTRAINFO_CMD_DEVICENUMBER(%d£¬%d)",m_iLogonId, m_iChannelNo);
		goto EXIT_FUNC;
	}

	AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo ITS_EXTRAINFO_CMD_DEVICENUMBER(%d£¬%d)",m_iLogonId, m_iChannelNo);

	GetDlgItem(IDC_EDT_DEV_EDIT_NUM)->SetWindowText(tITSDeviceNumber.cDevNumber);
	GetDlgItem(IDC_EDT_DEV_EDIT_ID)->SetWindowText(tITSDeviceNumber.cDevID);
	GetDlgItem(IDC_EDT_DEV_EDIT_NAME)->SetWindowText(tITSDeviceNumber.cDevName);
	if (m_iChannelNo >= 0 && m_iChannelNo < MAX_ITS_DEVICE_COUNT)
	{
		m_iOrderId[m_iChannelNo] = tITSDeviceNumber.iOrderId;
	}

EXIT_FUNC:
	return;
}


void CLS_ITSDevManage::OnBnClickedChkBayonetData()
{
	SetBayonetDataEnable();
}

void CLS_ITSDevManage::OnBnClickedCheckNvrAnr()
{
	int iEnableValue = m_chkNvrAnrEnable.GetCheck();
	int iRet = NetClient_SetCommonEnable(m_iLogonId, CI_COMMON_ID_NVR_ANR, PARAM_CHANNEL_ALL, iEnableValue);
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetCommonEnable CI_COMMON_ID_NVR_ANR(%d)",m_iLogonId);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetCommonEnable CI_COMMON_ID_NVR_ANR(%d)",m_iLogonId);
	}
}

void CLS_ITSDevManage::UI_UpdateNvrAnrEnable()
{
	int iEnableValue = -1;
	int iRet = NetClient_GetCommonEnable(m_iLogonId, CI_COMMON_ID_NVR_ANR, PARAM_CHANNEL_ALL, &iEnableValue);
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetCommonEnable CI_COMMON_ID_NVR_ANR(%d)",m_iLogonId);
	}
	else
	{
		m_chkNvrAnrEnable.SetCheck(iEnableValue);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetCommonEnable CI_COMMON_ID_NVR_ANR(%d)",m_iLogonId);
	}
}

void CLS_ITSDevManage::OnBnClickedButtonFtpSet()
{
	CString cstrFileName;
	CString cstrFtpPath;
	CString cstrFtpName;
	CString cstrFtpPwd;
	m_edtFtpFileName.GetWindowText(cstrFileName);
	m_edtFtpPath.GetWindowText(cstrFtpPath);
	m_edtFtpUserName.GetWindowText(cstrFtpName);
	m_edtFtpPassword.GetWindowText(cstrFtpPwd);

	HotBackupFtpInfo tInfo = {0};
	tInfo.iBufSize = sizeof(HotBackupFtpInfo);
	strcpy_s(tInfo.cFileName, LEN_64 - 1, cstrFileName.GetBuffer());
	strcpy_s(tInfo.cFtpPath, LEN_64 - 1, cstrFtpPath.GetBuffer());
	strcpy_s(tInfo.cFtpUserName, LEN_32 - 1, cstrFtpName.GetBuffer());
	strcpy_s(tInfo.cFtpPassword, LEN_32 - 1, cstrFtpPwd.GetBuffer());
	int iRet = NetClient_SendCommand(m_iLogonId, COMMAND_ID_HOTBACKUP_RECORDFILE, m_iChannelNo, &tInfo, sizeof(HotBackupFtpInfo));
	if (0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_SendCommand][COMMAND_ID_HOTBACKUP_RECORDFILE]");
	}
	else 
	{
		AddLog(LOG_TYPE_SUCC, "", "[NetClient_SendCommand][COMMAND_ID_HOTBACKUP_RECORDFILE]");
	}
}
