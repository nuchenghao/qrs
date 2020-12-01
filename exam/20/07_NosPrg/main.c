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
void Test_Motor();
void main_Dly_ms(uint32_t ms);
//----------------------------------------------------------------------
//��������һ������¿�����Ϊ����Ӵ˿�ʼ���У�ʵ�������������̼���壩
int main(void)
{

    uint32_t mMainLoopCount;  
    uint8_t  mFlag,cnt;            
    uint16_t light;

    DISABLE_INTERRUPTS;

    

    mMainLoopCount = 0;    
    mFlag='A';              
    

    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);   
	adc_init(AD_LIGHT,0);
    
    //��1.6��ʹ��ģ���ж�
    //uart_enable_re_int(UART_User);
    //��1.7�������䡿�����ж�
    ENABLE_INTERRUPTS;
    
    printf("-----------------------------------------------------\r\n"); 
    printf("���«��ʾ����������ʵ�� \r\n");
    printf("  �� ������˸\n");
    printf("  �� UART_Debug���ڣ�������115200��������������ʾ��Ϣ \r\n");
    printf("----------------------------------------------------\r\n"); 
    
    
    //��1��======�������֣���β��==========================================
    
    cnt=0;
    for(;;)     //for(;;)����ͷ��
    {
        
        mMainLoopCount++;                      
        if (mMainLoopCount<=6556677)  continue;  
        mMainLoopCount=0;
       // Test_Motor();
		light = adc_read(AD_LIGHT);
		light/=10;
		printf("%d\n",light);
		if(light<=1000){
			gpio_init(MOTOR,GPIO_OUTPUT,1);
		}
		else gpio_init(MOTOR,GPIO_OUTPUT,0);
    }   
}

//======����Ϊ���������õ��Ӻ�����Ŵ�=====================================
//=====================================================================
//�������ƣ�Test_Motor
//�������أ���
//����˵������
//���ܸ�Ҫ����������ﴫ��������
//=====================================================================
void Test_Motor()
{	
    static char OutputCtl=0;
    OutputCtl++;
    if (OutputCtl>=4) OutputCtl=1;
    switch (OutputCtl)
    {
    	case 1:
        	gpio_init(MOTOR,GPIO_OUTPUT,1);
            printf("����￪ʼ��\r\n\r\n");
            break;
        case 2:
            gpio_init(MOTOR,GPIO_OUTPUT,0);
            printf("�����ֹͣ��\r\n\r\n");
            break;
        case 3:
            gpio_init(MOTOR,GPIO_OUTPUT,1);
            printf("������ٴ���\r\n\r\n");
            break;
        default:
	        break;
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



