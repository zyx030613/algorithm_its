// Config\StoragePage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "Config\StoragePage.h"


// CStoragePage dialog

IMPLEMENT_DYNAMIC(CStoragePage, CDialog)

CStoragePage::CStoragePage(CWnd* pParent /*=NULL*/)
: CLS_BasePage(CStoragePage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = 0;

	m_pCboRecordMode[0] = &m_cboRecordMode1;
	m_pCboRecordMode[1] = &m_cboRecordMode2;
	m_pCboRecordMode[2] = &m_cboRecordMode3;
	m_pCboRecordMode[3] = &m_cboRecordMode4;

	m_pDtTMStart[0] = &m_dtTMStart1;
	m_pDtTMStart[1] = &m_dtTMStart2;
	m_pDtTMStart[2] = &m_dtTMStart3;
	m_pDtTMStart[3] = &m_dtTMStart4;

	m_pDtTMEnd[0] = &m_dtTMEnd1;
	m_pDtTMEnd[1] = &m_dtTMEnd2;
	m_pDtTMEnd[2] = &m_dtTMEnd3;
	m_pDtTMEnd[3] = &m_dtTMEnd4;

	//m_pChkTMButton[0] = &m_chkTM1;
	//m_pChkTMButton[1] = &m_chkTM2;
	//m_pChkTMButton[2] = &m_chkTM3;
	//m_pChkTMButton[3] = &m_chkTM4;
}

CStoragePage::~CStoragePage()
{
	
}

void CStoragePage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ALARMREC_ENABLE, m_chk_AlarmRecEnable);
	DDX_Control(pDX, IDC_COMBO_WEEKDAY, m_cbo_WeekDay);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TMSTART1, m_dtTMStart1);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TMSTART2, m_dtTMStart2);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TMSTART3, m_dtTMStart3);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TMSTART4, m_dtTMStart4);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TMEND1, m_dtTMEnd1);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TMEND2, m_dtTMEnd2);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TMEND3, m_dtTMEnd3);
	DDX_Control(pDX, IDC_DATETIMEPICKER__TMEND3, m_dtTMEnd4);
	DDX_Control(pDX, IDC_COMBO_RECTYPE1, m_cboRecordMode1);
	DDX_Control(pDX, IDC_COMBO_RECTYPE2, m_cboRecordMode2);
	DDX_Control(pDX, IDC_COMBO_RECTYPE3, m_cboRecordMode3);
	DDX_Control(pDX, IDC_COMBO_RECTYPE4, m_cboRecordMode4);
	DDX_Control(pDX, IDC_CHECK_BYTIME, m_chkByTime);
	DDX_Control(pDX, IDC_CHECK_BYSIZE, m_chkByFileSize);
	DDX_Control(pDX, IDC_EDIT_RECTIME, m_edtByTime);
	DDX_Control(pDX, IDC_EDIT_RECSIZE, m_edtByFileSize);
	DDX_Control(pDX, IDC_COMBO_POLICY, m_cboRecRule);
	DDX_Control(pDX, IDC_CHECK_ALM_PREREC_ENABLE, m_chkAlarmPreRec);
	DDX_Control(pDX, IDC_COMBO_STORAGE_RULE_TYPE, m_cboStorageRuleType);
	DDX_Control(pDX, IDC_CHECK_TASKREC_ENABLE, m_chk_TaskRecEnable);
	DDX_Control(pDX, IDC_COMBO_RECSTAT, m_cboRecordStatus);
	DDX_Control(pDX, IDC_CHECKREDUNDANTREC_ENABLE, m_chkRedundantRec);
	DDX_Control(pDX, IDC_CHECK_SUB_RECORD, m_chkSubRecord);
	DDX_Control(pDX, IDC_COMBO_STORAGE_TIME, m_cboStorageTime);
	DDX_Control(pDX, IDC_COMBO_SUB_STORAGE_TIME, m_cboSubStorageTime);
}


BEGIN_MESSAGE_MAP(CStoragePage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SETALLCHANNEL, &CStoragePage::OnBnClickedButtonSetallchannel)
	ON_BN_CLICKED(IDC_BUTTON_SETREC, &CStoragePage::OnBnClickedButtonSetrec)
	ON_BN_CLICKED(IDC_CHECK_ALARMREC_ENABLE, &CStoragePage::OnBnClickedCheckAlarmrecEnable)
	ON_BN_CLICKED(IDC_CHECK_TASKREC_ENABLE, &CStoragePage::OnBnClickedCheckTaskrecEnable)
	ON_CBN_SELCHANGE(IDC_COMBO_WEEKDAY, &CStoragePage::OnCbnSelchangeComboWeekday)
	ON_BN_CLICKED(IDC_BUTTON_SET_ALLDAY, &CStoragePage::OnBnClickedButtonSetAllday)
	ON_BN_CLICKED(IDC_CHECK_BYTIME, &CStoragePage::OnBnClickedCheckBytime)
	ON_BN_CLICKED(IDC_CHECK_BYSIZE, &CStoragePage::OnBnClickedCheckBysize)
	ON_BN_CLICKED(IDC_BUTTON_SETPOLICY, &CStoragePage::OnBnClickedButtonSetpolicy)
	ON_BN_CLICKED(IDC_BUTTON_PREREC_SET, &CStoragePage::OnBnClickedButtonPrerecSet)
	ON_BN_CLICKED(IDC_BUTTON_EXTENSION_SET, &CStoragePage::OnBnClickedButtonExtensionSet)
	ON_BN_CLICKED(IDC_BUTTON_RULE_TYPE_SET, &CStoragePage::OnBnClickedButtonRuleTypeSet)
	ON_BN_CLICKED(IDC_BUTTON_SNAPSHOT, &CStoragePage::OnBnClickedButtonSnapshot)
	ON_BN_CLICKED(IDC_BUTTON_CTRLREC, &CStoragePage::OnBnClickedButtonCtrlrec)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_REC, &CStoragePage::OnBnClickedButtonManualRec)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_STATUS, &CStoragePage::OnBnClickedButtonManualStatus)
	ON_BN_CLICKED(IDC_BUTTON_REBUILDER, &CStoragePage::OnBnClickedButtonRebuilder)
	ON_CBN_SELCHANGE(IDC_COMBO_STORAGE_RULE_TYPE, &CStoragePage::OnCbnSelchangeComboStorageRuleType)
	ON_BN_CLICKED(IDC_CHECKREDUNDANTREC_ENABLE, &CStoragePage::OnBnClickedCheckredundantrecEnable)
	ON_BN_CLICKED(IDC_BUTTON_STORAGE_TIME, &CStoragePage::OnBnClickedButtonStorageTime)
	ON_BN_CLICKED(IDC_BUTTON_SUB_STORAGE_TIME, &CStoragePage::OnBnClickedButtonSubStorageTime)
	ON_BN_CLICKED(IDC_CHECK_SUB_RECORD, &CStoragePage::OnBnClickedCheckSubRecord)
