#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//angle to radian
#define RAD(ARC) ((ARC) * 3.14159 / 180)

int main(void){
    printf("%d\n", abs(-10));
    printf("%f\n", pow(8,3));
    printf("%f\n", sqrt(16));
    printf("%f\n", sin(RAD(30)));
    double syahenn = 5 / cos(RAD(40));
    double taihenn = syahenn * sin(RAD(40));
    printf("対辺:%f\n", taihenn);
    printf("高さ:%f\n", taihenn + 1.6);
}
