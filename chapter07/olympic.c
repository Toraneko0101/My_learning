#include <stdio.h>

int main(void){

    int years;
    
    printf("西暦年を入力してください。ex) 2000 : ");
    scanf("%d", &years);

    if(years % 4 == 0){
        printf("%dは夏季オリンピックの年", years);
    }else if(years % 4 == 2){
        printf("%dは冬季オリンピックの年", years);
    }else{
        printf("%dはオリンピックがありません", years);
    }

    return 0;

}