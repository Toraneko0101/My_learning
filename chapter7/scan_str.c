#include <stdio.h>

int main(void){
    char text[128];
    printf("文字列を入力してください(9文字まで)\n");
    scanf("%9s", text);

    printf("入力された文字列の先頭文字は%cです", *text);
    return 0;
}