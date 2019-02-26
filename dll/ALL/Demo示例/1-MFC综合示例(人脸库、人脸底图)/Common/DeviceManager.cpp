#include "StdAfx.h"
#include "DeviceManager.h"


CLS_DeviceManager* CLS_DeviceManager::s_pInstance = NULL;

CLS_DeviceManager::CLS_DeviceManager(void)
{
	
}

CLS_DeviceManager::~CLS_DeviceManager(void)
{
	ItChannelMap itChannelMap = m_mapChannel.begin();
	while(m_mapChannel.end() != itChannelMap)
	{
		m_lstFreeChannel.push_back(itChannelMap->second);
		++itChannelMap;
	}
	m_mapChannel.clear();

	ItDeviceMap itDeviceMap = m_mapDevice.begin();
	while(m_mapDevice.end() != itDeviceMap)
	{
		m_lstFreeDevice.push_back(itDeviceMap->second);
		++itDeviceMap;
	}
	m_mapDevice.clear();

	ItChannelList itChannelList = m_lstFreeChannel.begin();
	while(m_lstFreeChannel.end() != itChannelList)
	{
		delete *itChannelList;
		++itChannelList;
	}
	m_lstFreeChannel.clear();

	ItDeviceList itDeviceList = m_lstFreeDevice.begin();
	while(m_lstFreeDevice.end() != itDeviceList)
	{
		delete *itDeviceList;
		++itDeviceList;
	}
	m_lstFreeDevice.clear();

}

CLS_DeviceManager* CLS_DeviceManager::Instance()
{
	if (NULL == s_pInstance)
	{
		s_pInstance = new CLS_DeviceManager();
	}
	return s_pInstance;
}

void CLS_DeviceManager::Destroy()
{
	if (s_pInstance)
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}

PDEVICE_INFO CLS_DeviceManager::GetFreeDevice()
{
	if (m_lstFreeDevice.empty())
	{
		m_lstFreeDevice.push_back(new DEVICE_INFO());
	}
	PDEVICE_INFO pDevice = m_lstFreeDevice.back();
	if (pDevice)
	{
		memset(pDevice,0,sizeof(DEVICE_INFO));
		pDevice->uiInterTalkID = -1;
		pDevice->hThreadTalk = NULL;
		pDevice->hEventQuitTalking = NULL;
	}
	m_lstFreeDevice.pop_back();
	return pDevice;
}

BOOL CLS_DeviceManager::IsDeviceEqual(PDEVICE_INFO _pDevice,char* _pcIP, int _iPort, char* _pcProxy,char* _pcID)
{
	if (NULL == _pDevice)
	{
		return FALSE;
	}
	if (NULL == _pcIP)
	{
		_pcIP = "";
	}
	if (NULL == _pcProxy)
	{
		_pcProxy = "";
	}
	if (NULL == _pcID)
	{
		_pcID = "";
	}

	if (strlen(_pcID) <= 0 && strlen(_pcIP) <= 0)
	{
		return FALSE;
	}

	if (0 == strlen(_pcID)*strcmp(_pcID,_pDevice->cID) 
				&& 0 == strlen(_pcIP)*strcmp(_pcIP,_pDevice->cIP)
				&& _pDevice->iPort == _iPort
				/*&& 0 == strlen(_pcProxy)*strcmp(_pcProxy,_pDevice->cProxy)*/)//直连和代理不能同时用
	{
		return TRUE;
	}

	return FALSE;
}

PDEVICE_INFO CLS_DeviceManager::FindDevice( char* _pcIP, int _iPort, char* _pcProxy,char* _pcID,int* _piLogonID)
{
	PDEVICE_INFO pDevice = NULL;
	ItDeviceMap it = m_mapDevice.begin();
	while(m_mapDevice.end() != it)
	{
		pDevice = it->second;
		if (TRUE == IsDeviceEqual(pDevice,_pcIP,_iPort,_pcProxy,_pcID))
		{
			if (_piLogonID)
			{
				*_piLogonID = it->first;
			}
			return it->second;
		}
		++it;
	}
	return NULL;
}

PDEVICE_INFO CLS_DeviceManager::FindDevice( int _iLogonID )
{
	if (_iLogonID < 0)
	{
		return NULL;
	}

	ItDeviceMap it = m_mapDevice.find(_iLogonID);
	if (m_mapDevice.end() == it)
	{
		return NULL;
	}
	return it->second;
}

PDEVICE_INFO CLS_DeviceManager::AddDevice( int _iLogonID )
{
	if (_iLogonID < 0)
	{
		return NULL;
	}

	ItDeviceMap it = m_mapDevice.find(_iLogonID);
	if (m_mapDevice.end() == it)
	{
		m_mapDevice[_iLogonID] = GetFreeDevice();
	}
	return m_mapDevice[_iLogonID];
}

PDEVICE_INFO CLS_DeviceManager::RemoveDevice(int _iLogonID)
{
	if (_iLogonID < 0)
	{
		return NULL;
	}

	ItDeviceMap itDevice = m_mapDevice.find(_iLogonID);
	if (m_mapDevice.end() == itDevice)
	{
		return NULL;
	}

	PCHANNEL_INFO pChannel = NULL;
	unsigned int uConnID = -1;
	ItChannelMap itChannel = m_mapChannel.begin();
	while(itChannel != m_mapChannel.end())
	{
		pChannel = itChannel->second;
		if (pChannel && pChannel->iLogonID == _iLogonID)
		{
			uConnID = itChannel->first;
			m_lstFreeChannel.push_back(itChannel->second);
			++itChannel;
			m_mapChannel.erase(uConnID);
		}
		else
		{
			++itChannel;
		}
	}
	
	PDEVICE_INFO pDevice = itDevice->second;
	m_lstFreeDevice.push_back(pDevice);
	m_mapDevice.erase(itDevice);
	return pDevice;
}

