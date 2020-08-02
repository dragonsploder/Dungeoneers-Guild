#include "common.h"

#define TASK_DUNGEON 0
#define TASK_FETCH 1

#define NUMBER_OF_TYPES 2
int typeConvert[NUMBER_OF_TYPES][10] = {
    {1, 2, 3, 4, 5, 6,-1,-1,-1,-1},
    {6, 7, 8, 9,-1,-1,-1,-1,-1,-1},
};

/*
struct Task {
    int type;
    int numberOfChecks;
    int checks[50];
    int difficulty;
    int reward;
};

struct Check {
    int type;
    char name[30];

    u_int8_t str;
    u_int8_t dex;
    u_int8_t con;
    u_int8_t inl;
    u_int8_t wis;
    u_int8_t cha;
}*/

#define CHECK_TRAP       1
#define CHECK_MONS       2
#define CHECK_PUZZLE     3
#define CHECK_SECRET     4
#define CHECK_MAZE       5
#define CHECK_MISC       6



#define NUMBER_OF_CHECKS 22
struct Check checks[NUMBER_OF_CHECKS] = {
    {CHECK_TRAP, "Trip Wire", 0, 45, 0, 0, 0, 0},
    {CHECK_TRAP, "Spike Pit", 0, 50, 0, 0, 0, 0},
    {CHECK_TRAP, "Falling Cage", 0, 55, 0, 0, 0, 0},
    {CHECK_TRAP, "Dart Launcher", 0, 60, 0, 0, 0, 0},
    {CHECK_TRAP, "Trapdoor", 0, 70, 0, 0, 0, 0},
    {CHECK_TRAP, "Rolling Bolder", 0, 75, 0, 0, 0, 0},
    {CHECK_TRAP, "Swinging Blade", 0, 80, 0, 0, 0, 0},

    {CHECK_MONS, "Rat", 50, 0, 0, 0, 0, 0},
    {CHECK_MONS, "Goblin", 55, 0, 0, 0, 0, 0},
    {CHECK_MONS, "Bandit", 55, 0, 0, 0, 0, 0},
    {CHECK_MONS, "Troll", 60, 0, 0, 0, 0, 0},
    {CHECK_MONS, "Witch", 70, 0, 0, 0, 0, 0},
    {CHECK_MONS, "Necromancer", 75, 0, 0, 0, 0, 0},
    {CHECK_MONS, "Dragon", 80, 0, 0, 0, 0, 0},


    {CHECK_PUZZLE, "Combination Lock", 0, 0, 0, 50, 0, 0},
    {CHECK_PUZZLE, "Sokoban Room", 0, 0, 0, 60, 0, 0},
    {CHECK_PUZZLE, "Riddle Sphinx", 0, 0, 0, 70, 0, 0},
    {CHECK_PUZZLE, "Sundial Shadow", 0, 0, 0, 75, 0, 0},

    {CHECK_SECRET, "Hidden Door", 0, 0, 0, 0, 50, 0},
    {CHECK_SECRET, "Cryptic Key", 0, 0, 0, 0, 60, 0},
    {CHECK_SECRET, "Secret Passage", 0, 0, 0, 0, 70, 0},
    {CHECK_SECRET, "Invisable Button", 0, 0, 0, 0, 75, 0}
};

int getDifficulty(int array[], int size){
    int total = 0;
    for(int i = 0; i < size; i++){
        total+=checks[array[i]].str;
        total+=checks[array[i]].dex;
        total+=checks[array[i]].con;
        total+=checks[array[i]].inl;
        total+=checks[array[i]].wis;
        total+=checks[array[i]].cha;
    }
    total = round(total / (size * 10));
    return total;
}

struct Task genTask(int type, int difficulty){
    struct Task task;
    task.numberOfChecks = difficulty + (1 - myRand(2));
    if (task.numberOfChecks < 0) task.numberOfChecks = 0;

    int tempTaskTypes[10];
    copyArray(typeConvert[type], tempTaskTypes, 10, false);
    shuffleArray(tempTaskTypes, 10);
    int taskTypes[3];
    copyArray(tempTaskTypes, taskTypes, 3, true);
    printf("%i,%i,%i\n", taskTypes[0], taskTypes[1], taskTypes[2]);


    int tempTask;
    do{
        for (int i = 0; i < task.numberOfChecks; i++){
            do{
                tempTask = myRand(NUMBER_OF_CHECKS);
            }while ((isInIntArray(taskTypes, 3, checks[tempTask].type) == -1) /*&& (myRand(3) != 0)*/);
            task.checks[i] = tempTask;
        } 
    }while (getDifficulty(task.checks, task.numberOfChecks) != difficulty);

    return task;
}

void outPutTask(struct Task *curTask){
    for(int i = 0; i < curTask->numberOfChecks; i++){
        printf("Task:%s:%i\n", checks[curTask->checks[i]].name, checks[curTask->checks[i]].type);
    }
}

//https://www.desmos.com/calculator/vsatioqttz
bool individualCheck(int check, int character){
    if (check != 0){
        if(character - check > 0){
            printf("Chance:%f\n", ((4.7931*pow(character - check, 3.0/5.0)) + 50));
            return ((float)myRand(100) < ((4.7931*pow(character - check, 3.0/5.0)) + 50));
        } else {
            printf("Chance:%f\n", ((-4.7931*pow(check - character, 3.0/5.0)) + 50));
            return ((float)myRand(100) < ((-4.7931*pow(check - character, 3.0/5.0)) + 50));
        }
    }
    return true;
}

bool passCheck(struct Character* character, int checkId){
    return (individualCheck(checks[checkId].str, character->str) &&
            individualCheck(checks[checkId].dex, character->dex) &&
            individualCheck(checks[checkId].con, character->con) &&
            individualCheck(checks[checkId].inl, character->inl) &&
            individualCheck(checks[checkId].wis, character->wis) &&
            individualCheck(checks[checkId].cha, character->cha));
}

int runTask(struct Character characters[], int numberOfCharacters, struct Task* task){
    int failedChecks = 0;
    int passedCheck = false;
    for(int i = 0; i < task->numberOfChecks; i++){
        passedCheck = false;
        for(int j = 0; j < numberOfCharacters; j++){
            printf("Char Stats:\nstr:%i dex:%i con:%i inl:%i wis:%i cha:%i\n", characters[j].str, characters[j].dex, characters[j].con, characters[j].inl, characters[j].wis, characters[j].cha);
            printf("Check Stats:\nstr:%i dex:%i con:%i inl:%i wis:%i cha:%i\n", checks[task->checks[i]].str, checks[task->checks[i]].dex, checks[task->checks[i]].con, checks[task->checks[i]].inl, checks[task->checks[i]].wis, checks[task->checks[i]].cha);
            passedCheck = passCheck(&characters[j], task->checks[i]);
            printf(passedCheck?"pass\n\n":"fail\n\n");
            if (passedCheck) break;
        }
        if (!passedCheck) failedChecks++;
    }

    return failedChecks;
}