// ItsSystemParam3.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ItsSystemParam3.h"


// CLS_ItsSystemParam3 对话框

IMPLEMENT_DYNAMIC(CLS_ItsSystemParam3, CDialog)

CLS_ItsSystemParam3::CLS_ItsSystemParam3(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ItsSystemParam3::IDD, pParent)
{

}

CLS_ItsSystemParam3::~CLS_ItsSystemParam3()
{
}

void CLS_ItsSystemParam3::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GP_DEVICE_NUMBER, m_gpDeviceNumber);
	DDX_Control(pDX, IDC_STC_DEVICE_NUMBER, m_stcDeviceNumber);
	DDX_Control(pDX, IDC_EDT_DEVICE_NUMBER, m_edtDeviceNumber);
	DDX_Control(pDX, IDC_BTN_DEVICE_NUMBER, m_btnDeviceNumber);
	DDX_Control(pDX, IDC_GP_ORGAN_MESSAGE, m_gpOrganMessage);
	DDX_Control(pDX, IDC_STC_ORGAN_CODE, m_stcOrganCode);
	DDX_Control(pDX, IDC_EDT_ORGAN_CODE, m_edtOrganCode1);
	DDX_Control(pDX, IDC_BTN_SET_CODE, m_btnOrganCode);
	DDX_Control(pDX, IDC_GP_CAPTURE, m_gpCapture);
	DDX_Control(pDX, IDC_STC_CHANNEL_NUMBER, m_stcChannelNumner);
	DDX_Control(pDX, IDC_CBO_CHANNEL_NUMBER, m_cboChannelNumber);
	DDX_Control(pDX, IDC_STC_CAPTURE_MODE, m_stcCaptureMode);
	DDX_Control(pDX, IDC_CBO_CAPTURE_MODE, m_cboCaptureMode);
	DDX_Control(pDX, IDC_STC_PICTURE_QUALITY, m_stcPictureQuality);
	DDX_Control(pDX, IDC_EDT_PICTURE_QUALITY, m_edtPictureQuality);
	DDX_Control(pDX, IDC_STC_TIME, m_stcTime);
	DDX_Control(pDX, IDC_EDT_TIME, m_edtTime);
	DDX_Control(pDX, IDC_STC_PICTURE_SIZE, m_stcPictureSize);
	DDX_Control(pDX, IDC_STC_PICTURE_NUMBER, m_stcPictureNumber);
	DDX_Control(pDX, IDC_EDT_PICTURE_NUMBER, m_edtPictureNumber);
	DDX_Control(pDX, IDC_EDT_PICTURE_SIZE, m_edtPictureSize);
	DDX_Control(pDX, IDC_BTN_SET_CAPTURE, m_btnSetCapture);
	DDX_Control(pDX, IDC_GP_SECURITY_CODE, m_gpSecurityCode);
	DDX_Control(pDX, IDC_STC_START_BIT, m_stcStartBit);
	DDX_Control(pDX, IDC_EDT_START_BIT, m_edtStartBit);
	DDX_Control(pDX, IDC_STC_LENGTH, m_stcLength);
	DDX_Control(pDX, IDC_EDT_LENGTH, m_edtLength);
	DDX_Control(pDX, IDC_BTN_SET_SECURITY_CODE, m_btnSetSecurityCode);
	DDX_Control(pDX, IDC_STC__DEVICE_TYPE_NUMBER, m_stcDeviceTypeNumber);
	DDX_Control(pDX, IDC_CBO_DEVICE_TYPE, m_cboDeviceType);
}


BEGIN_MESSAGE_MAP(CLS_ItsSystemParam3, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_SET_CAPTURE, &CLS_ItsSystemParam3::OnBnClickedBtnSetCapture)
	ON_BN_CLICKED(IDC_BTN_SET_CODE, &CLS_ItsSystemParam3::OnBnClickedBtnSetCode)
	ON_BN_CLICKED(IDC_BTN_SET_SECURITY_CODE, &CLS_ItsSystemParam3::OnBnClickedBtnSetSecurityCode)
	ON_BN_CLICKED(IDC_BTN_DEVICE_NUMBER, &CLS_ItsSystemParam3::OnBnClickedBtnDeviceNumber)
	ON_CBN_SELCHANGE(IDC_CBO_CHANNEL_NUMBER, &CLS_ItsSystemParam3::OnCbnSelchangeCboChannelNumber)
	ON_CBN_SELCHANGE(IDC_CBO_CAPTURE_MODE, &CLS_ItsSystemParam3::OnCbnSelchangeCboCaptureMode)
END_MESSAGE_MAP()


// CLS_ItsSystemParam3 消息处理程序

