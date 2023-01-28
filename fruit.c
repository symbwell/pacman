#include "fruit.h"
#include "monsters.h"

Fruit *getFruit()
{
    Fruit *ptr = (Fruit *) calloc(1, sizeof(Fruit));

    return ptr;
}

void destructFruit(Fruit* fruit)
{
    free(fruit);
}

int isFruit(Fruit *ptr, int x,int y)
{

    if(ptr->x == x && ptr->y == y)
    {
        return 1;
    }

    return 0;
}

void fruitsRenderEngine(Fruit *ptrFruit, MonsterArray *monsters, Board *board)
{
    if(ptrFruit->alive == 0){
        int tempX, tempY;

        do {
            tempX = (rand() % board->mapHeight) + 6;
            tempY = (rand() % board->mapWidth) + 6;
        } while (
            (tempX >= board->mapHeight || tempY >= board->mapWidth) &&
            !isMonster(monsters, tempX, tempY)
        );

        ptrFruit->x = tempX;
        ptrFruit->y = tempY;
        ptrFruit->alive = 1;
    }
}
