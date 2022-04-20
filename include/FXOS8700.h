#ifndef _FXOS8700_H
#define _FXOS8700_H
//https://www.nxp.com/docs/en/data-sheet/FXOS8700CQ.pdf
#include <iic.h>
#define Accelerometer 0x1f

/** Macro for mg per LSB at +/- 2g sensitivity (1 LSB = 0.000244mg) */
#define ACCEL_MG_LSB_2G (0.000244F)
/** Macro for mg per LSB at +/- 4g sensitivity (1 LSB = 0.000488mg) */
#define ACCEL_MG_LSB_4G (0.000488F)
/** Macro for mg per LSB at +/- 8g sensitivity (1 LSB = 0.000976mg) */
#define ACCEL_MG_LSB_8G (0.000976F)
/** Macro for micro tesla (uT) per LSB (1 LSB = 0.1uT) */
#define MAG_UT_LSB (0.1F)

/***********************************/
#define ACCEL_MG_LSB ACCEL_MG_LSB_2G
#define GRAVITY_EARTH (9.80665F)        /**< Earth's gravity in m/s^2 */
/**********************************/


#define FXOS8700_REGISTER_STATUS        0x00/**< 0x00 */
#define FXOS8700_REGISTER_OUT_X_MSB     0x01/**< 0x01 */
#define FXOS8700_REGISTER_OUT_X_LSB     0x02/**< 0x02 */
#define FXOS8700_REGISTER_OUT_Y_MSB     0x03/**< 0x03 */
#define FXOS8700_REGISTER_OUT_Y_LSB     0x04/**< 0x04 */
#define FXOS8700_REGISTER_OUT_Z_MSB     0x05/**< 0x05 */
#define FXOS8700_REGISTER_OUT_Z_LSB     0x06/**< 0x06 */
#define FXOS8700_REGISTER_WHO_AM_I      0x0D/**< 0x0D (default value = 0b11000111, read only) */
#define FXOS8700_REGISTER_XYZ_DATA_CFG  0x0E/**< 0x0E */
#define FXOS8700_REGISTER_CTRL_REG1     0x2A/**< 0x2A (default value = 0b00000000, read/write) */
#define FXOS8700_REGISTER_CTRL_REG2     0x2B/**< 0x2B (default value = 0b00000000, read/write) */
#define FXOS8700_REGISTER_CTRL_REG3     0x2C/**< 0x2C (default value = 0b00000000, read/write) */
#define FXOS8700_REGISTER_CTRL_REG4     0x2D/**< 0x2D (default value = 0b00000000, read/write) */
#define FXOS8700_REGISTER_CTRL_REG5     0x2E/**< 0x2E (default value = 0b00000000, read/write) */
#define FXOS8700_REGISTER_MSTATUS       0x32/**< 0x32 */
#define FXOS8700_REGISTER_MOUT_X_MSB    0x33/**< 0x33 */
#define FXOS8700_REGISTER_MOUT_X_LSB    0x34/**< 0x34 */
#define FXOS8700_REGISTER_MOUT_Y_MSB    0x35/**< 0x35 */
#define FXOS8700_REGISTER_MOUT_Y_LSB    0x36/**< 0x36 */
#define FXOS8700_REGISTER_MOUT_Z_MSB    0x37/**< 0x37 */
#define FXOS8700_REGISTER_MOUT_Z_LSB    0x38/**< 0x38 */
#define FXOS8700_REGISTER_MCTRL_REG1    0x5B/**< 0x5B (default value = 0b00000000, read/write) */
#define FXOS8700_REGISTER_MCTRL_REG2    0x5C/**< 0x5C (default value = 0b00000000, read/write) */
#define FXOS8700_REGISTER_MCTRL_REG3    0x5D/**< 0x5D (default value = 0b00000000, read/write) */

void FXOS8700_Init(void);
double get_Accelerometer_X(void);
double get_Accelerometer_Y(void);
double get_Accelerometer_Z(void);



#endif
