#include "StdAfx.h"
#include "VideoView.h"
#include "Resource.h"
#include "Preview/PreviewWindow.h"
#include <commctrl.h>
#include <share.h>
#include <bitset>

using namespace std;

#define MULTIPLY_SCREEN 0
#define SINGLE_SCREEN 1
#define FULL_SCREEN 2
/*******************************/
#define DRAG_TYPE_NONE			0
#define DRAG_TYPE_3D_LOCATE		1
#define	DRAG_TYPE_EZOOM			2
#define DRAG_TYPE_VIDEO_COVER		3
#define DRAG_TYPE_MOTION_DETECT		4

#define SHOW_CAP_NONE					0x0
#define SHOW_CAP_BITRATE				0x1
#define SHOW_CAP_MOTION_DETECT			0x2
#define SHOW_CAP_ALL					0xFFFFFFFF

#define WM_INPUT_CHANNELTALKING_END WM_USER+5000           //InputChannelTalk End Okay

//整个移动侦测区域分为18*22的矩阵
#define DETECT_ROW_NUM 18
#define DETECT_COLUMN_NUM 22

static HWND s_hViewWnd;

#define TENTHOUSAND_RATE 10000

// 基本参数
//bit0除雾：0-不支持，1-支持除雾
//bit1 新3D定位协议：0-不支持，1-支持
//bit2 是否支持罗盘：0-不支持，1-支持
enum ABILITY_TYPE_BASSPARA
{
	ABILITY_TYPE_BASEPARA_WIPEFOG		= 0,	//第0位代表是否支持除雾
	ABILITY_TYPE_BASEPARA_NEW3D			= 1,	//第1位代表是否支持新3D定位协议
	ABILITY_TYPE_BASEPARA_COMPASS		= 2		//第2位代表是否支持罗盘
};

CLS_VideoView::CLS_VideoView(void)
{
	m_iID = -1;
	m_uColor = GetSysColor(COLOR_BTNFACE);
	m_uConnID = -1;
	m_iDragType = DRAG_TYPE_NONE;
	m_uShowCaps = SHOW_CAP_NONE;
	m_iVideoCoverIndex = -1;
	memset(&m_rcDrag,0xff,sizeof(RECT));
	m_IsChannelTalk = false;
	m_IsInputTalkData = false;
}

CLS_VideoView::~CLS_VideoView(void)
{

}

BEGIN_MESSAGE_MAP(CLS_VideoView, CStatic)
	ON_WM_PAINT()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_COMMAND(ID_3D_LOCATE,&CLS_VideoView::On3DLocate)
	ON_COMMAND(ID_EZOOM,&CLS_VideoView::OnEZoom)
	ON_COMMAND(ID_VIDEO_COVER_AREA,&CLS_VideoView::OnVideoCoverArea)
	ON_COMMAND(ID_MOTION_DETECT_AREA,&CLS_VideoView::OnMotionDetectArea)
	ON_COMMAND(ID_SHOW_BITRATE,&CLS_VideoView::OnShowBitrate)
	ON_COMMAND(ID_SHOW_MOTION_DETECT,&CLS_VideoView::OnShowMotionDetect)
	ON_COMMAND(ID_DISCONNECT, &CLS_VideoView::OnDisconnect)
	ON_COMMAND(ID_AUTO_FOCUS, &CLS_VideoView::OnAutoFocus)
	ON_COMMAND(ID_CHANNEL_TALK, &CLS_VideoView::OnChannelTalk)
	ON_COMMAND(ID_INPUT_TALK_DATA, &CLS_VideoView::OnInputTalkData)
	ON_WM_LBUTTONDBLCLK()
	ON_MESSAGE(WM_INPUT_CHANNELTALKING_END, &CLS_VideoView::OnChannelTalkEnd)
END_MESSAGE_MAP()

CLS_VideoView* CLS_VideoView::CreateInstance( int _iID,CWnd* _pParent )
{
	RECT rcShow = {0};
	CLS_VideoView* pVideo = new CLS_VideoView();
	pVideo->Create(NULL,WS_CHILD | WS_VISIBLE | SS_NOTIFY /*| SS_GRAYRECT*/,rcShow,_pParent);
	if (pVideo)
	{
		pVideo->SetID(_iID);
		pVideo->SetOwner(_pParent);
		s_hViewWnd = _pParent->GetSafeHwnd();
	}	
	return pVideo;
}

void CLS_VideoView::OnPaint()
{
	CPaintDC dc(this); 
	DrawRect(m_uColor,&dc);
}

void CLS_VideoView::SetConnID( unsigned int _uConnID )
{
	m_uShowCaps = SHOW_CAP_NONE;
	m_iDragType = DRAG_TYPE_NONE;
	m_iVideoCoverIndex = -1;
	m_uConnID = _uConnID;
	m_IsChannelTalk = false;
	m_IsInputTalkData = false;
}

void CLS_VideoView::DrawRect( COLORREF _uColor,CDC* _pDC)
{
	RECT rcShow = {0};
	GetClientRect(&rcShow);
	if (NULL == _pDC)
	{
 		_pDC = this->GetDC();
 		m_uColor = _uColor;
	}
	else
	{
		_pDC->FillSolidRect(&rcShow,RGB(0,0,0));
	}
	
	CBrush	brFrame(m_uColor);
 	InflateRect(&rcShow,1,1);
 	_pDC->FrameRect(&rcShow,&brFrame);
	ReleaseDC(_pDC);
}

