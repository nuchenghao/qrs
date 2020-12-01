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
    float temperature;
    uint16_t light;
    uint16_t mcu_temp_AD;
    float mcu_temp;
    uint16_t bat_AD;
    float bat_V;
    uint8_t mag;
    uint16_t AD_CAL1;
	uint16_t AD_CAL2;
    
    //��1.2�������䡿�����ж�
    DISABLE_INTERRUPTS;
    wdog_feed();
    printf("����User��main...\n");
    
    //��1.3����������ʹ�õľֲ���������ֵ
    mMainLoopCount=0;    //��ѭ����������
    mFlag='R';           //�Ƶ�״̬��־
    //��1.4����ȫ�ֱ�������ֵ
    
    //��1.5���û�����ģ���ʼ��
    wdog_start(3);	  //�������Ź�

    gpio_init(PIN_MAG,GPIO_INPUT,1);     
    wdog_feed();
    printf("LCD��ʼ��...");
    LCD_Init();
    printf("�ɹ�\n");
    uart_init(UART_User,115200);

    adc_init(AD_TEMP,0);
    adc_init(AD_MCU_TEMP,0);
    wdog_feed();
//    adc_init(AD_BAT,0);

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
    LCD_ShowString(8,88,BLACK,GRAY,(char *)"MCU_Tmp:");
    wdog_feed();                                         

	uint8_t temp[3];

    for(;;)
    {
    	wdog_feed();
        mMainLoopCount++;
        if (mMainLoopCount<=0x1fffff)  continue;
        mMainLoopCount=0; 
        wdog_feed();
		
		mcu_temp_AD = adc_read(AD_MCU_TEMP);
        mcu_temp=TempTrans(mcu_temp_AD);
        LCD_ShowString(84,88,BLACK,GRAY,"     ");
        LCD_ShowString(84,88,GREEN,GRAY,(char *)NumToStr_float(mcu_temp,2,temp));
        wdog_feed();


			
          uint8_t friction=(((int)(mcu_temp*10.0))%10)*10+((int)(mcu_temp*100.0))%10;
          temp[0] = (char)mcu_temp;
          temp[1] = (char)friction;//MCU���¶�
          temp[2] = '\0';
         uart_send_string(UART_User,temp);

        
    }  
}  

float TempRegression(uint16_t tmpAD)
{
    float v1,v2,S,T;
    v1 = ((float)tmpAD*3300)/65535;
    v2=3300 - v1;                    
    S = v1/v2;                     
    T = (1/(log(S)/3950.0 + (1/(273.15 + 25)))) - 273.15 + 0.5;
    return T;
}