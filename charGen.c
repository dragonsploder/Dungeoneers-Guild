#include "common.h"


bool debug = false;
/* tokens
#they# : he or she
#their# : his or her
#them# : him or her
#gender# : man or woman
#age# : current arg
#aan# : a or an
#rand3# : 1 - 3 
#rand10# : 2 - 10
#rand100# : 50 - 100
#size# : tiny to huge
#profession# : a list of professions
#region# : neighborhood to kingdom
#city# : random last name
#building# : house to castle
#object# : small nick-nack things
#enemy# : orc to ogre
#competitionActivity# : marathon to chess comp
#shapes# : round to square
#hairshape# : short to curly
#color# : red to blue
#hight# : short to tall
#emotion# : calm to crazy
*/

#define NUMBER_OF_DESCRIPTIONS 13
char descriptions[NUMBER_OF_DESCRIPTIONS][100] = {
    "#they# has #hairshape# #color# hair.",
    "#they# has #size# #color# eyes.",
    "#they# has many #size# scars.",
    //"#they# is missing #rand10# toes.",
    //"#they# is missing #rand10# fingers.",
    "#they# is very #hight#.",
    "#they# has #length# legs.",
    "#they# has #length# arms.",
    "#they# has #size# ears.",
    "#they# has a #shapes# sized head.",
    "#they# has #size# eyebrows.",
    "#they# has #color#ish skin.",
    "#they# has #shapes# finger and toe nails.",
    "#they# has #size# mouth.",
    "#they# has a #emotion# look in #their# eyes."
};

