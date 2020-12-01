//=====================================================================
//�ļ����ƣ�isr.c���жϴ������Դ�ļ���
//����ṩ��SD-ARM��sumcu.suda.edu.cn��
//�汾���£�20170801-20191020
//�����������ṩ�жϴ�������̿��
//=====================================================================
#include "includes.h"
#include <string.h>
//�ڲ���������
uint8_t CreateFrame(uint8_t Data,uint8_t * buffer);

//======================================================================
//�жϷ���������ƣ�UART_USER_Handler
//����������UART_USE�����յ�һ���ֽڴ���
//��    �ܣ��յ�һ���ֽڣ�ֱ�ӷ��ظ��ֽ�
//��    ע�����뱾����󣬿�ʹ��uart_get_re_int�������ٽ����жϱ�־�ж�
//          ��1-��UART�����жϣ�0-û��UART�����жϣ�
//======================================================================
void UART_User_Handler(void)
{

    uint8_t ch,flag,cnt;
    DISABLE_INTERRUPTS;               //�����ж�
    //-----------------------------------------------------------------------
    ch = uart_re1(UART_User, &flag);   //���ý���һ���ֽڵĺ�����������ж�λ
    //�����ڲ�����CreateFrame������֡
   // uart_send1(UART_User,ch);//�ط����յ����ֽ�
    printf("char:%c\n",ch);
   	if('0'<=ch&&ch<='3'){
   		if((ch == '0'))
		{
			whi=1;
		}	
		if(ch == '1')
		{
			whi=2;
		}
		if(ch == '2')
		{
			whi=3;
		}
		if(ch== '3')
		{
			whi=4;
		}
   	}
    
   	
	ENABLE_INTERRUPTS;       //�����ж�
	
	
}


//�ڲ����ú���

//===========================================================================
//�������ƣ�CreateFrame
//���ܸ�Ҫ���齨����֡��������֡���ݼ��뵽����֡��
//����˵����Data��         ����֡����
//          buffer:        ����֡����
//�������أ���֡״̬    0-��֡δ�ɹ���1-��֡�ɹ�
//��ע��ʮ����������֡��ʽ
//               ֡ͷ        + ���ݳ���         + ��Ч����    +  ֡β
//           FrameHead   +   len       + ��Ч����    + FrameTail
//===========================================================================
//open֡ͷ֡β
#define FrameHead1    (0x6F)       //֡ͷ     ASCII���Ӧo
#define FrameTail1    (0x6E)       //֡β     ASCII���Ӧn
//close֡ͷ֡β
#define FrameHead2    (0x63)       //֡ͷ     ASCII���Ӧc
#define FrameTail2    (0x65)       //֡β     ASCII���Ӧe
//blue֡ͷ֡β
#define FrameHead3    (0x62)       //֡ͷ     ASCII���Ӧb
#define FrameTail3    (0x65)       //֡β     ASCII���Ӧe
//green֡ͷ֡β
#define FrameHead4    (0x67)       //֡ͷ     ASCII���Ӧg
#define FrameTail4    (0x6E)       //֡β     ASCII���Ӧn
//red֡ͷ֡β
#define FrameHead5    (0x72)       //֡ͷ     ASCII���Ӧr
#define FrameTail5    (0x64)       //֡β     ASCII���Ӧd


//
static uint8_t frameLen=0;    //֡�ļ�����
uint8_t frameFlag;            //��֡״̬
uint8_t length;



//���֡ͷ��o��b��֡�ܳ���4(open/blue)
//���֡ͷ��c��g��֡�ܳ���5(close/green)
uint8_t CreateFrame(uint8_t Data,uint8_t * buffer)
{
    frameFlag=0;            //��֡״̬��ʼ��
    //���ݾ�̬����frameLen��֡
    switch(frameLen)
    {
        case 0:    //��һ������
        {
            if ((Data==FrameHead1) || (Data==FrameHead3))    //�յ�������֡ͷFrameHead1
                length=4;
            else if ((Data==FrameHead2) || (Data==FrameHead4))
            	length=5;
            else
            	length=3;
            buffer[0]=Data;
            frameLen++;
            frameFlag=0;        //��֡��ʼ
            break;
        }
        default:    //�������
        {
            //���ݳ��Ƚ������µ�����ֱ��֡βǰһλ
            if(frameLen>=1 && frameLen<=(length-2))
            {
                buffer[frameLen]=Data;
                frameLen++;
                break;
            }

            //����ĩβ������ִ��
            if(frameLen>=(length-1))
            {
                if ((Data==FrameTail1)||(Data==FrameTail2)||(Data==FrameTail3)||(Data==FrameTail4)||(Data==FrameTail5))    //����֡β
                {
                    buffer[frameLen]=Data;     //��֡β���뻺����
                    frameFlag=1;    //��֡�ɹ�
                }
                frameLen=0    ;     //������0��׼��������֡
                break;
            }
        }
    }     //switch_END
    return frameFlag;                 //������֡״̬
}
