[null] 最高タイプ NKBM-ST110 revision 2.1 Keyboard Firmware
==================================
This is a keyboard firmware based on the tmk_core firmware library. It was necessary to fork from tmk_core to implement features that require significant changes to the core of the firmware. The following link will take you to the original tmk_core library this firmware is based on. There you can find more detailed information about how the core of the firmware works. 

<https://github.com/tmk/tmk_core>

Disclaimer
-------
This firmware is provided as an example to build your firmware from. While this firmware is designed for my 最高タイプ NKBM-ST110 hardware product, it is separate and not NOT part of the NKBM-ST110 hardware products. The NKBM-ST110 is a PCB/keyboard that is designed for customers to load their own custom firmware onto and does not come with and software support.


License
-------
**GPLv2** or later. Some protocol files are under **Modified BSD License**.
LUFA, PJRC and V-USB stack have their own license respectively.


TMK Documentation
-------------------------------------
See [doc/build.md](doc/build.md).


Keyboard Specific Firmware Features
--------
* Boot animation                    - Boot animation indicates that the keyboard has finished booting and can accept key press. 
* LED animations                    - Customizable LED animations can be initiated with macros and custom functions.
* Indicator LED brightness control  - Set brightness of LEDs in firmware or on-the-fly with hotkeys.
* Bluetooth Support                 - Bluetooth support is mostly functional but still in development, power-saving and usability features are not implemented yet. 
* Passcode protected macro layer    - When user passcode is entered, keyboard will enter a layer which can be used to store protected macros. 
* External device switch activation - Example function to switch external transistors and control devices like monitor inputs or KVM switch.
* HEX-shift input keypad            - While holding down keypad enter, keypad turns into HEX value input pad.

Default Configuration
--------
* FN + B     - Switch to Bluetooth mode.
* FN + U     - Switch to USB mode. 
* FN + ?     - Play macro to print firmware details.
* FN + O     - OS detection macro, prints "unix" or "windows"
* FN + META  - Enter Game mode, pressing META again causes META LED to flash indicating re-enabling of certain keys. 
* FN + KP-   - Enter MouseKeys mode. 
* CAP + INS  - Max indicator brightness
* CAP + DEL  - Min indicator brightness
* CAP + HOME - Large indicator brightness increment
* CAP + END  - Large indicator brightness decrement 
* CAP + PGUP - Fine indicator brightness increment 
* CAP + PGDN - Fine indicator brightness decrement 


