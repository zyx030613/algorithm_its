// VidepParamPage.cpp : implementation file
//

#include "stdafx.h"
#include "VideoParamPage.h"
#include <map>
using namespace std;

#define	MAX_VIDEOSZ_LEN	(16*2) 

static map<int, CString> g_mapNVSize;	//NTSC制 视频尺寸
static map<int, CString> g_mapPVSize;	//PAL制 视频尺寸

#define		H_264		0
#define		M_JPEG		1
#define		MPEG4		2
#define		H_265		3
#define     CORRIDOR_PATTERN_ON  0
#define     CORRIDOR_PATTERN_OFF 1
#define     SPLUS_ON    1
#define     SPLUS_OFF   2

// CLS_VidepParamPage dialog

IMPLEMENT_DYNAMIC(CLS_VideoParamPage, CDialog)

CLS_VideoParamPage::CLS_VideoParamPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_VideoParamPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNo = 0;
}

CLS_VideoParamPage::~CLS_VideoParamPage()
{
}

void CLS_VideoParamPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_VIDEOQUALITY, m_cboVideoQuality);
	DDX_Control(pDX, IDC_COMBO_FRAMERATE, m_cboFrameRate);
	DDX_Control(pDX, IDC_COMBO_STREAMTYPE, m_cboStreamType);
	DDX_Control(pDX, IDC_COMBO_PREFERMODE, m_cboPreferMode);
	DDX_Control(pDX, IDC_EDIT_BITRATE, m_edtBitRate);
	DDX_Control(pDX, IDC_BUTTON_BITRATE, m_btnBitRate);
	DDX_Control(pDX, IDC_COMBO_VIDEOSIZE, m_cboVideoSize);
	DDX_Control(pDX, IDC_BUTTON_VIDEOSIZE, m_btnVideoSize);
	DDX_Control(pDX, IDC_COMBO_ENCODEMODE, m_cboEncodeMode);
	DDX_Control(pDX, IDC_COMBO_VIDEONPMODE, m_cboVideoNPMode);
	DDX_Control(pDX, IDC_BUTTON_VIDEONPMODE, m_btnVideoNPMode);
	DDX_Control(pDX, IDC_COMBO_VENCTYPE, m_cboVencType);
	DDX_Control(pDX, IDC_COMBO_FRAMEMODE, m_cboFrameMode);
	DDX_Control(pDX, IDC_EDIT_IFRAMERATE, m_edtIFrameRate);
	DDX_Control(pDX, IDC_BUTTON_IFRAMERATE, m_btnIFrameRate);
	DDX_Control(pDX, IDC_COMBO_VENCPROFILE_ENCODER, m_cboVencProfileEncode);
	DDX_Control(pDX, IDC_COMBO_MODEMETHOD, m_cboModeMethod);
	DDX_Control(pDX, IDC_COMBO_REDUSE_NOISE, m_cboReduceNoise);
	DDX_Control(pDX, IDC_COMBO_SAME_STREAM, m_cboBothStreamSame);
	DDX_Control(pDX, IDC_COMBO_VERTICALSYNC, m_cboVSync);
	DDX_Control(pDX, IDC_BUTTON_VERTICALSYNC, m_btnVSync);
	DDX_Control(pDX, IDC_COMBO_CHANNELTYPE, m_cboChannelType);
	DDX_Control(pDX, IDC_COMBO_VIDEOSIZE_PASSAGE, m_cboPassageMode);
	DDX_Control(pDX, IDC_COMBO_VIDEO_SPLUS, m_cboSplusMode);
}


BEGIN_MESSAGE_MAP(CLS_VideoParamPage, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEOQUALITY, &CLS_VideoParamPage::OnCbnSelchangeComboVideoquality)
//	ON_CBN_SELCHANGE(IDC_COMBO_FRAMERATE, &CLS_VideoParamPage::OnCbnSelchangeComboFramerate)
	ON_CBN_SELCHANGE(IDC_COMBO_STREAMTYPE, &CLS_VideoParamPage::OnCbnSelchangeComboStreamtype)
	ON_CBN_SELCHANGE(IDC_COMBO_PREFERMODE, &CLS_VideoParamPage::OnCbnSelchangeComboPrefermode)
	ON_BN_CLICKED(IDC_BUTTON_BITRATE, &CLS_VideoParamPage::OnBnClickedButtonBitrate)
	ON_BN_CLICKED(IDC_BUTTON_VIDEOSIZE, &CLS_VideoParamPage::OnBnClickedButtonVideosize)
	ON_CBN_SELCHANGE(IDC_COMBO_ENCODEMODE, &CLS_VideoParamPage::OnCbnSelchangeComboEncodemode)
	ON_BN_CLICKED(IDC_BUTTON_VIDEONPMODE, &CLS_VideoParamPage::OnBnClickedButtonVideonpmode)
	ON_CBN_SELCHANGE(IDC_COMBO_VENCTYPE, &CLS_VideoParamPage::OnCbnSelchangeComboVenctype)		//修改视频编码方式
	ON_BN_CLICKED(IDC_BUTTON_MODEMETHOD, &CLS_VideoParamPage::OnBnClickedButtonModemethod)
	ON_CBN_SELCHANGE(IDC_COMBO_FRAMEMODE, &CLS_VideoParamPage::OnCbnSelchangeComboFramemode)
	ON_BN_CLICKED(IDC_BUTTON_IFRAMERATE, &CLS_VideoParamPage::OnBnClickedButtonIframerate)
	ON_BN_CLICKED(IDC_BUTTON_VENCPROFILE_ENCODER, &CLS_VideoParamPage::OnBnClickedButtonVencprofileEncoder)
	ON_BN_CLICKED(IDC_BUTTON_REDUSE_NOISE, &CLS_VideoParamPage::OnBnClickedButtonReduseNoise)
	ON_BN_CLICKED(IDC_BUTTON_SAME_STREAM, &CLS_VideoParamPage::OnBnClickedButtonSameStream)
	ON_BN_CLICKED(IDC_BUTTON_VERTICALSYNC, &CLS_VideoParamPage::OnBnClickedButtonVerticalsync)
	ON_BN_CLICKED(IDC_BUTTON_FRAME_RATE, &CLS_VideoParamPage::OnBnClickedButtonFrameRate)
	ON_BN_CLICKED(IDC_BUTTON_CHANNELTYPE, &CLS_VideoParamPage::OnBnClickedButtonChanneltype)
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEOSIZE_PASSAGE, &CLS_VideoParamPage::OnCbnSelchangeComboVideosizePassage)
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEO_SPLUS, &CLS_VideoParamPage::OnCbnSelchangeComboVideoSplus)
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEONPMODE, &CLS_VideoParamPage::OnCbnSelchangeComboVideoNPMode)
END_MESSAGE_MAP()


// CLS_VidepParamPage message handlers

