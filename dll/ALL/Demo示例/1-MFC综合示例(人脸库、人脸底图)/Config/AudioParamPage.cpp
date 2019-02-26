// Config/AudioParamPage.cpp : implementation file
//

#include "stdafx.h"
#include "AudioParamPage.h"


// CLS_AudioParamPage dialog
#define MAX_AUDIO_VOLUME_MAX	100
#define AUDIOTYPE_INDEX_CLOSE   0   // 音频输出方式 关闭 索引
#define AUDIOTYPE_INDEX_USESELF 1   // 音频输出方式 扬声器 索引
#define AUDIOTYPE_INDEX_LINE    2   // 音频输出方式 引出线 索引
#define AUDIOTYPE_INDEX_MAX     3 
#define AUDIO_SAMPLE_NO			100	//最大录音编号

IMPLEMENT_DYNAMIC(CLS_AudioParamPage, CDialog)

CLS_AudioParamPage::CLS_AudioParamPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_AudioParamPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iCurrentSceneId = 0;
}

CLS_AudioParamPage::~CLS_AudioParamPage()
{
}

void CLS_AudioParamPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_AUDIO_ENCODER, m_cboAudioEncoder);
	DDX_Control(pDX, IDC_COMBO_AUDIO_SAMPLE, m_cboAudioSample);
	DDX_Control(pDX, IDC_CBO_VOLUME_OUT_TYPE, m_cboVolumeOutType);
	DDX_Control(pDX, IDC_SLD_VOLUME_OUT_VALUE, m_sldVolumeOutValue);
	DDX_Control(pDX, IDC_CBO_SCENE_ID, m_cboSceneId);
	DDX_Control(pDX, IDC_CHK_GETAUDIO_ENABLE, m_chkGetAudio);
}


BEGIN_MESSAGE_MAP(CLS_AudioParamPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_AUDIO_ENCODER, &CLS_AudioParamPage::OnBnClickedButtonAudioEncoder)
	ON_BN_CLICKED(IDC_BUTTON_AUDIO_SAMPLE, &CLS_AudioParamPage::OnBnClickedButtonAudioSample)
	ON_BN_CLICKED(IDC_BTN_VOLUME_OUT_SET, &CLS_AudioParamPage::OnBnClickedBtnVolumeOutSet)
	ON_CBN_SELCHANGE(IDC_CBO_VOLUME_OUT_TYPE, &CLS_AudioParamPage::OnCbnSelchangeCboVolumeOutType)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BTN_PLAY_AUDIO_PLAY, &CLS_AudioParamPage::OnBnClickedBtnPlayAudioPlay)
	ON_EN_CHANGE(IDC_EDT_PLAY_AUDIO_NO, &CLS_AudioParamPage::OnEnChangeEdtPlayAudioNo)
	ON_BN_CLICKED(IDC_CHK_GETAUDIO_ENABLE, &CLS_AudioParamPage::OnBnClickedChkGetaudioEnable)
	ON_CBN_SELCHANGE(IDC_CBO_SCENE_ID, &CLS_AudioParamPage::OnCbnSelchangeCboSceneId)
	ON_BN_CLICKED(IDC_BTN_SET_MAX_VOLUME, &CLS_AudioParamPage::OnBnClickedBtnSetMaxVolume)
	ON_EN_CHANGE(IDC_EDT_MAX_VOLUME, &CLS_AudioParamPage::OnEnChangeEdtMaxVolume)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CLS_AudioParamPage message handlers