BOOL CLS_ItsSystemParam3::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	int i = 0;
	CString csCboSelectRoad[] = {"0","1","2","3"};
	for(i = 0;i < 4;i++)
	{
		InsertString(m_cboChannelNumber, i, csCboSelectRoad[i]);
	}
	UI_UpdateDialog();
	//UI_UpdateData();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLS_ItsSystemParam3::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	if(_iChannelNo < 0)
	{
		m_iChannel = 0;
	}
	else
	{
		m_iChannel = _iChannelNo;
	}
	UI_UpdateDialog();
}

void CLS_ItsSystemParam3::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();

}

void CLS_ItsSystemParam3::UI_UpdateData1()
{
	ITS_CamLocationEx tSetDeviceType = {0};
	int iRet1 = NetClient_GetITSExtraInfo(m_iLogonID, ITS_CAMLOCATION_CMD_GET, m_iChannel, &tSetDeviceType, sizeof(ITS_CamLocationEx));
	if (0 == iRet1)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_CAMLOCATION_CMD_GET](%d, %d)",m_iLogonID, m_iChannel);
		m_cboDeviceType.SetCurSel(tSetDeviceType.iDeviceType);
		GetDlgItem(IDC_EDT_DEVICE_NUMBER)->SetWindowText((LPSTR)(tSetDeviceType.tITS_CamLocation.cDeviceVode));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_CAMLOCATION_CMD_GET] (%d, %d),error(%d)",m_iLogonID, m_iChannel, GetLastError());
	}
}

void CLS_ItsSystemParam3::UI_UpdateData2()
{
	ITS_DevCommonInfo tRecieve = {0};
	int iBufLength = 0;
	int iLength = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_ITS_DEV_COMMONINFO, m_iChannel, &tRecieve, iBufLength, &iLength);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_ITS_DEV_COMMONINFO](%d, %d)",m_iLogonID, m_iChannel);
		GetDlgItem(IDC_EDT_ORGAN_CODE)->SetWindowText((LPSTR)(tRecieve.cCommonInfo));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_ITS_DEV_COMMONINFO] (%d, %d),error(%d)",m_iLogonID, m_iChannel, GetLastError());
	}
}

void CLS_ItsSystemParam3::UI_UpdateData3()
{
	FtpSnapshot tRecieveCapture = {0};
	tRecieveCapture.iChannelNo = m_cboChannelNumber.GetCurSel();
	tRecieveCapture.iType = m_cboCaptureMode.GetCurSel();
	int iRet = NetClient_GetFTPUploadConfig(m_iLogonID, FTP_COMMON_CMD_SNAPSHOT_EX, &tRecieveCapture, sizeof(FtpSnapshot));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetFTPUploadConfig[FTP_COMMON_CMD_SNAPSHOT_EX](%d, %d)",m_iLogonID, m_iChannel);
		/*m_cboChannelNumber.SetCurSel(tRecieveCapture.iChannelNo);
		m_cboCaptureMode.SetCurSel(tRecieveCapture.iType);*/
		SetDlgItemInt(IDC_EDT_PICTURE_NUMBER, tRecieveCapture.iPicCount);
		SetDlgItemInt(IDC_EDT_PICTURE_SIZE, tRecieveCapture.iPictureSize);
		SetDlgItemInt(IDC_EDT_PICTURE_QUALITY, tRecieveCapture.iQValue);
		GetDlgItem(IDC_EDT_TIME)->SetWindowText((LPSTR)(tRecieveCapture.cInterval));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetFTPUploadConfig[FTP_COMMON_CMD_SNAPSHOT_EX] (%d, %d),error(%d)",m_iLogonID, m_iChannel, GetLastError());
	}
}

void CLS_ItsSystemParam3::UI_UpdateData4()
{
	ITS_SecurityCode tRecieveSecurity = {0};
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_SECURITYCODE_CMD_GET, m_iChannel, &tRecieveSecurity, sizeof(ITS_SecurityCode));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_SECURITYCODE_CMD_GET](%d, %d)",m_iLogonID, m_iChannel);
		SetDlgItemInt(IDC_EDT_START_BIT, tRecieveSecurity.iPos + 1);
		SetDlgItemInt(IDC_EDT_LENGTH, tRecieveSecurity.iCount);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_SECURITYCODE_CMD_GET] (%d, %d),error(%d)",m_iLogonID, m_iChannel, GetLastError());
	}
}

