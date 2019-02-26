#ifndef  _H_FACE_ATTR_INFO_DEFINE_H_
#define  _H_FACE_ATTR_INFO_DEFINE_H_

#define _USE_ZH

//��������
typedef enum
{
	FACE_ATTR_Unknow			= -1,
	FACE_ATTR_Age				= 0,	//0-����
	FACE_ATTR_Sex				,		//1-�Ա�
	FACE_ATTR_Mask				,		//2-����
	FACE_ATTR_Beard				,		//3-����	
	FACE_ATTR_OpenEye			,		//4-����
	FACE_ATTR_OpenMouth			,		//5-����
	FACE_ATTR_Glasses			,		//6-�۾�
	FACE_ATTR_Race				,		//7-����
	FACE_ATTR_Expression		,		//8-����
	FACE_ATTR_Smile				,		//9-΢Ц
	FACE_ATTR_Value				,		//10-��ֵ
	FACE_ATTR_Nation			,		//11-����
	FACE_ATTR_12				,		//
	FACE_ATTR_13				,		//
	FACE_ATTR_14				,		//
	FACE_ATTR_15				,		//
	FACE_ATTR_16				,		//
	FACE_ATTR_refid				,		//ref id
	FACE_ATTR_Objtype			,		//object type
}EnumFaceAttrInfo;

#ifdef _USE_ZH
const char* g_strFaceAttrName[] = {"����", "�Ա�", "����", "����", "����", "����", "�۾�", "����", "����", "΢Ц", "��ֵ", "����"
, "Attr12", "Attr13", "Attr14", "Attr15", "Attr16", "RefId", "Ŀ������"};
#else
const char* g_strFaceAttrName[] = {"Age", "Sex", "Mask", "Beard", "OpenEye", "OpenMouth", "Glasses", "Race", "Expression", "Smile", "Value", "Nation"
, "Attr12", "Attr13", "Attr14", "Attr15", "Attr16", "RefId", "ObjType"};
#endif

#define MAX_FACE_ATTR_NUM			(sizeof(g_strFaceAttrName)/sizeof(char*))

//�Ա� 
typedef enum
{
	ATTR_SEX_Unknow				= -1,
	ATTR_SEX_Female   			= 0,  	//0-Ů
	ATTR_SEX_Male       			,  	//1-��
} EnumAttrSex;

#ifdef _USE_ZH
const char* g_strAttrSexName[] = {"Ů", "��"};
#else
const char* g_strAttrSexName[] = {"Female", "Male"};
#endif

#define MAX_ATTR_SEX_NUM			(sizeof(g_strAttrSexName)/sizeof(char*))


//���� ���� ���� ����
typedef enum
{
	ATTR_COMMON_Unknow			= -1,
	ATTR_COMMON_No       		= 0,  	//0-��
	ATTR_COMMON_Yes     		,  		//1-��
} EnumAttrCommon;

#ifdef _USE_ZH
const char* g_strAttrCommonName[] = {"��", "��"};
#else
const char* g_strAttrCommonName[] = {"No", "Yes"};
#endif

#define MAX_ATTR_COMMON_NUM			(sizeof(g_strAttrCommonName)/sizeof(char*))

//�۾� 
typedef enum
{
	ATTR_GLASSES_Unknow			= -1,
	ATTR_GLASSES_No   			= 0,  	//0-��
	ATTR_GLASSES_Wear       	,  		//1-��ͨ�۾�
	ATTR_GLASSES_Sunglasses    	,  		//2-̫����
} EnumAttrGlasses;

#ifdef _USE_ZH
const char* g_strAttrGlassesName[] = {"��", "��", "̫����"};
#else
const char* g_strAttrGlassesName[] = {"No", "Wear", "Sunglasses"};
#endif

#define MAX_ATTR_GLASSES_NUM			(sizeof(g_strAttrGlassesName)/sizeof(char*))

//����
typedef enum
{
	ATTR_RACE_Unknow			= -1,
	ATTR_RACE_Yellow   			= 0,  	//0-������
	ATTR_RACE_Black     		,  		//1-������
	ATTR_RACE_White    			,  		//2-������
	ATTR_RACE_Uygur    			,  		//3-ά����
} EnumAttrRace;

#ifdef _USE_ZH
const char* g_strAttrRaceName[] = {"������", "������", "������", "ά����"};
#else
const char* g_strAttrRaceName[] = {"Yellow", "Black", "White", "Uygur"};
#endif

#define MAX_ATTR_RACE_NUM			(sizeof(g_strAttrRaceName)/sizeof(char*))
//����
typedef enum
{
	ATTR_EXPRESSION_Unknow		= -1,
	ATTR_EXPRESSION_Angry     	= 0,  	//0-����
	ATTR_EXPRESSION_Calm      	,  		//1-ƽ��
	ATTR_EXPRESSION_Confused  	,  		//2-���
	ATTR_EXPRESSION_Disgust   	,  		//3-����
	ATTR_EXPRESSION_Happy     	,  		//4-����
	ATTR_EXPRESSION_Sad       	,  		//5-����
	ATTR_EXPRESSION_Scared    	,  		//6-����
	ATTR_EXPRESSION_Surprised 	,  		//7-����
	ATTR_EXPRESSION_Squint    	,  		//8-б��
	ATTR_EXPRESSION_Scream    	,  		//9-���
} EnumAttrExpression;

#ifdef _USE_ZH
const char* g_strAttrExpressionName[] = {"����", "ƽ��", "���", "����", "����", "����", "����", "����", "б��", "���"};
#else
const char* g_strAttrExpressionName[] = {"Angry", "Calm", "Confused", "Disgust", "Happy", "Sad", "Scared", "Surprised", "Squint", "Scream"};
#endif

#define MAX_ATTR_EXPRESSION_NUM			(sizeof(g_strAttrExpressionName)/sizeof(char*))


//΢Ц

//�����¼� -С��50��Ϊû��΢Ц������50��Ϊ��΢Ц
//�����¼� -С��50��Ϊû��΢Ц������50��Ϊ��΢Ц
#define FACE_ATTR_SMILE_THRESHOLD_VALUE			50
typedef enum
{
	ATTR_SMILE_Unknow			= -1,
	ATTR_SMILE_No       		= 0,  	
	ATTR_SMILE_Yes     			,  		
} EnumAttrSmile;

#ifdef _USE_ZH
const char* g_strAttrSmileName[] = {"��", "��"};
#else
const char* g_strAttrSmileName[] = {"No", "Yes"};
#endif

#define MAX_ATTR_SMILE_NUM			(sizeof(g_strAttrSmileName)/sizeof(char*))

//����
typedef enum
{
	ATTR_NATION_Unknow			= -1,
	ATTR_NATION_Han       		= 0,  	//0-����
	ATTR_NATION_Other     		,  		//����
} EnumAttrNation;

#ifdef _USE_ZH
const char* g_strAttrNationName[] = {"��", "����"};
#else
const char* g_strAttrNationName[] = {"Han", "Other"};
#endif

#define MAX_ATTR_NATION_NUM			(sizeof(g_strAttrNationName)/sizeof(char*))

#ifdef _USE_ZH
const char* g_strAttrObjTypeName[] = {"����", "��", "��ֹ��", "����"};
#else
const char* g_strAttrObjTypeName[] = {"Face", "Vehicle", "Nonmotor", "Pedestrian"};
#endif

#define MAX_ATTR_OBJTYPE_NUM			(sizeof(g_strAttrObjTypeName)/sizeof(char*))


#endif
