# stm32f303re_project

simple project of stm32f303re Neuclo Board development.

short description of this project:
1. MCU: stm32f303re Neuclo Board
2. development enviroment: platformio in VS Code 
3. Framework: CMSIS

Serval examples of following functions are provided:
  1. UART communication between terminal and mcu.
  2. IIC communication between Adafruit Precision NXP 9-DOF Breakout Board and mcu.
  3. Timer
  4. 4 PWM pins controlling

## UART communication
By using "prinf" to print data in terminal.(Serial Monitor)

## IIC communication with Adafruit Precision NXP 9-DOF Breakout Board(FXAS21002 + FXOS8700CQ)

Connection
  |Pin on MCU |Breakout Board|
  |-----------|--------------|
  |GPIOB Pin 8|SCL           |
  |GPIOB Pin 9|SDA           |
  |5V         |Vin           |
  |GND        |GND           |

datasheets:<br>
  FXAS21002:  https://www.nxp.com/docs/en/data-sheet/FXAS21002.pdf  
  FXOS8700CQ: https://www.nxp.com/docs/en/data-sheet/FXOS8700CQ.pdf

## Timer(Delay)

delay in microsecon(μs)

## PWM
  |Pin        |Timer   |
  |-----------|--------|
  |GPIOC Pin 6|TIM3_CH1|
  |GPIOC Pin 7|TIM3_CH2|
  |GPIOC Pin 8|TIM3_CH3|
  |GPIOC Pin 9|TIM3_CH4|
