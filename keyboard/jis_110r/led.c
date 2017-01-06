/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/io.h>
#include "stdint.h"
#include "led.h"

// STANDARD HID LED -------------------------------------------
void led_set(uint8_t usb_led)
{
// NUM LOCK
    if (usb_led & (1<<USB_LED_NUM_LOCK))
    {
        DDRE |= (1<<7);
        PORTE |= (1<<7);
    }
    else
    {
        DDRE &= ~(1<<7);
        PORTE &= ~(1<<7);
    }

// SCROLL LOCK
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
    {
        DDRA |= (1<<1);
        PORTA |= (1<<1);
    }
    else
    {
        DDRA &= ~(1<<1);
        PORTA &= ~(1<<1);
    }

// CAPS LOCK
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
    {
        DDRE |= (1<<1);
        PORTE |= (1<<1);
    }
    else
    {
        DDRE &= ~(1<<1);
        PORTE &= ~(1<<1);
    }
// KANA 
    if (usb_led & (1<<USB_LED_KANA))
    {
        DDRA |= (1<<0);
        PORTA |= (1<<0);
    }
    else
    {
        DDRA &= ~(1<<0);
        PORTA &= ~(1<<0);
    }
}

// LAYER LED -------------------------------------------
void led_layer_set(uint32_t state) {
// GUI 
    if ((1<<1 & state) != 0 || (1<<2 & state) != 0) {
        DDRE |= (1<<0);
        PORTE |= (1<<0);
    }
    else
    {
        DDRE &= ~(1<<0);
        PORTE &= ~(1<<0);
    }
// FN
    if ((1<<5 & state) != 0) {
        DDRE |= (1<<6);
        PORTE |= (1<<6);
    }
    else
    {
        DDRE &= ~(1<<6);
        PORTE &= ~(1<<6);
    }
// MOUSE & HEX KEYPAD
    if ((1<<4 & state) != 0 || (1<<3 & state) != 0) {
        DDRA |= (1<<2);
        PORTA |= (1<<2);
        //DDRE &= ~(1<<7);
        //PORTE &= ~(1<<7);
    }
    else
    {
        DDRA &= ~(1<<2);
        PORTA &= ~(1<<2);
    }
} 
