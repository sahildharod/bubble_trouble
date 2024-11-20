#include <simplecpp>

//all variables needed across files are put here

/*Simulation vars*/
const double STEP_TIME = 0.02;
const int TOTAL_TIME = 51;//time in seconds + 1, max. value 100 as of now.

/* Game Window Vars */
const int WINDOW_X = 500;
const int WINDOW_Y = 500;
const int PLAY_Y_HEIGHT = 450;
const int LEFT_MARGIN = 70;
const int TOP_MARGIN = 20;
const int BOTTOM_MARGIN = (PLAY_Y_HEIGHT+TOP_MARGIN);

/* Shooter Vars */
const int SHOOTER_START_X = 250;
const int SHOOTER_START_Y = 425;
const double SHOOTER_VX = 600;
const int HEAD_RADIUS = 8;
const int SHOOTER_HEIGHT = 30;
const int SHOOTER_WIDTH = 18;
const int INITIAL_HEALTH = 100;//10 health per hit

/* Bubble Vars */
const int BUBBLE_START_X = 200;
const int BUBBLE_START_Y = 0;
const int BASE_BUBBLE_RADIUS = 10;
const int BUBBLE_DEFAULT_VX = 400;
const int BUBBLE_DEFAULT_VY = 50;