END_MESSAGE_MAP()


// CStoragePage message handlers

void CStoragePage::UI_UpdateWeek(int _iCurSel)
{
	_iCurSel = (_iCurSel < 0)?0:_iCurSel;
	m_cbo_WeekDay.ResetContent();
	m_cbo_WeekDay.AddString(GetTextEx(IDS_CONFIG_STORAGE_SUNDAY));
	m_cbo_WeekDay.AddString(GetTextEx(IDS_CONFIG_STORAGE_MONDAY));
	m_cbo_WeekDay.AddString(GetTextEx(IDS_CONFIG_STORAGE_TUESDAY));
	m_cbo_WeekDay.AddString(GetTextEx(IDS_CONFIG_STORAGE_WEDNESDAY));
	m_cbo_WeekDay.AddString(GetTextEx(IDS_CONFIG_STORAGE_THURSDAY));
	m_cbo_WeekDay.AddString(GetTextEx(IDS_CONFIG_STORAGE_FRIDAY));
	m_cbo_WeekDay.AddString(GetTextEx(IDS_CONFIG_STORAGE_SATURDAY));
	m_cbo_WeekDay.AddString(GetTextEx(IDS_CONFIG_STORAGE_HOLIDAY));
	m_cbo_WeekDay.SetCurSel(_iCurSel);
}

void CStoragePage::UI_UpdateRecordMode(int* _iCurSel, int _iSize)
{
	for (int i = 0; i < MAX_RECORDMODE_CONTROL; i++)
	{
		if (_iCurSel[i] < 0)
		{
			_iCurSel[i] = 0;
		}
		m_pCboRecordMode[i]->ResetContent();
		InsertString(*(m_pCboRecordMode[i]), 0, IDS_CONFIG_STORAGE_DISABLE);
		InsertString(*(m_pCboRecordMode[i]), 1, IDS_CONFIG_STORAGE_TASKREC);
		InsertString(*(m_pCboRecordMode[i]), 2, IDS_CONFIG_STORAGE_PORTREC);
		InsertString(*(m_pCboRecordMode[i]), 3, IDS_CONFIG_STORAGE_MOTIONREC);
		InsertString(*(m_pCboRecordMode[i]), 4, IDS_CONFIG_STORAGE_LOSTREC);
		InsertString(*(m_pCboRecordMode[i]), 5, IDS_CONFIG_STORAGE_MPORT);
		InsertString(*(m_pCboRecordMode[i]), 6, IDS_CONFIG_STORAGE_COVERREC);
		m_pCboRecordMode[i]->SetCurSel(_iCurSel[_iSize > MAX_RECORDMODE_CONTROL?0:i]);
	}
}

void CStoragePage::UI_UpdatePolicy(int _iCurSel)
{
	_iCurSel = (_iCurSel < 0)?0:_iCurSel;
	m_cboRecRule.ResetContent();
	InsertString(m_cboRecRule, 0, IDS_CONFIG_STORAGE_RULE_STOPRECORD);
	InsertString(m_cboRecRule, 1, IDS_CONFIG_STORAGE_RULE_DELELTEFILE);
	InsertString(m_cboRecRule, 2, IDS_CONFIG_STORAGE_RULE_DELELTEFILE_EXCLUDEALARM);
	m_cboRecRule.SetCurSel(_iCurSel);
}

void CStoragePage::UI_UpdateStorageType(int _iCurSel)
{
	_iCurSel = (_iCurSel < 0)?0:_iCurSel;
	m_cboStorageRuleType.ResetContent();
	InsertString(m_cboStorageRuleType, 0, IDS_CONFIG_STORAGE_RULE_RECORDAUDIO);
	InsertString(m_cboStorageRuleType, 1, IDS_CONFIG_STORAGE_RULE_STORAGETIME);
	InsertString(m_cboStorageRuleType, 2, IDS_CONFIG_STORAGE_RULE_EXTRACTFRAME);
//	InsertString(m_cboStorageRuleType, 3, IDS_CONFIG_STORAGE_RULE_REDUNDANCERECORD);
	m_cboStorageRuleType.SetCurSel(_iCurSel);
}

void CStoragePage::UI_UpdateStorageRule()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	STORAGE_RULE tStorageRule = {sizeof(STORAGE_RULE)};
	tStorageRule.iType = m_cboStorageRuleType.GetCurSel();;
	int iRet = NetClient_NetFileGetChannelParam(m_iLogonID, m_iChannelNo, STORAGE_CMD_STORAGE_RULE, &tStorageRule);
	if(0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_RULE_VALUE, tStorageRule.iValue);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileGetChannelParam:LogonID(%d),tStorageRule.iType(%d),tStorageRule.iValue(%d)", m_iLogonID,tStorageRule.iType,tStorageRule.iValue);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileGetChannelParam:LogonID(%d),tStorageRule.iType(%d),tStorageRule.iValue(%d)", m_iLogonID,tStorageRule.iType,tStorageRule.iValue);
	}

	tStorageRule.iType = 3;//参数值 iType == 3；0，不开启冗余录像；1，开启冗余录像；
	iRet = NetClient_NetFileGetChannelParam(m_iLogonID, m_iChannelNo,STORAGE_CMD_STORAGE_RULE,&tStorageRule);
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileGetChannelParam:LogonID(%d),tStorageRule.iType(%d),tStorageRule.iValue(%d)", m_iLogonID,tStorageRule.iType,tStorageRule.iValue);
		m_chkRedundantRec.SetCheck(tStorageRule.iValue);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileGetChannelParam:LogonID(%d),tStorageRule.iType(%d),tStorageRule.iValue(%d)", m_iLogonID,tStorageRule.iType,tStorageRule.iValue);
	}

	tStorageRule.iType = STORAGE_RULE_STORAGE_TIME;
	tStorageRule.iValue = 0;
	NetClient_NetFileGetChannelParam(m_iLogonID,m_iChannelNo,STORAGE_CMD_STORAGE_RULE,&tStorageRule);
	SetDlgItemInt(IDC_COMBO_STORAGE_TIME,tStorageRule.iValue);

	tStorageRule.iType = STORAGE_RULE_SUB_RECORD;
	tStorageRule.iValue = 0;
	NetClient_NetFileGetChannelParam(m_iLogonID,m_iChannelNo,STORAGE_CMD_STORAGE_RULE,&tStorageRule);
	CheckDlgButton(IDC_CHECK_SUB_RECORD,tStorageRule.iValue);

	tStorageRule.iType = STORAGE_RULE_SUB_STORAGE_TIME;
	tStorageRule.iValue = 0;
	NetClient_NetFileGetChannelParam(m_iLogonID,m_iChannelNo,STORAGE_CMD_STORAGE_RULE,&tStorageRule);
	SetDlgItemInt(IDC_COMBO_SUB_STORAGE_TIME,tStorageRule.iValue);
}

