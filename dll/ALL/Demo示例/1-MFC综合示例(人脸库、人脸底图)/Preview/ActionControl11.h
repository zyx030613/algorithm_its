//0x00-0x63ͨ�ù���
//0x00-0x2f����������
#define     REGISTER                0         //ע�Ṧ��
#define     MOVE_UP                 1         //��̨����
#define     MOVE_UP_STOP            2         //��̨����ͣ
#define     MOVE_DOWN               3         //��̨����
#define     MOVE_DOWN_STOP          4         //��̨����ͣ
#define     MOVE_LEFT               5         //��̨����
#define     MOVE_LEFT_STOP          6         //��̨����ͣ
#define     MOVE_RIGHT              7         //��̨����
#define     MOVE_RIGHT_STOP         8         //��̨����ͣ
#define     MOVE_UP_LEFT            9         //��̨����
#define     MOVE_UP_LEFT_STOP       10         //��̨����ͣ
#define     MOVE_UP_RIGHT           11        //��̨����
#define     MOVE_UP_RIGHT_STOP      12        //��̨����ͣ
#define     MOVE_DOWN_LEFT          13        //��̨����
#define     MOVE_DOWN_LEFT_STOP     14        //��̨����ͣ
#define     MOVE_DOWN_RIGHT         15        //��̨����
#define     MOVE_DOWN_RIGHT_STOP    16        //��̨����ͣ
#define     SET_LEFT_BORDER         17        //������߽�
#define     SET_RIGHT_BORDER        18        //�����ұ߽�
#define     SET_UP_BORDER           19        //�����ϱ߽�
#define     SET_DOWN_BORDER         20        //�����±߽�
#define     HOR_AUTO                21        //ˮƽ�Զ�
#define     HOR_AUTO_STOP           22        //ˮƽ�Զ�ͣ
#define     SET_HOR_AUTO_BEGIN      23        //��ˮƽ�Զ���ʼ��
#define     SET_HOR_AUTO_END        24        //��ˮƽ�Զ�������
#define     SET_HOR_AUTO_SPEED      25        //����ˮƽ�Զ��ٶ�
#define     VER_AUTO                26        //��ֱ�Զ�
#define     SET_VER_AUTO_BEGIN      27        //���ô�ֱ�Զ���ʼ��
#define     SET_VER_AUTO_END        28        //���ô�ֱ�Զ�������
#define     SET_VER_AUTO_SPEED      29        //���ô�ֱ�Զ��ٶ�
#define     VER_AUTO_STOP           30        //��ֱ�Զ�ͣ

#define     ZOOM_BIG                31        //�䱶��
#define     ZOOM_BIG_STOP           32        //�䱶��ͣ
#define     ZOOM_SMALL              33        //�䱶С
#define     ZOOM_SMALL_STOP         34        //�䱶Сͣ
#define     FOCUS_FAR               35        //�۽�Զ
#define     FOCUS_FAR_STOP          36        //�۽�Զͣ
#define     FOCUS_NEAR              37        //�۽���
#define     FOCUS_NEAR_STOP         38        //�۽���ͣ
#define     IRIS_OPEN               39        //��Ȧ��
#define     IRIS_OPEN_STOP          40        //��Ȧ��ͣ
#define     IRIS_CLOSE              41        //��Ȧ��
#define     IRIS_CLOSE_STOP         42        //��Ȧ��ͣ

#define     LIGHT_ON                43        //�ƹ⿪
#define     LIGHT_OFF               44        //�ƹ��
#define     POWER_ON                45        //��Դ��
#define     POWER_OFF               46        //��Դ��
#define     RAIN_ON                 47        //��ˢ��
#define     RAIN_OFF                48        //��ˢ��
#define     TALK_ON                 49        //�Խ���
#define     TALK_OFF                50        //�Խ���
#define     DEF_ON                  51        //����
#define     DEF_OFF                 52        //����

