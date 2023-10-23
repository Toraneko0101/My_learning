#include <stdio.h>

int main(void){
    int buf = 100;
    FILE *file;
    file = fopen("test.dat", "wb");
    //fwrite(書き込む変数アドレス, 1項目のサイズ, 書き込むデータの個数, ファイルのパス)
    fwrite(&buf, sizeof(buf), 1, file);
    fclose(file);
    return 0;
    //xxd test.dat 
    // 00000000: 6400 0000  リトルエンディアン
    // リトルエンディアンは先頭に意味がある数値が来やすいので、人間的にはわかりにくそうだがよさそう
}