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
    ZKHK,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,FN5, PAUS,PSLS,NLCK,PAST,PMNS,PPLS, \
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,INS ,HOME,PGUP,NO,  NO,  NO,   \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,NO,  NO,  DEL, END, PGDN,P7,  P8,  P9,   \
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,BSLS,ENT, NO,  NO,  NO,  NO,  P4,  P5,  P6,   \
    FN6, Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RO,  FN7, NO,  NO,  NO,  UP,  NO,  P1,  P2,  P3,   \
    CAPS,LGUI,LALT,MHEN, ENT,BSPC, SPC,HENK,KANA,RALT,FN0, RCTL,NO,  NO,  NO,  LEFT,DOWN,RGHT,P0  ,PDOT,FN30),

   
// 1: JIS110R - Game Compatibility Mode 1 --------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
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
      | |CAP |G2 |ALT |MHEN| -  | +  |SPACE |HENK|KANA|ALT |FN |CTRL| |LEF|DOW|RIG| |   0   | . |HEX| |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  KEYMAP_JIS110R(
    ZKHK,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,FN5, PAUS,PSLS,NLCK,PAST,PMNS,PPLS, \
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,INS ,HOME,PGUP,NO,  NO,  NO,   \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,NO,  NO,  DEL, END, PGDN,P7,  P8,  P9,   \
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,BSLS,ENT, NO,  NO,  NO,  NO,  P4,  P5,  P6,   \
    FN6, Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RO,  FN7, NO,  NO,  NO,  UP,  NO,  P1,  P2,  P3,   \
    CAPS,FN4, LALT,MHEN,PMNS,PPLS,SPC, HENK,KANA,RALT,TRNS,RCTL,NO,  NO,  NO,  LEFT,DOWN,RGHT,P0  ,PDOT,FN30),


// 2: JIS110R - Game Compatibility Mode 2 [for really bad games] ---------------------------------------------\
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
      | |CTRL|G1 |ALT |ALT |SPCE|ENT |SPACE |ALT |ALT |ALT |FN |CTRL| |LEF|DOW|RIG| |   0   | . |HEX| |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  KEYMAP_JIS110R(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,FN5, PAUS,PSLS,NLCK,PAST,PMNS,PPLS, \
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,INS ,HOME,PGUP,NO,  NO,  NO,   \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,NO,  NO,  DEL, END, PGDN,P7,  P8,  P9,   \
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,BSLS,ENT, NO,  NO,  NO,  NO,  P4,  P5,  P6,   \
    FN6, Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RO,  FN7, NO,  NO,  NO,  UP,  NO,  P1,  P2,  P3,   \
    LCTL,FN3, LALT,LALT,SPC, ENT, SPC, RALT,RALT,RALT,TRNS,RCTL,NO,  NO,  NO,  LEFT,DOWN,RGHT,P0  ,PDOT,FN30),


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
      | |    |   |    |    |    |    |      |    |    |    |   |    | |   |   |   | | SPACE | x |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  KEYMAP_JIS110R(
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN23,FN22,FN21, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN26,FN25,FN24, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN29,FN28,FN27, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,SPC, X,   TRNS),


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
      | |    |   |    |    |    |    |      |    |    |    |   |    | |   |   |   | |   LCL |RCL|   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  KEYMAP_JIS110R(
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,WH_L,TRNS,WH_R,BTN3,WH_U, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,BTN1,MS_U,BTN2, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,MS_L,MS_D,MS_R, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,NO,  NO,  NO,   \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,BTN1,BTN2,WH_D),


// 5: JIS110R - Modern Scroll Lock [mouse wheel] -------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |       \
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

  KEYMAP_JIS110R(
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,WH_U,TRNS,TRNS,TRNS,TRNS, \
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,WH_L,WH_D,WH_R,TRNS,TRNS,TRNS),


// 6: JIS110R - FN -------------------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |       \
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
      | |    |GM |    |    |    |    |      |    |    |MENU|   |    | |   |   |   | |       |   |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  KEYMAP_JIS110R(
    NO,  VOLU,VOLD,MUTE,MRWD,MPRV,MPLY,MSTP,MNXT,MFFD,NO,  NO,  SLEP,NO,  NO,  NO,  NO,  CALC,NO,  FN31,NO,   \
    FN2, NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  FN19,NO,  NO,  NO,  NO,  NO,  NO,  NO,   \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,   \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  FN1, NO,  NO,  NO,  NO,  NO,  NO,  NO,   \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  FN20,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,   \
    NO,  FN3, NO,  NO,  NO,  NO,  NO,  NO,  NO,  APP, TRNS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  FN0 ),


