#ifndef _IIC_H
#define _IIC_H
#include <stm32f3xx.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <delay.h>

#define SCL_Port GPIOB
#define SDA_Port GPIOB
#define SCL_Pin 8
#define SDA_Pin 9

bool IIC_Read_SDA(void);
void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
uint8_t IIC_WaitAck(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_WriteByte(uint8_t);
uint8_t IIC_ReadByte(uint8_t ack);
void IIC_Scan(void);
uint8_t Single_Byte_Read(uint8_t device_add, uint8_t register_add);
void Single_Byte_Write(uint8_t device_add, uint8_t register_add, uint8_t data);

#endif