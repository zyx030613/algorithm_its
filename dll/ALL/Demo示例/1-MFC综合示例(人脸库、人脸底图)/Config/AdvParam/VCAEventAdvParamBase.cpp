#include "StdAfx.h"
#include "NetClientDemo.h"
#include "VCAEventAdvParamBase.h"

CLS_VCAEventAdvParamBase::CLS_VCAEventAdvParamBase( UINT nIDTemplate, CWnd* pParentWnd )
:CLS_BasePage(nIDTemplate, pParentWnd)
{
	m_iLogonID = -1;
	m_iChannelNO = -1;
	m_iStreamNO = -1;

	m_iRuleID = -1;
	m_iSceneID = -1;
	m_pVcaParam = NULL;
}

CLS_VCAEventAdvParamBase::~CLS_VCAEventAdvParamBase(void)
{
}

void CLS_VCAEventAdvParamBase::SetRuleID( int _iRuleID )
{
	m_iRuleID = _iRuleID;
}

void CLS_VCAEventAdvParamBase::SetSceneID( int _iSceneID )
{
	m_iSceneID = _iSceneID;
}

int CLS_VCAEventAdvParamBase::RestartVCALib( int _iLogonID, int _iChannel /*= -1*/ )
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

