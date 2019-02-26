#ifndef _NETREGSTRUCT_H
#define _NETREGSTRUCT_H

//返回信息码
#define  ERR_SUCCESS		   0     // 成功
#define  ERR_WSASTARTUP        1001  //Windows Socket初始化失败
#define  ERR_PORTNOTAVAILABLE  1002  //端口已被占用
#define  ERR_WRONGPASSWORD     1003  //密码错误
#define  ERR_ACCOUNTLIMIT      1004  //超出最大帐户数
#define  ERR_NVSHOSTLIMIT      1005
#define  ERR_NOTRANSFER        1006
#define  ERR_NONVSHOST         1007
#define  ERR_DNSHOSTLIMIT      1008
#define  ERR_CLIENTHOSTLIMIT   1009
#define  ERR_INVALIDUSERNAME   1010
#define  ERR_INVALIDPASSWORD   1011
#define  ERR_DSHOSTLIMIT       1012
#define  ERR_ERRPARA           1013  //函数传入无效参数
#define  ERR_STSTEM	    	   1014  //系统错误

#define  ERR_DATABASE	       101  // 数据库操作失败
//#define  ERR_INVALIDPARA	   102  // 字符中含有非法字符，不能包含< > / ' " & ?等HTML中使用的字符
#define  ERR_NOHOST		       103  // 该主机名不存在
//#define  ERR_NOACCOUNT	       104  // 该用户不存在
//#define  ERR_NOPASS		       105  // 主机密码错误
#define  ERR_TOLONGSTR	       106  // 字串超过规定的长度，用户ID、主机ID最长20位，密码最长10位
#define  ERR_CONNECT		   107  // 通迅错误


//新增错误码
#define  ERR_CONNMIDSVR      151   // 应该重联二级注册中心
#define  ERR_NOPROXY         152   // 没有代理服务器可用
#define  ERR_NORIGHT         153   // 没有创建用户的权限
#define  ERR_WAITSVR         154   // 应该等待服务器的应答
#define  ERR_INVALIDDATA     155   // 非法数据

#define  ERR_DATA               301                   //zyp add
#define  ERR_TIMEOUT            302
#define  ERR_USERINVALID        303
#define  ERR_FACTORYIDINVALID   304


/*---------------------------------------------------------------------------*/
//消息定义
#define  MSG_REGCENTER               (WM_USER+101)    
/*---------------------------------------------------------------------------*/
//消息的WPARAM参数的高16位定义如下
#define  PARA_ADDUSER                0x101          //添加用户

#define  PARA_REGISTE_DS             0x111          //目录服务器注册
#define  PARA_UPDATE_DS              0x112          //目录服务器更新
#define  PARA_DISCONNECT_DS          0x113          //目录服务器断开

#define  PARA_REGISTE_NVS            0x121          //Nvs注册
#define  PARA_UPDATE_NVS             0x122          //Nvs更新
#define  PARA_DISCONNECT_NVS         0x123          //Nvs断开

#define  PARA_REGISTE_PROXY          0x131          //代理注册
#define  PARA_UPDATE_PROXY           0x134          //代理更新
#define  PARA_DISCONNECT_PROXY       0x135          //代理断开

#define  PARA_REGISTE_CLIENT         0x141          //待连接的客户端注册
#define  PARA_UPDATE_CLIENT          0x142          //待连接的客户端更新
#define  PARA_DISCONNECT_CLIENT      0x143          //待连接的客户端断开

#define  PARA_REGISTE_TRANSFER       0x151          //视频转发关系注册
#define  PARA_UPDATE_TRANSFER        0x152          //视频转发关系更新
#define  PARA_DISCONNECT_TRANSFER    0x153          //视频转发关系断开

#define  PARA_REGISTE_ASSIGN         0x161          //代理分配注册
#define  PARA_UPDATE_ASSIGN          0x162          //代理分配更新
#define  PARA_DELETE_ASSIGN          0x163          //代理分配删除
#define  PARA_DELETEALL_ASSIGN       0x164          //代理分配全部删除

