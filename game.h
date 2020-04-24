/* 
   game.h  -- Program to  controll the game based on action passed in from ReadInput.h file

   Author: Vatsal Patel

   Modification History
   Date        Action
   12/5/18  -- Original version

   ID code: 5ARc4N3ihjpc.
*/
#ifndef GAME_H
#define GAME_H
using namespace std;
#include <iostream>
#include <iomanip>
#include <string>
#include <ncurses.h>
#include "ReadInput.h"
#include <sstream>
#include <vector>

const int SIZE = 3;

class Game : public ReadInput
{
 protected:
   char mgrid[SIZE][SIZE];
   WINDOW *grid[SIZE][SIZE];
   int input;
   WINDOW *command;
   WINDOW *coverWin;

 public:
   // assign mgrid placeholder values
   void initWindow()
   {
      char ch = '1';
      for (int r = 0; r < SIZE; ++r)
      {
         for (int c = 0; c < SIZE; ++c)
         {
            mgrid[r][c] = ch;
            ch++;
         }
      }
   }

   // create windows and store them into a array.
   void displayGrid()
   {
      // Display the grid
      int n = 1; // window number
      WINDOW *w;
      for (int r = 0; r < SIZE; ++r)
      {
         for (int c = 0; c < SIZE; ++c)
         {
            grid[r][c] = newwin(5, 5, (4 * r) + 10, (4 * c) + 10);
            w = grid[r][c];

            // Set border
            wborder(grid[r][c], ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_PLUS, ACS_PLUS, ACS_PLUS, ACS_PLUS);
            start_color();
            init_pair(2, COLOR_CYAN, COLOR_BLACK);
            wattron(w, COLOR_PAIR(2));
            if (n == 1)
               mvwaddch(w, 0, 0, ACS_ULCORNER);
            else if (n == 2)
               mvwaddch(w, 0, 0, ACS_TTEE);
            else if (n == 3)
               mvwaddch(w, 0, 0, ACS_TTEE);
            mvwaddch(w, 0, 4, ACS_URCORNER);

            if (n == 4)
            {
               mvwaddch(w, 0, 0, ACS_LTEE);
            }
            if (n == 6)
            {
               mvwaddch(w, 0, 4, ACS_RTEE);
            }
            if (n == 7)
            {
               mvwaddch(w, 0, 0, ACS_LTEE);
               mvwaddch(w, 4, 0, ACS_LLCORNER);
               mvwaddch(w, 4, 4, ACS_BTEE);
            }
            if (n == 8)
            {
               mvwaddch(w, 4, 0, ACS_BTEE);
            }
            if (n == 9)
            {
               mvwaddch(w, 4, 0, ACS_BTEE);
               mvwaddch(w, 0, 4, ACS_RTEE);
               mvwaddch(w, 4, 4, ACS_LRCORNER);
            }
            mvwaddch(w, 2, 2, mgrid[r][c]);
            wrefresh(grid[r][c]);
            ++n;
         }
      }
   }

   // Display the title and other info upto of the program.
   void header()
   {
      WINDOW *display;
      start_color();
      init_pair(3, COLOR_GREEN, COLOR_BLACK);
      display = newwin(9, COLS, 1, 1);
      wattron(display, COLOR_PAIR(3));
      waddstr(display, "Tic Tac Toe\n");
      waddstr(display, "By: Vatsal Patel\n");
      waddstr(display, "\nPlease enter any number shown in the grid to place your move");
      waddstr(display, "\n\nPlayer 1: X");
      waddstr(display, "\n\nPlayer 2: O");
      wrefresh(display);
   }

   // to show output of various actions.
   void commandWindow()
   {
      start_color();
      init_pair(1, COLOR_RED, COLOR_WHITE);
      int r, c;
      getmaxyx(stdscr, r, c);
      command = newwin(1, c, r - 1, 0);
      wattron(command, COLOR_PAIR(1));
      waddstr(command, "Hello: ");
      wrefresh(command);
   }
   /*
   void cover(){
     start_color();
     init_pair(1,COLOR_RED, COLOR_WHITE);
     coverWin = newwin(1,COLS, LINES- 20, 10);
     waddstr(coverWin, "Click to continue");
     wrefresh(coverWin);
     mousemask(ALL_MOUSE_EVENTS, NULL);
     int ch = wgetch(coverWin);
     if(ch == KEY_MOUSE){
        MEVENT event;
	if(getmouse(&event) == OK){
	  wmove(coverWin, 0, 0);
          wclrtoeol(coverWin);
          wrefresh(coverWin);
     }else{
     waddstr(coverWin, "Nothing!");
     wrefresh(coverWin);
    }
  }
 }
*/
   // erase called window
   void clear()
   {
      wmove(command, 0, 0);
      wclrtoeol(command);
      wrefresh(command);
   }

