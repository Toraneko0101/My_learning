#include <stdio.h>
#include <string.h>

int main(void){
    //spaceが区切り記号とみなされることに注意
    //桁数を指定しないとバッファオーバーフローのもとになる
    char str[10];
    scanf("%10s", str);
    printf("%s\n",str);
    int i = 0;
    //文字数のカウント(EOFが出てくるまでカウントアップ)
    for (i=0; str[i] != '\0'; i++){

    }
    printf("%d\n", i);
    //strlenでも同じことができる
    i = strlen(str);
    printf("%d\n", i);
    return 0;
}