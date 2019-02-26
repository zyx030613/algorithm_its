
#include "stdafx.h"
#include "NetClientDemo.h"
#include "ChanCheck.h"

// CLS_ChanCheck ¶Ô»°¿ò

IMPLEMENT_DYNAMIC(CLS_ChanCheck, CDialog)

CLS_ChanCheck::CLS_ChanCheck(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ChanCheck::IDD, pParent)
{
	m_iChanNum = 0;
	m_iCurrentPage = 0;
	memset(m_iEnable, 0, sizeof(m_iEnable));
}

CLS_ChanCheck::~CLS_ChanCheck()
{
}

void CLS_ChanCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);	
	for (int i=0; i<MAX_CHAN_PAGE; i++)
	{
		DDX_Control(pDX, IDC_CHK_CH_1+i, m_chkChan[i]);
		DDX_Control(pDX, IDC_STC_CH_1+i, m_stcChanNo[i]);
	}	
	DDX_Control(pDX, IDC_CHK_SELECT_ALL, m_chkSelALl);
	DDX_Control(pDX, IDC_CBO_CH_PAGE, m_cboPage);
}

BEGIN_MESSAGE_MAP(CLS_ChanCheck, CDialog)
	ON_BN_CLICKED(IDC_CHK_SELECT_ALL, &CLS_ChanCheck::OnBnClickedChkSelectAll)
	ON_CBN_SELCHANGE(IDC_CBO_CH_PAGE, &CLS_ChanCheck::OnCbnSelchangeCboChPage)
	ON_BN_CLICKED(IDC_BTN_FTONT_PAGE, &CLS_ChanCheck::OnBnClickedBtnFtontPage)
	ON_BN_CLICKED(IDC_BTN_NEXT_PAGE, &CLS_ChanCheck::OnBnClickedBtnNextPage)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_CHK_CH_1,IDC_CHK_CH_64, &CLS_ChanCheck::OnBnClickedChkChan)
END_MESSAGE_MAP()


BOOL CLS_ChanCheck::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemTextEx(IDC_CHK_SELECT_ALL, IDS_CONFIG_LINK_SELECT_ALL);	

	m_cboPage.ResetContent();
	for (int i=0; i<MAX_PAGE_NUM; i++)
	{
		m_cboPage.InsertString(i, IntToStr(i+1).c_str());
	}
	m_cboPage.SetCurSel(m_iCurrentPage);

	for (int i=0; i<MAX_CHAN_PAGE; i++)
	{
		m_chkChan[i].EnableWindow(FALSE);
	}

	return TRUE;
}

void CLS_ChanCheck::OnLanguageChanged( int _iLanguage )
{
	SetDlgItemTextEx(IDC_CHK_SELECT_ALL, IDS_CONFIG_LINK_SELECT_ALL);	
}

void CLS_ChanCheck::InitData(int _iChanNum, int* _iEnable)
{
	if (_iChanNum > MAX_CHAN_PAGE*4)
	{
		_iChanNum = MAX_CHAN_PAGE*4;
	}

	for (int i=0; i<MAX_BITSET_COUNT; i++)
	{
		m_iEnable[i] = _iEnable[i];
	}

	m_iChanNum = _iChanNum;
	OnShowPage(m_iCurrentPage);

	m_chkSelALl.SetCheck(BST_CHECKED);
	for (int i=0; i<m_iChanNum; i++)
	{
		if ((m_iEnable[i/LEN_32]>>i%LEN_32&1) == 0)
		{
			m_chkSelALl.SetCheck(BST_UNCHECKED);
			break;
		}
	}
}

void CLS_ChanCheck::OnBnClickedChkSelectAll()
{
	OnCheckAll(m_chkSelALl.GetCheck());
}

void CLS_ChanCheck::OnCheckAll(BOOL _blChk)
{
	for (int i=0; i<LEN_16; i++)
	{
		m_iEnable[i] = 0;
	}

	if (BST_CHECKED == _blChk)
	{
		for (int i=0; i<m_iChanNum; i++)
		{
			m_iEnable[i/LEN_32] |= 1<<i%LEN_32;
		}
	}
	
	OnChanCheck();
}

void CLS_ChanCheck::OnChanCheck()
{
	for (int i=0; i<LEN_64; i++)
	{
		if (m_iCurrentPage*LEN_64+i<m_iChanNum)
		{
			m_chkChan[i].SetCheck(1<<i&m_iEnable[m_iCurrentPage*2+i/LEN_32]?TRUE:FALSE);
		}
		else
		{
			m_chkChan[i].SetCheck(FALSE);
		}
	}
}

void CLS_ChanCheck::OnShowPage(int _iPage)
{
	for (int i=0; i<MAX_CHAN_PAGE; i++)
	{
		m_stcChanNo[i].SetWindowText(IntToStr(MAX_CHAN_PAGE*_iPage+i+1).c_str());
	}

	for (int i=0; i<MAX_CHAN_PAGE; i++)
	{
		m_chkChan[i].SetCheck(FALSE);
		m_chkChan[i].EnableWindow(FALSE);
	}

	for (int i=0; i<LEN_64; i++)
	{
		if ((m_iCurrentPage*LEN_64+i)<m_iChanNum)
		{
			m_chkChan[i].SetCheck(1<<i&m_iEnable[m_iCurrentPage*2+i/LEN_32]?TRUE:FALSE);
			m_chkChan[i].EnableWindow(TRUE);
		}
		else
		{
			m_chkChan[i].SetCheck(FALSE);
		}
	}
}

void CLS_ChanCheck::OnCbnSelchangeCboChPage()
{
	int iSel = m_cboPage.GetCurSel();
	if (iSel == m_iCurrentPage)
	{
		return;
	}
	m_iCurrentPage = iSel;
	OnShowPage(m_iCurrentPage);
}

void CLS_ChanCheck::OnBnClickedBtnFtontPage()
{
	if (m_iCurrentPage == 0)
	{
		return;
	}
	m_iCurrentPage--;
	m_cboPage.SetCurSel(m_iCurrentPage);
	OnShowPage(m_iCurrentPage);
}

void CLS_ChanCheck::OnBnClickedBtnNextPage()
{
	if (m_iCurrentPage == MAX_PAGE_NUM-1)
	{
		return;
	}
	m_iCurrentPage++;
	m_cboPage.SetCurSel(m_iCurrentPage);
	OnShowPage(m_iCurrentPage);
}

void CLS_ChanCheck::OnBnClickedChkChan(UINT _uiID)
{
	int index = _uiID - IDC_CHK_CH_1;
	if (m_chkChan[index].GetCheck() == BST_CHECKED)
	{
		m_iEnable[m_iCurrentPage*2+index/LEN_32] |= 1<<index;
	} 
	else
	{
		m_iEnable[m_iCurrentPage*2+index/LEN_32] &= ~(1<<index);
	}

	m_chkSelALl.SetCheck(BST_CHECKED);
	for (int i=0; i<m_iChanNum; i++)
	{
		if ((m_iEnable[i/LEN_32]>>i%LEN_32&1) == 0)
		{
			m_chkSelALl.SetCheck(BST_UNCHECKED);
			break;
		}
	}
}

void CLS_ChanCheck::GetChanValue(int * _iEnable )
{
	memcpy(_iEnable, m_iEnable, sizeof(int)*MAX_BITSET_COUNT );
}
