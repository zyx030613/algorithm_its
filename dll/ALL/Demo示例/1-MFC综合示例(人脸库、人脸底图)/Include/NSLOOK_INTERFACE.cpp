#include "stdafx.h"
#include "NSLOOK_INTERFACE.h"

HINSTANCE CLS_NsLook_Interface::s_hInstance  = NULL;

IMPLEMENT_FUNCTION(NSLook_Startup);
IMPLEMENT_FUNCTION(NSLook_Cleanup);
IMPLEMENT_FUNCTION(NSLook_LogonServer);
IMPLEMENT_FUNCTION(NSLook_LogoffServer);
IMPLEMENT_FUNCTION(NSLook_GetServerVersion);
IMPLEMENT_FUNCTION(NSLook_Query);
IMPLEMENT_FUNCTION(NSLook_GetCount);
IMPLEMENT_FUNCTION(NSLook_GetList);
IMPLEMENT_FUNCTION(NSLook_ConnectNVS);

int CLS_NsLook_Interface::LoadDLL(char* _szPath)
{
	if (NULL != s_hInstance)
	{
		return	DLL_LOAD_SUCCESS;
	}
	else
	{
		s_hInstance = LoadLibrary(_szPath);
		if(!s_hInstance) DLL_NOT_FOUND;
	}

	EXPORT_FUNCTION(s_hInstance,NSLook_Startup);
	EXPORT_FUNCTION(s_hInstance,NSLook_Cleanup);
	EXPORT_FUNCTION(s_hInstance,NSLook_LogonServer);
	EXPORT_FUNCTION(s_hInstance,NSLook_LogoffServer);	
	EXPORT_FUNCTION(s_hInstance,NSLook_GetServerVersion);
	EXPORT_FUNCTION(s_hInstance,NSLook_Query);
	EXPORT_FUNCTION(s_hInstance,NSLook_GetCount);
	EXPORT_FUNCTION(s_hInstance,NSLook_GetList);
	EXPORT_FUNCTION(s_hInstance,NSLook_ConnectNVS);

	return DLL_LOAD_SUCCESS;
}

void CLS_NsLook_Interface::FreeDLL()
{
	if(s_hInstance)
	{
		::FreeLibrary(s_hInstance);
		s_hInstance = NULL;
	}
}
