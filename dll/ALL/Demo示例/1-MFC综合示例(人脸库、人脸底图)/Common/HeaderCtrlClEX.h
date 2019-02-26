#pragma once

// CHeaderCtrlCl

class CHeaderCtrlClEX : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CHeaderCtrlClEX)

public:
	CHeaderCtrlClEX();
	virtual ~CHeaderCtrlClEX();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CStringArray m_HChar;
	CString m_Format; //表示对齐类型的整型数组,0表示左对齐，1表示中间对齐，2表示右对齐
	CBrush *m_pbrHeadBk;//列表头背景画刷
public:
	float m_Height;  //表头高度，这是倍数,
	int m_fontHeight; //字体高度
	int m_fontWith;   //字体宽度

	COLORREF m_color;//字体颜色
	LRESULT OnLayout( WPARAM wParam, LPARAM lParam );

	/*
	函数名称：DrawHeaderItemRect
	函数功能：绘制列表头矩形区域.
	输入参数:_dc 绘制所用DC,_rtDraw绘制区域,
	*/
	void DrawHeaderItemRect(CDC& _dc,CRect& _rtDraw);
};


