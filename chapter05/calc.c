#include <stdio.h>

int main(void){
    int water, milk, ans, money;
    double tax;
    water = 198;
    milk = 138;
    money = 1000;
    tax = 1.05;
    ans = money - (int)((water + milk * 2) * tax);

    printf("%d\n", ans);
}