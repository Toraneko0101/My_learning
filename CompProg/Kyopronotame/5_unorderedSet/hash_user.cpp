#include <bits/stdc++.h>
using namespace std;
/**
 * 自作クラスに対してunordered_setを使う方法
*/

class MyClass{
public:
    int value;
    MyClass(int v) : value(v){}

    //()の後のconstで関数内でのメンバ変数の書き換えが不可に
    bool operator==(const MyClass& other) const{
        return value == other.value;
    }
};

struct MyClassHash{
    std::size_t operator()(const MyClass& myClass) const{
        return std::hash<int>()(myClass.value); //int型の値、myClass.valueに対するハッシュ値を求める。
    }
};

int main(){
    std::unordered_set<MyClass, MyClassHash> mySet;
    mySet.insert(MyClass(1));
    mySet.insert(MyClass(2));

    for(auto m: mySet){
        cout << m.value << endl;
    }
}