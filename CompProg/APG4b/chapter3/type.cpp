#include <bits/stdc++.h>
using namespace std;

int main(){
    //long long 64bit以上
    //int64_t 64bit固定
    //10LL等と書いておけばどのシステムでも動くはず

    //精度はストリーム経由で値を出力するためのもの
    //val == other 等の比較では、3.14159の値が使用される
    double x = 3.14159;
    streamsize ss = cout.precision();
    cout << "Initial precision: " << ss << "\n";
    cout << setprecision(3) << x << "\n";
    cout << setprecision(ss) << x << "\n";
    //精度の誤差を丸めるには以下を使う: fabs:浮動小数点の絶対値の計算
    if((fabs (x - 3.1415)) < 0.001) cout << "Yes" << endl;

    //C++20から
    cout << format("{:.3} {:.4}\n", x, x);

    //キャスト: 大きい場合は暗黙的代入
    cout << (int)x << endl;

    /**
     * double: 16桁の並びを保持可能
     * 差が極端に大きいと情報落ちする⇒小さい数から足していき影響を減らす
     * 差が極端に小さいと桁落ちする⇒1e-20を1e20回引いても何もひかれていないことになる
     * printf:
     * %d : int
     * %lld : int64_t
     * %lf : double
     * %c : char
     * 
     * scanfで受け取ることもできるが、scanfには問題があったはず
     * stringの場合は、おとなしくcinを使う
    */

   //数値 -> 文字列
   int num = 100;
   string s = to_string(num) + "neko";
   cout << s << "\n";
   /**
    * 文字列 -> int : stoi
    * 文字列 -> int64_t: stol
    * 文字列 -> double : stod
   */
   string str1 = "120";
   cout << stoi(s) + 70 << endl;

   /**
    * size_t: size()で返る要素数の型
    * 符号なしの整数型で、gccにおいてはunsigned long
    * 暗黙的にキャストするのでint等として扱って問題はない
    * しかし、size_tは符号なしの整数型なので、
    * data.size() -1などとするとsize()が空の場合に、-1とみなされずエラーを吐くので注意
    * 配列のサイズ-1だけループしたい場合は、(int)等でキャストする
    * 
   */
}