int CStoragePage::UpdateRecordStatusParam()
{
	int iRecordState = 0;
	if(RET_SUCCESS == NetClient_NetFileGetRecordState(m_iLogonID, m_iChannelNo, &iRecordState))
	{
		if (iRecordState < m_cboRecordStatus.GetCount() - 1)
			m_cboRecordStatus.SetCurSel(iRecordState);
		else                                    //  如果是用户自己定义录像，就在下方的编辑框里显示
		{
			m_cboRecordStatus.SetCurSel(m_cboRecordStatus.GetCount()-1);
			SetDlgItemInt(IDC_EDIT_RECTYPE, iRecordState);
		}

		if(REC_MANUAL == iRecordState)
			SetDlgItemTextEx(IDC_BUTTON_MANUAL_REC, IDS_CONFIG_STORAGE_MANUALRECSTOP);
		else
			SetDlgItemTextEx(IDC_BUTTON_MANUAL_REC, IDS_CONFIG_STORAGE_MANUALREC);
	}

	return RET_SUCCESS;

}

void CStoragePage::UI_UpdateRecordStatus(int _iCurSel)
{
	_iCurSel = (_iCurSel < 0)?0:_iCurSel;
	m_cboRecordStatus.ResetContent();
	InsertString(m_cboRecordStatus, 0, IDS_CONFIG_STORAGE_RECSTAT_STOP);
	InsertString(m_cboRecordStatus, 1, IDS_CONFIG_STORAGE_RECSTAT_MANUALRECORD);
	InsertString(m_cboRecordStatus, 2, IDS_CONFIG_STORAGE_RECSTAT_TASKRECORD);
	InsertString(m_cboRecordStatus, 3, IDS_CONFIG_STORAGE_RECSTAT_ALARMRECORD);
	InsertString(m_cboRecordStatus, 4, IDS_CONFIG_STORAGE_RECSTAT_USERDEFINED);
	m_cboRecordStatus.SetCurSel(_iCurSel);

}

void CStoragePage::UI_UpdateAllStorageInfo()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	UI_UpdateSurface();
	OnCbnSelchangeComboWeekday();

	char cExtName[16];
	if(NetClient_NetFileGetExtendname(m_iLogonID, cExtName) == 0)
	{
		SetDlgItemText(IDC_EDIT_FILE_EXTENSION, cExtName);
	}

	int iRule,iMaxFileTLen,iFreeDisk,iMaxFileSize;
	if(NetClient_NetFileGetRecordRule(m_iLogonID, &iRule, &iMaxFileTLen, &iFreeDisk,&iMaxFileSize) == 0)
	{
		m_cboRecRule.SetCurSel(iRule);
		SetDlgItemInt(IDC_EDIT_RECTIME, iMaxFileTLen);
		SetDlgItemInt(IDC_EDIT_FREE_DISKSIZE, iFreeDisk);
		SetDlgItemInt(IDC_EDIT_RECSIZE, iMaxFileSize);
		if(iMaxFileTLen==0)
		{
			m_edtByTime.EnableWindow(FALSE);
			m_chkByTime.SetCheck(BST_UNCHECKED);
			m_edtByFileSize.EnableWindow(TRUE);
			m_chkByFileSize.SetCheck(BST_CHECKED);
		}
		else
		{
			m_edtByTime.EnableWindow(TRUE);
			m_chkByTime.SetCheck(BST_CHECKED);
			m_edtByFileSize.EnableWindow(FALSE);
			m_chkByFileSize.SetCheck(BST_UNCHECKED);
		}
	}

	int iPreEnable,iPreTime,iDelay,iDelayEnable;
	int iRet;
	int iCurTypeModel = -1;
	if (0 == NetClient_GetProductType(m_iLogonID, &iCurTypeModel))
	{
		iCurTypeModel = iCurTypeModel & 0xFFFF;
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetProductType(%d),error no:(%d)", m_iLogonID, GetLastError());
		return;
	}

	if(IsDVR(iCurTypeModel))
	{
		iRet = NetClient_NetFileGetAlarmRule(m_iLogonID, &iPreEnable, &iPreTime, &iDelay,&iDelayEnable,m_iChannelNo);
	}
	else
	{
		iRet = NetClient_NetFileGetAlarmRule(m_iLogonID, &iPreEnable, &iPreTime, &iDelay,&iDelayEnable,m_iChannelNo);
	}
	if( iRet == 0)
	{
		m_chkAlarmPreRec.SetCheck((iPreEnable==1)?BST_CHECKED:BST_UNCHECKED);
		SetDlgItemInt(IDC_EDIT_PRETIME, iPreTime);
		SetDlgItemInt(IDC_EDIT_DELAYTIME, iDelay);
		//chkAlarmDelay->Checked = (iDelayEnable==1)?true:false;
	}

	int iAlarmRecEnable;
	if(NetClient_NetFileGetAlarmState(m_iLogonID, m_iChannelNo, &iAlarmRecEnable) == 0)
	{
		m_chk_AlarmRecEnable.SetCheck(iAlarmRecEnable?BST_CHECKED:BST_UNCHECKED);
	}

	int iTaskRecEnable = 0;
	if(NetClient_NetFileGetTaskState(m_iLogonID, m_iChannelNo, &iTaskRecEnable) == 0)
	{
		m_chk_TaskRecEnable.SetCheck(iTaskRecEnable?BST_CHECKED:BST_UNCHECKED);
	}
	
	ITS_EnalbeParam pEnableParam = {0};
	pEnableParam.iType = MAX_ITS_ITSMANUALENABLE_NUM;
	ASSERT(NetClient_GetITSExtraInfo);
	if (0 == NetClient_GetITSExtraInfo( m_iLogonID, ITS_ENABLE_CMD_SET, NULL, &pEnableParam, sizeof(ITS_EnalbeParam)))
	{
		if(1 == pEnableParam.iEnable)
		{
			SetDlgItemTextEx(IDC_BUTTON_MANUAL_STATUS, IDS_CONFIG_STORAGE_MANUALEND);
		}
		else
		{
			SetDlgItemTextEx(IDC_BUTTON_MANUAL_STATUS, IDS_CONFIG_STORAGE_MANUALSTART);
		}
	}

	UpdateRecordStatusParam();
	UI_UpdateStorageRule();
}

