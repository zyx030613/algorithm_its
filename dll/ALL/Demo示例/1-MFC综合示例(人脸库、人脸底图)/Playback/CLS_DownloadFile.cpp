#include "stdafx.h"
#include "CLS_DownloadFile.h"
CLS_DownloadFile::CLS_DownloadFile(int _iLogonID, unsigned long _ulConnID,CString _szFileName,CString _szOperationTime,CString _szOperate)
{
	m_ulConnID = _ulConnID;
	m_iLogonID = _iLogonID;
	m_szFileName = _szFileName;
	m_szOperationTime = _szOperationTime;
	m_szOperate = _szOperate;
	m_iBreakContine = 0;
	m_iReqMode = 1;
	m_iPosition = 0;
}

CLS_DownloadFile::~CLS_DownloadFile()
{
	StopDownload();
}

void CLS_DownloadFile::StopDownload()
{
	NetClient_NetFileStopDownloadFile(m_ulConnID);
}

int CLS_DownloadFile::GetLogonID()
{
	return m_iLogonID;
}

unsigned long CLS_DownloadFile::GetConnID()
{
	return m_ulConnID;
}

CString CLS_DownloadFile::GetFilename()
{
	return m_szFileName;
}

CString CLS_DownloadFile::GetOperationTime()
{
	return m_szOperationTime;
}

CString CLS_DownloadFile::GetOperate()
{
	return m_szOperate;
}

int CLS_DownloadFile::GetBreakContinue()
{
	return m_iBreakContine;
}

int CLS_DownloadFile::SetBreakContinue( int _iFlag )
{
	m_iBreakContine = _iFlag;
	return 0;
}

int CLS_DownloadFile::GetReqMode()
{
	return m_iReqMode;
}

int CLS_DownloadFile::SetReqMode(int _iMode)
{
	m_iReqMode = _iMode;
	return 0;
}

int CLS_DownloadFile::SetConnID( unsigned long _ulConnID )
{
	m_ulConnID = _ulConnID;
	return 0;
}

int CLS_DownloadFile::GetPosition()
{
	return m_iPosition;
}

int CLS_DownloadFile::SetPosition( int _iPos )
{
	m_iPosition = _iPos;
	return 0;
}