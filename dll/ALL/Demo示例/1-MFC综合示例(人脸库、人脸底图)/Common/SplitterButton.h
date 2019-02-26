#pragma once
#include "afxwin.h"
#include "SplitterCtrl.h"

#define CHILD_NUM 8

class CLS_SplitterButton :
	public CButton
{
public:
	CLS_SplitterButton(void);
	~CLS_SplitterButton(void);
	void SetTimeChangeNotify(TimeChangeNotify _pfTimeChange,void* _pContext=NULL){m_Splitter.SetTimeChangeNotify(_pfTimeChange,_pContext);}
	int SetChildNum(int _iNum);
	int GetChildNum(){return (int)m_vctChild.size();}
	void SetColor(UINT _iID,COLORREF _bkColor);
	void SetTime(UINT _iID,int _iBegain,int _iEnd);
	int FindChild(UINT _iID);
	bool AddChild(UINT _iID,int _iBegainTime = -1,int _iEndTime = -1);
	bool RemoveChild(UINT _iID);
	bool RemoveAll();
	int GetBegainTime(UINT _iID);
	int GetEndTime(UINT _iID);

private:
	SplitterCtrl m_Splitter;
	vector<ChildWnd*> m_vctChild;
	
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
protected:
	virtual void PreSubclassWindow();
};