void CLS_VideoView::OnRButtonUp(UINT nFlags, CPoint point)
{
	//GetOwner()->PostMessage(WM_COMMAND,STN_CLICKED<<16,(LPARAM)GetSafeHwnd());

	PCHANNEL_INFO pChannel = FindChannel(m_uConnID);
	if (NULL == pChannel)
	{
		return;
	}

	POINT ptCursor = {0};	
	CMenu menu;

	GetCursorPos(&ptCursor);	
	ScreenToClient(&ptCursor);
	menu.CreatePopupMenu();

	if (GetParent())
	{
		menu.AppendMenu(MF_STRING,ID_DISCONNECT,GetTextEx(IDS_MENU_DISCONNECT));	
		menu.AppendMenu(MF_SEPARATOR);
	}

	menu.AppendMenu(MF_STRING,ID_3D_LOCATE,GetTextEx(IDS_MENU_3D_LOCATE));
	if (GetParent())
	{
		menu.AppendMenu(MF_STRING,ID_EZOOM,GetTextEx(IDS_MENU_EZOOM));
	}
	menu.AppendMenu(MF_STRING,ID_VIDEO_COVER_AREA,GetTextEx(IDS_MENU_VIDEO_COVER_AREA));
	menu.AppendMenu(MF_STRING,ID_MOTION_DETECT_AREA,GetTextEx(IDS_MENU_MOTION_DETECT_AREA));
	if (m_iDragType > 0)
	{
		menu.CheckMenuRadioItem(ID_3D_LOCATE,ID_MOTION_DETECT_AREA,ID_3D_LOCATE+m_iDragType-1,MF_CHECKED);
	}
	menu.AppendMenu(MF_SEPARATOR);
	
	int iX = 0;
	int iY = 0;
	int iEnabled = 0;
	m_uShowCaps &= ~SHOW_CAP_BITRATE;
	menu.AppendMenu(MF_STRING,ID_SHOW_BITRATE,GetTextEx(IDS_MENU_SHOW_BITRATE));
	

	int iRet = NetClient_GetBitrateOnVideo(m_uConnID,&iX,&iY,&iEnabled);
	if (0 == iRet)
	{
		//AddLog(LOG_TYPE_SUCC,"","NetClient_GetBitrateOnVideo(%u,%d,%d,%d)",m_uConnID,iX,iY,m_bShowBitrate);
		if (1 == iEnabled)
		{
			menu.CheckMenuItem(ID_SHOW_BITRATE,MF_CHECKED);
			m_uShowCaps |= SHOW_CAP_BITRATE;
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetBitrateOnVideo(%u,%d,%d,%d)",m_uConnID,iX,iY,iEnabled);
	}

	menu.AppendMenu(MF_STRING,ID_SHOW_MOTION_DETECT,GetTextEx(IDS_MENU_SHOW_MOTION_DETECT));
	if (m_uShowCaps & SHOW_CAP_MOTION_DETECT)
	{
		menu.CheckMenuItem(ID_SHOW_MOTION_DETECT,MF_CHECKED);
	}

	menu.AppendMenu(MF_STRING,ID_AUTO_FOCUS,GetTextEx(IDS_MENU_AUTO_FOCUS));

	menu.AppendMenu(MF_STRING,ID_CHANNEL_TALK,GetTextEx(IDS_MENU_CHANNEL_TALK));	
	if (m_IsChannelTalk)
	{
		menu.CheckMenuItem(ID_CHANNEL_TALK,MF_CHECKED);
	}

	menu.AppendMenu(MF_STRING,ID_INPUT_TALK_DATA,GetTextEx(IDS_MENU_INPUT_TALK_DATA));
	if (m_IsInputTalkData)
	{
		menu.CheckMenuItem(ID_INPUT_TALK_DATA,MF_CHECKED);
	}

	ClientToScreen(&ptCursor);
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,ptCursor.x,ptCursor.y,this);
	menu.DestroyMenu();

	int iWidth = 0,iHeight = 0;
	memset(&m_rcVideo,0,sizeof(RECT));
	iRet = NetClient_GetVideoSize(pChannel->iLogonID,pChannel->iChannelNo,&iWidth,&iHeight,pChannel->iStreamNo);
	if (0 == iRet)
	{
		m_rcVideo.right = iWidth;
		m_rcVideo.bottom = iHeight;
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetVideoSize(%d,%d,%d,%d,%d)"
			,pChannel->iLogonID,pChannel->iChannelNo,iWidth,iHeight,pChannel->iStreamNo);
	}

	CStatic::OnRButtonUp(nFlags, point);
}

void CLS_VideoView::On3DLocate()
{
	if (m_iDragType == DRAG_TYPE_3D_LOCATE)
	{
		m_iDragType = DRAG_TYPE_NONE;
	}
	else
	{
		m_iDragType = DRAG_TYPE_3D_LOCATE;
	}
}

void CLS_VideoView::OnEZoom()
{
	if (m_iDragType == DRAG_TYPE_EZOOM)
	{
		m_iDragType = DRAG_TYPE_NONE;
	}
	else
	{
		m_iDragType = DRAG_TYPE_EZOOM;
	}
}

void CLS_VideoView::OnVideoCoverArea()
{
	if (m_iDragType == DRAG_TYPE_VIDEO_COVER)
	{
		m_iDragType = DRAG_TYPE_NONE;
	}
	else
	{
		m_iDragType = DRAG_TYPE_VIDEO_COVER;
	}
}

void CLS_VideoView::OnMotionDetectArea()
{
	if (m_iDragType == DRAG_TYPE_MOTION_DETECT)
	{
		m_iDragType = DRAG_TYPE_NONE;
	}
	else
	{
		m_iDragType = DRAG_TYPE_MOTION_DETECT;
	}
}

