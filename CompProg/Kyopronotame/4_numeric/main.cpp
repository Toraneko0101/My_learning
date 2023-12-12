#include <bits/stdc++.h>
using namespace std;

int main(){
    //reduce(順不同で要素を計算)
    //一般の場合、並列実行のための追加のパラメータを渡さない限り順番は前後しないが
    //保証もされていない
    //戻り値の型はinitの型に依存する⇒今回は1LLなのでlong long型
    //initがない場合、戻り値の型は配列の要素で決まる
    vector<int> v1(10);
    std::iota(v1.begin(), v1.end(), 1);

    long long mul = std::reduce(v1.begin(), v1.end(), 1LL, [](int a, int b){
        return a*b;
    });
    cout << mul << endl;

    //accumulate
    //先頭から順に計算していくので順不同ではない
    //reduceと異なり、戻り値は不可欠なので注意
    vector<string> v = {"a", "b", "c", "d", "e"};
    string a = std::accumulate(v.begin(), v.end(), string());
    cout << a << "\n";

    //累積和
    vector<int> v2 = {1,2,3,4,5};
    vector<int> sums = {0};
    //sumsの末尾に結果を追加
    partial_sum(v2.begin(), v2.end(), back_inserter(sums));
    for(const auto &sum : sums) cout << sum << " ";
    cout << "\n";
    /**
     * back_inserter()
     * 挿入イテレータ
     * ・iteratorに対する代入処理を挿入処理に置き換える
     *  ・back_inserter
     *  ・front_inserter
     *  ・inserter
    */
    vector<int> v3 = {1,2,3};
    auto i = std::back_inserter(v3);
    *i = 4;
    *i = 5;
    i++; //挿入イテレータに対するincrement処理は可能だが、何も行われない
    *i = 6;
    copy(v3.begin(), v3.end(), ostream_iterator<int>(cout, " "));
    cout << "\n";

    //copy関数を応用した追加処理等が有名
    vector<int> v4 = {1,2,3};
    vector<int> v5 = {4,5,6};
    copy(v4.begin(), v4.end(), back_inserter(v4));
    //v4 = {1,2,3,4,5,6};
    /**
     * copy関数の内部処理
     * template<class B, class U, class V>
     * void copy(B begin, U end, V target){
     *      while(begin != end) *target++ = *begin++;
     * }
     * 実質的には、以下のような処理になる
     * backの箇所を1つずつずらしていって、代入していく
     * auto begin = w.begin();
     * auto target = std::back_inserter(v);
     * *target++ = *begin++;
     * *target++ = *begin++;
     * *target++ = *begin++;
     * 
    */

    //iota(itfirst, itlast, val)
    //iteratorで指定した範囲を、valから1ずつ増えていく値で埋める
    //charならalphabetで埋められる
    vector<char> v6(26);
    iota(v6.begin(), v6.end(), 'a');
    for(auto v: v6){cout << v << " "; }
    cout << "\n";
    string s(26, 'a');
    iota(s.begin(), s.end(), 'a');
    cout << s << endl;

    //gcd & lcm
    cout << gcd(100, 150) << "\n";
    cout << lcm(100,150) << "\n";

}

