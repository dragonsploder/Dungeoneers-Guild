#pragma once

/* printf and rand stuff */
#include <stdlib.h>
#include <stdio.h>

/* uint8_t and stuff */
#include <stdint.h> 
#include <inttypes.h>

/* used to seed rand */
#include <time.h>

/* true and false */
#include <stdbool.h>

/* String manipulation */
#include <string.h>

/* Char manipulation */
#include <ctype.h> 

/* Usefall math functions like pow */
#include <math.h> 

/* curses (terminal manipulation) */
#if defined(_WIN32)
    #include <pdcurses/curses.h>
#else
    #include <ncurses.h>
#endif


extern bool debug; /* Controls lots of informational printfs */

#define NUMBER_OF_CHECK_TYPES 8


/* Holds information for characters */
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


/* Holds event data for a Character's background */
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

/* Holds replacements for Tokens like #buildings# */
struct TokenList {
    char replacment[30];
    int numberOfTokens;
    char tokens[20][30];
};

/* Holds data for tasks */
struct Task {
    int type;
    int taskTypes[3];
    int numberOfChecks;
    int checks[50];
    char description[50];
    int difficulty;
    int reward;
};

/* Holds possible checks which make up Tasks */
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



/* charGen.c */
void genApperance(struct Character *curChar);
struct Character genEmptyCharacter();
void genHistory(struct Character *curChar);
void genRandomName(char name[10], bool isSurname, bool gender);
void outPutCharacter(struct Character *curChar);
void charStatsCheck();

/* taskGen.c */
struct Task genTask(int type, int difficulty);
void outPutTask(struct Task *curTask);
int runTask(struct Character characters[], int numberOfCharacters, struct Task* task);


/* misc.c */
void copyArray(int source[], int destination[], int size, bool skipNegativeOne);
int getStringLength(char string[]);
int isInIntArray(int array[], int size, int check);
int isInString(char string[], char check[]);
int myRand(int i);
void shuffleArray(int array[], int size);
void sliceIncertString(char expression[2000], char incert[], int location, int replacmentLen);
void formatBlock(char* oldParagraph, char* newParagraph, int lineLength);

/* cursesIO.c */
void initCurses();
void stopCurses();
wchar_t myGetch();
int charMenu(struct Character* characters, int numberOfCharacters);
int taskPrep(struct Task task);

/* data.c */
extern char taskIcons[NUMBER_OF_CHECK_TYPES][7][22];