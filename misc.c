#include "common.h"

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

int myRand(int i){
    if (i == 0) return 0;
    return rand() % i;
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

void sliceIncertString(char expression[100], char incert[], int location, int replacmentLen){
    char oldExpression[100];
    strcpy(oldExpression, expression);
    expression[location] = '\0';
    strcat(expression, incert);
    strcat(expression, &oldExpression[location + replacmentLen]);
}