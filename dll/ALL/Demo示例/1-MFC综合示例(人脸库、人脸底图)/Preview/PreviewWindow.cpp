// PreviewWindow.cpp : implementation file
//

#include "stdafx.h"
#include "PreviewWindow.h"
#include <math.h>
#include "ActionControl.h"
#include <share.h>
#include "NetClientDemoDlg.h"

#include "mmsystem.h"
#pragma comment(lib, "Winmm.lib")

#define MULTIPLY_SCREEN 0
#define SINGLE_SCREEN 1
#define FULL_SCREEN 2
//default parameter
#define DEFAULT_BRIGHTNESS	128			//default brightness
#define DEFAULT_CONTRAST	128			//default contrast
#define DEFAULT_SATURATION  128			//default saturation
#define DEFAULT_HUE			128			//default hue
#define DEFAULT_SPEED		50			//default speed
#define DEFAULT_VOLUME		30000		//default speed

#define WM_INPUTTALKING_END WM_USER+4000           //  InputTalk End Okay

#define USER_ERROR  0x10000000
#define ERROR_ALREADY_INTERTALK			(USER_ERROR+0x32)

char* pcRecordSuffix[] = {".sdv",".avi",".asf",".sdv",".aac",".sdv",".mp4",".ts",".ps"};


HWND CLS_PreviewWindow::s_hWnd = NULL;

// CLS_PreviewWindow dialog

IMPLEMENT_DYNAMIC(CLS_PreviewWindow, CDialog)

BEGIN_MESSAGE_MAP(CLS_PreviewWindow, CLS_BaseWindow)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_WINDOW_NUM, &CLS_PreviewWindow::OnCbnSelchangeComboWindowNum)
	ON_CBN_SELCHANGE(IDC_COMBO_NETDELAY, &CLS_PreviewWindow::OnCbnSelchangeComboNetdelay)
	ON_BN_CLICKED(IDC_BTN_DEFAUT, &CLS_PreviewWindow::OnBnClickedBtnDefaut)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BRIGHTNESS, &CLS_PreviewWindow::OnNMCustomdrawSliderBrightness)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CONTRAST, &CLS_PreviewWindow::OnNMCustomdrawSliderContrast)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SATURATION, &CLS_PreviewWindow::OnNMCustomdrawSliderSaturation)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_HUE, &CLS_PreviewWindow::OnNMCustomdrawSliderHue)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SPEED, &CLS_PreviewWindow::OnNMCustomdrawSliderSpeed)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_VOLUME, &CLS_PreviewWindow::OnNMCustomdrawSliderVolume)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHK_AUDIO, &CLS_PreviewWindow::OnBnClickedChkAudio)
	ON_BN_CLICKED(IDC_CHK_TALK, &CLS_PreviewWindow::OnBnClickedChkTalk)
	ON_BN_CLICKED(IDC_CHK_RECORD, &CLS_PreviewWindow::OnBnClickedChkRecord)
	ON_COMMAND_RANGE(ID_RECORD_SDV, ID_RECORD_PS, &CLS_PreviewWindow::OnRecord)
	ON_COMMAND_RANGE(ID_TALK_SINGLE, ID_TALK_INPUTTALK, &CLS_PreviewWindow::OnTalk)
	ON_COMMAND_RANGE(ID_SNATCH_BMP, ID_SNATCH_YUV, &CLS_PreviewWindow::OnSnatch)
	ON_BN_CLICKED(IDC_BTN_SNATCH, &CLS_PreviewWindow::OnBnClickedBtnSnatch)
	ON_BN_CLICKED(IDC_CHECK_HOR_AUTO, &CLS_PreviewWindow::OnBnClickedCheckHorAuto)
	ON_BN_CLICKED(IDC_CHK_LIGHT, &CLS_PreviewWindow::OnBnClickedChkLight)
	ON_BN_CLICKED(IDC_CHK_POWER, &CLS_PreviewWindow::OnBnClickedChkPower)
	ON_BN_CLICKED(IDC_CHK_RAIN, &CLS_PreviewWindow::OnBnClickedChkRain)
	ON_BN_CLICKED(IDC_BUTTON_ASSISTANT_ON, &CLS_PreviewWindow::OnBnClickedButtonAssistantOn)
	ON_BN_CLICKED(IDC_BUTTON_ASSISTANT_OFF, &CLS_PreviewWindow::OnBnClickedButtonAssistantOff)
	ON_BN_CLICKED(IDC_BUTTON_SET_PRESET, &CLS_PreviewWindow::OnBnClickedButtonSetPreset)
	ON_BN_CLICKED(IDC_BUTTON_CALL_PRESET, &CLS_PreviewWindow::OnBnClickedButtonCallPreset)
	ON_BN_CLICKED(IDC_BTN_FORCE_IFRAME, &CLS_PreviewWindow::OnBnClickedBtnForceIframe)
	ON_MESSAGE(WM_INPUTTALKING_END, &CLS_PreviewWindow::OnTalkEnd)
	ON_WM_TIMER()
END_MESSAGE_MAP()

CLS_PreviewWindow::CLS_PreviewWindow(CWnd* pParent /*=NULL*/)
	: CLS_BaseWindow(CLS_PreviewWindow::IDD, pParent)
{
	m_iCurrentVideo = 0;
	m_iRows = 0;
	m_cbkVideoChanged  = NULL;
	m_pUserData = NULL;
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iComNo = 1;
	m_iAddress = 0;
	m_iWorkMode = 1;
	memset(m_cDeviceType,0,sizeof(m_cDeviceType));
	m_iClickNum = 0;
	m_hReverse = NULL;
	InitializeCriticalSection(&m_csCriticalSession);
}

CLS_PreviewWindow::~CLS_PreviewWindow()
{
	m_cbkVideoChanged  = NULL;
	m_pUserData = NULL;
	DeleteCriticalSection(&m_csCriticalSession);
}

void CLS_PreviewWindow::DoDataExchange(CDataExchange* pDX)
{
	CLS_BaseWindow::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WINDOW_NUM, m_cboWindowNum);
	DDX_Control(pDX, IDC_COMBO_NETDELAY, m_cboNetDelay);
	DDX_Control(pDX, IDC_SLIDER_BRIGHTNESS, m_sldBrightness);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_sldContrast);
	DDX_Control(pDX, IDC_SLIDER_SATURATION, m_sldSatuation);
	DDX_Control(pDX, IDC_SLIDER_HUE, m_sldHue);
	DDX_Control(pDX, IDC_SLIDER_SPEED, m_sldSpeed);
	DDX_Control(pDX, IDC_SLIDER_VOLUME, m_sldVolume);
	DDX_Control(pDX, IDC_SPIN_PRESET, m_spinPreset);
	DDX_Control(pDX, IDC_EDIT_PRESET, m_edtPreset);
	DDX_Control(pDX, IDC_COMBO_ASSISTANT, m_cboAssistant);
}

int CLS_PreviewWindow::ShowVideoWindow( int _iRows)
{
	if (_iRows <= 0 || _iRows*_iRows > MAX_VIDEO_NUM)
	{
		return -1;
	}

	if (1 == _iRows)
	{
		m_iClickNum = 1;
	}
	else
	{
		m_iClickNum = 0;
	}
	m_pVideo[m_iCurrentVideo]->DrawRect(GetSysColor(COLOR_BTNFACE));
	RECT rcShow = {0};
	GetDlgItem(IDC_STATIC_CENTER_BG)->GetWindowRect(&rcShow);
	ScreenToClient(&rcShow);
	int iWidth = (rcShow.right - rcShow.left)/_iRows;
	int iHeight = (rcShow.bottom - rcShow.top)/_iRows;
	m_pVideo[m_iCurrentVideo]->SetParent((CWnd *)this);
	m_pVideo[m_iCurrentVideo]->ModifyStyle(WS_POPUP, WS_CHILD);
	RECT rcVideo = {0};
	for (int i = 0; i < _iRows; ++i)
	{
		for (int j = 0; j < _iRows; ++j)
		{
			rcVideo.left = j*iWidth+1;
			rcVideo.right = rcVideo.left + iWidth-2;
			rcVideo.top = i*iHeight+1;
			rcVideo.bottom = rcVideo.top + iHeight-2;
			m_pVideo[i*_iRows+j]->MoveWindow(&rcVideo);
			m_pVideo[i*_iRows+j]->ShowWindow(SW_SHOW);
			m_pVideo[i*_iRows+j]->RedrawWindow();
		}
	}
	memset(&rcVideo,0,sizeof(RECT));
	for (int i = _iRows*_iRows; i < MAX_VIDEO_NUM; ++i)
	{
		m_pVideo[i]->MoveWindow(&rcVideo);
		m_pVideo[i]->ShowWindow(SW_HIDE);
	}

	m_iRows = _iRows;
	if (m_iCurrentVideo >= m_iRows*m_iRows)
	{
		m_iCurrentVideo = 0;
	}
	m_pVideo[m_iCurrentVideo]->DrawRect(RGB(255,0,0));

	return 0;
}

BOOL CLS_PreviewWindow::OnInitDialog()
{
	CLS_BaseWindow::OnInitDialog();

	UI_UpdateDialog();

	m_cboNetDelay.SetCurSel(0);

	CString strWindowNum;
	int iRows = (int)sqrt(MAX_VIDEO_NUM*1.0);
	for (int i = 1; i <= iRows;++i)
	{
		strWindowNum.Format(_T("%d"),i*i);
		m_cboWindowNum.AddString(strWindowNum);
	}
	m_cboWindowNum.SetCurSel(1);

	m_sldBrightness.SetRange(0,255,TRUE);
	m_sldBrightness.SetPos(DEFAULT_BRIGHTNESS);
	m_sldHue.SetRange(0,255,TRUE);
	m_sldHue.SetPos(DEFAULT_HUE);
	m_sldSatuation.SetRange(0,255,TRUE);
	m_sldSatuation.SetPos(DEFAULT_SATURATION);
	m_sldContrast.SetRange(0,255,TRUE);
	m_sldContrast.SetPos(DEFAULT_CONTRAST);
	m_sldSpeed.SetRange(1,100,TRUE);
	m_sldSpeed.SetPos(DEFAULT_SPEED);
	m_sldVolume.SetRange(0,65535,TRUE);
	m_sldVolume.SetPos(0);
	m_sldVolume.SetLineSize(655);

	m_edtPreset.SetLimitText(3);	
	m_spinPreset.SetRange(1,255);
	m_spinPreset.SetBuddy(&m_edtPreset);
	SetDlgItemInt(IDC_EDIT_PRESET,1);

	for (int i = 1; i <= 8; ++i)
	{
		m_cboAssistant.AddString(IntToString(i));
	}
	m_cboAssistant.SetCurSel(0);

	m_tipCtrl.Create(this,TTF_ALWAYSTIP);
	m_tipCtrl.AddTool(&m_cboAssistant,GetTextEx(IDS_PREVIEW_ASSITANT));
	m_tipCtrl.AddTool(&m_edtPreset,GetTextEx(IDS_PREVIEW_PRESET));
	m_tipCtrl.SetDelayTime(150);
    
	ShowVideoWindow(2);
	s_hWnd = this->GetSafeHwnd();
	
	return TRUE; 
}

int CLS_PreviewWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CLS_BaseWindow::OnCreate(lpCreateStruct) == -1)
		return -1;

	RECT rcShow = {0};
	for(int i = 0; i <= MAX_VIDEO_NUM; ++i)
	{
		m_pVideo[i] = CLS_VideoView::CreateInstance(i,this);
	}
	if (m_pVideo[MAX_VIDEO_NUM])
	{
		RECT rcVideo = {0};
		rcVideo.right = GetSystemMetrics(SM_CXSCREEN);
		rcVideo.bottom = GetSystemMetrics(SM_CYSCREEN);
		m_pVideo[MAX_VIDEO_NUM]->ShowWindow(SW_HIDE);
		m_pVideo[MAX_VIDEO_NUM]->SetParent(NULL);
		m_pVideo[MAX_VIDEO_NUM]->ModifyStyle(WS_CHILD,WS_POPUP);
		m_pVideo[MAX_VIDEO_NUM]->MoveWindow(&rcVideo);
	}

	return 0;
}

void CLS_PreviewWindow::OnCbnSelchangeComboWindowNum()
{
	ShowVideoWindow(m_cboWindowNum.GetCurSel()+1);
}

