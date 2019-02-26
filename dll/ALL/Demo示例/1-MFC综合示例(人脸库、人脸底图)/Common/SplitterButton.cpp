#include "stdafx.h"
#include "SplitterButton.h"

BEGIN_MESSAGE_MAP(CLS_SplitterButton, CButton)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

CLS_SplitterButton::CLS_SplitterButton(void)
{
	
}

CLS_SplitterButton::~CLS_SplitterButton(void)
{

}

int CLS_SplitterButton::SetChildNum( int _iNum )
{
	m_vctChild.clear();
	ChildWnd* pWnd = NULL;
	CRect rc;
	GetClientRect(&rc);
	if(m_Splitter.Create(this,WS_CHILD | WS_VISIBLE,rc,150)==false)
		return 0;

	m_Splitter.AddRow();
	for (int i = 0;i < _iNum;++i)
	{
		pWnd = new ChildWnd();
		if (pWnd)
		{
			if (pWnd->Create(&m_Splitter,i) == 0)
			{
				delete pWnd;
				pWnd = NULL;
				return i+1;
			}
			else
			{
				m_vctChild.push_back(pWnd);
				m_Splitter.AddColumn();
				m_Splitter.SetWindow(0,i,pWnd->GetSafeHwnd());
			}
		}
	}

	m_Splitter.Update();

	return (int)m_vctChild.size();
}

int CLS_SplitterButton::FindChild(UINT _iID)
{
	int iIndex = 0;
	ChildWnd* pWnd = NULL;
	vector<ChildWnd*>::iterator it = m_vctChild.begin();
	for (;it < m_vctChild.end();++it)
	{
		ChildWnd* pWnd = *it;
		if (pWnd && pWnd->GetID() == _iID)
		{
			return iIndex;
		}
		++iIndex;
	}

	return -1;
}

bool CLS_SplitterButton::AddChild(UINT _iID,int _iBegainTime,int _iEndTime)
{
	int index = FindChild(_iID);
	if (index < 0)
	{
		CRect rc;
		GetClientRect(&rc);
		ChildWnd* pWnd = new ChildWnd();
		if (pWnd)
		{
			if (pWnd->Create(&m_Splitter,_iID))
			{
				int iInsert = 0;
				ChildWnd* pWndInsert = NULL;
				vector<ChildWnd*>::iterator it = m_vctChild.begin();
				for (;it < m_vctChild.end();++it)
				{
					ChildWnd* pWndInsert = *it;
					if (pWndInsert && pWndInsert->GetID() > _iID)
					{
						m_Splitter.InsertColumn(iInsert);
						m_Splitter.SetWindow(0,iInsert,pWnd->GetSafeHwnd());
						m_vctChild.insert(it,pWnd);
						if (_iBegainTime < 0 || _iEndTime < 0)
						{
							int iBegainTime = pWndInsert->GetBegainTime();
							int iEndTime = pWndInsert->GetEndTime();
							pWndInsert->SetTime(iBegainTime,iBegainTime+(iEndTime-iBegainTime)/2);
							pWnd->SetTime(iBegainTime+(iEndTime-iBegainTime)/2,iEndTime);
						}
						else
						{
							pWnd->SetTime(_iBegainTime,_iEndTime);
						}
						m_Splitter.Update();
						return true;
					}
					++iInsert;
				}
				if (m_vctChild.empty())
				{
					pWndInsert = NULL;
				}
				else
				{
					pWndInsert = m_vctChild.back();
				}
				m_Splitter.AddColumn();
				m_Splitter.SetWindow(0,iInsert,pWnd->GetSafeHwnd());
				m_vctChild.insert(it,pWnd);
				if (pWndInsert)
				{
					if (_iBegainTime < 0 || _iEndTime < 0)
					{
						int iBegainTime = pWndInsert->GetBegainTime();
						int iEndTime = pWndInsert->GetEndTime();
						pWndInsert->SetTime(iBegainTime,iBegainTime+(iEndTime-iBegainTime)/2);
						pWnd->SetTime(iBegainTime+(iEndTime-iBegainTime)/2,iEndTime);
					}
					else
					{
						pWnd->SetTime(_iBegainTime,_iEndTime);
					}
				}				
				m_Splitter.Update();
			}
			else
			{
				delete pWnd;
				pWnd = NULL;
				return false;
			}
		}
	}
	else
	{
		ChildWnd* pWnd = m_vctChild[index];
		if (pWnd)
		{
			if (_iBegainTime >= 0 && _iEndTime < TIME_LEN)
			{
				pWnd->SetTime(_iBegainTime,_iEndTime);
			}
		}
	}

	return true;
}

