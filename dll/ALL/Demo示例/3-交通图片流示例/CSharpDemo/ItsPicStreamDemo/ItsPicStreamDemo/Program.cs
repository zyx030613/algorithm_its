using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Runtime.InteropServices;
using System.Threading;
using System.IO;

using COMMON_STRUCT;
using NVSSDK_INTERFACE;

namespace ItsPicStreamDemo
{
    class Program
    {
        public static readonly string[] g_strPlateColor = { "未知", "蓝底白字", "黄底黑字", "白底黑字", "黑底白字", "绿底白字" };
        public static readonly string[] g_strCarColor = {"白色", "红色", "黄色", "黄色", "蓝色", "绿色", "绿色", "紫色", "粉色", "黑色"
								, "红色", "黄色", "黄色", "灰色", "黄色", "蓝色", "蓝色", "绿色", "绿色", "白色"
								, "绿色", "青色", "黄色", "红色", "蓝色", "蓝色", "灰色", "紫色", "紫色", "棕色"
								, "棕色", "棕色"};
        const uint CONST_INVALID_RECV_ID = 0xffffffff;
        private static int g_iLogonID = -1;
        private static uint g_uiRecvID = CONST_INVALID_RECV_ID;
        private static int g_iCount = 0;
        private const string g_strPicStreamDir = @".\PicStream";
        private static MAIN_NOTIFY_V4 MainNotify_V4 = null;
        private static NetPicPara g_tNetPicPara = new NetPicPara();


        private static void MyMAIN_NOTIFY_V4(UInt32 _ulLogonID, int _iWparam, IntPtr _iLParam, IntPtr _iUser)
        {
            int iMsgType = _iWparam & 0xffff;
            int iMsgValue = _iLParam.ToInt32();
            switch (iMsgType)
            {
                case SDKConstMsg.WCM_LOGON_NOTIFY:
                    {
                        Console.WriteLine("WCM_LOGON_NOTIFY!\n");
                        if (SDKConstMsg.LOGON_SUCCESS == iMsgValue)
                        {
                            Console.WriteLine("Logon Success!\n");
                            if (CONST_INVALID_RECV_ID == g_uiRecvID)
                            {
                                StartRecvPicture(); //开始接收图片流
                            }
                        }
                        else
                        {
                            Console.WriteLine("Logon Failed!\n");
                        }
                        break;
                    }
                default:
                    break;
            }
        }

