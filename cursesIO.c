#include "common.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define MENU_SCREEN_FIRST_PARTITION 21
#define MENU_SCREEN_SECOND_PARTITION 40

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

void initColor(){
    // Alow the use of color
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

// Set up terminal with ncurses library
void initCurses(){
    // Init curses
    initscr(); 
    // Disable buffering and get one character-at-a-time input
    cbreak(); 
    // Get Special keys
    keypad(stdscr, TRUE);
    // Suppress echoing of typed keys
    noecho();
    // Hide cursor
    curs_set(0);
    initColor();

    //nodelay(stdscr, true);
}

void stopCurses(){
    // Gracefully stop curses
    endwin();
}

wchar_t myGetch(){
    return getch();
}

void printHorizontalLine(int y, int start, int stop, char* toPrint){
    for (int i = start; i <= stop; i++){
        mvprintw(y, i, toPrint);
    }
}

void printVerticalLine(int x, int start, int stop, char* toPrint){
    for (int i = start; i <= stop; i++){
        mvprintw(i, x, toPrint);
    }
}

void printBox(int y, int x, int stopY, int stopX, char* toPrint){
    for (int i = y; i < stopY; i++){
        printHorizontalLine(i, x, stopX, toPrint);
    }
}

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

void printOverview(struct Character* curChar, int y, int x){
    mvprintw(y,     x, "Overview:");
    mvprintw(y + 2, x, "Fullname: %s %s%s", curChar->name, curChar->lastName, (strncmp(curChar->title, " the Untitled", 13) == 0 ? "" : curChar->title));
    mvprintw(y + 3, x, "Age %i", curChar->age);
    mvprintw(y + 4, x, "Gender: %s", curChar->gender ? "Female" : "Male");
    mvprintw(y + 5, x, "Lucky Number: %i", curChar->luckyNumber);

}

void printStats(struct Character* curChar, int y, int x){
    mvprintw(y,     x, "Current stats:");
    mvprintw(y + 2, x, "Strength: %i", curChar->str);
    mvprintw(y + 3, x, "Dexterity: %i", curChar->dex);
    mvprintw(y + 4, x, "Constitution: %i", curChar->con);
    mvprintw(y + 5, x, "Intelligence: %i", curChar->inl);
    mvprintw(y + 6, x, "Wisdom: %i", curChar->wis);
    mvprintw(y + 7, x, "Charisma: %i", curChar->cha);
}

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

void printAppearance(struct Character* curChar, int y, int x, int lineLength){
    mvprintw(y, x, "Appearance:");
    printFormatedBlockOfText(curChar->appearance, y + 2, x, lineLength);
}

void printHistory(struct Character* curChar, int y, int x, int lineLength){
    mvprintw(y, x, "History:");
    printFormatedBlockOfText(curChar->background, y + 2, x, lineLength);
}

void charMenu(struct Character* characters, int numberOfCharacters){
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
        if (input == KEY_RIGHT){
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
        //printf("%i\n", input);
    } while (input != 'q');

}