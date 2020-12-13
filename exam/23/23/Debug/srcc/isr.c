//=====================================================================
//文件名称：isr.c（中断处理程序源文件）
//框架提供：SD-ARM（sumcu.suda.edu.cn）
//版本更新：20170801-20191020
//功能描述：提供中断处理程序编程框架
//=====================================================================
#include "includes.h"
//======================================================================
//中断服务程序名称：UART_USER_Handler
//触发条件：UART_USE串口收到一个字节触发
//功    能：收到一个字节，直接返回该字节
//备    注：进入本程序后，可使用uart_get_re_int函数可再进行中断标志判断
//          （1-有UART接收中断，0-没有UART接收中断）
//======================================================================
void UART_User_Handler(void)
{
	uint8_t mString[30];
    uint8_t xyzData[6];         //x、y、z轴倾角，均占两个字节
    uint16_t xdata,ydata,zdata; //x轴倾角
    uint8_t checkdata;          //ADLX345的验证数据,正确接收为0xe5
    uint8_t temp[6];
    uint8_t ch;	uint8_t flag;
   	ch = uart_re1(UART_User, &flag);
    if(flag)   //有数据
	{
	   if(ch == 'q')
	   {
	   			printf("ask\n");
				adlx345_init(i2cAcceleration,0x0B,0x08,0x08,0x80,0x00,0x00,0x05);//初始化ADLX345(J2端口) 
				adlx345_read1(0x00,&checkdata);    //读取adxl345校验数据
				adlx345_init(0,0x0B,0x08,0x08,0x80,0x00,0x00,0x05);//初始化ADLX345(J2端口)
				adlx345_read1(0x00,&checkdata);    //读取adxl345校验数据
				main_Dly_ms(5);
				adlx345_readN(0x32,xyzData,6);		   //读倾角传感器数值
				xdata = (xyzData[1]<<8)+xyzData[0];    //x方向倾角
				ydata = (xyzData[3]<<8)+xyzData[2];    //y方向倾角
				zdata = (xyzData[5]<<8)+xyzData[4];    //z方向倾角
				temp[0] = xyzData[1] ;
          		temp[1] = xyzData[0];
          		temp[2] =xyzData[3];
				temp[3] =xyzData[2];
				temp[4] =xyzData[5];
				temp[5] =xyzData[4];
				
          		printf("%d %d %d %d %d %d\n",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5]);
         		uart_send_string(UART_User,temp);
	   }
	}
}


/*
 知识要素：
 1.本文件中的中断处理函数调用的均是相关设备封装好的具体构件，在更换芯片
 时，只需保证设备的构件接口一致，即可保证本文件的相关中断处理函数不做任何
 更改，从而达到芯片无关性的要求。
 */
