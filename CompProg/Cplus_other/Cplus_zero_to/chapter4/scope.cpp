#include <bits/stdc++.h>
using namespace std;

/**
 * 同一スコープ内でも引数の型が異なれば宣言可能
 * ⇒関数のオーバーロード
 * 
*/

/**
 * 同一の名前空間に属する場合は
 * スコープ解決演算子(::)による名前空間の指定は省略可能
 * 名前空間は入れ子にできる
 * 同一空間に指定したシンボルが見つからない場合、シンボルを探す範囲を
 * namespaceブロック毎に外に広げ、最初に見つかったものが使用される
 * ★スコープ解決演算子を用いると、内部の値を優先させることなく名前解決が可能
*/
namespace A{
    int count = 2;
    int another_count = 3;
    namespace AA{
        int count = 4;
        int GetCount(){return count;}
        int GetAnotherCount(){return another_count;}
    }
}
namespace B{
    int count = 3;
}

int x = 12;
int main(){
    cout << A::count << endl;
    cout << B::count << endl;
    int count = B::count;
    cout << count << endl;
    cout << A::AA::GetCount() << endl;
    cout << A::AA::GetAnotherCount() << endl; //3
    //明示的にグローバルスコープを指定
    int x = 10;
    cout << ::x << endl;
}

/**
 * 関数スコープ：関数内でだけ有効
 * ブロックスコープ:ブロック内でだけ有効
 * グローバルスコープ：宣言以降ならそこからでも利用可能
 * 
*/