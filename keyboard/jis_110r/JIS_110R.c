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



#include "actionmap.h"
#include "action_code.h"
#include "JIS_110R.h"
#include "action_layer.h"
#include "action_util.h"
#include "led.h"
#include "led_pwm.h"
#include <string.h>
#include "debug.h"
#include "wait.h"
#include "host.h"



// ACTION DEFINITIONS ----------------------------------------------------------------------------------------

// GAME LAYERS
	#define AC_LRG1      ACTION_LAYER_TOGGLE(2)                       // Game on
        #define AC_LRGM      ACTION_FUNCTION(GAME_LAYER)                  // Game/Type toggle

// FN LAYERS
	#define AC_FNNM      ACTION_LAYER_MOMENTARY(6)                    // FN momentary
	#define AC_FNON      ACTION_LAYER_ON(7, ON_BOTH)                  // FN on
        #define AC_FNOF      ACTION_LAYER_OFF(7, ON_BOTH)                 // FN off

// MOUSE KEYPAD
	#define AC_MSKY      ACTION_LAYER_TOGGLE(4)                       // mouse keypad

// SHIFT HEX KEYPAD
	#define AC_SHEX      ACTION_LAYER_TAP_KEY(3, KC_PENT)             // Shift HEX keypad
	#define AC_HEXF      ACTION_MODS_KEY(MOD_LSFT, KC_F)              // HEX keypad-[F]
	#define AC_HEXE      ACTION_MODS_KEY(MOD_LSFT, KC_E)              // HEX keypad-[E]
	#define AC_HEXD      ACTION_MODS_KEY(MOD_LSFT, KC_D)              // HEX keypad-[D]
	#define AC_HEXC      ACTION_MODS_KEY(MOD_LSFT, KC_C)              // HEX keypad-[C]
	#define AC_HEXB      ACTION_MODS_KEY(MOD_LSFT, KC_B)              // HEX keypad-[B]
	#define AC_HEXA      ACTION_MODS_KEY(MOD_LSFT, KC_A)              // HEX keypad-[A]
	#define AC_HEX6      ACTION_MODS_KEY(MOD_LSFT, KC_6)              // HEX keypad-[&]
	#define AC_HEX5      ACTION_MODS_KEY(MOD_LSFT, KC_5)              // HEX keypad-[%]
	#define AC_HEX3      ACTION_MODS_KEY(MOD_LSFT, KC_3)              // HEX keypad-[#]

// DUAL SCROLL LOCK 
	#define AC_SCLK      ACTION_LAYER_TAP_KEY(5, KC_SLCK)             // hold Scroll Lock for mouse wheel scrolling

// LEFT SHIFT MOD
	#define AC_SFTM      ACTION_MODS_ONESHOT(MOD_LSFT)                // tap left shift to activate for 1 keypress

// CAPS LOCK MOD
	#define AC_UCAP      ACTION_MODS_KEY(MOD_LSFT, KC_CAPS)           // Shift + Caps Lock

// MACROS
	#define AC_MGPG      ACTION_MACRO(GPG_KEY)                        // (wget & install shion-os public GPG key)
	#define AC_MURL      ACTION_MACRO(URL)                            // [null-bin.blogspot.com]
          	
// CLEAR KEYBOARD
	#define AC_CLAL      ACTION_FUNCTION(CLEAR_AND_LOAD)              // turn off all layers and USB HID locked keys

// PIN LAYER OFF
	#define AC_PLOF      ACTION_LAYER_OFF(15, ON_PRESS)               // set PIN layer off

// PASSWORDS
	#define AC_PSW1      ACTION_MACRO(PSW1)                           // [password1]
	#define AC_PSW2      ACTION_MACRO(PSW2)                           // [password2]
	#define AC_PSW3      ACTION_MACRO(PSW3)                           // [password3]

