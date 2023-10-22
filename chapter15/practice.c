#include <stdio.h>

void max_min(int array[], int *max, int *min);

int main(void){
    int array[10];
    int max, min;
    int cnt = 0;
    //-1で入力終了と判断
    //0~100までしか入力されない
    //10個までしか入力されない前提
    do{
        printf("%d番目:", cnt + 1);
        scanf("%d", &array[cnt]);
        cnt++;
    }while (array[cnt-1] != -1);

    max_min(array, &max, &min);
    printf("最大値:%d, 最小値:%d", max, min);
    return 0;
}

void max_min(int array[], int *max, int *min){
    *min = 200;
    *max = -100;
    for (int i=0;; i++){
        if (array[i] == -1){
            return;
        }
        if(array[i] < *min){
            *min = array[i];
        }
        if (array[i] > *max){
            *max = array[i];
        }
    }
    return;
}