BOOL CStoragePage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_dtTMStart1.SetFormat(_T("HH:mm"));
	m_dtTMEnd1.SetFormat(_T("HH:mm"));
	m_dtTMStart2.SetFormat(_T("HH:mm"));
	m_dtTMEnd2.SetFormat(_T("HH:mm"));
	m_dtTMStart3.SetFormat(_T("HH:mm"));
	m_dtTMEnd3.SetFormat(_T("HH:mm"));
	m_dtTMStart4.SetFormat(_T("HH:mm"));
	m_dtTMEnd4.SetFormat(_T("HH:mm"));

	m_cboStorageTime.AddString(_T("0"));
	m_cboStorageTime.AddString(_T("1"));
	m_cboStorageTime.AddString(_T("2"));
	m_cboStorageTime.AddString(_T("3"));
	m_cboStorageTime.AddString(_T("5"));
	m_cboStorageTime.AddString(_T("7"));
	m_cboStorageTime.AddString(_T("10"));
	m_cboStorageTime.AddString(_T("20"));
	m_cboStorageTime.AddString(_T("30"));
	m_cboStorageTime.AddString(_T("60"));
	m_cboStorageTime.SetCurSel(0);

	m_cboSubStorageTime.AddString(_T("0"));
	m_cboSubStorageTime.AddString(_T("1"));
	m_cboSubStorageTime.AddString(_T("2"));
	m_cboSubStorageTime.AddString(_T("3"));
	m_cboSubStorageTime.AddString(_T("5"));
	m_cboSubStorageTime.AddString(_T("7"));
	m_cboSubStorageTime.AddString(_T("10"));
	m_cboSubStorageTime.AddString(_T("20"));
	m_cboSubStorageTime.AddString(_T("30"));
	m_cboSubStorageTime.AddString(_T("60"));
	m_cboSubStorageTime.AddString(_T("90"));
	m_cboSubStorageTime.AddString(_T("180"));
	m_cboSubStorageTime.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CStoragePage::UI_UpdateSurface()
{
	SetDlgItemTextEx(IDC_CHECK_ALARMREC_ENABLE, IDS_CONFIG_STORAGE_ALARM_REC_ENABLE);
	SetDlgItemTextEx(IDC_CHECK_TASKREC_ENABLE, IDS_CONFIG_STORAGE_TASK_REC_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_WEEKDAY, IDS_CONFIG_STORAGE_WEEKDAY);
	SetDlgItemTextEx(IDC_BUTTON_SETALLCHANNEL, IDS_CONFIG_STORAGE_SETALLCHANNEL);
	SetDlgItemTextEx(IDC_STATIC_TMSTART1, IDS_CONFIG_STORAGE_PERIOD1);
	SetDlgItemTextEx(IDC_STATIC_TMSTART2, IDS_CONFIG_STORAGE_PERIOD2);
	SetDlgItemTextEx(IDC_STATIC_TMSTART3, IDS_CONFIG_STORAGE_PERIOD3);
	SetDlgItemTextEx(IDC_STATIC_TMSTART4, IDS_CONFIG_STORAGE_PERIOD4);
	SetDlgItemTextEx(IDC_STATIC_RECORD_STATUS, IDS_CONFIG_STORAGE_RECORD_STATUS);
	SetDlgItemTextEx(IDC_BUTTON_SETREC, IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_SET_ALLDAY, IDS_CONFIG_STORAGE_ALLDAY_SET);
	SetDlgItemTextEx(IDC_STATIC_MAX_FILE_LENGTH, IDS_CONFIG_STORAGE_MAXFILELEN);
	SetDlgItemTextEx(IDC_STATIC_BYTIME, IDS_CONFIG_STORAGE_RECBYTIME);
	SetDlgItemTextEx(IDC_STATIC_BYSIZE, IDS_CONFIG_STORAGE_RECBYSIZE);
	SetDlgItemTextEx(IDC_STATIC_FREE_DISKSIZE, IDS_CONFIG_STORAGE_MINFREEDISK);
	SetDlgItemTextEx(IDC_STATIC_POLICY, IDS_CONFIG_STORAGE_POLICY);
	SetDlgItemTextEx(IDC_BUTTON_SETPOLICY, IDS_SET);
	SetDlgItemTextEx(IDC_CHECK_ALM_PREREC_ENABLE, IDS_CONFIG_STORAGE_ALARM_PREREC_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_PRETIME, IDS_CONFIG_STORAGE_PREREC_TIME);
	SetDlgItemTextEx(IDC_STATIC_DELAYTIME, IDS_CONFIG_STORAGE_DELAY_TIME);
	SetDlgItemTextEx(IDC_BUTTON_PREREC_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_PSPRETIME, IDS_CONFIG_STORAGE_PSRECTIME);
	SetDlgItemTextEx(IDC_STATIC_PSDELAYTIME, IDS_CONFIG_STORAGE_PSDELAYTIME);
	SetDlgItemTextEx(IDC_STATIC_EXTENSION, IDS_CONFIG_STORAGE_EXTENSION);
	SetDlgItemTextEx(IDC_BUTTON_EXTENSION_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_PIC_QUALITY, IDS_CONFIG_STORAGE_QUALITYPIC);
	SetDlgItemTextEx(IDC_BUTTON_SNAPSHOT, IDS_CONFIG_STORAGE_SNAPSHOT);
	SetDlgItemTextEx(IDC_BUTTON_RULE_TYPE_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_RECTYPE, IDS_CONFIG_STORAGE_RECTYPE);
	SetDlgItemTextEx(IDC_STATIC_ACTION, IDS_CONFIG_STORAGE_ACTION);
	SetDlgItemTextEx(IDC_BUTTON_CTRLREC, IDS_CONFIG_STORAGE_CTRLREC);
	SetDlgItemTextEx(IDC_BUTTON_MANUAL_STATUS, IDS_CONFIG_STORAGE_MANUALSTART);
	SetDlgItemTextEx(IDC_BUTTON_MANUAL_REC, IDS_CONFIG_STORAGE_MANUALREC);
	SetDlgItemTextEx(IDC_BUTTON_DISKINFO, IDS_CONFIG_STORAGE_DISKINFO);
	SetDlgItemTextEx(IDC_BUTTON_REBUILDER, IDS_CONFIG_STORAGE_REBUILDERINDEX);
	SetDlgItemTextEx(IDC_CHECKREDUNDANTREC_ENABLE, IDS_CFG_STORAGE_REDUNDANTREC);
	SetDlgItemTextEx(IDC_GROUP_STORAGE_TIME, IDS_STORAGE_STORAGE_TIME);
	SetDlgItemTextEx(IDC_STATIC_MAIN_STORAGE_TIME, IDS_MAJOR);
	SetDlgItemTextEx(IDC_BUTTON_STORAGE_TIME, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_SUB_STORAGE_TIME, IDS_MINOR);
	SetDlgItemTextEx(IDC_BUTTON_SUB_STORAGE_TIME, IDS_SET);
	SetDlgItemTextEx(IDC_CHECK_SUB_RECORD, IDS_STORAGE_SUB_RECORD);
	
	UI_UpdateRecordStatus(0);
	if (m_cbo_WeekDay.GetCurSel() == -1)
	{
		SYSTEMTIME systime;
		GetLocalTime(&systime);
		UI_UpdateWeek(systime.wDayOfWeek/*m_cbo_WeekDay.GetCurSel()*/);
	}
	else
	{
		UI_UpdateWeek(m_cbo_WeekDay.GetCurSel());
	}
	int iSel[] = {m_cboRecordMode1.GetCurSel(),m_cboRecordMode2.GetCurSel(),m_cboRecordMode3.GetCurSel(),m_cboRecordMode4.GetCurSel()};
	UI_UpdateRecordMode(iSel, 4);
	UI_UpdatePolicy(m_cboRecRule.GetCurSel());
	UI_UpdateStorageType(m_cboStorageRuleType.GetCurSel());

    return TRUE;
}

