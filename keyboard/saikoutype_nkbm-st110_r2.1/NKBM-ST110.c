/*
Copyright 2018 Yuki Sakatoi A.K.A. [null] <null.bin.pc@gmail.com>

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

#include <stdbool.h>
#include "actionmap.h"
#include "action_code.h"
#include "NKBM-ST110.h"
#include "action.h"
#include "action_layer.h"
#include "command.h"
#include "action_util.h"
#include "led.h"
#include "led_pwm.h"
#include <string.h>
#include "debug.h"
#include "wait.h"
#include "host.h"
#include "uart.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include "rn42-bt-module.h"
#include "lufa.h"


// write a string to the uart
//#define uart_print(s) uart_print_P(PSTR(s))
uint16_t pressed_counter = 0;


// ACTION DEFINITIONS ---------------------------------------------------------------------------------------------------

// GAME LAYERS
	#define AC_LRG1      ACTION_LAYER_TOGGLE(2)                       // Game on
        #define AC_LRGM      ACTION_FUNCTION(GAME_LAYER)                  // Game/Type toggle

// FN LAYERS
	#define AC_FNNM      ACTION_LAYER_TAP_KEY(6, KC_APP)              // FN 1 / App
        #define AC_FCAP      ACTION_LAYER_TAP_KEY(7, KC_CAPS)             // FN 2 / Caps Lock

// MOUSE KEYPAD
	#define AC_MSKY      ACTION_LAYER_TOGGLE(4)                       // mouse keypad

// SHIFT HEX KEYPAD
	#define AC_SHEX      ACTION_LAYER_TAP_KEY(3, KC_PENT)             // Shift HEX keypad
	#define AC_HEXF      ACTION_MACRO(HEXF)                           // HEX keypad-[F]
	#define AC_HEXE      ACTION_MACRO(HEXE)                           // HEX keypad-[E]
	#define AC_HEXD      ACTION_MACRO(HEXD)                           // HEX keypad-[D]
	#define AC_HEXC      ACTION_MACRO(HEXC)                           // HEX keypad-[C]
	#define AC_HEXB      ACTION_MACRO(HEXB)                           // HEX keypad-[B]
	#define AC_HEXA      ACTION_MACRO(HEXA)                           // HEX keypad-[A]
	#define AC_HEX6      ACTION_MODS_KEY(MOD_LSFT, KC_6)              // HEX keypad-[&]
	#define AC_HEX5      ACTION_MODS_KEY(MOD_LSFT, KC_5)              // HEX keypad-[%]
	#define AC_HEX3      ACTION_MODS_KEY(MOD_LSFT, KC_3)              // HEX keypad-[#]
	#define AC_HEXX      ACTION_MACRO(HEXX)                           // HEX keypad-[x]

// DUAL SCROLL LOCK 
	#define AC_SCLK      ACTION_LAYER_TAP_KEY(5, KC_SLCK)             // hold Scroll Lock for mouse wheel scrolling

// LEFT SHIFT MOD
	#define AC_SFTM      ACTION_MODS_ONESHOT(MOD_LSFT)                // tap left shift to activate for 1 keypress

// CAPS LOCK MOD
	#define AC_UCAP      ACTION_MODS_KEY(MOD_LSFT, KC_CAPS)           // Shift + Caps Lock

// MACROS
	#define AC_INFO      ACTION_MACRO(INFO)                           // keyboard info
        #define AC_DTOS      ACTION_MACRO(DTOS)                           // detect operating system

// STRING MACROS
	#define AC_STR1      ACTION_FUNCTION(STRING_1)                    // sample string macro

// TELEMETRY
        #define AC_KPPR      ACTION_FUNCTION(KEYS_PRESSED)                // print number of keys pressed
        #define AC_KPRS      ACTION_FUNCTION(KEYS_PRESSED_RESET)          // reset number of keys pressed

// CLEAR KEYBOARD
	#define AC_CLAL      ACTION_FUNCTION(CLEAR)                       // turn off all layers and USB HID locked keys

// PIN LAYER OFF
	#define AC_PLOF      ACTION_LAYER_OFF(15, ON_PRESS)               // set PIN layer off

// PASSWORDS
	#define AC_PSW1      ACTION_MACRO(PSW1)                           // [password1]

// LED BRIGHTNESS
	#define AC_LEDU      ACTION_FUNCTION(LED_BRIGHTNESS_UP)           // LED brightness increase
        #define AC_LDUH      ACTION_FUNCTION(LED_BRIGHTNESS_UP_HIGHRES)   // LED brightness increase (small step)
	#define AC_LEDD      ACTION_FUNCTION(LED_BRIGHTNESS_DOWN)         // LED brightness decrease 
        #define AC_LDDH      ACTION_FUNCTION(LED_BRIGHTNESS_DOWN_HIGHRES) // LED brightness decrease (small step)
	#define AC_LED1      ACTION_FUNCTION(LED_BRIGHTNESS_MAX)          // LED brightness 100%
	#define AC_LED0      ACTION_FUNCTION(LED_BRIGHTNESS_MIN)          // LED brightness 0%

// BLUETOOTH
	#define AC_BTCT      ACTION_FUNCTION(BLUETOOTH_CONNECT)           // initialize RN42 bluetooth module and connect to bluetooth device
	#define AC_SBTH      ACTION_FUNCTION(BLUETOOTH)                   // Switch to Bluetooth driver
	#define AC_SUSB      ACTION_FUNCTION(USB)                         // Switch to USB driver

// MONITOR INPUT SWITCH
	#define AC_MIPB      ACTION_FUNCTION(MONITOR_INPUT_BOTH)          // Switch both monitor inputs
	#define AC_MIPR      ACTION_FUNCTION(MONITOR_INPUT_RIGHT)         // Switch right monitor input
	#define AC_MIPL      ACTION_FUNCTION(MONITOR_INPUT_LEFT)          // Switch left monitor input

// SYNERGY INPUT SWITCH
	#define AC_SYN1      ACTION_MACRO(SYN1)                           // Shift+F1
	#define AC_SYN2      ACTION_MACRO(SYN2)                           // Shift+F2



// STRING LOOKUP TABLE --------------------------------------------------------------------------------------------------

uint8_t lookup(uint8_t index) {
    index = index - 32;
    static const uint8_t lookup[94] = {
        KC_SPACE, /* shift */KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_QUOT, KC_SCLN, /* end shift */ KC_COMM, KC_MINS, KC_DOT, KC_SLSH, KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_QUOT, KC_SCLN, /* shift */ KC_COMM, KC_MINS, KC_DOT, KC_SLSH, /* end shift */
        KC_LBRC, /* shift */ KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S, KC_T, KC_U, KC_V, KC_W, KC_X, KC_Y, KC_Z, /* endshift */ KC_RBRC, KC_RO, KC_BSLS, KC_EQL, /*shift */ KC_RO, 
        KC_LBRC, /* end shift */ KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S, KC_T, KC_U, KC_V, KC_W, KC_X, KC_Y, KC_Z, /* shift */ KC_RBRC, KC_JYEN, KC_BSLS, KC_EQL
        };
	
    if ( index < 94 ) {
        return lookup[index];
    }
    else {
        return KC_NO;
    }
}


		  	 
// SET FUNCTION IDs -----------------------------------------------------------------------------------------------------
enum function_id {
	CLEAR,
        LED_BRIGHTNESS_UP,
        LED_BRIGHTNESS_UP_HIGHRES,
        LED_BRIGHTNESS_DOWN,
        LED_BRIGHTNESS_DOWN_HIGHRES,
        LED_BRIGHTNESS_MAX,
        LED_BRIGHTNESS_MIN,
        GAME_LAYER,
        STRING_1,
        KEYS_PRESSED,
        KEYS_PRESSED_RESET,
        BLUETOOTH_CONNECT,
	BLUETOOTH,
	MONITOR_INPUT_RIGHT,
        MONITOR_INPUT_LEFT,
        MONITOR_INPUT_BOTH,
	USB,
};



