/***************************************************************
Module Name£ºini
Description£ºlike TIniFile in c++builder
Version    £ºv1.0
Time       £º2012/10/31 21:02:59
Author     £ºgujinfei
Other      £ºsimple 
***************************************************************/
#ifndef _INIH_
#define _INIH_
#include <atlstr.h>

class CIniFile
{
public:
	CIniFile();
	CIniFile(const char* _cPath);
	~CIniFile();
	void SetFileName(const char* _cFile){strcpy_s(m_cFilePath, sizeof(m_cFilePath), _cFile);}
	int ReadInteger(char* _szSection, char* _szKey, int _iDefaultValue);
	int WriteInteger(char* _szSection, char* _szKey, int _iValue);
	CString ReadString(char* _szSection, char* _szKey, char* _szDefaultValue);
	int WriteString(char* _szSection, char* _szKey, char* _szValue);
	void ResetFile();
private:
    char m_cFilePath[256];
};
#endif