
// ITSFaceSnapDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CITSFaceSnapDemoApp:
// �йش����ʵ�֣������ ITSFaceSnapDemo.cpp
//

class CITSFaceSnapDemoApp : public CWinAppEx
{
public:
	CITSFaceSnapDemoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CITSFaceSnapDemoApp theApp;