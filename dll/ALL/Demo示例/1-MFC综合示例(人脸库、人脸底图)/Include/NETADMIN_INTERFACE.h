#ifndef _NETADMIN_INTERFACE_H_
#define _NETADMIN_INTERFACE_H_

#include "../Common/CommonFun.h"
#include "NetAdminTypes.h"

TYPEDEF_FUNCTION(NetAdmin_Startup)();
TYPEDEF_FUNCTION(NetAdmin_Closeup)();
TYPEDEF_FUNCTION(NetAdmin_SetNotify)(FIND_NOTIFY _Notify);
TYPEDEF_FUNCTION(NetAdmin_SetNetInterface)(int _iIndex);
TYPEDEF_FUNCTION_RET(char*,NetAdmin_GetNetInterface)(int _iIndex);
TYPEDEF_FUNCTION(NetAdmin_SeekServers)();
TYPEDEF_FUNCTION(NetAdmin_ChangeIP)(char* _strMAC, char* _newIP, char* _cMask, char* _Gateway, char* _cDNS);
TYPEDEF_FUNCTION(NetAdmin_ChangeMAC)(char* _strMac, char* _strNew);
TYPEDEF_FUNCTION(NetAdmin_ChangePort)(char* _strMAC, int _serverPort, int _clientPort);
TYPEDEF_FUNCTION(NetAdmin_RebootServer)(char* _strMac);

DECLARE_FUNCTION(NetAdmin_Startup);
DECLARE_FUNCTION(NetAdmin_Closeup);
DECLARE_FUNCTION(NetAdmin_SetNotify);
DECLARE_FUNCTION(NetAdmin_SetNetInterface);
DECLARE_FUNCTION(NetAdmin_GetNetInterface);
DECLARE_FUNCTION(NetAdmin_SeekServers);
DECLARE_FUNCTION(NetAdmin_ChangeIP);
DECLARE_FUNCTION(NetAdmin_RebootServer);
DECLARE_FUNCTION(NetAdmin_ChangeMAC);
DECLARE_FUNCTION(NetAdmin_ChangePort);

class CLS_NetAdmin_Interface
{
public :
    static int LoadDLL(char* _szPath = "NetAdmin.dll");
    static void FreeDLL();

private:
	static HINSTANCE s_hInstance;
};

#endif
