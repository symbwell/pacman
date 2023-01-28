#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include "monsters.h"

//Helper function allow to rand intiger number from range.
int randNumber(int minimum, int maximum);

//Initial function allow user to choose how many monsters should be on the map.
int hello();

//Function allow to get random direction from enum Direction.
Direction randomDirection();

//Function allow to get random direction between one of the directions from arguments.
Direction randomFromTwoDirection(Direction first, Direction second);

#endif