BOOL CLS_AudioParamPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_cboAudioEncoder.AddString("G.711A (64kbps)");
	m_cboAudioEncoder.AddString("G.711U (64kbps)");
	m_cboAudioEncoder.AddString("ADPCM-DVI4 (32kbps)");
	m_cboAudioEncoder.AddString("ADPCM-IMA (32kbps)");
	m_cboAudioEncoder.AddString("MEDIA_G.726 (16kbps)");
	m_cboAudioEncoder.AddString("MEDIA_G.726 (24kbps)");
	m_cboAudioEncoder.AddString("MEDIA_G.726 (32kbps)");
	m_cboAudioEncoder.AddString("MEDIA_G.726 (40kbps)");
	m_cboAudioEncoder.AddString("AMR_NB");
	m_cboAudioEncoder.AddString("G726  (24kbps)");
	m_cboAudioEncoder.AddString("G726  (32kbps)");
	m_cboAudioEncoder.AddString("G726  (40kbps)");
	m_cboAudioEncoder.AddString("MPEG4 AAC");
	
	m_cboAudioEncoder.SetItemData(0,G711_A);
	m_cboAudioEncoder.SetItemData(1,G711_U);
	m_cboAudioEncoder.SetItemData(2,ADPCM_DVI4);
	m_cboAudioEncoder.SetItemData(3,ADPCM_IMA);
	m_cboAudioEncoder.SetItemData(4,MEDIA_G726_16KBPS);
	m_cboAudioEncoder.SetItemData(5,MEDIA_G726_24KBPS);
	m_cboAudioEncoder.SetItemData(6,MEDIA_G726_32KBPS);
	m_cboAudioEncoder.SetItemData(7,MEDIA_G726_40KBPS);
	m_cboAudioEncoder.SetItemData(8,AMR_NB);
	m_cboAudioEncoder.SetItemData(9,G726_24KBPS);
	m_cboAudioEncoder.SetItemData(10,G726_32KBPS);
	m_cboAudioEncoder.SetItemData(11,G726_40KBPS);
	m_cboAudioEncoder.SetItemData(12,MPEG4_AAC);

	m_sldVolumeOutValue.SetRange(0, MAX_AUDIO_VOLUME_MAX);

	UI_UpdateDialog();

	return TRUE;  
}

void CLS_AudioParamPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);

	if (!bShow)
	{
		CommandGetAudio(m_iCurrentSceneId, GET_AUDIO_ENABLE_OFF);
	}
}

void CLS_AudioParamPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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

	UI_UpdateAudioEncoder();
	UI_UpdateAudioSample();
	UI_UpdateVolumeOut();
	OnCbnSelchangeCboSceneId();
}

void CLS_AudioParamPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

void CLS_AudioParamPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_AUDIO_ENCODER, IDS_CFG_AUDIO_PARAM_AUDIO_ENCODER);
	SetDlgItemTextEx(IDC_STATIC_AUDIO_SAMPLE, IDS_CFG_AUDIO_PARAM_AUDIO_SAMPLE);	
	SetDlgItemTextEx(IDC_BUTTON_AUDIO_ENCODER, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_AUDIO_SAMPLE, IDS_SET);

	SetDlgItemTextEx(IDC_STC_VOLUME_OUT_TYPE, IDS_AUDIO_OUTTYPE);
	SetDlgItemTextEx(IDC_STC_VOLUME_OUT_VALUE, IDS_PREVIEW_VOLUME);
	SetDlgItemTextEx(IDC_BTN_VOLUME_OUT_SET, IDS_SET);
	
	SetDlgItemTextEx(IDC_GPO_PLAY_AUDIO_SAMPLE, IDS_PLAY_AUDIO_SAMPLE);
	SetDlgItemTextEx(IDC_STC_PLAY_AUDIO_NO, IDS_AUDIO_SAMPLE_NO);
	SetDlgItemTextEx(IDC_BTN_PLAY_AUDIO_PLAY, IDS_START_PLAY);

	SetDlgItemTextEx(IDC_GPO_AUDIO_DETECTION, IDS_AUDIO_DETECTION);
	SetDlgItemTextEx(IDC_STC_SCENE_ID, IDS_CONFIG_COMS_SCENE);
	SetDlgItemTextEx(IDC_CHK_GETAUDIO_ENABLE, IDS_GETAUDIO_ENABLE);
	SetDlgItemTextEx(IDC_STC_CURRENT_VOLUME, IDS_PREVIEW_VOLUME);
	SetDlgItemTextEx(IDC_STC_MAX_VOLUME, IDS_MAX_AUDIO_VOLUME);
	SetDlgItemTextEx(IDC_BTN_SET_MAX_VOLUME, IDS_SET);

	int iTempSel = m_cboVolumeOutType.GetCurSel();
	iTempSel = iTempSel >= 0 ? iTempSel : 0;
	m_cboVolumeOutType.ResetContent();
	m_cboVolumeOutType.SetItemData(m_cboVolumeOutType.AddString(GetTextEx(IDS_CONFIG_CLOSE)), AUDIOTYPE_INDEX_CLOSE);
	m_cboVolumeOutType.SetItemData(m_cboVolumeOutType.AddString(GetTextEx(IDS_AUDIO_OUTTYPE_USESELF)), AUDIOTYPE_INDEX_USESELF);
	m_cboVolumeOutType.SetItemData(m_cboVolumeOutType.AddString(GetTextEx(IDS_AUDIO_OUTTYPE_LINE)), AUDIOTYPE_INDEX_LINE);
	if (m_cboVolumeOutType.GetCount() > iTempSel)
	{
		m_cboVolumeOutType.SetCurSel(iTempSel);
	}
	else
	{
		m_cboVolumeOutType.SetCurSel(0);
	}

	iTempSel = m_cboSceneId.GetCurSel();
	iTempSel = iTempSel >= 0 ? iTempSel : 0;
	m_cboSceneId.ResetContent();
	for (int i = 0; i < MAX_SCENE_NUM; ++i)
	{
		m_cboSceneId.SetItemData(m_cboSceneId.AddString(IntToString(i + 1)), i);
	}
	iTempSel = (m_cboSceneId.GetCount() > iTempSel) ? iTempSel : 0;
	m_cboSceneId.SetCurSel(iTempSel);

}

