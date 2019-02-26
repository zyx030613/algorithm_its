// AutoTestPage.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "AutoTestPage.h"

#define MAX_LANGUAGE_TYPE	13
enum LanguageType
{
	LAN_ENGLISH = 0,			//	英文
	LAN_CHINESE = 1,			//	简体中文
	LAN_TRADITIONAL = 2,			//	繁体中文
	LAN_KOREAN = 3,		//	韩文（朝鲜语）
	LAN_SPANISH = 4,	//	西班牙语
	LAN_ITALIAN = 5,	//	意大利语
	LAN_RUSSIAN = 6,	//	俄语
	LAN_TURKISH = 7,	//	土耳其语
	LAN_THAI = 8,		//	泰语
	LAN_POLISH = 9,		//	波兰语
	LAN_HEBREW = 10,	//	希伯来语
	LAN_FRENCH = 11,	//	法语
	LAN_GERMAN = 12,	//	德语
};

// CLS_AutoTestPage dialog

IMPLEMENT_DYNAMIC(CLS_AutoTestPage, CDialog)

CLS_AutoTestPage::CLS_AutoTestPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_AutoTestPage::IDD, pParent)
{

}

CLS_AutoTestPage::~CLS_AutoTestPage()
{
}

void CLS_AutoTestPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_AUTOTEST_ENGLISH, m_chkEnglish);
	DDX_Control(pDX, IDC_CHECK_AUTOTEST_CHINESE, m_chkChinese);
	DDX_Control(pDX, IDC_CHECK_AUTOTEST_TRADITIONAL, m_chkTraditional);
	DDX_Control(pDX, IDC_CHECK_AUTOTEST_Korean, m_chkKorean);
	DDX_Control(pDX, IDC_CHECK_AUTOTEST_Spanish, m_chkSpanish);
	DDX_Control(pDX, IDC_CHECK_AUTOTEST_Italian, m_chkItalian);
	DDX_Control(pDX, IDC_CHECK_AUTOTEST_Russian, m_chkRussian);
	DDX_Control(pDX, IDC_CHECK_AUTOTEST_Turkish, m_chkTurkish);
	DDX_Control(pDX, IDC_CHECK_AUTOTEST_Thai, m_chkThai);
	DDX_Control(pDX, IDC_CHECK_AUTOTEST_Polish, m_chkPolish);
	DDX_Control(pDX, IDC_CHECK_AUTOTEST_Hebrew, m_chkHebrew);
	DDX_Control(pDX, IDC_CHECK_AUTOTEST_French, m_chkFrench);
	DDX_Control(pDX, IDC_CHECK_AUTOTEST_German, m_chkGerman);
	DDX_Control(pDX, IDC_EDIT_AUTOTEST_Pixels_X, m_edtPixels_X);
	DDX_Control(pDX, IDC_EDIT_AUTOTEST_Pixels_Y, m_edtPixels_Y);
	DDX_Control(pDX, IDC_CBO_TESTITEM, m_cboTestItem);
	DDX_Control(pDX, IDC_EDT_PARAONE, m_edtParaOne);
	DDX_Control(pDX, IDC_EDT_PARATWO, m_ParaTwo);
	DDX_Control(pDX, IDC_EDT_RESULT, m_edtResult);
}


BEGIN_MESSAGE_MAP(CLS_AutoTestPage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_MULTI_LANGUAGE, &CLS_AutoTestPage::OnBnClickedButtonMultiLanguage)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_TEST_AXIS, &CLS_AutoTestPage::OnBnClickedButtonAutoTestAxis)
	ON_BN_CLICKED(IDC_BTN_AUTOTEST, &CLS_AutoTestPage::OnBnClickedBtnAutotest)
END_MESSAGE_MAP()


// CLS_AutoTestPage message handlers

BOOL CLS_AutoTestPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_edtPixels_X.SetLimitText(LEN_16);
	m_edtPixels_Y.SetLimitText(LEN_16);

	UI_UpdateDialogText();


	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_AutoTestPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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

void CLS_AutoTestPage::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialogText();
}

