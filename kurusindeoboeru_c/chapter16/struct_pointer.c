#include <stdio.h>
#include <string.h>

typedef struct{
    int year;
    int classes;
    int number;
    char name[64];
    double height;
    double weight;
}student;

void student_operate(student *data);

int main(void){
    student data;
    student *pdata;

    pdata = &data;
    (*pdata).year = 10;
    strcpy(pdata->name, "Nyanko");

    printf("%d\n", pdata->year);
    printf("%s\n", data.name);

    student_operate(&data);
    printf("%d\n", pdata->year);
}

//構造体型のポインタ型の引数を持つ関数
//引数の型はポインタ型:構造体のはじめの要素のアドレス
//コピーされないので高速化になる
void student_operate(student *data){
    data->year = 1;
}