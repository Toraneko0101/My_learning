/**
 * ムーブコンストラクタ
 *  該当クラスの右辺値参照だけを受け取るコンストラクタx
 *  ⇒これを定義すると、コピーコンストラクタが暗黙定義されなくなる
 * 
 * コピーコンストラクタや、ムーブ代入演算子
 * デストラクタが明示的に定義されていると暗黙的なムーブコンストラクタの定義は行われない
 * 
*/
#include <bits/stdc++.h>
using namespace std;

class MyClass{
public:
    //配列を確保して初期化
    MyClass(int _size) : data(make_shared<int[]>(_size)), size(_size){}//default
    //copy
    MyClass(const MyClass& other) :
        size(other.size)
    {
        for(int i=0; i<size; ++i){
            data[i] = other.data[i];
        }
    }

    //move
    MyClass(MyClass&& other) noexcept:
        data(std::move(other.data)),
        size(other.size){}

    shared_ptr<int[]> data;
    int size;
};


int main(){
    MyClass m1(20);
    m1.data[0] = 291;
    MyClass m2 = std::move(m1);
    cout << m2.size << endl;
    cout << m2.data[0] << endl;
}