using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using COMMON_STRUCT;

namespace NVSSDK_INTERFACE
{
    class NVSSDK
    {
        [DllImport("NVSSDK.dll")]
        public static extern Int32 NetClient_Startup_V4(Int32 _iServerPort, Int32 _iClientPort, Int32 _iWnd);
    
        [DllImport("NVSSDK.dll")]
        public static extern Int32 NetClient_Cleanup();
       
        [DllImport("NVSSDK.dll")]
        public static extern Int32 NetClient_Logon(String _cProxy, String _cIP, String _cUserName, String _cPassword, String _pcProID, Int32 _iPort);

        [DllImport("NVSSDK.dll")]
        public static extern Int32 NetClient_Logon_V4(Int32 _iLogonType, IntPtr _pvPara, Int32 _iInBufferSize);

        [DllImport("NVSSDK.dll")]
        public static extern Int32 NetClient_Logoff(Int32 _iLogonID);

        [DllImport("NVSSDK.dll")]
        public static extern Int32 NetClient_GetChannelNum(Int32 _iLogonID, IntPtr _iChannelNum);
       
        [DllImport("NVSSDK.dll", EntryPoint = "NetClient_StartRecv")]
        public static extern Int32 NetClient_StartRecv(ref UInt32 _ulConID, ref CLIENTINFO _cltInfo, RECVDATA_NOTIFY _cbkDataArrive);

        [DllImport("NVSSDK.dll", EntryPoint = "NetClient_StartRecvEx")]
        public static extern Int32 NetClient_StartRecvEx(ref UInt32 _ulConID, ref CLIENTINFO _cltInfo, RECVDATA_NOTIFY_EX _cbkDataNotifyEx, IntPtr _lpUserData);

        [DllImport("NVSSDK.dll")]
        public static extern Int32 NetClient_SetFullStreamNotify_V4(UInt32 _uiRecvID, FULLFRAME_NOTIFY_V4 _cbkFullStream, UInt32 _iUserData);

        [DllImport("NVSSDK.dll")]
        public static extern Int32 NetClient_StopPlay(UInt32 _ulID);

        [DllImport("NVSSDK.dll")]
        public static extern Int32 NetClient_StartPlay(UInt32 _ulID, Int32 _hWnd, RECT _rcShow, UInt32 _iDecflag);

       
        [DllImport("NVSSDK.dll")]
        public static extern Int32 NetClient_StartCaptureData(ulong _ulID);
        
        [DllImport("NVSSDK.dll")]
        public static extern Int32 NetClient_StopCaptureData(ulong _ulID);
  
        [DllImport("NVSSDK.dll")]
        public static extern Int32 NetClient_StopRecv(ulong _ulID);
        
        [DllImport("NVSSDK.dll")]
        public static extern Int32 NetClient_SetNotifyFunction_V4(MAIN_NOTIFY_V4 _MainNotify,
													         ALARM_NOTIFY_V4 _AlarmNotify, 
													         PARACHANGE_NOTIFY_V4  _ParaNotify,
													         COMRECV_NOTIFY_V4 _ComNotify,
													         PROXY_NOTIFY _ProxyNotify);

        [DllImport("NVSSDK.dll")]
        public static extern Int32 NetClient_StartRecvNetPicStream(Int32 _iLogonID, IntPtr _ptPara, Int32 _iBufLen, ref UInt32 _puiRecvID);

        [DllImport("NVSSDK.dll")]
        public static extern Int32 NetClient_StopRecvNetPicStream(UInt32 _uiRecvID);

        [DllImport("NVSSDK.dll")]
        public static extern Int32 NetClient_GetDsmRegstierInfo(Int32 _iCommand, IntPtr _pvBuf, Int32 _iBufSize);
        }
}
