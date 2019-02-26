#ifndef _NSLOOK_INTERFACE_H_
#define _NSLOOK_INTERFACE_H_

#include "../Common/CommonFun.h"
#include "RegServerTypes.h"

TYPEDEF_FUNCTION(NSLook_Startup)();
TYPEDEF_FUNCTION(NSLook_Cleanup)();
TYPEDEF_FUNCTION(NSLook_LogonServer)(char *_cServerIP,int _iServerPort,bool _blRepeat);
TYPEDEF_FUNCTION(NSLook_LogoffServer)(int _iID);
TYPEDEF_FUNCTION_RET(LPCSTR,NSLook_GetServerVersion)(int _iID);
TYPEDEF_FUNCTION(NSLook_Query)(int _iID,REG_DNS *_regDNS,REG_NVS* _RegNVS,int _iType);
TYPEDEF_FUNCTION(NSLook_GetCount)(int _iID,const char *_cUserName,const char *_cPwd,int *_iCount,int _iType);
TYPEDEF_FUNCTION(NSLook_GetList)(int _iID,const char *_cUserName,const char *_cPwd,int _iPageIndex,
                             cbkGetDNSList _pGetDNS,cbkGetNVSList _pGetNVS,int _iType);
TYPEDEF_FUNCTION(NSLook_ConnectNVS)(int _iID,IN st_LogOnInfo *_stLogOn,OUT st_ProxyInfo *_stProxy);

DECLARE_FUNCTION(NSLook_Startup);
DECLARE_FUNCTION(NSLook_Cleanup);
DECLARE_FUNCTION(NSLook_LogonServer);
DECLARE_FUNCTION(NSLook_LogoffServer);
DECLARE_FUNCTION(NSLook_GetServerVersion);
DECLARE_FUNCTION(NSLook_Query);
DECLARE_FUNCTION(NSLook_GetCount);
DECLARE_FUNCTION(NSLook_GetList);
DECLARE_FUNCTION(NSLook_ConnectNVS);

class CLS_NsLook_Interface
{
public :
	static int LoadDLL(char* _szPath = "nslook.dll");
	static void FreeDLL();

private:
	static HINSTANCE s_hInstance;
};
//---------------------------------------------------------------------------
#endif