void CStoragePage::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser)
{
	int iMsgType = LOWORD(_iWparam);
	CString strMsg;
	switch(iMsgType)
	{
	case WCM_CONTROL_DEVICE_RECORD:
		{
			int iCode = (int)_iLParam;
			int iChannelID =    (iCode & 0xFF000000) >> 24;
			int iRecordType =   (iCode & 0x00FF0000) >> 16;
			int iAction =       (iCode & 0x0000FF00) >> 8;
			int iResult =       (iCode & 0x000000FF);

			AddLog(LOG_TYPE_MSG,"", "CtrlDevRec (Channel:%d, RecType:%d, Action:%d, Result:%d)", iChannelID, iRecordType, iAction, iResult);
			break;   
		}
	case WCM_REBUILDINDEX:
		{
			int iCode = HIWORD(_iWparam);
			PDEVICE_INFO ptDevice = FindDevice(_ulLogonID);
			if (NULL != ptDevice)
			{
				AddLog(LOG_TYPE_MSG,"", "WCM_REBUILDINDEX Code(%d),IP(%s)", iCode, ptDevice->cIP);
			}
		}
		break;
	default:
		break;
	}
}


void CStoragePage::OnParamChangeNotify( int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData )
{
	if (_iLogonID != m_iLogonID)
	{
		return;
	}

	if (PARA_STORAGE_RECORDSTATE == _iParaType)
	{
		//刷新录像状态
		UpdateRecordStatusParam();
	}
}

void CStoragePage::OnBnClickedButtonSetallchannel()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	int iChannelNum = 0;
	int iCurrentChannel = m_iChannelNo;
	if (0 == NetClient_GetChannelNum(m_iLogonID, &iChannelNum))
	{
		for(int i=0; i<iChannelNum; i++)
		{
			m_iChannelNo = i;
			OnBnClickedButtonSetrec();
		}
	}
	m_iChannelNo = iCurrentChannel;	
}


void CStoragePage::OnBnClickedButtonSetrec()
{
	int iRecordMode1,iRecordMode2,iRecordMode3,iRecordMode4;
	int* piRecordMode[MAX_RECORDMODE_CONTROL] = {&iRecordMode1, &iRecordMode2, &iRecordMode3, &iRecordMode4};
	NVS_SCHEDTIME timeSeg1,timeSeg2,timeSeg3,timeSeg4;
	NVS_SCHEDTIME* schedule[MAX_RECORDMODE_CONTROL] = {&timeSeg1,&timeSeg2,&timeSeg3,&timeSeg4};
    
	SYSTEMTIME systemTime = {0};
	for (int i = 0; i < MAX_RECORDMODE_CONTROL; i++)
	{
		//if(m_pChkTMButton[i]->GetCheck())
		//{
			m_pDtTMStart[i]->GetTime(&systemTime);
			schedule[i]->iStartHour = systemTime.wHour;
			schedule[i]->iStartMin  = systemTime.wMinute;
			m_pDtTMEnd[i]->GetTime(&systemTime);
			schedule[i]->iStopHour  = systemTime.wHour;
			schedule[i]->iStopMin   = systemTime.wMinute;
		//}
		//else
		//{
		//	schedule[i]->iStartHour = 0;
		//	schedule[i]->iStartMin  = 0;
		//	schedule[i]->iStopHour  = 0;
		//	schedule[i]->iStopMin   = 0;
		//}
		
		int iCurSel = m_pCboRecordMode[i]->GetCurSel();
		if (iCurSel == 0 || iCurSel == 1 || iCurSel == 2)
		{
			*(piRecordMode[i]) = iCurSel;
		}
		else if(iCurSel == 3 || iCurSel == 5)
		{
			*(piRecordMode[i]) = iCurSel + 1;
		}
		else if(iCurSel == 4)
		{
			*(piRecordMode[i]) = iCurSel*2;
		}
		else if(iCurSel == 6)
		{
			*(piRecordMode[i]) = 16;
		}
		schedule[i]->iRecordMode = *(piRecordMode[i]);
	}

	int iStarti = 0;
	int iStopi = 0;
	int iStartj = 0;
	int iStopj = 0;
	for (int i = 0; i < MAX_TIMESEGMENT; ++i)
	{
		for(int j = 0; j < MAX_TIMESEGMENT; ++j)
		{
			iStarti = schedule[i]->iStartHour*60+schedule[i]->iStartMin;
			iStopi = schedule[i]->iStopHour*60+schedule[i]->iStopMin;
			iStartj = schedule[j]->iStartHour*60+schedule[j]->iStartMin;
			iStopj = schedule[j]->iStopHour*60+schedule[j]->iStopMin;
			if (i == j || 0 == (iStarti+iStopi) || 0 == (iStartj+iStopi))
			{
				continue;
			}

			if (iStarti >= iStopi
				|| iStarti >= iStartj && iStarti < iStopj 
				|| iStopi > iStartj && iStopi <= iStopj)
			{
				AddLog(LOG_TYPE_MSG,"","time range %d(%2d:%2d - %2d:%2d) collide with time range %d(%2d:%2d - %2d:%2d)"
					,i,schedule[i]->iStartHour,schedule[i]->iStartMin,schedule[i]->iStopHour,schedule[i]->iStopMin
					,j,schedule[j]->iStartHour,schedule[j]->iStartMin,schedule[j]->iStopHour,schedule[j]->iStopMin);
				return;
			}
		}
	}

	int iRet = NetClient_NetFileSetTaskSchedule(m_iLogonID, m_iChannelNo, m_cbo_WeekDay.GetCurSel(),schedule);
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileSetTaskSchedule(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileSetTaskSchedule(%d),error no:(%d)", m_iLogonID, GetLastError());
		::MessageBox(NULL,"Setup failed!","Error",MB_OK);
		OnCbnSelchangeComboWeekday();
	}
}

void CStoragePage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = (_iChannelNo)<0?0:_iChannelNo;
	m_iStreamNo = _iStreamNo;
	UI_UpdateAllStorageInfo();
}

void CStoragePage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateSurface();
}


