// VideoVideoForDraw.cpp : implementation file
//

#include "stdafx.h"
#include "RetValue.h"
#include "NetClientDemo.h"
#include "NetClientTypes.h"
#include "Include/NVSSDK_INTERFACE.h"
using namespace NVSSDK_INTERFACE;
#include "Common/CommonFun.h"
#include "VideoViewForDrawWindowDetection.h"

#define COLOR_RED					RGB(255,0,0)		//��ɫ
#define COLOR_GREEN					RGB(0,255,0)		//��ɫ
#define COLOR_ORANGE				RGB(255,97,0)		//��ɫ
#define COLOR_YELLOW				RGB(255,255,0)		//��ɫ
#define COLOR_DEEP_RED				RGB(255,0,255)		//����

#define DRAW_WIDTH					1					//���߿��

#define	INVALID_CONNECT_ID			(0xFFFFFFFF)


int DrawCallbackFunc(long _lHandle, HDC _hDc, long _lUserData)
{
	if (NULL == _hDc)
	{
		return RET_SUCCESS;
	}

	CLS_VideoViewForDrawWindowDetection* _pclsPreview = (CLS_VideoViewForDrawWindowDetection*)_lUserData;
	if (NULL == _pclsPreview)
	{
		return RET_SUCCESS;
	}

	HGDIOBJ original = SelectObject(_hDc, GetStockObject(DC_PEN));
	_pclsPreview->PaintLinesOnDc(_hDc);
	SelectObject(_hDc, original);
	return RET_SUCCESS;
}

IMPLEMENT_DYNAMIC(CLS_VideoViewForDrawWindowDetection, CDialog)

CLS_VideoViewForDrawWindowDetection::CLS_VideoViewForDrawWindowDetection(CWnd* pParent /*=NULL*/)
	: CDialog(CLS_VideoViewForDrawWindowDetection::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNO = -1;
	m_iStreamNO = -1;
	m_blStarDrawNotify = FALSE;
	m_uiConnID = INVALID_CONNECT_ID;

	m_iDrawColor = COLOR_DEEP_RED;		//��ˢ��ɫ
	m_penRule = NULL;
	m_blDrawFinish = false;
	m_blDrawing = false;

	m_blDrawOutFrame = true; //�Ȼ����
	m_blDrawInnerFrame = false; //�ٻ��ڿ�

	m_iMaxAreamNum = MAX_WINDOW_DOUBLE_CIRCLE_NUM;
}

CLS_VideoViewForDrawWindowDetection::~CLS_VideoViewForDrawWindowDetection()
{
	if (NULL != m_penRule)
	{
		DeleteObject(m_penRule);
		m_penRule = NULL;
	}
}

void CLS_VideoViewForDrawWindowDetection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_VIDEO_DRAW, m_StcVideoShow);
}


BEGIN_MESSAGE_MAP(CLS_VideoViewForDrawWindowDetection, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DrawOK, &CLS_VideoViewForDrawWindowDetection::OnBnClickedButtonDrawok)
	ON_BN_CLICKED(IDC_BUTTON_ClearRegion, &CLS_VideoViewForDrawWindowDetection::OnBnClickedButtonClearRegion)
	ON_BN_CLICKED(IDC_BUTTON_StartDraw, &CLS_VideoViewForDrawWindowDetection::OnBnClickedButtonStartDraw)
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CLS_VideoViewForDrawWindowDetection::OnInitDialog()
{
	CDialog::OnInitDialog();

	StartRecv();
	UI_UpdateDialog();
	return TRUE;  
}

void CLS_VideoViewForDrawWindowDetection::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
}

void CLS_VideoViewForDrawWindowDetection::OnClose()
{
	StopPlay();
	CDialog::OnClose();
}

void CLS_VideoViewForDrawWindowDetection::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}


void CLS_VideoViewForDrawWindowDetection::OnMainNotify( int _iLogonID,int _wParam, void* _iLParam, void* _iUser )
{
	int iMsgType = _wParam & 0xFFFF;
	if (WCM_VIDEO_HEAD == iMsgType)
	{
		if (NULL == NetClient_StartPlay)
		{
			return;
		}

		RECT rcShow = {0};
		int iRet = NetClient_StartPlay(m_uiConnID, m_StcVideoShow.GetSafeHwnd(), rcShow, 0);

		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL," CH%d-%d","NetClient_StartPlay(%u,,,)",m_iChannelNO, m_iStreamNO, m_uiConnID);
		}

		StartDrawNotify();
	}
}

