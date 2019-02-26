//0x00-0x63通用功能
//0x00-0x2f解码器控制
#define     REGISTER                0         //注册功能
#define     MOVE_UP                 1         //云台向上
#define     MOVE_UP_STOP            2         //云台向上停
#define     MOVE_DOWN               3         //云台向下
#define     MOVE_DOWN_STOP          4         //云台向下停
#define     MOVE_LEFT               5         //云台向左
#define     MOVE_LEFT_STOP          6         //云台向左停
#define     MOVE_RIGHT              7         //云台向右
#define     MOVE_RIGHT_STOP         8         //云台向右停
#define     MOVE_UP_LEFT            9         //云台左上
#define     MOVE_UP_LEFT_STOP       10         //云台左上停
#define     MOVE_UP_RIGHT           11        //云台右上
#define     MOVE_UP_RIGHT_STOP      12        //云台右上停
#define     MOVE_DOWN_LEFT          13        //云台左下
#define     MOVE_DOWN_LEFT_STOP     14        //云台左下停
#define     MOVE_DOWN_RIGHT         15        //云台右下
#define     MOVE_DOWN_RIGHT_STOP    16        //云台右下停
#define     SET_LEFT_BORDER         17        //设置左边界
#define     SET_RIGHT_BORDER        18        //设置右边界
#define     SET_UP_BORDER           19        //设置上边界
#define     SET_DOWN_BORDER         20        //设置下边界
#define     HOR_AUTO                21        //水平自动
#define     HOR_AUTO_STOP           22        //水平自动停
#define     SET_HOR_AUTO_BEGIN      23        //设水平自动开始点
#define     SET_HOR_AUTO_END        24        //设水平自动结束点
#define     SET_HOR_AUTO_SPEED      25        //设置水平自动速度
#define     VER_AUTO                26        //垂直自动
#define     SET_VER_AUTO_BEGIN      27        //设置垂直自动开始点
#define     SET_VER_AUTO_END        28        //设置垂直自动结束点
#define     SET_VER_AUTO_SPEED      29        //设置垂直自动速度
#define     VER_AUTO_STOP           30        //垂直自动停

#define     ZOOM_BIG                31        //变倍大
#define     ZOOM_BIG_STOP           32        //变倍大停
#define     ZOOM_SMALL              33        //变倍小
#define     ZOOM_SMALL_STOP         34        //变倍小停
#define     FOCUS_FAR               35        //聚焦远
#define     FOCUS_FAR_STOP          36        //聚焦远停
#define     FOCUS_NEAR              37        //聚焦近
#define     FOCUS_NEAR_STOP         38        //聚焦近停
#define     IRIS_OPEN               39        //光圈开
#define     IRIS_OPEN_STOP          40        //光圈开停
#define     IRIS_CLOSE              41        //光圈关
#define     IRIS_CLOSE_STOP         42        //光圈关停

#define     LIGHT_ON                43        //灯光开
#define     LIGHT_OFF               44        //灯光关
#define     POWER_ON                45        //电源开
#define     POWER_OFF               46        //电源关
#define     RAIN_ON                 47        //雨刷开
#define     RAIN_OFF                48        //雨刷关
#define     TALK_ON                 49        //对讲开
#define     TALK_OFF                50        //对讲关
#define     DEF_ON                  51        //布防
#define     DEF_OFF                 52        //撤防

#define     BROWSE                  53        //查询
#define     ALARM_ANSWER            54        //报警应答
#define     STATE_ASK               55        //请求上传控制状态


//0x30-0x4f快球控制
#define     MOVE                    60        //快球动作
#define     MOVE_STOP               61        //快球动作停
#define     CALL_VIEW               62        //景点调用
#define     SET_VIEW                63        //景点预置
#define     DELETE_VIEW             64        //删除预置景点
#define     SEQUENCE_BEGIN          65        //开始巡航
#define     SEQUENCE_END            66        //停止巡航
#define     ADD_PRESET              67        //添加巡航点
#define     DELETE_PRESET           68        //删除巡航点
#define     CLEAR_SEQUENCE          69        //清除巡航设置
#define     TIME_SEQUENCE           70        //设置巡航时间
#define     SET_GUARD               71        //设置看守位
#define     DELETE_GUARD            72        //删除看守位
#define     GET_HOR_AUTO_SPEED      73        //获得水平自动速度
#define     GET_TRACK_TIME          74        //获得巡航时间
#define     GET_TRACK_SEQUENCE      75        //获得巡航序列
#define     GUARD_TIME              76        //设置看守位的时间
#define     GET_VIEW_LIST           77        //获得景点序列

#define     MEMU_OPEN				78        //打开菜单	Call 95
#define     MEMU_CLOSE              79        //关闭菜单	Call 96

//0x64-0xc7专用功能
#define     SWITCH                  101        //手动矩阵切换
#define     SWITCH_MONITOR          102        //切监
#define     SWITCH_VIDICON          103        //切点
#define     SWITCH_ORDER            104        //顺序切换
#define     SWITCH_ORDER_STOP       105        //顺序切换停
#define     SWITCH_GROUP            106        //群组切换
#define     SWITCH_GROUP_STOP       107        //群组切换停

#define     PROTOCOL_MOVE_UP                 1			//ptz up
#define     PROTOCOL_MOVE_DOWN               2			//ptz down
#define     PROTOCOL_MOVE_LEFT               3			//ptz left
#define     PROTOCOL_MOVE_RIGHT              4			//ptz right
#define     PROTOCOL_MOVE_UP_RIGHT           5			//ptz top right
#define     PROTOCOL_MOVE_UP_LEFT            6			//ptz top left
#define     PROTOCOL_MOVE_DOWN_RIGHT         7			//ptz down right
#define     PROTOCOL_MOVE_DOWN_LEFT          8			//ptz down left
#define     PROTOCOL_MOVE_STOP				 9			//stop ptz up
#define     PROTOCOL_ZOOM_BIG                10        //变倍大
#define     PROTOCOL_ZOOM_SMALL              11        //变倍小

#define     PROTOCOL_FOCUS_NEAR              13        //聚焦近
#define     PROTOCOL_FOCUS_FAR               14        //聚焦远

#define     PROTOCOL_IRIS_OPEN               17        //光圈开
#define     PROTOCOL_IRIS_CLOSE              18        //光圈关
#define     PROTOCOL_RAIN_ON                 19        //雨刷开
#define     PROTOCOL_RAIN_OFF                20        //雨刷关
#define     PROTOCOL_LIGHT_ON                21        //灯光开
#define     PROTOCOL_LIGHT_OFF               22        //灯光关
#define     PROTOCOL_HOR_AUTO				 23		  //horizontal auto
#define     PROTOCOL_HOR_AUTO_STOP			 24		  //stop horizontal auto
#define     PROTOCOL_CALL_VIEW				 25		  //调用预置位

#define     PROTOCOL_SET_VIEW				 28		  //设置预置位
#define     PROTOCOL_POWER_ON                29        //电源开
#define     PROTOCOL_POWER_OFF               30        //电源关
