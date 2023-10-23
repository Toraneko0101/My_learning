#include <stdio.h>

int main(void){
    int i, j, k;
    //iのmemoryを参照
    //例) 0x7ffd481ff824
    // int型は4byteなので、4番だけずれた連番が与えられている
    // アドレスさえ分かっていればいいので、必ずしも連番だとは限らない
    printf("%p\n", &i); 
    printf("%p\n", &j); 
    printf("%p\n", &k); 
    return 0;
}