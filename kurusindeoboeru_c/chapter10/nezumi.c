#include <stdio.h>
#include <math.h>

int main(void){

    int judge = pow(10,6);
    int current_money = 1;
    int cnt = 1;
    while(1){
        current_money *= 2;
        cnt ++;
        if (current_money > judge){
            break;
        }
    }
    printf("%d\n", cnt);
}