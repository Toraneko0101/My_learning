#include <stdio.h>
#include <string.h>

struct student{
    int year;
    int classes;
    int number;
    char name[64];
    double height;
    double weight;
};

int main(void){
    struct student data1, data2;

    data1.year = 3;
    data1.classes = 4;
    data1.number = 18;
    strcpy(data1.name, "Nyanko");
    data1.height = 167.1;
    data1.weight = 55.1;

    data2 = data1;
    data2.weight = 56.3;

    printf("data1.year = %d : data2.year = %d\n", data1.year, data2.year);
    printf("data1.weight: %f, data2.weight: %f\n", data1.weight, data2.weight);
}