
#include "stdafx.h"
#include "NetClientDemo.h"
#include "LinkDevSetEdit.h"
#include "..\\Include\\NVSSDK_INTERFACE.h"
using namespace NVSSDK_INTERFACE;

// CLS_LinkDevSetEdit 对话框

IMPLEMENT_DYNAMIC(CLS_LinkDevSetEdit, CDialog)

CLS_LinkDevSetEdit::CLS_LinkDevSetEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CLS_LinkDevSetEdit::IDD, pParent)
{
	for (int i=0;i<DLGNUM;i++)
	{
		m_clsDlg[i] = NULL;
	}
	memset(&m_LinkInfo,0,sizeof(m_LinkInfo));
	m_LinkInfo.iSize = sizeof(AlarmInLink);
}

CLS_LinkDevSetEdit::~CLS_LinkDevSetEdit()
{
	for (int i=0;i<DLGNUM;i++)
	{
		m_clsDlg[i] = NULL;
		if (NULL != m_clsDlg[i])
		{
			delete m_clsDlg[i];
			m_clsDlg[i] = NULL;
		}
	}
}

void CLS_LinkDevSetEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_ALARM_TYPE, m_cboAlarmType);
	DDX_Control(pDX, IDC_CBO_LINK_TYPE, m_cboLinkType);
	DDX_Control(pDX, IDC_EDT_ACTION_NAME, m_edtActionName);
	DDX_Control(pDX, IDC_CBO_RECOVER_TYPE, m_cboRecoverType);
	DDX_Control(pDX, IDC_EDT_LINK_TIME, m_edtLinkTime);
	DDX_Control(pDX, IDC_SPIN_LINK_TIME, m_spinLinkTime);
}


BEGIN_MESSAGE_MAP(CLS_LinkDevSetEdit, CDialog)
	ON_BN_CLICKED(IDC_BTN_LINK_SURE, &CLS_LinkDevSetEdit::OnBnClickedBtnLinkSure)
	ON_CBN_SELCHANGE(IDC_CBO_LINK_TYPE, &CLS_LinkDevSetEdit::OnCbnSelchangeCboLinkType)
	ON_CBN_SELCHANGE(IDC_CBO_ALARM_TYPE, &CLS_LinkDevSetEdit::OnCbnSelchangeCboAlarmType)
END_MESSAGE_MAP()


// CLS_LinkDevSetEdit 消息处理程序

BOOL CLS_LinkDevSetEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemTextEx(IDC_STC_ALARM_TYPE, IDS_CONFIG_LINK_ALARM_TYPE);
	SetDlgItemTextEx(IDC_STC_LINK_TYPE, IDS_CONFIG_LINK_TYPE);
	SetDlgItemTextEx(IDC_STC_ACTION_NAME, IDS_CONFIG_LINK_ACTION_NAME);
	SetDlgItemTextEx(IDC_STC_RECOVER_TYPR, IDS_CONFIG_LINK_RECOVER_TYPE);
	SetDlgItemTextEx(IDC_STC_LINK_TIME, IDS_CONFIG_LINK_TIME);
	SetDlgItemTextEx(IDC_BTN_LINK_SURE, IDS_CONFIG_LINK_SURE);

	InitDlg();

	UpdateUI();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLS_LinkDevSetEdit::InitDlg()
{
	CRect rc;
	GetDlgItem(IDC_PIC_LINK_TYPE)->GetWindowRect(rc);
	ScreenToClient(rc);

	m_clsDlg[0]= new CLS_LinkOut(m_iLogonID, this);
	m_clsDlg[0]->Create(IDD_DLG_CFG_LINK_OUT,this);

// 	m_clsDlg[1] = new CLS_LinkOSD();
// 	m_clsDlg[1]->Create(IDD_DLG_CFG_LINK_OSD,this);

	m_clsDlg[1] = new CLS_LinkBSF(m_iLogonID, this);
	m_clsDlg[1]->Create(IDD_DLG_CFG_LINK_BSF,this);

	for (int i=0;i<DLGNUM;i++)
	{
		m_clsDlg[i]->MoveWindow(rc);
		m_clsDlg[i]->ShowWindow(SW_HIDE);
	}
}

