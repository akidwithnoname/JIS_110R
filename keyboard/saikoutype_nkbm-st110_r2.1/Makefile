# Target file name (without extension).

TARGET ?= NKBM-ST110_firmware

# Directory common source filess exist
TMK_DIR ?= ../../tmk_core

# Directory keyboard dependent files exist
TARGET_DIR ?= .

# project specific files
SRC ?=	matrix.c \
	led.c

CONFIG_H ?= config.h


# MCU name
MCU ?= at90usb1286

# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the
#     processor frequency in Hz. You can then use this symbol in your source code to
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
#
#     This will be an integer division of F_USB below, as it is sourced by
#     F_USB after it has run through any CPU prescalers. Note that this value
#     does not *change* the processor frequency - it should merely be updated to
#     reflect the processor speed set externally so that the code can use accurate
#     software delays.
F_CPU ?= 16000000


#
# LUFA specific
#
# Target architecture (see library "Board Types" documentation).
ARCH ?= AVR8

# Input clock frequency.
#     This will define a symbol, F_USB, in all source code files equal to the
#     input clock frequency (before any prescaling is performed) in Hz. This value may
#     differ from F_CPU if prescaling is used on the latter, and is required as the
#     raw input clock is fed directly to the PLL sections of the AVR for high speed
#     clock generation for the USB and other AVR subsections. Do NOT tack on a 'UL'
#     at the end, this will be done automatically to create a 32-bit value in your
#     source code.
#
#     If no clock division is performed on the input clock inside the AVR (via the
#     CPU clock adjust registers or the clock division fuses), this will be equal to F_CPU.
F_USB ?= $(F_CPU)

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT


# Boot Section Size in *bytes*
BOOTLOADER_SIZE ?= 1024
OPT_DEFS += -DBOOTLOADER_SIZE=$(BOOTLOADER_SIZE)


# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE ?= yes	    # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE ?= yes	    # Mouse keys(+4700)
EXTRAKEY_ENABLE ?= yes	    # Audio control and System control(+450)
CONSOLE_ENABLE ?= yes	    # Console for debug(+400)
COMMAND_ENABLE ?= yes       # Commands for debug and configuration
LED_PWM_ENABLE ?= yes	    # PWM LEDs for animations and brightness control
SLEEP_LED_ENABLE ?= yes     # Breathing sleep LED during USB suspend
NKRO_ENABLE ?= yes	    # USB Nkey Rollover
ACTIONMAP_ENABLE ?= yes	    # Use 16bit action codes in keymap instead of 8bit key codes
RN42_BT_ENABLE ?= yes       # [!_ALPHA_!] Enable RN42 bluetooth expansion module support

ifeq (yes,$(strip $(RN42_BT_ENABLE)))
    SRC += main.c
    SRC += uart.c
    SRC += rn42-bt-module.c
endif


# keymap
SRC := NKBM-ST110_MAJESTOUCH-JIS.c $(SRC)
#SRC := NKBM-ST110_RK9000v2-US.c $(SRC)

ifeq (yes,$(strip $(LED_PWM_ENABLE)))
    SRC += led_pwm.c
    OPT_DEFS += -DLED_PWM_ENABLE
    ifeq (yes,$(strip $(SLEEP_LED_ENABLE)))
        OPT_DEFS += -DSLEEP_LED_ENABLE
        OPT_DEFS += -DNO_SUSPEND_POWER_DOWN
    endif
endif

# Optimize size but this may cause error "relocation truncated to fit"
#EXTRALDFLAGS = -Wl,--relax

# Search Path
VPATH += $(TARGET_DIR)
VPATH += $(TMK_DIR)

include $(TMK_DIR)/protocol/lufa.mk
include $(TMK_DIR)/common.mk
include $(TMK_DIR)/rules.mk
