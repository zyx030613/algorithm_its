// VCATargetPage.cpp : implementation file
//

#include "stdafx.h"
#include "VCATargetPage.h"

#define LEN_2		2		//定义长度

// CLS_VCATargetPage dialog

//	VIDEOSIZE 列表中对应的分辨率数值
const int g_iArrVCAVideoSz[10] = {0, 2};

IMPLEMENT_DYNAMIC(CLS_VCATargetPage, CDialog)

CLS_VCATargetPage::CLS_VCATargetPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_VCATargetPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNO = 0;
	m_iStreamNO = 0;
}

CLS_VCATargetPage::~CLS_VCATargetPage()
{
}

void CLS_VCATargetPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_VCA_VIDEOSZ, m_cboVCAVideoSz);
	DDX_Control(pDX, IDC_CHECK_VCA_DISPLAY_TARGET, m_chkDisplayTarget);
	DDX_Control(pDX, IDC_COMBO_VCA_TARGETCOLOR, m_cboTargetColor);
	DDX_Control(pDX, IDC_CHECK_VCA_DISPLAY_TRACE, m_chkDisplayTrace);
	DDX_Control(pDX, IDC_COMBO_VCA_ALARM_COLOR, m_cboAlarmColor);
	DDX_Control(pDX, IDC_EDIT_TRACE_LEN, m_edtTagetTraceLen);
	DDX_Control(pDX, IDC_COMBO_VCA_ENABLE, m_cboEnable);
	DDX_Control(pDX, IDC_CBO_VCA_SENSITIVITY, m_cboSensitivity);
}


BEGIN_MESSAGE_MAP(CLS_VCATargetPage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_VCA_TARGET_SET, &CLS_VCATargetPage::OnBnClickedButtonVcaTargetSet)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_COMBO_VCA_VIDEOSZ, &CLS_VCATargetPage::OnCbnSelchangeComboVcaVideosz)
	ON_CBN_SELCHANGE(IDC_COMBO_VCA_ENABLE, &CLS_VCATargetPage::OnCbnSelchangeComboVcaEnable)
	ON_BN_CLICKED(IDC_CHECK_VCA_DISPLAY_TRACE, &CLS_VCATargetPage::OnBnClickedCheckVcaDisplayTrace)
END_MESSAGE_MAP()


// CLS_VCATargetPage message handlers
void CLS_VCATargetPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	m_iChannelNO = _iChannelNo;
	m_iStreamNO = _iStreamNo;

	UpdatePageUI();
}

void CLS_VCATargetPage::OnLanguageChanged( int _iLanguage )
{
	UpdateUIText();
	UpdatePageUI();
}

void CLS_VCATargetPage::OnMainNotify( int _iLogonID,int _wParam, void* _iLParam, void* _iUser)
{

}

int CLS_VCATargetPage::RestartVCALib( int _iLogonID, int _iChannel /*= -1*/ )
{
	int iRet = -1;
	if (_iChannel == -1)
	{
		iRet = NetClient_VCARestart(_iLogonID);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","CLS_VCATargetPage::NetClient_VCARestart (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
		}
		else
		{
			AddLog(LOG_TYPE_SUCC,"","CLS_VCATargetPage::NetClient_VCARestart (%d, %d)", m_iLogonID, m_iChannelNO);
		}
		return iRet;
	}

	iRet = NetClient_VCARestartEx(_iLogonID, _iChannel);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCATargetPage::NetClient_VCARestartEx (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCATargetPage::NetClient_VCARestartEx (%d, %d)", m_iLogonID, m_iChannelNO);
	}
	return iRet;
}