bool CLS_SplitterButton::RemoveChild(UINT _iID)
{
	int iIndex = 0;
	ChildWnd* pWnd = NULL;
	vector<ChildWnd*>::iterator it = m_vctChild.begin();
	for (;it < m_vctChild.end();++it)
	{
		ChildWnd* pWnd = *it;
		if (pWnd && pWnd->GetID() == _iID)
		{
			int iBegin = pWnd->GetBegainTime();
			unsigned int iNext = pWnd->GetIndex();
			//pWnd->SetTime(0,0);
			m_vctChild.erase(it);
			m_Splitter.DeleteColumn(iIndex);
			pWnd->DestroyWindow();
			delete pWnd;
			pWnd = NULL;
			
			if (iNext+1 < m_vctChild.size())
			{
				m_vctChild[iNext]->SetTime(iBegin,m_vctChild[iNext]->GetEndTime());
			}
			break;
		}
		++iIndex;
	}
	m_Splitter.Update();

	return true;
}

bool CLS_SplitterButton::RemoveAll()
{
	vector<ChildWnd*>::iterator it = m_vctChild.begin();
	while(it != m_vctChild.end())
	{
		ChildWnd* pWnd = *it;
		m_vctChild.erase(it);
		m_Splitter.DeleteColumn(0);
		if (pWnd)
		{
			pWnd->DestroyWindow();
			delete pWnd;
			pWnd = NULL;
		}
		it = m_vctChild.begin();
	}
	m_Splitter.Update();
	return true;
}

void CLS_SplitterButton::SetColor( UINT _iID,COLORREF _bkColor )
{
	ChildWnd* pWnd = NULL;
	vector<ChildWnd*>::iterator it = m_vctChild.begin();
	for (;it < m_vctChild.end();++it)
	{
		ChildWnd* pWnd = *it;
		if (pWnd && pWnd->GetID() == _iID)
		{
			pWnd->SetBackColor(_bkColor);
			pWnd->Invalidate();
		}
	}
	m_Splitter.Update();
}

void CLS_SplitterButton::SetTime( UINT _iID,int _iBegain,int _iEnd )
{
	ChildWnd* pWnd = NULL;
	vector<ChildWnd*>::iterator it = m_vctChild.begin();
	for (;it < m_vctChild.end();++it)
	{
		ChildWnd* pWnd = *it;
		if (pWnd && pWnd->GetID() == _iID)
		{
			pWnd->SetTime(_iBegain,_iEnd);
			m_Splitter.Update();
		}
	}
}


void CLS_SplitterButton::OnDestroy()
{
	CButton::OnDestroy();

	ChildWnd* pWnd = NULL;
	vector<ChildWnd*>::iterator it = m_vctChild.begin();
	for (;it != m_vctChild.end();++it)
	{
		pWnd = *it;
		if (pWnd)
		{
			delete pWnd;
			pWnd = NULL;
		}
	}
}

void CLS_SplitterButton::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)
{

	// TODO:  Add your code to draw the specified item
}

void CLS_SplitterButton::PreSubclassWindow()
{
	this->ModifyStyle(0,BS_OWNERDRAW);

	CButton::PreSubclassWindow();
}

int CLS_SplitterButton::GetBegainTime(UINT _iID)
{
	ChildWnd* pWnd = NULL;
	vector<ChildWnd*>::iterator it = m_vctChild.begin();
	for (;it < m_vctChild.end();++it)
	{
		ChildWnd* pWnd = *it;
		if (pWnd && pWnd->GetID() == _iID)
		{
			return pWnd->GetBegainTime();
		}
	}

	return 0;
}

int CLS_SplitterButton::GetEndTime(UINT _iID)
{
	ChildWnd* pWnd = NULL;
	vector<ChildWnd*>::iterator it = m_vctChild.begin();
	for (;it < m_vctChild.end();++it)
	{
		ChildWnd* pWnd = *it;
		if (pWnd && pWnd->GetID() == _iID)
		{
			return pWnd->GetEndTime();
		}
	}

	return 0;
}