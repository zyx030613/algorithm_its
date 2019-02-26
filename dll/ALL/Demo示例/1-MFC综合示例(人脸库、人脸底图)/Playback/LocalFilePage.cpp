// LocalFileTab.cpp : implementation file
//

#include "stdafx.h"
#include "LocalFilePage.h"


// CLS_LocalFilePage dialog

IMPLEMENT_DYNAMIC(CLS_LocalFilePage, CDialog)

CLS_LocalFilePage::CLS_LocalFilePage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_LocalFilePage::IDD, pParent)
{

}

CLS_LocalFilePage::~CLS_LocalFilePage()
{

}

void CLS_LocalFilePage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_LocalFilePage, CLS_BasePage)
END_MESSAGE_MAP()


// CLS_LocalFilePage message handlers
