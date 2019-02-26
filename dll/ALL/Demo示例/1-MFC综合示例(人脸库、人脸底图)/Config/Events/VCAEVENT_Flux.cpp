// Config\Events\CLS_EVENT_FULX.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_Flux.h"


// CLS_EVENT_FULX dialog

IMPLEMENT_DYNAMIC(CLS_EVENT_FULX, CDialog)

CLS_EVENT_FULX::CLS_EVENT_FULX(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_EVENT_FULX::IDD, pParent)
{

}

CLS_EVENT_FULX::~CLS_EVENT_FULX()
{
}

void CLS_EVENT_FULX::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_DisplayRule, m_chkDisplayRule);
	DDX_Control(pDX, IDC_CHECK_DisplayState, m_chkDisplayState);
	DDX_Control(pDX, IDC_EDIT_PointNum, m_edtPointNum);
	DDX_Control(pDX, IDC_EDIT_Points, m_edtPoints);
}


BEGIN_MESSAGE_MAP(CLS_EVENT_FULX, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_FluxSet, &CLS_EVENT_FULX::OnBnClickedButtonFluxset)
	ON_BN_CLICKED(IDC_BUTTON_Draw, &CLS_EVENT_FULX::OnBnClickedButtonDraw)

	ON_BN_CLICKED(IDC_BUTTON_FluxStop, &CLS_EVENT_FULX::OnBnClickedButtonFluxstop)
	ON_BN_CLICKED(IDC_BUTTON_FluxStart, &CLS_EVENT_FULX::OnBnClickedButtonFluxstart)
END_MESSAGE_MAP()


// CLS_EVENT_FULX message handlers
BOOL CLS_EVENT_FULX::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();
	UpdateUIText();
	return TRUE; 
}

void CLS_EVENT_FULX::OnBnClickedButtonFluxset()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}

	int iRuleID = m_iRuleID;
	vca_TVCAParam *vp = m_pVcaParam;
	if (NULL == vp)
	{
		AddLog(LOG_TYPE_FAIL, "Error!!", "VCA param is NULL.");
		return;
	}
	memset(vp, 0, sizeof(vca_TVCAParam));

	vp->chnParam[m_iChannelNO].iRuleID = iRuleID;
	vca_TRuleParam* pRP = &vp->chnParam[m_iChannelNO].rule[iRuleID];
	pRP->iEventID = VCA_EVENT_FLUXSTATISTIC;
	vca_tFluxStatistic *tF = &(vp->chnParam[m_iChannelNO].rule[iRuleID].events.m_stFluxStatic);
	pRP->stDisplayParam.iDisplayRule = m_chkDisplayRule.GetCheck();
	pRP->stDisplayParam.iDisplayStat = m_chkDisplayState.GetCheck();

	int iPointNum = GetDlgItemInt(IDC_EDIT_PointNum);
	tF->stRegion.iPointNum = iPointNum;

	CString strPointStr;
	GetDlgItemText(IDC_EDIT_Points, strPointStr);
	GetPolyFromString(strPointStr, iPointNum, tF->stRegion);

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_SET_RULE12_FLUXSTATISTIC, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CVCAEventPage::OnBnClickedButtonCrowdset]VCASetConfig fluxstatistic error = %d", GetLastError());
	}
	else
	{
		RestartVCALib(m_iLogonID, m_iChannelNO);//重启智能库
	}
}

void CLS_EVENT_FULX::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	CleanText();
	if (bShow)
	{
		UpdatePageUI();
	}
}

void CLS_EVENT_FULX::OnLanguageChanged()
{
	UpdateUIText();
}

