#include "uart.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include "debug.h"
#include "wait.h"
#include "print.h"
#include "timer.h"
#include "host.h"
#include "host_driver.h"
#include "action.h"
#include "command.h"
#include "action_util.h"
#include "lufa.h"
//#include "led_pwm.h"

// UART FUNCTIONS -------------------------------------------------------------------------------------------------------

#define uart_print(s) uart_print_P(PSTR(s))

void uart_print_P(const char *str)
{
	char c;
	while (1) {
		c = pgm_read_byte(str++);
		if (!c) break;
		uart_putchar(c);
	}
}

void uart_return(void) {
   // wait_ms(50);
    uart_print("\r");
    uart_print("\n");
   // wait_ms(50);
}


// RN42 COMMANDS --------------------------------------------------------------------------------------------------------

void rn42_init(void) {
    DDRE |= (1<<0); 
    PORTE |= (1<<0);
    DDRE  &= ~(1<<1);
    PORTE |=  (1<<1);
}

void rn42_reboot(void) {
    dprint("RN42 Bluetooth: Reboot RN42\n");
    uart_print("R,1");
    uart_return();
    wait_ms(500);
}

void rn42_enter_cmd(void) {
    dprint("RN42 Bluetooth: Enter CMD Mode\n");
    uart_print("$$$");
    uart_return();
}

void rn42_set_name(void) {
    dprint("RN42 Bluetooth: Set Device Name\n");
    uart_print("SN,SaikouType-ST110");
    uart_return();
}

void rn42_mode_hid(void) {
    dprint("RN42 Bluetooth: Set RN42 to HID keyboard+mouse mode\n");
    uart_print("S~,6");
    uart_return();
    uart_print("SH,0000"); 
    uart_return();
    uart_print("SS,Keyboard/Mouse"); 
    uart_return();
    uart_print("SW,0000"); 
    uart_return();
    uart_print("SY,0010"); 
    uart_return();
    uart_print("SQ,16"); 
    uart_return();
    rn42_reboot();
    rn42_enter_cmd();
}

void rn42_mode_spp(void) {
    dprint("RN42 Bluetooth: Set RN42 to SPP mode\n");
    uart_print("SS,SaikouType-ST110-SPP");
    uart_return();
    rn42_reboot();
    rn42_enter_cmd();
    uart_print("SE,2011"); 
    uart_return();
    rn42_reboot();
    rn42_enter_cmd();
}

void rn42_set_default(void) {
    dprint("RN42 Bluetooth: Set Factory Defaults\n");
    uart_print("SF,1");
    uart_return();
    rn42_reboot();
    rn42_enter_cmd();
}

void rn42_off(void) {
    dprint("RN42 Bluetooth: Power off\n");
    uart_print("$$$");
    uart_return();
    uart_print("Z");
    uart_return();
}


// RN42 BLUETOOTH DRIVER ------------------------------------------------------------------------------------------------

//static uint8_t keyboard_leds(void);
static uint8_t leds = 0;
static uint8_t keyboard_leds(void) { return leds; }
static void send_keyboard(report_keyboard_t *report);
static void send_mouse(report_mouse_t *report);
static void send_system(uint16_t data);
static void send_consumer(uint16_t data);

host_driver_t rn42_driver = {
    keyboard_leds,
    send_keyboard,
    send_mouse,
    send_system,
    send_consumer
};

static void send_keyboard(report_keyboard_t *report) {
        uart_putchar(0xFD);            // rn42 raw mode 
	uart_putchar(0x09);            // length
	uart_putchar(0x01);            // descriptor
	uart_putchar(report->mods);    // modifier
	uart_putchar(0x00); 
	uart_putchar(report->keys[0]); // scancode 1
	uart_putchar(report->keys[1]); // scancode 2
	uart_putchar(report->keys[2]); // scancode 3
	uart_putchar(report->keys[3]); // scancode 4
	uart_putchar(report->keys[4]); // scancode 5
	uart_putchar(report->keys[5]); // scancode 6
}

static void send_mouse(report_mouse_t *report)
{
    uart_putchar(0xFD);            // rn42 raw mode
    uart_putchar(0x05);            // length
    uart_putchar(0x02);            // descriptor
    uart_putchar(report->buttons);
    uart_putchar(report->x);
    uart_putchar(report->y);
    uart_putchar(report->v);
}

static uint16_t usage2bits(uint16_t usage)
{
    switch (usage) {
        case APPCONTROL_HOME:         return 0x01;
        case APPLAUNCH_EMAIL:         return 0x02;
        case APPCONTROL_SEARCH:       return 0x04;
        case AUDIO_VOL_UP:            return 0x10;
        case AUDIO_VOL_DOWN:          return 0x20;
        case AUDIO_MUTE:              return 0x40;
        case TRANSPORT_PLAY_PAUSE:    return 0x80;
        case TRANSPORT_NEXT_TRACK:    return 0x100;
        case TRANSPORT_PREV_TRACK:    return 0x200;
        case TRANSPORT_STOP:          return 0x400;
        case TRANSPORT_STOP_EJECT:    return 0x800;
        case TRANSPORT_FAST_FORWARD:  return 0x1000;
        case TRANSPORT_REWIND:        return 0x2000;
    };
    return 0;
}

static void send_consumer(uint16_t data)
{
    uint16_t bits = usage2bits(data);
    uart_putchar(0xFD);           // rn42 raw mode
    uart_putchar(0x03);           // length
    uart_putchar(0x03);           // descriptor
    uart_putchar(bits&0xFF);      // low byte
    uart_putchar((bits>>8)&0xFF); // high byte
}

static void send_system(uint16_t data) {}
     
