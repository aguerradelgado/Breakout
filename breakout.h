// file: breakout.h
//  lab:  11
//   by:  A.Guerra
//  org:  COP 2001, 202101, 10410
// desc:  main application header file for a 2D Breakout game
// ----------------------------------------------------------

#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <string>   // window title

#include "fgcugl.h" // OpenGL
#include "block.h"

//-------------------------------------------
// enumes

enum Direction {
    DIR_EXIT = -1,
    DIR_NONE,
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
};

//-------------------------------------------
// global constants

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 604;
const std::string WINDOW_TITLE = "Breakout";

// game settings
const double FRAME_RATE = 1.0 / 60.0;


// game components

// player paddle properties
int PADDLE_WIDTH = 96;
int PADDLE_HEIGHT = 20;

// ball properties
const int BALL_SIZE = 8;    // radius of the ball in pixels
const fgcugl::Color BALL_COLOR = fgcugl::Blue;
const float BALL_SPEED_X = 40.0;   // speed horizontally in pixels
const float BALL_SPEED_Y = 70.0;   // speed vertically in pixels

// border walls
const int WALL_SIZE = 2;  // 2 pixels

// bricks
const int BRICK_WIDTH = 64;
const int BRICK_HEIGHT = 20;
const int BRICK_COLUMNS = 14;  // number of bricks across
const int BRICK_ROWS = 8;      // number of bricks down
const int BRICKS_START_X = WALL_SIZE;
const int BRICKS_START_Y = (WINDOW_HEIGHT - 2 * WALL_SIZE) / 2;

//-------------------------------------------
// structures

// border walls
struct Walls {
    Block top;
    Block bottom;
    Block left;
    Block right;
};

#endif //BREAKOUT_H