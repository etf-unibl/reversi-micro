/**
* @file main.c
* @brief This is the main file of the project
*
* @author Aleksandar Majstorovic, Dario Djuric
*
* @date 2016/2017
*
*/

#include "main.h"
#include "Keypad_and_Display.h"
#include "Timer.h"
#include "Reversy.h"


char board [8][8] = { 0 };              /**< The board matrix contains played moves.                    */
char moves[8][8] = { 0 };               /**< The moves matrix contains valid moves (flip hints).        */

int no_of_games = 0;                    /**< Number of games.          */
char row = 0;                           /**< Board row index.          */
char col = 0;                           /**< Board column index.       */
char again = 0;                         /**< Replay choice input.      */

char C = 0;                             /**< Column number.            */
char R = 0;                             /**< Row number.               */
char player = 0;                        /**< Player indicator.         */

char msg[17];        /**< 16 characters plus 1 [for terminator] message for copying text from ROM. */ 

const char txt1[] = "Enter your move";                
const char txt2[] = "P1_Green :";
const char txt3[] = "P2_Red   :";
const char txt4[] = "Reversi Game";
const char txt5[] = "Two player";
const char txt6[] = "Not a valid move";
const char txt7[] = "You have to pass";
const char txt8[] = "No valid moves";
const char txt9[] = "  Game is over  ";
const char txt10[] = "WON";
const char txt11[] = "    Goodbye    ";

const char txt0_0[] = "*  MENU  HINT  *";
const char txt0_1[] = "Turn On The Flip";
const char txt0_2[] = "Hint (y/n): ";
const char txt0_3[] = "NO  ";
const char txt0_4[] = "YES ";
const char txt0_5[] = "yes=green no=red";

const char txt1_0[] = "Play Again";
const char txt1_1[] = "(y/n): ";

char j;

char menu[8][8] = { ' ',' ',' ',' ',' ',' ',' ','O',
                    ' ',' ',' ',' ',' ',' ',' ','O',
                    ' ',' ',' ',' ',' ',' ',' ','O',
                    ' ',' ',' ',' ',' ',' ',' ','O',
                    ' ',' ',' ',' ',' ',' ',' ','O',
                    ' ',' ',' ',' ',' ',' ',' ','O',
                    ' ',' ',' ',' ',' ',' ',' ','O',
                    'X','X','X','X','X','X','X',' ', };   /**< yes=green and no=red buttons indicator*/

char mode=2;   /**< Play mode: mode=1 -> hint on, mode=0 -> hint off */

/**
 * This function will be used to run Menu Hint.
 * Menu will be displayed on LCD display.
 * It will turn on the flip hint by pressing any row button or
 * turn off the flip hint by pressing any column button.
 * @param None.
 * @return None.
 */
void menu1()
{
    char k;
    bit buttonPress;
    unsigned char a=0;

    // Wait to release key
    while (keypad_index() !=0){ };
    DDC4_bit = 1; DDC5_bit = 1; DDC6_bit = 1; DDC7_bit = 1;
    Lcd_Cmd(_LCD_CLEAR);
    // Write text "*  MENU  HINT  *"
    Lcd_Out(1,1,CopyConst2Ram(msg,txt0_0));
    // Write text "yes=green no=red"
    Lcd_Out(2,1,CopyConst2Ram(msg,txt0_5));
    delay_ms(2000);
    // Wait to release key
    while (keypad_index() !=0){ };
    DDC4_bit = 1; DDC5_bit = 1; DDC6_bit = 1; DDC7_bit = 1;
    Lcd_Cmd(_LCD_CLEAR);
    // Write text "Turn On The Flip"
    Lcd_Out(1,1,CopyConst2Ram(msg,txt0_1));
    // Write text "Hint (y/n): "
    Lcd_Out(2,1,CopyConst2Ram(msg,txt0_2));
    
    //Turn on yes=green and no=red buttons indicator
    for(row=0;row<8;row++)
        for(col=0;col<8;col++)
            board[row][col]=menu[row][col];
            
    do
    {
             while (keypad_index() !=0 )
             {     delay_ms(10);
                   if (buttonPress==0 && keypad_index() !=0)
                   {
                      k=keypad_index();
                      //column index
                      if (k==1 || k==2 || k==3 || k==4 || k==5 || k==6 || k==7 || k==8)
                      {
                          a++;
                          // NO hint
                          mode=0;
                      }
                      //row index
                      else
                      {
                          a++;
                          // YES hint
                          mode=1;
                      }
                      buttonPress=1;
                   }
             }
             buttonPress=0;

             if (keypad_index() ==0)
             {
                DDC4_bit = 1; DDC5_bit = 1; DDC6_bit = 1; DDC7_bit = 1;
                if (mode==0)
                   // Write text "NO  "
                   Lcd_Out(2,13,CopyConst2Ram(msg,txt0_3));
                else if (mode==1)
                   // Write text "YES "
                   Lcd_Out(2,13,CopyConst2Ram(msg,txt0_4));
             }

    }while(a<1);
    delay_ms(1000);
}


/**
 * This function will be used to run Menu Play Again.
 * Menu will be displayed on LCD display.
 * New game will be played by pressing any row button.
 * @param None.
 * @return None.
 */