#define NUMBER_OF_EVENTS 40
#define NUMBER_OF_BIRTH_EVENTS 5
struct Event events[NUMBER_OF_EVENTS] = {
    {"#they# grew up an orphan.", 2, 10, 0, 5, -10, 0, -5, "None"},
    {"#they# was born to a wealthy family.", 1, -10, 5, -10, 5, 0, 10, "None"},
    {"#their# father was #aan# #profession#.", 2, 5, 5, -5, 5, -5, -5, "None"},
    {"#their# were born to #emotion# parents.", 3, -1, 1, -1, 1, -1, 1, "None"},
    {"#their# grew up the youngest of #rand10# siblings.", 3, 1, -1, 1, -1, 1, -1, "None"},
    {"At the age of #age#, #they# won #their# #region#'s arm wrestling competition.", 3, 15, 0, 5, 0, 0, 0, " the Arm Wrestler"},
    {"#they# was banished from #their# #region# after killing a sacride #animal#.", 2, 0, 0, -10, 0, 0, 0, "None"},
    {"#they# has #aan# #size# scar on #their# face from being attacked by #aan# #enemy#.", 1, 5, 0, -5, 0, 0, 0, "None"},
    {"#they# was pivotal in the founding of a #size# #building# in the #region# of #city#.", 3, 0, 0, 0, 10, 0, 0, "None"},
    {"#they# is good at building #object#s.", 2, 0, 10, 0, 0, 0, 0, "None"},
    {"#they# is known for loseing a staring contest with #aan# #animal#.", 3, 0, 0, -5, 0, 0, 0, " the Blinking"},
    {"#they# is known as the most beautiful #gender# in the #region# of #city#.", 3, 0, 0, 0, 0, 0, 15, " the Beautiful"},
    {"#they# is known as the strongest #gender# in the #region# of #city#.", 3, 15, 0, 0, 0, 0, 0, " the Strong"},
    {"#they# is known as the smartest #gender# in the #region# of #city#.", 3, 0, 0, 0, 15, 0, 0, " the intelligent"},
    {"#they# always wanted a #animal#, but #they# doesn't think #they# could take care of it.", 1, 0, -2, -2, -2, 0, 0, "None"},
    {"#they# has participated in #rand100# #competitionActivity#s, and has won #rand10# of them.", 1, 0, -2, -2, -2, 0, 0, "None"},
    {"#they# owns #rand100# #animal#s.", 1, 5, 0, 5, 0, 0, 0, "None"},
    {"#they# once meditated for #rand10# years.", 4, 0, 0, 0, 0, 10, 0, " the Wise"},
    {"#they# lives in a #size# #building#.", 5, -1, -1, -1, -1, -1, -1, "None"},
    {"#they# has slain over #rand100# #enemy#s.", 3, 5, 0, 5, 0, 0, 0, " the Slayer"},
    {"#they# has read #rand100# books about #object#s.", 2, 0, 0, 0, 10, 0, 0, "None"},
    {"#they# wanted to be a #profession#, but was too stupid.", 2, 0, 0, 0, -15, 0, 0, "None"},
    {"#they# likes to go to #city#'s #building#.", 2, 0, 0, 5, 0, 0, 0, "None"},
    {"#they# wants to burn #city#'s #building#.", 2, 0, 0, 0, 0, -5, 0, "None"},
    {"When #they# was only #age#, #they# kicked #aan# #enemy#. It ended badly.", 3, 0, 0, 0, 0, -10, 0, " the Stupid"},
    {"#they# pets #their# #animal# #rand10# times a day, every day.", 3, 0, 0, 0, 0, 5, 0, "None"},
    {"#they# can currently only lift a maximum of #rand10# #object#s.", 3, -15, -2, 0, 0, 0, 0, "None"},
    {"#they# believes that experience is #rand10# times more important than strength.", 2, -15, 0, 0, 0, 5, 0, "None"},
    {"#they# has the face of an #animal#.", 3, 0, 0, 0, 0, 0, -5, "None"},
    {"At the age of #age#, #they# chained #them#self to #their# favorite #building# in protest.", 3, 0, 0, 10, -5, 0, 0, "None"},
    {"#they# has often messed up the setup of the #region# of #city#'s #competitionActivity#.", 2, 0, -5, 0, 0, 0, 0, "None"},
    {"#they# has trouble using #object#s.", 3, -5, -5, 0, -5, 0, 0, "None"},
    {"#they# doesn't like mirrors.", 0, 0, 0, 0, 0, 0, -5, "None"},
    {"#their# #region#'s #profession# took pity on #them# when #they# was #age#.", 2, -5, -3, 0, -5, 0, -4, "None"},
    {"#they# does more sit-downs then sit-ups.", 4, -10, 0, 0, 0, 0, 0, "None"},
    {"#they# goes on a jog every #time#.", 1, 1, 0, 5, 0, 0, 0, "None"},
    {"#they# finally understood gravity at the age of #age#.", 3, 0, 0, 0, -5, 1, 0, "None"},
    {"#they# fought in a #length# war for the #size# #region# of #city#.", 2, 0, 0, 10, 0, 0, 0, " the War Torn"},
    {"#they# discovered an ancient #enemy#'s lair full of scrolls.", 1, 0, 0, 0, 0, 5, 0, "None"},
    {"#they# created a well known #color# beverage in #their# #region#", 3, 0, 0, 0, 0, -5, 0, "None"}
};

#define ALL_TOKEN_LISTS_SIZE 15
struct TokenList allTokenLists[ALL_TOKEN_LISTS_SIZE] = {
    {"#object#", 10, {
        "key",
        "chair",
        "table",
        "fork",
        "mirror",
        "plate",
        "mug",
        "marble",
        "sundial",
        "candle"
        }
    },
    {"#building#", 6, {
        "house",
        "library",
        "church",
        "theater",
        "castle",
        "inn"
        }
    },
    {"#size#", 4, {
        "tiny",
        "little",
        "big",
        "huge"
        }
    },
    {"#length#", 4, {
        "tiny",
        "short",
        "long",
        "very drawn-out"
        }
    },
    {"#enemy#", 10, {
        "goblin",
        "orc",
        "ogre",
        "troll",
        "bandit",
        "dragon",
        "witch",
        "necromancer",
        "kobold",
        "rat"
        }
    },
    {"#region#", 6, {
        "household",
        "neighborhood",
        "village",
        "town",
        "city",
        "kingdom"
        }
    },
    {"#profession#", 6, {
        "blacksmith",
        "carpinter",
        "merchant",
        "fishermen",
        "musician",
        "shoemaker"
        }
    },
    {"#animal#", 9, {
        "cat",
        "dog",
        "fish",
        "cow",
        "warthog",
        "goat",
        "pig",
        "horse",
        "parrot"
        }
    },
    {"#competitionActivity#", 8, {
        "marathon",
        "chess competition",
        "swiming contest",
        "dance contest",
        "smelliest sock contest",
        "sword fight competition",
        "fashion competition",
        "lumpiest head contest"
        }
    },
    {"#time#", 5, {
        "morning",
        "midday",
        "afternoon",
        "evening",
        "night",
        }
    },
    {"#hairshape#", 7, {
        "very little",
        "short",
        "medium length",
        "long",
        "waist length",
        "wavey",
        "curly"
        }
    },
    {"#color#", 8, {
        "red",
        "orange",
        "yellow",
        "green",
        "blue",
        "purple",
        "brown",
        "white",
        "black"
        }
    },
    {"#hight#", 4, {
        "small",
        "short",
        "tall",
        "big"
        }
    },
    {"#shapes#", 4, {
        "round",
        "oval",
        "square",
        "triangle"
        }
    },
    {"#emotion#", 8, {
        "calm",
        "tired",
        "hopefull",
        "sad",
        "curious",
        "happy",
        "vengefull",
        "crazy"
        }
    }
};

