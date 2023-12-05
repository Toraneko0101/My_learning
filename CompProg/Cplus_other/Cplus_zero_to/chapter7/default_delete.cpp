/**
 * デフォルトコンストラクタ
 * コピーコンストラクタ/代入演算子
 * ムーブコンストラクタ/代入演算子
 * デストラクタ
 * これらは暗黙的に定義されることがある特別なメンバ関数
 * 
 * 以上に対する指定として
 * default,deleteがある
 * 
 * default
 *  暗黙的に定義されているものと同じものを明示的に定義可能
 * delete
 *  暗黙的に定義される特別なメンバ関数の削除を指定可能
 * 例：コピーを禁止する
 * 
*/
#include <bits/stdc++.h>
using namespace std;

//default
class Square{
public:
    //デフォルトコンストラクタ以外が存在するので暗黙定義は行われない
    //しかし書くのはめんどくさいのでdefault指定が欲しい
    Square() = default;
    explicit Square(int size) : size_(size){}

    void Print(){
        if(this->size_ == 0) cout << "default\n";
    }

private:
    int size_;
};

//delete:コピー禁止
class NonCopyable{
public:
    NonCopyable() = default;
    //相手は関係ないので変数はいらない
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

int main(){
    Square s1;
    Square s2(10);
    s1.Print();

    s2 = s1; //OK

    NonCopyable n1;
    NonCopyable n2;
    //n2 = n1; //error


}