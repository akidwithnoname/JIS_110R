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
#include "led.h"
#include "wait.h"
#include "led_def.h"



// ACTION DEFINITIONS ----------------------------------------------------------------------------------------

// SET LAYERS
   #define AC_LRJP      ACTION_LAYER_SET(0, ON_RELEASE)                 // JP  
   #define AC_LRG1      ACTION_LAYER_SET(1, ON_RELEASE)                 // Game Compatibility Mode 1
   #define AC_LRG2      ACTION_LAYER_SET(2, ON_RELEASE)                 // Game Compatibility Mode 2

// FN LAYERS [MOMENTARY]
   #define AC_FNNM      ACTION_LAYER_MOMENTARY(6)                       // FN
   #define AC_FNGM      ACTION_LAYER_MOMENTARY(8)                       // GAME FN

// FN LAYERS [TOGGLE]
   #define AC_FNNL      ACTION_LAYER_ON(7, ON_BOTH)                     // FN [LOCKED]
   #define AC_FNGL      ACTION_LAYER_ON(9, ON_BOTH)                     // GAME FN [LOCKED]

// MOUSE KEYPAD
   #define AC_MSKY      ACTION_LAYER_TOGGLE(4)                          // Mouse Keypad

// SHIFT HEX KEYPAD
   #define AC_SHEX      ACTION_LAYER_TAP_KEY(3, KC_PENT)                // Shift HEX Keypad
   #define AC_HEXF      ACTION_MODS_KEY(MOD_LSFT, KC_F)                 // HEX Keypad-[F]
   #define AC_HEXE      ACTION_MODS_KEY(MOD_LSFT, KC_E)                 // HEX Keypad-[E]
   #define AC_HEXD      ACTION_MODS_KEY(MOD_LSFT, KC_D)                 // HEX Keypad-[D]
   #define AC_HEXC      ACTION_MODS_KEY(MOD_LSFT, KC_C)                 // HEX Keypad-[C]
   #define AC_HEXB      ACTION_MODS_KEY(MOD_LSFT, KC_B)                 // HEX Keypad-[B]
   #define AC_HEXA      ACTION_MODS_KEY(MOD_LSFT, KC_A)                 // HEX Keypad-[A]
   #define AC_HEX6      ACTION_MODS_KEY(MOD_LSFT, KC_6)                 // HEX Keypad-[&]
   #define AC_HEX5      ACTION_MODS_KEY(MOD_LSFT, KC_5)                 // HEX Keypad-[%]
   #define AC_HEX3      ACTION_MODS_KEY(MOD_LSFT, KC_3)                 // HEX Keypad-[#]

// DUAL SCROLL LOCK 
   #define AC_SCLK      ACTION_LAYER_TAP_KEY(5, KC_SLCK)                // Hold Scroll Lock for mouse wheel scrolling

// SHIFT MODS
   #define AC_SFTM      ACTION_MODS_ONESHOT(MOD_LSFT)                   // Tap left shift to activate for 1 keypress

// MACROS
   #define AC_MGPG      ACTION_MACRO(GPG_KEY)                           // [wget & install shion-os public GPG key]
   #define AC_MURL      ACTION_MACRO(URL)                               // [null-bin.blogspot.com]

// LED EFFECTS
   #define AC_CLAL      ACTION_FUNCTION(CLEAR_AND_LOAD)                // Clear all layers, turn off key locks, and make LEDs dance!




// SET FUNCTION IDs ------------------------------------------------------------------------------------------
enum function_id {
    CLEAR_AND_LOAD,
};




// FUNCTION DEFINITIONS --------------------------------------------------------------------------------------
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (id == CLEAR_AND_LOAD) {

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

        // TURN OFF ALL LEDS
	jis_110r_led_off_all();

        // PLAY LOADING ANIMATION
        jis_110r_loading_animation();
        jis_110r_loading_animation();
        jis_110r_loading_animation();
        jis_110r_loading_animation();
        jis_110r_loading_animation();

    }

}




// SET MACRO IDs ---------------------------------------------------------------------------------------------
enum macro_id {
    URL,
    GPG_KEY,
    ALT_TAB,
};




