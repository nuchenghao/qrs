//====================================================================
//�ļ����ƣ�main.c��Ӧ�ù�����������
//����ṩ��SD-Arm��sumcu.suda.edu.cn��
//�汾���£�2017.08, 2020.06
//�����������������̵�<01_Doc>�ļ�����Readme.txt�ļ�
//====================================================================

#define GLOBLE_VAR
#include "includes.h"      //������ͷ�ļ�




int main(void)
{
    //��1��======�������֣���ͷ��==========================================
    //��1.1������main����ʹ�õľֲ�����
    uint32_t mMainLoopCount,cnt;  //��ѭ��ʹ�õļ�¼��ѭ����������
    uint8_t  mFlag;            //��ѭ��ʹ�õ���ʱ����
    
    //��1.2�������䡿�����ж�
    DISABLE_INTERRUPTS;

    
    //��1.3����������ʹ�õľֲ���������ֵ
    mMainLoopCount = 0;     //��ѭ��ʹ�õļ�¼��ѭ����������
    mFlag='A';              //��ѭ��ʹ�õ���ʱ����������״̬��־
    
    //��1.4����ȫ�ֱ�������ֵ
    
    //��1.5���û�����ģ���ʼ��
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);    //��ʼ������
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);    //��ʼ�����
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);    //��ʼ���̵�
    uart_init(UART_User,9600); 
  //  whii=4;
    
    //��1.6��ʹ��ģ���ж�
    uart_enable_re_int(UART_User);
    //��1.7�������䡿�����ж�
    ENABLE_INTERRUPTS;
    
    printf("-----------------------------------------------------\r\n"); 
    printf("���«��ʾ������ͨ��ʵ�� \r\n"); 
    printf("  �� ������˸\n");
    printf("  �� UART_User���ڣ��յ�һ���ֽڽ�������жϷ������ \r\n");
    printf("     ��isr.c�ļ���UART_USER_Handler���ó�����Ϊ�� \r\n");
    printf("     �յ�һ���ֽڣ�ֱ�ӷ��ظ��ֽڣ�������115200��    \r\n");
    printf("     ���˳������棬ת�롰���ߡ��������ڹ��ߡ���֤    \r\n"); 
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