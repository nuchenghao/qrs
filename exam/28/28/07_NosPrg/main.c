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
    //（1）======启动部分（开头）==========================================
    //（1.1）声明main函数使用的局部变量
    uint8_t  mFlag;           //主循环使用的临时变量
    uint8_t  mSec;	         //记当前秒的值
    //（1.2）【不变】关总中断
    DISABLE_INTERRUPTS;
    wdog_stop();
    
    //（1.3）给主函数使用的局部变量赋初值
    mFlag='A';              //主循环使用的临时变量：蓝灯状态标志

    //（1.4）给全局变量赋初值
   	//"时分秒"缓存初始化(00:00:00)
   	gTime[0] = 0;       //时
   	gTime[1] = 0;	  	//分
   	gTime[2] = 0;	  	//秒
   	mSec = gTime[2];	//记住当前秒的值
    //（1.5）用户外设模块初始化
 //   gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_ON);    //初始化蓝灯
    gpio_init(PTC_NUM|(0),1,0);
    uart_init(UART_User, 9600);
    timer_init(TIMER_USER,20);   //设置TIMER_USER为20ms中断

    pwm_init(PWM_USER,1500,600,90,PWM_EDGE,PWM_PLUS );   //PWM输出初始化
 //   pwm_init(LIGHT_RED,1500,600,90,PWM_EDGE,PWM_PLUS );
    incapture_init(INCAP_USER,48000,37500,CAP_DOUBLE);     //上升沿捕捉初始化

  
    //（1.6）使能模块中断
    uart_enable_re_int(UART_User);
    timer_enable_int(TIMER_USER);
    cap_enable_int(INCAP_USER);    //使能输入捕捉中断
    //（1.7）【不变】开总中断
    ENABLE_INTERRUPTS;

    printf("------------------------------------------------------\n");
    printf("金葫芦提示：PWM-INCAP实例 \n");
    printf("  ① 蓝灯闪烁\n");
   	printf("  ② 通过INCAP_USER输出4KHz的PWM信号，占空比为50%。 \n");
   	printf("  ③ 设置INCAP_USER为输入捕捉，采用双边沿捕捉， \n");
   	printf("  ④ 每次触发输入捕捉，都会向上位机输出当前捕捉到的通道值”。 \n");
    printf("------------------------------------------------------\n");

    
    for(;;)     //for(;;)（开头）
    {
    	__asm("NOP");
   		if (gTime[2] == mSec)   continue;
   		mSec=gTime[2];
   		printf("%d\n",value);
   		if(value==1){
   		printf("s1\n");
   			gpio_set(PTC_NUM|(0),1);
   		}else{
   			gpio_set(PTC_NUM|(0),0);
   		}
   		
   		
    }     
}