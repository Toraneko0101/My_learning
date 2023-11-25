#include <bits/stdc++.h>
using namespace std;

namespace A{
    void f(){
        cout << "namespace A" << "\n";
    }
    namespace C{
        void f(){
            cout << "namespace A::C" << "\n";
        }
    }
}

namespace B{
    void f(){
        cout << "namespace B" << "\n";
    }
}

int main(){
    //名前空間::関数名
    A::f();
    B::f();
    A::C::f();
    namespace ac = A::C;
    ac::f(); //名前空間のエイリアス
    //viewsもnamespaceなのか?
    //using namespace 名前空間;と書くことで祖のスコープ内において、名前空間の指定を省略できる
    //using namespace std;とグローバルで書くことでstd::を省略しているわけだ

}