void CLS_AutoTestPage::UI_UpdateDialogText()
{
	m_cboTestItem.ResetContent();
	m_cboTestItem.AddString(GetTextEx(IDS_AUTOTEST_TEMPERATURE_REVISE));
	m_cboTestItem.SetCurSel(0);

	SetDlgItemTextEx(IDC_STATIC_AXIS, IDS_AUTOTEST_AXIS);
	SetDlgItemTextEx(IDC_STATIC_AUTOTEST_Pixels, IDS_AUTOTEST_PIXELS);
	SetDlgItemTextEx(IDC_BUTTON_AUTO_TEST_AXIS, IDS_AUTOTEST_AXIS_TEST);
	SetDlgItemTextEx(IDC_STATIC_MULTI_LANGUAGE, IDS_MULTI_LANGUAGE);
	SetDlgItemTextEx(IDC_BUTTON_MULTI_LANGUAGE, IDS_AUTOTEST_MULTI_LANGUAGE);
	SetDlgItemTextEx(IDC_CHECK_AUTOTEST_ENGLISH, IDS_AUTOTEST_ENGLISH);
	SetDlgItemTextEx(IDC_CHECK_AUTOTEST_CHINESE, IDS_AUTOTEAT_CHINESE);
	SetDlgItemTextEx(IDC_CHECK_AUTOTEST_TRADITIONAL, IDS_AUTOTEST_TRADITIONAL);
	SetDlgItemTextEx(IDC_CHECK_AUTOTEST_Korean, IDS_AUTOTEST_KOREAN);
	SetDlgItemTextEx(IDC_CHECK_AUTOTEST_Spanish, IDS_AUTOTEST_SPANISH);
	SetDlgItemTextEx(IDC_CHECK_AUTOTEST_Italian, IDS_AUTOTEST_Italian);
	SetDlgItemTextEx(IDC_CHECK_AUTOTEST_Russian, IDS_AUTOTEAT_Russian);
	SetDlgItemTextEx(IDC_CHECK_AUTOTEST_Turkish, IDS_AUTOTEST_Turkish);
	SetDlgItemTextEx(IDC_CHECK_AUTOTEST_Thai, IDS_AUTOTEST_Thai);
	SetDlgItemTextEx(IDC_CHECK_AUTOTEST_Polish, IDS_AUTOTEST_Polish);
	SetDlgItemTextEx(IDC_CHECK_AUTOTEST_Hebrew, IDS_AUTOTEST_Hebrew);
	SetDlgItemTextEx(IDC_CHECK_AUTOTEST_French, IDS_AUTOTEST_French);
	SetDlgItemTextEx(IDC_CHECK_AUTOTEST_German, IDS_AUTOTEST_German);

	SetDlgItemTextEx(IDC_STC_COMMONTESTITEM, IDS_AUTOTEST_COMMONTESTITEM);
	SetDlgItemTextEx(IDC_STC_TESTITEM, IDS_AUTOTEST_TESTITEM);
	SetDlgItemTextEx(IDC_STC_PARAONE, IDS_AUTOTEST_PARAONE);
	SetDlgItemTextEx(IDC_STC_PARATWO, IDS_AUTOTEST_PARATWO);
	SetDlgItemTextEx(IDC_STC_RESULT, IDS_AUTOTEST_RESULT);
	SetDlgItemTextEx(IDC_BTN_AUTOTEST, IDS_SET);


}

void CLS_AutoTestPage::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser )
{
	if (_ulLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",_ulLogonID);
		return;
	}

	int iMsgType = LOWORD(_iWparam);
	switch (iMsgType)
	{
	case WCM_AUTOTEST_INFO:
		{
			unsigned int uiTestItem = (_iWparam>>24) & 0xFF;
			unsigned int uiTestParam = (_iWparam>>16) & 0x00FF;
			int iResult = (int)_iLParam;

			CString cstrResult;
			if (0 == iResult)
			{
				cstrResult.Format("Test Success!  TestItem: %d, TestNo：%d", uiTestItem, uiTestParam);
			}
			else
			{
				cstrResult.Format("Test Fail!  TestItem: %d, TestNo：%d", uiTestItem, uiTestParam);
			}
			MessageBox(cstrResult, GetTextEx(IDS_LOG_OPERATION_MSG), MB_OK);

			m_edtResult.SetWindowText(cstrResult);
		}
		break;
	default:
		break;
	}
}