BOOL CLS_LinkDevSetEdit::UpdateUI()
{
	//报警类型
	switch (m_iDevType)
	{
	case ALARM_INTERFACE_TYPE_SWITCH:
		//m_cboAlarmType.AddString(GetTextEx(IDS_CONFIG_ALARM));
		//m_cboAlarmType.AddString(GetTextEx(IDS_CONFIG_LINK_ALARM_CLEAR));
		break;
	case ALARM_INTERFACE_TYPE_ANALOG:
		m_cboAlarmType.AddString(GetTextEx(IDS_CONFIG_ALARM_UPPER));
		m_cboAlarmType.AddString(GetTextEx(IDS_CONFIG_ALARM_LOWER));
		m_cboAlarmType.AddString(GetTextEx(IDS_CONFIG_ALARM_UPPER_CLEAR));
		m_cboAlarmType.AddString(GetTextEx(IDS_CONFIG_ALARM_LOWER_CLEAR));
		break;
	case ALARM_INTERFACE_TYPE_COM:
		m_cboAlarmType.AddString(GetTextEx(IDS_CONFIG_ALARM_UPPER_TMP));
		m_cboAlarmType.AddString(GetTextEx(IDS_CONFIG_ALARM_LOWER_TMP));
		m_cboAlarmType.AddString(GetTextEx(IDS_CONFIG_ALARM_UPPER_HMD));
		m_cboAlarmType.AddString(GetTextEx(IDS_CONFIG_ALARM_LOWER_HMD));
		m_cboAlarmType.AddString(GetTextEx(IDS_CONFIG_ALARM_UPPER_TMP_CLEAR));
		m_cboAlarmType.AddString(GetTextEx(IDS_CONFIG_ALARM_LOWER_TMP_CLEAR));
		m_cboAlarmType.AddString(GetTextEx(IDS_CONFIG_ALARM_UPPER_HMD_CLEAR));
		m_cboAlarmType.AddString(GetTextEx(IDS_CONFIG_ALARM_LOWER_HMD_CLEAR));
		break;
	}
	//联动类型
	m_cboLinkType.InsertString(0,GetTextEx(IDS_CONFIG_LINK_OUT));
	//联动OSD去掉
	//m_cboLinkType.InsertString(1,GetTextEx(IDS_CONFIG_LINK_OSD));
	m_cboLinkType.InsertString(1,GetTextEx(IDS_CONFIG_LINK_BF));
	m_cboLinkType.InsertString(2,GetTextEx(IDS_CONFIG_LINK_SF));
	m_cboLinkType.InsertString(3,GetTextEx(IDS_CONFIG_LINK_RECOVER));
	//联动恢复方式
	m_cboRecoverType.InsertString(0,GetTextEx(IDS_CONFIG_RECOVER_NOT));
	m_cboRecoverType.InsertString(1,GetTextEx(IDS_CONFIG_RECOVER_DELAY));
	m_cboRecoverType.InsertString(2,GetTextEx(IDS_CONFIG_RECOVER_ALARM_CLEAR));
	m_cboRecoverType.InsertString(3,GetTextEx(IDS_CONFIG_RECOVER_ALARM_CLEAR_DELAY));
	//联动时长
	m_edtLinkTime.SetLimitText(3);
	m_spinLinkTime.SetRange(1,255);
	m_spinLinkTime.SetBuddy(&m_edtLinkTime);
	m_edtLinkTime.SetWindowText("5");

	if(n_Dlg_ADD == m_iDlgFlag)	//添加
	{
		m_cboAlarmType.SetCurSel(0);
		m_cboLinkType.SetCurSel(0);
		m_cboRecoverType.SetCurSel(1);
		ShowWidget(0);
	}
	else
	{
		m_LinkInfo.iLinkIndex = m_iActionNo;
		int iRet = NetClient_GetAlarmConfig(m_iLogonID,m_iDevNo,-1,CMD_ALARM_IN_LINK,&m_LinkInfo);
		if (iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL,"","[CLS_LinkSet::UpdateLinkInfo] NetClient_GetAlarmConfig failed! logonID(%d),m_iChNo(%d),_iLinkNo(%d),error(%d)"
				,m_iLogonID,m_iDevNo,GetLastError());
			return FALSE;
		}
		//报警类型
		int iAlarmType = m_LinkInfo.iAlarmType;
		m_cboAlarmType.SetCurSel(iAlarmType);
		//联动类型:0-保留，1-输出，2-OSD，3-布防，4-撤防，5-恢复自控
		int iLinkType = m_LinkInfo.iLinkType;
		if (iLinkType == 1)
		{
			iLinkType -= 1;
			m_cboLinkType.SetCurSel(iLinkType);
		} 
		else
		{
			iLinkType -= 2;
			m_cboLinkType.SetCurSel(iLinkType);
		}

		//动作名
		CString csName = m_LinkInfo.cName;
		m_edtActionName.SetWindowText(csName);
		//联动恢复方式 0-不恢复，1-延时恢复，2-消警恢复，3-消警延时恢复 
		int iRecoverType = m_LinkInfo.iDisappearType;
		m_cboRecoverType.SetCurSel(iRecoverType);
		//联动时长
		int iLinkTime = m_LinkInfo.iDisappearTime;
		SetDlgItemInt(IDC_EDT_LINK_TIME,iLinkTime);
		//

		ShowWidget(iLinkType);
		GetWidgetInfo(iLinkType);
	}

	UpdateAlarmType();

	return TRUE;	
}