BOOL CLS_VideoParamPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	InitVideoSizeMap();
	m_cboVideoQuality.AddString("4");
	m_cboVideoQuality.AddString("6");
	m_cboVideoQuality.AddString("8");
	m_cboVideoQuality.AddString("10");
	m_cboVideoQuality.AddString("12");
	m_cboVideoQuality.AddString("14");
	//m_cboVideoQuality.AddString("16");

	UpdateFrameRateCbo();

	m_edtBitRate.SetLimitText(5);

	m_cboEncodeMode.AddString("CBR");
	m_cboEncodeMode.AddString("VBR");

	m_cboVideoNPMode.AddString("PAL");
	m_cboVideoNPMode.AddString("NTSC");
	//m_cboVideoNPMode.AddString("AUTO");

	m_edtIFrameRate.SetLimitText(3);

	UI_UpdateDialog();

	m_cboStreamType.SetCurSel(0);
	m_cboPreferMode.SetCurSel(0);
	m_cboFrameMode.SetCurSel(0);
	m_cboBothStreamSame.SetCurSel(0);
	m_cboReduceNoise.SetCurSel(0);
	m_cboVSync.SetCurSel(0);

	m_cboVencProfileEncode.AddString(_T("baseline"));
	m_cboVencProfileEncode.AddString(_T("main profile"));
	m_cboVencProfileEncode.AddString(_T("high profile"));
	m_cboVencProfileEncode.SetCurSel(0);

	m_cboChannelType.SetCurSel(0);

	m_cboPassageMode.AddString("On");//开启
	m_cboPassageMode.AddString("Off");//关闭

	int iVideoSize = 0;
	NetClient_GetVideoSizeEx(m_iLogonID, m_iChannelNo, &iVideoSize, m_iStreamNo);
	int iMode = iVideoSize - 0x100000 ;
	if (iMode > 0)
	{
		m_cboPassageMode.SetCurSel(0);
	} 
	else
	{
		m_cboPassageMode.SetCurSel(1);
	}
	
	return TRUE;
}

void CLS_VideoParamPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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
	if (_iStreamNo < 0 || _iStreamNo > 1)
	{
		m_iStreamNo = 0;
		if (254 == _iStreamNo)
		{
			m_iStreamNo = 4;
		}
	}
	else
	{
		m_iStreamNo = _iStreamNo;
	}

	UI_UpdateVedioQuality();
	UI_UpdateFrameRate();
	UI_UpdateStreamType();
	UI_UpdatePreferMode();
	UI_UpdateBitRate();
	UI_UpdateVideoSize();
	UI_UpdateEncodeMode();
	UI_UpdateModeMethod();
	UI_UpdateVideoPNMode();
	UI_InitVideoEncodeList();		//获取当前编码格式并刷新到界面;
	UI_UpdateFrameMode();
	UI_UpdateIFrameRate();
	UI_UpdateVencProfileEncoder();
	UI_UpdateReduceNoise();
	UI_UpdateSameStream();
	UI_UpdateVSync();
	UI_UpdateChannelType();
	UI_UpdateSplusMode();
}

void CLS_VideoParamPage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
	UI_UpdateStreamType();
	UI_UpdatePreferMode();
}

void CLS_VideoParamPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_VIDEOQUALITY, IDS_CONFIG_VIDEO_PARAM_VIDEOQUALITY);
	SetDlgItemTextEx(IDC_STATIC_FRAMERATE, IDS_CONFIG_VIDEO_PARAM_FRAMERATE);
	SetDlgItemTextEx(IDC_STATIC_STREAMTYPE, IDS_CONFIG_VIDEO_PARAM_STREAMTYPE);
	SetDlgItemTextEx(IDC_STATIC_PREFERMODE, IDS_CONFIG_VIDEO_PARAM_PREFERMODE);
	SetDlgItemTextEx(IDC_STATIC_BITRATE, IDS_CONFIG_VIDEO_PARAM_BITRATE);
	SetDlgItemTextEx(IDC_STATIC_VIDEOSIZE, IDS_CONFIG_VIDEO_PARAM_VIDEOSIZE);
	SetDlgItemTextEx(IDC_STATIC_VIDEONPMODE, IDS_CONFIG_VIDEO_PARAM_VIDEONPMODE);
	SetDlgItemTextEx(IDC_STATIC_VENCTYPE, IDS_CONFIG_VIDEO_PARAM_VENCTYPE);
	SetDlgItemTextEx(IDC_STATIC_AUDIOENCODER, IDS_CONFIG_VIDEO_PARAM_AUDIOENCODER);
	SetDlgItemTextEx(IDC_STATIC_FRAMEMODE, IDS_CONFIG_VIDEO_PARAM_FRAMEMODE);
	SetDlgItemTextEx(IDC_STATIC_IFRAMERATE, IDS_CONFIG_VIDEO_PARAM_IFRAMERATE);
	SetDlgItemTextEx(IDC_STATIC_VENCPROFILE_ENCODER, IDS_CONFIG_VIDEO_PARAM_VENPROFILE_ENCODE);
	SetDlgItemTextEx(IDC_STATIC_CHANNELTYPE, IDS_CONFIG_VIDEO_PARAM_CHANNELTYPE);
	SetDlgItemTextEx(IDC_BUTTON_BITRATE, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_VIDEOSIZE, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_MODEMETHOD, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_VIDEONPMODE, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_IFRAMERATE, IDS_SET);
	SetDlgItemTextEx(IDC_CHECK_AUTODETECT, IDS_CONFIG_VIDEO_PARAM_AUTODETECT);
	SetDlgItemTextEx(IDC_BUTTON_DUPLICATE, IDS_CONFIG_VIDEO_PARAM_DUPLICATE);
	SetDlgItemTextEx(IDC_STATIC_ENCODEMODE, IDS_CONFIG_VIDEO_PARAM_ENCODEMODE);
	SetDlgItemTextEx(IDC_STATIC_REDUCE_NOISE,IDS_VIDEO_REDUCE_NOISE);
	SetDlgItemTextEx(IDC_STATIC_SAME_STREAM, IDS_VIDEO_BOTH_STREAM_SAME);
	SetDlgItemTextEx(IDC_BUTTON_REDUSE_NOISE, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_SAME_STREAM, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_VERTICALSYNC, IDS_CONFIG_VIDEOPARAM_SYNC);
	SetDlgItemTextEx(IDC_BUTTON_VERTICALSYNC, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_VENCPROFILE_ENCODER, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_FRAME_RATE, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_CHANNELTYPE, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_CHANNELTYPE, IDS_CONFIG_VIDEO_PARAM_CHANNELTYPE);
	SetDlgItemTextEx(IDC_STATIC_VIDEOSIZE_PASSAGE, IDS_VIDEO_PASSAGE_MODE);
	SetDlgItemTextEx(IDC_STATIC_VIDEO_SPLUS, IDS_SPLUS_MODE);

	InsertString(m_cboStreamType,0,IDS_CONFIG_VIDEO_PARAM_VIDEOSTREAM);
	InsertString(m_cboStreamType,1,IDS_CONFIG_VIDEO_PARAM_AUDIOSTREAM);
	InsertString(m_cboStreamType,2,IDS_CONFIG_VIDEO_PARAM_AUDIO_VIDEO);
	
	InsertString(m_cboPreferMode,0,IDS_CONFIG_VIDEO_PARAM_PREFER_QUALITY);
	InsertString(m_cboPreferMode,1,IDS_CONFIG_VIDEO_PARAM_PREFER_FRAMERATE);

	InsertString(m_cboFrameMode,0,IDS_CONFIG_VIDEO_PARAM_LOWDELAY);
	InsertString(m_cboFrameMode,1,IDS_CONFIG_VIDEO_PARAM_SMOOTH);
	InsertString(m_cboFrameMode,2,IDS_PREVIEW_NETDELAY_NO_DELAY);
	InsertString(m_cboFrameMode,3,IDS_PREVIEW_NETDELAY_BALANCE);

	InsertString(m_cboReduceNoise,0,IDS_ADV_CHANNEL_DISABLE);
	InsertString(m_cboReduceNoise,1,IDS_ADV_CHANNEL_ENABLE);

	InsertString(m_cboBothStreamSame,0,IDS_ADV_CHANNEL_DISABLE);
	InsertString(m_cboBothStreamSame,1,IDS_ADV_CHANNEL_ENABLE);

	InsertString(m_cboVSync,0,IDS_CONFIG_VIDEOPARAM_DISABLE);
	InsertString(m_cboVSync,1,IDS_CONFIG_VIDEOPARAM_ENABLE);

	InsertString(m_cboChannelType, 0, IDS_CONFIG_VIDEO_PARAM_DIGITALCHAN);
	InsertString(m_cboChannelType, 1, IDS_CONFIG_VIDEO_PARAM_LOCALCHAN);
	InsertString(m_cboChannelType, 2, IDS_CONFIG_VIDEO_PARAM_COMBINECHAN);

	m_cboModeMethod.ResetContent();
	m_cboModeMethod.AddString(GetTextEx(IDS_DOME_HANDLE));
	m_cboModeMethod.AddString(GetTextEx(IDS_DOME_AUTO));
	m_cboModeMethod.SetCurSel(0);

	m_cboSplusMode.ResetContent();
	m_cboSplusMode.SetItemData(m_cboSplusMode.AddString(GetTextEx(IDS_PREVIEW_IRIS_OPEN)), SPLUS_ON);
	m_cboSplusMode.SetItemData(m_cboSplusMode.AddString(GetTextEx(IDS_PREVIEW_IRIS_CLOSE)), SPLUS_OFF);
	m_cboSplusMode.SetCurSel(0);

}