void CLS_VideoViewForDrawWindowDetection::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_BUTTON_DrawOK, IDS_CONFIG_VCA_DRAWING_OK);
	SetDlgItemTextEx(IDC_BUTTON_ClearRegion, IDS_CONFIG_VCA_DRAWING_CLEAR);
	SetDlgItemTextEx(IDC_BUTTON_NextRegion, IDS_CONFIG_VCA_DRAWING_NEXT);
	SetDlgItemTextEx(IDC_BUTTON_StartDraw, IDS_START_DRAW);

	GetDlgItem(IDC_BUTTON_NextRegion)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_StartDraw)->ShowWindow(SW_SHOW);
	
}

void CLS_VideoViewForDrawWindowDetection::StartRecv()
{
	if (NULL == NetClient_StartRecvEx || NULL == NetClient_StartPlay)
	{
		AddLog(LOG_TYPE_FAIL,"CH%d-%d", "Load Interface NetClient_StartPlay/NetClient_StartRecvEx failed!",m_iChannelNO, m_iStreamNO);
		return;
	}

	CLIENTINFO tInfo = {0};
	tInfo.m_iServerID = m_iLogonID;
	tInfo.m_iChannelNo = m_iChannelNO;
	tInfo.m_iStreamNO = m_iStreamNO;
	tInfo.m_iNetMode = NETMODE_TCP;
	tInfo.m_iTimeout = 20;

	int iRet = NetClient_StartRecvEx(&m_uiConnID, &tInfo, NULL, NULL);
	if (1 == iRet)
	{
		RECT rcShow = {0};
		iRet = NetClient_StartPlay(m_uiConnID, m_StcVideoShow.GetSafeHwnd(), rcShow, 0);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL," CH%d-%d","NetClient_StartPlay(%u)",m_iChannelNO, m_iStreamNO, m_uiConnID);
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL," CH%d-%d","NetClient_StartRecvEx(%u)",m_iChannelNO, m_iStreamNO, m_uiConnID);
	}

	StartDrawNotify();
}

void CLS_VideoViewForDrawWindowDetection::InitVideoParam( int _iLogonID, int _iChnnelNO, int _iStreamNO )
{
	m_iLogonID = _iLogonID;
	m_iChannelNO = _iChnnelNO;
	m_iStreamNO = _iStreamNO;
}

void CLS_VideoViewForDrawWindowDetection::StopPlay()
{
	if (NULL == NetClient_StopPlay || NULL == NetClient_StopRecv)
	{
		AddLog(LOG_TYPE_FAIL,"CH%d-%d", "Load Interface NetClient_StopPlay/NetClient_StopRecv failed!",m_iChannelNO, m_iStreamNO);
		return;
	}

	if (INVALID_CONNECT_ID == m_uiConnID || INVALID_CONNECT_ID < 0)
	{
		return;
	}

	RECT rcShow = {0};
	int iRet = NetClient_StopPlay(m_uiConnID);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL," CH%d-%d","NetClient_StopPlay(%d)",m_iChannelNO, m_iStreamNO, m_uiConnID);
	}

	iRet = NetClient_StopRecv(m_uiConnID);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL," CH%d-%d","NetClient_StopRecv(%d)",m_iChannelNO, m_iStreamNO, m_uiConnID);
	}
}

