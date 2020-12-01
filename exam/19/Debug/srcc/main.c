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

void main_Dly_ms(uint32_t ms);
uint8_t ans[4];
int main(void)
{
    //（1）======启动部分（开头）==========================================
    //（1.1）声明main函数使用的局部变量
    uint32_t mMainLoopCount;  //主循环使用的记录主循环次数变量
    uint8_t  mFlag;            //主循环使用的临时变量
    
    //（1.2）【不变】关总中断
    DISABLE_INTERRUPTS;

    
	uint16_t mcu_temp_AD;	
	float temperature;
	float mcu_temp;
    mMainLoopCount = 0;    
    mFlag='A';             
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);   
	adc_init(AD_MCU_TEMP,0);
	adc_init(AD_BOARD_TEMP,0);
    ENABLE_INTERRUPTS;
    
    printf("-----------------------------------------------------\r\n"); 
    printf("金葫芦提示：数码管测试实例 \r\n");
    printf("  ① 蓝灯闪烁\n");
    printf("  ② UART_Debug串口（波特率115200），输出数码管提示信息 \r\n");
    printf("----------------------------------------------------\r\n"); 

    for(;;)     //for(;;)（开头）
    {
        

        mMainLoopCount++;                        
        if (mMainLoopCount<=16556677)  continue;  
		mcu_temp_AD = adc_read(AD_MCU_TEMP);
        mcu_temp=TempTrans(mcu_temp_AD);
        temperature = TempRegression(adc_read(AD_BOARD_TEMP));
        printf("%.2f\n",temperature);
        if(temperature>=25.00)gpio_init(BEEF,GPIO_OUTPUT,1);
        else gpio_init(BEEF,GPIO_OUTPUT,0);
        mMainLoopCount=0;     
	
    }     
}



void main_Dly_ms(uint32_t ms)
{
    for(uint32_t i= 0; i < (6000*ms); i++) __asm("nop");
}