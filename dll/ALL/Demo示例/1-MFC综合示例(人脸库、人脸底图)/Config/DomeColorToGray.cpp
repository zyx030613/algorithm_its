// DomeColorToGray.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "DomeColorToGray.h"


// CLS_DomeColorToGray 对话框

IMPLEMENT_DYNAMIC(CLS_DomeColorToGray, CDialog)

CLS_DomeColorToGray::CLS_DomeColorToGray(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DomeColorToGray::IDD, pParent)
{

}

CLS_DomeColorToGray::~CLS_DomeColorToGray()
{
}

void CLS_DomeColorToGray::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_COLOR2GRAY_TYPE, m_cboType);
	DDX_Control(pDX, IDC_SLD_COLOR2GRAY_DAY_LIGHT, m_sldDayLight);
	DDX_Control(pDX, IDC_SLD_COLOR2GRAY_NIGHT_LIGHT, m_sldNightLight);
	DDX_Control(pDX, IDC_EDT_GRAY2COLOR_DELAY, m_edtGray2ColorDelay);
	DDX_Control(pDX, IDC_EDT_COLOR2GRAY_DELAY, m_edtColor2GrayDelay);
	DDX_Control(pDX, IDC_DTP_GRAY2COLOR_TIME, m_dtpGray2ColorTime);
	DDX_Control(pDX, IDC_DTP_COLOR2GRAY_TIME, m_dtpColor2GrayTime);
}


BEGIN_MESSAGE_MAP(CLS_DomeColorToGray, CDialog)
	ON_BN_CLICKED(IDC_BTN_COLOR2GRAY_SET, &CLS_DomeColorToGray::OnBnClickedBtnColor2graySet)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CLS_DomeColorToGray 消息处理程序


BOOL CLS_DomeColorToGray::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLS_DomeColorToGray::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
}

void CLS_DomeColorToGray::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;

	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo;
	}

	if (_iStreamNo < 0)
	{
		m_iStreamNO = 0;
	}
	else
	{
		m_iStreamNO =  _iStreamNo;
	}

	UI_UpdateDialogText();
}

void CLS_DomeColorToGray::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialogText();
}

void CLS_DomeColorToGray::UI_UpdateDialogText()
{
	SetDlgItemTextEx(IDC_STC_COLOR2GRAY_TYPE, IDS_DOME_COLOR2GRAY_TYPE);
	SetDlgItemTextEx(IDC_STC_COLOR2GRAY_DAY_LIGHT, IDS_DOME_DAY_LIGHT);
	SetDlgItemTextEx(IDC_STC_GRAY2COLOR_DELAY, IDS_DOME_GRAY2COLOR_DELAY);
	SetDlgItemTextEx(IDC_STC_COLOR2GRAY_DELAY, IDS_DOME_COLOR2GRAY_DELAY);
	SetDlgItemTextEx(IDC_STC_GRAY2COLOR_TIME, IDS_DOME_GRAY2COLOR_TIME);
	SetDlgItemTextEx(IDC_STC_COLOR2GRAY_TIME, IDS_DOME_COLOR2GRAY_TIME);
	SetDlgItemTextEx(IDC_BTN_COLOR2GRAY_SET, IDS_SET);

	CString cstrType[] = {GetTextEx(IDS_CONFIG_INNER_SYN),
		GetTextEx(IDS_CONFIG_BLACK_WHITE)};

}


void CLS_DomeColorToGray::OnBnClickedBtnColor2graySet()
{
	// TODO: 在此添加控件通知处理程序代码
}

