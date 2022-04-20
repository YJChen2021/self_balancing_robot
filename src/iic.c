#include "iic.h"


#define SDA_IN  {SDA_Port->MODER &= ~(3 << (SDA_Pin * 2));SDA_Port->MODER |= 0<< SDA_Pin * 2;}
#define SDA_OUT {SDA_Port->MODER &= ~(3 << (SDA_Pin * 2));SDA_Port->MODER |= 1<< SDA_Pin * 2;}
#define IIC_SCL_1 {SCL_Port->ODR |= 1 << SCL_Pin;}
#define IIC_SCL_0 {SCL_Port->ODR &= ~(1 << SCL_Pin);}
#define IIC_SDA_1 {SDA_Port->ODR |= 1 << SDA_Pin;}
#define IIC_SDA_0 {SDA_Port->ODR &= ~(1 << SDA_Pin);}

/*
Input:High,bit=1
Input:Low ,bit=0
*/
bool IIC_Read_SDA(void){
    SDA_IN;
    return SDA_Port->IDR & (uint16_t)(1 << SDA_Pin);
}

void IIC_Init(void){
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    SCL_Port->MODER |= 0b01 << (2 * SCL_Pin);
    SDA_Port->MODER |= 0b01 << (2 * SDA_Pin);
    SCL_Port->OTYPER |= 1 << SCL_Pin;
    SDA_Port->OTYPER |= 1 << SDA_Pin;
    SCL_Port->OSPEEDR |= 0b11 << (2 * SCL_Pin);
    SDA_Port->OSPEEDR |= 0b11 << (2 * SDA_Pin);
    SCL_Port->PUPDR |= 0b01 << (2 * SCL_Pin);
    SDA_Port->PUPDR |= 0b01 << (2 * SDA_Pin);
    IIC_Stop();
}

void IIC_Start(void){
    SDA_OUT;
    IIC_SDA_1;
    IIC_SCL_1;
    Delay_Us(4);
    IIC_SDA_0;
    Delay_Us(4);
    IIC_SCL_0;
}
void IIC_Stop(void){
    SDA_OUT;
	IIC_SCL_0;
	IIC_SDA_0;
 	Delay_Us(4);
	IIC_SDA_1;
	Delay_Us(4);
    IIC_SCL_1; 
}

uint8_t IIC_WaitAck(void){
    uint8_t errCount = 0;
    uint8_t ack = 0;
    SDA_IN;
    IIC_SDA_1;
    Delay_Us(4);
    IIC_SCL_1;
    Delay_Us(4);     

    while(IIC_Read_SDA()){
        errCount++;
        if(errCount > 250){
            ack = 1;
            break;
        }
    }
    IIC_SCL_0;
     
    return ack;
}

void IIC_Ack(void){
    IIC_SCL_0;
	SDA_OUT;
	IIC_SDA_0;
	Delay_Us(4);
	IIC_SCL_1;
	Delay_Us(4);
	IIC_SCL_0;
}

void IIC_NAck(void){
	IIC_SCL_0;
	SDA_OUT;
	IIC_SDA_1;
	Delay_Us(4);
	IIC_SCL_1;
	Delay_Us(4);
	IIC_SCL_0;
}        

void IIC_WriteByte(uint8_t txd){                        
    uint8_t i;
    SDA_OUT;
    IIC_SCL_0;
    for(i = 0; i < 8; i++){
        if(txd & 0x80){
            IIC_SDA_1;
        }
        else{
            IIC_SDA_0;
        }
        txd <<= 1;
        Delay_Us(4);
        IIC_SCL_1;
        Delay_Us(4);
        IIC_SCL_0;
        Delay_Us(4);
    }
}        

uint8_t IIC_ReadByte(uint8_t ack){
    uint8_t i, rcv = 0;
    for(i = 0; i < 8; i++){
        rcv <<= 1;
        IIC_SCL_1;
        //IIC_SCL_0;
        Delay_Us(4); 
        if(IIC_Read_SDA()){
            rcv++;   
        }
        IIC_SCL_0; 
        Delay_Us(4);
    }
    ack ? IIC_Ack() : IIC_NAck();
    
    return rcv;
}

void IIC_Scan(void){
    for(uint8_t i = 0; i < 128; i++){
        IIC_Start();
        IIC_WriteByte(i);
        uint8_t ack = IIC_WaitAck();
        IIC_Stop();
        if(ack){
            ;
        }
        else{
            printf("0x%x\n", i >> 1);
            printf("succeed\n");
        }
        Delay_Us(5);
    }
}

uint8_t Single_Byte_Read(uint8_t device_add, uint8_t register_add){

    #ifdef DEBUG
		IIC_Start();
    	IIC_WriteByte(device_add << 1 | 0x00);
    	uint8_t ack1 = IIC_WaitAck();
		IIC_WriteByte(register_add);
		uint8_t ack2 = IIC_WaitAck();
		IIC_Start();
		device_add = (device_add << 1 | 0x01);
		IIC_WriteByte(device_add);
		uint8_t ack3 = IIC_WaitAck();
		uint8_t data = IIC_ReadByte(0);
		IIC_Stop();
		printf("Read-");
		printf("ack1 = %d", ack1);
		printf(", ");
		printf("ack2 = %d", ack2);
		printf(", ");
		printf("ack3 = %d", ack3);
		printf(", ");
		printf("data = %d\n", data);
	#else
		IIC_Start();
    	IIC_WriteByte(device_add << 1 | 0x00);//0 for write
    	IIC_WaitAck();
		IIC_WriteByte(register_add);
		IIC_WaitAck();
		IIC_Start();
		device_add = (device_add << 1 | 0x01);//1 for read
		IIC_WriteByte(device_add);
		IIC_WaitAck();
		uint8_t data = IIC_ReadByte(0);
		IIC_Stop();
    #endif
	return data;
}

void Single_Byte_Write(uint8_t device_add, uint8_t register_add, uint8_t data){
    #ifdef DEBUG
		IIC_Start();
		IIC_WriteByte(device_add << 1 | 0x00);
    	uint8_t ack1 = IIC_WaitAck();
    	IIC_WriteByte(register_add);
		uint8_t ack2 = IIC_WaitAck();
    	IIC_WriteByte(data);
		uint8_t ack3 = IIC_WaitAck();
    	IIC_Stop();
		printf("Write-");
		printf("ack1 = %d", ack1);
		printf(", ");
		printf("ack2 = %d", ack2);
		printf(", ");
		printf("ack3 = %d", ack3);
		printf(", ");
    #else
		IIC_Start();
		IIC_WriteByte(device_add << 1 | 0x00);
    	IIC_WaitAck();
    	IIC_WriteByte(register_add);
		IIC_WaitAck();
    	IIC_WriteByte(data);
		IIC_WaitAck();
    	IIC_Stop();
	#endif
}