BOOL CLS_VCATargetPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_pVcaParam = new vca_TVCAParam();
	memset(m_pVcaParam, 0, sizeof(vca_TVCAParam));
	ASSERT(m_pVcaParam != NULL);

	UpdateUIText();
	m_cboVCAVideoSz.SetCurSel(0);
	m_cboTargetColor.SetCurSel(0);
	m_cboAlarmColor.SetCurSel(0);	//目标的报警颜色
	m_cboEnable.SetCurSel(0);
	m_edtTagetTraceLen.SetLimitText(LEN_2);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VCATargetPage::OnBnClickedButtonVcaTargetSet()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}

	vca_TVCAParam *vp = m_pVcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));

	vp->iChannelID = m_iChannelNO;
	vca_TConfig &config = vp->chnParam[m_iChannelNO].config;
	
	//设参...
	config.iDisplayTarget = m_chkDisplayTarget.GetCheck();
	config.iDisplayTrace = m_chkDisplayTrace.GetCheck();
	config.iTargetColor = m_cboTargetColor.GetCurSel()+1;
	config.iTargetAlarmColor = m_cboAlarmColor.GetCurSel()+1;
	//config.iTraceLength = m_iTraceLen;
	config.iTraceLength = GetDlgItemInt(IDC_EDIT_TRACE_LEN);
	int iRet = -1;
	
	iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_SET_TARGET_PARAM, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCATargetPage::NetClient_VCASetConfig[VCA_CMD_SET_TARGET_PARAM] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCATargetPage::NetClient_VCASetConfig[VCA_CMD_SET_TARGET_PARAM] (%d, %d)", m_iLogonID, m_iChannelNO);
	}

	vp->chnParam[m_iChannelNO].advParam.iSensitivity = m_cboSensitivity.GetCurSel();

	iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_SET_ADVANCE_PARAM, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCATargetPage::NetClient_VCASetConfig[VCA_CMD_SET_ADVANCE_PARAM] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCATargetPage::NetClient_VCASetConfig[VCA_CMD_SET_ADVANCE_PARAM] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}

void CLS_VCATargetPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	if (bShow)
	{
		UpdatePageUI();
	}
}

