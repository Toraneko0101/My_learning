#include <bits/stdc++.h>
using namespace std;

auto answer(){return 42;}
//constexprが付いた関数はコンパイル時に計算可能
//標準入出力、ファイルへの書き出し、乱数はコンパイル時には行えない
constexpr auto answer_constexpr(){return 42;}

constexpr int mul(const vector<int> &a){
    return reduce(a.begin(), a.end(), 1, [](int acc, int i){
        return acc * i;
    });
    //reduceのdefaultはsum
    // return reduce(a.begin(), a.end());
}
int main(){
    //1. コンテナのメンバ関数の追加
    // 1.1 連想配列にcontainsメンバ関数が追加
    //unordered_multisetは重複を許す
    unordered_set<int> a{1,2,3};
    unordered_map<string, int> b{
        {"neko", 1},
        {"inu", 2},
        {"lion", 3}
    };
    cout << boolalpha;
    cout << a.contains(1) << "\n"; //true
    cout << b.contains("tora") << "\n"; //false

    //1.2 文字列型にstarts_with, ends_withメンバ関数を追加
    string s = "Hello world!";
    cout << s.starts_with("Hello") << "\n"; //true
    cout << s.ends_with("world") << "\n"; //false

    //2. numbersヘッダ：様々な数学定数
    cout << numbers::e << "\n";
    cout << numbers::pi << "\n";
    //任意の浮動小数点型の定数
    cout << numbers::phi_v<long double> << "\n"; //黄金比の型指定
    cout << numbers::log2e << "\n";

    //format:Atcoderでは2023年現在使えないとか

    //3. bit
    //符号なし整数型として使う必要がある
    cout << bit_ceil((unsigned int)9) << "\n";
    cout << bit_floor(9u) << "\n";
    cout << bit_width(9u) << "\n"; //bitの幅
    cout << popcount(9u) << "\n"; //立っているbitの数
    //他にも両端の連続した0,1の数を返す関数がある
    cout << countl_zero(9u) << "\n"; //32bitであることに注意

    //4. constexpr
    /**
     * constexpr:コンパイル時に値を計算する
     * ⇒つまりコンパイル時に値が不定であればコンパイルエラー
     * ⇒使用するメモリが少なくなる
     * ⇒配列の添え字などに定数を使える
     * 
     * reduce
     * [first, last)を集計する関数
     * (first, last, init == 0, f == operator+)
     * 結果が、次の要素と組み合わせられ、また結果として返される
     * accumulateは集計順を規定しない
    */

   /**
    * 本題
    * 動的メモリ確保がコンパイル時に行えるようになったので
    * vecやstringがconstexpr化された
   */

    //int constexpr d = answer(); //error
    constexpr int d = answer_constexpr();
    int D[d];

    constexpr int result = mul({1,2,4});
    cout << result << "\n";

   //5 range
   /**
    * 開始イテレータと終了イテレータのペアがなくとも、範囲が直接使えるようになった
   */
  vector<int> a1 = {9,5,3}, b1 = {9,5,3};
  ranges::sort(a1);
  ranges::sort(b1.begin(), b1.end()); //今まで通りの使い方も可能
  cout << a1.at(0) << "\n";

  //6. view
  /**
   * iota_view; 範囲[l,r)を扱う
   * rep(i,n)マクロの代わりに使えそう
   * 
   * filter:条件を満たす要素のみを返す
  */
    for(auto i: views::iota(0,5)){
        cout << i << "\n";
    }
    //iteratorを入れる
    vector<int> a2 = {1,2,3};
    for(auto i: views::iota(a2.begin(), a2.end())){
        //i - a2.begin()はidx
        cout << i - a2.begin() << " " << *i << "\n";
    }
    //filter
    for(auto i: views::filter(a2, [](int i){return i % 2 == 1;})){
        cout << i << "\n";
    }



}