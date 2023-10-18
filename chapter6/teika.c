#include <stdio.h>

int main(void){
    int original_price;
    int one, three, five, eight;
    printf("定価を入力してください:");
    scanf("%d", &original_price);

    one = (int)(original_price * (1 - 0.1));
    three = (int)(original_price * (1 - 0.3));
    five = (int)(original_price * (1 - 0.5));
    eight = (int)(original_price * (1 - 0.8));

    printf("1割引:%d\n", one);
    printf("3割引:%d\n", three);
    printf("5割引:%d\n", five);
    printf("8割引:%d\n", eight);


}