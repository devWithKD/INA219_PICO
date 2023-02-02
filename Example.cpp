#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "include/INA219.hpp"

#define SDA 4
#define SCL 5
#define I2C i2c0
#define PCF8575_addr 0x40




int main(){
    stdio_init_all();
    INA219 sensor(I2C,PCF8575_addr);
    sensor.init();
    sensor.calibrate();
    while(true){
        double curr = sensor.readCurrent();
        double pow = sensor.readPower();
        printf("Curr = %f, Pow = %f\n", curr, pow);
    }
}