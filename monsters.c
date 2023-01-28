#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monsters.h"
#include "player.h"
#include "helpers.h"

MonsterArray* getMonstersArray(const unsigned char _size)
{

    MonsterArray* monsters = (MonsterArray* ) malloc(sizeof(MonsterArray));

    if(monsters == NULL) {
        puts("Error, cannot allocate memory for monsterArray");
        return NULL;
    }

    monsters->_size = _size;
    monsters->secondsCounter = 0;
    monsters->arr = (Monster *) calloc(monsters->_size, sizeof(Monster));

    if(monsters->arr == NULL) {
        puts("Error, cannot allocate memory for inner array of struct monster.");
        free(monsters);
        return NULL;
    }

    return monsters;
}

void removeMonsterFromArray(MonsterArray* monsters)
{
    if(monsters == NULL) {
        puts("Error, monster array is NULL");
        return;
    }

    if(monsters->_size == 0) {
        puts("Error, monster array has no elements.");
        return;
    }

    int index = rand() % monsters->_size;

    for(int i = index; i < monsters->_size - 1; i++) {
        monsters->arr[i] = monsters->arr[i + 1];
    }

    monsters->_size--;
}

void addNewMonsterToArray(MonsterArray* monsters, Monster* monster)
{
    if(monsters == NULL) {
        puts("Error, monster array is NULL");
        return;
    }

    monsters->_size++;
    monsters->arr = (Monster*) realloc(monsters->arr, monsters->_size * sizeof(Monster));

    if (monsters->arr == NULL) {
        puts("Error, cannot allocate memory for new monster");
        return;
    }

    monsters->arr[monsters->_size - 1] = *monster;
}

Monster* generateNewMonster(MonsterArray* monsterArray, const Player* player, const Board* board, MonsterName*** monsterNames, const char index)
{
    unsigned char tempX, tempY;
    Monster* monster = (Monster*) malloc(sizeof(Monster));

    do {
        tempX = (rand() % board->mapHeight) + 6;
        tempY = (rand() % board->mapWidth) + 6;
    } while (
        (tempX >= board->mapHeight || tempY >= board->mapWidth)
            && isMonster(monsterArray, tempX, tempY) == NULL
    );

    monster->id = index;
    monster->coordinateX = tempX;
    monster->coordinateY = tempY;
    monster->direction = getNewDirection(Empty,tempX,tempY, player, board);
    monster->secondsCounter = 0;
    monster->stepCounter = 0;

    assignMonsterName(monster, *(*monsterNames + index));

    return monster;
}

void assignMonsterName(Monster* monster, MonsterName* monsterName) {
    monster->name = monsterName;
}

void destructMonsters(MonsterArray* monsterArray)
{
    free(monsterArray->arr);
    free(monsterArray);
}

void createMonsterNames(MonsterName*** monsterName, const unsigned char _size)
{
    MonsterName** temp = (MonsterName**) calloc(_size, sizeof(MonsterName*));
    char name[100];
    int total = 0;
    FILE* file;

    if(monsterName == NULL) {
        printf("Error, cannot allocate memory in createMonsterNames[45]");
        return;
    }

    file = fopen("names.txt", "r");

    if(file) {
        while(fgets(name, sizeof(name), file)) {
            total++;
        }
    } else {
        printf("Cannot open file with names");
        return;
    }

    rewind(file);

    for(int i = 0; i < _size; i++){
        int randomNameIndex = rand() % total;

        for(int j = 0; j <= randomNameIndex; j++)
        {
            if(fgets(name, sizeof(name), file) == NULL) {
                printf("Cannot read name from file");
                destroyTemporaryMonsterName(temp, i, T);
                fclose(file);
                return;
            }
        }

        temp[i] = (MonsterName*) malloc(sizeof(MonsterName));

        if(temp[i] == NULL) {
            printf("Error, cannot allocate memory for struct monsterName.");
            destroyTemporaryMonsterName(temp, i, T);
            fclose(file);
            return;
        }
        temp[i]->name = (char*) malloc(sizeof(char));

        if(temp[i]->name == NULL) {
            printf("Error, cannot allocate memory for name of struct monsterName.");
            destroyTemporaryMonsterName(temp, i, F);
            fclose(file);
            return;
        }

        temp[i]->name = strdup(name);
        rewind(file);
    }

    fclose(file);

    *monsterName = temp;
}

void destroyTemporaryMonsterName(MonsterName** temp, const unsigned char _size, Boolean alsoName)
{
    for(int k = _size-1; k >= 0; k--) {
        if(alsoName == T) {
            free(temp[k]->name);
        }
        free(temp[k]);
    }
    free(temp);
}

void destroyMonsterNames(MonsterName*** monsterName, const unsigned char _size)
{
    for(int i = 0; i < _size; i++){
        free((*monsterName)[i]->name);
        free((*monsterName)[i]);
    }
    free(*monsterName);
    *monsterName = NULL;
}

Monster* isMonster(const MonsterArray *ptr, const unsigned char xField, const unsigned char yField)
{

    for(int monster = 0; monster < ptr->_size; monster++)
    {
        if(ptr->arr[monster].coordinateX == xField && ptr->arr[monster].coordinateY == yField)
        {
            return &ptr->arr[monster];
        }
    }

    return NULL;
}

