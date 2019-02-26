// VCAAdvParamWld.cpp : implementation file
//
#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAAdvParamWld.h"


// CLS_VCAAdvParamWld dialog

IMPLEMENT_DYNAMIC(CLS_VCAAdvParamWld, CDialog)

CLS_VCAAdvParamWld::CLS_VCAAdvParamWld(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventAdvParamBase(CLS_VCAAdvParamWld::IDD, pParent)
{

}

CLS_VCAAdvParamWld::~CLS_VCAAdvParamWld()
{
}

void CLS_VCAAdvParamWld::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_VCA_WLD_WAVEPERIOD, m_edtWavePeriod);
}


BEGIN_MESSAGE_MAP(CLS_VCAAdvParamWld, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_VCA_WLD_ADV_PARA_SET, &CLS_VCAAdvParamWld::OnBnClickedBtnVcaWldAdvParaSet)
END_MESSAGE_MAP()


// CLS_VCAAdvParamWld message handlers

BOOL CLS_VCAAdvParamWld::OnInitDialog()
{
	CLS_VCAEventAdvParamBase::OnInitDialog();

	UI_UpdateDialog();
	m_edtWavePeriod.SetLimitText(LEN_16);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAAdvParamWld::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventAdvParamBase::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		UI_UpdateSdkParam();
	}
}

void CLS_VCAAdvParamWld::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STC_WLD_WAVEPERIOD, IDS_VCA_WLD_WAVEPERIOD);
	SetDlgItemTextEx(IDC_BTN_VCA_WLD_ADV_PARA_SET, IDS_SET);
}

void CLS_VCAAdvParamWld::OnLanguageChanged()
{
	UI_UpdateDialog();
}

void CLS_VCAAdvParamWld::UI_UpdateSdkParam()
{
	CString cstrWaveTime;
	int iReturn = -1;
	int iWaveTime = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_WATER_STEADY_PERIOD,m_iChannelNO, &iWaveTime, sizeof(iWaveTime), &iReturn);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_GetDevConfig]NET_CLIENT_WATER_STEADY_PERIOD fail!");
	}
	else
	{
		cstrWaveTime.Format("%d",iWaveTime);
		m_edtWavePeriod.SetWindowText(cstrWaveTime);
		AddLog(LOG_TYPE_SUCC, "", "[NetClient_GetDevConfig]NET_CLIENT_WATER_STEADY_PERIOD success!");
	}
}

void CLS_VCAAdvParamWld::OnBnClickedBtnVcaWldAdvParaSet()
{
	int iWaveTime = GetDlgItemInt(IDC_EDT_VCA_WLD_WAVEPERIOD);
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_WATER_STEADY_PERIOD, m_iChannelNO, &iWaveTime, sizeof(iWaveTime));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[NetClient_SetDevConfig]NET_CLIENT_WATER_STEADY_PERIOD fail!");
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "[NetClient_SetDevConfig]NET_CLIENT_WATER_STEADY_PERIOD success!");
	}
}
