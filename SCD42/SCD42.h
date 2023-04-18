/*
 *  Title: SCD42.h

 *  Description:
 *     SCD42 registers defined from SCD42 Datasheet. 
 *     Calls the read and write functions from SCD42.cpp
 * 
 *  Author: Berglind Dan Robertsdottir
 */


#pragma once
#include "hardware/i2c.h"

/*Gisti*/
#define START_PERIODIC_MEASUREMENT _u(0x21B1) //Send command
#define READ_MEASUREMENT _u(0xEC05) //read - 1ms
#define STOP_PERIODIC_MEASUREMENT _u(0x3F86) //send command - 500ms
#define SET_TEMPERATURE_OFFSET _u(0x241D) //write - 1ms
#define GET_TEMPERATURE_OFFSET _u(0x2318) //read - 1ms
#define SET_SENSOR_ALTITUDE _u(0x2427) //write - 1ms
#define GET_SENSOR_ALTITUDE _u(0x2322) //read - 1ms
#define SET_AMBIENT_PRESSURE _u(0xE000) //write - 1ms
#define PERFORM_FORCED_RECALIBRATION _u(0x362F) //send command and fetch result - 400ms
#define SET_AUTOMATIC_SELF_CALIBRATION_ENABLED _u(0x2416) //write - 1ms
#define GET_AUTOMATIC_SELF_CALIBRATION_ENABLED _u(0x2313) //read - 1ms
#define PERSIST_SETTINGS _u(0x3615) //send command - 800ms
#define GET_SERIAL_NUMBER _u(0x3682) //read - 1ms
#define PERFORM_SELF_TEST _u(0x3639) //read - 10000ms
#define PERFORM_FACTORY_RESET _u(0x3632) //send command - 1200ms
#define REINIT _u(0x3646) //send command - 20ms

#define SCD42_DEFAULT_ADDRESS 0x62

class SCD42 {
public:

    SCD42(i2c_inst_t* i2c, uint8_t addr = SCD42_DEFAULT_ADDRESS);

    bool init(void);
    bool send_command(uint16_t cmd);
    bool start_periodic_measurement(void);
    bool read(void);

    uint16_t CO2;
    int16_t temperature, humidity;
private:
    i2c_inst_t* _i2c;
    uint8_t SCD42_ADDRESS;
};