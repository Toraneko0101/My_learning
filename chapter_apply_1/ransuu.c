#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_random(int min, int max);

int main(void){
    //乱数の最大値はRAND_MAX
    //rand() / RAND_MAXで 0 ~ 1
    //max - minで幅
    int min = 5;
    int max = 10;
    int num;
    //乱数の計算に使う種を指定
    srand((unsigned int)time(NULL));

    for (int i=0; i<10; i++){
        //rand() 0 ~ RAND_MAX
        // 5 + rand()* 6 / (1.0 + RANS_MAX)
        // min-pattern
        // 5 + 0 = 5
        // max-pattern
        // 5 + (int)(6x  / 1 + x) = 5 + (int)5.9999 = 10
        printf("%d\n", get_random(1,6));
    }
}

int get_random(int min, int max){
    int num = min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
    return num;
}