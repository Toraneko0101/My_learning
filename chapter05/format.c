#include <stdio.h>

int main(void){
    int a = 10000, b = 500, c = 3;

    printf("Aは %05d です。\n", a);
    printf("Bは %05d です。\n", b);
    printf("Cは %05d です。\n", c);
    printf("小数は %06.2fです。\n", 3.2);
    return 0;
}