#include <bits/stdc++.h>
using namespace std;

int main(){
    bitset<4> a; //全て0
    //bitset<4> b("1001");
    bitset<4> b(9); //整数をbitsetに
    //特定の位置にbitをset
    b.set(3, 0);
    auto c = ~a;
    //第二引数がないと、1になる
    c.set(3,0);
    c^= b;
    //特定の位置が1か調べる
    if(!c.test(3)) cout << "0!!!" << endl;
    cout << c << endl; //0110
    c.reset(2); //特定のbitをzero
    c.reset(); //全てのbitをzero
    c.flip(); //反転
    cout << c.all() << endl; //全てのbitが1か
    cout << c.any() << endl; //1つでも1があるか
    cout << c.count() << endl; //1を数える
    cout << c[1] << endl;//特定bitにアクセス
    //cout << c.to_string() << endl;//文字列型に変更
    cout << c.to_ullong() << endl;//数字型に変更
    /**
     * 整数型に応じてbit列の長さが固定されているので
     * bitsetが便利
     * bit演算の演算子は優先順位が低いものが多いので、
     * 明示的に()で囲む必要がある
    */

   /**
    * 0b11で2進数リテラルが書ける
    * 計算量はO(N)だが、整数のbit演算を用いて、
    * 複数bitをまとめて処理するため64bit以内ならO(1)になる
    * 64bitを超える場合でも、O(N)より高速に動作することが多い
    * ※負の数を右シフトした場合は、空いたbitは1で埋められる
   */
}