// E:\新项目\trunk\Demo\NetClientDemo\Config\ItsAdvanceConf2.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ItsAdvanceConf2.h"
#define ITS_MAX_STR_NUM 5

// CLS_ItsAdvanceConf2 对话框

IMPLEMENT_DYNAMIC(CLS_ItsAdvanceConf2, CDialog)

CLS_ItsAdvanceConf2::CLS_ItsAdvanceConf2(CWnd* pParent /*=NULL*/)
	:  CLS_BasePage(CLS_ItsAdvanceConf2::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannel = -1;
}

CLS_ItsAdvanceConf2::~CLS_ItsAdvanceConf2()
{
}

void CLS_ItsAdvanceConf2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_ALGTYPE, m_cboAlgType);
	DDX_Control(pDX, IDC_EDT_CHANNELID, m_edtChannelID);
	DDX_Control(pDX, IDC_CBO_ALGOTYPE, m_cboAlgoType);
	DDX_Control(pDX, IDC_CBO_START_CHECK, m_cboStartCheck);
	DDX_Control(pDX, IDC_CBO_PARAM_ENABLE, m_cboParamEnable);
	DDX_Control(pDX, IDC_EDT_CARWIDTH, m_edtCarWidth);
	DDX_Control(pDX, IDC_CBO_FRAMETYPE, m_cboFrameType);
	DDX_Control(pDX, IDC_CBO_RELIABILITY, m_cboReliability);
	DDX_Control(pDX, IDC_EDT_WIDTH, m_edtWidth);
	DDX_Control(pDX, IDC_EDT_HIGHTH, m_edtHighth);
	DDX_Control(pDX, IDC_CBO_MODEL_PROP, m_cboModelProp);
	DDX_Control(pDX, IDC_EDT_MAXSIZE, m_edtMaxSize);
	DDX_Control(pDX, IDC_EDT_MINSIZE, m_edtMinSize);
	DDX_Control(pDX, IDC_EDT_BINARIZITION, m_edtBinarization);
	DDX_Control(pDX, IDC_CBO_ANALYSIS_FRAME, m_cboAnalysisFrame);
	DDX_Control(pDX, IDC_CBO_MODEL_ANGLE, m_cboModelAngle);
	DDX_Control(pDX, IDC_EDT_IMAGEPROP, m_edtImageProp);
}


BEGIN_MESSAGE_MAP(CLS_ItsAdvanceConf2, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_ADVANCE_SET, &CLS_ItsAdvanceConf2::OnBnClickedBtnAdvanceSet)
	ON_BN_CLICKED(IDC_BTN_ALGTYPE_SET, &CLS_ItsAdvanceConf2::OnBnClickedBtnAlgtypeSet)
END_MESSAGE_MAP()

BOOL CLS_ItsAdvanceConf2::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	UI_UpdateDialog();
	return TRUE;
}
void CLS_ItsAdvanceConf2::OnChannelChanged( int _iLogonID,int _iChannelNo, int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	if(_iChannelNo < 0)
	{
		m_iChannel = 0;
	}
	else
	{
		m_iChannel = _iChannelNo;
	}
	UI_UpdateDialog();
	UI_UpdateAdvance();
	UI_UpdateAlgType();
}
void CLS_ItsAdvanceConf2::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}
void CLS_ItsAdvanceConf2::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STC_ADVANCE_CONF2, IDS_ITS_ADVANCE_CONF2);
	SetDlgItemTextEx(IDC_STC_CHANNELID, IDS_ITS_CHANNELID);
	SetDlgItemTextEx(IDC_STC_ANALYSIS_FRAME, IDS_ITS_ANALYSIS_FRAME);
	SetDlgItemTextEx(IDC_STC_ALGOTYPE, IDS_ITS_ALGTYPE);
	SetDlgItemTextEx(IDC_STC_START_CHECK, IDS_ITS_START_CHECK);
	SetDlgItemTextEx(IDC_STC_PARAM_ENABLE, IDS_CONFIG_ITS_ENABLE);
	SetDlgItemTextEx(IDC_STC_CARWIDTH, IDS_ITS_CARWIDTH);
	SetDlgItemTextEx(IDC_STC_FRAMETYPE, IDS_ITS_FRAMETYPE);
	SetDlgItemTextEx(IDC_STC_RELIABILITY, IDS_ITS_RELIABILITY);
	SetDlgItemTextEx(IDC_STC_WIDHIGH, IDS_ITS_WIDHIGH);
	SetDlgItemTextEx(IDC_STC_MODEL_PROP, IDS_ITS_MODEL_PROP);
	SetDlgItemTextEx(IDC_STC_MAXMIN_SIZE, IDS_ITS_MAXMIN_SIZE);
	SetDlgItemTextEx(IDC_STC_BINARIZITION, IDS_ITS_BINARIZITION);
	SetDlgItemTextEx(IDC_BTN_ADVANCE_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BTN_ALGTYPE_SET,IDS_SET);
	SetDlgItemTextEx(IDC_STC_ALGTYPE, IDS_ITS_ALGTYPE_TYPE);
	SetDlgItemTextEx(IDC_STC_MODEL_ANGLE, IDS_ITS_CAR_MODLE_ANGLE);
	SetDlgItemTextEx(IDC_STC_IMAGE_PROP, IDS_ITS_IMAGE_ZOOM);
	for(int i = 0; i<26; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		InsertString(m_cboAnalysisFrame, i, strNo);
	}
	InsertString(m_cboStartCheck,0,IDS_ITS_NO);
	InsertString(m_cboStartCheck,1,IDS_ITS_YES);
	InsertString(m_cboParamEnable,0,IDS_ITS_NO);
	InsertString(m_cboParamEnable,1,IDS_ITS_YES);
	//
	InsertString(m_cboFrameType,0,"RGB");
	InsertString(m_cboFrameType,1,"YUV422");
	InsertString(m_cboFrameType,2,"256");
	InsertString(m_cboFrameType,3,"420");
	//
	InsertString(m_cboAlgoType,0,"T130T");
	InsertString(m_cboAlgoType,1,"T130G");
	InsertString(m_cboAlgoType,2,"T110G");
	//
	InsertString(m_cboAlgType,0,"T130T");
	InsertString(m_cboAlgType,1,"T130G");
	InsertString(m_cboAlgType,2,"T110G");
	//
	InsertString(m_cboModelAngle,0,"0");
	InsertString(m_cboModelAngle,1,"1");
	int j = 40;
	for(int i = 0; i<60;i++)
	{
		CString strNo;
		strNo.Format("%d",j);
		InsertString(m_cboAnalysisFrame, i, strNo);
		j++;
	}

	for(int i = 0; i <= 100; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		InsertString(m_cboModelProp, i, strNo);
	}

	for(int i = 0; i <= 10; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		InsertString(m_cboReliability, i, strNo);
	}
}

