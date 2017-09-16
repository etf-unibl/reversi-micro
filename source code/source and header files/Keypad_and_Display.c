#include "Keypad_and_Display.h"
#include "Reversy.h"
#include "main.h"

// LCD module connections
sbit LCD_RS at PORTA2_bit;
sbit LCD_EN at PORTD6_bit;
sbit LCD_D4 at PORTC4_bit;
sbit LCD_D5 at PORTC5_bit;
sbit LCD_D6 at PORTC6_bit;
sbit LCD_D7 at PORTC7_bit;

sbit LCD_RS_Direction at DDA2_bit;
sbit LCD_EN_Direction at DDD6_bit;
sbit LCD_D4_Direction at DDC4_bit;
sbit LCD_D5_Direction at DDC5_bit;
sbit LCD_D6_Direction at DDC6_bit;
sbit LCD_D7_Direction at DDC7_bit;
// End LCD module connections

// Dot-Matrix 8x8 Display module connections
sbit SH_CP    at PORTC0_bit;
sbit DS       at PORTC1_bit;
sbit ST_CP    at PORTC2_bit;
sbit OEn      at PORTC3_bit;
sbit ROW_CLK  at PORTB0_bit;
sbit ROW_RST  at PORTB1_bit;
// End Dot-Matrix 8x8 Display module connections

char k;
bit buttonPress;

/**
 * @brief        This function will be used to copy string from rom to ram.
 * @param dest   Pointer to destination(ram) string.
 * @param src    Pointer to source(rom) string.
 * @return       Returns address of destination string.
 */
char * CopyConst2Ram(char * dest, const char * src){
  char * d ;
  d = dest;
  while( *(dest++) = *(src++) );
  return d;
}

/**
 * @brief  This function will be used to scan keypad.
 * @return Returns index of key pressed.
 */
char keypad_index ()
{
     DDD7_bit = 1;                                              //OUTPUT
     DDC4_bit = 0; DDC5_bit = 0; DDC6_bit = 0; DDC7_bit = 0;    //INPUTS
     PORTD7_bit = 1;
     delay_us(100);
     if (PINC4_bit==1)
        return 1;
     if (PINC5_bit==1)
        return 2;
     if (PINC6_bit==1)
        return 3;
     if (PINC7_bit==1)
        return 4;

     DDC4_bit = 1;                                              //OUTPUT
     DDD7_bit = 0; DDC5_bit = 0; DDC6_bit = 0; DDC7_bit = 0;    //INPUTS
     PORTC4_bit = 1;
     delay_us(100);
     if (PINC5_bit==1)
        return 5;
     if (PINC6_bit==1)
        return 6;
     if (PINC7_bit==1)
        return 7;

     DDC5_bit = 1;                                              //OUTPUT
     DDD7_bit = 0; DDC4_bit = 0; DDC6_bit = 0; DDC7_bit = 0;    //INPUTS
     PORTC5_bit = 1;
     delay_us(100);
     if (PINC4_bit==1)
        return 8;
     if (PINC6_bit==1)
        return 9;
     if (PINC7_bit==1)
        return 10;

     DDC6_bit = 1;                                              //OUTPUT
     DDD7_bit = 0; DDC4_bit = 0; DDC5_bit = 0; DDC7_bit = 0;    //INPUTS
     PORTC6_bit = 1;
     delay_us(100);
     if (PINC4_bit==1)
        return 11;
     if (PINC5_bit==1)
        return 12;
     if (PINC7_bit==1)
        return 13;

     DDC7_bit = 1;                                              //OUTPUT
     DDD7_bit = 0; DDC4_bit = 0; DDC5_bit = 0; DDC6_bit = 0;    //INPUTS
     PORTC7_bit = 1;
     delay_us(100);
     if (PINC4_bit==1)
        return 14;
     if (PINC5_bit==1)
        return 15;
     if (PINC6_bit==1)
        return 16;

     return 0;
}

/**
 * @brief     This function will be used to mask key index.
 * @param num The key pressed index.
 * @return    Returns mask of key index.
 */