void CLS_PreviewWindow::OnVideoViewClicked( int _iID )
{
	//if (m_iCurrentVideo != _iID)
	{
		m_pVideo[m_iCurrentVideo]->DrawRect(GetSysColor(COLOR_BTNFACE));
		m_iCurrentVideo = _iID;
		m_pVideo[m_iCurrentVideo]->DrawRect(RGB(255,0,0));

		if (m_cbkVideoChanged)
		{
			m_cbkVideoChanged(m_pVideo[m_iCurrentVideo],m_pUserData);
		}
		UI_UpdateWindow();
	}
}

void CLS_PreviewWindow::OnVideoViewDblclk( int _iID )
{
	if (-1 == m_pVideo[m_iCurrentVideo]->GetConnID())
	{
		m_iClickNum = 0;
		return;
	}

	m_iClickNum = (m_iClickNum+1)%3;
	switch (m_iClickNum)
	{
	case MULTIPLY_SCREEN:
		{
			ShowMultiplyWindow();
		}
		break;
	case SINGLE_SCREEN:
		{
			ShowSingleWindow();
		}
		break;
	case FULL_SCREEN:
		{
			ShowFullWindow();
		}
		break;
	}
}

void CLS_PreviewWindow::OnDestroy()
{
	CLS_BaseWindow::OnDestroy();

	PCHANNEL_INFO pChannel = NULL;
	for(int i = 0; i <= MAX_VIDEO_NUM; ++i)
	{
		if(m_pVideo[i])
		{
			m_pVideo[i]->DestroyWindow();
			delete m_pVideo[i];
			m_pVideo[i] = NULL;
		}
	}
}

BOOL CLS_PreviewWindow::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch(HIWORD(wParam))
	{
	case STN_CLICKED:
		{
			if (lParam)
			{
				CLS_VideoView* pVideo = (CLS_VideoView*)CWnd::FromHandle((HWND)lParam);
				if (pVideo)
				{
					int iID = pVideo->GetID();
					if (iID >= 0 && iID < MAX_VIDEO_NUM)
					{
						OnVideoViewClicked(iID);
					}
				}
			}
		}
		break;
	case STN_DBLCLK:
		{
			if (lParam)
			{
				CLS_VideoView* pVideo = (CLS_VideoView*)CWnd::FromHandle((HWND)lParam);
				if (pVideo)
				{
					int iID = pVideo->GetID();
					if (iID >= 0 && iID < MAX_VIDEO_NUM)
					{
						OnVideoViewDblclk(iID);
					}
				}
			}		
		}
		break;
	}

	return CLS_BaseWindow::OnCommand(wParam, lParam);
}

CLS_VideoView* CLS_PreviewWindow::GetCurrentVideoView()
{
	return m_pVideo[m_iCurrentVideo];
}

CLS_VideoView* CLS_PreviewWindow::GetFreeVideoView()
{
	if (m_pVideo[m_iCurrentVideo] && m_pVideo[m_iCurrentVideo]->GetConnID() == -1)
	{
		return m_pVideo[m_iCurrentVideo];
	}

	for (int i = 0; i < m_iRows*m_iRows; ++i)
	{
		if (m_pVideo[i] && m_pVideo[i]->GetConnID() == -1)
		{
			return m_pVideo[i];
		}
	}

	return NULL;
}

void CLS_PreviewWindow::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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
	
	UI_UpdateTalk();
	UI_UpdatePTZ();
	if (_iLogonID < 0 || _iChannelNo < 0 || _iStreamNo < 0)
	{
		return;
	}

	unsigned int uConnID = -1;
	PCHANNEL_INFO pChannel = FindChannel(_iLogonID,_iChannelNo,_iStreamNo,&uConnID);
	if (pChannel && pChannel->pVideo)
	{
		CLS_VideoView* pVideo = (CLS_VideoView*)pChannel->pVideo;
		int iID = pVideo->GetID();
		//if (iID != m_iCurrentVideo && iID >= 0 && iID < MAX_VIDEO_NUM)
		{
			OnVideoViewClicked(iID);
		}
	}
}

void CLS_PreviewWindow::SetVideoChangedNotify( VIDED_CHANGED_NOTIFY _cbkNotify,void* _pUserData )
{
	m_cbkVideoChanged = _cbkNotify;
	m_pUserData = _pUserData;
}

void CLS_PreviewWindow::OnCbnSelchangeComboNetdelay()
{
	if (m_pVideo[m_iCurrentVideo])
	{
		unsigned int uConnID = m_pVideo[m_iCurrentVideo]->GetConnID();
		PCHANNEL_INFO pChannel = FindChannel(uConnID);
		if (pChannel)
		{
			int iDelay = m_cboNetDelay.GetCurSel();
			int iRet = NetClient_SetPlayerShowFrameMode(pChannel->iLogonID,pChannel->iChannelNo,iDelay,pChannel->iStreamNo);
			if (0 == iRet)
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_SetPlayerShowFrameMode(%d,%d,%d,%d)"
					,pChannel->iLogonID,pChannel->iChannelNo,iDelay,pChannel->iStreamNo);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_SetPlayerShowFrameMode(%d,%d,%d,%d)"
					,pChannel->iLogonID,pChannel->iChannelNo,iDelay,pChannel->iStreamNo);
			}
		}
	}
}

void CLS_PreviewWindow::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
	m_tipCtrl.UpdateTipText(GetTextEx(IDS_PREVIEW_ASSITANT),&m_cboAssistant);
	m_tipCtrl.UpdateTipText(GetTextEx(IDS_PREVIEW_PRESET),&m_edtPreset);
}

void CLS_PreviewWindow::UI_UpdateDialog()
{
	InsertString(m_cboNetDelay,0,IDS_PREVIEW_NETDELAY_LOW_DELAY);
	InsertString(m_cboNetDelay,1,IDS_PREVIEW_NETDELAY_HIGH_SMOOTH);
	InsertString(m_cboNetDelay,2,IDS_PREVIEW_NETDELAY_NO_DELAY);
	InsertString(m_cboNetDelay,3,IDS_PREVIEW_NETDELAY_BALANCE);
	InsertString(m_cboNetDelay,4,IDS_PREVIEW_NETDELAY_ADAPTIVE);

	SetDlgItemTextEx(IDC_STATIC_NETDELAY,IDS_PREVIEW_NETDELAY);
	SetDlgItemTextEx(IDC_STATIC_WIN_NUM,IDS_PREVIEW_WINDOW_NUM);
	SetDlgItemTextEx(IDC_CHK_AUDIO,IDS_PREVIEW_AUDIO);
	SetDlgItemTextEx(IDC_CHK_TALK,IDS_PREVIEW_TALK);
	SetDlgItemTextEx(IDC_CHK_RECORD,IDS_PREVIEW_RECORD);
	SetDlgItemTextEx(IDC_BTN_SNATCH,IDS_PREVIEW_SNATCH);
	SetDlgItemTextEx(IDC_BTN_FORCE_IFRAME,IDS_PREVIEW_FORCE_IFRAME);
	SetDlgItemTextEx(IDC_STATIC_BRIGHTNESS,IDS_PREVIEW_BRIGHTNESS);
	SetDlgItemTextEx(IDC_STATIC_HUE,IDS_PREVIEW_HUE);
	SetDlgItemTextEx(IDC_STATIC_CONTRAST,IDS_PREVIEW_CONTRAST);
	SetDlgItemTextEx(IDC_STATIC_SATURATION,IDS_PREVIEW_SATURATION);
	SetDlgItemTextEx(IDC_BTN_DEFAUT,IDS_PREVIEW_DEFAULT);
	SetDlgItemTextEx(IDC_STATIC_SPEED,IDS_PREVIEW_SPEED);
	SetDlgItemTextEx(IDC_STATIC_VOLUME,IDS_PREVIEW_VOLUME);
	SetDlgItemTextEx(IDC_STATIC_ZOOM,IDS_PREVIEW_ZOOM);
	SetDlgItemTextEx(IDC_BUTTON_ZOOM_BIG,IDS_PREVIEW_ZOOM_BIG);
	SetDlgItemTextEx(IDC_BUTTON_ZOOM_SMALL,IDS_PREVIEW_ZOOM_SMALL);
	SetDlgItemTextEx(IDC_STATIC_IRIS,IDS_PREVIEW_IRIS);
	SetDlgItemTextEx(IDC_BUTTON_IRIS_OPEN,IDS_PREVIEW_IRIS_OPEN);
	SetDlgItemTextEx(IDC_BUTTON_IRIS_CLOSE,IDS_PREVIEW_IRIS_CLOSE);
	SetDlgItemTextEx(IDC_STATIC_FOCUS,IDS_PREVIEW_FOCUS);
	SetDlgItemTextEx(IDC_BUTTON_FOCUS_NEAR,IDS_PREVIEW_FOCUS_NEAR);
	SetDlgItemTextEx(IDC_BUTTON_FOCUS_FAR,IDS_PREVIEW_FOCUS_FAR);
	SetDlgItemTextEx(IDC_CHK_LIGHT,IDS_PREVIEW_LIGHT);
	SetDlgItemTextEx(IDC_CHK_POWER,IDS_PREVIEW_POWER);
	SetDlgItemTextEx(IDC_CHK_RAIN,IDS_PREVIEW_RAIN_BRUSH);
	SetDlgItemTextEx(IDC_BUTTON_ASSISTANT_ON,IDS_PREVIEW_ASSISTANT_ON);
	SetDlgItemTextEx(IDC_BUTTON_ASSISTANT_OFF,IDS_PREVIEW_ASSISTANT_OFF);
	SetDlgItemTextEx(IDC_BUTTON_SET_PRESET,IDS_PREVIEW_SET_PRESET);
	SetDlgItemTextEx(IDC_BUTTON_CALL_PRESET,IDS_PREVIEW_CALL_PRESET);
	SetDlgItemTextEx(IDC_BUTTON_MOVE_UP,IDS_PREVIEW_MOVE_UP);
	SetDlgItemTextEx(IDC_BUTTON_MOVE_UP_LEFT,IDS_PREVIEW_MOVE_UP_LEFT);
	SetDlgItemTextEx(IDC_BUTTON_MOVE_UP_RIGHT,IDS_PREVIEW_MOVE_UP_RIGHT);
	SetDlgItemTextEx(IDC_BUTTON_MOVE_DOWN,IDS_PREVIEW_MOVE_DOWN);
	SetDlgItemTextEx(IDC_BUTTON_MOVE_DOWN_LEFT,IDS_PREVIEW_MOVE_DOWN_LEFT);
	SetDlgItemTextEx(IDC_BUTTON_MOVE_DOWN_RIGHT,IDS_PREVIEW_MOVE_DOWN_RIGHT);
	SetDlgItemTextEx(IDC_BUTTON_MOVE_LEFT,IDS_PREVIEW_MOVE_LEFT);
	SetDlgItemTextEx(IDC_BUTTON_MOVE_RIGHT,IDS_PREVIEW_MOVE_RIGHT);
	SetDlgItemTextEx(IDC_CHECK_HOR_AUTO,IDS_PREVIEW_HOR_AUTO);
}