void CLS_AutoTestPage::InnerAutoTest(int _iCmd, strAutoTest_Para* _pvTestBuf)
{
	if (_pvTestBuf == NULL)
	{
		return;
	}

	int iRet = NetClient_InnerAutoTest(m_iLogonID, _iCmd, _pvTestBuf, sizeof(strAutoTest_Para));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_InnerAutoTest[%d, cmd(%d), %d, (%s)]"
			, m_iLogonID, _iCmd, _pvTestBuf->iTestParam[0], _pvTestBuf->cTestParam);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_InnerAutoTest[%d, cmd(%d), %d, (%s)]"
			, m_iLogonID, _iCmd, _pvTestBuf->iTestParam[0], _pvTestBuf->cTestParam);
	}
}

void CLS_AutoTestPage::OnBnClickedButtonMultiLanguage()
{
	int iLanguageType[MAX_LANGUAGE_TYPE] = {BST_UNCHECKED};
	iLanguageType[LAN_ENGLISH] = m_chkEnglish.GetCheck();
	iLanguageType[LAN_CHINESE] = m_chkChinese.GetCheck();
	iLanguageType[LAN_TRADITIONAL] = m_chkTraditional.GetCheck();
	iLanguageType[LAN_KOREAN] = m_chkKorean.GetCheck();
	iLanguageType[LAN_SPANISH] = m_chkSpanish.GetCheck();
	iLanguageType[LAN_ITALIAN] = m_chkItalian.GetCheck();
	iLanguageType[LAN_RUSSIAN] = m_chkRussian.GetCheck();
	iLanguageType[LAN_TURKISH] = m_chkTurkish.GetCheck();
	iLanguageType[LAN_THAI] = m_chkThai.GetCheck();
	iLanguageType[LAN_POLISH] = m_chkPolish.GetCheck();
	iLanguageType[LAN_HEBREW] = m_chkHebrew.GetCheck();
	iLanguageType[LAN_FRENCH] = m_chkFrench.GetCheck();
	iLanguageType[LAN_GERMAN] = m_chkGerman.GetCheck();

	CString cstrBuf;
	int iLanguageCheck[MAX_LANGUAGE_TYPE] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int iCheckNum = 0;
	for (int i = 0; i < MAX_LANGUAGE_TYPE; ++i)
	{
		if (BST_CHECKED == iLanguageType[i])
		{
			for (int j = 0; j < MAX_LANGUAGE_TYPE; ++j)
			{
				if (-1 == iLanguageCheck[j])
				{
					iLanguageCheck[j] = i;
					iCheckNum++;
					break;
				}
			}
		}
	}

	for (int k = 0; k < iCheckNum - 1; ++k)
	{
		if (-1 != iLanguageCheck[k])
		{
			cstrBuf.AppendFormat(("%d,"), iLanguageCheck[k]);
		}
	}
	if (-1 != iLanguageCheck[iCheckNum - 1])
	{
		cstrBuf.AppendFormat(("%d"), iLanguageCheck[iCheckNum - 1]);
	}

	strAutoTest_Para tPara = {0};
	strcpy(tPara.cTestParam, cstrBuf.GetBuffer());
	InnerAutoTest(AUTOTEST_MODIFYLANGUAGE, &tPara);
}

void CLS_AutoTestPage::OnBnClickedButtonAutoTestAxis()
{
	int iPixels_X = 0;
	int iPixels_Y = 0;
	iPixels_X = GetDlgItemInt(IDC_EDIT_AUTOTEST_Pixels_X);
	iPixels_Y = GetDlgItemInt(IDC_EDIT_AUTOTEST_Pixels_Y);
	strAutoTest_Para tPara = {0};
	sprintf(tPara.cTestParam, "%d:%d", iPixels_X, iPixels_Y);
	InnerAutoTest(AUTOTEST_CAMERALENS, &tPara);
}

void CLS_AutoTestPage::OnBnClickedBtnAutotest()
{
	strAutoTest_Para tPara = {0};
	int iIndex = m_cboTestItem.GetCurSel();
	int iCmd = -1;
	int iParaOne = 0;;
	switch(iIndex)
	{
	case CBO_INDEX_TEMPERATURE_REVISE:
		iCmd = CMD_AUTOTEST_TEMPERATURE_REVISE;
		iParaOne = GetDlgItemInt(IDC_EDT_PARAONE) + TEMPERATURE_REVISE_DEF;
		break;
	default:
		break;
	}

	
	sprintf(tPara.cTestParam, "%d", iParaOne);
	InnerAutoTest(CMD_AUTOTEST_TEMPERATURE_REVISE, &tPara);
}