void CLS_LinkDevSetEdit::ShowWidget(int _iLinkType)
{
	if (_iLinkType >= DLGNUM-1)
	{
		_iLinkType = DLGNUM-1;
	}
	for (int i=0;i<DLGNUM;i++)
	{
		m_clsDlg[i]->ShowWindow(SW_HIDE);
	}
	m_clsDlg[_iLinkType]->ShowWindow(SW_SHOW);
}

void CLS_LinkDevSetEdit::SetWidgetInfo(int _iLinkType)
{
	switch (_iLinkType)
	{	
	case 0:
		{
			m_pclsLinkOut = (CLS_LinkOut *)m_clsDlg[0];
			m_pclsLinkOut->SetDlgInfo(m_LinkInfo.cParam,sizeof(m_LinkInfo.cParam));
		}
		break;
// 	case 1:
// 		{
// 			m_pclsLinkOsd = (CLS_LinkOSD *)m_clsDlg[1];
// 			m_pclsLinkOsd->SetDlgInfo(&m_LinkInfo);
// 		}		
// 		break;
	default:	
		m_pclsLinkBsf =(CLS_LinkBSF *)m_clsDlg[1];
		m_pclsLinkBsf->SetDlgInfo(m_LinkInfo.cParam,sizeof(m_LinkInfo.cParam));
		break;
	}
}

void CLS_LinkDevSetEdit::OnCbnSelchangeCboLinkType()
{
	int iSel = m_cboLinkType.GetCurSel();
	ShowWidget(iSel);
}

