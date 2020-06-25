#include "common.h"

#define TASK_DUNGEON 1

/*
struct Task {
    int type;
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
}*/

#define CHECK_TRAP       1
#define CHECK_MONS       2
#define CHECK_PUZZLE     3
#define CHECK_SECRET     4
#define CHECK_MAZE       5
#define CHECK_MISC       6



#define NUMBER_OF_CHECKS
struct Check checks[50] = {
    {CHECK_TRAP, "Spike Pit", 0, 50, 0, 0, 0, 0},
    {CHECK_TRAP, "Dart Launcher", 0, 60, 0, 0, 0, 0},
    {CHECK_TRAP, "Trapdoor", 0, 70, 0, 0, 0, 0},

    {CHECK_MONS, "Rat", 50, 0, 0, 0, 0, 0},
    {CHECK_MONS, "Goblin", 60, 0, 0, 0, 0, 0},
    {CHECK_MONS, "Necromancer", 70, 0, 0, 0, 0, 0},

    {CHECK_PUZZLE, "Combination Lock", 0, 0, 0, 50, 0, 0},
    {CHECK_PUZZLE, "Sokoban Room", 0, 0, 0, 60, 0, 0},
    {CHECK_PUZZLE, "Riddle Sphinx", 0, 0, 0, 70, 0, 0},

    {CHECK_SECRET, "Hidden Door", 0, 0, 0, 0, 50, 0},
    {CHECK_SECRET, "Cryptic Key", 0, 0, 0, 0, 60, 0},
    {CHECK_SECRET, "Secret Passage", 0, 0, 0, 0, 70, 0},
}