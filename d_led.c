#include <avr/io.h>
#include <avr/interrupt.h>
#include "d_led.h"


volatile uint8_t cy1;
volatile uint8_t cy2;
volatile uint8_t cy3;
volatile uint8_t cy4;
volatile uint8_t hz1=0;
volatile uint8_t hz2=0;
void d_led_init(void){
	DDRB = 0xFF;
	DDRD |= LED_KK;
	//TIMER
	TCCR0A |= (1<<WGM01);
	TCCR0B |= (1<<CS02);
	OCR0A = 155;//155
	TIMSK |=(1<<OCIE0A);
}
ISR(TIMER0_COMPA_vect){
if(hz1>=hz2){
	static uint8_t licznik = 0;
	PORTD &= ~LED_KK;
	PORTB = 0x00;
	if(licznik == 0){PORTD = LED_K1; PORTB = cy1;}
	if(licznik == 1){PORTD = LED_K2; PORTB = cy2 | (1<<PB0);}
	if(licznik == 2){PORTD = LED_K3; PORTB = cy3 | (1<<PB0);}
	if(licznik == 3){PORTD = LED_K4; PORTB = cy4;}
	licznik++;
	if(licznik>3) licznik = 0;
	hz1=0;
}else hz1++;
}

