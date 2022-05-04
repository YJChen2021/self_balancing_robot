#include <FXAS21002C.h>
//https://www.nxp.com/docs/en/data-sheet/FXAS21002.pdf

void FXAS21002C_Init(void){
    //Page 46 of datasheet
    //IIC_Init();
    Single_Byte_Write(Gyro, FXAS21002C_REGISTER_CTRL_REG1, 0x00);    //Standby
    Single_Byte_Write(Gyro, FXAS21002C_REGISTER_CTRL_REG1, (1 << 6));//Reset
    Single_Byte_Write(Gyro, FXAS21002C_REGISTER_CTRL_REG0, 0x03);    //Set sensitivity = +/- 250
    Single_Byte_Write(Gyro, FXAS21002C_REGISTER_CTRL_REG1, 0x06);    //Active + output data rate = 400
    // write 0000 0110 = 0x06 to gyro control register 1
    // [7]: -
    // [6]: RST=0 to disable the software reset
    // [5]: ST=0 to disable the Self-Test
    // [4-2]: DR=001 for 400Hz data rate
    // [1]: Active=1 for active mode
    // [0]: Ready/Standby has no work when Active=1
	#if DEBUG
		Single_Byte_Read(Gyro, FXAS21002C_REGISTER_CTRL_REG1);
	#endif
}

double get_Gyro_X(void){
    double data = (int16_t)((Single_Byte_Read(Gyro, FXAS21002C_REGISTER_OUT_X_MSB) << 8) | Single_Byte_Read(Gyro, FXAS21002C_REGISTER_OUT_X_LSB));
    return data * FXAS21002C_SENSITIVITY * SENSORS_DPS_TO_RADS; 
}

double get_Gyro_Y(void){
    double data = (int16_t)((Single_Byte_Read(Gyro, FXAS21002C_REGISTER_OUT_Y_MSB) << 8) | Single_Byte_Read(Gyro, FXAS21002C_REGISTER_OUT_Y_LSB));
    return data * FXAS21002C_SENSITIVITY * SENSORS_DPS_TO_RADS;
}


double get_Gyro_Z(void){
    double data = (int16_t)((Single_Byte_Read(Gyro, FXAS21002C_REGISTER_OUT_Z_MSB) << 8) | Single_Byte_Read(Gyro, FXAS21002C_REGISTER_OUT_Z_LSB));
    return data * FXAS21002C_SENSITIVITY * SENSORS_DPS_TO_RADS;
}