#include <stdio.h>
#include <stdlib.h>

typedef struct{

    char name[64];
    int age;
    char sex[64];
}Person;

void input_data(Person *data);
void show_data(Person data);

int main(void){
    int cnt, data_size;
    Person *data; //ポインタ変数
    //reallocによる呼び出し回数を減らす
    data_size = 10;
    data = (Person*)malloc(sizeof(Person) * data_size);
    cnt = 0;

    while(1){
        //ポインタを渡し、関数内でメンバに代入
        input_data(&data[cnt]);
        if(data[cnt].age == -1){
            break;
        }
        cnt++;
        //配列の拡張
        if(cnt >= data_size){
            data_size += 10;
            data = (Person*)realloc(data, sizeof(Person) * data_size);
        }
    }
    for(int i=0; i < cnt; i++){
        show_data(data[i]);
    }

    free(data);
    return 0;
}

//アドレスを渡す
void input_data(Person *data){
    //printf(data->age); 構造体のメンバにアクセス。 
    // &data->age ポインタが指し示すメンバのアドレスを渡す。文字列の場合は当然 data->ageで先頭を指しているのでよい
    printf("名前:");
    scanf("%64s", data->name);
    printf("年齢:");
    scanf("%d", &data->age);
    printf("性別(male or female)");
    scanf("%64s", data->sex);
    printf("\n");
}

void show_data(Person data){
    printf("名前:%s\n", data.name);
    printf("年齢:%d\n", data.age);
    printf("性別:%s\n", data.sex);
}