void CLS_VideoParamPage::OnCbnSelchangeComboVideoquality()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iVedioQuality = m_cboVideoQuality.GetCurSel() * 2 + 4;
	if (iVedioQuality < 4 || iVedioQuality >16)
	{
		AddLog(LOG_TYPE_MSG,"","m_cboVideoQuality Param Error (%d)",iVedioQuality);
		return;
	}
	int iRet = NetClient_SetVideoQuality(m_iLogonID, m_iChannelNo, iVedioQuality, m_iStreamNo);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetVideoQuality(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iVedioQuality,m_iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetVideoQuality(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iVedioQuality,m_iStreamNo);
	}

}

BOOL CLS_VideoParamPage::UI_UpdateVedioQuality()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iVedioQuality;
	int iRet = NetClient_GetVideoQuality(m_iLogonID, m_iChannelNo, &iVedioQuality, m_iStreamNo);
	
	if (0 == iRet)
	{
		m_cboVideoQuality.SetCurSel((iVedioQuality - 4)/2);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetVideoQuality(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iVedioQuality,m_iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetVideoQuality(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iVedioQuality,m_iStreamNo);
	}
	return TRUE;
}

//void CLS_VideoParamPage::OnCbnSelchangeComboFramerate()
//{
//	if (m_iLogonID < 0)
//	{
//		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
//		return;
//	}
//
// 	int iFrameRate = m_cboFrameRate.GetCurSel();
// 	if (0 == iFrameRate)
// 	{
// 		iFrameRate = 1;
// 	}
// 	else
// 	{
// 		iFrameRate *= 5;
// 	}
//	int iFrameRate = GetDlgItemInt(IDC_COMBO_FRAMERATE);
//	if (iFrameRate < 1 || iFrameRate >30)
//	{
//		AddLog(LOG_TYPE_MSG,"","m_cboFrameRate Param Error (%d)",iFrameRate);
//		return;
//	}
//	int iRet = NetClient_SetFrameRate(m_iLogonID, m_iChannelNo, iFrameRate, m_iStreamNo);
//	if (0 == iRet)
//	{
//		AddLog(LOG_TYPE_SUCC,"","NetClient_SetFrameRate(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iFrameRate,m_iStreamNo);
//	}
//	else
//	{
//		AddLog(LOG_TYPE_FAIL,"","NetClient_SetFrameRate(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iFrameRate,m_iStreamNo);
//	}
//}


BOOL CLS_VideoParamPage::UI_UpdateFrameRate()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iFrameRate;
	int iRet = NetClient_GetFrameRate(m_iLogonID, m_iChannelNo, &iFrameRate, m_iStreamNo);
	if (0 == iRet)
	{
// 		if (1 == iFrameRate)
// 		{
// 			m_cboFrameRate.SetCurSel(0);
// 		}
// 		else
// 		{
// 			m_cboFrameRate.SetCurSel(iFrameRate/5);
// 		}
		SetDlgItemInt(IDC_COMBO_FRAMERATE,iFrameRate);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetFrameRate(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iFrameRate,m_iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetFrameRate(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iFrameRate,m_iStreamNo);
	}

	return TRUE;
}


void CLS_VideoParamPage::OnCbnSelchangeComboStreamtype()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iStreamType = m_cboStreamType.GetCurSel()+1;
	if (iStreamType < 0 || iStreamType >3)
	{
		AddLog(LOG_TYPE_MSG,"","m_cboStreamType Param Error (%d)",iStreamType);
		return;
	}
	int iRet = NetClient_SetStreamType(m_iLogonID, m_iChannelNo, iStreamType, m_iStreamNo);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetStreamType(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iStreamType,m_iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetStreamType(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iStreamType,m_iStreamNo);
	}
}

BOOL CLS_VideoParamPage::UI_UpdateStreamType()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iStreamType;
	int iRet = NetClient_GetStreamType(m_iLogonID, m_iChannelNo, &iStreamType, m_iStreamNo);
	if (0 == iRet)
	{
		m_cboStreamType.SetCurSel(iStreamType-1);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetStreamType(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iStreamType,m_iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetStreamType(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iStreamType,m_iStreamNo);
	}

	return TRUE;
}
void CLS_VideoParamPage::OnCbnSelchangeComboPrefermode()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iPreferMode = m_cboPreferMode.GetCurSel();
	if (iPreferMode < 0 || iPreferMode > 1)
	{
		AddLog(LOG_TYPE_MSG,"","m_cboPreferMode Param Error (%d)",iPreferMode);
		return;
	}
	int iRet = NetClient_SetPreferMode(m_iLogonID, m_iChannelNo, m_iStreamNo, iPreferMode);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetPreferMode(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iStreamNo,iPreferMode);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetPreferMode(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iStreamNo,iPreferMode);
	}
}

BOOL CLS_VideoParamPage::UI_UpdatePreferMode()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iPreferMode;
	int iRet = NetClient_GetPreferMode(m_iLogonID, m_iChannelNo, m_iStreamNo, &iPreferMode);
	if (0 == iRet)
	{
		m_cboPreferMode.SetCurSel(iPreferMode);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetPreferMode(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iStreamNo,iPreferMode);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetPreferMode(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iStreamNo,iPreferMode);
	}

	return TRUE;
}
void CLS_VideoParamPage::OnBnClickedButtonBitrate()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iBitRate = GetDlgItemInt(IDC_EDIT_BITRATE);
	if (iBitRate < 32 || iBitRate > 16384)
	{
		AddLog(LOG_TYPE_FAIL,"","BitRate(%d) illegal",iBitRate);
		return;
	}

	if (iBitRate < 0)
	{
		iBitRate = 10240;
	}
	else
	{
		iBitRate /= 8;
	}
	int iRet = NetClient_SetMaxKByteRate(m_iLogonID, m_iChannelNo, iBitRate, m_iStreamNo);
	if (0 == iRet)
	{
// 		if (iBitRate == 8 || iBitRate == 1024)
// 		{
// 			SetDlgItemInt(IDC_EDIT_BITRATE, iBitRate);
// 		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetMaxKByteRate(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iBitRate,m_iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetMaxKByteRate(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iBitRate,m_iStreamNo);
	}
}

BOOL CLS_VideoParamPage::UI_UpdateBitRate()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iBitRate;
	int iRet = NetClient_GetMaxKByteRate(m_iLogonID, m_iChannelNo, &iBitRate, m_iStreamNo);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_BITRATE, iBitRate * 8);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetMaxKByteRate(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iBitRate,m_iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetMaxKByteRate(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iBitRate,m_iStreamNo);
	}

	return TRUE;
}

void CLS_VideoParamPage::OnBnClickedButtonVideosize()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	//设置视频大小
	int iCurSel = m_cboVideoSize.GetCurSel();
	if (iCurSel >= 0)
	{
		int iCurVideoSize = m_cboVideoSize.GetItemData(iCurSel);
		if (iCurVideoSize > 0)
		{
			SetVideoSize(m_iLogonID,m_iChannelNo,m_iStreamNo, iCurVideoSize);
		}
	}
}

