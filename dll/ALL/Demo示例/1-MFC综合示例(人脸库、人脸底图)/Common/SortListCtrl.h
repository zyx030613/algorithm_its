#ifndef _SORT_LIST_CTRL_H_
#define _SORT_LIST_CTRL_H_

#include "afxcmn.h"

#define SORT_TYPE_MIN				-1
#define SORT_TYPE_NONE		(SORT_TYPE_MIN+0)
#define SORT_TYPE_STRING	(SORT_TYPE_MIN+1)
#define SORT_TYPE_INT		(SORT_TYPE_MIN+2)
#define SORT_TYPE_IP		(SORT_TYPE_MIN+3)
#define SORT_TYPE_MAX		(SORT_TYPE_MIN+4)

class CSortListCtrl :
	public CListCtrl
{
public:
	CSortListCtrl(void);
	~CSortListCtrl(void);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);
	friend int __stdcall StringItemCompare(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort);
	friend int __stdcall IntItemCompare(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort);
	friend int __stdcall IPItemCompare(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort);
	int SetSortType(int _iColumn,int _iType);//-1:None 0:String(Ä¬ÈÏÖµ) 1:int 2:IP
	int GetSortType(int _iColumn);

private:
	int	m_iSubItem;	//ÁÐ
	int m_iSort; //1:ÉýÐò -1:½µÐò
	
};

#endif