#include "StdAfx.h"
#include "NetClientDemo.h"
#include "VCAEventBasePage.h"

CLS_VCAEventBasePage::CLS_VCAEventBasePage( UINT nIDTemplate, CWnd* pParentWnd )
:CLS_BasePage(nIDTemplate, pParentWnd)
{
	m_iLogonID = -1;
	m_iChannelNO = -1;
	m_iStreamNO = -1;

	m_iRuleID = -1;
	m_iSceneID = -1;
	m_pVcaParam = NULL;

	m_pDlgVideoView = NULL;
}

CLS_VCAEventBasePage::~CLS_VCAEventBasePage(void)
{
	if (m_pDlgVideoView)
	{
		m_pDlgVideoView->DestroyWindow();
		delete m_pDlgVideoView;
		m_pDlgVideoView = NULL;
	}
}

void CLS_VCAEventBasePage::OnMainNotify(int _iLogonID,int _wParam, void* _iLParam, void* _iUser)
{
	if (m_pDlgVideoView)
	{
		m_pDlgVideoView->OnMainNotify(_iLogonID, _wParam, _iLParam, _iUser);
	}
}

void CLS_VCAEventBasePage::SetRuleID( int _iRuleID )
{
	m_iRuleID = _iRuleID;
}

void CLS_VCAEventBasePage::SetSceneID( int _iSceneID )
{
	m_iSceneID = _iSceneID;
}

void CLS_VCAEventBasePage::GetPolyFromString( CString _strPoints, int _iPointNum, vca_TPolygon& _stPoly )
{
	int iLength = _strPoints.GetLength()+1;
	char* pcData = new char [iLength];
	memset(pcData, 0, iLength);
	memcpy(pcData, _strPoints.GetBuffer(), iLength-1);
	char* p1 = pcData;
	char* p2 = NULL;
	int iPointIndex = 0;
	for (int i = 0; i < iLength; ++i)
	{
		p2 = strstr(p1, ")");
		if (p2 == NULL)
			break;

		char cCell[200] = {0};
		int iX = 0, iY = 0;
		memcpy(cCell, p1, p2-p1+1);
		sscanf_s(cCell, "(%d,%d)", &iX, &iY);
		_stPoly.stPoints[iPointIndex].iX = iX;
		_stPoly.stPoints[iPointIndex].iY = iY;
		if (++iPointIndex == VCA_MAX_POLYGON_POINT_NUM)
			break;

		if ((p1 = p2+1) >= pcData+iLength)
			break;
	}

	_stPoly.iPointNum =  iPointIndex;
	if (iPointIndex != _iPointNum && _iPointNum != 0)
	{
		_stPoly.iPointNum = _iPointNum;
	}

	delete [] pcData;
	pcData = NULL;
}

void CLS_VCAEventBasePage::GetPolyFromStringEx( CString _strPoints, int _iPointNum, vca_TPolygonEx& _stPoly )
{
	int iLength = _strPoints.GetLength()+1;
	char* pcData = new char [iLength];
	memset(pcData, 0, iLength);
	memcpy(pcData, _strPoints.GetBuffer(), iLength-1);
	char* p1 = pcData;
	char* p2 = NULL;
	int iPointIndex = 0;
	for (int i = 0; i < iLength; ++i)
	{
		p2 = strstr(p1, ")");
		if (p2 == NULL)
			break;

		char cCell[200] = {0};
		int iX = 0, iY = 0;
		memcpy(cCell, p1, p2-p1+1);
		sscanf_s(cCell, "(%d,%d)", &iX, &iY);
		_stPoly.stPoints[iPointIndex].iX = iX;
		_stPoly.stPoints[iPointIndex].iY = iY;
		if (++iPointIndex == VCA_MAX_POLYGON_POINT_NUMEX)
			break;

		if ((p1 = p2+1) >= pcData+iLength)
			break;
	}

	_stPoly.iPointNum =  iPointIndex;
	if (iPointIndex != _iPointNum && _iPointNum != 0)
	{
		_stPoly.iPointNum = _iPointNum;
	}

	delete [] pcData;
	pcData = NULL;
}

