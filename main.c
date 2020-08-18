#include "common.h"

bool debug = false;

void genCharacter(){
    struct Character test = genEmptyCharacter();

    test.gender = rand() % 2;
    genRandomName(test.name, false, test.gender);
    genRandomName(test.lastName, true, test.gender);
    genApperance(&test);
    genHistory(&test);
    outPutCharacter(&test);
}

void genFullChar(struct Character* test){
    test->gender = rand() % 2;
    genRandomName(test->name, false, test->gender);
    genRandomName(test->lastName, true, test->gender);
    genApperance(test);
    genHistory(test);
}

void genNewTask(){
    struct Character test = genEmptyCharacter();
    genFullChar(&test);
    outPutCharacter(&test);

    struct Character test2 = genEmptyCharacter();
    genFullChar(&test2);
    outPutCharacter(&test2);

    struct Character test3 = genEmptyCharacter();
    genFullChar(&test3);
    outPutCharacter(&test3);

    struct Character characters[3] = {test, test2, test3};
    

    struct Task task = genTask(0, 6);
    //outPutTask(&task);
    printf("\n\n");
    printf("Task count: %i\n", runTask(&characters[0], 3, &task));
}

void main(int argc, char *argv[]){
    long seed = time(NULL);
    for (int i = 0; i < argc; i++){
        if (strcmp(argv[i], "-s") == 0){
            seed = atol(argv[i + 1]);
        } else if (strcmp(argv[i], "-d") == 0){
            debug = true;
        } else if (strcmp(argv[i], "-c") == 0){
            charStatsCheck();
            exit(0);
        }
    }

    srand(seed);
    printf("Seed:%i\n\n", seed);

    //genCharacter();
    genNewTask();
}