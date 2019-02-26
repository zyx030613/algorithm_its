#include "stdafx.h"
#include "MP4_INTERFACE.h"
using namespace MP4_INTERFACE;

namespace MP4_INTERFACE
{
	HINSTANCE hMP4 =NULL;


	MP4_ConvertSdvToMp4 TMP4_ConvertSdvToMp4 = NULL;
	

HRESULT	LoadMp4Dll()
	{
		if (NULL != hMP4)
		{
			return	S_FALSE;
		}
		else
		{
			hMP4=::LoadLibrary("libmp4adpter.dll");
			if (NULL == hMP4)
			{
				return	E_FAIL;
			}
		}
	
		TMP4_ConvertSdvToMp4 = (MP4_ConvertSdvToMp4)GetProcAddress(hMP4, "MP4_ConvertSdvToMp4");
		
		return S_OK;
	}
}