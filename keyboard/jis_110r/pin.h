/*
Copyright 2017 Tobi Sakatoi <tobizehpanda@gmail.com>

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

#include "action_layer.h"

// SET PIN
char pin[] = "828281818079807954"; // USB HID hex values in decimal [ "828281818079807954" = "52 52 51 51 50 4F 50 4F 05 04" = "KONAMI code" ] 

// SET PIN CHARECTER COUNT 
char pin_char_current[18]; // "pin_char_current" and "str_action" Must be egual to number of digits in "pin"
char str_action[18];

// PIN ACTION [ runs once every time correct pin is input ]
static void pin_action(void)
{
	// CTRL & A + BACKSPACE 
	add_key(KC_LCTRL);
	add_key(KC_A);
	send_keyboard_report();
	del_key(KC_LCTRL);
	del_key(KC_A);
	add_key(KC_BSPACE);
	send_keyboard_report();
	del_key(KC_BSPACE);
	send_keyboard_report();
	// BACKSPACE NUMBER OF CHARECTERS IN PIN
	for (int i = strlen(pin)/2; i > 0; i--){
		add_key(KC_BSPACE);
		send_keyboard_report();
		del_key(KC_BSPACE);
		send_keyboard_report();
	}
	// DELETE NUMBER OF CHARECTERS IN PIN
	for (int i = strlen(pin)/2; i > 0; i--){
		add_key(KC_DELETE);
		send_keyboard_report();
		del_key(KC_DELETE);
		send_keyboard_report();
	} 

	layer_on(15); // set layer 15 [PIN / PASSWORD LAYER] on 
}