void CLS_ItsAdvanceConf2::OnBnClickedBtnAdvanceSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	ITS_VideoDetect tVideoDetect = {0};
	tVideoDetect.iEnable = m_cboParamEnable.GetCurSel();
	tVideoDetect.iFrameRateCount = m_cboAnalysisFrame.GetCurSel();
	tVideoDetect.iVedioType = m_cboFrameType.GetCurSel();
	tVideoDetect.iVehicleMaxSize = GetDlgItemInt(IDC_EDT_MAXSIZE);
	if(tVideoDetect.iVehicleMaxSize > 100)
	{
		tVideoDetect.iVehicleMaxSize = 100;
	}
	else if(tVideoDetect.iVehicleMaxSize < 40)
	{
		tVideoDetect.iVehicleMaxSize = 40;
	}
	tVideoDetect.iVehicleMinSize = GetDlgItemInt(IDC_EDT_MINSIZE);
	if(tVideoDetect.iVehicleMinSize > 100)
	{
		tVideoDetect.iVehicleMinSize = 100;
	}
	else if(tVideoDetect.iVehicleMinSize < 40)
	{
		tVideoDetect.iVehicleMinSize = 40;
	}
	int iTemp = 0;
	if(tVideoDetect.iVehicleMaxSize < tVideoDetect.iVehicleMinSize)
	{
		iTemp = tVideoDetect.iVehicleMaxSize;
		tVideoDetect.iVehicleMaxSize = tVideoDetect.iVehicleMinSize;
		tVideoDetect.iVehicleMinSize = iTemp;
	}
	tVideoDetect.iVedioWidth = GetDlgItemInt(IDC_EDT_WIDTH);
	tVideoDetect.iVedioHeight = GetDlgItemInt(IDC_EDT_HIGHTH);
	tVideoDetect.iVDetectMotor = m_cboStartCheck.GetCurSel();
	tVideoDetect.iModelType = m_cboModelAngle.GetCurSel();
	//tVideoDetect.iEngineType = ((CComboBox*)GetDlgItem(IDC_CBO_ALGOTYPE))->GetCurSel() + 1;
	tVideoDetect.iEngineType = m_cboAlgoType.GetCurSel();
	CString str1;
	CString str2;
	CString str3;
	CString str4;
	CString str5;
	CString str;
	GetDlgItemText(IDC_EDT_IMAGEPROP, str1);
	GetDlgItemText(IDC_EDT_CARWIDTH, str2);
	int iCarWidth = GetDlgItemInt(IDC_EDT_CARWIDTH);
	if((iCarWidth < 40)|| (iCarWidth > 100))
	{
		AddLog(LOG_TYPE_FAIL,"","car width error!");
		return;
	}
	GetDlgItemText(IDC_CBO_RELIABILITY, str3);
	GetDlgItemText(IDC_CBO_MODEL_PROP,str4);
	GetDlgItemText(IDC_EDT_BINARIZITION, str5);
	int iBinarizition = GetDlgItemInt(IDC_EDT_BINARIZITION);
	if((iBinarizition < 210)||(iBinarizition > 255))
	{
		AddLog(LOG_TYPE_FAIL,"","iBinarizition error!");
		return;
	}
	str = str1+','+str2+','+str3+','+str4 +','+str5;
	strcpy(tVideoDetect.cParams130T,str);
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_VIDEODECTECT_NEW_CMD_SET, m_iChannel, &tVideoDetect, sizeof(tVideoDetect));
	if(iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_VIDEODECTECT_NEW_CMD_SET] (%d,%d)",m_iLogonID,m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_VIDEODECTECT_NEW_CMD_SET] (%d,%d), error(%d)",m_iLogonID,m_iChannel, GetLastError());
	}
}
BOOL CLS_ItsAdvanceConf2::UI_UpdateAdvance()
{
	if(m_iLogonID < 0)
		return FALSE;

	ITS_VideoDetect tVideoDetect = {0};
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_VIDEODECTECT_NEW_CMD_GET, m_iChannel, &tVideoDetect, sizeof(tVideoDetect));
	if(iRet == 0)
	{
		m_cboParamEnable.SetCurSel(tVideoDetect.iEnable);
		m_cboAnalysisFrame.SetCurSel(tVideoDetect.iFrameRateCount);
		 m_cboFrameType.SetCurSel(tVideoDetect.iVedioType);
		m_cboStartCheck.SetCurSel(tVideoDetect.iVDetectMotor);
		m_cboModelAngle.SetCurSel(tVideoDetect.iModelType);
		m_cboAlgoType.SetCurSel(tVideoDetect.iEngineType);
		SetDlgItemInt(IDC_EDT_CHANNELID, m_iChannel);
		SetDlgItemInt(IDC_EDT_MAXSIZE,tVideoDetect.iVehicleMaxSize);
		SetDlgItemInt(IDC_EDT_MINSIZE, tVideoDetect.iVehicleMinSize);
		SetDlgItemInt(IDC_EDT_WIDTH, tVideoDetect.iVedioWidth);
		SetDlgItemInt(IDC_EDT_HIGHTH, tVideoDetect.iVedioHeight);
		CString str( tVideoDetect.cParams130T);
		CString strFilter[ITS_MAX_STR_NUM];
		int iNum= 0;
		for(int i = 0; i< ITS_MAX_STR_NUM; i++)
		{
			AfxExtractSubString(strFilter[i], str,i,',');
			iNum++;
		}
		CEdit* pEdit = NULL;
		pEdit = (CEdit*)GetDlgItem(IDC_EDT_BINARIZITION);
		if(NULL != pEdit)
		{
			if(iNum>-1 && iNum < 6)
			pEdit->SetWindowText(strFilter[--iNum]);
		}
		if(iNum>-1 && iNum < 5)
		{
			m_cboModelProp.SetCurSel(atoi(strFilter[--iNum]));
		}
		if(iNum > -1 && iNum < 4)
		{
			m_cboReliability.SetCurSel(atoi(strFilter[--iNum]));
		}
		pEdit = (CEdit*)GetDlgItem(IDC_EDT_CARWIDTH);
		if(NULL != pEdit)
		{
			if(iNum > -1 && iNum < 3)
			pEdit->SetWindowText(strFilter[--iNum]);
		}	
		 pEdit = (CEdit*)GetDlgItem(IDC_EDT_IMAGEPROP);
		if(NULL != pEdit)
		{
			if(iNum > -1 && iNum < 2)
			pEdit->SetWindowText(strFilter[--iNum]);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_VIDEODECTECT_NEW_CMD_GET](%d,%d)",m_iLogonID,m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_VIDEODECTECT_NEW_CMD_GET](%d,%d), error(%d)",m_iLogonID,m_iChannel,GetLastError());
		return FALSE;
	}

	return TRUE;
}

void CLS_ItsAdvanceConf2::OnBnClickedBtnAlgtypeSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iCmd = 0;
	iCmd = ((CComboBox*)GetDlgItem(IDC_CBO_ALGTYPE))->GetCurSel();
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_RECOTYPE_CMD_SET,m_iChannel, &iCmd, sizeof(int));
	if(iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_RECOTYPE_CMD_SET] (%d,%d)",m_iLogonID,m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_RECOTYPE_CMD_SET] (%d,%d), error(%d)",m_iLogonID,m_iChannel, GetLastError());
	}
}
BOOL CLS_ItsAdvanceConf2::UI_UpdateAlgType()
{
	if(m_iLogonID<0)
		return FALSE;

	int iCmd = 0;
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_RECOTYPE_CMD_GET, m_iChannel, &iCmd, sizeof(int));
	if(iRet == 0)
	{
		m_cboAlgType.SetCurSel(iCmd);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_RECOTYPE_CMD_GET](%d,%d)",m_iLogonID,m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_RECOTYPE_CMD_GET](%d,%d), error(%d)",m_iLogonID,m_iChannel,GetLastError());
		return FALSE;
	}

	return TRUE;
}
