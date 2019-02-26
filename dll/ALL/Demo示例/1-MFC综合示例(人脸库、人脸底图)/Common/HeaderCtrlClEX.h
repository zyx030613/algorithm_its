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
	CString m_Format; //��ʾ�������͵���������,0��ʾ����룬1��ʾ�м���룬2��ʾ�Ҷ���
	CBrush *m_pbrHeadBk;//�б�ͷ������ˢ
public:
	float m_Height;  //��ͷ�߶ȣ����Ǳ���,
	int m_fontHeight; //����߶�
	int m_fontWith;   //������

	COLORREF m_color;//������ɫ
	LRESULT OnLayout( WPARAM wParam, LPARAM lParam );

	/*
	�������ƣ�DrawHeaderItemRect
	�������ܣ������б�ͷ��������.
	�������:_dc ��������DC,_rtDraw��������,
	*/
	void DrawHeaderItemRect(CDC& _dc,CRect& _rtDraw);
};


