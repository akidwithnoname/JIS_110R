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

// SET PIN
char pin[] = ""; // USB HID hex values in decimal [ "899195" = "Keypad 137" ] 

// SET PIN CHARECTER COUNT 
char pin_char_current[0]; // "pin_char_current" and "str_action" Must be egual to number of digits in "pin"
char str_action[0];

// PIN ACTION [ runs once every time correct pin is input ]
static void pin_action(void) { }
