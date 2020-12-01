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

//----------------------------------------------------------------------
//��������һ������¿�����Ϊ����Ӵ˿�ʼ���У�ʵ�������������̼���壩
int main(void)
{

    uint8_t  mFlag;           //��ѭ��ʹ�õ���ʱ����
    uint8_t  mSec;	         //�ǵ�ǰ���ֵ
    DISABLE_INTERRUPTS;
    wdog_stop();

    mFlag='A';              //��ѭ��ʹ�õ���ʱ����������״̬��־
	
   	gTime[0] = 0;       //ʱ
   	gTime[1] = 0;	  	//��
   	gTime[2] = 0;	  	//��
   	mSec = gTime[2];	//��ס��ǰ���ֵ

    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);    //��ʼ������
   	uart_init(UART_User, 9600);
    systick_init(20);      //����systickΪ10ms�ж�
   	uart_enable_re_int(UART_User);
    ENABLE_INTERRUPTS;//���ж�

    printf("------------------------------------------------------\n");
    printf("���«��ʾ��systick��ʱ��ʵ�� \n");
    printf("  �� ������˸\n");
   	printf("  �� ÿ10ms�жϴ���SysTick��ʱ���жϴ�������һ�Ρ� \n");
   	printf("  �� ����SysTick��ʱ���жϴ�������󣬾�̬����10ms��Ԫ+1�� \n");
   	printf("  �� �ﵽһ��ʱ��������+1�����򣬼��㡰ʱ���֡��롱�� \n");
   	printf("  �� ʹ��ȫ�ֱ����ֽ�������gTime[3]���ֱ�洢��ʱ���֡��롱�� \n");
   	printf("  �� ע�����о�̬������ʹ�� \n");
    printf("------------------------------------------------------\n");


    for(;;)     //for(;;)����ͷ��
    {

   		if (gTime[2] == mSec%60||gTime[2] == (mSec+1)%60)   continue;
        mSec = gTime[2];
        if (mFlag=='A')   
        {
            gpio_set(LIGHT_RED,LIGHT_ON);   //���õơ�����
            printf("%d:%d:%d  ",gTime[0],gTime[1],gTime[2]);
            printf("��ƣ���\n");             //ͨ�����Դ�������Ƶ�״̬
            mFlag='L';                        //�ı�״̬��־
        }
        else                   //����,����״̬��־��Ϊ'A'
        {
            gpio_set(LIGHT_RED,LIGHT_OFF);  //���õơ�����
            printf("%d:%d:%d  ",gTime[0],gTime[1],gTime[2]);
            printf("��ƣ���\n");             //ͨ�����Դ�������Ƶ�״̬
            mFlag='A';                        //�ı�״̬��־
        }
    }    
}

