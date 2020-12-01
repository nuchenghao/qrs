//====================================================================
//�ļ����ƣ�main.c��Ӧ�ù�����������
//����ṩ��SD-Arm��sumcu.suda.edu.cn��
//�汾���£�2017.08, 2020.06
//�����������������̵�<01_Doc>�ļ�����Readme.txt�ļ�
//====================================================================

#define GLOBLE_VAR
#include "includes.h"      //������ͷ�ļ�

//----------------------------------------------------------------------
//����ʹ�õ����ڲ�����
//main.cʹ�õ��ڲ�����������

void main_Dly_ms(uint32_t ms);
uint8_t ans[4];
int main(void)
{
    //��1��======�������֣���ͷ��==========================================
    //��1.1������main����ʹ�õľֲ�����
    uint32_t mMainLoopCount;  //��ѭ��ʹ�õļ�¼��ѭ����������
    uint8_t  mFlag;            //��ѭ��ʹ�õ���ʱ����
    
    //��1.2�������䡿�����ж�
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
    printf("���«��ʾ������ܲ���ʵ�� \r\n");
    printf("  �� ������˸\n");
    printf("  �� UART_Debug���ڣ�������115200��������������ʾ��Ϣ \r\n");
    printf("----------------------------------------------------\r\n"); 

    for(;;)     //for(;;)����ͷ��
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