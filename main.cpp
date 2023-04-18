/*
 *  Title: SCD42 Driver - main function

 *  Description:
 *      Read data from SCD42 via i2c and print over USB serial
 * 
 *  Author: Berglind Dan Robertsdottir
 */

#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include <hardware/i2c.h>
#include <SCD30.h>
#include <SCD42.h>
#include <Display.h>

// Defines
#define I2C_BAUD_RATE (100*1000) // Set i2c speed at 100 kHz, SCD42 maximum

// Pinouts
#define I2C_SDA_PIN 0
#define I2C_SCL_PIN 1

// Display pins
#define DISPLAY_1 16
#define DISPLAY_2 17
#define DISPLAY_3 18
#define DISPLAY_4 19
#define DISPLAY_5 20
#define DISPLAY_6 21
#define DISPLAY_7 22
#define DISPLAY_8 26
#define DISPLAY_9 8
#define DISPLAY_10 9
#define DISPLAY_11 10
#define DISPLAY_12 11
#define DISPLAY_13 12
#define DISPLAY_14 13
#define DISPLAY_15 14
#define DISPLAY_16 15

// Variables and data structures
Display_GPIO_pins display_pins;
uint8_t digit_1 = 0;
uint8_t digit_2 = 0;
uint8_t digit_3 = 0;
uint8_t digit_4 = 0;
bool colon = false;
bool period = false;

// Constructors
SCD42 scd42(i2c0);
Display display;

void init() {
    stdio_init_all();
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    i2c_init(i2c0, I2C_BAUD_RATE);
    sleep_ms(1000);
    if (!scd42.init()) {
        printf("Failed to initialize SCD42 Sensor\n");
    }
    display_pins.anode_digit_1_0 = DISPLAY_16; //ytri hringur
    display_pins.anode_digit_1_1 = DISPLAY_1; // innra stuff
    display_pins.anode_digit_2_0 = DISPLAY_15;
    display_pins.anode_digit_2_1 = DISPLAY_2;
    display_pins.anode_digit_3_0 = DISPLAY_11;
    display_pins.anode_digit_3_1 = DISPLAY_10;
    display_pins.anode_digit_4_0 = DISPLAY_8;
    display_pins.anode_digit_4_1 = DISPLAY_9;
    display_pins.anode_colon_period = DISPLAY_7;
    display_pins.common_A_G2_DC = DISPLAY_14;
    display_pins.common_B_H_DP = DISPLAY_13;
    display_pins.common_C_J = DISPLAY_4;
    display_pins.common_D_K = DISPLAY_3;
    display_pins.common_E_L = DISPLAY_6;
    display_pins.common_F_M = DISPLAY_12;
    display_pins.common_G1_N = DISPLAY_5;
    display.init(&display_pins);
}
uint counter = 0;
void loop() {
    if(counter == 5000) {
        counter = 0;
        scd42.read();
        digit_1 = scd42.CO2 / 1000 % 10;
        digit_2 = scd42.CO2 / 100 % 10;
        digit_3 = scd42.CO2 / 10 % 10;
        digit_4 = scd42.CO2 % 10;
        printf("Co2:      %d ppm\n", scd42.CO2);
        printf("Temp:     %d °C\n", scd42.temperature);
        printf("Humidity: %d %%\n\n", scd42.humidity);
    }
    counter++;
    sleep_ms(1);
    display.update_digit(&digit_1, &digit_2, &digit_3, &digit_4, &colon, &period);
}

int main() {
    init();
    while(1) {
        loop();
    }
    return 0;
}

