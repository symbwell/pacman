/**
 *
 *  This file contains all methods to create, destruct and managements monsters in the game.
 *
 */

#ifndef MONSTERS_H_INCLUDED
#define MONSTERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/** Describe directions of monsters. The "Empty" value is use only when monster is initialized. */
typedef enum { North, East, South, West, Empty } Direction;

/** Structure stores the name of the monster. */
typedef struct
{
    short int id;
    char* name;
} MonsterName;

/** Monster Structure. */
typedef struct
{
    short int id;
    short int coordinateX; //Current X coordinate on a board
    short int coordinateY; //Current Y coordinate on a board
    Direction direction; //Current direction (North, South, East, West)
    short int stepCounter; //How many steps did the monster take
    long double secondsCounter; //It stores the time when the monster took a step. Needed for non-blocking monster movement delay.
    MonsterName* name; //Monster name
} Monster;

/**
    Main structure of monsters.
    Stores their number, an array of Monster structures,
    and a seconds counter
    (needed to dynamically remove and add monsters every 10 seconds)
*/
typedef struct
{
    size_t _size;
    long double secondsCounter;
    Monster *arr;
} MonsterArray;

#include "player.h"
#include "general.h"

/** Creates an array of pointers with structures containing the names of monsters. */
void createMonsterNames(MonsterName*** monsterName, const unsigned char _size);

/** An helper function to remove allocated memory for names. Used in case of allocation problems. */
void destroyTemporaryMonsterName(MonsterName** temp, const unsigned char _size, Boolean alsoName);

/** Function assigns a name to a monster. */
void assignMonsterName(Monster* monster, MonsterName* monsterName);

/** Function remove all monster names from memory. */
void destroyMonsterNames(MonsterName*** monsterName, const unsigned char _size);

/** Add new monster to array of monsters with relloc. */
void addNewMonsterToArray(MonsterArray* monsters, Monster* monster);

/** Remove random monster struct from array of monster. */
void removeMonsterFromArray(MonsterArray* monsters);

/** Generate new monster. This function is used when we dynamically destroy and add new monster. */
Monster* generateNewMonster(MonsterArray* monsterArray, const Player* player, const Board* board, MonsterName*** monsterNames, const char index);

/**
 *  Create struct MonsterArray with size (count of monsters)
 *  and array of struct Monster which contains
 *  single monster.
 */
MonsterArray* getMonstersArray(const unsigned char _size);

/**
 *  Free memory of monsters.
 */
void destructMonsters(MonsterArray* monsterArray);

/**
 *  Check is a monster on a board in x and y coordinates.
 */
Monster* isMonster(const MonsterArray *ptr, const unsigned char xField, const unsigned char yField);

/**
 *  Check is a monster eat the player which is basically end of the game.
 */
int isMonsterEatPlayer(Player *playerPtr, MonsterArray *monsterPtr);


/**
 *  Set new monster coordinates (based on getNewDirection).
 */
void monstersRenderEngine(MonsterArray *monstersPtr, const Player *ptrPlayer, const Board *board, clock_t t1);

/**
 *  Calculate new direction of monster
 *  (is monster should go top, bottom, left or right).
 */
Direction getNewDirection(
    const Direction previousDirection,
    const unsigned char x,
    const unsigned char y,
    const Player *ptrPlayer,
    const Board *board
);

/**
 *  Check if next of monster move is end of the map.
 */
int isNextStepEndOfMap(const unsigned char x, const unsigned char y, const Direction direction, const Board *board);

#endif
