#include <bits/stdc++.h>
using namespace std;

//前置き方式
int Hoge(void){return 0;}
//int [](){return 0;} ラムダ式は無理

//後置き方式
auto Fuga(void) -> int{return 0;} //C++11から。通常関数で利い要するにはpressholderとして前置き部分にautoを書く必要あり
//[]() -> int{return 0:}

//省略形式
//Hogehoge(void){return 0;} //error
//[](){return 0;} 戻り値型を記述しない。ラムダ式のみ許される

/**
 * 通常関数で前置きと後置きの戻り値型にauto指定が許されたのはC++14から
 * 関数本体にreturnがないと戻り値型はvoidに推論
 * returnが複数ある場合は、共通の型が戻り値型になる
 * 通常関数の場合、後置き記法の前置きautoは、pressholderであって型推論ではない
*/

//参照型が返される
decltype(auto) f(int &r){
    return r;
}

int main(){
    //式から決定されるのは同じ
    decltype(10+1) x = 10 + 1;
    auto y = 10 + 1;
    //参照の場合
    int v = 0;
    int &r = v;
    decltype(r) x1 = r; //式rから int&型 -> 式が参照型の場合は、decltypeも参照型になる
    auto x2 = r; //式rからint型
    x1 = 3;
    x2 = 8;
    cout << v << endl;
    cout << x2 << endl;
    /**
     * 戻り値の型がdecltype(auto)なら、戻り値の型は
     * decltype(return文の式部分)となる。
     * 参照の変数を参照のままreturnで返したい場合に使う
    */

    //同じ型か確認
    static_assert(is_same<decltype(x1), int&>::value, "");

    int test = 1;
    //参照型として受け取る
    decltype(auto) test1 = f(test);
    test1 = 5;
    cout << test << endl; //5
}