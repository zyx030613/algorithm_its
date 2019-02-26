// IOData.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "IOData.h"


// CLS_IOData 对话框

IMPLEMENT_DYNAMIC(CLS_IOData, CDialog)

CLS_IOData::CLS_IOData(CWnd* pParent /*=NULL*/)
: CLS_BasePage(CLS_IOData::IDD, pParent)
{
	m_iLogonId = -1;
	m_iChannelNo = -1;
}

CLS_IOData::~CLS_IOData()
{
}

void CLS_IOData::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonId = _iLogonID;
	m_iChannelNo = _iChannelNo;
}

void CLS_IOData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_DEV_TYPE, m_cboDevType);
	DDX_Control(pDX, IDC_CBO_IO_NO, m_cboIONo);
	DDX_Control(pDX, IDC_CBO_DEF_STA, m_cboDefaultState);
	DDX_Control(pDX, IDC_CBO_WORK_STA, m_cboWorkState);
	DDX_Control(pDX, IDC_EDT_DUTY_RADIO, m_edtDutyCycle);
	DDX_Control(pDX, IDC_EDT_LAST_TIME, m_edtDuration);
	DDX_Control(pDX, IDC_EDT_ADVANCED_TIME, m_LeadTime);
	DDX_Control(pDX, IDC_EDT_DOUBLING_FREQUENCY, m_edtDouFre);
}

BOOL CLS_IOData::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	int iI = 0;
	InsertString(m_cboDevType, 0, IDS_ITS_FLASHLIGHT);
	InsertString(m_cboDevType, 1, IDS_ITS_STROBELAMP);
	InsertString(m_cboDevType, 2, IDS_ITS_POLARIZER);
	InsertString(m_cboDefaultState, 0, IDS_ITS_PULSEWIDTH);
	InsertString(m_cboDefaultState, 1, IDS_ITS_ELECTRICAL_LEVEL);
	InsertString(m_cboWorkState, 0, IDS_ITS_WORK_LOW);
	InsertString(m_cboWorkState, 1, IDS_ITS_WORK_HIGH);
	for(iI = 1; iI <= 10; iI++)
	{
		CString cstrNum;
		cstrNum.Format("%d", iI);
		m_cboIONo.AddString(cstrNum);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLS_IOData::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}
void CLS_IOData::UI_UpdateDialog()
{
	//SetDlgItemTextEx(IDC_GP_OTHER_DEVICE_PARA, IDS_ITS_OTHER_DEVICE_PARA);
	SetDlgItemTextEx(IDC_GP_IO_OUT, IDS_ITS_IO_OUT);
	SetDlgItemTextEx(IDC_STC_IO_NO, IDS_ITS_IO_NO);
	SetDlgItemTextEx(IDC_STC_DEVICETYPE, IDS_ITS_DEVICE_TYPE);
	SetDlgItemTextEx(IDC_STC_DEFAULT_STATE, IDS_ITS_DEFAULT_STATE);
	SetDlgItemTextEx(IDC_STC_WORK_STATE, IDS_ITS_WORK_STATE);
	SetDlgItemTextEx(IDC_STC_DUTYFACTOR, IDS_ITS_DUTYFACTOR);
	SetDlgItemTextEx(IDC_STC_DURATION, IDS_ITS_DURATION);
	SetDlgItemTextEx(IDC_STC_TIME_IN_ADVANCE, IDS_ITS_TIME_IN_ADVANCE);
	SetDlgItemTextEx(IDC_STC_DOUBLING_FREQUENCY, IDS_ITS_DOUBLING_FREQUENCY);
	SetDlgItemTextEx(IDC_BTN_SET, IDS_ITS_IO_SET);

	InsertString(m_cboDevType, 0, IDS_ITS_FLASHLIGHT);
	InsertString(m_cboDevType, 1, IDS_ITS_STROBELAMP);
	InsertString(m_cboDefaultState, 0, IDS_ITS_PULSEWIDTH);
	InsertString(m_cboDefaultState, 1, IDS_ITS_ELECTRICAL_LEVEL);
	InsertString(m_cboWorkState, 0, IDS_ITS_WORK_HIGH);
	InsertString(m_cboWorkState, 1, IDS_ITS_WORK_LOW);
}


BEGIN_MESSAGE_MAP(CLS_IOData, CDialog)
	ON_BN_CLICKED(IDC_BTN_SET, &CLS_IOData::OnBnClickedBtnSet)
	ON_CBN_SELCHANGE(IDC_CBO_IO_NO, &CLS_IOData::OnCbnSelchangeCboIoNo)
END_MESSAGE_MAP()


// CLS_IOData 消息处理程序

void CLS_IOData::OnBnClickedBtnSet()
{
	TITS_IOLinkInfo tIOdata;
	memset(&tIOdata, 0, sizeof(TITS_IOLinkInfo));
	int iRet = -1;
	tIOdata.m_iIONo = m_cboIONo.GetCurSel();
	tIOdata.m_iLinkDevice = m_cboDevType.GetCurSel();
	tIOdata.m_iDefaultState = m_cboDefaultState.GetCurSel();
	tIOdata.m_iWorkState = m_cboWorkState.GetCurSel();
	tIOdata.m_iDutyCycle = GetDlgItemInt(IDC_EDT_DUTY_RADIO);
	tIOdata.m_iAheadTime = GetDlgItemInt(IDC_EDT_ADVANCED_TIME);
	tIOdata.m_iFrequency = GetDlgItemInt(IDC_EDT_DOUBLING_FREQUENCY);
	tIOdata.m_iDevicePulse = GetDlgItemInt(IDC_EDT_LAST_TIME);
	iRet = NetClient_SetDevConfig(m_iLogonId, NET_CLIENT_IO_LINK_INFO, m_iChannelNo, &tIOdata, sizeof(TITS_IOLinkInfo));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_LIGHTINFO_CMD_GET][NET_CLIENT_IO_LINK_INFO] (%d, %d)",m_iLogonId, m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_LIGHTINFO_CMD_GET] (%d, %d),error(%d)",m_iLogonId, m_iChannelNo, GetLastError());
	}
}

void CLS_IOData::OnCbnSelchangeCboIoNo()
{
	TITS_IOLinkInfo tGetIOdata = {-1};
	int iRet = -1;
	int iReturn = -1;
	tGetIOdata.m_iIONo = m_cboIONo.GetCurSel();
	iRet = NetClient_GetDevConfig(m_iLogonId, NET_CLIENT_IO_LINK_INFO, m_iChannelNo, &tGetIOdata, sizeof(TITS_IOLinkInfo), &iReturn);
	if (0 == iRet)
	{
		m_cboDevType.SetCurSel(tGetIOdata.m_iLinkDevice);
		m_cboDefaultState.SetCurSel(tGetIOdata.m_iDefaultState);
		m_cboWorkState.SetCurSel(tGetIOdata.m_iWorkState);
		SetDlgItemInt(IDC_EDT_DUTY_RADIO,tGetIOdata.m_iDutyCycle);
		
		SetDlgItemInt(IDC_EDT_LAST_TIME,tGetIOdata.m_iDevicePulse);
		SetDlgItemInt(IDC_EDT_ADVANCED_TIME,tGetIOdata.m_iAheadTime);
		SetDlgItemInt(IDC_EDT_DOUBLING_FREQUENCY,tGetIOdata.m_iFrequency);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_IO_LINK_INFO] (%d, %d)",m_iLogonId, m_iChannelNo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_IO_LINK_INFO] (%d, %d),error(%d)",m_iLogonId, m_iChannelNo, GetLastError());
	}
}
