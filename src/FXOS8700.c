#include <FXOS8700.h>
//https://www.nxp.com/docs/en/data-sheet/FXAS21002.pdf


void FXOS8700_Init(void){
    IIC_Init();
	//Page 42 of datasheet
    Single_Byte_Write(Accelerometer, FXOS8700_REGISTER_CTRL_REG1, 0x00);//Reset
	Single_Byte_Write(Accelerometer, FXOS8700_REGISTER_CTRL_REG1, 0x0D);//Configuration and Enable
	// write 0000 1101 = 0x0D to accelerometer control register 1
	// [7-6]: aslp_rate=00
	// [5-3]: dr=001 for 400Hz data rate (only accelerometer mode - [1:0] in M_CTRL_REG1)
	// [2]: lnoise=1 for low noise mode
	// [1]: f_read=0 for normal 16 bit reads
	// [0]: active=1 to take the part out of standby and enable
	#if DEBUG
		Single_Byte_Read(Accelerometer, FXOS8700_REGISTER_CTRL_REG1);
	#endif
}
double get_Accelerometer_X(void){
    //00000000xxxxxxxx-MSB, 00000000xxxxxx00-LSB;MSB<<8=xxxxxxxx00000000, MSB|LSB=xxxxxxxxxxxxxx00, MSB|LSB >>2 = data
    double data = (int16_t)((Single_Byte_Read(Accelerometer, FXOS8700_REGISTER_OUT_X_MSB) << 8) | Single_Byte_Read(Accelerometer, FXOS8700_REGISTER_OUT_X_LSB)) >> 2;
    return data * ACCEL_MG_LSB * GRAVITY_EARTH; // +/-2, +/-4, +/-8
}

double get_Accelerometer_Y(void){
    //00000000xxxxxxxx-MSB, 00000000xxxxxx00-LSB;MSB<<8=xxxxxxxx00000000, MSB|LSB=xxxxxxxxxxxxxx00, MSB|LSB >>2 = data
    double data = (int16_t)((Single_Byte_Read(Accelerometer, FXOS8700_REGISTER_OUT_Y_MSB) << 8) | Single_Byte_Read(Accelerometer, FXOS8700_REGISTER_OUT_Y_LSB)) >> 2;
    return data * ACCEL_MG_LSB * GRAVITY_EARTH; // +/-2, +/-4, +/-8
}

double get_Accelerometer_Z(void){
	//00000000xxxxxxxx-MSB, 00000000xxxxxx00-LSB;MSB<<8=xxxxxxxx00000000, MSB|LSB=xxxxxxxxxxxxxx00, MSB|LSB >>2 = data    
    double data = (int16_t)((Single_Byte_Read(Accelerometer, FXOS8700_REGISTER_OUT_Z_MSB) << 8) | Single_Byte_Read(Accelerometer, FXOS8700_REGISTER_OUT_Z_LSB)) >> 2;
    return data * ACCEL_MG_LSB * GRAVITY_EARTH; // +/-2, +/-4, +/-8
}