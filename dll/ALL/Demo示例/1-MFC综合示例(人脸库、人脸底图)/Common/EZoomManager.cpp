#include "stdafx.h"
#include "EZoomManager.h"

CLS_EZoomManager* CLS_EZoomManager::s_pInstance = NULL;
CLS_EZoomManager::CLS_EZoomManager()
{
	for(int i=0; i<MAX_EZOOM_NUM; ++i)
	{
		m_pdlgEZoom[i] = NULL;
	}
}

CLS_EZoomManager::~CLS_EZoomManager(void)
{
	for(int i=0; i<MAX_EZOOM_NUM; ++i)
	{
		if(m_pdlgEZoom[i])
		{
			delete m_pdlgEZoom[i];
			m_pdlgEZoom[i] = NULL;
		}
	}
}

CLS_EZoomManager* CLS_EZoomManager::Instance()
{
	if (NULL == s_pInstance)
	{
		s_pInstance = new CLS_EZoomManager();
	}
	return s_pInstance;
}

void CLS_EZoomManager::Destroy()
{
	if (s_pInstance)
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}

BOOL CLS_EZoomManager::AddEZoom( unsigned int _uiConnID, RECT* _prcVideo )
{
	BOOL bShow = TRUE;
	for(int i=0; i<MAX_EZOOM_NUM; ++i)
	{
		if (NULL == m_pdlgEZoom[i])
		{
			m_pdlgEZoom[i] = new CLS_EZoomView();
			m_pdlgEZoom[i]->Create(IDD_DLG_EZOOM,NULL);
		}
		if (m_pdlgEZoom[i] && m_pdlgEZoom[i]->AddEZoom(_uiConnID,_prcVideo))
		{
			bShow = TRUE;
			break;
		}
	}
	return bShow;
}

BOOL CLS_EZoomManager::DeleteEZoom( unsigned int _uiConnID)
{
	for(int i=0; i<MAX_EZOOM_NUM; ++i)
	{
		if (m_pdlgEZoom[i])
		{
			m_pdlgEZoom[i]->DeleteEZoom(_uiConnID);
		}
	}
	return TRUE;
}

BOOL CLS_EZoomManager::DeleteAllEZoom()
{
	for(int i=0; i<MAX_EZOOM_NUM; ++i)
	{
		if (m_pdlgEZoom[i])
		{
			m_pdlgEZoom[i]->DeleteEZoom(-1,TRUE);
		}
	}
	return TRUE;
}