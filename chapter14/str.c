#include <stdio.h>

int main(void){
    //EOFが入るので、1つ要素数が多くなる
    //なお、配列の初期化時に、要素を省略した場合、残りには0が入り、それがEOSとなる
    //EOSを書いた場合は、要素数を省略可能
    char str[6] = {'M', 'A', 'T', 'T', 'O', '\0'};
    printf("%s\n", str);

    //文字数リテラル
    //初期化時にしか使えない
    //後から代入した場合は以下のようにする
    char str1[] = "MATTO";
    str1[2] = 'R';
    str1[3] = 'I';
    printf("%s\n", str1);
    return 0;
}