   // window used to show game result.
   void write(string n)
   {
      start_color();
      init_pair(4, COLOR_YELLOW, COLOR_BLACK);
      command = newwin(1, COLS, LINES - 20, 5);
      wattron(command, COLOR_PAIR(4));
      waddstr(command, n.c_str());
      wrefresh(command);
   }

   // waits for input.
   void pause()
   {
      wgetch(command);
   }

   // check for a winner
   int checkWin()
   {
      // check if any row is the same
      for (int i = 0; i <= 2; i++)
      {
         if (mgrid[i][0] == mgrid[i][1] and mgrid[i][1] == mgrid[i][2])
         {
            if (mgrid[i][1] == 'X')
            {
               write("Player 1 WON! Press Any Key to Exit!");
               pause();
            }
            else if (mgrid[i][1] == 'O')
            {
               write("Player 2 WON! Press Any Key to Exit!");
               pause();
            }
            return 1;
         }
      }

      // check if any col is the same
      for (int i = 0; i <= 2; i++)
      {
         if (mgrid[0][i] == mgrid[1][i] and mgrid[1][i] == mgrid[2][i])
         {
            if (mgrid[1][i] == 'X')
            {
               write("Player 1 WON! Press Any Key to Exit!");
               pause();
            }
            else if (mgrid[1][i] == 'O')
            {
               write("Player 2 WON! Press Any Key to Exit!");
               pause();
            }
            return 1;
         }
      }

      // Diagonal slop downward
      if (mgrid[0][0] == mgrid[1][1] and mgrid[1][1] == mgrid[2][2])
      {
         clear();
         if (mgrid[1][1] == 'X')
         {
            write("Player 1 WON! Press Any Key to Exit!");
            pause();
         }
         else if (mgrid[1][1] == 'O')
         {
            write("Player 2 WON! Press Any Key to Exit!");
            pause();
         }
         return 1;
      }

      // Diagonal Slop Upwards
      if (mgrid[2][0] == mgrid[1][1] and mgrid[1][1] == mgrid[0][2]) 
      {
         clear();
         if (mgrid[1][1] == 'X')
         {
            write("Player 1 WON! Press Any Key to Exit!");
            pause();
         }
         else if (mgrid[1][1] == 'O')
         {
            write("Player 2 WON! Press Any Key to Exit!");
            pause();
         }
         return 1;
      }

      // if there are empty spot in grid keep going.
      for (int i = 0; i <= 2; i++)
      {
         for (int j = 0; j <= 2; j++)
         {
            if (mgrid[i][j] != 'X' and mgrid[i][j] != 'O')
            {
               //continue;
               return 0;
            }
         }
      }

      // it is a tie!
      return 2;
   }

   // called when there is a tie.
   void tie()
   {
      clear();
      write("Its a Tie! Press Any Key to Exit!");
      wgetch(command);
   }

   // called when invalid input is entered.
   void writes(string s)
   {
      waddstr(command, s.c_str());
      wrefresh(command);
   }

   // player 1 turn.
   bool player1_Turn(char i)
   {
      // convert char to int.
      int input = i - '0';
      input = input - 1;
      int row = input / 3;
      int col = input % 3;

      if (mgrid[row][col] == 'X' or mgrid[row][col] == 'O')
      {
         // input is already taken.
         clear();
         waddstr(command, "Already Taken Try Again");
         wrefresh(command);
         return false;
      }
      else
      {
         // input number is empty space
         clear();
         wrefresh(command);
         mgrid[row][col] = 'X';
         mvwaddch(grid[row][col], 2, 2, 'X');
         wrefresh(grid[row][col]);
         return true;
      }
   }

   // player 2 turn.
   bool player2_Turn(char i)
   {
      // convert char to int
      int input = i - '0';
      input = input - 1;
      int row = input / 3;
      int col = input % 3;

      if (mgrid[row][col] == 'X' or mgrid[row][col] == 'O')
      {
         // input number is already taken
         clear();
         waddstr(command, "Already Taken Try Again");
         wrefresh(command);
         return false;
      }
      else
      {
         // input number is empty space
         clear();
         wrefresh(command);
         mgrid[row][col] = 'O';
         mvwaddch(grid[row][col], 2, 2, 'O');
         wrefresh(grid[row][col]);
         return true;
      }
   }
};
#endif