void CLS_VideoParamPage::OnCbnSelchangeComboEncodemode()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iEncodeMode = m_cboEncodeMode.GetCurSel();
	if (iEncodeMode < 0 || iEncodeMode > 1)
	{
		AddLog(LOG_TYPE_MSG,"","m_cboEncodeMode Param Error (%d)",iEncodeMode);
		return;
	}
	int iRet =  NetClient_SetEncodeMode(m_iLogonID, m_iChannelNo, m_iStreamNo, iEncodeMode);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetEncodeMode(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iStreamNo,iEncodeMode);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetEncodeMode(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iStreamNo,iEncodeMode);
	}
}

BOOL CLS_VideoParamPage::UI_UpdateEncodeMode()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iEncodeMode;
	int iRet = NetClient_GetEncodeMode(m_iLogonID, m_iChannelNo, m_iStreamNo, &iEncodeMode);
	if (0 == iRet)
	{
		m_cboEncodeMode.SetCurSel(iEncodeMode);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetEncodeMode(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iStreamNo,iEncodeMode);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetEncodeMode(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iStreamNo,iEncodeMode);
	}
	return TRUE;
}

void CLS_VideoParamPage::OnBnClickedButtonVideonpmode()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	
	VIDEO_NORM vMode = VIDEO_MODE_PAL;
	int iVideoNPMode = m_cboVideoNPMode.GetCurSel();
	if (0 == iVideoNPMode)
	{
		vMode = VIDEO_MODE_PAL;
	}
	else if (1 == iVideoNPMode)
	{
		vMode = VIDEO_MODE_NTSC;
	}
	else
	{
// 		NetClient_GetProductType(m_iLogonID, &iDeviceType);
// 		iDeviceType = iDeviceType & 0xFFFF;
// 		if((iDeviceType & 0x100) == 0x100)     
// 		{
// 			vMode = (VIDEO_NORM)m_cboEncodeMode.GetCurSel();
// 		}
		return;
	}
	
	int iRet =  NetClient_SetVideoNPModeEx(m_iLogonID, m_iChannelNo, vMode);
	if (0 == iRet)
	{
// 		NetClient_GetProductType(m_iLogonID, &iDeviceType);
// 		if ((iDeviceType) != TC_1002S2_3C)
// 		{
// 			if (TC_NC9000S3_3MP == iDeviceType || TC_NC9100S3_3MP_IR30 == iDeviceType ||
// 				TC_NC9000S3_2MP_E == iDeviceType || TC_NC9200S3_MP_E_IR15 == iDeviceType ||
// 				TC_NC9100S3E_MP_IR30 == iDeviceType)
// 			{
// 				AddLog(LOG_TYPE_MSG,"","DeviceType (%d) mustn't reboot",iDeviceType);
// 				return;
// 			}
// 			else
// 			{
// 				iRet = NetClient_Reboot(m_iLogonID);
// 			}
// 		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetVideoNPModeEx(%d,%d,%d)",m_iLogonID,m_iChannelNo,vMode);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetVideoNPModeEx(%d,%d,%d)",m_iLogonID,m_iChannelNo,vMode);
	}
}

BOOL CLS_VideoParamPage::UI_UpdateVideoPNMode()
{
	if (m_iLogonID < 0)
		return FALSE;

	VIDEO_NORM vMode = VIDEO_MODE_PAL;
	int iRet = NetClient_GetVideoNPModeEx(m_iLogonID, m_iChannelNo, &vMode);
	if (0 == iRet)
	{
		m_cboVideoNPMode.SetCurSel(vMode);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetVideoNPModeEx(%d,%d,%d)",m_iLogonID,m_iChannelNo,vMode);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetVideoNPModeEx(%d,%d,%d)",m_iLogonID,m_iChannelNo,vMode);
	}
	return TRUE;
}

void CLS_VideoParamPage::OnCbnSelchangeComboVenctype()
{
	UI_UpdateVencProfileEncoder();

	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iVencType = (int)m_cboVencType.GetItemData(m_cboVencType.GetCurSel());

	if (iVencType < H_264 || iVencType > H_265)
	{
		AddLog(LOG_TYPE_MSG,"","m_cboVencType Param Error (%d)",iVencType);
		return;
	}
	int iRet = NetClient_SetVencType(m_iLogonID, m_iChannelNo, iVencType);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetVencType(%d,%d,%d)",m_iLogonID,m_iChannelNo,iVencType);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetVencType(%d,%d,%d)",m_iLogonID,m_iChannelNo,iVencType);
	}
}

void CLS_VideoParamPage::OnBnClickedButtonModemethod()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	VIDEO_METHOD vMethod = VIDEO_MODE_AUT;
	int iDeviceType;
	int iModeMethod = m_cboModeMethod.GetCurSel();
	if (0 == iModeMethod)
	{
		vMethod = VIDEO_MODE_HAND;
	}
	else if (1 == iModeMethod)
	{
		vMethod = VIDEO_MODE_AUT;
	}
	else
	{
		NetClient_GetProductType(m_iLogonID, &iDeviceType);
		iDeviceType = iDeviceType & 0xFFFF;
		if((iDeviceType & 0x100) == 0x100)     
		{
			vMethod = (VIDEO_NORM)m_cboEncodeMode.GetCurSel();
		}
	}

	int iRet =  NetClient_SetVideoModeMethod(m_iLogonID, m_iChannelNo, vMethod);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetVideoModeMethod(%d,%d,%d)",m_iLogonID,m_iChannelNo,vMethod);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetVideoModeMethod(%d,%d,%d)",m_iLogonID,m_iChannelNo,vMethod);
	}
}

BOOL CLS_VideoParamPage::UI_UpdateModeMethod()
{
	if (m_iLogonID < 0)
		return FALSE;

	VIDEO_METHOD vMethod = VIDEO_MODE_AUT;
	int iRet = NetClient_GetVideoModeMethod(m_iLogonID, m_iChannelNo, &vMethod);
	if (0 == iRet)
	{
		m_cboModeMethod.SetCurSel(vMethod);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetVideoModeMethod(%d,%d,%d)",m_iLogonID,m_iChannelNo,vMethod);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetVideoModeMethod(%d,%d,%d)",m_iLogonID,m_iChannelNo,vMethod);
	}
	return TRUE;
}

void CLS_VideoParamPage::OnCbnSelchangeComboFramemode()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	unsigned int uiFrameMode = (unsigned int)m_cboFrameMode.GetCurSel();
	if (uiFrameMode < 0 || uiFrameMode > 1)
	{
		AddLog(LOG_TYPE_MSG,"","m_cboFrameMode Param Error (%d)",uiFrameMode);
		return;
	}
	int iRet = NetClient_SetPlayerShowFrameMode(m_iLogonID, m_iChannelNo, uiFrameMode, m_iStreamNo);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetPlayerShowFrameMode(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,uiFrameMode,m_iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetPlayerShowFrameMode(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,uiFrameMode,m_iStreamNo);
	}
}

BOOL CLS_VideoParamPage::UI_UpdateFrameMode()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iFrameMode = NetClient_GetPlayerShowFrameMode(m_iLogonID, m_iChannelNo, m_iStreamNo);
	if (iFrameMode >= 0)
	{
		m_cboFrameMode.SetCurSel(iFrameMode);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetPlayerShowFrameMode(%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetPlayerShowFrameMode(%d,%d,%d)",m_iLogonID,m_iChannelNo,m_iStreamNo);
	}
	return TRUE;
}

