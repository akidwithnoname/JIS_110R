/*
Copyright 2017 Yuki Sakatoi A.K.A. [null] <null.bin.pc@gmail.com>

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
#include "wait.h"
#include "led_def.h"



// STANDBY LED/s ----------------------------------------------------------------------------------------------------

void sleep_led_on(void)
{
    jis_110r_led_on_kana();
}



// STANDARD HID LEDs ------------------------------------------------------------------------------------------------
void led_set(uint8_t usb_led)
{

    // NUM LOCK
    if (usb_led & (1<<USB_LED_NUM_LOCK))
    {
        jis_110r_led_on_num_lock();
    }
    else
    {
        jis_110r_led_off_num_lock();
    }

    // SCROLL LOCK
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
    {
        jis_110r_led_on_scroll_lock();
    }
    else
    {
        jis_110r_led_off_scroll_lock();
    } 

    // CAPS LOCK
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
    {
        jis_110r_led_on_caps_lock();
    }
    else
    {
        jis_110r_led_off_caps_lock();
    }

    // KANA 
    if (usb_led & (1<<USB_LED_KANA))
    {
        jis_110r_led_on_kana();
    }
    else
    {
        jis_110r_led_off_kana();
    }   
}



// LAYER LEDs -------------------------------------------------------------------------------------------------------
void led_layer_set(uint32_t state) 
{
    // COMPATIBILITY MODE 
    // if either compatibility mode layeris enabled turn on SUPER key LED
    if ((1<<1 & state) != 0 || (1<<2 & state) != 0) {
        jis_110r_led_on_meta();
    }
    else
    {
        jis_110r_led_off_meta();
    }

    // FN
    if ((1<<6 & state) != 0 || (1<<7 & state) != 0 || (1<<8 & state) != 0 || (1<<9 & state) != 0) {
        jis_110r_led_on_fn();
    }
    else
    {
        jis_110r_led_off_fn();
    }

    // MODERN SCROLL LOCK [mouse wheel]
    if ((1<<5 & state) != 0)
    {
        jis_110r_led_on_scroll_lock();
    }
    else
    {
        jis_110r_led_off_scroll_lock();
    }

    // MOUSE KEYPAD
    if ((1<<4 & state) != 0) {
        jis_110r_led_on_keypad();
    }
    else
    {
        jis_110r_led_off_keypad();
    }
}
