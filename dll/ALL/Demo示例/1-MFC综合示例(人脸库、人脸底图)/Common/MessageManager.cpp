#include "StdAfx.h"
#include "MessageManager.h"

CLS_MessageManager* CLS_MessageManager::s_pInstance = NULL;
CLS_MessageManager::CLS_MessageManager( void )
{
	::InitializeCriticalSection(&m_csList);
}

CLS_MessageManager::~CLS_MessageManager( void )
{
	list<void*>::iterator itMemory = m_lstFreeMemory.begin();
	while(m_lstFreeMemory.end() != itMemory)
	{
		free(*itMemory);
		++itMemory;
	}
	m_lstFreeMemory.clear();
	::DeleteCriticalSection(&m_csList);
}

void* CLS_MessageManager::MallocMemory(int _iSize)
{
	if (_iSize > MESSAGE_MEMORY_SIZE)
	{
		return NULL;
	}
	::EnterCriticalSection(&m_csList);
	void* pMemory = NULL;
	if (m_lstFreeMemory.empty())
	{
		pMemory = malloc(MESSAGE_MEMORY_SIZE);
	}
	else
	{
		pMemory = m_lstFreeMemory.front();
		m_lstFreeMemory.pop_front();
	}
	
	if (pMemory)
	{
		memset(pMemory,0,MESSAGE_MEMORY_SIZE);
	}
	
	if (m_lstFreeMemory.size() > MESSAGE_MEMORY_COUNT)
	{
		list<void*>::iterator itMemory = m_lstFreeMemory.begin();
		while(m_lstFreeMemory.end() != itMemory)
		{
			free(*itMemory);
			++itMemory;
		}
		m_lstFreeMemory.clear();
	}

	::LeaveCriticalSection(&m_csList);
	return pMemory;
}

void CLS_MessageManager::FreeMemory(void* _pMemory)
{
	::EnterCriticalSection(&m_csList);
	if (_pMemory)
	{
		m_lstFreeMemory.push_back(_pMemory);
	}
	::LeaveCriticalSection(&m_csList);
}

CLS_MessageManager* CLS_MessageManager::Instance()
{
	if (NULL == s_pInstance)
	{
		s_pInstance = new CLS_MessageManager();
	}
	return s_pInstance;
}

void CLS_MessageManager::Destroy()
{
	if (s_pInstance)
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}
