typedef struct{

    char name[64];
    int age;
    char sex[64];
}Person;

void input_data(Person *data);
void show_data(Person data);

int main(void){

    Person data[3];
    for (int i=0; i<3; i++){
        input_data(&data[i]);
    }

    for (int i=0; i<3; i++){
        show_data(data[i]);
    }

    return 0;
}

//アドレスを渡す
void input_data(Person *data){
    //printf(data->name); 構造体のメンバにアクセス。 
    // &data->name ポインタが指し示すメンバのアドレスを渡す
    printf("名前:");
    scanf("%s", &data->name);
    printf("年齢:");
    scanf("%d", &data->age);
    printf("性別(male or female)");
    scanf("%s", &data->sex);
    printf("\n");
}

void show_data(Person data){
    printf("名前:%s\n", data.name);
    printf("年齢:%d\n", data.age);
    printf("性別:%s\n", data.sex);
}