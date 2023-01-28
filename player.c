#include "fruit.h"
#include "player.h"
#include "monsters.h"
#include <conio.h>

Player *getPlayer()
{
    Player *ptr = (Player *) calloc(1, sizeof(Player));

    return ptr;
}

void destructPlayer(Player* player)
{
    free(player);
}

int isPlayerGetTheFruit(Player *player, Fruit *fruit)
{
    if(player->coordinateX == fruit->x && player->coordinateY == fruit->y){
        return 1;
    }

    return 0;
}

/**
*   Check if is a player on coordinates
*/
int isPlayer(Player *ptr, const int x,const int y)
{

    if(ptr->coordinateX == x && ptr->coordinateY == y)
    {
        return 1;
    }

    return 0;
}

void playerRenderEngine(Player *ptr, Board *board)
{
    if(kbhit()) {
        switch(getch()) {
        case 'w':
            if(ptr->coordinateX != 1) {
                ptr->coordinateX -= 1;
            }
            break;

        case 's':
            if(ptr->coordinateX != board->mapHeight - 1) {
                ptr->coordinateX += 1;
            }
            break;

        case 'a':
            if(ptr->coordinateY != 1) {
              ptr->coordinateY -= 1;
            }
            break;

        case 'd':
            if(ptr->coordinateY != board->mapWidth - 1){
                ptr->coordinateY += 1;
            }
            break;
        }
    }
}