void CLS_VideoView::OnShowBitrate()
{
	int iEnable = 1 - (m_uShowCaps & SHOW_CAP_BITRATE);
	int iRet = NetClient_ShowBitrateOnVideo(m_uConnID,0,0,iEnable);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_ShowBitrateOnVideo(%d,0,0,%d)",m_uConnID,iEnable);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_ShowBitrateOnVideo(%d,0,0,%d)",m_uConnID,iEnable);
	}
}

void CLS_VideoView::OnShowMotionDetect()
{
	if (m_uShowCaps & SHOW_CAP_MOTION_DETECT)
	{
		NetClient_DrawRectOnLocalVideo(m_uConnID,NULL,0);
		m_uShowCaps &= ~SHOW_CAP_MOTION_DETECT;
	}
	else
	{
		RECT rcArea[DETECT_COLUMN_NUM*DETECT_ROW_NUM] = {0};

		int iCount = sizeof(rcArea)/sizeof(RECT);
		GetMotionDetetionArea(rcArea,iCount);
		ShowMotionDetetionArea(rcArea,iCount);
		m_uShowCaps |= SHOW_CAP_MOTION_DETECT;
	}
}

void CLS_VideoView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (DRAG_TYPE_NONE != m_iDragType)
	{
		//AddLog(LOG_TYPE_MSG,"","OnLButtonDown(%d,%d)",point.x,point.y);
		m_rcDrag.left = point.x;
		m_rcDrag.top = point.y;
	}

	CStatic::OnLButtonDown(nFlags, point);
}

void CLS_VideoView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (MK_LBUTTON == nFlags && DRAG_TYPE_NONE != m_iDragType && m_rcDrag.left >= 0)
	{
		//AddLog(LOG_TYPE_MSG,"","OnMouseMove(%d,%d)",point.x,point.y);
		m_rcDrag.right = point.x;
		m_rcDrag.bottom = point.y;

		RECT rcVideo = {0};
		ClientToVideo(m_rcDrag,rcVideo);
		if (DRAG_TYPE_MOTION_DETECT == m_iDragType && (m_uShowCaps & SHOW_CAP_MOTION_DETECT))
		{
			RECT rcArea[DETECT_COLUMN_NUM*DETECT_ROW_NUM+1];
			int iCount = sizeof(rcArea)/sizeof(RECT);
			GetMotionDetetionArea(rcArea,iCount,&rcVideo);
			NetClient_DrawRectOnLocalVideo(m_uConnID,rcArea,iCount);
		}
		else
		{
			NetClient_DrawRectOnLocalVideo(m_uConnID,&rcVideo,1);
		}

		TRACKMOUSEEVENT tme; 
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.dwHoverTime = HOVER_DEFAULT;
		tme.hwndTrack = m_hWnd;
		TrackMouseEvent(&tme);
	}

	CStatic::OnMouseMove(nFlags, point);
}

void CLS_VideoView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (DRAG_TYPE_NONE != m_iDragType && m_rcDrag.left >= 0)
	{
		//AddLog(LOG_TYPE_MSG,"","OnLButtonUp(%d,%d)",point.x,point.y);
		m_rcDrag.right = point.x;
		m_rcDrag.bottom = point.y;
		DrawVideoArea(m_rcDrag);
		memset(&m_rcDrag,0xff,sizeof(RECT));
	}

	CStatic::OnLButtonUp(nFlags, point);
}

void CLS_VideoView::OnMouseLeave()
{
	if (DRAG_TYPE_NONE != m_iDragType && m_rcDrag.left >= 0)
	{
		//AddLog(LOG_TYPE_MSG,"","OnMouseLeave(%d,%d,%d,%d)",m_rcDrag.left,m_rcDrag.top,m_rcDrag.right,m_rcDrag.bottom);
		DrawVideoArea(m_rcDrag);
		memset(&m_rcDrag,0xff,sizeof(RECT));
	}

	CStatic::OnMouseLeave();
}

int CLS_VideoView::ClientToVideo(RECT& _rcScreen,OUT RECT& _rcVideo)
{
	if (0 == m_rcVideo.right || 0 == m_rcVideo.bottom)
	{
		memset(&_rcVideo,0,sizeof(RECT));
		return -1;
	}

	_rcVideo.left = min(_rcScreen.left,_rcScreen.right);
	_rcVideo.top = min(_rcScreen.top,_rcScreen.bottom);
	_rcVideo.right = max(_rcScreen.left,_rcScreen.right);
	_rcVideo.bottom = max(_rcScreen.top,_rcScreen.bottom);

	int iWidth = m_rcVideo.right-m_rcVideo.left;
	int iHeight = m_rcVideo.bottom-m_rcVideo.top;
	int iSWidth = 0;
	int iSHeight = 0;
	RECT rcClient = {0};
	GetClientRect(&rcClient);
	_rcVideo.left = (_rcVideo.left*iWidth+rcClient.right/2)/rcClient.right;
	_rcVideo.top = (_rcVideo.top*iHeight+rcClient.bottom/2)/rcClient.bottom;
	_rcVideo.right = (_rcVideo.right*iWidth+rcClient.right/2)/rcClient.right;
	_rcVideo.bottom = (_rcVideo.bottom*iHeight+rcClient.bottom/2)/rcClient.bottom;	

	return 0;
}

