#include <stdio.h>

int main(void){
    int a,b,c,d,e;
    FILE *file;
    file = fopen("test2.txt", "r");
    fscanf(file, "%d,%d,%d,%d,%d", &a, &b, &c, &d, &e);
    fclose(file);
    printf("%d,%d,%d,%d,%d\n",a,b,c,d,e);
    return 0;
}