void CLS_VideoParamPage::OnBnClickedButtonIframerate()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iIFrameRate = GetDlgItemInt(IDC_EDIT_IFRAMERATE);
	if (iIFrameRate < 10 || iIFrameRate > 100)
	{
		AddLog(LOG_TYPE_FAIL,"","I FrameRate(%d) illegal",iIFrameRate);
		return;
	}

	if (iIFrameRate < 1)
	{
		iIFrameRate = 1;
	}
	if (iIFrameRate > 255)
	{
		iIFrameRate = 255;
	}
	int iRet = NetClient_SetIFrameRate(m_iLogonID, m_iChannelNo, iIFrameRate, m_iStreamNo);
	if (0 == iRet)
	{
		if (iIFrameRate == 1 || iIFrameRate == 255)
		{
			SetDlgItemInt(IDC_EDIT_IFRAMERATE, iIFrameRate);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetIFrameRate(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iIFrameRate,m_iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetIFrameRate(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iIFrameRate,m_iStreamNo);
	}
}

BOOL CLS_VideoParamPage::UI_UpdateIFrameRate()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iIFrameRate;
	int iRet = NetClient_GetIFrameRate(m_iLogonID, m_iChannelNo, &iIFrameRate, m_iStreamNo);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_IFRAMERATE, iIFrameRate);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetIFrameRate(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iIFrameRate,m_iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetIFrameRate(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iIFrameRate,m_iStreamNo);
	}
	return TRUE;
}

void CLS_VideoParamPage::OnBnClickedButtonVencprofileEncoder()
{
	int iLevel = m_cboVencProfileEncode.GetCurSel();
	int iRet = NetClient_SetChannelEncodeProfile(m_iLogonID,m_iChannelNo,m_iStreamNo,iLevel);
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetChannelEncodeProfile(%d,%d,%d,%d)"
			,m_iLogonID,m_iChannelNo,m_iStreamNo,iLevel);

// 		Sleep(500);
// 		int iCurTypeModel = 0;
// 		NetClient_GetProductType(m_iLogonID, &iCurTypeModel);
// 		iCurTypeModel &= 0xFFFF;
// 		if(IsDVR(iCurTypeModel)
// 			|| TC_NC9000S3_3MP == iCurTypeModel || TC_NC9100S3_3MP_IR30 == iCurTypeModel
// 			|| TC_NC9000S3_2MP_E == iCurTypeModel || TC_NC9200S3_MP_E_IR15 == iCurTypeModel
// 			|| TC_NC9100S3E_MP_IR30 == iCurTypeModel)
// 		{
// 			
// 		}
// 		else
// 		{
// 			iRet = NetClient_Reboot(m_iLogonID);
// 			if (0 == iRet)
// 			{
// 				AddLog(LOG_TYPE_SUCC,"","NetClient_Reboot(%d)",m_iLogonID);
// 			}
// 			else
// 			{
// 				AddLog(LOG_TYPE_FAIL,"","NetClient_Reboot(%d)",m_iLogonID);
// 			}
// 		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetChannelEncodeProfile(%d,%d,%d,%d)"
			,m_iLogonID,m_iChannelNo,m_iStreamNo,iLevel);
	}
}

BOOL CLS_VideoParamPage::UI_UpdateVencProfileEncoder()
{
	if (0 == m_cboVencType.GetItemData(m_cboVencType.GetCurSel()))
	{//H264才支持设置profile
		int iLevel = 0;
		int iRet = NetClient_GetChannelEncodeProfile(m_iLogonID,m_iChannelNo,m_iStreamNo,&iLevel);
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_GetChannelEncodeProfile(%d,%d,%d,%d)"
				,m_iLogonID,m_iChannelNo,m_iStreamNo,iLevel);

			m_cboVencProfileEncode.SetCurSel(iLevel);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetChannelEncodeProfile(%d,%d,%d,%d)"
				,m_iLogonID,m_iChannelNo,m_iStreamNo,iLevel);
		}
		m_cboVencProfileEncode.EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_VENCPROFILE_ENCODER)->EnableWindow(TRUE);
	}
	else
	{
		m_cboVencProfileEncode.SetCurSel(-1);
		m_cboVencProfileEncode.EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_VENCPROFILE_ENCODER)->EnableWindow(FALSE);
	}
	
	return TRUE;
}
void CLS_VideoParamPage::OnBnClickedButtonReduseNoise()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iNoiseEnable = m_cboReduceNoise.GetCurSel();

	int iRet = NetClient_SetReducenoiseState(m_iLogonID, m_iChannelNo, iNoiseEnable);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetReducenoiseState(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo, iNoiseEnable);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetReducenoiseState(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo, iNoiseEnable);
	}
}

BOOL CLS_VideoParamPage::UI_UpdateReduceNoise()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iNoiseEnable = 0;
	int iRet = NetClient_GetReducenoiseState(m_iLogonID, m_iChannelNo, &iNoiseEnable);
	if (0 == iRet)
	{
		m_cboReduceNoise.SetCurSel(iNoiseEnable);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetReducenoiseState(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iNoiseEnable,m_iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetReducenoiseState(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iNoiseEnable,m_iStreamNo);
	}
	return TRUE;	
}
void CLS_VideoParamPage::OnBnClickedButtonSameStream()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iSameEnable = m_cboBothStreamSame.GetCurSel();
	int iRet = NetClient_SetBothStreamSame(m_iLogonID, m_iChannelNo, iSameEnable);
	if (0 == iRet)
	{
		int iNvsType = 0;
		int iGet = NetClient_GetDevType(m_iLogonID,&iNvsType);
		if(iGet == 0 )
		{
			if ( NVS_T == iNvsType || NVS_TPLUS == iNvsType )
			{
				iRet = NetClient_Reboot(m_iLogonID);
			}
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetBothStreamSame(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo, iSameEnable);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetBothStreamSame(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo, iSameEnable);
	}
}

BOOL CLS_VideoParamPage::UI_UpdateSameStream()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iSameEnable = 0;
	int iRet = NetClient_GetBothStreamSame(m_iLogonID, m_iChannelNo, &iSameEnable);
	if (0 == iRet)
	{
		m_cboBothStreamSame.SetCurSel(iSameEnable);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetReducenoiseState(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iSameEnable,m_iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetReducenoiseState(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iSameEnable,m_iStreamNo);
	}
	return TRUE;	
}

void CLS_VideoParamPage::OnBnClickedButtonVerticalsync()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iVSyn = m_cboVSync.GetCurSel();
	unsigned int puConnID;
	PCHANNEL_INFO pChannelInfo = FindChannel(m_iLogonID, m_iChannelNo, m_iStreamNo, &puConnID);
	if (pChannelInfo == NULL)
	{
		AddLog(LOG_TYPE_MSG,"","please connect video ");
		m_cboVSync.SetCurSel(0);
		return;
	}
	int iRet = NetClient_SetVerticalSync(puConnID, iVSyn);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetVerticalSync(%d,%d)",puConnID,iVSyn);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetVerticalSync(%d,%d)",puConnID,iVSyn);
	}
}

BOOL CLS_VideoParamPage::UI_UpdateVSync()
{
	unsigned int puConnID;
	PCHANNEL_INFO pChannelInfo = FindChannel(m_iLogonID, m_iChannelNo, m_iStreamNo, &puConnID);
	if (pChannelInfo == NULL)
	{
		AddLog(LOG_TYPE_MSG,"","please connect video");
		return FALSE;
	}
	int iVSyn = -1;
	int iRet = NetClient_GetVerticalSync(puConnID, &iVSyn);
	if (0 == iRet)
	{
		m_cboVSync.SetCurSel(iVSyn);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetVerticalSync(%d,%d)",puConnID,iVSyn);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetVerticalSync(%d,%d)",puConnID,iVSyn);
	}
	return TRUE;
}

