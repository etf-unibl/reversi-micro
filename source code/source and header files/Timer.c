#include "Timer.h"
#include "Keypad_and_Display.h"
#include "Reversy.h"
#include "main.h"

char blank[8][8] = { 0 };

/**
* @brief Timer Intialisation
* @return Returns nothing.
*/
void InitTimer1(){
  SREG_I_bit = 1;
  TCCR1A = 0x80;
  TCCR1B = 0x09;
  OCR1AH = 0x1F;
  OCR1AL = 0x3F;
  OCIE1A_bit = 1;
}

/**
* @brief Interrupt handler routine
* @return Returns nothing.
*/
void Timer1Overflow_ISR() org IVT_ADDR_TIMER1_COMPA {
     
     if (mode==1)
        refresh_8x8_dot_mat_disp(board,moves);
     else
        refresh_8x8_dot_mat_disp(board,blank);
}