void CLS_AudioParamPage::UI_UpdateAudioEncoder()
{
	if (m_iLogonID < 0)
		return;

	AUDIO_ENCODER aEncoder;
	int iRet = NetClient_GetAudioEncoder(m_iLogonID, m_iChannelNo, &aEncoder);
	if (0 == iRet)
	{
		int iIndex = -1;
		int iData = 0;
		for (int i = 0; i < m_cboAudioEncoder.GetCount(); ++i)
		{
			iData = (int)m_cboAudioEncoder.GetItemData(i);
			if (aEncoder == iData)
			{
				iIndex = i;
				break;
			}
		}
		m_cboAudioEncoder.SetCurSel(iIndex);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetAudioEncoder(%d,%d,%d)",m_iLogonID,m_iChannelNo,aEncoder);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetAudioEncoder(%d,%d,%d)",m_iLogonID,m_iChannelNo,aEncoder);
	}
}

void CLS_AudioParamPage::UI_UpdateAudioSample()
{
	if (m_iLogonID < 0)
		return;

	int iCount = 0;
	CString sTempSample;
	m_cboAudioSample.ResetContent();
	if(0 == NetClient_GetAudioSample(m_iLogonID,m_iChannelNo,AUDIO_SAMPLE_CMD_SAMPLE_COUNT,&iCount))
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetAudioSample(%d,%d,SAMPLE_COUNT,%d)",m_iLogonID,m_iChannelNo,iCount);

		AUDIO_SAMPLE tSample = {sizeof(AUDIO_SAMPLE)};
		for(int i = 0; i < iCount; ++i)
		{
			tSample.iIndex = i;
			int iIndex = 0;
			if(0 == NetClient_GetAudioSample(m_iLogonID,m_iChannelNo,AUDIO_SAMPLE_CMD_SAMPLE_LIST,&tSample))
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_GetAudioSample(%d,%d,SAMPLE_LIST,%d,%d)",m_iLogonID,m_iChannelNo,i,tSample.iSample);

				sTempSample.Format(_T("%gK"),tSample.iSample*1.0/1000);
				iIndex = m_cboAudioSample.AddString(sTempSample);
				m_cboAudioSample.SetItemData(iIndex,tSample.iSample);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_GetAudioSample(%d,%d,SAMPLE_LIST,%d)",m_iLogonID,m_iChannelNo,i);
			}
		}
		int iSample = 0;
		if(0 == NetClient_GetAudioSample(m_iLogonID,m_iChannelNo,AUDIO_SAMPLE_CMD_SAMPLE,&iSample))
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_GetAudioSample(%d,%d,SAMPLE,%d)",m_iLogonID,m_iChannelNo,iSample);

			sTempSample.Format(_T("%gK"),iSample*1.0/1000);
			m_cboAudioSample.SelectString(-1,sTempSample);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetAudioSample(%d,%d,SAMPLE,%d)",m_iLogonID,m_iChannelNo,iSample);
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetAudioSample(%d,%d,SAMPLE_COUNT,%d)",m_iLogonID,m_iChannelNo,iCount);
	} 
}

