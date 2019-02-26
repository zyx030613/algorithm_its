#ifndef _NETADMIN_TYPES_H_
#define _NETADMIN_TYPES_H_

#define TYPE_NVS_T          0     //T NVS
#define TYPE_KEYBOARD       1     //Net keyboard
#define TYPE_CTL_ALLOTER    2     //Control code distributor
#define TYPE_ALARMHOST      3     //Network alarm host
#define TYPE_NVS_S          4     //S NVS
#define TYPE_MATRIX         5     //Matrix
#define TYPE_NET_PU         6     //Network Front-end device
#define TYPE_NET_GURAD      7     //Net Entrance Gurad
#define TYPE_PC_DVR         8     //PC DVR
#define TYPE_S_DECODER      9     //S Decoder
#define TYPE_NVS_TPLUS      10    //TPLUS NVS
#define TYPE_WIH_S          11    //����ְ������
#define TYPE_EMBED_DVR      12    //Ƕ��ʽDVR
#define TYPE_SMS_200        13    //Linux��ý������
#define TYPE_ALARM_HOST42   14    //���籨������
#define TYPE_TC_T820GE      15    //�ⴥ������
#define TYPE_TC_T860GE      16    //����Ƶ����
#define TYPE_TC_T890GE      17    //�ⴥ��������̨
#define TYPE_TC_HDC         18    //�������
#define TYPE_ONVIF          19    //Onvif�豸

typedef struct
{
	char    m_cIP[16];
	char    m_cMAC[18];
	char    m_cMask[16];
	char    m_Gateway[16];
	char    m_cDNS[16];
	int     m_iChanNum;
	int     m_iServerPort;
	int     m_iClientPort;
	int     m_iDeviceType;
	int     m_iHttpPort;
	int     m_iProductModel;
	char    m_cFactoryID[64];
	char    m_cKernelVersion[64];
	char    m_cOCXVersion[64];
}TDEVICE, *PTDEVICE;

typedef void (__stdcall *FIND_NOTIFY)(PTDEVICE _pDevice);

#endif
