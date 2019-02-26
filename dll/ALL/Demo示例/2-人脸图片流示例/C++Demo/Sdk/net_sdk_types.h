
#ifndef _NET_SDK_TYPES_H_
#define _NET_SDK_TYPES_H_

#ifndef LEN_2
#define LEN_2   2
#endif

#ifndef LEN_4
#define LEN_4   4
#endif

#ifndef LEN_6
#define LEN_6   6
#endif

#ifndef LEN_8
#define LEN_8   8
#endif


#ifndef LEN_10
#define LEN_10	10
#endif

#ifndef LEN_16
#define LEN_16  16
#endif

#ifndef LEN_17
#define LEN_17  17
#endif

#ifndef LEN_20
#define LEN_20  20
#endif

#ifndef LEN_24
#define LEN_24  24
#endif

#ifndef LEN_31
#define LEN_31  31
#endif

#ifndef LEN_32
#define LEN_32  32
#endif

#ifndef LEN_33
#define LEN_33  33
#endif

#ifndef LEN_36
#define LEN_36  36
#endif

#ifndef LEN_64
#define LEN_64  64
#endif

#ifndef LEN_65
#define LEN_65		65
#endif

#ifndef LEN_128
#define LEN_128 128
#endif

#ifndef LEN_250
#define LEN_250	250
#endif

#ifndef LEN_256
#define LEN_256 256
#endif


#ifndef LEN_255
#define LEN_255 255
#endif

#ifndef LEN_300
#define LEN_300 300
#endif

#ifndef LEN_512
#define LEN_512 512
#endif

#ifndef LEN_1024
#define LEN_1024 1024
#endif

#define MAX_QUERY_PAGE_COUNT							20
#define MAX_QUERY_VCA_CONDITION							32
#define MAX_VCA_FILE_COUNT								5
#define MAX_VCA_ATTR_COUNT								32
#define MAX_QUERY_LIST_COUNT							32


typedef struct
{
	unsigned short iYear;   							/* Year */
	unsigned short iMonth;  							/* Month */
	unsigned short iDay;    							/* Day */
	unsigned short iHour;   							/* Hour */
	unsigned short iMinute; 							/* Minute */
	unsigned short iSecond; 							/* Second */
} NVS_FILE_TIME,*PNVS_FILE_TIME;

typedef struct tagQueryChanNo
{
	int 			iChanNo;
	int 			iStream;
}QueryChanNo, *PQueryChanNo;


typedef struct tagNetFileQueryVca
{
	int				iSize;
	
	int				iChanCount;
	int				iChanSize;
	QueryChanNo*	pChanList;

	int				iVcaCount;
	int				iVcaList[MAX_QUERY_LIST_COUNT];

	NVS_FILE_TIME	tBegTime;
	NVS_FILE_TIME	tEndTime;
	int				iPageCount;
	int				iPageNo;
	int				iFileType;

	int				iConditionCount;
	char			cQueryCondition[MAX_QUERY_VCA_CONDITION][LEN_256];
}NetFileQueryVca, *pNetFileQueryVca;


typedef struct tagVcaFileAttr
{
	int				iFileIndex;
	char			cFileName[LEN_256];
	int				iFileSize;
	int				iFileType;
	int				iReserve;
	char			cReserve[LEN_64];
}VcaFileAttr, *pVcaFileAttr;


typedef struct tagNetFileQueryVcaResult
{
	int				iSize;
	int				iChanNo;
	int				iFileAttrCount;
	VcaFileAttr		tFileAttr[MAX_VCA_FILE_COUNT];

	int				iTotal;
	int				iCurPageCount;
	int				iItemIndex;
	int				iFileType;
	int				iVcaType;
	NVS_FILE_TIME	tBegTime;
	NVS_FILE_TIME	tEndTime;
	
	int				iExAttrCount;
	char			cExAttr[MAX_VCA_ATTR_COUNT][LEN_256];
}NetFileQueryVcaResult, *pNetFileQueryVcaResult;

typedef struct tagIpcDevAttr
{
	int				iSize;
	int				iType;
	int				iParam;
}IpcDevAttr, *pIpcDevAttr;


typedef struct tagUniqueAlertAlarmStatClr
{
	int					iSize;
	int					iSceneId;
	int					iTypeEnable[LEN_32];//Whether the current alert event needs to eliminate the state of the alarm
	int					iEventNo;
}UniqueAlertAlarmStatClr,*pUniqueAlertAlarmStatClr;

typedef struct tagITS_LightStatus
{
	int					iSize;
	int					iLaneNo;
	int					iLightType;
	int					iStatus;
}ITS_LightStatus, *pITS_LightStatus;

