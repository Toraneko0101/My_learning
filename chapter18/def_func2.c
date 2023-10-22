#include <stdio.h>
//名前の後に()で文字を指定すると、置き換え部分で同じアルファベットの部分を置き換える
#define PRINTM(X) printf("%d\n", X);

int main(void){
    int a1 = 100, a2 = 50;

    PRINTM(a1);
    PRINTM(a2);
    return 0;

}