#ifndef  _H_FACE_ATTR_INFO_DEFINE_H_
#define  _H_FACE_ATTR_INFO_DEFINE_H_

#define _USE_ZH

//人脸属性
typedef enum
{
	FACE_ATTR_Unknow			= -1,
	FACE_ATTR_Age				= 0,	//0-年龄
	FACE_ATTR_Sex				,		//1-性别
	FACE_ATTR_Mask				,		//2-口罩
	FACE_ATTR_Beard				,		//3-胡子	
	FACE_ATTR_OpenEye			,		//4-睁眼
	FACE_ATTR_OpenMouth			,		//5-张嘴
	FACE_ATTR_Glasses			,		//6-眼镜
	FACE_ATTR_Race				,		//7-种族
	FACE_ATTR_Expression		,		//8-表情
	FACE_ATTR_Smile				,		//9-微笑
	FACE_ATTR_Value				,		//10-颜值
	FACE_ATTR_Nation			,		//11-民族
	FACE_ATTR_12				,		//
	FACE_ATTR_13				,		//
	FACE_ATTR_14				,		//
	FACE_ATTR_15				,		//
	FACE_ATTR_16				,		//
	FACE_ATTR_refid				,		//ref id
	FACE_ATTR_Objtype			,		//object type
}EnumFaceAttrInfo;

#ifdef _USE_ZH
const char* g_strFaceAttrName[] = {"年龄", "性别", "口罩", "胡子", "睁眼", "张嘴", "眼镜", "种族", "表情", "微笑", "颜值", "民族"
, "Attr12", "Attr13", "Attr14", "Attr15", "Attr16", "RefId", "目标类型"};
#else
const char* g_strFaceAttrName[] = {"Age", "Sex", "Mask", "Beard", "OpenEye", "OpenMouth", "Glasses", "Race", "Expression", "Smile", "Value", "Nation"
, "Attr12", "Attr13", "Attr14", "Attr15", "Attr16", "RefId", "ObjType"};
#endif

#define MAX_FACE_ATTR_NUM			(sizeof(g_strFaceAttrName)/sizeof(char*))

//性别 
typedef enum
{
	ATTR_SEX_Unknow				= -1,
	ATTR_SEX_Female   			= 0,  	//0-女
	ATTR_SEX_Male       			,  	//1-男
} EnumAttrSex;

#ifdef _USE_ZH
const char* g_strAttrSexName[] = {"女", "男"};
#else
const char* g_strAttrSexName[] = {"Female", "Male"};
#endif

#define MAX_ATTR_SEX_NUM			(sizeof(g_strAttrSexName)/sizeof(char*))


//口罩 胡子 睁眼 张嘴
typedef enum
{
	ATTR_COMMON_Unknow			= -1,
	ATTR_COMMON_No       		= 0,  	//0-无
	ATTR_COMMON_Yes     		,  		//1-有
} EnumAttrCommon;

#ifdef _USE_ZH
const char* g_strAttrCommonName[] = {"无", "有"};
#else
const char* g_strAttrCommonName[] = {"No", "Yes"};
#endif

#define MAX_ATTR_COMMON_NUM			(sizeof(g_strAttrCommonName)/sizeof(char*))

//眼镜 
typedef enum
{
	ATTR_GLASSES_Unknow			= -1,
	ATTR_GLASSES_No   			= 0,  	//0-无
	ATTR_GLASSES_Wear       	,  		//1-普通眼镜
	ATTR_GLASSES_Sunglasses    	,  		//2-太阳镜
} EnumAttrGlasses;

#ifdef _USE_ZH
const char* g_strAttrGlassesName[] = {"无", "有", "太阳镜"};
#else
const char* g_strAttrGlassesName[] = {"No", "Wear", "Sunglasses"};
#endif

#define MAX_ATTR_GLASSES_NUM			(sizeof(g_strAttrGlassesName)/sizeof(char*))

//种族
typedef enum
{
	ATTR_RACE_Unknow			= -1,
	ATTR_RACE_Yellow   			= 0,  	//0-黄种人
	ATTR_RACE_Black     		,  		//1-黑种人
	ATTR_RACE_White    			,  		//2-白种人
	ATTR_RACE_Uygur    			,  		//3-维族人
} EnumAttrRace;

#ifdef _USE_ZH
const char* g_strAttrRaceName[] = {"黄种人", "黑种人", "白种人", "维族人"};
#else
const char* g_strAttrRaceName[] = {"Yellow", "Black", "White", "Uygur"};
#endif

#define MAX_ATTR_RACE_NUM			(sizeof(g_strAttrRaceName)/sizeof(char*))
//表情
typedef enum
{
	ATTR_EXPRESSION_Unknow		= -1,
	ATTR_EXPRESSION_Angry     	= 0,  	//0-生气
	ATTR_EXPRESSION_Calm      	,  		//1-平静
	ATTR_EXPRESSION_Confused  	,  		//2-厌恶
	ATTR_EXPRESSION_Disgust   	,  		//3-困惑
	ATTR_EXPRESSION_Happy     	,  		//4-高兴
	ATTR_EXPRESSION_Sad       	,  		//5-悲伤
	ATTR_EXPRESSION_Scared    	,  		//6-害怕
	ATTR_EXPRESSION_Surprised 	,  		//7-惊讶
	ATTR_EXPRESSION_Squint    	,  		//8-斜视
	ATTR_EXPRESSION_Scream    	,  		//9-尖叫
} EnumAttrExpression;

#ifdef _USE_ZH
const char* g_strAttrExpressionName[] = {"生气", "平静", "厌恶", "困惑", "高兴", "悲伤", "害怕", "惊讶", "斜视", "尖叫"};
#else
const char* g_strAttrExpressionName[] = {"Angry", "Calm", "Confused", "Disgust", "Happy", "Sad", "Scared", "Surprised", "Squint", "Scream"};
#endif

#define MAX_ATTR_EXPRESSION_NUM			(sizeof(g_strAttrExpressionName)/sizeof(char*))


//微笑

//概率事件 -小于50认为没有微笑，大于50认为在微笑
//概率事件 -小于50认为没有微笑，大于50认为在微笑
#define FACE_ATTR_SMILE_THRESHOLD_VALUE			50
typedef enum
{
	ATTR_SMILE_Unknow			= -1,
	ATTR_SMILE_No       		= 0,  	
	ATTR_SMILE_Yes     			,  		
} EnumAttrSmile;

#ifdef _USE_ZH
const char* g_strAttrSmileName[] = {"无", "有"};
#else
const char* g_strAttrSmileName[] = {"No", "Yes"};
#endif

#define MAX_ATTR_SMILE_NUM			(sizeof(g_strAttrSmileName)/sizeof(char*))

//民族
typedef enum
{
	ATTR_NATION_Unknow			= -1,
	ATTR_NATION_Han       		= 0,  	//0-汉族
	ATTR_NATION_Other     		,  		//其他
} EnumAttrNation;

#ifdef _USE_ZH
const char* g_strAttrNationName[] = {"汉", "其他"};
#else
const char* g_strAttrNationName[] = {"Han", "Other"};
#endif

#define MAX_ATTR_NATION_NUM			(sizeof(g_strAttrNationName)/sizeof(char*))

#ifdef _USE_ZH
const char* g_strAttrObjTypeName[] = {"人脸", "车", "静止物", "行人"};
#else
const char* g_strAttrObjTypeName[] = {"Face", "Vehicle", "Nonmotor", "Pedestrian"};
#endif

#define MAX_ATTR_OBJTYPE_NUM			(sizeof(g_strAttrObjTypeName)/sizeof(char*))


#endif