void CLS_VideoParamPage::OnBnClickedButtonFrameRate()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	// 	int iFrameRate = m_cboFrameRate.GetCurSel();
	// 	if (0 == iFrameRate)
	// 	{
	// 		iFrameRate = 1;
	// 	}
	// 	else
	// 	{
	// 		iFrameRate *= 5;
	// 	}
	int iFrameRate = GetDlgItemInt(IDC_COMBO_FRAMERATE);
	if (iFrameRate < 1 || iFrameRate > 60)
	{
		AddLog(LOG_TYPE_MSG,"","m_cboFrameRate Param Error (%d)",iFrameRate);
		return;
	}
	int iRet = NetClient_SetFrameRate(m_iLogonID, m_iChannelNo, iFrameRate, m_iStreamNo);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetFrameRate(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iFrameRate,m_iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetFrameRate(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iFrameRate,m_iStreamNo);
	}
}

BOOL CLS_VideoParamPage::UI_UpdateChannelType()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iChannelType = m_cboChannelType.GetCurSel();
	int iChannelTypeSize = sizeof(int);
	int iCmd = GENERAL_CMD_CHANNEL_TYPE;
	int iRet = NetClient_GetChannelProperty(m_iLogonID, m_iChannelNo, iCmd, &iChannelType, iChannelTypeSize);
	if (0 == iRet)
	{
		int iChannelTypeCurSel = 0;
		if (CHANNEL_TYPE_LOCAL == iChannelType)
		{
			iChannelTypeCurSel = 1;
		} 
		else if (CHANNEL_TYPE_DIGITAL == iChannelType)
		{
			iChannelTypeCurSel = 0;
		}
		else if (CHANNEL_TYPE_COMBINE == iChannelType)
		{
			iChannelTypeCurSel = 2;
		}
		m_cboChannelType.SetCurSel(iChannelTypeCurSel);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetChannelProperty(%d,%d,%d,%d,%d)", m_iLogonID, m_iChannelNo, iCmd, iChannelType, iChannelTypeSize);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetChannelProperty(%d,%d,%d,%d,%d)", m_iLogonID, m_iChannelNo, iCmd, iChannelType, iChannelTypeSize);
	}

	return TRUE;
}
//@120418
void CLS_VideoParamPage::OnParamChangeNotify(int m_iLogonID, int m_iChannelNo, int _iParaType,void* _pPara,int _iUser)
{
	switch(_iParaType)
	{
		case PARA_CHANNEL_TYPE:
			{
				int iRet = MessageBox(GetTextEx(IDS_CONFIG_LAN_MESSAGETEXT), GetTextEx(IDS_CONFIG_PROMPT),MB_OKCANCEL);
				if (IDOK == iRet)
				{
					iRet = NetClient_Reboot(m_iLogonID);
					if (0 == iRet)
					{
						AddLog(LOG_TYPE_SUCC,"","NetClient_Reboot(%d)",m_iLogonID);
					}
					else
					{
						AddLog(LOG_TYPE_FAIL,"","NetClient_Reboot(%d)",m_iLogonID);
					}
				}
			}
			break;
		default:
			break;
	}
}

void CLS_VideoParamPage::OnBnClickedButtonChanneltype()
{
	// TODO: Add your control notification handler code here
 	if (m_iLogonID < 0)
 	{
 		AddLog(LOG_TYPE_MSG,"", "Invalid logon id(%d)",m_iLogonID);
 		return;
 	}
 
 	int iChannelType = m_cboChannelType.GetCurSel();
 	if (iChannelType < 0 || iChannelType > 3)
 	{
 		AddLog(LOG_TYPE_MSG, "", "m_cboChannelType Param Error (%d)", iChannelType);
 	}

 	int iCnannelTypeCmd = 0;
 	if (0 == iChannelType)
 	{
 		iCnannelTypeCmd = CHANNEL_TYPE_DIGITAL;
 	} 
 	else if (1 == iChannelType)
 	{
 		iCnannelTypeCmd = CHANNEL_TYPE_LOCAL;
 	}
 	else if (2 == iChannelType)
 	{
		iCnannelTypeCmd = CHANNEL_TYPE_COMBINE;
 	}

 	int iCmd = GENERAL_CMD_CHANNEL_TYPE;
 	int iCnannelTypeCmdSize = sizeof(int);
 	int iRet = NetClient_SetChannelProperty(m_iLogonID, m_iChannelNo, iCmd, &iCnannelTypeCmd, iCnannelTypeCmdSize);
 	if (0 == iRet)
 	{
 		AddLog(LOG_TYPE_SUCC,"","NetClient_SetChannelProperty(%d,%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iCmd,iCnannelTypeCmd,iCnannelTypeCmdSize);
 	} 
 	else
 	{
 		AddLog(LOG_TYPE_FAIL,"","NetClient_SetChannelProperty(%d,%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,iCmd,iCnannelTypeCmd,iCnannelTypeCmdSize);
 	}
}


void CLS_VideoParamPage::OnCbnSelchangeComboVideosizePassage()
{
	int iSul = m_cboVideoSize.GetCurSel();
	if (iSul < 0)
	{
		return;
	}
		
	int iCurVideoSize = (int)m_cboVideoSize.GetItemData(iSul);

	int iVideoSize = 0; 
	if (m_cboPassageMode.GetCurSel() == 0)//开启
	{			
		iVideoSize = iCurVideoSize + 0x100000;
		NetClient_SetVideoSize(m_iLogonID,m_iChannelNo,iVideoSize,m_iStreamNo);
	} 
	else//关闭
	{
		iVideoSize = iCurVideoSize;
		NetClient_SetVideoSize(m_iLogonID,m_iChannelNo,iVideoSize,m_iStreamNo);
	}
}

void CLS_VideoParamPage::SetVideoSize( int _iLogonID, int _iChannelNo, int _iStreamNo,int _iVideoSize)
{
	int iVideoSizeEx = -1;
	int iRet = NetClient_GetVideoSizeEx(_iLogonID,_iChannelNo,&iVideoSizeEx,_iStreamNo);
	if (iRet == 0)
	{		
		int iNewPassageMode = _iVideoSize;
		if (iVideoSizeEx & 0x100000)
		{
			iNewPassageMode = 0x100000 | _iVideoSize;
			m_cboPassageMode.SetCurSel(0);
		}
		else
		{
			m_cboPassageMode.SetCurSel(1);
		}
		
		int iDeviceType = 0;
		int iRet = NetClient_SetVideoSize(_iLogonID,_iChannelNo,_iVideoSize,_iStreamNo);
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetVideoSize(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,_iVideoSize,m_iStreamNo);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetVideoSize(%d,%d,%d,%d)",m_iLogonID,m_iChannelNo,_iVideoSize,m_iStreamNo);
		}
	}	
}



void CLS_VideoParamPage::UI_UpdateVideoSize()
{
	m_cboVideoSize.ResetContent();
	int iCount = 0;
	int iStreamNo = m_iStreamNo;
	//获取设备当前视频制式
	int iNPMode = m_cboVideoNPMode.GetCurSel();
	BOOL blPalMode = (iNPMode == 1)?FALSE:TRUE;
	//获取设备当前分辨率
	int iCurrentVideoSize = -1;
	if(NetClient_GetVideoSizeEx(m_iLogonID,m_iChannelNo,&iCurrentVideoSize,m_iStreamNo) < 0)
	{
		AddLog(LOG_TYPE_FAIL,"", "[CLS_VideoParamPage::InitVideoSizeList] GetVideoSizeEx Failed!");
	}       

	int iRet = NetClient_GetVideoSzList(m_iLogonID,m_iChannelNo,iStreamNo,NULL,&iCount);
	if (iRet < 0 || iCount <= 0)
	{
		AddLog(LOG_TYPE_FAIL,"", "[CLS_VideoParamPage::InitVideoSizeList] GetVideoSzList Failed!");
		return;
	}
	int *piVideoSizelist = new int[iCount];
	iRet = NetClient_GetVideoSzList(m_iLogonID,m_iChannelNo,iStreamNo,piVideoSizelist,&iCount);

	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"", "[CLS_VideoParamPage::InitVideoSizeList] GetVideoSzList Failed!");

		if(NULL != piVideoSizelist)
		{
			delete piVideoSizelist;
			piVideoSizelist = NULL;   
		}

		return;
	}

	int index = 0;
	for(int i =0;i<iCount;++i)
	{
		int iVideoSize = piVideoSizelist[i];
		CString csVideoSize;


		//添加鱼眼超大分辨率
		if (0 != (iVideoSize&0x40000000))
		{
			csVideoSize.Format(_T("%dx%d"), iVideoSize&0x7FFF, (iVideoSize>>15)&0x7FFF);
		}

		if(((iVideoSize >= 0x100000) || (iVideoSize < 0) ) && csVideoSize.IsEmpty())
		{
			continue;
		}

		if (csVideoSize.IsEmpty())
		{
			csVideoSize = blPalMode?g_mapPVSize[iVideoSize]:g_mapNVSize[iVideoSize];
		}

		if (csVideoSize.IsEmpty())
		{
			csVideoSize.Format("Undefined-0x%0x", iVideoSize);
		}

		int iItem = m_cboVideoSize.InsertString(index, csVideoSize);
		m_cboVideoSize.SetItemData(iItem, iVideoSize);
		
		if ((iCurrentVideoSize > 0) && (piVideoSizelist[i] == iCurrentVideoSize))
		{
			m_cboVideoSize.SetCurSel(index);
		}
		else
		{
			int iTempVideoSize = iCurrentVideoSize - 0x100000;
			if ((iTempVideoSize > 0) && (piVideoSizelist[i] == iTempVideoSize))
			{
				m_cboVideoSize.SetCurSel(index);
			}
		}
		index++;
	}

	if(NULL != piVideoSizelist)
	{
		delete piVideoSizelist;
		piVideoSizelist = NULL;
	}
	
	int iPassageMode = iCurrentVideoSize - 0x100000;
	if (iPassageMode > CORRIDOR_PATTERN_ON)
	{
		m_cboPassageMode.SetCurSel(CORRIDOR_PATTERN_ON);
	}
	else
	{
		m_cboPassageMode.SetCurSel(CORRIDOR_PATTERN_OFF);
	}
}


