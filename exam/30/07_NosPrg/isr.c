//=====================================================================
//文件名称：isr.c（中断处理程序源文件）
//框架提供：SD-ARM（sumcu.suda.edu.cn）
//版本更新：20170801-20191020
//功能描述：提供中断处理程序编程框架
//=====================================================================
#include "includes.h"

void PORTC_PORTD_IRQHandler()

{
		DISABLE_INTERRUPTS;      //关总中断
	    if(gpio_get_int(PTC_NUM|(0))&&!ccnt){
	    
			if(cnt){
				printf("out\n");
	    		gpio_set(PTC_NUM|(1),0);
	    		cnt^=1;
			}else{

				printf("in\n");
	    		gpio_set(PTC_NUM|(1),1);
	    		cnt^=1;
			}
			ccnt=1;
			//gpio_clear_int(PTC_NUM|(0));
        }
        gpio_clear_int(PTC_NUM|(0));
        ENABLE_INTERRUPTS;       //开总中断
}
/*
 知识要素：
 1.本文件中的中断处理函数调用的均是相关设备封装好的具体构件，在更换芯片
 时，只需保证设备的构件接口一致，即可保证本文件的相关中断处理函数不做任何
 更改，从而达到芯片无关性的要求。
 */
