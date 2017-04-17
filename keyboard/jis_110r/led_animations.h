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



#include <util/delay.h> 
#include "wait.h"
#include "led_definitions.h"



// FADES IN --------------------------------------------------------------------------------------------------

static void jis_110r_led_fadein_right(void)
{
    for (int x = 0; x<50; x++){
        jis_110r_led_on_right();
            for (int y = x; y>0; y--){
            _delay_us(1);
            }
        jis_110r_led_off_right();
        _delay_ms(8);
        }   
}

static void jis_110r_led_fadein_ping_right(void)
{
    for (int x = 0; x<100; x++){
        jis_110r_led_on_right();
            for (int y = x/10; y>0; y--){
            _delay_us(0.1);
            }
        jis_110r_led_off_right();
        _delay_ms(8);
        }   
}

static void jis_110r_led_fadein_center(void)
{
    for (int x = 0; x<50; x++){
        jis_110r_led_on_center();
            for (int y = x; y>0; y--){
            _delay_us(1);
            }
        jis_110r_led_off_center();
        _delay_ms(8);
        }   
}

static void jis_110r_led_fadein_left(void)
{
    for (int x = 0; x<50; x++){
        jis_110r_led_on_left();
            for (int y = x; y>0; y--){
            _delay_us(1);
            }
        jis_110r_led_off_left();
        _delay_ms(8);
        }   
}

static void jis_110r_led_fadein_outer(void)
{
    for (int x = 0; x<50; x++){
        jis_110r_led_on_left();
        jis_110r_led_on_right();
            for (int y = x; y>0; y--){
            _delay_us(1);
            }
        jis_110r_led_off_left();
        jis_110r_led_off_right();
        _delay_ms(8);
        }   
}


// FADE OUTs --------------------------------------------------------------------------------------------------
static void jis_110r_led_fadeout_right(void)
{ 
    for (int x = 50; x>0; x--){
        jis_110r_led_on_right();
            for (int y = x; y>0; y--){
            _delay_us(1);
            }
        jis_110r_led_off_right();
        _delay_ms(8);
        }   
}

static void jis_110r_led_fadeout_center(void)
{ 
    for (int x = 50; x>0; x--){
        jis_110r_led_on_center();
            for (int y = x; y>0; y--){
            _delay_us(1);
            }
        jis_110r_led_off_center();
        _delay_ms(8);
        }   
}

static void jis_110r_led_fadeout_left(void)
{ 
    for (int x = 50; x>0; x--){
        jis_110r_led_on_left();
            for (int y = x; y>0; y--){
            _delay_us(1);
            }
        jis_110r_led_off_left();
        _delay_ms(8);
        }   
}

static void jis_110r_led_fadeout_outer(void)
{ 
    for (int x = 50; x>0; x--){
        jis_110r_led_on_left();
        jis_110r_led_on_right();
            for (int y = x; y>0; y--){
            _delay_us(1);
            }
        jis_110r_led_off_left();
        jis_110r_led_off_right();
        _delay_ms(8);
        }   
}



// ANIMATION 1 --------------------------------------------------------------------------------------------
static void jis_110r_led_animation_1(void)
{
    jis_110r_led_fadein_left();
    jis_110r_led_fadeout_left();
    jis_110r_led_fadein_center();
    jis_110r_led_fadeout_center();
    jis_110r_led_fadein_right();
    jis_110r_led_fadeout_right();
    jis_110r_led_fadein_center();
    jis_110r_led_fadeout_center();
    jis_110r_led_fadein_left();
    jis_110r_led_fadeout_left();
}


// ANIMATION 2 --------------------------------------------------------------------------------------------

static void jis_110r_led_animation_2(void)
{
    jis_110r_led_fadein_outer();
    jis_110r_led_fadeout_outer();
    wait_ms(100);
    jis_110r_led_fadein_center();
    jis_110r_led_fadeout_center();
}

// ANIMATION SLEEP -----------------------------------------------------------------------------------------
static void jis_110r_led_animation_sleep(void)
{
    jis_110r_led_fadein_ping_right();
    jis_110r_led_fadeout_right();
}
