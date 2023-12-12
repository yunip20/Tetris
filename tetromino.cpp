/* tetromino.cpp --- 
 * 
 * Filename: tetromino.cpp
 * Description: 
 * Author: Bryce
 * Maintainer: Adeel Bhutta
 * Created: Tue Sep  6 11:08:59 2016
 * Last-Updated: 01-10-2021
 *           By: Adeel Bhutta
 *     Update #: 0
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

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <ncurses.h>
#include "tetromino.hpp"

const tetromino_t tetromino_types[9] = {
  {"new1",
   {{1,1,1,0},
    {1,0,0,0},
    {1,0,0,0},
    {0,0,0,0}}, 
   0,
   0,
   '%',
   0, 0}, 
   {"new2",
   {{1,1,1,1},
    {0,1,0,0},
    {0,0,0,0},
    {0,0,0,0}}, 
   0,
   0,
   '%',
   0, 0},
  {"block",
   {{0,0,0,0}, 
    {0,1,1,0},
    {0,1,1,0},
    {0,0,0,0}}, 
   0,
   0,
   '%',
   0, 0},
  {"tee",
   {{0,0,0,0}, 
    {1,1,1,0},
    {0,1,0,0},
    {0,0,0,0}}, 
   0,
   0,
   '%',
   0, 0},
  {"zigzag_l",
   {{0,0,1,0}, 
    {0,1,1,0},
    {0,1,0,0},
    {0,0,0,0}}, 
   0,
   0,
   '%',
   0, 0},
  {"zigzag_r",
   {{0,1,0,0}, 
    {0,1,1,0},
    {0,0,1,0},
    {0,0,0,0}}, 
   0,
   0,
   '%',
   0, 0},
  {"lform_l",
   {{0,0,1,0}, 
    {0,0,1,0},
    {0,1,1,0},
    {0,0,0,0}}, 
   0,
   0,
   '%',
   0, 0},
  {"lform_r",
   {{0,1,0,0}, 
    {0,1,0,0},
    {0,1,1,0},
    {0,0,0,0}}, 
   0,
   0,
   '%',
   0, 0},
  {"pipe",
   {{0,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0}}, 
   0,
   0,
   '%',
   0, 0}
};

const int tetromino_droprates[5] = {
400, 300, 100, 700, 900
};

int check_collision (tetromino_t *tet) {
  /* Function to check if the tetromino is currenly overlapping
     anything other than a space.  Spaces are used to designate a site
     that is free of a character in ncurses.
     
     Uses ncurses function mvinchnstr to read back rows of characters
     that have been previously placed on the screen from the location
     where the tet is currently placed. 4 rows are read that represent
     the 4x4 area of a tetromino.
     If an overlap is detected, the function returns
     COLLIDE. Otherwise it returns SAFE.
  */
  int x,y;
  chtype row_buf[5];
  int num_chars;
  int i;
  for (y=0;y<+4;y++) {
    num_chars = mvinchnstr(tet->upper_left_y+y, tet->upper_left_x, row_buf, 4);
    for (x=0;x<4;x++) {
      if (tet->piece[x][y] && row_buf[x]!=' ') {
	        return COLLIDE;
      }
    }
  }
  return SAFE;
}

int move_tet (tetromino_t *tet, int new_x, int new_y) {
  /* Moves the tetromino if it will not collide with another feature
     on the screen such as the well or a previously placed tets. 
     The old position of the tet is saved so that it can be returned
     to this position if there is a collision. The new position passed
     as an argument is applied to the tet. The tet is then checked for
     collision.
     If a collistion is detected, then the tet is returned back to
     it's original location and a status of MOVE_FAILED is
     returned. Otherwise a status if MOVE_OK is returned.
   */
  int old_x = tet->upper_left_x;
  int old_y = tet->upper_left_y;
  tet->upper_left_x = new_x;
  tet->upper_left_y = new_y;
  if (check_collision(tet) == COLLIDE) {
    tet->upper_left_x = old_x;
    tet->upper_left_y = old_y;
    return MOVE_FAILED;
  }  
  else {
    return MOVE_OK;
  }
}

int rotate_cw(tetromino_t *tet) {
  /* Rotates a tetromino clockwise. A copy of the tetromino is saved
   prior to executing the rotation. If a collision is detected as a
   result of the rotation, the original tet is restored and a status
   of MOVE_FAILED is returned. Otherwise MOVE_OK is returned.
  */
  char temp[4][4];
  int x,y;
  tetromino_t temp_tet;
  // tempt_tet is not edited throughout the function
  memcpy(&temp_tet,tet,sizeof(tetromino_t));
  for (x=0;x<4;x++) {
    for (y=0;y<4;y++) { 
      // sets the new rotation (new piece[x][y])
      temp[x][y] = tet->piece[y][3-x]; 
    }
  } 
  // rotates the original piece 
  memcpy(tet->piece,&temp,sizeof(tet->piece));
  if (check_collision(tet) == COLLIDE) {
    // restoring
    memcpy(tet,&temp_tet,sizeof(tetromino_t));
    return MOVE_FAILED;
  }
  else {
    return MOVE_OK;
  }
}

