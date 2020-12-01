//====================================================================
//�ļ����ƣ�main.c��Ӧ�ù�����������
//����ṩ��SD-Arm��sumcu.suda.edu.cn��
//�汾���£�20170801-20200502
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
    uint32_t mMainLoopCount;  //��ѭ��ʹ�õļ�¼��ѭ����������
    uint8_t  mFlag;            //��ѭ��ʹ�õ���ʱ����
    
    //��1.2�������䡿�����ж�
    DISABLE_INTERRUPTS;

    
    //��1.3����������ʹ�õľֲ���������ֵ
    mMainLoopCount = 0;     //��ѭ��ʹ�õļ�¼��ѭ����������
    mFlag='A';              //��ѭ��ʹ�õ���ʱ����������״̬��־
    
    //��1.4����ȫ�ֱ�������ֵ
    

    gpio_init(LIGHT_BLUE,1,LIGHT_OFF);    //��ʼ������
    gpio_init(LIGHT_RED,1,LIGHT_OFF);
    gpio_init(LIGHT_GREEN,1,LIGHT_OFF);
    gpio_init(PTC_NUM|(1),0,1);
    gpio_init(PTC_NUM|(0),0,1);

	
    //��1.7�������䡿�����ж�
    ENABLE_INTERRUPTS;
    
    printf("------------------------------------------------------\n");   
    printf("���«��ʾ���������������С������   \n");
    printf("��һ���ù���������������ɫ��������ܣ�\n");
    printf("���ǽ���Ӧ�ñ�̵ĵ�һ���������ڴ˻����ϣ�\n");
    printf("���պ�«��ư���ؼ���ѧϰʵ����\n");
    printf("���磺��Ϊ�̵ƣ�������˸Ƶ�ʵȡ�\n");
    printf("------------------------------------------------------\n"); 
    
    //for(;;) {  }     //�ڴ˴�׮�������ɫ���������Ϊ���������ˣ�
    
    //��1��======�������֣���β��==========================================
    
    //��2��======��ѭ�����֣���ͷ��=========================================
    int cnt=0;
    for(;;)     //for(;;)����ͷ��
    {
        
        if(gpio_get(PTC_NUM|(0))==1 && gpio_get(PTC_NUM|(1))==1){
        	cnt=0;
         	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_ON);    //���õơ����� ����
        	while(cnt<=5000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_ON); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //���õơ����� �̵�
        	while(cnt<=10000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_ON); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //���õơ����� ���
        	while(cnt<=15000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //���õơ����� ���
        	while(cnt<=35000009)cnt++;
        }
        if(gpio_get(PTC_NUM|(1))==0 && gpio_get(PTC_NUM|(0))==1){//01 
        	cnt=0;
         	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_ON);    //���õơ����� ����
        	while(cnt<=5000009)cnt++;
//        	gpio_set(LIGHT_RED,LIGHT_OFF); 
//        	gpio_set(LIGHT_GREEN,LIGHT_ON); 
//        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //���õơ����� �̵�
//        	while(cnt<=10000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_ON); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //���õơ����� ���
        	while(cnt<=10000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //���õơ����� ���
        	while(cnt<=30000009)cnt++;
        }
        if(gpio_get(PTC_NUM|(1))==1 && gpio_get(PTC_NUM|(0))==0){//10
        	        	cnt=0;
//         	gpio_set(LIGHT_RED,LIGHT_OFF); 
//        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
//        	gpio_set(LIGHT_BLUE,LIGHT_ON);    //���õơ����� ����
//        	while(cnt<=5000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_ON); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //���õơ����� �̵�
        	while(cnt<=5000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_ON); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //���õơ����� ���
        	while(cnt<=10000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //���õơ����� ���
        	while(cnt<=30000009)cnt++;
        }
        if(gpio_get(PTC_NUM|(1))==0 && gpio_get(PTC_NUM|(0))==0){//00
        	cnt=0;
         	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_ON);    //���õơ����� ����
        	while(cnt<=5000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_ON); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //���õơ����� �̵�
        	while(cnt<=10000009)cnt++;
//        	gpio_set(LIGHT_RED,LIGHT_ON); 
//        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
//        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //���õơ����� ���
//        	while(cnt<=15000009)cnt++;
        	gpio_set(LIGHT_RED,LIGHT_OFF); 
        	gpio_set(LIGHT_GREEN,LIGHT_OFF); 
        	gpio_set(LIGHT_BLUE,LIGHT_OFF);   //���õơ����� ���
        	while(cnt<=30000009)cnt++;
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



