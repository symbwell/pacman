#ifndef GENERALS_H_INCLUDED
#define GENERALS_H_INCLUDED

/**
  * Board struct with height and width.
  * Height is a number of rows.
  * Width is a sum of element in one row
  **/
typedef struct {
    int mapWidth;
    int mapHeight;
} Board;
//
typedef enum { F, T } Boolean;

#include "fruit.h"
#include "player.h"
#include "monsters.h"

//Function create the board.
Board* createBoard(int width, int height);

void destructBoard(Board* board);

/**
*   General setup before start game.
*/
void setup(MonsterArray* monsterArray, Player *ptrPlayer, Fruit *ptrFruit, Board *board, MonsterName*** monsterNames);

/**
*   Draw game.
*/
void draw(Player *player, MonsterArray *monstersArray, Fruit *fruit, Board *board);

//Save end score to name with date and name of the monster who killed us.
void saveScoreToFile(Player *player);

#endif
