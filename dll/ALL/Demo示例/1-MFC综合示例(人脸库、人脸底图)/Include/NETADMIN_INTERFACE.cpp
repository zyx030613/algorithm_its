#include "stdafx.h"
#include "NETADMIN_INTERFACE.h"

HINSTANCE CLS_NetAdmin_Interface::s_hInstance  = NULL;

IMPLEMENT_FUNCTION(NetAdmin_Startup);
IMPLEMENT_FUNCTION(NetAdmin_Closeup);
IMPLEMENT_FUNCTION(NetAdmin_SetNotify);
IMPLEMENT_FUNCTION(NetAdmin_SetNetInterface);
IMPLEMENT_FUNCTION(NetAdmin_GetNetInterface);
IMPLEMENT_FUNCTION(NetAdmin_SeekServers);
IMPLEMENT_FUNCTION(NetAdmin_ChangeIP);
IMPLEMENT_FUNCTION(NetAdmin_RebootServer);
IMPLEMENT_FUNCTION(NetAdmin_ChangeMAC);
IMPLEMENT_FUNCTION(NetAdmin_ChangePort);

int CLS_NetAdmin_Interface::LoadDLL(char* _szPath)
{
	if (s_hInstance)
		return	DLL_RELOAD;
	else
	{
		s_hInstance = LoadLibrary(_szPath);
		if(!s_hInstance) 
			return DLL_NOT_FOUND;
	}
    
	EXPORT_FUNCTION(s_hInstance,NetAdmin_Startup);
	EXPORT_FUNCTION(s_hInstance,NetAdmin_Closeup);
	EXPORT_FUNCTION(s_hInstance,NetAdmin_SetNotify);
	EXPORT_FUNCTION(s_hInstance,NetAdmin_SetNetInterface);
	EXPORT_FUNCTION(s_hInstance,NetAdmin_GetNetInterface);
	EXPORT_FUNCTION(s_hInstance,NetAdmin_SeekServers);
	EXPORT_FUNCTION(s_hInstance,NetAdmin_ChangeIP);
	EXPORT_FUNCTION(s_hInstance,NetAdmin_RebootServer);
	EXPORT_FUNCTION(s_hInstance,NetAdmin_ChangeMAC);
	EXPORT_FUNCTION(s_hInstance,NetAdmin_ChangePort);

    return DLL_LOAD_SUCCESS;
}

void CLS_NetAdmin_Interface::FreeDLL()
{
    if(s_hInstance)
    {
        ::FreeLibrary(s_hInstance);
        s_hInstance = NULL;
    }
}
