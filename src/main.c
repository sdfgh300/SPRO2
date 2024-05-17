
/*
requirements: 
- ADC  
- battery checker
- take measurements (5 functions)
- display


*/





#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "i2cmaster.h"
#include "usart.h"
#include "lcd.h"

volatile uint32_t ms_counter;
int seconds;
int minutes;

////////////declarations

void timer_setup();
void seconds_to_minutes();

///display code

int rxDisplay(char *componentValue);
void txDisplay(char *componentValue, float value, unsigned int type);


//uint16_t adc_read(uint8_t );
uint16_t read_voltage(uint8_t chosenPIN);
//pin 0
#define ADC 
#define channel7 7
#define channel6 6
#define channel5 5
#define channel4 4
#define channel3 3
#define channel2 2
#define channel1 1
#define channel0 0

int main(void) {  

  uart_init(); // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication
  //I2C communication enabled
  i2c_init(); //??? not sure about the order
  LCD_init();

  ms_counter=0;
  seconds=0;


    
    timer_setup();

    while (1) 
    {
      
        // Your main loop code here
        //printf("%d seconds\n", seconds);
        seconds_to_minutes();
        LCD_set_cursor(1,1);
        printf("%d:%d", minutes, seconds);
        int value = read_voltage(channel0);
        LCD_set_cursor(1,2);
        printf("%d", value);

    }
  
  return 0;
}


//////////TIMERS
void timer_setup()
{

// Calculate the number of clock cycles per second
// (Clock Frequency / Prescaler) = Number of Clock Cycles
// (16,000,000 / 64) = 250 000 clock cycles per second

// Calculate OCR0A value
// OCR0A = Number of Clock Cycles per Second - 1
//OCR0A = 250,000 - 1 = 249,999 //(0x1E 0x7F in hexadecimal) -> every one milisecond

// Set OCR0A to 249,999 (0x1E 0x7F)

  // Set the Timer Mode to CTC
 // Set the Timer Mode to CTC
 TCCR1B |= (1 << WGM12);// Set the value that you want to count to
 
 OCR1A = 0xF9; //250
 TIMSK1 |= (1 << OCIE1A);    //Set the ISR COMPA vect
 sei(); 
 TCCR1B |= (1 << CS11)|(1<<CS00);//prescaler to 64
         

}

// Timer overflow interrupt service routine TIMER0_COMPA_vect
ISR(TIMER1_COMPA_vect) {
  // Increment seconds counter
  if(ms_counter == 1000 ){
  seconds++;
  ms_counter = 0;
  PORTB ^=(1<<PB5);
  //turns on motor
  }
  else
  ms_counter++;

 
}


void seconds_to_minutes()
{
  if(seconds == 60){
    seconds =0;
    minutes++;
    LCD_set_cursor(4,1);
    printf(" ");
    LCD_set_cursor(5,1);
    printf(" ");
    if(minutes==5 ){
      LCD_set_cursor(1,1);
      printf("TIME EXCEEDED!!!");
    }
    
  }


}
//////////////////////////////////////////////////////////////////
/////////////ADC/////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

/*

void readPIN()
{
uint16_t adc_result;
// Select Vref= AVcc
ADMUX = (1<<REFS0); //set prescalerto 128 and turn on the ADC module
ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)| (1<<ADEN); //219 DS
//ADEN - Writing this bit to one enables the ADC 
//ADSC - start conversion
//ADP 0,1,2 as 1 - prescaler o 128



  adc_result= adc_read(ADC_PIN1);
  LCD_set_cursor(2,2);
  printf("%d", adc_result );
  

}

uint16_t adc_read(uint8_t adc_channel)
{
ADMUX &= 0xf0; // clear any previously used channel, but keep internal reference
ADMUX |= adc_channel; // set the desired channel 
//start a conversion
ADCSRA |= (1<<ADSC);
// now wait for the conversion to complete
while ( (ADCSRA & (1<<ADSC)) );
// now we have the result, so we return it to the 
//calling function as a 16 bit unsigned int
return ADC;
}
*/


