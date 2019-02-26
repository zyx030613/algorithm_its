#pragma once
#include "../Common/CommonFun.h"

namespace PROXY_INTERFACE
{
	int 	LoadProxySDK(const char* _pszPath = "ProxySdk.dll");
	bool    ReleaseProxySDK();

	TYPEDEF_FUNCTION(NetClient_ProxyStart)(int _iProxyPort, int _iType);
	DECLARE_FUNCTION(NetClient_ProxyStart);
}