void CLS_VCATargetPage::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}

	vca_TVCAParam *vp = m_pVcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));

	if(IsDigistChannel(m_iChannelNO))
	{
		if (m_cboEnable.GetCount() == 2)
		{
			m_cboEnable.AddString(GetTextEx(IDS_VCA_ENABLE_REMOTE));
		}
	}
	else
	{
		if (m_cboEnable.GetCount() == 3)
		{
			m_cboEnable.DeleteString(2);
		}
	}

	vp->iChannelID = m_iChannelNO;
	int iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_CHANNEL_ENABLE, m_iChannelNO, vp, sizeof(vca_TVCAParam));

	if (iRet >= 0)
	{
		m_cboEnable.SetCurSel(vp->chnParam[m_iChannelNO].iEnable);
	}
	else
	{
		m_cboEnable.SetCurSel(0);
	}

	int iCmd = VCA_CMD_GET_VIDEOSIZE;
	vp->iChannelID = m_iChannelNO;
	ASSERT(NetClient_VCAGetConfig);
	iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if(iRet >= 0)
	{
		//m_iChannelNO = -1时调会出错
		if (vp->chnParam[m_iChannelNO].config.iVideoSize == 0)
		{
			m_cboVCAVideoSz.SetCurSel(0);
		}
		else if (vp->chnParam[m_iChannelNO].config.iVideoSize == 2)
		{
			m_cboVCAVideoSz.SetCurSel(1);
		}

		AddLog(LOG_TYPE_SUCC,"","CLS_VCATargetPage::NetClient_VCAGetConfig[VCA_CMD_GET_VIDEOSIZE] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCATargetPage::NetClient_VCAGetConfig[VCA_CMD_GET_VIDEOSIZE] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}

	iCmd = VCA_CMD_GET_TARGET_PARAM;
	iRet = NetClient_VCAGetConfig(m_iLogonID, iCmd, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet >= 0)
	{
		vca_TConfig &config = vp->chnParam[m_iChannelNO].config;
		m_chkDisplayTrace.SetCheck(config.iDisplayTrace);
		if (1 == config.iDisplayTrace)
		{
			m_chkDisplayTarget.SetCheck(BST_CHECKED);
			GetDlgItem(IDC_CHECK_VCA_DISPLAY_TARGET)->EnableWindow(FALSE);	
		}
		else if (0 == config.iDisplayTrace)
		{
			GetDlgItem(IDC_CHECK_VCA_DISPLAY_TARGET)->EnableWindow(TRUE);
		}

		m_cboTargetColor.SetCurSel(config.iTargetColor-1);
		m_cboAlarmColor.SetCurSel(config.iTargetAlarmColor-1);
		SetDlgItemInt(IDC_EDIT_TRACE_LEN, config.iTraceLength);

		AddLog(LOG_TYPE_SUCC,"","CLS_VCATargetPage::NetClient_VCAGetConfig[VCA_CMD_GET_TARGET_PARAM] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCATargetPage::NetClient_VCAGetConfig[VCA_CMD_GET_TARGET_PARAM] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}

	
	iRet = NetClient_VCAGetConfig(m_iLogonID, VCA_CMD_GET_ADVANCE_PARAM, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet >= 0)
	{
		int iSensi = vp->chnParam[m_iChannelNO].advParam.iSensitivity;
		m_cboSensitivity.SetCurSel(iSensi);

		AddLog(LOG_TYPE_SUCC,"","CLS_VCATargetPage::NetClient_VCAGetConfig[VCA_CMD_GET_ADVANCE_PARAM] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCATargetPage::NetClient_VCAGetConfig[VCA_CMD_GET_ADVANCE_PARAM] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
}

void CLS_VCATargetPage::OnCbnSelchangeComboVcaVideosz()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		return;
	}

	vca_TVCAParam *vp = m_pVcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));

	vp->iChannelID = m_iChannelNO;
	vca_TConfig &config = vp->chnParam[m_iChannelNO].config;

	int iIndex = m_cboVCAVideoSz.GetCurSel();
	if (iIndex >= 0)
	{
		vp->chnParam[m_iChannelNO].config.iVideoSize = g_iArrVCAVideoSz[iIndex];
	}

	int iRet = -1;
	ASSERT(NetClient_VCASetConfig);
	iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_SET_VIDEOSIZE, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCATargetPage::NetClient_VCASetConfig[VCA_CMD_SET_VIDEOSIZE] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCATargetPage::NetClient_VCASetConfig[VCA_CMD_SET_VIDEOSIZE] (%d, %d)", m_iLogonID, m_iChannelNO);
	}

	//重启智能库
	iRet = RestartVCALib(m_iLogonID, m_iChannelNO);
	if (iRet < 0)
	{
		TRACE("[CVCATargetPage::OnSetVCAVideoSize]TDVCRestart error = %d", GetLastError());
	}
}