// MACRO DEFINITIONS -----------------------------------------------------------------------------------------
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case GPG_KEY:      // [wget & install shion-os public GPG key]
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
        case URL:          // [null-bin.blogspot.com]
            return (record->event.pressed ?
                    MACRO( I(10), T(N), T(U), T(L), T(L), T(MINS), T(B), T(I), T(N), T(DOT), T(B), T(L), T(O), \
                    T(G), T(S), T(P), T(O), T(T), T(DOT), T(C), T(O), T(M), END ) :
                    MACRO_NONE );
        case ALT_TAB:      // Application Switcher
            return (record->event.pressed ?
                    MACRO( D(LALT), D(TAB), END ) :
                    MACRO( U(TAB), END ));
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
      | |CAP |OS |ALT |MHEN| ENT| BS |SPACE |HENK|KANA|ALT |FN |CTRL| |LEF|DOW|RIG| |   0   | . |HEX| |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `----------------------------------------------------------------------------------------------'        \

  [0] = ACTIONMAP_JIS_110R( \
    ZKHK,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,SCLK,PAUS,PSLS,NLCK,PAST,PMNS,PPLS, \
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,INS ,HOME,PGUP,NO,  NO,  NO,   \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,NO,  NO,  DEL, END, PGDN,P7,  P8,  P9,   \
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,BSLS,ENT, NO,  NO,  NO,  NO,  P4,  P5,  P6,   \
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RO,  SFTM,NO,  NO,  NO,  UP,  NO,  P1,  P2,  P3,   \
    CAPS,LGUI,LALT,MHEN, ENT,BSPC, SPC,HENK,KANA,RALT,FNNM,RCTL,NO,  NO,  NO,  LEFT,DOWN,RGHT,P0  ,PDOT,SHEX),

  
// LAYER 1: Game Compatibility Mode 1 ------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
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
      | |CAP |G2 |ALT |MHEN| -  | +  |SPACE |HENK|KANA|ALT |FN |CTRL| |LEF|DOW|RIG| |   0   | . |HEX| |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  [1] = ACTIONMAP_JIS_110R( \
    ZKHK,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,SCLK,PAUS,PSLS,NLCK,PAST,PMNS,PPLS, \
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,INS ,HOME,PGUP,NO,  NO,  NO,   \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,NO,  NO,  DEL, END, PGDN,P7,  P8,  P9,   \
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,BSLS,ENT, NO,  NO,  NO,  NO,  P4,  P5,  P6,   \
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RO,  SFTM,NO,  NO,  NO,  UP,  NO,  P1,  P2,  P3,   \
    CAPS,LRG2,LALT,MHEN,PMNS,PPLS,SPC, HENK,KANA,RALT,FNGM,RCTL,NO,  NO,  NO,  LEFT,DOWN,RGHT,P0  ,PDOT,SHEX),


// LAYER 2: Game Compatibility Mode 2 [for really bad games] -------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.        f i l c o  |       \
      | |ESC|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PRS|SCL|PAU|                   |       \
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
      | |CTRL|G1 |ALT |ALT |SPCE|ENT |SPACE |ALT |ALT |ALT |FN |CTRL| |LEF|DOW|RIG| |   0   | . |HEX| |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  [2] = ACTIONMAP_JIS_110R( \
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,SCLK,PAUS,PSLS,NLCK,PAST,PMNS,PPLS, \
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,INS ,HOME,PGUP,NO,  NO,  NO,   \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,NO,  NO,  DEL, END, PGDN,P7,  P8,  P9,   \
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,BSLS,ENT, NO,  NO,  NO,  NO,  P4,  P5,  P6,   \
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RO,  SFTM,NO,  NO,  NO,  UP,  NO,  P1,  P2,  P3,   \
    LCTL,LRG1,LALT,LALT,SPC, ENT, SPC, RALT,RALT,RALT,FNGM,RCTL,NO,  NO,  NO,  LEFT,DOWN,RGHT,P0  ,PDOT,SHEX),


// LAYER 3: Shift HEX Keypad ---------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.        f i l c o  |       \
      | |   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |   |   |   | |   |   |   |   | |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | | D | E | F |   | |       \
      | |------------------------------------------------------     | `-----------' |------------   | |       \
      | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               | A | B | C |   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | |        |   |   |   |   |   |   |   |   |   |   |   |      |     |   |     | # | % | & |   | |       \
      | |-----------------------------------------------------------| ,-----------. |------------   | |       \
      | |    |   |    |    |    |    |      |    |    |    |   |    | |   |   |   | | SPACE | x |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  [3] = ACTIONMAP_JIS_110R( \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,HEXD,HEXE,HEXF, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,HEXA,HEXB,HEXC, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,HEX6,HEX5,HEX3, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,SPC, X,   TRNS),


