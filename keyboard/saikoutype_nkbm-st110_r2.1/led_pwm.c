/*
Copyright 2018 Yuki Rea <null-src.com>

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
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdbool.h>
#include "led.h"
//#include "led_pwm.h"
//#include "host_driver.h"
//#include "rn42-bt-module.h"
//#include "lufa.h"

// TIMER --------------------------------------------------------------------------\

#define SLEEP_LED_TIMER_TOP F_CPU/(256*64)

void pwm_timer_init(void)
{
    TCCR1B |= _BV(WGM12);
    TCCR1B |= _BV(CS10);
    uint8_t sreg = SREG;
    cli();
    OCR1AH = (SLEEP_LED_TIMER_TOP>>8)&0xff;
    OCR1AL = SLEEP_LED_TIMER_TOP&0xff;
    SREG = sreg;
}
void pwm_timer_enable(void) { TIMSK1 |= _BV(OCIE1A); } 
void pwm_timer_disable(void) { TIMSK1 &= ~_BV(OCIE1A); }


// COUNTERS -----------------------------------------------------------------------\

uint16_t loading_animation_counter = 0;
uint16_t special_animation_counter = 0;
uint16_t typing_animation_counter = 0;
uint16_t keypress_animation_counter = 0;


// LED BRIGHTNESS [ 0 = 0% | 255 = 100% ] -----------------------------------------\

__attribute__((weak))
uint8_t led_brightness_level = 100;

__attribute__((weak))
uint8_t bare_led_brightness_level = 5;

__attribute__((weak))
uint8_t led_brightness_step = 25;

__attribute__((weak))
uint8_t led_brightness_step_highres = 5;

__attribute__((weak))
uint8_t led_brightness_highres_treshold = 25;

void led_brightness_min(void) { led_brightness_level = 0; }

void led_brightness_max(void) { led_brightness_level = 255; }



void led_brightness_up(void) {
    if ((255 - led_brightness_level) > led_brightness_step)
        if (led_brightness_level <= led_brightness_highres_treshold)
            { led_brightness_level = led_brightness_level + led_brightness_step_highres;}
        else
            { led_brightness_level = led_brightness_level + led_brightness_step; }
    else
        { led_brightness_max(); }
}



void led_brightness_down(void) {
    if ((255 - led_brightness_highres_treshold - led_brightness_level) < (255 - led_brightness_step))
        if (led_brightness_level <= led_brightness_highres_treshold)
            { led_brightness_level = led_brightness_level - led_brightness_step_highres;}
        else if ((led_brightness_level - led_brightness_step) <= led_brightness_highres_treshold)
            { led_brightness_level = led_brightness_highres_treshold; } 
        else
            { led_brightness_level = led_brightness_level - led_brightness_step; }
    else
        if ((255 - led_brightness_level) < (255 - led_brightness_step_highres))
            if (led_brightness_level <= led_brightness_highres_treshold)
                { led_brightness_level = led_brightness_level - led_brightness_step_highres;}
            else
                { led_brightness_min();}
       else
           { led_brightness_min();}
}



void led_brightness_up_highres(void) {
    if ((255 - led_brightness_level) > led_brightness_step_highres)
        { led_brightness_level = led_brightness_level + led_brightness_step_highres; }
    else
        { led_brightness_max(); }
}



void led_brightness_down_highres(void) {
    if ((255 - led_brightness_level) < (255 - led_brightness_step_highres))
        { led_brightness_level = led_brightness_level - led_brightness_step_highres;}
    else
        { led_brightness_min();}
}


// LED STATE BOOLEANS -------------------------------------------------------------\
note: will change booleans to bitwise operations for optimization reasons
static bool led_animation = true;
static bool led_indicators = false;
static bool kana_led_animation = false;
static bool kana_led_solid = false;
static bool meta_led_animation = false;
static bool meta_led_solid = false;
static bool fn_led_animation = false;
static bool fn_led_solid = false;
static bool num_lock_led_animation = false; 
static bool num_lock_led_solid = false; 
static bool keypad_led_animation = false; 
static bool keypad_led_solid = false; 
static bool caps_lock_led_animation = false; 
static bool caps_lock_led_solid = false; 
static bool scroll_lock_led_animation = false; 
static bool scroll_lock_led_solid = false; 
static bool usb_link_led_solid = false;
static bool center_led_solid = false;
static bool bt_link_led_solid = false;
static bool bt_nc_led_animation = false;
static bool usb_nc_led_animation = false; 
static bool special_led_animation = false;
static bool loading_led_animation = false;
static bool typing_led_animation = false;


// LED STATE SWITCHES -------------------------------------------------------------\

void keypad_led_animation_on(void) { keypad_led_animation = true; keypad_led_solid = false; }       
void keypad_led_animation_off(void) { keypad_led_animation = false; }
void keypad_led_solid_on(void) { keypad_led_solid = true; keypad_led_animation = false; }       
void keypad_led_solid_off(void) { keypad_led_solid = false; }
void scroll_lock_led_animation_on(void) { scroll_lock_led_animation = true; }       
void scroll_lock_led_animation_off(void) { scroll_lock_led_animation = false; }
void scroll_lock_led_solid_on(void) { scroll_lock_led_solid = true; }       
void scroll_lock_led_solid_off(void) { scroll_lock_led_solid = false; }
void caps_lock_led_animation_on(void) { caps_lock_led_animation = true; }       
void caps_lock_led_animation_off(void) { caps_lock_led_animation = false; }
void caps_lock_led_solid_on(void) { caps_lock_led_solid = true; }       
void caps_lock_led_solid_off(void) { caps_lock_led_solid = false; }
void num_lock_led_animation_on(void) { num_lock_led_animation = true; }       
void num_lock_led_animation_off(void) { num_lock_led_animation = false; }
void num_lock_led_solid_on(void) { num_lock_led_solid = true; }       
void num_lock_led_solid_off(void) { num_lock_led_solid = false; }
void fn_led_animation_on(void) { fn_led_animation = true; fn_led_solid = false;}
void fn_led_animation_off(void) { fn_led_animation = false; }
void fn_led_solid_on(void) { fn_led_solid = true; }
void fn_led_solid_off(void) { fn_led_solid = false; }
void meta_led_animation_on(void) { meta_led_animation = true; meta_led_solid = false; }
void meta_led_animation_off(void) { meta_led_animation = false; }
void meta_led_solid_on(void) { meta_led_solid = true; meta_led_animation = false; }
void meta_led_solid_off(void) { meta_led_solid = false; }
void kana_led_animation_on(void) { kana_led_animation = true; }
void kana_led_animation_off(void) { kana_led_animation = false; }
void kana_led_solid_on(void) { kana_led_solid = true; }
void kana_led_solid_off(void) { kana_led_solid = false; }
void special_led_animation_on(void) { special_led_animation = true; bt_link_led_solid = false; bt_nc_led_animation = false; usb_link_led_solid = false; usb_nc_led_animation = false; }
void special_led_animation_off(void) { special_led_animation = false; left_led_off(); center_led_off(); right_led_off(); }
void loading_led_animation_on(void) { loading_led_animation = true; bt_link_led_solid = false; bt_nc_led_animation = false; usb_link_led_solid = false; usb_nc_led_animation = false; }
void loading_led_animation_off(void) { loading_led_animation = false; left_led_off(); center_led_off(); right_led_off(); }
void typing_led_animation_on(void) { typing_led_animation = true; true; bt_link_led_solid = false; bt_nc_led_animation = false; usb_link_led_solid = false; usb_nc_led_animation = false; }
void typing_led_animation_off(void) { typing_led_animation = false; left_led_off(); center_led_off(); right_led_off(); }
void usb_nc_led_animation_on(void) { usb_nc_led_animation = true; usb_link_led_solid = false; bt_link_led_solid = false; bt_nc_led_animation = false; }       
void usb_nc_led_animation_off(void) { usb_nc_led_animation = false; left_led_off(); center_led_off(); right_led_off(); }
void bt_link_led_solid_on(void) { bt_link_led_solid = true; bt_nc_led_animation = false; usb_link_led_solid = false; usb_nc_led_animation = false;  }
void bt_link_led_solid_off(void) { bt_link_led_solid = false; }
void center_led_solid_on(void) { center_led_solid = true; }
void center_led_solid_off(void) { center_led_solid = false; }
void usb_link_led_solid_on(void) { usb_link_led_solid = true; usb_nc_led_animation = false; bt_link_led_solid = false; bt_nc_led_animation = false; }
void usb_link_led_solid_off(void) { usb_link_led_solid = false; }
void bt_nc_led_animation_on(void) { bt_nc_led_animation = true; bt_link_led_solid = false; usb_link_led_solid = false; usb_nc_led_animation = false; }
void bt_nc_led_animation_off(void) { bt_nc_led_animation = false; }
void led_indicators_on(void) { led_indicators = true; }
void led_indicators_off(void) { led_indicators = false; }
void led_animation_on(void) { led_animation = true; }
void led_animation_off(void) { led_animation = false; 
    keypad_led_off();
    meta_led_off();
    caps_lock_led_off();
    num_lock_led_off();
    kana_led_off();
    fn_led_off();
    scroll_lock_led_off();
}

// ANIMATION TABLES ---------------------------------------------------------------\
   [ 0 = 0% | 255 = 100% ]                                                         \
   0-5 for bare LEDs                                                               \
   0-255 for LEDs under keycaps                                                    \
   Maximum value of blinking_table determined by "led_brightness_level"            \

// BLINK ANIMATION TABLE
    static const uint16_t blinking_table[64] PROGMEM = {
    75,  255, 255, 255, 255, 75,  0,   0,   75,  255, 255, 255, 255, 75,  0,   0,
    75,  255, 255, 255, 255, 75,  0,   0,   75,  255, 255, 255, 255, 75,  0,   0,
    75,  255, 255, 255, 255, 75,  0,   0,   75,  255, 255, 255, 255, 75,  0,   0,
    75,  255, 255, 255, 255, 75,  0,   0,   75,  255, 255, 255, 255, 75,  0,   0
    };

// SLEEP ANIMATION TABLE
    static const uint8_t ping_table[64] PROGMEM = {
    1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
    1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
    6,   5,   4,   3,   2,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
    };

// SPECIAL ANIMATION TABLES
    // LEFT LED
    static const uint16_t special_left_table[64] PROGMEM = {
    0,   0,   1,   1,   1,   2,   2,   2,   3,   3,   3,   4,   4,   4,   3,   2,  
    1,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   1,   2,   4,   1,   0,   0,   0,   0
    };
    // CENTER LED
    static const uint16_t special_center_table[64] PROGMEM = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   1,   1,   1,   2,   2,   2,   3,   3,   3,   4,   4,   4,   3,   2,  
    1,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   1,   2,   4,   1,   0,   0,   0,   0,   0,   0
    }; 
    // RIGHT LED
    static const uint16_t special_right_table[64] PROGMEM = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   1,   1,   1,   2,   2,   2,   3,   3,   3,   4,   4,   4,   3,   2,  
    0,   0,   0,   0,   1,   2,   4,   1,   0,   0,   0,   0,   0,   0,   0,   0
    };

// LOADING ANIMATION TABLES
    // LEFT LED
    static const uint16_t loading_left_table[64] PROGMEM = {
    1,   1,   2,   2,   2,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,
    4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
    4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
    4,   4,   4,   3,   3,   2,   2,   1,   0,   0,   0,   0,   0,   0,   0,   0
    };
    // CENTER LED
    static const uint16_t loading_center_table[64] PROGMEM = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  
    1,   1,   2,   2,   2,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,
    4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
    4,   4,   4,   3,   3,   2,   2,   1,   0,   0,   0,   0,   0,   0,   0,   0
    };
    // RIGHT LED
    static const uint16_t loading_right_table[64] PROGMEM = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  
    1,   1,   2,   2,   2,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,
    4,   4,   4,   3,   3,   2,   2,   1,   0,   0,   0,   0,   0,   0,   0,   0
    };

// TYPING ANIMATION TABLES
    // LEFT LED
    static const uint16_t typing_left_table[64] PROGMEM = {
    4,   3,   3,   3,   2,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  
    4,   3,   3,   3,   2,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  
    4,   3,   3,   3,   2,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  
    4,   3,   3,   3,   2,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  
    };
    // CENTER LED
    static const uint16_t typing_center_table[64] PROGMEM = {
    0,   0,   0,   0,   0,   4,   3,   3,   3,   2,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   4,   3,   3,   3,   2,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   4,   3,   3,   3,   2,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   4,   3,   3,   3,   2,   1,   0,   0,   0,   0,   0
    }; 
    // RIGHT LED
    static const uint16_t typing_right_table[64] PROGMEM = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   4,   4,   3,   3,   2,   1,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   4,   4,   3,   3,   2,   1,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   4,   4,   3,   3,   2,   1,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   4,   4,   3,   3,   2,   1
    };


// SOFTWARE PWM -------------------------------------------------------------------\
                                                                                   \
    ______           ______           __                                           \
   |  ON  |___OFF___|  ON  |___OFF___|   ....                                      \
   |<-------------->|<-------------->|<- ....                                      \
       PWM period       PWM period                                                 \
                                                                                   \
   256              interrupts/period[resolution]                                  \
   64               periods/second[frequency]                                      \
   256*64           interrupts/second                                              \
   F_CPU/(256*64)   clocks/interrupt                                               \
                                                                                   \
                                                                                   \
   timer:1111 1111 1111 1111                                                       \
         \_____/\/ \_______/____  count(0-255)                                     \
            \    \______________  duration of step(4)                              \
             \__________________  index of step table(0-63)                        \



// TIMER 1 ------------------------------------------------------------------------\

ISR(TIMER1_COMPA_vect)
{
    static union {
        uint16_t row;
        struct {
            uint8_t count:8;
            uint8_t duration:1;
            uint8_t index:6;
        } pwm;
    } timer = { .row = 0 };
    timer.row++;


if (led_animation) {
      
// IN-KEY LEDS --------------------------------------------------------------------\

    // META    
    if (meta_led_animation) {
        if (timer.pwm.count == 0 && pgm_read_byte(&blinking_table[timer.pwm.index]) != 0 && led_brightness_level != 0) 
            { meta_led_on(); }
        if (pgm_read_byte(&blinking_table[timer.pwm.index]) >= led_brightness_level && timer.pwm.count == led_brightness_level)
            { meta_led_off(); }
        else if (timer.pwm.count == pgm_read_byte(&blinking_table[timer.pwm.index]))
            { meta_led_off(); }
    }
    if (meta_led_solid) {
        if (timer.pwm.count == 0 && led_brightness_level != 0) 
            { meta_led_on(); }
        if (timer.pwm.count == led_brightness_level)
            { meta_led_off(); }
    }



    // CAPS LOCK    
    if (caps_lock_led_animation) {
        if (timer.pwm.count == 0 && pgm_read_byte(&blinking_table[timer.pwm.index]) != 0 && led_brightness_level != 0) 
            { caps_lock_led_on(); }
        if (pgm_read_byte(&blinking_table[timer.pwm.index]) >= led_brightness_level && timer.pwm.count == led_brightness_level)
            { caps_lock_led_off(); }
        else if (timer.pwm.count == pgm_read_byte(&blinking_table[timer.pwm.index]))
            { caps_lock_led_off(); }
    }
    if (caps_lock_led_solid) {
        if (timer.pwm.count == 0 && led_brightness_level != 0) 
            { caps_lock_led_on(); }
        if (timer.pwm.count == led_brightness_level)
            { caps_lock_led_off(); }
    }



    // NUM LOCK    
    if (num_lock_led_animation) {
        if (timer.pwm.count == 0 && pgm_read_byte(&blinking_table[timer.pwm.index]) != 0 && led_brightness_level !=0 ) 
            { num_lock_led_on(); }
        if (pgm_read_byte(&blinking_table[timer.pwm.index]) >= led_brightness_level && timer.pwm.count == led_brightness_level)
            { num_lock_led_off(); }
        else if (timer.pwm.count == pgm_read_byte(&blinking_table[timer.pwm.index]))
            { num_lock_led_off(); }
    }
    if (num_lock_led_solid) {
       if (timer.pwm.count == 0 && led_brightness_level != 0) 
            { num_lock_led_on(); }
       if (timer.pwm.count == led_brightness_level)
            { num_lock_led_off(); }
    }

    

    // KEYPAD    
    if (keypad_led_animation) {
        if (timer.pwm.count == 0 && pgm_read_byte(&blinking_table[timer.pwm.index]) != 0 && led_brightness_level != 0) 
            { keypad_led_on(); }
        if (pgm_read_byte(&blinking_table[timer.pwm.index]) >= led_brightness_level && timer.pwm.count == led_brightness_level)
            { keypad_led_off(); }
        else if (timer.pwm.count == pgm_read_byte(&blinking_table[timer.pwm.index]))
            { keypad_led_off(); }
    }
    else if (keypad_led_solid) {
        if (timer.pwm.count == 0 && led_brightness_level != 0) 
            { keypad_led_on(); }
        if (timer.pwm.count == led_brightness_level)
            { keypad_led_off(); }
    }



    // SCROLL LOCK    
    if (scroll_lock_led_animation) {
        if (timer.pwm.count == 0 && pgm_read_byte(&blinking_table[timer.pwm.index]) != 0 && led_brightness_level != 0)
            { scroll_lock_led_on(); }
        if (pgm_read_byte(&blinking_table[timer.pwm.index]) >= led_brightness_level && timer.pwm.count == led_brightness_level)
            { scroll_lock_led_off(); }
        else if (timer.pwm.count == pgm_read_byte(&blinking_table[timer.pwm.index]))
            { scroll_lock_led_off(); }
    }
    else if (scroll_lock_led_solid) {
        if (timer.pwm.count == 0 && led_brightness_level != 0) 
            { scroll_lock_led_on(); }
        if (timer.pwm.count == led_brightness_level)
            { scroll_lock_led_off(); }
    }

  
   
    // FN 
    if (fn_led_animation) {
        if (timer.pwm.count == 0 && pgm_read_byte(&blinking_table[timer.pwm.index]) != 0 && led_brightness_level != 0)
            { fn_led_on(); }
        if (pgm_read_byte(&blinking_table[timer.pwm.index]) >= led_brightness_level && timer.pwm.count == led_brightness_level)
            { fn_led_off(); }
        if (timer.pwm.count == pgm_read_byte(&blinking_table[timer.pwm.index]))
            { fn_led_off(); }
    }
    if (fn_led_solid) {
        if (timer.pwm.count == 0 && led_brightness_level != 0) 
            { fn_led_on(); }
        if (timer.pwm.count == led_brightness_level)
            { fn_led_off(); }
    }



    // KANA    
    if (kana_led_animation) {
        if (timer.pwm.count == 0 && pgm_read_byte(&blinking_table[timer.pwm.index]) != 0 && led_brightness_level != 0) 
            { kana_led_on(); }
        if (pgm_read_byte(&blinking_table[timer.pwm.index]) >= led_brightness_level && timer.pwm.count == led_brightness_level)
            { kana_led_off(); }
        if (timer.pwm.count == pgm_read_byte(&blinking_table[timer.pwm.index]))
            { kana_led_off(); }
    }
    if (kana_led_solid) {
        if (timer.pwm.count == 0 && led_brightness_level != 0) 
            { kana_led_on(); }
        if (timer.pwm.count == led_brightness_level)
            { kana_led_off(); }
    }


// CASE INDICATORS ----------------------------------------------------------------\

    // SPECIAL ANIMATION
    if (special_led_animation) {
	if (special_animation_counter == 0) { timer.row = 0; }
        if (timer.pwm.count == 0 && pgm_read_byte(&special_left_table[timer.pwm.index]) != 0)
            { left_led_on(); }
        if (timer.pwm.count == pgm_read_byte(&special_left_table[timer.pwm.index]))
            { left_led_off(); }
        if (timer.pwm.count == 0 && pgm_read_byte(&special_center_table[timer.pwm.index]) != 0)
            { center_led_on(); }
        if (timer.pwm.count == pgm_read_byte(&special_center_table[timer.pwm.index]))
            { center_led_off(); }
        if (timer.pwm.count == 0 && pgm_read_byte(&special_right_table[timer.pwm.index]) != 0)
            { right_led_on(); }
        if (timer.pwm.count == pgm_read_byte(&special_right_table[timer.pwm.index]))
            { right_led_off(); }
	special_animation_counter++;
    }
    else { special_animation_counter = 0; }


    // LOADING ANIMATION
    if (loading_led_animation) {
        if (loading_animation_counter == 0) {  timer.row = 0; }    
        if (timer.pwm.count == 0 && pgm_read_byte(&loading_left_table[timer.pwm.index]) != 0)
            { left_led_on(); }
        if (timer.pwm.count == pgm_read_byte(&loading_left_table[timer.pwm.index]))
            { left_led_off(); }
        if (timer.pwm.count == 0 && pgm_read_byte(&loading_center_table[timer.pwm.index]) != 0)
            { center_led_on(); }
        if (timer.pwm.count == pgm_read_byte(&loading_center_table[timer.pwm.index]))
            { center_led_off(); }
        if (timer.pwm.count == 0 && pgm_read_byte(&loading_right_table[timer.pwm.index]) != 0)
            { right_led_on(); }
        if (timer.pwm.count == pgm_read_byte(&loading_right_table[timer.pwm.index]))
           { right_led_off(); }
	loading_animation_counter++;
	if (loading_animation_counter >= 32500) {
	    loading_animation_counter = 0;
	    loading_led_animation_off(); }
    }


    // TYPING ANIMATION
    if (typing_led_animation) {
	if (typing_animation_counter == 0) { timer.row = 0; }
        if (timer.pwm.count == 0 && pgm_read_byte(&typing_left_table[timer.pwm.index]) != 0)
            { left_led_on(); }
        if (timer.pwm.count == pgm_read_byte(&typing_left_table[timer.pwm.index]))
            { left_led_off(); }
        if (timer.pwm.count == 0 && pgm_read_byte(&typing_center_table[timer.pwm.index]) != 0)
            { center_led_on(); }
        if (timer.pwm.count == pgm_read_byte(&typing_center_table[timer.pwm.index]))
            { center_led_off(); }
        if (timer.pwm.count == 0 && pgm_read_byte(&typing_right_table[timer.pwm.index]) != 0)
            { right_led_on(); }
        if (timer.pwm.count == pgm_read_byte(&typing_right_table[timer.pwm.index]))
            { right_led_off(); }
	typing_animation_counter++;
    }
    else { typing_animation_counter = 0; }
}
else { led_animation_off(); }


    // SINGLE INDICATORS
    if (!typing_led_animation && !loading_led_animation && !special_led_animation && led_indicators) {
        if (bt_link_led_solid) {
            if (timer.pwm.count == 0 && bare_led_brightness_level != 0) 
                { left_led_on(); }
            if (timer.pwm.count == bare_led_brightness_level)
                { left_led_off(); }
         }
        else if (bt_nc_led_animation) {
            if (timer.pwm.count == 0 && pgm_read_byte(&ping_table[timer.pwm.index]) != 0 && led_brightness_level != 0)
                { left_led_on(); }
            if (pgm_read_byte(&ping_table[timer.pwm.index]) >= led_brightness_level && timer.pwm.count == led_brightness_level)
                { left_led_off(); }
            if (timer.pwm.count == pgm_read_byte(&ping_table[timer.pwm.index]))
                { left_led_off(); }
        }
        else {
            left_led_off();
        }
        if (usb_link_led_solid) {
            if (timer.pwm.count == 0 && bare_led_brightness_level != 0) 
                { right_led_on(); }
            if (timer.pwm.count == bare_led_brightness_level)
                { right_led_off(); }
        }
        else if (usb_nc_led_animation) {
            if (timer.pwm.count == 0 && pgm_read_byte(&ping_table[timer.pwm.index]) != 0)
                { sleep_led_on(); }
            if (timer.pwm.count == pgm_read_byte(&ping_table[timer.pwm.index]))
                { sleep_led_off(); }
        }
        else {
            right_led_off();
        }
    } 
}
