
#include "stdafx.h"
#include "NetClientDemo.h"
#include "SerialInfo.h"
#include "Common\CommonFun.h"

// CLS_SerialInfo �Ի���
#define DATABIT                      7             //����λ
#define DATABITLENGTH                9             //����λ
#define RATENUM                     11             //�����ʸ���
#define DEVICE_LIST_TYPE             2             //�����豸����

IMPLEMENT_DYNAMIC(CLS_SerialInfo, CDialog)

CLS_SerialInfo::CLS_SerialInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CLS_SerialInfo::IDD, pParent)
{

}

CLS_SerialInfo::~CLS_SerialInfo()
{
}

void CLS_SerialInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_COM, m_cboComNo);
	DDX_Control(pDX, IDC_CBO_BAUDRATE, m_cboBaudRate);
	DDX_Control(pDX, IDC_CBO_PARITY, m_cboParityBit);
	DDX_Control(pDX, IDC_CBO_BYTESIZE, m_cboDataBit);
	DDX_Control(pDX, IDC_EDT_STOPBITES, m_edtStopBit);
	DDX_Control(pDX, IDC_CBO_DEVICE_TYPE, m_cboDevType);
	DDX_Control(pDX, IDC_EDT_COLLECT_TIME, m_edtGap);
	DDX_Control(pDX, IDC_SPIN_COM_COLLECT_TIME, m_spinGap);
}


BEGIN_MESSAGE_MAP(CLS_SerialInfo, CDialog)
	ON_BN_CLICKED(IDC_BTN_COM_SET, &CLS_SerialInfo::OnBnClickedBtnComSet)
END_MESSAGE_MAP()


// CLS_SerialInfo ��Ϣ�������

BOOL CLS_SerialInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemTextEx(IDC_STC_COM, IDS_CONFIG_COM_NUM);
	SetDlgItemTextEx(IDC_STC_BAUDRATE, IDS_CONFIG_COM_BAUDRATE);
	SetDlgItemTextEx(IDC_STC_PARITY, IDS_CONFIG_COM_PARITY);
	SetDlgItemTextEx(IDC_STC_BYTESIZE, IDS_CONFIG_COM_BYTESIZE);
	SetDlgItemTextEx(IDC_STC_STOPBITES, IDS_CONFIG_COM_STOPBITES);
	SetDlgItemTextEx(IDC_STC_DEVICETYPE, IDS_CONFIG_COM_DEV_TYPE);
	SetDlgItemTextEx(IDC_STC_COLLECT_TIME, IDS_CONFIG_COM_COLLECT_TIME);
	SetDlgItemTextEx(IDC_BTN_COM_SET, IDS_CONFIG_LINK_SURE);

	InitWidget();

	UpdateUI();

	return TRUE;
}

void CLS_SerialInfo::InitWidget()
{
	//���ں�
	m_cboComNo.EnableWindow(FALSE);
	//������
	m_cboBaudRate.ResetContent();
	int iArrRate[RATENUM] = {300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 76800, 115200};
	for (int i = 0; i < RATENUM; ++i)
	{
		CString cstrRate;
		cstrRate.Format(_T("%d"), iArrRate[i]);
		m_cboBaudRate.AddString(_T(cstrRate));
	}
	m_cboBaudRate.SetCurSel(5);
	//У��λ
	m_cboParityBit.ResetContent();
	InsertString(m_cboParityBit,0,IDS_CFG_COM_PARITY_NONE);
	InsertString(m_cboParityBit,1,IDS_CFG_COM_PARITY_ODD);
	InsertString(m_cboParityBit,2,IDS_CFG_COM_PARITY_EVEN);
	m_cboParityBit.SetItemData(0,'n');
	m_cboParityBit.SetItemData(1,'o');
	m_cboParityBit.SetItemData(2,'e');
	m_cboParityBit.SetCurSel(1);
	//����λ
	m_cboDataBit.ResetContent();
	for (int i = DATABIT; i < DATABITLENGTH; ++i)
	{
		m_cboDataBit.AddString(IntToString(i));
	}
	m_cboDataBit.SetCurSel(1);

	//ֹͣλ
	m_edtStopBit.SetWindowText("1");

	//�豸����
	InsertString(m_cboDevType,0,_T("TD��ʪ��"));
	InsertString(m_cboDevType,1,_T("ɽ��UPS"));
	InsertString(m_cboDevType,2,_T("�����"));
	InsertString(m_cboDevType,3,_T("�����"));
	InsertString(m_cboDevType,4,_T("��Ӣ��ʪ��"));
	InsertString(m_cboDevType,5,_T("����è"));
	//�ɼ����
	m_edtGap.SetLimitText(3);
	m_spinGap.SetRange(1, 255);
	m_spinGap.SetBuddy(&m_edtGap);	
	m_edtGap.SetWindowText("1");
}

