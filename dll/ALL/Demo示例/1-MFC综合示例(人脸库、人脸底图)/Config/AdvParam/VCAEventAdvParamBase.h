#pragma once
#include "afxwin.h"

#include "../../Include/NVSSDK_INTERFACE.h"
#include "../../BasePage.h"
using namespace NVSSDK_INTERFACE;

class CLS_VCAEventAdvParamBase :
	public CLS_BasePage
{
public:
	CLS_VCAEventAdvParamBase(UINT nIDTemplate, CWnd* pParentWnd);
	~CLS_VCAEventAdvParamBase(void);

	int		m_iLogonID;
	int		m_iChannelNO;
	int		m_iStreamNO;

	int		m_iRuleID;
	int		m_iSceneID;
	vca_TVCAParam *m_pVcaParam;

public:
	virtual void Init(int _iLogonID,int _iChannelNo,int _iStreamNo)
	{
		m_iLogonID = _iLogonID;
		m_iChannelNO = _iChannelNo;
		m_iStreamNO = _iStreamNo;
	}

	virtual void OnLanguageChanged(){};
	virtual void OnCancel(){};
	virtual void OnOK(){};

	int		RestartVCALib(int _iLogonID, int _iChannel = -1);
	void	SetRuleID(int _iRuleID);
	void	SetSceneID(int _iSceneID);
	void	SetVCAParam(vca_TVCAParam* _pVcaParam){m_pVcaParam = _pVcaParam;}


};
