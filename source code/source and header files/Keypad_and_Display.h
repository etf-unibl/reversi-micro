/**
* @file Keypad_and_Display.h
* @brief This header file contains displays and keypad functions.
*
* @author Dario Djuric
*
* @date 2016/2017
*/

#ifndef _Keypad_and_Display_
#define _Keypad_and_Display_

/**
 * @brief      This function will be used to scan keypad.
 * @return     Returns index of key pressed.
 */
char keypad_index (void);

/**
 * @brief      This function will be used to mask key index.
 * @param num  The key pressed index.
 * @return     Returns mask of key index.
 */
unsigned short mask_keypad (unsigned short num);

/**
 * @brief      This function will be used to Enter and Display on LCD played move by Player.
 * @return     Returns nothing.
 */
void scan_keypad(void);

/**
 * @brief              This function will be used to refreshe next row of 8x8 dot matrix display each time it is called.
 * @param board        The board matrix contains played moves.
 * @param moves        The moves matrix contains playable moves (flip hints).
 * @return             Returns nothing.
 */
void refresh_8x8_dot_mat_disp(char board[][], char moves[][]);

/**
 * @brief        This function will be used to copy string from rom to ram.
 * @param dest   Pointer to destination(ram) string.
 * @param src    Pointer to source(rom) string.
 * @return       Returns address of destination string.
 */
char * CopyConst2Ram(char * dest, const char * src);

#endif