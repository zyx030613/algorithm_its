#ifndef _NETREGSTRUCT_H
#define _NETREGSTRUCT_H

//������Ϣ��
#define  ERR_SUCCESS		   0     // �ɹ�
#define  ERR_WSASTARTUP        1001  //Windows Socket��ʼ��ʧ��
#define  ERR_PORTNOTAVAILABLE  1002  //�˿��ѱ�ռ��
#define  ERR_WRONGPASSWORD     1003  //�������
#define  ERR_ACCOUNTLIMIT      1004  //��������ʻ���
#define  ERR_NVSHOSTLIMIT      1005
#define  ERR_NOTRANSFER        1006
#define  ERR_NONVSHOST         1007
#define  ERR_DNSHOSTLIMIT      1008
#define  ERR_CLIENTHOSTLIMIT   1009
#define  ERR_INVALIDUSERNAME   1010
#define  ERR_INVALIDPASSWORD   1011
#define  ERR_DSHOSTLIMIT       1012
#define  ERR_ERRPARA           1013  //����������Ч����
#define  ERR_STSTEM	    	   1014  //ϵͳ����

#define  ERR_DATABASE	       101  // ���ݿ����ʧ��
//#define  ERR_INVALIDPARA	   102  // �ַ��к��зǷ��ַ������ܰ���< > / ' " & ?��HTML��ʹ�õ��ַ�
#define  ERR_NOHOST		       103  // ��������������
//#define  ERR_NOACCOUNT	       104  // ���û�������
//#define  ERR_NOPASS		       105  // �����������
#define  ERR_TOLONGSTR	       106  // �ִ������涨�ĳ��ȣ��û�ID������ID�20λ�������10λ
#define  ERR_CONNECT		   107  // ͨѸ����


//����������
#define  ERR_CONNMIDSVR      151   // Ӧ����������ע������
#define  ERR_NOPROXY         152   // û�д������������
#define  ERR_NORIGHT         153   // û�д����û���Ȩ��
#define  ERR_WAITSVR         154   // Ӧ�õȴ���������Ӧ��
#define  ERR_INVALIDDATA     155   // �Ƿ�����

#define  ERR_DATA               301                   //zyp add
#define  ERR_TIMEOUT            302
#define  ERR_USERINVALID        303
#define  ERR_FACTORYIDINVALID   304


/*---------------------------------------------------------------------------*/
//��Ϣ����
#define  MSG_REGCENTER               (WM_USER+101)    
/*---------------------------------------------------------------------------*/
//��Ϣ��WPARAM�����ĸ�16λ��������
#define  PARA_ADDUSER                0x101          //����û�

#define  PARA_REGISTE_DS             0x111          //Ŀ¼������ע��
#define  PARA_UPDATE_DS              0x112          //Ŀ¼����������
#define  PARA_DISCONNECT_DS          0x113          //Ŀ¼�������Ͽ�

#define  PARA_REGISTE_NVS            0x121          //Nvsע��
#define  PARA_UPDATE_NVS             0x122          //Nvs����
#define  PARA_DISCONNECT_NVS         0x123          //Nvs�Ͽ�

#define  PARA_REGISTE_PROXY          0x131          //����ע��
#define  PARA_UPDATE_PROXY           0x134          //�������
#define  PARA_DISCONNECT_PROXY       0x135          //����Ͽ�

#define  PARA_REGISTE_CLIENT         0x141          //�����ӵĿͻ���ע��
#define  PARA_UPDATE_CLIENT          0x142          //�����ӵĿͻ��˸���
#define  PARA_DISCONNECT_CLIENT      0x143          //�����ӵĿͻ��˶Ͽ�

#define  PARA_REGISTE_TRANSFER       0x151          //��Ƶת����ϵע��
#define  PARA_UPDATE_TRANSFER        0x152          //��Ƶת����ϵ����
#define  PARA_DISCONNECT_TRANSFER    0x153          //��Ƶת����ϵ�Ͽ�

#define  PARA_REGISTE_ASSIGN         0x161          //�������ע��
#define  PARA_UPDATE_ASSIGN          0x162          //����������
#define  PARA_DELETE_ASSIGN          0x163          //�������ɾ��
#define  PARA_DELETEALL_ASSIGN       0x164          //�������ȫ��ɾ��

#define  PARA_REGISTE_DNS            0x171          //��������ע��
#define  PARA_UPDATE_DNS             0x172          //������������
#define  PARA_DISCONNECT_DNS         0x173          //���������Ͽ�

#define  PARA_REGISTE_CONNCLIENT     0x181          //�ͻ���ע��
#define  PARA_UPDATE_CONNCLIENT      0x182          //�ͻ��˸���
#define  PARA_DISCONNECT_CONNCLIENT  0x183          //�ͻ��˶Ͽ�

//zhangyanping add
#define  TYPE_BYNAME      0            //����nvs name
#define  TYPE_BYID        1            //����nvs id

#define  REG_PAGE_SIZE    20           //ҳ���С

//#define  LEN_128         128           //128�ֽڵ����ݳ���
//#define  LEN_64           64           //64�ֽ����ݳ���
//#define  32           32           //32�ֽ����ݳ��ȣ�������IP��ʱ��,�û����������

//��������

