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
void Test_RAY_HUMAN();
void main_Dly_ms(uint32_t ms);
//----------------------------------------------------------------------
//��������һ������¿�����Ϊ����Ӵ˿�ʼ���У�ʵ�������������̼���壩
int main(void)
{
    //��1��======�������֣���ͷ��==========================================
    //��1.1������main����ʹ�õľֲ�����
    uint32_t mMainLoopCount;  //��ѭ��ʹ�õļ�¼��ѭ����������
    uint8_t  mFlag;            //��ѭ��ʹ�õ���ʱ����
    
    //��1.2�������䡿�����ж�
    DISABLE_INTERRUPTS;

    
    //��1.3����������ʹ�õľֲ���������ֵ
    mMainLoopCount = 0;     //��ѭ��ʹ�õļ�¼��ѭ����������
    mFlag='A';              //��ѭ��ʹ�õ���ʱ����������״̬��־
    
    //��1.4����ȫ�ֱ�������ֵ
    
    //��1.5���û�����ģ���ʼ��
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);    //��ʼ������
     wdog_feed();
     printf("LCD��ʼ��...");
     LCD_Init();
      printf("�ɹ�\n");
    //��1.6��ʹ��ģ���ж�
    //uart_enable_re_int(UART_User);
    //��1.7�������䡿�����ж�
    ENABLE_INTERRUPTS;
    

    
    LCD_aotu(2,2,238,318,0);
    LCD_aotu(4,40,236,80,1);
    LCD_ShowString(72,20,RED,GRAY,(char *)"AHL-MCU-KL36");

  	wdog_feed();
   	LCD_ShowString(8,50,BLACK,GRAY,(char *)"Person:");
   	LCD_aotu(4,70,236,316,1);
   
   for(;;)     //for(;;)����ͷ��
    {
        
        //��2.1����ѭ������+1�����ж��Ƿ�С���ض�����
        mMainLoopCount++;                         //+1
        if (mMainLoopCount<=6556677)  continue;   //���С���ض�����������ѭ��
     //   gpio_init(BEEF,GPIO_OUTPUT,0);
     //   while(mMainLoopCount<=12556677) mMainLoopCount++; 
        mMainLoopCount=0;  
        Test_RAY_HUMAN();
        
    }     
}

//======����Ϊ���������õ��Ӻ�����Ŵ�=====================================
//=====================================================================
//�������ƣ�Test_RAY_HUMAN
//�������أ���
//����˵������
//���ܸ�Ҫ������������⴫��������
//=====================================================================
void Test_RAY_HUMAN()
{
    gpio_init(RAY_HUMAN,GPIO_INPUT,0);		//��ʼ����ƺ�������⴫����ģ��
    gpio_pull(RAY_HUMAN,0);
    if (gpio_get(RAY_HUMAN))
    {
    	gpio_init(BEEF,GPIO_OUTPUT,1);
    	LCD_ShowString(84,50,RED,GRAY,"Yes");
    	printf("���⣺�������\r\n\r\n");
    	LCD_DrawCircle(120,110,15,BLACK);
    	LCD_DrawLine(120,125,120,180,BLACK);
    	LCD_DrawLine(120,140,60,160,BLACK);
    	LCD_DrawLine(120,140,180,160,BLACK);
    	LCD_DrawLine(120,180,80,220,BLACK);
    	LCD_DrawLine(120,180,160,220,BLACK);
    }
    else
    {
    gpio_init(BEEF,GPIO_OUTPUT,0);
    	LCD_ShowString(84,50,BLACK,GRAY,"No ");
    	printf("���⣺�������\r\n\r\n");
    	LCD_DrawCircle(120,110,15,GRAY);
    	LCD_DrawLine(120,125,120,180,GRAY);
    	LCD_DrawLine(120,140,60,160,GRAY);
    	LCD_DrawLine(120,140,180,160,GRAY);
    	LCD_DrawLine(120,180,80,220,GRAY);
    	LCD_DrawLine(120,180,160,220,GRAY);
    }
}

void main_Dly_ms(uint32_t ms)
{
    for(uint32_t i= 0; i < (6000*ms); i++) __asm("nop");
}
//====================================================================
/*
֪ʶҪ�أ�
��1��main.c��һ��ģ�壬���ļ����д�������漰�����Ӳ���ͻ�����ͨ�����ù���
ʵ�ֶ�Ӳ���ĸ�Ԥ��
��2�����ļ��б��С����䡿�ĵط�Ϊϵͳ��������������������Ŀ�޹أ�����ɾ����
��3�����ļ��жԺ�GLOBLE_VAR�����˶��壬�����ڰ���"includes.h"ͷ�ļ�ʱ���ᶨ
��ȫ�ֱ������������ļ��а���"includes.h"ͷ�ļ�ʱ��
����ʱ���Զ�����extern
*/



