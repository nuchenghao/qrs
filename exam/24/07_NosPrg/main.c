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
void Test_Raytrace();
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
    printf("LCD初始化...");
    LCD_Init();
    printf("成功\n");
    ENABLE_INTERRUPTS;
    
    printf("-----------------------------------------------------\r\n"); 
    printf("金葫芦提示：红外寻迹测试实例 \r\n");
    printf("  ① 蓝灯闪烁\n");
    printf("  ② UART_Debug串口（波特率115200），输出红外感应提示信息 \r\n");
    printf("----------------------------------------------------\r\n"); 
    
    
    LCD_aotu(2,2,238,318,0);
    LCD_ShowString(72,20,RED,GRAY,(char *)"AHL-MCU-KL36");
    LCD_DrawLine(2,40,238,40,BLACK);
  //  LCD_ShowString(8,52,RED,GRAY,(char *)"Offtrack:");
    for(;;)     //for(;;)（开头）
    {
        
        //（2.1）主循环次数+1，并判断是否小于特定常数
        mMainLoopCount++;                         //+1
        if (mMainLoopCount<=6556677)  continue;   //如果小于特定常数，继续循环
       // Test_Raytrace();


		static char OutputCtl=0;
		OutputCtl++;
		uint8_t cnt=0;
		if (OutputCtl>=4) OutputCtl=1;
		gpio_init(RAY_RIGHT,GPIO_INPUT,0);
		gpio_init(RAY_LEFT,GPIO_INPUT,0);
		gpio_pull(RAY_RIGHT,0);
		gpio_pull(RAY_LEFT,0);
		if (gpio_get(RAY_LEFT))
		{
		   	gpio_init(MOTOR,GPIO_OUTPUT,1);
		    printf("左侧红外：有物体\r\n\r\n");
		    LCD_ShowString(6,50,BLACK,GRAY,"[RAY-L]                    ");
		}
		else
		{
//		    gpio_init(MOTOR,GPIO_OUTPUT,0);
//		    
//		    LCD_ShowString(6,50,BLACK,GRAY,"                           ");
		    if (gpio_get(RAY_RIGHT))
		    {
		    	gpio_init(MOTOR,GPIO_OUTPUT,1);
		    	printf("右侧红外：有物体\r\n\r\n");
		    	LCD_ShowString(66,50,BLACK,GRAY,"[RAY-R]                   ");
		    }
		    else
		    {
		    	gpio_init(MOTOR,GPIO_OUTPUT,0);
		    	printf("右侧红外：无物体;右侧红外：无物体\n");
		    	LCD_ShowString(6,50,BLACK,GRAY,"                                            ");
		    }
		
		}

		
        mMainLoopCount=0;    
        if (mFlag=='A')   
        {
            gpio_set(LIGHT_BLUE,LIGHT_ON);   //设置灯“亮”
            printf("蓝灯：亮\r\n\r\n");           //通过调试串口输出灯的状态
            mFlag='L';                        //改变状态标志
        }
        else                   //否则,若灯状态标志不为'A'    
        {
            gpio_set(LIGHT_BLUE,LIGHT_OFF);  //设置灯“暗”  
            printf("蓝灯：暗\r\n\r\n");           //通过调试串口输出灯的状态
            mFlag='A';                        //改变状态标志
        }	
    }     //for(;;)结尾
    //（2）======主循环部分（结尾）========================================
}

//======以下为主函数调用的子函数存放处=====================================
//=====================================================================
//函数名称：Test_Raytrace
//函数返回：无
//参数说明：无
//功能概要：测试红外寻迹传感器函数
//=====================================================================
void Test_Raytrace()
{
    static char OutputCtl=0;
    OutputCtl++;
    uint8_t cnt=0;
    if (OutputCtl>=4) OutputCtl=1;
    //初始化红外循迹传感器两个引脚，设置为低电平输入
    gpio_init(RAY_RIGHT,GPIO_INPUT,0);
    gpio_init(RAY_LEFT,GPIO_INPUT,0);
    gpio_pull(RAY_RIGHT,0);
    gpio_pull(RAY_LEFT,0);
    if (gpio_get(RAY_LEFT))
    {
    	gpio_init(MOTOR,GPIO_OUTPUT,1);
    	printf("左侧红外：有物体\r\n\r\n");
    	LCD_ShowString(6,50,BLACK,GRAY,"[RAY-L]                    ");
    }
    else
    {
    	gpio_init(MOTOR,GPIO_OUTPUT,0);
    	printf("左侧红外：无物体\r\n\r\n");
    	LCD_ShowString(6,50,BLACK,GRAY,"                           ");

    }
    if (gpio_get(RAY_RIGHT))
    {
    	gpio_init(MOTOR,GPIO_OUTPUT,1);
    	printf("右侧红外：有物体\r\n\r\n");
    	LCD_ShowString(66,50,BLACK,GRAY,"[RAY-R]                   ");
    }
    else
    {
    	gpio_init(MOTOR,GPIO_OUTPUT,0);
    	printf("右侧红外：无物体\r\n\r\n");
    	LCD_ShowString(66,50,BLACK,GRAY,"                         ");
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



