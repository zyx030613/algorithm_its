// ItsSystemParam2.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ItsSystemParam2.h"


#define MAX_CAP_COUNT		8

IMPLEMENT_DYNAMIC(CLS_ItsSystemParam2, CDialog)

CLS_ItsSystemParam2::CLS_ItsSystemParam2(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ItsSystemParam2::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannel = -1;
}

CLS_ItsSystemParam2::~CLS_ItsSystemParam2()
{
}

void CLS_ItsSystemParam2::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GP_SYSTEM, m_gpSystem);
	DDX_Control(pDX, IDC_STC_SYSTEM_TYPE, m_stcSystemType);
	DDX_Control(pDX, IDC_STC_ELECTRIC_POLICE, m_stcElectricPolice);
	DDX_Control(pDX, IDC_CHK_USE_AROUND_PICTURE, m_chkAroundPicture);
	DDX_Control(pDX, IDC_BTN_SET_USE_AROUND_PICTURE, m_btnSetUseAroundPicture);
	DDX_Control(pDX, IDC_STC_CURRELATION_CAMERA_CAR, m_stcCorrelationCameraCar);
	DDX_Control(pDX, IDC_STC_CORRELATION_CAMERA, m_stcCorrelationCamera);
	DDX_Control(pDX, IDC_EDT_CORRELATION_CAMERA, m_edtCorrelationCamera);
	DDX_Control(pDX, IDC_STC_CAPTURE_MODE, m_stcCaptureMode);
	DDX_Control(pDX, IDC_CBO_CAPTURE_MODE, m_cboCaptureMode);
	DDX_Control(pDX, IDC_STC_ILLEGAL_CAPTURE_NUMBER, m_stcIllegalCaptureNumber);
	DDX_Control(pDX, IDC_CBO_ILLEGAL_CAPTURE_NUMBER, m_cboIllegalCaptureNumber);
	DDX_Control(pDX, IDC_BTN_SET_ILLEGAL_CAPTURE_NUMBER, m_btnSetIllegalCaptureNumber);
	DDX_Control(pDX, IDC_CBO_CORRELATION_CAMERA_CAR, m_cboCorrelationCameraCarRoad);
	DDX_Control(pDX, IDC_CBO_ROADID, m_cboRoadID);
}


BEGIN_MESSAGE_MAP(CLS_ItsSystemParam2, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_SET_USE_AROUND_PICTURE, &CLS_ItsSystemParam2::OnBnClickedBtnSetUseAroundPicture)
	ON_BN_CLICKED(IDC_BTN_SET_ILLEGAL_CAPTURE_NUMBER, &CLS_ItsSystemParam2::OnBnClickedBtnSetIllegalCaptureNumber)
	ON_CBN_SELCHANGE(IDC_CBO_ROADID, &CLS_ItsSystemParam2::OnCbnSelchangeCboRoadid)
	ON_CBN_SELCHANGE(IDC_CBO_CAPTURE_MODE, &CLS_ItsSystemParam2::OnCbnSelchangeCboCaptureMode)
END_MESSAGE_MAP()


// CLS_ItsSystemParam2 消息处理程序

BOOL CLS_ItsSystemParam2::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	int i = 0;
	m_cboIllegalCaptureNumber.ResetContent();
	for(i = 0; i < MAX_CAP_COUNT; i++)
	{
		int iCapCount = i + 1;
		m_cboIllegalCaptureNumber.SetItemData(m_cboIllegalCaptureNumber.AddString(IntToString(iCapCount)), iCapCount);
	}

	m_cboIllegalCaptureNumber.SetItemData(m_cboIllegalCaptureNumber.AddString(GetTextEx(IDS_PICK_OVER)), 9);

	CString csCboSelectRoad[] = {"0","1","2","3"};
	for(i = 0;i < 4;i++)
	{
		InsertString(m_cboCorrelationCameraCarRoad, i, csCboSelectRoad[i]);
	}
	UI_UpdateDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLS_ItsSystemParam2::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
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

 	UI_UpdateUseAroundPicture();
	UI_UpdateCaptureNumber();
}

