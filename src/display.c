//Importing libraries
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"
#include "math.h"

//Prototypes
int rxDisplay(char *componentValue);
void txDisplay(char *componentValue, float value, unsigned int type);

char receivedValue[8] = {0};

int main(void)
{
    //Initalizing funtions that should be called once
    uart_init();
    io_redirect();

    rxDisplay("Lives.val");
    txDisplay("Lives.val",0,0);
    printf("click %s,%d%c%c%c","NoLife3", 1, 0xFF, 0xFF, 0xFF);
    for(int i = 0; i < 8; i++)
    {
        scanf("%c", &receivedValue[i]);
    }

    // rxDisplay("Lives.val");
    // txDisplay("Lives.val", 2, 0);

    while(1)
    {
        
    }
    return 0;
}



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