//�жϽ����Ƿ�����Ƶ����
BOOL CLS_VideoViewForDrawWindowDetection::IsInsideVideoStatic( POINT _pt )
{
	RECT rcVideo = {0};
	m_StcVideoShow.GetWindowRect(&rcVideo);
	ScreenToClient(&rcVideo);

	if (_pt.x <= rcVideo.right && _pt.x >= rcVideo.left)
	{
		if (_pt.y <= rcVideo.bottom && _pt.y >= rcVideo.top)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CLS_VideoViewForDrawWindowDetection::OnBnClickedButtonDrawok()
{
	m_blDrawing = false;
	m_blDrawFinish = true;
	StopPlay();
	OnOK();
}

void CLS_VideoViewForDrawWindowDetection::OnBnClickedButtonClearRegion()
{
	memset(&m_tWinPosInfo, 0, sizeof(m_tWinPosInfo));
	m_blDrawOutFrame = true;
	m_blDrawing = true;
	m_blDrawFinish = false;
}

void CLS_VideoViewForDrawWindowDetection::OnBnClickedButtonStartDraw()
{
	m_blDrawing = true;
	m_blDrawFinish = false;
}

int CLS_VideoViewForDrawWindowDetection::GetDrawPolygonInfo(void* OUT _pvInBuff, int IN _iBufSize)
{
	int iRet = RET_FAILED;
	if (NULL == _pvInBuff)
	{
		return RET_FAILED;
	}

	int iCpySize = min(sizeof(m_tWinPosInfo), _iBufSize);
	memcpy(_pvInBuff, &m_tWinPosInfo, iCpySize);
	return RET_SUCCESS;
}

int CLS_VideoViewForDrawWindowDetection::SetDrawPolygonInfo( void* IN _pvInBuff, int IN _iBufSize )
{
	int iRet = RET_FAILED;
	if (NULL == _pvInBuff)
	{
		return RET_FAILED;
	}

	int iCpySize = min(sizeof(m_tWinPosInfo), _iBufSize);
	memcpy(&m_tWinPosInfo, _pvInBuff, iCpySize);
	return RET_SUCCESS;
}

int CLS_VideoViewForDrawWindowDetection::StartDrawNotify()
{
	if (m_blStarDrawNotify)
	{
		return RET_FAILED;	//�Ѿ�������ͼ�ص���ֱ�ӷ���
	}

	if (INVALID_CONNECT_ID == m_uiConnID || m_uiConnID < 0)
	{
		AddLog(LOG_TYPE_FAIL," CH%d-%d","StartDrawNotify(%d)",m_iChannelNO, m_iStreamNO, m_uiConnID);
		return RET_FAILED;
	}

	int iType = 1;//�������ͣ�0�������� 1������  Ĭ��Ϊ1
	int iRet = NetClient_RegisterDrawFun(m_uiConnID, DrawCallbackFunc, (int)this, &iType, sizeof(iType));

	m_blStarDrawNotify = (iRet < RET_SUCCESS) ? FALSE : TRUE;
	if (iRet < RET_SUCCESS)
	{
		AddLog(LOG_TYPE_FAIL," CH%d-%d","NetClient_RegisterDrawFun(%d)",m_iChannelNO, m_iStreamNO, m_uiConnID);
	}
	return iRet;
}

int CLS_VideoViewForDrawWindowDetection::PaintLinesOnDc(HDC _hdc)
{
	HGDIOBJ originalPen;
	m_penRule = ::CreatePen(PS_SOLID, DRAW_WIDTH, m_iDrawColor);
	originalPen = ::SelectObject(_hdc, m_penRule);

	//���ڻ����Ǹ�ҲҪ��ʾ���������Լ�1
	int iPolygonNum = m_tWinPosInfo.iDoubleCircleNum + 1;
	iPolygonNum = min(MAX_WINDOW_DOUBLE_CIRCLE_NUM, iPolygonNum);

	for (int iAreaNo=0; iAreaNo < iPolygonNum; iAreaNo++)
	{
		WindowDetectionPos& tWinPolygonInfo = m_tWinPosInfo.tWindowDetectionPos[iAreaNo];
		//���
		int iOutPolygonPointNum = min(tWinPolygonInfo.iOutPolygonPointNum, VCA_MAX_POLYGON_POINT_NUMEX);
		DrawPolygonOnDC(_hdc, iOutPolygonPointNum, tWinPolygonInfo.stOutPolygonPoints);
		//�ڿ�
		int iInnerPolygonPointNum = min(tWinPolygonInfo.iInnerPolygonPointNum, VCA_MAX_POLYGON_POINT_NUMEX);
		DrawPolygonOnDC(_hdc, iInnerPolygonPointNum, tWinPolygonInfo.stInnerPolygonPoints);
	}

	SelectObject(_hdc, originalPen);
	DeleteObject(m_penRule);
	return 0;
}

int CLS_VideoViewForDrawWindowDetection::DrawPolygonOnDC(HDC _hdc, int _iPointNum, vca_TPoint* _ptPoint)
{
	if (NULL == _ptPoint)
	{
		return RET_FAILED;
	}

	//��� û�е�ʱ������ƶ�������Ͻ�����һ���ߵ�Bug
	if (_iPointNum < 1)
	{
		return RET_FAILED;
	}

	for (int i = 0; i + 1 < _iPointNum; i++)
	{
		DrawLineOnDC(_hdc, _ptPoint[i].iX, _ptPoint[i].iY, _ptPoint[i+1].iX, _ptPoint[i+1].iY);
	}

	DrawLineOnDC(_hdc, _ptPoint[_iPointNum - 1].iX, _ptPoint[_iPointNum - 1].iY, _ptPoint[0].iX, _ptPoint[0].iY);
	return RET_SUCCESS;
}

int CLS_VideoViewForDrawWindowDetection::DrawLineOnDC(HDC _hdc, int _iXStart, int _iYStart, int _iXEnd, int _iYEnd)
{	
	if (_iXStart == _iXEnd && _iYStart == _iYEnd)
	{
		return RET_FAILED;
	}

	_iXStart = RestoreTenThousandX(_iXStart);
	_iYStart = RestoreTenThousandY(_iYStart);
	_iXEnd = RestoreTenThousandX(_iXEnd);
	_iYEnd = RestoreTenThousandY(_iYEnd);

	MoveToEx(_hdc, _iXStart, _iYStart, NULL);
	LineTo(_hdc, _iXEnd, _iYEnd);
	return 0;
}


LRESULT CLS_VideoViewForDrawWindowDetection::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_blDrawFinish)
	{
		return CDialog::WindowProc(message, wParam, lParam);
	}

	if (!IsWindow(m_hWnd))
	{
		return CDialog::WindowProc(message, wParam, lParam);
	}
	
	if (!m_blDrawing)
	{
		return CDialog::WindowProc(message, wParam, lParam);
	}

	POINT pt = {0};
	GetCursorPos(&pt);
	ScreenToClient(&pt);
	if (!IsInsideVideoStatic(pt) && message != WM_MOUSELEAVE)
	{
		return CDialog::WindowProc(message, wParam, lParam);
	}

	//��������͵������ʵ�ʸ�����Ǳ����1����Ҫ��1 
	//��һ�����أ�
	int iAreaIndex = m_tWinPosInfo.iDoubleCircleNum/* - 1*/;
	if (iAreaIndex >= MAX_WINDOW_DOUBLE_CIRCLE_NUM || iAreaIndex < 0)
	{
		return CDialog::WindowProc(message, wParam, lParam);
	}

	WindowDetectionPos &stCurPolygon = m_tWinPosInfo.tWindowDetectionPos[iAreaIndex];

	int iPtIndex = 0;
	vca_TPoint* ptCurPonitArray = NULL;		//��ǰҪ���ĵ�
	int* piCurPolygonPointNum = NULL;	//��ǰ��ĵ���
	//��ǰ�������Ϣ
	if (m_blDrawOutFrame)		//�����
	{
		iPtIndex = m_tWinPosInfo.tWindowDetectionPos[iAreaIndex].iOutPolygonPointNum/* - 1*/;
		ptCurPonitArray = m_tWinPosInfo.tWindowDetectionPos[iAreaIndex].stOutPolygonPoints;
		piCurPolygonPointNum = &m_tWinPosInfo.tWindowDetectionPos[iAreaIndex].iOutPolygonPointNum;
	}
	else						//���ڿ�
	{
		iPtIndex = m_tWinPosInfo.tWindowDetectionPos[iAreaIndex].iInnerPolygonPointNum/* - 1*/;
		ptCurPonitArray = m_tWinPosInfo.tWindowDetectionPos[iAreaIndex].stInnerPolygonPoints;
		piCurPolygonPointNum = &m_tWinPosInfo.tWindowDetectionPos[iAreaIndex].iInnerPolygonPointNum;
	}

	if (iPtIndex >= VCA_MAX_POLYGON_POINT_NUM || iAreaIndex < 0)
	{
		return CDialog::WindowProc(message, wParam, lParam);
	}


	vca_TPoint tTouThousandPoint = {0};
	tTouThousandPoint.iX = SwitchTenThousandX(pt.x);
	tTouThousandPoint.iY = SwitchTenThousandY(pt.y);

	if (!m_blDrawOutFrame)
	{
		if (!IsPointInsidePolygon(m_tWinPosInfo.tWindowDetectionPos[iAreaIndex].iOutPolygonPointNum, 
			m_tWinPosInfo.tWindowDetectionPos[iAreaIndex].stOutPolygonPoints, tTouThousandPoint))
		{
			return CDialog::WindowProc(message, wParam, lParam);
		}
		
	}
	
	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
			//�ﵽ����������ٻ���
			if (iPtIndex+1 == VCA_MAX_POLYGON_POINT_NUM)
			{
				break;
			}

			//�����߽��
			if (0 == pt.x || 0 == pt.y)
			{
				break;
			}

			//TODO �ж��������Ƿ��н���
			ptCurPonitArray[iPtIndex].iX = tTouThousandPoint.iX;
			ptCurPonitArray[iPtIndex].iY = tTouThousandPoint.iY;
			(*piCurPolygonPointNum)++;
		}
		break;
	case WM_MOUSEMOVE:
		{
			ptCurPonitArray[iPtIndex].iX = tTouThousandPoint.iX;
			ptCurPonitArray[iPtIndex].iY = tTouThousandPoint.iY;
		}
		break;
	case WM_LBUTTONDBLCLK:
		{		
	
			//�պ����������3���㣨�����غϵĵ㣩
			if (*piCurPolygonPointNum <= 3)
			{
				break;
			}

			//���һ��������Ϊ��һ���������
			int iLastX = ptCurPonitArray[0].iX;
			int iLastY = ptCurPonitArray[0].iY;
			ptCurPonitArray[iPtIndex].iX = iLastX;
			ptCurPonitArray[iPtIndex].iY = iLastY;

			//TODO �ж��������Ƿ��н���

			//��������ﵽ���󣬽�����ͼ
			if (m_iMaxAreamNum == m_tWinPosInfo.iDoubleCircleNum)
			{
				m_blDrawFinish = true;
			}
			else
			{
				//�����ǰ����������л����ڿ�
				//����������˵�����ڿ򣬽�����ǰ������
				if (m_blDrawOutFrame)
				{
					m_blDrawOutFrame = false;
				}
				else
				{
					m_blDrawOutFrame = true;
					m_tWinPosInfo.iDoubleCircleNum++;//���˫����ʾ����һ������
				}
			}			
		}
		break;
	default:
		break;
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

