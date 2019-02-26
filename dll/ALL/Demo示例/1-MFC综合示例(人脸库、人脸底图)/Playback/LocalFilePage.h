#ifndef _LOCAL_FILE_TAB_H
#define _LOCAL_FILE_TAB_H

#include "../BasePage.h"

// CLS_LocalFilePage dialog

class CLS_LocalFilePage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_LocalFilePage)

public:
	CLS_LocalFilePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_LocalFilePage();

// Dialog Data
	enum { IDD = IDD_DLG_PBK_LOCAL_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

#endif
