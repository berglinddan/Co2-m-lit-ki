/*
 *  Title: Display.h

 *  Description: LED-screen pins defined from COM-21214 Datasheet.
 * 
 *  Author: Berglind Dan Robertsdottir
 */


#pragma once

struct Display_GPIO_pins {
    uint anode_digit_1_0; // 0
    uint anode_digit_1_1; // 1
    uint anode_digit_2_0; // 2
    uint anode_digit_2_1; // 3
    uint anode_digit_3_0; // 4
    uint anode_digit_3_1; // 5
    uint anode_digit_4_0; // 6
    uint anode_digit_4_1; // 7
    uint anode_colon_period; // 8
    uint common_A_G2_DC; // 9
    uint common_B_H_DP; // 10
    uint common_C_J; // 11
    uint common_D_K; // 12
    uint common_E_L; // 13
    uint common_F_M; // 14
    uint common_G1_N; // 15
};

class Display {
public:
    Display();

    void init(Display_GPIO_pins* pins);
    void update_digit(uint8_t* digit_1, uint8_t* digit_2, uint8_t* digit_3, uint8_t* digit_4, bool* colon, bool* period);
private:
    uint _pins[16] = {0};
    uint8_t _counter = 0;
    uint32_t _anode_mask = 0;
    uint32_t _cathode_mask = 0;
    //GPIO_pins _pins;
};