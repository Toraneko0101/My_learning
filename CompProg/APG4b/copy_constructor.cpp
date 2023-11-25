#include <bits/stdc++.h>
using namespace std;

/**
 * 関数の引数としてオブジェクトを渡す場合
 * コピーコンストラクタが呼ばれる
 * 例
 * Mystruct MyPair = old_obj;
 * Mystruct MyPair(old_obj);
*/


struct MyPair{
    int x;
    string y;

    MyPair(){
        cout << "normal constructor called" << "\n";
    }
    //定義しない場合、全てのメンバ変数をそのままコピーして新しいobjを作る
    //oldのメンバ変数を書き換えられないようにconstにしている
    MyPair(const MyPair &old){
        cout << "copy constructor called" << "\n";
        x = old.x + 1;
        y = old.y + "(new)";
    }
};

int main(){
    MyPair p;
    p.x = 12345;
    p.y = "hello";
    MyPair q(p);
    cout << format("q.x = {}\n", q.x);
    cout << format("q.y = {}\n", q.y);
}