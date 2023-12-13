/**
 * 変換コンストラクタとexplict
 * std::string str = my_classなどで変換コンストラクタは使えそう
 * 
 * 
*/
#include <bits/stdc++.h>
using namespace std;

class MyClass{
public:

    //MyClass(int _value) : value(_value){}
    //explicit修飾子をつける
    explicit MyClass(int _value) : value(_value){}

    void printData() const{
        cout << value << endl;
    }

private:
    int value;

};

int main(){
    //1引数の変換コンストラクタが呼ばれる
    //explicit無し:int -> MyClassへの暗黙の型変換が行われる
    //MyClass obj = 42  , MyClass obj(42);
    //MyClass obj = 42; 
    
    //explicit有り: 暗黙の型変換を禁止できる
    //MyClass obj = 42; //error
    MyClass obj(42);
    obj.printData();

}