void CLS_SerialInfo::UpdateUI()
{
	//���ں�
	CString cstrComNo;
	cstrComNo.Format(_T("COM %d"), m_iComNo);
	m_cboComNo.ResetContent();
	m_cboComNo.AddString(cstrComNo);
	m_cboComNo.SetCurSel(0);

	ComDevice comdev = {0};
	comdev.iSize = sizeof(ComDevice);
	comdev.iComNo = m_iComNo;
	int iBytesReturned = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_COM_DEVICE, -1, &comdev, sizeof(comdev), &iBytesReturned);
	if(iRet < 0)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig(%d,%d,%d)"
			,m_iLogonID,comdev.iComNo,iBytesReturned);
		return;
	}

	//�豸����
	string strType;
	CString cstrTypeName;
	GetDevTypeName(comdev.iDeviceType, strType);
	cstrTypeName = strType.c_str();
	int iIndex = m_cboDevType.FindString(-1, cstrTypeName);
	m_cboDevType.SetCurSel(iIndex);

	//�ɼ����---��Ҫ����param
	CString cstrField;
	AfxExtractSubString(cstrField, comdev.cParam, 0, DH_PARAM_SEPARATOR);
	int iState = atoi((LPSTR)(LPCTSTR)cstrField);
	//m_edtGap.SetWindowText(IntToCString(iState));

	//�Ӹ�ʽ���з�����������ʡ�У��λ������λ��ֹͣλ
	int iBaudRate = 0;
	char cParityBit = 0;
	int iDataBit = 0;
	int iStopBit = 0;
	sscanf_s(comdev.cComFormat,"%d,%c,%d,%d",&iBaudRate,&cParityBit,sizeof(char),&iDataBit,&iStopBit);
	
	//������
	SetDlgItemInt(IDC_CBO_BAUDRATE,iBaudRate);

	//У��λ
	for (int i = 0; i < m_cboParityBit.GetCount(); ++i)
	{
		if(cParityBit == m_cboParityBit.GetItemData(i))
		{
			m_cboParityBit.SetCurSel(i);
			break;
		}
	}

	//����λ
	m_cboDataBit.SelectString(-1,IntToString(iDataBit));

	//ֹͣλ
	m_edtStopBit.SetWindowText(IntToString(iStopBit));
}

void CLS_SerialInfo::OnBnClickedBtnComSet()
{
	ComDevice comdev = {0};
	comdev.iSize = sizeof(COMFORMAT);
	comdev.iComNo = m_iComNo;
	
	//�豸����
	int iIndex = m_cboDevType.GetCurSel();
	if (iIndex < 0)
	{
		return;
	}
	comdev.iDeviceType = (int)m_cboDevType.GetItemData(iIndex);

	//������
	int iBaudRate = GetDlgItemInt(IDC_CBO_BAUDRATE);

	//У��λ
	char cParityBit = (char)m_cboParityBit.GetItemData(m_cboParityBit.GetCurSel());
	
	//����λ
	int iDataBit = GetDlgItemInt(IDC_CBO_BYTESIZE);

	//ֹͣλ
	int iStopBit = GetDlgItemInt(IDC_EDT_STOPBITES);

	//ƴ�Ӹ�ʽ��
	sprintf_s(comdev.cComFormat,"%d,%c,%d,%d",iBaudRate,cParityBit,iDataBit,iStopBit);

	//�ɼ����
	int iData = GetDlgItemInt(IDC_EDT_COLLECT_TIME);
	CString strParam;
	strParam.Format(_T("%d"), iData);
	memcpy(comdev.cParam, (LPSTR)(LPCTSTR)strParam, strParam.GetLength()+1);

	int iRet = -1;
	iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_COM_DEVICE, -1, &comdev, sizeof(comdev));
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig(%d,%d,%s)"
			,m_iLogonID,comdev.iComNo,comdev.cComFormat);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig(%d,%d,%s)"
			,m_iLogonID,comdev.iComNo,comdev.cComFormat);
		return;
	}
	EndDialog(IDOK);
}

void CLS_SerialInfo::GetDevTypeName(int _iDevType, string &_strDevName)
{
	CString cstrDevTypeName = "";
	switch(_iDevType)
	{
	case 0:
		cstrDevTypeName = GetTextEx(IDS_CFG_COM_PARITY_NONE);//��
		break;
	case 1:
		//cstrDevTypeName.LoadString("TD��ʪ��");
		cstrDevTypeName = GetTextEx(IDS_POWER_DEV_HUMITURE);//("TD��ʪ��")
		break;
	default:
		break;
	}
	_strDevName = cstrDevTypeName.GetBuffer();
	cstrDevTypeName.ReleaseBuffer();
}
