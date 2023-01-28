#include "general.h"
#include "monsters.h"
#include <stdio.h>
#include <windows.h>
#include <time.h>

Board* createBoard(int width, int height)
{
    Board *board = calloc(1, sizeof(Board));

    board->mapHeight = height;
    board->mapWidth = width;

    return board;
}

void destructBoard(Board* board)
{
    free(board);
}

/**
*   General setup before start game.
*/
void setup(MonsterArray* monsterArray, Player *ptrPlayer, Fruit *ptrFruit, Board *board, MonsterName*** monsterNames)
{
    //Map Setup. Print the board.
    for(int mapHeight = 0; mapHeight <= board->mapHeight; mapHeight++)
    {
        for(int mapRow = 0; mapRow <= board->mapWidth; mapRow++)
        {
            if(mapHeight == 0 || mapHeight == board->mapHeight) {
                printf("#");
            } else if (mapRow == 0 || mapRow == board->mapWidth) {
                printf("#");
            } else {
                printf(" ");
            }
        }

        printf("\n");
    }

    //MonstersSetup. Randomly locate monsters on board.
    for(int monsterIndex = 0; monsterIndex < monsterArray->_size; monsterIndex++)
    {
        monsterArray->arr[monsterIndex] = *generateNewMonster(monsterArray, ptrPlayer, board, monsterNames, monsterIndex);
    }

    // Set initial player coordinates for top left corner of board.
    ptrPlayer->coordinateX = 1;
    ptrPlayer->coordinateY = 1;
}

void draw(Player *player, MonsterArray *monstersArray, Fruit *fruit, Board *board)
{
    for(int mapHeight = 1; mapHeight < board->mapHeight; mapHeight++)
    {
        for(int mapRow = 1; mapRow < board->mapWidth; mapRow++)
        {
            COORD c;
            c.X = mapRow;
            c.Y = mapHeight;

            SetConsoleCursorPosition(
                GetStdHandle(STD_OUTPUT_HANDLE), c);

            if(isMonster(monstersArray, mapHeight, mapRow) != NULL) {
                printf("M");
            } else if(isPlayer(player, mapHeight, mapRow)) {
                printf("P");
            } else if(isFruit(fruit, mapHeight, mapRow)) {
                printf("*");
            } else {
                printf(" ");
            }
        }

        printf("\n");
    }

    puts("");
    printf("Your score: %d", player->score);
}

void saveScoreToFile(Player *player)
{
    time_t t = time(NULL);
    struct tm *local = localtime(&t);
    char buf[80];
    strftime(buf, sizeof(buf), "%c", local);

    FILE* file;

    if((file=fopen("score.txt","a+"))==NULL){
        fprintf(stdout, "Cannot save your score to file. Sorry.");
        exit(1);
    }

    fprintf(file, "(%s) Your score: %d. You killed by: %s\n", buf, player->score, player->monsterWhoKill->name->name);
    rewind(file);

    if(fclose(file) != 0) {
        fprintf(stderr, "Error while closing file\n");
    }
    fclose(file);
}
