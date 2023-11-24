#include <bits/stdc++.h>
using namespace std;

int main(){
    //pairもtupleも1番目の値から比較される
    pair<string, int> p("abc", 3);
    cout << p.first << endl;
    cout << p.second << endl;

    //make_pair(val1, val2)でpair生成
    //tie(val1, val2) = pair型の値でpairを分解
    //make_pairによる生成方法の方が、型を明示しなくていい
    //型エイリアスを用いてpairの型に簡単な名前を付ける場合は、後者も選択肢に入る
    p = make_pair("*", 1);
    string s;
    int a;
    tie(s, a) = p;
    cout << s << endl;
    cout << a << endl;
    cout << p.first << endl;

}