void CLS_AudioParamPage::OnBnClickedButtonAudioEncoder()
{
	int iItem = m_cboAudioEncoder.GetCurSel();
	if (iItem < 0)
	{
		return;
	}

	AUDIO_ENCODER aEncoder;
	aEncoder = (AUDIO_ENCODER)m_cboAudioEncoder.GetItemData(iItem);
	int iRet =  NetClient_SetAudioEncoder(m_iLogonID, m_iChannelNo, aEncoder);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetAudioEncoder(%d,%d,%d)",m_iLogonID,m_iChannelNo,aEncoder);

		//修改音频编码方式不重启
		//int iDeviceType = 0;
		//NetClient_GetProductType(m_iLogonID, &iDeviceType);
		//iDeviceType &= 0xFFFF;
		//if ((iDeviceType & 0x100) == 0x100 || TC_NC9000S3_3MP == iDeviceType ||
		//	TC_NC9100S3_3MP_IR30 == iDeviceType || TC_NC9000S3_2MP_E == iDeviceType ||
		//	TC_NC9200S3_MP_E_IR15 == iDeviceType || TC_NC9100S3E_MP_IR30 == iDeviceType)
		//{
		//	
		//}
		//else
		//{
		//	iRet = NetClient_Reboot(m_iLogonID);
		//	if (0 == iRet)
		//	{
		//		AddLog(LOG_TYPE_SUCC,"","NetClient_Reboot(%d)",m_iLogonID);
		//	}
		//	else
		//	{
		//		AddLog(LOG_TYPE_FAIL,"","NetClient_Reboot(%d)",m_iLogonID);
		//	}
		//}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetAudioEncoder(%d,%d,%d)",m_iLogonID,m_iChannelNo,aEncoder);
	}
}

void CLS_AudioParamPage::OnBnClickedButtonAudioSample()
{
	int iItem = m_cboAudioSample.GetCurSel();
	if (iItem < 0)
	{
		return;
	}

	int iSample = (int)m_cboAudioSample.GetItemData(iItem);
	if(0 == NetClient_SetAudioSample(m_iLogonID,m_iChannelNo,AUDIO_SAMPLE_CMD_SAMPLE,&iSample))
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetAudioSample(%d,%d,SAMPLE,%d)",m_iLogonID,m_iChannelNo,iSample);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetAudioSample(%d,%d,SAMPLE,%d)",m_iLogonID,m_iChannelNo,iSample);
	}
}

void CLS_AudioParamPage::OnBnClickedBtnVolumeOutSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage LogonId(%d)",m_iLogonID);
		return;
	}

	if (m_iChannelNo < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage ChannelNo(%d)",m_iChannelNo);
		return;
	}

	VolumeOut tVolumeOut = {0};
	tVolumeOut.iSize = sizeof(tVolumeOut);
	tVolumeOut.iType = (int)m_cboVolumeOutType.GetItemData(m_cboVolumeOutType.GetCurSel());
	tVolumeOut.iValue = m_sldVolumeOutValue.GetPos();
	int iByteReturned = -1;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VOLUME_OUT, m_iChannelNo, &tVolumeOut, sizeof(tVolumeOut));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig VolumeOut(%d,%d,SAMPLE,%d)",m_iLogonID,m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig VolumeOut(%d,%d,SAMPLE,%d)",m_iLogonID,m_iChannelNo);
	}
}


void CLS_AudioParamPage::UI_UpdateVolumeOut()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage LogonId(%d)",m_iLogonID);
		return;
	}

	if (m_iChannelNo < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage ChannelNo(%d)",m_iChannelNo);
		return;
	}

	VolumeOut tVolumeOut = {0};
	tVolumeOut.iSize = sizeof(tVolumeOut);
	int iByteReturned = -1;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_VOLUME_OUT, m_iChannelNo, &tVolumeOut, sizeof(tVolumeOut), &iByteReturned);

	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig VolumeOut(%d,%d)",m_iLogonID,m_iChannelNo);
		return;
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig VolumeOut(%d,%d)",m_iLogonID,m_iChannelNo);
	}

	if (tVolumeOut.iType >= 0 && tVolumeOut.iType < AUDIOTYPE_INDEX_MAX)
	{
		m_cboVolumeOutType.SetCurSel(GetCboSel(&m_cboVolumeOutType, tVolumeOut.iType));
		OnCbnSelchangeCboVolumeOutType();
	}

	if (tVolumeOut.iValue >= m_sldVolumeOutValue.GetRangeMin() && 
		tVolumeOut.iValue <= m_sldVolumeOutValue.GetRangeMax())
	{
		m_sldVolumeOutValue.SetPos(tVolumeOut.iValue);
		SetDlgItemInt(IDC_STC_VOLUME_OUT_VALUE_SHOW, tVolumeOut.iValue);
	}
	return;
}

