// VCAEVENT_Track.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_Track.h"


// CLS_VCAEVENT_Track dialog

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_Track, CDialog)

CLS_VCAEVENT_Track::CLS_VCAEVENT_Track(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_Track::IDD, pParent)
{

}

CLS_VCAEVENT_Track::~CLS_VCAEVENT_Track()
{
}

void CLS_VCAEVENT_Track::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PRESET, m_cboTrackNo);
	DDX_Control(pDX, IDC_COMBO_TargetCheck2, m_cboTrackSence);
	DDX_Control(pDX, IDC_EDIT_TrackRegoin, m_edtTrackRegion);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_Track, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_Draw, &CLS_VCAEVENT_Track::OnBnClickedButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_TRACKSET, &CLS_VCAEVENT_Track::OnBnClickedButtonTrackset)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_Call, &CLS_VCAEVENT_Track::OnBnClickedButtonCall)
	ON_BN_CLICKED(IDC_BUTTON_TRACKSTOP, &CLS_VCAEVENT_Track::OnBnClickedButtonTrackstop)
	ON_BN_CLICKED(IDC_BUTTON_TRACKSTART, &CLS_VCAEVENT_Track::OnBnClickedButtonTrackstart)
END_MESSAGE_MAP()


// CLS_VCAEVENT_Track message handlers

BOOL CLS_VCAEVENT_Track::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UpdateUIText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCAEVENT_Track::OnBnClickedButtonDraw()
{
	// TODO: Add your control notification handler code here
	if (NULL == m_pDlgVideoView)
	{
		m_pDlgVideoView = new CLS_VideoViewForDraw();
		if (NULL == m_pDlgVideoView)
		{
			return;
		}
		//m_pDlgVideoView->Create(IDD_DLG_VIDEOVIEW_DRAWLINES, this);
	}
	/*以下代码为了能从draw对话框中取出相应参数*/
	m_pDlgVideoView->Init(m_iLogonID, m_iChannelNO, m_iStreamNO);
	m_pDlgVideoView->SetDrawType(DrawType_track);
	int iPointNum = 0;
	int iDirection = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	int iSetRet = m_pDlgVideoView->SetPointRegionParam(cPointBuf, &iPointNum, &iDirection);
	if (-1 == iSetRet)
	{
		return;
	}
	/*******************/

	if (IDOK == m_pDlgVideoView->DoModal())
	{
		m_edtTrackRegion.SetWindowText(cPointBuf);
		SetDlgItemInt(IDC_EDIT_PointNum, iPointNum);
		SetDlgItemInt(IDC_EDIT_Dir, iDirection);
	}
	else
	{

	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_Track::OnBnClickedButtonTrackset()
{
	// TODO: Add your control notification handler code here
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
	pRP->iEventID = VCA_EVENT_TRACK;
	vca_tTrack& vt = vp->chnParam[m_iChannelNO].rule[iRuleID].events.m_stTrack;
	vt.m_iStartPreset = m_cboTrackNo.GetCurSel() /*+ 1*/;
	vt.m_iScene = m_cboTrackSence.GetCurSel() /*+ 1*/;

	int iPointNum = GetDlgItemInt(IDC_EDIT_TrackRegoin);
	vt.m_TrackRegion.iPointNum = iPointNum;
	CString strPointStr;
	GetDlgItemText(IDC_EDIT_TrackRegoin, strPointStr);
	vca_TLine stLineTmp = {0};
	GetPolyFromString(strPointStr, iPointNum, vt.m_TrackRegion);

	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_SET_RULE11_TRACK, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CVCAEventPage::OnBnClickedButtonEventset]TDVCASetConfig track error = %d", GetLastError());
	}
	else
	{
		//重启智能库
		RestartVCALib(m_iLogonID, m_iChannelNO);
	}
}

