#include <stdio.h>

int main(int argc, char* argv[]){
    //コマンドライン引数
    // argc:コマンドラインの数
    // argv:文字配列へのポインタ変数

    //アプリケーション自身のファイル名
    printf("%d\n", argc);
    printf("%s\n", argv[0]);

    if(argc > 1){
        printf("%s\n", argv[1]);
    }


    return 0;
}