void CLS_AudioParamPage::OnCbnSelchangeCboVolumeOutType()
{
	if(AUDIOTYPE_INDEX_USESELF == m_cboVolumeOutType.GetItemData(m_cboVolumeOutType.GetCurSel()))
	{
		GetDlgItem(IDC_STC_VOLUME_OUT_VALUE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SLD_VOLUME_OUT_VALUE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STC_VOLUME_OUT_VALUE_SHOW)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_STC_VOLUME_OUT_VALUE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLD_VOLUME_OUT_VALUE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STC_VOLUME_OUT_VALUE_SHOW)->ShowWindow(SW_HIDE);
	}
}

void CLS_AudioParamPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CLS_BasePage::OnHScroll(nSBCode, nPos, pScrollBar);
	
	CSliderCtrl* psldCtrl = (CSliderCtrl*)pScrollBar;

	switch (psldCtrl->GetDlgCtrlID())
	{
		case IDC_SLD_VOLUME_OUT_VALUE:
			{
				SetDlgItemInt(IDC_STC_VOLUME_OUT_VALUE_SHOW, m_sldVolumeOutValue.GetPos());
			}
			break;
		default:
			break;
	}
	return;
}

void CLS_AudioParamPage::OnBnClickedBtnPlayAudioPlay()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage LogonId(%d)",m_iLogonID);
		return;
	}

	if (m_iChannelNo < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage ChannelNo(%d)",m_iChannelNo);
		return;
	}

	PlayAudioSample tPlayAudioSample = {0};

	tPlayAudioSample.iSize = sizeof(PlayAudioSample);
	tPlayAudioSample.iType = 0;						//音频类型，预留
	tPlayAudioSample.iSampleNo = GetDlgItemInt(IDC_EDT_PLAY_AUDIO_NO);

	int iRet = NetClient_SendCommand(m_iLogonID, COMMAND_ID_PLAY_AUDIO_SAMPLE, m_iChannelNo, (void*)&tPlayAudioSample, sizeof(PlayAudioSample));

	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SendCommand PlayAudioSample(%d,%d,%d)",m_iLogonID,m_iChannelNo, tPlayAudioSample.iSampleNo);
		return;
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SendCommand PlayAudioSample(%d,%d,%d)",m_iLogonID,m_iChannelNo, tPlayAudioSample.iSampleNo);
	}
}

void CLS_AudioParamPage::OnEnChangeEdtPlayAudioNo()
{
	int iAudioSampleNo = GetDlgItemInt(IDC_EDT_PLAY_AUDIO_NO);
	//限制音频编号输入为0-100
	if (iAudioSampleNo >100)
	{
		SetDlgItemInt(IDC_EDT_PLAY_AUDIO_NO, iAudioSampleNo / 10);
	}
	return;
}

//开启关闭实时音量值上传
void CLS_AudioParamPage::OnBnClickedChkGetaudioEnable()
{
	int iGetAudioEnable = m_chkGetAudio.GetCheck() ? GET_AUDIO_ENABLE_ON : GET_AUDIO_ENABLE_OFF;
	int iSceneId = (int)m_cboSceneId.GetItemData(m_cboSceneId.GetCurSel());
	
	if (GET_AUDIO_ENABLE_ON == iGetAudioEnable)
	{
		if (iSceneId != m_iCurrentSceneId)
		{
			CommandGetAudio(m_iCurrentSceneId, GET_AUDIO_ENABLE_OFF);
		}
	}

	CommandGetAudio(iSceneId, iGetAudioEnable);
	m_iCurrentSceneId = iSceneId;
}

void CLS_AudioParamPage::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUser)
{
	if (_iLogonID != m_iLogonID)
	{
		return;
	}

	switch(_iParaType)
	{
	case PARA_AUDIO_DETECTION:
		UI_UpdateCurrentVolume();
		break;
	case PARA_AUDIO_THRESHOLD:
		UI_UpdateMaxVolume();
		break;
	default:
		break;
	}
}

