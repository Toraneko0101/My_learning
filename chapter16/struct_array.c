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

void student_print(student data[], int cnt);
int main(void){

    student data[10];
    data[1].year = 3;
    strcpy(data[2].name, "Nyanko");

    student_print(data, 10);
    printf("%s\n", data[2].name);
    return 0;
}

//構造体配列の最初の要素のアドレス,data[0]を渡している
//内部ではindexなどで目的の要素のアドレスにアクセスしている
void student_print(student data[], int cnt){
    printf("%d\n", data[1].year);
    //data[2].nameのアドレスにアクセスし、値を書き換え
    strcpy(data[2].name , "Inudayo!!!");
    return;
}