int myRand(int i){
    if (i == 0) return 0;
    return rand() % i;
}

struct Character genEmptyCharacter(){
    return (struct Character) {"Nameless", "Smith", " the Untitled", 0, 0, 50, 50, 50, 50, 50, 50, "They are bland.", "They have done nothing."};
}

void outPutCharacter(struct Character *curChar){
    printf("%s %s%s\n", curChar->name, curChar->lastName, (strncmp(curChar->title, " the Untitled", 13) == 0 ? "" : curChar->title));
    printf("Age %i\n", curChar->age);
    printf(curChar->gender ? "Female\n" : "Male\n");
    printf("\n");
    printf("Strength: %i\n", curChar->str);
    printf("Dexterity: %i\n", curChar->dex);
    printf("Constitution: %i\n", curChar->con);
    printf("intelligence: %i\n", curChar->inl);
    printf("Wisdom: %i\n", curChar->wis);
    printf("Charisma: %i\n", curChar->cha);
    printf("\n");
    printf("%s\n", curChar->appearance);
    printf("\n");
    printf("%s\n", curChar->background);
    printf("\n");
}

// http://arns.freeservers.com/workshop38.html
void genRandomName(char name[10], bool isSurname, bool gender){
    char vowels[] = "aaaeeeiiou";
    int vowelsLen = 10;
    char consonants[] = "bbbcdddffgghjkllmmmnnnppqrrssstttvwxyz";
    int consonantsLen = 38;

    name[0] = '\0';

    if (myRand(2) == 0){
        strncat(name, &consonants[myRand(consonantsLen)], 1);
    }

    int nameLen = myRand(3) + 1;

    for (int i = 0; i < nameLen; i++){
        strncat(name, &vowels[myRand(vowelsLen)], 1);
        strncat(name, &consonants[myRand(consonantsLen)], 1);
    }

    char maleGenderEnding[] = "us";
    char femaleGenderEnding[] = "a";

    if (!isSurname){
        strcat(name, gender ? femaleGenderEnding : maleGenderEnding);
    }

    name[0] = toupper(name[0]);
}

int getStringLength(char string[]){
    int len = 0;
    while (string[len] != '\0') len++;
    return len;
}

int isInString(char string[], char check[]){
    int stringLength = getStringLength(string);
    int checkLength = getStringLength(check);

    for (int i = 0; i < (stringLength - checkLength); i++){
        if (strncmp(&string[i], check, checkLength) == 0){
            return i;
        }
    }

    return -1;
}

void sliceIncertString(char expression[100], char incert[], int location, int replacmentLen){
    char oldExpression[100];
    strcpy(oldExpression, expression);
    expression[location] = '\0';
    strcat(expression, incert);
    strcat(expression, &oldExpression[location + replacmentLen]);
}