// LED BRIGHTNESS
	#define AC_LEDU      ACTION_FUNCTION(LED_BRIGHTNESS_UP)           // LED brightness increase
        #define AC_LDUH      ACTION_FUNCTION(LED_BRIGHTNESS_UP_HIGHRES)   // LED brightness increase (small step)
	#define AC_LEDD      ACTION_FUNCTION(LED_BRIGHTNESS_DOWN)         // LED brightness decrease 
        #define AC_LDDH      ACTION_FUNCTION(LED_BRIGHTNESS_DOWN_HIGHRES) // LED brightness decrease (small step)
	#define AC_LED1      ACTION_FUNCTION(LED_BRIGHTNESS_MAX)          // LED brightness 100%
	#define AC_LED0      ACTION_FUNCTION(LED_BRIGHTNESS_MIN)          // LED brightness 0%


		  	 
// SET FUNCTION IDs ------------------------------------------------------------------------------------------
enum function_id {
	CLEAR_AND_LOAD,
        LED_BRIGHTNESS_UP,
        LED_BRIGHTNESS_UP_HIGHRES,
        LED_BRIGHTNESS_DOWN,
        LED_BRIGHTNESS_DOWN_HIGHRES,
        LED_BRIGHTNESS_MAX,
        LED_BRIGHTNESS_MIN,
        GAME_LAYER,
};



// FUNCTION DEFINITIONS --------------------------------------------------------------------------------------
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

    if (id == CLEAR_AND_LOAD) {

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
}




// SET MACRO IDs ---------------------------------------------------------------------------------------------
enum macro_id {
	URL,
	GPG_KEY,
	ALT_TAB,
	PSW1,
	PSW2,
	PSW3,
};



// MACRO DEFINITIONS -----------------------------------------------------------------------------------------
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case GPG_KEY:       // [wget & install shion-os public GPG key]
            typing_led_animation_on();
            return (record->event.pressed ?
                    MACRO( I(10), T(C), T(D), T(SPC), T(SLSH), T(T), T(M), T(P), T(SPC), D(LSHIFT), D(6),      \
                    U(LSHIFT), U(6), D(LSHIFT), D(6), U(LSHIFT), U(6), T(SPC), T(W), T(G), T(E), T(T),        \
                    T(SPC), T(H), T(T), T(T), T(P), T(QUOT), T(SLSH), T(SLSH), T(S), T(H), T(I), T(O), T(N),  \
                    T(O), T(S), T(DOT), T(S), T(3), T(DOT), T(A), T(M), T(A), T(Z), T(O), T(N), T(A), T(W),   \
                    T(S), T(DOT), T(C), T(O), T(M), T(SLSH), T(R), T(E), T(P), T(O), T(SLSH), T(K), T(E),     \
                    T(Y), T(SLSH), T(D), T(E), T(B), T(DOT), T(G), T(P), T(G), T(DOT), T(K), T(E), T(Y),      \
                    T(SPC), T(MINS), D(LSHIFT), D(O), U(LSHIFT), U(O), T(SPC), T(S), T(H), T(I), T(O), T(N),  \
                    T(MINS), T(P), T(U), T(B), T(L), T(I), T(C), T(DOT), T(D), T(E), T(B), T(DOT), T(K),      \
                    T(E), T(Y), T(DOT), T(G), T(P), T(G), T(SPC), D(LSHIFT), D(6), U(LSHIFT), U(6),           \
                    D(LSHIFT), D(6), U(LSHIFT), U(6), T(SPC), T(S), T(U), T(D), T(O), T(SPC), T(A), T(P),     \
                    T(T), T(MINS), T(K), T(E), T(Y), T(SPC), T(A), T(D), T(D), T(SPC), T(SLSH), T(T), T(M),   \
                    T(P), T(SLSH), T(S), T(H), T(I), T(O), T(N), T(MINS), T(P), T(U), T(B), T(L), T(I), T(C), \
                    T(DOT), T(D), T(E), T(B), T(DOT), T(K), T(E), T(Y), T(DOT), T(G), T(P), T(G), END ) :
                    MACRO_NONE );

        case URL:           // [null-bin.blogspot.com]
            typing_led_animation_on();
            return (record->event.pressed ?
                    MACRO( I(10), T(N), T(U), T(L), T(L), T(MINS), T(B), T(I), T(N), T(DOT), T(B), T(L), T(O), \
                    T(G), T(S), T(P), T(O), T(T), T(DOT), T(C), T(O), T(M), END ) :
                    MACRO_NONE );

        case ALT_TAB:       // Applicasion Switcher
            return (record->event.pressed ?
                    MACRO( D(LALT), D(TAB), END ) :
                    MACRO( U(TAB), END ));

        case PSW1:          // password1
             layer_off(15); // [all functions must be before macros]
             typing_led_animation_on();	
             return (record->event.pressed ?
                    MACRO( I(10), T(P), T(A), T(S), T(S), T(W), T(O), T(R), T(D), T(1), END ) :
                    MACRO_NONE );

        case PSW2:          // password2
             layer_off(15); // [all functions must be before macros]
             typing_led_animation_on();	
             return (record->event.pressed ?
                    MACRO( I(10), T(P), T(A), T(S), T(S), T(W), T(O), T(R), T(D), T(2), END ) :
                    MACRO_NONE );

        case PSW3:          // password3
             layer_off(15); // [all functions must be before macros]
             typing_led_animation_on();	
             return (record->event.pressed ?
                    MACRO( I(10), T(P), T(A), T(S), T(S), T(W), T(O), T(R), T(D), T(3), END ) :
                    MACRO_NONE );

    }
    return MACRO_NONE;
}