#define  PARA_REGISTE_DNS            0x171          //域名解析注册
#define  PARA_UPDATE_DNS             0x172          //域名解析更新
#define  PARA_DISCONNECT_DNS         0x173          //域名解析断开

#define  PARA_REGISTE_CONNCLIENT     0x181          //客户端注册
#define  PARA_UPDATE_CONNCLIENT      0x182          //客户端更新
#define  PARA_DISCONNECT_CONNCLIENT  0x183          //客户端断开

//zhangyanping add
#define  TYPE_BYNAME      0            //按照nvs name
#define  TYPE_BYID        1            //按照nvs id

#define  REG_PAGE_SIZE    20           //页面大小

//#define  LEN_128         128           //128字节的数据长度
//#define  LEN_64           64           //64字节数据长度
//#define  32           32           //32字节数据长度，可用于IP，时间,用户名，密码等

//数据类型

#define  TYPE_NVS        0                      //nvs
#define  TYPE_PROXY      1                      //代理服务器
#define  TYPE_CLIENT     2                      //待连接的客户端
#define  TYPE_TRANSFER   3                      //视频转发关系
#define  TYPE_ASSIGN     4                      //代理分配
#define  TYPE_DNS        5                      //域名解析
#define  TYPE_DS         6                      //二级注册中心
#define  TYPE_P2P_NVS    7                      //p2p nvs
#define  TPYE_P2P_CLIENT 8                      //使用P2P连接方式的客户端


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


typedef struct   //NVS的标识，无论时UDP注册中心，还是TCP的主动模式，NVS都靠此标识
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

typedef struct    //代理信息
{
    char cProxyIP[32];
    int  iProxyPort;

    st_Reserve m_stReserve;
}st_ProxyInfo,*pst_ProxyInfo;                           

//==============================================================================

//NVS的注册信息
typedef struct
{
    char            szPrimaryDS[32];     //首选目录服务器IP
	st_NvsSingle    m_stNvs;
    char            szRegTime[32];       //更新注册时间
    unsigned long   dwClientConnNum;         //客户端连接个数
    bool            bRegister;               //数据类型：true-直接注册的数据，false-备份的数据

    st_Reserve m_stReserve;
}REG_NVS,*REG_PNVS;

//代理服务器的信息
typedef struct
{
    char            szPrimaryDS[32];     //首选目录服务器IP
    st_ProxyInfo    m_stProxy;               //代理信息
    char            szRegTime[32];       //更新注册时间
    bool            bRegister;               //数据类型：true-直接注册的数据，false-备份的数据

    st_Reserve m_stReserve;
}REG_PROXY,*REG_PPROXY;


//客户端通过代理连接前端某个设备时，连接设备的参数
typedef struct
{
    unsigned long   dwConnectID;             //ConnectID
    unsigned long   dwConnMode;              //网络模式
    unsigned long   dwChannel;               //通道号
    unsigned long   dwStreamType;            //码流类型
    char            szClientIP[32];      //客户端IP

    st_Reserve m_stReserve;
}CLICONN,*PCLICONN;


//(待连接的)客户端信息
typedef struct
{
    char          szPrimaryDS[32];     //首选目录服务器IP
    st_NvsSingle  stNvs;                   //该客户端请求连接的nvs

    int         iWaitTime;
    int         iTriedNum;
    char        szTriedProxy[3][32];

    st_Reserve m_stReserve;
}REG_CLIENT,*REG_PCLIENT;


//视频转发关系表
typedef struct
{
    st_NvsSingle  stNvs;                 //NVS
    st_ProxyInfo  m_stPorxy;             //该NVS对应的代理
    bool blRegister;                     //数据类型：true-直接注册的数据，false-备份的数据

    st_Reserve m_stReserve;
}REG_TRANSFER,*REG_PTRANSFER;


//手动分配的代理
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
    char            szRegTime[32];  //更新注册时间

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


//客户端通过目录服务器，请求登陆某个NVS时，发送的请求信息
typedef struct   //CLIENT*CONNECTNVS*DS IP*用户名*密码*Nvs IP*NVS Name*Nvs Type*Factory ID
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