// FUNCTION DEFINITIONS -------------------------------------------------------------------------------------------------
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (id == LED_BRIGHTNESS_UP)   { if (record->event.pressed) { led_brightness_up(); }}

    if (id == LED_BRIGHTNESS_UP_HIGHRES)   { if (record->event.pressed) { led_brightness_up_highres(); }}

    if (id == LED_BRIGHTNESS_DOWN) { if (record->event.pressed) { led_brightness_down(); }}

    if (id == LED_BRIGHTNESS_DOWN_HIGHRES) { if (record->event.pressed) { led_brightness_down_highres(); }}

    if (id == LED_BRIGHTNESS_MAX)  { if (record->event.pressed) { led_brightness_max(); }}

    if (id == LED_BRIGHTNESS_MIN)  { if (record->event.pressed) { led_brightness_min(); }}

    if (id == GAME_LAYER) { 
        if (record->event.pressed) {
            layer_invert(1);
            layer_off(2);
        }
    }

    if (id == STRING_1) {
        char *str = "This is a sample string, type anything here to create a simple plain text macro.";
        if (record->event.pressed) {
            for (uint16_t i = 0; i < strlen(str); i++){

                register_code(lookup(str[i]));
                unregister_code(lookup(str[i]));
            }
        }
    }

    if (id == KEYS_PRESSED) {
        char stra[5];
        utoa(pressed_counter, stra, 10);
        if (record->event.pressed) {
            for (uint16_t i = 0; i < strlen(stra); i++){

                register_code(lookup(stra[i]));
                unregister_code(lookup(stra[i]));
            }
        }
    }

    if (id == KEYS_PRESSED_RESET) {
        pressed_counter = 0;
        loading_led_animation_on();
    }

    if (id == CLEAR) {

        // PLAY LOADING ANIMATION
	loading_led_animation_on();

        // TURN OFF NUM/SCROLL/CAPS/KANA TOGGLE KEYS
        if (host_keyboard_leds() & (1<<USB_LED_KANA)) { add_key(KC_KANA); }
        if (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) { add_key(KC_SCROLLLOCK); }
        if (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) { add_key(KC_NUMLOCK); }
        if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { add_key(KC_LSHIFT); add_key(KC_CAPSLOCK); }
        send_keyboard_report();
        wait_ms(10);
        del_key(KC_KANA);
        del_key(KC_LSHIFT); del_key(KC_CAPSLOCK);
        del_key(KC_NUMLOCK);
        del_key(KC_SCROLLLOCK);
        send_keyboard_report();

	// CLEAR LAYERS
        layer_off(1);
        layer_off(2);
        layer_off(3);
        layer_off(4);
        layer_off(5);
        layer_off(6);
        layer_off(7);
        layer_off(8);
        layer_off(9);

	}

    if (id == BLUETOOTH_CONNECT) {
 	
        if (record->event.pressed) {
        CPU_PRESCALE(0);  // run at 16 MHz
     	uart_init(BAUD_RATE);
        loading_led_animation_on();
	rn42_enter_cmd();
        rn42_set_default();
	rn42_enter_cmd();
        rn42_set_name();
        rn42_mode_hid();
	uart_print("C");
	uart_return();
	}
    }   

    if (id == BLUETOOTH) {
        
        if (record->event.pressed) {
        CPU_PRESCALE(0);  // run at 16 MHz
     	uart_init(BAUD_RATE);
        host_set_driver(&rn42_driver);	
	}
      }
    if (id == USB) {
        
        if (record->event.pressed) {
        host_set_driver(&lufa_driver);	
	}
    }

    if (id == MONITOR_INPUT_LEFT) {
       uint8_t c; 
        if (record->event.pressed) {
        DDRE |=  (1<<7); PORTE |=  (1<<7);
        wait_ms(20);
        DDRE &= ~(1<<7); PORTE &= ~(1<<7);
        }
    }

    if (id == MONITOR_INPUT_RIGHT) {
       uint8_t c; 
        if (record->event.pressed) {
        DDRE |=  (1<<6); PORTE |=  (1<<6);
        wait_ms(20);
        DDRE &= ~(1<<6); PORTE &= ~(1<<6);
        }
    }

    if (id == MONITOR_INPUT_BOTH) {
       uint8_t c; 
        if (record->event.pressed) {
        DDRE |=  (1<<6); PORTE |=  (1<<6);
        DDRE |=  (1<<7); PORTE |=  (1<<7);
        wait_ms(20);
        DDRE &= ~(1<<6); PORTE &= ~(1<<6);
        DDRE &= ~(1<<7); PORTE &= ~(1<<7);
        }
    }
}



