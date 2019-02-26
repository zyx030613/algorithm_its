#pragma once
#include "../Common/CommonFun.h"
#include "../Include/NVSSDK_INTERFACE.h"
using namespace NVSSDK_INTERFACE;
class CLS_DownloadFile
{
public:
	CLS_DownloadFile(int _iLogonID, unsigned long _ulConnID, CString _szFileName,CString _szOperationTime = _T(""),CString _szOperate = _T(""));
	~CLS_DownloadFile();

private:
	CString m_szFileName;
	int m_iLogonID;
	unsigned long m_ulConnID;
	CString m_szOperationTime;
	CString m_szOperate;
	int m_iBreakContine;
	int m_iReqMode;
	int m_iPosition;

public:
	void StopDownload();
	int GetLogonID();
	unsigned long GetConnID();
	int SetConnID(unsigned long _ulConnID);
	CString GetFilename();
	CString GetOperationTime();
	CString GetOperate();
	int GetBreakContinue();
	int SetBreakContinue(int _iFlag);
	int GetReqMode();
	int SetReqMode(int _iMode);
	int GetPosition();
	int SetPosition(int _iPos);
};