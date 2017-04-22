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
#include "led_pwm.h"
#include <avr/interrupt.h>



// LED DEFINITION ---------------------------------------------------------------------------------------------------
void fn_led_on(void)             { DDRE |=  (1<<6); PORTE |=  (1<<6); }
void fn_led_off(void)            { DDRE &= ~(1<<6); PORTE &= ~(1<<6); }

void keypad_led_on(void)         { DDRA |=  (1<<2); PORTA |=  (1<<2); }
void keypad_led_off(void)        { DDRA &= ~(1<<2); PORTA &= ~(1<<2); }

void scroll_lock_led_on(void)    { DDRA |=  (1<<1); PORTA |=  (1<<1); }
void scroll_lock_led_off(void)   { DDRA &= ~(1<<1); PORTA &= ~(1<<1); }

void num_lock_led_on(void)       { DDRE |=  (1<<7); PORTE |=  (1<<7); }
void num_lock_led_off(void)      { DDRE &= ~(1<<7); PORTE &= ~(1<<7); }

void caps_lock_led_on(void)      { DDRE |=  (1<<1); PORTE |=  (1<<1); }
void caps_lock_led_off(void)     { DDRE &= ~(1<<1); PORTE &= ~(1<<1); }

void kana_led_on(void)           { DDRA |=  (1<<0); PORTA |=  (1<<0); }
void kana_led_off(void)          { DDRA &= ~(1<<0); PORTA &= ~(1<<0); }

void meta_led_on(void)           { DDRE |=  (1<<0); PORTE |=  (1<<0); }
void meta_led_off(void)          { DDRE &= ~(1<<0); PORTE &= ~(1<<0); }

void left_led_on(void)           { DDRA |=  (1<<5); PORTA |=  (1<<5); }
void left_led_off(void)          { DDRA &= ~(1<<5); PORTA &= ~(1<<5); }

void center_led_on(void)         { DDRA |=  (1<<3); PORTA |=  (1<<3); }
void center_led_off(void)        { DDRA &= ~(1<<3); PORTA &= ~(1<<3); }

void right_led_on(void)          { DDRA |=  (1<<6); PORTA |=  (1<<6); }
void right_led_off(void)         { DDRA &= ~(1<<6); PORTA &= ~(1<<6); }

void sleep_led_on(void)          { right_led_on(); }
void sleep_led_off(void)         { right_led_off(); }



// LED BRIGHTNESS [ 0 - 255 ] ---------------------------------------------------------------------------------------
uint8_t led_brightness_level = 75;

 

// STANDARD HID LEDs ------------------------------------------------------------------------------------------------
void led_set(uint8_t usb_led)
{
    // NUM LOCK
    if (usb_led & (1<<USB_LED_NUM_LOCK))
    {
        num_lock_led_solid_on();
    }
    else
    {
        num_lock_led_solid_off();
        num_lock_led_off();
    }

    // SCROLL LOCK
    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
    {
        scroll_lock_led_solid_on();
    }
    else
    {
        scroll_lock_led_solid_off();
        scroll_lock_led_off(); 
    } 

    // CAPS LOCK
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
    {
        caps_lock_led_solid_on();
    }
    else
    {
        caps_lock_led_solid_off();
        caps_lock_led_off();
    }

    // KANA 
    if (usb_led & (1<<USB_LED_KANA))
    {
        kana_led_solid_on();
    }
    else
    {
        kana_led_solid_off();
        kana_led_off();
    }   
}



// LAYER LEDs -------------------------------------------------------------------------------------------------------
void led_layer_set(uint32_t state) 
{
    // COMPATIBILITY MODE 
    // if either compatibility mode layeris enabled turn on SUPER key LED
    if ((1<<1 & state) != 0 || (1<<2 & state) != 0) {
        meta_led_solid_on();
    }
    else
    {
        meta_led_solid_off();
        meta_led_off();
    }

    // FN [ 6 & 8 = momentary ] [ 7 & 9 = toggle ]
    if ((1<<6 & state) != 0 || (1<<8 & state) != 0) {
        fn_led_animation_on();
    }
    else if ((1<<7 & state) != 0 || (1<<9 & state) !=0) {
        fn_led_solid_on(); 
    }
    else
    {
        fn_led_animation_off(); 
        fn_led_solid_off();
        fn_led_off();
    }

    //PASSWORD LAYER
    if ((1<<15 & state) != 0)
    {
        special_led_animation_on();
    }
    else
    {
        special_led_animation_off();
    }

    // MODERN SCROLL LOCK [mouse wheel]
    if ((1<<5 & state) != 0)
    {
        scroll_lock_led_animation_on();
    }
    else
    {
        scroll_lock_led_animation_off();
        scroll_lock_led_off(); 
    }

    // KEYPAD
    if ((1<<3 & state) != 0 && (1<<4 & state) == 0) {
        keypad_led_off();
        keypad_led_solid_off();
        keypad_led_animation_on();
    }
    else if ((1<<3 & state) != 0 && (1<<4 & state) != 0) {
        keypad_led_off();
        keypad_led_solid_off();
        keypad_led_animation_on();
    }
    else if ((1<<3 & state) == 0  && (1<<4 & state) != 0) {
        keypad_led_animation_off();
        keypad_led_solid_off();
        keypad_led_solid_on();
    }    
    else {
        keypad_led_off();
        keypad_led_solid_off();
        keypad_led_animation_off();
    }       
}
