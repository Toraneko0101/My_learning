#include <stdio.h>

int main(void){

    int *data;
    int average = 0;
    int array[5] = {7,16,5,8,11};
    data = array;

    for (int i=0; i<10; i++){
        average += *(data + i);
    }

    printf("%d\n", average / 5);

    return 0;
}