void CLS_VCATargetPage::UpdateUIText()
{
	SetDlgItemTextEx(IDC_STATIC_VCA_VIDEOSZ, IDS_VCA_VIDEOSIZE);
	SetDlgItemTextEx(IDC_CHECK_VCA_DISPLAY_TARGET, IDS_VCA_SHOWTARGET);
	SetDlgItemTextEx(IDC_CHECK_VCA_DISPLAY_TRACE, IDS_VCA_SHOWTRACE);
	SetDlgItemTextEx(IDC_STATIC_TARGET_COLOR, IDS_VCA_TARGETCOLOR);
	SetDlgItemTextEx(IDC_STATIC_VCA_ALARMCOLOR, IDS_VCA_TAR_ALARMCOLOR);
	SetDlgItemTextEx(IDC_STATIC_TRACE_LEN, IDS_VCA_TAR_TRACELEN);
	SetDlgItemTextEx(IDC_STC_VCA_SENSITIVITY, IDS_ITS_SENSITY);

	const CString strColor[] = {GetTextEx(IDS_VCA_COL_RED), GetTextEx(IDS_VCA_COL_GREEN), GetTextEx(IDS_VCA_COL_YELLOW), 
		GetTextEx(IDS_VCA_COL_BLUE), GetTextEx(IDS_VCA_COL_MAGENTA), GetTextEx(IDS_VCA_COL_CYAN), GetTextEx(IDS_VCA_COL_BLACK), GetTextEx(IDS_VCA_COL_WHITE)};
	m_cboAlarmColor.ResetContent();
	m_cboTargetColor.ResetContent();
	for (int i=0; i<sizeof(strColor)/sizeof(CString); i++)
	{
		m_cboAlarmColor.InsertString(i, strColor[i]);
		m_cboTargetColor.InsertString(i, strColor[i]);
	}

	const CString strVideoSz[] = {"QCIF", "CIF"};
	m_cboVCAVideoSz.ResetContent();
	for (int i=0; i<sizeof(strVideoSz)/sizeof(CString); i++)
	{
		m_cboVCAVideoSz.InsertString(i, strVideoSz[i]);
	}

	SetDlgItemTextEx(IDC_BUTTON_VCA_TARGET_SET, IDS_SET);

	const CString strEntype[] = {
		GetTextEx(IDS_VCA_DISABLE),
		GetTextEx(IDS_VCA_ENABLE_LOCAL),
		GetTextEx(IDS_VCA_ENABLE_REMOTE),
	};
	m_cboEnable.ResetContent();
	for (int i=0; i<sizeof(strEntype)/sizeof(CString); i++)
	{
		m_cboEnable.InsertString(i, strEntype[i]);
	}

	m_cboSensitivity.ResetContent();
	const CString cstSensi[] = {GetTextEx(IDS_ITS_LOW),GetTextEx(IDS_ITS_MIDDLE),GetTextEx(IDS_ITS_HIGH)};
	for(int i = 0; i < sizeof(cstSensi)/sizeof(CString); i++)
	{
		m_cboSensitivity.InsertString(i, cstSensi[i]);
	}
	m_cboSensitivity.SetCurSel(0);
}

void CLS_VCATargetPage::OnCbnSelchangeComboVcaEnable()
{
	if (m_iLogonID<0 || m_iChannelNO<0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d), channel no(%d)", m_iLogonID, m_iChannelNO);
		return;
	}
	int iEnable = m_cboEnable.GetCurSel();
	vca_TVCAParam *vp = m_pVcaParam;
	memset(vp, 0, sizeof(vca_TVCAParam));
	vp->iChannelID = m_iChannelNO;
	vp->iEnable = iEnable;
	vp->chnParam[m_iChannelNO].iEnable = iEnable;
	int iRet = NetClient_VCASetConfig(m_iLogonID, VCA_CMD_SET_CHANNEL_ENABLE, m_iChannelNO, vp, sizeof(vca_TVCAParam));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCATargetPage::NetClient_VCASetConfig[VCA_CMD_SET_CHANNEL_ENABLE] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCATargetPage::NetClient_VCASetConfig[VCA_CMD_SET_CHANNEL_ENABLE] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}

bool CLS_VCATargetPage::IsDigistChannel(int _iChannelNO)
{
	int iChannelType = 0;
	//获取通道类型： 1，本地模拟通道；  2，数字通道；3，合成通道
	if(NetClient_GetChannelProperty(m_iLogonID, _iChannelNO, GENERAL_CMD_GET_CHANNEL_TYPE,
		&iChannelType,sizeof(iChannelType)) == 0 && iChannelType == CHANNEL_TYPE_DIGITAL)
	{
		return true;
	}
	return false;
}

void CLS_VCATargetPage::OnBnClickedCheckVcaDisplayTrace()
{
	if(BST_CHECKED == m_chkDisplayTrace.GetCheck())
	{
		m_chkDisplayTarget.SetCheck(BST_CHECKED);
		GetDlgItem(IDC_CHECK_VCA_DISPLAY_TARGET)->EnableWindow(FALSE);	
	}
	else if(BST_UNCHECKED == m_chkDisplayTrace.GetCheck())
	{
		GetDlgItem(IDC_CHECK_VCA_DISPLAY_TARGET)->EnableWindow(TRUE);
	}
}
