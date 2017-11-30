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

int CUSTO = 0;

void countWords(const char *filename, WordList *list); // Função para abrir o arquivo de texto e guardar todas as suas palavras na lista
int searchWordInList(char *word, WordList *list); // Verifica se uma palavra já está incluída na lista de palavras
int isStopWord(char *word, char *language); // Verifica se uma palavra está na lista de stopwords para o idioma especificado
void sortWords(WordList *list); // Função para ordenar a lista de palavras em ordem decrescente com relação à quantidade de repetições no texto
void showImportantWords(WordList *list, int n); // Exibe a lista das n palavras que mais aparecem no texto

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

    printf("\n\nCusto do algoritmo: %d\n", CUSTO);
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
        CUSTO++;
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
    for (i = list->length; strcmp(strtoup(list->palavras[i].valor), strtoup(word)) != 0; i--) CUSTO++;

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
        CUSTO += 4;
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
        CUSTO++;
        aux = list->palavras[i];
        j = i-1;

        while ((j >= 1) && (aux.quant > list->palavras[j].quant)) {
            CUSTO++;
            list->palavras[j+1] = list->palavras[j];
            j--;
        }

        CUSTO++;
        list->palavras[j+1] = aux;
    }
}

void showImportantWords(WordList *list, int n) {
    if (list->length < n) n = list->length;
    for (int i = 1; i <= n; i++) {
        printf("%-20s %2d\n", list->palavras[i].valor, list->palavras[i].quant);
    }
}
