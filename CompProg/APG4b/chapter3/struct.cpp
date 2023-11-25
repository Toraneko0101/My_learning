#include <bits/stdc++.h>
using namespace std;

/**
 * pair,tupleも構造体を使って実装されている
 * 複数の型をまとめた新しい型を定義するならこれ
 * class: デフォルトのアクセスがprivate
 * struct: デフォルトのアクセスがpublic
*/

struct Human{
    int age;
    int height;
    int weight;
    string region;
    bool is_working;

    Human(int _age, int _height, int _weight, string _region, bool _is_working){
        age = _age;
        height = _height;
        weight = _weight;
        region = _region + "(country)";
        is_working = _is_working;
    }

    double BMI(){
        double bmi = weight / pow((double)height / 100, 2);
        return bmi; 
    }
};

int main(){
    //オブジェクト生成
    //Human h = {12, 159, 43, "japan", false};
    //コンストラクタ
    Human h(12,159,43,"japan", false);
    cout << format("region = {}\n", h.region);
    cout << h.BMI() << endl;
}