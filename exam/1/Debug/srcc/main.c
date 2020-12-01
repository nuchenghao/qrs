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

    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);    //初始化蓝灯
   	uart_init(UART_User, 9600);
    systick_init(20);      //设置systick为10ms中断
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

   		if (gTime[2] == mSec%60||gTime[2] == (mSec+1)%60)   continue;
        mSec = gTime[2];
        if (mFlag=='A')   
        {
            gpio_set(LIGHT_RED,LIGHT_ON);   //设置灯“亮”
            printf("%d:%d:%d  ",gTime[0],gTime[1],gTime[2]);
            printf("红灯：亮\n");             //通过调试串口输出灯的状态
            mFlag='L';                        //改变状态标志
        }
        else                   //否则,若灯状态标志不为'A'
        {
            gpio_set(LIGHT_RED,LIGHT_OFF);  //设置灯“暗”
            printf("%d:%d:%d  ",gTime[0],gTime[1],gTime[2]);
            printf("红灯：暗\n");             //通过调试串口输出灯的状态
            mFlag='A';                        //改变状态标志
        }
    }    
}


