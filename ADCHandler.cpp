/* ADCHandler.h

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



#include<arduino.h>
#include "ADCHandler.h"



void ADCHandler::initADC( uint8_t Freq, uint8_t LAdj, uint8_t REFSel)
{

	ADCSRA = 0;
	ADMUX = 0;
	
	// disable ADC sleep mode
	PRR0 & (0 << PRADC);
	
	ADCSRA |= Freq;				// set frequency
	ADMUX |= LAdj;				// set output format
	ADMUX |= REFSel;			// set Vref source
	ADCSRA |= (1 << ADEN);		// turn on ADC

}


void ADCHandler::connectADCPin(uint8_t ADCPin)
{
	// disable digital input 
	
	uint8_t tmpBitMask=1;
	
	// set channel to analogue
	if(ADCPin<8){
		tmpBitMask |= (tmpBitMask << ADCPin);
		DIDR0 |= tmpBitMask;
	}
	else{
		ADCPin = ADCPin >> 4;
		tmpBitMask = (tmpBitMask << ADCPin);
		DIDR2 |= tmpBitMask;
	}
			
}		

void ADCHandler::startADCConversion(uint8_t ADC_Channel, uint8_t ADC_AutoEn, uint8_t AutoSource )
{
	// set up ADC channel select
	ADMUX &= 0xE0;			
	if(ADC_Channel > 7){
		ADCSRB |= (1 << MUX5);
		ADC_Channel &= 0xE0;
	}
	else{
		ADCSRB &= ~(1 << MUX5);
	}
	
	ADMUX |= ADC_Channel;
	
	//set up auto trigger if required
	if(ADC_AutoEn){
		ADCSRA |= (1 << ADATE);
		ADCSRB &= 0xF8;
		ADCSRB |= AutoSource;
	}
	else{
		ADCSRA &= ~(1 << ADATE);
	}
		
	// start conversion
	ADCSRA |= (1 << ADSC);
	
}

uint8_t ADCHandler::getADCResult(uint16_t *ADCResult)
{
	uint8_t ADCCompleted = 0;
	uint8_t test = 0;
	// is conversion complete?
	test = ADCSRA;
	if(test &= 0x10){		// test ADIF
		*ADCResult = ADC;
		ADCCompleted = 1;
		ADCSRA |= (1 << ADIF);
	}
	
	return ADCCompleted;
}


uint16_t ADCHandler::readADC(uint8_t ADCChannel)
{
	uint8_t isDone=0;
	uint16_t ADCResult;
	
	startADCConversion(ADCChannel, ADC_AUTO_OFF, 0);
	
	do{
		isDone = getADCResult(&ADCResult);
	}while(!isDone);
	
	ADCSRA |= (1 << ADIF);	// clear AD interrupt flag
	
	return ADCResult;
}

void attachADCInterrupt()
{
	ADCSRA |= (1 << ADIE);
}

void ADCHandler::detachADCInterrupt()
{
	
	ADCSRA &= ~(1 << ADIE);
	
}
	
	

	
	
	
	
	
	

			