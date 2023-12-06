#include <bits/stdc++.h>
using namespace std;

struct Print{
    Print() {cout << __func__ << endl;}
    void operator()(const int &value) const {cout << "int: " << value << "\n"; }
    void operator()(const double &value) const {cout << "double: " << value << "\n"; }
    void operator()(const string &value) const {cout << "string: " << value << "\n"; }
};

int main(){
    std::variant<int, double ,string> var;
    var = "Hello";
    //第一引数には関数objやラムダ式、第二引数以降が、それに対する実引数
    //引数の型に応じた関数オーバーロードを呼び出す
    
    //print関数objの適切なメソッドを呼び出す
    std::visit(Print{}, var); //stringなので、三つ目のoperatorが呼ばれる

    var = 12;
    std::visit(Print{}, var);

    //全ての候補型で共通の操作を粉う場合
    std::variant<int, double, string> v;
    v = "Neko";
    std::visit([](const auto& x){
        cout << x << endl;
    },v);

    /**
     * variantの値の型はコンパイル時には既知
     * 実際の訪問先の関数はtemplateの特殊化として生成される
     * そのため候補型が増えると、コンパイル時の特殊化にかかる時間は増える
     * しかし通常は影響は小さく、利用価値が高いはず
    */
}