void CLS_PreviewWindow::UI_UpdateWindow()
{
	BOOL bIsAudioPlaying = FALSE;
	BOOL bIsRecording = FALSE;
	m_iLogonID = -1;
	m_iChannelNo = 0;
	if (m_pVideo[m_iCurrentVideo])
	{
		unsigned int uConnID = m_pVideo[m_iCurrentVideo]->GetConnID();
		PCHANNEL_INFO pChannel = FindChannel(uConnID);
		if (pChannel)
		{
			m_iLogonID = pChannel->iLogonID;
			m_iChannelNo = pChannel->iChannelNo;

			int iDelay = NetClient_GetPlayerShowFrameMode(pChannel->iLogonID,pChannel->iChannelNo,pChannel->iStreamNo);
			m_cboNetDelay.SetCurSel(iDelay);

			STR_VideoParam tVideoParam = {0};
			int iRet = NetClient_GetVideoPara(pChannel->iLogonID,pChannel->iChannelNo,&tVideoParam);
			if (0 == iRet)
			{
				m_sldBrightness.SetPos(tVideoParam.m_u16Brightness);
				m_sldContrast.SetPos(tVideoParam.m_u16Contrast);
				m_sldHue.SetPos(tVideoParam.m_u16Hue);
				m_sldSatuation.SetPos(tVideoParam.m_u16Saturation);
				AddLog(LOG_TYPE_SUCC,"","NetClient_GetVideoPara(%d,%d,)",pChannel->iLogonID,pChannel->iChannelNo);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_GetVideoPara(%d,%d,)",pChannel->iLogonID,pChannel->iChannelNo);
			}

			if (BST_UNCHECKED != IsDlgButtonChecked(IDC_CHK_AUDIO))
			{
				int iVolume = 0;
				iRet = NetClient_GetLocalAudioVolumeEx(uConnID, &iVolume);
				if (0 == iRet)
				{
					AddLog(LOG_TYPE_SUCC,"","NetClient_GetLocalAudioVolumeEx(%u,%d)",uConnID,iVolume);
				}
				else
				{
					AddLog(LOG_TYPE_FAIL,"","NetClient_GetLocalAudioVolumeEx(%u,%d)",uConnID,iVolume);
				}
				m_sldVolume.SetPos(iVolume);
			}			
			
			bIsAudioPlaying = pChannel->bIsAudioPlaying;
			bIsRecording = pChannel->bIsRecording;
		}
	}
	CheckDlgButton(IDC_CHK_AUDIO,bIsAudioPlaying);
	CheckDlgButton(IDC_CHK_RECORD,bIsRecording);

// 	UI_UpdateTalk();
// 	UI_UpdatePTZ();
}

void CLS_PreviewWindow::OnBnClickedBtnDefaut()
{
	m_sldBrightness.SetPos(DEFAULT_BRIGHTNESS);
	m_sldHue.SetPos(DEFAULT_HUE);
	m_sldSatuation.SetPos(DEFAULT_SATURATION);
	m_sldContrast.SetPos(DEFAULT_CONTRAST);
	SetVideoParam();
}

void CLS_PreviewWindow::OnNMCustomdrawSliderBrightness(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	int iBrightness = m_sldBrightness.GetPos();
	SetDlgItemInt(IDC_STATIC_BRIGHTNESS_VALUE,iBrightness);

	*pResult = 0;
}

void CLS_PreviewWindow::OnNMCustomdrawSliderContrast(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	int iContrast = m_sldContrast.GetPos();
	SetDlgItemInt(IDC_STATIC_CONTRAST_VALUE,iContrast);

	*pResult = 0;
}

void CLS_PreviewWindow::OnNMCustomdrawSliderSaturation(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	int iSatuation = m_sldSatuation.GetPos();
	SetDlgItemInt(IDC_STATIC_SATURATION_VALUE,iSatuation);

	*pResult = 0;
}

void CLS_PreviewWindow::OnNMCustomdrawSliderHue(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	int iHue = m_sldHue.GetPos();
	SetDlgItemInt(IDC_STATIC_HUE_VALUE,iHue);

	*pResult = 0;
}

void CLS_PreviewWindow::OnNMCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	int iSpeed = m_sldSpeed.GetPos();
	if (iSpeed <= 1)
	{
		iSpeed = 0;
	}
	SetDlgItemInt(IDC_STATIC_SPEED_VALUE,iSpeed);

	*pResult = 0;
}

void CLS_PreviewWindow::OnNMCustomdrawSliderVolume(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	int iVolume = m_sldVolume.GetPos();
	SetDlgItemInt(IDC_STATIC_VOLUME_VALUE,iVolume*100/65535);

	*pResult = 0;
}

void CLS_PreviewWindow::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (SB_ENDSCROLL == nSBCode)
	{
		int iCtrlID = pScrollBar->GetDlgCtrlID();
		switch(iCtrlID)
		{
		case IDC_SLIDER_BRIGHTNESS:
		case IDC_SLIDER_CONTRAST:
		case IDC_SLIDER_HUE:
		case IDC_SLIDER_SATURATION:
			{
				SetVideoParam();
			}
			break;
		case IDC_SLIDER_VOLUME:
			{
				SetAudioVolume();
			}
			break;
		default:
			break;
		}
	}

	CLS_BaseWindow::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CLS_PreviewWindow::SetVideoParam()
{
	if (m_pVideo[m_iCurrentVideo])
	{
		unsigned int uConnID = m_pVideo[m_iCurrentVideo]->GetConnID();
		PCHANNEL_INFO pChannel = FindChannel(uConnID);
		if (pChannel)
		{
			STR_VideoParam tVideoParam = {0};
			tVideoParam.m_u16Saturation = m_sldSatuation.GetPos();
			tVideoParam.m_u16Brightness = m_sldBrightness.GetPos();
			tVideoParam.m_u16Contrast = m_sldContrast.GetPos();
			tVideoParam.m_u16Hue = m_sldHue.GetPos();

			int iRet = NetClient_SetVideoPara(pChannel->iLogonID,pChannel->iChannelNo,&tVideoParam);	
			if (0 == iRet)
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_SetVideoPara(%d,%d,)",pChannel->iLogonID,pChannel->iChannelNo);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_SetVideoPara(%d,%d,)",pChannel->iLogonID,pChannel->iChannelNo);
			}
		}
	}
}

void CLS_PreviewWindow::SetAudioVolume()
{
	if (NULL == m_pVideo[m_iCurrentVideo])
	{
		return;
	}

	unsigned int uConnID = m_pVideo[m_iCurrentVideo]->GetConnID();
	if (-1 != uConnID)
	{

	
		int iVolume = m_sldVolume.GetPos();

		if (0 == iVolume)
		{
			NetClient_AudioStop(uConnID);
		}
		else
		{
			NetClient_AudioStart(uConnID);
		}

		int iRet = NetClient_SetLocalAudioVolumeEx(uConnID, iVolume);
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetLocalAudioVolumeEx(%u,%d)",uConnID,iVolume);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetLocalAudioVolumeEx(%u,%d)",uConnID,iVolume);
		}
	}
}

void CLS_PreviewWindow::OnBnClickedChkAudio()
{
	BOOL bIsAudioPlaying = FALSE;
	if(m_pVideo[m_iCurrentVideo])
	{
		unsigned int uConnID = m_pVideo[m_iCurrentVideo]->GetConnID();
		PCHANNEL_INFO pChannel = FindChannel(uConnID);
		if (pChannel)
		{
			int iRet = 0;
			BOOL bChecked = IsDlgButtonChecked(IDC_CHK_AUDIO);
			if(bChecked)
			{
				iRet = NetClient_AudioStart(uConnID);
				if(iRet == 0)
				{
					bIsAudioPlaying = TRUE;
					AddLog(LOG_TYPE_SUCC,"","NetClient_AudioStart(%u)",uConnID);
				}
				else
				{
					AddLog(LOG_TYPE_FAIL,"","NetClient_AudioStart(%u)",uConnID);
				}
			}
			else
			{
				iRet = NetClient_AudioStop(uConnID);
				if (0 == iRet)
				{
					AddLog(LOG_TYPE_SUCC,"","NetClient_AudioStop(%u)",uConnID);
				}
				else
				{
					AddLog(LOG_TYPE_FAIL,"","NetClient_AudioStop(%u)",uConnID);
				}
			}
			pChannel->bIsAudioPlaying = bIsAudioPlaying;
		}
	}
	CheckDlgButton(IDC_CHK_AUDIO,bIsAudioPlaying);
}

void CLS_PreviewWindow::OnBnClickedChkTalk()
{
	PDEVICE_INFO pDevice = FindDevice(m_iLogonID);
	if (pDevice)
	{
		int iRet = 0;
		BOOL bChecked = IsDlgButtonChecked(IDC_CHK_TALK);
		if(bChecked)
		{
			RECT rcShow = {0};
			GetDlgItem(IDC_CHK_TALK)->GetWindowRect(&rcShow);
			CMenu menu;
			menu.CreatePopupMenu();
			menu.AppendMenu(MF_STRING,ID_TALK_SINGLE,GetTextEx(IDS_MENU_TALK_SINGLE));
			menu.AppendMenu(MF_STRING,ID_TALK_INNER,GetTextEx(IDS_MENU_TALK_INNER));
			menu.AppendMenu(MF_STRING,ID_TALK_BROADCAST,GetTextEx(IDS_MENU_TALK_BROADCAST));
			menu.AppendMenu(MF_STRING,ID_TALK_INPUTTALK,GetTextEx(IDS_MENU_TALK_INPUTDATA));
			menu.CheckMenuRadioItem(ID_TALK_SINGLE,ID_TALK_INPUTTALK,ID_TALK_SINGLE+pDevice->iTalkType,MF_CHECKED);
			menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,rcShow.left-3,rcShow.bottom,this);
			menu.DestroyMenu();
		}
		else
		{
			if (-1 == pDevice->uiInterTalkID)
			{
				iRet = NetClient_TalkEnd(m_iLogonID);
				if (0 == iRet)
				{
					AddLog(LOG_TYPE_SUCC,"","NetClient_TalkEnd(%d)",m_iLogonID);
				}
				else
				{
					AddLog(LOG_TYPE_FAIL,"","NetClient_TalkEnd(%d)",m_iLogonID);
				}
				
			}
			else
			{
				iRet = NetClient_InterTalkEnd(pDevice->uiInterTalkID,true);
				if (0 == iRet)
				{
					AddLog(LOG_TYPE_SUCC,"","NetClient_InterTalkEnd(%u,true)",pDevice->uiInterTalkID);
				}
				else
				{
					AddLog(LOG_TYPE_FAIL,"","NetClient_InterTalkEnd(%u,false)",pDevice->uiInterTalkID);
				}
				pDevice->uiInterTalkID = -1;
			}
		}
		pDevice->bIsTalking = 0;
	}
	CheckDlgButton(IDC_CHK_TALK,FALSE);
}

void CLS_PreviewWindow::OnTalk( UINT nID )
{
	int iType = nID-ID_TALK_SINGLE;

	PDEVICE_INFO pDevice = FindDevice(m_iLogonID);
	if (pDevice)
	{
		switch(iType)
		{
		case 0://single talk
		case 1://inner talk
			if(0 == NetClient_TalkStart(m_iLogonID,false))
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_TalkStart(%d)",m_iLogonID);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_TalkStart(%d)",m_iLogonID);
			}
			break;
		case 2://broadcast
			if(0 == NetClient_TalkStart(-1, false))
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_TalkStart(%d)",m_iLogonID);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_TalkStart(%d)",m_iLogonID);
			}
			break;
		case 3://inputstream
			if (0 ==  NetClient_TalkStart(m_iLogonID, true))
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_TalkStart(%d)",m_iLogonID);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_TalkStart(%d)",m_iLogonID);
			}
			break;
		default:
			break;
		}
		pDevice->iTalkType = iType;
	}
}

void CLS_PreviewWindow::UI_UpdateTalk()
{
	PDEVICE_INFO pDevice = FindDevice(m_iLogonID);
	if (pDevice && pDevice->bIsTalking)
	{
		CheckDlgButton(IDC_CHK_TALK,TRUE);
	}
	else
	{
		CheckDlgButton(IDC_CHK_TALK,FALSE);
	}
}

