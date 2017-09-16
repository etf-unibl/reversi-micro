/**
* @file Reversy.h
* @brief This header file contains game logic functions.
*
* @author Aleksandar Majstorovic
*
* @date 2016/2017
*/

#ifndef _Reversy_
#define _Reversy_   
        

/**
* This function will be used to analyses matrix board and calculate which squares are valid moves for current player.
* It forms matrix moves of valid moves for current player, by puting 1 for valid move and 0 for invalid move.  
*
* @param board The board matrix contains played moves.
* @param moves The moves matrix. 
* @param player The player indicator which indicates current player.
* @return Returns number of valid moves.
*/
int valid_moves(char board[][8], char moves[][8], char player);


 /**
* This function will be used to put player's "disc" on the marked spot (row,col)
* and reverse all the opponent's "disc's" affected by the move. 
*
* @param board The board matrix contains played moves.
* @param row Matrix board row index of the marked spot.
* @param col Matrix board column index of the marked spot.
* @param player The player indicator which indicates current player.
* @return NONE.
*/
void make_move(char board[][8], int row, int col, char player);

 
/**
* This function will be used to calculate a final score of the played game.
* It shows the winner and the score on LCD display.
*
* @param board The board matrix contains played moves. 
* @return NONE.
*/
void final_score(char board[][8]);

#endif