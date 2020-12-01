//=====================================================================
//文件名称：adc.h
//功能概要：ADC底层驱动构件头文件
//制作单位：苏州大学嵌入式系统与物联网研究所(sumcu.suda.edu.cn)
//版    本：  2019-05-09  V2.0
//适用芯片：KL25、KL26、KL36
//=====================================================================

#ifndef _ADC_H           //防止重复定义（ 开头）
#define _ADC_H

#include "mcu.h"
#include "string.h"

//用于定义硬件滤波次数
#define SAMPLE4   0
#define SAMPLE8   1
#define SAMPLE16  2
#define SAMPLE32  3

//通道选择
#define MUXSEL_A     0    //选择端口的A通道
#define MUXSEL_B     1    //选择端口的B通道

//============================================================================
//功能概要：初始化一个AD通道组
//参数说明：A_SENSOR_No：可用模拟量传感器通道，可用参数可参见gec.h文件
//          accurary：采样精度，差分可选9-13-11-16；
//                    单端可选8-12-10-16，越高精度越高
//============================================================================
void adc_init(uint16_t A_SENSOR_No,uint8_t accurary);

//============================================================================
//功能概要：进行一个通道的一次A/D转换
//参数说明：A_SENSOR_No：可用模拟量传感器通道，可用参数可参见gec.h文件
//============================================================================
uint16_t adc_read(uint16_t A_SENSOR_No);

//============================================================================
//功能概要：将读到的mcu温度AD值转换为实际温度
//参数说明：mcu_temp_AD：通过adc_read函数得到的AD值
//函数返回：实际温度值
//============================================================================
float TempTrans(uint16_t mcu_temp_AD);
float TempRegression(uint16_t tmpAD);
#endif

//===========================================================================
//声明：
//（1）我们开发的源代码，在本中心提供的硬件系统测试通过，真诚奉献给社会，不足之处，
//    欢迎指正。
//（2）对于使用非本中心硬件系统的用户，移植代码时，请仔细根据自己的硬件匹配。
//
//苏州大学嵌入式社区，http://sumcu.suda.edu.cn；0512-65214835

#define ADC_PIN17  (26|MUXSEL_A<<8)   //芯片自带温度传感器 引脚未引出
#define ADC_PIN4  (2|MUXSEL_A<<8)     //所在引脚：GEC_12（PTE_NUM|18），ADC0_DP2/SE2