void CLS_PreviewWindow::OnMainNotify( int _iLogonID,int _wParam, void* _iLParam, void* _iUser  )
 {
	int iMsgType = LOWORD(_wParam);
	int iChNo = _wParam>>16 & 0xFFFF;
	switch(iMsgType)
	{
		//视频头消息
		//lParam:通道
	case WCM_VIDEO_HEAD_EX:
		{
			unsigned int uiConnID = (unsigned int)_iLParam;
			PCHANNEL_INFO pChannel = FindChannel(uiConnID);
			if (pChannel)
			{
				if (pChannel->bIsAudioPlaying)
				{
					int iRet = NetClient_AudioStart(uiConnID);
					if(iRet == 0)
					{
						AddLog(LOG_TYPE_SUCC,"","NetClient_AudioStart(%u)",uiConnID);
					}
					else
					{
						pChannel->bIsAudioPlaying = FALSE;
						AddLog(LOG_TYPE_FAIL,"","NetClient_AudioStart(%u)",uiConnID);
					}
				}
			}
			ResumeRecord(uiConnID);		
		}
		break;

		//对讲状态消息
		//lParam:对讲状态
	case WCM_TALK:
		TalkNotify(_iLogonID,(int)_iLParam);		
		break;

		//双向对讲成功消息
		//lParam，双向对讲ID
	case WCM_INTERTALK_READY:
		{ 
			InterTalkNotify((unsigned int)_iLParam);
		}
		break;

	case WCM_CHANNEL_TALK:
		{
			m_pVideo[iChNo]->ChannelTalkNotify(_iLogonID, iChNo, (int)_iLParam);			
		}
		break;
	case WCM_RECORD_OVER_MAX_LIMIT:
		{
			unsigned int uiConnID = (unsigned int)_iLParam;
			ResumeRecord(uiConnID);
			AddLog(LOG_TYPE_MSG,"%d","WCM_RECORD_OVER_MAX_LIMIT %u",_iLogonID,uiConnID);
		}
		break;

	case WCM_RECORD_ERR:
		{
			unsigned int uiConnID = (unsigned int)_iLParam;
			AddLog(LOG_TYPE_MSG,"%d","WCM_RECORD_ERR %u",_iLogonID,uiConnID);
			PCHANNEL_INFO pChannel = FindChannel(uiConnID);
			if (pChannel)
			{
				pChannel->bIsRecording = NULL;
				if (pChannel->pfYuv)
				{
					fclose(pChannel->pfYuv);
					AddLog(LOG_TYPE_SUCC,"","fclose(%#x)",pChannel->pfYuv);
					pChannel->pfYuv = NULL;
				}
				if (pChannel->pfPcm)
				{
					fclose(pChannel->pfPcm);
					AddLog(LOG_TYPE_SUCC,"","fclose(%#x)",pChannel->pfPcm);
					pChannel->pfPcm = NULL;
				}
			}
		}
		break;
	default:
		break;
	}
}

void CLS_PreviewWindow::TalkNotify(int _iLogonID,int _iTalkStatus)
{
	PDEVICE_INFO pDevice = FindDevice(_iLogonID);
	if (NULL == pDevice)
	{
		return;
	}

	if (TALK_BEGIN_OK == _iTalkStatus)
	{
		pDevice->bIsTalking = 1;
		AddLog(LOG_TYPE_MSG,"","[TALK_BEGIN_OK] LogonID(%d)",_iLogonID);

		int iType = pDevice->iTalkType;

		if (iType == 1)
		{
			unsigned int uiInterTalkID = -1;
			int iRet=NetClient_InterTalkStartEx(&uiInterTalkID,_iLogonID,NULL,0);
			if (0 == iRet)
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_InterTalkStartEx(%u,%d,NULL,0)",uiInterTalkID,_iLogonID);	
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_InterTalkStartEx(%u,%d,NULL,0)",uiInterTalkID,_iLogonID);
			}
			PCHANNEL_INFO pChannel = AddChannel(uiInterTalkID);
			if(pChannel)
			{
				pChannel->iLogonID = _iLogonID;
				pChannel->iChannelNo = 0;
				pChannel->iStreamNo = 2;
			}
		}
		else if (iType == 3)
		{
			static TCHAR BASED_CODE szFilter[] = _T("Record Files (*.wav)|*.wav||");
			CFileDialog file(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,this);
			if (IDOK == file.DoModal())
			{
				CString szFileName = file.GetPathName();
				strcpy_s(pDevice->cTalkInputFile, sizeof(pDevice->cTalkInputFile), szFileName.GetBuffer(0));
				if (NULL != pDevice->hEventQuitTalking)
				{
					ResetEvent(pDevice->hEventQuitTalking);
				}
				else
				{
					pDevice->hEventQuitTalking = CreateEvent(NULL, FALSE, FALSE, "");
				}
				if (NULL != pDevice->hThreadTalk)
				{
					if (NULL != pDevice->hEventQuitTalking)
					{
						SetEvent(pDevice->hEventQuitTalking);
					}
					WaitForSingleObject(pDevice->hThreadTalk,INFINITE);
					CloseHandle(pDevice->hThreadTalk);
					pDevice->hThreadTalk = NULL;
					if (NULL != pDevice->hEventQuitTalking)
					{
						ResetEvent(pDevice->hEventQuitTalking);
					}
				}
				pDevice->hThreadTalk = CreateThread(NULL, 0, ThreadInputTalking, &m_iLogonID, 0, NULL);
			}
		}
	}
	else
	{
		pDevice->bIsTalking = 0;
	}
	UI_UpdateTalk();

	switch(_iTalkStatus)
	{		
	case TALK_BEGIN_ERROR:
		{
			AddLog(LOG_TYPE_MSG,"","[TALK_BEGIN_ERROR] LogonID(%d)",_iLogonID);	
			NetClient_TalkEnd(_iLogonID);
			break;
		}
	case TALK_ERROR:	
		{
			AddLog(LOG_TYPE_MSG,"","[TALK_ERROR] LogonID(%d)",_iLogonID);	
			NetClient_TalkEnd(_iLogonID);
			break;
		}
	case TALK_END_OK:	
		{
			AddLog(LOG_TYPE_MSG,"","[TALK_END_OK] LogonID(%d)",_iLogonID);	
			break;
		}
	}
}

void CLS_PreviewWindow::InterTalkNotify(unsigned int _uiConnID)
{
	AddLog(LOG_TYPE_MSG,"","[WCM_INTERTALK_READY] ConnID(%u)",_uiConnID);	

	PCHANNEL_INFO pChannel = FindChannel(_uiConnID);
	if (pChannel)
	{
		PDEVICE_INFO pDevice = FindDevice(pChannel->iLogonID);
		if (pDevice)
		{
			RECT rctShow ={0};		
			int iRet = NetClient_StartPlay(_uiConnID, NULL, rctShow, 0);
			if (0 == iRet)
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_StartPlay(%u,NULL,,0)",_uiConnID);	

				iRet = NetClient_AudioStart(_uiConnID);
				if (0 == iRet)
				{
					AddLog(LOG_TYPE_SUCC,"","NetClient_AudioStart(%u)",_uiConnID);
				}
				else
				{
					AddLog(LOG_TYPE_FAIL,"","NetClient_AudioStart(%u)",_uiConnID);
				}
				pDevice->uiInterTalkID = _uiConnID;
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_StartPlay(%u,NULL,,0)",_uiConnID);

				iRet = NetClient_InterTalkEnd(_uiConnID,false);
				if (0 == iRet)
				{
					AddLog(LOG_TYPE_SUCC,"","NetClient_InterTalkEnd(%u)",_uiConnID);
				}
				else
				{
					AddLog(LOG_TYPE_FAIL,"","NetClient_InterTalkEnd(%u)",_uiConnID);
				}

				RemoveChannel(_uiConnID);
				pDevice->uiInterTalkID = -1;
			}
		}
	}
}

void CLS_PreviewWindow::OnBnClickedChkRecord()
{
	if(m_pVideo[m_iCurrentVideo])
	{
		unsigned int uConnID = m_pVideo[m_iCurrentVideo]->GetConnID();
		PCHANNEL_INFO pChannel = FindChannel(uConnID);
		if (pChannel)
		{
			int iRet = 0;
			BOOL bChecked = IsDlgButtonChecked(IDC_CHK_RECORD);
			if(bChecked)
			{
				RECT rcShow = {0};
				GetDlgItem(IDC_CHK_RECORD)->GetWindowRect(&rcShow);
				CMenu menu;
				menu.CreatePopupMenu();
				menu.AppendMenu(MF_STRING,ID_RECORD_SDV,GetTextEx(IDS_MENU_RECORD_SDV));
				menu.AppendMenu(MF_STRING,ID_RECORD_AVI,GetTextEx(IDS_MENU_RECORD_AVI));
				menu.AppendMenu(MF_STRING,ID_RECORD_ASF,GetTextEx(IDS_MENU_RECORD_ASF));
				menu.AppendMenu(MF_STRING,ID_RECORD_AUDIO,GetTextEx(IDS_MENU_RECORD_AUDIO));
				menu.AppendMenu(MF_STRING,ID_RECORD_AAC,GetTextEx(IDS_MENU_RECORD_AAC));
				menu.AppendMenu(MF_STRING,ID_RECORD_VIDEO,GetTextEx(IDS_MENU_RECORD_VIDEO));
				menu.AppendMenu(MF_STRING,ID_RECORD_YUV,GetTextEx(IDS_MENU_RECORD_YUV));
				menu.AppendMenu(MF_STRING,ID_RECORD_RAW,GetTextEx(IDS_MENU_RECORD_RAW));
				menu.AppendMenu(MF_STRING,ID_RECORD_PS,"PS");
				menu.CheckMenuRadioItem(ID_RECORD_SDV,ID_RECORD_RAW,ID_RECORD_SDV+pChannel->iRecordType,MF_CHECKED);
				menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,rcShow.left-3,rcShow.bottom,this);
				menu.DestroyMenu();
			}
			else
			{
				if (ID_RECORD_YUV-ID_RECORD_SDV == pChannel->iRecordType)
				{
					NetClient_SetDecCallBack_V4(uConnID, NULL, NULL);
					if (pChannel->pfYuv)
					{
						fclose(pChannel->pfYuv);
						AddLog(LOG_TYPE_SUCC,"","fclose(%#x)",pChannel->pfYuv);
						pChannel->pfYuv = NULL;
					}
					if (pChannel->pfPcm)
					{
						fclose(pChannel->pfPcm);
						AddLog(LOG_TYPE_SUCC,"","fclose(%#x)",pChannel->pfPcm);
						pChannel->pfPcm = NULL;
					}
				}
				else if(ID_RECORD_RAW - ID_RECORD_SDV == pChannel->iRecordType)
				{
					if (NULL != pChannel->pfRaw)
					{
						fclose(pChannel->pfRaw);
						AddLog(LOG_TYPE_SUCC,"","fclose(%#x)",pChannel->pfRaw);
						pChannel->pfRaw = NULL;
					}
					AddLog(LOG_TYPE_SUCC,"","NetClient_SetDecCallBackEx(%u,NULL,NULL)",uConnID);
				}
				else
				{
					iRet = NetClient_StopCaptureFile(uConnID);
					if (RET_SUCCESS == iRet)
					{
						AddLog(LOG_TYPE_SUCC,"","NetClient_StopCaptureFile(%u)",uConnID);
					}
					else
					{
						AddLog(LOG_TYPE_FAIL,"","NetClient_StopCaptureFile(%u)",uConnID);
					}
				}
			}
			pChannel->bIsRecording = FALSE;
		}
	}
	CheckDlgButton(IDC_CHK_RECORD,FALSE);
}

void CLS_PreviewWindow::OnRecord( UINT nID )
{
	BOOL bIsRecording = FALSE;
	int iType = nID-ID_RECORD_SDV;
	if (m_pVideo[m_iCurrentVideo])
	{
		unsigned int uConnID = m_pVideo[m_iCurrentVideo]->GetConnID();
		PCHANNEL_INFO pChannel = FindChannel(uConnID);
		if (pChannel)
		{
			if (ID_RECORD_YUV == nID)
			{
				int iRet = NetClient_SetDecCallBack_V4(uConnID,(DECYUV_NOTIFY_V4)&CLS_PreviewWindow::DecodeYuvNotify,(int)this);
				if (0 == iRet)
				{
					AddLog(LOG_TYPE_SUCC,"","NetClient_SetDecCallBackEx(%u)",uConnID);
					bIsRecording = TRUE;
				}
				else
				{
					AddLog(LOG_TYPE_FAIL,"","NetClient_SetDecCallBackEx(%u)",uConnID);
				}
			}
			else if(ID_RECORD_RAW == nID)
			{
				int iRet = NetClient_SetRawFrameCallBack(uConnID, (RAWFRAME_NOTIFY)&CLS_PreviewWindow::RawVideoAndAudioNotify, this);
				if (RET_SUCCESS == iRet)
				{
					AddLog(LOG_TYPE_SUCC,"","NetClient_SetRawFrameCallBack(%u)",uConnID);
					bIsRecording = TRUE;
				}
				else
				{
					AddLog(LOG_TYPE_FAIL,"","NetClient_SetRawFrameCallBack(%u)",uConnID);
				}
			}
			else
			{
				CString strFileName = MakeFileName(iType);
				int iRet = NetClient_StartCaptureFile(uConnID,(LPSTR)(LPCTSTR)strFileName,iType);
				if (RET_SUCCESS == iRet)
				{
					AddLog(LOG_TYPE_SUCC,"","NetClient_StartCaptureFile(%u,%s,%d)",uConnID,(LPSTR)(LPCTSTR)strFileName,iType);
					bIsRecording = TRUE;
				}
				else
				{
					AddLog(LOG_TYPE_FAIL,"","NetClient_StartCaptureFile(%u,%s,%d)",uConnID,(LPSTR)(LPCTSTR)strFileName,iType);
				}
			}

			pChannel->iRecordType = iType;
			pChannel->bIsRecording = bIsRecording;
		}
	}
	
	CheckDlgButton(IDC_CHK_RECORD,bIsRecording);
}

