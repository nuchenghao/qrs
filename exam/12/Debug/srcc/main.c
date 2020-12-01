//======================================================================
//�ļ����ƣ�main.c��Ӧ�ù�����������
//����ṩ��SD-ARM��sumcu.suda.edu.cn��
//�汾���£�
//�����������������̵�<01_Doc>�ļ�����Readme.txt�ļ�
//======================================================================
#define GLOBLE_VAR
#include "includes.h"      //������ͷ�ļ�

//----------------------------------------------------------------------
//����ʹ�õ����ڲ�����
//main.cʹ�õ��ڲ�����������
float TempRegression(uint16_t AD);
//----------------------------------------------------------------------
//��������һ������¿�����Ϊ����Ӵ˿�ʼ���У�ʵ�������������̣��μ���壩
int main(void)
{
    //��1��======�������֣���ͷ��==========================================
    //��1.1������main����ʹ�õľֲ�����
    uint32_t mMainLoopCount;  //��ѭ����������
    uint8_t  mFlag;           //�Ƶ�״̬��־
    uint8_t i;


    
    //��1.2�������䡿�����ж�
    DISABLE_INTERRUPTS;
    wdog_feed();
    printf("����User��main...\n");
    
    //��1.3����������ʹ�õľֲ���������ֵ
    mMainLoopCount=0;    //��ѭ����������
    mFlag='R';           //�Ƶ�״̬��־

    wdog_start(3);	  //�������Ź�

    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);      
    gpio_init(PIN_MAG,GPIO_INPUT,1);     
    wdog_feed();
    printf("LCD��ʼ��...");
    LCD_Init();
    printf("�ɹ�\n");
    uart_init(UART_User,115200);

    wdog_feed();


    //��1.6��ʹ��ģ���ж�
    uart_enable_re_int(UART_User);
    //��1.7�������䡿�����ж�
    ENABLE_INTERRUPTS;
    
  
    
    printf("���«��ʾ��LCD��Ļ����...");
    LCD_aotu(2,2,238,318,0);
    LCD_aotu(4,40,236,80,1);
    LCD_ShowString(72,20,RED,GRAY,(char *)"AHL-MCU-KL36");
    LCD_ShowString(68,52,RED,GRAY,(char *)"Hardware-Test");
  	wdog_feed();
    LCD_ShowString(8,88,BLACK,GRAY,(char *)"The current state:");
    LCD_aotu(4,106,236,116,1);

    LCD_ShowString(8,120,BLACK,GRAY,(char *)"Tri-coloured light:");
    wdog_feed();                                         
    
    LCD_aotu(4,138,236,316,1);
    printf("���\n");

    for(;;)  
    {
		if(OoC==1){
			gpio_set(LIGHT_BLUE,LIGHT_ON); 
			LCD_ShowString(160,88,BLUE,GRAY,"OPEN ");
			LCD_ShowString(160,120,BLUE,GRAY,"BLUE");
			for (i=40;i>2;i=i-2)LCD_DrawCircle(120,220,i,BLUE);
		}
        if(OoC==0){
        	gpio_set(LIGHT_BLUE,LIGHT_OFF); 
        	LCD_ShowString(160,88,BLUE,GRAY,"CLOSE");
        	LCD_ShowString(160,120,BLUE,GRAY,"     ");
        	for (i=40;i>2;i=i-2)LCD_DrawCircle(120,220,i,GRAY);
        }
    }  
}   


//======����Ϊ���������õ��Ӻ���===========================================
float TempRegression(uint16_t tmpAD)
{
    float v1,v2,S,T;
    v1 = ((float)tmpAD*3300)/65535;   //ADֵ��Ϊ�������ѹ(mV)
    v2=3300 - v1;                    //��ѹ�������˵�ѹ(mV)
    S = v1/v2;                       //��ѹ��
    T = (1/(log(S)/3950.0 + (1/(273.15 + 25)))) - 273.15 + 0.5;
    return T;
}