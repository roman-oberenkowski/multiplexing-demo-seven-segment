#include <avr/io.h>
#include <avr/interrupt.h>
#include "d_led.h"

volatile uint8_t pos1;
volatile uint8_t pos2;
volatile uint8_t pos3;
volatile uint8_t pos4;
uint8_t refreshHz=50;

volatile uint8_t additionalSoftwarePrescallerMax=0;
uint8_t DigitMap[10] = {DIGIT_0, DIGIT_1, DIGIT_2, DIGIT_3, DIGIT_4, DIGIT_5, DIGIT_6, DIGIT_7, DIGIT_8, DIGIT_9};
void d_led_init(void){
	DDRB = 0xFF;	// PORTB pin is used for each display segment
	DDRD |= LED_KK; // PORTD is used for all four cathodes (one per digit)
	TCCR0A |= (1<<WGM01); 	// TIMER0 (8bit), WGM01 => CTC
	TCCR0B |= (1<<CS02); 	// CS02 => CLK/256
	OCR0A = 155;		 	// OCR0A=155 => Timer/156 => 200Hz interrupt
	TIMSK |=(1<<OCIE0A);	// Enable Timer compare interrupt
}

void calculateAndSetTimings(){
	
	uint16_t ocrDivider = 8000000/256/refreshHz/4;
	if (ocrDivider<=255){
		TCCR0B &= ~(1<<CS00); // restore to /256
		OCR0A = ocrDivider-1; // TODO: check if zero, or underflow?
		additionalSoftwarePrescallerMax=0; // not used
	} else {
		ocrDivider /= 4;
		TCCR0B |= (1<<CS00); // set to /1024
		if (ocrDivider <= 255) {
			OCR0A = ocrDivider-1;
			additionalSoftwarePrescallerMax=0; // not used
		} else {
			additionalSoftwarePrescallerMax = 0;
			while (ocrDivider>255) {
				ocrDivider /= 2;
				additionalSoftwarePrescallerMax++;
			}
		}
	}
}

uint8_t makeRefreshSlower(){
	refreshHz = (refreshHz-1) % 64;
	if (refreshHz==0) {
		refreshHz=1;
	}
	calculateAndSetTimings();
	return refreshHz;
}

uint8_t makeRefreshFaster() {
	refreshHz = (refreshHz+1) % 64;
	if (refreshHz==0) {
		refreshHz=63;
	}
	calculateAndSetTimings();
	return refreshHz;
}

	
ISR(TIMER0_COMPA_vect){ // Show (refresh) the digit on the next position
	static uint8_t currentPosition = 0;
	static uint8_t additionalSoftwarePrescallerCurrent = 0;
	if (additionalSoftwarePrescallerMax > 0 && additionalSoftwarePrescallerCurrent++ < additionalSoftwarePrescallerMax ) {
		return;
	}
	additionalSoftwarePrescallerCurrent=0;

	//PORTD &= ~LED_KK; // disable all cathodes (current one) to prevent ghosting
	PORTB = 0x00; // disable all segments to prevent ghosting

	switch (currentPosition) {
		case 0:
			PORTD = LED_K1; // enable cathode
			PORTB = pos1;	// enable correct output (order is important to prevent ghosting)
			break;
		case 1:
			PORTD = LED_K2;
			PORTB = pos2;
			break;
		case 2:
			PORTD = LED_K3;
			PORTB = pos3;
			break;
		case 3:
			PORTD = LED_K4;
			PORTB = pos4;
			break;
	}
	currentPosition = (currentPosition + 1) & 0b0011; // increment and mask to get 0..3 range
}