int rotate_ccw(tetromino_t *tet) {
  /* Rotates a tetromino counter clockwise. A copy of the tetromino is saved
   prior to executing the rotation. If a collision is detected as a
   result of the rotation, the original tet is restored and a status
   of MOVE_FAILED is returned. Otherwise MOVE_OK is returned.
  */
  char temp[4][4];
  int x,y;
  tetromino_t temp_tet;
  // &temp_tet is not edited throughout the function 
  // so that it can be used for restoration 
  memcpy(&temp_tet,tet,sizeof(tetromino_t));
  for (x=0;x<4;x++) {
    for (y=0;y<4;y++) {
      // creates the new  angle for rotation
      temp[x][y] = tet->piece[3-y][x]; 
    }
  }
  // rotating: applying the angle to the actual piece 
  memcpy(tet->piece,&temp,sizeof(tet->piece));
  if (check_collision(tet) == COLLIDE) {
    // restoring 
    memcpy(tet,&temp_tet,sizeof(tetromino_t));
    return MOVE_FAILED;
  }
  else {
    return MOVE_OK;
  }
}

tetromino_t *create_tetromino (int initial_x, int initial_y) {
<<<<<<< HEAD
  /* Creates a random tetronimo and sets the location to be 
      the x, y position that the function takes in
  */
  int type;
  // initializes new tet 
  tetromino_t *tet = (tetromino*) malloc(sizeof(tetromino_t));
  // creates random type(shape)
  type = rand()%7;
  // creates new tetronimo by setting tet to the given tetronimo type
=======
  int type; 
  int color = rand() % 7 +1;
  tetromino_t *tet = (tetromino*) malloc(sizeof(tetromino_t));
  type = rand()%9; 
>>>>>>> d6b687d7f30c058a8148e49195cef918fc04a1c7
  memcpy(tet, &tetromino_types[type], sizeof(tetromino_t));
  // sets the x and y position of the new tet
  tet->upper_left_x = initial_x;
  tet->upper_left_y = initial_y; 
  tet->color =  color;  
  tet->droprate = tetromino_droprates[rand()%5];  
  return(tet);
}

void display_tetromino(tetromino_t *tet) {  
  initscr();
  start_color();
  int x,y;
  for (x=0;x<4;x++) {
    for (y=0;y<+4;y++) {
<<<<<<< HEAD
      // displays (1 == true) 
      // doesn't display (0 == false)
      if (tet->piece[x][y]) {
        // gets the elements of that tet to draw out (x,y) and prints the character 
        // WHY ADD X AND Y? 
	mvprintw(tet->upper_left_y+y,tet->upper_left_x+x,"%c",tet->draw_char);
=======
      if (tet->piece[x][y]) {    
        int key = tet->color;
        attron(COLOR_PAIR(key));
      	mvprintw(tet->upper_left_y+y,tet->upper_left_x+x,"%c",tet->draw_char);
        attroff(COLOR_PAIR(key));
>>>>>>> d6b687d7f30c058a8148e49195cef918fc04a1c7
      }
    }
  }
}

void undisplay_tetromino(tetromino_t *tet) {
  int x,y;
  for (x=0;x<4;x++) {
    for (y=0;y<+4;y++) {
      // 0's are not printed 
      if (tet->piece[x][y]) { 
        // not printed by setting printing string value as ""
	mvprintw(tet->upper_left_y+y,tet->upper_left_x+x," ",tet->draw_char);
      }
    }
  }
}

int destroy_tetromino(tetromino_t *tet) {
  // dallocates previously allocated memory 
  // doesn't change value of the pointer, still has the same memory
  free(tet);
}

void display_next(tetromino_t *tet, int wellwidth){
  for (int x=0;x<4;x++) {
    for (int y=0;y<+4;y++) {
      mvprintw(tet->upper_left_y+y,tet->upper_left_x+x+wellwidth+4," ",tet->draw_char);
      if (tet->piece[x][y]) {  
        int key = tet->color;
        attron(COLOR_PAIR(key));
      	mvprintw(tet->upper_left_y+y,tet->upper_left_x+x+wellwidth+4,"%c",tet->draw_char);
        attroff(COLOR_PAIR(key));
        }
      } 
    }
}

/* tetromino.cpp ends here */