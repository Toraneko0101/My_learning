#include <stdio.h>

int main(void){
    //これでポインタ変数pはiと同じアドレスを指し示すことになった
    int *p;
    int i;
    p = &i;

    printf("p=%p\n", p);
    printf("&i=%p\n", &i);

    return 0;
}