void CLS_PreviewWindow::OnBnClickedBtnSnatch()
{
	if(m_pVideo[m_iCurrentVideo])
	{
		unsigned int uConnID = m_pVideo[m_iCurrentVideo]->GetConnID();
		if (-1 != uConnID)
		{
			RECT rcShow = {0};
			GetDlgItem(IDC_BTN_SNATCH)->GetWindowRect(&rcShow);
			CMenu menu;
			menu.CreatePopupMenu();
			menu.AppendMenu(MF_STRING,ID_SNATCH_BMP,GetTextEx(IDS_MENU_SNATCH_BMP));
			menu.AppendMenu(MF_STRING,ID_SNATCH_YUV,GetTextEx(IDS_MENU_SNATCH_YUV));
			menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,rcShow.left+2,rcShow.bottom,this);
			menu.DestroyMenu();
		}
	}
}

CString CLS_PreviewWindow::MakeFileName(int _iType)
{
	SYSTEMTIME tmNow = {0};
	GetLocalTime(&tmNow);
	CString	strFileName;
	char* pcSuffix = "";

	if (_iType >= 0 && _iType < sizeof(pcRecordSuffix)/sizeof(char*))
	{
		pcSuffix = pcRecordSuffix[_iType];
	}
	
	strFileName.Format(_T("%s\\%04d%02d%02d%02d%02d%02d%04d%s")
		,GetLocalSaveDirectory(),tmNow.wYear,tmNow.wMonth,tmNow.wDay,tmNow.wHour
		,tmNow.wMinute,tmNow.wSecond,tmNow.wMilliseconds,pcSuffix);

	return strFileName;
}

BOOL CLS_PreviewWindow::PreTranslateMessage(MSG* pMsg)
{
	if( pMsg->message == WM_LBUTTONDOWN)
	{
		switch(::GetDlgCtrlID(pMsg->hwnd))
		{
		case IDC_BUTTON_MOVE_UP://向上移动的控制按钮按下
			{
				BOOL bRet = FALSE;
				int iSpeed = m_sldSpeed.GetPos();
				if (1 == m_iWorkMode)
				{
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					bRet = ProtocolControl(PROTOCOL_MOVE_UP,0,iSpeed,bEPTZ);
				}
				else
				{
					bRet = TransparentControl(MOVE_UP,m_iAddress,iSpeed,0);
				}
				if (TRUE == bRet)
				{
					CheckDlgButton(IDC_CHECK_HOR_AUTO,FALSE);
				}
				m_hReverse = pMsg->hwnd;
				SetTimer(TIMER_REVERSE,500,NULL);
			}
			break;
		case IDC_BUTTON_MOVE_DOWN://向下移动的控制按钮按下
			{
				BOOL bRet = FALSE;
				int iSpeed = m_sldSpeed.GetPos();
				if (1 == m_iWorkMode)
				{
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					bRet = ProtocolControl(PROTOCOL_MOVE_DOWN,0,iSpeed,bEPTZ);
				}
				else
				{
					bRet = TransparentControl(MOVE_DOWN,m_iAddress,iSpeed,0);
				}
				if (TRUE == bRet)
				{
					CheckDlgButton(IDC_CHECK_HOR_AUTO,FALSE);
				}
				m_hReverse = pMsg->hwnd;
				SetTimer(TIMER_REVERSE,500,NULL);
			}
			break;
		case IDC_BUTTON_MOVE_LEFT://向左移动的控制按钮按下
			{
				BOOL bRet = FALSE;
				int iSpeed = m_sldSpeed.GetPos();
				if (1 == m_iWorkMode)
				{
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					bRet = ProtocolControl(PROTOCOL_MOVE_LEFT,iSpeed,0,bEPTZ);
				}
				else
				{
					bRet = TransparentControl(MOVE_LEFT,m_iAddress,iSpeed,0);
				}
				if (TRUE == bRet)
				{
					CheckDlgButton(IDC_CHECK_HOR_AUTO,FALSE);
				}
				m_hReverse = pMsg->hwnd;
				SetTimer(TIMER_REVERSE,500,NULL);
			}
			break;
		case IDC_BUTTON_MOVE_RIGHT://向右移动的控制按钮按下
			{
				BOOL bRet = FALSE;
				int iSpeed = m_sldSpeed.GetPos();
				if (1 == m_iWorkMode)
				{
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					bRet = ProtocolControl(PROTOCOL_MOVE_RIGHT,iSpeed,0,bEPTZ);
				}
				else
				{
					bRet = TransparentControl(MOVE_RIGHT,m_iAddress,iSpeed,0);
				}
				if (TRUE == bRet)
				{
					CheckDlgButton(IDC_CHECK_HOR_AUTO,FALSE);
				}
				m_hReverse = pMsg->hwnd;
				SetTimer(TIMER_REVERSE,500,NULL);
			}
			break;
		case IDC_BUTTON_MOVE_UP_LEFT://向左上移动的控制按钮按下
			{
				BOOL bRet = FALSE;
				int iSpeed = m_sldSpeed.GetPos();
				if (1 == m_iWorkMode)
				{
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					bRet = ProtocolControl(PROTOCOL_MOVE_UP_LEFT,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					bRet = TransparentControl(MOVE_UP_LEFT,m_iAddress,iSpeed,0);
				}
				if (TRUE == bRet)
				{
					CheckDlgButton(IDC_CHECK_HOR_AUTO,FALSE);
				}
				m_hReverse = pMsg->hwnd;
				SetTimer(TIMER_REVERSE,500,NULL);
			}
			break;
		case IDC_BUTTON_MOVE_UP_RIGHT://向右上移动的控制按钮按下
			{
				BOOL bRet = FALSE;
				int iSpeed = m_sldSpeed.GetPos();
				if (1 == m_iWorkMode)
				{
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					bRet = ProtocolControl(PROTOCOL_MOVE_UP_RIGHT,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					bRet = TransparentControl(MOVE_UP_RIGHT,m_iAddress,iSpeed,0);
				}
				if (TRUE == bRet)
				{
					CheckDlgButton(IDC_CHECK_HOR_AUTO,FALSE);
				}
				m_hReverse = pMsg->hwnd;
				SetTimer(TIMER_REVERSE,500,NULL);
			}
			break;
		case IDC_BUTTON_MOVE_DOWN_LEFT://向左下移动的控制按钮按下
			{
				BOOL bRet = FALSE;
				int iSpeed = m_sldSpeed.GetPos();
				if (1 == m_iWorkMode)
				{
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					bRet = ProtocolControl(PROTOCOL_MOVE_DOWN_LEFT,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					bRet = TransparentControl(MOVE_DOWN_LEFT,m_iAddress,iSpeed,0);
				}
				if (TRUE == bRet)
				{
					CheckDlgButton(IDC_CHECK_HOR_AUTO,FALSE);
				}
				m_hReverse = pMsg->hwnd;
				SetTimer(TIMER_REVERSE,500,NULL);
			}
			break;
		case IDC_BUTTON_MOVE_DOWN_RIGHT://向右下移动的控制按钮按下
			{
				BOOL bRet = FALSE;
				int iSpeed = m_sldSpeed.GetPos();
				if (1 == m_iWorkMode)
				{
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					bRet = ProtocolControl(PROTOCOL_MOVE_DOWN_RIGHT,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					bRet = TransparentControl(MOVE_DOWN_RIGHT,m_iAddress,iSpeed,0);
				}
				if (TRUE == bRet)
				{
					CheckDlgButton(IDC_CHECK_HOR_AUTO,FALSE);
				}
				m_hReverse = pMsg->hwnd;
				SetTimer(TIMER_REVERSE,500,NULL);
			}
			break;
		case IDC_BUTTON_FOCUS_NEAR://聚焦近的按钮按下
			{
				if (1 == m_iWorkMode)
				{
					int iSpeed = m_sldSpeed.GetPos();
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_FOCUS_ON,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(FOCUS_NEAR,m_iAddress,0,0);
				}
			}
			break;
		case IDC_BUTTON_FOCUS_FAR://聚焦远的按钮按下
			{
				if (1 == m_iWorkMode)
				{
					int iSpeed = m_sldSpeed.GetPos();
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_FOCUS_OFF,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(FOCUS_FAR,m_iAddress,0,0);
				}
			}
			break;
		case IDC_BUTTON_ZOOM_BIG://变倍大的按钮按下
			{
				if (1 == m_iWorkMode)
				{
					int iSpeed = m_sldSpeed.GetPos();
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_ZOOMIN,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(ZOOM_BIG,m_iAddress,0,0);
				}
			}
			break;
		case IDC_BUTTON_ZOOM_SMALL://变倍小的按钮按下
			{
				if (1 == m_iWorkMode)
				{
					int iSpeed = m_sldSpeed.GetPos();
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_ZOOMOUT,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(ZOOM_SMALL,m_iAddress,0,0);
				}
			}
			break;
		case IDC_BUTTON_IRIS_OPEN://打开光圈的按钮按下
			{
				if (1 == m_iWorkMode)
				{
					int iSpeed = m_sldSpeed.GetPos();
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_IRIS_OPEN,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(IRIS_OPEN,m_iAddress,0,0);
				}
			}
			break;
		case IDC_BUTTON_IRIS_CLOSE://关闭光圈的按钮按下
			{
				if (1 == m_iWorkMode)
				{
					int iSpeed = m_sldSpeed.GetPos();
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_IRIS_CLOSE,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(IRIS_CLOSE,m_iAddress,0,0);
				}
			}
			break;
		default :
			break;
		}
	}
	else if( pMsg->message == WM_LBUTTONUP)
	{
		switch(::GetDlgCtrlID(pMsg->hwnd))
		{
		case IDC_BUTTON_MOVE_UP://松开向上移动的控制按钮
			{
				int iSpeed = m_sldSpeed.GetPos();
				if (1 == m_iWorkMode)
				{
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_MOVE_STOP,0,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(MOVE_UP_STOP,m_iAddress,iSpeed,0);
				}
				m_hReverse = NULL;
				KillTimer(TIMER_REVERSE);
			}
			break;
		case IDC_BUTTON_MOVE_DOWN://松开向下移动的控制按钮
			{
				int iSpeed = m_sldSpeed.GetPos();
				if (1 == m_iWorkMode)
				{
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_MOVE_STOP,0,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(MOVE_DOWN_STOP,m_iAddress,iSpeed,0);
				}
				m_hReverse = NULL;
				KillTimer(TIMER_REVERSE);
			}
			break;
		case IDC_BUTTON_MOVE_LEFT://松开向左移动的控制按钮
			{
				int iSpeed = m_sldSpeed.GetPos();
				if (1 == m_iWorkMode)
				{
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_MOVE_STOP,iSpeed,0,bEPTZ);
				}
				else
				{
					TransparentControl(MOVE_LEFT_STOP,m_iAddress,iSpeed,0);
				}
				m_hReverse = NULL;
				KillTimer(TIMER_REVERSE);
			}
			break;
		case IDC_BUTTON_MOVE_RIGHT://松开向右移动的控制按钮
			{
				int iSpeed = m_sldSpeed.GetPos();
				if (1 == m_iWorkMode)
				{
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_MOVE_STOP,iSpeed,0,bEPTZ);
				}
				else
				{
					TransparentControl(MOVE_RIGHT_STOP,m_iAddress,iSpeed,0);
				}
				m_hReverse = NULL;
				KillTimer(TIMER_REVERSE);
			}
			break;
		case IDC_BUTTON_MOVE_UP_LEFT://松开向左上移动的控制按钮
			{
				int iSpeed = m_sldSpeed.GetPos();
				if (1 == m_iWorkMode)
				{
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_MOVE_STOP,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(MOVE_UP_LEFT_STOP,m_iAddress,iSpeed,0);
				}
				m_hReverse = NULL;
				KillTimer(TIMER_REVERSE);
			}
			break;
		case IDC_BUTTON_MOVE_UP_RIGHT://松开向右上移动的控制按钮
			{
				int iSpeed = m_sldSpeed.GetPos();
				if (1 == m_iWorkMode)
				{
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_MOVE_STOP,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(MOVE_UP_RIGHT_STOP,m_iAddress,iSpeed,0);
				}
				m_hReverse = NULL;
				KillTimer(TIMER_REVERSE);
			}
			break;
		case IDC_BUTTON_MOVE_DOWN_LEFT://松开向左下移动的控制按钮
			{
				int iSpeed = m_sldSpeed.GetPos();
				if (1 == m_iWorkMode)
				{
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_MOVE_STOP,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(MOVE_DOWN_LEFT_STOP,m_iAddress,iSpeed,0);
				}
				m_hReverse = NULL;
				KillTimer(TIMER_REVERSE);
			}
			break;
		case IDC_BUTTON_MOVE_DOWN_RIGHT://松开右下移动的控制按钮
			{
				int iSpeed = m_sldSpeed.GetPos();
				if (1 == m_iWorkMode)
				{
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_MOVE_STOP,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(MOVE_DOWN_RIGHT_STOP,m_iAddress,iSpeed,0);
				}
				m_hReverse = NULL;
				KillTimer(TIMER_REVERSE);
			}
			break;
		case IDC_BUTTON_FOCUS_NEAR://松开聚焦近的按钮
			{
				if (1 == m_iWorkMode)
				{
					int iSpeed = m_sldSpeed.GetPos();
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_MOVE_STOP,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(FOCUS_NEAR_STOP,m_iAddress,0,0);
				}
			}
			break;
		case IDC_BUTTON_FOCUS_FAR://松开聚焦远的按钮
			{
				if (1 == m_iWorkMode)
				{
					int iSpeed = m_sldSpeed.GetPos();
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_MOVE_STOP,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(FOCUS_FAR_STOP,m_iAddress,0,0);
				}
			}
			break;
		case IDC_BUTTON_ZOOM_BIG://松开变倍大的按钮
			{
				if (1 == m_iWorkMode)
				{
					int iSpeed = m_sldSpeed.GetPos();
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_MOVE_STOP,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(ZOOM_BIG_STOP,m_iAddress,0,0);
				}
			}
			break;
		case IDC_BUTTON_ZOOM_SMALL://松开变倍小的按钮
			{
				if (1 == m_iWorkMode)
				{
					int iSpeed = m_sldSpeed.GetPos();
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_MOVE_STOP,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(ZOOM_SMALL_STOP,m_iAddress,0,0);
				}
			}
			break;
		case IDC_BUTTON_IRIS_OPEN://松开光圈开的按钮
			{
				if (1 == m_iWorkMode)
				{
					int iSpeed = m_sldSpeed.GetPos();
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_MOVE_STOP,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(IRIS_OPEN_STOP,m_iAddress,0,0);
				}
			}
			break;
		case IDC_BUTTON_IRIS_CLOSE://松开光圈关的按钮
			{
				if (1 == m_iWorkMode)
				{
					int iSpeed = m_sldSpeed.GetPos();
					BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
					ProtocolControl(PROTOCOL_MOVE_STOP,iSpeed,iSpeed,bEPTZ);
				}
				else
				{
					TransparentControl(IRIS_CLOSE_STOP,m_iAddress,0,0);
				}
			}
			break;
		default :
			break;
		}
	}
	else if(WM_MOUSEMOVE == pMsg->message)
	{
		m_tipCtrl.RelayEvent(pMsg);
	}

	return CLS_BaseWindow::PreTranslateMessage(pMsg);
}

BOOL CLS_PreviewWindow::UI_UpdatePTZ()
{
	GetDlgItem(IDC_CHECK_EPTZ)->ShowWindow(SW_HIDE);
	if (m_iLogonID < 0)
	{
		return FALSE;
	}
	
	int iProductType = 0;
	int iRet = NetClient_GetProductType(m_iLogonID,&iProductType);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetProductType(%d,%d)"
			,m_iLogonID, iProductType);

		iProductType &= 0xFFFF;
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetProductType(%d,%d)"
			,m_iLogonID, iProductType);
	}

	int iChannelNo = 0;
	if (IsDVR(iProductType)||iProductType==0x64)
	{
		iChannelNo = m_iChannelNo;
	}

	m_iComNo = 1;
	m_iAddress = 0;
	iRet = NetClient_GetDeviceType(m_iLogonID,iChannelNo,&m_iComNo,&m_iAddress,m_cDeviceType);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDeviceType(%d,%d,%d,%d,%s)"
			,m_iLogonID,iChannelNo,m_iComNo,m_iAddress,m_cDeviceType);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDeviceType(%d,%d,%d,%d,%s)"
			,m_iLogonID,iChannelNo,m_iComNo,m_iAddress,m_cDeviceType);
	}
	m_iAddress -= 1;


	char cComFormat[32] = {0};
	m_iWorkMode = 1;
	if(m_iComNo <= 0)
	{
		m_iComNo = 1;
	}
	iRet = NetClient_GetComFormat(m_iLogonID,m_iComNo,cComFormat,&m_iWorkMode);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetComFormat(%d,%d,%s,%d)"
			,m_iLogonID,m_iComNo,cComFormat,m_iWorkMode);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetComFormat(%d,%d,%s,%d)"
			,m_iLogonID,m_iComNo,cComFormat,m_iWorkMode);
	}
	if (1 == m_iWorkMode)
	{
		GetDlgItem(IDC_CHECK_EPTZ)->ShowWindow(SW_SHOW);
	}
	
	return TRUE;
}

