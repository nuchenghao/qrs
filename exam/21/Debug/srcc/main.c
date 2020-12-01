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
void Test_RAY_HUMAN();
void main_Dly_ms(uint32_t ms);
//----------------------------------------------------------------------
//主函数，一般情况下可以认为程序从此开始运行（实际上有启动过程见书稿）
int main(void)
{
    //（1）======启动部分（开头）==========================================
    //（1.1）声明main函数使用的局部变量
    uint32_t mMainLoopCount;  //主循环使用的记录主循环次数变量
    uint8_t  mFlag;            //主循环使用的临时变量
    
    //（1.2）【不变】关总中断
    DISABLE_INTERRUPTS;

    
    //（1.3）给主函数使用的局部变量赋初值
    mMainLoopCount = 0;     //主循环使用的记录主循环次数变量
    mFlag='A';              //主循环使用的临时变量：蓝灯状态标志
    
    //（1.4）给全局变量赋初值
    
    //（1.5）用户外设模块初始化
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);    //初始化蓝灯
     wdog_feed();
     printf("LCD初始化...");
     LCD_Init();
      printf("成功\n");
    //（1.6）使能模块中断
    //uart_enable_re_int(UART_User);
    //（1.7）【不变】开总中断
    ENABLE_INTERRUPTS;
    

    
    LCD_aotu(2,2,238,318,0);
    LCD_aotu(4,40,236,80,1);
    LCD_ShowString(72,20,RED,GRAY,(char *)"AHL-MCU-KL36");

  	wdog_feed();
   	LCD_ShowString(8,50,BLACK,GRAY,(char *)"Person:");
   	LCD_aotu(4,70,236,316,1);
   
   for(;;)     //for(;;)（开头）
    {
        
        //（2.1）主循环次数+1，并判断是否小于特定常数
        mMainLoopCount++;                         //+1
        if (mMainLoopCount<=6556677)  continue;   //如果小于特定常数，继续循环
     //   gpio_init(BEEF,GPIO_OUTPUT,0);
     //   while(mMainLoopCount<=12556677) mMainLoopCount++; 
        mMainLoopCount=0;  
        Test_RAY_HUMAN();
        
    }     
}

//======以下为主函数调用的子函数存放处=====================================
//=====================================================================
//函数名称：Test_RAY_HUMAN
//函数返回：无
//参数说明：无
//功能概要：测试人体红外传感器函数
//=====================================================================
void Test_RAY_HUMAN()
{
    gpio_init(RAY_HUMAN,GPIO_INPUT,0);		//初始化红灯和人体红外传感器模块
    gpio_pull(RAY_HUMAN,0);
    if (gpio_get(RAY_HUMAN))
    {
    	gpio_init(BEEF,GPIO_OUTPUT,1);
    	LCD_ShowString(84,50,RED,GRAY,"Yes");
    	printf("红外：监测有人\r\n\r\n");
    	LCD_DrawCircle(120,110,15,BLACK);
    	LCD_DrawLine(120,125,120,180,BLACK);
    	LCD_DrawLine(120,140,60,160,BLACK);
    	LCD_DrawLine(120,140,180,160,BLACK);
    	LCD_DrawLine(120,180,80,220,BLACK);
    	LCD_DrawLine(120,180,160,220,BLACK);
    }
    else
    {
    gpio_init(BEEF,GPIO_OUTPUT,0);
    	LCD_ShowString(84,50,BLACK,GRAY,"No ");
    	printf("红外：监测无人\r\n\r\n");
    	LCD_DrawCircle(120,110,15,GRAY);
    	LCD_DrawLine(120,125,120,180,GRAY);
    	LCD_DrawLine(120,140,60,160,GRAY);
    	LCD_DrawLine(120,140,180,160,GRAY);
    	LCD_DrawLine(120,180,80,220,GRAY);
    	LCD_DrawLine(120,180,160,220,GRAY);
    }
}

void main_Dly_ms(uint32_t ms)
{
    for(uint32_t i= 0; i < (6000*ms); i++) __asm("nop");
}
//====================================================================
/*
知识要素：
（1）main.c是一个模板，该文件所有代码均不涉及具体的硬件和环境，通过调用构件
实现对硬件的干预。
（2）本文件中标有【不变】的地方为系统保留，此类代码与具体项目无关，不宜删除。
（3）本文件中对宏GLOBLE_VAR进行了定义，所以在包含"includes.h"头文件时，会定
义全局变量，在其他文件中包含"includes.h"头文件时，
编译时会自动增加extern
*/



