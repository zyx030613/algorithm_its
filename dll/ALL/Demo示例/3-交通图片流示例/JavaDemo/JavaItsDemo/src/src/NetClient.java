package src;

import java.awt.Component;

import src.NVSSDK.ALARM_NOTIFY;
import src.NVSSDK.CLIENTINFO;
import src.NVSSDK.ENCODERINFO;
import src.NVSSDK.MAIN_NOTIFY;
import src.NVSSDK.NetPicPara;
import src.NVSSDK.PARACHANGE_NOTIFY;
import src.NVSSDK.RECT;
import src.NVSSDK.RECVDATA_NOTIFY;
import src.NVSSDK.SDK_VERSION;

import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.ptr.IntByReference;

public class NetClient {

	private static NVSSDK nvssdk = (NVSSDK) Native.loadLibrary("NVSSDK",
			NVSSDK.class);
	public static int GetVersion(SDK_VERSION _ver) {
		return nvssdk.NetClient_GetVersion(_ver);
	}

	public static int SetNotifyFunction(MAIN_NOTIFY _cbkMainNotify,
			ALARM_NOTIFY _cbkAlarmNotify,PARACHANGE_NOTIFY _cbkParaChangeNotify) {
		return nvssdk.NetClient_SetNotifyFunction_V4(_cbkMainNotify, _cbkAlarmNotify, _cbkParaChangeNotify, null, null);
	}

	public static int SetPort(int _iServerPort, int _iClientPort) {
		return nvssdk
				.NetClient_SetPort(_iServerPort, _iClientPort);
	}

	public static int Startup() {
		return nvssdk.NetClient_Startup_V4(0, 0, 0);
	}

	public static int Cleanup() {
		return nvssdk.NetClient_Cleanup();
	}

	public static int Logon(String _cProxy, String _cIP, String _cUserName,
			String _cPassword, String _pcProID, int _iPort) {
		return nvssdk.NetClient_Logon(_cProxy, _cIP, _cUserName,
				_cPassword, _pcProID, _iPort);
	}

	public static int Logoff(int _iLogonID) {
		return nvssdk.NetClient_Logoff(_iLogonID);
	}

	public static int StartRecv(IntByReference _ulConID, CLIENTINFO _cltInfo,
			RECVDATA_NOTIFY _cbkDataNotify) {
		return nvssdk.NetClient_StartRecvEx(_ulConID, _cltInfo,
				_cbkDataNotify, Pointer.NULL);
	}

	public static int StopRecv(int _ulConID) {
		return nvssdk.NetClient_StopRecv(_ulConID);
	}

	public static int StartCaptureData(int _ulConID) {
		return nvssdk.NetClient_StartCaptureData(_ulConID);
	}

	public static int StartPlay(int _ulConID, Component _hWnd, int _iDecflag) {
		int hWnd = (int) Native.getComponentID(_hWnd);
		RECT rcShow = new RECT();
		return nvssdk.NetClient_StartPlay(_ulConID, hWnd, rcShow,
				_iDecflag);
	}

	public static int StopPlay(int _ulConID) {
		return nvssdk.NetClient_StopPlay(_ulConID);
	}

	public static int StartCaptureFile(int _ulConID, String _cFileName,
			int _iRecFileType) {
		return nvssdk.NetClient_StartCaptureFile(_ulConID,
				_cFileName, _iRecFileType);
	}

	public static int StopCaptureFile(int _ulConID) {
		return nvssdk.NetClient_StopCaptureFile(_ulConID);
	}
	
	public static int StartRecvNetPicStream(int _iLogonID, NetPicPara _ptPara, int _iBufLen, IntByReference _puiRecvID) {
		return nvssdk.NetClient_StartRecvNetPicStream(_iLogonID, _ptPara, _iBufLen,  _puiRecvID);
	}
	
	public static int GetLogonStatus(int _iLogonID) {
		return nvssdk.NetClient_GetLogonStatus(_iLogonID);
	}
	
	public static int GetDevInfo(int _iLogonID ,ENCODERINFO _pEncoderInfo) {
		return nvssdk.NetClient_GetDevInfo(_iLogonID, _pEncoderInfo);
	}
	
}
