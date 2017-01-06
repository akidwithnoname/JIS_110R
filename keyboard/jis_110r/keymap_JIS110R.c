#include "keymap_common.h"



// KEYMAPS ---------------------------------------------------------------------------------------------------
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// 0: JIS110R - JP -------------------------------------------------------------------------------------------\
       ,----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |       \
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

  KEYMAP_JIS110R(
    ZKHK,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,SLCK,PAUS,PSLS,NLCK,PAST,PMNS,PPLS, \
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,INS ,HOME,PGUP,NO,  NO,  NO,   \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,NO,  NO,  DEL, END, PGDN,P7,  P8,  P9,   \
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,BSLS,ENT, NO,  NO,  NO,  NO,  P4,  P5,  P6,   \
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM, DOT,SLSH,RO,  RSFT,NO,  NO,  NO,  UP,  NO,  P1,  P2,  P3,   \
    CAPS,LGUI,LALT,MHEN, ENT,BSPC, SPC,HENK,KANA,RALT,FN0, RCTL,NO,  NO,  NO,  LEFT,DOWN,RGHT,P0  ,PDOT,FN31),

   
// 1: JIS110R - Game Compatibility Mode 1 --------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |       \
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
      | |CAP |FN |ALT | /  | -  | +  |SPACE | *  | .  |ALT |FN |CTRL| |LEF|DOW|RIG| |   0   | . |HEX| |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  KEYMAP_JIS110R(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,SLCK,PAUS,PSLS,NLCK,PAST,PMNS,PPLS, \
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,INS ,HOME,PGUP,NO,  NO,  NO,   \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,NO,  NO,  DEL, END, PGDN,P7,  P8,  P9,   \
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,BSLS,ENT, NO,  NO,  NO,  NO,  P4,  P5,  P6,   \
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM, DOT,SLSH,RO,  RSFT,NO,  NO,  NO,  UP,  NO,  P1,  P2,  P3,   \
    CAPS,FN0, LALT,PSLS,PMNS,PPLS,SPC, PAST,PDOT,RALT,FN0, RCTL,NO,  NO,  NO,  LEFT,DOWN,RGHT,P0  ,PDOT,FN31),


// 2: JIS110R - Game Compatibility Mode 2 (for really bad games) ---------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |       \
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
      | |CTRL|FN |ALT |ALT |SPCE|ENT |SPACE |ALT |ALT |ALT |FN |CTRL| |LEF|DOW|RIG| |   0   | . |HEX| |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  KEYMAP_JIS110R(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,SLCK,PAUS,PSLS,NLCK,PAST,PMNS,PPLS, \
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,INS ,HOME,PGUP,NO,  NO,  NO,   \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,NO,  NO,  DEL, END, PGDN,P7,  P8,  P9,   \
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,BSLS,ENT, NO,  NO,  NO,  NO,  P4,  P5,  P6,   \
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM, DOT,SLSH,RO,  RSFT,NO,  NO,  NO,  UP,  NO,  P1,  P2,  P3,   \
    LCTL,FN0, LALT,LALT,SPC, ENT,SPC, RALT,RALT,RALT,FN0, RCTL,NO,  NO,  NO,  LEFT,DOWN,RGHT,P0  ,PDOT,FN31),


// 3: JIS110R - HEX Keypad -----------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |       \
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
      | |    |   |    |    |    |    |      |    |    |    |FN |    | |   |   |   | | SPACE | x |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  KEYMAP_JIS110R(
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN23,FN22,FN21, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN26,FN25,FN24, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN29,FN28,FN27, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN0, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,SPC, X,   TRNS),


