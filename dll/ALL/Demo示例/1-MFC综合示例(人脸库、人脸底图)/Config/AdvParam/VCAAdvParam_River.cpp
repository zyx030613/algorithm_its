
#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAAdvParam_River.h"


// CLS_VCAAdvParam_River ¶Ô»°¿ò

IMPLEMENT_DYNAMIC(CLS_VCAAdvParam_River, CDialog)

CLS_VCAAdvParam_River::CLS_VCAAdvParam_River(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventAdvParamBase(CLS_VCAAdvParam_River::IDD, pParent)
{

}

CLS_VCAAdvParam_River::~CLS_VCAAdvParam_River()
{
}

void CLS_VCAAdvParam_River::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_VCAAdvParam_River, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADVPARAM_RIVER_SET, &CLS_VCAAdvParam_River::OnBnClickedBtnAdvparamRiverSet)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CLS_VCAAdvParam_River::OnInitDialog()
{
	CLS_VCAEventAdvParamBase::OnInitDialog();
	
	UI_UpdateDialog();
	UI_Update();

	return TRUE;
}

void CLS_VCAAdvParam_River::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventAdvParamBase::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		UI_Update();
	}

}

void CLS_VCAAdvParam_River::OnLanguageChanged()
{
	UI_UpdateDialog();
}

void CLS_VCAAdvParam_River::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STC_SAMPLE_NUM, IDS_VCA_SAMPLE_NUM);
	SetDlgItemTextEx(IDC_STC_THRESH_DIST, IDS_VCA_THRESH_DIST);	
	SetDlgItemTextEx(IDC_STC_THRESH_COUNT, IDS_VCA_THRESH_COUNT);	
	SetDlgItemTextEx(IDC_STC_THRESH_LIFE, IDS_VCA_HRESH_LIFE);
	SetDlgItemTextEx(IDC_BTN_ADVPARAM_RIVER_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_ADV_RIVER_NOTICE1, IDS_RANGE_0_100);
	SetDlgItemTextEx(IDC_STATIC_ADV_RIVER_NOTICE2, IDS_RANGE_0_100);
	SetDlgItemTextEx(IDC_STATIC_ADV_RIVER_NOTICE3, IDS_RANGE_0_100);
	SetDlgItemTextEx(IDC_STATIC_ADV_RIVER_NOTICE4, IDS_RANGE_0_100);
}

void CLS_VCAAdvParam_River::UI_Update()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}

	VCARiverAdvance st = {0};
	st.iBufSize = sizeof(st);
	st.iSceneID = m_iSceneID;
	int iCmd = VCA_CMD_RIVERADV	;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, &st, sizeof(st));
	if (iRet == 0)
	{
		SetDlgItemInt(IDC_EDT_SAMPLE_NUM, st.iFGSampleNum);
		SetDlgItemInt(IDC_EDT_THRESH_DIST, st.iFGDistThresh);
		SetDlgItemInt(IDC_EDT_THRESH_COUNT, st.iFGCountThresh);
		SetDlgItemInt(IDC_EDT_THRESH_LIFE, st.iFGLifeThresh);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_VCAGetConfig(%d,%d,%d)error=%d",m_iLogonID, iCmd,m_iChannelNO,GetLastError());
	}
}

void CLS_VCAAdvParam_River::OnBnClickedBtnAdvparamRiverSet()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}
	CheckValueLimits();
	VCARiverAdvance st = {0};
	st.iBufSize = sizeof(st);
	st.iSceneID = m_iSceneID;
	st.iFGSampleNum = GetDlgItemInt(IDC_EDT_SAMPLE_NUM);
	st.iFGDistThresh = GetDlgItemInt(IDC_EDT_THRESH_DIST);
	st.iFGCountThresh = GetDlgItemInt(IDC_EDT_THRESH_COUNT);
	st.iFGLifeThresh = GetDlgItemInt(IDC_EDT_THRESH_LIFE);

	int iCmd = VCA_CMD_RIVERADV	;
	int iRet = NetClient_VCASetConfig(m_iLogonID, iCmd, m_iChannelNO, &st, sizeof(st));
	if (iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_VCAGetConfig(%d,%d,%d)error=%d",m_iLogonID, iCmd,m_iChannelNO,GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_VCAGetConfig(%d,%d,%d)error=%d",m_iLogonID, iCmd,m_iChannelNO,GetLastError());
	}
}

void CLS_VCAAdvParam_River::CheckValueLimits()
{
	int iValue = -1;
	iValue = GetDlgItemInt(IDC_EDT_SAMPLE_NUM);
	if(iValue < 0)
	{
		SetDlgItemInt(IDC_EDT_SAMPLE_NUM, 0);
	}
	if(iValue > 100)
	{
		SetDlgItemInt(IDC_EDT_SAMPLE_NUM, 100);
	}
	iValue = GetDlgItemInt(IDC_EDT_THRESH_DIST);
	if(iValue < 1)
	{
		SetDlgItemInt(IDC_EDT_THRESH_DIST, 1);
	}
	if(iValue > 100)
	{
		SetDlgItemInt(IDC_EDT_THRESH_DIST, 100);
	}
	iValue = GetDlgItemInt(IDC_EDT_THRESH_COUNT);
	if(iValue < 1)
	{
		SetDlgItemInt(IDC_EDT_THRESH_COUNT, 1);
	}
	if(iValue > 100)
	{
		SetDlgItemInt(IDC_EDT_THRESH_COUNT, 100);
	}

	iValue = GetDlgItemInt(IDC_EDT_THRESH_LIFE);
	if(iValue < 1)
	{
		SetDlgItemInt(IDC_EDT_THRESH_LIFE, 1);
	}
	if(iValue > 100)
	{
		SetDlgItemInt(IDC_EDT_THRESH_LIFE, 100);
	}
}
