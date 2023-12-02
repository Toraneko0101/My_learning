#include <bits/stdc++.h>
using namespace std;

namespace ns1{
    class X {};
    inline namespace ns2{
        class Y{};

        void f(X){
            cout << "call f()" << "\n";
        }
    }

    void g(Y){
        cout << "call g()" << endl;
    }
}

//名前が不要な場合、必ずしも名前を付ける必要はない
void test(int, int y){
    cout << y << endl;
}
int main(){
    //インスタンス化
    f(ns1::X());
    g(ns1::Y()); //ns1::ns2とせずに使える
    g(ns1::ns2::Y());
    test(12,21);
}