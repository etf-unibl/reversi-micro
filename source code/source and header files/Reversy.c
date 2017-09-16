#include "Reversy.h"
#include "Keypad_and_Display.h"
#include "main.h"
   
/**
* This function will be used to analyses matrix board and calculate which squares are valid moves for current player.
* It forms matrix moves of valid moves for current player, by puting 1 for valid move and 0 for invalid move.  
*
* @param board The board matrix contains played moves.
* @param moves The moves matrix. 
* @param player The player indicator which indicates current player.
* @return Returns number of valid moves.
*/
int valid_moves(char board[][8], char moves[][8], char player)
{
   int rowdelta = 0;     /* Row increment around a square    */
   int coldelta = 0;     /* Column increment around a square */
   int row = 0;          /* Row index                        */
   int col = 0;          /* Column index                     */
   int x = 0;            /* Row index when searching         */
   int y = 0;            /* Column index when searching      */
   int no_of_moves = 0;  /* Number of valid moves            */

   /* Set the opponent            */
   char opponent = (player == 'O')? 'X' : 'O';

   /* Initialize moves array to zero */
   for(row = 0; row < 8; row++)
     for(col = 0; col < 8; col++)
       moves[row][col] = 0;

   /* Find squares for valid moves.                           */
   /* A valid move must be on a blank square and must enclose */
   /* at least one opponent square between two player squares */
   for(row = 0; row < 8; row++)
     for(col = 0; col < 8; col++)
     {
       if(board[row][col] != ' ')   /* Is it a blank square?  */
         continue;                  /* No - so on to the next */

       /* Check all the squares around the blank square  */
       /* for the opponents "disc"                      */
       for(rowdelta = -1; rowdelta <= 1; rowdelta++)
         for(coldelta = -1; coldelta <= 1; coldelta++)
         {
           /* Don't check outside the array, or the current square */
           if(row + rowdelta < 0 || row + rowdelta >= 8 ||
              col + coldelta < 0 || col + coldelta >= 8 ||
                                       (rowdelta==0 && coldelta==0))
             continue;

           /* Now check the square */
           if(board[row + rowdelta][col + coldelta] == opponent)
           {
             /* If we find the opponent, move in the delta direction  */
             /* over opponent "disc's" searching for a player "disc" */
             x = row + rowdelta;                /* Move to          */
             y = col + coldelta;                /* opponent square  */

             /* Look for a player square in the delta direction */
             for(;;)
             {
               x += rowdelta;                  /* Go to next square */
               y += coldelta;                  /* in delta direction*/

               /* If we move outside the array, give up */
               if(x < 0 || x >= 8 || y < 0 || y >= 8)
                 break;

               /* If we find a blank square, give up */
               if(board[x][y] == ' ')
                 break;
                /*  If the square has a player "disc" */
                /*  then we have a valid move          */
               if(board[x][y] == player)
               {
                 moves[row][col] = 1;   /* Mark as valid */
                 no_of_moves++;         /* Increase valid moves count */
                 break;                 /* Go check another square    */
               }
             }
           }
         }
     }
   return no_of_moves;
}

 /**
* This function will be used to put player's "disc" on the marked spot (row,col)
* and reverse all the opponent's "disc's" affected by the move. 
*
* @param board The board matrix contains played moves.
* @param row Matrix board row index of the marked spot.
* @param col Matrix board column index of the marked spot.
* @param player The player indicator which indicates current player.
* @return None.
*/
void make_move(char board[][8], int row, int col, char player)
{
   int rowdelta = 0;                   /* Row increment              */
   int coldelta = 0;                   /* Column increment           */
   int x = 0;                          /* Row index for searching    */
   int y = 0;                          /* Column index for searching */
   char opponent = (player == 'O')? 'X' : 'O';  /* Identify opponent */

   board[row][col] = player;           /* Place the player "disc"   */

   /* Check all the squares around this square */
   /* for the opponents "disc's"                */
   for(rowdelta = -1; rowdelta <= 1; rowdelta++)
     for(coldelta = -1; coldelta <= 1; coldelta++)
     {
       /* Don't check off the board, or the current square */
       if(row + rowdelta < 0 || row + rowdelta >= 8 ||
          col + coldelta < 0 || col + coldelta >= 8 ||
                               (rowdelta==0 && coldelta== 0))
         continue;

       /* Now check the square */
       if(board[row + rowdelta][col + coldelta] == opponent)
       {
         /* If we find the opponent, search in the same direction */
         /* for a player "disc"                                  */
         x = row + rowdelta;        /* Move to opponent */
         y = col + coldelta;        /* square           */

         for(;;)
         {
           x += rowdelta;           /* Move to the      */
           y += coldelta;           /* next square      */

           /* If we are off the board give up */
           if(x < 0 || x >= 8 || y < 0 || y >= 8)
             break;

           /* If the square is blank give up */
           if(board[x][y] == ' ')
             break;

           /* If we find the player "disc", go backwards from here */
           /* changing all the opponents "disc's" to player         */
           if(board[x][y] == player)
           {
             while(board[x-=rowdelta][y-=coldelta]==opponent) /* Opponent? */
               board[x][y] = player;    /* Yes, change it */
             break;                     /* We are done    */
           }
         }
       }
     }
}


/**
* This function will be used to calculate a final score of the played game.
* It shows the winner and the score on LCD display.
*
* @param board The board matrix contains played moves.
* @return NONE.
*/
void final_score(char board[][8])
{
     char player1_score[] ={0x30,0x30};      // Player 1 score as character
     char player2_score[] ={0x30,0x30};      // Player 2 score as character
     int user1_score = 0;                    // Player 1 score
     int user2_score = 0;                    // Player 2 score
     int row = 0;                            // Row index
     int col = 0;                            // Column index
     
     for (row = 0; row < 8; row++)
         for (col = 0; col < 8; col++)
         {
             user2_score += board[row][col] == 'X';  // user score + 1 if True(1)
             user1_score += board[row][col] == 'O';
         }
             
     DDC4_bit = 1; DDC5_bit = 1; DDC6_bit = 1; DDC7_bit = 1;
     Lcd_Cmd(_LCD_CLEAR);
     
     if (user1_score > user2_score)
     {
        Lcd_Out(1,3,CopyConst2Ram(msg,txt2));       // Write text "P1_Green :"
        Lcd_Out(1,12,CopyConst2Ram(msg,txt10));     // Write text "WON"
     }
     else
     {
        Lcd_Out(1,3,CopyConst2Ram(msg,txt3));       // Write text "P2_Red   :"
        Lcd_Out(1,12,CopyConst2Ram(msg,txt10));      // Write text "WON"
     }
     
     player1_score[1] =(user1_score % 10)+'0';
     user1_score=user1_score / 10;
     player1_score[0] =(user1_score % 10)+'0';

     player2_score[1] =(user2_score % 10)+'0';
     user2_score=user2_score / 10;
     player2_score[0] =(user2_score % 10)+'0';

     delay_ms(2000);
     
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Out(1,1,CopyConst2Ram(msg,txt2));        // Write text "P1_Green :"
     Lcd_Out(1,15,player1_score);                 // Write player1_score

     Lcd_Out(2,1,CopyConst2Ram(msg,txt3));        // Write text "P2_Red   :"
     Lcd_Out(2,15,player2_score);                 // Write player2_score
     
     delay_ms(5000);
}