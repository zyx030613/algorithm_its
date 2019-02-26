#ifndef _VIDEO_VIEW_H
#define _VIDEO_VIEW_H

#include "afxwin.h"
#include "Common/EZoomManager.h"

class CLS_VideoView :
	public CStatic
{
public:
	static CLS_VideoView* CreateInstance(int _iID,CWnd* _pParent);
	~CLS_VideoView(void);
	DECLARE_MESSAGE_MAP()

public:
	int GetID(){return m_iID;}
	void SetID(int _iID){m_iID = _iID;}
	unsigned int GetConnID(){return m_uConnID;}
	void SetConnID(unsigned int _uConnID);
	void DrawRect(COLORREF _uColor,CDC* _pDC = NULL);
	bool SupportNew3D();
	void New3DLocate(RECT& _rcVideo);
	afx_msg void OnPaint();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	void ChannelTalkNotify(int _iLogonID, int _iChannelNo, int _iTalkStatus);
private:
	CLS_VideoView(void);	
	void On3DLocate();
	void OnEZoom();
	void OnVideoCoverArea();
	void OnMotionDetectArea();
	void OnShowBitrate();
	void OnShowMotionDetect();
	void OnDisconnect();
	void OnAutoFocus();
	void OnChannelTalk();
	void OnInputTalkData();
	bool StopTalk();
	int ClientToVideo(RECT& _rcScreen,OUT RECT& _rcVideo);
	int DrawVideoArea(RECT& _rcVideo);
	int _3DLocate(RECT& _rcVideo,BOOL _bDirection);
	int SetVideoCoverArea(RECT& _rcVideo);
	int GetMotionDetetionArea(RECT* _prcArea,int _iCount,RECT* _prcVideo = NULL);
	int SetMotionDetetionArea(RECT* _prcArea,int _iCount);
	int SetMotionDetetionArea(RECT& _rcVideo);
	int ShowMotionDetetionArea(RECT* _prcArea,int _iCount);
	static DWORD WINAPI ThreadInputChannelTalking(LPVOID pParam);
	afx_msg LRESULT OnChannelTalkEnd(WPARAM wParam, LPARAM lParam);
private:
	int m_iID;
	COLORREF m_uColor;
	unsigned int m_uConnID;
	unsigned int m_uShowCaps;
	int m_iDragType;
	RECT m_rcDrag;
	RECT m_rcVideo;
	int m_iVideoCoverIndex;
public:
	bool m_IsChannelTalk;
	bool m_IsInputTalkData;
};

#endif
