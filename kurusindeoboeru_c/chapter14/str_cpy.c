#include <stdio.h>
#include <string.h>

int main(void){

    //strcpy(to_copy, from_copy);
    char str[10];
    char str1[10];
    //文字列のコピーに使用:こうすれば初期化以外にも使える
    strcpy(str, "NEKONEKO");
    printf("%s\n", str);

    //strncpy:先頭から指定された文字数のみコピー
    //コピー元にEOSが入っていない可能性があるので\0を付けること
    strncpy(str1, "NEKONEKO", 3);
    str1[3] = '\0';
    printf("%s\n", str1);
    return 0;
}