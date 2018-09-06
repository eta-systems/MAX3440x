
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

#include "max3440x.h"
#include "main.h"

/**
  * @brief      writes a single value into a MAX3340X register
  * @param      *chip, pointer to the MAX3340X typedef struct
  * @param      reg, the destination register's address
  * @param      val, the value for the destination register
  */
uint8_t MAX3340X_Write8(MAX3440X *chip, uint8_t reg, uint8_t val){
    if(HAL_I2C_Mem_Write(chip->wireIface, chip->devAddress, reg, 1, &val, 1, 10) != HAL_OK) 
        return 1;
    return 0;
}

/**
  * @brief      reads a single value from a MAX3340X register
  * @param      *chip, pointer to the MAX3340X typedef struct
  * @param      reg, the destination register's address
  * @param      val, pointer to the location where the value shall be stored
  * @return     0 on success, 1 on transmission error
  */
uint8_t MAX3340X_Read8(MAX3440X *chip, uint8_t reg, uint8_t *val){
  HAL_I2C_Master_Transmit(chip->wireIface, chip->devAddress, &reg, 1, 1);
  HAL_I2C_Master_Receive(chip->wireIface, chip->devAddress, val, 1, 1);
  return 0;
}

/**
  * @brief      Initalizer function
  * @param      *chip, pointer to the MAX3440X typedef struct
  * @param      *wireIface a pointer to a HAL I2C_HandleTypeDef
  * @param      address of the chip on the I2C bus
  */
uint8_t MAX3440X_Init(MAX3440X *chip, I2C_HandleTypeDef *wireIface, uint16_t address){
  chip->wireIface = wireIface;
  chip->devAddress = address;
  return 0;
}

uint8_t MAX3440X_Print_Info(MAX3440X *chip){
  uint8_t dev_year = 0, dev_week = 0, dev_id = 0, dev_status = 0;
  MAX3340X_Read8(chip, MAX3440X_DATE_CODE_YEAR,      &dev_year);
  MAX3340X_Read8(chip, MAX3440X_DATE_CODE_WORK_WEEK, &dev_week);
  MAX3340X_Read8(chip, MAX3440X_DEVICE_ID_REVISION,  &dev_id);
  MAX3340X_Read8(chip, MAX3440X_STATUS,              &dev_status);
  printf("MAX3340X\n\
Dev  ID:  \t%d\n\
Revision: \t%d\n\
Prod Year:\t20%02d\n\
Prod Week:\t%d\n\
Status   :\t0x%02x\n", ((dev_id>>3)&0x1F), (dev_id&0x7),dev_year, dev_week, dev_status);
  return 0;
}

uint8_t MAX3440X_Set_Shutdown_Delay(MAX3440X *chip, uint8_t delay){
  return MAX3340X_Write8(chip, MAX3440X_SHUTDOWN_DELAY, delay);
}

uint8_t MAX3440X_Clear_Alert(MAX3440X *chip){
  return 0;
}

uint8_t MAX3440X_Set_Samlperate(MAX3440X *chip, uint8_t rate){
  return 0;
}



