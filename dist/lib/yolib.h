/*
    Autor: Adriano Rocha
*/

#include <stdio.h>
#include <stdlib.h>

char * input(char *message); // imprime uma mensagem na tela e solicita a entrada do usuário, então é retornada a string digitada pelo usuário

int toint(char *charV); // converte uma string em inteiro
int tofloat(char *charV); // converte uma string em float

char * input(char *message) {
    char *temp = malloc(255);
    printf("%s ", message);
    scanf("%s", temp);
    return temp;
}

int toint(char *charV) {
    int r = atoi(charV);
    return r;
}

int tofloat(char *charV) {
    return atof(charV);
}
