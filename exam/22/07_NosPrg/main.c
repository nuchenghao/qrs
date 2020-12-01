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
void Test_Lantern(uint8_t whii);
void Test_Button();
void main_Dly_ms(uint32_t ms);
uint8_t whi;
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


    mMainLoopCount = 0;    
    mFlag='A';             
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);  

    ENABLE_INTERRUPTS;
    
    printf("-----------------------------------------------------\r\n"); 
    printf("���«��ʾ���ʵƲ���ʵ�� \r\n");
    printf("  �� ������˸\n");
    printf("  �� UART_Debug���ڣ�������115200��������ʵ���ʾ��Ϣ \r\n");
    printf("----------------------------------------------------\r\n"); 
    uint32_t cnt;
	whi=0;

    for(;;)    
    {
 
        Test_Button();

    }    
}

void Test_Button()
{
	gpio_init(Button1,GPIO_OUTPUT,0);
	gpio_init(Button2,GPIO_OUTPUT,1);
	gpio_init(Button3,GPIO_INPUT,0);
	gpio_pull(Button3,1);
	gpio_init(Button4,GPIO_INPUT,0);
	gpio_pull(Button4,1);
	if (gpio_get(Button3)==0)       
	{
		whi=1;
	}
	if (gpio_get(Button4)==0)
	{
		whi=2;
	}

	gpio_init(Button1,GPIO_OUTPUT,1);
	gpio_init(Button2,GPIO_OUTPUT,0);
	gpio_init(Button3,GPIO_INPUT,0);
	gpio_pull(Button3,1);
	gpio_init(Button4,GPIO_INPUT,0);
	gpio_pull(Button4,1);
	if (gpio_get(Button3)==0)
	{
		whi=3;
	}
	if (gpio_get(Button4)==0)
	{
		whi=4;
	}
	if(whi!=0)Test_Lantern(whi);
}


void Test_Lantern(uint8_t whii)
{	
    
    uint8_t grb1[12]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t grb2[12]={0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t grb4[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00};
    uint8_t grb3[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF};
    uint8_t grb5[12]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t grb6[12]={0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t grb7[12]={0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF};
    uint8_t grb8[12]={0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};
    uint8_t grb9[12]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x0};
    uint8_t grb10[12]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};
    uint8_t grb11[12]={0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};
    
    uint8_t rwg1[12]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t rwg2[12]={0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00};
    uint8_t rwg3[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF};
    uint8_t rwg4[12]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t rwg5[12]={0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00};
    uint8_t rwg6[12]={0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};
    uint8_t rwg7[12]={0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};
    
    uint8_t black[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    WS_Init(COLORLIGHT);
    uint32_t cntt=0;
    switch(whii)
    {
    	case 1:
    		WS_SendOnePix(COLORLIGHT,black,4);
    		WS_SendOnePix(COLORLIGHT,grb1,4);
    		while(cntt<=1500000)cntt++;
    		WS_SendOnePix(COLORLIGHT,grb2,4);
    		while(cntt<=3000000)cntt++;
    		WS_SendOnePix(COLORLIGHT,grb3,4);
    		while(cntt<=4500000)cntt++;
    		WS_SendOnePix(COLORLIGHT,grb4,4);
    		while(cntt<=6000000)cntt++;
    		WS_SendOnePix(COLORLIGHT,grb5,4);
    		while(cntt<=7500000)cntt++;
    		WS_SendOnePix(COLORLIGHT,grb6,4);
    		while(cntt<=9000000)cntt++;
    		WS_SendOnePix(COLORLIGHT,grb7,4);
    		while(cntt<=10500000)cntt++;
    		WS_SendOnePix(COLORLIGHT,grb8,4);
    		while(cntt<=12000000)cntt++;
    		break;
    	case 2:
    			WS_SendOnePix(COLORLIGHT,black,4);
    			WS_SendOnePix(COLORLIGHT,grb1,4);
    		 	while(cntt<=1500000)cntt++;
    			WS_SendOnePix(COLORLIGHT,grb4,4);
    			while(cntt<=3000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,grb3,4);
    			while(cntt<=4500000)cntt++;
    			WS_SendOnePix(COLORLIGHT,grb2,4);
    			while(cntt<=6000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,grb5,4);
    			while(cntt<=7500000)cntt++;
    			WS_SendOnePix(COLORLIGHT,grb9,4);
    			while(cntt<=9000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,grb10,4);
    			while(cntt<=10500000)cntt++;
    			WS_SendOnePix(COLORLIGHT,grb11,4);
    			while(cntt<=12000000)cntt++;
    			break;
    			
    	case 3:
				WS_SendOnePix(COLORLIGHT,black,4);
    			WS_SendOnePix(COLORLIGHT,rwg1,4);
    			while(cntt<=2000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg2,4);
    			while(cntt<=4000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg3,4);
    			while(cntt<=6000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg4,4);
    			while(cntt<=8000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg5,4);
    			while(cntt<=10000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg6,4);
    			while(cntt<=12000000)cntt++;
    			break;
    	case 4:
    			WS_SendOnePix(COLORLIGHT,black,4);
    			WS_SendOnePix(COLORLIGHT,rwg3,4);
    			while(cntt<=2000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg2,4);
    			while(cntt<=4000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg1,4);
    			while(cntt<=6000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg3,4);
    			while(cntt<=8000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg7,4);
    			while(cntt<=10000000)cntt++;
    			WS_SendOnePix(COLORLIGHT,rwg6,4);
    			while(cntt<=12000000)cntt++;
    			break;
    			
    	default:
		        break;
    }
    
//    static char OutputCtl=0;
//    OutputCtl++;
//    if (OutputCtl>=4) OutputCtl=1;
//    WS_Init(COLORLIGHT);
//    //(1)�ʵƲ�������
//    switch (OutputCtl)
//    {
//    	case 1:
//        	WS_SendOnePix(COLORLIGHT,grbw,2);
//            printf("�����ʵ�\r\n\r\n");
//            break;
//        case 2:
//            WS_SendOnePix(COLORLIGHT,black,2);
//            printf("Ϩ��ʵ�\r\n\r\n");
//            break;
//        case 3:
//            WS_SendOnePix(COLORLIGHT,rwgb,2);
//            printf("�ı�ʵ���ɫ\r\n\r\n");
//            break;
//        default:
//	        break;
//    }
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



