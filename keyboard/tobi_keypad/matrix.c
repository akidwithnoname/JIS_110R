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
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "wait.h"


#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif
static uint8_t debouncing = DEBOUNCE;

// matrix state [1=on |  0=off] 
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);


void matrix_init(void)
{
    // initialize row and col
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

}

uint8_t matrix_scan(void)
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        _delay_us(30);  // without this wait read unstable value
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}


// Column pin configuration
// col  0   1   2   3 
// pin: D1  D0  D3  D2

static void  init_cols(void)
{
    // Input with pull-up
    DDRD  &= ~(1<<0 | 1<<1 | 1<<2 | 1<<3);
    PORTD |=  (1<<0 | 1<<1 | 1<<2 | 1<<3);
    
}

// Returns status of switches [1=on | 0=off]
static matrix_row_t read_cols(void)
{
    return  (PIND&(1<<0) ? 0 : (1<<1)) |
            (PIND&(1<<1) ? 0 : (1<<0)) |
            (PIND&(1<<2) ? 0 : (1<<3)) |
            (PIND&(1<<3) ? 0 : (1<<2)) ;
}

// Row pin configuration
// row: 0   1   2   3   4
// pin: B2  B3  B7  B0  B1

static void unselect_rows(void)
{
    // Hi-Z to unselect
    DDRB  &= ~0b11111111;
    PORTB &= ~0b11111111;
}

static void select_row(uint8_t row)
{
    // Output low to select
    switch (row) {
        case 0:
            DDRB  |= (1<<2);
            PORTB &= ~(1<<2);
            break;
        case 1:
            DDRB  |= (1<<3);
            PORTB &= ~(1<<3);
            break;
        case 2:
            DDRB  |= (1<<7);
            PORTB &= ~(1<<7);
            break;
        case 3:
            DDRB  |= (1<<0);
            PORTB &= ~(1<<0);
            break;
        case 4:
            DDRB  |= (1<<1);
            PORTB &= ~(1<<1);
            break;
    }
}