// HOOKS ----------------------------------------------------------------------------------------------------------------

// ON LAYER CHANGE
void hook_layer_function(uint32_t state) { }

// ON KEY PRESS
void hook_key_function(bool pressed) {

    // KEYPRESS COUNTER
    if (pressed) { 
        pressed_counter++;	
    }
}
 
// SET MACRO IDs --------------------------------------------------------------------------------------------------------
enum macro_id {
	INFO,
	ALT_TAB,
	PSW1,
        DTOS,
        HEXA,
        HEXB,
        HEXC,
        HEXD,
        HEXE,
        HEXF,
        HEXX,
	SYN1,
	SYN2,

};


// MACRO DEFINITIONS ----------------------------------------------------------------------------------------------------
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case INFO:           // keyboard information
            typing_led_animation_on();
            if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { 
                add_key(KC_LSHIFT); 
                add_key(KC_CAPSLOCK); 
                send_keyboard_report(); 
                wait_ms(20); 
                del_key(KC_CAPSLOCK); 
                del_key(KC_LSHIFT);
                send_keyboard_report();
                wait_ms(20); }
            return (record->event.pressed ?
                    MACRO( I(16), T(N), T(U), T(L), T(L), T(SPC), D(LSHIFT), T(S), U(LSHIFT), T(A), T(I), T(K), T(O),    \
                    T(U), D(LSHIFT), T(T), U(LSHIFT), T(Y), T(P), T(E), T(SPC), T(1), T(1), T(0), T(ENT), D(LSHIFT),     \
                    T(N), T(K), T(B), T(M), U(LSHIFT), T(MINS), D(LSHIFT), T(S), T(T), U(LSHIFT), T(1), T(1), T(0),      \
                    T(SPC), T(R), T(E), T(V), T(DOT), T(SPC), T(2), T(DOT), T(0), T(ENT), T(2), T(0), T(1), T(8), T(DOT),\
                    T(0), T(1), T(DOT), T(1), T(7), T(ENT), T(C), T(O), T(P), T(Y), T(R), T(I), T(G), T(H), T(T), T(SPC),\
                    T(2), T(0), T(1), T(8), T(SPC), D(LSHIFT), T(Y), U(LSHIFT), T(U), T(K), T(I), T(SPC), D(LSHIFT),     \
		    T(S), U(LSHIFT), T(A), T(K), T(A), T(T), T(O), T(I), T(ENT), T(N), T(U), T(L), T(L), T(MINS), T(B),  \
		    T(I), T(N), T(DOT), T(B), T(L), T(O), T(G), T(S), T(P), T(O), T(T), T(DOT), T(C), T(O), T(M), END ) :
		    MACRO_NONE );

        case ALT_TAB:       // applicasion Switcher
            return (record->event.pressed ?
                    MACRO( D(LALT), D(TAB), END ) :
                    MACRO( U(TAB), END ));

        case PSW1:          // password1
             layer_off(15); 
             typing_led_animation_on();	
             return (record->event.pressed ?
                    MACRO( I(16), T(P), T(A), T(5), T(S), T(W), T(0), D(LSHIFT), T(R), U(LSHIFT), T(D), END ) : 
                    MACRO_NONE );

        case DTOS:          // detect operating system
            if (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) { 
                return (record->event.pressed ?
                    MACRO( I(5), T(W), T(I), T(N), T(D), T(O), T(W), T(S), END ) :
                    MACRO_NONE ); }
            else { 
                add_key(KC_SCROLLLOCK);
                send_keyboard_report();
                wait_ms(20);
                del_key(KC_SCROLLLOCK);
                send_keyboard_report();
                wait_ms(20);
                if (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) { 
                    add_key(KC_SCROLLLOCK); 
                    send_keyboard_report();
                    wait_ms(20);
                    del_key(KC_SCROLLLOCK);
                    send_keyboard_report();
                    wait_ms(20);
                    return (record->event.pressed ?
                        MACRO( I(5), T(W), T(I), T(N), T(D), T(O), T(W), T(S), END ) :
                        MACRO_NONE ); }
                else {
                    return (record->event.pressed ?
                        MACRO( I(5),T(U),T(N), T(I), T(X), END ) :
                        MACRO_NONE ); }
            }
 
        case HEXA:
            if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { 
                return (record->event.pressed ?
                    MACRO( I(5), T(A), END ) :
                    MACRO_NONE ); }
            else {
                return (record->event.pressed ?
                    MACRO( I(5), D(LSHIFT), T(A), U(LSHIFT), END ) :
                    MACRO_NONE ); }

        case HEXB:
            if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { 
                return (record->event.pressed ?
                    MACRO( I(5), T(B), END ) :
                    MACRO_NONE ); }
            else {
                return (record->event.pressed ?
                    MACRO( I(5), D(LSHIFT), T(B), U(LSHIFT), END ) :
                    MACRO_NONE ); }

        case HEXC:
            if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { 
                return (record->event.pressed ?
                    MACRO( I(5), T(C), END ) :
                    MACRO_NONE ); }
            else {
                return (record->event.pressed ?
                    MACRO( I(5), D(LSHIFT), T(C), U(LSHIFT), END ) :
                    MACRO_NONE ); }

        case HEXD:
            if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { 
                return (record->event.pressed ?
                    MACRO( I(5), T(D), END ) :
                    MACRO_NONE ); }
            else {
                return (record->event.pressed ?
                    MACRO( I(5), D(LSHIFT), T(D), U(LSHIFT), END ) :
                    MACRO_NONE ); }

        case HEXE:
            if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { 
                return (record->event.pressed ?
                    MACRO( I(5), T(E), END ) :
                    MACRO_NONE ); }
            else {
                return (record->event.pressed ?
                    MACRO( I(5), D(LSHIFT), T(E), U(LSHIFT), END ) :
                    MACRO_NONE ); }

        case HEXF:
            if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { 
                return (record->event.pressed ?
                    MACRO( I(5), T(F), END ) :
                    MACRO_NONE ); }
            else {
                return (record->event.pressed ?
                    MACRO( I(5), D(LSHIFT), T(F), U(LSHIFT), END ) :
                    MACRO_NONE ); }

        case HEXX:
            if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { 
                return (record->event.pressed ?
                    MACRO( I(5), D(LSHIFT), T(X), U(LSHIFT), END ) :
                    MACRO_NONE ); }

            else {
                return (record->event.pressed ?
                    MACRO( I(5), T(X), END ) :
                    MACRO_NONE ); }

        case SYN1:
                return (record->event.pressed ?
                    MACRO( I(5), D(LSHIFT), T(F1), U(LSHIFT), END ) :
                    MACRO_NONE ); 

        case SYN2:
                return (record->event.pressed ?
                    MACRO( I(5), D(LSHIFT), T(F2), U(LSHIFT), END ) :
                    MACRO_NONE ); 

    }
    return MACRO_NONE;
}