void CLS_AudioParamPage::UI_UpdateCurrentVolume()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage LogonId(%d)",m_iLogonID);
		return;
	}
	AudioDetection tAudioDetection = {0};
	tAudioDetection.iSize = sizeof(AudioDetection);
	tAudioDetection.iSceneId = (int)m_cboSceneId.GetItemData(m_cboSceneId.GetCurSel());
	int iByteReturn = 0;

	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_AUDIO_DETECTION, m_iChannelNo, &tAudioDetection, sizeof(AudioDetection), &iByteReturn);
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL,"","GetDevConfig AudioDetection(%d,%d,%d)",m_iLogonID, m_iChannelNo, tAudioDetection.iSceneId);
		goto EXIT_FUNC;
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","GetDevConfig AudioDetection(%d,%d,%d)",m_iLogonID, m_iChannelNo, tAudioDetection.iSceneId);
	} 
	
	SetDlgItemInt(IDC_EDT_CURRENT_VOLUME, tAudioDetection.iAudioValue);

EXIT_FUNC:
	return;
}

void CLS_AudioParamPage::UI_UpdateMaxVolume()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage LogonId(%d)",m_iLogonID);
		return;
	}
	AudioThreshold tAudioThreshold = {0};
	tAudioThreshold.iSize = sizeof(AudioThreshold);
	tAudioThreshold.iSceneId = (int)m_cboSceneId.GetItemData(m_cboSceneId.GetCurSel());
	int iByteReturn = 0;

	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_AUDIO_THRESHOLD, m_iChannelNo, &tAudioThreshold, sizeof(AudioThreshold), &iByteReturn);
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL,"","GetDevConfig AudioThreshold(%d,%d,%d)",m_iLogonID, m_iChannelNo, tAudioThreshold.iSceneId);
		goto EXIT_FUNC;
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","GetDevConfig AudioThreshold(%d,%d,%d)",m_iLogonID, m_iChannelNo, tAudioThreshold.iSceneId);
	} 

	SetDlgItemInt(IDC_EDT_MAX_VOLUME, tAudioThreshold.iThresholdValue);

EXIT_FUNC:
	return;
}

void CLS_AudioParamPage::OnCbnSelchangeCboSceneId()
{
	OnBnClickedChkGetaudioEnable();
	UI_UpdateMaxVolume();
}

void CLS_AudioParamPage::OnBnClickedBtnSetMaxVolume()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage LogonId(%d)",m_iLogonID);
		return;
	}
	AudioThreshold tAudioThreshold = {0};
	tAudioThreshold.iSize = sizeof(AudioThreshold);
	tAudioThreshold.iSceneId = (int)m_cboSceneId.GetItemData(m_cboSceneId.GetCurSel());

	tAudioThreshold.iThresholdValue = GetDlgItemInt(IDC_EDT_MAX_VOLUME);

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_AUDIO_THRESHOLD, m_iChannelNo, &tAudioThreshold, sizeof(AudioThreshold));
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL,"","SetDevConfig AudioThreshold(%d,%d,%d)",m_iLogonID, m_iChannelNo, tAudioThreshold.iSceneId);
		goto EXIT_FUNC;
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","SetDevConfig AudioThreshold(%d,%d,%d)",m_iLogonID, m_iChannelNo, tAudioThreshold.iSceneId);
	} 

EXIT_FUNC:
	return;
}

void CLS_AudioParamPage::OnEnChangeEdtMaxVolume()
{
 	//int iVolume = GetDlgItemInt(IDC_EDT_MAX_VOLUME);
 
 	//iVolume = (iVolume < MIN_THRESHOLD_VALUE) ? MIN_THRESHOLD_VALUE : iVolume;
 	//iVolume = (iVolume > MAX_THRESHOLD_VALUE) ? MAX_THRESHOLD_VALUE : iVolume;
 
 	//SetDlgItemInt(IDC_EDT_MAX_VOLUME, iVolume);
}

void CLS_AudioParamPage::CommandGetAudio(int _iSceneId, int _iState)
{
	GetAudio tGetAudio = {0};
	tGetAudio.iSize = sizeof(GetAudio);
	tGetAudio.iSceneId = _iSceneId;
	tGetAudio.iEnable = _iState;

	int iRet = NetClient_SendCommand(m_iLogonID, COMMAND_ID_GET_AUDIO, m_iChannelNo, (void*)&tGetAudio, sizeof(GetAudio));
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL,"","SendCommand GetAudio(%d,%d,%d)",m_iLogonID,m_iChannelNo, _iState);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","SendCommand GetAudio(%d,%d,%d)",m_iLogonID,m_iChannelNo, _iState);
	}
}