// LAYER 4: Mouse Keypad -------------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.        f i l c o  |       \
      | |   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |   |   |   | |   |SCL|SCR|MCL| |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | |LCL|MSU|RCL|   | |       \
      | |------------------------------------------------------     | `-----------' |------------SCU| |       \
      | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               |MSL|MSD|MSR|   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | |        |   |   |   |   |   |   |   |   |   |   |   |      |     |   |     |[X]|[X]|[X]|   | |       \
      | |-----------------------------------------------------------| ,-----------. |------------SCD| |       \
      | |    |   |    |    |    |    |      |    |    |    |   |    | |   |   |   | |   LCL |RCL|   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  [4] = ACTIONMAP_JIS_110R( \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,WH_L,TRNS,WH_R,BTN3,WH_U, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,BTN1,MS_U,BTN2, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,MS_L,MS_D,MS_R, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,NO,  NO,  NO,   \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,BTN1,BTN2,WH_D),


// LAYER 5: Dual Scroll Lock ---------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.        f i l c o  |       \
      | |   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |   |   |   | |   |   |   |   | |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | |   |   |   |   | |       \
      | |------------------------------------------------------     | `-----------' |------------   | |       \
      | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               |   |   |   |   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | |        |   |   |   |   |   |   |   |   |   |   |   |      |     |SCU|     |   |   |   |   | |       \
      | |-----------------------------------------------------------| ,-----------. |------------   | |       \
      | |    |   |    |    |    |    |      |    |    |    |   |    | |SCL|SCD|SCR| |       |   |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  [5] = ACTIONMAP_JIS_110R( \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,WH_U,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,WH_L,WH_D,WH_R,TRNS,TRNS,TRNS),


// LAYER 6: FN -----------------------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.        f i l c o  |       \
      | |   |   |VLU|VLD|MUT|RWD| |PRV|PLY|STP|NXT| |FWD|   |   |SLP| |   |   |   |                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |JP |   |   |   |   |   |   |   |   |   |   |   |   |GPG|   | |   |   |   | |CLC|   |   |MKY| |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | |     |   |   |   |   |   |   |   |   |   |   |   |   |LOCK | |   |   |   | |   |   |   |   | |       \
      | |------------------------------------------------------     | `-----------' |------------   | |       \
      | |      |   |   |   |   |   |   |   |   |   |   |   |   |FN  |               |   |   |   |   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | |        |   |   |   |   |   |   |   |   |   |URL|   |      |     |   |     |   |   |   |   | |       \
      | |-----------------------------------------------------------| ,-----------. |------------   | |       \
      | |    |GM |    |    |    |    |CLEAR |    |    |MENU|   |    | |   |   |   | |       |   |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  [6] = ACTIONMAP_JIS_110R( \
    NO,  VOLU,VOLD,MUTE,MRWD,MPRV,MPLY,MSTP,MNXT,MFFD,NO,  NO,  SLEP,NO,  NO,  NO,  NO,  CALC,NO,  MSKY,NO,   \
    LRJP,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  MGPG,NO,  NO,  NO,  NO,  NO,  NO,  NO,   \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,   \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  FNNL,NO,  NO,  NO,  NO,  NO,  NO,  NO,   \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  MURL,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,   \
    NO,  LRG1,NO,  NO,  NO,  NO,  CLAL,NO,  NO,  APP, TRNS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  FNNM),


// LAYER 7: FN [LOCKED] --------------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.        f i l c o  |       \
      | |   |   |VLU|VLD|MUT|RWD| |PRV|PLY|STP|NXT| |FWD|   |   |SLP| |   |   |   |                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |JP |   |   |   |   |   |   |   |   |   |   |   |   |GPG|   | |   |   |   | |CLC|   |   |MKY| |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | |   |   |   |   | |       \
      | |------------------------------------------------------     | `-----------' |------------   | |       \
      | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               |   |   |   |   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | |        |   |   |   |   |   |   |   |   |   |URL|   |      |     |   |     |   |   |   |   | |       \
      | |-----------------------------------------------------------| ,-----------. |------------   | |       \
      | |    |GM |    |    |    |    |CLEAR |    |    |MENU|   |    | |   |   |   | |       |   |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  [7] = ACTIONMAP_JIS_110R( \
    LRJP,VOLU,VOLD,MUTE,MRWD,MPRV,MPLY,MSTP,MNXT,MFFD,LRJP,LRJP,SLEP,LRJP,LRJP,LRJP,LRJP,CALC,LRJP,MSKY,LRJP, \
    LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,MGPG,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP, \
    LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP, \
    LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP, \
    LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,MURL,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP, \
    LRJP,LRG1,LRJP,LRJP,LRJP,LRJP,CLAL,LRJP,LRJP,APP, TRNS,TRNS,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,LRJP,FNNM),


