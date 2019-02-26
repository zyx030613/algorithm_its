#pragma once
#include "../BasePage.h"
#include "afxwin.h"

#include "AdvParam/VCAEventAdvParamBase.h"
#include "AdvParam/VCAAdvParam_River.h"
#include "AdvParam/VCAAdvParamWld.h"

typedef enum __tagEEventAdvSel
{
	RIVER_CLEAN_ADV_SEL = 0,
	WLD_ADV_SEL = 1,
	MAX_EVENT_ADV_NUM
}EEventAdvSel;

class CLS_VCAEvnetsAdvParam : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_VCAEvnetsAdvParam)

public:
	CLS_VCAEvnetsAdvParam(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLS_VCAEvnetsAdvParam();

// 对话框数据
	enum { IDD = IDD_DLG_CFG_VCA_EVENTS_ADV_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CLS_VCAEventAdvParamBase* m_plArrEventAdvPage[MAX_EVENT_ADV_NUM];
	int		m_iLogonID;
	int		m_iChannelNo;
	int		m_iStreamNO;
	int		m_iCurrentSel;
	int     m_iScreenID;

protected:
	CComboBox m_cboAdvEventType;
	CComboBox m_cboAdvSceneID;
public:
	void UI_Updata();
	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _iLogonID,int _wParam, void* _iLParam, void* _iUser);

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCboEventId();	
	afx_msg void OnCbnSelchangeCboAdvSceneid();
};
