#include <stdio.h>
#include <string.h>

int main(void){
    //配列の場合、==でメモリの比較になるので使えない
    //EOFまで同じか比較するためにloopを書く場合は、注意が必要

    //等しいなら0。プラスマイナスは文字コードに関係する
    int judge = strcmp("Neko", "Neko");
    // 三項演算子
    printf("%s\n", judge == 0 ? "True" : "False");
    return 0;
}