// KEYBOARD ACTION MAP LAYERS -------------------------------------------------------------------------------------------

const action_t PROGMEM actionmaps[][MATRIX_ROWS][MATRIX_COLS] = {



// MATRIX LAYOUT --------------------------------------------------------------------------------------------------------\
            ,-----------------------------------------------------------------------------------------------.            \
            | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |            \
            | |K00|   |K02|K03|K04|K05| |K06|K07|K08|K09| |K0B|K0C|K0D|K0E| |K60|K61|K62|                   |            \
            | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |            \
            | ,-----------------------------------------------------------. ,-----------. ,---------------. |            \
            | |K10|K11|K12|K13|K14|K15|K16|K17|K18|K19|K1A|K1B|K1C|K1D|K1E| |K63|K64|K65| |K6D|K6E|K70|K71| |            \
            | |-----------------------------------------------------------| |-----------| |---------------| |            \
            | | K20 |K21|K22|K23|K24|K25|K26|K27|K28|K29|K2A|K2B|K2C| K3C | |K66|K67|K68| |K72|K73|K74|   | |            \
            | |------------------------------------------------------ K3E | `-----------' |------------K75| |            \
            | | K30  |K31|K32|K33|K34|K35|K36|K37|K38|K39|K3A|K3B|K3C|K3E |               |K76|K77|K78|   | |            \
            | |-----------------------------------------------------------|     ,---.     |---------------| |            \
            | | K40 K41|K42|K43|K44|K45|K46|K47|K48|K49|K4A|K4B|K4C  K4D  |     |K69|     |K79|K7A|K7B|   | |            \
            | |-----------------------------------------------------------| ,-----------. |------------K7C| |            \
            | | K50|K51|K52 |K53| K54   K55   K57 |K58 |K59 |K5A |K5D|K5E | |K6A|K6B|K6C| |  K7D  |K7E|   | |            \
            | `-----------------------------------------------------------' `-----------' `---------------' |            \
            `-----------------------------------------------------------------------------------------------'            \
                                                                                                                         \
  [#] = ACTIONMAP_NKBMST110(                                                                                             \
    K00,       K02, K03, K04, K05,   K06, K07, K08, K09,   K0B, K0C, K0D, K0E,    K60, K61, K62,                         \
                                                                                                                         \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E,    K63, K64, K65,    K6D, K6E, K70, K71,  \
    K20,   K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,            K66, K67, K68,    K72, K73, K74,       \
    K30,    K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,   K3E,                      K76, K77, K78, K75,  \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C,      K4D,         K69,         K79, K7A, K7B,       \
    K50, K51, K52, K53,        K54, K55, K57,         K58, K59, K5A, K5D, K5E,    K6A, K6B, K6C,    K7D,      K7E, K7C   \



// LAYER 0: JP ----------------------------------------------------------------------------------------------------------\
            ,----------------------------------------------------------------------------------------------.             \
            | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |            \
            | |ESC|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PRS|SCL|PAU|                   |            \
            | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |            \
            | ,-----------------------------------------------------------. ,-----------. ,---------------. |            \
            | |E/J| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | ^ |JPY|BS | |INS|HOM|PGU| |NUM| / | * | - | |            \
            | |-----------------------------------------------------------| |-----------| |---------------| |            \
            | | TAB | Q | W | E | R | T | Y | U | I | O | P | @ | [ |     | |DEL|END|PGD| | 7 | 8 | 9 |   | |            \
            | |------------------------------------------------------ ENT | `-----------' |------------ + | |            \
            | | CAPS | A | S | D | F | G | H | J | K | L | ; | : | ] |    |               | 4 | 5 | 6 |   | |            \
            | |-----------------------------------------------------------|     ,---.     |---------------| |            \
            | | SHIFT  | Z | X | C | V | B | N | M | , | . | / | \ |SHIFT |     |UP |     | 1 | 2 | 3 |ENT| |            \
            | |-----------------------------------------------------------| ,-----------. |------------ / | |            \
            | |CTRL|OS |ALT |MHN|      SPACE      |HENK|KANA|ALT |FN |CTRL| |LEF|DOW|RIG| |   0   | . |HEX| |            \
            | `-----------------------------------------------------------' `-----------' `---------------' |            \
            `----------------------------------------------------------------------------------------------'             \
                                                                                                                         /
  [0] = ACTIONMAP_NKBMST110(                                                                                             \
    ESC,       F1,  F2,  F3,  F4,    F5,  F6,  F7,  F8,    F9,  F10, F11, F12,    PSCR,SCLK,PAUS,                        \
                                                                                                                         \
    ZKHK,1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL ,JYEN,BSPC,   INS, HOME,PGUP,   NLCK,PSLS,PAST,PMNS, \
    TAB,   Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,           DEL, END, PGDN,   P7,  P8,  P9,        \
    FCAP,   A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,BSLS,   ENT,                     P4,  P5,  P6,  PPLS, \
    LSFT,NO,  Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RO,       RSFT,        UP,          P1,  P2,  P3,        \
    LCTL,LGUI,LALT,MHEN,       NO,  SPC, NO,          HENK,KANA,RALT,FNNM,RCTL,   LEFT,DOWN,RGHT,   P0,       PDOT,SHEX),\

  
// LAYER 1: Game --------------------------------------------------------------------------------------------------------\
            ,-----------------------------------------------------------------------------------------------.            \
            | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |            \
            | |   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |                   |            \
            | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |            \
            | ,-----------------------------------------------------------. ,-----------. ,---------------. |            \
            | |ESC|   |   |   |   |   |   |   |   |   |   |   |   |   |   | |   |   |   | |   |   |   |   | |            \
            | |-----------------------------------------------------------| |-----------| |---------------| |            \
            | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | |   |   |   |   | |            \
            | |------------------------------------------------------     | `-----------' |------------   | |            \
            | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               |   |   |   |   | |            \
            | |-----------------------------------------------------------|     ,---.     |---------------| |            \
            | |        |   |   |   |   |   |   |   |   |   |   |   |      |     |   |     |   |   |   |   | |            \
            | |-----------------------------------------------------------| ,-----------. |------------   | |            \
            | |     |[G]|     |ENT|      SPACE    |ENT |    |    |   |    | |   |   |   | |       |   |   | |            \
            | `-----------------------------------------------------------' `-----------' `---------------' |            \
            `-----------------------------------------------------------------------------------------------'            \
                                                                                                                         /
  [1] = ACTIONMAP_NKBMST110(                                                                                             \
    TRNS,      TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,                        \
                                                                                                                         \
    ESC, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,TRNS, \
    TRNS,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,           TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,      \
    FCAP,   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,                     TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,        TRNS,        TRNS,TRNS,TRNS,      \
    TRNS,LRG1,TRNS,ENT,        NO,  SPC, NO,          ENT, TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,   TRNS,     TRNS,TRNS),\


// LAYER 2: Game/Type ---------------------------------------------------------------------------------------------------\
            ,-----------------------------------------------------------------------------------------------.            \
            | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |            \
            | |   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |                   |            \
            | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |            \
            | ,-----------------------------------------------------------. ,-----------. ,---------------. |            \
            | |E/J|   |   |   |   |   |   |   |   |   |   |   |   |   |   | |   |   |   | |   |   |   |   | |            \
            | |-----------------------------------------------------------| |-----------| |---------------| |            \
            | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | |   |   |   |   | |            \
            | |------------------------------------------------------     | `-----------' |------------   | |            \
            | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               |   |   |   |   | |            \
            | |-----------------------------------------------------------|     ,---.     |---------------| |            \
            | |        |   |   |   |   |   |   |   |   |   |   |   |      |     |   |     |   |   |   |   | |            \
            | |-----------------------------------------------------------| ,-----------. |------------   | |            \
            | |    |[G]|    |MHN|      SPACE      |HENK|KANA|    |   |    | |   |   |   | |       |   |   | |            \
            | `-----------------------------------------------------------' `-----------' `---------------' |            \
            `-----------------------------------------------------------------------------------------------'            \
                                                                                                                         /
  [2] = ACTIONMAP_NKBMST110(                                                                                             \
    TRNS,      TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,                        \
                                                                                                                         \
    ZKHK,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,TRNS, \
    TRNS,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,           TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,      \
    FCAP,   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,                     TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,        TRNS,        TRNS,TRNS,TRNS,      \
    TRNS,TRNS,TRNS,MHEN,       NO,  SPC, NO,          HENK,TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,   TRNS,     TRNS,TRNS),\


// LAYER 3: Shift HEX Keypad --------------------------------------------------------------------------------------------\
            ,-----------------------------------------------------------------------------------------------.            \
            | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |            \
            | |   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |                   |            \
            | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |            \
            | ,-----------------------------------------------------------. ,-----------. ,---------------. |            \
            | |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |   |   |   | |   |   |   |   | |            \
            | |-----------------------------------------------------------| |-----------| |---------------| |            \
            | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | | # | % | & |   | |            \
            | |------------------------------------------------------     | `-----------' |------------   | |            \
            | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               | D | E | F |   | |            \
            | |-----------------------------------------------------------|     ,---.     |---------------| |            \
            | |        |   |   |   |   |   |   |   |   |   |   |   |      |     |   |     | A | B | C |   | |            \
            | |-----------------------------------------------------------| ,-----------. |------------   | |            \
            | |    |   |    |   |                 |    |    |    |   |    | |   |   |   | | SPACE | x |   | |            \
            | `-----------------------------------------------------------' `-----------' `---------------' |            \
            `-----------------------------------------------------------------------------------------------'            \
                                                                                                                         /
  [3] = ACTIONMAP_NKBMST110(                                                                                             \
    TRNS,      TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,                        \
                                                                                                                         \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,TRNS, \
    TRNS,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,           TRNS,TRNS,TRNS,   HEX3,HEX5,HEX6,      \
    TRNS,   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,                     HEXD,HEXE,HEXF,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,        TRNS,        HEXA,HEXB,HEXC,      \
    TRNS,TRNS,TRNS,TRNS,       TRNS,TRNS,TRNS,        TRNS,TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,   SPC,      HEXX,TRNS),\


// LAYER 4: Mouse Keypad ------------------------------------------------------------------------------------------------\
            ,-----------------------------------------------------------------------------------------------.            \
            | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |            \
            | |   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |                   |            \
            | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |            \
            | ,-----------------------------------------------------------. ,-----------. ,---------------. |            \
            | |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |   |   |   | |   |SCL|SCR|MCL| |            \
            | |-----------------------------------------------------------| |-----------| |---------------| |            \
            | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | |LCL|MSU|RCL|   | |            \
            | |------------------------------------------------------     | `-----------' |------------SCU| |            \
            | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               |MSL|MSD|MSR|   | |            \
            | |-----------------------------------------------------------|     ,---.     |---------------| |            \
            | |        |   |   |   |   |   |   |   |   |   |   |   |      |     |   |     |[X]|[X]|[X]|   | |            \
            | |-----------------------------------------------------------| ,-----------. |------------SCD| |            \
            | |    |   |    |   |                 |    |    |    |   |    | |   |   |   | |   LCL |RCL|   | |            \
            | `-----------------------------------------------------------' `-----------' `---------------' |            \
            `-----------------------------------------------------------------------------------------------'            \
                                                                                                                         /
  [4] = ACTIONMAP_NKBMST110(                                                                                             \
    TRNS,      TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,                        \
                                                                                                                         \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,   TRNS,WH_L,WH_R,BTN3, \
    TRNS,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,           TRNS,TRNS,TRNS,   BTN1,MS_U,BTN2,      \
    TRNS,   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,                     MS_L,MS_D,MS_R,WH_U, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,        TRNS,        NO,  NO,  NO,        \
    TRNS,TRNS,TRNS,TRNS,       TRNS,TRNS,TRNS,        TRNS,TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,   BTN1,     BTN2,WH_D),\


// LAYER 5: Dual Scroll Lock --------------------------------------------------------------------------------------------\
            ,-----------------------------------------------------------------------------------------------.            \
            | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |            \
            | |   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |SCL|   |SCR|                   |            \
            | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |            \
            | ,-----------------------------------------------------------. ,-----------. ,---------------. |            \
            | |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |SCU|   |   | |   |   |   |   | |            \
            | |-----------------------------------------------------------| |-----------| |---------------| |            \
            | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |SCD|   |   | |   |   |   |   | |            \
            | |------------------------------------------------------     | `-----------' |------------   | |            \
            | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               |   |   |   |   | |            \
            | |-----------------------------------------------------------|     ,---.     |---------------| |            \
            | |        |   |   |   |   |   |   |   |   |   |   |   |      |     |   |     |   |   |   |   | |            \
            | |-----------------------------------------------------------| ,-----------. |------------   | |            \
            | |    |   |    |   |                 |    |    |    |   |    | |   |   |   | |       |   |   | |            \
            | `-----------------------------------------------------------' `-----------' `---------------' |            \
            `-----------------------------------------------------------------------------------------------'            \
                                                                                                                         /
  [5] = ACTIONMAP_NKBMST110(                                                                                             \
    TRNS,      TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,   WH_L,TRNS,WH_R,                        \
                                                                                                                         \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,   WH_U,TRNS,TRNS,   TRNS,TRNS,TRNS,TRNS, \
    TRNS,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,           WH_D,TRNS,TRNS,   TRNS,TRNS,TRNS,      \
    TRNS,   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,                     TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,        TRNS,        TRNS,TRNS,TRNS,      \
    TRNS,TRNS,TRNS,TRNS,       TRNS,TRNS,TRNS,        TRNS,TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,   TRNS,     TRNS,TRNS),\


// LAYER 6: FN ----------------------------------------------------------------------------------------------------------\
            ,-----------------------------------------------------------------------------------------------.            \
            | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |            \
            | |CLR|   |F13|F14|F15|F16| |F17|F18|F19|F20| |F21|F22|F23|F24| |WAK|OS |SLP|                   |            \
            | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |            \
            | ,-----------------------------------------------------------. ,-----------. ,---------------. |            \
            | |CLR|   |   |   |   |   |   |   |   |   |   |   |   |   |   | |PLY|NXT|VUP| |CLC|   |   |MKY| |            \
            | |-----------------------------------------------------------| |-----------| |---------------| |            \
            | |     |   |   |   |KRS|   |   |USB|   |OS |   |   |   |     | |MUT|PRV|VDW| |   |   |   |   | |            \
            | |------------------------------------------------------     | `-----------' |------------   | |            \
            | |      |   |ST1|   |   |   |   |   |KPR|   |   |   |   |    |               |   |   |   |   | |            \
            | |-----------------------------------------------------------|     ,---.     |---------------| |            \
            | |        |   |   |   |BTR|BTC|   |   |   |   | ? |   |      |     |   |     |   |   |   |   | |            \
            | |-----------------------------------------------------------| ,-----------. |------------   | |            \
            | |    |GM |    |   |                 |    |    |MENU|   |    | |   |   |   | |       |   |   | |            \
            | `-----------------------------------------------------------' `-----------' `---------------' |            \
            `-----------------------------------------------------------------------------------------------'            \
                                                                                                                         /
  [6] = ACTIONMAP_NKBMST110(                                                                                             \
    CLAL,     TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,MIPB,  MIPL,MIPR,SYN1,SYN2,    WAKE,DTOS,SLEP,                        \
                                                                                                                         \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,   MPLY,MNXT,VOLU,   CALC,TRNS,TRNS,MSKY, \
    TRNS,  TRNS,TRNS,TRNS,KPRS,TRNS,TRNS,SUSB,TRNS,DTOS,TRNS,TRNS,TRNS,           MUTE,MPRV,VOLD,   TRNS,TRNS,TRNS,      \
    TRNS,   TRNS,STR1,TRNS,TRNS,TRNS,TRNS,TRNS,KPPR,TRNS,TRNS,TRNS,TRNS,  TRNS,                     TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,BTCT,SBTH,TRNS,TRNS,TRNS,TRNS,INFO,TRNS,     TRNS,        TRNS,        TRNS,TRNS,TRNS,      \
    TRNS,LRGM,TRNS,TRNS,       NO,  TRNS,NO,          TRNS,TRNS,APP, TRNS,TRNS,   TRNS,TRNS,TRNS,   TRNS,     TRNS,TRNS),\


// LAYER 7: FN 2 --------------------------------------------------------------------------------------------------------\
            ,-----------------------------------------------------------------------------------------------.            \
            | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |            \
            | |CLR|   |VDN|VUP|PRV|NXT| |PLY|STP|RWD|FWD| |   |   |   |   | |WAK|   |SLP|                   |            \
            | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |            \
            | ,-----------------------------------------------------------. ,-----------. ,---------------. |            \
            | |CLR|   |   |   |   |   |   |   |   |   |   |   |   |   |   | |LMX|LUP|LUH| |   |SCL|SCR|MCL| |            \
            | |-----------------------------------------------------------| |-----------| |---------------| |            \
            | |     |HOM|UP |END|PGU|WHU|   |USB|   |OS |   |   |   |     | |LMN|LDN|LDH| |LCL|MSU|RCL|   | |            \
            | |------------------------------------------------------     | `-----------' |------------SCU| |            \
            | |      |LFT|DWN|RIG|PGD|WHD|   |   |   |   |   |   |   |    |               |MSL|MSD|MSR|   | |            \
            | |-----------------------------------------------------------|     ,---.     |---------------| |            \
            | |        |BS |DEL|INS|BTR|BTC|   |   |   |   |   |   |      |     |   |     |[X]|[X]|[X]|   | |            \
            | |-----------------------------------------------------------| ,-----------. |------------SCD| |            \
            | |    |OS |    |   |      ENTER      |    |    |    |   |    | |   |   |   | |  LCL  |RCL|   | |            \
            | `-----------------------------------------------------------' `-----------' `---------------' |            \
            `-----------------------------------------------------------------------------------------------'            \
                                                                                                                         /
  [7] = ACTIONMAP_NKBMST110(                                                                                             \
    CLAL,      VOLD,VOLU,MPRV,MNXT,  MPLY,MSTP,MRWD,MFFD,  TRNS,TRNS,TRNS,TRNS,   WAKE,TRNS,SLEP,                        \
                                                                                                                         \
    MIPB,MIPL,MIPR,SYN1,SYN2,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,   LED1,LEDU,LDUH,   TRNS,WH_L,WH_R,BTN3, \
    TRNS,  HOME,UP,  END, PGUP,WH_U,TRNS,SUSB,TRNS,DTOS,TRNS,TRNS,TRNS,           LED0,LEDD,LDDH,   BTN1,MS_U,BTN2,      \
    TRNS,   LEFT,DOWN,RGHT,PGDN,WH_D,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,                     MS_L,MS_D,MS_R,WH_U, \
    TRNS,TRNS,BSPC,DEL, INS, BTCT,SBTH,TRNS,TRNS,TRNS,TRNS,INFO,TRNS,     TRNS,        TRNS,        NO,  NO,  NO,        \
    TRNS,DTOS,TRNS,TRNS,       NO,  ENT, NO,          TRNS,TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,   BTN1,     BTN2,WH_D),\


//                        ||
//                        || 
//  ADD MORE LAYERS HERE  ||  -------------------------------------------------------------------------------------------
//                       \  /
//                        \/




 
//                        /\
//                       /  \
//  ADD MORE LAYERS HERE  ||  -------------------------------------------------------------------------------------------
//                        ||
//                        ||


// LAYER 15: PIN / PASSOWRDS LAYER --------------------------------------------------------------------------------------\
            ,-----------------------------------------------------------------------------------------------.            \
            | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |            \
            | | X |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |                   |            \
            | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |            \
            | ,-----------------------------------------------------------. ,-----------. ,---------------. |            \
            | | X |P1 |   |   |   |   |   |   |   |   |   |   |   |   |   | |   |   |   | |   |   |   |   | |            \
            | |-----------------------------------------------------------| |-----------| |---------------| |            \
            | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | |   |   |   |   | |            \
            | |------------------------------------------------------     | `-----------' |------------   | |            \
            | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               |   |   |   |   | |            \
            | |-----------------------------------------------------------|     ,---.     |---------------| |            \
            | |        |   |   |   |   |   |   |   |   |   |   |   |      |     |   |     | P1|   |   |   | |            \
            | |-----------------------------------------------------------| ,-----------. |------------   | |            \
            | |    |   |    |   |                 |    |    |    |   |    | |   |   |   | |       |   |   | |            \
            | `-----------------------------------------------------------' `-----------' `---------------' |            \
            `-----------------------------------------------------------------------------------------------'            \
                                                                                                                         /
  [15] = ACTIONMAP_NKBMST110(                                                                                            \
    PLOF,      TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,  TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,                        \
                                                                                                                         \
    PLOF,PSW1,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,TRNS, \
    TRNS,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,           TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,      \
    TRNS,   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,  TRNS,                     TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,        TRNS,        PSW1,TRNS,TRNS,      \
    TRNS,TRNS,TRNS,TRNS,       TRNS,TRNS,TRNS,        TRNS,TRNS,TRNS,TRNS,TRNS,   TRNS,TRNS,TRNS,   TRNS,     TRNS,TRNS),\

};
