
#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEvnetsAdvParam.h"


IMPLEMENT_DYNAMIC(CLS_VCAEvnetsAdvParam, CDialog)
#define ADJUST_EVENT_ADV_RECT(rc) {rc.top += 20; rc.left += 5; rc.right -= 5; rc.bottom -= 5;}

CLS_VCAEvnetsAdvParam::CLS_VCAEvnetsAdvParam(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_VCAEvnetsAdvParam::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNO = 0;
	m_iCurrentSel = 0;
	for(int i=0; i<MAX_EVENT_ADV_NUM; i++)
	{
		m_plArrEventAdvPage[i] = NULL;
	}
}

CLS_VCAEvnetsAdvParam::~CLS_VCAEvnetsAdvParam()
{
	for(int i=0; i<MAX_EVENT_ADV_NUM; i++)
	{
		if (m_plArrEventAdvPage[i])
		{
			m_plArrEventAdvPage[i]->DestroyWindow();
			delete m_plArrEventAdvPage[i];
			m_plArrEventAdvPage[i] = NULL;
		}
	}
}

void CLS_VCAEvnetsAdvParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_EVENT_ID, m_cboAdvEventType);
	DDX_Control(pDX, IDC_CBO_ADV_SCENEID, m_cboAdvSceneID);
}


BEGIN_MESSAGE_MAP(CLS_VCAEvnetsAdvParam, CDialog)
	ON_CBN_SELCHANGE(IDC_CBO_EVENT_ID, &CLS_VCAEvnetsAdvParam::OnCbnSelchangeCboEventId)
	ON_CBN_SELCHANGE(IDC_CBO_ADV_SCENEID, &CLS_VCAEvnetsAdvParam::OnCbnSelchangeCboAdvSceneid)
END_MESSAGE_MAP()


BOOL CLS_VCAEvnetsAdvParam::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	
	UI_Updata();
	OnCbnSelchangeCboAdvSceneid();
	return TRUE;
}

void CLS_VCAEvnetsAdvParam::OnLanguageChanged( int _iLanguage )
{
	UI_Updata();
	m_cboAdvEventType.SetCurSel(0);
	m_cboAdvSceneID.SetCurSel(0);
	for (int i=0; i<MAX_EVENT_ADV_NUM; i++)
	{
		if (m_plArrEventAdvPage[i])
		{
			m_plArrEventAdvPage[i]->OnLanguageChanged();
		}
	}
}

void CLS_VCAEvnetsAdvParam::OnMainNotify( int _iLogonID,int _wParam, void* _iLParam, void* _iUser)
{
	int iSelIndex = m_cboAdvEventType.GetCurSel();
	if (m_plArrEventAdvPage[iSelIndex])
	{
		m_plArrEventAdvPage[iSelIndex]->OnMainNotify(_iLogonID, _wParam, _iLParam, _iUser);
	}
}

void CLS_VCAEvnetsAdvParam::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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
		m_iStreamNO = _iStreamNo;
	}
	OnCbnSelchangeCboEventId();
}


void CLS_VCAEvnetsAdvParam::UI_Updata()
{
	SetDlgItemTextEx(IDC_STC_ADV_EVENT_ID, IDS_VCA_EVENT_ID);
	SetDlgItemTextEx(IDC_STC_ADV_SCENEID, IDS_VCA_SCENE_ID);
	SetDlgItemTextEx(IDC_GBO_VCA_EVENT_ADV_PARAM, IDS_CONFIGPAGE_VCA_EVENTS_ADV);

	const CString strEvent[] = {
		GetTextEx(IDS_VCA_EVENT_RIVER), GetTextEx(IDS_CFG_FUNC_WATER_LEVEL)
	};

	m_cboAdvSceneID.ResetContent();
	int j;
	for (int i = 0; i < MAX_SCENE_NUM; ++i)
	{
		j = i + 1;
		m_cboAdvSceneID.InsertString(i, IntToCString(j));
		
	}
	m_cboAdvSceneID.SetCurSel(0);
	m_cboAdvEventType.ResetContent();
	for (int i=0; i<sizeof(strEvent)/sizeof(CString); i++)
	{
		m_cboAdvEventType.InsertString(i, strEvent[i]);
	}
	m_cboAdvEventType.SetCurSel(0);
}

void CLS_VCAEvnetsAdvParam::OnCbnSelchangeCboEventId()
{
	int iSel = m_cboAdvEventType.GetCurSel();
	for (int i=0; i<MAX_EVENT_ADV_NUM; i++)
	{
		if (NULL != m_plArrEventAdvPage[i])
		{
			m_plArrEventAdvPage[i]->ShowWindow(SW_HIDE);	
		}
	}

	switch (iSel)
	{
	case RIVER_CLEAN_ADV_SEL:
		if (NULL == m_plArrEventAdvPage[RIVER_CLEAN_ADV_SEL])
		{
			m_plArrEventAdvPage[RIVER_CLEAN_ADV_SEL] = new CLS_VCAAdvParam_River();
			m_plArrEventAdvPage[RIVER_CLEAN_ADV_SEL]->Create(IDD_DLG_VCAPARAM_ADV_RIVER, this);
		}
		break;
	case WLD_ADV_SEL:
		if (NULL == m_plArrEventAdvPage[WLD_ADV_SEL])
		{
			m_plArrEventAdvPage[WLD_ADV_SEL] = new CLS_VCAAdvParamWld();
			m_plArrEventAdvPage[WLD_ADV_SEL]->Create(IDD_DLG_VCAPARAM_ADV_WLD, this);
		}
		break;
	default:
		break;
	}

	if (m_plArrEventAdvPage[iSel])
	{
		RECT rcShow = {0};
		GetDlgItem(IDC_GBO_VCA_EVENT_ADV_PARAM)->GetWindowRect(&rcShow);
		ScreenToClient(&rcShow);
		ADJUST_EVENT_ADV_RECT(rcShow);
		m_plArrEventAdvPage[iSel]->MoveWindow(&rcShow);
		m_plArrEventAdvPage[iSel]->SetSceneID(m_iScreenID);
		m_plArrEventAdvPage[iSel]->Init(m_iLogonID, m_iChannelNo, m_iStreamNO);
		m_plArrEventAdvPage[iSel]->ShowWindow(SW_SHOW);
	}
}

void CLS_VCAEvnetsAdvParam::OnCbnSelchangeCboAdvSceneid()
{
	// TODO: Add your control notification handler code here
	m_iScreenID = m_cboAdvSceneID.GetCurSel();
	OnCbnSelchangeCboEventId();
}
