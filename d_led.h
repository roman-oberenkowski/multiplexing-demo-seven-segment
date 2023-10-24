/*
 * d_led.h
 *
 *  Created on: 26.07.2016
 *      Author: Unknown
 */
#ifndef _d_led_h
#define _d_del_h
#define LED_a (1<<PB1)
#define LED_b (1<<PB2)
#define LED_c (1<<PB5)
#define LED_d (1<<PB7)
#define LED_e (1<<PB6)
#define LED_f (1<<PB3)
#define LED_g (1<<PB4)
#define LED_K4 (1<<PD2)
#define LED_K3 (1<<PD3)
#define LED_K2 (1<<PD4)
#define LED_K1 (1<<PD5)
#define LED_KK LED_K1 | LED_K2 | LED_K3 | LED_K4
#define LED_C0 LED_a | LED_b | LED_c | LED_d | LED_e | LED_f
#define LED_C1 LED_b | LED_c
#define LED_C2 LED_a | LED_b | LED_d | LED_g | LED_e
#define LED_C3 LED_a | LED_b | LED_c | LED_g | LED_d
#define LED_C4 LED_b | LED_c | LED_g | LED_f
#define LED_C5 LED_a | LED_f | LED_g | LED_c | LED_d
#define LED_C6 LED_a | LED_c | LED_d | LED_e | LED_f | LED_g
#define LED_C7 LED_a | LED_b | LED_c
#define LED_C8 LED_a | LED_b | LED_c | LED_d | LED_e | LED_f | LED_g
#define LED_C9 LED_a | LED_b | LED_c | LED_d | LED_f | LED_g
extern volatile uint8_t cy1;
extern volatile uint8_t cy2;
extern volatile uint8_t cy3;
extern volatile uint8_t cy4;
extern volatile uint8_t hz1;
extern volatile uint8_t hz2;
void d_led_init(void);
#endif