void CLS_LinkDevSetEdit::OnBnClickedBtnLinkSure()
{
	int iLinkType = m_cboLinkType.GetCurSel();
	if (m_pDlgLink[iLinkType] == NULL)
	{
		return;
	}

	BOOL blRe = false;
	if (iLinkType == 0)
	{
		//m_pclsLinkOut = (CLS_LinkOut *)m_clsDlg[0];
		blRe = ((CLS_LinkOut *)m_clsDlg[iLinkType])->GetData(&m_LinkInfo);
	} 
	else
	{
		
		if (iLinkType > 1)
		{
			iLinkType = 1;
		}
		blRe = ((CLS_LinkBSF *)m_clsDlg[iLinkType])->GetData(&m_LinkInfo);
	}

	if (!blRe)
	{
		return;
	}

	//报警类型
	m_LinkInfo.iAlarmType = m_cboAlarmType.GetCurSel();
	//联动类型1-输出，2-OSD，3-布防，4-撤防，5-恢复自控
	iLinkType = m_cboLinkType.GetCurSel();
	if (iLinkType == 0)
	{
		m_LinkInfo.iLinkType = iLinkType + 1;
	} 
	else
	{
		m_LinkInfo.iLinkType = iLinkType + 2;
	}
	//动作名
	CString csName;
	m_edtActionName.GetWindowText(csName);
	memcpy(m_LinkInfo.cName,csName,csName.GetLength()); 
	//联动恢复方式0-不恢复，1-延时恢复，2-消警恢复，3-消警延时恢复 
	m_LinkInfo.iDisappearType = m_cboRecoverType.GetCurSel();
	//联动时长
//	GetDlgItemInt(IDC_EDT_LINK_TIME,&m_LinkInfo.iDisappearTime);

	CString cstrDisappearTime;
	GetDlgItemText(IDC_EDT_LINK_TIME,cstrDisappearTime);
	m_LinkInfo.iDisappearTime = atoi(cstrDisappearTime.GetBuffer());
	m_LinkInfo.iLinkIndex = m_iActionNo;

	GetWidgetInfo(m_LinkInfo.iAlarmType);

	m_LinkInfo.iLinkEnable = 1;
	m_LinkInfo.iSize = sizeof(AlarmInLink);

	
	int iRet = NetClient_SetAlarmConfig(m_iLogonID,m_iDevNo,-1,CMD_ALARM_IN_LINK,&m_LinkInfo);
	if (iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"","[CLS_LinkSet::UpdateLinkInfo] OnBnClickedBtnLinkSure failed! logonID(%d),m_iChNo(%d)"
			,m_iLogonID,m_iDevNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","[CLS_LinkSet::UpdateLinkInfo] OnBnClickedBtnLinkSure failed! logonID(%d),m_iChNo(%d),error(%d)"
			,m_iLogonID,m_iDevNo,GetLastError());
	}
	EndDialog(IDOK);
}

void CLS_LinkDevSetEdit::GetWidgetInfo(int _iLinkType)
{
	switch (_iLinkType)
	{		
	case 0:
		{
			m_pclsLinkOut = (CLS_LinkOut *)m_clsDlg[0];
			m_pclsLinkOut->GetDlgInfo(m_LinkInfo.cParam,sizeof(m_LinkInfo.cParam));
			m_pclsLinkOut->SetData(&m_LinkInfo);
		}		
		break;
// 	case 1:
// 		{
// 			m_pclsLinkOsd = (CLS_LinkOSD *)m_clsDlg[1];
// 			m_pclsLinkOsd->GetDlgInfo(&m_LinkInfo);
// 		}		
// 		break;
	default:
		m_pclsLinkBsf = (CLS_LinkBSF *)m_clsDlg[1];
		m_pclsLinkBsf->GetDlgInfo(m_LinkInfo.cParam,sizeof(m_LinkInfo.cParam));
		m_pclsLinkBsf->SetData(&m_LinkInfo);
		break;
	}
}

