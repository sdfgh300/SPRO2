
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
#include <math.h>
// #include "lcd.h"

// uint16_t adc_read(uint8_t );
float read_voltage(uint8_t chosenPIN);
// pin 0

#define channel7 7
#define channel6 6
#define channel5 5
#define channel4 4
#define channel3 3
#define channel2 2
#define channel1 1
#define channel0 0

#define AVG_STRENGTH 50
/* #define ADC_PIN 0

uint16_t adc_read(uint8_t adc_channel);


int main(){

  uart_init(); // open the communication to the microcontroller
  io_redirect(); // redirect input and output to the communication
  //I2C communication enabled
  i2c_init(); //??? not sure about the order
  //LCD_init();
 uint16_t adc_result;// Select Vref= AVcc
ADMUX = (1<<REFS0);//set prescalerto 128 and turn on the ADC module
ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);


int lol;
while(1){
        printf("Write 1");
        scanf("%d", &lol);

        if(lol==1){
        //float value = read_voltage(channel0);

        adc_result= adc_read(ADC_PIN);
        printf("%f\n", adc_result);
        }
}




return 0;
}*/

int main(void)
{

    uart_init();   // open the communication to the microcontroller
    io_redirect(); // redirect input and output to the communication
    // I2C communication enabled
    i2c_init(); //??? not sure about the order
                // LCD_init();

    PIND |= (1<<PD7);
    PORTD |= (1<<PD7);

    

    while (1)
    {
        int lol;
        // printf("Write 1\n");
        // scanf("%d", &lol);
        // if(lol==1){

        float avgVoltage = 0;
        for (uint8_t i = 0; i < AVG_STRENGTH; i++)
        {
            float value = read_voltage(channel0);
            float voltage = (((value * 5) / 1024.0f) - 2.5) * 2;
            avgVoltage += voltage;
        }
        avgVoltage /= AVG_STRENGTH;     

        float value = read_voltage(channel1);
        float resistance = ((1024.0f / value) - 1) * 986;
        
             
        // printf("Volts: %.1f\n", avgResistance);

        printf("Volts: %.1f  || Resistance: %.1f\n", avgVoltage, resistance);
        // }
    }

    return 0;
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

float read_voltage(uint8_t channel)
{
    // ADMUX &= 0xf0;
    // ADMUX = 0x00;//(1 << REFS0); // select internal 5V as reference voltage
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // selecting the prescaler for ADC conversion

    ADMUX &= 0xF0;    // clear the lower 4 bits of ADMUX to select ADC channel
    ADMUX |= channel; // select ADC channel 1 (replace ADC_CHANNEL_1 with your defined constant)

    ADCSRA |= (1 << ADEN) | (1 << ADSC); // enable ADC and start conversion
    ADMUX |= (1 << REFS0);
    // Wait for the conversion to complete
    while (ADCSRA & (1 << ADSC))
    {
        // Wait until ADSC becomes 0 (conversion is complete)
    }

    // You may want to clear the ADSC bit here, although it's not necessary for single conversions
    // ADCSRA &= ~(1 << ADSC);

    // Return the ADC result
    return ADC;
}

/*


uint16_t adc_read(uint8_t adc_channel){
  ADMUX &= 0xf0; // clear any previously used channel, but keep internal reference
  ADMUX |= adc_channel; // set the desired channel
  //start a conversion
  ADCSRA |= (1<<ADSC);// now wait for the conversion to complete
  while ( (ADCSRA & (1<<ADSC)) );
  // now we have the result, so we return it to the calling function as a 16 bit unsigned int
  return ADC;
  }
*/