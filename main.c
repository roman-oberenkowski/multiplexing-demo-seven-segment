/*
 * main.c
 *
 *  Created on: 26.07.2016
 *      Author: Unknown
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "d_led.h"
#include <util/delay.h>
int i=256;
volatile uint8_t sec=0;
uint8_t sec2=0;
uint8_t min=0;
uint8_t min2=0;
uint8_t seg7(uint8_t a);
int main(void){
	TCCR1B |= (1<<CS12);
	TCCR1B |= (1<<WGM12);
	TIMSK |= (1<<OCIE1A);
	OCR1A = 31250;
	d_led_init();
	DDRA &= ~((1<<PA0)| (1<<PA1));
	PORTA |= (1<<PA0)| (1<<PA1);
	cy1=LED_C0;
	cy2=LED_C0;
	cy3=LED_C0;
	cy4=LED_C0;
	sei();
	while(1){
		if(sec>9){sec=0;sec2++;}
		if(sec2>5){sec2=0;min++;}
		if(min>9){min=0;min2++;}
		if(min2>6){min2=0;}
		cy4=seg7(sec);
		cy3=seg7(sec2);
		cy2=seg7(min);
		cy1=seg7(min2);
		if(  bit_is_clear(PINA, PA1) ){hz2++;_delay_ms(200);}
		if(  bit_is_clear(PINA, PA0)&&(hz2>0)  ){hz2--;_delay_ms(200);}
	}
}

ISR(TIMER1_COMPA_vect){
	sec++;
}
uint8_t seg7(uint8_t a){
	uint8_t value=0;
	switch (a){
	case 0:
				value=LED_C0;
				break;
	case 1:
				value=LED_C1;
				break;
	case 2:
				value=LED_C2;
				break;
	case 3:
				value=LED_C3;
				break;
	case 4:
				value=LED_C4;
				break;
	case 5:
				value=LED_C5;
				break;
	case 6:
				value=LED_C6;
				break;
	case 7:
				value=LED_C7;
				break;
	case 8:
				value=LED_C8;
				break;
	case 9:
				value=LED_C9;
				break;
	}


	return value;
}
