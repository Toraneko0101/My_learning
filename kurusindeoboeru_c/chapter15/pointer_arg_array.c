#include <stdio.h>

int get_average(int[], int);
int main(void){
    int average, array[10] = { 15, 78, 98, 15, 98, 85, 17, 35, 42, 15 };
    
    //配列の場合、アドレスを渡しているので関数内で値を変更すると、呼び出し元も変化する
    //アドレスを渡しているので要素数は無視される
    //仮引数内でのdata[10], data[], *dataはすべて同じものを意味する
    //本来は*dataで、data[10], data[]のような書き方も許されている
    int length = sizeof(array) / sizeof(array[0]);
    average = get_average(array, length);
    printf("%d\n", average);
    printf("array[3] = %d\n", array[3]);
    return 0;
}

int get_average(int data[], int len){
    int average = 0;
    for(int i=0; i<len; i++){
        average += data[i];
    }
    data[3] = 111;

    return average / 10;
}