        private static int MyNETPICSTREAM_NOTIFY(UInt32 _uiRecvID, int _lCommand, IntPtr _pvCallBackInfo, Int32 _BufLen, IntPtr _iUser)
        {
            if (null == _pvCallBackInfo)
            {
                return -1;
            }

            if (_uiRecvID != g_uiRecvID)
            {
                return -1;
            }

            if (SDKTypes.NET_PICSTREAM_CMD_ITS != _lCommand)
            {
                return 0;
            }

            if (g_iCount++ >= SDKTypes.MAX_SAVE_PCTURE_COUNT)
            {
                Console.WriteLine("save picture over 2000!\n");
                return -1;
            }

            IntPtr ptVca = _pvCallBackInfo;
            ItsPicStream tItsPicStream = (ItsPicStream)Marshal.PtrToStructure(ptVca, typeof(ItsPicStream));
            
		    int iPlateColor = tItsPicStream.iPlateColor;
            string strPlateColor = "";
            if (iPlateColor >= 0 && iPlateColor < g_strPlateColor.Length)
            {
                strPlateColor= g_strPlateColor[iPlateColor];
            }
            else
            {
                strPlateColor = "未知";
            }
            int iCarColor = tItsPicStream.iCarColor;
            string strCarColor = "";
            if (iCarColor >= 0 && iCarColor < g_strCarColor.Length)
            {
                strCarColor = g_strCarColor[iCarColor]; 
            }
            else
            {
                strCarColor = "未知";
            }
             
            Console.WriteLine("picture info:iPicCount(" + tItsPicStream.iPicCount + "),cCameraIP(" + tItsPicStream.strCameraIP +
            ")" + "cPlate(" + tItsPicStream.strPlate + ")," + "PlateColor(" + strPlateColor + ")," + "CarColor(" + strCarColor + ")\n");

            //抓拍大图，至多8张
            for (int i = 0; i < tItsPicStream.iPicCount && i < 8; ++i)
            {
                if (null == tItsPicStream.tPicData[i])
                {
                    continue;
                }

                PicData tPicData = (PicData)Marshal.PtrToStructure(tItsPicStream.tPicData[i], typeof(PicData));
                PicTime tTime = tPicData.tPicTime;
                DateTime tDataTime = new DateTime((int)tTime.uiYear, (int)tTime.uiMonth, (int)tTime.uiDay, 
                    (int) tTime.uiHour, (int)tTime.uiMinute, (int) tTime.uiSecondsr, (int)tTime.uiMilliseconds);
                string cFileName = ".\\PicStream\\ItsPic-" + tItsPicStream.strCameraIP + "-No" + (g_iCount) + "-Time" + tDataTime.ToString("yyyyMMddhhmmss") + i + ".jpg";
                byte[] btPicData = new byte[tPicData.iDataLen];
                Marshal.Copy(tPicData.piPicData, btPicData, 0, tPicData.iDataLen);                
                FileStream fFile = null;
                try
                {
                    fFile = new FileStream(cFileName, FileMode.Create);
                    fFile.Write(btPicData, 0, tPicData.iDataLen);
                }
                catch (IOException e)
                {
                    Console.WriteLine(e.Message);
                }
                finally
                {
                    if (null != fFile)
                    {
                        fFile.Close();
                    }
                }
            }
            //车牌图片
            if (tItsPicStream.iPlatCount > 0 && null != tItsPicStream.tPlatData)
            {
                PicData tPicData = (PicData)Marshal.PtrToStructure(tItsPicStream.tPlatData, typeof(PicData));
                string cFileName = ".\\PicStream\\ItsPlat-" + tItsPicStream.strCameraIP + "-No" + (g_iCount) + "CP" + ".jpg";
                byte[] btPicData = new byte[tPicData.iDataLen];
                Marshal.Copy(tPicData.piPicData, btPicData, 0, tPicData.iDataLen);
                FileStream fFile = new FileStream(cFileName, FileMode.Create);
                if (null != fFile)
                {
                    fFile.Write(btPicData, 0, tPicData.iDataLen);
                    fFile.Close();
                }             
            }
            //人脸图片
            for (int i = 0; i < tItsPicStream.iFaceCount && i < 3; ++i)
            {
                if (null == tItsPicStream.tFaceData[i])
                {
                    continue;
                }
                PicData tPicData = (PicData)Marshal.PtrToStructure(tItsPicStream.tFaceData[i], typeof(PicData));
                string cFileName = ".\\PicStream\\ItsFace-" + tItsPicStream.strCameraIP + "-No" + (g_iCount) + "CP_" + i + ".jpg";
                byte[] btPicData = new byte[tPicData.iDataLen];
                Marshal.Copy(tPicData.piPicData, btPicData, 0, tPicData.iDataLen);
                FileStream fFile = new FileStream(cFileName, FileMode.Create);
                if (null != fFile)
                {
                    fFile.Write(btPicData, 0, tPicData.iDataLen);
                    fFile.Close();
                }
            }
            return 0;
        }

