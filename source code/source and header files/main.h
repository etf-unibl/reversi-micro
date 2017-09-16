/**
* @file main.h
* @brief File containing headers of a MAIN module. 
*
* @author Aleksandar Majstorovic, Dario Djuric
*
* @date 2016/2017
*/

#ifndef _main_
#define _main_

extern char player;
extern char C;
extern char R;
extern char mode;

extern char board [8][8];
extern char moves[8][8];

extern char msg[17];
extern const char txt1[];
extern const char txt2[];
extern const char txt3[];
extern const char txt4[];
extern const char txt5[];
extern const char txt6[];
extern const char txt7[];
extern const char txt8[];
extern const char txt9[];
extern const char txt10[];

/**
 * This function will be used to run Menu Hint.
 * Menu will be displayed on LCD display.
 * It will turn on the flip hint by pressing any row button or
 * turn off the flip hint by pressing any column button.
 *
 * @param None.
 * @return None.
 */
void menu1(void);

/**
 * This function will be used to run Menu Play Again.
 * Menu will be displayed on LCD display.
 * New game will be played by pressing any row button.
 *
 * @param None.
 * @return None.
 */
void menu2(void);

/**
 * Main program
 *
 * @param NONE.
 * @return NONE.
 */
void main(void);

#endif