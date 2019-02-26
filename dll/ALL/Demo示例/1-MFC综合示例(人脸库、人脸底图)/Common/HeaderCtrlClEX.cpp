// HeaderCtrlCl.cpp : 实现文件
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

// CHeaderCtrlCl 消息处理程序

void CHeaderCtrlClEX::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 添加消息处理程序代码
	// 不为绘图消息调用 CHeaderCtrl::OnPaint()
	int nItem = GetItemCount();//得到有几个单元 
	CString cstrTmp;
	for(int i = 0; i<nItem;i ++) 
	{ 
		CRect tRect;
		GetItemRect(i,&tRect);//得到Item的尺寸
		CRect nRect(tRect);//拷贝尺寸到新的容器中 

		tRect =nRect;
 		nRect.left++;//留出分割线的地方 

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
		nFont.DeleteObject(); //释放字体 
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

	//表头高度为原来1.5倍，如果要动态修改表头高度的话，将1.5设成一个全局变量 
	int nHeight = (int)(pwpos->cy * m_Height);
	pwpos->cy = nHeight; 
	prc->top = nHeight; 
	return lResult; 
}