void CLS_LinkDevSetEdit::UpdateLinkType( int _iType )
{
	for(int i = 0; i < DH_ALARM_LINK_TYPE_MAX; i++)
	{
		if (m_pDlgLink[i] != NULL)
		{
			m_pDlgLink[i]->ShowWindow(SW_HIDE);
		}
	}

	switch(_iType)
	{
	case DH_ALARM_LINK_TYPE_OUT:
		{
			if (m_pDlgLink[DH_ALARM_LINK_TYPE_OUT] == NULL)
			{
				m_pDlgLink[DH_ALARM_LINK_TYPE_OUT] = new CLS_LinkOut(m_iLogonID, this);
				m_pDlgLink[DH_ALARM_LINK_TYPE_OUT]->Create(IDD_DLG_CFG_LINK_OUT, this);
			}
			m_pDlgLink[DH_ALARM_LINK_TYPE_OUT]->ShowWindow(SW_SHOW);
			//((CLS_LinkOut *)m_pDlgLink[DH_ALARM_LINK_TYPE_OUT])->SetAlarmTypeFlag(m_bAlarmTypeFlag);
		}
		break;
// 	case DH_ALARM_LINK_TYPE_OSD:
// 		{
// 			if (m_pDlgLink[DH_ALARM_LINK_TYPE_OSD] == NULL)
// 			{
// 				m_pDlgLink[DH_ALARM_LINK_TYPE_OSD] = new CLS_LinkOsd(m_iLogonID, this);
// 				m_pDlgLink[DH_ALARM_LINK_TYPE_OSD]->Create(IDD_DLG_LINKOSD, this);
// 			}
// 			m_pDlgLink[DH_ALARM_LINK_TYPE_OSD]->ShowWindow(SW_SHOW);
// 		}
// 		break;
	case DH_ALARM_LINK_TYPE_EMBATTLE:
		{
			if (m_pDlgLink[DH_ALARM_LINK_TYPE_EMBATTLE] == NULL)
			{
				m_pDlgLink[DH_ALARM_LINK_TYPE_EMBATTLE] = new CLS_LinkBSF(m_iLogonID, this);
				m_pDlgLink[DH_ALARM_LINK_TYPE_EMBATTLE]->Create(IDD_DLG_CFG_LINK_BSF, this);
			}
			m_pDlgLink[DH_ALARM_LINK_TYPE_EMBATTLE]->ShowWindow(SW_SHOW);
			((CLS_LinkBSF *)m_pDlgLink[DH_ALARM_LINK_TYPE_EMBATTLE])->SetAlarmTypeFlag(m_bAlarmTypeFlag);
		}
		break;
	case DH_ALARM_LINK_TYPE_DISMANTLE:
		{
			if (m_pDlgLink[DH_ALARM_LINK_TYPE_DISMANTLE] == NULL)
			{
				m_pDlgLink[DH_ALARM_LINK_TYPE_DISMANTLE] = new CLS_LinkBSF(m_iLogonID, this);
				m_pDlgLink[DH_ALARM_LINK_TYPE_DISMANTLE]->Create(IDD_DLG_CFG_LINK_BSF, this);
			}
			m_pDlgLink[DH_ALARM_LINK_TYPE_DISMANTLE]->ShowWindow(SW_SHOW);
			((CLS_LinkBSF *)m_pDlgLink[DH_ALARM_LINK_TYPE_DISMANTLE])->SetAlarmTypeFlag(m_bAlarmTypeFlag);
		}
		break;
	case DH_ALARM_LINK_TYPE_RECOVERY:
		{
			if (m_pDlgLink[DH_ALARM_LINK_TYPE_RECOVERY] == NULL)
			{
				m_pDlgLink[DH_ALARM_LINK_TYPE_RECOVERY] = new CLS_LinkBSF(m_iLogonID, this);
				m_pDlgLink[DH_ALARM_LINK_TYPE_RECOVERY]->Create(IDD_DLG_CFG_LINK_BSF, this);
			}
			m_pDlgLink[DH_ALARM_LINK_TYPE_RECOVERY]->ShowWindow(SW_SHOW);
			((CLS_LinkBSF *)m_pDlgLink[DH_ALARM_LINK_TYPE_RECOVERY])->SetAlarmTypeFlag(m_bAlarmTypeFlag);
		}
		break;
	default:
		break;
	}

	CRect rect;
	GetDlgItem(IDC_STC_ACTION_NAME)->GetWindowRect(rect);
	ScreenToClient(&rect);

 	if (m_pDlgLink[_iType] != NULL)
 	{
 		CRect rectLink;
 		m_pDlgLink[_iType]->GetWindowRect(rectLink);
 		ScreenToClient(&rectLink);
 		int iHeight = rectLink.Height();
 		rectLink.top = rect.bottom + ROW_STEP;
 		rectLink.bottom = rectLink.top + iHeight;
 		rectLink.left = 0;
 		m_pDlgLink[_iType]->MoveWindow(rectLink, SW_SHOW);
 
 		CRect rectLinkSet;
 		GetDlgItem(IDC_BTN_LINK_SURE)->GetWindowRect(rectLinkSet);
 		ScreenToClient(&rectLinkSet);
 		iHeight = rectLinkSet.Height();
 		rectLinkSet.top = rectLink.bottom;
 		rectLinkSet.bottom = rectLinkSet.top + iHeight;
 		GetDlgItem(IDC_BTN_LINK_SURE)->MoveWindow(rectLinkSet, SW_SHOW);
 	}
}

