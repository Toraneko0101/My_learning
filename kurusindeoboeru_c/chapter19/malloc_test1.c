#include <stdio.h>
#include <stdlib.h>

int main(void){
    int* heap;
    //int型を10個分のメモリを確保
    //ポインタ変数にするため(int*)で型変換
    heap = (int*)malloc(sizeof(int) * 10);
    
    //メモリ確保に失敗した場合、exitやabortで強制終了する
    if(heap == NULL) exit(0);

    for(int i=0; i<10; i++){
        heap[i] = i;
    }

    printf("%d\n", heap[5]);
    free(heap);
    return 0;
}