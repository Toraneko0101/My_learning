#include <stdio.h>

int main(void){
    int n[4];

    printf("整数nを入力してください\n");
    scanf("%d", n);

    printf("入力された整数は%dです。\n", n[0]);
    return 0;
}