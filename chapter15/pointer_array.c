#include <stdio.h>

int main(void){
    int *data;
    int average = 0;
    int array[5] = {7,9,10,2,17};

    data = array;
    for (int i=0; i<5; i++){
        average += data[i];
    }
    average /= 5;
    printf("%d\n", average);
    return 0;
}