void CLS_VCAEVENT_Track::UpdatePageUI()
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

	int iRuleID = m_iRuleID;

	vp->iChannelID=m_iChannelNO;
	vp->chnParam[m_iChannelNO].iRuleID=iRuleID;

	int iCmd = VCA_CMD_GET_RULE11_TRACK;
	iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet >= 0)
	{
		if ( vp->chnParam[m_iChannelNO].rule[m_iRuleID].iEventID != VCA_EVENT_TRACK)
		{
			return;
		}
		const vca_tTrack & tTrack = vp->chnParam[m_iChannelNO].rule[iRuleID].events.m_stTrack;
		m_cboTrackNo.SetCurSel(tTrack.m_iStartPreset /*-1*/);
		m_cboTrackSence.SetCurSel(tTrack.m_iScene /*-1*/);

		SetDlgItemInt(IDC_EDIT_PointNum, tTrack.m_TrackRegion.iPointNum);
		int iPointNum = tTrack.m_TrackRegion.iPointNum;
		char cPointBuf[MAX_POINTBUF_LEN] = {0};
		CString strPoints;
		for (int i=0; i<iPointNum; i++)
		{
			sprintf_s(cPointBuf, "(%d:%d)", tTrack.m_TrackRegion.stPoints[i].iX, tTrack.m_TrackRegion.stPoints[i].iY);
			strPoints += cPointBuf;
		}
		SetDlgItemText(IDC_EDIT_TrackRegoin, strPoints);

		//edtTrackRegion->Text.sprintf("%d,%d,%d,%d,%d,%d,%d", tTrack.m_TrackRegion.stPoints[0].iX, tTrack.m_TrackRegion.stPoints[0].iY,
		//	tTrack.m_TrackRegion.stPoints[1].iX, tTrack.m_TrackRegion.stPoints[1].iY,
		//	tTrack.m_TrackRegion.stPoints[2].iX, tTrack.m_TrackRegion.stPoints[2].iY,
		//	tTrack.m_TrackRegion.stPoints[3].iX, tTrack.m_TrackRegion.stPoints[3].iY);

/*		int iWeekDay = cbbTrackWeek->ItemIndex;

		const NVS_SCHEDTIME *pTS = &(tTrack.m_timeSeg[iWeekDay][0]);
		dtpTrackTime1->Time = TDateTime(pTS->iStartHour, pTS->iStartMin, 0, 0);
		dtpTrackTime2->Time = TDateTime(pTS->iStopHour, pTS->iStopMin, 0, 0);
		chkTrack1->Checked = (pTS->iRecordMode != 0);

		pTS = &(tTrack.m_timeSeg[iWeekDay][1]);
		dtpTrackTime3->Time = TDateTime(pTS->iStartHour, pTS->iStartMin, 0, 0);
		dtpTrackTime4->Time = TDateTime(pTS->iStopHour, pTS->iStopMin, 0, 0);
		chkTrack2->Checked = (pTS->iRecordMode != 0);

		pTS = &(tTrack.m_timeSeg[iWeekDay][2]);
		dtpTrackTime5->Time = TDateTime(pTS->iStartHour, pTS->iStartMin, 0, 0);
		dtpTrackTime6->Time = TDateTime(pTS->iStopHour, pTS->iStopMin, 0, 0);
		chkTrack3->Checked = (pTS->iRecordMode != 0);

		pTS = &(tTrack.m_timeSeg[iWeekDay][3]);
		dtpTrackTime7->Time = TDateTime(pTS->iStartHour, pTS->iStartMin, 0, 0);
		dtpTrackTime8->Time = TDateTime(pTS->iStopHour, pTS->iStopMin, 0, 0);
		chkTrack4->Checked = (pTS->iRecordMode != 0);*/
	}
	else
	{
		//cbbTrackPreset->ItemIndex = 0;
		//cbbScene->ItemIndex = 0;
		//edtTrackRegion->Text = "";
	}
}

void CLS_VCAEVENT_Track::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	CleanText();
	if(bShow)
	{
		UpdatePageUI();
	}
}

void CLS_VCAEVENT_Track::UpdateUIText()
{
	SetDlgItemTextEx(IDC_STATIC_TRACKPRESET, IDS_VCA_TRACKPRESET);
	SetDlgItemTextEx(IDC_STATIC_Scene, IDS_VCA_TRACKSCENE);
	SetDlgItemTextEx(IDC_BUTTON_Call, IDS_VCA_TRACK_CALL);
	SetDlgItemTextEx(IDC_STATIC_VCA_POINTNUM, IDS_VCA_POINTNUM);
	SetDlgItemTextEx(IDC_STATIC_TrackRegoin, IDS_VCA_POINTS);
	SetDlgItemTextEx(IDC_BUTTON_Draw, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BUTTON_TRACKSET, IDS_SET);
	

	SetDlgItemTextEx(IDC_BUTTON_TRACKSTOP, IDS_STOP);
	SetDlgItemTextEx(IDC_BUTTON_TRACKSTART, IDS_START);

	CString strPreset;
	m_cboTrackNo.ResetContent();
	for (int i=0; i<8; i++)
	{
		strPreset.Format("%d", i+1);
		m_cboTrackNo.InsertString(i, strPreset);
	} 

	CString strScene[] = {GetTextEx(IDS_MNG_ADMIN_AUTO),GetTextEx(IDS_VCA_TRACK_SCENE_SMALL), GetTextEx(IDS_VCA_TRACK_SCENE_MID), GetTextEx(IDS_VCA_TRACK_SCENE_BIG)};
	m_cboTrackSence.ResetContent();
	for(int i=0; i<sizeof(strScene)/sizeof(CString); i++)
		m_cboTrackSence.InsertString(i, strScene[i]);
}

void CLS_VCAEVENT_Track::OnLanguageChanged()
{
	UpdateUIText();
}

void CLS_VCAEVENT_Track::OnBnClickedButtonCall()
{
	// TODO: Add your control notification handler code here
	int iPreset = m_cboTrackNo.GetCurSel() /*+ 1*/;
	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_CALL_TRACK_NO, m_iChannelNO, &iPreset, sizeof(int));
}

void CLS_VCAEVENT_Track::CleanText()
{
	m_cboTrackNo.SetCurSel(-1);
	m_cboTrackSence.SetCurSel(-1);
	m_edtTrackRegion.Clear();
	SetDlgItemText(IDC_STATIC_TrackRegoin, "");
}

void CLS_VCAEVENT_Track::OnBnClickedButtonTrackstop()
{
	int iStatus = 0;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}

void CLS_VCAEVENT_Track::OnBnClickedButtonTrackstart()
{
	int iStatus = 1;
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_VCA_SUSPEND, m_iChannelNO, &iStatus, sizeof(int));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig failed logonID(%d)", m_iLogonID);
	}
}
