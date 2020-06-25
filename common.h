#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h> 

extern bool debug;

// charGen.c
struct Character {
    char name[10];
    char lastName[10];
    char title[20];
    u_int8_t age;
    bool gender;

    u_int8_t str;
    u_int8_t dex;
    u_int8_t con;
    u_int8_t inl;
    u_int8_t wis;
    u_int8_t cha;

    char appearance[500];
    char background[2000];
};

struct CharacterEvent {
    char sentence[100];
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
    u_int8_t str;
    u_int8_t dex;
    u_int8_t con;
    u_int8_t inl;
    u_int8_t wis;
    u_int8_t cha;

    int difficulty;
}



// charGen.c
void genApperance(struct Character *curChar);
struct Character genEmptyCharacter();
void genHistory(struct Character *curChar);
void genRandomName(char name[10], bool isSurname, bool gender);
void outPutCharacter(struct Character *curChar);
void charStatsCheck();


// misc.c
int getStringLength(char string[]);
int isInString(char string[], char check[]);
int myRand(int i);
void shuffleArray(int array[], int size);
void sliceIncertString(char expression[100], char incert[], int location, int replacmentLen);