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

#include "host_driver.h"

void uart_return(void);
void rn42_reboot(void);
void rn42_enter_cmd(void);
void rn42_set_name(void);
void rn42_mode_hid(void);
void rn42_mode_spp(void);
void rn42_set_default(void);
void rn42_off(void);
void rn42_init(void);

host_driver_t rn42_driver;

#define uart_print(s) uart_print_P(PSTR(s))

#define BAUD_RATE 115200

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
