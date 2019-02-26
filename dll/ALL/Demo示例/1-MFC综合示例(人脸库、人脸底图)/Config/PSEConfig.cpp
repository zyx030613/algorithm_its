// D:\SDK_DEMO\NetClientDemo\Config\PSEConfig.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "PSEConfig.h"


// PSEConfig dialog

IMPLEMENT_DYNAMIC(PSEConfig, CDialog)

PSEConfig::PSEConfig(CWnd* pParent /*=NULL*/)
	: CDialog(PSEConfig::IDD, pParent)
{

}

PSEConfig::~PSEConfig()
{
}

void PSEConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PSEConfig, CDialog)
END_MESSAGE_MAP()


// PSEConfig message handlers
