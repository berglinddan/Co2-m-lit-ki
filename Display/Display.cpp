/*
 *  Title: Display.cpp

 *  Description: Numbers 1-9 and DIG1,2,3,4 defined from COM-21214 datasheet.
 * 
 *  Author: Berglind Dan Robertsdottir
 */


#include <stdio.h>
#include "pico/stdlib.h"
#include "Display.h"

/*!
 * @brief Construct a new Display object
 * @param pins Display_GPIO_pins struct containing the pin definition for the display
 */
Display::Display() {}

/*!
 * @brief initialize
 */
void Display::init(Display_GPIO_pins* pins) {
    _pins[0] = pins->anode_digit_1_0;
    _pins[1] = pins->anode_digit_1_1;
    _pins[2] = pins->anode_digit_2_0;
    _pins[3] = pins->anode_digit_2_1;
    _pins[4] = pins->anode_digit_3_0;
    _pins[5] = pins->anode_digit_3_1;
    _pins[6] = pins->anode_digit_4_0;
    _pins[7] = pins->anode_digit_4_1;
    _pins[8] = pins->anode_colon_period;
    _pins[9] = pins->common_A_G2_DC;
    _pins[10] = pins->common_B_H_DP;
    _pins[11] = pins->common_C_J;
    _pins[12] = pins->common_D_K;
    _pins[13] = pins->common_E_L;
    _pins[14] = pins->common_F_M;
    _pins[15] = pins->common_G1_N;
    for(uint i = 0; i < 16; i++) {
        gpio_init(_pins[i]);
        gpio_set_dir(_pins[i], GPIO_OUT);
        gpio_set_drive_strength(_pins[i], gpio_drive_strength::GPIO_DRIVE_STRENGTH_12MA);
        gpio_put(_pins[i], false);
    }
    for(uint i = 0; i < 9; i++) {
        _anode_mask |= (uint32_t)1u << _pins[i];
    }
    for(uint i = 0; i < 7; i++) {
        _cathode_mask |= (uint32_t)1u << _pins[i+9];
    }
}

void Display::update_digit(uint8_t* digit_1, uint8_t* digit_2, uint8_t* digit_3, uint8_t* digit_4, bool* colon, bool* period) {
    //printf("0x%x\n", ((uint32_t)1u << _pins[_counter]));
    if(_counter == 9) _counter = 0;
    uint32_t digit_value_mask = 0xFFFFFFFFu;
    switch(_counter) {
        case 0:
            //printf("Counter: %d\n", _counter);
            switch(*digit_1) {
                case 0:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[13]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    break;
                case 1:
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    break;
                case 2:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[13]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 3:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 4:
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 5:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 6:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[13]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 7:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    break;
                case 8:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[13]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 9:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                default:
                    break;

            }
            break;
        case 1:
            switch(*digit_1) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 3:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 4:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 5:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 6:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 8:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 9:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                default:
                    break;
            }
            break;
        case 2:
            //printf("Counter: %d\n", _counter);
            switch(*digit_2) {
                case 0:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[13]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    break;
                case 1:
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    break;
                case 2:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[13]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 3:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 4:
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 5:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 6:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[13]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 7:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    break;
                case 8:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[13]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 9:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                default:
                    break;

            }
            break;
        case 3:
            switch(*digit_2) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 3:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 4:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 5:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 6:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 8:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 9:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                default:
                    break;
            }
            break;
        case 4:
            //printf("Counter: %d\n", _counter);
            switch(*digit_3) {
                case 0:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[13]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    break;
                case 1:
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    break;
                case 2:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[13]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 3:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 4:
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 5:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 6:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[13]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 7:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    break;
                case 8:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[13]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 9:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                default:
                    break;

            }
            break;
        case 5:
            switch(*digit_3) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 3:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 4:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 5:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 6:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 8:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 9:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                default:
                    break;
            }
            break;
        case 6:
            //printf("Counter: %d\n", _counter);
            switch(*digit_4) {
                case 0:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[13]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    break;
                case 1:
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    break;
                case 2:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[13]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 3:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 4:
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 5:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 6:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[13]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 7:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    break;
                case 8:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[13]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                case 9:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[10]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[11]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[12]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[14]);
                    digit_value_mask &= ~((uint32_t)1u << _pins[15]);
                    break;
                default:
                    break;

            }
            break;
        case 7:
            switch(*digit_4) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 3:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 4:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 5:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 6:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 8:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                case 9:
                    digit_value_mask &= ~((uint32_t)1u << _pins[9]);
                    break;
                default:
                    break;
            }
            break;
        case 8:
            if(*colon) {
                digit_value_mask &= ~((uint32_t)1u << _pins[9]);
            }
            if(*period) {
                digit_value_mask &= ~((uint32_t)1u << _pins[10]);
            }
        default:
            break;
    }
    digit_value_mask = digit_value_mask & _cathode_mask;
    gpio_put_masked(_cathode_mask | _anode_mask, digit_value_mask | ((uint32_t)1u << _pins[_counter] & _anode_mask));
    _counter++;
}