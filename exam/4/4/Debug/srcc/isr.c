//=====================================================================
//文件名称：isr.c（中断处理程序源文件）
//框架提供：SD-ARM（sumcu.suda.edu.cn）
//版本更新：20170801-20191020
//功能描述：提供中断处理程序编程框架
//=====================================================================
#include "includes.h"
#include <string.h>
//内部函数声明
uint8_t CreateFrame(uint8_t Data,uint8_t * buffer);

//======================================================================
//中断服务程序名称：UART_USER_Handler
//触发条件：UART_USE串口收到一个字节触发
//功    能：收到一个字节，直接返回该字节
//备    注：进入本程序后，可使用uart_get_re_int函数可再进行中断标志判断
//          （1-有UART接收中断，0-没有UART接收中断）
//======================================================================
void UART_User_Handler(void)
{

    uint8_t ch,flag,cnt;
    DISABLE_INTERRUPTS;               //关总中断
    //-----------------------------------------------------------------------
    ch = uart_re1(UART_User, &flag);   //调用接收一个字节的函数，清接收中断位
    //调用内部函数CreateFrame进行组帧
   // uart_send1(UART_User,ch);//回发接收到的字节
    printf("char:%c\n",ch);
   	if('0'<=ch&&ch<='3'){
   		if((ch == '0'))
		{
			whi=1;
		}	
		if(ch == '1')
		{
			whi=2;
		}
		if(ch == '2')
		{
			whi=3;
		}
		if(ch== '3')
		{
			whi=4;
		}
   	}
    
   	
	ENABLE_INTERRUPTS;       //开总中断
	
	
}


//内部调用函数

//===========================================================================
//函数名称：CreateFrame
//功能概要：组建数据帧，将待组帧数据加入到数据帧中
//参数说明：Data：         待组帧数据
//          buffer:        数据帧变量
//函数返回：组帧状态    0-组帧未成功，1-组帧成功
//备注：十六进制数据帧格式
//               帧头        + 数据长度         + 有效数据    +  帧尾
//           FrameHead   +   len       + 有效数据    + FrameTail
//===========================================================================
//open帧头帧尾
#define FrameHead1    (0x6F)       //帧头     ASCII码对应o
#define FrameTail1    (0x6E)       //帧尾     ASCII码对应n
//close帧头帧尾
#define FrameHead2    (0x63)       //帧头     ASCII码对应c
#define FrameTail2    (0x65)       //帧尾     ASCII码对应e
//blue帧头帧尾
#define FrameHead3    (0x62)       //帧头     ASCII码对应b
#define FrameTail3    (0x65)       //帧尾     ASCII码对应e
//green帧头帧尾
#define FrameHead4    (0x67)       //帧头     ASCII码对应g
#define FrameTail4    (0x6E)       //帧尾     ASCII码对应n
//red帧头帧尾
#define FrameHead5    (0x72)       //帧头     ASCII码对应r
#define FrameTail5    (0x64)       //帧尾     ASCII码对应d


//
static uint8_t frameLen=0;    //帧的计数器
uint8_t frameFlag;            //组帧状态
uint8_t length;



//如果帧头是o或b则帧总长是4(open/blue)
//如果帧头是c或g则帧总长是5(close/green)
uint8_t CreateFrame(uint8_t Data,uint8_t * buffer)
{
    frameFlag=0;            //组帧状态初始化
    //根据静态变量frameLen组帧
    switch(frameLen)
    {
        case 0:    //第一个数据
        {
            if ((Data==FrameHead1) || (Data==FrameHead3))    //收到数据是帧头FrameHead1
                length=4;
            else if ((Data==FrameHead2) || (Data==FrameHead4))
            	length=5;
            else
            	length=3;
            buffer[0]=Data;
            frameLen++;
            frameFlag=0;        //组帧开始
            break;
        }
        default:    //其他情况
        {
            //根据长度接收余下的数据直到帧尾前一位
            if(frameLen>=1 && frameLen<=(length-2))
            {
                buffer[frameLen]=Data;
                frameLen++;
                break;
            }

            //若是末尾数据则执行
            if(frameLen>=(length-1))
            {
                if ((Data==FrameTail1)||(Data==FrameTail2)||(Data==FrameTail3)||(Data==FrameTail4)||(Data==FrameTail5))    //若是帧尾
                {
                    buffer[frameLen]=Data;     //将帧尾存入缓冲区
                    frameFlag=1;    //组帧成功
                }
                frameLen=0    ;     //计数清0，准备重新组帧
                break;
            }
        }
    }     //switch_END
    return frameFlag;                 //返回组帧状态
}
