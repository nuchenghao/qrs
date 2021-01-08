//====================================================================
//�ļ����ƣ�main.c��Ӧ�ù�����������
//����ṩ��SD-Arm��sumcu.suda.edu.cn��
//�汾���£�2017.08, 2020.05
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
    //��1��======�������֣���ͷ��==========================================
    //��1.1������main����ʹ�õľֲ�����
    uint32_t mTime;           //��ѭ��ʹ�õ���ʱʱ�����
    uint8_t  mFlag;           //��ѭ��ʹ�õ���ʱ����
    uint8_t  mSec;	         //�ǵ�ǰ���ֵ
    //uint8_t data[20];                 //���ڱ���SPIģ��䴫�ݵ���Ϣ
    //��1.2�������䡿�����ж�
    DISABLE_INTERRUPTS;
    wdog_stop();
    
    //��1.3����������ʹ�õľֲ���������ֵ
    mFlag='A';              //��ѭ��ʹ�õ���ʱ����������״̬��־
    //strcpy(data,"TEST I2C");   //��ʼ��data�е����ݣ���Ϊ��������
    //��1.4����ȫ�ֱ�������ֵ
   	//"ʱ����"�����ʼ��(00:00:00)
   	gTime[0] = 0;       //ʱ
   	gTime[1] = 0;	  	//��
   	gTime[2] = 0;	  	//��
   	mSec = gTime[2];	//��ס��ǰ���ֵ
    //��1.5���û�����ģ���ʼ��
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);    //��ʼ������
    uart_init(UART_User, 115200);
    uart_init(UART_UE, 115200);
    systick_init(10);      //����systickΪ10ms�ж�

    //I2C_SEND��ʼ����I2C_SEND:ģ��� 1:���� 0x74:��ַ  100:������(��λ:KBps)
    i2c_init(I2C_SEND,1,0x74,100);
    //I2C_RECEIVE��ʼ����I2C_RECEIVE:ģ��� 0:�ӻ� 0x73:��ַ  100:������(��λ:KBps)
    i2c_init(I2C_RECEIVE,0,0x73,100);

    i2c_slaveAddress=(0x73<<1)&0xfe;         //��ȡ�ӻ���ַ�������ʼ�ź�Ҳ���ط�������XSX

    //��1.6��ʹ��ģ���ж�
    uart_enable_re_int(UART_User);
    uart_enable_re_int(UART_UE);
    i2c_enable_re_int(I2C_RECEIVE);//ʹ��ģ���ж�
    //��1.7�������䡿�����ж�
    ENABLE_INTERRUPTS;

    printf("------------------------------------------------------\n"); 
    printf("���«��ʾ��I2CͨѶʵ�� \n");
    printf("  �� ������˸\n");
   	printf("  �� ÿ1s��I2C����ģ��I2C0��I2C�ӻ�ģ��I2C1����һ�����ݡ� \n");
   	printf("  �� ����I2C1�����жϴ�������󣬴ӻ����յ�������ͨ��UART_USER���ڷ��͸���λ��\n");
    printf("    ���˳������棬ת�롰���ߡ��������ڹ��ߡ���֤ ��������115200�� \n");
    printf("------------------------------------------------------\n"); 


    //for(;;) {  }     //�ڴ˴�׮��������ɫ���������Ϊ���������ˣ�
    
    //��1��======�������֣���β��==========================================
    
    //��2��======��ѭ�����֣���ͷ��=========================================
    for(;;)     //for(;;)����ͷ��
    {
   		if (gTime[2] == mSec)   continue;
   		mSec=gTime[2];
        //������1�뵽�Ĵ������Ƶ�״̬�л���������ÿ����һ�Σ�
        //�л���״̬
        if (mFlag=='A')   //����״̬��־Ϊ'A'
        {
            gpio_set(LIGHT_BLUE,LIGHT_ON);   //���õơ�����
            printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
            printf("���ƣ���\n");             //ͨ�����Դ�������Ƶ�״̬
            mFlag='L';                        //�ı�״̬��־
        }
        else                   //����,����״̬��־��Ϊ'A'    
        {
            gpio_set(LIGHT_BLUE,LIGHT_OFF);  //���õơ�����  
            printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
            printf("���ƣ���\n");             //ͨ�����Դ�������Ƶ�״̬
            mFlag='A';                        //�ı�״̬��־
        }	
        //I2C���ݷ���
        if(flag_User){
        
        i2c_writeN(I2C_SEND, 0x73, data1,len);         //IIC_0��������
        flag_User=0;flag_UE=0;
        }
        if(flag_UE){
        i2c_writeN(I2C_SEND, 0x73, data2,len);         //IIC_0��������
        uart_sendN(UART_UE,8,g_uart_recvBuf);
        flag_UE=0;flag_User=0;
        }
        
    }     //for(;;)��β
    //��2��======��ѭ�����֣���β��========================================
}

//======����Ϊ���������õ��Ӻ�����Ŵ�=====================================

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