unsigned short mask_keypad (unsigned short num) {
  switch (num) {
    case 1 : return 0x61;  //col a
    case 2 : return 0x62;  //col b
    case 3 : return 0x63;  //col c
    case 4 : return 0x64;  //col d
    case 5 : return 0x65;  //col e
    case 6 : return 0x66;  //col f
    case 7 : return 0x67;  //col g
    case 8 : return 0x68;  //col h
    case 9 : return 0x31;  //row 1
    case 10 : return 0x32; //row 2
    case 11 : return 0x33; //row 3
    case 12 : return 0x34; //row 4
    case 13 : return 0x35; //row 5
    case 14 : return 0x36; //row 6
    case 15 : return 0x37; //row 7
    case 16 : return 0x38; //row 8
  } //case end
}


/**
 * @brief     This function will be used to Enter and Display on LCD played move by Player.
 * @return    Returns nothing.
 */
void scan_keypad()
{
    unsigned char a=0;
    char disp_array[]={0x30,0x30};

    while (keypad_index() !=0){ }; // Wait to release key
    DDC4_bit = 1; DDC5_bit = 1; DDC6_bit = 1; DDC7_bit = 1;
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Out(1,1,CopyConst2Ram(msg,txt1));             // Write text "Enter your move"

    if (player % 2) {
       if (keypad_index() ==0  )
       {
          DDC4_bit = 1; DDC5_bit = 1; DDC6_bit = 1; DDC7_bit = 1;
          Lcd_Out(2,1,CopyConst2Ram(msg,txt3));       // Write text "P2_Red"
       }
    }
    else
        if (keypad_index() ==0  )
        {
           DDC4_bit = 1; DDC5_bit = 1; DDC6_bit = 1; DDC7_bit = 1;
           Lcd_Out(2,1,CopyConst2Ram(msg,txt2));      // Write text "P1_Green"
        }
    do
    {
             while (keypad_index() !=0 )
             {     delay_ms(10);
                   if (buttonPress==0 && keypad_index() !=0)
                   {
                      k=keypad_index();
                      //column index
                      if (k==1 | k==2 | k==3 | k==4 | k==5 | k==6 | k==7 | k==8)
                      {
                          disp_array[0] = mask_keypad(k);
                          C = k-1;
                          a++;
                      }
                      //row index
                      else
                      {   disp_array[1] = mask_keypad(k);
                          R = k-9;
                          a++;
                      }
                      buttonPress=1;
                   }
             }
             buttonPress=0;

             if (keypad_index() ==0)
             {
                DDC4_bit = 1; DDC5_bit = 1; DDC6_bit = 1; DDC7_bit = 1;
                Lcd_Out(2,15,disp_array);
             }

    }while(a<2);
    delay_ms(300);
}

/**
 * @brief           This function will be used to refreshe next row of 8x8 dot matrix display each time it is called.
 * @param board     The board matrix contains played moves.
 * @param moves     The moves matrix contains playable moves (flip hints).
 * @return          Returns nothing.
 */
void refresh_8x8_dot_mat_disp(char board[][8], char moves[][8])
{
     static unsigned char i=0;	//row index
     unsigned char c;
     
     //set direction to be output
     DDC0_bit=1; DDC1_bit=1; DDC2_bit=1; DDC3_bit=1; DDB0_bit=1; DDB1_bit=1;

     // Turn OFF 8x8 LED Dot Matrix Display
     OEn = 1;
     delay_us(100);
     //blue
     for (c=0; c<8; c++)
     {
         if (moves[i][7-c]==1)
            DS = 0;
         else
             DS = 1;
         SH_CP = 1;
         SH_CP = 0;
     }
     //green
     for (c=0; c<8; c++)
     {
         if (board[i][7-c]=='O')
            DS = 0;
         else
             DS = 1;
         SH_CP = 1;
         SH_CP = 0;
     }
     //red
     for (c=0; c<8; c++)
     {
         if (board[i][7-c]=='X')
            DS = 0;
         else
             DS = 1;
         SH_CP = 1;
         SH_CP = 0;
     }
     
     // Apply pulse on ST_CP
     ST_CP = 1;
     ST_CP = 0;
	 
     i++;
     Row_Clk = 1;
     Row_Clk = 0;
     if (i==9)
     {
        Row_Rst = 1;
        Row_Rst = 0;
        i=0;
     }
     delay_us(100);
     // Turn ON 8x8 LED Dot Matrix Display
     OEn = 0;
}