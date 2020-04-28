/* 
   run.cc  -- Program to  get input from user and call functions to complete actions

   Author: Vatsal Patel

   Modification History
   Date        Action
   12/5/18  -- Original version

   ID code: 5ARc4N3ihjpc.
*/
using namespace std;
#include <iostream>
#include <iomanip>
#include <string>
#include <ncurses.h>
#include "game.h"
#include "ReadInput.h"

int main()
{
   initscr();
   cbreak();

   Game game;
   ReadInput readInput;

   // game.cover();

   game.header();
   game.initWindow();
   game.displayGrid();
   game.commandWindow();
   readInput.commandWindow();

   char i;
   int win;
   bool input = false;

   // while there are empty spot on board keep going.
   while (win != 1)
   {
      do
      {
         readInput.clear1();
         i = readInput.read();
         if (i > '0' and i <= '9')
         {
            input = game.player1_Turn(i);
         }
         else
         {
            game.writes("Invalid Input Try Again!");
            input = false;
         }
      } while (input != true); // keep asking until valid input is entered.

      win = game.checkWin();// check if someone won the game

      if (win == 1) // winner found
      {
         break; // exit loop
      }

      if (win == 2) // tie found
      {
         game.tie(); // print its a tie
         break; // exit loop
      }

      do
      {
         readInput.clear2();
         i = readInput.read();
         if (i > '0' and i <= '9')
         {
            input = game.player2_Turn(i);
         }
         else
         {
            game.writes("Invalid Input Try Again!");
            input = false;
         }
      } while (input != true); // keep asking until valid input is entered

      win = game.checkWin(); // check if someone won the game
   }
   endwin();
   return 0;
}