uint16_t read_voltage(uint8_t channel) {
    ADMUX |= (1 << REFS0); // select internal 5V as reference voltage
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // selecting the prescaler for ADC conversion

    ADMUX &= 0xF0; // clear the lower 4 bits of ADMUX to select ADC channel
    ADMUX |= channel; // select ADC channel 1 (replace ADC_CHANNEL_1 with your defined constant)

    ADCSRA |= (1 << ADEN) | (1 << ADSC); // enable ADC and start conversion

    // Wait for the conversion to complete
    while (ADCSRA & (1 << ADSC)) {
        // Wait until ADSC becomes 0 (conversion is complete)
    }

    // You may want to clear the ADSC bit here, although it's not necessary for single conversions
    // ADCSRA &= ~(1 << ADSC);

    // Return the ADC result
    return ADC;
}

///Read battery///

void battery_read(){
  //int battery = read_voltage(channel0)
}


////GAME 1////

void game_one()
{
  //voltages
  // x = 5 V; 
  //green LED if ADC == correct
  //if(read_voltages(channel1)== x)
  //{ greenLED.On =  true; return 1;}
  //else return 0;

}

void game_two(){

/*
check button pressed



*/



//voltages
  // x = 5 V; 
  //green LED if ADC == correct
  //if(read_voltages(channel2)== x)
  //{ greenLED.On =  true; return 1;}
  //else return 0;

}

void game_three(){

//if button is pressed, then check
  //voltages
  // x = 5 V; 
  //green LED if ADC == correct
  //if(read_voltages(channel3)== x)
  //{ greenLED.On =  true; return 1;}
  //else return 0;

}

void count_hearts(){
  //how?
  //if an LED is off ->
}



/////Mauserements

//Convertst the difference between voltages to get resistance (V=IR).
//It uses read_voltage(pin) function where you need to declare the proper pin
//depending on the place it is connected
float convert_resistance()
{
  //choose the pin
  uint8_t pin = 1; //chosen pin 1 as default
  //set the value of the current
  float current = 2; //ampers
  //set the supply voltage that goes before the resistor
  float voltage = 4; //volts
  //measured voltage
  float measured_voltage = read_voltage(pin);

  //resistance declaration
  float resistance = 0;
  //V=IR
  resistance = (voltage - measured_voltage)/current;
  return resistance;

}




//check if accurate
float convert_voltage()
{

  ///put code
  return 0;
}






#define btn_voltage 0//put value
#define btn_resistnce 0 


//copy and put it into mutlimeter
void multimeter_main()
{

  while(1)
  {
    
    //check buttons pressed
    if(btn_voltage == 1){
      //printf on nextio  value from
      float value = convert_voltage();

    }

    if(btn_resistnce == 1){
      //printf on nextio  value from
      float value = convert_resistance();

    }

    



  }//while(1)

}//main ends


/////////////////////////////////////////////////////

//Display functions
int rxDisplay(char *componentValue)
{
    char receivedValue[8] = {0};
    printf("get %s%c%c%c",componentValue, 0xFF, 0xFF, 0xFF);
    for(int i = 0; i < 8; i++)
    {
        scanf("%c", &receivedValue[i]);
    }
    // printf("%c%c%c%c",recievedValue[1],0xFF,0xFF,0xFF); //For debugging purposes
    return receivedValue[1];
}

void txDisplay(char *componentValue, float value, unsigned int type) //type 0=int, type 1 = float
{ 
    if (type == 0)
    {
        printf("%s=%d%c%c%c",componentValue,(int)value,0xFF,0xFF,0xFF);
    }
    else
    {
        printf("%s=%d%c%c%c",componentValue,(int)(value*10),0xFF,0xFF,0xFF);
    }
}