#include <stdio.h>

int main(void){

    int num;
    scanf("%d", &num);
    switch(num){
        case 1:
        case 10:
            printf("%d\n", 1);
            break;
        case 2:
            printf("%d\n", 2);
            break;
        default:
            printf("%d\n", -1);
            break;
    }

    return 0;
}