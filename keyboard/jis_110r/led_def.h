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
inline void jis_110r_led_on_num_lock(void)      { DDRE |= (1<<7); PORTE |= (1<<7); }
inline void jis_110r_led_on_scroll_lock(void)   { DDRA |= (1<<1); PORTA |= (1<<1); }
inline void jis_110r_led_on_caps_lock(void)     { DDRE |= (1<<1); PORTE |= (1<<1); }
inline void jis_110r_led_on_kana(void)          { DDRA |= (1<<0); PORTA |= (1<<0); }
inline void jis_110r_led_on_fn(void)            { DDRE |= (1<<6); PORTE |= (1<<6); }
inline void jis_110r_led_on_meta(void)          { DDRE |= (1<<0); PORTE |= (1<<0); }
inline void jis_110r_led_on_keypad(void)        { DDRA |= (1<<2); PORTA |= (1<<2); }



// LED OFF ---------------------------------------------------------------------------------------------------------
inline void jis_110r_led_off_num_lock(void)     { DDRE &= ~(1<<7); PORTE &= ~(1<<7); }
inline void jis_110r_led_off_scroll_lock(void)  { DDRA &= ~(1<<1); PORTA &= ~(1<<1); }
inline void jis_110r_led_off_caps_lock(void)    { DDRE &= ~(1<<1); PORTE &= ~(1<<1); }
inline void jis_110r_led_off_kana(void)         { DDRA &= ~(1<<0); PORTA &= ~(1<<0); }
inline void jis_110r_led_off_fn(void)           { DDRE &= ~(1<<6); PORTE &= ~(1<<6); }
inline void jis_110r_led_off_meta(void)         { DDRE &= ~(1<<0); PORTE &= ~(1<<0); }
inline void jis_110r_led_off_keypad(void)       { DDRA &= ~(1<<2); PORTA &= ~(1<<2); }



// ALL LEDs ON -----------------------------------------------------------------------------------------------------
inline void jis_110r_led_on_all(void)
{
jis_110r_led_on_num_lock();   
jis_110r_led_on_scroll_lock();
jis_110r_led_on_caps_lock();  
jis_110r_led_on_kana();       
jis_110r_led_on_fn();         
jis_110r_led_on_meta();       
jis_110r_led_on_keypad();
}



// ALL LEDs OFF ----------------------------------------------------------------------------------------------------
inline void jis_110r_led_off_all(void)
{
jis_110r_led_off_num_lock();   
jis_110r_led_off_scroll_lock();
jis_110r_led_off_caps_lock();  
jis_110r_led_off_kana();       
jis_110r_led_off_fn();         
jis_110r_led_off_meta();       
jis_110r_led_off_keypad();
}


// LOADING ANIMATION -----------------------------------------------------------------------------------------------
inline void jis_110r_loading_animation(void)
{
    jis_110r_led_on_caps_lock();
    wait_ms(150);
    jis_110r_led_on_meta();
    wait_ms(250);
    jis_110r_led_on_kana();
    wait_ms(150);
    jis_110r_led_on_fn();
    wait_ms(160);
    jis_110r_led_off_all();
    wait_ms(300);
}

