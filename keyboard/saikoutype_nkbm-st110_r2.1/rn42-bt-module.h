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