typedef struct tagNetBitRate
{
	int			iSize;
	int			iMaxBw;		//NIC maximum capacity bandwidth
	int			iMaxRxBw;	//maximum access bandwidth
	int			iMaxTxBw;	//maximum forwarding bandwidth
} NetBitRate, *pNetBitRate;

typedef struct tagSipLocalServer
{
	int			iSize;
	int			iServerPort;		//local server port,default 5060
	char		cServerID[LEN_64];	//local server ID
	int			iHeartBeatInterval;	//heart beat interval,Unit: s
	int			iHeartBeatTimes;	//heart beat times
} SipLocalServer, *pSipLocalServer;

#define MAX_MACFILTER_COUNT			32
#define MAC_FILTERTYPE_DISAUTH		0		//Disable MAC authentication
#define MAC_FILTERTYPE_DISACCESS	1		//Disable MAC access
#define MAC_FILTERTYPE_ALLOWACCESS	2		//Allow MAC access
typedef struct tagMacAddrFilter
{
	int			iSize;
	int			iFilterType;		//filter type:0-Disable MAC authentication; 1-Disable MAC access; 2-Allow MAC access
	int			iMacCount;			//mac count,supports up to 32 different MAC addresses
	char		cMacAddr[MAX_MACFILTER_COUNT][LEN_64];	//MAC address string
} MacAddrFilter, *pMacAddrFilter;


#define VPN_VIRNETCARD_TUN			0
#define VPN_VIRNETCARD_TAP			1

#define VPN_PROTOCOL_TCP			0
#define VPN_PROTOCOL_UDP			1

#define VPN_COMPRESS_DISABLE		0
#define VPN_COMPRESS_LZO			1
#define VPN_COMPRESS_LZ4V2			2

#define VPN_CERTIFICATE_AUTH		0
#define VPN_USERNAMEPWD_AUTH		1
#define VPN_CERT_NAMEPWD_AUTH		2
typedef struct tagVpnParam
{
	int			iSize;
	int			iEnable;			//Enable switch:0-disable openvpn, 1-enable openvpn
	char		cServerIp[LEN_64];	//VPN server address
	int			iServerPort;		//VPN server port
	int			iVirNetCardType;	//Virtual network card type:0-TUN, 1-TAP
	int			iProtoType;			//Transfer Protocol:0-TCP, 1-UDP
	int			iTlsEnable;			//Whether to enable ta.key attack defense:0-disable, 1-enable
	int			iCompress;			//Compression method:0-Not enabled; 1-LZO; 2-LZ4_V2
	int			iCipherType;		//Data encryption method
	int			iIdentifyType;		//verification method:0: Certificate authentication 1: User name password authentication 2: Certificate + username password
	char		cUserName[LEN_64];	//User name, valid when the authentication method is 1 or 2 and the length is <=32
	char		cPassword[LEN_64];	//The password is valid when the authentication method is 1 or 2. The password must be encrypted using the base64 algorithm. Password length <= 64 bytes
} VpnParam, *pVpnParam;

typedef struct tagVpnLan
{
	int			iSize;
	int			iLanNo;				//Network card number
	int			iDhcpEnable;		//0-disable; 1-enable
	char		cIP[LEN_32];		//IPV4 IP address
	char 		cMask[LEN_32];		//IPV4 subnet mask
	char 		cGateway[LEN_32];	//IPV4 default gateway
	int			iMtu;				//Mtu value in the tunnel,range:500-65535
} VpnLan, *pVpnLan;

typedef struct tagVpnState
{
	int			iSize;
	int			iLanNo;
	int			iState;				//0: Not connected, 1:Connected
} VpnState, *pVpnState;

#define CHN_STATE_OFFLINE		0
#define CHN_STATE_ONLINE		1
#define CHNOFFLINE_RSN_USRPWDERR	1
#define CHNOFFLINE_RSN_IPBLOCKED	2	//IP is blocked
#define CHNOFFLINE_RSN_ACCTLOCK		3	//Account lockout
#define CHNOFFLINE_RSN_MAXCON		4	//Maximum number of connections
#define CHNOFFLINE_RSN_NETEXCP		5	//network anomaly
#define CHNOFFLINE_RSN_MAXBD		6	//Reach the NVR maximum bandwidth
#define CHNOFFLINE_RSN_CAPUPPER		7	//Performance cap
typedef struct tagChnOnlineState 
{
	int			iSize;
	int			iState;				//OnlineState :0-offline, 1-online
	int			iOffLineReason;		//the reason when the channel is offline
} ChnOnlineState, *pChnOnlineState;

#endif


