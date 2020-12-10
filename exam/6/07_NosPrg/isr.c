//=====================================================================
//文件名称：isr.c（中断处理程序源文件）
//框架提供：SD-ARM（sumcu.suda.edu.cn）
//版本更新：20170801-20191020
//功能描述：提供中断处理程序编程框架
//=====================================================================
#include "includes.h"

//声明使用到的内部函数
//isr.c使用的内部函数声明处
void SecAdd1(uint8_t *p);
//======================================================================
//中断服务程序名称：UART_USER_Handler
//触发条件：UART_USE串口收到一个字节触发
//功    能：收到一个字节，直接返回该字节
//备    注：进入本程序后，可使用uart_get_re_int函数可再进行中断标志判断
//          （1-有UART接收中断，0-没有UART接收中断）
//======================================================================
uint8_t count=0;
uint8_t order[1024];
uint8_t nullnum,fflag,opt;
uint16_t secot,offset,len;
uint32_t addr;
void UART_User_Handler(void)
{
    uint8_t ch;
	uint8_t flag,mFlag;
    uint8_t flashRead[2048];
	DISABLE_INTERRUPTS;      //关总中断
	
	
	ch=uart_re1(UART_User,&flag);
	if(flag==1)
	{
		if(ch==' ')nullnum--;
		else 
		{

			if(fflag==0)
			{
				opt=ch;
				if(ch=='w')nullnum=5;
				else if(ch=='r')nullnum=4;
				else nullnum=3;
				fflag=1;
			}
			else
			{
					
				switch(opt)
				{
				
					case 'w':
			//			printf("%c %d\n",opt,nullnum);
						if(nullnum==4)secot=secot*10+(ch-'0');
						if(nullnum==3)offset=offset*10+(ch-'0');
						if(nullnum==2)len=len*10+(ch-'0');
						if(nullnum==1)order[count++]=ch;
						break;
			
					case 'r':
			//			printf("%c %d\n",opt,nullnum);
					   if(nullnum==3)secot=secot*10+(ch-'0');
					   if(nullnum==2)offset=offset*10+(ch-'0');
					   if(nullnum==1)len=len*10+(ch-'0');
					   break;
				   
					case 'a':
			//			printf("%c %d\n",opt,nullnum);
						if(nullnum==2)addr=addr*10+(ch-'0');
						if(nullnum==1)len=len*10+(ch-'0');
						break;
					default:
					 	break;
				}
				
				
				
			    
			}
		//	printf("%c %d\n",opt,nullnum);

		}
	//	printf("%c %d\n",opt,nullnum);
		if(nullnum==0)
		{
			switch(opt)
			{
				case 'w':	
						mFlag=flash_erase(secot);
						mFlag=flash_write(secot, offset,len,order);	
						break;
				case 'r':	
				   		flash_read_logic(flashRead,secot,offset,len);
				   		uart_sendN(UART_User,len,flashRead);					   
					   break;
				case 'a':
						flash_read_physical(flashRead,addr,len);
						uart_sendN(UART_User,len,flashRead);	
						break;
			}
			addr=0;len=0;secot=offset=0;fflag=0;
			count=0;
		}
	}
//加空格
//w 63 0 4 abcd 
//r 63 0 4  
//a 64512 4  
	
	
	ENABLE_INTERRUPTS;       //开总中断
}

//=====================================================================
//函数名称：SYSTICK_USER_Handler（SysTick定时器中断处理程序）
//参数说明：无
//函数返回：无
//功能概要：（1）每10ms中断触发本程序一次；（2）达到一秒时，调用秒+1
//           程序，计算“时、分、秒”
//特别提示：（1）使用全局变量字节型数组gTime[3]，分别存储“时、分、秒”
//          （2）注意其中静态变量的使用
//=====================================================================
//void SYSTICK_USER_Handler()

void SysTick_Handler()
{
	static uint8_t SysTickCount = 0;
	SysTickCount++;    //Tick单元+1
	wdog_feed();      //看门狗“喂狗”
	if (SysTickCount >= 100)
	{
		SysTickCount = 0;
		SecAdd1(gTime);
	}
}



//===========================================================================
//函数名称：SecAdd1
//函数返回：无
//参数说明：*p:为指向一个时分秒数组p[3]
//功能概要：秒单元+1，并处理时分单元（00:00:00-23:59:59)
//===========================================================================
void SecAdd1(uint8_t *p)
{
	*(p+2)+=1;         //秒+1
	if(*(p+2)>=60)     //秒溢出
	{
		*(p+2)=0;       //清秒
		*(p+1)+=1;      //分+1
		if(*(p+1)>=60)  //分溢出
		{
			*(p+1)=0;    //清分
			*p+=1;       //时+1
			if(*p>=24)   //时溢出
			{
				*p=0;      //清时
			}
		}
	}
}


/*
 知识要素：
 1.本文件中的中断处理函数调用的均是相关设备封装好的具体构件，在更换芯片
 时，只需保证设备的构件接口一致，即可保证本文件的相关中断处理函数不做任何
 更改，从而达到芯片无关性的要求。
 */