#define     BROWSE                  53        //��ѯ
#define     ALARM_ANSWER            54        //����Ӧ��
#define     STATE_ASK               55        //�����ϴ�����״̬


//0x30-0x4f�������
#define     MOVE                    60        //������
#define     MOVE_STOP               61        //������ͣ
#define     CALL_VIEW               62        //�������
#define     SET_VIEW                63        //����Ԥ��
#define     DELETE_VIEW             64        //ɾ��Ԥ�þ���
#define     SEQUENCE_BEGIN          65        //��ʼѲ��
#define     SEQUENCE_END            66        //ֹͣѲ��
#define     ADD_PRESET              67        //���Ѳ����
#define     DELETE_PRESET           68        //ɾ��Ѳ����
#define     CLEAR_SEQUENCE          69        //���Ѳ������
#define     TIME_SEQUENCE           70        //����Ѳ��ʱ��
#define     SET_GUARD               71        //���ÿ���λ
#define     DELETE_GUARD            72        //ɾ������λ
#define     GET_HOR_AUTO_SPEED      73        //���ˮƽ�Զ��ٶ�
#define     GET_TRACK_TIME          74        //���Ѳ��ʱ��
#define     GET_TRACK_SEQUENCE      75        //���Ѳ������
#define     GUARD_TIME              76        //���ÿ���λ��ʱ��
#define     GET_VIEW_LIST           77        //��þ�������

#define     MEMU_OPEN				78        //�򿪲˵�	Call 95
#define     MEMU_CLOSE              79        //�رղ˵�	Call 96

//0x64-0xc7ר�ù���
#define     SWITCH                  101        //�ֶ������л�
#define     SWITCH_MONITOR          102        //�м�
#define     SWITCH_VIDICON          103        //�е�
#define     SWITCH_ORDER            104        //˳���л�
#define     SWITCH_ORDER_STOP       105        //˳���л�ͣ
#define     SWITCH_GROUP            106        //Ⱥ���л�
#define     SWITCH_GROUP_STOP       107        //Ⱥ���л�ͣ

#define     PROTOCOL_MOVE_UP                 1			//ptz up
#define     PROTOCOL_MOVE_DOWN               2			//ptz down
#define     PROTOCOL_MOVE_LEFT               3			//ptz left
#define     PROTOCOL_MOVE_RIGHT              4			//ptz right
#define     PROTOCOL_MOVE_UP_RIGHT           5			//ptz top right
#define     PROTOCOL_MOVE_UP_LEFT            6			//ptz top left
#define     PROTOCOL_MOVE_DOWN_RIGHT         7			//ptz down right
#define     PROTOCOL_MOVE_DOWN_LEFT          8			//ptz down left
#define     PROTOCOL_MOVE_STOP				 9			//stop ptz up
#define     PROTOCOL_ZOOM_BIG                10        //�䱶��
#define     PROTOCOL_ZOOM_SMALL              11        //�䱶С

#define     PROTOCOL_FOCUS_NEAR              13        //�۽���
#define     PROTOCOL_FOCUS_FAR               14        //�۽�Զ

#define     PROTOCOL_IRIS_OPEN               17        //��Ȧ��
#define     PROTOCOL_IRIS_CLOSE              18        //��Ȧ��
#define     PROTOCOL_RAIN_ON                 19        //��ˢ��
#define     PROTOCOL_RAIN_OFF                20        //��ˢ��
#define     PROTOCOL_LIGHT_ON                21        //�ƹ⿪
#define     PROTOCOL_LIGHT_OFF               22        //�ƹ��
#define     PROTOCOL_HOR_AUTO				 23		  //horizontal auto
#define     PROTOCOL_HOR_AUTO_STOP			 24		  //stop horizontal auto
#define     PROTOCOL_CALL_VIEW				 25		  //����Ԥ��λ

#define     PROTOCOL_SET_VIEW				 28		  //����Ԥ��λ
#define     PROTOCOL_POWER_ON                29        //��Դ��
#define     PROTOCOL_POWER_OFF               30        //��Դ��
