#include <stdio.h>
#define NAME_LENGTH 50
enum Direction{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

typedef struct{
    char name[NAME_LENGTH];
    enum Direction direction;
}Person;

int main(void){
    Person person = {"Nekoyama", UP};

    if(person.direction == UP){
        printf("UP\n");
    }
}

