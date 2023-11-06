/*
 * d_led.h
 *
 *  Created  on: 26.07.2016
 *  Modified on: 31.10.2023
 *      Author: Unknown
 */
#ifndef _d_led_h
#define _d_led_h
#define SEG_DOT (1<<PB0)
#define SEG_A (1<<PB1)
#define SEG_B (1<<PB2)
#define SEG_C (1<<PB5)
#define SEG_D (1<<PB7)
#define SEG_E (1<<PB6)
#define SEG_F (1<<PB3)
#define SEG_G (1<<PB4)
#define LED_K4 (1<<PD2)
#define LED_K3 (1<<PD3)
#define LED_K2 (1<<PD4)
#define LED_K1 (1<<PD5)
#define LED_KK LED_K1 | LED_K2 | LED_K3 | LED_K4
#define DIGIT_0 SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F    //Digit 0 consists of 6 lit segments
#define DIGIT_1 SEG_B | SEG_C                                    //Digit 1 ... etc.
#define DIGIT_2 SEG_A | SEG_B | SEG_D | SEG_G | SEG_E
#define DIGIT_3 SEG_A | SEG_B | SEG_C | SEG_G | SEG_D
#define DIGIT_4 SEG_B | SEG_C | SEG_G | SEG_F
#define DIGIT_5 SEG_A | SEG_F | SEG_G | SEG_C | SEG_D
#define DIGIT_6 SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G
#define DIGIT_7 SEG_A | SEG_B | SEG_C
#define DIGIT_8 SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G
#define DIGIT_9 SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G

extern uint8_t DigitMap[10];

void d_led_init(void);

extern volatile uint8_t pos1;
extern volatile uint8_t pos2;
extern volatile uint8_t pos3;
extern volatile uint8_t pos4;

extern volatile uint8_t hz1,hz2;

uint8_t makeRefreshSlower();
uint8_t makeRefreshFaster();

#endif