#define  TYPE_NVS        0                      //nvs
#define  TYPE_PROXY      1                      //���������
#define  TYPE_CLIENT     2                      //�����ӵĿͻ���
#define  TYPE_TRANSFER   3                      //��Ƶת����ϵ
#define  TYPE_ASSIGN     4                      //�������
#define  TYPE_DNS        5                      //��������
#define  TYPE_DS         6                      //����ע������
#define  TYPE_P2P_NVS    7                      //p2p nvs
#define  TPYE_P2P_CLIENT 8                      //ʹ��P2P���ӷ�ʽ�Ŀͻ���


typedef struct                            //This structure is for reserve.
{
    int   m_iReserved1;
    unsigned long m_dwReserved2;
    char  m_cReserved1[32];
    char  m_cReserved2[64];
}st_Reserve;

typedef struct
{
    char    szUserName[32];
    char    szPassWord[32];
    char    szReference[32];
    int     iReference;

    st_Reserve m_stReserve;
}MSG_LPARAM;


typedef struct   //NVS�ı�ʶ������ʱUDPע�����ģ�����TCP������ģʽ��NVS�����˱�ʶ
{
    char  cNvsIP[32];
    char  cNvsName[32];
    int   iNvsType;
    char  cFactoryID[32];
    st_Reserve m_stReserve;
}st_NvsSingle,*pst_NvsSingle;

typedef struct  //INNER*NVSREGISTER*userID*nvsName*password*nvsIP*nvsPort*nvsFactoryID*nvsType*nvsChannels
{
    char          m_cUserName[32];
    char          m_cPwd[32];
    st_NvsSingle  stNvs;
    int           m_iPort;
    int           m_iChannel;
    
    st_Reserve    m_stReserve;
}st_DNSRegInfo,*pst_DNSRegInfo;

typedef struct    //������Ϣ
{
    char cProxyIP[32];
    int  iProxyPort;

    st_Reserve m_stReserve;
}st_ProxyInfo,*pst_ProxyInfo;                           

//==============================================================================

//NVS��ע����Ϣ
typedef struct
{
    char            szPrimaryDS[32];     //��ѡĿ¼������IP
	st_NvsSingle    m_stNvs;
    char            szRegTime[32];       //����ע��ʱ��
    unsigned long   dwClientConnNum;         //�ͻ������Ӹ���
    bool            bRegister;               //�������ͣ�true-ֱ��ע������ݣ�false-���ݵ�����

    st_Reserve m_stReserve;
}REG_NVS,*REG_PNVS;

//�������������Ϣ
typedef struct
{
    char            szPrimaryDS[32];     //��ѡĿ¼������IP
    st_ProxyInfo    m_stProxy;               //������Ϣ
    char            szRegTime[32];       //����ע��ʱ��
    bool            bRegister;               //�������ͣ�true-ֱ��ע������ݣ�false-���ݵ�����

    st_Reserve m_stReserve;
}REG_PROXY,*REG_PPROXY;


//�ͻ���ͨ����������ǰ��ĳ���豸ʱ�������豸�Ĳ���
typedef struct
{
    unsigned long   dwConnectID;             //ConnectID
    unsigned long   dwConnMode;              //����ģʽ
    unsigned long   dwChannel;               //ͨ����
    unsigned long   dwStreamType;            //��������
    char            szClientIP[32];      //�ͻ���IP

    st_Reserve m_stReserve;
}CLICONN,*PCLICONN;


//(�����ӵ�)�ͻ�����Ϣ
typedef struct
{
    char          szPrimaryDS[32];     //��ѡĿ¼������IP
    st_NvsSingle  stNvs;                   //�ÿͻ����������ӵ�nvs

    int         iWaitTime;
    int         iTriedNum;
    char        szTriedProxy[3][32];

    st_Reserve m_stReserve;
}REG_CLIENT,*REG_PCLIENT;


//��Ƶת����ϵ��
typedef struct
{
    st_NvsSingle  stNvs;                 //NVS
    st_ProxyInfo  m_stPorxy;             //��NVS��Ӧ�Ĵ���
    bool blRegister;                     //�������ͣ�true-ֱ��ע������ݣ�false-���ݵ�����

    st_Reserve m_stReserve;
}REG_TRANSFER,*REG_PTRANSFER;


//�ֶ�����Ĵ���
typedef struct
{
    st_NvsSingle  stNvs;
    st_ProxyInfo  m_stPorxy;

    st_Reserve m_stReserve;
}REG_ASSIGN,*REG_PASSIGN;


//DNS
typedef struct
{
    st_DNSRegInfo   m_stDNSInfo;
    char            szRegTime[32];  //����ע��ʱ��

    st_Reserve      m_stReserve;
}REG_DNS,*REG_PDNS;


typedef struct
{
    st_NvsSingle    m_stNvs;
    char            m_cHoleIP[32];
    int             m_iHolePort;

    st_Reserve      m_stReserve;
}REG_P2PNVS,*RREG_P2PNVS;
//==============================================================================


//�ͻ���ͨ��Ŀ¼�������������½ĳ��NVSʱ�����͵�������Ϣ
typedef struct   //CLIENT*CONNECTNVS*DS IP*�û���*����*Nvs IP*NVS Name*Nvs Type*Factory ID
{
    char cDSIP[32];
    char cUserName[32];
    char cUserPwd[32];
    st_NvsSingle  stNvs;

    st_Reserve m_stReserve;
}st_LogOnInfo,*pst_LogOnInfo;


typedef int (__stdcall *cbkGetDNSList)(int _iCount,REG_DNS *_regDNS);
typedef int (__stdcall *cbkGetNVSList)(int _iCount,st_NvsSingle *_stNvs);

#endif 
