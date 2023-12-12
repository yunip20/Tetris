/* tetromino.hpp --- 
 * 
 * Filename: tetromino.hpp
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

typedef struct tetromino{
  char type_str[20];
  char piece[4][4];             // 4x4 grid of characters, piece[x][y]
  int upper_left_x;
  int upper_left_y;
  char draw_char;
  //char color[3];
  int color;
  int droprate;
} tetromino_t;

extern const int tetromino_droprates[5]; // 5 different droprates
extern const tetromino_t tetromino_types[9];

enum {SAFE, COLLIDE}; // Return status for check_collision 
int check_collision (tetromino_t *);

enum {MOVE_OK, MOVE_FAILED}; // Return status for move
int move_tet (tetromino_t *, int, int);
int rotate_cw(tetromino_t *);
int rotate_ccw(tetromino_t *);
tetromino_t *create_tetromino (int, int);
int destroy_tetromino(tetromino_t *);
//void print_tetromino(tetromino_t *tet);
void undisplay_tetromino(tetromino_t *tet);
void display_tetromino(tetromino_t *tet);
<<<<<<< HEAD
void undisplay_tetromino(tetromino_t *tet);
void test_tetromino(void);
=======
void display_next(tetromino_t *tet,   int);
//void test_tetromino(void);
>>>>>>> d6b687d7f30c058a8148e49195cef918fc04a1c7

/* tetromino.hpp ends here */