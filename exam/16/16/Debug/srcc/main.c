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
    float temperature;
    uint16_t light;
    uint16_t mcu_temp_AD;
    float mcu_temp;
    uint16_t bat_AD;
    float bat_V;
    uint8_t mag;
    uint16_t AD_CAL1;
	uint16_t AD_CAL2;
    
    //（1.2）【不变】关总中断
    DISABLE_INTERRUPTS;
    wdog_feed();
    printf("进入User的main...\n");
    
    //（1.3）给主函数使用的局部变量赋初值
    mMainLoopCount=0;    //主循环次数变量
    mFlag='R';           //灯的状态标志
    //（1.4）给全局变量赋初值
    
    //（1.5）用户外设模块初始化
    wdog_start(3);	  //启动看门狗

    gpio_init(PIN_MAG,GPIO_INPUT,1);     
    wdog_feed();
    printf("LCD初始化...");
    LCD_Init();
    printf("成功\n");
    uart_init(UART_User,115200);

    adc_init(AD_TEMP,0);
    adc_init(AD_MCU_TEMP,0);
    wdog_feed();
//    adc_init(AD_BAT,0);

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
    LCD_ShowString(8,88,BLACK,GRAY,(char *)"MCU_Tmp:");
    wdog_feed();                                         

	uint8_t temp[3];

    for(;;)
    {
    	wdog_feed();
        mMainLoopCount++;
        if (mMainLoopCount<=0x1fffff)  continue;
        mMainLoopCount=0; 
        wdog_feed();
		
		mcu_temp_AD = adc_read(AD_MCU_TEMP);
        mcu_temp=TempTrans(mcu_temp_AD);
        LCD_ShowString(84,88,BLACK,GRAY,"     ");
        LCD_ShowString(84,88,GREEN,GRAY,(char *)NumToStr_float(mcu_temp,2,temp));
        wdog_feed();


			
          uint8_t friction=(((int)(mcu_temp*10.0))%10)*10+((int)(mcu_temp*100.0))%10;
          temp[0] = (char)mcu_temp;
          temp[1] = (char)friction;//MCU的温度
          temp[2] = '\0';
         uart_send_string(UART_User,temp);

        
    }  
}  

float TempRegression(uint16_t tmpAD)
{
    float v1,v2,S,T;
    v1 = ((float)tmpAD*3300)/65535;
    v2=3300 - v1;                    
    S = v1/v2;                     
    T = (1/(log(S)/3950.0 + (1/(273.15 + 25)))) - 273.15 + 0.5;
    return T;
}