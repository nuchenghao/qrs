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
void Test_Lantern(uint8_t whii);
void Test_Button();
void main_Dly_ms(uint32_t ms);
uint8_t whi;
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


    mMainLoopCount = 0;    
    mFlag='A';             
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);  

    ENABLE_INTERRUPTS;
    
    printf("-----------------------------------------------------\r\n"); 
    printf("金葫芦提示：彩灯测试实例 \r\n");
    printf("  ① 蓝灯闪烁\n");
    printf("  ② UART_Debug串口（波特率115200），输出彩灯提示信息 \r\n");
    printf("----------------------------------------------------\r\n"); 
    uint32_t cnt;
	whi=0;

    for(;;)    
    {
 
        Test_Button();

    }    
}

void Test_Button()
{
	gpio_init(Button1,GPIO_OUTPUT,0);
	gpio_init(Button2,GPIO_OUTPUT,1);
	gpio_init(Button3,GPIO_INPUT,0);
	gpio_pull(Button3,1);
	gpio_init(Button4,GPIO_INPUT,0);
	gpio_pull(Button4,1);
	if (gpio_get(Button3)==0)       
	{
		whi=1;
	}
	if (gpio_get(Button4)==0)
	{
		whi=2;
	}

	gpio_init(Button1,GPIO_OUTPUT,1);
	gpio_init(Button2,GPIO_OUTPUT,0);
	gpio_init(Button3,GPIO_INPUT,0);
	gpio_pull(Button3,1);
	gpio_init(Button4,GPIO_INPUT,0);
	gpio_pull(Button4,1);
	if (gpio_get(Button3)==0)
	{
		whi=3;
	}
	if (gpio_get(Button4)==0)
	{
		whi=4;
	}
	if(whi!=0)Test_Lantern(whi);
}


void Test_Lantern(uint8_t whii)
{	
    
    uint8_t grb1[12]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t grb2[12]={0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t grb4[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00};
    uint8_t grb3[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF};
    uint8_t grb5[12]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t grb6[12]={0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t grb7[12]={0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF};
    uint8_t grb8[12]={0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};
    uint8_t grb9[12]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x0};
    uint8_t grb10[12]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};
    uint8_t grb11[12]={0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};
    
    uint8_t rwg1[12]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t rwg2[12]={0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00};
    uint8_t rwg3[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF};
    uint8_t rwg4[12]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t rwg5[12]={0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00};
    uint8_t rwg6[12]={0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};
    uint8_t rwg7[12]={0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};
    
    uint8_t black[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    WS_Init(COLORLIGHT);
    uint32_t cntt=0;
    switch(whii)
    {
    	case 1:
    		WS_SendOnePix(COLORLIGHT,black,4);
    		WS_SendOnePix(COLORLIGHT,grb1,4);
    		while(cntt<=1500000)cntt++;
    		WS_SendOnePix(COLORLIGHT,grb2,4);
    		while(cntt<=3000000)cntt++;
    		WS_SendOnePix(COLORLIGHT,grb3,4);
    		while(cntt<=4500000)cntt++;
    		WS_SendOnePix(COLORLIGHT,grb4,4);
    		while(cntt<=6000000)cntt++;
    		WS_SendOnePix(COLORLIGHT,grb5,4);
    		while(cntt<=7500000)cntt++;
    		WS_SendOnePix(COLORLIGHT,grb6,4);
    		while(cntt<=9000000)cntt++;
    		WS_SendOnePix(COLORLIGHT,grb7,4);
    		while(cntt<=10500000)cntt++;
    		WS_SendOnePix(COLORLIGHT,grb8,4);
    		while(cntt<=12000000)cntt++;
    		break;
    	case 2:
    			WS_SendOnePix(COLORLIGHT,black,4);
    			WS_SendOnePix(COLORLIGHT,grb1,4);
    		 	while(cntt<=1500000)cntt++;
    			WS_SendOnePix(COLORLIGHT,grb4,4);
    			while(cntt<=3000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,grb3,4);
    			while(cntt<=4500000)cntt++;
    			WS_SendOnePix(COLORLIGHT,grb2,4);
    			while(cntt<=6000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,grb5,4);
    			while(cntt<=7500000)cntt++;
    			WS_SendOnePix(COLORLIGHT,grb9,4);
    			while(cntt<=9000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,grb10,4);
    			while(cntt<=10500000)cntt++;
    			WS_SendOnePix(COLORLIGHT,grb11,4);
    			while(cntt<=12000000)cntt++;
    			break;
    			
    	case 3:
				WS_SendOnePix(COLORLIGHT,black,4);
    			WS_SendOnePix(COLORLIGHT,rwg1,4);
    			while(cntt<=2000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg2,4);
    			while(cntt<=4000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg3,4);
    			while(cntt<=6000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg4,4);
    			while(cntt<=8000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg5,4);
    			while(cntt<=10000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg6,4);
    			while(cntt<=12000000)cntt++;
    			break;
    	case 4:
    			WS_SendOnePix(COLORLIGHT,black,4);
    			WS_SendOnePix(COLORLIGHT,rwg3,4);
    			while(cntt<=2000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg2,4);
    			while(cntt<=4000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg1,4);
    			while(cntt<=6000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg3,4);
    			while(cntt<=8000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg7,4);
    			while(cntt<=10000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg6,4);
    			while(cntt<=12000000)cntt++;
    			break;
    			
    	default:
		        break;
    }
    
//    static char OutputCtl=0;
//    OutputCtl++;
//    if (OutputCtl>=4) OutputCtl=1;
//    WS_Init(COLORLIGHT);
//    //(1)彩灯测试数据
//    switch (OutputCtl)
//    {
//    	case 1:
//        	WS_SendOnePix(COLORLIGHT,grbw,2);
//            printf("点亮彩灯\r\n\r\n");
//            break;
//        case 2:
//            WS_SendOnePix(COLORLIGHT,black,2);
//            printf("熄灭彩灯\r\n\r\n");
//            break;
//        case 3:
//            WS_SendOnePix(COLORLIGHT,rwgb,2);
//            printf("改变彩灯颜色\r\n\r\n");
//            break;
//        default:
//	        break;
//    }
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



