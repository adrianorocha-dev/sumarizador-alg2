/*
    Autor: Adriano Rocha
*/

int strLen(char *str); // Retorna o tamanho de uma string.

char * strtoup(char *str); // Converte todas as letras de uma string para maiúsculo.
char * strtolow(char *str); // Converte todas as letras de uma string para minúsculo.

char *removeSpecialChars(char *str); // Remove quaisquer caracteres especiais de uma string
int thereIsSpecialChar(char *str); // Verifica se uma string contém caracteres especiais

int strLen(char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++);
    return i;
}

char * strtoup(char *str) {
    int length = strLen(str);
    for (int i = 0; i < length; i++) {
        if ((str[i] >= 'a') && (str[i] <= 'z')) {
            str[i] -= 32;
        }
    }
    return str;
}

char * strtolow(char *str) {
    int length = strLen(str);
    for (int i = 0; i < length; i++) {
        if ((str[i] >= 'A') && (str[i] <= 'Z')) {
            str[i] += 32;
        }
    }
    return str;
}

char *removeSpecialChars(char *str) {
    int specialChar = thereIsSpecialChar(str);
    while (specialChar >= 0) {
        int length = strLen(str);
        for (int i = specialChar; i < length; i++) {
            str[i] = str[i+1];
        }
        specialChar = thereIsSpecialChar(str);
    }

    return str;
}

int thereIsSpecialChar(char *str) {
    int index = -1;
    int length = strLen(str);
    for (int i = 0; i < length; i++) {
        //if ((str[i] < '0' || str[i] > '9') && (str[i] < 'A' || str[i] > 'Z') && (str[i] < 'a' || str[i] > 'z') && str[i] != '-') {
        if ((str[i] == '\"') || (str[i] == '\'') || (str[i] == ',') || (str[i] == '.') || (str[i] == ':') || (str[i] == ';')) {
            index = i;
            break;
        }
    }
    return index;
}
