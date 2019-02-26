// HeaderCtrlCl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HeaderCtrlClEX.h"

// CHeaderCtrlCl

extern int g_iLanguage;

IMPLEMENT_DYNAMIC(CHeaderCtrlClEX, CHeaderCtrl)

CHeaderCtrlClEX::CHeaderCtrlClEX()
{
	m_Format = "";
	m_Height = 1;
	m_fontHeight = 15;
	m_fontWith = 0;
	m_pbrHeadBk = new CBrush();

}

CHeaderCtrlClEX::~CHeaderCtrlClEX()
{
	if (m_pbrHeadBk)
	{
		m_pbrHeadBk->DeleteObject();
		delete m_pbrHeadBk;
		m_pbrHeadBk = NULL; 
	}

}


BEGIN_MESSAGE_MAP(CHeaderCtrlClEX, CHeaderCtrl)
	ON_WM_PAINT()
	ON_MESSAGE(HDM_LAYOUT, OnLayout)
END_MESSAGE_MAP()

// CHeaderCtrlCl ��Ϣ�������

void CHeaderCtrlClEX::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �����Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CHeaderCtrl::OnPaint()
	int nItem = GetItemCount();//�õ��м�����Ԫ 
	CString cstrTmp;
	for(int i = 0; i<nItem;i ++) 
	{ 
		CRect tRect;
		GetItemRect(i,&tRect);//�õ�Item�ĳߴ�
		CRect nRect(tRect);//�����ߴ絽�µ������� 

		tRect =nRect;
 		nRect.left++;//�����ָ��ߵĵط� 

 		DrawHeaderItemRect(dc,nRect);

		dc.SetBkMode(TRANSPARENT);
		CFont nFont ,* nOldFont; 
		dc.SetTextColor(m_color);

		nOldFont = dc.SelectObject(&nFont);

		UINT nFormat = 1;
		if (m_Format[i]=='0')
		{
			nFormat = DT_LEFT;
			tRect.left+=3;
		}
		else if (m_Format[i]=='1')
		{
			nFormat = DT_CENTER;
		}
		else if (m_Format[i]=='2')
		{
			nFormat = DT_RIGHT;
			tRect.right-=3;
		}
		TEXTMETRIC metric;
		dc.GetTextMetrics(&metric);
		int ofst = 0;
		ofst = tRect.Height() - metric.tmHeight;
		tRect.OffsetRect(0,ofst/2);
		dc.DrawText(m_HChar[i],&tRect,nFormat);
		dc.SelectObject(nOldFont); 
		nFont.DeleteObject(); //�ͷ����� 
	} 

	CRect rtRect;
	CRect clientRect;
	GetItemRect(nItem - 1,rtRect);
	GetClientRect(clientRect);
	rtRect.left = rtRect.right+1;
	rtRect.right = clientRect.right;
	DrawHeaderItemRect(dc,rtRect);
}

void CHeaderCtrlClEX::DrawHeaderItemRect(CDC& _dc, CRect& _rtDraw )
{
	if (m_pbrHeadBk)
	{
		CRect nRect(_rtDraw);
		nRect.right--;
		nRect.bottom -= 2;
		_dc.FillRect(&nRect,m_pbrHeadBk);
	}
}

LRESULT CHeaderCtrlClEX::OnLayout( WPARAM wParam, LPARAM lParam )
{
	LRESULT lResult = CHeaderCtrlClEX::DefWindowProc(HDM_LAYOUT, 0, lParam); 
	HD_LAYOUT &hdl = *( HD_LAYOUT * )lParam; 
	RECT *prc = hdl.prc; 
	WINDOWPOS *pwpos = hdl.pwpos; 

	//��ͷ�߶�Ϊԭ��1.5�������Ҫ��̬�޸ı�ͷ�߶ȵĻ�����1.5���һ��ȫ�ֱ��� 
	int nHeight = (int)(pwpos->cy * m_Height);
	pwpos->cy = nHeight; 
	prc->top = nHeight; 
	return lResult; 
}