//����������� ���Ƿ��ڶ������
bool CLS_VideoViewForDrawWindowDetection::IsPointInsidePolygon(int _iPolygonPointNum, vca_TPoint* _ptPolygonPoint, vca_TPoint _tTestPoint)
{
	if (NULL == _ptPolygonPoint || _iPolygonPointNum <= 2)
	{
		return false;
	}

	int i = 0;
	int j = 0;

	bool blInside = false;

	for (i = 0, j = _iPolygonPointNum-1; i < _iPolygonPointNum; j = i++) 
	{
		if ( ( (_ptPolygonPoint[i].iY > _tTestPoint.iY) != (_ptPolygonPoint[j].iY > _tTestPoint.iY) ) &&

			(_tTestPoint.iX < (_ptPolygonPoint[j].iX - _ptPolygonPoint[i].iX) * (_tTestPoint.iY - _ptPolygonPoint[i].iY) / (_ptPolygonPoint[j].iY-_ptPolygonPoint[i].iY) + _ptPolygonPoint[i].iX) )

			blInside = !blInside;
	}

	return blInside;

	//��㻭������Σ���㶨һ���㣬Ȼ��ͨ�������ˮƽ��һ���ߣ�
	//���������������ߺͶ���εı��ཻ���Σ�������˵���ų���Щ���ཻ�ıߣ���һ���ж���������
	//Ȼ�������������ߴ�Խ����εĴ����Ƿ�Ϊ�������������������ô�õ��ڶ�����ڣ�
	//�����ż�������ڶ�����⡣
}

