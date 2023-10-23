#include <stdio.h>
#include <ctype.h>

int main(void){
    char c = 'A' + 32;
    printf("%c\n", c);

    // '0', '1'...という順に並んでいることを利用し、intにする
    //数字以外は-1にする
    char d = 'A';
    int digit = -1;
    if (d >= '0' && d <= '9'){
        digit = d - '0';
    }
    printf("%d\n", digit);

    //ライブラリを使ったパターン
    char e = '0';
    char judge;

    if (!isalpha(e)){
       judge = '!'; 
    }else{
        judge = e;
    }
    printf("%c\n", judge);

    return 0;
}