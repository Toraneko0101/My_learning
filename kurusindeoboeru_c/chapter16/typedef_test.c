#include <stdio.h>

typedef struct{
    int year;
    int classes;
    int number;
    char name[64];
    double height;
    double weight;
}student;

int main(void){
    
    student data1;
    data1.year = 3;
    data1.classes = 4;
    printf("%d年%d組", data1.year, data1.classes);
    return 0;
}