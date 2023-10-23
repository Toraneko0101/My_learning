#include <stdio.h>

void cnt();

int main(void){
    cnt();
    cnt();
    cnt();
    return 0;
}

void cnt(void){
    static int count;
    count++;
    printf("%d\n", count);
}