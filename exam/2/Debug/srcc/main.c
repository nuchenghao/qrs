//====================================================================
//文件名称：main.c（应用工程主函数）
//框架提供：SD-Arm（sumcu.suda.edu.cn）
//版本更新：2017.08, 2020.06
//功能描述：见本工程的<01_Doc>文件夹下Readme.txt文件
//====================================================================

#define GLOBLE_VAR
#include "includes.h"      //包含总头文件

//----------------------------------------------------------------------
//声明使用到的内部函数
//main.c使用的内部函数声明处

//----------------------------------------------------------------------
//主函数，一般情况下可以认为程序从此开始运行（实际上有启动过程见书稿）
int main(void)
{

    uint8_t  mFlag;           //主循环使用的临时变量
    uint8_t  mSec;	         //记当前秒的值
    DISABLE_INTERRUPTS;
    wdog_stop();

    mFlag='A';              //主循环使用的临时变量：蓝灯状态标志
	
   	gTime[0] = 0;       //时
   	gTime[1] = 0;	  	//分
   	gTime[2] = 0;	  	//秒
   	mSec = gTime[2];	//记住当前秒的值

	
	volatile uint32_t *portA_ptr = (uint32_t*)0x40049000u;
    
    //PORTA13的引脚控制寄存器地址=基地址+偏移量
    volatile uint32_t *portA_PCR_5 = portA_ptr + 5;
    //（1.5.2）计算给出PORTA的数据方向寄存器、输出反转寄存器地址
    //PORTA端口（作为GPIO功能）的基地址为0x400FF000u
    volatile uint32_t *gpioA_ptr = (uint32_t*)0x400FF000u;
    //PORTA的数据方向寄存器地址=基地址+偏移量
    volatile uint32_t *portA_PDDR=gpioA_ptr+5;
    //PORTA的输出寄存器地址=基地址+偏移量
    volatile uint32_t *portA_PDO=gpioA_ptr+0;
    
    //（1.5.3）设置PORTA13引脚为GPIO引脚，即令相应引脚控制寄存器的10-8位
    //(MUX)字段为001
    *portA_PCR_5 &= 0b11111111111111111111100011111111;  //清MUX位段
    *portA_PCR_5 |= 0b00000000000000000000000100000000;
    
    *portA_PDO |= (1<<5);
    *portA_PDDR |= (1<<5);
    

   	uart_init(UART_User, 9600);
    systick_init(50);      
   	uart_enable_re_int(UART_User);
    ENABLE_INTERRUPTS;//开中断

    printf("------------------------------------------------------\n");
    printf("金葫芦提示：systick定时器实例 \n");
    printf("  ① 蓝灯闪烁\n");
   	printf("  ② 每10ms中断触发SysTick定时器中断处理程序一次。 \n");
   	printf("  ③ 进入SysTick定时器中断处理程序后，静态变量10ms单元+1， \n");
   	printf("  ④ 达到一秒时，调用秒+1，程序，计算“时、分、秒”。 \n");
   	printf("  ⑤ 使用全局变量字节型数组gTime[3]，分别存储“时、分、秒”。 \n");
   	printf("  ⑥ 注意其中静态变量的使用 \n");
    printf("------------------------------------------------------\n");


    for(;;)     //for(;;)（开头）
    {
   		if (gTime[2]==(mSec)%60||gTime[2]==(mSec+1)%60||gTime[2]==(mSec+2)%60||gTime[2]==(mSec+3)%60||(gTime[2]==(mSec+4)%60))continue;
        mSec = gTime[2];
        if (mFlag=='A')   
        {
            *portA_PDO &= ~(1<<5);   //设置灯“亮”
            printf("%d:%d:%d  ",gTime[0],gTime[1],gTime[2]);
            printf("红灯：亮\n");             //通过调试串口输出灯的状态
            mFlag='L';                        //改变状态标志
        }
        else                   //否则,若灯状态标志不为'A'
        {
            *portA_PDO |= (1<<5);
            printf("%d:%d:%d  ",gTime[0],gTime[1],gTime[2]);
            printf("红灯：暗\n");             //通过调试串口输出灯的状态
            mFlag='A';                        //改变状态标志
        }
    }    
}