int CLS_VideoView::DrawVideoArea(RECT& _rcDrag)
{
	RECT rcVideo = {0};
	ClientToVideo(_rcDrag,rcVideo);
	switch(m_iDragType)
	{
	case DRAG_TYPE_3D_LOCATE:
		{
			if (SupportNew3D())		//全景球支持新的3D定位
			{
				New3DLocate(_rcDrag);
			}
			else
			{
				_3DLocate(rcVideo, _rcDrag.left < _rcDrag.right ? TRUE : FALSE);				
			}
			NetClient_DrawRectOnLocalVideo(m_uConnID,NULL,0);
		}
		break;
	case DRAG_TYPE_EZOOM:
		{
			if (!IsRectEmpty(&rcVideo))
			{
				CLS_EZoomManager::Instance()->AddEZoom(m_uConnID,&rcVideo);
			}
			NetClient_DrawRectOnLocalVideo(m_uConnID,NULL,0);
		}
		break;
	case DRAG_TYPE_VIDEO_COVER:
		SetVideoCoverArea(rcVideo);
		NetClient_DrawRectOnLocalVideo(m_uConnID,NULL,0);
		break;
	case DRAG_TYPE_MOTION_DETECT:
		SetMotionDetetionArea(rcVideo);
		break;
	default:
		break;
	}

	return 0;
}

int CLS_VideoView::_3DLocate(RECT& _rcVideo,BOOL _bDirection)
{
	PCHANNEL_INFO pChannel = FindChannel(m_uConnID);
	if (NULL == pChannel)
	{
		return -1;
	}

	int	 iDevAddress = 0;
	int  iComPort = 1;
	char pcProtocol[32] = {0};
	int iRet = NetClient_GetDeviceType(pChannel->iLogonID,pChannel->iChannelNo,&iComPort,&iDevAddress,pcProtocol);
	if (0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDeviceType(%d,%d,,,)"
			,pChannel->iLogonID,pChannel->iChannelNo);
		return -1;
	}
	if(0 != strcmp(pcProtocol,"DOME_PLUS"))
	{
		AddLog(LOG_TYPE_MSG,"","Protocol name(%s) is not DOME_PLUS",pcProtocol);
		return -1;
	}
	--iDevAddress;
	if (iDevAddress < 0)
	{
		iDevAddress = 0;
	}

	int iFlip=0;
	iRet = NetClient_GetSensorFlip(pChannel->iLogonID,pChannel->iChannelNo, &iFlip);
	if (0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetSensorFlip(%d,%d,%d)"
			,pChannel->iLogonID,pChannel->iChannelNo,iFlip);
		return -1;
	}

	int L=0,R=0,U=0,D=0,W=0,T=0,iComNo=1,iPan=0,iTilt=0,iZoom=0;
	POINT ptVideo;
	ptVideo.x = (_rcVideo.left+_rcVideo.right)/2;
	ptVideo.y = (_rcVideo.top+_rcVideo.bottom)/2;
	T = _bDirection;
	W = 1-_bDirection;

	INT	ox=ptVideo.x,oy=ptVideo.y;
	if (1 == iFlip)
	{
		ox = m_rcVideo.right-ox;
		oy = m_rcVideo.bottom-oy;
	}
	if(ox < m_rcVideo.right/2)
	{
		L=1;
		R=0;
	}
	else
	{
		L=0;
		R=1;
	}

	if(oy < m_rcVideo.bottom/2)
	{
		U=1;
		D=0;
	}
	else
	{
		U=0;
		D=1;
	}

	BYTE cDecBuf[9] = {0};
	cDecBuf[0]=0xf6;
	cDecBuf[1]=8;
	cDecBuf[2]=iDevAddress;
	cDecBuf[3]=0x52;
	cDecBuf[4]=R+L*2+U*4+D*8+W*16+T*32;
	cDecBuf[5]=BYTE(abs(2*ox-m_rcVideo.right)*63/m_rcVideo.right);
	cDecBuf[6]=BYTE(abs(2*oy-m_rcVideo.bottom)*63/m_rcVideo.bottom);
	cDecBuf[7]=BYTE(IsRectEmpty(&_rcVideo) ? 0x3f : (_rcVideo.right-_rcVideo.left)*0x3f/m_rcVideo.right);
	cDecBuf[8]=(cDecBuf[1]+cDecBuf[2]+cDecBuf[3]+cDecBuf[4]+cDecBuf[5]+cDecBuf[6]+cDecBuf[7])&0x7f;

	CString strOut = Bytes2HexString(cDecBuf,sizeof(cDecBuf));
	
	int iChannelType = 0;
	iRet = NetClient_GetChannelProperty(pChannel->iLogonID,pChannel->iChannelNo
		,GENERAL_CMD_GET_CHANNEL_TYPE,&iChannelType,sizeof(iChannelType));
	if (0 == iRet && iChannelType == CHANNEL_TYPE_DIGITAL)
	{
		iRet = NetClient_DigitalChannelSend(pChannel->iLogonID,pChannel->iChannelNo,cDecBuf,sizeof(cDecBuf));
		if(0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_DigitalChannelSend(%d,%d,%s,%d)"
				,pChannel->iLogonID,pChannel->iChannelNo,(LPSTR)(LPCTSTR)strOut,sizeof(cDecBuf));
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_DigitalChannelSend(%d,%d,%s,%d)"
				,pChannel->iLogonID,pChannel->iChannelNo,(LPSTR)(LPCTSTR)strOut,sizeof(cDecBuf));
		}
	}
	else
	{
		iRet = NetClient_ComSend(pChannel->iLogonID,cDecBuf,sizeof(cDecBuf),iComPort);
		if(0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_ComSend(%d,%s,%d,%d)"
				,pChannel->iLogonID,(LPSTR)(LPCTSTR)strOut,sizeof(cDecBuf),iComPort);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_ComSend(%d,%s,%d,%d)"
				,pChannel->iLogonID,(LPSTR)(LPCTSTR)strOut,sizeof(cDecBuf),iComPort);
		}
	}
	return 0;
}

