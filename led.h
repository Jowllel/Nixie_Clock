/****************************************************************************************\
 * Project: Nixie Clock
 * File: C:\Users\jschaller\OneDrive\Beruflich\ETH\Projekte\Sem 3\Nixie_Clock\V1_1_0\SW\Nixie_Clock_Code\led.h
 * Author: Joel Schaller
 * Date: 02.02.2023
 * Version: 1.1.0
 * Description:
 * controls for the leds
\****************************************************************************************/

#ifndef LED_H_
#define LED_H_

#include "main.h"
#include <msp430.h>




///////////////////////////////////////////////////////////
/////////////           DEBUG LED            //////////////
///////////////////////////////////////////////////////////

#define LED_DEBUG_PORT P7OUT

#define LED_DEBUG_R_PIN BIT5
#define LED_DEBUG_G_PIN BIT6
#define LED_DEBUG_B_PIN BIT7


typedef enum _color3Enum
{
    OFF, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE
} color3Enum;


void led_debug_setColor(color3Enum color);

color3Enum led_debug_getColor();




///////////////////////////////////////////////////////////
/////////////       ADDRESSABLE LEDS         //////////////
///////////////////////////////////////////////////////////

#define LED_ADDRESSABLE_COUNT 6


#define LED_ADDRESSABLE_PORT P1OUT

#define LED_ADDRESSABLE_PIN BIT0


typedef struct _color24Struct
{
    char Red;
    char Green;
    char Blue;
} color24Struct;

static color24Struct led_addressable_colorArray[LED_ADDRESSABLE_COUNT];


void led_addressable_setColorRGB(int index, char red, char green, char blue);

void led_addressable_setColorHUE(int index, int hue);

color24Struct led_addressable_getColorRGB(int index);


void led_addressable_sendByte (unsigned char byte);
void led_addressable_sendRGB(color24Struct* color);
void led_addressable_sendData();

#define LED_ADDRESSABLE_SEND1 LED_ADDRESSABLE_PORT|=LED_ADDRESSABLE_PIN; _delay_cycles(8); LED_ADDRESSABLE_PORT&=~LED_ADDRESSABLE_PIN; _delay_cycles(2);
#define LED_ADDRESSABLE_SEND0 LED_ADDRESSABLE_PORT|=LED_ADDRESSABLE_PIN; _delay_cycles(2); LED_ADDRESSABLE_PORT&=~LED_ADDRESSABLE_PIN; _delay_cycles(8);
#define LED_ADDRESSABLE_STOP_DELAY _delay_cycles(4000);





#endif /* LED_H_ */
