#include <stdio.h>

int olympic(int year);

enum {
    NON_HEID = 0,
    SUMMER = 1,
    WINTER = 2
};

int main(void){
    int year, hold;
    scanf("%d", &year);
    hold = olympic(year);

    if(hold == SUMMER){
        printf("夏季オリンピック開催");
    }else if(hold == WINTER){
        printf("冬季オリンピック開催");
    }else{
        printf("オリンピックは開催しません");
    }
}

int olympic(int year){
    if (year % 4== 0){
        return SUMMER;
    }else if(year % 4 == 2){
        return WINTER;
    }else{
        return NON_HEID;
    }
}