BOOL CLS_PreviewWindow::TransparentControl(int _iAction,int _iAddress, int _iSpeed, int _iPreset)
{
	if (m_iLogonID < 0)
	{
		return FALSE;
	}

	CONTROL_PARAM ctrlParam = {0};
    ctrlParam.m_iAddress = _iAddress;
    if(0 == memcmp(m_cDeviceType,"DOME",4))
    {
        if(_iAction>0 && _iAction <= 16)
        {
            switch(_iAction)
            {
               case MOVE_UP:
                   ctrlParam.m_ptMove.x = 0;
                   ctrlParam.m_ptMove.y = _iSpeed;
                   _iAction = MOVE;
                   break;
               case MOVE_DOWN:
                   ctrlParam.m_ptMove.x = 0;
                   ctrlParam.m_ptMove.y = -_iSpeed;
                   _iAction = MOVE;
                   break;
               case MOVE_LEFT:
                   ctrlParam.m_ptMove.x = -_iSpeed;
                   ctrlParam.m_ptMove.y = 0;
                   _iAction = MOVE;
                   break;
               case MOVE_RIGHT:
                   ctrlParam.m_ptMove.x = _iSpeed;
                   ctrlParam.m_ptMove.y = 0;
                   _iAction = MOVE;
                   break;
               case MOVE_UP_LEFT:
                   ctrlParam.m_ptMove.x = -_iSpeed;
                   ctrlParam.m_ptMove.y = _iSpeed;
                   _iAction = MOVE;
                   break;
               case MOVE_UP_RIGHT:
                   ctrlParam.m_ptMove.x = _iSpeed;
                   ctrlParam.m_ptMove.y = _iSpeed;
                   _iAction = MOVE;
                   break;
               case MOVE_DOWN_LEFT:
                   ctrlParam.m_ptMove.x = -_iSpeed;
                   ctrlParam.m_ptMove.y = -_iSpeed;
                   _iAction = MOVE;
                   break;
               case MOVE_DOWN_RIGHT:
                   ctrlParam.m_ptMove.x = _iSpeed;
                   ctrlParam.m_ptMove.y = -_iSpeed;
                   _iAction = MOVE;
                   break;
               default:
                   _iAction = MOVE_STOP;
                   break;
            }
        }
    }
    else
    {
		AddLog(LOG_TYPE_MSG,"","[DeviceControl] device type(%s) is not DOME",m_cDeviceType);
    }
    //preset:
    if((_iAction == CALL_VIEW)||(_iAction == SET_VIEW))
    {
        ctrlParam.m_iPreset = _iPreset;
    }

    //Get the real action code
    int iRet = m_tDevCtrl.GetCtrlCode(m_cDeviceType,_iAction,&ctrlParam);
    if(0 == iRet)
    {
		CString strOut = Bytes2HexString(ctrlParam.m_btBuf,ctrlParam.m_iCount);
		int iChannelProperty = -1;
		int iRet = NetClient_GetChannelProperty(m_iLogonID, m_iChannelNo
			, GENERAL_CMD_GET_CHANNEL_TYPE, &iChannelProperty, sizeof(iChannelProperty));
		if (0 == iRet)
		{
			if(iChannelProperty == 2)
			{
				int iRet = NetClient_DigitalChannelSend(m_iLogonID, m_iChannelNo
					,ctrlParam.m_btBuf, ctrlParam.m_iCount);
				if (0 == iRet)
				{
					AddLog(LOG_TYPE_SUCC,"","NetClient_DigitalChannelSend(%d,%d,%s,%d)",m_iLogonID
						, m_iChannelNo,(LPSTR)(LPCTSTR)strOut, ctrlParam.m_iCount);
				}
				else
				{
					AddLog(LOG_TYPE_FAIL,"","NetClient_DigitalChannelSend(%d,%d,%s,%d)",m_iLogonID
						, m_iChannelNo,(LPSTR)(LPCTSTR)strOut, ctrlParam.m_iCount);
				}
				return TRUE;
			}
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetChannelProperty(%d,%d,CHANNEL_TYPE,,)",m_iLogonID
				,m_iChannelNo);
		}
		
		iRet = NetClient_ComSend(m_iLogonID,ctrlParam.m_btBuf, ctrlParam.m_iCount,m_iComNo);
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_ComSend(%d,%s,%d,%d)",m_iLogonID
				,(LPSTR)(LPCTSTR)strOut, ctrlParam.m_iCount,m_iComNo);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_ComSend(%d,%s,%d,%d)",m_iLogonID
				,(LPSTR)(LPCTSTR)strOut, ctrlParam.m_iCount,m_iComNo);
		}
		return TRUE;
    }
    else
    {
        AddLog(LOG_TYPE_FAIL,"","GetCtrlCode(%s,%d)",m_cDeviceType,_iAction);
		return FALSE;
    }
}

BOOL CLS_PreviewWindow::ProtocolControl( int _iAction,int _iParam1,int _iParam2,int _iEPTZ )
{
	if (m_iLogonID < 0)
	{
		return FALSE;
	}

	int iRet = NetClient_DeviceCtrlEx(m_iLogonID,m_iChannelNo
		,_iAction,_iParam1,_iParam2,_iEPTZ);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_DeviceCtrlEx(%d,%d,%d,%d,%d,%d)"
			,m_iLogonID,m_iChannelNo,_iAction,_iParam1,_iParam2,_iEPTZ);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_DeviceCtrlEx(%d,%d,%d,%d,%d,%d)"
			,m_iLogonID,m_iChannelNo,_iAction,_iParam1,_iParam2,_iEPTZ);
	}
	return TRUE;
}

void CLS_PreviewWindow::OnBnClickedCheckHorAuto()
{
	if (m_iLogonID < 0)
	{
		CheckDlgButton(IDC_CHECK_HOR_AUTO,FALSE);
		return;
	}

	BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
	if(IsDlgButtonChecked(IDC_CHECK_HOR_AUTO))
	{
		if (1 == m_iWorkMode)
		{
			ProtocolControl(PTZ_START_ROUTINE,0,0,bEPTZ);
		}
		else
		{
			TransparentControl(HOR_AUTO,m_iAddress,0,0);
		}
	}
	else
	{
		if (1 == m_iWorkMode)
		{
			ProtocolControl(PTZ_STOP_ROUTINE,0,0,bEPTZ);
		}
		else
		{
			TransparentControl(HOR_AUTO_STOP,m_iAddress,0,0);
		}
	}
}

