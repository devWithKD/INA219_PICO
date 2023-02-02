#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "INA219.hpp"

INA219::INA219(i2c_inst_t * _i2c, uint8_t addr)
{
    i2c = _i2c;
    ADDR = addr;
    i2c_init(i2c, 400 * 1000);
    gpio_set_function(SDA, GPIO_FUNC_I2C);
    gpio_set_function(SCL, GPIO_FUNC_I2C);
    gpio_pull_up(SDA);
    gpio_pull_up(SCL);
}

INA219::~INA219()
{
}

void INA219::init(){
    uint16_t data;
    data = (0x0000|
            INA219_busV_RANGE_32|                       // Buss Range Enum
            INA219_CONFIG_GAIN_8_320mv|                 // Gain Config Enum
            INA219_busV_ADC_12_BIT_16S|                 // VBus Sampling and adc resolution Enum
            INA219_shuntV_ADC_12_BIT_16S|               // Vshunt Sampling and adc resolution Enum
            INA219_CONFIG_shuntV_AND_busV_CONTINUOUS);  // Mode Enum
    uint8_t datatosend[3];
    datatosend[0] = INA219_CONFIG_REG;
    datatosend[1] = data >> 8;
    datatosend[2] = data & 0x00FF;
    i2c_write_blocking(i2c,ADDR,datatosend,3,false);
}

void INA219::calibrate(){
    uint8_t datatosend[3];
    datatosend[0] = (uint8_t)INA219_CALIBRATION_REG;
    datatosend[1] = ((uint16_t)CALVAL) >> 8;
    datatosend[2] = ((uint16_t)CALVAL) & 0x00FF;
    i2c_write_blocking(i2c,ADDR,datatosend,3,false);
}

double INA219::readCurrent(){
    calibrate();
    uint8_t data[2];
    uint8_t regRead = (uint8_t)INA219_CURRENT_REG;
    i2c_write_blocking(i2c,ADDR,&regRead,1,false);
    i2c_read_blocking(i2c,ADDR,data,2,false);
    int rawCurr = (data[0] << 8)|(data[1]);
    double curr = rawCurr * Current_LSB;
    return curr;
}

double INA219::readPower(){
    calibrate();
    uint8_t data[2];
    uint8_t regRead = (uint8_t)INA219_POWER_REG;
    i2c_write_blocking(i2c,ADDR,&regRead,1,false);
    i2c_read_blocking(i2c,ADDR,data,2,false);
    int rawPow = (data[0] << 8)|(data[1]);
    double pow = rawPow * Power_LSB;
    return pow;
}