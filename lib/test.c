#include "yolib.h"
#include "yostring.h"
#include <stdio.h>

void main() {
    char *palavra = input("");
    removeSpecialChars(palavra);
    printf("Palavra sem caracteres especiais: %s\n", palavra);
}
