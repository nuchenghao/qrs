//====================================================================
//文件名称：main.c（应用工程主函数）
//框架提供：SD-Arm（sumcu.suda.edu.cn）
//版本更新：2017.08, 2020.06
//功能描述：见本工程的<01_Doc>文件夹下Readme.txt文件
//====================================================================

#define GLOBLE_VAR
#include "includes.h"      //包含总头文件




int main(void)
{
    //（1）======启动部分（开头）==========================================
    //（1.1）声明main函数使用的局部变量
    uint32_t mMainLoopCount,cnt;  //主循环使用的记录主循环次数变量
    uint8_t  mFlag;            //主循环使用的临时变量
    
    //（1.2）【不变】关总中断
    DISABLE_INTERRUPTS;

    
    //（1.3）给主函数使用的局部变量赋初值
    mMainLoopCount = 0;     //主循环使用的记录主循环次数变量
    mFlag='A';              //主循环使用的临时变量：蓝灯状态标志
    
    //（1.4）给全局变量赋初值
    
    //（1.5）用户外设模块初始化
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);    //初始化蓝灯
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);    //初始化红灯
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);    //初始化绿灯
    uart_init(UART_User,9600); 
  //  whii=4;
    
    //（1.6）使能模块中断
    uart_enable_re_int(UART_User);
    //（1.7）【不变】开总中断
    ENABLE_INTERRUPTS;
    
    printf("-----------------------------------------------------\r\n"); 
    printf("金葫芦提示：串行通信实例 \r\n"); 
    printf("  ① 蓝灯闪烁\n");
    printf("  ② UART_User串口，收到一个字节进入接收中断服务程序 \r\n");
    printf("     即isr.c文件中UART_USER_Handler，该程序功能为： \r\n");
    printf("     收到一个字节，直接返回该字节（波特率115200）    \r\n");
    printf("     请退出本界面，转入“工具”→“串口工具”验证    \r\n"); 
    printf("----------------------------------------------------\r\n"); 


//	gpio_set(LIGHT_RED,LIGHT_OFF);
//	gpio_set(LIGHT_GREEN,LIGHT_OFF);
//	gpio_set(LIGHT_BLUE,LIGHT_ON);

	
    for(;;)   
    {
    	mMainLoopCount++;                        
        if (mMainLoopCount<=6556677)  continue;   
        mMainLoopCount=0;  
        cnt=0;
        printf("%d\n",whi);
        switch(whi){
        	case 0:{
        		gpio_set(LIGHT_RED,LIGHT_OFF);
				gpio_set(LIGHT_GREEN,LIGHT_OFF);
				gpio_set(LIGHT_BLUE,LIGHT_OFF);
				break;
        	}
        	case 1:{
        		gpio_set(LIGHT_RED,LIGHT_OFF);
				gpio_set(LIGHT_GREEN,LIGHT_OFF);
				gpio_set(LIGHT_BLUE,LIGHT_ON);
				while(cnt<=1556677)cnt++;
				gpio_set(LIGHT_RED,LIGHT_ON);
				gpio_set(LIGHT_GREEN,LIGHT_OFF);
				gpio_set(LIGHT_BLUE,LIGHT_OFF);
				while(cnt<=1556677*3)cnt++;
				gpio_set(LIGHT_RED,LIGHT_OFF);
				gpio_set(LIGHT_GREEN,LIGHT_ON);
				gpio_set(LIGHT_BLUE,LIGHT_OFF);
				while(cnt<=1556677*5)cnt++;
				gpio_set(LIGHT_RED,LIGHT_OFF);
				gpio_set(LIGHT_GREEN,LIGHT_OFF);
				gpio_set(LIGHT_BLUE,LIGHT_OFF);
				break;
        	}
        	case 2:{
        		gpio_set(LIGHT_RED,LIGHT_OFF);
				gpio_set(LIGHT_GREEN,LIGHT_OFF);
				gpio_set(LIGHT_BLUE,LIGHT_ON);
				while(cnt<=1556677*3)cnt++;
				gpio_set(LIGHT_RED,LIGHT_OFF);
				gpio_set(LIGHT_GREEN,LIGHT_ON);
				gpio_set(LIGHT_BLUE,LIGHT_OFF);
				while(cnt<=1556677*5)cnt++;
				gpio_set(LIGHT_RED,LIGHT_OFF);
				gpio_set(LIGHT_GREEN,LIGHT_OFF);
				gpio_set(LIGHT_BLUE,LIGHT_OFF);
				break;
        	}
        	case 3:{
        		gpio_set(LIGHT_RED,LIGHT_OFF);
				gpio_set(LIGHT_GREEN,LIGHT_OFF);
				gpio_set(LIGHT_BLUE,LIGHT_ON);
				while(cnt<=1556677)cnt++;
				gpio_set(LIGHT_RED,LIGHT_ON);
				gpio_set(LIGHT_GREEN,LIGHT_OFF);
				gpio_set(LIGHT_BLUE,LIGHT_OFF);
				while(cnt<=1556677*5)cnt++;
				gpio_set(LIGHT_RED,LIGHT_OFF);
				gpio_set(LIGHT_GREEN,LIGHT_OFF);
				gpio_set(LIGHT_BLUE,LIGHT_OFF);
				break;
        	}
        	case 4:{
				gpio_set(LIGHT_RED,LIGHT_ON);
				gpio_set(LIGHT_GREEN,LIGHT_OFF);
				gpio_set(LIGHT_BLUE,LIGHT_OFF);
				while(cnt<=1556677*3)cnt++;
				gpio_set(LIGHT_RED,LIGHT_OFF);
				gpio_set(LIGHT_GREEN,LIGHT_ON);
				gpio_set(LIGHT_BLUE,LIGHT_OFF);
				while(cnt<=1556677*5)cnt++;
				gpio_set(LIGHT_RED,LIGHT_OFF);
				gpio_set(LIGHT_GREEN,LIGHT_OFF);
				gpio_set(LIGHT_BLUE,LIGHT_OFF);
				break;
        	}
        }
    }     
}