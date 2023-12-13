/**
 * 関数呼び出しの操作を統一化したもの
 * 引数、f, args...
*/
#include <bits/stdc++.h>
using namespace std;


struct test1{
    /**
     * auto:型推論機能
     * 1550: 40 = 500 : x
     * コンパイル時に変数の型を決定する
     * 具体的には変数の初期化に使われる値から推論する
     * しかし、operator()の戻り値に対してはautoが直接使えない
     * よって、-> intという後置記法で、戻り値の型を明示的に指定している(使える場合はいらない)
     * operatorはオペランドの型によって戻り値の型が決まったりするので
     * 戻り値の型が複雑な場合にはautoの仕様が推奨される
    */
    auto operator() ()-> int{
        return 10;
    }
    // int operator() (){
    //     return 10;
    // }

    auto operator() (int n) -> int{
        return n;
    }
};


struct has_member{
    auto member_function(int n) -> int{
        return n;
    }

    int member_object;
};

auto f(int) -> double{
    return 3.14159;
}

auto g(int) -> double {
  return 2.71828182846;
}

auto g(int,int) -> double {
  return 3.14159265359;
}

int main(){
    //test1 obj(); //推奨されない.初期化ではなく、test1型のobjという名前の関数を定義しているように見える
    test1 obj1{}; //ユーザ定義のコンストラクタにとらわれないので推奨
    cout << invoke(obj1) << endl;
    // cout << obj1(100) << endl;
    cout << invoke(obj1, 100) << endl;

    has_member obj{25};
    //メンバ関数、メンバ変数呼び出し
    cout << invoke(&has_member::member_function, obj , 50) << "\n";
    cout << invoke(&has_member::member_object, obj) << endl;
    auto ref = std::ref(obj); //参照
    //reference_wrapperからのメンバ関数呼び出し
    cout << invoke(&has_member::member_object, ref) << "\n";
    //関数呼び出し
    cout << invoke(f, 20) << "\n";

    /**
     * 関数ポインタは関数のシグネチャを明示的に指定する
     * シグネチャ：関数の多重定義解決に用いるための情報
     * 関数がクラスのメンバなら関数自身のconst等の情報やクラスも呼び出し情報に含まれる
     * 関数を直接呼び出す場合、引数の型の情報がないのでどちらかわからずエラる。そのため関数ポインタを使う
     * 
     * 関数ポインタ
     * double func(int val); という関数があった場合
     * auto f = (double(*)(int))func
     * オーバーロードされていなければ
     * f = &func
     * double val = (*f)(2); で済む話
    */
   cout << invoke((double(*)(int))g, 10) << "\n";
   cout << invoke((double(*)(int, int))g, 10, 10) << "\n";


}