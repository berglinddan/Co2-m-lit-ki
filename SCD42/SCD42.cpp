/*
 *  Title: SCD42.cpp

 *  Description:
 *     Read and write functions.
 * 
 *  Author: Berglind Dan Robertsdottir
 */


#include <stdio.h>
#include "pico/stdlib.h"
#include <hardware/i2c.h>
#include "SCD42.h"

/*The sensor needs 1000ms to enter idle state.
All SCD42 commands and data are mapped to a 16-bit address space 0x62*/


static uint8_t crc8(const uint8_t *data, int len);

/*!
 * @brief Construct a new SCD42::SCD42 object
 * @param *i2c
 *        The I2C hardware instance to be used
 * @param addr
 *        The I2C address for the sensor, defaulted to 0x62 (optional)
 */
SCD42::SCD42(i2c_inst_t *i2c, uint8_t addr) {
    _i2c = i2c;
    SCD42_ADDRESS = addr;
}

bool SCD42::send_command(uint16_t cmd){
    uint8_t buffer[2];
    buffer[0] = (cmd >> 8) & 0xFF;
    buffer[1] = cmd & 0xFF;

    return (i2c_write_timeout_us(i2c0, SCD42_ADDRESS, buffer, 2, false, 10000 ) == 2);
}

bool SCD42::start_periodic_measurement(void){
    return send_command(START_PERIODIC_MEASUREMENT);
}

// Initialize the sensor
bool SCD42::init(void) {
   return start_periodic_measurement();
}

/**
 * @brief Read data from sensor and place in the respective variables
 * @return True if data read successful, false if otherwise
 */
bool SCD42::read(void) {
    uint8_t buffer[9];

    for(int i = 0; i < 9; i++) buffer[i] = 0x00;
    
    buffer[0] = (READ_MEASUREMENT >> 8) & 0xFF;
    buffer[1] = READ_MEASUREMENT & 0xFF;

    i2c_write_timeout_us(_i2c, SCD42_ADDRESS, buffer, 2, true, 10000);
    
    sleep_ms(4); // Delay between write and read specified by datasheet as 4 ms

    i2c_read_timeout_us(_i2c, SCD42_ADDRESS, buffer, 9, false, 10000);

    for(uint8_t i = 0; i < 9; i += 3) {
        if(crc8(buffer + i, 2) != buffer[i+2]) {
            return false; // CRC is bad
        }
    }

    uint16_t _co2 = 0, _temp = 0, _hum = 0;

    _co2 |= buffer[0];
    _co2 <<= 8;
    _co2 |= buffer[1];

    _temp |= buffer[3];
    _temp <<= 8;
    _temp |= buffer[4];

    _hum |= buffer[6];
    _hum <<= 8;
    _hum |= buffer[7];

    CO2 = _co2;
    temperature = -45 + (175 * _temp / 65536);
    humidity = 100 * _hum / 65536;

    return true;
}

/**
 * @brief Calculate CRC8 checksum
 * @param *data
 *        Pointer to data to calculate checksum for
 * @param len
 *        Length of data in bytes
 * @return Checksum byte
 */
static uint8_t crc8(const uint8_t *data, int len) {
    const uint8_t POLYNOMIAL(0x31);
    uint8_t crc(0xFF);

    for(int j = len; j; --j) {
        crc ^= *data++;

        for(int i = 8; i; --i) {
            crc = (crc & 0x80) ? (crc << 1) ^ POLYNOMIAL : (crc << 1);
        }
    }
    return crc;
}






