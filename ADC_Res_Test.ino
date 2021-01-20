/* ADC Resolution Test
 *  
 *  A0 is connected directly to GND
 *  A1 is connected via a 1k resistor to a voltage calibrator set at 
 *  just under 5V
 *  
 *  sequence is:
 *  read A0 50 times to drive the SAH cap to 0V
 *  read A1 50 times to get a stable reading from the input
 *  switch between A0 and A1 for 50 cycles
 *  send results via serial port

  ADC clock frequency can be re-configured in setup()
*/

// ADC clock frequency defines
// at fclk=16MHz
#define ADC_8MHz  1
#define ADC_4MHz  2
#define ADC_2MHz  3
#define ADC_1MHz  4
#define ADC_500K  5
#define ADC_250K  6
#define ADC_125K  7     // standard Arduino setting

uint16_t resultBuff[50][2];

void setup() {
  
  // re-configure ADC here
    ADCSRA &= 0xF8;       // clear cuurrent setting 
    ADCSRA |= ADC_500K;   // write new setting

  Serial.begin(115200);
  
}

void loop() {

  
   // read 0V opin (A0)
    for(int i=0;i<50;i++){
      resultBuff[i][0] = analogRead(A0);
    }
    // read 5V pin
    for(int i=0;i<50;i++){
      resultBuff[i][1] = analogRead(A1);
    }

  Serial.println("Test 1");  

  for(int i=0;i<50;i++){
    Serial.println(String(resultBuff[i][0]) + "," + String(resultBuff[i][1]));
  }

  Serial.println("Test 2");

  // toggle between inputs
    for(int i=0;i<50;i++){
      resultBuff[i][0] = analogRead(A0);
      resultBuff[i][1] = analogRead(A1);
    }
  
  for(int i=0;i<50;i++){
    Serial.println(String(resultBuff[i][0]) + "," + String(resultBuff[i][1]));
  }

  while(1);

    
 }

 
