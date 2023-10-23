//どこか1つのソースファイル内で普通の宣言を行い、定義する
int Public;

int sum(int min, int max){
    int num;
    num = (min + max) * (max - min + 1) / 2;
    return num;
}