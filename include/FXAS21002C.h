#ifndef _FXAS21002C_H
#define _FXAS21002C_H
#include <iic.h>
//https://www.nxp.com/docs/en/data-sheet/FXAS21002.pdf

#define Gyro 0x21 //Device Address

/** Gyroscope sensitivity at 250dps */
#define FXAS21002C_SENSITIVITY_250DPS (0.0078125F)
/** Gyroscope sensitivity at 500dps */
#define FXAS21002C_SENSITIVITY_500DPS (0.015625F)
/** Gyroscope sensitivity at 1000dps */
#define FXAS21002C_SENSITIVITY_1000DPS (0.03125F)
/** Gyroscope sensitivity at 2000dps */
#define FXAS21002C_SENSITIVITY_2000DPS (0.0625F)

/**********************************/
#define FXAS21002C_SENSITIVITY  FXAS21002C_SENSITIVITY_250DPS
#define GRAVITY_EARTH (9.80665F) /**< Earth's gravity in m/s^2 */
#define SENSORS_DPS_TO_RADS (0.017453293F)
/**********************************/


#define FXAS21002C_REGISTER_STATUS    0x00    /**< 0x00 */
#define FXAS21002C_REGISTER_OUT_X_MSB 0x01    /**< 0x01 */
#define FXAS21002C_REGISTER_OUT_X_LSB 0x02    /**< 0x02 */
#define FXAS21002C_REGISTER_OUT_Y_MSB 0x03    /**< 0x03 */
#define FXAS21002C_REGISTER_OUT_Y_LSB 0x04    /**< 0x04 */
#define FXAS21002C_REGISTER_OUT_Z_MSB 0x05    /**< 0x05 */
#define FXAS21002C_REGISTER_OUT_Z_LSB 0x06    /**< 0x06 */
#define FXAS21002C_REGISTER_WHO_AM_I  0x0C    /**< 0x0C (default value = 0b11010111, read only) */
#define FXAS21002C_REGISTER_CTRL_REG0 0x0D    /**< 0x0D (default value = 0b00000000, read/write) */
#define FXAS21002C_REGISTER_CTRL_REG1 0x13    /**< 0x13 (default value = 0b00000000, read/write) */
#define FXAS21002C_REGISTER_CTRL_REG2 0x14    /**< 0x14 (default value = 0b00000000, read/write) */

void FXAS21002C_Init(void);

/**return angular rate in [rad/s]*/
double get_Gyro_X(void);
double get_Gyro_Y(void);
double get_Gyro_Z(void);
#endif