void CLS_ItsSystemParam2::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ItsSystemParam2::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_GP_SYSTEM, IDS_CFG_LOG_DVR_SYSTEM);
	SetDlgItemTextEx(IDC_STC_SYSTEM_TYPE, IDS_ITS_STC_SYSTEM_TYPE);
	SetDlgItemTextEx(IDC_STC_ELECTRIC_POLICE,IDS_ITS_STC_ELECTRIC_POLICE);
	SetDlgItemTextEx(IDC_CHK_USE_AROUND_PICTURE, IDS_ITS_CHK_USE_AROUND_CAPTURE);
	SetDlgItemTextEx(IDC_STC_CORRELATION_CAMERA, IDS_ITS_CORRELATION_CAMERA);
	SetDlgItemTextEx(IDC_STC_CURRELATION_CAMERA_CAR, IDS_ITS_CORRELATION_CAMERA_ROAD);
	SetDlgItemTextEx(IDC_STC_CAPTURE_MODE, IDS_ITS_CAPTURE_MODE);
	SetDlgItemTextEx(IDC_STC_ILLEGAL_CAPTURE_NUMBER, IDS_ITS_CAPTURE_NUMBER);
	SetDlgItemTextEx(IDC_BTN_SET_USE_AROUND_PICTURE, IDS_SET);
	SetDlgItemTextEx(IDC_BTN_SET_ILLEGAL_CAPTURE_NUMBER, IDS_SET);
	SetDlgItemTextEx(IDC_STC_ROADID, IDS_ITS_SET_ROADID);

	int iTempSel = m_cboCaptureMode.GetCurSel();
	iTempSel = (iTempSel <= 0) ? 0 : iTempSel;
	m_cboCaptureMode.ResetContent();
	m_cboCaptureMode.SetItemData(m_cboCaptureMode.AddString(GetTextEx(IDS_ITS_KK_CAPTURE)), 0);
	m_cboCaptureMode.SetItemData(m_cboCaptureMode.AddString(GetTextEx(IDS_ITS_PARA_BAYONET_CAMERA)), 1);
	m_cboCaptureMode.SetItemData(m_cboCaptureMode.AddString(GetTextEx(IDS_ITS_RETROGRADE)), 2);
	m_cboCaptureMode.SetItemData(m_cboCaptureMode.AddString(GetTextEx(IDS_ITS_CROSS_RED_LIGHT)), 3);
	m_cboCaptureMode.SetItemData(m_cboCaptureMode.AddString(GetTextEx(IDS_ITS_INTRANCE)), 4);
	m_cboCaptureMode.SetItemData(m_cboCaptureMode.AddString(GetTextEx(IDS_ITS_CROSS_THE_LINE)), 5);
	m_cboCaptureMode.SetItemData(m_cboCaptureMode.AddString(GetTextEx(IDS_ITS_BAN_ORDER)), 6);
	m_cboCaptureMode.SetItemData(m_cboCaptureMode.AddString(GetTextEx(IDS_ITS_AMBLE)), 7);
	m_cboCaptureMode.SetItemData(m_cboCaptureMode.AddString(GetTextEx(IDS_ITS_SPEED)), 8);
	m_cboCaptureMode.SetItemData(m_cboCaptureMode.AddString(GetTextEx(IDS_ITS_TURN2)), 9);
	m_cboCaptureMode.SetItemData(m_cboCaptureMode.AddString(GetTextEx(IDS_ITS_BUS_ROAD)), 10);
	m_cboCaptureMode.SetItemData(m_cboCaptureMode.AddString(GetTextEx(IDS_ITS_BACK_CAR)), 11);
	m_cboCaptureMode.SetItemData(m_cboCaptureMode.AddString(GetTextEx(IDS_ITS_ILLEAGLE_CHANGE_LANE)), 12);
	m_cboCaptureMode.SetItemData(m_cboCaptureMode.AddString(GetTextEx(IDS_ITS_MIXED_ENABLE)), 13);
	m_cboCaptureMode.SetItemData(m_cboCaptureMode.AddString(GetTextEx(IDS_ITS_FASTENSB)), 14);
	m_cboCaptureMode.SetItemData(m_cboCaptureMode.AddString(GetTextEx(IDS_ITS_CALLING)), 15);
	iTempSel = (iTempSel >= m_cboCaptureMode.GetCount()) ? 0 : iTempSel;
	m_cboCaptureMode.SetCurSel(iTempSel);

	for(int i = 0;i < MAX_ITS_ROADID_NUM;i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		InsertString(m_cboRoadID,i,strNo);
	}
	m_cboRoadID.SetCurSel(0);
//  UI_UpdateUseAroundPicture();
// 	UI_UpdateCaptureNumber();
}

