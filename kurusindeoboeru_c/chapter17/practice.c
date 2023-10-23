#include <stdio.h>
#include <string.h>

typedef struct{
    int num;
    char name[64];
    int test_avg;
}Person;

int main(void){

    FILE *file;
    file = fopen("test.csv", "w");
    fprintf(file, "番号,名前,テストの平均点\n");

    char names[][64] = {"野比のび太", "源静香", "剛田武", "骨川スネ夫"};
    int point[] = {0,90,40,70};
    Person persons[4];
    for (int i=0; i<4; i++){
        persons[i].num = i+1;
        strcpy(persons[i].name, names[i]);
        persons[i].test_avg = point[i];
    }

    for(int i=0; i<4; i++){
        fprintf(file,"%d,%s,%d\n", persons[i].num, persons[i].name, persons[i].test_avg);
    }



    return 0;
}