#include <stdio.h>
#include <string.h>

int main(void){
    FILE *file;
    char data1[64], data2[64];
    strcpy(data1, "neko");
    strcpy(data2, "inu");

    file = fopen("test.txt", "w");
    fprintf(file, "%s\n%s\n", data1, data2);
    fclose(file);
    return 0;
}