// 4: JIS110R - Mouse Keypad ---------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |       \
      | |   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   |                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | |   |   |   | |   |SCL|SCR|MCL| |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | |LCL|MSU|RCL|   | |       \
      | |------------------------------------------------------     | `-----------' |------------SCU| |       \
      | |      |   |   |   |   |   |   |   |   |   |   |   |   |    |               |MSL|MSD|MSR|   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | |        |   |   |   |   |   |   |   |   |   |   |   |      |     |   |     |   |   |   |   | |       \
      | |-----------------------------------------------------------| ,-----------. |------------SCD| |       \
      | |    |   |    |    |    |    |      |    |    |    |FN |    | |   |   |   | |   LCL |RCL|   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  KEYMAP_JIS110R(
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,WH_L,TRNS,WH_R,BTN3,WH_U, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,BTN1,MS_U,BTN2, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,MS_L,MS_D,MS_R, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,NO,  NO,  NO,   \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN0, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,BTN1,BTN2,WH_D),


// 5: JIS110R - FN0 ------------------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |       \
      | |   |   |VLU|VLD|MUT|RWD| |PRV|PLY|STP|NXT| |FWD|   |   |SLP| |   |   |   |                   |       \
      | `---'   `---------------' `---------------' `---------------' `-----------'       o   o   o   |       \
      | ,-----------------------------------------------------------. ,-----------. ,---------------. |       \
      | |LR0|LR1|LR2|   |   |   |   |   |   |   |   |   |   |   |   | |   |   |   | |CLC|   |   |MSE| |       \
      | |-----------------------------------------------------------| |-----------| |---------------| |       \
      | |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | |   |   |   |   | |       \
      | |------------------------------------------------------     | `-----------' |------------   | |       \
      | |      |   |   |   |   |   |   |   |GPG|   |   |   |   |    |               |   |   |   |   | |       \
      | |-----------------------------------------------------------|     ,---.     |---------------| |       \
      | |        |   |   |   |   |   |   |   |   |   |URL|   |      |     |   |     |   |   |   |   | |       \
      | |-----------------------------------------------------------| ,-----------. |------------   | |       \
      | |    |   |    |    |    |    |      |    |    |MENU|FN |    | |   |   |   | |       |   |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  KEYMAP_JIS110R(
    FN0, VOLU,VOLD,MUTE,MRWD,MPRV,MPLY,MSTP,MNXT,MFFD,FN0, FN0, SLEP,FN0, FN0, FN0, FN0, CALC,FN0, FN30,FN0,  \
    FN1, FN2, FN3, FN4, FN5, FN6, FN7, FN8, FN9, FN10,FN11,FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0,  \
    FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0,  \
    FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN19,FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0,  \
    FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN20,FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0,  \
    FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, APP, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0, FN0 ),
    };



// SET MACRO IDs ---------------------------------------------------------------------------------------------
enum macro_id {
    URL,
    GPG_KEY,
    HEX_OCA,
    HEX_PCT,
    HEX_AND,
    HEX_A,
    HEX_B,
    HEX_C,
    HEX_D,
    HEX_E,
    HEX_F,
};



// FN ACTIONS ------------------------------------------------------------------------------------------------
const action_t PROGMEM fn_actions[] = {
    // MODE
    [1] = ACTION_LAYER_SET_CLEAR(0),           // JP  
    [2] = ACTION_LAYER_SET_CLEAR(1),           // Game Compatibility Mode 1
    [3] = ACTION_LAYER_SET_CLEAR(2),           // Game Compatibility Mode 2
    // LAYER
    [0] = ACTION_LAYER_TAP_TOGGLE(5),          // FN0
    [30] = ACTION_LAYER_TOGGLE(4),             // Mouse Keypad
    [31] = ACTION_LAYER_TAP_KEY(3, KC_PENT),   // HEX Keypad
    // MACRO
    [19] = ACTION_MACRO(GPG_KEY),              // unix-[wget & install shion-os public GPG key]
    [20] = ACTION_MACRO(URL),                  // url-[null-bin.blogspot.com]
    [21] = ACTION_MACRO(HEX_F),                // HEX Keypad-[F]
    [22] = ACTION_MACRO(HEX_E),                // HEX Keypad-[E]
    [23] = ACTION_MACRO(HEX_D),                // HEX Keypad-[D]
    [24] = ACTION_MACRO(HEX_C),                // HEX Keypad-[C]
    [25] = ACTION_MACRO(HEX_B),                // HEX Keypad-[B]
    [26] = ACTION_MACRO(HEX_A),                // HEX Keypad-[A]
    [27] = ACTION_MACRO(HEX_AND),              // HEX Keypad-[&]
    [28] = ACTION_MACRO(HEX_PCT),              // HEX Keypad-[%]
    [29] = ACTION_MACRO(HEX_OCA),              // HEX Keypad-[#]
};



// MACRO FUNCTIONS -------------------------------------------------------------------------------------------
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case GPG_KEY:      // unix-[wget & install shion-os public GPG key]
            return (record->event.pressed ?
                    MACRO( I(0), T(C), T(D), T(SPC), T(SLSH), T(T), T(M), T(P), T(SPC), D(LSHIFT), D(6),      \
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
        case URL:          // url-[null-bin.blogspot.com]
            return (record->event.pressed ?
                    MACRO( I(0), T(N), T(U), T(L), T(L), T(MINS), T(B), T(I), T(N), T(DOT), T(B), T(L), T(O), \
                    T(G), T(S), T(P), T(O), T(T), T(DOT), T(C), T(O), T(M), END ) :
                    MACRO_NONE );
        case HEX_OCA:      // HEX Keypad-[#]
            return (record->event.pressed ?
                    MACRO( D(LSHIFT), D(3), U(LSHIFT), U(3), END ) :
                    MACRO_NONE );
        case HEX_PCT:      // HEX Keypad-[%]
            return (record->event.pressed ?
                    MACRO( D(LSHIFT), D(5), U(LSHIFT), U(5), END ) :
                    MACRO_NONE );
        case HEX_AND:      // HEX Keypad-[&]
            return (record->event.pressed ?
                    MACRO( D(LSHIFT), D(6), U(LSHIFT), U(6), END ) :
                    MACRO_NONE );
        case HEX_A:        // HEX Keypad-[A]
            return (record->event.pressed ?
                    MACRO( D(LSHIFT), D(A), U(LSHIFT), U(A), END ) :
                    MACRO_NONE );
        case HEX_B:        // HEX Keypad-[B]
            return (record->event.pressed ?
                    MACRO( D(LSHIFT), D(B), U(LSHIFT), U(B), END ) :
                    MACRO_NONE );
        case HEX_C:        // HEX Keypad-[C]
            return (record->event.pressed ?
                    MACRO( D(LSHIFT), D(C), U(LSHIFT), U(C), END ) :
                    MACRO_NONE );
        case HEX_D:        // HEX Keypad-[D]
            return (record->event.pressed ?
                    MACRO( D(LSHIFT), D(D), U(LSHIFT), U(D), END ) :
                    MACRO_NONE );
        case HEX_E:        // HEX Keypad-[E]
            return (record->event.pressed ?
                    MACRO( D(LSHIFT), D(E), U(LSHIFT), U(E), END ) :
                    MACRO_NONE );
        case HEX_F:        // HEX Keypad-[F]
            return (record->event.pressed ?
                    MACRO( D(LSHIFT), D(F), U(LSHIFT), U(F), END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}
