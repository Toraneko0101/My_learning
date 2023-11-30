#include <bits/stdc++.h>
using namespace std;

/**
 * std::viewsはstd::ranges::viewsのエイリアス
*/
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
    // a.end() != a.find(val)とする必要がなくなった
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
    //transform:全ての要素に関数を適用して返す
    for(auto i: views::transform(a2, [](int i){return i * 2;})){
        cout << i << "\n";
    }

    //join:要素の連結を返す:別の範囲を1つの結合された範囲とする
    for(auto i: views::join(vector{a2,a2})){
        cout << i << "\n";
    }

    //iteratorからn個先までの要素を返す
    for(auto i: views::counted(a2.begin(),2)){
        cout << i <<"\n";
    }

    //連想班列のkeyのみを取り出す
    //valueを取り出したい場合は、std::views::values
    for(auto i: views::keys(map<int, int>{{1,2},{2,3}})){
        cout << i << "\n";
    }

    //逆順はviews::reverse

    /**
     * パイプライン記法で関数のネストを防ぐ
    */
    
    //0~9を2倍にして逆順にする
    for(auto i : views::iota(0,10)
        | views::transform([](int i){return i*2;})
        | views::reverse
    ){
        cout << i << " ";
    }
    cout << "\n";

    /**
     * 7. プロジェクション
     * ranges::sortに限らず、ranges::lower_boundなどの
     * 比較関数を取る別のアルゴリズム関数にも追加されている
    */
    vector<pair<int,int>> test = {
        {1,3},
        {2,2},
        {3,1}
    };
    //secondの値でsort
    ranges::sort(test, {}, [](auto p){return p.second; });
    cout << test.at(0).first << "\n";
    //降順ソート
    //第二引数に比較関数を返すと、第三引数の返り値をもとに比較が行われる
    //第二引数はオブジェクトなので初期化している?
    ranges::sort(test, ranges::greater(), [](auto p){return p.second;});
    cout << test.at(0).first << "\n";
    
    //呼び出しにstd::invokeを使っているので、secondへのメンバポインタを渡して簡潔な記述も可能
    /**
     * std::invokeでは通常の関数の呼び出しとメンバポインタ(::)を使ったメンバの取得を
     * 一般化して同じように扱える。
     * 引数
     * f: 関数ポインタ/関数obj/メンバポインタ
     * args... : fに与える引数列。fがメンバポインタなら対応するクラスのobjはargs...の先頭にある必要がある
     * 使い方の例
     * std::invoke(関数名, 引数, 引数)
     * つまり、ranges::sortの場合、比較関数がstd::invokeを使って呼び出されているので
     * (おそらくだが、第3引数に書いた値がfの部分に入るのだろうか)
    */
    ranges::sort(test, {}, &pair<int, int>::second);
    cout << test.at(0).first << "\n";
}