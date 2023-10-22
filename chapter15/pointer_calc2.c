#include <stdio.h>

int main(void){
    int *data;
    int average = 0;
    int array[5] = {7,16,5,8,11};

    //array[5]のアドレス値になるまで、dataが指すアドレスをポインタが指す型の分だけ増やす
    for (data = array; data != &array[5]; data++){
        average += *data;
    }

    printf("%d\n", average / 5);
    return 0;
}