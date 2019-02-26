// DNVRVideoCombinePage.cpp : implementation file
//

#include "stdafx.h"
#include "DNVRVideoCombinePage.h"


// CLS_DNVRVideoCombinePage dialog

IMPLEMENT_DYNAMIC(CLS_DNVRVideoCombinePage, CDialog)

CLS_DNVRVideoCombinePage::CLS_DNVRVideoCombinePage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DNVRVideoCombinePage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
}

CLS_DNVRVideoCombinePage::~CLS_DNVRVideoCombinePage()
{
}

void CLS_DNVRVideoCombinePage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CHANNELENABLE, m_btnChannelEnable);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE1, m_chkChannelEnable[0]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE2, m_chkChannelEnable[1]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE3, m_chkChannelEnable[2]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE4, m_chkChannelEnable[3]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE5, m_chkChannelEnable[4]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE6, m_chkChannelEnable[5]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE7, m_chkChannelEnable[6]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE8, m_chkChannelEnable[7]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE9, m_chkChannelEnable[8]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE10, m_chkChannelEnable[9]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE11, m_chkChannelEnable[10]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE12, m_chkChannelEnable[11]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE13, m_chkChannelEnable[12]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE14, m_chkChannelEnable[13]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE15, m_chkChannelEnable[14]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE16, m_chkChannelEnable[15]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE17, m_chkChannelEnable[16]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE18, m_chkChannelEnable[17]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE19, m_chkChannelEnable[18]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE20, m_chkChannelEnable[19]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE21, m_chkChannelEnable[20]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE22, m_chkChannelEnable[21]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE23, m_chkChannelEnable[22]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE24, m_chkChannelEnable[23]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE25, m_chkChannelEnable[24]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE26, m_chkChannelEnable[25]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE27, m_chkChannelEnable[26]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE28, m_chkChannelEnable[27]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE29, m_chkChannelEnable[28]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE30, m_chkChannelEnable[29]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE31, m_chkChannelEnable[30]);
	DDX_Control(pDX, IDC_CHECK_CHANNELENABLE32, m_chkChannelEnable[31]);
	DDX_Control(pDX, IDC_EDIT_PICTURENUM, m_edtPictureNum);
	DDX_Control(pDX, IDC_EDIT_COMBINERECT, m_edtCombineRect);
	DDX_Control(pDX, IDC_EDIT_COMBINECHANNEL, m_edtCombineChannel);
	DDX_Control(pDX, IDC_BUTTON_VIDEOCOMBINE, m_btnVideoCombine);
	DDX_Control(pDX, IDC_CHECK_ENABLEAUDIOMIX, m_btnEnableAudioMix);
	DDX_Control(pDX, IDC_EDIT_MIXCHANNEL, m_edtMixChannel);
	DDX_Control(pDX, IDC_BUTTON_AUDIOMIX, m_btnAudioMix);
}


BEGIN_MESSAGE_MAP(CLS_DNVRVideoCombinePage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_CHANNELENABLE, &CLS_DNVRVideoCombinePage::OnBnClickedButtonChannelenable)
	ON_BN_CLICKED(IDC_BUTTON_VIDEOCOMBINE, &CLS_DNVRVideoCombinePage::OnBnClickedButtonVideocombine)
	ON_BN_CLICKED(IDC_BUTTON_AUDIOMIX, &CLS_DNVRVideoCombinePage::OnBnClickedButtonAudiomix)
END_MESSAGE_MAP()


// CLS_DNVRVideoCombinePage message handlers
BOOL CLS_DNVRVideoCombinePage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	SetDlgItemText(IDC_EDIT_PICTURENUM, "");
	SetDlgItemText(IDC_EDIT_COMBINERECT, "");
	SetDlgItemText(IDC_EDIT_COMBINECHANNEL, "");	
	SetDlgItemText(IDC_EDIT_MIXCHANNEL, "");	
	m_edtPictureNum.SetLimitText(5);
	m_edtCombineRect.SetLimitText(5);
	m_edtCombineChannel.SetLimitText(299);
	m_edtMixChannel.SetLimitText(299);

	UI_UpdateDialog();

	return TRUE;
}

void CLS_DNVRVideoCombinePage::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
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

	UI_UpdateVideoCombineEnable();
	UI_UpdateVideoCombine();
}

void CLS_DNVRVideoCombinePage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_DNVRVideoCombinePage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_VIDEOCOMBINEENABLE,IDS_CONFIG_DNVR_VIDEOCOMBINEENABLE);
	SetDlgItemTextEx(IDC_STATIC_CHANNELENABLE,IDS_CONFIG_DNVR_ALMSCH_INPUTSCH);
	SetDlgItemTextEx(IDC_BUTTON_CHANNELENABLE,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_VIDEOCOMBINE,IDS_CONFIG_DNVR_VIDEOCOMBINE);
	SetDlgItemTextEx(IDC_STATIC_PICTURENUM,IDS_CONFIG_DNVR_PICTURENUM);
	SetDlgItemTextEx(IDC_STATIC_COMBINERECT,IDS_CONFIG_DNVR_COMBINERECT);
	SetDlgItemTextEx(IDC_STATIC_COMBINECHANNEL,IDS_CONFIG_DNVR_COMBINECHANNEL);
	SetDlgItemTextEx(IDC_BUTTON_VIDEOCOMBINE,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_AUDIOMIX,IDS_CONFIG_DNVR_AUDIOMIX);
	SetDlgItemTextEx(IDC_CHECK_ENABLEAUDIOMIX,IDS_CONFIG_DNVR_ENABLEAUDIOMIX);
	SetDlgItemTextEx(IDC_STATIC_MIXCHANNEL,IDS_CONFIG_DNVR_MIXCHANNEL);
	SetDlgItemTextEx(IDC_BUTTON_AUDIOMIX,IDS_SET);
}

