/* game.cpp --- 
 * 
 * Filename: game.cpp
 * Description: 
 * Author: Bryce
 * Maintainer: Adeel Bhutta
 * Created: Tue Sep  6 11:08:59 2016
 * Last-Updated: 01-10-2021
 *           By: Adeel Bhutta
 *     Update #: 20
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* Copyright (c) 2016 IUB
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */
#include <unistd.h> 
#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include "game.hpp"
#include "well.hpp"
#include "tetris.hpp"
#include "tetromino.hpp"
#include "key.hpp"

void init_game(void) {
  int x,y;
}

int game(void) {
  static int state = INIT;
  tetromino_t *next = NULL;
  tetromino_t *current = NULL;
  well_t *w;
  int x,y;
  int c;
  int arrow;
  struct timespec tim = {0,1000000};  // Each execution of while(1) is approximately 1mS 
  struct timespec tim_ret;
  int move_counter = 0;
<<<<<<< HEAD
  int move_timeout = BASE_FALL_RATE;          
  bool timer = true; 
=======
  int move_timeout = BASE_FALL_RATE;      
  int preserveColor;       
>>>>>>> d6b687d7f30c058a8148e49195cef918fc04a1c7

  while(1) { 
    switch(state) {
    case INIT:               // Initialize the game, only run one time 
      initscr();
      nodelay(stdscr,TRUE);  // Do not wait for characters using getch.  
      noecho();              // Do not echo input characters 
      getmaxyx(stdscr,y,x);  // Get the screen dimensions 
      w = init_well(((x/2)-(WELL_WIDTH/2)),1,WELL_WIDTH,WELL_HEIGHT);
      draw_well(w);
      srand(time(NULL));     // Seed the random number generator with the time. Used in create tet. 
      state = ADD_PIECE;
      //initialize color  
      start_color();
      init_pair(1, COLOR_RED, COLOR_RED);  
      init_pair(2, COLOR_GREEN, COLOR_GREEN);  
      init_pair(3, COLOR_YELLOW, COLOR_YELLOW);  
      init_pair(4, COLOR_BLUE, COLOR_BLUE);  
      init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);  
      init_pair(6, COLOR_CYAN, COLOR_CYAN);  
      init_pair(7, COLOR_WHITE, COLOR_WHITE);
      break;
<<<<<<< HEAD
    case ADD_PIECE:          // Add a new piece to the game
      if (!next) { // if it's not NULL , set the next to the current one  
	current = next; 
  // then create another next tetris 
	next = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y); 
      }
      else {
        // if it's null, then create both current and next
	current = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
  // create a tetromino and set it as current 
	next = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
  // create a tetromino and set it as current 
      }
      display_tetromino(current);
      // display the current tetromino

      // change the state to make the pieces
=======
    case ADD_PIECE:          // Add a new piece to the game     
      if (next) {    
	// if next exists, set next to the current one    
	current = next;    
  move_timeout = current->droprate;       
	// then create the next tetris    
	next = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);  
  }
  else {
        move_timeout = BASE_FALL_RATE;
	// if it doesn't exist,  create a tetromino and set it as current   
	current = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
	// create a tetromino and set it as next
	next = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);  }   
       display_next(next,  w->width/2 );
      display_tetromino(current);
      // change state to move the pieces
>>>>>>> d6b687d7f30c058a8148e49195cef918fc04a1c7
      state = MOVE_PIECE;
      break;
    case MOVE_PIECE:         // Move the current piece 
