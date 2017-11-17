#include <stdio.h>
#include <stdlib.h>

char * input(char *message);

int toint(char *charV);
int tofloat(char *charV);

void print(char *message, ...);
void printN(int n);

char * strformat(char *str, ...);

char * input(char *message) {
    char *temp = malloc(255);
    printf("%s ", message);
    scanf("%s", temp);
    return temp;
}

int toint(char *charV) {
    int r = atoi(charV);
    // if (r == 0) {
    //     for (int i = 0; charV[i] != '\0'; i++) {
    //         if (charV[i] != '0') {
    //             r = charV[0];
    //             break;
    //         }
    //     }
    // }
    return r;
}

int tofloat(char *charV) {
    return atof(charV);
}