        private static void LogonDevice(int _iLogonType)
        {
            string strIP;
            string strUserName;
            string strPassword;
            string strProductID;

            Console.WriteLine("Please input user name: ");
            strUserName = Console.ReadLine();

            Console.WriteLine("Please input password: ");
            strPassword = Console.ReadLine();

            LogonPara tNormal;
            LogonActiveServer tActive;
            IntPtr pvPara = IntPtr.Zero;
            int iBufLen = 0;

            try
            {
                if (SDKTypes.SERVER_ACTIVE == _iLogonType)
                {
                    Console.WriteLine("Please input ProductID: ");
                    strProductID = Console.ReadLine();
                    tActive = new LogonActiveServer();
                    tActive.iSize = Marshal.SizeOf(tActive);
                    Array.Copy(Encoding.ASCII.GetBytes(strUserName), tActive.btUserName, strUserName.Length);
                    Array.Copy(Encoding.ASCII.GetBytes(strPassword), tActive.btUserPwd, strPassword.Length);
                    Array.Copy(Encoding.ASCII.GetBytes(strProductID), tActive.btProductID, strProductID.Length);
                    pvPara = Marshal.AllocHGlobal(Marshal.SizeOf(tActive));
                    Marshal.StructureToPtr(tActive, pvPara, true);
                    iBufLen = Marshal.SizeOf(tActive);

                    DsmOnline tOnline = new DsmOnline();
                    int length = Marshal.SizeOf(tOnline);
                    Array.Copy(Encoding.ASCII.GetBytes(strProductID), tOnline.btProductID, strProductID.Length);
                    IntPtr ptOnline = IntPtr.Zero;
                    try
                    {
                        ptOnline = Marshal.AllocHGlobal(length);
                        Marshal.StructureToPtr(tOnline, ptOnline, true);
                        NVSSDK.NetClient_GetDsmRegstierInfo(SDKConstMsg.DSM_CMD_GET_ONLINE_STATE, ptOnline, Marshal.SizeOf(tOnline));
                        int iOutTime = 0;
                        while (SDKTypes.DSM_STATE_ONLINE != tOnline.iOnline)
                        {
                            if (iOutTime >= 20)
                            {
                                Console.WriteLine("Device not register!\n");
                                break;
                            }
                            Thread.Sleep(1000);
                            NVSSDK.NetClient_GetDsmRegstierInfo(SDKConstMsg.DSM_CMD_GET_ONLINE_STATE, ptOnline, Marshal.SizeOf(tOnline));
                            iOutTime++;
                        }
                    }
                    catch (System.Exception ex)
                    {
                        Console.WriteLine(ex.Message);
                    }
                    finally
                    {
                        Marshal.FreeHGlobal(ptOnline);
                    }
                }
                else
                {
                    string strCharSet = "UTF-8";
                    Console.WriteLine("Please input server IP: ");
                    strIP = Console.ReadLine();
                    tNormal = new LogonPara();
                    tNormal.iSize = Marshal.SizeOf(tNormal);
                    tNormal.iNvsPort = 3000;
                    Array.Copy(Encoding.ASCII.GetBytes(strIP), tNormal.btNvsIP, strIP.Length);
                    Array.Copy(Encoding.ASCII.GetBytes(strUserName), tNormal.btUserName, strUserName.Length);
                    Array.Copy(Encoding.ASCII.GetBytes(strPassword), tNormal.btUserPwd, strPassword.Length);
                    Array.Copy(Encoding.ASCII.GetBytes(strCharSet), tNormal.btCharSet, strCharSet.Length);
                    iBufLen = Marshal.SizeOf(tNormal);
                    pvPara = Marshal.AllocHGlobal(Marshal.SizeOf(tNormal));
                    Marshal.StructureToPtr(tNormal, pvPara, true);
                }

                g_iLogonID = NVSSDK.NetClient_Logon_V4(_iLogonType, pvPara, iBufLen);
                if (g_iLogonID < 0)
                {
                    Console.WriteLine("[NetClient_Logon_V4] fail! " + g_iLogonID + "\n");
                }
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            finally
            {
                Marshal.FreeHGlobal(pvPara);
            }
        }

        private static void StartRecvPicture()
        {
            IntPtr ptNetPicPara = IntPtr.Zero;
            try
            {
                g_tNetPicPara.iStructLen = Marshal.SizeOf(g_tNetPicPara);
                g_tNetPicPara.iChannelNo = 0;
                g_tNetPicPara.cbkPicStreamNotify = MyNETPICSTREAM_NOTIFY;
                g_tNetPicPara.pvUser = IntPtr.Zero;
                ptNetPicPara = Marshal.AllocHGlobal(Marshal.SizeOf(g_tNetPicPara));
                Marshal.StructureToPtr(g_tNetPicPara, ptNetPicPara, true);
                int iRet = NVSSDK.NetClient_StartRecvNetPicStream(g_iLogonID, ptNetPicPara, Marshal.SizeOf(g_tNetPicPara), ref g_uiRecvID);
                if (0 != iRet)
                {
                    Console.WriteLine("[NetClient_StartRecvNetPicStream] fail!");
                }
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            finally
            {
                Marshal.FreeHGlobal(ptNetPicPara);
            }
        }

        private static void StopRecvPicture()
        {
            int iRet = NVSSDK.NetClient_StopRecvNetPicStream(g_uiRecvID);
            if (0 != iRet)
            {
                Console.WriteLine("[NetClient_StopRecvNetPicStream] fail!");
            }
            else
            {
                g_uiRecvID = CONST_INVALID_RECV_ID;
            }
        }

        private static void CreateStreamDirectory()
        {
            if (!Directory.Exists(g_strPicStreamDir))
            {
                Directory.CreateDirectory(g_strPicStreamDir);
            }
        }

        static void Main(string[] args)
        {

            int iLogonType = SDKTypes.SERVER_NORMAL;
            string strTemp;
            Console.WriteLine("Please input LogonType: 0----Normal  1----Active\n");
            strTemp = Console.ReadLine();
            iLogonType = Convert.ToInt32(strTemp);

            //初始化SDK
            if (SDKTypes.SERVER_ACTIVE == iLogonType)
            {
                Console.WriteLine("Please input listening port:");
                strTemp = Console.ReadLine();
                int iLlisteningPort = Convert.ToInt32(strTemp);
                NVSSDK.NetClient_Startup_V4(iLlisteningPort, 0, 0);
            }
            else
            {
                NVSSDK.NetClient_Startup_V4(0, 0, 0);
            }

            //设置回调函数
            MainNotify_V4 = MyMAIN_NOTIFY_V4;
            NVSSDK.NetClient_SetNotifyFunction_V4(MainNotify_V4, null, null, null, null);

            //登录设备
            LogonDevice(iLogonType);

            //创建图片流接收目录
            CreateStreamDirectory();

            Console.ReadLine();

            //停止接收图片流
            StopRecvPicture();

            //注销用户
            NVSSDK.NetClient_Logoff(g_iLogonID);

            //释放SDK资源
            NVSSDK.NetClient_Cleanup();

        }
    }
}
