#include <stdio.h>

int main(int argc, char* argv[]){
    //optionの指定を確認する
    //オプションを一つずつ消化していく
    for(int i=1; i< argc; i++){
        if(argv[i][0] == '-'){
            if(argv[i][1] == 'a')
                printf("-a オプション\n");
            if(argv[i][1] == 's')
                printf("-s オプション\n");
        }
    }
}