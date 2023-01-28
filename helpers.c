#include "helpers.h"

int randNumber(int minimum, int maximum)
{
    return minimum + rand() % (maximum - minimum + 1);
}

Direction randomDirection() {
    int randomNum = rand() % 4;
    switch (randomNum) {
        case 0: return North;
        case 1: return East;
        case 2: return South;
        case 3: return West;
    }

    return North;
}

Direction randomFromTwoDirection(Direction first, Direction second)
{
    int randomNum = rand() % 2;
    switch (randomNum) {
        case 0: return first;
        case 1: return second;
    }

    return first;
}

int hello()
{
    short int countOfMonsters = 0;

    puts("Welcome to a game you'll become addicted to.");
    puts("The rules are simple. Your designation is P. Avoid monsters (M). Collect fruits (*). Earn points.");
    puts("But first...");
    puts("");

    do {
        printf("Specify the number of opponents (maximum 20): ");
        scanf("%hd", &countOfMonsters);
    }
    while(countOfMonsters > 20 || countOfMonsters <= 0);

    return countOfMonsters;
}
