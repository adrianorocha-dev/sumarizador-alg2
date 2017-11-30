#include "lib/yolib.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *arquivo = fopen("melhor_caso_160.txt", "w");

    for (int i = 1; i <= 160; i++) {
        fprintf(arquivo, "teste ");
    }

    arquivo = fopen("melhor_caso_320.txt", "w");

    for (int i = 1; i <= 320; i++) {
        fprintf(arquivo, "teste ");
    }

    return 0;
}
