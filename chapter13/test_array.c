#include <stdio.h>

int main(void){
    //残りには0が代入される
    //要素数を省略すると{}内の個数が要素数となる
    int array[10] = {100, 67, 45};
    array[2] = 100;
    printf("%d\n", array[2]);
    array[2] ++;
    printf("%d\n", array[2]);
    printf("%d\n", array[9]);
    printf("------------\n");

    //sizeを求める
    int length = sizeof(array) / sizeof(array[0]);
    for (int i=0; i<length; i++){
        printf("%d\n", array[i]);
    }
    return 0;
}