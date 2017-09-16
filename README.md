# reversi-micro
Reversi two player game implementation on resource-constraint uC devices.

Required hardware:
	1. EasyAVR v7 Development Board with 8MHz external clock,
	2. LCD 2x16 display,
	3. Custom made 8x8 LED dot matrix display with push buttons.

Required software:
	1. mikroC Pro for AVR,
	2. AVRFLASH

Setup EasyAVR v7 Development Board:
	1. Connect LCD 2x16 display at its place,
	2. Connect custom made dot matrix display at GLCD128x64 place,
	3. Turn off all switches except SW3.1 (LCD back-light),
	4. Turn on all PORTC pull down resistors, turn on pull down resistor of pins PD7, PB0, PB1.
	5. Program the MCU.