void CLS_ItsSystemParam3::UI_UpdateDialog()
{
	InsertString(m_cboCaptureMode,0,IDS_ITS_NOT_ENABLE);
	InsertString(m_cboCaptureMode,1,IDS_ENABLE_TIME);
	InsertString(m_cboCaptureMode,2,IDS_CONFIG_FTP_SNAPSHOT_LINKAGESEND);
	InsertString(m_cboCaptureMode,3,IDS_ITS_NOTES);
	InsertString(m_cboCaptureMode,4,IDS_ITS_MANY_CAPTURE);
	InsertString(m_cboDeviceType,0,IDS_ITS_DEVICE_OF_RED_TRAFFIC_LIGHT);
	InsertString(m_cboDeviceType,1,IDS_ITS_SPEED_MEASUREMENT);
	SetDlgItemTextEx(IDC_GP_ORGAN_MESSAGE,IDS_ITS_ORGAN_CODE);
	SetDlgItemTextEx(IDC_STC_ORGAN_CODE, IDS_ITS_ORGAN_CODE);
	SetDlgItemTextEx(IDC_BTN_SET_CODE, IDS_SET);
	SetDlgItemTextEx(IDC_GP_CAPTURE, IDS_ITS_SIMULATION_TRIGGER_CAPTURE);
	SetDlgItemTextEx(IDC_STC_PICTURE_NUMBER, IDS_ITS_PICTURE_NUMBER);
	SetDlgItemTextEx(IDC_STC_PICTURE_QUALITY, IDS_ITS_PICTURE_QUALITY);
	SetDlgItemTextEx(IDC_STC_PICTURE_SIZE, IDS_ITS_PICTURE_SIZE);
	SetDlgItemTextEx(IDC_STC_CHANNEL_NUMBER, IDS_ITS_CHANNEL_NUMBER);
	SetDlgItemTextEx(IDC_STC_CAPTURE_MODE, IDS_ITS_TRIGGER_MODE);
	SetDlgItemTextEx(IDC_BTN_SET_CAPTURE, IDS_SET);
	SetDlgItemTextEx(IDC_STC_TIME,IDS_ITS_TIME);
	SetDlgItemTextEx(IDC_GP_SECURITY_CODE, IDS_ITS_SECURITY_CODE);
	SetDlgItemTextEx(IDC_STC_START_BIT, IDS_ITS_START_BIT);
	SetDlgItemTextEx(IDC_STC_LENGTH, IDS_ITS_LENGTH);
	SetDlgItemTextEx(IDC_BTN_SET_SECURITY_CODE, IDS_SET);
	SetDlgItemTextEx(IDC_GP_DEVICE_NUMBER, IDS_ITS_DEVICE_NUMBER);
	SetDlgItemTextEx(IDC_STC_DEVICE_NUMBER, IDS_ITS_DEVICE_NUMBER);
	SetDlgItemTextEx(IDC_STC__DEVICE_TYPE_NUMBER, IDS_ITS_DEVICE_TYPE);
	SetDlgItemTextEx(IDC_BTN_DEVICE_NUMBER, IDS_SET);
	UI_UpdateData1();
	UI_UpdateData2();
	UI_UpdateData3();
	UI_UpdateData4();
	UI_UpdateCode();
}

void CLS_ItsSystemParam3::OnBnClickedBtnSetCapture()
{
	if(m_iLogonID >= 0)
	{
		FtpSnapshot tSetCapture = {0};
		tSetCapture.iSize = sizeof(FtpSnapshot);
		tSetCapture.iChannelNo = m_cboChannelNumber.GetCurSel();
		tSetCapture.iType = m_cboCaptureMode.GetCurSel();
		tSetCapture.iPicCount = GetDlgItemInt(IDC_EDT_PICTURE_NUMBER);
		if(tSetCapture.iPicCount > 5)
		{
			tSetCapture.iPicCount = 5;
		}
		else if((tSetCapture.iPicCount < 0) && (tSetCapture.iType != 4))
		{
			tSetCapture.iPicCount = 0;
		}
		else if(((tSetCapture.iPicCount < 1) && (tSetCapture.iType == 4)))
		{
			tSetCapture.iPicCount = 1;
		}
		tSetCapture.iPictureSize = GetDlgItemInt(IDC_EDT_PICTURE_SIZE);
		tSetCapture.iQValue = GetDlgItemInt(IDC_EDT_PICTURE_QUALITY);
		GetDlgItem(IDC_EDT_TIME)->GetWindowText((LPSTR)(tSetCapture.cInterval),LEN_16);
		int iRet = NetClient_SetFTPUploadConfig(m_iLogonID, FTP_COMMON_CMD_SNAPSHOT_EX, &tSetCapture, sizeof(FtpSnapshot));
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetFTPUploadConfig[FTP_COMMON_CMD_SNAPSHOT_EX](%d, %d)",m_iLogonID, m_iChannel);
		} 
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetFTPUploadConfig[FTP_COMMON_CMD_SNAPSHOT_EX] (%d, %d),error(%d)",m_iLogonID, m_iChannel, GetLastError());
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","iLogonId or iChannel ERROR (%d, %d),error(%d)",m_iLogonID, m_iChannel, GetLastError());
	}
}