// LAYER 8: GAME FN ------------------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.        f i l c o  |       \
      | |   |   |VLU|VLD|MUT|RWD| |PRV|PLY|STP|NXT| |FWD|   |   |SLP| |   |   |   |                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |JP |   |   |   |   |   |   |   |   |   |   |   |   |GPG|   | |   |   |   | |CLC|   |   |MKY| |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | |     |   |   |   |   |   |   |   |   |   |   |   |   |LOCK | |   |   |   | |   |   |   |   | |       \
      | |------------------------------------------------------     | `-----------' |------------   | |       \
      | |      |   |   |   |   |   |   |   |   |   |   |   |   |FN  |               |   |   |   |   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | |        |   |   |   |   |   |   |   |   |   |URL|   |      |     |   |     |   |   |   |   | |       \
      | |-----------------------------------------------------------| ,-----------. |------------   | |       \
      | |    |GM |    |    |    |    |CLEAR |    |    |MENU|   |    | |   |   |   | |       |   |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  [8] = ACTIONMAP_JIS_110R( \
    NO,  VOLU,VOLD,MUTE,MRWD,MPRV,MPLY,MSTP,MNXT,MFFD,NO,  NO,  SLEP,NO,  NO,  NO,  NO,  CALC,NO,  MSKY,NO,   \
    LRJP,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  MGPG,NO,  NO,  NO,  NO,  NO,  NO,  NO,   \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,   \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  FNGL,NO,  NO,  NO,  NO,  NO,  NO,  NO,   \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  MURL,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,   \
    NO,  LRJP,NO,  NO,  NO,  NO,  CLAL,NO,  NO,  APP, TRNS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  FNNM),


// LAYER 9: GAME FN [LOCKED] ---------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.        f i l c o  |       \
      | |   |   |VLU|VLD|MUT|RWD| |PRV|PLY|STP|NXT| |FWD|   |   |SLP| |   |   |   |                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |JP |   |   |   |   |   |   |   |   |   |   |   |   |GPG|   | |   |   |   | |CLC|   |   |MKY| |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | |   |   |   |   | |       \
      | |------------------------------------------------------     | `-----------' |------------   | |       \
      | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               |   |   |   |   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | |        |   |   |   |   |   |   |   |   |   |URL|   |      |     |   |     |   |   |   |   | |       \
      | |-----------------------------------------------------------| ,-----------. |------------   | |       \
      | |    |GM |    |    |    |    |CLEAR |    |    |MENU|   |    | |   |   |   | |       |   |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  [9] = ACTIONMAP_JIS_110R( \
    FNGL,VOLU,VOLD,MUTE,MRWD,MPRV,MPLY,MSTP,MNXT,MFFD,FNGL,FNGL,SLEP,FNGL,FNGL,FNGL,FNGL,CALC,FNGL,MSKY,FNGL, \
    LRJP,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,MGPG,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL, \
    FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL, \
    FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL, \
    FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,MURL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL, \
    FNGL,LRJP,FNGL,FNGL,FNGL,FNGL,CLAL,FNGL,FNGL,APP, TRNS,TRNS,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNGL,FNNM),

};


