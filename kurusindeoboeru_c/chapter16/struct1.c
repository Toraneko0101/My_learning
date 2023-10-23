#include <stdio.h>
#include <string.h>

//構造体の名前（型名）を構造体タグ名と呼ぶこともある
//ブロックの中にまとめたい変数の型と名前を宣言する
//構造体タグは使用前に宣言する

//以下でstudent型の構造を宣言
//末尾のセミコロンを忘れないこと
struct student{
    int year;
    int classes;
    int number;
    char name[64];
    double height;
    double weight;
};

int main(void){

    //student型の変数(構造体変数)を宣言
    // C++ではstructをつけなくても構造体変数を宣言可能
    //コンパイラはほとんどがC++用なのでstructをつけなくても動いたりする
    struct student data;

    //構造体変数.要素名でアクセス
    data.year = 10;
    data.classes = 2;
    strcpy(data.name, "MAX_MIN_AVG");
    printf("%d年%d組\n", data.year, data.classes);
    printf("%s\n", data.name);
    return 0;

}