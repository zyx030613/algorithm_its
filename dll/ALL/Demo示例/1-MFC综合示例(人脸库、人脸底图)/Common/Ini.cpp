#include <stdafx.h>
#include <Windows.h>
#include "Ini.h"

CIniFile::CIniFile()
{

}

CIniFile::CIniFile( const char* _cPath )
{
    if(_cPath != NULL)
	{
		strcpy_s(m_cFilePath, sizeof(m_cFilePath), _cPath);
	}
	else
	{
		memset(m_cFilePath, 0, sizeof(m_cFilePath));
	}
}

CIniFile::~CIniFile()
{

}

int CIniFile::ReadInteger( char* _szSection, char* _szKey, int _iDefaultValue )
{
	if (strcmp(m_cFilePath, "") != 0)
	{
		return GetPrivateProfileInt(_szSection, _szKey, _iDefaultValue, m_cFilePath);
	}	
	return _iDefaultValue;
}

int CIniFile::WriteInteger( char* _szSection, char* _szKey, int _iValue )
{
	if (strcmp(m_cFilePath, "") != 0)
	{
		char cNum[128] = {0};
		sprintf_s(cNum, sizeof(cNum), "%d", _iValue);
		return WritePrivateProfileString(_szSection, _szKey, cNum, m_cFilePath);
	}
	return 0;	
}

CString CIniFile::ReadString( char* _szSection, char* _szKey, char* _szDefaultValue)
{

	if (strcmp(m_cFilePath, "") != 0)
	{
		char szResultString[512] = {0};
		CString szResult;
		GetPrivateProfileString(_szSection, _szKey, _szDefaultValue, szResultString, sizeof(szResultString), m_cFilePath);
		szResult = szResultString;
		return szResult;
	}
	return 0;
}

int CIniFile::WriteString( char* _szSection, char* _szKey, char* _szValue )
{
	if (strcmp(m_cFilePath, "") != 0)
	{
		return WritePrivateProfileString(_szSection, _szKey, _szValue, m_cFilePath);
	}
	return 0;
}

void CIniFile::ResetFile()
{	
	if (strlen(m_cFilePath) > 0)
	{
		FILE *file = fopen(m_cFilePath, "wb");
		if (file)
		{
			fclose(file);
		}
	}	
}