void CLS_PreviewWindow::OnBnClickedChkLight()
{
	if (m_iLogonID < 0)
	{
		return;
	}

	int iSpeed = m_sldSpeed.GetPos();
	BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
	if(IsDlgButtonChecked(IDC_CHK_LIGHT))
	{
		BOOL bRet = FALSE;
		if (1 == m_iWorkMode)
		{
			bRet = ProtocolControl(PROTOCOL_LIGHT_ON,iSpeed,iSpeed,bEPTZ);
		}
		else
		{
			bRet = TransparentControl(LIGHT_ON,m_iAddress,0,0);
		}
		if (FALSE == bRet)
		{
			CheckDlgButton(IDC_CHK_LIGHT,FALSE);
		}
	}
	else
	{
		if (1 == m_iWorkMode)
		{
			ProtocolControl(PROTOCOL_LIGHT_OFF,iSpeed,iSpeed,bEPTZ);
		}
		else
		{
			TransparentControl(LIGHT_OFF,m_iAddress,0,0);
		}
	}
}

void CLS_PreviewWindow::OnBnClickedChkPower()
{
	if (m_iLogonID < 0)
	{
		return;
	}

	int iSpeed = m_sldSpeed.GetPos();
	BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
	if(IsDlgButtonChecked(IDC_CHK_POWER))
	{
		BOOL bRet = FALSE;
		if (1 == m_iWorkMode)
		{
			bRet = ProtocolControl(PROTOCOL_POWER_ON,iSpeed,iSpeed,bEPTZ);
		}
		else
		{
			bRet = TransparentControl(POWER_ON,m_iAddress,0,0);
		}
		if (FALSE == bRet)
		{
			CheckDlgButton(IDC_CHK_POWER,FALSE);
		}
	}
	else
	{
		if (1 == m_iWorkMode)
		{
			ProtocolControl(PROTOCOL_POWER_OFF,iSpeed,iSpeed,bEPTZ);
		}
		else
		{
			TransparentControl(POWER_OFF,m_iAddress,0,0);
		}
	}
}

void CLS_PreviewWindow::OnBnClickedChkRain()
{
	if (m_iLogonID < 0)
	{
		return;
	}

	int iSpeed = m_sldSpeed.GetPos();
	BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
	if(IsDlgButtonChecked(IDC_CHK_RAIN))
	{
		BOOL bRet = FALSE;
		if (1 == m_iWorkMode)
		{
			bRet = ProtocolControl(PROTOCOL_RAIN_ON,iSpeed,iSpeed,bEPTZ);
		}
		else
		{
			bRet = TransparentControl(RAIN_ON,m_iAddress,0,0);
		}
		if (FALSE == bRet)
		{
			CheckDlgButton(IDC_CHK_RAIN,FALSE);
		}
	}
	else
	{
		if (1 == m_iWorkMode)
		{
			ProtocolControl(PROTOCOL_RAIN_OFF,iSpeed,iSpeed,bEPTZ);
		}
		else
		{
			TransparentControl(RAIN_OFF,m_iAddress,0,0);
		}
	}
}

void CLS_PreviewWindow::OnBnClickedButtonAssistantOn()
{
	if (m_iLogonID < 0)
	{
		return;
	}

	int iSpeed = m_sldSpeed.GetPos();
	int iAssistantNo = m_cboAssistant.GetCurSel();
	BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
	if (1 == m_iWorkMode)
	{
		ProtocolControl(PROTOCOL_ASSISTANT_ON,iAssistantNo,iSpeed,bEPTZ);
	}
}

void CLS_PreviewWindow::OnBnClickedButtonAssistantOff()
{
	if (m_iLogonID < 0)
	{
		return;
	}

	int iSpeed = m_sldSpeed.GetPos();
	int iAssistantNo = m_cboAssistant.GetCurSel();
	BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
	if (1 == m_iWorkMode)
	{
		ProtocolControl(PROTOCOL_ASSISTANT_OFF,iAssistantNo,iSpeed,bEPTZ);
	}
}

void CLS_PreviewWindow::OnBnClickedButtonSetPreset()
{
	if (m_iLogonID < 0)
	{
		return;
	}

	int iSpeed = m_sldSpeed.GetPos();
	int iPreset = GetDlgItemInt(IDC_EDIT_PRESET);
	if (iPreset < 1 || iPreset > 255)
	{
		AddLog(LOG_TYPE_MSG,"","please select a correct preset(%d)",iPreset);
		return;
	}

	BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
	if (1 == m_iWorkMode)
	{
		ProtocolControl(PROTOCOL_SET_PRESET,iPreset,iSpeed,bEPTZ);
	}
	else
	{
		TransparentControl(SET_VIEW,m_iAddress,0,iPreset);
	}
}

void CLS_PreviewWindow::OnBnClickedButtonCallPreset()
{
	if (m_iLogonID < 0)
	{
		return;
	}

	int iSpeed = m_sldSpeed.GetPos();
	int iPreset = GetDlgItemInt(IDC_EDIT_PRESET);
	if (iPreset < 1 || iPreset > 255)
	{
		AddLog(LOG_TYPE_MSG,"","please select a correct preset(%d)",iPreset);
		return;
	}

	BOOL bEPTZ = IsDlgButtonChecked(IDC_CHECK_EPTZ);
	if (1 == m_iWorkMode)
	{
		ProtocolControl(PROTOCOL_PRESET,iPreset,iSpeed,bEPTZ);
	}
	else
	{
		TransparentControl(CALL_VIEW,m_iAddress,0,iPreset);
	}
}

void CLS_PreviewWindow::OnBnClickedBtnForceIframe()
{
	if(m_pVideo[m_iCurrentVideo])
	{
		unsigned int uConnID = m_pVideo[m_iCurrentVideo]->GetConnID();
		PCHANNEL_INFO pChannel = FindChannel(uConnID);
		if (pChannel)
		{
			int iRet = NetClient_ForceIFrame(pChannel->iLogonID, pChannel->iChannelNo,pChannel->iStreamNo);
			if (0 == iRet)
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_ForceIFrame(%d,%d,%d)"
					,pChannel->iLogonID, pChannel->iChannelNo,pChannel->iStreamNo);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_ForceIFrame(%d,%d,%d)"
					,pChannel->iLogonID, pChannel->iChannelNo,pChannel->iStreamNo);
			}
		}
	}
}


DWORD WINAPI CLS_PreviewWindow::ThreadInputTalking( LPVOID pParam )
{
	int iLogonID = *(int*)pParam;

	PDEVICE_INFO pDevice = FindDevice(iLogonID);
	int iSleepTime = 40;
	int iDataLen = 16*iSleepTime;

	int srcFileSize = 0;
	int iReadNum = 0, iRet = 0;

	unsigned char* ucBuf = NULL;
	FILE* fpSrc = _fsopen(pDevice->cTalkInputFile, "rb",_SH_DENYNO);
	if(fpSrc==NULL)
	{
		TRACE("[ThreadInputTalking] open file failed, then return ....\n");
		goto END_POINT;
	}

	ucBuf = (unsigned char*)malloc(iDataLen);

	fseek(fpSrc,0,SEEK_END);  //定位到文件尾部
	srcFileSize = ftell(fpSrc);                     //  获取文件大小
	fseek(fpSrc,0,SEEK_SET); //定位到文件的开头
	if (srcFileSize % iDataLen != 0)                //  不是整数倍，读取次数要+1
	{
		iReadNum =  srcFileSize/iDataLen + 1;
	}
	else
	{
		iReadNum =  srcFileSize/iDataLen + 0;
	}

	TRACE("ReadNum:    %d\n", iReadNum);

	for(int i=0;i<iReadNum-1;i++)
	{
		if (::WaitForSingleObject(pDevice->hEventQuitTalking, iSleepTime) == WAIT_OBJECT_0)
			goto END_POINT;

		fread(ucBuf,1,iDataLen,fpSrc);
		iRet = NetClient_InputTalkingdata(ucBuf, iDataLen);
		//        ::Sleep(iSleepTime-10);
		if(iRet < 0)
		{
			::OutputDebugString("[ThreadInputTalking]  -- (NetClient_InputTalkingdata) Failed, ");
		}
	}

	::Sleep(iSleepTime);
	iDataLen = srcFileSize - iDataLen*(iReadNum-1);
	fread(ucBuf,1,iDataLen,fpSrc);
	iRet = NetClient_InputTalkingdata(ucBuf, iDataLen);

END_POINT:
	TRACE("[ThreadInputTalking] -- End_Point, will return -----------------------\n");
	if (ucBuf)
	{
		free(ucBuf);
		ucBuf = NULL;
	}

	Inner_SafeCloseFile(&fpSrc);

	//  通知上层应用程序，inputTalking完成。
	LRESULT iRet1 = ::SendMessageTimeout(s_hWnd, WM_INPUTTALKING_END, 0, iLogonID, SMTO_NORMAL,3000,NULL);

	return 0;
}

LRESULT CLS_PreviewWindow::OnTalkEnd( WPARAM wParam, LPARAM lParam )
{
	int iLogonID = (int)lParam;
	PDEVICE_INFO pDevice = FindDevice(iLogonID);
	if (0 == NetClient_TalkEnd(iLogonID))
	{
		AddLog(LOG_TYPE_SUCC,"","Input success end!!");
		pDevice->bIsTalking = FALSE;
	}
	return 0; 
}

void CLS_PreviewWindow::OnSnatch( UINT nID )
{
	unsigned int uConnID = m_pVideo[m_iCurrentVideo]->GetConnID();
	if (-1 == uConnID)
	{
		return;
	}

	CString strFileName = MakeFileName();
	switch(nID)
	{
	case ID_SNATCH_BMP:
		{
			strFileName.AppendFormat(_T(".bmp"));
			int iSize = NetClient_CaptureBmpPic(uConnID,(LPSTR)(LPCTSTR)strFileName);
			if (iSize >= 0)
			{
				AddLog(LOG_TYPE_SUCC,"","(%d)NetClient_CaptureBmpPic(%u,%s)",iSize,uConnID,(LPSTR)(LPCTSTR)strFileName);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","(%d)NetClient_CaptureBmpPic(%u,%s)",iSize,uConnID,(LPSTR)(LPCTSTR)strFileName);
			}
		}
		break;
	case ID_SNATCH_YUV:
		{
			unsigned char *dataP = NULL;
			int iSize = NetClient_CapturePic(uConnID,&dataP);
			if(iSize <= 0)
			{
				AddLog(LOG_TYPE_FAIL,"","(%d)NetClient_CapturePic(%u,%#x)",iSize,uConnID,dataP);
				return;
			}
			strFileName.AppendFormat(_T(".yuy2"));
			FILE *fp = _fsopen((LPSTR)(LPCTSTR)strFileName,"wb+",_SH_DENYNO);
			if (fp == NULL)
			{
				AddLog(LOG_TYPE_FAIL,"","fopen(%s)",strFileName);
				return;
			}
			fwrite(dataP,sizeof(char),iSize,fp);
			fflush(fp);
			fclose(fp);
			AddLog(LOG_TYPE_SUCC,"","(%d)NetClient_CapturePic(%u,%s)",iSize,uConnID,strFileName);
		}
		break;
	default:break;
	}
}

void CLS_PreviewWindow::DecodeYuvNotify( unsigned int _ulID,unsigned char *_cData, int _iLen, const FRAME_INFO *_pFrameInfo, void* _iUser )
{
	CLS_PreviewWindow* pThis = (CLS_PreviewWindow*)_iUser;
	if (pThis)
	{
		pThis->DecodeYuvNotify(_ulID,_cData,_iLen,_pFrameInfo);
	}
}

void __stdcall CLS_PreviewWindow::RawVideoAndAudioNotify(unsigned long _ulID, unsigned char* _ucData, int _iSize, RAWFRAME_INFO* _pRawFrameInfo, void* _pContext)
{
	CLS_PreviewWindow* pThis = (CLS_PreviewWindow*)_pContext;
	if (pThis)
	{
		pThis->RawVideoAndAudio(_ulID,_ucData,_iSize,_pRawFrameInfo);
	}
}