int CLS_VideoView::SetVideoCoverArea(RECT& _rcVideo)
{
	PCHANNEL_INFO pChannel = FindChannel(m_uConnID);
	if (NULL == pChannel)
	{
		return -1;
	}

	RECT rcCover[4] = {0};
	if (TRUE == IsRectEmpty(&_rcVideo))
	{
		int iRet = NetClient_SetVideoCovArea(pChannel->iLogonID,pChannel->iChannelNo,rcCover,pChannel->iStreamNo);
		if(0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetVideoCovArea(%d,%d,[%d,%d,%d,%d],%d)"
				,pChannel->iLogonID,pChannel->iChannelNo,_rcVideo.left,_rcVideo.top
				,_rcVideo.right,_rcVideo.bottom,pChannel->iStreamNo);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetVideoCovArea(%d,%d,[%d,%d,%d,%d],%d)"
				,pChannel->iLogonID,pChannel->iChannelNo,_rcVideo.left,_rcVideo.top
				,_rcVideo.right,_rcVideo.bottom,pChannel->iStreamNo);
		}
		return 0;
	}

	int iRet = NetClient_GetVideoCovArea(pChannel->iLogonID,pChannel->iChannelNo,rcCover,pChannel->iStreamNo);
	if(0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetVideoCovArea(%d,%d,,%d)"
			,pChannel->iLogonID,pChannel->iChannelNo,pChannel->iStreamNo);
		return -1;
	}

	AddLog(LOG_TYPE_SUCC,"","NetClient_GetVideoCovArea(%d,%d,,%d)"
		,pChannel->iLogonID,pChannel->iChannelNo,pChannel->iStreamNo);

	int i = 0;
	for(; i < 4; ++i)//修改替换顺序 
	{
		if (IsRectEmpty(&rcCover[i]))
		{			
			break;
		}
	}

	if (i >= 4)
	{			
		m_iVideoCoverIndex = (m_iVideoCoverIndex+1)%4;
	}
	else
	{
		m_iVideoCoverIndex = i;
	}

	rcCover[m_iVideoCoverIndex] = _rcVideo;
	iRet = NetClient_SetVideoCovArea(pChannel->iLogonID,pChannel->iChannelNo,rcCover,pChannel->iStreamNo);
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetVideoCovArea(%d,%d,[%d,%d,%d,%d],%d)"
			,pChannel->iLogonID,pChannel->iChannelNo,_rcVideo.left,_rcVideo.top
			,_rcVideo.right,_rcVideo.bottom,pChannel->iStreamNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetVideoCovArea(%d,%d,[%d,%d,%d,%d],%d)"
			,pChannel->iLogonID,pChannel->iChannelNo,_rcVideo.left,_rcVideo.top
			,_rcVideo.right,_rcVideo.bottom,pChannel->iStreamNo);
	}
	return 0;
}

int CLS_VideoView::GetMotionDetetionArea(RECT* _prcArea,int _iCount,RECT* _prcVideo)
{
	PCHANNEL_INFO pChannel = FindChannel(m_uConnID);
	if (NULL == pChannel || NULL == _prcArea || _iCount < DETECT_COLUMN_NUM*DETECT_ROW_NUM)
	{
		return -1;
	}

	int iWidth = m_rcVideo.right /DETECT_COLUMN_NUM;
	int iHeight = m_rcVideo.bottom/DETECT_ROW_NUM;
	INT iEnabled	=	0;
	int iRet = -1;
	
	memset(_prcArea,0,_iCount*sizeof(RECT));

	//已有报警区域
	int iIndex = 0;		
	for(INT y = 0;y < DETECT_ROW_NUM;y ++)
	{
		for(INT x = 0;x < DETECT_COLUMN_NUM;x ++)
		{
			iRet = NetClient_GetMotionDetetionArea(pChannel->iLogonID,pChannel->iChannelNo,x,y,&iEnabled);
			if(0 == iRet)
			{
				if (1 == iEnabled)
				{
					_prcArea[iIndex].left   =x*iWidth;
					_prcArea[iIndex].top    =y*iHeight;
					_prcArea[iIndex].right  =(x+1)*iWidth;
					_prcArea[iIndex].bottom =(y+1)*iHeight;
				}
			}
			else
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_GetMotionDetetionArea(%d,%d,%d,%d,%d)"
					,pChannel->iLogonID,pChannel->iChannelNo,x,y,iEnabled);
			}
			++iIndex;
		}
	}

	//增加的区域
	if (_prcVideo)
	{
		iIndex = 0;
		for(INT y = (_prcVideo->top+iHeight/2)/iHeight;y < (_prcVideo->bottom+iHeight/2)/iHeight; ++y)
		{
			for(INT x = (_prcVideo->left+iWidth/2)/iWidth;x < (_prcVideo->right+iWidth/2)/iWidth; ++x)
			{
				iIndex = y*DETECT_COLUMN_NUM+x;
				_prcArea[iIndex].left   =x*iWidth;
				_prcArea[iIndex].top    =y*iHeight;
				_prcArea[iIndex].right  =(x+1)*iWidth;
				_prcArea[iIndex].bottom =(y+1)*iHeight;
			}
		}
	}

	return 0;
}