void CLS_ItsSystemParam2::OnBnClickedBtnSetUseAroundPicture()
{
	if(m_iChannel >= 0)
	{
		TITS_SnapShotInfo tUse = {0};
		tUse.m_iSize = sizeof(tUse);
		tUse.m_iRoadNo = m_cboRoadID.GetCurSel();
		int iRecieveLength = 0;
		tUse.m_iEnable = m_chkAroundPicture.GetCheck();
		tUse.m_iLinkRoadNo = m_cboCorrelationCameraCarRoad.GetCurSel();
		GetDlgItem(IDC_EDT_CORRELATION_CAMERA)->GetWindowText((LPSTR)(tUse.m_cLinkIP),LENGTH_IPV4);
		int iCheckIp = IsValidIP(tUse.m_cLinkIP);
		if(iCheckIp <= 0)
		{
			return;
		}
		int iRet2 = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_SNAP_SHOT_INFO, m_iChannel, &tUse, sizeof(TITS_SnapShotInfo));
		if (0 == iRet2)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_SNAP_SHOT_INFO](%d, %d)",m_iLogonID, m_iChannel);
		} 
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_SNAP_SHOT_INFO] (%d, %d),error(%d)",m_iLogonID, m_iChannel, GetLastError());
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","iLogonId or iChannel ERROR (%d, %d),error(%d)",m_iLogonID, m_iChannel, GetLastError());
	}
}

//刷新关联相机
BOOL CLS_ItsSystemParam2::UI_UpdateUseAroundPicture()
{
	if(m_iLogonID < 0)
		return FALSE;

	TITS_SnapShotInfo tSnapShotInfo = {0};
	tSnapShotInfo.m_iSize = sizeof(tSnapShotInfo);
	tSnapShotInfo.m_iRoadNo = m_cboRoadID.GetCurSel();
	int iBytesReturned = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_SNAP_SHOT_INFO, m_iChannel, &tSnapShotInfo, sizeof(tSnapShotInfo), &iBytesReturned);
	if(0 == iRet)
	{
		m_chkAroundPicture.SetCheck(tSnapShotInfo.m_iEnable);
		m_cboCorrelationCameraCarRoad.SetCurSel(tSnapShotInfo.m_iLinkRoadNo);
		SetDlgItemText(IDC_EDT_CORRELATION_CAMERA, tSnapShotInfo.m_cLinkIP);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_SNAP_SHOT_INFO](%d,%d)",m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_SNAP_SHOT_INFO](%d,%d), error(%d)",m_iLogonID, m_iChannel,GetLastError());
		return FALSE;
	}

	return TRUE;
}

void CLS_ItsSystemParam2::OnBnClickedBtnSetIllegalCaptureNumber()
{
	if(m_iLogonID >= 0)
	{
		ITS_CapCount tSetCapture = {0};
		tSetCapture.iBufSize = sizeof(ITS_CapCount);
		tSetCapture.iCapCount = (int)m_cboIllegalCaptureNumber.GetItemData(m_cboIllegalCaptureNumber.GetCurSel());
		tSetCapture.iCapType = (int)m_cboCaptureMode.GetItemData(m_cboCaptureMode.GetCurSel());
		int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_CAPTURECOUNT_CMD_SET, m_iChannel, &tSetCapture, sizeof(ITS_CapCount));
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_CAPTURECOUNT_CMD_SET](%d, %d)",m_iLogonID, m_iChannel);
		} 
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_CAPTURECOUNT_CMD_SET] (%d, %d),error(%d)",m_iLogonID, m_iChannel, GetLastError());
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","iLogonId or iChannel ERROR (%d, %d),error(%d)",m_iLogonID, m_iChannel, GetLastError());
	}
}
//刷新抓拍模式和抓拍方式
BOOL CLS_ItsSystemParam2::UI_UpdateCaptureNumber()
{
	if(m_iLogonID < 0)
		return FALSE;

	ITS_CapCount tSetCapture = {0};
	tSetCapture.iBufSize = sizeof(tSetCapture);
	tSetCapture.iCapType = (int)m_cboCaptureMode.GetItemData(m_cboCaptureMode.GetCurSel());
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_CAPTURECOUNT_CMD_GET, m_iChannel, &tSetCapture, sizeof(ITS_CapCount));
	if(0 == iRet)
	{
		m_cboIllegalCaptureNumber.SetCurSel(GetCboSel(&m_cboIllegalCaptureNumber, tSetCapture.iCapCount));
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_CAPTURECOUNT_CMD_GET],(%d,%d)", m_iLogonID,m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_CAPTURECOUNT_CMD_GET],(%d,%d),err0r(%d)", m_iLogonID,m_iChannel,GetLastError());
		return FALSE;
	}

	return TRUE;
}

void CLS_ItsSystemParam2::OnCbnSelchangeCboRoadid()
{
	UI_UpdateUseAroundPicture();
}

void CLS_ItsSystemParam2::OnCbnSelchangeCboCaptureMode()
{
	UI_UpdateCaptureNumber();
}
