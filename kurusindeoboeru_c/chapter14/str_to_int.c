#include <stdio.h>
#include <stdlib.h>

int main(void){
    //atoiでは+-が付いた符号付きの数字も変換可能
    char str[] = "-1450";
    int digit = atoi(str);
    printf("%d\n", digit * 2);
    //atofは実数変換
    char str1[] = "-3.14159";
    float f = atof(str1);
    printf("%f\n", 2*2*f);
    return 0;
}