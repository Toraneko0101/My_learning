#include <stdio.h>
#include <string.h>

int main(void){

    //memcpy(to_copy, from_copy, 配列全体のsize)

    int array1[5];
    int array2[5];
    
    for (int i=0; i < sizeof(array1) / 4; i++){
        array1[i] = i;
    }

    memcpy(array2, array1, sizeof(array1));

    for (int i=0; i < sizeof(array2) / 4; i++){
        printf("%d\n", array2[i]);
    }

    return 0;
}