void CLS_ItsSystemParam3::OnBnClickedBtnSetCode()
{
	if ( m_iLogonID >= 0)
	{
		ITS_DevCommonInfo tSetOrgan = {0};
		tSetOrgan.iSize = sizeof(ITS_DevCommonInfo);
		tSetOrgan.iType = ORGAN_CODE;
		GetDlgItem(IDC_EDT_ORGAN_CODE)->GetWindowText((LPSTR)(tSetOrgan.cCommonInfo),LEN_64);
		int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_ITS_DEV_COMMONINFO, m_iChannel, &tSetOrgan, sizeof(ITS_DevCommonInfo));
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_ITS_DEV_COMMONINFO](%d, %d)",m_iLogonID, m_iChannel);
		} 
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_ITS_DEV_COMMONINFO] (%d, %d),error(%d)",m_iLogonID, m_iChannel, GetLastError());
		}
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","iLogonId or iChannel ERROR (%d, %d),error(%d)",m_iLogonID, m_iChannel, GetLastError());
	}
}

void CLS_ItsSystemParam3::UI_UpdateCode()
{
	ITS_DevCommonInfo tSetOrgan = {0};
	tSetOrgan.iSize = sizeof(ITS_DevCommonInfo);
	tSetOrgan.iType = ORGAN_CODE;
	int iBytesReturned = 0;
	int iRet =  NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_ITS_DEV_COMMONINFO, m_iChannel, &tSetOrgan, sizeof(ITS_DevCommonInfo), &iBytesReturned);
	if(iRet == 0)
	{
		GetDlgItem(IDC_EDT_ORGAN_CODE)->SetWindowText((LPSTR)(tSetOrgan.cCommonInfo));
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetDevConfig[NET_CLIENT_ITS_DEV_COMMONINFO](%de,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_GetDevConfig[NET_CLIENT_ITS_DEV_COMMONINFO](%de,%d), error(%d)", m_iLogonID, m_iChannel,GetLastError());
	}
}

void CLS_ItsSystemParam3::OnBnClickedBtnSetSecurityCode()
{
	if (m_iChannel >= 0 && m_iLogonID >= 0)
	{
		ITS_SecurityCode tSetSecurityCode = {0};
		tSetSecurityCode.iBufSize = sizeof(ITS_SecurityCode);
		tSetSecurityCode.iPos = GetDlgItemInt(IDC_EDT_START_BIT) - 1;
		tSetSecurityCode.iCount = GetDlgItemInt(IDC_EDT_LENGTH);
		int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_SECURITYCODE_CMD_SET, m_iChannel, &tSetSecurityCode, sizeof(ITS_SecurityCode));
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_SECURITYCODE_CMD_SET](%d, %d)",m_iLogonID, m_iChannel);
		} 
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_SECURITYCODE_CMD_SET] (%d, %d),error(%d)",m_iLogonID, m_iChannel, GetLastError());
		}
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","iLogonId or iChannel ERROR (%d, %d),error(%d)",m_iLogonID, m_iChannel, GetLastError());
	}
}

void CLS_ItsSystemParam3::OnBnClickedBtnDeviceNumber()
{
	if ( m_iLogonID >= 0)
	{
		ITS_CamLocationEx tSetDeviceType = {0};
		int iRet1 = NetClient_GetITSExtraInfo(m_iLogonID, ITS_CAMLOCATION_CMD_GET, m_iChannel, &tSetDeviceType, sizeof(ITS_CamLocationEx));
		if (0 == iRet1)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_CAMLOCATION_CMD_GET](%d, %d)",m_iLogonID, m_iChannel);
			tSetDeviceType.iDeviceType = m_cboDeviceType.GetCurSel();
			GetDlgItem(IDC_EDT_DEVICE_NUMBER)->GetWindowText((LPSTR)(tSetDeviceType.tITS_CamLocation.cDeviceVode),LEN_64);
			int iRet2 = NetClient_SetITSExtraInfo(m_iLogonID, ITS_CAMLOCATION_CMD_SET, m_iChannel, &tSetDeviceType, sizeof(ITS_CamLocationEx));
			if (0 == iRet2)
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_CAMLOCATION_CMD_SET](%d, %d)",m_iLogonID, m_iChannel);
			} 
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_CAMLOCATION_CMD_SET] (%d, %d),error(%d)",m_iLogonID, m_iChannel, GetLastError());
			}
		} 
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_CAMLOCATION_CMD_GET] (%d, %d),error(%d)",m_iLogonID, m_iChannel, GetLastError());
		}
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","iLogonId or iChannel ERROR (%d, %d),error(%d)",m_iLogonID, m_iChannel, GetLastError());
	}
}

void CLS_ItsSystemParam3::OnCbnSelchangeCboChannelNumber()
{
	UI_UpdateData3();
}

void CLS_ItsSystemParam3::OnCbnSelchangeCboCaptureMode()
{
	UI_UpdateData3();
}
