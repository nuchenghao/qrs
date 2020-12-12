//======================================================================
//文件名称：adlx345.h
//功能概要：i2c传感器构件头文件
//制作单位：苏大arm技术中心(sumcu.suda.edu.cn)
//更新记录：20190309 ZYL
//======================================================================


#ifndef _ADLX345_H     //防止重复定义（_ADLX345_H  开头)
#define _ADLX345_H


#include "gec.h"      //包含gpio头文件
#include "i2c.h"
#include "mcu.h"    //包含公共要素头文件

//宏定义
#define   slaveaddress    0x53    //该数据取决于地址线选择，选择的地址为0x53

//====================接口函数声明=======================================
//======================================================================
//函数名称：adlx345_init
//函数参数：module:I2C模块号；range:测量范围；rate:测量速率；power:电源模式
//         xOffset:X轴偏移量；yOffset:Y轴偏移量；zOffset:Z轴偏移量；
//函数返回：无
//功能概要：ADLX345加速度传感器初始化。
//======================================================================
void adlx345_init(uint8_t module,uint8_t range,uint8_t rate,uint8_t power,uint8_t dataready,
		uint8_t xOffset,uint8_t yOffset,uint8_t zOffset);

//======================================================================
//函数名称：adlx345_read1
//函数参数：command:读取地址（命令）；data:存放读取的数据
//函数返回：无
//功能概要：ADLX345加速度传感器读取1字节。
//======================================================================
void adlx345_read1(uint8_t command,uint8_t *data);

//======================================================================
//函数名称：adlx345_readN
//函数参数：command:读取地址（命令）；data:存放读取的数据
//函数返回：无
//功能概要：ADLX345加速度传感器读取N字节。。
//======================================================================
void adlx345_readN(uint8_t command,uint8_t *data,uint8_t num);

void adlx345_Dly_ms(uint32_t ms);

#endif    //防止重复定义（_ADLX345_H  结尾)
