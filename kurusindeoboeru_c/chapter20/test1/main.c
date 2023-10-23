#include "sum.h"
#include <stdio.h>

int main(void){
    int value;
    value = sum(70,100);
    printf("%d\n", value);
    //gcc -o my_program main.c sum.c
    return 0;
}