void CStoragePage::OnBnClickedCheckAlarmrecEnable()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	int iState = -1;
	if(NetClient_NetFileGetAlarmState(m_iLogonID,m_iChannelNo,&iState)== 0)
	{
		if( m_chk_AlarmRecEnable.GetCheck() != iState)
		{
			if(0 == NetClient_NetFileSetAlarmState(m_iLogonID, m_iChannelNo, m_chk_AlarmRecEnable.GetCheck()))
			{
				AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileSetAlarmState(%d)", m_iLogonID);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileSetAlarmState(%d),error no:(%d)", m_iLogonID, GetLastError());
			}
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileGetAlarmState(%d),error no:(%d)", m_iLogonID, GetLastError());
	}
}

void CStoragePage::OnBnClickedCheckTaskrecEnable()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}
	int iState = -1;
	if(NetClient_NetFileGetTaskState(m_iLogonID,m_iChannelNo,&iState)== 0)
	{
		if( m_chk_TaskRecEnable.GetCheck() != iState)
		{
			if(0 == NetClient_NetFileSetTaskState(m_iLogonID, m_iChannelNo, m_chk_TaskRecEnable.GetCheck()))
			{
				AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileSetTaskState(%d)", m_iLogonID);
			}
			else
			{
				AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileSetTaskState(%d),error no:(%d)", m_iLogonID, GetLastError());
			}
		}

	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileGetTaskState(%d),error no:(%d)", m_iLogonID, GetLastError());
	}
}

void CStoragePage::OnCbnSelchangeComboWeekday()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	} 
	NVS_SCHEDTIME timeSeg1,timeSeg2,timeSeg3,timeSeg4;
	NVS_SCHEDTIME* schedule[MAX_RECORDMODE_CONTROL] = {&timeSeg1,&timeSeg2,&timeSeg3,&timeSeg4};
	int iRet = NetClient_NetFileGetTaskSchedule(m_iLogonID,m_iChannelNo,m_cbo_WeekDay.GetCurSel(),schedule);
	if(iRet == 0)
	{
		SYSTEMTIME systemTime = {0};
		GetLocalTime(&systemTime);
		for (int i = 0; i < MAX_RECORDMODE_CONTROL; ++i)
		{
			systemTime.wHour = schedule[i]->iStartHour;
			systemTime.wMinute = schedule[i]->iStartMin;
			VERIFY(m_pDtTMStart[i]->SetTime(&systemTime));
			systemTime.wHour = schedule[i]->iStopHour;
			systemTime.wMinute = schedule[i]->iStopMin;
			VERIFY(m_pDtTMEnd[i]->SetTime(&systemTime));
			//m_pChkTMButton[i]->SetCheck((schedule[i]->iStartHour + schedule[i]->iStartMin + schedule[i]->iStopHour + schedule[i]->iStopMin)?BST_CHECKED:BST_UNCHECKED);

			if(schedule[i]->iRecordMode == 0 || schedule[i]->iRecordMode == 1 || schedule[i]->iRecordMode == 2)
			{
				m_pCboRecordMode[i]->SetCurSel(schedule[i]->iRecordMode);
			}
			else if(schedule[i]->iRecordMode == 4 || schedule[i]->iRecordMode == 6)
			{
				m_pCboRecordMode[i]->SetCurSel(schedule[i]->iRecordMode - 1);
			}
			else if(schedule[i]->iRecordMode == 8)
			{
				m_pCboRecordMode[i]->SetCurSel(schedule[i]->iRecordMode/2);
			}
			else if(schedule[i]->iRecordMode == 16)
			{
				m_pCboRecordMode[i]->SetCurSel(6);
			}
		}
		AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileGetTaskSchedule(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileGetTaskSchedule(%d),error no:(%d)", m_iLogonID, GetLastError());
	}
}

void CStoragePage::OnBnClickedButtonSetAllday()
{
	int iCurDay = m_cbo_WeekDay.GetCurSel();

	for(int i=0; i<7; i++)
	{
		m_cbo_WeekDay.SetCurSel(i);
		OnBnClickedButtonSetrec();
	}
	m_cbo_WeekDay.SetCurSel(iCurDay);	
}

void CStoragePage::OnBnClickedCheckBytime()
{
	if(BST_CHECKED == m_chkByTime.GetCheck())
	{
		m_edtByFileSize.EnableWindow(FALSE);
		m_edtByTime.EnableWindow(TRUE);
		m_chkByFileSize.SetCheck(BST_UNCHECKED);
	}
	else
	{
		m_edtByTime.SetWindowText("0");
		m_edtByTime.EnableWindow(FALSE);
	}
	
}

void CStoragePage::OnBnClickedCheckBysize()
{
	if(BST_CHECKED == m_chkByFileSize.GetCheck())
	{
		m_edtByTime.EnableWindow(FALSE);
		m_edtByFileSize.EnableWindow(TRUE);
		m_chkByTime.SetCheck(BST_UNCHECKED);
	}
	else
	{
		m_edtByFileSize.SetWindowText("0");
		m_edtByFileSize.EnableWindow(FALSE);
	}
}

void CStoragePage::OnBnClickedButtonSetpolicy()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	} 
	int iMaxTime    = (BST_CHECKED == m_chkByTime.GetCheck())?GetDlgItemInt(IDC_EDIT_RECTIME):0;
	int iMaxFileLen = (BST_CHECKED == m_chkByFileSize.GetCheck())?GetDlgItemInt(IDC_EDIT_RECSIZE):0;
	int iFreeDisk   = GetDlgItemInt(IDC_EDIT_FREE_DISKSIZE);
	if (0 == NetClient_NetFileSetRecordRule(m_iLogonID, m_cboRecRule.GetCurSel(), iMaxTime, iFreeDisk, iMaxFileLen))
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileSetRecordRule(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileSetRecordRule(%d),error no:(%d)", m_iLogonID, GetLastError());
	}
}

void CStoragePage::OnBnClickedButtonPrerecSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	} 

	int iPreRecord = 0;
	int iDelayEnable = 0;
	int iPreTime = GetDlgItemInt(IDC_EDIT_PRETIME);
	int iDelayTime = GetDlgItemInt(IDC_EDIT_DELAYTIME);

	int iCurTypeModel = -1;
	if (0 == NetClient_GetProductType(m_iLogonID, &iCurTypeModel))
	{
		iCurTypeModel = iCurTypeModel & 0xFFFF;
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetProductType(%d),error no:(%d)", m_iLogonID, GetLastError());
		return;
	}
	
	if(IsDVR(iCurTypeModel))
	{
		if(iPreTime < 5 || iPreTime > 600 || iDelayTime < 10 || iDelayTime > 600)
		{
			::MessageBox(NULL,"error! DVR:PreTime:(5-600),DelayTime:(10-600)","Error",MB_OK);
			return;
		}
	}
	else
	{
		if(iPreTime < 5 || iPreTime > 180 || iDelayTime < 10 || iDelayTime > 180)
		{
			::MessageBox(NULL,"error! NVSS:PreTime:(5-180),DelayTime:(10-180)","Error",MB_OK);
			return;
		}
	}
	if(BST_CHECKED == m_chkAlarmPreRec.GetCheck())
	{
		iPreRecord = 1;
	}

	iDelayEnable = 1;    //延时一直处于启用状态

	int iRet = NetClient_NetFileSetAlarmRule(m_iLogonID,
		iPreRecord,iPreTime,iDelayTime,iDelayEnable,m_iChannelNo);
	if(iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileSetAlarmRule(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileSetAlarmRule(%d)", m_iLogonID);
	}
}

