#include <bits/stdc++.h>
using namespace std;
//共用体の代替手段であるstd::variantを用いる

/**
 * variantクラスは格納されうる候補の型リストに含まれる
 * 型のobjを切り替えながら保持する
 * 継承関係になくとも単一のobjに代入切り替え可能
 * 
 * 派生⇒基底ならアップキャストで可能
 * 列挙した複数の型⇒単一の型で多態性
 * 
*/

// 継承関係にないクラス群
// 共通のインターフェースを呼び出し、対応する関数を呼び出す
struct A { void f() {cout << "A is called\n";} };
struct B { void f() {cout << "B is called\n";} };
struct C { void f() {cout << "C is called\n";} };


int main(){
    //int, char, stringのいずれかの型を代入できる型を生成する
    //以下では保持できる型を渡している
    variant<int, char, string> v = 3; //int型のobjを代入

    //候補型の0番目の型を保持しているか(index)
    if(v.index() == 0){
        //保持している値を取得。参照として取得;
        //get_ifなら保持している値を指すポインタを取得する。
        int &x = std::get<0>(v); 
        x = 11;
        cout << x << endl;
    }

    //string型を代入
    v = string("Hello");

    //string型を保持しているか
    //holds_alternative: variantオブジェクトが指定の候補型を現在保持しているかを判定
    //variant<Types...> &xでのindexとx.index()が等価な時にtrue, それ以外false
    if(holds_alternative<string>(v)){
        string &x = std::get<string>(v);
        cout << x << endl;
    }

    variant<A,B,C> test = A{};
    test = B{};
    if(holds_alternative<B>(test)){
        cout << "test has B-type obj.\n";
    }

    //ジェネリックラムダを用いて、全ての候補型で共通の操作を行う
    //std::visitはVisitorパターンを簡単に実装可能
    
    std::visit([](auto &x){
        x.f();
    },test);

}