int CLS_VideoView::SetMotionDetetionArea( RECT* _prcArea,int _iCount )
{
	PCHANNEL_INFO pChannel = FindChannel(m_uConnID);
	if (NULL == pChannel || NULL == _prcArea || _iCount < DETECT_COLUMN_NUM*DETECT_ROW_NUM)
	{
		return -1;
	}

	int iRet = -1;
	int iIndex = 0;
	int iEnable = 0;
	for(INT y = 0;y < DETECT_ROW_NUM;y ++)
	{
		for(INT x = 0;x < DETECT_COLUMN_NUM;x ++)
		{
			if (IsRectEmpty(_prcArea+iIndex))
			{
				iEnable = 0;
			}
			else
			{
				iEnable = 1;
			}
			iRet = NetClient_SetMotionDetetionArea(pChannel->iLogonID,pChannel->iChannelNo,x,y,iEnable);
			if(0 != iRet)
			{
				AddLog(LOG_TYPE_FAIL,"","NetClient_SetMotionDetetionArea(%d,%d,%d,%d,%d)"
					,pChannel->iLogonID,pChannel->iChannelNo,x,y,iEnable);
			}
			++iIndex;
		}
	}
	iRet = NetClient_SetMotionAreaEnable(pChannel->iLogonID,pChannel->iChannelNo);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetMotionAreaEnable(%d,%d)"
			,pChannel->iLogonID,pChannel->iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetMotionAreaEnable(%d,%d)"
			,pChannel->iLogonID,pChannel->iChannelNo);
	}

	return 0;
}

int CLS_VideoView::SetMotionDetetionArea( RECT& _rcVideo )
{
	RECT rcArea[DETECT_COLUMN_NUM*DETECT_ROW_NUM] = {0};
	int iCount = sizeof(rcArea)/sizeof(RECT);
	if (FALSE == IsRectEmpty(&_rcVideo))
	{
		GetMotionDetetionArea(rcArea,iCount,&_rcVideo);
	}
	SetMotionDetetionArea(rcArea,iCount);
	if (m_uShowCaps & SHOW_CAP_MOTION_DETECT)
	{
		ShowMotionDetetionArea(rcArea,iCount);
	}
	else
	{
		NetClient_DrawRectOnLocalVideo(m_uConnID,NULL,0);
	}
	return 0;
}

int CLS_VideoView::ShowMotionDetetionArea( RECT* _prcArea,int _iCount )
{
	if (NULL == _prcArea)
	{
		return -1;
	}

	int iRet = NetClient_DrawRectOnLocalVideo(m_uConnID,_prcArea,_iCount);
	if (0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_DrawRectOnLocalVideo(%u,,%d)"
			,m_uConnID,_iCount);
	}
	return 0;
}

void CLS_VideoView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (NULL == GetParent())
	{
		ShowWindow(SW_HIDE);
 		PCHANNEL_INFO pChannel = FindChannel(m_uConnID);
 		if (pChannel)
		{
			CLS_VideoView* pVideo = (CLS_VideoView*)pChannel->pVideo;
			if (pVideo)
			{
				HWND hWnd = pVideo->GetSafeHwnd();
				int iRet = NetClient_ResetPlayerWnd(m_uConnID,hWnd);
				if (0 == iRet)
				{
					AddLog(LOG_TYPE_SUCC,"","NetClient_ResetPlayerWnd(%u,0x%08x)",m_uConnID,hWnd);
				}
				else
				{
					AddLog(LOG_TYPE_FAIL,"","NetClient_ResetPlayerWnd(%u,0x%08x)",m_uConnID,hWnd);
				}
				GetOwner()->PostMessage(WM_COMMAND,STN_DBLCLK<<16,(LPARAM)hWnd);
			}
		}
	}
	else
	{
		CStatic::OnLButtonDblClk(nFlags,point);
	}
}

void CLS_VideoView::OnDisconnect()
{
	CLS_PreviewWindow* pParent = (CLS_PreviewWindow*)GetOwner();
	if (pParent)
	{
		CTreeCtrl* ptvDevice = pParent->GetDeviceTreeCtrl();
		PCHANNEL_INFO pChannel = FindChannel(m_uConnID);
		if (pChannel && ptvDevice)
		{
			ptvDevice->SelectItem(pChannel->hItem);
			AfxGetApp()->GetMainWnd()->PostMessage(WM_COMMAND,ID_DISCONNECT,NULL);
		}
	}
	//GetOwner()->PostMessage(WM_COMMAND,STN_CLICKED<<16,(LPARAM)GetSafeHwnd());
	//AfxGetApp()->GetMainWnd()->PostMessage(WM_COMMAND,ID_DISCONNECT,NULL);
}

void CLS_VideoView::OnAutoFocus()
{
	int i=1;
	int iRet= NetClient_SendCommand(m_uConnID, COMMAND_ID_AUTO_FOCUS, 1, &i, 1);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SendCommand(%u,%s)",m_uConnID,"COMMAND_ID_AUTO_FOCUS");
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SendCommand(%u,%s)",m_uConnID,"COMMAND_ID_AUTO_FOCUS");
	}
}