void CStoragePage::OnBnClickedButtonExtensionSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	} 
	CString szExtensionName;
	GetDlgItemText(IDC_EDIT_FILE_EXTENSION, szExtensionName);

	if (0 == NetClient_NetFileSetExtendname(m_iLogonID,szExtensionName.GetBuffer(0)))
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileSetExtendname(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileSetExtendname(%d)", m_iLogonID);
	}
}

void CStoragePage::OnBnClickedButtonRuleTypeSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	} 

	STORAGE_RULE tStorageRule = {sizeof(STORAGE_RULE)};
	tStorageRule.iType = m_cboStorageRuleType.GetCurSel();
	int iResult = 0;
    tStorageRule.iValue = GetDlgItemInt(IDC_EDIT_RULE_VALUE, &iResult);
    if (iResult == 0)
    {
		AddLog(LOG_TYPE_FAIL, "", "GetDlgItemInt(%d)", m_iLogonID);
		return;
    }
	if((STORAGE_RULE_RECORD_AUDIO == tStorageRule.iType && tStorageRule.iValue >= 0 && tStorageRule.iValue <= 1)
		|| (STORAGE_RULE_STORAGE_TIME == tStorageRule.iType && tStorageRule.iValue >= 0 && tStorageRule.iValue <= 60)
		||(STORAGE_RULE_EXTRACT_FRAME == tStorageRule.iType && tStorageRule.iValue >= 0 && tStorageRule.iValue <= 1)
		/*||(STORAGE_RULE_REDUNDANCE_RECORD == tStorageRule.iType && tStorageRule.iValue >= 0 && tStorageRule.iValue <= 1)*/)
	{
		int iRet = NetClient_NetFileSetChannelParam(m_iLogonID, m_iChannelNo, STORAGE_CMD_STORAGE_RULE, &tStorageRule);
		if(iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileSetChannelParam(%d),error no:(%d)", m_iLogonID, GetLastError());
		}
		else
		{
			AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileSetChannelParam(%d)", m_iLogonID);
		}
	}
	else
	{
		AddLog(LOG_TYPE_MSG, "", "Net File Set Channel Param Failed, invalid param.(%d)", m_iLogonID);
	}
}

void CStoragePage::OnBnClickedButtonSnapshot()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	} 
	int iResult = 0;
	int iQuality  = GetDlgItemInt(IDC_EDIT_PIC_QUALITY, &iResult);
	if (0 == iResult)
	{
		AddLog(LOG_TYPE_FAIL, "", "GetDlgItemInt(%d)", m_iLogonID);
		return;
	}
	if(iQuality < 1 || (iQuality > 100 && iQuality != 110 && iQuality != 120))
	{
		MessageBox(GetTextEx(IDS_CONFIG_STORAGE_HINT1));
		return;
	}
	if (0 == NetClient_Snapshot(m_iLogonID, m_iChannelNo, iQuality))
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_Snapshot(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_Snapshot(%d),error no:(%d)", m_iLogonID, GetLastError());
	}
}

void CStoragePage::OnBnClickedButtonCtrlrec()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	} 
	int iResult = 0;
	int iAction  = GetDlgItemInt(IDC_EDIT_ACTION, &iResult);
	if (0 == iResult)
	{
		AddLog(LOG_TYPE_FAIL, "", "GetDlgItemInt(%d)", m_iLogonID);
		return;
	}
	int iRecordType = GetDlgItemInt(IDC_EDIT_RECTYPE, &iResult);
	if (0 == iResult)
	{
		AddLog(LOG_TYPE_FAIL, "", "GetDlgItemInt(%d)", m_iLogonID);
		return;
	}

	int iRet = NetClient_ControlDeviceRecord(m_iLogonID, m_iChannelNo, iRecordType, iAction);
	if (iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_ControlDeviceRecord(%d)", m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_ControlDeviceRecord(%d),error no:(%d)", m_iLogonID, GetLastError());
	}
}

void CStoragePage::OnBnClickedButtonManualRec()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	} 
	CString szManualRec;
	GetDlgItemText(IDC_BUTTON_MANUAL_REC, szManualRec);
	if(szManualRec== GetTextEx(IDS_CONFIG_STORAGE_MANUALREC))
	{
		if(0 == NetClient_NetFileManualRecord(m_iLogonID, m_iChannelNo, 1))
		{
			SetDlgItemTextEx(IDC_BUTTON_MANUAL_REC, IDS_CONFIG_STORAGE_MANUALRECSTOP);
			AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileManualRecord(%d)", m_iLogonID);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileManualRecord(%d),error no:(%d)", m_iLogonID, GetLastError());
		}
	}
	else
	{
		if (0 == NetClient_NetFileManualRecord(m_iLogonID, m_iChannelNo, 0))
		{
			AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileManualRecord(%d)", m_iLogonID);
			SetDlgItemTextEx(IDC_BUTTON_MANUAL_REC, IDS_CONFIG_STORAGE_MANUALREC);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileManualRecord(%d),error no:(%d)", m_iLogonID, GetLastError());
		}	
	}
}

void CStoragePage::OnBnClickedButtonManualStatus()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	} 
	ITS_EnalbeParam pEnableParam = {0};
	pEnableParam.iType = MAX_ITS_ITSMANUALENABLE_NUM;

	if (0 == NetClient_GetITSExtraInfo( m_iLogonID, ITS_ENABLE_CMD_SET, NULL, &pEnableParam, sizeof(ITS_EnalbeParam)))
	{
		if(1 == pEnableParam.iEnable)
		{
			SetDlgItemTextEx(IDC_BUTTON_MANUAL_STATUS, IDS_CONFIG_STORAGE_MANUALEND);
		}
		else
		{
			SetDlgItemTextEx(IDC_BUTTON_MANUAL_STATUS, IDS_CONFIG_STORAGE_MANUALSTART);
		}

		CString szCaption;
		GetDlgItemText(IDC_BUTTON_MANUAL_STATUS, szCaption);
		if(szCaption == GetTextEx(IDS_CONFIG_STORAGE_MANUALSTART))
		{
			pEnableParam.iEnable = true;
			if(IDCANCEL == ::MessageBox(NULL,"you choose to change ITSManualCap state to ManualStart?!","Warn",MB_OKCANCEL))
			{
				return;
			}
			SetDlgItemTextEx(IDC_BUTTON_MANUAL_STATUS, IDS_CONFIG_STORAGE_MANUALEND);
		}
		else
		{
			pEnableParam.iEnable = false;

			if( IDCANCEL == ::MessageBox(NULL,"you choose to change ITSManualCap state to ManualEnd?!","Warn",MB_OKCANCEL))
			{
				return;
			}
			SetDlgItemTextEx(IDC_BUTTON_MANUAL_STATUS, IDS_CONFIG_STORAGE_MANUALSTART);
		}

		if (0 == NetClient_SetITSExtraInfo( m_iLogonID, ITS_ENABLE_CMD_SET, NULL, &pEnableParam, sizeof(ITS_EnalbeParam)))
		{
			AddLog(LOG_TYPE_SUCC, "", "NetClient_SetITSExtraInfo(%d)", m_iLogonID);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_SetITSExtraInfo(%d),error no:(%d)", m_iLogonID, GetLastError());
		}
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetITSExtraInfo(%d),error no:(%d)", m_iLogonID, GetLastError());
	}
}