void evalExpression(char expression[], char destination[], struct Character *curChar){
    int location;
    do {
        location = isInString(expression, "#name#");
        if (location != -1){
            sliceIncertString(expression, curChar->name, location, 6);
        } 
    } while (location != -1);

    do {
        location = isInString(expression, "#age#");
        if (location != -1){
            char temp[3];
            sprintf(temp, "%i", curChar->age);
            sliceIncertString(expression, temp, location, 5);
        }
    } while (location != -1);

    do {
        location = isInString(expression, "#they#");
        if (location != -1){
            sliceIncertString(expression, curChar->gender ? "she" : "he", location, 6);
        }
    } while (location != -1);

    do {
        location = isInString(expression, "#their#");
        if (location != -1){
            sliceIncertString(expression, curChar->gender ? "her" : "his", location, 7);
        }
    } while (location != -1);

    do {
        location = isInString(expression, "#them#");
        if (location != -1){
            sliceIncertString(expression, curChar->gender ? "her" : "him", location, 6);
        }
    } while (location != -1);

    do {
        location = isInString(expression, "#gender#");
        if (location != -1){
            sliceIncertString(expression, curChar->gender ? "woman" : "man", location, 8);
        }
    } while (location != -1);

    do {
        location = isInString(expression, "#rand3#");
        if (location != -1){
            char temp[3];
            sprintf(temp, "%i", myRand(3) + 1); 
            sliceIncertString(expression, temp, location, 7);
        }
    } while (location != -1);

    do {
        
        location = isInString(expression, "#rand10#");
        if (location != -1){
            char temp[3];
            sprintf(temp, "%i", myRand(9) + 2); 
            sliceIncertString(expression, temp, location, 8);
        }
    } while (location != -1);

    do {
        location = isInString(expression, "#rand100#");
        if (location != -1){
            char temp[4];
            sprintf(temp, "%i", myRand(51) + 50); 
            sliceIncertString(expression, temp, location, 9);
        }
    } while (location != -1);

    do {
        location = isInString(expression, "#city#");
        if (location != -1){
            char temp[20];
            genRandomName(temp, true, 0);
            sliceIncertString(expression, temp, location, 6);
        }
    } while (location != -1);

    // Lists
    for (int i = 0; i < ALL_TOKEN_LISTS_SIZE; i++){
        do {
            location = isInString(expression, allTokenLists[i].replacment);
            if (location != -1){
                int token = myRand(allTokenLists[i].numberOfTokens);
                char temp[30];
                strcpy(temp, allTokenLists[i].tokens[token]);
                sliceIncertString(expression, temp, location, strlen(allTokenLists[i].replacment));
            }
        } while (location != -1);
    }

    // must be last
    do {
        location = isInString(expression, "#aan#");
        if (location != -1){
            char temp[20];
            char testChar = expression[location + 5 + 1];
            if (testChar == 'a' || testChar == 'i' || testChar == 'o' || testChar == 'u' || testChar == 'y'){
                strcpy(temp, "an");
            } else {
                strcpy(temp, "a");
            }
            sliceIncertString(expression, temp, location, 5);
        }
    } while (location != -1);

    strcpy(destination, expression);
    destination[0] = toupper(destination[0]);
}


void shuffleArray(int array[], int size){
    int temp;
    int randLocation;
    for (int i = 0; i < size; i++){
        randLocation = myRand(size);
        temp = array[i];
        array[i] = array[randLocation];
        array[randLocation] = temp;
    }
}

void genApperance(struct Character *curChar){      
    char temp[100];
    char expression[100];
    int descriptionNumber;
    int numberOfDiscriptions = 3 + ((rand() % 4));

    if (numberOfDiscriptions > NUMBER_OF_DESCRIPTIONS){
        numberOfDiscriptions = NUMBER_OF_DESCRIPTIONS;
    }

    int discriptionsOrder[numberOfDiscriptions];
    for (int i = 0; i < numberOfDiscriptions; i++){
        discriptionsOrder[i] = i;
    }

    shuffleArray(discriptionsOrder, numberOfDiscriptions);
    
    curChar->appearance[0] = '\0';

    for (int i = 0; i < numberOfDiscriptions; i++){
        descriptionNumber = discriptionsOrder[i];

        strcpy(expression, descriptions[descriptionNumber]);
        evalExpression(expression, temp, curChar);
        strcat(curChar->appearance, temp);
        strcat(curChar->appearance, " ");

        if (debug){
            outPutCharacter(curChar);
            printf("----------\n");
        }
    }
}

