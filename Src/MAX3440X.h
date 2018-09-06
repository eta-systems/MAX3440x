
/**
  * @file       max3440x.h
  * @author     Simon Burkhardt github.com/mnemocron
  * @copyright  MIT license
  * @date       2018.09.06
  * @brief      C library for the MAX34408/9 Current Monitor.
  * @details
  * @see        github.com/mnemocron
  * @see        github.com/eta-systems
  * @see        https://datasheets.maximintegrated.com/en/ds/MAX34408-MAX34409.pdf
  */

#ifndef _MAX3440X_H
#define _MAX3440X_H

/**
  * @note  tested using STM32F373
  */
#ifndef STM32F3XX_H
#include "stm32f3xx_hal.h"
#endif

#ifndef STM32F3XX_HAL_I2C_H
#include "stm32f3xx_hal_i2c.h"
#endif

#ifndef MAIN_H
#include "main.h"
#endif

/**
  * @note  datasheet p.9 table 6 Command Codes
  */
#define MAX3440X_STATUS                           0x00 // Overcurrent Alarm
#define MAX3440X_CONTROL                          0x01 // Device Configuration
#define MAX3440X_OCDELAY                          0x02 // Overcurrent Detection Delay Configuration
#define MAX3440X_SHUTDOWN_DELAY                   0x03 // Shutdown Pin Delay Configuration
#define MAX3440X_ADC1                             0x04 // Averaged ADC Reading
#define MAX3440X_ADC2                             0x05 // 
#define MAX3440X_ADC3                             0x06 // 
#define MAX3440X_ADC4                             0x07 // 
#define MAX3440X_OVER_CURRENT_THRESHOLD_1         0x08 // Overcurrent Threshold
#define MAX3440X_OVER_CURRENT_THRESHOLD_2         0x09 // 
#define MAX3440X_OVER_CURRENT_THRESHOLD_3         0x0A // 
#define MAX3440X_OVER_CURRENT_THRESHOLD_4         0x0B // 
#define MAX3440X_DEVICE_ID_REVISION               0x0C // Device ID & Rev
#define MAX3440X_DATE_CODE_YEAR                   0x0D // Date Code Year
#define MAX3440X_DATE_CODE_WORK_WEEK              0x0E // Date Code Work Week
#define MAX3440X_ALERT_RESPONSE_ADDRESS           0x0C
#define MAX3440X_DISABLE_OVER_CURRENT_THRESHOLD   0xFF

#define MAX3440X_DISABLE_SHUTDOWN_DELAY 0x00
#define MAX3440X_ENABLE_SHUTDOWN_DELAY 0x80
#define MAX3440X_DISABLE_OVERCURRENT_DELAY 0x00
#define MAX3440X_ENABLE_OVERCURRENT_DELAY 0x80

/**
  * @note  datasheet p.11 table 8 Control Byte
  */
#define MAX3440X_CONTROL_ALERT      0x08
#define MAX3440X_SAMPLERATE_1       0x00
#define MAX3440X_SAMPLERATE_2       0x01
#define MAX3440X_SAMPLERATE_4       0x02
#define MAX3440X_SAMPLERATE_8       0x03
#define MAX3440X_SAMPLERATE_16      0x04
#define MAX3440X_SAMPLERATE_32      0x05
#define MAX3440X_SAMPLERATE_64      0x06
#define MAX3440X_SAMPLERATE_128     0x07

typedef struct {
  uint16_t devAddress;
  I2C_HandleTypeDef *wireIface;
} MAX3440X;

uint8_t MAX3440X_Write8             (MAX3440X*, uint8_t, uint8_t);
uint8_t MAX3440X_Read8              (MAX3440X*, uint8_t, uint8_t*);
uint8_t MAX3440X_Init               (MAX3440X*, I2C_HandleTypeDef*, uint16_t);
uint8_t MAX3440X_Print_Info         (MAX3440X*);
uint8_t MAX3440X_Clear_Alert        (MAX3440X*);
uint8_t MAX3440X_Set_Shutdown_Delay (MAX3440X*, uint8_t);
uint8_t MAX3440X_Set_Samlperate     (MAX3440X*, uint8_t);

#endif
