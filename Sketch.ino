/* ADCHandlertest.ino

    ADC Routines for ATMega 2560
	
	These routines were written, primarily, to allow an ADC conversion to
	execute place as a background task. Selection of more configurations
	is also possible  Refer to the datasheet for the ATMega and Microchip 
	app note AN2538 for details
	To improve execution speed the ADCn channel number is used
	and not the Arduino An pin designation.
	
	Author: James Holland
	Date:  21st January 2021
	version: 0.1 -  only single ended conversions supported
*/


#include <Arduino.h>
#include "ADCHandler.h"



ADCHandler MyADC;
uint16_t CH0Value = 0;
uint16_t CH1Value = 0;
uint16_t CH2Value = 0;


void setup() {

  MyADC.initADC( ADC_DIV8, ADC_RJUST, ADC_AVCC );
  MyADC.connectADCPin( ADC0 );
  MyADC.connectADCPin( ADC1 );
  MyADC.connectADCPin( ADC2 );

  //for timing test
  pinMode(12, OUTPUT);

  // turn off system timer to prevent timing scatter
  // note: DELAY() won't work !!!!!!!!
  // TCCR0B = 0;
  
}

void loop() {

  // run ADC conversion as a background task
 
  MyADC.startADCConversion(ADC1, ADC_AUTO_OFF, 0 );				// begin a conversion - takes 2.96us
 
  delay(1);														// execute some code

  // PORTB |= (1 << PB6 );										
  MyADC.getADCResult(&CH0Value);								// go back for the result - takes 2.14us
  // PORTB &= ~(1 << PB6 );

  delay(1);		


  // start a conversion and wait for result (much the same as Analogread())
  CH0Value = MyADC.readADC(ADC0);

  //PORTB |= (1 << PB6 );
  CH1Value = MyADC.readADC(ADC1);									// takes 15.1us @500kHz
  //PORTB &= ~(1 << PB6 );


   CH2Value = MyADC.readADC(ADC2);

 }
