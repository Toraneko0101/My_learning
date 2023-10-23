#include <stdio.h>
#include <string.h>

int main(void){
    char str[] = "Nekoneko""Inudayo";
    printf("%s\n", str);
    
    //配列に記憶された文字列を連結する場合
    //stringを操作するときはたいてい,string.h
    char str1[100] = "Onigiri";
    char str2[] = "Mogumogu";
    strcat(str1, str2);
    printf("%s\n", str1);

    //sprintf
    //結果を配列の中に記憶する
    char str3[100];
    char str4[] = "Nezumi";
    char str5[] = " ate Lion";
    int i = 3;
    sprintf(str3, "%s%s%d", str4, str5, i);
    printf("%s\n", str3);
    return 0;

}