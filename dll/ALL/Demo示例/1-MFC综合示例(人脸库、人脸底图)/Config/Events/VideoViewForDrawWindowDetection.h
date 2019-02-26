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

	BOOL	m_blStarDrawNotify;						//�Ƿ����˻�ͼ�ص�
	VCAWindowDetectionPosInfo m_tWinPosInfo;		//������Ϣ

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
	BOOL	IsInsideVideoStatic(POINT _pt);			//����ֵ�����ж��Ƿ񻭳���Ƶ���ڷ�Χ
	void	InitVideoParam(int _iLogonID, int _iChnnelNO, int _iStreamNO);
	int		SetDrawPolygonInfo(void* IN _pvInBuff, int IN _iBufSize);
	int		GetDrawPolygonInfo(void* OUT _pvInBuff, int IN _iBufSize);
	
	int		PaintLinesOnDc(HDC _hdc);

	bool	IsPointInsidePolygon(int _iPolygonPointNum, vca_TPoint* _ptPolygonPoint, vca_TPoint _tTestPoint);

	int		SwitchTenThousandX(int _iX);					//ת��Ϊ��ֱȺ�����
	int		SwitchTenThousandY(int _iY);					//ת��Ϊ��ֱ�������
	int		RestoreTenThousandX(int _iX);					//��ֱȺ����껹ԭ
	int		RestoreTenThousandY(int _iY);					//��ֱ������껹ԭ

private:
	HPEN			m_penRule;						//����
	int				m_iDrawColor;					//������ɫ
	int		StartDrawNotify();						//���û�ͼ�ص�
	int		DrawPolygonOnDC(HDC _hdc, int _iPointNum, vca_TPoint* _ptPoint);				//�������
	int		DrawLineOnDC(HDC _hdc, int _iXStart, int _iYStart, int _iXEnd, int _iYEnd);		//��ֱ��

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

