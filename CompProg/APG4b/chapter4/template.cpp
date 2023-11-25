#include <bits/stdc++.h>
using namespace std;
/**
 * 同様の処理を行うが、利用する型が異なる関数は
 * 関数テンプレートを使ってまとめることができる
 * template <typename テンプレート引数>
 * 普通の関数
 * 
 * 関数名<テンプレート引数>();で呼び出し
 * 
 * 構造体の内容を型について一般化したい場合
 * template <typename テンプレート引数>
 * 普通の構造体
 * 
 * 構造体名<テンプレート引数>;で呼び出し
 * 
 * minやmaxはtemplate,
 * mapやvector等のコンテナはクラステンプレートで定義されている
 * 思えばvector<int>みたいに書いてたな。なるほど
*/

//例: 2乗を返す関数をint,doubleでまとめたい
//共通化したい場所にテンプレートの型を書く感じ
template <typename T>
T square(T x){
    return x*x;
}

//座標値の型を一般化したもの
template <typename S>
struct Point{
    S x;
    S y;
    void print(){
        cout << format("({},{})\n", x, y);
    }
};

int main(){
    int a = 3;
    double b = 3.14;
    cout << square<int>(a) << "\n";
    //square(b)と書くことも可能：引数の型から推定できるなら
    cout << square<double>(b) << "\n";

    //テンプレート引数の省略は許可されていない
    Point<int> p1 = {0,1};
    Point<double> p2 = {2.3, 4.5};
    p1.print();
    p2.print();


}