BOOL CLS_DNVRVideoCombinePage::UI_UpdateVideoCombineEnable()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iChannelNum = 0;
	int iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetChannelNum (%d,%d)",m_iLogonID,iChannelNum);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetChannelNum (%d,%d)",m_iLogonID,iChannelNum);
	}

	for(int i=0; i<32; i++)
	{
		m_chkChannelEnable[i].SetCheck(BST_UNCHECKED);
		if (i < iChannelNum)
		{
			m_chkChannelEnable[i].EnableWindow(TRUE);
		}
		else
		{
			m_chkChannelEnable[i].EnableWindow(FALSE);
		}
	}
	int iEnable = -1;
	if (iChannelNum > 32)
	{
		iChannelNum = 32;
	}
	for(int i=0; i<iChannelNum; i++)
	{
		iRet = NetClient_GetPreRecEnable(m_iLogonID, i, &iEnable);
		if (0 == iRet)
		{
			m_chkChannelEnable[i].SetCheck(iEnable?BST_CHECKED:BST_UNCHECKED);
			AddLog(LOG_TYPE_SUCC,"","NetClient_GetPreRecEnable (%d,%d,%d)",m_iLogonID,i,iEnable);
		} 
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetPreRecEnable (%d,%d,%d)",m_iLogonID,i,iEnable);
		}
	}
	return TRUE;
}

void CLS_DNVRVideoCombinePage::OnBnClickedButtonChannelenable()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iChannelNum = 0;
	int iRet = NetClient_GetChannelNum(m_iLogonID, &iChannelNum);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetChannelNum (%d,%d)",m_iLogonID,iChannelNum);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetChannelNum (%d,%d)",m_iLogonID,iChannelNum);
	}

	if (iChannelNum > 32)
	{
		iChannelNum = 32;
	}

	for (int i=0; i<iChannelNum; i++)
	{
		int iEnable = (m_chkChannelEnable[i].GetCheck() == BST_CHECKED)?1:0;
		iRet = NetClient_SetPreRecEnable(m_iLogonID, i, iEnable);
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetPreRecEnable (%d,%d,%d)",m_iLogonID,i,iEnable);
		} 
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetPreRecEnable (%d,%d,%d)",m_iLogonID,i,iEnable);
		}
	}
}

BOOL CLS_DNVRVideoCombinePage::UI_UpdateVideoCombine()
{
	if (m_iLogonID < 0)
		return FALSE;

	TVideoCombine svc = {0};
	int iRet = NetClient_GetVideoCombine(m_iLogonID, &svc, sizeof(svc));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetVideoCombine (%d,%d)",m_iLogonID,sizeof(svc));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetVideoCombine (%d,%d)",m_iLogonID,sizeof(svc));
	}
	if (svc.iPicNum > 0)
	{
		SetDlgItemInt(IDC_EDIT_PICTURENUM, svc.iPicNum);
		SetDlgItemInt(IDC_EDIT_COMBINERECT, svc.iRec);
		SetDlgItemText(IDC_EDIT_COMBINECHANNEL, svc.cChannelID);
	}
	else
	{
		SetDlgItemText(IDC_EDIT_PICTURENUM, "");
		SetDlgItemText(IDC_EDIT_COMBINERECT, "");
		SetDlgItemText(IDC_EDIT_COMBINECHANNEL, "");	
	}
	//»ìÒô
	TAudioMix mix = {0};
	mix.iChannel = m_iChannelNo;
	iRet = NetClient_GetVideoCombine(m_iLogonID, &mix, sizeof(mix));
	if (0 == iRet)
	{
		m_btnEnableAudioMix.SetCheck(mix.iEnable>0?BST_CHECKED:BST_UNCHECKED);
		SetDlgItemText(IDC_EDIT_MIXCHANNEL, mix.cMixChannels);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetVideoCombine (%d,%d)",m_iLogonID,mix.iChannel);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetVideoCombine (%d,%d)",m_iLogonID,mix.iChannel);
	}
	return TRUE;
}

void CLS_DNVRVideoCombinePage::OnBnClickedButtonVideocombine()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TVideoCombine svc = {0};
	svc.iPicNum = GetDlgItemInt(IDC_EDIT_PICTURENUM);
	svc.iRec = GetDlgItemInt(IDC_EDIT_COMBINERECT);
	GetDlgItemText(IDC_EDIT_COMBINECHANNEL, svc.cChannelID, 299);
	int iRet = NetClient_SetVideoCombine(m_iLogonID, &svc, sizeof(svc));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetVideoCombine (%d,%d)",m_iLogonID,sizeof(svc));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetVideoCombine (%d,%d)",m_iLogonID,sizeof(svc));
	}
}

void CLS_DNVRVideoCombinePage::OnBnClickedButtonAudiomix()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TAudioMix mix = {0};
	mix.iEnable = (m_btnEnableAudioMix.GetCheck() == BST_CHECKED)?1:0;
	mix.iChannel = m_iChannelNo;
	GetDlgItemText(IDC_EDIT_MIXCHANNEL, mix.cMixChannels, 299);
	int iRet = NetClient_SetVideoCombine(m_iLogonID, &mix, sizeof(TAudioMix));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetVideoCombine (%d,%d)",m_iLogonID,mix.iChannel);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetVideoCombine (%d,%d)",m_iLogonID,mix.iChannel);
	}
}
