#include <stdio.h>

int main(void){
    //整数->実数
    printf("%f\n", 1.03 * 9);
    //キャスト(強制的に型変換)
    printf("%d\n", (int)(1.03 * 9));
    return 0;
}