void CLS_PreviewWindow::RawVideoAndAudio(unsigned long _ulID, unsigned char* _ucData, int _iSize, RAWFRAME_INFO* _pRawFrameInfo)
{
	PCHANNEL_INFO pChannel = FindChannel(_ulID);
	if(NULL == pChannel || NULL == _ucData || NULL == _pRawFrameInfo)
	{
		return;
	}

	static int g_iTime = 0;
	RAWFRAME_INFO tRawFrameInfo = {0};
	memcpy(&tRawFrameInfo, _pRawFrameInfo, sizeof(tRawFrameInfo));
	CString cstrLog;
	int iTime = timeGetTime();
	cstrLog.Format("[RecvRawFramNotify PlayerId(%d) FrameType(%d) DataLen(%d) Time(%d) \
				   ,nWidth(%d), nHeight(%d),nStamp(%d) nEnCoder(%d)\
				   nFrameRate(%d) nAbsStamp(%d) ucBitsPerSample(%d)\
				   uiSamplesPerSec(%d)\n]", _ulID, tRawFrameInfo.nType, _iSize, iTime - g_iTime, \
				   tRawFrameInfo.nWidth, tRawFrameInfo.nHeight, tRawFrameInfo.nStamp, tRawFrameInfo.nEnCoder,\
				   tRawFrameInfo.nFrameRate, tRawFrameInfo.nAbsStamp, tRawFrameInfo.ucBitsPerSample, tRawFrameInfo.uiSamplesPerSec);
#ifdef _DEBUG_LOG_
	OutputDebugString(cstrLog);
#endif
	g_iTime = iTime;

	if(AUDIO_FRAME == _pRawFrameInfo->nType)//原始音频
	{
		if(NULL == pChannel->pfRaw &&  pChannel->bIsRecording)
		{
			CString strFileName = MakeFileName();
			strFileName.AppendFormat(_T(".raw")); 
			pChannel->pfRaw = _fsopen((LPSTR)(LPCTSTR)strFileName,"wb+",_SH_DENYNO);
			if(NULL == pChannel->pfRaw)
			{
				AddLog(LOG_TYPE_FAIL,"","_fsopen(%s)",strFileName);
				return;
			}
			pChannel->bIsRecording = TRUE;
			CheckDlgButton(IDC_CHK_RECORD, TRUE);	
		}

		EnterCriticalSection(&m_csCriticalSession);
		if(NULL == pChannel->pfRaw)
		{
			LeaveCriticalSection(&m_csCriticalSession);
			return;
		}
		
		size_t iRetLength = fwrite(_ucData, sizeof(unsigned char), _iSize, pChannel->pfRaw);
		if(iRetLength != _iSize)
		{
			AddLog(LOG_TYPE_FAIL,"","fwrite iRetLength:%d",iRetLength);
		}
		LeaveCriticalSection(&m_csCriticalSession);
		
	}
	else//原始视频
	{
		if(NULL == pChannel->pfRaw &&  pChannel->bIsRecording)//多加一个条件，防止回调上来的消息慢，再次打开文件无法停止录像
		{
			CString strFileName = MakeFileName();
			strFileName.AppendFormat(_T(".raw")); 
			pChannel->pfRaw = _fsopen((LPSTR)(LPCTSTR)strFileName,"wb+",_SH_DENYNO);
			if(NULL == pChannel->pfRaw)
			{
				AddLog(LOG_TYPE_FAIL,"","_fsopen(%s)",strFileName);
				return;
			}
			pChannel->bIsRecording = TRUE;
			CheckDlgButton(IDC_CHK_RECORD, TRUE);
		}
		EnterCriticalSection(&m_csCriticalSession);
		if(NULL == pChannel->pfRaw)
		{
			LeaveCriticalSection(&m_csCriticalSession);
			return;
		}

		size_t iRetLength = fwrite(_ucData, sizeof(unsigned char), _iSize, pChannel->pfRaw);
		if(iRetLength != _iSize)
		{
			AddLog(LOG_TYPE_FAIL,"","fwrite iRetLength:%d",iRetLength);
		}
		LeaveCriticalSection(&m_csCriticalSession);
	}
}

void CLS_PreviewWindow::DecodeYuvNotify( unsigned int _ulID,unsigned char *_cData, int _iLen, const FRAME_INFO *_pFrameInfo )
{
	PCHANNEL_INFO pChannel = FindChannel(_ulID);
	if (NULL == pChannel || NULL == _cData || NULL == _pFrameInfo)
	{
		return;
	}

	TStreamData StreamData = {0};
	StreamData.iSize = sizeof(TStreamData);
	int iRet = NetClient_GetUserDataInfo(_ulID,  GET_USERDATA_INFO_USER_DEFINE, &StreamData, sizeof(StreamData));
	char cData[65] = {0};
	if (StreamData.iStreamLen < sizeof(cData) && StreamData.iStreamLen >0)
	{
		memcpy(cData, StreamData.cStreamData, StreamData.iStreamLen);
		OutputDebugString(cData);
		OutputDebugString("\n");
		OutputDebugString("--------------------------------------------------------\n");
	}

	switch(_pFrameInfo->nType)
	{
	case T_YUV420:
		{
			if (NULL == pChannel->pfYuv)
			{
				CString strFileName = MakeFileName();
				strFileName.AppendFormat(_T(".yuv420"));
				pChannel->pfYuv = _fsopen((LPSTR)(LPCTSTR)strFileName,"wb+",_SH_DENYNO);
				if (NULL == pChannel->pfYuv)
				{
					AddLog(LOG_TYPE_FAIL,"","_fsopen(%s)",strFileName);
					return;
				}
				AddLog(LOG_TYPE_SUCC,"","(%#x)_fsopen(%s)",pChannel->pfYuv,strFileName);
				pChannel->bIsRecording = TRUE;
				CheckDlgButton(IDC_CHK_RECORD,TRUE);
			}

			fwrite(_cData,sizeof(unsigned char),_iLen,pChannel->pfYuv);
		}
		break;
	case T_AUDIO8:
		{
			if (NULL == pChannel->pfPcm)
			{
				CString strFileName = MakeFileName();
				strFileName.AppendFormat(_T(".pcm"));
				pChannel->pfPcm = _fsopen((LPSTR)(LPCTSTR)strFileName,"wb+",_SH_DENYNO);
				if (NULL == pChannel->pfPcm)
				{
					AddLog(LOG_TYPE_FAIL,"","_fsopen(%s)",strFileName);
					return;
				}
				AddLog(LOG_TYPE_SUCC,"","(%#x)_fsopen(%s)",pChannel->pfPcm,strFileName);
				pChannel->bIsRecording = TRUE;
				CheckDlgButton(IDC_CHK_RECORD,TRUE);
			}

			fwrite(_cData,sizeof(unsigned char),_iLen,pChannel->pfPcm);
		}
		break;
	default:
		break;
	}
}

int CLS_PreviewWindow::ShowMultiplyWindow()
{
	int iNum = m_cboWindowNum.GetCurSel()+1;
	ShowVideoWindow(m_cboWindowNum.GetCurSel()+1);
	for (int i = 0; i < iNum; ++i)
	{
		for (int j = 0; j < iNum; ++j)
		{
			m_pVideo[i*iNum+j]->Invalidate();
		}
	}
	return 0;
}

int CLS_PreviewWindow::ShowSingleWindow()
{
	RECT rcVideo = {0};
	GetDlgItem(IDC_STATIC_CENTER_BG)->GetWindowRect(&rcVideo);
	ScreenToClient(&rcVideo);
	int iRows = m_cboWindowNum.GetCurSel()+1;

	m_pVideo[m_iCurrentVideo]->DrawRect(GetSysColor(COLOR_BTNFACE));
	for (int i = 0; i < iRows; ++i)
	{
		for (int j = 0; j < iRows; ++j)
		{
			if ((i*iRows+j) == m_iCurrentVideo)
			{
				continue;
			}
			m_pVideo[i*iRows+j]->ShowWindow(SW_HIDE);
		}
	}
	m_pVideo[m_iCurrentVideo]->MoveWindow(&rcVideo);
 	m_pVideo[m_iCurrentVideo]->ShowWindow(SW_SHOW);
 	m_pVideo[m_iCurrentVideo]->RedrawWindow();
	m_pVideo[m_iCurrentVideo]->DrawRect(RGB(255,0,0));

	return 0;
}

int CLS_PreviewWindow::ShowFullWindow()
{
	if (NULL == m_pVideo[MAX_VIDEO_NUM])
	{
		ShowMultiplyWindow();
		return -1;
	}

	unsigned int uiConnID = m_pVideo[m_iCurrentVideo]->GetConnID();
	HWND hWnd = m_pVideo[MAX_VIDEO_NUM]->GetSafeHwnd();
	m_pVideo[MAX_VIDEO_NUM]->ShowWindow(SW_SHOW);
	m_pVideo[MAX_VIDEO_NUM]->RedrawWindow();
	m_pVideo[MAX_VIDEO_NUM]->SetConnID(uiConnID);
	int iRet = NetClient_ResetPlayerWnd(uiConnID,hWnd);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_ResetPlayerWnd(%u,0x%08x)",uiConnID,hWnd);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_ResetPlayerWnd(%u,0x%08x)",uiConnID,hWnd);
	}

	return 0;
}

void CLS_PreviewWindow::ResumeRecord(unsigned int _uiConnID)
{
	PCHANNEL_INFO pChannel = FindChannel(_uiConnID);
	if (NULL == pChannel || FALSE == pChannel->bIsRecording)
	{
		return;
	}

	if (ID_RECORD_RAW-ID_RECORD_SDV == pChannel->iRecordType)
	{
		if (pChannel->pfYuv)
		{
			fclose(pChannel->pfYuv);
			AddLog(LOG_TYPE_SUCC,"","fclose(%#x)",pChannel->pfYuv);
			pChannel->pfYuv = NULL;
		}
		if (pChannel->pfPcm)
		{
			fclose(pChannel->pfPcm);
			AddLog(LOG_TYPE_SUCC,"","fclose(%#x)",pChannel->pfPcm);
			pChannel->pfPcm = NULL;
		}
		if (pChannel->pfRaw)
		{
			fclose(pChannel->pfRaw);
			AddLog(LOG_TYPE_SUCC,"","fclose(%#x)",pChannel->pfRaw);
			pChannel->pfRaw = NULL;
		}
		if(ID_RECORD_YUV == pChannel->iRecordType)
		{
			int iRet = NetClient_SetDecCallBack_V4(_uiConnID,(DECYUV_NOTIFY_V4)&CLS_PreviewWindow::DecodeYuvNotify,(int)this);
			if (RET_SUCCESS == iRet)
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_SetDecCallBackEx(%u,,)",_uiConnID);
			}
			else
			{
				pChannel->bIsRecording = FALSE;
				AddLog(LOG_TYPE_FAIL,"","NetClient_SetDecCallBackEx(%u,,)",_uiConnID);
			}
		}
		if(ID_RECORD_RAW == pChannel->iRecordType)
		{
			int iRet = NetClient_SetRawFrameCallBack(_uiConnID, (RAWFRAME_NOTIFY)&CLS_PreviewWindow::RawVideoAndAudioNotify, this);
			if (RET_SUCCESS == iRet)
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_SetRawFrameCallBack(%u,,)",_uiConnID);
			}
			else
			{
				pChannel->bIsRecording = FALSE;
				AddLog(LOG_TYPE_FAIL,"","NetClient_SetRawFrameCallBack(%u,,)",_uiConnID);
			}
		}
	}
	else
	{
		CString strFileName = MakeFileName(pChannel->iRecordType);
		int iRet = NetClient_StartCaptureFile(_uiConnID,(LPSTR)(LPCTSTR)strFileName,pChannel->iRecordType);
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_StartCaptureFile(%u,%s,%d)",_uiConnID,(LPSTR)(LPCTSTR)strFileName,pChannel->iRecordType);
		}
		else
		{
			pChannel->bIsRecording = FALSE;
			AddLog(LOG_TYPE_FAIL,"","NetClient_StartCaptureFile(%u,%s,%d)",_uiConnID,(LPSTR)(LPCTSTR)strFileName,pChannel->iRecordType);
		}
	}
}

CTreeCtrl* CLS_PreviewWindow::GetDeviceTreeCtrl()
{
	CNetClientDemoDlg* pParent = (CNetClientDemoDlg*)GetParent();
	if (pParent)
	{
		return pParent->GetDeviceTreeCtrl();
	}
	return NULL;
}

void CLS_PreviewWindow::OnTimer(UINT_PTR nIDEvent)
{
	if (TIMER_REVERSE == nIDEvent)
	{
		MSG msg = {0};
		msg.message = WM_LBUTTONDOWN;
		msg.hwnd = m_hReverse;
		PreTranslateMessage(&msg);
	}

	CLS_BaseWindow::OnTimer(nIDEvent);
}
