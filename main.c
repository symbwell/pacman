#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "monsters.h"
#include "player.h"
#include "fruit.h"
#include "general.h"
#include "helpers.h"

#define VERSION 2
#define MAP_WIDTH 30
#define MAP_HEIGHT 20

int main(void)
{
    srand(time(NULL));

    int *game_over_Ptr;
    MonsterName** monsterNamesPtrArr = NULL;

    int monstersSize = hello();
    int game_over = 0;
    int mapHeight = MAP_HEIGHT;
    int mapWidth = MAP_WIDTH;

    system("@cls||clear");

    Board *board = createBoard(mapWidth, mapHeight);

    if(board == NULL) {
        printf("There is an internal error with allocate memory. Please try again.\n");
        return 0;
    }

    Player *ptrPlayer = getPlayer();

     if(ptrPlayer == NULL) {
        printf("There is an internal error with alocate memory. Please try again.\n");
        return 0;
    }

    Fruit *ptrFruit = getFruit();

     if(ptrFruit == NULL) {
        printf("There is an internal error with alocate memory. Please try again.\n");
        return 0;
    }

    MonsterArray *monsters = getMonstersArray(monstersSize);

    if(monsters == NULL) {
        printf("There is an internal error with alocate memory. Please try again.\n");
        return 0;
    }

    game_over_Ptr = &game_over;

    createMonsterNames(&monsterNamesPtrArr, monsters->_size);
    setup(monsters, ptrPlayer, ptrFruit, board, &monsterNamesPtrArr);

    while(*game_over_Ptr == 0) {

        clock_t t1;
        t1 = clock();

        if ((t1 - (monsters->secondsCounter)) >= 10000) {
            monsters->secondsCounter = t1;
            removeMonsterFromArray(monsters);
            Monster* newMonster = generateNewMonster(monsters, ptrPlayer, board, &monsterNamesPtrArr, monsters->_size + 1);
            addNewMonsterToArray(monsters, newMonster);

        }

        monstersRenderEngine(monsters, ptrPlayer, board, t1);
        playerRenderEngine(ptrPlayer, board);
        fruitsRenderEngine(ptrFruit, monsters, board);

        draw(ptrPlayer, monsters, ptrFruit, board);

        if(isPlayerGetTheFruit(ptrPlayer, ptrFruit)) {
            ptrFruit->alive = 0;
            ptrPlayer->score += 10;
        }

        if(isMonsterEatPlayer(ptrPlayer, monsters)) {
            *game_over_Ptr = 1;
        }
    }

    system("@cls||clear");
    puts("You Lose");
    printf("Final score: %d\n", ptrPlayer->score);
    saveScoreToFile(ptrPlayer);
    puts("Click X to quit the game.");

    destructMonsters(monsters);
    destroyMonsterNames(&monsterNamesPtrArr, monstersSize);
    destructFruit(ptrFruit);
    destructBoard(board);

    char var;
    while(var != 'x')
    {
        var = getch();
    };

    destructPlayer(ptrPlayer);
    return 0;
}
