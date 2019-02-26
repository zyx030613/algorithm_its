#pragma once
#include "afxwin.h"

typedef struct tagVCAWindowDetectionPosInfo
{
	int					iDoubleCircleNum;		//0-63
	WindowDetectionPos  tWindowDetectionPos[MAX_WINDOW_DOUBLE_CIRCLE_NUM];
}VCAWindowDetectionPosInfo,*pVCAWindowDetectionPosInfo;

class CLS_VideoViewForDrawWindowDetection : public CDialog
{
	DECLARE_DYNAMIC(CLS_VideoViewForDrawWindowDetection)

public:
	CLS_VideoViewForDrawWindowDetection(CWnd* pParent = NULL); 
	virtual ~CLS_VideoViewForDrawWindowDetection();

	enum { IDD = IDD_DLG_VIDEOVIEW_DRAWLINES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   

	DECLARE_MESSAGE_MAP()

private:
	CStatic m_StcVideoShow;

	UINT	m_uiConnID;	
	int		m_iLogonID;
	int		m_iChannelNO;
	int		m_iStreamNO;

	BOOL	m_blStarDrawNotify;						//是否开启了画图回调
	VCAWindowDetectionPosInfo m_tWinPosInfo;		//划线信息

	bool	m_blDrawFinish;
	bool	m_blDrawing;
	int		m_iMaxAreamNum;

	bool	m_blDrawOutFrame;
	bool	m_blDrawInnerFrame;

public:
	void	StartRecv();
	void	StartPlay();
	void	StopPlay();
	void    UI_UpdateDialog();
	BOOL	IsInsideVideoStatic(POINT _pt);			//返回值用来判断是否画出视频窗口范围
	void	InitVideoParam(int _iLogonID, int _iChnnelNO, int _iStreamNO);
	int		SetDrawPolygonInfo(void* IN _pvInBuff, int IN _iBufSize);
	int		GetDrawPolygonInfo(void* OUT _pvInBuff, int IN _iBufSize);
	
	int		PaintLinesOnDc(HDC _hdc);

	bool	IsPointInsidePolygon(int _iPolygonPointNum, vca_TPoint* _ptPolygonPoint, vca_TPoint _tTestPoint);

	int		SwitchTenThousandX(int _iX);					//转换为万分比横坐标
	int		SwitchTenThousandY(int _iY);					//转换为万分比纵坐标
	int		RestoreTenThousandX(int _iX);					//万分比横坐标还原
	int		RestoreTenThousandY(int _iY);					//万分比纵坐标还原

private:
	HPEN			m_penRule;						//画笔
	int				m_iDrawColor;					//画笔颜色
	int		StartDrawNotify();						//设置画图回调
	int		DrawPolygonOnDC(HDC _hdc, int _iPointNum, vca_TPoint* _ptPoint);				//画多边形
	int		DrawLineOnDC(HDC _hdc, int _iXStart, int _iYStart, int _iXEnd, int _iYEnd);		//画直线

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

public:
	void	OnMainNotify( int _iLogonID,int _wParam, void* _lParam, void*_iUserData );
	void	OnLanguageChanged(int _iLanguage);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonDrawok();
	afx_msg void OnBnClickedButtonClearRegion();
	afx_msg void OnBnClickedButtonStartDraw();
	
};