void CLS_VideoView::OnChannelTalk()
{
	PCHANNEL_INFO pChannel = FindChannel(m_uConnID);
	if (NULL == pChannel)
	{
		return;
	}

	if(NULL == NetClient_ChannelTalkStart || NULL == NetClient_ChannelTalkEnd)
	{
		return;
	}

	int iRet = -1;
	//如果已开启，再次点击关闭对讲
	if (m_IsChannelTalk) 
	{
		if (StopTalk())
		{
			m_IsChannelTalk = false;
		}
		
		return;
	}

	m_IsChannelTalk = true;
	//首先停止对讲
	int iUser = 0;	//SDK采集音频数据

	iRet = NetClient_ChannelTalkEnd(pChannel->iLogonID, pChannel->iChannelNo);

	iRet = NetClient_ChannelTalkStart(pChannel->iLogonID, pChannel->iChannelNo, iUser);
	if (0 == iRet)
	{
		m_IsInputTalkData = false;
		AddLog(LOG_TYPE_SUCC,"","NetClient_ChannelTalkStart(%d,%d,%d)",pChannel->iLogonID,pChannel->iChannelNo,iUser);
	}
	else
	{
		m_IsChannelTalk = false;
		AddLog(LOG_TYPE_FAIL,"","NetClient_ChannelTalkStart(%d,%d,%d)",pChannel->iLogonID,pChannel->iChannelNo,iUser);
	}

}

void CLS_VideoView::OnInputTalkData()
{
	PCHANNEL_INFO pChannel = FindChannel(m_uConnID);
	if (NULL == pChannel)
	{
		return;
	}

	if(NULL == NetClient_ChannelTalkStart || NULL == NetClient_ChannelTalkEnd)
	{
		return;
	}

	//如果已开启，再次点击关闭对讲
	if (m_IsInputTalkData) 
	{
		if (StopTalk())
		{
			m_IsInputTalkData = false;
		}

		return;
	}

	m_IsInputTalkData = true;

	int iUser = 1;	//上层输入音频数据
	int iRet = -1;

	iRet = NetClient_ChannelTalkEnd(pChannel->iLogonID, pChannel->iChannelNo);

	iRet = NetClient_ChannelTalkStart(pChannel->iLogonID, pChannel->iChannelNo, iUser);
	if (0 == iRet)
	{
		m_IsChannelTalk = false;
		AddLog(LOG_TYPE_SUCC,"","NetClient_ChannelTalkStart(%d,%d,%d)",pChannel->iLogonID, pChannel->iChannelNo,iUser);
	}
	else
	{
		m_IsInputTalkData = false;
		AddLog(LOG_TYPE_FAIL,"","NetClient_ChannelTalkStart(%d,%d,%d)",pChannel->iLogonID,pChannel->iChannelNo,iUser);
	}
}

void CLS_VideoView::ChannelTalkNotify(int _iLogonID, int _iChannelNo, int _iTalkStatus)
{
	if (!m_IsInputTalkData)
	{
		return;
	}

	PCHANNEL_INFO pChannel = FindChannel(m_uConnID);
	if (NULL == pChannel)
	{
		return;
	}

	PDEVICE_INFO pDevice = FindDevice(pChannel->iLogonID);
	if (!pDevice || TALK_BEGIN_OK != _iTalkStatus || _iChannelNo < 0)
	{
		return;
	}

	static TCHAR BASED_CODE szFilter[] = _T("Record Files (*.wav)|*.wav||");
	CFileDialog file(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,this);
	if (IDOK == file.DoModal())
	{
		CString szFileName = file.GetPathName();
		strcpy_s(pDevice->cTalkInputFile, sizeof(pDevice->cTalkInputFile), szFileName.GetBuffer(0));
		if (NULL != pDevice->hEventQuitTalking)
		{
			ResetEvent(pDevice->hEventQuitTalking);
		}
		else
		{
			pDevice->hEventQuitTalking = CreateEvent(NULL, FALSE, FALSE, "");
		}
		if (NULL != pDevice->hThreadTalk)
		{
			if (NULL != pDevice->hEventQuitTalking)
			{
				SetEvent(pDevice->hEventQuitTalking);
			}
			WaitForSingleObject(pDevice->hThreadTalk,INFINITE);
			CloseHandle(pDevice->hThreadTalk);
			pDevice->hThreadTalk = NULL;
			if (NULL != pDevice->hEventQuitTalking)
			{
				ResetEvent(pDevice->hEventQuitTalking);
			}
		}
		int iParam = pChannel->iLogonID;
		iParam |= (_iChannelNo << 16);
		pDevice->hThreadTalk = CreateThread(NULL, 0, ThreadInputChannelTalking, &iParam, 0, NULL);	
	}
}

DWORD WINAPI CLS_VideoView::ThreadInputChannelTalking(LPVOID pParam)
{
	int iParam = *(int*)pParam;
	int iChNo = iParam >> 16 & 0xFFFF;
	int iLogonID = iParam & 0xFFFF;

	iChNo = 0;
	iLogonID= 0;
	PDEVICE_INFO pDevice = FindDevice(iLogonID);
	int iSleepTime = 40;
	int iDataLen = 16*iSleepTime;

	int srcFileSize = 0;
	int iReadNum = 0, iRet = 0;

	unsigned char* ucBuf = NULL;
	FILE* fpSrc = _fsopen(pDevice->cTalkInputFile, "rb",_SH_DENYNO);
	if(fpSrc==NULL)
	{
		TRACE("[ThreadInputTalking] open file failed, then return ....\n");
		goto END;
	}

	ucBuf = (unsigned char*)malloc(iDataLen);

	fseek(fpSrc,0,SEEK_END);  //定位到文件尾部
	srcFileSize = ftell(fpSrc);                     //  获取文件大小
	fseek(fpSrc,0,SEEK_SET); //定位到文件的开头
	if (srcFileSize % iDataLen != 0)                //  不是整数倍，读取次数要+1
	{
		iReadNum =  srcFileSize/iDataLen + 1;
	}
	else
	{
		iReadNum =  srcFileSize/iDataLen + 0;
	}

	TRACE("ReadNum:    %d\n", iReadNum);

	for(int i=0;i<iReadNum-1;i++)
	{
		if (::WaitForSingleObject(pDevice->hEventQuitTalking, iSleepTime) == WAIT_OBJECT_0)
			goto END;

		fread(ucBuf,1,iDataLen,fpSrc);
		iRet = NetClient_InputChannelTalkingdata(iLogonID, iChNo, ucBuf, iDataLen);
		if(iRet < 0)
		{
			::OutputDebugString("[ThreadInputTalking]  -- (NetClient_InputTalkingdata) Failed, ");
		}
	}

	::Sleep(iSleepTime);
	iDataLen = srcFileSize - iDataLen*(iReadNum-1);
	fread(ucBuf,1,iDataLen,fpSrc);
	iRet = NetClient_InputChannelTalkingdata(iLogonID, iChNo, ucBuf, iDataLen);

END:
	if (ucBuf)
	{
		free(ucBuf);
		ucBuf = NULL;
	}

	Inner_SafeCloseFile(&fpSrc);

	//通知上层应用程序，inputTalking完成。
	::SendMessageTimeout(s_hViewWnd, WM_INPUT_CHANNELTALKING_END, 0, iLogonID, SMTO_NORMAL, 3000,NULL);

	return 0;
}

