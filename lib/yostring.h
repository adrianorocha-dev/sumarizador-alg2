int strLen(char *str);

char * strtoup(char *str);

int strLen(char *str) {
    printf(" %s\n", str);
    int i;
    for (i = 0; str[i] != '\0'; i++);
    return i;
}

char * strtoup(char *str) {
    printf("calc %s ", str);
    int length = strLen(str);
    for (int i = 0; i < length; i++) {
        if ((str[i] >= 'a') && (str[i] <= 'z')) {
            str[i] -= 32;
        }
    }
    return str;
}
