//=====================================================================
//�ļ����ƣ�isr.c���жϴ������Դ�ļ���
//����ṩ��SD-ARM��sumcu.suda.edu.cn��
//�汾���£�20170801-20191020
//�����������ṩ�жϴ�������̿��
//=====================================================================
#include "includes.h"

void PORTC_PORTD_IRQHandler()

{
		DISABLE_INTERRUPTS;      //�����ж�
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
        ENABLE_INTERRUPTS;       //�����ж�
}
/*
 ֪ʶҪ�أ�
 1.���ļ��е��жϴ��������õľ�������豸��װ�õľ��幹�����ڸ���оƬ
 ʱ��ֻ�豣֤�豸�Ĺ����ӿ�һ�£����ɱ�֤���ļ�������жϴ����������κ�
 ���ģ��Ӷ��ﵽоƬ�޹��Ե�Ҫ��
 */
