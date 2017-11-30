/*
    EQUIPE:
    Adriano de Oliveira Leal Rocha
    Hélio Rocha Vieira de Couto Júnior
    Myllena Caetano de Oliveira
*/

#include "lib/yolib.h"
#include "lib/yostring.h"
#include <stdio.h>
#include <string.h>
#define MAX 10000

/* Estrutura para guardar uma palavra encontrada no texto e a sua respectiva quantidade */
typedef struct {
    char valor[50];
    int quant;
} Palavra;

/* Estrutura para guardar a lista de palavras do texto */
typedef struct {
    Palavra palavras[MAX+1];
    int length;
} WordList;

void countWords(const char *filename, WordList *list); // Função para abrir o arquivo de texto e guardar todas as suas palavras na lista
int searchWordInList(char *word, WordList *list); // Verifica se uma palavra já está incluída na lista de palavras
int isStopWord(char *word); // Verifica se uma palavra está na lista de stopwords para o idioma especificado
void sortWords(WordList *list); // Função para ordenar a lista de palavras em ordem decrescente com relação à quantidade de repetições no texto
void showImportantWords(WordList *list, int n); // Exibe a lista das n palavras que mais aparecem no texto

void main() {
    char *filePath;
    int quantPalavras;

    WordList *lista = malloc(sizeof(WordList));
    lista->length = 0;

    filePath = input("Informe o caminho para o arquivo de texto:");
    quantPalavras = toint(input("Informe o tamanho do resumo (a quantidade de palavras):"));

    countWords(filePath, lista);
    sortWords(lista);
    showImportantWords(lista, quantPalavras);
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
        if (isOnList > 0 && !isStopWord(aux)) {
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

int isStopWord(char *word) {
    FILE *stopwords = fopen("stopwords.txt", "r");
    if (stopwords == NULL) {
        printf("Erro. Arquivo de stopwords inexistente.\n");
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

void showImportantWords(WordList *list, int n) {
    if (list->length < n) n = list->length;
    for (int i = 1; i <= n; i++) {
        printf("%-20s %2d\n", list->palavras[i].valor, list->palavras[i].quant);
    }
}
