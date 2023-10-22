#include <stdio.h>

void func(int *p_value);

int main(void){
    int value = 10;
    printf("&value = %p\n", &value);
    func(&value);
    printf("value = %d\n", value);
    return 0;
}

void func(int *p_value){
    //アドレス値がコピーして渡される
    printf("p_value = %p\n", p_value);
    //通常変数モードで代入
    *p_value = 100;
    return;
}