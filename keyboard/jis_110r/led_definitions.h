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


#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

 

// LED ON ----------------------------------------------------------------------------------------------------------
static void jis_110r_led_on_num_lock(void)     { DDRE |= (1<<7); PORTE |= (1<<7); }
static void jis_110r_led_on_scroll_lock(void)  { DDRA |= (1<<1); PORTA |= (1<<1); }
static void jis_110r_led_on_caps_lock(void)    { DDRE |= (1<<1); PORTE |= (1<<1); }
static void jis_110r_led_on_kana(void)         { DDRA |= (1<<0); PORTA |= (1<<0); }
static void jis_110r_led_on_fn(void)           { DDRE |= (1<<6); PORTE |= (1<<6); }
static void jis_110r_led_on_meta(void)         { DDRE |= (1<<0); PORTE |= (1<<0); }
static void jis_110r_led_on_keypad(void)       { DDRA |= (1<<2); PORTA |= (1<<2); }
static void jis_110r_led_on_left(void)         { DDRA |= (1<<5); PORTA |= (1<<5); }
static void jis_110r_led_on_center(void)       { DDRA |= (1<<3); PORTA |= (1<<3); }
static void jis_110r_led_on_right(void)        { DDRA |= (1<<6); PORTA |= (1<<6); }



// LED OFF ---------------------------------------------------------------------------------------------------------
static void jis_110r_led_off_num_lock(void)    { DDRE &= ~(1<<7); PORTE &= ~(1<<7); }
static void jis_110r_led_off_scroll_lock(void) { DDRA &= ~(1<<1); PORTA &= ~(1<<1); }
static void jis_110r_led_off_caps_lock(void)   { DDRE &= ~(1<<1); PORTE &= ~(1<<1); }
static void jis_110r_led_off_kana(void)        { DDRA &= ~(1<<0); PORTA &= ~(1<<0); }
static void jis_110r_led_off_fn(void)          { DDRE &= ~(1<<6); PORTE &= ~(1<<6); }
static void jis_110r_led_off_meta(void)        { DDRE &= ~(1<<0); PORTE &= ~(1<<0); }
static void jis_110r_led_off_keypad(void)      { DDRA &= ~(1<<2); PORTA &= ~(1<<2); }
static void jis_110r_led_off_left(void)        { DDRA &= ~(1<<5); PORTA &= ~(1<<5); }
static void jis_110r_led_off_center(void)      { DDRA &= ~(1<<3); PORTA &= ~(1<<3); }
static void jis_110r_led_off_right(void)       { DDRA &= ~(1<<6); PORTA &= ~(1<<6); }



// ALL LEDs ON -----------------------------------------------------------------------------------------------------
static void jis_110r_led_on_all(void)
{
jis_110r_led_on_num_lock();   
jis_110r_led_on_scroll_lock();
jis_110r_led_on_caps_lock();  
jis_110r_led_on_kana();       
jis_110r_led_on_fn();         
jis_110r_led_on_meta();       
jis_110r_led_on_keypad();
jis_110r_led_on_right();
jis_110r_led_on_center();
jis_110r_led_on_left();
}



// ALL LEDs OFF ----------------------------------------------------------------------------------------------------
static void jis_110r_led_off_all(void)
{
jis_110r_led_off_num_lock();   
jis_110r_led_off_scroll_lock();
jis_110r_led_off_caps_lock();  
jis_110r_led_off_kana();       
jis_110r_led_off_fn();         
jis_110r_led_off_meta();       
jis_110r_led_off_keypad();
jis_110r_led_off_right();
jis_110r_led_off_center();
jis_110r_led_off_left();
}
