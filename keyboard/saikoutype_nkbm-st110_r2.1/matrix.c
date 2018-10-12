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
// col  0   1   2   3   4   5   6   7   8   9   10  11  12  13  14 
// pin: FO  F1  F2  F3  F4  F5  F6  F7  C0  C1  C2  C3  C4  C5  C6

static void  init_cols(void)
{
    // Input with pull-up
    DDRF  &= ~(1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6 | 1<<7);
    PORTF |=  (1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6 | 1<<7);
    DDRC  &= ~(1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6);
    PORTC |=  (1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6);
    
}

// Returns status of switches [1=on | 0=off]
static matrix_row_t read_cols(void)
{
    return (PINF&(1<<0) ? 0 : (1<<0)) |
           (PINF&(1<<1) ? 0 : (1<<1)) |
           (PINF&(1<<2) ? 0 : (1<<2)) |
           (PINF&(1<<3) ? 0 : (1<<3)) |
           (PINF&(1<<4) ? 0 : (1<<4)) |
           (PINF&(1<<5) ? 0 : (1<<5)) |
           (PINF&(1<<6) ? 0 : (1<<6)) |
           (PINF&(1<<7) ? 0 : (1<<7)) |
           (PINC&(1<<0) ? 0 : (1<<8)) |
           (PINC&(1<<1) ? 0 : (1<<9)) |
           (PINC&(1<<2) ? 0 : (1<<10)) |
           (PINC&(1<<3) ? 0 : (1<<11)) |
           (PINC&(1<<4) ? 0 : (1<<12)) |
           (PINC&(1<<5) ? 0 : (1<<13)) |
           (PINC&(1<<6) ? 0 : (1UL<<14));          
}

// Row pin configuration
// row: 0   1   2   3   4   5   6   7
// pin: A0  A1  A2  A3  A4  A5  A6  A7

static void unselect_rows(void)
{
    // Hi-Z to unselect
    DDRA  &= ~0b11111111;
    PORTA &= ~0b11111111;
}

static void select_row(uint8_t row)
{
    // Output low to select
    switch (row) {
        case 0:
            DDRA  |= (1<<0);
            PORTA &= ~(1<<0);
            break;
        case 1:
            DDRA  |= (1<<1);
            PORTA &= ~(1<<1);
            break;
        case 2:
            DDRA  |= (1<<2);
            PORTA &= ~(1<<2);
            break;
        case 3:
            DDRA  |= (1<<3);
            PORTA &= ~(1<<3);
            break;
        case 4:
            DDRA  |= (1<<4);
            PORTA &= ~(1<<4);
            break;
        case 5:
            DDRA  |= (1<<5);
            PORTA &= ~(1<<5);
            break;
        case 6:
            DDRA  |= (1<<6);
            PORTA &= ~(1<<6);
            break;
        case 7:
            DDRA  |= (1<<7);
            PORTA &= ~(1<<7);
            break;
    }
}