void CLS_VCAEventBasePage::GetLineFromString( CString _strPoints, vca_TLine& _stLine )
{
	int iLength = _strPoints.GetLength()+1;
	char* pcData = new char [iLength];
	memset(pcData, 0, iLength);
	memcpy(pcData, _strPoints.GetBuffer(), iLength-1);
	char* p1 = pcData;
	char* p2 = NULL;

	p2 = strstr(p1, ")");
	if (p2 == NULL)
		return;

	char cCell[200] = {0};
	int iX = 0, iY = 0;
	memcpy(cCell, p1, p2-p1+1);
	sscanf_s(cCell, "(%d,%d)", &iX, &iY);
	_stLine.stStart.iX = iX;
	_stLine.stStart.iY = iY;

	//	取第二个点
	if ((p1 = p2+1) >= pcData+iLength)
		return;

	p2 = strstr(p1, ")");
	if (p2 == NULL)
		return;

	memcpy(cCell, p1, p2-p1+1);
	sscanf_s(cCell, "(%d,%d)", &iX, &iY);
	_stLine.stEnd.iX = iX;
	_stLine.stEnd.iY = iY;

	delete [] pcData;
	pcData = NULL;
}

void CLS_VCAEventBasePage::GetPointsFromString(CString _strPoints, int _iPointNum, POINT* _poPoint)
{
	int iLength = _strPoints.GetLength()+1;
	char* pcData = new char [iLength];
	memset(pcData, 0, iLength);
	memcpy(pcData, _strPoints.GetBuffer(), iLength-1);
	char* p1 = pcData;
	char* p2 = NULL;
	int iPointIndex = 0;
	for (int i = 0; i < iLength; ++i)
	{
		p2 = strstr(p1, ")");
		if (p2 == NULL)
			break;

		char cCell[200] = {0};
		int iX = 0, iY = 0;
		memcpy(cCell, p1, p2-p1+1);
		sscanf_s(cCell, "(%d,%d)", &iX, &iY);
		_poPoint[iPointIndex].x = iX;
		_poPoint[iPointIndex].y = iY;
		if (++iPointIndex == _iPointNum)
			break;

		if ((p1 = p2+1) >= pcData+iLength)
			break;
	}
	delete [] pcData;
	pcData = NULL;
}

void CLS_VCAEventBasePage::GetWldPointsFromString(CString _strPoints, int _iPointNum, WldPoint* _ptWldPoint)
{
	int iLength = _strPoints.GetLength()+1;
	char* pcData = new char [iLength];
	memset(pcData, 0, iLength);
	memcpy(pcData, _strPoints.GetBuffer(), iLength-1);
	char* p1 = pcData;
	char* p2 = NULL;
	int iPointIndex = 0;
	for (int i = 0; i < iLength; ++i)
	{
		p2 = strstr(p1, ")");
		if (p2 == NULL)
			break;

		char cCell[200] = {0};
		int iX = 0, iY = 0, iValue = 0;
		memcpy(cCell, p1, p2-p1+1);
		sscanf_s(cCell, "(%d,%d,%d)", &iX, &iY, &iValue);
		_ptWldPoint[iPointIndex].iX = iX;
		_ptWldPoint[iPointIndex].iY = iY;
		_ptWldPoint[iPointIndex].iValue = iValue;
		if (++iPointIndex == _iPointNum)
			break;

		if ((p1 = p2+1) >= pcData+iLength)
			break;
	}
	delete [] pcData;
	pcData = NULL;
}

int CLS_VCAEventBasePage::RestartVCALib( int _iLogonID, int _iChannel /*= -1*/ )
{
	int iRet = -1;
	if (_iChannel == -1)
	{
		iRet = NetClient_VCARestart(_iLogonID);
		if (iRet < 0)
			AddLog(LOG_TYPE_FAIL, "", "VCARestart failed, ret(%d), err(%d)", iRet, GetLastError());

		return iRet;
	}

	iRet = NetClient_VCARestartEx(_iLogonID, _iChannel);
	if (iRet < 0)
		AddLog(LOG_TYPE_FAIL, "", "VCARestartEx failed, ret(%d), err(%d)", iRet, GetLastError());

	return iRet;
}

bool CLS_VCAEventBasePage::CheckPublicPara()
{
	bool blRet = false;
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "CheckPublicPara fail! m_iLogonID(%d)", m_iLogonID);
		goto END;
	}

	if (m_iChannelNO < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "CheckPublicPara fail! m_iChannelNO(%d)", m_iChannelNO);
		goto END;
	}

	if (m_iSceneID < 0 || m_iSceneID >= MAX_SCENE_NUM)
	{
		AddLog(LOG_TYPE_FAIL, "", "CheckPublicPara fail! m_iSceneID(%d)", m_iSceneID);
		goto END;
	}

	blRet = true;

END:
	return blRet;
}