void CLS_VideoParamPage::InitVideoSizeMap()
{

	g_mapNVSize.insert(pair<int, CString>(QCIF		, "QCIF(176x120)"	));
	g_mapNVSize.insert(pair<int, CString>(HCIF		, "HCIF(352x120)"	));
	g_mapNVSize.insert(pair<int, CString>(FCIF		, "CIF(352x240)"	));
	g_mapNVSize.insert(pair<int, CString>(HD1		, "2CIF(704x288)"	));
	g_mapNVSize.insert(pair<int, CString>(FD1		, "4CIF(704x576)"	));
	g_mapNVSize.insert(pair<int, CString>(MD1		, "2CIF(704x288)"	));
	g_mapNVSize.insert(pair<int, CString>(QVGA		, "QVGA(320x240)"	));
	g_mapNVSize.insert(pair<int, CString>(VGA		, "VGA(640x480)"	));
	g_mapNVSize.insert(pair<int, CString>(HVGA		, "HVGA(640x240)"	));
	g_mapNVSize.insert(pair<int, CString>(HD_720P	, "720P(1280x720)"	));
	g_mapNVSize.insert(pair<int, CString>(HD_960P	, "960P(1280x960)"	));
	g_mapNVSize.insert(pair<int, CString>(HD_200W	, "UXGA(1600x1200)"	));
	g_mapNVSize.insert(pair<int, CString>(HD_1080P	, "1080P(1920x1080)"));

	g_mapNVSize.insert(pair<int, CString>(HD_QXGA	, "QXGA(2048x1536)"	));
	g_mapNVSize.insert(pair<int, CString>(QHD		, "QHD(960x540)"	));
	g_mapNVSize.insert(pair<int, CString>(VZ_960H	, "960H(960x480)"	));
	g_mapNVSize.insert(pair<int, CString>(VZ_1440P	, "1440P(2560x1440)"));
	g_mapNVSize.insert(pair<int, CString>(VZ_4MP	, "4.0MP(2592x1520)"));
	g_mapNVSize.insert(pair<int, CString>(WUXGA		, "WUXGA(1920x1200)"));
	g_mapNVSize.insert(pair<int, CString>(VZ_5MA	, "5.0MP(2448x2048)"));
	g_mapNVSize.insert(pair<int, CString>(VZ_5M		, "5.0MP(2560x1920)"));
	g_mapNVSize.insert(pair<int, CString>(VZ_5MB	, "5.0MP(2592*1944)"));
	g_mapNVSize.insert(pair<int, CString>(VZ_5MC	, "5.0MP(2592*2048)"));
	g_mapNVSize.insert(pair<int, CString>(VZ_5MD	, "5.0MP(2528*2128)"));
	g_mapNVSize.insert(pair<int, CString>(VZ_5ME	, "5.0MP(2560x2048)"));
	g_mapNVSize.insert(pair<int, CString>(VZ_6M		, "6.0MP(2752*2208)"));
	g_mapNVSize.insert(pair<int, CString>(VZ_6MA	, "6.0MP(3008*2008)"));
	g_mapNVSize.insert(pair<int, CString>(VZ_6MB	, "6.0MP(3408*2008)"));
	g_mapNVSize.insert(pair<int, CString>(VZ_7M		, "7.0MP(3392*2008)"));
	g_mapNVSize.insert(pair<int, CString>(VZ_8MA	, "8.0MP(3840*2160)"));
	g_mapNVSize.insert(pair<int, CString>(VZ_8MB	, "8.0MP(3264x2448)"));
	g_mapNVSize.insert(pair<int, CString>(VZ_8MC	, "8.0MP(3296x2472)"));

	g_mapPVSize.insert(pair<int, CString>(QCIF		, "QCIF(176x144)"	));
	g_mapPVSize.insert(pair<int, CString>(HCIF		, "HCIF(352x144)"	));
	g_mapPVSize.insert(pair<int, CString>(FCIF		, "CIF(352x288)"	));
	g_mapPVSize.insert(pair<int, CString>(HD1		, "2CIF(704x288)"	));
	g_mapPVSize.insert(pair<int, CString>(FD1		, "4CIF(704x576)"	));
	g_mapPVSize.insert(pair<int, CString>(MD1		, "2CIF(704x288)"	));
	g_mapPVSize.insert(pair<int, CString>(QVGA		, "QVGA(320x240)"	));
	g_mapPVSize.insert(pair<int, CString>(VGA		, "VGA(640x480)"	));
	g_mapPVSize.insert(pair<int, CString>(HVGA		, "HVGA(640x240)"	));
	g_mapPVSize.insert(pair<int, CString>(HD_720P	, "720P(1280x720)"	));
	g_mapPVSize.insert(pair<int, CString>(HD_960P	, "960P(1280x960)"	));
	g_mapPVSize.insert(pair<int, CString>(HD_200W	, "UXGA(1600x1200)"	));
	g_mapPVSize.insert(pair<int, CString>(HD_1080P	, "1080P(1920x1080)"));

	g_mapPVSize.insert(pair<int, CString>(HD_QXGA	, "QXGA(2048x1536)"	));
	g_mapPVSize.insert(pair<int, CString>(QHD		, "QHD(960x540)"	));
	g_mapPVSize.insert(pair<int, CString>(VZ_960H	, "960H(960x480)"	));
	g_mapPVSize.insert(pair<int, CString>(VZ_1440P	, "1440P(2560*1440)"));
	g_mapPVSize.insert(pair<int, CString>(VZ_4MP	, "4.0MP(2592x1520)"));
	g_mapPVSize.insert(pair<int, CString>(WUXGA		, "WUXGA(1920x1200)"));
	g_mapPVSize.insert(pair<int, CString>(VZ_5MA	, "5.0MP(2448x2048)"));
	g_mapPVSize.insert(pair<int, CString>(VZ_5M		, "5.0MP(2560x1920)"));
	g_mapPVSize.insert(pair<int, CString>(VZ_5MB	, "5.0MP(2592*1944)"));
	g_mapPVSize.insert(pair<int, CString>(VZ_5MC	, "5.0MP(2592*2048)"));
	g_mapPVSize.insert(pair<int, CString>(VZ_5MD	, "5.0MP(2528*2128)"));
	g_mapPVSize.insert(pair<int, CString>(VZ_5ME	, "5.0MP(2560x2048)"));
	g_mapPVSize.insert(pair<int, CString>(VZ_6M		, "6.0MP(2752*2208)"));
	g_mapPVSize.insert(pair<int, CString>(VZ_6MA	, "6.0MP(3008*2008)"));
	g_mapPVSize.insert(pair<int, CString>(VZ_6MB	, "6.0MP(3408*2008)"));
	g_mapPVSize.insert(pair<int, CString>(VZ_7M		, "7.0MP(3392*2008)"));
	g_mapPVSize.insert(pair<int, CString>(VZ_8MA	, "8.0MP(3840*2160)"));
	g_mapPVSize.insert(pair<int, CString>(VZ_8MB	, "8.0MP(3264x2448)"));
	g_mapPVSize.insert(pair<int, CString>(VZ_8MC	, "8.0MP(3296x2472)"));

}

