#include <stdio.h>

int main(void){
    //配列を書き込む
    int buf[] = {10, 100, 1000, 10000};
    int ans[4] = {};
    FILE *file;
    file = fopen("test.dat", "wb");
    fwrite(buf, sizeof(int), 4, file);
    fclose(file);
    //00000000: 0a00 0000 6400 0000 e803 0000 1027 0000  ....d........'.. ASCIIで印刷可能な文字があれば右に表示される

    //配列を読み込む
    file = fopen("test.dat", "rb");
    fread(ans, sizeof(int),4, file);
    printf("%d,%d,%d,%d\n", ans[0], ans[1], ans[2], ans[3]);
    return 0;
}