LRESULT CLS_VideoView::OnChannelTalkEnd(WPARAM wParam, LPARAM lParam)
{
	//OnInputTalkData();
	return 0;
}

bool CLS_VideoView::StopTalk()
{
	PCHANNEL_INFO pChannel = FindChannel(m_uConnID);
	if (NULL == pChannel)
	{
		return false;
	}

	if(NULL == NetClient_ChannelTalkStart || NULL == NetClient_ChannelTalkEnd)
	{
		return false;
	}

	bool blRet = false;
	int iRet = NetClient_ChannelTalkEnd(pChannel->iLogonID, pChannel->iChannelNo);
	if (0 == iRet)
	{
		blRet = true;
		AddLog(LOG_TYPE_SUCC,"","NetClient_ChannelTalkEnd(%d,%d)",pChannel->iLogonID,pChannel->iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_ChannelTalkEndt(%d,%d)",pChannel->iLogonID,pChannel->iChannelNo);
	}

	return blRet;
}

bool CLS_VideoView::SupportNew3D()
{
	PCHANNEL_INFO pChannel = FindChannel(m_uConnID);
	if (NULL == pChannel)
	{
		return false;
	}

	int iLogonID = pChannel->iLogonID;
	int iChannelNo = pChannel->iChannelNo;
	bool bFlag = false;

	//bit0除雾：0-不支持，1-支持除雾
	//bit1 新3D定位协议：0-不支持，1-支持
	//bit2 是否支持罗盘：0-不支持，1-支持
	FuncAbilityLevel stFuncAbilityLevel = {0};
	stFuncAbilityLevel.iSize = sizeof(FuncAbilityLevel);
	stFuncAbilityLevel.iMainFuncType = MAIN_FUNC_TYPE_DOME_PARA;
	stFuncAbilityLevel.iSubFuncType = 0;
	int iReturnByte = -1;
	int iRet = NetClient_GetDevConfig(iLogonID, NET_CLIENT_GET_FUNC_ABILITY, iChannelNo, &stFuncAbilityLevel, sizeof(stFuncAbilityLevel), &iReturnByte);
	if (RET_SUCCESS == iRet)
	{
		int iFuncPara = _ttoi(stFuncAbilityLevel.cParam);
		std::bitset<sizeof(int) * LEN_8> bitAbility(iFuncPara);
		if (1 == bitAbility[ABILITY_TYPE_BASEPARA_NEW3D])
		{
			bFlag = true;
		}
	}
	return bFlag;
}

void CLS_VideoView::New3DLocate(RECT& _rcVideo)
{
	PCHANNEL_INFO pChannel = FindChannel(m_uConnID);
	if (NULL == pChannel)
	{
		return;
	}
	int iLogonID = pChannel->iLogonID;
	int iChannelNo = pChannel->iChannelNo;

	Locate3DPosition t3dInfo = {0}; 
	t3dInfo.iBufSize = sizeof(t3dInfo);

	CRect rcShow;
	GetClientRect(&rcShow);
	CRect rcDraw = _rcVideo;	//视频上画的区域，点或者矩形

	//需要将坐标转换为万分比
	if (rcDraw.left == rcDraw.right && rcDraw.top == rcDraw.bottom)	
	{							//画1个点
		t3dInfo.iPointNum = 1;
		t3dInfo.tPoint[0].iX = rcDraw.left*TENTHOUSAND_RATE/rcShow.Width();
		t3dInfo.tPoint[0].iY = rcDraw.top*TENTHOUSAND_RATE/rcShow.Height();
	}
	else						//画矩形
	{
		t3dInfo.iPointNum = 2;
		t3dInfo.tPoint[0].iX = rcDraw.left*TENTHOUSAND_RATE/rcShow.Width();
		t3dInfo.tPoint[0].iY = rcDraw.top*TENTHOUSAND_RATE/rcShow.Height();
		t3dInfo.tPoint[1].iX = rcDraw.right*TENTHOUSAND_RATE/rcShow.Width();
		t3dInfo.tPoint[1].iY = rcDraw.bottom*TENTHOUSAND_RATE/rcShow.Height();
	}

	int iRet = NetClient_SendCommand(iLogonID, COMMAND_ID_3D_POSITION, iChannelNo, &t3dInfo, sizeof(t3dInfo));
	if(RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","3D NetClient_SendCommand(%d,%d)",pChannel->iLogonID, pChannel->iChannelNo);
	}
}