void CLS_LinkDevSetEdit::UpdateAlarmType()
{
	int iNum = GetAlarmType(m_iDevNo,NULL,0);

	if (iNum < 0)
	{
		return;
	}

	LinkAlarmType* linkAlarmType = new LinkAlarmType[iNum];

	if (linkAlarmType == NULL)
	{
		return;
	}

	GetAlarmType(m_iDevNo,linkAlarmType,iNum);

	for(int i = 0; i < iNum; i++)
	{
		int iItemComb = m_cboAlarmType.AddString(linkAlarmType[i].cName);
		m_cboAlarmType.SetItemData(iItemComb, linkAlarmType[i].iAlarmType);
	}

	m_cboAlarmType.SetCurSel(0);

	if (linkAlarmType != NULL)
	{
		delete linkAlarmType;
		linkAlarmType = NULL;
	}
}

int CLS_LinkDevSetEdit::GetAlarmType(int _iID,LinkAlarmType* _pType,int _iBufLen)
{
	AlarmInConfig alarminConfig;
	memset(&alarminConfig, 0, sizeof(AlarmInConfig));
	alarminConfig.iSize = sizeof(AlarmInConfig);
	if(NetClient_GetAlarmConfig(m_iLogonID, _iID, -1, CMD_ALARM_IN_CONFIG, &alarminConfig) < 0)
	{
		return -1;
	}

	int iLength = -1;

	switch(alarminConfig.iInterfaceType)
	{
	case ALARM_INTERFACE_TYPE_SWITCH:
		{
			iLength = 2;
			if (_pType != NULL && _iBufLen >= iLength)
			{
				strcpy_s(_pType[0].cName, (LPSTR)(LPCTSTR)GetText(IDS_ALARM_TYPE_ALARM));
				_pType[0].iAlarmType = ALARM_VDO_INPORT;

				strcpy_s(_pType[1].cName, (LPSTR)(LPCTSTR)GetText(IDS_ALARM_TYPE_CANCEL_ALARM));
				_pType[1].iAlarmType = ALARM_VDO_INPORT_OFF;
			}
		}
		break;
	case ALARM_INTERFACE_TYPE_ANALOG:
		{
			iLength = 4;
			if (_pType != NULL && _iBufLen >= iLength)
			{
				strcpy_s(_pType[0].cName, (LPSTR)(LPCTSTR)GetText(IDS_ALARM_TYPE_TOPLIMIT));
				_pType[0].iAlarmType = ALARM_ANALOG_UPPER_LIMIT_ON; 

				strcpy_s(_pType[1].cName, (LPSTR)(LPCTSTR)GetText(IDS_ALARM_TYPE_LOWLIMIT));
				_pType[1].iAlarmType = ALARM_ANALOG_LOWER_LIMIT_ON;

				strcpy_s(_pType[2].cName, (LPSTR)(LPCTSTR)GetText(IDS_ALARM_TYPE_TOPLIMIT_CANCEL));
				_pType[2].iAlarmType = ALARM_ANALOG_UPPER_LIMIT_OFF;

				strcpy_s(_pType[3].cName, (LPSTR)(LPCTSTR)GetText(IDS_ALARM_TYPE_LOWLIMIT_CANCEL));
				_pType[3].iAlarmType = ALARM_ANALOG_LOWER_LIMIT_OFF;
			}
		}
		break;
	case ALARM_INTERFACE_TYPE_COM:
		{
			iLength = 8;
			if (_pType != NULL && _iBufLen >= iLength)
			{
				strcpy_s(_pType[0].cName, (LPSTR)(LPCTSTR)GetText(IDS_ALARM_TYPE_TEM_TOPLIMIT));
				_pType[0].iAlarmType = ALARM_TEMPERATURE_UPPER_LIMIT_ON;

				strcpy_s(_pType[1].cName, (LPSTR)(LPCTSTR)GetText(IDS_ALARM_TYPE_TEM_LOWLIMIT));
				_pType[1].iAlarmType = ALARM_TEMPERATURE_LOWER_LIMIT_ON;

				strcpy_s(_pType[2].cName, (LPSTR)(LPCTSTR)GetText(IDS_ALARM_TYPE_HUM_TOPLIMIT));
				_pType[2].iAlarmType = ALARM_HUMIDITY_UPPER_LIMIT_ON;

				strcpy_s(_pType[3].cName, (LPSTR)(LPCTSTR)GetText(IDS_ALARM_TYPE_HUM_LOWLIMIT));
				_pType[3].iAlarmType = ALARM_HUMIDITY_LOWER_LIMIT_ON;

				strcpy_s(_pType[4].cName, (LPSTR)(LPCTSTR)GetText(IDS_ALARM_TYPE_TEM_TOPLIMIT_CANCEL));
				_pType[4].iAlarmType = ALARM_TEMPERATURE_UPPER_LIMIT_OFF;

				strcpy_s(_pType[5].cName, (LPSTR)(LPCTSTR)GetText(IDS_ALARM_TYPE_TEM_LOWLIMIT_CANCEL));
				_pType[5].iAlarmType = ALARM_TEMPERATURE_LOWER_LIMIT_OFF;

				strcpy_s(_pType[6].cName, (LPSTR)(LPCTSTR)GetText(IDS_ALARM_TYPE_HUM_TOPLIMIT_CANCEL));
				_pType[6].iAlarmType = ALARM_HUMIDITY_UPPER_LIMIT_OFF;

				strcpy_s(_pType[7].cName, (LPSTR)(LPCTSTR)GetText(IDS_ALARM_TYPE_HUM_LOWLIMIT_CANCEL));
				_pType[7].iAlarmType = ALARM_HUMIDITY_LOWER_LIMIT_OFF;
			}
		}
		break;
	default:
		break;
	}

	return iLength;
}


