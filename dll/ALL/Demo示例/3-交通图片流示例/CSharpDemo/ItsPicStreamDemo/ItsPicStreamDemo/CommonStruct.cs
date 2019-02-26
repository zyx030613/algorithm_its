using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace COMMON_STRUCT
{
    delegate void RECVDATA_NOTIFY(UInt32 _ulID, string _strData, Int32 _iLen);
    delegate void RECVDATA_NOTIFY_EX(int _ulID, string _ucData, Int32 _iLen, Int32 _iFlag, IntPtr _lpUserData);
    delegate void FULLFRAME_NOTIFY_V4(UInt32 _ulID, UInt32 _ulStreamType, string _cData, Int32 _iLen, IntPtr _iUser, IntPtr _iUserData); //_iUser：文件头数据，_iUserData：用户数据

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    delegate void MAIN_NOTIFY_V4(UInt32 _ulLogonID, int _iWparam, IntPtr _iLParam, IntPtr _iUser);
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    delegate void ALARM_NOTIFY_V4(Int32 _ulLogonID, Int32 _iChan, Int32 _iAlarmState, Int32 _iAlarmType, Int32 _iUser);
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    delegate void PARACHANGE_NOTIFY_V4(Int32 _ulLogonID, Int32 _iChan, Int32 _iParaType, ref STR_Para _strPara, Int32 _iUser);
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    delegate void COMRECV_NOTIFY_V4(Int32 _ulLogonID, IntPtr _cData, Int32 _iLen, Int32 _iComNo, Int32 _iUser);
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    delegate void PROXY_NOTIFY(Int32 _ulLogonID, Int32 _iCmdKey, IntPtr _cData, Int32 _iLen, Int32 _iUser);
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    delegate int NETPICSTREAM_NOTIFY(UInt32 _uiRecvID, int _lCommand, IntPtr _pvCallBackInfo, Int32 _BufLen, IntPtr _iUser);

    [StructLayout(LayoutKind.Sequential)]
    struct STR_Para
    {

    };

    [StructLayout(LayoutKind.Sequential)]
    public struct CLIENTINFO
    {
        public int m_iServerID;         //NVS ID,NetClient_Logon 返回值
        public int m_iChannelNo;	    //Remote host to be connected video channel number (Begin from 0)
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 255)]
        public Char[] m_cNetFile;       //Play the file on net, not used temporarily
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public Char[] m_cRemoteIP;	    //IP address of remote host
        public int m_iNetMode;		    //Select net mode 1--TCP  2--UDP  3--Multicast
        public int m_iTimeout;		    //Timeout length for data receipt
        public int m_iTTL;			    //TTL value when Multicast
        public int m_iBufferCount;      //Buffer number
        public int m_iDelayNum;         //Start to call play progress after which buffer is filled
        public int m_iDelayTime;        //Delay time(second), reserve
        public int m_iStreamNO;         //Stream type
        public int m_iFlag;			    //0，首次请求该录像文件；1，操作录像文件
        public int m_iPosition;		    //0～100，定位文件播放位置；-1，不进行定位
        public int m_iSpeed;			//1，2，4，8，控制文件播放速度        
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct RECT
    {
        public int left;
        public int top;
        public int right;
        public int bottom;
    };

    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate int NET_PICSTREAM_NOTIFY(UInt32 _uiRecvID, int _lCommand, IntPtr _pvBuf, Int32 _iBufLen, IntPtr _pvUser);
    [StructLayout(LayoutKind.Sequential)]
    public class NetPicPara
    {
        public Int32            iStructLen;				//Structure length
        public Int32            iChannelNo;
        public NET_PICSTREAM_NOTIFY    cbkPicStreamNotify;
        public IntPtr			pvUser;
        public NetPicPara()
        {
            cbkPicStreamNotify = null;
            pvUser = IntPtr.Zero;
            iChannelNo = 0;
            iStructLen = 0;
        }
    };

    [StructLayout(LayoutKind.Sequential)]
    class LogonPara
    {
        public int		iSize;			//Structure size
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] btProxy;			//The ip address of the upper-level proxy to which the video is connected,not more than 32 characters, including '\0'
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] btNvsIP;			//IP address，not more than 32 characters, including '\0'
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] btNvsName;		//Nvs name. Used for domain name resolution
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] btUserName;		//Login Nvs username，not more than 16 characters, including '\0'
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] btUserPwd;		//Login Nvs password，not more than 16 characters, including '\0'
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] btProductID;		//Product ID，not more than 32 characters, including '\0'
        public int		iNvsPort;		//The communication port used by the Nvs server, if not specificed,Use the system default port(3000)
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] btCharSet;		//Character set
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] btAccontName;	//The username that connects to the contents server
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] btAccontPasswd;	//The password that connects to the contents server

        public LogonPara()
        {
            btProxy = new byte[32];
            btNvsIP = new byte[32];
            btNvsName = new byte[32];
            btUserName = new byte[16];
            btUserPwd = new byte[16];
            btProductID = new byte[32];
            btCharSet = new byte[32];
            btAccontName = new byte[16];
            btAccontPasswd = new byte[16];
        }
    };

    [StructLayout(LayoutKind.Sequential)]
    class LogonActiveServer
    {
        public int		iSize;	
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] btUserName;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] btUserPwd;	
	    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] btProductID;	//product id	
        public LogonActiveServer()
        {
            btUserName = new byte[16];
            btUserPwd = new byte[16];
            btProductID = new byte[32];
        }
    };

    [StructLayout(LayoutKind.Sequential)]
    class DsmOnline
    {
        public int		iSize;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] btProductID;	        //product id	
        public int		iOnline;			//0--Offline 1--Online
        public DsmOnline()
        {
            btProductID = new byte[32];
        }
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct PicTime
    {
        public UInt32 uiYear;
        public UInt32 uiMonth;
        public UInt32 uiDay;
        public UInt32 uiWeek;
        public UInt32 uiHour;
        public UInt32 uiMinute;
        public UInt32 uiSecondsr;
        public UInt32 uiMilliseconds;
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct PicData
    {
        [MarshalAs(UnmanagedType.Struct)]
        public PicTime		tPicTime;
        public Int32        iDataLen;		    //Image length
        public IntPtr       piPicData;		    //Picture raw data, the upper can be directly saved as a picture
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct VcaPicStream
    {
        public Int32        iStructLen;				//Structure length
        public Int32        iWidth;					//Picture wide
        public Int32        iHeight;				//Picture high
        public Int32        iChannelID;				//Channel number
        public Int32        iEventType;				//Event type
        public Int32        iRuleID;				//Rule ID
        public Int32        iTargetID;				//Target ID
        public Int32        iTargetType;			//Target type:1-person,2-(other),3-car
        public Int32        iTargetSpeed;			//The target speed by the number of pixels per second (pixel/s)
        public Int32        iTargetDirection;		//Target movement direction,0 ~ 359 degrees
        [MarshalAs(UnmanagedType.Struct)]
        public RECT         tTargetPosition;		//target location
        public Int32        iPresetNo;          	//Preset number (scene number)       
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
        public string       strCameraIP;//Camera IP     		
        public Int32        iPicCount;				//Record the number of images included,Maximum 3
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public PicData[]    tPicData; // 结构体数组定义   
    };

    public struct ItsPicStream
    {
        public Int32 			iStructLen;				//Structure length
        public Int32    		iChannelID;				//Lane number
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string		    strPlate;			    //License plate
        public Int32    		iPlateColor;			//License plate color		
        public Int32    		iPlateType;				//License plate type
        public Int32 	  		iCarColor;				//the color of car
        [MarshalAs(UnmanagedType.Struct)]
        RECT		            tPlateRange;			//License plate range
        public Int32    		iCharNum;				//The number of characters in the license plate
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 12)]
        public Int32[]    		iCharConfid;		    //Each character confidence, up to 12 characters
        public Int32    		iPlateConfid;			//The entire license plate confidence
        public Int32    		iRecrdoNum;				//Identify picture serial number
        public Single  		    fSpeed;					//Vehicle speed
        public Int32  		    iVehicleDirection;		//Direction of the vehicle
        public Int32 			iAlarmType;				//Alarm type
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
        public string  		    strCameraIP;		    //Camera IP
        public Int32 			iRedBeginTime;			//Red light start time in seconds
        public Int32 			iRedEndTime;			//Red light end time in seconds
        public Int32    		iPicCount;				//Record the number of images included
        public Int32            iSize;					//The size of strcut PicData 
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public IntPtr[]         tPicData;
        public Int32            iPlatCount;
        public IntPtr           tPlatData;
        public Int32            iFaceCount;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public IntPtr[]         tFaceData;
    };

    public class SDKConstMsg
    {
        public const int WM_USER = 0x0400; 
        public const int WM_MAIN_MESSAGE = WM_USER + 1001;
        public const int MSG_PARACHG = WM_USER + 90910;
        public const int MSG_ALARM = WM_USER + 90911;
        public const int WCM_ERR_ORDER = 2;
        public const int WCM_ERR_DATANET = 3;
        public const int WCM_LOGON_NOTIFY = 7;
        public const int WCM_VIDEO_HEAD = 8;
        public const int WCM_VIDEO_DISCONNECT = 9;
        public const int WCM_RECORD_ERR = 13;

        public const int LOGON_SUCCESS = 0;
        public const int LOGON_ING = 1;
        public const int LOGON_RETRY = 2;
        public const int LOGON_DSMING = 3;
        public const int LOGON_FAILED = 4;
        public const int LOGON_TIMEOUT = 5;
        public const int NOT_LOGON = 6;
        public const int LOGON_DSMFAILED = 7;
        public const int LOGON_DSMTIMEOUT = 8;
        public const int PLAYER_PLAYING = 0x02;
        public const int USER_ERROR = 0x10000000;

        public const int WCM_QUERYFILE_FINISHED = 18;  
        public const int WCM_DWONLOAD_FINISHED = 19;
        public const int WCM_DWONLOAD_FAULT = 20;

        public const int DSM_CMD_GET_ONLINE_STATE = 0;
    };

    public class SDKTypes
    {
        public const int SERVER_NORMAL = 0;
        public const int SERVER_ACTIVE = 1;
        public const int SERVER_DNS = 2;

        public const int DSM_STATE_OFFLINE = 0;
        public const int DSM_STATE_ONLINE = 1;

        public const int MAX_SAVE_PCTURE_COUNT = 2000;
        public const int NET_PICSTREAM_CMD_VCA = 1;
        public const int NET_PICSTREAM_CMD_ITS = 2;
    };
}