#include <bits/stdc++.h>
using namespace std;

//副作用のある関数
void g(int &x){
    x *= 2;
}

void min_and_max(int a, int b, int c, int &minimum, int &maximum){
    minimum = min({a,b,c});
    maximum = max({a,b,c});
}
int sum100(vector<int> &a);

int main(){
    int a =  3;
    int &b = a;
    b = 4;
    g(b);
    cout << a << endl;

    //宣言時に参照先の指定が必要
    //後から参照先を変更することはできない
    //参照への参照にならないように注意する

    //結果を複数返したいとき
    //配列に入れる or 参照の引数を用いて結果を返す
    int minimum, maximum;
    min_and_max(3,1,5,minimum, maximum);
    cout << minimum << maximum << endl;

    //無駄なコピーを減らす
    vector<int> vec(10000000, 1);
    for(int i=0; i<500; i++){
        cout << sum100(vec) << endl;
    }

    //範囲forで参照を使う
    vector<int> data = {1,3,2,5,4,6,7};
    //前三つだけ2倍に
    for(int &x: data | views::take(3)){
        x *= 2;
    }
    for(int d : data){
        cout << d << endl;
    }
    //vector要素への参照を作った場合
    //push_back等をして要素数を変えると意図せぬ結果が起こる
    //スコープ内で定義した参照型をreturnするのも未定義動作であるため避ける必要がある
    //グローバル変数の場合は、返り値がスコープ内なので許可される
}

int sum100(vector<int> &a){
    int result = 0;
    for(int i=0; i<100; i++) result += a.at(i);
    return result;
}
