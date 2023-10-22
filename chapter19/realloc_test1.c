#include <stdio.h>
#include <stdlib.h>

int main(void){
    int* heap;

    heap = (int*)malloc(sizeof(int) * 10);
    heap = (int*)realloc(heap, sizeof(int) * 100);
    //添え字でアクセス
    heap[99] = 4;
    printf("%d\n", heap[99]);
    free(heap);
    return 0;
}