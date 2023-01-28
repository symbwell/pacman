#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

//Player structure
typedef struct {
    int coordinateX;
    int coordinateY;
    int score;
    Monster* monsterWhoKill;
} Player;

#include "general.h"
#include "fruit.h"

//Function return player structure pointer with allocate memory.
Player *getPlayer();

//Function free memory from player.
void destructPlayer(Player* player);

//The function checks if there is a player under the X and Y coordinates
int isPlayer(Player *ptr, int x, int y);

//Function responsible for render player on the map
void playerRenderEngine(Player *ptr, Board *board);

//Function recognize if player get the fruit.
int isPlayerGetTheFruit(Player *player, Fruit *fruit);

#endif