if ((arrow = read_escape(&c)) != NOCHAR) {
	switch (arrow) {
	case UP:
<<<<<<< HEAD
  undisplay_tetromino(current);
  rotate_cw(current);
  display_tetromino(current);
	  mvprintw(10,10,"UP            ");
	  break;
	case DOWN:
  undisplay_tetromino(current);
  rotate_ccw(current);
  display_tetromino(current);
	  mvprintw(10,10,"DOWN          ");
	  break;
	case LEFT:
    move_tet(current,current->upper_left_x--, current->upper_left_y);
	  mvprintw(10,10,"LEFT          ");
	  break;
	case RIGHT:
   move_tet(current,current->upper_left_x++, current->upper_left_y);
	  mvprintw(10,10,"RIGHT         ");
	  break;
  case SPACE: 
  // set the counter to 20 
  move_counter = 20; 
   break;
=======
    	  // makes the current tetromino rotate clockwise 
    	  // when UP (^) is pressed 
	  undisplay_tetromino(current);
	  rotate_cw(current);
	  display_tetromino(current);
	  mvprintw(10,10,"UP            ");
	  break;
	case DOWN:
	  // makes the current tetromino rotate counter clockwise 
	  // when DOWN is pressed 
	  undisplay_tetromino(current);
	  rotate_ccw(current);
	  display_tetromino(current);
	  mvprintw(10,10,"DOWN          ");
	  break;
	case LEFT:  
    undisplay_tetromino(current);
     move_tet(current,current->upper_left_x-1, current->upper_left_y) ;
	  // makes the current tetromino move left, bounded by left wall  
      display_tetromino(current); 
	 // display_tetromino(current);
	  mvprintw(10,10,"LEFT          ");
	  break;
	case RIGHT:  
	  // makes the current tetromino move right, bounded by right wall  
    undisplay_tetromino(current);
    move_tet(current,current->upper_left_x+1, current->upper_left_y) ;
    display_tetromino(current);  
	//  display_tetromino(current);
	  mvprintw(10,10,"RIGHT         ");
	  break; 
  case SPACE:
    move_timeout = DROP_RATE;
    break;
>>>>>>> d6b687d7f30c058a8148e49195cef918fc04a1c7
	case REGCHAR: 
	   //mvprintw(10,10,"REGCHAR 0x%02x",c);
	  if (c == 'q') {
		mvprintw(10,10,"QUIT         ",c);
	    state = EXIT;
<<<<<<< HEAD
 	  }else if(c == 'p'){
       state = PAUSE;
     }
	}
      } 
      if (move_counter++ >= move_timeout) { 
        // if want tetris to fall faster, decreae move timeout 
        // each time the counter times out, it moves down by one 
          move_tet(next,next->upper_left_x, next->upper_left_y--); 
      	move_counter = 0;
=======
 	  }
	  else if(c=='p'){ 
	    state = PAUSE; 
		mvprintw(10,10,"PAUSE         ",c);
	  } 
	} 
  } 
      if (move_counter++ >= move_timeout) { 
          // each time the counter times out, it moves down by one   
        undisplay_tetromino(current);      
          if(move_tet(current, current->upper_left_x, current->upper_left_y+1) == MOVE_FAILED){   
            // if the well height is the same as the curernt y-value 
            if(w->upper_left_y ==  current->upper_left_y){  
              // game will be over 
              state = GAME_OVER;
               } else{       
                 // assigns new value to the current piece
                 state = ADD_PIECE;  // creates new current 
                 }
            }   
            display_tetromino(current); 
	      move_counter = 0;
>>>>>>> d6b687d7f30c058a8148e49195cef918fc04a1c7
      }
      break;
    case EXIT:
      endwin();
      return(0);
      break;
    case PAUSE: 
<<<<<<< HEAD
    char unpause;
    nanosleep(0,0); 
=======
      if ((arrow = read_escape(&c)) != NOCHAR) {
        state = MOVE_PIECE; }
		break; 
    case GAME_OVER:  
    for(int y=0; y< 1000; y++){
      for(int x=0; x< 1000 ; x++){ 
        mvprintw(y, x, "   ");  
      } 
    } 
    mvprintw((WELL_HEIGHT/2),(WELL_WIDTH/2), "GAME OVER");
    break;
    }  
>>>>>>> d6b687d7f30c058a8148e49195cef918fc04a1c7
    refresh();
    nanosleep(&tim,&tim_ret); 
  } 
}
/* game.cpp ends here */
