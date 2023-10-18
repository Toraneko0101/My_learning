#include <stdio.h>

int main(void){
    int digit;
    scanf("%d", &digit);

    if(digit <= -1){
        printf("%dは負の整数です\n", digit);
    }

    if(digit % 3 == 0 && digit % 5==0){
        printf("%dは15の倍数\n", digit);
    }else if(digit % 3== 0){
        printf("%dは3の倍数\n", digit);
    }else if(digit % 5 == 0){
        printf("%dは5の倍数\n", digit);
    }else{
        printf("%dは3の倍数でも5の倍数でもない",digit);
    }

    return 0;
}