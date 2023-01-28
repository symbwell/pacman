#ifndef FRUIT_H_INCLUDED
#define FRUIT_H_INCLUDED

typedef struct fruit Fruit;

struct fruit
{
    int x;
    int y;
    int alive;
};

#include "monsters.h"

Fruit *getFruit();

void destructFruit(Fruit* fruit);

void fruitsRenderEngine(Fruit *ptrFruit, MonsterArray *monsters, Board *board);

int isFruit(Fruit *ptr, int x,int y);

#endif
