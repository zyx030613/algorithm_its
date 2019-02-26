#pragma once

#include "../BasePage.h"
#include "afxwin.h"

#include "Events/VCAEventBasePage.h"
#include "Events/VCAEVENT_Abandum.h"
#include "Events/VCAEVENT_Tripwire.h"
#include "Events/VCAEVENT_Perimeter.h"
#include "Events/VCAEVENT_VideoDetect.h"
#include "Events/VCAEVENT_FaceRec.h"
#include "Events/VCAEVENT_Track.h"
#include "Events/VCAEVENT_Crowd.h"
#include "Events/VCAEVENT_Flux.h"
#include "Events/VCAEVENT_LeaveDetect.h"
#include "Events/VCAEVENT_TripwireEx.h"
#include "Events/VCAEVENT_AudioDiagnose.h"
#include "Events/VCAEVENT_MulitTrip.h"
#include "Events/VCAEVENT_Lisence.h"
#include "Events/VCAEVENT_RiverClean.h"
#include "Events/VCAEVENT_Dredge.h"
#include "Events/VCAEVENT_Fight.h"
#include "Events/VCAEVENT_OnDutyDetect.h"
#include "Events/VCAEVENT_IllegalPark.h"
#include "Events/VCAEVENT_GoodsLose.h"
#include "Events/VCAEVENT_Running.h"
#include "Events/VCAEVENT_Hover.h"
#include "Events/VCAEVENT_Parking.h"
#include "Events/VCAEVENT_GoodsDerelict.h"
#include "Events/VCAEVENT_PersonStat.h"
#include "Events/VCAEVENT_VideoDetectNew.h"
#include "Events/VCAEVENT_AudioDiagnoseNew.h"
#include "Events/VCAEVENT_FaceRecNew.h"
#include "Events/VCAEVENT_CrowdNew.h"
#include "Events/VCAEVENT_Protect.h"
#include "Events/VCAEVENT_HeatMap.h"
#include "Events/VCAEVENT_WindowDetevtion.h"
#include "Events/VCAEVENT_WaterLevelDetection.h"
#include "Events/VCAEVENT_SluiceGate.h"

// CLS_VCAEventPage dialog
//����Ϊ��������㷨����ǰ��������ʾ������������

typedef enum __tagEEventSel
{
	TRIPWIRE_SEL = 0,	//������
	MULIT_TRIP_SEL,		//˫����
	PERIMETER_SEL,		//�ܽ���
	HOVER_SEL,			//�ǻ�
	PARKING_SEL,		//ͣ��
	RUNNING_SEL,		//����
	GOODS_DERELICT_SEL,	//������
	GOODS_LOSE_SEL,		//������
	PROTECT_SEL,		//����
	HEATMAP_SEL,		//�ȶ�ͼ
	WATER_LEVEL_DETECTION_SEL,//ˮλ���
	RIVER_CLEAN_SEL,	//Ư������
	DREDGE_SEL,			//���ɺ�ɳ
	SLUICE_GATE_SEL,	//բ�ż��
	VIDEODETECT_NEW_SEL,
	AUDIO_DIAGNOSE_NEW_SEL,
	FACEREC_NEW_SEL,
	ABANDUM_SEL,
	TRACK_SEL,
	CROWD_NEW_SEL,
	FLUX_SEL,
	LEAVE_DETECT_SEL,
	TRIPWIRE_SEL_EX,
	LISENCE_SEL,
	FIGHT_SEL,
	ONDUTY_DETECT_SEL,
	ILLEGAL_PARK_SEL,
	PERSON_STAT_SEL,
	FACEREC_SEL,
	VIDEODETECT_SEL,
	CROWD_SEL,
	AUDIO_DIAGNOSE_SEL,
	WINDOW_DETECTION_SEL,		//�������
	MAX_EVENT_NUM
}EEventSel;
class CLS_VCAEventPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_VCAEventPage)

public:
	CLS_VCAEventPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_VCAEventPage();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_VCA_EVENTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	void	EventPageInit();
	CLS_VCAEventBasePage* m_plArrEventPage[MAX_EVENT_NUM];
	int		m_iLogonID;
	int		m_iChannelNo;
	int		m_iStreamNO;
	int     m_iSceneID;


	virtual void OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo);
	virtual void OnLanguageChanged(int _iLanguage);
	virtual void OnMainNotify(int _iLogonID,int _wParam, void* _iLParam, void* _iUser);


	int		RestartVCALib(int _iLogonID, int _iChannel = -1);
	void	UpdateUIText();
	void	UpdatePageUI();
	bool	IsDigistChannel(int _iChannelNO);
	int     ReturnParamVCA();
	void    SetParamVCA(int _param);
	void    SetVCAStatus(bool _bStatus);
	void    InitVcaList();
public:
	afx_msg void OnBnClickedButtonRuleSet();
//	afx_msg void OnCbnSelendcancelComboEvnetid();

public:
	CComboBox m_cboEventType;
	virtual BOOL OnInitDialog();
	CStatic m_staticEventGroup;
	afx_msg void OnCbnSelchangeComboEvnetid();
	afx_msg void OnDestroy();

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CComboBox m_cboRuleID;
	CButton m_chkRuleValid;
	CEdit m_edtRuleName;
	CButton m_chkVCAEnable;

	vca_TVCAParam *m_pVcaParam;
	afx_msg void OnCbnSelchangeComboRuleid();
	afx_msg void OnBnClickedCheckVcaEnable();
	afx_msg void OnCbnSelchangeComboVcaEnable();
private:
	CComboBox m_cboEnable;
	CButton m_checkVCA[9];
public:
	CComboBox m_cboSceneID;
	afx_msg void OnBnClickedCheckValidRule();
	afx_msg void OnBnClickedButtonSceneidset();
	afx_msg void OnBnClickedButtonCallScene();
	afx_msg void OnCbnSelchangeComboSceneid();
	CEdit m_cdtSceneName;
	afx_msg void OnBnClickedVcaCheck1();

	afx_msg void OnBnClickedVcaCheck3();
	afx_msg void OnBnClickedVcaCheck4();
	afx_msg void OnBnClickedVcaCheck6();
	afx_msg void OnBnClickedVcaCheck8();
	afx_msg void OnBnClickedVcaCheck9();

	int GetSelIndexByEventID(int _iEventID);
	int GetEventIDBySelIndex(int _iSelIndex);
	void CallCurScene();
	int GetDemoUseRule();
};
