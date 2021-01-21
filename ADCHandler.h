/* ADCHandler.cpp

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

#ifndef ADC_HNDLR
#define ADC_HNDLR

// ADC channel definitions - 
// do not use Arduino style A0, A1 etc
#define ADC0	0
#define ADC1	1
#define ADC2	2
#define ADC3	3
#define ADC4	4
#define ADC5	5
#define ADC6	6
#define ADC7	7
#define ADC8	8
#define ADC9	9
#define ADC10	10
#define ADC11	11
#define ADC12	12
#define ADC13	13
#define ADC14	14
#define ADC15	15

// ADC clock frequency defines
// at fclk=16MHz, DIV16 gives a 13us conversion time
#define ADC_DIV2	1
#define ADC_DIV4	2
#define ADC_DIV8	3
#define ADC_DIV16	4
#define ADC_DIV32	5
#define ADC_DIV64	6
#define ADC_DIV128	7

//ADC reference select defines
#define ADC_AREF	0x00
#define ADC_AVCC	0x40
#define ADC_1V1		0x80
#define ADC_2V56	0xC0

// ADC result left or right justify
#define ADC_RJUST	0x00
#define ADC_LJUST	0x20

//Auto trigger defines
#define ADC_AUTO_ON		1
#define ADC_AUTO_OFF	0
#define ADC_FREE_RUN	0	// Free running conversion
#define ADC_ACOMP		1	// Analogue comparator
#define ADC_EXTINT0		2	// External interrupt request 0
#define ADC_OC0A		3	// Timer0 Output Compare Match A
#define ADC_T0OVF		4	// Timer 0 Overflow
#define ADC_OC1B		5	// Timer 1 Output Compare Match B
#define ADC_T1OVF		6	// Timer 1 Overflow
#define ADC_T1IC		7	// Timer 1 Input Capture Event


 class ADCHandler{
	 
	 public: 
		void initADC( uint8_t Freq, uint8_t LAdj, uint8_t REFSel );
		void connectADCPin( uint8_t ADCChannel );
		uint16_t readADC(uint8_t ADCChannel);
		void startADCConversion(uint8_t ADC_Channel, uint8_t ADC_AutoEn, uint8_t AutoSource );
		uint8_t getADCResult(uint16_t *ADCResult);
		void attachADCInterrupt();
		void detachADCInterrupt();
		
		private:
		
 };
 
 #endif
 
