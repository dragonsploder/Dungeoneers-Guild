#include "common.h"

/* Screen laylout def */
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24


#define MENU_SCREEN_FIRST_PARTITION 21
#define MENU_SCREEN_SECOND_PARTITION 34

// Uncomment if using VS code cmd terminal
/*
#if defined(_WIN32)
    #undef  KEY_DOWN
    #define KEY_DOWN      456
    #undef  KEY_UP
    #define KEY_UP        450
    #undef  KEY_LEFT
    #define KEY_LEFT      452
    #undef  KEY_RIGHT
    #define KEY_RIGHT     454
#endif
*/

/* Curses init color */
void initColor(){
    /* Alow the use of color */
    use_default_colors();
    start_color();
    init_pair(COLOR_BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
}

/* Set up terminal with curses library */
void initCurses(){
    /* Init curses */
    initscr(); 
    /* Disable buffering and get one character-at-a-time input */
    cbreak(); 
    /* Get Special keys */
    keypad(stdscr, TRUE);
    /* Suppress echoing of typed keys */
    noecho();
    /* Hide cursor */
    curs_set(0);

    initColor();

    /* nodelay(stdscr, true); */
}

/* Stop Curses */
void stopCurses(){
    // Gracefully stop curses
    endwin();
}

/* Incase I need to do some input flitering at somepoint */
wchar_t myGetch(){
    return getch();
}

/* Clear the scren */
void clearScreen(){
    erase();
}

/* Print a horizontal line at y starting at start and stoping at stop */
void printHorizontalLine(int y, int start, int stop, char* toPrint){
    for (int i = start; i <= stop; i++){
        mvprintw(y, i, toPrint);
    }
}

/* Print a vertical line at x starting at start and stoping at stop */
void printVerticalLine(int x, int start, int stop, char* toPrint){
    for (int i = start; i <= stop; i++){
        mvprintw(i, x, toPrint);
    }
}

/* Print a filled in box at (y,x) to (stopY, stopX) */
void printBox(int y, int x, int stopY, int stopX, char* toPrint){
    for (int i = y; i < stopY; i++){
        printHorizontalLine(i, x, stopX, toPrint);
    }
}

/* Print nice boarder around screen */
void printBoarder(){
    printVerticalLine(0, 0, SCREEN_HEIGHT, "|");
    printVerticalLine(SCREEN_WIDTH, 0, SCREEN_HEIGHT, "|");

    printHorizontalLine(0, 0, SCREEN_WIDTH, "-");
    printHorizontalLine(SCREEN_HEIGHT, 0, SCREEN_WIDTH, "-");

    mvprintw(0, 0, "+");
    mvprintw(0, SCREEN_WIDTH, "+");
    mvprintw(SCREEN_HEIGHT, 0, "+");
    mvprintw(SCREEN_HEIGHT, SCREEN_WIDTH, "+");
}

/* Print overview of a character */
void printOverview(struct Character* curChar, int y, int x){
    mvprintw(y,     x, "Overview:");
    mvprintw(y + 2, x, "Fullname: %s %s%s", curChar->name, curChar->lastName, (strncmp(curChar->title, " the Untitled", 13) == 0 ? "" : curChar->title));
    mvprintw(y + 3, x, "Age %i", curChar->age);
    mvprintw(y + 4, x, "Gender: %s", curChar->gender ? "Female" : "Male");
    mvprintw(y + 5, x, "Lucky Number: %i", curChar->luckyNumber);
}

/* Print stats of a character */
void printStats(struct Character* curChar, int y, int x){
    mvprintw(y,     x, "Current stats:");
    mvprintw(y + 2, x, "Strength: %i", curChar->str);
    mvprintw(y + 3, x, "Dexterity: %i", curChar->dex);
    mvprintw(y + 4, x, "Constitution: %i", curChar->con);
    mvprintw(y + 5, x, "Intelligence: %i", curChar->inl);
    mvprintw(y + 6, x, "Wisdom: %i", curChar->wis);
    mvprintw(y + 7, x, "Charisma: %i", curChar->cha);
}

/* Print a formated block of text at (y,x) */
void printFormatedBlockOfText(char* paragraph, int y, int x, int lineLength){
    char formatedHistory[10000];
    formatBlock(paragraph, formatedHistory, lineLength);
    int currentLine = 0;
    for(int i = 0; i < getStringLength(formatedHistory); i++){
        if(i % lineLength == 0 && i != 0){
            currentLine++;
        }
        mvaddch(y + currentLine, x + (i - (currentLine * lineLength)), formatedHistory[i]);
    }
}

/* Print appearance of a character */
void printAppearance(struct Character* curChar, int y, int x, int lineLength){
    mvprintw(y, x, "Appearance:");
    printFormatedBlockOfText(curChar->appearance, y + 2, x, lineLength);
}

/* Print history of a character */
void printHistory(struct Character* curChar, int y, int x, int lineLength){
    mvprintw(y, x, "History:");
    printFormatedBlockOfText(curChar->background, y + 2, x, lineLength);
}

/* A menu for viewing characters */
int charMenu(struct Character* characters, int numberOfCharacters){
    clearScreen();
    printBoarder();

    printVerticalLine(MENU_SCREEN_FIRST_PARTITION, 1, SCREEN_HEIGHT - 1, "|");
    printVerticalLine(MENU_SCREEN_SECOND_PARTITION, 1, SCREEN_HEIGHT - 1, "|");

    int numberOfViewableCharInfo = 4;
    char viewableCharInfo[10][20] = {
        "Overview",
        "Stats",
        "Appearance",
        "History"
    };

    int currentCharSelected = 0;
    int currentViewableCharInfoSelected = 0;

    int currentSection = 0;

    int currentTopChar = 0;

    wchar_t input = 0;

    do {
        if (input == KEY_ENTER){
            return currentCharSelected;
        } else if (input == KEY_RIGHT){
            currentViewableCharInfoSelected = 0;
            if (currentSection == 1){
                currentSection = 0;
            } else {
                currentSection++;
            }
        } else if (input == KEY_LEFT){
            currentViewableCharInfoSelected = 0;
            if (currentSection == 0){
                currentSection = 1;
            } else {
                currentSection--;
            }
        } else {
            if(currentSection == 0){
                if (input == KEY_UP){
                    if (currentCharSelected == 0){
                        currentCharSelected = numberOfCharacters - 1;
                    } else {
                        currentCharSelected--;
                    }
                } else if (input == KEY_DOWN){
                    if (currentCharSelected == numberOfCharacters - 1){
                        currentCharSelected = 0;
                    } else {
                        currentCharSelected++;
                    }
                }
            } else if (currentSection == 1){
                if (input == KEY_UP){
                    if (currentViewableCharInfoSelected == 0){
                        currentViewableCharInfoSelected = numberOfViewableCharInfo - 1;
                    } else {
                        currentViewableCharInfoSelected--;
                    }
                } else if (input == KEY_DOWN){
                    if (currentViewableCharInfoSelected == numberOfViewableCharInfo - 1){
                        currentViewableCharInfoSelected = 0;
                    } else {
                        currentViewableCharInfoSelected++;
                    }
                }
            }
        }

        for (int i = 0; i < numberOfCharacters; i++){
            if (i == currentCharSelected){
                attron(A_STANDOUT);
            }
            mvprintw(1 + i, 1, "%s ", characters[i].name);
            mvprintw(1 + i, 2 + getStringLength(characters[i].name), "%s", characters[i].lastName);
            attrset(A_NORMAL);
        }

        for (int i = 0; i < numberOfViewableCharInfo; i++){
            if (i == currentViewableCharInfoSelected){
                if (currentSection == 1){
                    attron(A_STANDOUT);
                } else {
                    attron(A_BOLD);
                }
            }
            mvprintw(1 + i, MENU_SCREEN_FIRST_PARTITION + 1,  "%s", viewableCharInfo[i]);
            attrset(A_NORMAL);
        }

        printBox(1, MENU_SCREEN_SECOND_PARTITION + 1, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1, " ");
        if (currentViewableCharInfoSelected == 0){
            printOverview(&characters[currentCharSelected], 1, MENU_SCREEN_SECOND_PARTITION + 1);
        } else if (currentViewableCharInfoSelected == 1){
            printStats(&characters[currentCharSelected], 1, MENU_SCREEN_SECOND_PARTITION + 1);
        } else if (currentViewableCharInfoSelected == 2){
            printAppearance(&characters[currentCharSelected], 1, MENU_SCREEN_SECOND_PARTITION + 1, SCREEN_WIDTH - (MENU_SCREEN_SECOND_PARTITION + 1));
        } else if (currentViewableCharInfoSelected == 3){
            printHistory(&characters[currentCharSelected], 1, MENU_SCREEN_SECOND_PARTITION + 1, SCREEN_WIDTH - (MENU_SCREEN_SECOND_PARTITION + 1));
        }




        input = myGetch();
    } while (input != 'q');

    return -1;
}

void printIcon(int icon, int y, int x){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 20; j++){
            if(taskIcons[icon - 1][i][j] != ' '){
                mvaddch(y + i, x + j, taskIcons[icon - 1][i][j]);
            }
        }
    }
}

int taskPrep(struct Task task){
    clearScreen();
    printBoarder();

    printHorizontalLine((int) (SCREEN_HEIGHT / 3), 1, SCREEN_WIDTH -1, "-");

    printVerticalLine((int) (SCREEN_WIDTH / 3), ((int) (SCREEN_HEIGHT / 3)) + 1, SCREEN_HEIGHT - 1, "|");
    printVerticalLine(SCREEN_WIDTH - ((int) (SCREEN_WIDTH / 3)), ((int) (SCREEN_HEIGHT / 3)) + 1, SCREEN_HEIGHT - 1, "|");

    char temp[20];
    mvprintw(1, 1, task.description);

    mvprintw(3, 1, "Difficulty: ");
    sprintf(temp ,"%d", task.difficulty);
    mvprintw(3, 13, temp);

    mvprintw(4, 1, "Reward: ");
    sprintf(temp ,"%d", task.reward);
    mvprintw(4, 9, temp);

    for(int i = 0; i < 3; i++){
        printIcon(task.taskTypes[i], 1, (int) (SCREEN_WIDTH / 3) + 4);
    }



    return -1;
}