// KEYBOARD ACTION MAP LAYERS --------------------------------------------------------------------------------

const action_t PROGMEM actionmaps[][MATRIX_ROWS][MATRIX_COLS] = {

// LAYER 0: JP -----------------------------------------------------------------------------------------------\
       ,----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.        f i l c o  |       \
      | |E/J|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PRS|SCL|PAU|                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |ESC| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | ^ |JPY|BS | |INS|HOM|PGU| |NUM| / | * | - | |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | | TAB | Q | W | E | R | T | Y | U | I | O | P | @ | [ |     | |DEL|END|PGD| | 7 | 8 | 9 |   | |       \
      | |------------------------------------------------------ ENT | `-----------' |------------ + | |       \
      | | CTRL | A | S | D | F | G | H | J | K | L | ; | : | ] |    |               | 4 | 5 | 6 |   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | | SHIFT  | Z | X | C | V | B | N | M | , | . | / | \ |SHIFT |     |UP |     | 1 | 2 | 3 |ENT| |       \
      | |-----------------------------------------------------------| ,-----------. |------------ / | |       \
      | |CAP |OS |ALT |MHN| BS |ENT | SPACE |HENK|KANA|ALT |FN |CTRL| |LEF|DOW|RIG| |   0   | . |HEX| |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `----------------------------------------------------------------------------------------------'        \
                                                                                                              /
  [0] = ACTIONMAP_JIS_110R(                                                                                   \
    ZKHK,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,SCLK,PAUS,PSLS,NLCK,PAST,PMNS,PPLS, \
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,INS ,HOME,PGUP,NO,  NO,  NO,   \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,NO,  NO,  DEL, END, PGDN,P7,  P8,  P9,   \
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,BSLS,ENT, NO,  NO,  NO,  NO,  P4,  P5,  P6,   \
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RO,  RSFT,NO,  NO,  NO,  UP,  NO,  P1,  P2,  P3,   \
    UCAP,LGUI,LALT,MHEN,BSPC,ENT, SPC, HENK,KANA,RALT,FNNM,RCTL,NO,  NO,  NO,  LEFT,DOWN,RGHT,P0  ,PDOT,SHEX),\

  
// LAYER 1: Game ---------------------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.        f i l c o  |       \
      | | ` |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |   |   |   | |   |   |   |   | |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | |   |   |   |   | |       \
      | |------------------------------------------------------     | `-----------' |------------   | |       \
      | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               |   |   |   |   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | |        |   |   |   |   |   |   |   |   |   |   |   |      |     |   |     |   |   |   |   | |       \
      | |-----------------------------------------------------------| ,-----------. |------------   | |       \
      | |CAP |[G]|ALT | [ | ]  |   SPACE    |  / | \  |ALT |FN |CTRL| |   |   |   | |       |   |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \
                                                                                                              /
  [1] = ACTIONMAP_JIS_110R(                                                                                   \
    NO,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,LRG1,TRNS,RBRC,BSLS,SPC, SPC, SLSH,RO,  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS),\


// LAYER 2: Game/Type ----------------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.        f i l c o  |       \
      | |A/J|   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |   |   |   | |   |   |   |   | |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | |   |   |   |   | |       \
      | |------------------------------------------------------     | `-----------' |------------   | |       \
      | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               |   |   |   |   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | |        |   |   |   |   |   |   |   |   |   |   |   |      |     |   |     |   |   |   |   | |       \
      | |-----------------------------------------------------------| ,-----------. |------------   | |       \
      | |CAP |[G]|ALT |MHN| BS |ENT | SPACE |HENK|KANA|ALT |FN |CTRL| |   |   |   | |       |   |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \
                                                                                                              /
  [2] = ACTIONMAP_JIS_110R(                                                                                   \
    ZKHK,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,MHEN,BSPC,ENT, SPC, HENK,KANA,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS),\


// LAYER 3: Shift HEX Keypad ---------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.        f i l c o  |       \
      | |   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |   |   |   | |   |   |   |   | |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | | # | % | & |   | |       \
      | |------------------------------------------------------     | `-----------' |------------   | |       \
      | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               | D | E | F |   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | |        |   |   |   |   |   |   |   |   |   |   |   |      |     |   |     | A | B | C |   | |       \
      | |-----------------------------------------------------------| ,-----------. |------------   | |       \
      | |    |   |    |   |    |    |       |    |    |    |   |    | |   |   |   | | SPACE | x |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \
                                                                                                              /
  [3] = ACTIONMAP_JIS_110R(                                                                                   \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,HEX3,HEX5,HEX6, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,HEXD,HEXE,HEXF, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,HEXA,HEXB,HEXC, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,SPC, X,   TRNS),\


// LAYER 4: Mouse Keypad -------------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.        f i l c o  |       \
      | |   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |   |   |   | |NUM|SCL|SCR|MCL| |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | |LCL|MSU|RCL|   | |       \
      | |------------------------------------------------------     | `-----------' |------------SCU| |       \
      | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               |MSL|MSD|MSR|   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | |        |   |   |   |   |   |   |   |   |   |   |   |      |     |   |     |[X]|[X]|[X]|   | |       \
      | |-----------------------------------------------------------| ,-----------. |------------SCD| |       \
      | |    |   |    |   |    |    |       |    |    |    |   |    | |   |   |   | |   LCL |RCL|   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \
                                                                                                              /
  [4] = ACTIONMAP_JIS_110R(                                                                                   \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,WH_L,TRNS,WH_R,BTN3,WH_U, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,BTN1,MS_U,BTN2, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,MS_L,MS_D,MS_R, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,NO,  NO,  NO,   \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,BTN1,BTN2,WH_D),\


// LAYER 5: Dual Scroll Lock ---------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.        f i l c o  |       \
      | |   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |SCL|   |SCR|                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |SCU|   |   | |   |   |   |   | |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |SCD|   |   | |   |   |   |   | |       \
      | |------------------------------------------------------     | `-----------' |------------   | |       \
      | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               |   |   |   |   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | |        |   |   |   |   |   |   |   |   |   |   |   |      |     |   |     |   |   |   |   | |       \
      | |-----------------------------------------------------------| ,-----------. |------------   | |       \
      | |    |   |    |   |    |    |       |    |    |    |   |    | |   |   |   | |       |   |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \
                                                                                                              /
  [5] = ACTIONMAP_JIS_110R(                                                                                   \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,WH_L,TRNS,WH_R,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,WH_U,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,WH_D,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS),\


// LAYER 6: FN -----------------------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.        f i l c o  |       \
      | |   |   |VLU|VLD|MUT|RWD| |PRV|PLY|STP|NXT| |FWD|   |   |SLP| |   |   |   |                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |   |   |   |   |   |   |   |   |   |   |   |   |   |GPG|   | |   |LMX|LUP| |CLC|   |   |MKY| |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | |     |   |   |   |   |   |   |   |   |   |   |   |   |LOCK | |   |LMN|LDW| |   |   |   |   | |       \
      | |------------------------------------------------------     | `-----------' |------------   | |       \
      | |      |   |   |   |   |   |   |   |   |   |   |   |   |FN  |               |   |   |   |   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | |        |   |   |   |   |   |   |   |   |   |URL|   |      |     |   |     |   |   |   |   | |       \
      | |-----------------------------------------------------------| ,-----------. |------------   | |       \
      | |    |GM |    |   |    |    | CLEAR |    | US |MENU|   |    | |   |   |   | |       |   |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \
                                                                                                              /
  [6] = ACTIONMAP_JIS_110R(                                                                                   \
    NO,  VOLU,VOLD,MUTE,MRWD,MPRV,MPLY,MSTP,MNXT,MFFD,NO,  WAKE,SLEP,NO,  NO,  NO,  NO,  CALC,NO,  MSKY,NO,   \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  MGPG,NO,  LED1,LEDU,LDUH,NO,  NO,  NO,   \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  LED0,LEDD,LDDH,NO,  NO,  NO,   \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  FNON,NO,  NO,  NO,  NO,  NO,  NO,  NO,   \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  MURL,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,   \
    NO,  LRGM,NO,  NO,  NO,  NO,  CLAL,NO,  FNOF,APP, TRNS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO),  \


// LAYER 7: FN [LOCKED] --------------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.        f i l c o  |       \
      | |   |   |VLU|VLD|MUT|RWD| |PRV|PLY|STP|NXT| |FWD|   |   |SLP| |   |   |   |                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |   |   |   |   |   |   |   |   |   |   |   |   |   |GPG|   | |LMX|LUP|LUH| |CLC|   |   |MKY| |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |LMN|LDN|LDH| |   |   |   |   | |       \
      | |------------------------------------------------------ [-] | `-----------' |------------   | |       \
      | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               |   |   |   |   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | |        |   |   |   |   |   |   |   |   |   |URL|   |      |     |   |     |   |   |   |   | |       \
      | |-----------------------------------------------------------| ,-----------. |------------   | |       \
      | |    |GM |    |   |    |    | CLEAR |    | US |MENU|   |    | |   |   |   | |       |   |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \
                                                                                                              /
  [7] = ACTIONMAP_JIS_110R(                                                                                   \
    FNOF,VOLU,VOLD,MUTE,MRWD,MPRV,MPLY,MSTP,MNXT,MFFD,FNOF,WAKE,SLEP,FNOF,FNOF,FNOF,FNOF,CALC,FNOF,MSKY,FNOF, \
    FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,MGPG,FNOF,LED1,LEDU,LDUH,FNOF,FNOF,FNOF, \
    FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,LED0,LEDD,LDDH,FNOF,FNOF,FNOF, \
    FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,NO,  FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF, \
    FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,MURL,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF, \
    FNOF,LRGM,FNOF,FNOF,FNOF,FNOF,CLAL,FNOF,FNOF,APP, TRNS,TRNS,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF,FNOF),\


//                        ||
//                        || 
//  ADD MORE LAYERS HERE  ||  -----------------------------------------------------------------------------------
//                       \  /
//                        \/




 
//                        /\
//                       /  \
//  ADD MORE LAYERS HERE  ||  -----------------------------------------------------------------------------------
//                        ||
//                        ||


// LAYER 15: PIN / PASSOWRDS LAYER ---------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.        f i l c o  |       \
      | |   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |   |P1 |P2 |P3 |   |   |   |   |   |   |   |   |   |   |   | |   |   |   | |   |   |   |   | |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | |   |   |   |   | |       \
      | |------------------------------------------------------     | `-----------' |------------   | |       \
      | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               |   |   |   |   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | |        |   |   |   |   |   |   |   |   |   |   |   |      |     |   |     | P1| P2| P3|   | |       \
      | |-----------------------------------------------------------| ,-----------. |------------   | |       \
      | |    |   |    |   |    |    |       |    |    |    |   |    | |   |   |   | |       |   |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \
                                                                                                              /
  [15] = ACTIONMAP_JIS_110R(                                                                                  \
    PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF, \
    PLOF,PSW1,PSW2,PSW3,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF, \
    PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF, \
    PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF, \
    PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PSW1,PSW2,PSW3, \
    PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF,PLOF),\
};