void CLS_EVENT_FULX::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}

	vca_TVCAParam *vp = m_pVcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));

	vp->iChannelID = m_iChannelNO;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_CHANNEL, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (0 == vp->chnParam[vp->iChannelID].iEnable )
		return;

	vp->chnParam[m_iChannelNO].iRuleID = m_iRuleID;
	int iCmd = -1;

	vp->chnParam[m_iChannelNO].rule[m_iRuleID].iEventID = VCA_EVENT_FLUXSTATISTIC;

	iCmd = VCA_CMD_GET_RULE12_FLUXSTATISTIC;
	iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet >= 0)
	{
		if (vp->chnParam[m_iChannelNO].rule[m_iRuleID].iEventID != VCA_EVENT_FLUXSTATISTIC)
		{
			return;
		}
		const vca_TRuleParam& tr = vp->chnParam[m_iChannelNO].rule[m_iRuleID];
		const vca_tFluxStatistic& tF = vp->chnParam[m_iChannelNO].rule[m_iRuleID].events.m_stFluxStatic;
		if (!tr.iValid || !tF.iValid)
			return;

		m_chkDisplayRule.SetCheck(tr.stDisplayParam.iDisplayRule);
		m_chkDisplayState.SetCheck(tr.stDisplayParam.iDisplayStat);

		SetDlgItemInt(IDC_EDIT_PointNum, tF.stRegion.iPointNum);
		CString szPointBuf;
		for (int i = 0; i < tF.stRegion.iPointNum; i ++ )
		{
			szPointBuf.AppendFormat("(%d,%d)", tF.stRegion.stPoints[i].iX, tF.stRegion.stPoints[i].iY);
		}
		m_edtPoints.SetWindowText(szPointBuf);

	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_VCAGetConfig fluxstatistic error = %d", GetLastError());
	}
}

void CLS_EVENT_FULX::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHECK_DisplayRule, IDS_VCA_DISPLAY_RULE);
	SetDlgItemTextEx(IDC_CHECK_DisplayState, IDS_VCA_DISPLAY_ALARMSTATUS);
	SetDlgItemTextEx(IDC_STATIC_VCA_POINTNUM, IDS_VCA_POINTNUM);
	SetDlgItemTextEx(IDC_STATIC_Points, IDS_VCA_POINTS);
	SetDlgItemTextEx(IDC_BUTTON_Draw, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BUTTON_PerimeterSet, IDS_SET);

	SetDlgItemTextEx(IDC_BUTTON_PerimeterStop, IDS_STOP);
	SetDlgItemTextEx(IDC_BUTTON_PerimeterStart, IDS_START);
}

void CLS_EVENT_FULX::CleanText()
{
	m_chkDisplayRule.SetCheck(0);
	m_chkDisplayState.SetCheck(0);
	m_edtPointNum.Clear();
	m_edtPoints.Clear();
	SetDlgItemText(IDC_EDIT_PointNum, "");
	SetDlgItemText(IDC_EDIT_Points, "");
}

void CLS_EVENT_FULX::OnBnClickedButtonDraw()
{
	if (NULL == m_pDlgVideoView)
	{
		m_pDlgVideoView = new CLS_VideoViewForDraw();
		if (NULL == m_pDlgVideoView)
		{
			return;
		}
	}
	/*以下代码为了能从draw对话框中取出相应参数*/
	m_pDlgVideoView->Init(m_iLogonID, m_iChannelNO, m_iStreamNO);
	m_pDlgVideoView->SetDrawType(DrawType_Flux);
	int iPointNum = 0;
	int iDirection = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	int iSetRet = m_pDlgVideoView->SetPointRegionParam(cPointBuf, &iPointNum, &iDirection);
	if (-1 == iSetRet)
	{
		return;
	}
	if (IDOK == m_pDlgVideoView->DoModal())
	{
		m_edtPoints.SetWindowText(cPointBuf);
		SetDlgItemInt(IDC_EDIT_PointNum, iPointNum);
	}
	else
	{
	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_EVENT_FULX::OnBnClickedButtonFluxstop()
{
	int iStatus = 0;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}

void CLS_EVENT_FULX::OnBnClickedButtonFluxstart()
{
	int iStatus = 1;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}