void genHistory(struct Character *curChar){
    int numberOfEvents = 7 + ((rand() % 4) - 2);
    curChar->background[0] = '\0';

    char temp[100];
    char expression[100];
    int eventNumber;
    int tolerance;
    int eventsOrder[numberOfEvents];
    if (!REPEAT_EVENTS){
        for (int i = 0; i < (numberOfEvents - NUMBER_OF_BIRTH_EVENTS); i++){
            eventsOrder[i] = (i + NUMBER_OF_BIRTH_EVENTS);
        }
        shuffleArray(eventsOrder, numberOfEvents);
        eventsOrder[0] = myRand(NUMBER_OF_BIRTH_EVENTS);
        curChar->age = BASE_START_AGE + myRand(4) - 2;
    }


    for (int i = 0; i < numberOfEvents; i++){
        if (REPEAT_EVENTS){
            eventNumber = eventsOrder[i];
            curChar->age += myRand(6);
        } else {
            if (curChar->age == 0){
                eventNumber = myRand(NUMBER_OF_BIRTH_EVENTS);
                curChar->age = BASE_START_AGE + myRand(4) - 2;
            } else {
                eventNumber = myRand(NUMBER_OF_EVENTS - NUMBER_OF_BIRTH_EVENTS) + NUMBER_OF_BIRTH_EVENTS;
                curChar->age += myRand(6);
            }
        }

        strcpy(expression, events[eventNumber].sentence);
        evalExpression(expression, temp, curChar);
        strcat(curChar->background, temp);
        strcat(curChar->background, " ");

        tolerance = events[eventNumber].tolerance;

        if (events[eventNumber].str != 0) curChar->str += events[eventNumber].str + (myRand(tolerance * 2) - tolerance);
        if (curChar->str > 99) curChar->str = 99;
        if (events[eventNumber].dex != 0) curChar->dex += events[eventNumber].dex + (myRand(tolerance * 2) - tolerance);
        if (curChar->dex > 99) curChar->dex = 99;
        if (events[eventNumber].con != 0) curChar->con += events[eventNumber].con + (myRand(tolerance * 2) - tolerance);
        if (curChar->con > 99) curChar->con = 99;
        if (events[eventNumber].inl != 0) curChar->inl += events[eventNumber].inl + (myRand(tolerance * 2) - tolerance);
        if (curChar->inl > 99) curChar->inl = 99;
        if (events[eventNumber].wis != 0) curChar->wis += events[eventNumber].wis + (myRand(tolerance * 2) - tolerance);
        if (curChar->wis > 99) curChar->wis = 99;
        if (events[eventNumber].cha != 0) curChar->cha += events[eventNumber].cha + (myRand(tolerance * 2) - tolerance);
        if (curChar->cha > 99) curChar->cha = 99;

        if (strcmp(events[eventNumber].title, "None") != 0 && myRand(5) == 0){
            strcpy(curChar->title, events[eventNumber].title);
        }

        if (debug){
            outPutCharacter(curChar);
            printf("----------\n");
        }
    }
}

void statsCheck(){
    int8_t str = 0;
    int8_t dex = 0;
    int8_t con = 0;
    int8_t inl = 0;
    int8_t wis = 0;
    int8_t cha = 0; 
    for (int i = 0; i < NUMBER_OF_EVENTS; i++){
        str += events[i].str;
        dex += events[i].dex;
        con += events[i].con;
        inl += events[i].inl;
        wis += events[i].wis;
        cha += events[i].cha;
    }
    printf("str:%i dex:%i con:%i inl:%i wis:%i cha:%i\n", str, dex, con, inl, wis, cha);
}

void main(int argc, char *argv[]){
    long seed = time(NULL);
    for (int i = 0; i < argc; i++){
        if (strcmp(argv[i], "-s") == 0){
            seed = atol(argv[i + 1]);
        } else if (strcmp(argv[i], "-d") == 0){
            debug = true;
        } else if (strcmp(argv[i], "-c") == 0){
            statsCheck();
            exit(0);
        }
    }

    srand(seed);
    printf("Seed:%i\n\n", seed);

    struct Character test = genEmptyCharacter();

    test.gender = rand() % 2;
    genRandomName(test.name, false, test.gender);
    genRandomName(test.lastName, true, test.gender);
    genApperance(&test);
    genHistory(&test);
    outPutCharacter(&test);
}