//��������ת��ֱ�
int CLS_VideoViewForDrawWindowDetection::SwitchTenThousandX(int _iX)
{
	RECT rc = {0};
	m_StcVideoShow.GetClientRect(&rc);
	int iShowWidth = rc.right - rc.left;
	if (0 == iShowWidth)
	{
		return _iX;
	}

	double dRateX = (double)10000/iShowWidth;
	return (int)(_iX*dRateX);
}

//��������ת��ֱ�
int CLS_VideoViewForDrawWindowDetection::SwitchTenThousandY(int _iY)
{
	RECT rc = {0};
	m_StcVideoShow.GetClientRect(&rc);
	int iShowHeight = rc.bottom - rc.top;
	if (0 == iShowHeight)
	{
		return _iY;
	}

	double dRateY = (double)10000/iShowHeight;
	return (int)(_iY*dRateY);
}

//��ֱ�ת��������
int CLS_VideoViewForDrawWindowDetection::RestoreTenThousandX(int _iX)
{
	RECT rc = {0};
	m_StcVideoShow.GetWindowRect(&rc);
	int iShowWidth = rc.right - rc.left;
	double dRateX = (double)iShowWidth/10000;
	return (int)(_iX*dRateX);
}

//��ֱ�ת��������
int CLS_VideoViewForDrawWindowDetection::RestoreTenThousandY(int _iY)
{
	RECT rc = {0};
	m_StcVideoShow.GetWindowRect(&rc);
	int iShowHeight = rc.bottom - rc.top;
	double dRateY = (double)iShowHeight/10000;
	return (int)(_iY*dRateY);
}