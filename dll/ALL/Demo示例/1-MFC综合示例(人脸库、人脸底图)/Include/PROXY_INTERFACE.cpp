
#include <stdafx.h>
#include "PROXY_INTERFACE.h"
using namespace PROXY_INTERFACE;
namespace PROXY_INTERFACE
{
	static HINSTANCE hPROXYSDK = NULL;
	IMPLEMENT_FUNCTION(NetClient_ProxyStart);
	int LoadProxySDK(const char* _pszPath)
	{
		if (hPROXYSDK)
			return	DLL_RELOAD;
		else
		{
			hPROXYSDK=::LoadLibrary(_pszPath);
			if (!hPROXYSDK)
				return	DLL_NOT_FOUND;
		}
		EXPORT_FUNCTION(hPROXYSDK, NetClient_ProxyStart);
		return DLL_LOAD_SUCCESS;
	}
	bool ReleaseProxySDK()
	{
		if (hPROXYSDK)
		{
			::FreeLibrary(hPROXYSDK);
			hPROXYSDK = NULL;
		}

		return true;
	}
}
