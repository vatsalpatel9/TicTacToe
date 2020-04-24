/* 
   ReadInput.h  -- Program to  Get input from user to place a move

   Author: Vatsal Patel

   Modification History
   Date        Action
   12/5/18  -- Original version

   ID code: 5ARc4N3ihjpc.
*/
#ifndef READINPUT_H
#define READINPUT_H
using namespace std;
#include <iostream>
#include <iomanip>
#include <string>
#include <ncurses.h>

class ReadInput
{
 private:
   WINDOW *command;
   char c;

 public:
   // Window to get input value in
   void commandWindow()
   {
      int r, c;
      getmaxyx(stdscr, r, c);
      command = newwin(1, c, r - 2, 0);
      init_pair(1, COLOR_WHITE, COLOR_RED);
      wattron(command, COLOR_PAIR(1));
      waddstr(command, "Player 1 Enter your move: ");
      wrefresh(command);
   }

   // get input value
   char read()
   {
      char line[2];
      wgetnstr(command, line, 1);
      return line[0];
      c = line[0];
   }

   // erase the line and redraw for player 1 turn.
   void clear1()
   {
      wmove(command, 0, 0);
      wclrtoeol(command);
      waddstr(command, "Player 1 Enter your move: ");
      wrefresh(command);
   }

   // erase the line and redraw for player 2 turn.
   void clear2()
   {
      wmove(command, 0, 0);
      wclrtoeol(command);
      waddstr(command, "Player 2 Enter your move: ");
      wrefresh(command);
   }
};
#endif