void menu2()
{
    char k;
    bit buttonPress;
    unsigned char a=0;
    again=2;

    // Wait to release key
    while (keypad_index() !=0){ };
    DDC4_bit = 1; DDC5_bit = 1; DDC6_bit = 1; DDC7_bit = 1;
    Lcd_Cmd(_LCD_CLEAR);
    // Write text "Play Again"
    Lcd_Out(1,1,CopyConst2Ram(msg,txt1_0));
    // Write text "(y/n): "
    Lcd_Out(2,1,CopyConst2Ram(msg,txt1_1));
    
    //Turn on yes=green and no=red buttons indicator
    for(row=0;row<8;row++)
        for(col=0;col<8;col++)
            board[row][col]=menu[row][col];
    
    do
    {
             while (keypad_index() !=0 )
             {     delay_ms(10);
                   if (buttonPress==0 && keypad_index() !=0)
                   {
                      k=keypad_index();
                      //column index
                      if (k==1 || k==2 || k==3 || k==4 || k==5 || k==6 || k==7 || k==8)
                      {
                          a++;
                          // NO
                          again=0;
                      }
                      //row index
                      else
                      {
                          a++;
                          // YES
                          again=1;
                      }
                      buttonPress=1;
                   }
             }
             buttonPress=0;

             if (keypad_index() ==0)
             {
                DDC4_bit = 1; DDC5_bit = 1; DDC6_bit = 1; DDC7_bit = 1;
                if (again==0)
                  // Write text "NO  "
                  Lcd_Out(2,9,CopyConst2Ram(msg,txt0_3));
                else if (again==1)
                  // Write text "YES "
                  Lcd_Out(2,9,CopyConst2Ram(msg,txt0_4));
             }

    }while(a<1);
    delay_ms(1000);
}

void main()
{
     // Initialize Timer1
     InitTimer1();
     Delay_ms(1000);

     // Initialize Lcd
     Lcd_Init();
     // Clear display
     Lcd_Cmd(_LCD_CLEAR);
     // Cursor off
     Lcd_Cmd(_LCD_CURSOR_OFF);
     // Write text "Reversi Game"
     Lcd_Out(1,3,CopyConst2Ram(msg,txt4));
     // Write text "Two player"
     Lcd_Out(2,4,CopyConst2Ram(msg,txt5));
     Delay_ms(1500);
     // Move text to the right 14 times
     for (j=0; j<14; j++)
     {
         Lcd_Cmd(_LCD_SHIFT_RIGHT);
         Delay_ms(100);
     }
     Lcd_Cmd(_LCD_CLEAR);
     
     // Start Menu Hint
     menu1();
     Lcd_Cmd(_LCD_CLEAR);

     do
     {
           player = ++no_of_games % 2;

           // Blank all the board squares
           for (row = 0; row < 8; row++)
               for (col = 0; col < 8; col++)
                   board[row][col] = ' ';

           // Place the initial four "discs" in the center
           board[3][3] = board[4][4] = 'O';
           board[3][4] = board[4][3] = 'X';


           // The game play loop
           do
           {
               // Check is it the PLAYER_1_(green) turn
               if(player++ % 2)
               {
                   // check is there any valid moves
                   if(valid_moves(board, moves, 'O'))
                   {
                       // Scan keypad until a valid move is entered
                       for(;;)
                       {
                           scan_keypad();
                           // check is it valid move
                           if( moves[R][C] )
                           {
                             make_move(board, R, C, 'O');
                             break;
                           }
                           // not valid move
                           else
                           {
                               Lcd_Cmd(_LCD_CLEAR);
                               //Write text "Not a valid move"
                               Lcd_Out(1,1,CopyConst2Ram(msg,txt6));
                               delay_ms(1000);
                           }
                       }
                   }
                   // No valid moves
                   else
                   {
                        Lcd_Cmd(_LCD_CLEAR);
                        //Write text "You have to pass"
                        Lcd_Out(1,1,CopyConst2Ram(msg,txt7));
                        //Write text "No valid moves"
                        Lcd_Out(2,1,CopyConst2Ram(msg,txt8));
                        delay_ms(1000);
                   }
               }
               // It is the PLAYER_2_(Red) turn
               else
               {
                   // check is there any valid moves
                   if(valid_moves(board, moves, 'X'))
                   {
                       // Scan keypad until a valid move is entered
                       for (;;)
                       {
                           scan_keypad();
                           // check is it valid move
                           if( moves[R][C] )
                           {
                             make_move(board, R, C, 'X');
                             break;
                           }
                           // not valid move
                           else
                           {
                               Lcd_Cmd(_LCD_CLEAR);
                               //Write text "Not a valid move"
                               Lcd_Out(1,1,CopyConst2Ram(msg,txt6));
                               delay_ms(1000);
                           }
                       }
                    }
                    // No valid moves
                    else
                    {
                         Lcd_Cmd(_LCD_CLEAR);
                         //Write text "You have to pass"
                         Lcd_Out(1,1,CopyConst2Ram(msg,txt7));
                         //Write text "No valid moves"
                         Lcd_Out(2,1,CopyConst2Ram(msg,txt8));
                         delay_ms(1000);
                    }
                }
           // check is there valid moves for either player
           } while(valid_moves(board, moves, 'O')>0 || valid_moves(board, moves, 'X')>0);

          /******************************************************
           *                   GAME IS OVER                     *
          ******************************************************/
           Lcd_Cmd(_LCD_CLEAR);
           //Write text "Game is over"
           Lcd_Out(1,1,CopyConst2Ram(msg,txt9));
           delay_ms(2000);

          /*******************************************************
           *         Calculate final score and display it        *
           *******************************************************/
           final_score(board);

           // Start Menu Play Again
           menu2();

     }while(again == 1);
     
     Lcd_Cmd(_LCD_CLEAR);
     //Write text "    Goodbye    "
     Lcd_Out(1,1,CopyConst2Ram(msg,txt11));
     Delay_ms(3000);
     
     //blank all board squares
     for(row=0;row<8;row++)
         for(col=0;col<8;col++)
            board[row][col]=' ';
                                        
     
     Lcd_Cmd(_LCD_TURN_OFF);
     
}