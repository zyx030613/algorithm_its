#include "StdAfx.h"
#include "SortListCtrl.h"

CSortListCtrl::CSortListCtrl(void):m_iSort(1),m_iSubItem(-1)
{

}

CSortListCtrl::~CSortListCtrl(void)
{

}

BEGIN_MESSAGE_MAP(CSortListCtrl, CListCtrl)
ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &CSortListCtrl::OnLvnColumnclick)
END_MESSAGE_MAP()

void CSortListCtrl::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if (pNMLV->iSubItem == m_iSubItem)
	{
		m_iSort = -1*m_iSort;
	}
	else
	{
		m_iSubItem = pNMLV->iSubItem;
		m_iSort = 1;
	}

	for (int i = 0;i < GetItemCount(); ++i)
	{
		SetItemData(i,i);
	}

	int iType = GetSortType(m_iSubItem);
	switch(iType)
	{
	case SORT_TYPE_STRING:
		SortItems(StringItemCompare,(DWORD_PTR)this);
		break;
	case SORT_TYPE_INT:
		SortItems(IntItemCompare,(DWORD_PTR)this);
		break;
	case SORT_TYPE_IP:
		SortItems(IPItemCompare,(DWORD_PTR)this);
		break;
	default:
		break;
	}

	*pResult = 0;
}

int __stdcall StringItemCompare( LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort )
{
	CSortListCtrl* pThis = (CSortListCtrl*)lParamSort;
	CString strData1 = pThis->GetItemText((int)lParam1,pThis->m_iSubItem);
	CString strData2 = pThis->GetItemText((int)lParam2,pThis->m_iSubItem);
	return pThis->m_iSort*strData1.Compare(strData2);
}

int __stdcall IntItemCompare(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort)
{
	CSortListCtrl* pThis = (CSortListCtrl*)lParamSort;
	CString strData1 = pThis->GetItemText((int)lParam1,pThis->m_iSubItem);
	CString strData2 = pThis->GetItemText((int)lParam2,pThis->m_iSubItem);
	int iData1 = atoi((LPSTR)(LPCTSTR)strData1);
	int iData2 = atoi((LPSTR)(LPCTSTR)strData2);
	return pThis->m_iSort*(iData1-iData2);
}

int __stdcall IPItemCompare(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort)
{
	CSortListCtrl* pThis = (CSortListCtrl*)lParamSort;
	char cIP1[16] = {0};
	char cIP2[16] = {0};
	int iField11 = 0;
	int iField12 = 0;
	int iField13 = 0;
	int iField14 = 0;
	int iField21 = 0;
	int iField22 = 0;
	int iField23 = 0;
	int iField24 = 0;
	pThis->GetItemText((int)lParam1,pThis->m_iSubItem,cIP1,16);
	sscanf_s(cIP1,"%d.%d.%d.%d",&iField11,&iField12,&iField13,&iField14);
	pThis->GetItemText((int)lParam2,pThis->m_iSubItem,cIP2,16);
	sscanf_s(cIP2,"%d.%d.%d.%d",&iField21,&iField22,&iField23,&iField24);

	int iRet = 0;
	if (iField11 == iField21)
	{
		if (iField12 == iField22)
		{
			if (iField13 == iField23)
			{
				iRet = iField14-iField24;
			}
			else
			{
				iRet = iField13-iField23;
			}
		}
		else
		{
			iRet = iField12-iField22;
		}
	}
	else
	{
		iRet = iField11-iField21;
	}

	return pThis->m_iSort*iRet;
}

int CSortListCtrl::SetSortType(int _iColumn,int _iType )
{
	CHeaderCtrl* pHeader = GetHeaderCtrl();
	if (NULL == pHeader || _iType < SORT_TYPE_MIN || _iType >= SORT_TYPE_MAX)
	{
		return -1;
	}

	HDITEM tItem = {0};
	tItem.mask = HDI_LPARAM;
	tItem.lParam = _iType;
	pHeader->SetItem(_iColumn,&tItem);
	return 0;
}

int CSortListCtrl::GetSortType( int _iColumn )
{
	CHeaderCtrl* pHeader = GetHeaderCtrl();
	if (NULL == pHeader)
	{
		return -1;
	}

	HDITEM tItem = {0};
	tItem.mask = HDI_LPARAM;
	pHeader->GetItem(_iColumn,&tItem);
	return (int)tItem.lParam;
}