// 7: JIS110R - FN LOCK---------------------------------------------------------------------------------------\
      ,-----------------------------------------------------------------------------------------------.       \
      | ,---.   ,---------------. ,---------------. ,---------------. ,-----------.                   |       \
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
      | |    |GM |    |    |    |    |      |    |    |MENU|   |    | |   |   |   | |       |   |   | |       \
      | `-----------------------------------------------------------' `-----------' `---------------' |       \
      `-----------------------------------------------------------------------------------------------'       \

  KEYMAP_JIS110R(
    FN1, VOLU,VOLD,MUTE,MRWD,MPRV,MPLY,MSTP,MNXT,MFFD,FN1, FN1, SLEP,FN1, FN1, FN1, FN1, CALC,FN1, FN31,FN1,  \
    FN2, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN19,FN1, FN1, FN1, FN1, FN1, FN1, FN1,  \
    FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1,  \
    FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1,  \
    FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN20,FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1,  \
    FN1, FN3, FN1, FN1, FN1, FN1, FN1, FN1, FN1, APP, TRNS,TRNS,FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN1, FN0 ),
    };



// SET MACRO IDs ---------------------------------------------------------------------------------------------
enum macro_id {
    URL,
    GPG_KEY,
};



// FN ACTIONS ------------------------------------------------------------------------------------------------
const action_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(6),                // FN
    [1] = ACTION_LAYER_ON(7, ON_BOTH),              // FN LOCK
    [2] = ACTION_LAYER_SET(0, ON_RELEASE),          // JP  
    [3] = ACTION_LAYER_SET(1, ON_RELEASE),          // Game Compatibility Mode 1
    [4] = ACTION_LAYER_SET(2, ON_RELEASE),          // Game Compatibility Mode 2
    [5] = ACTION_LAYER_TOGGLE(5),                   // Modern Scroll Lock [mouse wheel]
    [6] = ACTION_MODS_ONESHOT(MOD_LSFT),            // Tap left shift to activate for 1 keypress
    [7] = ACTION_MODS_ONESHOT(MOD_RSFT),            // Tap right shift to activate for 1 keypress
//  [8] = 
//  [9] =
//  [10] =
//  [11] =
//  [12] =
//  [13] =
//  [14] =
//  [15] =
//  [16] =
//  [17] =
//  [18] =
    [19] = ACTION_MACRO(GPG_KEY),                   // unix-[wget & install shion-os public GPG key]
    [20] = ACTION_MACRO(URL),                       // url-[null-bin.blogspot.com]
    [21] = ACTION_MODS_KEY(MOD_LSFT, KC_F),         // HEX Keypad-[F]
    [22] = ACTION_MODS_KEY(MOD_LSFT, KC_E),         // HEX Keypad-[E]
    [23] = ACTION_MODS_KEY(MOD_LSFT, KC_D),         // HEX Keypad-[D]
    [24] = ACTION_MODS_KEY(MOD_LSFT, KC_C),         // HEX Keypad-[C]
    [25] = ACTION_MODS_KEY(MOD_LSFT, KC_B),         // HEX Keypad-[B]
    [26] = ACTION_MODS_KEY(MOD_LSFT, KC_A),         // HEX Keypad-[A]
    [27] = ACTION_MODS_KEY(MOD_LSFT, KC_6),         // HEX Keypad-[&]
    [28] = ACTION_MODS_KEY(MOD_LSFT, KC_5),         // HEX Keypad-[%]
    [29] = ACTION_MODS_KEY(MOD_LSFT, KC_3),         // HEX Keypad-[#]
    [30] = ACTION_LAYER_TAP_KEY(3, KC_PENT),        // HEX Keypad
    [31] = ACTION_LAYER_TOGGLE(4),                  // Mouse Keypad
};



// MACRO FUNCTIONS -------------------------------------------------------------------------------------------
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case GPG_KEY:      // unix-[wget & install shion-os public GPG key]
            return (record->event.pressed ?
                    MACRO( I(5), T(C), T(D), T(SPC), T(SLSH), T(T), T(M), T(P), T(SPC), D(LSHIFT), D(6),      \
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
                    MACRO( I(5), T(N), T(U), T(L), T(L), T(MINS), T(B), T(I), T(N), T(DOT), T(B), T(L), T(O), \
                    T(G), T(S), T(P), T(O), T(T), T(DOT), T(C), T(O), T(M), END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}
