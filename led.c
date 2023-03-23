/****************************************************************************************\
 * Project: Nixie Clock
 * File: C:\Users\jschaller\OneDrive\Beruflich\ETH\Projekte\Sem 3\Nixie_Clock\V1_1_0\SW\Nixie_Clock_Code\led.c
 * Author: Joel Schaller
 * Date: 02.02.2023
 * Version: 1.1.0
 * Description:
 * controls for the leds
\****************************************************************************************/


#include "led.h"

#include <msp430.h>



///////////////////////////////////////////////////////////
/////////////           DEBUG LED            //////////////
///////////////////////////////////////////////////////////


void led_debug_setColor(color3Enum color)
{
    switch (color)
    {
        case OFF:
            LED_DEBUG_PORT |= (LED_DEBUG_R_PIN | LED_DEBUG_G_PIN | LED_DEBUG_B_PIN);
            break;
        case RED:
            LED_DEBUG_PORT |= (LED_DEBUG_G_PIN | LED_DEBUG_B_PIN);
            LED_DEBUG_PORT &= ~(LED_DEBUG_R_PIN);
            break;
        case GREEN:
            LED_DEBUG_PORT |= (LED_DEBUG_R_PIN | LED_DEBUG_B_PIN);
            LED_DEBUG_PORT &= ~(LED_DEBUG_G_PIN);
            break;
        case BLUE:
            LED_DEBUG_PORT |= (LED_DEBUG_R_PIN | LED_DEBUG_G_PIN);
            LED_DEBUG_PORT &= ~(LED_DEBUG_B_PIN);
            break;
        case YELLOW:
            LED_DEBUG_PORT |= (LED_DEBUG_B_PIN );
            LED_DEBUG_PORT &= ~(LED_DEBUG_R_PIN | LED_DEBUG_G_PIN);
            break;
        case MAGENTA:
            LED_DEBUG_PORT |= (LED_DEBUG_G_PIN );
            LED_DEBUG_PORT &= ~(LED_DEBUG_R_PIN | LED_DEBUG_B_PIN);
            break;
        case CYAN:
            LED_DEBUG_PORT |= (LED_DEBUG_R_PIN );
            LED_DEBUG_PORT &= ~(LED_DEBUG_G_PIN | LED_DEBUG_B_PIN);
            break;
        case WHITE:
            LED_DEBUG_PORT &= ~(LED_DEBUG_R_PIN | LED_DEBUG_G_PIN | LED_DEBUG_B_PIN);
            break;
        default:
            errorHandler();
    }

    return;
}



color3Enum led_debug_getColor()
{
    switch(LED_DEBUG_PORT & (LED_DEBUG_R_PIN | LED_DEBUG_G_PIN | LED_DEBUG_B_PIN))
    {
        case 0xE0: return OFF;
        case 0xC0: return RED;
        case 0xA0: return GREEN;
        case 0x60: return BLUE;
        case 0x80: return YELLOW;
        case 0x40: return MAGENTA;
        case 0x20: return CYAN;
        case 0x00: return WHITE;
    }

    errorHandler();
    return OFF;
}




///////////////////////////////////////////////////////////
/////////////       ADDRESSABLE LEDS         //////////////
///////////////////////////////////////////////////////////


void led_addressable_setColorRGB(int index, char red, char green, char blue)
{
    led_addressable_colorArray[index].Red = red;
    led_addressable_colorArray[index].Green = green;
    led_addressable_colorArray[index].Blue = blue;
}

void led_addressable_setColorHUE(int index, int hue)
{
    if(hue >= 0 && hue < 256)
    {
        led_addressable_colorArray[index].Red = 0xFF;
        led_addressable_colorArray[index].Green = hue;
        led_addressable_colorArray[index].Blue = 0x00;

        return;
    }
    else if(hue >= 256 && hue < 512)
    {
        led_addressable_colorArray[index].Red = 0xFF - (hue-256);
        led_addressable_colorArray[index].Green = 0xFF;
        led_addressable_colorArray[index].Blue = 0x00;

        return;
    }
    else if(hue >= 512 && hue < 768)
    {
        led_addressable_colorArray[index].Red = 0x00;
        led_addressable_colorArray[index].Green = 0xFF;
        led_addressable_colorArray[index].Blue = (hue-512);

        return;
    }
    else if(hue >= 768 && hue < 1024)
    {
        led_addressable_colorArray[index].Red = 0x00;
        led_addressable_colorArray[index].Green = 0xFF - (hue-768);
        led_addressable_colorArray[index].Blue = 0xFF;

        return;
    }
    else if(hue >= 1024 && hue < 1280)
    {
        led_addressable_colorArray[index].Red = (hue-1024);
        led_addressable_colorArray[index].Green = 0x00;
        led_addressable_colorArray[index].Blue = 0xFF;

        return;
    }
    else if(hue >= 1280 && hue < 1536)
    {
        led_addressable_colorArray[index].Red = 0xFF;
        led_addressable_colorArray[index].Green = 0x00;
        led_addressable_colorArray[index].Blue = 0xFF - (hue-1280);

        return;
    }
}

color24Struct led_addressable_getColorRGB(int index)
{
    return led_addressable_colorArray[index];
}


void led_addressable_sendByte(unsigned char byte)
{
    if (byte & 0b10000000) { LED_ADDRESSABLE_SEND1; } else { LED_ADDRESSABLE_SEND0; }
    if (byte & 0b01000000) { LED_ADDRESSABLE_SEND1; } else { LED_ADDRESSABLE_SEND0; }
    if (byte & 0b00100000) { LED_ADDRESSABLE_SEND1; } else { LED_ADDRESSABLE_SEND0; }
    if (byte & 0b00010000) { LED_ADDRESSABLE_SEND1; } else { LED_ADDRESSABLE_SEND0; }
    if (byte & 0b00001000) { LED_ADDRESSABLE_SEND1; } else { LED_ADDRESSABLE_SEND0; }
    if (byte & 0b00000100) { LED_ADDRESSABLE_SEND1; } else { LED_ADDRESSABLE_SEND0; }
    if (byte & 0b00000010) { LED_ADDRESSABLE_SEND1; } else { LED_ADDRESSABLE_SEND0; }
    if (byte & 0b00000001) { LED_ADDRESSABLE_SEND1; } else { LED_ADDRESSABLE_SEND0; }
}

void led_addressable_sendRGB(color24Struct* color)
{
    led_addressable_sendByte(color->Green);
    led_addressable_sendByte(color->Red);
    led_addressable_sendByte(color->Blue);
}

void led_addressable_sendData()
{
    int i = 0;

    for(i = 0; i < LED_ADDRESSABLE_COUNT; i++)
    {
        led_addressable_sendRGB(&led_addressable_colorArray[i]);
    }

    LED_ADDRESSABLE_STOP_DELAY;
}