void CLS_VideoParamPage::UI_InitVideoEncodeList()
{
	if (m_iLogonID < 0 || m_iChannelNo < 0)
	{
		AddLog(LOG_TYPE_FAIL,"", "[CLS_VideoParamPage::InitVideoEncodeList] Wrong LogId || Wrong ChannelNo");
		return;
	}
	//获取当前视频压缩编码方式
	int iCurrentVencType = -1; 
	VencType stVenc = {0};
	stVenc.iSize = sizeof(stVenc);
	stVenc.iStreamType = m_iStreamNo;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_VENCTYPE, m_iChannelNo, &stVenc, sizeof(stVenc), 0);
	iCurrentVencType = stVenc.iVencType;
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_VideoParamPage::InitVideoEncodeList] GetVencType Failed! LogonID(%d),Channel(%d)", m_iLogonID, m_iChannelNo);
	}
	else if (iCurrentVencType < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_VideoParamPage::InitVideoEncodeList] GetVencType Error! LogonID(%d),Channel(%d)", m_iLogonID, m_iChannelNo);
	}

	//获取视频压缩编码方式列表
	int iReturnByte = 0;
	tVideoEncodList stVideoEncodeList = {0};
	stVideoEncodeList.iSize = sizeof(tVideoEncodList);
	stVideoEncodeList.iChnNo = m_iChannelNo;
	iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_VIDEOENCODE_LIST, m_iChannelNo, &stVideoEncodeList,sizeof(tVideoEncodList), &iReturnByte);
	m_cboVencType.ResetContent();
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"", "[CLS_VideoParamPage::InitVideoEncodeList] GetVideoEncodeList Failed! LogonID(%d),Channel(%d)", m_iLogonID, m_iChannelNo);
		goto ErrGetVencListExit;
	}

	if (stVideoEncodeList.iVideoEncode == 0)
	{
		AddLog(LOG_TYPE_FAIL,"", "[CLS_VideoParamPage::InitVideoEncodeList] GetVideoEncodeList Error! LogonID(%d),Channel(%d)", m_iLogonID, m_iChannelNo);
		goto ErrGetVencListExit;
	}
	int iComBoxIndex = 0;

	if (stVideoEncodeList.iVideoEncode & 0x01)
	{
		m_cboVencType.InsertString(iComBoxIndex,"H.264");
		m_cboVencType.SetItemData(iComBoxIndex, H_264);
		iComBoxIndex++;
	}

	if (stVideoEncodeList.iVideoEncode & 0x01<<3)
	{
		m_cboVencType.InsertString(iComBoxIndex,"H.265");
		m_cboVencType.SetItemData(iComBoxIndex, H_265);
		iComBoxIndex++;
	}

	if (stVideoEncodeList.iVideoEncode & 0x01<<1)
	{
		m_cboVencType.InsertString(iComBoxIndex,"MotionJPEG");
		m_cboVencType.SetItemData(iComBoxIndex, M_JPEG);
		iComBoxIndex++;
	}

	if (stVideoEncodeList.iVideoEncode & 0x01<<2)
	{
		m_cboVencType.InsertString(iComBoxIndex,"MPEG4");
		m_cboVencType.SetItemData(iComBoxIndex, MPEG4);
		iComBoxIndex++;
	}

	if (iCurrentVencType >= 0)
	{
		for (int i = 0; i < m_cboVencType.GetCount(); i++)
		{
			if (iCurrentVencType == m_cboVencType.GetItemData(i))
			{
				m_cboVencType.SetCurSel(i);
				break;
			}
		}
	}

	return;

ErrGetVencListExit:

	m_cboVencType.InsertString(0,"H.264");
	m_cboVencType.SetItemData(0, H_264);
	m_cboVencType.InsertString(1,"Motion JEPG");
	m_cboVencType.SetItemData(1, M_JPEG);

	if (iCurrentVencType <= M_JPEG && iCurrentVencType >= H_264)
	{
		m_cboVencType.SetCurSel(iCurrentVencType);
	}

	return;
}



void CLS_VideoParamPage::OnCbnSelchangeComboVideoSplus()
{
	SPlus tSPlus = {0};
	tSPlus.iStreamNo = m_iStreamNo;
	tSPlus.iSize = sizeof(tSPlus);
	tSPlus.iSPlusState = m_cboSplusMode.GetItemData(m_cboSplusMode.GetCurSel());
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_SPLUS, m_iChannelNo, &tSPlus, sizeof(tSPlus));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_SPLUS] (%d, %d)",m_iLogonID, m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_SPLUS] (%d, %d)",m_iLogonID, m_iChannelNo);
	}
	
}
void CLS_VideoParamPage::UI_UpdateSplusMode()
{
	SPlus tSPlus = {0};
	tSPlus.iSize = sizeof(tSPlus);
	int iReturnByte = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_SPLUS, m_iChannelNo, &tSPlus, sizeof(tSPlus), &iReturnByte);
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_SPLUS] (%d, %d)",m_iLogonID, m_iChannelNo);
	} 
	else
	{
		m_cboSplusMode.SetCurSel(GetCboSel(&m_cboSplusMode, tSPlus.iSPlusState));
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_SPLUS] (%d, %d)",m_iLogonID, m_iChannelNo);
	}
}

void CLS_VideoParamPage::UpdateFrameRateCbo()
{
	m_cboFrameRate.ResetContent();
	m_cboFrameRate.AddString("1");
	m_cboFrameRate.AddString("5");
	m_cboFrameRate.AddString("10");
	m_cboFrameRate.AddString("15");
	m_cboFrameRate.AddString("20");
	m_cboFrameRate.AddString("25");
	m_cboFrameRate.AddString("30");
	if (0 == m_cboVideoNPMode.GetCurSel())
	{
		m_cboFrameRate.AddString("50");
	}
	else
	{
		m_cboFrameRate.AddString("60");
	}
}

void CLS_VideoParamPage::OnCbnSelchangeComboVideoNPMode()
{
	UpdateFrameRateCbo();
	UI_UpdateFrameRate();
}
