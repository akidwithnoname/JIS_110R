#include <avr/io.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include "lufa.h"
#include "print.h"
#include "sendchar.h"
#include "rn42-bt-module.h"
#include "keyboard.h"
#include "keycode.h"
#include "action.h"
#include "action_util.h"
#include "wait.h"
#include "uart.h"
#include "suspend.h"
#include "hook.h"
#include "led.h"
#ifdef LED_PWM_ENABLE
#include "led_pwm.h"
#endif

//static bool bluetooth_off = false;
static uint8_t keyboard_led_stats =0;

static void setup_hw(void)
{
    MCUSR &= ~(1 << WDRF);
    wdt_disable();
    clock_prescale_set(clock_div_1);
    USB_Disable();
    USB_Init();
    USB_Device_EnableSOFEvents();
}

bool rn42_connected(void)
{
    return PINE&(1<<1);
}

// MAIN -----------------------------------------------------------------------------------------------------------------

int main(void)  __attribute__ ((weak));
int main(void)
{
    setup_hw();
    sei();
    uint8_t timeout = 255;
    while (timeout-- && USB_DeviceState != DEVICE_STATE_Configured) {
        wait_ms(5);
        #if defined(INTERRUPT_CONTROL_ENDPOINT)
            ;
        #else
            USB_USBTask();
        #endif
    }
    rn42_init();
    wait_ms(500);
    uart_init(BAUD_RATE);
    rn42_enter_cmd();
    rn42_set_name();
    rn42_mode_hid();
    uart_print("C");
    uart_return();
//#undef PRODUCT_ID 
//#define PRODUCT_ID 0x2012
    keyboard_init();
    host_set_driver(&lufa_driver);
    #ifdef LED_PWM_ENABLE    
        pwm_timer_init();
        pwm_timer_enable();
        #ifdef LED_BOOT_ANIMATION
            loading_led_animation_on();
        #endif
        led_indicators_on(); 
    #endif
    led_layer_set(0);
    while (1) {
        led_driver_set();
        keyboard_task();
        #if !defined(INTERRUPT_CONTROL_ENDPOINT)
            USB_USBTask();
        #endif
    }
}

static uint8_t _led_stats = 0;

__attribute__((weak))
void hook_usb_wakeup(void)
{
    suspend_wakeup_init();
    #ifdef LED_PWM_ENABLE
        #ifdef SLEEP_LED_ENABLE
            usb_nc_led_animation_off();
        #endif
        led_animation_on();
    #endif
    keyboard_led_stats = _led_stats;
}