void CStoragePage::OnBnClickedButtonRebuilder()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	} 
	int iSupport = NetClient_NetFileIsSupportStorage(m_iLogonID);
	if(iSupport == 0)
	{
		AddLog(LOG_TYPE_MSG, "", "no support!! id(%d)", m_iLogonID);
		return;
	}

	CString szCaption;
	GetDlgItemText(IDC_BUTTON_REBUILDER, szCaption);
	if (szCaption == GetTextEx(IDS_CONFIG_STORAGE_REBUILDERINDEX))
	{
		int iRet = NetClient_NetFileRebuildIndexFile(m_iLogonID, 1);
		if(iRet < 0)
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileRebuildIndexFile(%d),error no:(%d)", m_iLogonID, GetLastError());
			::MessageBox(NULL,GetTextEx(IDS_CONFIG_STORAGE_HINT2),"Warning",MB_OK);
		}
		else
		{
			SetDlgItemTextEx(IDC_BUTTON_REBUILDER, IDS_CONFIG_STORAGE_REBUILDERINDEXING);
		}
	}
	else
	{
		SetDlgItemTextEx(IDC_BUTTON_REBUILDER, IDS_CONFIG_STORAGE_REBUILDERINDEX);
		if (0 == NetClient_NetFileRebuildIndexFile(m_iLogonID, 0))
		{
			AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileRebuildIndexFile(%d)", m_iLogonID);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileRebuildIndexFile(%d),error no:(%d)", m_iLogonID, GetLastError());
		}
	}
}

void CStoragePage::OnCbnSelchangeComboStorageRuleType()
{
	UI_UpdateStorageRule();
}

void CStoragePage::OnBnClickedCheckredundantrecEnable()
{
	// TODO: Add your control notification handler code here
	STORAGE_RULE tStorageRule = {sizeof(STORAGE_RULE)};
	tStorageRule.iType = STORAGE_RULE_REDUNDANCE_RECORD;//参数值 iType == 3；0，不开启冗余录像；1，开启冗余录像；
	tStorageRule.iValue = (m_chkRedundantRec.GetCheck()==TRUE)?1:0;
	int iRet = NetClient_NetFileSetChannelParam(m_iLogonID,m_iChannelNo,STORAGE_CMD_STORAGE_RULE,&tStorageRule);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileSetChannelParam(%d,%d)", m_iLogonID,m_iChannelNo);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileSetChannelParam(%d,%d),error no:(%d)", m_iLogonID, m_iChannelNo, GetLastError());
	}

}

void CStoragePage::OnBnClickedButtonStorageTime()
{
	STORAGE_RULE tStorageRule = {sizeof(STORAGE_RULE)};
	tStorageRule.iType = STORAGE_RULE_STORAGE_TIME;
	tStorageRule.iValue = GetDlgItemInt(IDC_COMBO_STORAGE_TIME);
	if (tStorageRule.iValue > 60)
	{
		tStorageRule.iValue = 60;
	}
	SetDlgItemInt(IDC_COMBO_STORAGE_TIME,tStorageRule.iValue);
	int iRet = NetClient_NetFileSetChannelParam(m_iLogonID,m_iChannelNo,STORAGE_CMD_STORAGE_RULE,&tStorageRule);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileSetChannelParam(%d,%d,STORAGE_RULE,STORAGE_TIME,%d)"
			, m_iLogonID,m_iChannelNo,tStorageRule.iValue);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileSetChannelParam(%d,%d,STORAGE_RULE,STORAGE_TIME,%d),error no:(%d)"
			, m_iLogonID, m_iChannelNo,tStorageRule.iValue, GetLastError());
	}
}

void CStoragePage::OnBnClickedButtonSubStorageTime()
{
	STORAGE_RULE tStorageRule = {sizeof(STORAGE_RULE)};
	tStorageRule.iType = STORAGE_RULE_SUB_STORAGE_TIME;
	tStorageRule.iValue = GetDlgItemInt(IDC_COMBO_SUB_STORAGE_TIME);
	if (tStorageRule.iValue > 180)
	{
		tStorageRule.iValue = 180;
	}
	SetDlgItemInt(IDC_COMBO_SUB_STORAGE_TIME,tStorageRule.iValue);
	int iRet = NetClient_NetFileSetChannelParam(m_iLogonID,m_iChannelNo,STORAGE_CMD_STORAGE_RULE,&tStorageRule);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileSetChannelParam(%d,%d,STORAGE_RULE,SUB_STORAGE_TIME,%d)"
			, m_iLogonID,m_iChannelNo,tStorageRule.iValue);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileSetChannelParam(%d,%d,STORAGE_RULE,SUB_STORAGE_TIME,%d),error no:(%d)"
			, m_iLogonID, m_iChannelNo,tStorageRule.iValue, GetLastError());
	}
}

void CStoragePage::OnBnClickedCheckSubRecord()
{
	STORAGE_RULE tStorageRule = {sizeof(STORAGE_RULE)};
	tStorageRule.iType = STORAGE_RULE_SUB_RECORD;//参数值 iType == 4；0，不开启副码流录像；1，开启副码流录像；
	tStorageRule.iValue = IsDlgButtonChecked(IDC_CHECK_SUB_RECORD);
	int iRet = NetClient_NetFileSetChannelParam(m_iLogonID,m_iChannelNo,STORAGE_CMD_STORAGE_RULE,&tStorageRule);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_NetFileSetChannelParam(%d,%d,STORAGE_RULE,SUB_RECORD,%d)"
			, m_iLogonID,m_iChannelNo,tStorageRule.iValue);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_NetFileSetChannelParam(%d,%d,STORAGE_RULE,SUB_RECORD,%d),error no:(%d)"
			, m_iLogonID, m_iChannelNo,tStorageRule.iValue, GetLastError());
	}
}
