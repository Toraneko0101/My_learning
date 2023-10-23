#include <stdio.h>

int main(void){

    double r;
    double s;

    do{
        printf("半径?: ");
        scanf("%lf", &r);
    }while (r < 0);
        s = r * r * 3.14;
        printf("面積は %f です\n", s);

    return 0;
}