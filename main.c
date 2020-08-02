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

void genNewTask(){
    struct Character test = genEmptyCharacter();

    test.gender = rand() % 2;
    genRandomName(test.name, false, test.gender);
    genRandomName(test.lastName, true, test.gender);
    genApperance(&test);
    genHistory(&test);

    struct Task task = genTask(0, 5);
    outPutTask(&task);
    printf("\n\n");
    printf("Task count: %i\n", runTask(&test, 1, &task));
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