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

volatile uint8_t sec=0;
volatile uint8_t sec2=0;
volatile uint8_t min=0;
volatile uint8_t min2=0;
volatile uint8_t updateDisplayFlag=1;

void showTimer();
void makeRefreshSlowerAndShowHz();
void makeRefreshFasterAndShowHz();


/*
	number - one to show
	msToWait - delay to wait - in miliseconds (with granularity to 100ms, rounded down)
*/
void showNumberAndWait(uint16_t number, uint16_t msToWait){
	updateDisplayFlag=0;
	pos4 = DigitMap[number % 10];
	number /=10;
	pos3 = DigitMap[number % 10];
	number /=10;
	pos2 = 0x00; //DigitMap[number % 10];
	number /=10;
	pos1 = DigitMap[number % 10];
	for (uint8_t i = 0; i<msToWait/100; i++){
		_delay_ms(100);
	}
	showTimer();
	updateDisplayFlag=1;
}



int main(void){
	TCCR1B |= (1<<CS12);
	TCCR1B |= (1<<WGM12);
	TIMSK |= (1<<OCIE1A);
	OCR1A = 5000;	 	// 31250 for 1second
	d_led_init(); 		// setup pins, timer0 and interrupt for refresh operation
	
	DDRA &= ~((1<<PA0)| (1<<PA1)); 	// Buttons: DDR
	PORTA |= (1<<PA0)| (1<<PA1);	// Buttons: PULLUP
	pos1=DIGIT_8;
	pos2=DIGIT_7;
	pos3=DIGIT_6;
	pos4=DIGIT_5;
	sei();
	while(1){
		if( bit_is_clear(PINA, PA1) ){makeRefreshSlowerAndShowHz();}
		if( bit_is_clear(PINA, PA0) ){makeRefreshFasterAndShowHz();}
	}
}

void makeRefreshSlowerAndShowHz() {
	uint8_t currentHz = makeRefreshSlower();
	showNumberAndWait(currentHz, 200);
}
void makeRefreshFasterAndShowHz() {
	uint8_t currentHz = makeRefreshFaster();
	showNumberAndWait(currentHz, 200);
}

ISR(TIMER1_COMPA_vect){
	sec++;
	if(sec>9){sec=0;sec2++;}
	if(sec2>5){sec2=0;min++;}
	if(min>9){min=0;min2++;}
	if(min2>6){min2=0;}
	if (updateDisplayFlag){
		showTimer();
	}
}

void showTimer(){
	pos1=DigitMap[min2];
	pos2=DigitMap[min] | SEG_DOT;
	pos3=DigitMap[sec2] | SEG_DOT;
	pos4=DigitMap[sec];
}