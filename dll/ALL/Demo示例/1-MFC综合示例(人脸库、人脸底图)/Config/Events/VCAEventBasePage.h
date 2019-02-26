#pragma once
#include "afxwin.h"

#include "../../Include/NVSSDK_INTERFACE.h"
#include "../../BasePage.h"
using namespace NVSSDK_INTERFACE;
#include "VideoViewForDraw.h"

typedef struct tagWldPoint
{
	int iX;
	int iY;
	int iValue;
} WldPoint, *pWldPoint;

class CLS_VCAEventBasePage :
	public CLS_BasePage
{
public:
	CLS_VCAEventBasePage(UINT nIDTemplate, CWnd* pParentWnd);
	~CLS_VCAEventBasePage(void);

	CLS_VideoViewForDraw* m_pDlgVideoView;
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
	virtual void OnMainNotify(int _iLogonID,int _wParam, void* _iLParam, void* _iUser);
	virtual void OnLanguageChanged(){};
	virtual void GetPolyFromString(CString _strPoints, int _iPointNum, vca_TPolygon& _stPoly);
	virtual void GetPolyFromStringEx( CString _strPoints, int _iPointNum, vca_TPolygonEx& _stPoly );
	virtual void GetLineFromString(CString _strPoints, vca_TLine& _stLine);
	virtual void GetPointsFromString(CString _strPoints, int _iPointNum, POINT* _poPoint);
	virtual void GetWldPointsFromString(CString _strPoints, int _iPointNum, WldPoint* _ptWldPoint);
	virtual void OnCancel(){};
	virtual void OnOK(){};

	int		RestartVCALib(int _iLogonID, int _iChannel = -1);
	void	SetRuleID(int _iRuleID);
	void	SetSceneID(int _iSceneID);
	void	SetVCAParam(vca_TVCAParam* _pVcaParam){m_pVcaParam = _pVcaParam;}
	bool CheckPublicPara();
};
