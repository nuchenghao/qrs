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
void Test_Raytrace();
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
    printf("LCD��ʼ��...");
    LCD_Init();
    printf("�ɹ�\n");
    ENABLE_INTERRUPTS;
    
    printf("-----------------------------------------------------\r\n"); 
    printf("���«��ʾ������Ѱ������ʵ�� \r\n");
    printf("  �� ������˸\n");
    printf("  �� UART_Debug���ڣ�������115200������������Ӧ��ʾ��Ϣ \r\n");
    printf("----------------------------------------------------\r\n"); 
    
    
    LCD_aotu(2,2,238,318,0);
    LCD_ShowString(72,20,RED,GRAY,(char *)"AHL-MCU-KL36");
    LCD_DrawLine(2,40,238,40,BLACK);
  //  LCD_ShowString(8,52,RED,GRAY,(char *)"Offtrack:");
    for(;;)     //for(;;)����ͷ��
    {
        
        //��2.1����ѭ������+1�����ж��Ƿ�С���ض�����
        mMainLoopCount++;                         //+1
        if (mMainLoopCount<=6556677)  continue;   //���С���ض�����������ѭ��
       // Test_Raytrace();


		static char OutputCtl=0;
		OutputCtl++;
		uint8_t cnt=0;
		if (OutputCtl>=4) OutputCtl=1;
		gpio_init(RAY_RIGHT,GPIO_INPUT,0);
		gpio_init(RAY_LEFT,GPIO_INPUT,0);
		gpio_pull(RAY_RIGHT,0);
		gpio_pull(RAY_LEFT,0);
		if (gpio_get(RAY_LEFT))
		{
		   	gpio_init(MOTOR,GPIO_OUTPUT,1);
		    printf("�����⣺������\r\n\r\n");
		    LCD_ShowString(6,50,BLACK,GRAY,"[RAY-L]                    ");
		}
		else
		{
//		    gpio_init(MOTOR,GPIO_OUTPUT,0);
//		    
//		    LCD_ShowString(6,50,BLACK,GRAY,"                           ");
		    if (gpio_get(RAY_RIGHT))
		    {
		    	gpio_init(MOTOR,GPIO_OUTPUT,1);
		    	printf("�Ҳ���⣺������\r\n\r\n");
		    	LCD_ShowString(66,50,BLACK,GRAY,"[RAY-R]                   ");
		    }
		    else
		    {
		    	gpio_init(MOTOR,GPIO_OUTPUT,0);
		    	printf("�Ҳ���⣺������;�Ҳ���⣺������\n");
		    	LCD_ShowString(6,50,BLACK,GRAY,"                                            ");
		    }
		
		}

		
        mMainLoopCount=0;    
        if (mFlag=='A')   
        {
            gpio_set(LIGHT_BLUE,LIGHT_ON);   //���õơ�����
            printf("���ƣ���\r\n\r\n");           //ͨ�����Դ�������Ƶ�״̬
            mFlag='L';                        //�ı�״̬��־
        }
        else                   //����,����״̬��־��Ϊ'A'    
        {
            gpio_set(LIGHT_BLUE,LIGHT_OFF);  //���õơ�����  
            printf("���ƣ���\r\n\r\n");           //ͨ�����Դ�������Ƶ�״̬
            mFlag='A';                        //�ı�״̬��־
        }	
    }     //for(;;)��β
    //��2��======��ѭ�����֣���β��========================================
}

//======����Ϊ���������õ��Ӻ�����Ŵ�=====================================
//=====================================================================
//�������ƣ�Test_Raytrace
//�������أ���
//����˵������
//���ܸ�Ҫ�����Ժ���Ѱ������������
//=====================================================================
void Test_Raytrace()
{
    static char OutputCtl=0;
    OutputCtl++;
    uint8_t cnt=0;
    if (OutputCtl>=4) OutputCtl=1;
    //��ʼ������ѭ���������������ţ�����Ϊ�͵�ƽ����
    gpio_init(RAY_RIGHT,GPIO_INPUT,0);
    gpio_init(RAY_LEFT,GPIO_INPUT,0);
    gpio_pull(RAY_RIGHT,0);
    gpio_pull(RAY_LEFT,0);
    if (gpio_get(RAY_LEFT))
    {
    	gpio_init(MOTOR,GPIO_OUTPUT,1);
    	printf("�����⣺������\r\n\r\n");
    	LCD_ShowString(6,50,BLACK,GRAY,"[RAY-L]                    ");
    }
    else
    {
    	gpio_init(MOTOR,GPIO_OUTPUT,0);
    	printf("�����⣺������\r\n\r\n");
    	LCD_ShowString(6,50,BLACK,GRAY,"                           ");

    }
    if (gpio_get(RAY_RIGHT))
    {
    	gpio_init(MOTOR,GPIO_OUTPUT,1);
    	printf("�Ҳ���⣺������\r\n\r\n");
    	LCD_ShowString(66,50,BLACK,GRAY,"[RAY-R]                   ");
    }
    else
    {
    	gpio_init(MOTOR,GPIO_OUTPUT,0);
    	printf("�Ҳ���⣺������\r\n\r\n");
    	LCD_ShowString(66,50,BLACK,GRAY,"                         ");
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


