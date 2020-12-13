//=====================================================================
//�ļ����ƣ�isr.c���жϴ������Դ�ļ���
//����ṩ��SD-ARM��sumcu.suda.edu.cn��
//�汾���£�20170801-20191020
//�����������ṩ�жϴ�������̿��
//=====================================================================
#include "includes.h"
//======================================================================
//�жϷ���������ƣ�UART_USER_Handler
//����������UART_USE�����յ�һ���ֽڴ���
//��    �ܣ��յ�һ���ֽڣ�ֱ�ӷ��ظ��ֽ�
//��    ע�����뱾����󣬿�ʹ��uart_get_re_int�������ٽ����жϱ�־�ж�
//          ��1-��UART�����жϣ�0-û��UART�����жϣ�
//======================================================================
void UART_User_Handler(void)
{
	uint8_t mString[30];
    uint8_t xyzData[6];         //x��y��z����ǣ���ռ�����ֽ�
    uint16_t xdata,ydata,zdata; //x�����
    uint8_t checkdata;          //ADLX345����֤����,��ȷ����Ϊ0xe5
    uint8_t temp[6];
    uint8_t ch;	uint8_t flag;
   	ch = uart_re1(UART_User, &flag);
    if(flag)   //������
	{
	   if(ch == 'q')
	   {
	   			printf("ask\n");
				adlx345_init(i2cAcceleration,0x0B,0x08,0x08,0x80,0x00,0x00,0x05);//��ʼ��ADLX345(J2�˿�) 
				adlx345_read1(0x00,&checkdata);    //��ȡadxl345У������
				adlx345_init(0,0x0B,0x08,0x08,0x80,0x00,0x00,0x05);//��ʼ��ADLX345(J2�˿�)
				adlx345_read1(0x00,&checkdata);    //��ȡadxl345У������
				main_Dly_ms(5);
				adlx345_readN(0x32,xyzData,6);		   //����Ǵ�������ֵ
				xdata = (xyzData[1]<<8)+xyzData[0];    //x�������
				ydata = (xyzData[3]<<8)+xyzData[2];    //y�������
				zdata = (xyzData[5]<<8)+xyzData[4];    //z�������
				temp[0] = xyzData[1] ;
          		temp[1] = xyzData[0];
          		temp[2] =xyzData[3];
				temp[3] =xyzData[2];
				temp[4] =xyzData[5];
				temp[5] =xyzData[4];
				
          		printf("%d %d %d %d %d %d\n",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5]);
         		uart_send_string(UART_User,temp);
	   }
	}
}


/*
 ֪ʶҪ�أ�
 1.���ļ��е��жϴ��������õľ�������豸��װ�õľ��幹�����ڸ���оƬ
 ʱ��ֻ�豣֤�豸�Ĺ����ӿ�һ�£����ɱ�֤���ļ�������жϴ����������κ�
 ���ģ��Ӷ��ﵽоƬ�޹��Ե�Ҫ��
 */
