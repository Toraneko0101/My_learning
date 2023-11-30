#include <bits/stdc++.h>
using namespace std;
/**
 * 新しい言語機能
 * 1. 普通の関数でもautoで引数宣言が可能に
 * 4．ラムダの拡張
 * 5. 丸括弧による構造体初期化
 * 6. 指示付き初期化
 * 7. 初期化式を伴う範囲for: C++23ではenumerateが使えそう
 * 8. 一貫比較：宇宙演算子
 * 9. コンセプト
*/


//1
template<auto x>
auto func(auto y){
    return x + y;
}

//5
struct S{
    int x, y;
};

struct S1{
    int x, y, z;
};

//8
struct Hoge{
    int n;
    vector<double> a;
    //a <=> bは、a<bならマイナス、a > bならプラス。==なら0となる
    //デフォルト実装でよければ実装は大幅に省略可能
    //operator<=>から他の比較演算子の結果が求まるので<=などは暗黙定義が可能
    constexpr auto operator<=>(const Hoge&) const = default;
};


//9
template <class T, class U>
concept Addable = requires(T& x, U& y){
    x + y;
    y + x;
};

int main(){
    cout << func<2>(4) << "\n";

    //4
    auto func1 = []<class T>(T a, T b){
        return a > b;
    };

    vector<int> c = {1,2,3};
    sort(c.begin(), c.end(), func1);
    cout << c.at(0) << "\n";

    //5
    //変数の初期化ができるようになったわけではない
    int a1[](1,2,3);
    // int a[] = (1,2,3) //error
    S a2[]({1,2},{2,3});//構造体Sの配列
    cout << a2[0].x << "\n";
    S a3(1,2);
    cout << a3.x << "\n";
    cout << invoke(&S::y, a3) << "\n";

    //6
    //変数を指定して初期化可能
    //変数の順序は固定である必要がある
    S1 d1{.x{1}, .y{2}, .z{3}};
    S1 d2{.x = 1, .y = 2, .z = 3};
    cout << d2.x << endl;

    //7
    for(int idx = 0; auto i: {1,2,3}){
        cout << idx << ":" << i << "\n";
        ++idx;
    }

    cout << boolalpha << ( Hoge{1,{1,2,3}} < Hoge{1,{1,3,1}} ) << "\n";
    cout << boolalpha << ( Hoge{1,{1,2,3}} >= Hoge{1,{1,3,1}} ) << "\n";

    //9.コンセプト：型のふるまいによってtemplateを制約できる機能
    //requires式
    //この中に書かれた式がコンパイルエラーなしで評価できる場合はtrueとなる
    cout << boolalpha << requires(int x, double y){
        x + y;
        y + x;
    } << "\n";

    if(Addable<int, double>){
        int x = 1;
        double y = 1.02;

        cout << x + y << endl;
    }else{
        cout << "can't" << "\n";
    }
}