void CLS_LinkDevSetEdit::OnCbnSelchangeCboAlarmType()
{
	int iIndex = m_cboAlarmType.GetCurSel();
	int iAlarmType = (int)m_cboAlarmType.GetItemData(iIndex);
	if(iAlarmType== ALARM_VDO_INPORT_OFF || ((m_cboAlarmType.GetItemData(iIndex) >= ALARM_ANALOG_UPPER_LIMIT_OFF) && (m_cboAlarmType.GetItemData(iIndex) <= ALARM_HUMIDITY_LOWER_LIMIT_OFF)))
	{
		m_bAlarmTypeFlag = true;
	}
	else
	{
		m_bAlarmTypeFlag = false;
	}

	for (int i = DH_ALARM_LINK_TYPE_OUT; i <= DH_ALARM_LINK_TYPE_RECOVERY; i++)
	{
		if (i != DH_ALARM_LINK_TYPE_OSD)
		{
			if (m_pDlgLink[i]->IsWindowVisible()&&i != 0)
			{
				((CLS_LinkBSF *)m_pDlgLink[i])->SetAlarmTypeFlag(m_bAlarmTypeFlag);
				break;
			}
			else
			{
				//((CLS_LinkOut *)m_pDlgLink[i])->SetAlarmTypeFlag(m_bAlarmTypeFlag);
				break;
			}
		}
	}
}
