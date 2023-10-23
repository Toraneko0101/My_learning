#include <stdio.h>
#include <string.h>

int main(void){
    char lastname[100];
    char firstname[100];
    char fullname[200];
    printf("苗字:");
    scanf("%100s", lastname);
    printf("名前:");
    scanf("%100s", firstname);

    sprintf(fullname, "%s %s", lastname, firstname);
    printf("%s\n", fullname);
}