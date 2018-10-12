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

void pwm_timer_init(void);
void pwm_timer_enable(void);
void pwm_timer_disable(void);

void led_brightness_min(void);
void led_brightness_max(void);
void led_brightness_up(void);
void led_brightness_up_highres(void);
void led_brightness_down(void);
void led_brightness_down_highres(void);

void led_animation_on(void);
void led_animation_off(void);

void keypad_led_animation_on(void);
void keypad_led_animation_off(void);
void keypad_led_solid_on(void);
void keypad_led_solid_off(void);

void caps_lock_led_animation_on(void);
void caps_lock_led_animation_off(void);
void caps_lock_led_solid_on(void);
void caps_lock_led_solid_off(void);

void num_lock_led_animation_on(void);
void num_lock_led_animation_off(void);
void num_lock_led_solid_on(void);
void num_lock_led_solid_off(void);

void meta_led_animation_on(void);
void meta_led_animation_off(void);
void meta_led_solid_on(void);
void meta_led_solid_off(void);

void kana_led_animation_on(void);
void kana_led_animation_off(void);
void kana_led_solid_on(void);
void kana_led_solid_off(void);

void scroll_lock_led_animation_on(void);
void scroll_lock_led_animation_off(void);
void scroll_lock_led_solid_on(void);
void scroll_lock_led_solid_off(void);

void fn_led_animation_on(void);
void fn_led_animation_off(void);
void fn_led_solid_on(void);
void fn_led_solid_off(void);

void special_led_animation_on(void);
void special_led_animation_off(void);

void loading_led_animation_on(void);
void loading_led_animation_off(void);

void typing_led_animation_on(void);
void typing_led_animation_off(void);

void bt_link_led_solid_on(void);
void center_led_solid_on(void);
void usb_link_led_solid_on(void);
void bt_link_led_solid_off(void);
void center_led_solid_off(void);
void usb_link_led_solid_off(void);

void usb_nc_led_animation_on(void);
void usb_nc_led_animation_off(void);

void bt_nc_led_animation_on(void);
void bt_nc_led_animation_off(void);

bool rn42_connected(void);
