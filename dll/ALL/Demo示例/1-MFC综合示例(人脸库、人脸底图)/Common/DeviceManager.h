#ifndef _DEVICE_MANAGER_H
#define _DEVICE_MANAGER_H

#include <map>
#include <list>
using namespace std;

typedef struct DEVICE_INFO
{
	int iPort;
	char cIP[16];
	char cID[64];
	char cProxy[16];
	char cUserName[16];
	char cPassword[16];
	char cNvsName[32];
	char cAccontName[16];	//连接目录服务器的帐户
	char cAccontPasswd[16];	//连接目录服务器的帐户密码
	HTREEITEM hItem;
	BOOL bIsTalking;
	int  iTalkType;
	char cTalkInputFile[256];
	HANDLE hThreadTalk;
	HANDLE hEventQuitTalking;
	unsigned int uiInterTalkID;
}*PDEVICE_INFO;

typedef struct CHANNEL_INFO 
{
	int iLogonID;
	int iChannelNo;
	int iStreamNo;
	HTREEITEM hItem;
	void* pVideo;
	BOOL bIsAudioPlaying;
	int iRecordType;
	BOOL bIsRecording;
	FILE* pfYuv;
	FILE* pfPcm;
	FILE* pfRaw;
}*PCHANNEL_INFO;

typedef map<int,PDEVICE_INFO> DeviceMap;
typedef map<unsigned int,PCHANNEL_INFO> ChannelMap;
typedef list<PDEVICE_INFO> DeviceList;
typedef list<PCHANNEL_INFO> ChannelList;
typedef DeviceMap::iterator ItDeviceMap;
typedef ChannelMap::iterator ItChannelMap;
typedef DeviceList::iterator ItDeviceList;
typedef ChannelList::iterator ItChannelList;

class CLS_DeviceManager
{
public:
	static CLS_DeviceManager* Instance();
	static void Destroy();
	PDEVICE_INFO FindDevice(char* _pcIP, int _iPort, char* _pcProxy,char* _pcID,int* _piLogonID);
	PDEVICE_INFO FindDevice(int _iLogonID);
	PDEVICE_INFO AddDevice(int _iLogonID);
	PDEVICE_INFO RemoveDevice(int _iLogonID);
	PDEVICE_INFO RemoveDevice(char* _pcIP, int _iPort,char* _pcProxy,char* _pcID,int* _piLogonID);
	PCHANNEL_INFO FindChannel(int _iLogonID,int _iChannelNo,int _iStreamNo,unsigned int* _puConnID);
	PCHANNEL_INFO FindChannel(unsigned int _uConnID);
	PCHANNEL_INFO AddChannel(unsigned int _uConnID);
	PCHANNEL_INFO RemoveChannel(unsigned int _uConnID);
	PCHANNEL_INFO RemoveChannel(int _iLogonID,int _iChannelNo,int _iStreamNo,unsigned int* _puConnID);

private:
	CLS_DeviceManager();
	~CLS_DeviceManager();
	PDEVICE_INFO GetFreeDevice();
	BOOL IsDeviceEqual(PDEVICE_INFO _pDevice,char* _pcIP, int _iPort, char* _pcProxy,char* _pcID);
	BOOL IsChannelEqual(PCHANNEL_INFO _pChannel,int _iLogonID,int _iChannelNo,int _iStreamNo);
	PCHANNEL_INFO GetFreeChannel();

private:
	static CLS_DeviceManager* s_pInstance;
	DeviceMap m_mapDevice;
	ChannelMap m_mapChannel;
	DeviceList m_lstFreeDevice;		//维护未使用的设备列表(重复利用)
	ChannelList m_lstFreeChannel;	//维护未使用的通道列表(重复利用)

};

#endif