int isMonsterEatPlayer(Player *playerPtr, MonsterArray *monsterPtr)
{
    Monster* monster = isMonster(monsterPtr, playerPtr->coordinateX, playerPtr->coordinateY);

    if(monster != NULL) {
        playerPtr->monsterWhoKill = monster;
        return 1;
    }

    return 0;
}

void monstersRenderEngine(MonsterArray *monstersPtr, const Player *ptrPlayer, const Board *board, clock_t t1)
{

    //MonstersSetup
    for(int monster = 0; monster < monstersPtr->_size; monster++)
    {
        if ((t1 - (monstersPtr->arr[monster].secondsCounter)) <= 400)
            break;

        monstersPtr->arr[monster].secondsCounter = t1;

        int forceChangeDirection = 0;
        int wasMove = 0;

        while(wasMove == 0) {

            int currentX = monstersPtr->arr[monster].coordinateX;
            int currentY = monstersPtr->arr[monster].coordinateY;

            if(monstersPtr->arr[monster].stepCounter == 3 || forceChangeDirection == 1) {
                monstersPtr->arr[monster].stepCounter = 0;

                Direction newDirection = getNewDirection(monstersPtr->arr[monster].direction, currentX, currentY, ptrPlayer, board);
                monstersPtr->arr[monster].direction = newDirection;
            }

            switch(monstersPtr->arr[monster].direction) {
            case North:
                //top
                {
                    int newStep = currentX - 1;

                    if(isNextStepEndOfMap(currentX, currentY, North, board) || isMonster(monstersPtr, newStep, currentY) != NULL){
                        forceChangeDirection = 1;
                    }else {
                        monstersPtr->arr[monster].coordinateX = newStep;
                        monstersPtr->arr[monster].stepCounter++;
                        wasMove = 1;
                    }
                }
                break;

            case South: //bottom
                {
                    int newStep = currentX + 1;

                    if(isNextStepEndOfMap(currentX, currentY, South, board) || isMonster(monstersPtr, newStep, currentY) != NULL){
                        forceChangeDirection = 1;
                    }else {
                        monstersPtr->arr[monster].coordinateX = newStep;
                        monstersPtr->arr[monster].stepCounter++;
                        wasMove = 1;
                    }
                }
                break;

            case East: //right
                {
                    int newStep = currentY + 1;

                    if(isNextStepEndOfMap(currentX, currentY, East, board) || isMonster(monstersPtr, currentX, newStep) != NULL){
                        forceChangeDirection = 1;
                    }else {
                        monstersPtr->arr[monster].coordinateY = newStep;
                        monstersPtr->arr[monster].stepCounter++;
                        wasMove = 1;
                    }
                }
                break;

            case West: //left
                {
                    int newStep = currentY - 1;

                    if(isNextStepEndOfMap(currentX, currentY, West, board) || isMonster(monstersPtr, currentX, newStep) != NULL){
                        forceChangeDirection = 1;
                    }else {
                        monstersPtr->arr[monster].coordinateY = newStep;
                        monstersPtr->arr[monster].stepCounter++;
                        wasMove = 1;
                    }
                }
                break;
            }

        }
    }
}

Direction getNewDirection(
    const Direction previousDirection,
    const unsigned char x,
    const unsigned char y,
    const Player *ptrPlayer,
    const Board *board
)
{

    Direction newDirection = Empty;
    Direction direction = Empty;
    int goToPlayer = randNumber(0,1);

    while(newDirection == Empty){
        switch(previousDirection) {
        case North:
            {
                if(goToPlayer){
                    if(y <= ptrPlayer->coordinateY) {
                        direction = East;
                    }else {
                        direction = West;
                    }
                } else {
                   direction = randomFromTwoDirection(East,West);
                }
            }
            break;
        case South:
            {
                if(goToPlayer){
                    if(y <= ptrPlayer->coordinateY) {
                        direction = East;
                    }else {
                        direction = West;
                    }
                } else {
                   direction = randomFromTwoDirection(East,West);
                }
            }
            break;
        case East:
            {
                if(goToPlayer){
                    if(x <= ptrPlayer->coordinateX) {
                        direction = South;
                    }else {
                        direction = North;
                    }
                } else {
                   direction = randomFromTwoDirection(North, South);
                }
            }
            break;
        case West:
            {
                if(goToPlayer){
                    if(x <= ptrPlayer->coordinateX) {
                        direction = South;
                    }else {
                        direction = North;
                    }
                } else {
                   direction = randomFromTwoDirection(North, South);
                }
            }
            break;
        default:
            {direction = randomDirection();}
            break;
        }

        if(direction != Empty && isNextStepEndOfMap(x,y,direction, board) != 1) {
            newDirection = direction;
        }
    }

    return newDirection;
}

int isNextStepEndOfMap(const unsigned char x, const unsigned char y, const Direction direction, const Board *board)
{

    switch(direction) {
    case North:
        //top
        return x <= 1;
        break;

    case South:
        //bottom
        return x >= board->mapHeight -1;
        break;

    case East:
        //right
        return y >= board->mapWidth - 1;
        break;

    case West:
        //left
        return y <= 1;
        break;
    }

    return 0;
}

