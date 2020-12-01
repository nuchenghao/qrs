//======================================================================
//文件名称：main.c（应用工程主函数）
//框架提供：SD-ARM（sumcu.suda.edu.cn）
//版本更新：
//功能描述：见本工程的<01_Doc>文件夹下Readme.txt文件
//======================================================================
#define GLOBLE_VAR
#include "includes.h"      //包含总头文件

//----------------------------------------------------------------------
//声明使用到的内部函数
//main.c使用的内部函数声明处
float TempRegression(uint16_t AD);
//----------------------------------------------------------------------
//主函数，一般情况下可以认为程序从此开始运行（实际上有启动过程，参见书稿）
int main(void)
{
    //（1）======启动部分（开头）==========================================
    //（1.1）声明main函数使用的局部变量
    uint32_t mMainLoopCount;  //主循环次数变量
    uint8_t  mFlag;           //灯的状态标志
    uint8_t i;


    
    //（1.2）【不变】关总中断
    DISABLE_INTERRUPTS;
    wdog_feed();
    printf("进入User的main...\n");
    
    //（1.3）给主函数使用的局部变量赋初值
    mMainLoopCount=0;    //主循环次数变量
    mFlag='R';           //灯的状态标志

    wdog_start(3);	  //启动看门狗

    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);      
    gpio_init(PIN_MAG,GPIO_INPUT,1);     
    wdog_feed();
    printf("LCD初始化...");
    LCD_Init();
    printf("成功\n");
    uart_init(UART_User,115200);

    wdog_feed();


    //（1.6）使能模块中断
    uart_enable_re_int(UART_User);
    //（1.7）【不变】开总中断
    ENABLE_INTERRUPTS;
    
  
    
    printf("金葫芦提示：LCD屏幕版面...");
    LCD_aotu(2,2,238,318,0);
    LCD_aotu(4,40,236,80,1);
    LCD_ShowString(72,20,RED,GRAY,(char *)"AHL-MCU-KL36");
    LCD_ShowString(68,52,RED,GRAY,(char *)"Hardware-Test");
  	wdog_feed();
    LCD_ShowString(8,88,BLACK,GRAY,(char *)"The current state:");
    LCD_aotu(4,106,236,116,1);

    LCD_ShowString(8,120,BLACK,GRAY,(char *)"Tri-coloured light:");
    wdog_feed();                                         
    
    LCD_aotu(4,138,236,316,1);
    printf("完成\n");

    for(;;)  
    {
		if(OoC==1){
			gpio_set(LIGHT_BLUE,LIGHT_ON); 
			LCD_ShowString(160,88,BLUE,GRAY,"OPEN ");
			LCD_ShowString(160,120,BLUE,GRAY,"BLUE");
			for (i=40;i>2;i=i-2)LCD_DrawCircle(120,220,i,BLUE);
		}
        if(OoC==0){
        	gpio_set(LIGHT_BLUE,LIGHT_OFF); 
        	LCD_ShowString(160,88,BLUE,GRAY,"CLOSE");
        	LCD_ShowString(160,120,BLUE,GRAY,"     ");
        	for (i=40;i>2;i=i-2)LCD_DrawCircle(120,220,i,GRAY);
        }
    }  
}   


//======以下为主函数调用的子函数===========================================
float TempRegression(uint16_t tmpAD)
{
    float v1,v2,S,T;
    v1 = ((float)tmpAD*3300)/65535;   //AD值变为采样点电压(mV)
    v2=3300 - v1;                    //分压电阻两端电压(mV)
    S = v1/v2;                       //分压比
    T = (1/(log(S)/3950.0 + (1/(273.15 + 25)))) - 273.15 + 0.5;
    return T;
}