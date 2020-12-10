//=====================================================================
//�ļ����ƣ�isr.c���жϴ������Դ�ļ���
//����ṩ��SD-ARM��sumcu.suda.edu.cn��
//�汾���£�20170801-20191020
//�����������ṩ�жϴ�������̿��
//=====================================================================
#include "includes.h"

//����ʹ�õ����ڲ�����
//isr.cʹ�õ��ڲ�����������
void SecAdd1(uint8_t *p);
//======================================================================
//�жϷ���������ƣ�UART_USER_Handler
//����������UART_USE�����յ�һ���ֽڴ���
//��    �ܣ��յ�һ���ֽڣ�ֱ�ӷ��ظ��ֽ�
//��    ע�����뱾����󣬿�ʹ��uart_get_re_int�������ٽ����жϱ�־�ж�
//          ��1-��UART�����жϣ�0-û��UART�����жϣ�
//======================================================================
uint8_t count=0;
uint8_t order[1024];
uint8_t nullnum,fflag,opt;
uint16_t secot,offset,len;
uint32_t addr;
void UART_User_Handler(void)
{
    uint8_t ch;
	uint8_t flag,mFlag;
    uint8_t flashRead[2048];
	DISABLE_INTERRUPTS;      //�����ж�
	
	
	ch=uart_re1(UART_User,&flag);
	if(flag==1)
	{
		if(ch==' ')nullnum--;
		else 
		{

			if(fflag==0)
			{
				opt=ch;
				if(ch=='w')nullnum=5;
				else if(ch=='r')nullnum=4;
				else nullnum=3;
				fflag=1;
			}
			else
			{
					
				switch(opt)
				{
				
					case 'w':
			//			printf("%c %d\n",opt,nullnum);
						if(nullnum==4)secot=secot*10+(ch-'0');
						if(nullnum==3)offset=offset*10+(ch-'0');
						if(nullnum==2)len=len*10+(ch-'0');
						if(nullnum==1)order[count++]=ch;
						break;
			
					case 'r':
			//			printf("%c %d\n",opt,nullnum);
					   if(nullnum==3)secot=secot*10+(ch-'0');
					   if(nullnum==2)offset=offset*10+(ch-'0');
					   if(nullnum==1)len=len*10+(ch-'0');
					   break;
				   
					case 'a':
			//			printf("%c %d\n",opt,nullnum);
						if(nullnum==2)addr=addr*10+(ch-'0');
						if(nullnum==1)len=len*10+(ch-'0');
						break;
					default:
					 	break;
				}
				
				
				
			    
			}
		//	printf("%c %d\n",opt,nullnum);

		}
	//	printf("%c %d\n",opt,nullnum);
		if(nullnum==0)
		{
			switch(opt)
			{
				case 'w':	
						mFlag=flash_erase(secot);
						mFlag=flash_write(secot, offset,len,order);	
						break;
				case 'r':	
				   		flash_read_logic(flashRead,secot,offset,len);
				   		uart_sendN(UART_User,len,flashRead);					   
					   break;
				case 'a':
						flash_read_physical(flashRead,addr,len);
						uart_sendN(UART_User,len,flashRead);	
						break;
			}
			addr=0;len=0;secot=offset=0;fflag=0;
			count=0;
		}
	}
//�ӿո�
//w 63 0 4 abcd 
//r 63 0 4  
//a 64512 4  
	
	
	ENABLE_INTERRUPTS;       //�����ж�
}

//=====================================================================
//�������ƣ�SYSTICK_USER_Handler��SysTick��ʱ���жϴ������
//����˵������
//�������أ���
//���ܸ�Ҫ����1��ÿ10ms�жϴ���������һ�Σ���2���ﵽһ��ʱ��������+1
//           ���򣬼��㡰ʱ���֡��롱
//�ر���ʾ����1��ʹ��ȫ�ֱ����ֽ�������gTime[3]���ֱ�洢��ʱ���֡��롱
//          ��2��ע�����о�̬������ʹ��
//=====================================================================
//void SYSTICK_USER_Handler()

void SysTick_Handler()
{
	static uint8_t SysTickCount = 0;
	SysTickCount++;    //Tick��Ԫ+1
	wdog_feed();      //���Ź���ι����
	if (SysTickCount >= 100)
	{
		SysTickCount = 0;
		SecAdd1(gTime);
	}
}



//===========================================================================
//�������ƣ�SecAdd1
//�������أ���
//����˵����*p:Ϊָ��һ��ʱ��������p[3]
//���ܸ�Ҫ���뵥Ԫ+1��������ʱ�ֵ�Ԫ��00:00:00-23:59:59)
//===========================================================================
void SecAdd1(uint8_t *p)
{
	*(p+2)+=1;         //��+1
	if(*(p+2)>=60)     //�����
	{
		*(p+2)=0;       //����
		*(p+1)+=1;      //��+1
		if(*(p+1)>=60)  //�����
		{
			*(p+1)=0;    //���
			*p+=1;       //ʱ+1
			if(*p>=24)   //ʱ���
			{
				*p=0;      //��ʱ
			}
		}
	}
}


/*
 ֪ʶҪ�أ�
 1.���ļ��е��жϴ��������õľ�������豸��װ�õľ��幹�����ڸ���оƬ
 ʱ��ֻ�豣֤�豸�Ĺ����ӿ�һ�£����ɱ�֤���ļ�������жϴ����������κ�
 ���ģ��Ӷ��ﵽоƬ�޹��Ե�Ҫ��
 */
