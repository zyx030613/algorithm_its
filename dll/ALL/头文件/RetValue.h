/************************************************************************/
/*COMMON RETURN                                                                     
*/
/************************************************************************/
#define RET_NOTHING					((void)0)
#define RET_SUCCESS					0			//�ɹ�
#define RET_FAILED					-1			//ʧ��
#define RET_MALLOC_FALIED			-2

#define	RET_BUFFER_FULL				-11			//��������������û�з��뻺����
#define	RET_BUFFER_WILL_BE_FULL		-18			//�������������������ݵ�Ƶ��
#define	RET_BUFFER_WILL_BE_EMPTY	-19			//�����գ�����������ݵ�Ƶ��
#define RET_BUFFER_IS_OK			-20			//�������Է�����

#define RET_GETDATA_END				-50			//��ȡ�������������������ļ�β���߲���ֹͣλ��
				
#define RET_INVALID_PARA			-101		//�Ƿ�����
#define RET_DEVICE_NOT_LOGON		-102		//�豸δ��¼
#define RET_MEMORY_OVER				-103		//�ڴ治��
#define RET_ERR_AUTHORITY			-104		//Ȩ�޲���
#define RET_SEND_LIST_FULL			-105		//�����б�����


#define RET_SYSTEM_CALL_FAILED		-200		//����ϵͳ����ʧ��
#define RET_SDK_CALL_FAILED     	-201		//����SDK�ӿ�ʧ��
#define RET_INNER_CALL_FAILED		-202		//�����ڲ�����ʧ��
#define RET_DRAW_CREATE_FAILED		-203		//����Drawʧ��
#define RET_NOSUPPORT_PARATYPE		-204		//��֧�ֵĲ�������
#define RET_LIGHTLOGON_NETERROR		-205		//��������Э���������
#define RET_LIGHTLOGON_GET_TIME_OUT	-206		//��������Э��ȴ��豸�ظ���ʱ
#define RET_DEV_NOT_SUPPORT			-207		//�豸��֧�ֵ�ǰ������ȡ��ʽ

