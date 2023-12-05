/**
 * staticでーためんば
 * objごとではなく、クラス変数
 * staticデータメンバはクラスの外で実体を定義する
 * ⇒初期化、破棄は開始終了時にまとめて行われる
 * ⇒実行順序を制御できないのでエラーの発生要因特定に苦労することも
 * ⇒インスタンスを生成せずとも使えるのが利点
 * 
 * ヘッダファイルが2つ以上のファイルでincludeされる場合、headerで実体の定義を行うと多重定義となる
 * そのためstaticデータメンバの実体の定義はsourceで行う
 * 
 * 名前空間の時もstaticが登場したが、あれは無名名前空間を代わりに使うので気にしなくていいはず
*/
#include <bits/stdc++.h>
using namespace std;

class Counter{
public:
    static int count_;
    static void test();
private:
    static int hoge_;
};

int Counter::count_ = 0;
//★privateなstaticメンバ変数は、初期化のみクラスの外から可能
//代入や、要素の閲覧はstaticメンバ関数を通して行う！
int Counter::hoge_ = 0;
/**
 * staticメンバ関数
 * こちらもインスタンスを生成せずにクラスの内の関数を呼び出せる
 * しかし、staticでないメンバ変数や関数にアクセスはできない
 * これはインスタンスが複数存在する場合，どのインスタンスのメンバにアクセスすべきか区別できないため
 * 通常の関数と比べて優れているのはprivateなstaticメンバ変数にアクセスできる事
 * 
*/
void Counter::test(){
    cout << Counter::hoge_ << "\n";
}

int main(){
    vector<Counter> vec;
    for(auto i: views::iota(0,10)){
        Counter c;
        vec.push_back(c);
        ++Counter::count_; //参照方法
    }
    cout << Counter::count_ << endl; //10
    Counter::test(); //staticメンバ関数を通して、staticメンバ変数の値を確認する
}

