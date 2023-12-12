/**
 * std::ios::sync_with_stdio(false)
 * C++の入出力ストリームとC言語の入出力ストリームの同期を切る
 * 
 * 同期が有効だとどうなるの?
 * ・C++とCの入出力ストリームが混在する際の順序や内容の正確性の保証
 * ・複数スレッドからC++の入出力ストリームを使用した場合のデータ競合の防止
 * ⇒これらを使わない、つまり、scanf, printf, puts等を使わず、複数スレッドからC++の入出力ストリームを使用しないプログラム
 * の場合、同期は切れる
 * ⇒切ると、入出力に関する実行時間を短縮可能
 * ⇒プログラムの途中で切ると、その前に行った入出力では何が起きるかは実行依存なので、最初で切るべき
 * 
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    //本当に短縮になっているかは不明
    std::ios::sync_with_stdio(false);
    vector<int> v(100000);
    // std::ranges::iota(v, 0); C++23
    std::iota(v.begin(), v.end(), 0);

    for(const auto& n: v) cout << n << " ";
    cout << "\n";
}