PDEVICE_INFO CLS_DeviceManager::RemoveDevice( char* _pcIP, int _iPort,char* _pcProxy,char* _pcID,int* _piLogonID )
{
	PDEVICE_INFO pDevice = NULL;
	ItDeviceMap itDevice = m_mapDevice.begin();
	while(m_mapDevice.end() != itDevice)
	{
		pDevice = itDevice->second;
		if (TRUE == IsDeviceEqual(pDevice,_pcIP,_iPort,_pcProxy,_pcID))
		{
			break;
		}
		++itDevice;
	}
	if (m_mapDevice.end() == itDevice)
	{
		return NULL;
	}

	int iLogonID = itDevice->first;
	PCHANNEL_INFO pChannel = NULL;
	unsigned int uConnID = -1;
	ItChannelMap itChannel = m_mapChannel.begin();
	while(itChannel != m_mapChannel.end())
	{
		pChannel = itChannel->second;
		if (pChannel && pChannel->iLogonID == iLogonID)
		{
			uConnID = itChannel->first;
			m_lstFreeChannel.push_back(itChannel->second);
			++itChannel;
			m_mapChannel.erase(uConnID);
		}
		else
		{
			++itChannel;
		}
	}

	if (_piLogonID)
	{
		*_piLogonID = itDevice->first;
	}
	m_lstFreeDevice.push_back(pDevice);
	m_mapDevice.erase(itDevice);
	return pDevice;
}

BOOL CLS_DeviceManager::IsChannelEqual(PCHANNEL_INFO _pChannel,int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	if (NULL == _pChannel)
	{
		return FALSE;
	}

	if (_pChannel->iLogonID == _iLogonID 
		&& _pChannel->iChannelNo == _iChannelNo
		&& _pChannel->iStreamNo == _iStreamNo)
	{
		return TRUE;
	}

	return FALSE;
}

PCHANNEL_INFO CLS_DeviceManager::GetFreeChannel()
{
	if (m_lstFreeChannel.empty())
	{
		m_lstFreeChannel.push_back(new CHANNEL_INFO());
	}
	PCHANNEL_INFO pChannel = m_lstFreeChannel.back();
	if (pChannel)
	{
		memset(pChannel,0,sizeof(CHANNEL_INFO));
	}
	m_lstFreeChannel.pop_back();
	return pChannel;
}

PCHANNEL_INFO CLS_DeviceManager::FindChannel( int _iLogonID,int _iChannelNo,int _iStreamNo,unsigned int* _puConnID)
{
	if (_iLogonID < 0 || _iChannelNo < 0 || _iStreamNo < 0)
	{
		return NULL;
	}

	PCHANNEL_INFO pChannel = NULL;
	ItChannelMap it = m_mapChannel.begin();
	while(m_mapChannel.end() != it)
	{
		pChannel = it->second;
		if (TRUE == IsChannelEqual(pChannel,_iLogonID,_iChannelNo,_iStreamNo))
		{
			if (_puConnID)
			{
				*_puConnID = it->first;
			}
			return it->second;
		}
		++it;
	}
	return NULL;
}

PCHANNEL_INFO CLS_DeviceManager::FindChannel( unsigned int _uConnID )
{
	if (-1 == _uConnID)
	{
		return NULL;
	}

	ItChannelMap it = m_mapChannel.find(_uConnID);
	if (m_mapChannel.end() == it)
	{
		return NULL;
	}
	return it->second;
}

PCHANNEL_INFO CLS_DeviceManager::AddChannel(unsigned int _uConnID)
{
	if (-1 == _uConnID)
	{
		return NULL;
	}

	ItChannelMap it = m_mapChannel.find(_uConnID);
	if (m_mapChannel.end() == it)
	{
		m_mapChannel[_uConnID] = GetFreeChannel();
	}
	return m_mapChannel[_uConnID];
}

PCHANNEL_INFO CLS_DeviceManager::RemoveChannel(unsigned int _uConnID)
{
	if (-1 == _uConnID)
	{
		return NULL;
	}

	ItChannelMap it = m_mapChannel.find(_uConnID);
	if (m_mapChannel.end() == it)
	{
		return NULL;
	}

	PCHANNEL_INFO pChannel = it->second;
	m_lstFreeChannel.push_back(pChannel);
	m_mapChannel.erase(it);
	return pChannel;
}

PCHANNEL_INFO CLS_DeviceManager::RemoveChannel( int _iLogonID,int _iChannelNo,int _iStreamNo,unsigned int* _puConnID )
{
	if (_iLogonID < 0 || _iChannelNo < 0 || _iStreamNo < 0)
	{
		return NULL;
	}

	PCHANNEL_INFO pChannel = NULL;
	ItChannelMap itChannel = m_mapChannel.begin();
	while(m_mapChannel.end() != itChannel)
	{
		pChannel = itChannel->second;
		if (TRUE == IsChannelEqual(pChannel,_iLogonID,_iChannelNo,_iStreamNo))
		{
			break;
		}
		++itChannel;
	}

	if(m_mapChannel.end() == itChannel)
	{
		return NULL;
	}

	if (_puConnID)
	{
		*_puConnID = itChannel->first;
	}
	m_lstFreeChannel.push_back(pChannel);
	m_mapChannel.erase(itChannel);
	return pChannel;
}