#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h> 
#include <math.h>
#include <inttypes.h>

#if defined(_WIN32)
    #include <pdcurses/curses.h>
#else
    #include <ncurses.h>
#endif

extern bool debug;

// charGen.c
struct Character {
    char name[10];
    char lastName[10];
    char title[20];
    uint8_t age;
    bool gender;
    uint8_t luckyNumber;


    uint8_t str;
    uint8_t dex;
    uint8_t con;
    uint8_t inl;
    uint8_t wis;
    uint8_t cha;

    char appearance[500];
    char background[2000];
};

struct CharacterEvent {
    char sentence[500];
    int8_t tolerance;
    int8_t str;
    int8_t dex;
    int8_t con;
    int8_t inl;
    int8_t wis;
    int8_t cha;
    char title[50];
};

struct TokenList {
    char replacment[30];
    int numberOfTokens;
    char tokens[20][30];
};


// taskGen.c
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
    uint8_t str;
    uint8_t dex;
    uint8_t con;
    uint8_t inl;
    uint8_t wis;
    uint8_t cha;
};



// charGen.c
void genApperance(struct Character *curChar);
struct Character genEmptyCharacter();
void genHistory(struct Character *curChar);
void genRandomName(char name[10], bool isSurname, bool gender);
void outPutCharacter(struct Character *curChar);
void charStatsCheck();

// taskGen.c
struct Task genTask(int type, int difficulty);
void outPutTask(struct Task *curTask);
int runTask(struct Character characters[], int numberOfCharacters, struct Task* task);


// misc.c
void copyArray(int source[], int destination[], int size, bool skipNegativeOne);
int getStringLength(char string[]);
int isInIntArray(int array[], int size, int check);
int isInString(char string[], char check[]);
int myRand(int i);
void shuffleArray(int array[], int size);
void sliceIncertString(char expression[2000], char incert[], int location, int replacmentLen);
void formatBlock(char* oldParagraph, char* newParagraph, int lineLength);

// cursesIO.c
void initCurses();
void stopCurses();
void printBoarder();
void charMenu(struct Character* characters, int numberOfCharacters);