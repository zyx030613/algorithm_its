/************************************************************************/
/*COMMON RETURN                                                                     
*/
/************************************************************************/
#define RET_NOTHING					((void)0)
#define RET_SUCCESS					0			//成功
#define RET_FAILED					-1			//失败
#define RET_MALLOC_FALIED			-2

#define	RET_BUFFER_FULL				-11			//缓冲区满，数据没有放入缓冲区
#define	RET_BUFFER_WILL_BE_FULL		-18			//即将满，降低送入数据的频率
#define	RET_BUFFER_WILL_BE_EMPTY	-19			//即将空，提高送入数据的频率
#define RET_BUFFER_IS_OK			-20			//正常可以放数据

#define RET_GETDATA_END				-50			//获取数据正常结束，读到文件尾或者播放停止位置
				
#define RET_INVALID_PARA			-101		//非法参数
#define RET_DEVICE_NOT_LOGON		-102		//设备未登录
#define RET_MEMORY_OVER				-103		//内存不足
#define RET_ERR_AUTHORITY			-104		//权限不足
#define RET_SEND_LIST_FULL			-105		//发送列表满了


#define RET_SYSTEM_CALL_FAILED		-200		//调用系统函数失败
#define RET_SDK_CALL_FAILED     	-201		//调用SDK接口失败
#define RET_INNER_CALL_FAILED		-202		//调用内部函数失败
#define RET_DRAW_CREATE_FAILED		-203		//创建Draw失败
#define RET_NOSUPPORT_PARATYPE		-204		//不支持的参数类型
#define RET_LIGHTLOGON_NETERROR		-205		//轻量级发协议网络错误
#define RET_LIGHTLOGON_GET_TIME_OUT	-206		//轻量级发协议等待设备回复超时
#define RET_DEV_NOT_SUPPORT			-207		//设备不支持当前参数获取方式

