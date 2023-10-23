#include <stdio.h>

int main(void){

    int *p = NULL;
    int i;
    p = &i;
    *p = 10; //通常変数として使用
    printf("*p = %d\n", *p);
    printf("i = %d\n", i);
    return 0;
}