 // VideoDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VideoPage.h"

// CLS_VideoPage dialog

IMPLEMENT_DYNAMIC(CLS_VideoPage, CDialog)

CLS_VideoPage::CLS_VideoPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_VideoPage::IDD, pParent)
{
	m_pVideo = NULL;
	m_uConnID = -1;
}

CLS_VideoPage::~CLS_VideoPage()
{
	if (m_pVideo)
	{
		m_pVideo->DestroyWindow();
		delete m_pVideo;
		m_pVideo = NULL;
	}
	m_uConnID = -1;
}

void CLS_VideoPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_VideoPage, CLS_BasePage)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

BOOL CLS_VideoPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	return TRUE;
}

int CLS_VideoPage::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	m_pVideo = CLS_VideoView::CreateInstance(0x7FFFFFFF,this);
	RECT rcShow = {0};
	GetClientRect(&rcShow);
	m_pVideo->MoveWindow(&rcShow);
	m_pVideo->ShowWindow(SW_SHOW);
	return 0;
}

void CLS_VideoPage::OnClose()
{
	CloseVideo();
}

void CLS_VideoPage::OnDestroy()
{
	CLS_BasePage::OnDestroy();
	
}

BOOL CLS_VideoPage::ShowVideo( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (_iLogonID < 0 || _iChannelNo < 0 || _iStreamNo < 0)
	{
		return FALSE;
	}

	PDEVICE_INFO pDevice = FindDevice(_iLogonID);
	if(NULL == pDevice)
	{
		AddLog(LOG_TYPE_MSG,"","FindDevice(%d) Can not find device",_iLogonID);
		return FALSE;
	}

	ShowWindow(SW_SHOW);

	int iRet = -1;
	CLS_VideoView* pVideo = NULL;
	PCHANNEL_INFO pChannel = FindChannel(_iLogonID,_iChannelNo,_iStreamNo,&m_uConnID);
	if (pChannel)
	{
		iRet = NetClient_ResetPlayerWnd(m_uConnID,m_pVideo->GetSafeHwnd());
		if (0 == iRet)
		{
			m_pVideo->SetConnID(m_uConnID);
			AddLog(LOG_TYPE_SUCC,"","NetClient_ResetPlayerWnd(%u,0x%08x)",m_uConnID,m_pVideo->GetSafeHwnd());
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_ResetPlayerWnd(%u,0x%08x)",m_uConnID,m_pVideo->GetSafeHwnd());
		}
		return TRUE;
	}

	CLIENTINFO tInfo = {0};
	tInfo.m_iServerID = _iLogonID;
	tInfo.m_iChannelNo = _iChannelNo;
	tInfo.m_iStreamNO = _iStreamNo;
	tInfo.m_iNetMode = NETMODE_TCP;
	tInfo.m_iTimeout = 20;
	memcpy_s(tInfo.m_cRemoteIP,sizeof(tInfo.m_cRemoteIP),pDevice->cIP,sizeof(pDevice->cIP));

	iRet = NetClient_StartRecvEx(&m_uConnID,&tInfo,NULL,NULL);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"%s CH%d-%d","(%d)NetClient_StartRecvEx(%u,,,)",tInfo.m_cRemoteIP
			,tInfo.m_iChannelNo,tInfo.m_iStreamNO,iRet,m_uConnID);

		PCHANNEL_INFO pChannel = AddChannel(m_uConnID);
		if (pChannel)
		{
			pChannel->iLogonID = _iLogonID;
			pChannel->iChannelNo = _iChannelNo;
			pChannel->iStreamNo = _iStreamNo;
			pChannel->hItem = NULL;
			m_pVideo->SetConnID(m_uConnID);
			pChannel->pVideo = m_pVideo;
		}
		else
		{
			AddLog(LOG_TYPE_MSG,"%s CH%d-%d","AddChannel(%u) Can not add channel",tInfo.m_cRemoteIP,tInfo.m_iChannelNo
				,tInfo.m_iStreamNO,m_uConnID);
		}
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"%s CH%d-%d","(%d)NetClient_StartRecvEx(%u)",tInfo.m_cRemoteIP
			,tInfo.m_iChannelNo,tInfo.m_iStreamNO,iRet,m_uConnID);

		PCHANNEL_INFO pChannel = FindChannel(m_uConnID);
		if (pChannel && pChannel->pVideo)
		{
			pVideo = (CLS_VideoView*)pChannel->pVideo;
			RECT rcShow = {0};
			iRet = NetClient_StartPlay(m_uConnID,pVideo->GetSafeHwnd(), rcShow, 0);
			if (iRet == 0)
			{
				AddLog(LOG_TYPE_SUCC,"%s CH%d-%d","NetClient_StartPlay(%u,,,)",tInfo.m_cRemoteIP,tInfo.m_iChannelNo
					,tInfo.m_iStreamNO,m_uConnID);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"%s CH%d-%d","NetClient_StartPlay(%u,,,)",tInfo.m_cRemoteIP,tInfo.m_iChannelNo
					,tInfo.m_iStreamNO,m_uConnID);
			}
		}
		else
		{
			AddLog(LOG_TYPE_MSG,pDevice->cIP,"FindChannel(%u) Can not find channel",m_uConnID);
		}
	}

	return TRUE;
}

BOOL CLS_VideoPage::CloseVideo()
{
	if (m_hWnd)
	{
		ShowWindow(SW_HIDE);
	}

	if (-1 == m_uConnID)
	{
		return TRUE;
	}

	PCHANNEL_INFO pChannel = FindChannel(m_uConnID);
	if (pChannel)
	{
		if (pChannel->pVideo == m_pVideo)
		{
			RemoveChannel(m_uConnID);
		}
		else if(pChannel->pVideo)
		{
			CLS_VideoView* pVideo = (CLS_VideoView*)pChannel->pVideo;
			int iRet = NetClient_ResetPlayerWnd(m_uConnID,pVideo->GetSafeHwnd());
			if (0 == iRet)
			{
				AddLog(LOG_TYPE_SUCC,"","NetClient_ResetPlayerWnd(%u,0x%08x)",m_uConnID,pVideo->GetSafeHwnd());
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_ResetPlayerWnd(%u,0x%08x)",m_uConnID,pVideo->GetSafeHwnd());
			}
			return TRUE;
		}
	}

	NetClient_StopRecv(m_uConnID);
	AddLog(LOG_TYPE_SUCC,"","NetClient_StopRecv(%u)",m_uConnID);
	m_uConnID = -1;

	return TRUE;
}

void CLS_VideoPage::OnSize(UINT nType, int cx, int cy)
{
	CLS_BasePage::OnSize(nType, cx, cy);

	if (m_pVideo)
	{
		RECT rcShow = {0};
		GetClientRect(&rcShow);
		m_pVideo->MoveWindow(&rcShow);
	}
}
