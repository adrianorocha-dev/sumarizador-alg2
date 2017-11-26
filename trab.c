#include "lib/yolib.h"
#include "lib/yostring.h"
#include <stdio.h>
#include <string.h>
#define MAX 1000

typedef struct palavra {
    char valor[50];
    int quant;
} Palavra;

typedef struct wordList {
    Palavra palavras[MAX+1];
    int length;
} WordList;

void countWords(const char *filename, WordList *list);
int searchWordInList(char *word, WordList *list);
int isStopWord(char *word, char *language);
void sortWords(WordList *list);
void showImportantWords(WordList *list, int size);

void main() {
    int op;
    char *filePath;
    int quantPalavras;

    WordList *lista = malloc(sizeof(WordList));
    lista->length = 0;

    do {
        op = toint(input("Informe o tipo de conteúdo (1-website, 2-arquivo de texto puro):"));
        if (op < 1 || op > 2) printf("Opção Inválida");
    } while (op < 1 || op > 2);

    filePath = input("Informe o caminho para o website ou arquivo de texto:");
    quantPalavras = toint(input("Informe o tamanho do resumo (a quantidade de palavras):"));

    countWords(filePath, lista);
    sortWords(lista);
    showImportantWords(lista, quantPalavras);

    /*for (int i = 1; i <= lista->length; i++) {
        printf("%-20s %d\n", lista->palavras[i].valor, lista->palavras[i].quant);
    }*/
}

void countWords(const char *filename, WordList * list) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }

    int i = 0;
    char aux[50];
    while (fscanf(file, "%s ", aux) == 1) {
        removeSpecialChars(aux);
        int isOnList = searchWordInList(aux, list);
        if (isOnList > 0 && !isStopWord(aux, "pt-BR")) {
            list->palavras[isOnList].quant++;
        } else {
            list->length++;
            strcpy(list->palavras[list->length].valor, aux);
            list->palavras[list->length].quant = 1;
        }
    }
    fclose(file);
}

int searchWordInList(char *word, WordList *list) {
    Palavra aux;
    strcpy(aux.valor, word);
    aux.quant = 0;
    list->palavras[0] = aux;

    int i;
    for (i = list->length; strcmp(strtoup(list->palavras[i].valor), strtoup(word)) != 0; i--);

    return i;
}

int isStopWord(char *word, char *language) {
    FILE *stopwords;

    if (strcmp(language, "en") == 0) {
        stopwords = fopen("stopwords_en.txt", "r");
    } else if (strcmp(language, "pt-BR") == 0) {
        stopwords = fopen("stopwords_pt-BR.txt", "r");
    }


    if (stopwords == NULL) {
        printf("Erro. Arquivo de stopwords inexistente para o idioma selecionado.\n");
        exit(1);
    }

    int i = 0;
    char aux[50];
    while (fscanf(stopwords, "%s ", aux) == 1) {
        if (strcmp(strtoup(word), strtoup(aux)) == 0) {
            return 1;
        }
    }
    fclose(stopwords);
    return 0;
}

void sortWords(WordList *list) {
    int j;
    Palavra aux;

    for (int i = 2; i <= list->length; i++) {
        aux = list->palavras[i];
        j = i-1;

        while ((j >= 1) && (aux.quant > list->palavras[j].quant)) {
            list->palavras[j+1] = list->palavras[j];
            j--;
        }

        list->palavras[j+1] = aux;
    }
}

void showImportantWords(WordList *list, int size) {
    for (int i = 1; i <= size; i++) {
        printf("%-20s %02d\n", list->palavras[i].valor, list->palavras[i].quant);
    }
}
