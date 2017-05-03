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
#include "tobi_keypad.h"
#include "action_layer.h"
#include <string.h>
#include "debug.h"
#include "wait.h"

// KEYBOARD ACTION MAP LAYERS --------------------------------------------------------------------------------

const action_t PROGMEM actionmaps[][MATRIX_ROWS][MATRIX_COLS] = {

// LAYER 0: ---------------------\
      ,-------------------.      \
      |                   |      \
      |                   |      \
      | ,---------------. |      \
      | |NUM| / | * | - | |      \
      | |---------------| |      \
      | | 7 | 8 | 9 | + | |      \
      | |---------------| |      \
      | | 4 | 5 | 6 |PGU| |      \
      | |---------------| |      \
      | | 1 | 2 | 3 |PGD| |      \
      | |---------------| |      \
      | | 0 |BS | . |ENT| |      \
      | `---------------' |      \
      `-------------------'      \
                                  
  [0] = ACTIONMAP_tobi_keypad(   \
    NLCK,PSLS,PAST,PMNS,         \
    P7,  P8,  P9,  PPLS,         \
    P4,  P5,  P6,  PGUP,         \
    P1,  P2,  P3,  PGDN,         \
    P0,  BSPC,PDOT,PENT),        
};
