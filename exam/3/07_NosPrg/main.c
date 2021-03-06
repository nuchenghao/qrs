//====================================================================
//文件名称：main.c（应用工程主函数）
//框架提供：SD-Arm（sumcu.suda.edu.cn）
//版本更新：20170801-20200502
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
    uint32_t mMainLoopCount;  //主循环使用的记录主循环次数变量
    uint8_t  mFlag;            //主循环使用的临时变量
    
    //（1.2）【不变】关总中断
    DISABLE_INTERRUPTS;

    
    //（1.3）给主函数使用的局部变量赋初值
    mMainLoopCount = 0;     //主循环使用的记录主循环次数变量
    mFlag='A';              //主循环使用的临时变量：蓝灯状态标志
    
    //（1.4）给全局变量赋初值
    

    gpio_init(LIGHT_BLUE,1,LIGHT_OFF);    //初始化蓝灯
    gpio_init(LIGHT_RED,1,LIGHT_OFF);
    gpio_init(LIGHT_GREEN,1,LIGHT_OFF);
    gpio_init(PTC_NUM|(1),0,1);
    gpio_init(PTC_NUM|(0),0,1);

	
    //（1.7）【不变】开总中断
    ENABLE_INTERRUPTS;
    
    printf("------------------------------------------------------\n");   
    printf("金葫芦提示：构件法输出控制小灯亮暗   \n");
    printf("第一次用构件方法点亮的蓝色发光二极管，\n");
    printf("这是进行应用编程的第一步，可以在此基础上，\n");
    printf("“照葫芦画瓢”地继续学习实践。\n");
    printf("例如：改为绿灯；调整闪烁频率等。\n");
    printf("------------------------------------------------------\n"); 
    
    //for(;;) {  }     //在此打桩，理解蓝色发光二极管为何亮起来了？
    
    //（1）======启动部分（结尾）==========================================
    
    //（2）======主循环部分（开头）=========================================
    int cnt=0;
    for(;;)     //for(;;)（开头）
    {
        
        if(gpio_get(PTC_NUM|(0))==1 && gpio_get(PTC_NUM|(1))==1){
        	cnt=0;
         	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_ON);    //设置灯“亮” 蓝灯
        	while(cnt<=5000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_ON); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //设置灯“亮” 绿灯
        	while(cnt<=10000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_ON); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //设置灯“亮” 红灯
        	while(cnt<=15000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //设置灯“亮” 红灯
        	while(cnt<=35000009)cnt++;
        }
        if(gpio_get(PTC_NUM|(1))==0 && gpio_get(PTC_NUM|(0))==1){//01 
        	cnt=0;
         	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_ON);    //设置灯“亮” 蓝灯
        	while(cnt<=5000009)cnt++;
//        	gpio_set(LIGHT_RED,LIGHT_OFF); 
//        	gpio_set(LIGHT_GREEN,LIGHT_ON); 
//        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //设置灯“亮” 绿灯
//        	while(cnt<=10000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_ON); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //设置灯“亮” 红灯
        	while(cnt<=10000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //设置灯“亮” 红灯
        	while(cnt<=30000009)cnt++;
        }
        if(gpio_get(PTC_NUM|(1))==1 && gpio_get(PTC_NUM|(0))==0){//10
        	        	cnt=0;
//         	gpio_set(LIGHT_RED,LIGHT_OFF); 
//        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
//        	gpio_set(LIGHT_BLUE,LIGHT_ON);    //设置灯“亮” 蓝灯
//        	while(cnt<=5000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_ON); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //设置灯“亮” 绿灯
        	while(cnt<=5000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_ON); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //设置灯“亮” 红灯
        	while(cnt<=10000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //设置灯“亮” 红灯
        	while(cnt<=30000009)cnt++;
        }
        if(gpio_get(PTC_NUM|(1))==0 && gpio_get(PTC_NUM|(0))==0){//00
        	cnt=0;
         	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_ON);    //设置灯“亮” 蓝灯
        	while(cnt<=5000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_ON); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //设置灯“亮” 绿灯
        	while(cnt<=10000009)cnt++;
//        	gpio_set(LIGHT_RED,LIGHT_ON); 
//        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
//        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //设置灯“亮” 红灯
//        	while(cnt<=15000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //设置灯“亮” 红灯
        	while(cnt<=30000009)cnt++;
        }
    }     //for(;;)结尾
    //（2）======主循环部分（结尾）========================================
}

//======以下为主函数调用的子函数存放处=====================================

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



