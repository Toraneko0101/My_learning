#include <stdio.h>

int main(void){
    char data1[64], data2[64];
    FILE *file;
    file = fopen("test.txt", "r");
    fscanf(file, "%s%s", data1, data2);
    fclose(file);
    printf("%s\n%s\n", data1, data2);
    return 0;
}